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

#ifndef DML_AUDIOVIDEO_WRITERS_HPP
#define DML_AUDIOVIDEO_WRITERS_HPP

#include "dml-audioVideo.hpp"
#include "dml-audioVideo_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "shared-relationshipReference_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_AudioCDTime_writer;
		class CT_AudioCD_writer;
		class CT_AudioFile_writer;
		class CT_VideoFile_writer;
		class CT_QuickTimeFile_writer;

		class CT_AudioCDTime_writer : public type_writer
		{
			CT_AudioCDTime* t() { return static_cast<CT_AudioCDTime*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AudioCD_writer : public type_writer
		{
			auto_type_writer< CT_AudioCDTime_writer > _st_writer;
			auto_type_writer< CT_AudioCDTime_writer > _end_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_AudioCD* t() { return static_cast<CT_AudioCD*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AudioFile_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_AudioFile* t() { return static_cast<CT_AudioFile*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VideoFile_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_VideoFile* t() { return static_cast<CT_VideoFile*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QuickTimeFile_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_QuickTimeFile* t() { return static_cast<CT_QuickTimeFile*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

