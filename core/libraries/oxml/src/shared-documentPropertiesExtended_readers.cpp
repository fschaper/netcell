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


#include "shared-documentPropertiesExtended_readers.hpp"
#include "shared-documentPropertiesExtended_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace extended_properties
{
	namespace xio
	{
		void CT_VectorVariant_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_vector_literal))
			{
				driver()->push(localname, _vector_reader.get_reader(&t()->vector));
				return;
			}
		}
		void CT_VectorLpstr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_vector_literal))
			{
				driver()->push(localname, _vector_reader.get_reader(&t()->vector));
				return;
			}
		}
		void CT_DigSigBlob_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_blob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->blob);
				return;
			}
		}
		void CT_Properties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_HeadingPairs_literal))
			{
				driver()->push(localname, _HeadingPairs_reader.get_reader(&t()->HeadingPairs.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_TitlesOfParts_literal))
			{
				driver()->push(localname, _TitlesOfParts_reader.get_reader(&t()->TitlesOfParts.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_HLinks_literal))
			{
				driver()->push(localname, _HLinks_reader.get_reader(&t()->HLinks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_DigSig_literal))
			{
				driver()->push(localname, _DigSig_reader.get_reader(&t()->DigSig.getset()));
				return;
			}
		}
		void CT_Properties_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Template_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Template.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Manager_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Manager.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Company_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Company.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Pages_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Pages.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Words_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Words.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Characters_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Characters.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_PresentationFormat_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->PresentationFormat.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Lines_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Lines.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Paragraphs_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Paragraphs.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Slides_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Slides.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Notes_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Notes.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_TotalTime_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->TotalTime.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_HiddenSlides_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->HiddenSlides.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_MMClips_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->MMClips.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_ScaleCrop_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ScaleCrop.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_LinksUpToDate_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->LinksUpToDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_CharactersWithSpaces_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->CharactersWithSpaces.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_SharedDoc_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->SharedDoc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_HyperlinkBase_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->HyperlinkBase.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_HyperlinksChanged_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->HyperlinksChanged.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Application_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->Application.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_AppVersion_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->AppVersion.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_DocSecurity_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->DocSecurity.getset());
				return;
			}
		}
		void shared_documentPropertiesExtended_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesExtended_Properties_literal))
			{
				driver()->push(localname, _Properties_reader.get_reader(&t()->Properties.getset()));
				return;
			}
		}
	}
}
