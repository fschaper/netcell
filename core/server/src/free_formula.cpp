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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/free_formula.hpp"

#include "wss/named_formula_exception.hpp"
#include "wss/calculation_context.hpp"
#include "wss/application.hpp"

#include "free_formula_impl.hpp"
#include "named_formula.hpp"

#ifdef _DEBUG
#include "debug_logging_helper.hpp"
#endif // _DEBUG

free_formula::free_formula( session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position /* = sheet_point */, const bool adjust_legacy_references /* = false */ )
    : m_unloading( false )
{
#ifdef _DEBUG
    ++m_counter;
#endif // _DEBUG
    m_formula = free_formula_impl::create( *this, s, v, ws, position, adjust_legacy_references );
}

free_formula::free_formula( const shared_free_formula_type& other, const geometry::point& distance, const bool is_rewrite_to_clone_sheet, const bool use_copy_move, const sheet_range& source_range, const sheet_point& position, const shared_worksheet_type& ws )
    : m_unloading( false )
{
#ifdef _DEBUG
    ++m_counter;
#endif // _DEBUG
    m_formula = free_formula_impl::create( *this, other->m_formula, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, position, ws );
}

free_formula::~free_formula()
{
#ifdef _DEBUG
    --m_counter;
#endif // _DEBUG
    m_unloading = true;
    unload_formula();
}


void free_formula::set_formula( const shared_ff_impl_type& new_formula )
{
    if ( !m_unloading ) {
        unload_formula();
        m_formula = new_formula;
    }
}

void free_formula::unload_formula()
{
    if ( m_formula ) {
        boost::shared_static_cast<free_formula_impl>( m_formula )->unload();
        if ( "use count should be 1 now! " && m_formula.use_count() != 1 ) {
            std::string this_could_be_an_assertion( "!" );
        }
        m_formula.reset();
    }
}

bool free_formula::is_dirty( session& s, const sheet_point& position ) const
{
    if ( m_unloading ) {
        return false;
    }
    if ( ! m_formula ) {
        return false;
    } else if ( m_formula->is_volatile() ) {
        calculation_context cc( s, s.selected().application()->calculation_settings() );
        if ( !m_formula->fetch_cached_volatile( cc ) ) {

            variant tmp_val = m_formula->value( cc );
            if ( !m_cached_volatile_val || tmp_val != *m_cached_volatile_val ) {
                m_cached_volatile_val.reset( new variant( tmp_val ) );
                return true;
            } else {
                return false;
            }
        }
        return false;
    }
    return m_formula->is_dirty();
}

sheet_point free_formula::position() const
{
    return m_formula->position();
}

std::string free_formula::formula( const locale& l, const sheet_point& position ) const
{
    if ( !m_unloading && m_formula ) {
        boost::shared_static_cast<free_formula_impl>( m_formula )->update_position( position );
        return m_formula->formula( l );
    }
    return "";
}

std::string free_formula::formula_without_sheet_references( const locale& l, const sheet_point& position ) const
{
    if ( !m_unloading && m_formula ) {
        boost::shared_static_cast<free_formula_impl>( m_formula )->update_position( position );
        return boost::shared_static_cast<free_formula_impl>( m_formula )->formula_without_sheet_references( l );
    }
    return "";
}

variant free_formula::value( session& s, const sheet_point& position /* = sheet_point */ ) const
{
    if ( m_unloading || ! m_formula ) {
        return variant();
    }
    calculation_context cc( s, s.selected().application()->calculation_settings() );
    boost::shared_static_cast<free_formula_impl>( m_formula )->update_position(  position );
    if ( m_formula->is_volatile() ) {
        const variant tmp_val = m_formula->value( cc );
        if ( !m_cached_volatile_val || ( *m_cached_volatile_val != tmp_val ) ) {
            m_cached_volatile_val.reset( new variant( tmp_val ) );
        }

        return *m_cached_volatile_val;
    }
    return m_formula->value( cc );
}

void free_formula::value( session& s, const variant& v, const sheet_point& position /* = sheet_point */ )
{
    shared_worksheet_type ws = s.selected().worksheet().lock();
    if ( ws ) {
        if ( m_formula ) {
            boost::shared_static_cast<free_formula_impl>( m_formula )->position( position );
            boost::shared_static_cast<named_formula>( boost::shared_static_cast<free_formula_impl>( m_formula )->get_real_nf() )->value( s, v, position );
        } else {
            set_formula( free_formula_impl::create( *this, s, v, ws, position, false ) );
        }
    } else {
        throw named_formula_exception();
    }
}

bool free_formula::moved( session& s )
{
    if ( ! m_unloading && m_formula ) {
        return boost::shared_static_cast<free_formula_impl>( m_formula )->moved( s );
    }
    return false;
}

shared_free_formula_type free_formula::create( session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position /* = sheet_point */, const bool adjust_legacy_references /* = false */ )
{
    return boost::make_shared<free_formula>( boost::ref( s ), v, ws, position, adjust_legacy_references );
}

shared_free_formula_type free_formula::create( const shared_free_formula_type& other, const geometry::point& distance, const bool is_rewrite_to_clone_sheet, const bool use_copy_move, const sheet_range& source_range, const sheet_point& position, const shared_worksheet_type& ws )
{
    return boost::make_shared<free_formula>( other, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, position, ws );
}

bool free_formula::is_valid() const
{
    return ! m_unloading && m_formula;
}

unsigned int free_formula::number_of_covered_columns( const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    if ( ! m_unloading && m_formula ) {
        boost::shared_static_cast<free_formula_impl>( m_formula )->position( position );
        return m_formula->number_of_covered_columns();
    }
    return 0;
}

bool free_formula::is_volatile() const
{
    return m_formula->is_volatile();
}


#ifdef _DEBUG
std::string free_formula::get_debug_identifier() const
{
    return m_formula->get_debug_identifier();
}
void free_formula::rename( const std::string& new_name )
{
    utf8_ci_string n = convert_utf8_ci( new_name );
    //n += boost::shared_static_cast<named_formula>( boost::shared_static_cast<free_formula_impl>( m_formula )->get_real_nf() )->name();
    boost::shared_static_cast<named_formula>( boost::shared_static_cast<free_formula_impl>( m_formula )->get_real_nf() )->name( n );

}
#endif // _DEBUG

void free_formula::set_special_caching()
{
    if ( m_formula ) {
        boost::shared_static_cast<free_formula_impl>( m_formula )->set_special_caching();
    }
}


#ifdef _DEBUG
size_t free_formula::m_counter = 0;
size_t free_formula_impl::m_counter = 0;
#endif // _DEBUG
