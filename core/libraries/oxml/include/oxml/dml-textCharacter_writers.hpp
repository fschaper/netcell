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

#ifndef DML_TEXTCHARACTER_WRITERS_HPP
#define DML_TEXTCHARACTER_WRITERS_HPP

#include "dml-textCharacter.hpp"
#include "dml-textCharacter_literals.hpp"
#include "dml-shapeLineProperties_writers.hpp"
#include "dml-shapeEffects_writers.hpp"
#include "dml-baseTypes_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_TextFontSize_writer;
		class ST_TextTypeface_writer;
		class ST_Panose_writer;
		class CT_TextFont_writer;
		class CT_TextUnderlineLineFollowText_writer;
		class CT_TextUnderlineFillFollowText_writer;
		class CT_TextUnderlineFillGroupWrapper_writer;
		class ST_TextLanguageID_writer;
		class ST_TextNonNegativePoint_writer;
		class ST_TextPoint_writer;
		class CT_TextCharacterProperties_writer;

		class ST_TextFontSize_writer : public type_writer
		{
			ST_TextFontSize* t() { return static_cast<ST_TextFontSize*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextTypeface_writer : public type_writer
		{
			ST_TextTypeface* t() { return static_cast<ST_TextTypeface*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Panose_writer : public type_writer
		{
			ST_Panose* t() { return static_cast<ST_Panose*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextFont_writer : public type_writer
		{
			CT_TextFont* t() { return static_cast<CT_TextFont*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextUnderlineLineFollowText_writer : public type_writer
		{
			CT_TextUnderlineLineFollowText* t() { return static_cast<CT_TextUnderlineLineFollowText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextUnderlineFillFollowText_writer : public type_writer
		{
			CT_TextUnderlineFillFollowText* t() { return static_cast<CT_TextUnderlineFillFollowText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextUnderlineFillGroupWrapper_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_TextUnderlineFillGroupWrapper* t() { return static_cast<CT_TextUnderlineFillGroupWrapper*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextLanguageID_writer : public type_writer
		{
			ST_TextLanguageID* t() { return static_cast<ST_TextLanguageID*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextNonNegativePoint_writer : public type_writer
		{
			ST_TextNonNegativePoint* t() { return static_cast<ST_TextNonNegativePoint*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextPoint_writer : public type_writer
		{
			ST_TextPoint* t() { return static_cast<ST_TextPoint*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextCharacterProperties_writer : public type_writer
		{
			auto_type_writer< CT_LineProperties_writer > _ln_writer;
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			auto_type_writer< CT_EffectList_writer > _effectLst_writer;
			auto_type_writer< CT_EffectContainer_writer > _effectDag_writer;
			auto_type_writer< CT_Color_writer > _highlight_writer;
			auto_type_writer< CT_TextUnderlineLineFollowText_writer > _uLnTx_writer;
			auto_type_writer< CT_LineProperties_writer > _uLn_writer;
			auto_type_writer< CT_TextUnderlineFillFollowText_writer > _uFillTx_writer;
			auto_type_writer< CT_TextUnderlineFillGroupWrapper_writer > _uFill_writer;
			auto_type_writer< CT_TextFont_writer > _latin_writer;
			auto_type_writer< CT_TextFont_writer > _ea_writer;
			auto_type_writer< CT_TextFont_writer > _cs_writer;
			auto_type_writer< CT_TextFont_writer > _sym_writer;
			auto_type_writer< CT_Hyperlink_writer > _hlinkClick_writer;
			auto_type_writer< CT_Hyperlink_writer > _hlinkMouseOver_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_TextCharacterProperties* t() { return static_cast<CT_TextCharacterProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

