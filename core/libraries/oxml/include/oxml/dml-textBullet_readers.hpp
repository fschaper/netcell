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

#ifndef DML_TEXTBULLET_READERS_HPP
#define DML_TEXTBULLET_READERS_HPP

#include "dml-textBullet.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-textCharacter_readers.hpp"
#include "dml-shapeEffects_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TextBulletColorFollowText_reader;
		class CT_TextBulletSizeFollowText_reader;
		class ST_TextBulletSizePercent_reader;
		class CT_TextBulletSizePercent_reader;
		class CT_TextBulletSizePoint_reader;
		class CT_TextBulletTypefaceFollowText_reader;
		class CT_TextNoBullet_reader;
		class ST_TextBulletStartAtNum_reader;
		class CT_TextAutonumberBullet_reader;
		class CT_TextCharBullet_reader;
		class CT_TextBlipBullet_reader;

		class CT_TextBulletColorFollowText_reader : public type_reader
		{
		protected:
			CT_TextBulletColorFollowText* t() { return static_cast<CT_TextBulletColorFollowText*>(target()); }
		};

		class CT_TextBulletSizeFollowText_reader : public type_reader
		{
		protected:
			CT_TextBulletSizeFollowText* t() { return static_cast<CT_TextBulletSizeFollowText*>(target()); }
		};

		class ST_TextBulletSizePercent_reader : public ST_Percentage_reader
		{
		protected:
			ST_TextBulletSizePercent* t() { return static_cast<ST_TextBulletSizePercent*>(target()); }
		};

		class CT_TextBulletSizePercent_reader : public type_reader
		{
		protected:
			CT_TextBulletSizePercent* t() { return static_cast<CT_TextBulletSizePercent*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextBulletSizePoint_reader : public type_reader
		{
		protected:
			CT_TextBulletSizePoint* t() { return static_cast<CT_TextBulletSizePoint*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextBulletTypefaceFollowText_reader : public type_reader
		{
		protected:
			CT_TextBulletTypefaceFollowText* t() { return static_cast<CT_TextBulletTypefaceFollowText*>(target()); }
		};

		class CT_TextNoBullet_reader : public type_reader
		{
		protected:
			CT_TextNoBullet* t() { return static_cast<CT_TextNoBullet*>(target()); }
		};

		class ST_TextBulletStartAtNum_reader : public type_reader
		{
		protected:
			ST_TextBulletStartAtNum* t() { return static_cast<ST_TextBulletStartAtNum*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_TextAutonumberBullet_reader : public type_reader
		{
		protected:
			CT_TextAutonumberBullet* t() { return static_cast<CT_TextAutonumberBullet*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextCharBullet_reader : public type_reader
		{
		protected:
			CT_TextCharBullet* t() { return static_cast<CT_TextCharBullet*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextBlipBullet_reader : public type_reader
		{
			auto_type_reader< CT_Blip_reader > _blip_reader;
		protected:
			CT_TextBlipBullet* t() { return static_cast<CT_TextBlipBullet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

