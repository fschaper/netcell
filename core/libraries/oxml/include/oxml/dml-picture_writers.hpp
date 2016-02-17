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

#ifndef DML_PICTURE_WRITERS_HPP
#define DML_PICTURE_WRITERS_HPP

#include "dml-picture.hpp"
#include "dml-picture_literals.hpp"
#include "dml-documentProperties_writers.hpp"
#include "dml-shapeEffects_writers.hpp"
#include "dml-shapeProperties_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_PictureNonVisual_writer;
		class CT_Picture_writer;
		class dml_picture_writer;

		class CT_PictureNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualPictureProperties_writer > _cNvPicPr_writer;
			CT_PictureNonVisual* t() { return static_cast<CT_PictureNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Picture_writer : public type_writer
		{
			auto_type_writer< CT_PictureNonVisual_writer > _nvPicPr_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_ShapeProperties_writer > _spPr_writer;
			CT_Picture* t() { return static_cast<CT_Picture*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class dml_picture_writer : public type_writer
		{
			auto_type_writer< CT_Picture_writer > _pic_writer;
			dml_picture* t() { return static_cast<dml_picture*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

