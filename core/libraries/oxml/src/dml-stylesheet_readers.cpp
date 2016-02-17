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


#include "dml-stylesheet_readers.hpp"
#include "dml-stylesheet_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_ColorMapping_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ColorMapping_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_bg1_literal))
			{
				driver()->context()->parse(value, t()->bg1);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_tx1_literal))
			{
				driver()->context()->parse(value, t()->tx1);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_bg2_literal))
			{
				driver()->context()->parse(value, t()->bg2);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_tx2_literal))
			{
				driver()->context()->parse(value, t()->tx2);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent1_literal))
			{
				driver()->context()->parse(value, t()->accent1);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent2_literal))
			{
				driver()->context()->parse(value, t()->accent2);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent3_literal))
			{
				driver()->context()->parse(value, t()->accent3);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent4_literal))
			{
				driver()->context()->parse(value, t()->accent4);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent5_literal))
			{
				driver()->context()->parse(value, t()->accent5);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_accent6_literal))
			{
				driver()->context()->parse(value, t()->accent6);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_hlink_literal))
			{
				driver()->context()->parse(value, t()->hlink);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_folHlink_literal))
			{
				driver()->context()->parse(value, t()->folHlink);
				return;
			}
		}
		void CT_ColorSchemeAndMapping_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_clrScheme_literal))
			{
				driver()->push(localname, _clrScheme_reader.get_reader(&t()->clrScheme));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_clrMap_literal))
			{
				driver()->push(localname, _clrMap_reader.get_reader(&t()->clrMap.getset()));
				return;
			}
		}
		void CT_ColorSchemeList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_extraClrScheme_literal))
			{
				t()->extraClrScheme.resize(t()->extraClrScheme.size()+1);
				driver()->push(localname, _extraClrScheme_reader.get_reader(&t()->extraClrScheme.back()));
				return;
			}
		}
		void CT_OfficeStyleSheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_themeElements_literal))
			{
				driver()->push(localname, _themeElements_reader.get_reader(&t()->themeElements));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_objectDefaults_literal))
			{
				driver()->push(localname, _objectDefaults_reader.get_reader(&t()->objectDefaults.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_extraClrSchemeLst_literal))
			{
				driver()->push(localname, _extraClrSchemeLst_reader.get_reader(&t()->extraClrSchemeLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_custClrLst_literal))
			{
				driver()->push(localname, _custClrLst_reader.get_reader(&t()->custClrLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_OfficeStyleSheet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_BaseStylesOverride_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_clrScheme_literal))
			{
				driver()->push(localname, _clrScheme_reader.get_reader(&t()->clrScheme.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_fontScheme_literal))
			{
				driver()->push(localname, _fontScheme_reader.get_reader(&t()->fontScheme.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_fmtScheme_literal))
			{
				driver()->push(localname, _fmtScheme_reader.get_reader(&t()->fmtScheme.getset()));
				return;
			}
		}
		void dml_stylesheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_theme_literal))
			{
				driver()->push(localname, _theme_reader.get_reader(&t()->theme.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_themeOverride_literal))
			{
				driver()->push(localname, _themeOverride_reader.get_reader(&t()->themeOverride.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_themeManager_literal))
			{
				driver()->push(localname, _themeManager_reader.get_reader(&t()->themeManager.getset()));
				return;
			}
		}
		void CT_ColorMappingOverride_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_masterClrMapping_literal))
			{
				driver()->push(localname, _masterClrMapping_reader.get_reader(&t()->masterClrMapping.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_stylesheet_overrideClrMapping_literal))
			{
				driver()->push(localname, _overrideClrMapping_reader.get_reader(&t()->overrideClrMapping.getset()));
				return;
			}
		}
	}
}
