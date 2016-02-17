/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
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
 *  You should have received a copy of the GNU General Public License along with
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

#include "precompiled_header.hpp"
#include "wss/variant_conversion_exception.hpp"
#include "wss/variant.hpp"
#include "wss/translation_table.hpp"
#include "oxml/custom_data.hpp"

/*!
 * \brief
 *
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class variant::arrayize
{
public:
    arrayize( const variant& source );

    bool has_next() const;

    const variant& next();

    variant::sparse_array_type::size_type max_size() const;

private:
    const variant& m_source;
    variant::sparse_array_type::size_type m_index;
};

variant::arrayize::arrayize( const variant& source )
    : m_source( source )
    , m_index( 0 )
{}

bool variant::arrayize::has_next() const
{
    return m_source.is_array() ? m_index < m_source.array().size() : true;
}

const variant& variant::arrayize::next()
{
    return m_source.is_array() ? m_source.array()[ m_index++ ] : m_source;
}

variant::sparse_array_type::size_type variant::arrayize::max_size() const
{
    return m_source.is_array() ? m_source.array().size() : 0;
}

//////////////////////////////////////////////////////////////////////////

variant::variant()
    : m_value_type( type_empty )
    , m_double( 0.0 )
{}

variant::variant( double d )
    : m_value_type( type_double )
    , m_double( d )
{}

variant::variant( bool b )
    : m_value_type( type_bool )
    , m_double( b ? 1 : 0 )
{}

variant::variant( const char* s )
    : m_value_type( type_string )
    , m_double( 0.0 )
    , m_string( new std::string( s ) )
{}

variant::variant( const std::string& s )
    : m_value_type( type_string )
    , m_double( 0.0 )
    , m_string( new std::string( s ) )
{}

variant::variant( boost::shared_ptr<std::string> s )
    : m_value_type( type_string )
    , m_double( 0.0 )
    , m_string( s )
{}

variant::variant( error_type error )
    : m_value_type( type_error )
    , m_double( error )
{}

variant::variant( variant_type v_type )
    : m_value_type( v_type )
    , m_double( 0.0 )
{
    switch ( v_type ) {
        case type_string:
            m_string.reset( new std::string() );
            break;
        case type_array:
            m_array.reset( new sparse_array_type() );
            break;
        case type_error:
            m_double = error_value;
            break;

        default:
            break;
    }
}

variant::variant( const variant& other )
    : m_value_type( other.m_value_type )
    , m_double( other.m_double )
{
    switch ( other.type() ) {
        case type_string:
            m_string = const_cast<variant&>( other ).m_string;
            break;
        case type_array:
            m_array = const_cast<variant&>( other ).m_array;
            break;
        case type_error: {
            if ( other.m_string.get() != NULL ) {
                m_string = const_cast<variant&>( other ).m_string;
            }
            break;

        }
        default:
            break;
    }
}

variant::variant( const sparse_array_type& array, unsigned int column_width /*= 1 */ )
    : m_value_type( type_array )
    , m_double( column_width )
{
    m_array.reset( new sparse_array_type( array ) );
}

variant::variant( boost::shared_ptr<sparse_array_type> array, unsigned int column_width /*= 1 */ )
    : m_value_type( type_array )
    , m_double( column_width )
    , m_array ( array )
{}

variant::variant( sparse_array_type& array, unsigned int column_width /*= 1 */ )
    : m_value_type( type_array )
    , m_double( column_width )
{
    m_array.reset( new sparse_array_type( array ) );
}

void variant::swap( variant& other )
{
    // we swap both values here to be able to "early exit"
    // the method in case we are dealing with a string/string
    // array/array swap operation.
    std::swap( other.m_value_type, m_value_type );
    std::swap( other.m_double, m_double );

    // is one of the two variants of string type?
    if ( other.m_string.get() != NULL || m_string.get() != NULL ) {
        if ( ( other.m_value_type == m_value_type ) && ( m_value_type == type_string ) ) {
            // both were of string type, we are done and may return.
            m_string = other.m_string;
            return;
        } else {
            // in case both are of an different value type
            // we can simply exchange the auto_ptr content
            if ( other.m_string.get() ) {
                m_string = other.m_string;
            } else {
                other.m_string = m_string;
            }
        }
    }

    // test if one of the operands is of array type.
    if ( other.m_array.get() != NULL || m_array.get() != NULL ) {
        if ( other.m_value_type != m_value_type ) {
            // in case both are of an different value type
            // we can simply exchange the auto_ptr content
            if ( other.m_array.get() ) {
                m_array = other.m_array;
            } else {
                other.m_array = m_array;
            }
        } else {
            // both were of array type, we are done and may return.
            m_array = other.m_array;
            return;
        }
    }
}

