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

#ifndef DML_TEXTCHARACTER_READERS_HPP
#define DML_TEXTCHARACTER_READERS_HPP

#include "dml-textCharacter.hpp"
#include "dml-shapeLineProperties_readers.hpp"
#include "dml-shapeEffects_readers.hpp"
#include "dml-baseTypes_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_TextFontSize_reader;
		class ST_TextTypeface_reader;
		class ST_Panose_reader;
		class CT_TextFont_reader;
		class CT_TextUnderlineLineFollowText_reader;
		class CT_TextUnderlineFillFollowText_reader;
		class CT_TextUnderlineFillGroupWrapper_reader;
		class ST_TextLanguageID_reader;
		class ST_TextNonNegativePoint_reader;
		class ST_TextPoint_reader;
		class CT_TextCharacterProperties_reader;

		class ST_TextFontSize_reader : public type_reader
		{
		protected:
			ST_TextFontSize* t() { return static_cast<ST_TextFontSize*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_TextTypeface_reader : public type_reader
		{
		protected:
			ST_TextTypeface* t() { return static_cast<ST_TextTypeface*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Panose_reader : public type_reader
		{
		protected:
			ST_Panose* t() { return static_cast<ST_Panose*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_TextFont_reader : public type_reader
		{
		protected:
			CT_TextFont* t() { return static_cast<CT_TextFont*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextUnderlineLineFollowText_reader : public type_reader
		{
		protected:
			CT_TextUnderlineLineFollowText* t() { return static_cast<CT_TextUnderlineLineFollowText*>(target()); }
		};

		class CT_TextUnderlineFillFollowText_reader : public type_reader
		{
		protected:
			CT_TextUnderlineFillFollowText* t() { return static_cast<CT_TextUnderlineFillFollowText*>(target()); }
		};

		class CT_TextUnderlineFillGroupWrapper_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_TextUnderlineFillGroupWrapper* t() { return static_cast<CT_TextUnderlineFillGroupWrapper*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_TextLanguageID_reader : public type_reader
		{
		protected:
			ST_TextLanguageID* t() { return static_cast<ST_TextLanguageID*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_TextNonNegativePoint_reader : public type_reader
		{
		protected:
			ST_TextNonNegativePoint* t() { return static_cast<ST_TextNonNegativePoint*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_TextPoint_reader : public type_reader
		{
		protected:
			ST_TextPoint* t() { return static_cast<ST_TextPoint*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_TextCharacterProperties_reader : public type_reader
		{
			auto_type_reader< CT_LineProperties_reader > _ln_reader;
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
			auto_type_reader< CT_EffectList_reader > _effectLst_reader;
			auto_type_reader< CT_EffectContainer_reader > _effectDag_reader;
			auto_type_reader< CT_Color_reader > _highlight_reader;
			auto_type_reader< CT_TextUnderlineLineFollowText_reader > _uLnTx_reader;
			auto_type_reader< CT_LineProperties_reader > _uLn_reader;
			auto_type_reader< CT_TextUnderlineFillFollowText_reader > _uFillTx_reader;
			auto_type_reader< CT_TextUnderlineFillGroupWrapper_reader > _uFill_reader;
			auto_type_reader< CT_TextFont_reader > _latin_reader;
			auto_type_reader< CT_TextFont_reader > _ea_reader;
			auto_type_reader< CT_TextFont_reader > _cs_reader;
			auto_type_reader< CT_TextFont_reader > _sym_reader;
			auto_type_reader< CT_Hyperlink_reader > _hlinkClick_reader;
			auto_type_reader< CT_Hyperlink_reader > _hlinkMouseOver_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_TextCharacterProperties* t() { return static_cast<CT_TextCharacterProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

