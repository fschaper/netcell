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

#ifndef DML_AUDIOVIDEO_HPP
#define DML_AUDIOVIDEO_HPP


#include "dml-baseTypes.hpp"
#include "shared-relationshipReference.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_AudioCDTime;
	class CT_AudioCD;
	class CT_AudioFile;
	class CT_VideoFile;
	class CT_QuickTimeFile;

	class CT_AudioCDTime
	{
	public:
		CT_AudioCDTime() : time(0U) {}
		UnsignedByte track;
		UnsignedInt time;
	};

	class CT_AudioCD
	{
	public:
		CT_AudioCDTime st;
		CT_AudioCDTime end;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_AudioFile
	{
	public:
		poptional< CT_OfficeArtExtensionList > extLst;
		::relationships::ST_RelationshipId link;
	};

	class CT_VideoFile
	{
	public:
		poptional< CT_OfficeArtExtensionList > extLst;
		::relationships::ST_RelationshipId link;
	};

	class CT_QuickTimeFile
	{
	public:
		poptional< CT_OfficeArtExtensionList > extLst;
		::relationships::ST_RelationshipId link;
	};

}
#endif

