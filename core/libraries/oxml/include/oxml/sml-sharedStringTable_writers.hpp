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

#ifndef SML_SHAREDSTRINGTABLE_WRITERS_HPP
#define SML_SHAREDSTRINGTABLE_WRITERS_HPP

#include "sml-sharedStringTable.hpp"
#include "sml-sharedStringTable_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-styles_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_RPrElt_writer;
		class CT_RElt_writer;
		class CT_PhoneticRun_writer;
		class CT_PhoneticPr_writer;
		class CT_Rst_writer;
		class CT_Sst_writer;
		class sml_sharedStringTable_writer;

		class CT_RPrElt_writer : public type_writer
		{
			auto_type_writer< CT_FontName_writer > _rFont_writer;
			auto_type_writer< CT_IntProperty_writer > _charset_writer;
			auto_type_writer< CT_IntProperty_writer > _family_writer;
			auto_type_writer< CT_BooleanProperty_writer > _b_writer;
			auto_type_writer< CT_BooleanProperty_writer > _i_writer;
			auto_type_writer< CT_BooleanProperty_writer > _strike_writer;
			auto_type_writer< CT_BooleanProperty_writer > _outline_writer;
			auto_type_writer< CT_BooleanProperty_writer > _shadow_writer;
			auto_type_writer< CT_BooleanProperty_writer > _condense_writer;
			auto_type_writer< CT_BooleanProperty_writer > _extend_writer;
			auto_type_writer< CT_Color_writer > _color_writer;
			auto_type_writer< CT_FontSize_writer > _sz_writer;
			auto_type_writer< CT_UnderlineProperty_writer > _u_writer;
			auto_type_writer< CT_VerticalAlignFontProperty_writer > _vertAlign_writer;
			auto_type_writer< CT_FontScheme_writer > _scheme_writer;
			CT_RPrElt* t() { return static_cast<CT_RPrElt*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RElt_writer : public type_writer
		{
			auto_type_writer< CT_RPrElt_writer > _rPr_writer;
			auto_type_writer< ST_Xstring_writer > _t_writer;
			CT_RElt* t() { return static_cast<CT_RElt*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PhoneticRun_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _t_writer;
			CT_PhoneticRun* t() { return static_cast<CT_PhoneticRun*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PhoneticPr_writer : public type_writer
		{
			CT_PhoneticPr* t() { return static_cast<CT_PhoneticPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Rst_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _t_writer;
			auto_type_writer< CT_RElt_writer > _r_writer;
			auto_type_writer< CT_PhoneticRun_writer > _rPh_writer;
			auto_type_writer< CT_PhoneticPr_writer > _phoneticPr_writer;
			CT_Rst* t() { return static_cast<CT_Rst*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Sst_writer : public type_writer
		{
			auto_type_writer< CT_Rst_writer > _si_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Sst* t() { return static_cast<CT_Sst*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_sharedStringTable_writer : public type_writer
		{
			auto_type_writer< CT_Sst_writer > _sst_writer;
			sml_sharedStringTable* t() { return static_cast<sml_sharedStringTable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

