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
#include "named_formula_wrapper.hpp"
#include "named_formula.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/worksheet.hpp"
#include "wss/named_formula_exception.hpp"

named_formula_wrapper::named_formula_wrapper()
    : m_redirected( false )
    , m_scope_sheet_hidden( false )
    ,  m_named_formula()
{}

named_formula_wrapper::named_formula_wrapper( const shared_named_formula_type& nf )
    :  m_redirected( false )
    , m_scope_sheet_hidden( false )
    , m_named_formula( nf )
{
    shared_worksheet_type ws = nf->worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    m_scope_sheet_hidden = ws->hidden();
}

named_formula_wrapper::~named_formula_wrapper()
{}

void named_formula_wrapper::set_named_formula( const shared_named_formula_type& nf, const is_hidden& h )
{
    m_named_formula = nf;
    if ( nf->scope() == named_formula_scope::worksheet_scope ) {
        m_scope_sheet_hidden = h.my_val;
    }
}

void named_formula_wrapper::redirected( bool val )
{
    m_redirected = val;
}

void named_formula_wrapper::unload()
{
    shared_named_formula_type d = m_named_formula.lock();
    if ( d ) {
        d->unload();
        m_named_formula.reset();
    }
}

shared_dependency_type named_formula_wrapper::named_formula( const shared_dependency_type& d )
{
    shared_named_formula_type nf = m_named_formula.lock();
    if ( !nf ) {
        throw named_formula_exception();
    }
    if ( d == nf ) {
        return nf;
    }
    return nf->get_proxy( d );
}