variant& variant::operator=( const variant& rhs )
{
    if ( &rhs != this ) {
        variant tmp( rhs );
        swap( tmp );
    }
    return *this;
}

variant::variant_type variant::type() const
{
    return m_value_type;
}

bool variant::is_of_empty_value() const
{
    return ( ( type_empty == m_value_type )
             || ( is_string() && string().empty() )
             || ( is_array() && array().size() == 0 ) ) ? true : false;
}

bool variant::is_empty() const
{
    return type_empty == m_value_type;
}

bool variant::is_boolean() const
{
    return type_bool == m_value_type;
}

bool variant::is_double() const
{
    return type_double == m_value_type;
}

bool variant::is_error() const
{
    return type_error == m_value_type;
}

bool variant::is_array() const
{
    return type_array == m_value_type;
}

bool variant::is_string() const
{
    return type_string == m_value_type;
}

bool variant::is_numeric() const
{
    return is_error() || is_double() || is_boolean() || is_empty();
}

const std::string& variant::string() const
{
    if ( !( type_string == m_value_type ) ) {
        throw variant_conversion_exception( *this, "variant is not of string type!" );
    }
    return*m_string;
}

double variant::numeric() const
{
    if ( !( type_double == m_value_type || type_empty == m_value_type || type_bool == m_value_type ) ) {
        throw variant_conversion_exception( *this, "variant is not of double, empty or boolean type!" );
    }
    return m_double;
}

bool variant::boolean() const
{
    if ( !( type_double == m_value_type || type_empty == m_value_type || type_bool == m_value_type ) ) {
        throw variant_conversion_exception( *this,  "variant is not convertible to boolean type!" );
    }
    return m_double != 0.0;
}

variant::error_type variant::error_code() const
{
    if ( type_error != m_value_type ) {
        throw variant_conversion_exception( *this, "variant is not of error type!" );
    }
    return static_cast<error_type>( static_cast<unsigned int>( m_double ) );
}

variant::sparse_array_type& variant::array()
{
    if ( type_array != m_value_type ) {
        throw variant_conversion_exception( *this, "can not convert variant to array type!" );
    }
    return *m_array;
}

const variant::sparse_array_type& variant::array() const
{
    if ( type_array != m_value_type ) {
        throw variant_conversion_exception( *this, "can not convert variant to array type!" );
    }
    return *m_array;
}

std::string variant::as_string( const ::locale& l ) const
{
    static translation_table& table = translation_table::instance();

    switch ( type() ) {
        case variant::type_string:
            return*m_string;
            break;

        case variant::type_empty:
            return "";
            break;

        case variant::type_double:
            return boost::lexical_cast<std::string>( m_double );
            break;

        case variant::type_bool:
            return m_double != 0 ? table[ l ]->boolean_true() : table[ l ]->boolean_false();
            break;

        case variant::type_array: {
            //throw variant_conversion_exception( *this, "can not convert variant of array type to string!" );
            std::string  ret_array( "{" );
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, array().direct() ) {
                if ( ret_array == "{" ) {
                    ret_array += v.second.as_string( l );
                } else {
                    ret_array += ",";
                    ret_array += v.second.as_string( l );
                }
            }
            ret_array += "}";
            return ret_array;
        }

        case variant::type_error: {
            const translation_map::error_mapping::type& mapping = table[ l ]->error_translation();
            translation_map::error_mapping::type::const_iterator it( mapping.get<translation_map::error_mapping::code_tag>().find( error_code() ) );
            if ( it == mapping.end() ) {
                std::string error_value;
                switch ( error_code() ) {
                    case variant::error_div_null:
                        error_value = "#DIV/0!";
                        break;
                    case variant::error_n_a:
                        error_value = "#N/A!";
                        break;
                    case variant::error_name:
                        error_value = "#NAME!";
                        break;
                    case variant::error_null:
                        error_value = "#NULL!";
                        break;
                    case variant::error_num:
                        error_value = "#NUM!";
                        break;
                    case variant::error_ref:
                        error_value = "#REF!";
                        break;
                    case variant::error_value:
                        error_value = "#VALUE!";
                        break;
                    default:
                        throw std::runtime_error( "unknown error code in variant specified, error code is:\"" + boost::lexical_cast<std::string>( m_double ) + "\"" );
                }
            }
            return boost::to_upper_copy( it->second );
        }

        default:
            throw variant_conversion_exception( *this, "unknown conversion to string requested!" );
    }
}

