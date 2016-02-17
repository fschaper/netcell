/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
*
*  This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU General Public License (Version 2) as published
*  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
*
*  This program is distributed in the hope that it will be useful, but WITHOUT
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
*  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
*  more details.
*
*  You should have reeved a copy of the GNU General Public License along with
*  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
*  Place, Suite 330, Boston, MA 02111-1307 USA
*
*  You may obtain a copy of the License at
*
*  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
*    http://www.jedox.com/license_palo_bi_suite.txt
*  </a>
*
*  If you are developing and distributing open source applications under the
*  GPL License, then you are free to use Worksheetserver under the GPL License.
*  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
*  and do not license and distribute their source code under the GPL, Jedox provides
*  a flexible OEM Commercial License.
*
*  \author
*  Florian Schaper <florian.schaper@jedox.com>
*/


#include "palo_cell_adapter.hpp"
#include "spreadsheet_function.hpp"
#include "connection_handler.hpp"

#include <libconnectionpool/ConnectionException.h>
#include <PaloSpreadsheetFuncs/DimensionElementInfo.h>
#include <PaloSpreadsheetFuncs/DimensionElementInfoArray.h>

#include "palo_cell_adapter_helpers.hpp"

adapter_iterator_not_dereferenceable_exception::adapter_iterator_not_dereferenceable_exception()
    : std::runtime_error( "iterator not dereferenceable!" )
{}

palo_context palo_cell_adapter::m_context;

palo_cell_adapter::palo_cell_adapter( session& s, variant& value, const bool is_retval /* = false */, const size_t rows /* = 0 */, const size_t cols /* = 0 */ )
    : m_value( value )
    , m_session( s )
    , m_is_retval( is_retval )
    , m_rows( rows )
    , m_cols( cols )
    , m_dont_pad( false )
    , m_subset_inside_nf( false )
{}

palo_cell_adapter::palo_cell_adapter( session& s )
    : m_value_ptr( new variant() )
    , m_value( *m_value_ptr )
    , m_session( s )
    , m_is_retval( false )
    , m_rows( 0 )
    , m_cols( 0 )
    , m_dont_pad( false )
    , m_subset_inside_nf( false )
{}

palo_cell_adapter::palo_cell_adapter( const palo_cell_adapter& other )
    : m_value_ptr( other.m_value_ptr.get() != NULL ? new variant( *other.m_value_ptr ) : NULL )
    , m_value( other.m_value_ptr.get() != NULL ? *m_value_ptr : other.m_value )
    , m_server( other.m_server )
    , m_session( other.m_session )
    , m_is_retval( other.m_is_retval )
    , m_rows( other.m_rows )
    , m_cols( other.m_cols )
    , m_dont_pad( false )
    , m_subset_inside_nf( other.m_subset_inside_nf )
{}

palo_cell_adapter::Type palo_cell_adapter::getType()
{
    if ( m_server ) {
        return TConnection;
    }

    switch ( m_value.type() ) {
        case variant::type_empty:
            return TNull;

        case variant::type_double:
            return TDouble;

        case variant::type_string:
            return TString;

        case variant::type_array:
            return TArray;

        case variant::type_bool:
            return TBool;

        default:
            return TOther;
    }
}

bool palo_cell_adapter::isMissing()
{
    return m_value.type() == variant::type_empty;
}

Palo::Types::ElementList palo_cell_adapter::getElementList()
{
    ElementList     ret;
    StringArray     content;
    switch ( m_value.type() ) {
        case variant::type_string:
        case variant::type_double:
        case variant::type_bool: {
            std::string  crt = m_value.as_string( m_session.locale() );
            if ( "*" == crt ) {
                ret.setAll();
                return ret;
            }
            content.push_back( crt );
        }
        break;
        case variant::type_array:
            for ( variant::variant_array_type::iterator it = m_value.array().begin(), end = m_value.array().end()
                    ; it != end
                    ; ++it ) {
                content.push_back( static_cast<variant>( ( *it ) ).as_string( m_session.locale() ) );
            }
            break;
        default:
            throw std::runtime_error( std::string( "Invalid argument: Requires Element List. Found: " ) + m_value.as_string( m_session.locale() ) );
    }
    ret.set( content );
    return ret;
}

bool palo_cell_adapter::empty( bool allelements )
{
    return ( ( m_value.is_string() && m_value.string().empty() ) || m_value.is_empty() ) && ! m_server;
}

GenericCell& palo_cell_adapter::setEmpty()
{
    m_value = variant();
    m_server.reset();
    return *this;
}

