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

#ifndef SML_SHAREDSTRINGTABLE_READERS_HPP
#define SML_SHAREDSTRINGTABLE_READERS_HPP

#include "sml-sharedStringTable.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-styles_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_RPrElt_reader;
		class CT_RElt_reader;
		class CT_PhoneticRun_reader;
		class CT_PhoneticPr_reader;
		class CT_Rst_reader;
		class CT_Sst_reader;
		class sml_sharedStringTable_reader;

		class CT_RPrElt_reader : public type_reader
		{
			auto_type_reader< CT_FontName_reader > _rFont_reader;
			auto_type_reader< CT_IntProperty_reader > _charset_reader;
			auto_type_reader< CT_IntProperty_reader > _family_reader;
			auto_type_reader< CT_BooleanProperty_reader > _b_reader;
			auto_type_reader< CT_BooleanProperty_reader > _i_reader;
			auto_type_reader< CT_BooleanProperty_reader > _strike_reader;
			auto_type_reader< CT_BooleanProperty_reader > _outline_reader;
			auto_type_reader< CT_BooleanProperty_reader > _shadow_reader;
			auto_type_reader< CT_BooleanProperty_reader > _condense_reader;
			auto_type_reader< CT_BooleanProperty_reader > _extend_reader;
			auto_type_reader< CT_Color_reader > _color_reader;
			auto_type_reader< CT_FontSize_reader > _sz_reader;
			auto_type_reader< CT_UnderlineProperty_reader > _u_reader;
			auto_type_reader< CT_VerticalAlignFontProperty_reader > _vertAlign_reader;
			auto_type_reader< CT_FontScheme_reader > _scheme_reader;
		protected:
			CT_RPrElt* t() { return static_cast<CT_RPrElt*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_RElt_reader : public type_reader
		{
			auto_type_reader< CT_RPrElt_reader > _rPr_reader;
			auto_type_reader< ST_Xstring_reader > _t_reader;
		protected:
			CT_RElt* t() { return static_cast<CT_RElt*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PhoneticRun_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _t_reader;
		protected:
			CT_PhoneticRun* t() { return static_cast<CT_PhoneticRun*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PhoneticPr_reader : public type_reader
		{
		protected:
			CT_PhoneticPr* t() { return static_cast<CT_PhoneticPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Rst_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _t_reader;
			auto_type_reader< CT_RElt_reader > _r_reader;
			auto_type_reader< CT_PhoneticRun_reader > _rPh_reader;
			auto_type_reader< CT_PhoneticPr_reader > _phoneticPr_reader;
		protected:
			CT_Rst* t() { return static_cast<CT_Rst*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Sst_reader : public type_reader
		{
			auto_type_reader< CT_Rst_reader > _si_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Sst* t() { return static_cast<CT_Sst*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class sml_sharedStringTable_reader : public type_reader
		{
			auto_type_reader< CT_Sst_reader > _sst_reader;
		protected:
			sml_sharedStringTable* t() { return static_cast<sml_sharedStringTable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

