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

#ifndef SML_COMMENTS_HPP
#define SML_COMMENTS_HPP


#include "sml-baseTypes.hpp"
#include "sml-sharedStringTable.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Authors;
	class CT_Comment;
	class CT_CommentList;
	class CT_Comments;
	class sml_comments;

	class CT_Authors
	{
	public:
		std::vector< ST_Xstring > author;
	};

	class CT_Comment
	{
	public:
		CT_Rst text;
		ST_Ref ref;
		UnsignedInt authorId;
		poptional< ST_Guid > guid;
	};

	class CT_CommentList
	{
	public:
		std::vector< CT_Comment > comment;
	};

	class CT_Comments
	{
	public:
		CT_Authors authors;
		CT_CommentList commentList;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_comments
	{
	public:
		poptional< CT_Comments > comments;
	};

}
#endif

