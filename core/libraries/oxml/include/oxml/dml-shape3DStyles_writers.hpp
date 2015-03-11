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

#ifndef DML_SHAPE3DSTYLES_WRITERS_HPP
#define DML_SHAPE3DSTYLES_WRITERS_HPP

#include "dml-shape3DStyles.hpp"
#include "dml-shape3DStyles_literals.hpp"
#include "dml-baseTypes_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Bevel_writer;
		class CT_Shape3D_writer;
		class CT_FlatText_writer;

		class CT_Bevel_writer : public type_writer
		{
			CT_Bevel* t() { return static_cast<CT_Bevel*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Shape3D_writer : public type_writer
		{
			auto_type_writer< CT_Bevel_writer > _bevelT_writer;
			auto_type_writer< CT_Bevel_writer > _bevelB_writer;
			auto_type_writer< CT_Color_writer > _extrusionClr_writer;
			auto_type_writer< CT_Color_writer > _contourClr_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_Shape3D* t() { return static_cast<CT_Shape3D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FlatText_writer : public type_writer
		{
			CT_FlatText* t() { return static_cast<CT_FlatText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