double variant::as_double() const
{
    if ( type_array == m_value_type ) {
        if ( array().size() > 0 ) {
            return array()[0].as_double();
        }
    } else if ( type_error == m_value_type ) {
        throw variant_conversion_exception( *this, "can not convert variant of error type to double!" );
    } else if ( type_string == m_value_type ) {
        try {
            if ( m_string->empty() ) {
                return 0;
            } else {
                return boost::lexical_cast<double>( *m_string );
            }
        } catch ( const boost::bad_lexical_cast& ) {
            throw variant_conversion_exception( *this, "can not convert variant of type string to double!" );
        }
    }
    return m_double;
}

bool variant::as_boolean( const ::locale& l ) const
{
    if ( type_array == m_value_type ) {
        // if the default value of the sparse array evaluates to false and we have at least one
        // sparse value return false.
        if ( ! array().default_value().as_boolean( l ) && array().size() != array().direct().size() ) {
            return false;
        }
        for ( sparse_array_type::mapping_type::const_iterator current = array().direct().begin(), end = array().direct().end(); current != end; ++current ) {
            if ( ! current->second.as_boolean( l ) ) {
                return false;
            }
        }
        return true;
    } else if ( m_value_type == type_string ) {
        static translation_table& table = translation_table::instance();
        return boost::to_lower_copy( table[ l ]->boolean_true() ) == boost::to_lower_copy( string() );
    } else if ( m_value_type == type_error ) {
        throw variant_conversion_exception( *this, "can not convert error type to boolean!" );
    }
    return m_double != 0;
}

unsigned int variant::column_width() const
{
    return static_cast<unsigned int>( m_double ) ? static_cast<unsigned int>( m_double ) : 1 ;
}

void variant::column_width( unsigned int column_width )
{
    m_double = static_cast<double>( column_width );
}

#ifdef _DEBUG
void variant::dump() const
{
    switch ( type() ) {
        case type_empty:
            std::cout << "[EMPTY]";
            break;
        case type_string:
            std::cout << "[STRING:" << string() << "]";
            break;
        case type_double:
            std::cout << "[DOUBLE:" << numeric() << "]";
            break;
        case type_bool:
            std::cout << "[BOOL:" << boolean() << "]";
            break;
        case type_array: {
            std::cout << "[ARRAY:";
            sparse_array_type::const_iterator current( array().begin() );
            sparse_array_type::const_iterator end( array().end() );
            for ( ; current != end; ++current ) {
                ( *current ).dump();
            }
            std::cout << "]";
        }
        break;
        case type_error:
            std::cout << "[ERROR:" << numeric() << "]";
            break;
        default:
            assert( !"corrupt value or unknown type!" );
            break;
    }
}
#endif

bool variant::equals( const variant& other ) const
{
    //empty promotes to 0, empty string or false
    if ( type_empty ==  type() ) {
        switch ( other.type() ) {
            case type_double:
            case type_bool:
                return other.m_double == 0;
            case type_string:
                return other.m_string->empty();
            case type_empty:
                return true;
            default:
                return false;
        }
    } else if ( type_empty ==  other.type() ) {
        switch ( type() ) {
            case type_double:
            case type_bool:
                return m_double == 0;
            case type_string:
                return m_string->empty();
            default:
                return false;
        }
    }

    return *this == other;
}

bool variant::nequals( const variant& other ) const
{
    return !equals( other );
}

bool variant::operator==( const variant& other ) const
{
    if ( other.type() != type() ) {
        return false;
    }

    switch ( type() ) {
        case type_double:
        case type_bool:
        case type_empty:
            return other.numeric() == numeric();
            break;

        case type_error:
            return other.error_code() == error_code();
            break;

        case type_string:
            return *other.m_string == *m_string;
            break;

        case type_array:
            return other.array() == array();
            break;
    }
    return false;
}

bool variant::operator!=( const variant& other ) const
{
    return !( *this == other );
}

