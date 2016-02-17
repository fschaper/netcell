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

#ifndef SML_COMMENTS_WRITERS_HPP
#define SML_COMMENTS_WRITERS_HPP

#include "sml-comments.hpp"
#include "sml-comments_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-sharedStringTable_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Authors_writer;
		class CT_Comment_writer;
		class CT_CommentList_writer;
		class CT_Comments_writer;
		class sml_comments_writer;

		class CT_Authors_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _author_writer;
			CT_Authors* t() { return static_cast<CT_Authors*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Comment_writer : public type_writer
		{
			auto_type_writer< CT_Rst_writer > _text_writer;
			CT_Comment* t() { return static_cast<CT_Comment*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CommentList_writer : public type_writer
		{
			auto_type_writer< CT_Comment_writer > _comment_writer;
			CT_CommentList* t() { return static_cast<CT_CommentList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Comments_writer : public type_writer
		{
			auto_type_writer< CT_Authors_writer > _authors_writer;
			auto_type_writer< CT_CommentList_writer > _commentList_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Comments* t() { return static_cast<CT_Comments*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_comments_writer : public type_writer
		{
			auto_type_writer< CT_Comments_writer > _comments_writer;
			sml_comments* t() { return static_cast<sml_comments*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

