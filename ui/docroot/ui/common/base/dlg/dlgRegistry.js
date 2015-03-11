/*
 * \brief Dialog registry.
 *
 * \file dlgRegistry.js
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
 * SVN: $Id: dlgRegistry.js 3458 2010-07-02 13:51:23Z drazenk $
 *
 */

// Dialog registry.

Jedox.dlg.dlgRegistry = new function() {
	var that = this,
		_dlgs = [],
		_active = -1,

		_getIdx = function(id) {
			for (var idx in _dlgs)
				if (_dlgs[idx].id == id)
					return idx;

			return -1;
		};

	this.add = function(dlg, setAct) {
		setAct = setAct === false ? false : true;
		var idx = _getIdx(dlg.id);

		if (idx < 0)
			idx = _dlgs.push(dlg) - 1;

		if (setAct)
			_active = idx;
	};

	this.remove = function(id) {
		var idx = _getIdx(id);

		if (idx >= 0) {
			var actId = _dlgs[_active].id;

			_dlgs.splice(idx, 1);
			_active = idx == _active ? _dlgs.length - 1 : _getIdx(actId);
		}
	};

	this.setActive = function(id) {
		var idx = _getIdx(id);

		if (idx >= 0) {
			_active = idx;
			return true;
		} else
			return false;
	};

	this.getActive = function() {
		return _dlgs.length ? _dlgs[_active] : false;
	};

	this.dump = function() {
		return {dialogs: _dlgs, active: _active};
	};
};