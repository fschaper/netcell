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
*  and do not license and distribute their source op under the GPL, Jedox provides
*  a flexible OEM Commercial License.
*
*  \author
*  Radu Racariu <Radu@yalos-solutions.com>
*/
#pragma once

#include "wss/type.hpp"

class WSS_MODULE broken_evaluation_dependencies
{
public:
	void register_name_function(const std::string& function_name, const shared_dependency_type& dependency);
	void notify(const std::string& function_name);
	void remove_dependency( const shared_dependency_type& dependency);
private:
	typedef std::map<std::string, weak_dependency_set_type > incomplete_dependency_map_type;
	typedef locked_object<incomplete_dependency_map_type> locked_incomplete_dependency_map_type;

	locked_incomplete_dependency_map_type m_incomplete_dependencies;
};
