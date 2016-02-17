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

#ifndef SHARED_DOCUMENTPROPERTIESEXTENDED_READERS_HPP
#define SHARED_DOCUMENTPROPERTIESEXTENDED_READERS_HPP

#include "shared-documentPropertiesExtended.hpp"
#include "shared-documentPropertiesVariantTypes_readers.hpp"

namespace extended_properties
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_VectorVariant_reader;
		class CT_VectorLpstr_reader;
		class CT_DigSigBlob_reader;
		class CT_Properties_reader;
		class shared_documentPropertiesExtended_reader;

		class CT_VectorVariant_reader : public type_reader
		{
			auto_type_reader< ::docPropsVTypes::xio::CT_Vector_reader > _vector_reader;
		protected:
			CT_VectorVariant* t() { return static_cast<CT_VectorVariant*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_VectorLpstr_reader : public type_reader
		{
			auto_type_reader< ::docPropsVTypes::xio::CT_Vector_reader > _vector_reader;
		protected:
			CT_VectorLpstr* t() { return static_cast<CT_VectorLpstr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_DigSigBlob_reader : public type_reader
		{
		protected:
			CT_DigSigBlob* t() { return static_cast<CT_DigSigBlob*>(target()); }
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

		class CT_Properties_reader : public type_reader
		{
			auto_type_reader< CT_VectorVariant_reader > _HeadingPairs_reader;
			auto_type_reader< CT_VectorLpstr_reader > _TitlesOfParts_reader;
			auto_type_reader< CT_VectorVariant_reader > _HLinks_reader;
			auto_type_reader< CT_DigSigBlob_reader > _DigSig_reader;
		protected:
			CT_Properties* t() { return static_cast<CT_Properties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

		class shared_documentPropertiesExtended_reader : public type_reader
		{
			auto_type_reader< CT_Properties_reader > _Properties_reader;
		protected:
			shared_documentPropertiesExtended* t() { return static_cast<shared_documentPropertiesExtended*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

