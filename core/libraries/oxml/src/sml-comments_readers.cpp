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


#include "sml-comments_readers.hpp"
#include "sml-comments_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Authors_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_author_literal))
			{
				t()->author.resize(t()->author.size()+1);
				driver()->push(localname, _author_reader.get_reader(&t()->author.back()));
				return;
			}
		}
		void CT_Comment_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_text_literal))
			{
				driver()->push(localname, _text_reader.get_reader(&t()->text));
				return;
			}
		}
		void CT_Comment_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_comments_authorId_literal))
			{
				driver()->context()->parse(value, t()->authorId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_comments_guid_literal))
			{
				driver()->context()->parse(value, t()->guid.getset());
				return;
			}
		}
		void CT_CommentList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_comment_literal))
			{
				t()->comment.resize(t()->comment.size()+1);
				driver()->push(localname, _comment_reader.get_reader(&t()->comment.back()));
				return;
			}
		}
		void CT_Comments_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_authors_literal))
			{
				driver()->push(localname, _authors_reader.get_reader(&t()->authors));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_comments_commentList_literal))
			{
				driver()->push(localname, _commentList_reader.get_reader(&t()->commentList));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_comments_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_comments_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_comments_comments_literal))
			{
				driver()->push(localname, _comments_reader.get_reader(&t()->comments.getset()));
				return;
			}
		}
	}
}
