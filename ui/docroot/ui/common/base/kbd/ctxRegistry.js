/*
 * \brief Context registry.
 *
 * \file ctxRegistry.js
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
 * SVN: $Id: ctxRegistry.js 3471 2010-07-06 13:33:35Z drazenk $
 *
 */

// Context registry.

Jedox.kbd.ctxRegistry = new function() {
	var that = this,
		_active = _default = 'General',
		_ctxs = {},

		_chkCtx = function(id) {
			if (!Jedox.kbd[id])
				throw 'invalidContext';
		};

	_ctxs[_active] = new Jedox.kbd[_active]();

	this.add = function(id) {
		_chkCtx(id);

		var act = _active;

		if (_ctxs[id])
			_ctxs[id].useCnt++;
		else {
			_ctxs[id] = new Jedox.kbd[id]();
			_ctxs[id].useCnt = 1;
		}

		_active = id;

		return act;
	};

	this.remove = function(id, act) {
		if (!_ctxs[id])
			return;

		if (_ctxs[id].useCnt > 1) {
			_ctxs[id].useCnt--;
			return;
		} else
			delete _ctxs[id];

		if (act)
			_active = act;
	};

	this.replace = function(id) {
		var prevCtx = this.add(id);
		this.remove(prevCtx);
	};

	this.setActive = function(id) {
		_chkCtx(id);

		if (!_ctxs[id]) {
			_ctxs[id] = new Jedox.kbd[id]();
			_ctxs[id].useCnt = 1;
		}

		_active = id;
	};

	this.getActive = function() {
		return _ctxs[_active];
	};

	this.dump = function() {
		return {contexts: _ctxs, active: _active};
	};
};