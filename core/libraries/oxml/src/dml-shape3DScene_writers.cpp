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


#include "dml-shape3DScene_writers.hpp"
#include "dml-shape3DScene_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_Scene3D_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_shape3DScene_camera_literal);
			_camera_writer.get_writer(context(), &t()->camera)->write_target_to(w);
			w.end_element(0, dml_shape3DScene_camera_literal);
			w.start_element(0, dml_shape3DScene_lightRig_literal);
			_lightRig_writer.get_writer(context(), &t()->lightRig)->write_target_to(w);
			w.end_element(0, dml_shape3DScene_lightRig_literal);
			if (t()->backdrop.present()) {
				w.start_element(0, dml_shape3DScene_backdrop_literal);
				_backdrop_writer.get_writer(context(), &t()->backdrop.get())->write_target_to(w);
				w.end_element(0, dml_shape3DScene_backdrop_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shape3DScene_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shape3DScene_extLst_literal);
			}
		}

	}
}
