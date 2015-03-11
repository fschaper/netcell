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
#include "wss/formula_parsing_context.hpp"
#include "wss/translation_table.hpp"

parsing_context::parsing_context( ::session& s, const weak_worksheet_type& current_worksheet, const std::string& formula )
    : m_session( s )
    , m_current_worksheet( current_worksheet )
    , m_formula( formula )
    , m_translation_map( *translation_table::instance()[ s.locale() ] )
{}

const std::string& parsing_context::formula() const
{
    return m_formula;
}

::session& parsing_context::session() const
{
    return m_session;
}

const ::locale& parsing_context::locale() const
{
    return m_session.locale();
}

weak_worksheet_type parsing_context::worksheet() const
{
    return m_current_worksheet;
}

const ::translation_map& parsing_context::active_translation() const
{
    return m_translation_map;
}

