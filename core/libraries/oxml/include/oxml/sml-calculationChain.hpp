/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef SML_CALCULATIONCHAIN_HPP
#define SML_CALCULATIONCHAIN_HPP


#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_CalcCell;
	class CT_CalcChain;
	class sml_calculationChain;

	class CT_CalcCell
	{
	public:
		CT_CalcCell() : i(0), s(false), l(false), t(false), a(false) {}
		ST_CellRef r;
		Int i;
		Boolean s;
		Boolean l;
		Boolean t;
		Boolean a;
	};

	class CT_CalcChain
	{
	public:
		std::vector< CT_CalcCell > c;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_calculationChain
	{
	public:
		poptional< CT_CalcChain > calcChain;
	};

}
#endif