bool variant::operator>( const variant& other ) const
{
    if ( is_string() ) {
        if ( other.is_string() ) {
            return string() > other.string();
        } else {
            return true;
        }
    } else if ( other.is_string() ) {
        return false;
    }
    return numeric() > other.numeric();
}

bool variant::operator<( const variant& other ) const
{
    return other > *this;
}

bool variant::operator>=( const variant& other ) const
{
    return *this > other || *this == other;
}

bool variant::operator<=( const variant& other ) const
{
    return *this < other || *this == other;
}

variant variant::operator+( const variant& other ) const
{
    return variant( as_double() + other.as_double() );
}

variant variant::operator-( const variant& other ) const
{
    return variant( as_double() - other.as_double() );
}

variant variant::operator*( const variant& other ) const
{
    return variant( as_double() * other.as_double() );
}

variant variant::operator/( const variant& other ) const
{
    return variant( as_double() / other.as_double() );
}

variant variant::operator%( const variant& other ) const
{
    return variant( static_cast<double>( static_cast<long>( as_double() ) % static_cast<long>( other.as_double() ) ) );
}

bool variant::operator==( double rhs ) const
{
    return numeric() == rhs;
}

variant& variant::operator+=( const variant& other )
{
    to_numeric();
    m_double = numeric() + other.numeric();
    return *this;
}

variant& variant::operator-=( const variant& other )
{
    to_numeric();
    m_double = numeric() - other.numeric();
    return *this;
}

variant& variant::operator*=( const variant& other )
{
    to_numeric();
    m_double = numeric() * other.numeric();
    return *this;
}

variant& variant::operator/=( const variant& other )
{
    to_numeric();
    m_double = numeric() / other.numeric();
    return *this;
}

variant& variant::operator%=( const variant& other )
{
    to_numeric();
    m_double = static_cast<double>( static_cast<long>( numeric() ) % static_cast<long>( other.numeric() ) );
    return *this;
}

variant variant::pow( const variant& rhs ) const
{
    return std::pow( this->numeric(), rhs.numeric() );
}

variant variant::eq( const variant& rhs ) const
{
    return on_array < bool( variant::* )( const variant& ) const, &variant::equals > ( rhs, variant( true ) );
}

variant variant::neq( const variant& rhs ) const
{
    return on_array < bool( variant::* )( const variant& ) const, &variant::nequals > ( rhs, variant( false ) );
}

variant variant::le( const variant& rhs ) const
{
    return on_array < bool( variant::* )( const variant& ) const, &variant::operator <= > ( rhs, variant( true ) );
}

variant variant::gte( const variant& rhs ) const
{
    return on_array < bool( variant::* )( const variant& ) const, &variant::operator >= > ( rhs, variant( true ) );
}

variant variant::lt( const variant& rhs ) const
{
    return on_array < bool( variant::* )( const variant& ) const, &variant::operator < > ( rhs, variant( false ) );
}

variant variant::gt( const variant& rhs ) const
{
#if defined( WIN32 )
    return on_array < bool( variant::* )( const variant& ) const, ( &variant::operator > ) > ( rhs, variant( false ) );
#else
    return on_array < bool( variant::* )( const variant& ) const, &variant::operator > > ( rhs, variant( false ) );
#endif
}

variant variant::add( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::operator + > ( rhs );
}

variant variant::sub( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::operator - > ( rhs );
}

variant variant::mul( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::operator* > ( rhs );
}

variant variant::div( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::operator / > ( rhs );
}

variant variant::percent( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::operator % > ( rhs );
}

variant variant::exp( const variant& rhs ) const
{
    return on_array < variant( variant::* )( const variant& ) const, &variant::pow > ( rhs );
}

// TODO: (fschaper) we can make use of the fact that we deal with sparse vectors and
// don't have to iterate over the full range in most cases but make use
// of the underlying map structure and the default value for comparisons etc.
template < typename conversion_T, conversion_T callback >
variant variant::on_array( const variant& rhs, const variant& default_value /*= variant()*/ ) const
{
    unsigned int col_width = 0;
    if ( is_array() ) {
        col_width = this->column_width();
    }
    if ( rhs.is_array() && rhs.column_width() > col_width ) {
        col_width = rhs.column_width();
    }
    if ( rhs.is_array() || is_array() ) {
        arrayize a_lhs( *this );
        arrayize a_rhs( rhs );
        variant::sparse_array_type retval_array( default_value );
        retval_array.reserve( std::max( a_lhs.max_size(), a_rhs.max_size() ) );
        while ( a_lhs.has_next() && a_rhs.has_next() ) {
            try {
                retval_array.push_back( ( a_lhs.next().*callback )( a_rhs.next() ) );
            } catch ( const variant_conversion_exception& e ) {
                retval_array.push_back( e.operand() );
            }
        }
        return variant( retval_array, col_width );
    } else if ( rhs.is_error() || is_error() ) {
        return is_error() ? *this : rhs;
    } else {
        return ( ( *this ).*callback )( rhs );
    }
}

