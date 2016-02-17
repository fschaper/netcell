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

#ifndef SML_SHEETMETADATA_READERS_HPP
#define SML_SHEETMETADATA_READERS_HPP

#include "sml-sheetMetadata.hpp"
#include "sml-baseTypes_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_MetadataType_reader;
		class CT_MetadataTypes_reader;
		class CT_MetadataStrings_reader;
		class CT_MetadataStringIndex_reader;
		class CT_MdxTuple_reader;
		class CT_MdxSet_reader;
		class CT_MdxMemeberProp_reader;
		class CT_MdxKPI_reader;
		class CT_Mdx_reader;
		class CT_MdxMetadata_reader;
		class CT_FutureMetadataBlock_reader;
		class CT_FutureMetadata_reader;
		class CT_MetadataRecord_reader;
		class CT_MetadataBlock_reader;
		class CT_MetadataBlocks_reader;
		class CT_Metadata_reader;
		class sml_sheetMetadata_reader;

		class CT_MetadataType_reader : public type_reader
		{
		protected:
			CT_MetadataType* t() { return static_cast<CT_MetadataType*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MetadataTypes_reader : public type_reader
		{
			auto_type_reader< CT_MetadataType_reader > _metadataType_reader;
		protected:
			CT_MetadataTypes* t() { return static_cast<CT_MetadataTypes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MetadataStrings_reader : public type_reader
		{
			auto_type_reader< CT_XStringElement_reader > _s_reader;
		protected:
			CT_MetadataStrings* t() { return static_cast<CT_MetadataStrings*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MetadataStringIndex_reader : public type_reader
		{
		protected:
			CT_MetadataStringIndex* t() { return static_cast<CT_MetadataStringIndex*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MdxTuple_reader : public type_reader
		{
			auto_type_reader< CT_MetadataStringIndex_reader > _n_reader;
		protected:
			CT_MdxTuple* t() { return static_cast<CT_MdxTuple*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MdxSet_reader : public type_reader
		{
			auto_type_reader< CT_MetadataStringIndex_reader > _n_reader;
		protected:
			CT_MdxSet* t() { return static_cast<CT_MdxSet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MdxMemeberProp_reader : public type_reader
		{
		protected:
			CT_MdxMemeberProp* t() { return static_cast<CT_MdxMemeberProp*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MdxKPI_reader : public type_reader
		{
		protected:
			CT_MdxKPI* t() { return static_cast<CT_MdxKPI*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Mdx_reader : public type_reader
		{
			auto_type_reader< CT_MdxTuple_reader > _t_reader;
			auto_type_reader< CT_MdxSet_reader > _ms_reader;
			auto_type_reader< CT_MdxMemeberProp_reader > _p_reader;
			auto_type_reader< CT_MdxKPI_reader > _k_reader;
		protected:
			CT_Mdx* t() { return static_cast<CT_Mdx*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MdxMetadata_reader : public type_reader
		{
			auto_type_reader< CT_Mdx_reader > _mdx_reader;
		protected:
			CT_MdxMetadata* t() { return static_cast<CT_MdxMetadata*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FutureMetadataBlock_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_FutureMetadataBlock* t() { return static_cast<CT_FutureMetadataBlock*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_FutureMetadata_reader : public type_reader
		{
			auto_type_reader< CT_FutureMetadataBlock_reader > _bk_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_FutureMetadata* t() { return static_cast<CT_FutureMetadata*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MetadataRecord_reader : public type_reader
		{
		protected:
			CT_MetadataRecord* t() { return static_cast<CT_MetadataRecord*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MetadataBlock_reader : public type_reader
		{
			auto_type_reader< CT_MetadataRecord_reader > _rc_reader;
		protected:
			CT_MetadataBlock* t() { return static_cast<CT_MetadataBlock*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_MetadataBlocks_reader : public type_reader
		{
			auto_type_reader< CT_MetadataBlock_reader > _bk_reader;
		protected:
			CT_MetadataBlocks* t() { return static_cast<CT_MetadataBlocks*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Metadata_reader : public type_reader
		{
			auto_type_reader< CT_MetadataTypes_reader > _metadataTypes_reader;
			auto_type_reader< CT_MetadataStrings_reader > _metadataStrings_reader;
			auto_type_reader< CT_MdxMetadata_reader > _mdxMetadata_reader;
			auto_type_reader< CT_FutureMetadata_reader > _futureMetadata_reader;
			auto_type_reader< CT_MetadataBlocks_reader > _cellMetadata_reader;
			auto_type_reader< CT_MetadataBlocks_reader > _valueMetadata_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Metadata* t() { return static_cast<CT_Metadata*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_sheetMetadata_reader : public type_reader
		{
			auto_type_reader< CT_Metadata_reader > _metadata_reader;
		protected:
			sml_sheetMetadata* t() { return static_cast<sml_sheetMetadata*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

