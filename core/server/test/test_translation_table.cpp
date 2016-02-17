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

#include <boost/test/unit_test.hpp>
#include <wss/translation_map.hpp>
#include <wss/translation_table.hpp>

BOOST_AUTO_TEST_SUITE( translation_table_test );

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( translation_map_test )
{
    shared_translation_map_type m( translation_map::create( locale::create( "de" ), ";", "\\", ";", false, "wahr", "falsch" ) );
    m->add( translation_map::function_translation_entry( "sum", "summe" ) );
    m->add( translation_map::function_translation_entry( "if", "wenn" ) );

    const translation_map::function_translation_entry* s = m->external_name_lookup["sum"];
    const translation_map::function_translation_entry* i = m->internal_name_lookup["wenn"];

    translation_map::error_mapping::type em;

    BOOST_CHECK_EQUAL( s->identifier, "SUM" );
    BOOST_CHECK_EQUAL( i->identifier, "IF" );
}

BOOST_AUTO_TEST_SUITE_END()
