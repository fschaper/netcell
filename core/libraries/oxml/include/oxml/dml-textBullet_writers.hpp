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

#ifndef DML_TEXTBULLET_WRITERS_HPP
#define DML_TEXTBULLET_WRITERS_HPP

#include "dml-textBullet.hpp"
#include "dml-textBullet_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-textCharacter_writers.hpp"
#include "dml-shapeEffects_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TextBulletColorFollowText_writer;
		class CT_TextBulletSizeFollowText_writer;
		class ST_TextBulletSizePercent_writer;
		class CT_TextBulletSizePercent_writer;
		class CT_TextBulletSizePoint_writer;
		class CT_TextBulletTypefaceFollowText_writer;
		class CT_TextNoBullet_writer;
		class ST_TextBulletStartAtNum_writer;
		class CT_TextAutonumberBullet_writer;
		class CT_TextCharBullet_writer;
		class CT_TextBlipBullet_writer;

		class CT_TextBulletColorFollowText_writer : public type_writer
		{
			CT_TextBulletColorFollowText* t() { return static_cast<CT_TextBulletColorFollowText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBulletSizeFollowText_writer : public type_writer
		{
			CT_TextBulletSizeFollowText* t() { return static_cast<CT_TextBulletSizeFollowText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextBulletSizePercent_writer : public ST_Percentage_writer
		{
			ST_TextBulletSizePercent* t() { return static_cast<ST_TextBulletSizePercent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBulletSizePercent_writer : public type_writer
		{
			CT_TextBulletSizePercent* t() { return static_cast<CT_TextBulletSizePercent*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBulletSizePoint_writer : public type_writer
		{
			CT_TextBulletSizePoint* t() { return static_cast<CT_TextBulletSizePoint*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBulletTypefaceFollowText_writer : public type_writer
		{
			CT_TextBulletTypefaceFollowText* t() { return static_cast<CT_TextBulletTypefaceFollowText*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextNoBullet_writer : public type_writer
		{
			CT_TextNoBullet* t() { return static_cast<CT_TextNoBullet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_TextBulletStartAtNum_writer : public type_writer
		{
			ST_TextBulletStartAtNum* t() { return static_cast<ST_TextBulletStartAtNum*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextAutonumberBullet_writer : public type_writer
		{
			CT_TextAutonumberBullet* t() { return static_cast<CT_TextAutonumberBullet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextCharBullet_writer : public type_writer
		{
			CT_TextCharBullet* t() { return static_cast<CT_TextCharBullet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextBlipBullet_writer : public type_writer
		{
			auto_type_writer< CT_Blip_writer > _blip_writer;
			CT_TextBlipBullet* t() { return static_cast<CT_TextBlipBullet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

