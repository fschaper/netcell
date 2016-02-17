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

#ifndef SML_COMMENTS_READERS_HPP
#define SML_COMMENTS_READERS_HPP

#include "sml-comments.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-sharedStringTable_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Authors_reader;
		class CT_Comment_reader;
		class CT_CommentList_reader;
		class CT_Comments_reader;
		class sml_comments_reader;

		class CT_Authors_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _author_reader;
		protected:
			CT_Authors* t() { return static_cast<CT_Authors*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Comment_reader : public type_reader
		{
			auto_type_reader< CT_Rst_reader > _text_reader;
		protected:
			CT_Comment* t() { return static_cast<CT_Comment*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CommentList_reader : public type_reader
		{
			auto_type_reader< CT_Comment_reader > _comment_reader;
		protected:
			CT_CommentList* t() { return static_cast<CT_CommentList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Comments_reader : public type_reader
		{
			auto_type_reader< CT_Authors_reader > _authors_reader;
			auto_type_reader< CT_CommentList_reader > _commentList_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Comments* t() { return static_cast<CT_Comments*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_comments_reader : public type_reader
		{
			auto_type_reader< CT_Comments_reader > _comments_reader;
		protected:
			sml_comments* t() { return static_cast<sml_comments*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

