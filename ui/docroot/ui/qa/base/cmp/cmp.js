/*
 * \brief components handling routines
 *
 * \file cmp.js
 *
 * Copyright (C) 2006-2011 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may obtain a copy of the License at
 *
 * <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *   http://www.jedox.com/license_palo_bi_suite.txt
 * </a>
 *
 * If you are developing and distributing open source applications under the
 * GPL License, then you are free to use Palo under the GPL License.  For OEMs,
 * ISVs, and VARs who distribute Palo with their products, and do not license
 * and distribute their source code under the GPL, Jedox provides a flexible
 * OEM Commercial License.
 *
 * \author
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: cmp.js 5047 2011-06-10 10:26:19Z djordjez $
 *
 */

Jedox.qa.cmp = new function ()
{
	var that = this;

	var _type2cls = {
	  'btn':	'Button'
	, 'cmb':	'Combobox'
	, 'chk':	'Checkbox'
	, 'rd':		'Radio'
	, 'dv':		'DataView'
	, 'tbp':	'TabPanel'
	, 'grd':	'Grid'
	, 'wnd':	'Window'
	, 'fld':	'InputField'
	, 'mn':		'Menu'
	, 'spn':	'Spinner'
	, 'tx':		'TextArea'
	, 'tr':		'Tree'
	, 'tfl':	'TriggerField'
	, 'tlb':	'Toolbar'
	};

	this.get = function (id, data)
	{
		/*
		 * checking if modal dialog is present
		 * andrejv
		 */
//		var active = Jedox.dlg.dlgRegistry.getActive();
//		var el = (id=="_wnd")? active.win : Ext.getCmp(id).findParentByType("window");
//
//		if (active && active.win && active.win.modal && (!el || (active.id != "JedoxMsgBox" && el.id != active.id))){
//			return null;
//		}
//		// end of check

		var type = id.substr(id.lastIndexOf('_') + 1);

		return type in _type2cls ? new this[_type2cls[type]](id, data) : new this.Generic(id, data);
	};

};