palo_cell_adapter::Iterator palo_cell_adapter::getArray()
{
    if ( m_value.type() != variant::type_array ) {
        variant tmp( variant::type_array );
        tmp.array().push_back( m_value );
        ( m_value ).swap( tmp );
    }
    return Iterator( new adapter_cell_iterator( m_session, m_value ) );
}

GenericCell::Iterator palo_cell_adapter::getMatrix( unsigned int& rows, unsigned int& cols )
{
    GenericCell::Iterator retval = getArray();
    if ( m_value.array().size() && static_cast<const variant&>( m_value.array()[0] ).type() == variant::type_array ) {
        rows = static_cast<unsigned int>( m_value.array().size() );
        cols = static_cast<unsigned int>( static_cast<const variant&>( m_value.array()[0] ).array().size() );
    } else {
        rows = static_cast<unsigned int>( m_value.array().size() ) / m_value.column_width();
        cols = static_cast<unsigned int>( m_value.column_width() );
    }
    return retval;
}

palo_cell_adapter::ServerSPtr palo_cell_adapter::getConnection( ConnectionPool& cp, std::string& database )
{
    using namespace jedox::palo;

    boost::shared_ptr<jedox::palo::Server> s;

    std::string t = getString();
    std::string::size_type i;
    if ( ( i = t.find( "/" ) ) != std::string::npos ) {
        database = t.substr( i );
        t.resize( i );
        if ( database.length() <= 1 ) {
            throw std::exception();
        } else {
            database = database.substr( 1 );
        }
    } else {
        database = "";
    }
    s = static_cast<connection_handler&>( cp ).get( m_session, t );

    if ( s == NULL ) {
        throw std::exception();
    }

    return s;
}

palo_cell_adapter::ServerSPtr palo_cell_adapter::getConnection( ConnectionPool& cp )
{
    using namespace jedox::palo;
    boost::shared_ptr<jedox::palo::Server> s;

    // TODO this should always be our pool!
    connection_handler* handler = dynamic_cast<connection_handler*>( &cp );
    if ( handler ) {
        s = handler->get( m_session, getString() );
    } else {
        s = connection_handler::instance().get( m_session, getString() );
    }

    if ( s == NULL ) {
        throw ConnectionException( CurrentSourceLocation, "Unknown connection." );
    }
    return s;
}

std::string palo_cell_adapter::getString()
{
    return m_value.as_string( m_session.locale() );
}

long int palo_cell_adapter::getSLong()
{
    return static_cast<long int>( m_value.as_double() );
}

unsigned long int palo_cell_adapter::getULong()
{
    return static_cast<unsigned long int>( m_value.as_double() );
}

unsigned int palo_cell_adapter::getUInt()
{
    return static_cast<unsigned int>( m_value.as_double() );
}

int palo_cell_adapter::getSInt()
{
    return static_cast<int>( m_value.as_double() );
}

bool palo_cell_adapter::getBool()
{
    return m_value.as_double() == 1.0;
}

double palo_cell_adapter::getDouble()
{
    return m_value.as_double();
}
ConsolidationElementArray palo_cell_adapter::getConsolidationElementArray()
{
    ConsolidationElementArray cea;

    cea.reserve( getArray().minRemaining() );

    for ( GenericCell::Iterator i = getArray(); !i.end(); ++i ) {
        ConsolidationElement ce;

        ce.name = i->getString();
        ++i;
        if ( i.end() ) {
            throw std::exception();
        }
        ce.weight = i->getDouble();

        cea.push_back( ce );
    }

    return cea;
}

GenericCell& palo_cell_adapter::set( ServerSPtr s )
{
    m_server = s;
    m_value = variant();
    return *this;
}

GenericCell& palo_cell_adapter::set( int i )
{
    m_value = variant( static_cast<double>( i ) );
    return *this;
}

GenericCell& palo_cell_adapter::set( unsigned int i )
{
    m_value = variant( static_cast<double>( i ) );
    return *this;
}

GenericCell& palo_cell_adapter::set( long int i )
{
    m_value = variant( static_cast<double>( i ) );
    return *this;
}

GenericCell& palo_cell_adapter::set( double d )
{
    m_value = variant( d );
    return *this;
}

GenericCell& palo_cell_adapter::set( long double d )
{
    m_value = variant( static_cast<double>( d ) );
    return *this;
}

GenericCell& palo_cell_adapter::set( const std::string& s )
{
    m_value = variant( s );
    return *this;
}

GenericCell& palo_cell_adapter::set( const char* s )
{
    m_value = variant( std::string( s ) );
    return *this;
}

