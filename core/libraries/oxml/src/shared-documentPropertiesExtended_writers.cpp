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


#include "shared-documentPropertiesExtended_writers.hpp"
#include "shared-documentPropertiesExtended_literals.hpp"

namespace extended_properties
{
	namespace xio
	{
		void CT_VectorVariant_writer::write_target_to(xml_writer& w) {
			w.start_element(0, shared_documentPropertiesExtended_vector_literal);
			_vector_writer.get_writer(context(), &t()->vector)->write_target_to(w);
			w.end_element(0, shared_documentPropertiesExtended_vector_literal);
		}

		void CT_VectorLpstr_writer::write_target_to(xml_writer& w) {
			w.start_element(0, shared_documentPropertiesExtended_vector_literal);
			_vector_writer.get_writer(context(), &t()->vector)->write_target_to(w);
			w.end_element(0, shared_documentPropertiesExtended_vector_literal);
		}

		void CT_DigSigBlob_writer::write_target_to(xml_writer& w) {
			w.start_element(0, shared_documentPropertiesExtended_blob_literal);
			w.write_element_value(context()->serialize(t()->blob));
			w.end_element(0, shared_documentPropertiesExtended_blob_literal);
		}

		void CT_Properties_writer::write_target_to(xml_writer& w) {
			if (t()->Template.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Template_literal);
				w.write_element_value(context()->serialize(t()->Template.get()));
				w.end_element(0, shared_documentPropertiesExtended_Template_literal);
			}
			if (t()->Manager.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Manager_literal);
				w.write_element_value(context()->serialize(t()->Manager.get()));
				w.end_element(0, shared_documentPropertiesExtended_Manager_literal);
			}
			if (t()->Company.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Company_literal);
				w.write_element_value(context()->serialize(t()->Company.get()));
				w.end_element(0, shared_documentPropertiesExtended_Company_literal);
			}
			if (t()->Pages.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Pages_literal);
				w.write_element_value(context()->serialize(t()->Pages.get()));
				w.end_element(0, shared_documentPropertiesExtended_Pages_literal);
			}
			if (t()->Words.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Words_literal);
				w.write_element_value(context()->serialize(t()->Words.get()));
				w.end_element(0, shared_documentPropertiesExtended_Words_literal);
			}
			if (t()->Characters.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Characters_literal);
				w.write_element_value(context()->serialize(t()->Characters.get()));
				w.end_element(0, shared_documentPropertiesExtended_Characters_literal);
			}
			if (t()->PresentationFormat.present()) {
				w.start_element(0, shared_documentPropertiesExtended_PresentationFormat_literal);
				w.write_element_value(context()->serialize(t()->PresentationFormat.get()));
				w.end_element(0, shared_documentPropertiesExtended_PresentationFormat_literal);
			}
			if (t()->Lines.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Lines_literal);
				w.write_element_value(context()->serialize(t()->Lines.get()));
				w.end_element(0, shared_documentPropertiesExtended_Lines_literal);
			}
			if (t()->Paragraphs.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Paragraphs_literal);
				w.write_element_value(context()->serialize(t()->Paragraphs.get()));
				w.end_element(0, shared_documentPropertiesExtended_Paragraphs_literal);
			}
			if (t()->Slides.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Slides_literal);
				w.write_element_value(context()->serialize(t()->Slides.get()));
				w.end_element(0, shared_documentPropertiesExtended_Slides_literal);
			}
			if (t()->Notes.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Notes_literal);
				w.write_element_value(context()->serialize(t()->Notes.get()));
				w.end_element(0, shared_documentPropertiesExtended_Notes_literal);
			}
			if (t()->TotalTime.present()) {
				w.start_element(0, shared_documentPropertiesExtended_TotalTime_literal);
				w.write_element_value(context()->serialize(t()->TotalTime.get()));
				w.end_element(0, shared_documentPropertiesExtended_TotalTime_literal);
			}
			if (t()->HiddenSlides.present()) {
				w.start_element(0, shared_documentPropertiesExtended_HiddenSlides_literal);
				w.write_element_value(context()->serialize(t()->HiddenSlides.get()));
				w.end_element(0, shared_documentPropertiesExtended_HiddenSlides_literal);
			}
			if (t()->MMClips.present()) {
				w.start_element(0, shared_documentPropertiesExtended_MMClips_literal);
				w.write_element_value(context()->serialize(t()->MMClips.get()));
				w.end_element(0, shared_documentPropertiesExtended_MMClips_literal);
			}
			if (t()->ScaleCrop.present()) {
				w.start_element(0, shared_documentPropertiesExtended_ScaleCrop_literal);
				w.write_element_value(context()->serialize(t()->ScaleCrop.get()));
				w.end_element(0, shared_documentPropertiesExtended_ScaleCrop_literal);
			}
			if (t()->HeadingPairs.present()) {
				w.start_element(0, shared_documentPropertiesExtended_HeadingPairs_literal);
				_HeadingPairs_writer.get_writer(context(), &t()->HeadingPairs.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesExtended_HeadingPairs_literal);
			}
			if (t()->TitlesOfParts.present()) {
				w.start_element(0, shared_documentPropertiesExtended_TitlesOfParts_literal);
				_TitlesOfParts_writer.get_writer(context(), &t()->TitlesOfParts.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesExtended_TitlesOfParts_literal);
			}
			if (t()->LinksUpToDate.present()) {
				w.start_element(0, shared_documentPropertiesExtended_LinksUpToDate_literal);
				w.write_element_value(context()->serialize(t()->LinksUpToDate.get()));
				w.end_element(0, shared_documentPropertiesExtended_LinksUpToDate_literal);
			}
			if (t()->CharactersWithSpaces.present()) {
				w.start_element(0, shared_documentPropertiesExtended_CharactersWithSpaces_literal);
				w.write_element_value(context()->serialize(t()->CharactersWithSpaces.get()));
				w.end_element(0, shared_documentPropertiesExtended_CharactersWithSpaces_literal);
			}
			if (t()->SharedDoc.present()) {
				w.start_element(0, shared_documentPropertiesExtended_SharedDoc_literal);
				w.write_element_value(context()->serialize(t()->SharedDoc.get()));
				w.end_element(0, shared_documentPropertiesExtended_SharedDoc_literal);
			}
			if (t()->HyperlinkBase.present()) {
				w.start_element(0, shared_documentPropertiesExtended_HyperlinkBase_literal);
				w.write_element_value(context()->serialize(t()->HyperlinkBase.get()));
				w.end_element(0, shared_documentPropertiesExtended_HyperlinkBase_literal);
			}
			if (t()->HLinks.present()) {
				w.start_element(0, shared_documentPropertiesExtended_HLinks_literal);
				_HLinks_writer.get_writer(context(), &t()->HLinks.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesExtended_HLinks_literal);
			}
			if (t()->HyperlinksChanged.present()) {
				w.start_element(0, shared_documentPropertiesExtended_HyperlinksChanged_literal);
				w.write_element_value(context()->serialize(t()->HyperlinksChanged.get()));
				w.end_element(0, shared_documentPropertiesExtended_HyperlinksChanged_literal);
			}
			if (t()->DigSig.present()) {
				w.start_element(0, shared_documentPropertiesExtended_DigSig_literal);
				_DigSig_writer.get_writer(context(), &t()->DigSig.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesExtended_DigSig_literal);
			}
			if (t()->Application.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Application_literal);
				w.write_element_value(context()->serialize(t()->Application.get()));
				w.end_element(0, shared_documentPropertiesExtended_Application_literal);
			}
			if (t()->AppVersion.present()) {
				w.start_element(0, shared_documentPropertiesExtended_AppVersion_literal);
				w.write_element_value(context()->serialize(t()->AppVersion.get()));
				w.end_element(0, shared_documentPropertiesExtended_AppVersion_literal);
			}
			if (t()->DocSecurity.present()) {
				w.start_element(0, shared_documentPropertiesExtended_DocSecurity_literal);
				w.write_element_value(context()->serialize(t()->DocSecurity.get()));
				w.end_element(0, shared_documentPropertiesExtended_DocSecurity_literal);
			}
		}

		void shared_documentPropertiesExtended_writer::write_target_to(xml_writer& w) {
			if (t()->Properties.present()) {
				w.start_element(0, shared_documentPropertiesExtended_Properties_literal);
					w.attribute(0, shared_documentPropertiesExtended_xmlns_literal, shared_documentPropertiesExtended_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_extended_properties_literal);
					w.attribute(shared_documentPropertiesExtended_xmlns_literal, shared_documentPropertiesExtended_vt_literal, shared_documentPropertiesExtended_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_docPropsVTypes_literal);
					w.attribute(shared_documentPropertiesExtended_xmlns_literal, shared_documentPropertiesExtended_xsd_literal, shared_documentPropertiesExtended_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_Properties_writer.get_writer(context(), &t()->Properties.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesExtended_Properties_literal);
			}
		}

	}
}