void variant::to_numeric()
{
    switch ( m_value_type ) {
        case type_double:
        case type_bool:
        case type_empty:
            m_value_type = type_double;
            break;

        case type_error:
        case type_string:
        case type_array:
            throw variant_conversion_exception( *this, "can not convert to numeric type!" );
            break;
        default:
            assert( !"variant is of unknown type" );
    }
}

void variant::serialize( spreadsheetml::CT_vt_value& data ) const
{
    switch ( m_value_type ) {
        case type_empty:
            data.vt_empty = "empty";
            break;

        case type_string:
            data.vt_string = string();
            break;

        case type_double:
            data.vt_number = numeric();
            break;

        case type_bool:
            data.vt_bool = numeric() != 0.0;
            break;

        case type_error:
            data.vt_error = static_cast< short >( error_code() );
            break;

        case type_array: {
            spreadsheetml::CT_vt_array  out_array;

            foreach( const variant::sparse_array_type::mapping_type::value_type & v, array().direct() ) {
                spreadsheetml::CT_vt_value crt_output;
                v.second.serialize( crt_output );
                out_array.vt_value.push_back( crt_output );
            }
            data.vt_array  = out_array;

        }
        break;

        //there shouldn't be any other possible types!
        default:
            assert( ! "serialize called for a ValueCell, but type wasn't any of type_string, type_numeric, type_boolean, type_error, type_array" );
    }
}

void variant::deserialize( const spreadsheetml::CT_vt_value& data )
{
    if ( data.vt_empty.present () ) {
        m_value_type = type_empty;
    } else if ( data.vt_bool.present() ) {
        m_value_type = type_bool;
        m_double = data.vt_bool.get();
    } else if ( data.vt_number.present() ) {
        m_value_type = type_double;
        m_double = data.vt_number.get();
    } else if ( data.vt_string.present() ) {
        m_value_type = type_string;
        m_string.reset( new std::string( data.vt_string.get() ) );
    } else if ( data.vt_error.present() ) {
        m_value_type = type_error;
        m_double = data.vt_error.get();
    } else if ( data.vt_array.present() ) {
        m_value_type = type_array;
        m_array.reset( new sparse_array_type( ) );

        for ( std::vector< spreadsheetml::CT_vt_value >::const_iterator i = data.vt_array.get().vt_value.begin(); i != data.vt_array.get().vt_value.end(); i++ ) {
            variant crt;
            crt.deserialize( *i );
            m_array->push_back( crt );
        }
    }
}

void variant::error_message( const std::string& msg )
{
    if ( type_error != m_value_type ) {
        throw variant_conversion_exception( *this, "can not set an error message on a variant that is not of error type!" );
    }
    m_string.reset( new std::string( msg ) );
}

std::string variant::error_message() const
{
    if ( is_error() && m_string.get() != NULL ) {
        return*m_string;
    }
    return "";
}

std::ostream& operator <<( std::ostream& os, const variant& v )
{
    switch ( v.type() ) {
        case variant::type_empty:
            os << "[EMPTY]";
            break;

        case variant::type_string:
            os << "[STRING:" << v.string() << "]";
            break;

        case variant::type_double:
            os << "[DOUBLE:" << v.numeric() << "]";
            break;

        case variant::type_bool:
            os << "[BOOL:" << v.boolean() << "]";
            break;

        case variant::type_array: {
            os << "[ARRAY:";
            variant::sparse_array_type::const_iterator current( v.array().begin() );
            variant::sparse_array_type::const_iterator end( v.array().end() );
            for ( ; current != end; ++current ) {
                os << *current;
            }
            os << "]";
        }
        break;

        case variant::type_error:
            os << "[ERROR:" << v.error_code() << "]";
            break;

        default:
            assert( !"corrupt value or unknown type!" );
            break;
    }
    return os;
}
