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


#include "dml-textBullet_writers.hpp"
#include "dml-textBullet_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_TextBulletColorFollowText_writer::write_target_to(xml_writer& w) {
		}

		void CT_TextBulletSizeFollowText_writer::write_target_to(xml_writer& w) {
		}

		void ST_TextBulletSizePercent_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void CT_TextBulletSizePercent_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, dml_textBullet_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_TextBulletSizePoint_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, dml_textBullet_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_TextBulletTypefaceFollowText_writer::write_target_to(xml_writer& w) {
		}

		void CT_TextNoBullet_writer::write_target_to(xml_writer& w) {
		}

		void ST_TextBulletStartAtNum_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_TextAutonumberBullet_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_textBullet_type_literal, context()->serialize(t()->type));
			if (t()->startAt != 1)
				w.attribute(0, dml_textBullet_startAt_literal, context()->serialize(t()->startAt));
		}

		void CT_TextCharBullet_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_textBullet__char__literal, context()->serialize(t()->_char_));
		}

		void CT_TextBlipBullet_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_textBullet_blip_literal);
			_blip_writer.get_writer(context(), &t()->blip)->write_target_to(w);
			w.end_element(0, dml_textBullet_blip_literal);
		}

	}
}
