/**
*  \file
*  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
*  <a href="http://www.jedox.com/license_worksheetserver.txt">
*    http://www.jedox.com/license_worksheetserver.txt
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
#include "wss/named_formula_accessor.hpp"

#include "wss/workbook.hpp"
#include "wss/i_named_formula_manager.hpp"
#include "named_formula.hpp"
#include "wss/server.hpp"
#include "wss/named_formula_not_found_exception.hpp"

struct named_formula_accessor_helper {
    static shared_named_formula_type get_nf( const weak_named_formula_type& weak_nf ) {
        shared_named_formula_type nf = weak_nf.lock();
        if ( !nf ) {
            throw named_formula_not_found_exception();
        }
        return nf;
    }

    static named_formula_identifier get_identifier( const shared_named_formula_type& nf ) {
        if ( named_formula_scope::worksheet_scope == nf->scope() ) {
            shared_worksheet_type ws = nf->worksheet().lock();
            if ( !ws ) {
                throw named_formula_not_found_exception();
            }
            return named_formula_identifier( nf->name(), ws->uuid() );
        }
        return named_formula_identifier( nf->name(), boost::uuids::nil_uuid() );
    }
};

named_formula_accessor::named_formula_accessor( const shared_workbook_type& managers_parent, const shared_named_formula_type& nf )
    : m_managers_parent( managers_parent )
    , m_nf( nf )
{}

const bool named_formula_accessor::is_valid() const
{
    return !m_nf.expired();
}

variant named_formula_accessor::formula( const locale& l, const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    return named_formula_accessor_helper::get_nf( m_nf )->formula( l, position );
}

shared_named_formula_accessor_type named_formula_accessor::create( const shared_workbook_type& managers_parent, const shared_named_formula_type& nf )
{
    return boost::make_shared<named_formula_accessor>( managers_parent, nf );
}

void named_formula_accessor::value( session& s, const variant& v, const sheet_point& position /*= sheet_point( 0, 0 ) */ )
{
    named_formula_accessor_helper::get_nf( m_nf )->value( s, v, position );
}

variant named_formula_accessor::value( session& s, const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    shared_workbook_type wb = m_managers_parent.lock();
    if ( !wb ) {
        throw named_formula_not_found_exception();
    }
    shared_named_formula_type nf = named_formula_accessor_helper::get_nf( m_nf );
    return  wb->named_formulas().value( s, named_formula_accessor_helper::get_identifier( nf ), position );
}

void named_formula_accessor::comment( const std::string& c )
{
    named_formula_accessor_helper::get_nf( m_nf )->comment( c );
}

const std::string& named_formula_accessor::comment() const
{
    return named_formula_accessor_helper::get_nf( m_nf )->comment();
}

void named_formula_accessor::name( session& s, const std::string& new_name )
{
    shared_workbook_type wb = m_managers_parent.lock();
    if ( !wb ) {
        throw named_formula_not_found_exception();
    }
    shared_named_formula_type nf = named_formula_accessor_helper::get_nf( m_nf );
    wb->named_formulas().rename( s, nf->uuid(), new_name );
}

void named_formula_accessor::remove( session& s )
{
    shared_workbook_type wb = m_managers_parent.lock();
    if ( !wb ) {
        throw named_formula_not_found_exception();
    }
    wb->named_formulas().remove( s, named_formula_accessor_helper::get_nf( m_nf )->uuid() );
}

const std::string named_formula_accessor::name()
{
    return convert_utf8_ci( named_formula_accessor_helper::get_nf( m_nf )->name() );
}

const uuid_type named_formula_accessor::uuid()
{
    return named_formula_accessor_helper::get_nf( m_nf )->uuid();
}

bool named_formula_accessor::has_worksheet_scope( session& s )
{
    return named_formula_accessor_helper::get_nf( m_nf )->scope() == named_formula_scope::worksheet_scope;
}

const uuid_type& named_formula_accessor::get_scope_uuid( session& s )
{
    shared_named_formula_type nf = named_formula_accessor_helper::get_nf( m_nf );
    if ( nf->scope() == named_formula_scope::worksheet_scope ) {
        shared_worksheet_type ws = nf->worksheet().lock();
        if ( ws ) {
            return ws->uuid();
        }
    }
    static uuid_type dummy = boost::uuids::nil_uuid();
    return dummy;
}
