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

#pragma once


#include "palo_cell_adapter.hpp"

#include <wss/interpreter_variant.hpp>
#include <wss/interpreter_context.hpp>
#include <wss/function_parameters.hpp>

#include <vector>
#include <list>

/*!
 * \brief
 * adapter from worksheetserver values to generic cells.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class palo_argument_list
{
public:
    typedef std::vector<GenericCell*> generic_cell_pointer_list_type;

public:
    palo_argument_list( function_parameter& parameter );

    ~palo_argument_list();

    generic_cell_pointer_list_type& get();

private:
    generic_cell_pointer_list_type m_generic_cell_values;
};