GenericCell& palo_cell_adapter::set( bool b )
{
    m_value = variant( b );
    return *this;
}

GenericCell& palo_cell_adapter::set( const ConsolidationElementInfoArray& ea )
{
    typedef palo_cell_adapter_helper<get_types_and_static_data<ConsolidationElementInfoArray>::helper_type> helper_type;
    helper_type::handle_entries( *this, ea, m_is_retval, m_cols, m_rows, m_value, m_subset_inside_nf );
    return *this;
}

GenericCell& palo_cell_adapter::set( const DimensionElementInfoSimpleArray& ei )
{
    typedef palo_cell_adapter_helper<get_types_and_static_data<DimensionElementInfoSimpleArray>::helper_type> helper_type;
    helper_type::handle_entries( *this, ei, m_is_retval, m_cols, m_rows, m_value, m_subset_inside_nf );
    return *this;
}

GenericCell& palo_cell_adapter::set( const ConsolidationElementInfo& ei )
{
    throw std::exception();
}

GenericCell& palo_cell_adapter::set( const DimensionElementInfo& ei )
{
    throw  std::exception();
}

GenericCell& palo_cell_adapter::set( const DimensionElementInfoSimple& ei )
{
    throw  std::exception();
}

GenericCell& palo_cell_adapter::set( const SubsetResults& es )
{
    typedef palo_cell_adapter_helper<get_types_and_static_data<SubsetResults>::helper_type> subset_entries_helper_type;
    subset_entries_helper_type::handle_entries( *this, es, m_is_retval, m_cols, m_rows, m_value, m_subset_inside_nf );
    return *this;
}

GenericCell& palo_cell_adapter::set( unsigned long int i )
{
    m_value = variant( static_cast<double>( i ) );
    return *this;
}

#ifdef WIN64
GenericCell& palo_cell_adapter::set( size_t n )
{
    m_value = variant( static_cast<double>( i ) );
    return *this;
}

#endif

GenericCell& palo_cell_adapter::setError( const Palo::Types::ErrorInfo& error_info, bool SetErrorDesc  )
{
    switch ( error_info.errcode ) {
        case Palo::Types::XLError::DIVxl:
            m_value = variant( variant::error_div_null );
            break;

        case Palo::Types::XLError::NAMExl:
            m_value = variant( variant::error_name );
            break;

        case Palo::Types::XLError::NAxl:
            m_value = variant( variant::error_n_a );
            break;

        case Palo::Types::XLError::NULLxl:
            m_value = variant( variant::error_null );
            break;

        case Palo::Types::XLError::NUMxl:
            m_value = variant( variant::error_num );
            break;

        case Palo::Types::XLError::REFxl:
            m_value = variant( variant::error_ref );
            break;

        case Palo::Types::XLError::VALUExl:
            m_value = variant( variant::error_value );
            break;

        default:
            assert( !"unknown error type" );
    }

    return *this;
}

