/*
 * \brief Keyboard Base class.
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
 * SVN: $Id: Base.js 3484 2010-07-08 14:06:59Z andrejv $
 *
 */

Jedox.kbd.Base = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function () {
		// private fields
		var that = this;

		// private methods

		// public fields

		this.event = null;
		this.keyCode = null;
		this.keyModifier = 'ctrlKey'; // change this for keyboard shortcuts in studio

		// privileged methods

		// constructor code
	};
}
)();

//public fields
Jedox.kbd.Base.tags = {
	NO_ANY: 'no-kbd-any',
	NO_ENTER: 'no-kbd-enter',
	NO_ESC: 'no-kbd-esc'
};

//public methods
Jedox.kbd.Base.prototype = {
	handle: function(event) {
		this.event = document.all ? window.event : event;
		this.keyCode = document.all ? this.event.keyCode : this.event.which;

		var kHandler = '_'.concat(this.keyCode);

		if (this[kHandler])
			this[kHandler]();
		else
			this._handleDefault();
	},

	_handleDefault: function() {
		this._handleEnd();
	},

	_handleEnd: function() {

	},

	/* author: andrejv
	 * kill default browser handling of CTRL+key events
	 */
	_preventBubble: function(){

		var e = document.all ? window.event : this.event;

		try {
			e.keyCode = 0;
		    e.shiftKey = false;
		    e.ctrlKey = false;
		    e.altKey = false;
		}
		catch (e) {
		};

		e.cancelBubble = true;
		e.cancelEvent = true;
		e.returnValue = false;

		if (e.stopPropagation) {
			e.stopPropagation();
			e.preventDefault();
		};
		//return false;
	},
	/* END of default browser handling kill */

	_chkTabIdx: function(cmp) {
		return !cmp.hidden && !cmp.disabled && cmp.tabIndex != undefined;
	},

	_tabFocus: function(elems) {
		if (elems.length) {
			var backward = this.event.shiftKey,
				evTarget = document.all ? this.event.srcElement : this.event.target,
				currTabIdx = evTarget.tabIndex,
				currElIdx = -1;

			elems.sort(function (a, b) {
				return backward ? b.tabIndex - a.tabIndex : a.tabIndex - b.tabIndex;
			});

			for (var i in elems)
				if (elems[i].tabIndex == currTabIdx) {
					currElIdx = i;
					break;
				}

			if (currElIdx < 0 || ++currElIdx > elems.length - 1)
				currElIdx = 0;

			elems[currElIdx].focus();
		}

		if (document.all){
			this.event.returnValue = false;
			this.event.cancelBubble = true;
		} else {
			this.event.preventDefault();
			this.event.stopPropagation();
		}
	}

}