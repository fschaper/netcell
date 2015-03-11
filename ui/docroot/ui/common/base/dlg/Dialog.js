/*
 * \brief Dialog Base class.
 *
 * \file Base.js
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
 * SVN: $Id: Dialog.js 5117 2011-07-15 12:37:01Z drazenk $
 *
 */

Jedox.dlg.Dialog = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function () {
		// private fields
		var that = this;

		// private methods

		// public fields
		this.id = null;
		this.win = null;
		this.context = 'Dialog';
		this.prevContext = null;

		this.containers = {};
		this.components = {};
		this.cmpFocus = null;

		// privileged methods

		// constructor code
	};
}
)();

//public methods
Jedox.dlg.Dialog.prototype = {

	setContext: function() {
		this.prevContext = Jedox.kbd.ctxRegistry.add(this.context);
	},

	initFocus: function(selText, delay) {
		if (this.cmpFocus != null)
			this.cmpFocus.focus(selText, delay);
	},

	activate: function() {
		if (!Jedox.dlg.dlgRegistry.setActive(this.id))
			Jedox.dlg.dlgRegistry.add(this);

		Jedox.kbd.ctxRegistry.setActive(this.context);
	},

	close: function() {
		Jedox.dlg.dlgRegistry.remove(this.id);
		Jedox.kbd.ctxRegistry.remove(this.context, this.prevContext);
	}

};