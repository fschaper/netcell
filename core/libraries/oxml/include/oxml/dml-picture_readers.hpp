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

#ifndef DML_PICTURE_READERS_HPP
#define DML_PICTURE_READERS_HPP

#include "dml-picture.hpp"
#include "dml-documentProperties_readers.hpp"
#include "dml-shapeEffects_readers.hpp"
#include "dml-shapeProperties_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_PictureNonVisual_reader;
		class CT_Picture_reader;
		class dml_picture_reader;

		class CT_PictureNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualPictureProperties_reader > _cNvPicPr_reader;
		protected:
			CT_PictureNonVisual* t() { return static_cast<CT_PictureNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Picture_reader : public type_reader
		{
			auto_type_reader< CT_PictureNonVisual_reader > _nvPicPr_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_ShapeProperties_reader > _spPr_reader;
		protected:
			CT_Picture* t() { return static_cast<CT_Picture*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class dml_picture_reader : public type_reader
		{
			auto_type_reader< CT_Picture_reader > _pic_reader;
		protected:
			dml_picture* t() { return static_cast<dml_picture*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

