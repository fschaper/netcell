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

#ifndef DML_GRAPHICALOBJECTFORMAT_WRITERS_HPP
#define DML_GRAPHICALOBJECTFORMAT_WRITERS_HPP

#include "dml-graphicalObjectFormat.hpp"
#include "dml-graphicalObjectFormat_literals.hpp"
#include "dml-shapeEffects_writers.hpp"
#include "dml-shapeLineProperties_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_BackgroundFormatting_writer;
		class CT_WholeE2oFormatting_writer;

		class CT_BackgroundFormatting_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			auto_type_writer< CT_EffectList_writer > _effectLst_writer;
			auto_type_writer< CT_EffectContainer_writer > _effectDag_writer;
			CT_BackgroundFormatting* t() { return static_cast<CT_BackgroundFormatting*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WholeE2oFormatting_writer : public type_writer
		{
			auto_type_writer< CT_LineProperties_writer > _ln_writer;
			auto_type_writer< CT_EffectList_writer > _effectLst_writer;
			auto_type_writer< CT_EffectContainer_writer > _effectDag_writer;
			CT_WholeE2oFormatting* t() { return static_cast<CT_WholeE2oFormatting*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

