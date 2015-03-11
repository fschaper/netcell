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

#ifndef DML_SHAPESTYLE_WRITERS_HPP
#define DML_SHAPESTYLE_WRITERS_HPP

#include "dml-shapeStyle.hpp"
#include "dml-shapeStyle_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-baseStylesheet_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_StyleMatrixReference_writer;
		class CT_FontReference_writer;
		class CT_ShapeStyle_writer;

		class CT_StyleMatrixReference_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_StyleMatrixReference* t() { return static_cast<CT_StyleMatrixReference*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FontReference_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_FontReference* t() { return static_cast<CT_FontReference*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ShapeStyle_writer : public type_writer
		{
			auto_type_writer< CT_StyleMatrixReference_writer > _lnRef_writer;
			auto_type_writer< CT_StyleMatrixReference_writer > _fillRef_writer;
			auto_type_writer< CT_StyleMatrixReference_writer > _effectRef_writer;
			auto_type_writer< CT_FontReference_writer > _fontRef_writer;
			CT_ShapeStyle* t() { return static_cast<CT_ShapeStyle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

