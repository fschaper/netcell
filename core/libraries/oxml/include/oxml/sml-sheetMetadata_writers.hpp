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

#ifndef SML_SHEETMETADATA_WRITERS_HPP
#define SML_SHEETMETADATA_WRITERS_HPP

#include "sml-sheetMetadata.hpp"
#include "sml-sheetMetadata_literals.hpp"
#include "sml-baseTypes_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_MetadataType_writer;
		class CT_MetadataTypes_writer;
		class CT_MetadataStrings_writer;
		class CT_MetadataStringIndex_writer;
		class CT_MdxTuple_writer;
		class CT_MdxSet_writer;
		class CT_MdxMemeberProp_writer;
		class CT_MdxKPI_writer;
		class CT_Mdx_writer;
		class CT_MdxMetadata_writer;
		class CT_FutureMetadataBlock_writer;
		class CT_FutureMetadata_writer;
		class CT_MetadataRecord_writer;
		class CT_MetadataBlock_writer;
		class CT_MetadataBlocks_writer;
		class CT_Metadata_writer;
		class sml_sheetMetadata_writer;

		class CT_MetadataType_writer : public type_writer
		{
			CT_MetadataType* t() { return static_cast<CT_MetadataType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataTypes_writer : public type_writer
		{
			auto_type_writer< CT_MetadataType_writer > _metadataType_writer;
			CT_MetadataTypes* t() { return static_cast<CT_MetadataTypes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataStrings_writer : public type_writer
		{
			auto_type_writer< CT_XStringElement_writer > _s_writer;
			CT_MetadataStrings* t() { return static_cast<CT_MetadataStrings*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataStringIndex_writer : public type_writer
		{
			CT_MetadataStringIndex* t() { return static_cast<CT_MetadataStringIndex*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MdxTuple_writer : public type_writer
		{
			auto_type_writer< CT_MetadataStringIndex_writer > _n_writer;
			CT_MdxTuple* t() { return static_cast<CT_MdxTuple*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MdxSet_writer : public type_writer
		{
			auto_type_writer< CT_MetadataStringIndex_writer > _n_writer;
			CT_MdxSet* t() { return static_cast<CT_MdxSet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MdxMemeberProp_writer : public type_writer
		{
			CT_MdxMemeberProp* t() { return static_cast<CT_MdxMemeberProp*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MdxKPI_writer : public type_writer
		{
			CT_MdxKPI* t() { return static_cast<CT_MdxKPI*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Mdx_writer : public type_writer
		{
			auto_type_writer< CT_MdxTuple_writer > _t_writer;
			auto_type_writer< CT_MdxSet_writer > _ms_writer;
			auto_type_writer< CT_MdxMemeberProp_writer > _p_writer;
			auto_type_writer< CT_MdxKPI_writer > _k_writer;
			CT_Mdx* t() { return static_cast<CT_Mdx*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MdxMetadata_writer : public type_writer
		{
			auto_type_writer< CT_Mdx_writer > _mdx_writer;
			CT_MdxMetadata* t() { return static_cast<CT_MdxMetadata*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FutureMetadataBlock_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_FutureMetadataBlock* t() { return static_cast<CT_FutureMetadataBlock*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FutureMetadata_writer : public type_writer
		{
			auto_type_writer< CT_FutureMetadataBlock_writer > _bk_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_FutureMetadata* t() { return static_cast<CT_FutureMetadata*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataRecord_writer : public type_writer
		{
			CT_MetadataRecord* t() { return static_cast<CT_MetadataRecord*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataBlock_writer : public type_writer
		{
			auto_type_writer< CT_MetadataRecord_writer > _rc_writer;
			CT_MetadataBlock* t() { return static_cast<CT_MetadataBlock*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MetadataBlocks_writer : public type_writer
		{
			auto_type_writer< CT_MetadataBlock_writer > _bk_writer;
			CT_MetadataBlocks* t() { return static_cast<CT_MetadataBlocks*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Metadata_writer : public type_writer
		{
			auto_type_writer< CT_MetadataTypes_writer > _metadataTypes_writer;
			auto_type_writer< CT_MetadataStrings_writer > _metadataStrings_writer;
			auto_type_writer< CT_MdxMetadata_writer > _mdxMetadata_writer;
			auto_type_writer< CT_FutureMetadata_writer > _futureMetadata_writer;
			auto_type_writer< CT_MetadataBlocks_writer > _cellMetadata_writer;
			auto_type_writer< CT_MetadataBlocks_writer > _valueMetadata_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Metadata* t() { return static_cast<CT_Metadata*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_sheetMetadata_writer : public type_writer
		{
			auto_type_writer< CT_Metadata_writer > _metadata_writer;
			sml_sheetMetadata* t() { return static_cast<sml_sheetMetadata*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

