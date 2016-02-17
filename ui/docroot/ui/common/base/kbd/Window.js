/*
 * \brief Keyboard Window class.
 *
 * \file Window.js
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
 * SVN: $Id: Window.js 3999 2010-10-13 09:19:51Z andrejv $
 *
 */

Jedox.kbd.Window = (function () {

	// class constructor
	return function () {
		Jedox.kbd.Window.parent.constructor.call(this);
	};

}
)();

// Window extends Base
Jedox.util.extend(Jedox.kbd.Window, Jedox.kbd.Base);

//public methods
clsRef = Jedox.kbd.Window;

clsRef.prototype._chkCmpTags = function(tags) {
	var evTarget = document.all ? this.event.srcElement : this.event.target;
	tags.unshift(Jedox.kbd.Base.tags.NO_ANY);

	function inTags(cls) {
		for (tag in tags){
			if (tags[tag] == cls && typeof tags[tag] == 'string'){
				return true;
			}
		}

		return false;
	}

	for (var i = 10, el = evTarget, clsList = el.classList, cls; i > 0; i--, el = el.parentNode) {
		if (el)
			clsList = el.classList;
		else
			break;

		for (cls in clsList)
			if (inTags(clsList[cls]))
				return true;
	}

	return false;
};

// enter
clsRef.prototype._13 = function() {
	if (!this._chkCmpTags([Jedox.kbd.Base.tags.NO_ENTER]))
		Jedox.dlg.dlgRegistry.getActive().components.OK.handler();

	this._handleEnd();
};

// escape
clsRef.prototype._27 = function() {
	if (!this._chkCmpTags([Jedox.kbd.Base.tags.NO_ESC]))
		Jedox.dlg.dlgRegistry.getActive().components.Cancel.handler();

	this._handleEnd();
};

clsRef = null;