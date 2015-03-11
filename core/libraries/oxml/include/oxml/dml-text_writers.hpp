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

#ifndef DML_TEXT_WRITERS_HPP
#define DML_TEXT_WRITERS_HPP

#include "dml-text.hpp"
#include "dml-text_literals.hpp"
#include "dml-shapeGeometry_writers.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-textParagraph_writers.hpp"
#include "dml-shape3DScene_writers.hpp"
#include "dml-shape3DStyles_writers.hpp"
#include "dml-textRun_writers.hpp"
#include "dml-textCharacter_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TextNoAutofit_writer;
		class ST_TextFontScalePercent_writer;
		class CT_TextNormalAutofit_writer;
		class CT_TextShapeAutofit_writer;
		class ST_TextColumnCount_writer;
		class CT_TextBodyProperties_writer;
		class CT_TextListStyle_writer;
		class CT_TextParagraph_writer;
		class CT_TextBody_writer;

		class CT_TextNoAutofit_writer : public type_writer
		{
			CT_TextNoAutofit* t() { return static_cast<CT_TextNoAutofit*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextFontScalePercent_writer : public ST_Percentage_writer
		{
			ST_TextFontScalePercent* t() { return static_cast<ST_TextFontScalePercent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextNormalAutofit_writer : public type_writer
		{
			CT_TextNormalAutofit* t() { return static_cast<CT_TextNormalAutofit*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextShapeAutofit_writer : public type_writer
		{
			CT_TextShapeAutofit* t() { return static_cast<CT_TextShapeAutofit*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextColumnCount_writer : public type_writer
		{
			ST_TextColumnCount* t() { return static_cast<ST_TextColumnCount*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBodyProperties_writer : public type_writer
		{
			auto_type_writer< CT_PresetTextShape_writer > _prstTxWarp_writer;
			auto_type_writer< CT_TextNoAutofit_writer > _noAutofit_writer;
			auto_type_writer< CT_TextNormalAutofit_writer > _normAutofit_writer;
			auto_type_writer< CT_TextShapeAutofit_writer > _spAutoFit_writer;
			auto_type_writer< CT_Scene3D_writer > _scene3d_writer;
			auto_type_writer< CT_Shape3D_writer > _sp3d_writer;
			auto_type_writer< CT_FlatText_writer > _flatTx_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_TextBodyProperties* t() { return static_cast<CT_TextBodyProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextListStyle_writer : public type_writer
		{
			auto_type_writer< CT_TextParagraphProperties_writer > _defPPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl1pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl2pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl3pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl4pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl5pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl6pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl7pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl8pPr_writer;
			auto_type_writer< CT_TextParagraphProperties_writer > _lvl9pPr_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_TextListStyle* t() { return static_cast<CT_TextListStyle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextParagraph_writer : public type_writer
		{
			auto_type_writer< CT_TextParagraphProperties_writer > _pPr_writer;
			auto_type_writer< CT_RegularTextRun_writer > _r_writer;
			auto_type_writer< CT_TextLineBreak_writer > _br_writer;
			auto_type_writer< CT_TextField_writer > _fld_writer;
			auto_type_writer< CT_TextCharacterProperties_writer > _endParaRPr_writer;
			CT_TextParagraph* t() { return static_cast<CT_TextParagraph*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBody_writer : public type_writer
		{
			auto_type_writer< CT_TextBodyProperties_writer > _bodyPr_writer;
			auto_type_writer< CT_TextListStyle_writer > _lstStyle_writer;
			auto_type_writer< CT_TextParagraph_writer > _p_writer;
			CT_TextBody* t() { return static_cast<CT_TextBody*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

