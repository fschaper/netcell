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

#ifndef SHARED_DOCUMENTPROPERTIESCUSTOM_HPP
#define SHARED_DOCUMENTPROPERTIESCUSTOM_HPP


#include "shared-documentPropertiesVariantTypes.hpp"

namespace custom_properties
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Property;
	class CT_Properties;
	class shared_documentPropertiesCustom;

	class CT_Property
	{
	public:
		poptional< ::docPropsVTypes::CT_Vector > vector;
		poptional< ::docPropsVTypes::CT_Array > array;
		optional< Base64Binary > blob;
		optional< Base64Binary > oblob;
		poptional< ::docPropsVTypes::CT_Empty > empty;
		poptional< ::docPropsVTypes::CT_Null > null;
		optional< Byte > i1;
		optional< Short > i2;
		optional< Int > i4;
		optional< Long > i8;
		optional< Int > _int_;
		optional< UnsignedByte > ui1;
		optional< UnsignedShort > ui2;
		optional< UnsignedInt > ui4;
		optional< UnsignedLong > ui8;
		optional< UnsignedInt > uint;
		optional< Float > r4;
		optional< Double > r8;
		optional< Decimal > decimal;
		optional< String > lpstr;
		optional< String > lpwstr;
		optional< String > bstr;
		optional< DateTime > date;
		optional< DateTime > filetime;
		optional< Boolean > _bool_;
		poptional< ::docPropsVTypes::ST_Cy > cy;
		poptional< ::docPropsVTypes::ST_Error > error;
		optional< Base64Binary > stream;
		optional< Base64Binary > ostream;
		optional< Base64Binary > storage;
		optional< Base64Binary > ostorage;
		poptional< ::docPropsVTypes::CT_Vstream > vstream;
		poptional< ::docPropsVTypes::ST_Clsid > clsid;
		poptional< ::docPropsVTypes::CT_Cf > cf;
		::docPropsVTypes::ST_Clsid fmtid;
		Int pid;
		optional< String > name;
		optional< String > linkTarget;
	};

	class CT_Properties
	{
	public:
		std::vector< CT_Property > property;
	};

	class shared_documentPropertiesCustom
	{
	public:
		poptional< CT_Properties > Properties;
	};

}
#endif

