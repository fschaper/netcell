/*
 * \brief Keyboard Dialog class.
 *
 * \file Dialog.js
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: Dialog.js 3471 2010-07-06 13:33:35Z drazenk $
 *
 */

Jedox.kbd.Dialog = (function () {

	// class constructor
	return function () {
		Jedox.kbd.Dialog.parent.constructor.call(this);
	};

}
)();

// Dialog extends Window
Jedox.util.extend(Jedox.kbd.Dialog, Jedox.kbd.Window);

//public methods
clsRef = Jedox.kbd.Dialog;

//tab
clsRef.prototype._9 = function() {
	var that = this,
		dlg = Jedox.dlg.dlgRegistry.getActive(),
		win = dlg.win,
		conts = dlg.containers,
		elems = [];

	for (var cont in conts)
		elems = elems.concat(conts[cont].findBy(function(component, container) {
			return that._chkTabIdx(component);
		}));

	if (win.buttons)
		for (var btn in win.buttons)
			if (that._chkTabIdx(win.buttons[btn]))
				elems.push(win.buttons[btn]);

	this._tabFocus(elems);
	this._handleEnd();
};

clsRef = null;