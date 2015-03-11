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

#ifndef SML_CUSTOMXMLMAPPINGS_HPP
#define SML_CUSTOMXMLMAPPINGS_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Schema;
	class CT_DataBinding;
	class CT_Map;
	class CT_MapInfo;
	class sml_customXmlMappings;

	class CT_Schema
	{
	public:
		String ID;
		optional< String > SchemaRef;
		optional< String > Namespace;
	};

	class CT_DataBinding
	{
	public:
		optional< String > DataBindingName;
		optional< Boolean > FileBinding;
		optional< UnsignedInt > ConnectionID;
		optional< String > FileBindingName;
		UnsignedInt DataBindingLoadMode;
	};

	class CT_Map
	{
	public:
		poptional< CT_DataBinding > DataBinding;
		UnsignedInt ID;
		String Name;
		String RootElement;
		String SchemaID;
		Boolean ShowImportExportValidationErrors;
		Boolean AutoFit;
		Boolean Append;
		Boolean PreserveSortAFLayout;
		Boolean PreserveFormat;
	};

	class CT_MapInfo
	{
	public:
		std::vector< CT_Schema > Schema;
		std::vector< CT_Map > Map;
		String SelectionNamespaces;
	};

	class sml_customXmlMappings
	{
	public:
		poptional< CT_MapInfo > MapInfo;
	};

}
#endif

