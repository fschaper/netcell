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

#ifndef DML_TEXT_READERS_HPP
#define DML_TEXT_READERS_HPP

#include "dml-text.hpp"
#include "dml-shapeGeometry_readers.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-textParagraph_readers.hpp"
#include "dml-shape3DScene_readers.hpp"
#include "dml-shape3DStyles_readers.hpp"
#include "dml-textRun_readers.hpp"
#include "dml-textCharacter_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TextNoAutofit_reader;
		class ST_TextFontScalePercent_reader;
		class CT_TextNormalAutofit_reader;
		class CT_TextShapeAutofit_reader;
		class ST_TextColumnCount_reader;
		class CT_TextBodyProperties_reader;
		class CT_TextListStyle_reader;
		class CT_TextParagraph_reader;
		class CT_TextBody_reader;

		class CT_TextNoAutofit_reader : public type_reader
		{
		protected:
			CT_TextNoAutofit* t() { return static_cast<CT_TextNoAutofit*>(target()); }
		};

		class ST_TextFontScalePercent_reader : public ST_Percentage_reader
		{
		protected:
			ST_TextFontScalePercent* t() { return static_cast<ST_TextFontScalePercent*>(target()); }
		};

		class CT_TextNormalAutofit_reader : public type_reader
		{
		protected:
			CT_TextNormalAutofit* t() { return static_cast<CT_TextNormalAutofit*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextShapeAutofit_reader : public type_reader
		{
		protected:
			CT_TextShapeAutofit* t() { return static_cast<CT_TextShapeAutofit*>(target()); }
		};

		class ST_TextColumnCount_reader : public type_reader
		{
		protected:
			ST_TextColumnCount* t() { return static_cast<ST_TextColumnCount*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_TextBodyProperties_reader : public type_reader
		{
			auto_type_reader< CT_PresetTextShape_reader > _prstTxWarp_reader;
			auto_type_reader< CT_TextNoAutofit_reader > _noAutofit_reader;
			auto_type_reader< CT_TextNormalAutofit_reader > _normAutofit_reader;
			auto_type_reader< CT_TextShapeAutofit_reader > _spAutoFit_reader;
			auto_type_reader< CT_Scene3D_reader > _scene3d_reader;
			auto_type_reader< CT_Shape3D_reader > _sp3d_reader;
			auto_type_reader< CT_FlatText_reader > _flatTx_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_TextBodyProperties* t() { return static_cast<CT_TextBodyProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextListStyle_reader : public type_reader
		{
			auto_type_reader< CT_TextParagraphProperties_reader > _defPPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl1pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl2pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl3pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl4pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl5pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl6pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl7pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl8pPr_reader;
			auto_type_reader< CT_TextParagraphProperties_reader > _lvl9pPr_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_TextListStyle* t() { return static_cast<CT_TextListStyle*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_TextParagraph_reader : public type_reader
		{
			auto_type_reader< CT_TextParagraphProperties_reader > _pPr_reader;
			auto_type_reader< CT_RegularTextRun_reader > _r_reader;
			auto_type_reader< CT_TextLineBreak_reader > _br_reader;
			auto_type_reader< CT_TextField_reader > _fld_reader;
			auto_type_reader< CT_TextCharacterProperties_reader > _endParaRPr_reader;
		protected:
			CT_TextParagraph* t() { return static_cast<CT_TextParagraph*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_TextBody_reader : public type_reader
		{
			auto_type_reader< CT_TextBodyProperties_reader > _bodyPr_reader;
			auto_type_reader< CT_TextListStyle_reader > _lstStyle_reader;
			auto_type_reader< CT_TextParagraph_reader > _p_reader;
		protected:
			CT_TextBody* t() { return static_cast<CT_TextBody*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

