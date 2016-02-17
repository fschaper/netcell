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

#ifndef DML_TEXTPARAGRAPH_WRITERS_HPP
#define DML_TEXTPARAGRAPH_WRITERS_HPP

#include "dml-textParagraph.hpp"
#include "dml-textParagraph_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-textBullet_writers.hpp"
#include "dml-textCharacter_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_TextSpacingPercent_writer;
		class CT_TextSpacingPercent_writer;
		class ST_TextSpacingPoint_writer;
		class CT_TextSpacingPoint_writer;
		class CT_TextSpacing_writer;
		class CT_TextTabStop_writer;
		class CT_TextTabStopList_writer;
		class ST_TextMargin_writer;
		class ST_TextIndentLevelType_writer;
		class ST_TextIndent_writer;
		class CT_TextParagraphProperties_writer;
		class CT_TextLineBreak_writer;
		class CT_TextField_writer;

		class ST_TextSpacingPercent_writer : public ST_Percentage_writer
		{
			ST_TextSpacingPercent* t() { return static_cast<ST_TextSpacingPercent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextSpacingPercent_writer : public type_writer
		{
			CT_TextSpacingPercent* t() { return static_cast<CT_TextSpacingPercent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextSpacingPoint_writer : public type_writer
		{
			ST_TextSpacingPoint* t() { return static_cast<ST_TextSpacingPoint*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextSpacingPoint_writer : public type_writer
		{
			CT_TextSpacingPoint* t() { return static_cast<CT_TextSpacingPoint*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextSpacing_writer : public type_writer
		{
			auto_type_writer< CT_TextSpacingPercent_writer > _spcPct_writer;
			auto_type_writer< CT_TextSpacingPoint_writer > _spcPts_writer;
			CT_TextSpacing* t() { return static_cast<CT_TextSpacing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextTabStop_writer : public type_writer
		{
			CT_TextTabStop* t() { return static_cast<CT_TextTabStop*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextTabStopList_writer : public type_writer
		{
			auto_type_writer< CT_TextTabStop_writer > _tab_writer;
			CT_TextTabStopList* t() { return static_cast<CT_TextTabStopList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextMargin_writer : public ST_Coordinate32_writer
		{
			ST_TextMargin* t() { return static_cast<ST_TextMargin*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextIndentLevelType_writer : public type_writer
		{
			ST_TextIndentLevelType* t() { return static_cast<ST_TextIndentLevelType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextIndent_writer : public ST_Coordinate32_writer
		{
			ST_TextIndent* t() { return static_cast<ST_TextIndent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextParagraphProperties_writer : public type_writer
		{
			auto_type_writer< CT_TextSpacing_writer > _lnSpc_writer;
			auto_type_writer< CT_TextSpacing_writer > _spcBef_writer;
			auto_type_writer< CT_TextSpacing_writer > _spcAft_writer;
			auto_type_writer< CT_TextBulletColorFollowText_writer > _buClrTx_writer;
			auto_type_writer< CT_Color_writer > _buClr_writer;
			auto_type_writer< CT_TextBulletSizeFollowText_writer > _buSzTx_writer;
			auto_type_writer< CT_TextBulletSizePercent_writer > _buSzPct_writer;
			auto_type_writer< CT_TextBulletSizePoint_writer > _buSzPts_writer;
			auto_type_writer< CT_TextBulletTypefaceFollowText_writer > _buFontTx_writer;
			auto_type_writer< CT_TextFont_writer > _buFont_writer;
			auto_type_writer< CT_TextNoBullet_writer > _buNone_writer;
			auto_type_writer< CT_TextAutonumberBullet_writer > _buAutoNum_writer;
			auto_type_writer< CT_TextCharBullet_writer > _buChar_writer;
			auto_type_writer< CT_TextBlipBullet_writer > _buBlip_writer;
			auto_type_writer< CT_TextTabStopList_writer > _tabLst_writer;
			auto_type_writer< CT_TextCharacterProperties_writer > _defRPr_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_TextParagraphProperties* t() { return static_cast<CT_TextParagraphProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextLineBreak_writer : public type_writer
		{
			auto_type_writer< CT_TextCharacterProperties_writer > _rPr_writer;
			CT_TextLineBreak* t() { return static_cast<CT_TextLineBreak*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextField_writer : public type_writer
		{
			auto_type_writer< CT_TextCharacterProperties_writer > _rPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _pPr_writer;
			CT_TextField* t() { return static_cast<CT_TextField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

