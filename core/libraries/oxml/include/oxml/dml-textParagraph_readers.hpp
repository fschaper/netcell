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

#ifndef DML_TEXTPARAGRAPH_READERS_HPP
#define DML_TEXTPARAGRAPH_READERS_HPP

#include "dml-textParagraph.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-textBullet_readers.hpp"
#include "dml-textCharacter_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_TextSpacingPercent_reader;
		class CT_TextSpacingPercent_reader;
		class ST_TextSpacingPoint_reader;
		class CT_TextSpacingPoint_reader;
		class CT_TextSpacing_reader;
		class CT_TextTabStop_reader;
		class CT_TextTabStopList_reader;
		class ST_TextMargin_reader;
		class ST_TextIndentLevelType_reader;
		class ST_TextIndent_reader;
		class CT_TextParagraphProperties_reader;
		class CT_TextLineBreak_reader;
		class CT_TextField_reader;

		class ST_TextSpacingPercent_reader : public ST_Percentage_reader
		{
		protected:
			ST_TextSpacingPercent* t() { return static_cast<ST_TextSpacingPercent*>(target()); }
		};

		class CT_TextSpacingPercent_reader : public type_reader
		{
		protected:
			CT_TextSpacingPercent* t() { return static_cast<CT_TextSpacingPercent*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_TextSpacingPoint_reader : public type_reader
		{
		protected:
			ST_TextSpacingPoint* t() { return static_cast<ST_TextSpacingPoint*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_TextSpacingPoint_reader : public type_reader
		{
		protected:
			CT_TextSpacingPoint* t() { return static_cast<CT_TextSpacingPoint*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextSpacing_reader : public type_reader
		{
			auto_type_reader< CT_TextSpacingPercent_reader > _spcPct_reader;
			auto_type_reader< CT_TextSpacingPoint_reader > _spcPts_reader;
		protected:
			CT_TextSpacing* t() { return static_cast<CT_TextSpacing*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_TextTabStop_reader : public type_reader
		{
		protected:
			CT_TextTabStop* t() { return static_cast<CT_TextTabStop*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextTabStopList_reader : public type_reader
		{
			auto_type_reader< CT_TextTabStop_reader > _tab_reader;
		protected:
			CT_TextTabStopList* t() { return static_cast<CT_TextTabStopList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_TextMargin_reader : public ST_Coordinate32_reader
		{
		protected:
			ST_TextMargin* t() { return static_cast<ST_TextMargin*>(target()); }
		};

		class ST_TextIndentLevelType_reader : public type_reader
		{
		protected:
			ST_TextIndentLevelType* t() { return static_cast<ST_TextIndentLevelType*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_TextIndent_reader : public ST_Coordinate32_reader
		{
		protected:
			ST_TextIndent* t() { return static_cast<ST_TextIndent*>(target()); }
		};

		class CT_TextParagraphProperties_reader : public type_reader
		{
			auto_type_reader< CT_TextSpacing_reader > _lnSpc_reader;
			auto_type_reader< CT_TextSpacing_reader > _spcBef_reader;
			auto_type_reader< CT_TextSpacing_reader > _spcAft_reader;
			auto_type_reader< CT_TextBulletColorFollowText_reader > _buClrTx_reader;
			auto_type_reader< CT_Color_reader > _buClr_reader;
			auto_type_reader< CT_TextBulletSizeFollowText_reader > _buSzTx_reader;
			auto_type_reader< CT_TextBulletSizePercent_reader > _buSzPct_reader;
			auto_type_reader< CT_TextBulletSizePoint_reader > _buSzPts_reader;
			auto_type_reader< CT_TextBulletTypefaceFollowText_reader > _buFontTx_reader;
			auto_type_reader< CT_TextFont_reader > _buFont_reader;
			auto_type_reader< CT_TextNoBullet_reader > _buNone_reader;
			auto_type_reader< CT_TextAutonumberBullet_reader > _buAutoNum_reader;
			auto_type_reader< CT_TextCharBullet_reader > _buChar_reader;
			auto_type_reader< CT_TextBlipBullet_reader > _buBlip_reader;
			auto_type_reader< CT_TextTabStopList_reader > _tabLst_reader;
			auto_type_reader< CT_TextCharacterProperties_reader > _defRPr_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_TextParagraphProperties* t() { return static_cast<CT_TextParagraphProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextLineBreak_reader : public type_reader
		{
			auto_type_reader< CT_TextCharacterProperties_reader > _rPr_reader;
		protected:
			CT_TextLineBreak* t() { return static_cast<CT_TextLineBreak*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_TextField_reader : public type_reader
		{
			auto_type_reader< CT_TextCharacterProperties_reader > _rPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _pPr_reader;
		protected:
			CT_TextField* t() { return static_cast<CT_TextField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