GenericCell& palo_cell_adapter::setNull()
{
    m_value = variant();
    return *this;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

palo_cell_adapter::ArrayBuilder palo_cell_adapter::setArray( size_t length, bool pad )
{
    // transpose or not
    bool return_column = m_rows >= m_cols && ( m_rows > 3  || m_cols == 1 );

    return setMatrix( return_column ? length : 1, return_column ? 1 : length, !pad ? false : ( m_is_retval && !m_dont_pad ) );
}
palo_cell_adapter::ArrayBuilder palo_cell_adapter::setMatrix()
{
    return internal_setMatrix( m_rows, m_cols, m_is_retval );
}
palo_cell_adapter::ArrayBuilder palo_cell_adapter::setMatrix( size_t rows, size_t cols )
{
    m_value.column_width( static_cast<unsigned int>( cols ) );

    return ArrayBuilder( new AdapterArrayBuilder( m_session, m_value, rows, cols, rows, cols, m_is_retval, std::min<size_t>( cols, m_cols ) ) );
}

palo_cell_adapter::ArrayBuilder palo_cell_adapter::setMatrix( size_t rows, size_t cols, bool pad )
{
    return internal_setMatrix( rows, cols, pad );
}
palo_cell_adapter::ArrayBuilder palo_cell_adapter::internal_setMatrix( size_t rows, size_t cols, bool pad )
{
    m_value.column_width( static_cast<unsigned int>( cols ) );

    return ArrayBuilder( new AdapterArrayBuilder( m_session, m_value, rows, cols, m_rows, m_cols, pad, m_cols ) );
}

std::auto_ptr<GenericCell> palo_cell_adapter::create() const
{
    return std::auto_ptr<GenericCell>( new palo_cell_adapter( m_session ) );
}

std::auto_ptr<GenericCell> palo_cell_adapter::clone() const
{
    return std::auto_ptr<GenericCell>( new palo_cell_adapter( *this ) );
}

palo_cell_adapter::AdapterArrayBuilder::AdapterArrayBuilder( session& s, variant& value, size_t rows, size_t cols, size_t real_rows, size_t real_cols, bool pad_to_caller, size_t cols_to_set )
    : m_value( value )
    , m_session( s )
    , pad( pad_to_caller )
    , rows( rows )
    , cols( cols == 0 ? 3 : cols )
    , real_rows( real_rows )
    , real_cols( real_cols == 0 ? 3 : real_cols )
    , cols_to_set( cols_to_set )
{
    m_value = variant( variant::type_array );
    m_value.column_width( static_cast<unsigned int>( cols ) );
}

std::auto_ptr<GenericCell> palo_cell_adapter::AdapterArrayBuilder::createGenericCell()
{
    return std::auto_ptr<GenericCell>( new palo_cell_adapter( m_session ) );
}

void palo_cell_adapter::AdapterArrayBuilder::append( GenericCell& v )
{
    assert( m_value.type() == variant::type_array );
    switch ( v.getType() ) {
        case GenericCell::TString:
            m_value.array().push_back( variant( v.getString() ) );
            break;

        case GenericCell::TInt:
            m_value.array().push_back( variant( static_cast<double>( v.getSInt() ) ) );
            break;

        case GenericCell::TDouble:
            m_value.array().push_back( variant( v.getDouble() ) );
            break;

        case GenericCell::TArray: {
            for ( GenericCellIterator it( v.getArray() ); !it.end(); ++it ) {
                append( *it );
            }
        }
        break;

        case GenericCell::TBool:
            m_value.array().push_back( v.getBool() );
            break;

        case GenericCell::TNull:
            m_value.array().push_back( variant() );
            break;

        default:
            assert( !"unknown generic cell type"  );
            break;
    }
}

void palo_cell_adapter::setSubsetResult( GenericArrayBuilder& a, const SubsetResult& e, unsigned int num_entries )
{
    if ( num_entries >= 3 ) {
        a.append( "indent", a.createGenericCell()->set( e.idx ) );
    }

    a.append( "name", a.createGenericCell()->set( e.name ) );

    if ( num_entries >= 2 ) {
        a.append( "alias", a.createGenericCell()->set( e.alias ) );
    }
}

void palo_cell_adapter::setDimensionElementInfoSimple( GenericArrayBuilder& a, const DimensionElementInfoSimple& dis, unsigned int num_entries )
{
    a.append( "name", a.createGenericCell()->set( dis.name ) );

    if ( num_entries >= 2 ) {
        a.append( "type", a.createGenericCell()->set( dis.type ) );
    }

    if ( num_entries >= 3 ) {
        a.append( "identifier", a.createGenericCell()->set( dis.identifier ) );
    }
}

void palo_cell_adapter::setConsolidationElementInfo( GenericArrayBuilder& a, const ConsolidationElementInfo& e, unsigned int num_entries )
{
    a.append( "name", a.createGenericCell()->set( e.name ) );

    if ( num_entries >= 2 ) {
        a.append( "weight", a.createGenericCell()->set( e.weight ) );
    }

    if ( num_entries >= 3 ) {
        a.append( "type", a.createGenericCell()->set( e.type ) );
    }

    if ( num_entries >= 4 ) {
        a.append( "identifier", a.createGenericCell()->set( e.identifier ) );
    }
}

void palo_cell_adapter::AdapterArrayBuilder::append( const std::string /*key*/, GenericCell& v )
{
    append( v );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

palo_cell_adapter::adapter_cell_iterator::adapter_cell_iterator( session& s, variant& value )
    : m_session( s )
{
    assert( "variant need be of array type!" && value.type() == variant::type_array );
    // fill the sparse vector with real elements
    value.array().fill_to_size();

    for ( variant::sparse_array_type::iterator it = value.array().begin(), end = value.array().end();
            it != end;
            ++it ) {
        // well, isn't this ugly? but since we filled the vector up to size we are safe
        // with the believe that we deal with an real value and not an proxy object.
        variant& current = const_cast<variant&>( static_cast<const variant&>( *it ) );

        // TODO: do we still need this?
        // HACK: since we introduces multi-dimensional arrays (row/column separator)
        // we have to normalize our array at this point.
        if ( current.is_array() ) {
            current.array().fill_to_size();
            for ( variant::sparse_array_type::iterator iit = current.array().begin(), iend = current.array().end(); iit != iend; ++iit ) {
                variant& inner_current = const_cast<variant&>( static_cast<const variant&>( *iit ) );
                m_palo_cell_adapter_table.push_back( new palo_cell_adapter( m_session, inner_current ) );
            }

        } else {
            m_palo_cell_adapter_table.push_back( new palo_cell_adapter( m_session, current ) );
        }
    }
    m_current = m_palo_cell_adapter_table.begin();
}

GenericCell* palo_cell_adapter::adapter_cell_iterator::operator->()
{
    if ( m_current == m_palo_cell_adapter_table.end() ) {
        throw adapter_iterator_not_dereferenceable_exception();
    }
    return &*m_current;
}

GenericCellIteratorImpl& palo_cell_adapter::adapter_cell_iterator::operator++()
{
    ++m_current;
    return *this;
}

GenericCell* palo_cell_adapter::adapter_cell_iterator::release()
{
    return new palo_cell_adapter( *m_current );
}

bool palo_cell_adapter::adapter_cell_iterator::end() const
{
    return m_current == m_palo_cell_adapter_table.end();
}

size_t palo_cell_adapter::adapter_cell_iterator::minRemaining() const
{
    return std::distance( static_cast<PaloCellAdapterTable::const_iterator>( m_current ), m_palo_cell_adapter_table.end() );
}

template<unsigned int max_entries, typename MultiColumn, typename Functor>
GenericCell& palo_cell_adapter::set( const std::vector<MultiColumn>& mc, Functor setter )
{
    BOOST_STATIC_ASSERT( sizeof( MultiColumn ) == 0 );

    bool is_vertical = true;                   // return as column
    size_t num_entries = static_cast<size_t>( max_entries ); // return everything

    if ( m_is_retval ) {
        if ( m_cols > 3 && m_cols >= m_rows ) {
            is_vertical = false;
            num_entries = m_rows;
        } else {
            num_entries = m_cols;
        }

        if ( num_entries > max_entries || num_entries == 0 ) {
            num_entries = max_entries;
        }
    }

    const size_t rows_to_use = is_vertical ? mc.size() : num_entries;
    const size_t cols_to_use = is_vertical ? ( num_entries == 0 ? static_cast<size_t>( max_entries ) : num_entries ) : mc.size();

    GenericArrayBuilder a = setMatrix( rows_to_use, cols_to_use );

    for ( typename std::vector<MultiColumn>::const_iterator i = mc.begin(); i != mc.end(); ++i ) {
        const MultiColumn& mcr = *i;

        setter( a, mcr, static_cast<unsigned int>( num_entries ) );
    }

    if ( !is_vertical ) {
        a.transpose();
    }

    return *this;
}


GenericCell& palo_cell_adapter::supressPadding()
{
    m_dont_pad = true;
    return *this;
}

const std::string GenericCell::ELEMENTS_ALL = "*";

void palo_cell_adapter::AdapterArrayBuilder::transpose()
{
    if ( m_value.type() != variant::type_array ) {
        return;
    } else if ( rows == 1 || cols == 1 ) {
        return;
    }

    variant::variant_array_type a;
    variant::variant_array_type& old_a = m_value.array();

    a.reserve( old_a.size() );

    for ( unsigned int i = 0; i < rows; i++ )
        for ( unsigned int j = 0; j < cols; j++ ) {
            a.push_back( old_a[j * rows + i] );
        }

    variant tmp( a );
    m_value.swap( tmp );
    m_value.column_width( static_cast<unsigned int>( cols ) );
}

palo_cell_adapter::AdapterArrayBuilder::~AdapterArrayBuilder()
{
    if ( pad ) {
        if ( !( cols_to_set == 0 ) ) {
            variant::variant_array_type a;
            variant::variant_array_type& old_a = m_value.array();

            a.resize( real_rows * std::max<size_t>( std::max<size_t>( cols, real_cols ), cols_to_set ) );

            const size_t stop_col = std::min<size_t>( real_cols, std::min<size_t>( cols, cols_to_set ) );
            const size_t stop_row = std::min<size_t>( real_rows, rows );


            for ( size_t row = 0; row < stop_row; ++row ) {
                size_t col = 0;
                for ( ; row < rows && col < stop_col; ++col ) {
                    a.set( row * stop_col + col, old_a[row * cols + col] );
                }
            }

            variant tmp( a );
            m_value.swap( tmp );
            m_value.column_width( static_cast<unsigned int>( cols_to_set ) );
        } else {
            m_value.column_width( 3 );
        }
    }
}
