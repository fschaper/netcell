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

#ifndef SHARED_DOCUMENTPROPERTIESEXTENDED_WRITERS_HPP
#define SHARED_DOCUMENTPROPERTIESEXTENDED_WRITERS_HPP

#include "shared-documentPropertiesExtended.hpp"
#include "shared-documentPropertiesExtended_literals.hpp"
#include "shared-documentPropertiesVariantTypes_writers.hpp"

namespace extended_properties
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_VectorVariant_writer;
		class CT_VectorLpstr_writer;
		class CT_DigSigBlob_writer;
		class CT_Properties_writer;
		class shared_documentPropertiesExtended_writer;

		class CT_VectorVariant_writer : public type_writer
		{
			auto_type_writer< ::docPropsVTypes::xio::CT_Vector_writer > _vector_writer;
			CT_VectorVariant* t() { return static_cast<CT_VectorVariant*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VectorLpstr_writer : public type_writer
		{
			auto_type_writer< ::docPropsVTypes::xio::CT_Vector_writer > _vector_writer;
			CT_VectorLpstr* t() { return static_cast<CT_VectorLpstr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DigSigBlob_writer : public type_writer
		{
			CT_DigSigBlob* t() { return static_cast<CT_DigSigBlob*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Properties_writer : public type_writer
		{
			auto_type_writer< CT_VectorVariant_writer > _HeadingPairs_writer;
			auto_type_writer< CT_VectorLpstr_writer > _TitlesOfParts_writer;
			auto_type_writer< CT_VectorVariant_writer > _HLinks_writer;
			auto_type_writer< CT_DigSigBlob_writer > _DigSig_writer;
			CT_Properties* t() { return static_cast<CT_Properties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class shared_documentPropertiesExtended_writer : public type_writer
		{
			auto_type_writer< CT_Properties_writer > _Properties_writer;
			shared_documentPropertiesExtended* t() { return static_cast<shared_documentPropertiesExtended*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

