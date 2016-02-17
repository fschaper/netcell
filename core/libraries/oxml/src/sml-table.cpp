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


#include "sml-table.hpp"
namespace spreadsheetml
{
	const String ST_XmlDataType::anyType_literal = "anyType";
	const String ST_XmlDataType::anyURI_literal = "anyURI";
	const String ST_XmlDataType::base64Binary_literal = "base64Binary";
	const String ST_XmlDataType::boolean_literal = "boolean";
	const String ST_XmlDataType::byte_literal = "byte";
	const String ST_XmlDataType::date_literal = "date";
	const String ST_XmlDataType::dateTime_literal = "dateTime";
	const String ST_XmlDataType::decimal_literal = "decimal";
	const String ST_XmlDataType::_double__literal = "double";
	const String ST_XmlDataType::duration_literal = "duration";
	const String ST_XmlDataType::ENTITIES_literal = "ENTITIES";
	const String ST_XmlDataType::ENTITY_literal = "ENTITY";
	const String ST_XmlDataType::_float__literal = "float";
	const String ST_XmlDataType::gDay_literal = "gDay";
	const String ST_XmlDataType::gMonth_literal = "gMonth";
	const String ST_XmlDataType::gMonthDay_literal = "gMonthDay";
	const String ST_XmlDataType::gYear_literal = "gYear";
	const String ST_XmlDataType::gYearMonth_literal = "gYearMonth";
	const String ST_XmlDataType::hexBinary_literal = "hexBinary";
	const String ST_XmlDataType::ID_literal = "ID";
	const String ST_XmlDataType::IDREF_literal = "IDREF";
	const String ST_XmlDataType::IDREFS_literal = "IDREFS";
	const String ST_XmlDataType::_int__literal = "int";
	const String ST_XmlDataType::integer_literal = "integer";
	const String ST_XmlDataType::language_literal = "language";
	const String ST_XmlDataType::_long__literal = "long";
	const String ST_XmlDataType::Name_literal = "Name";
	const String ST_XmlDataType::NCName_literal = "NCName";
	const String ST_XmlDataType::negativeInteger_literal = "negativeInteger";
	const String ST_XmlDataType::NMTOKEN_literal = "NMTOKEN";
	const String ST_XmlDataType::NMTOKENS_literal = "NMTOKENS";
	const String ST_XmlDataType::nonNegativeInteger_literal = "nonNegativeInteger";
	const String ST_XmlDataType::nonPositiveInteger_literal = "nonPositiveInteger";
	const String ST_XmlDataType::normalizedString_literal = "normalizedString";
	const String ST_XmlDataType::NOTATION_literal = "NOTATION";
	const String ST_XmlDataType::positiveInteger_literal = "positiveInteger";
	const String ST_XmlDataType::QName_literal = "QName";
	const String ST_XmlDataType::_short__literal = "short";
	const String ST_XmlDataType::_string__literal = "string";
	const String ST_XmlDataType::time_literal = "time";
	const String ST_XmlDataType::token_literal = "token";
	const String ST_XmlDataType::unsignedByte_literal = "unsignedByte";
	const String ST_XmlDataType::unsignedInt_literal = "unsignedInt";
	const String ST_XmlDataType::unsignedLong_literal = "unsignedLong";
	const String ST_XmlDataType::unsignedShort_literal = "unsignedShort";
	String ST_XmlDataType::_literals[] = { ST_XmlDataType::anyType_literal, ST_XmlDataType::anyURI_literal, ST_XmlDataType::base64Binary_literal, ST_XmlDataType::boolean_literal, ST_XmlDataType::byte_literal, ST_XmlDataType::date_literal, ST_XmlDataType::dateTime_literal, ST_XmlDataType::decimal_literal, ST_XmlDataType::_double__literal, ST_XmlDataType::duration_literal, ST_XmlDataType::ENTITIES_literal, ST_XmlDataType::ENTITY_literal, ST_XmlDataType::_float__literal, ST_XmlDataType::gDay_literal, ST_XmlDataType::gMonth_literal, ST_XmlDataType::gMonthDay_literal, ST_XmlDataType::gYear_literal, ST_XmlDataType::gYearMonth_literal, ST_XmlDataType::hexBinary_literal, ST_XmlDataType::ID_literal, ST_XmlDataType::IDREF_literal, ST_XmlDataType::IDREFS_literal, ST_XmlDataType::_int__literal, ST_XmlDataType::integer_literal, ST_XmlDataType::language_literal, ST_XmlDataType::_long__literal, ST_XmlDataType::Name_literal, ST_XmlDataType::NCName_literal, ST_XmlDataType::negativeInteger_literal, ST_XmlDataType::NMTOKEN_literal, ST_XmlDataType::NMTOKENS_literal, ST_XmlDataType::nonNegativeInteger_literal, ST_XmlDataType::nonPositiveInteger_literal, ST_XmlDataType::normalizedString_literal, ST_XmlDataType::NOTATION_literal, ST_XmlDataType::positiveInteger_literal, ST_XmlDataType::QName_literal, ST_XmlDataType::_short__literal, ST_XmlDataType::_string__literal, ST_XmlDataType::time_literal, ST_XmlDataType::token_literal, ST_XmlDataType::unsignedByte_literal, ST_XmlDataType::unsignedInt_literal, ST_XmlDataType::unsignedLong_literal, ST_XmlDataType::unsignedShort_literal };

	const String ST_TotalsRowFunction::average_literal = "average";
	const String ST_TotalsRowFunction::count_literal = "count";
	const String ST_TotalsRowFunction::countNums_literal = "countNums";
	const String ST_TotalsRowFunction::custom_literal = "custom";
	const String ST_TotalsRowFunction::max_literal = "max";
	const String ST_TotalsRowFunction::min_literal = "min";
	const String ST_TotalsRowFunction::none_literal = "none";
	const String ST_TotalsRowFunction::stdDev_literal = "stdDev";
	const String ST_TotalsRowFunction::sum_literal = "sum";
	const String ST_TotalsRowFunction::var_literal = "var";
	String ST_TotalsRowFunction::_literals[] = { ST_TotalsRowFunction::average_literal, ST_TotalsRowFunction::count_literal, ST_TotalsRowFunction::countNums_literal, ST_TotalsRowFunction::custom_literal, ST_TotalsRowFunction::max_literal, ST_TotalsRowFunction::min_literal, ST_TotalsRowFunction::none_literal, ST_TotalsRowFunction::stdDev_literal, ST_TotalsRowFunction::sum_literal, ST_TotalsRowFunction::var_literal };

	const String ST_TableType::queryTable_literal = "queryTable";
	const String ST_TableType::worksheet_literal = "worksheet";
	const String ST_TableType::xml_literal = "xml";
	String ST_TableType::_literals[] = { ST_TableType::queryTable_literal, ST_TableType::worksheet_literal, ST_TableType::xml_literal };

}
