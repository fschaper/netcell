/*
 * \brief class handling auto scroll
 *
 * \file AutoScroll.js
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
 * SVN: $Id: AutoScroll.js 4808 2011-04-06 09:44:29Z drazenk $
 *
 */

Jedox.wss.grid.AutoScroll = function (sheet) {
	var that = this,
		_sheet = sheet,
		_book = _sheet._book,
		_panes = _sheet._panes,
		_pane = _sheet._aPane,
		_env = _sheet._env.shared,

		_hook = null,
		_isScrolling = {h: false, v: false},
		_defScrollSteps = [[25, 250], [50, 150], [75, 50], [100, 25]];

	this.scrollElem = false;

	function _calcScrollSpeed(scrollArea, position) {
		var scrollPerc = position * 100 / scrollArea;

		for (var i = 0; i < _defScrollSteps.length; ++i) {
			if (scrollPerc <= _defScrollSteps[i][0])
				return _defScrollSteps[i][1];
		}
	}

	function _stopScroll(ev) {
		clearTimeout(that.scrollElem);
		var scrollType = Jedox.wss.grid.scrollType;

		if (_pane._conf.hscroll)
			_pane._hScroll.stop();

		if (_pane._conf.vscroll)
			_pane._vScroll.stop();

		Jedox.wss.app.mouseUpObserver.unsubscribe(_stopScroll);

		if (_hook != null) {
			_book.scrollObserver.unsubscribe(_hook);
			_hook = null;
		}

		_isScrolling.h = _isScrolling.v = false;
	}

	this.checkAndScroll = function(ev, hook, direction, innerOffset, scope) {
		_hook = hook;
		var gridScreenCoords = Jedox.wss.app.environment.gridScreenCoords,
			scrollType = Jedox.wss.grid.scrollType,
			horScrollDir = Jedox.wss.grid.horScrollDir,
			vertScrollDir = Jedox.wss.grid.vertScrollDir,
			scrollAction = 0; // -1 = scroll backwards; 0 = no scroll; 1 = scroll forwards

		var cbStartScrollGrid = function() {
			if (direction == scrollType.ALL || direction == scrollType.VERT) {
				if (ev.clientY >= gridScreenCoords[0][1] && ev.clientY <= gridScreenCoords[1][1]) {
					if (_pane._conf.vscroll)
						_pane._vScroll.stop();

					_isScrolling.v = false;
				} else {
					Jedox.wss.app.mouseUpObserver.subscribe(_stopScroll, scope);

					if (hook != null)
						_book.scrollObserver.subscribe(hook, scope);

					if (_pane._conf.vscroll) {
						if (ev.clientY > gridScreenCoords[1][1])
							// Scroll down.
							_pane._vScroll.start(undefined, vertScrollDir.DOWN, _calcScrollSpeed(gridScreenCoords[2][1] - gridScreenCoords[1][1], ev.clientY - gridScreenCoords[1][1]));
						else
							// Scroll up.
							_pane._vScroll.start(undefined, vertScrollDir.UP, _calcScrollSpeed(gridScreenCoords[0][1], gridScreenCoords[0][1] - ev.clientY));

						_isScrolling.v = true;
					}
				}
			}
		};

		if (direction == scrollType.ALL || direction == scrollType.HORIZ) {
			if (innerOffset == undefined) {
				if (ev.clientX < gridScreenCoords[0][0])
					scrollAction--;
				else if (ev.clientX > gridScreenCoords[1][0])
					scrollAction++;
			} else {
				if (ev.clientX >= gridScreenCoords[0][0] && ev.clientX <= gridScreenCoords[0][0] + innerOffset)
					scrollAction--;
				else if (ev.clientX >= gridScreenCoords[1][0] - innerOffset && ev.clientX <= gridScreenCoords[1][0])
					scrollAction++;
			}

			if (scrollAction == 0) {
				if (_pane._conf.hscroll)
					_pane._hScroll.stop();

				_isScrolling.h = false;
			} else {
				Jedox.wss.app.mouseUpObserver.subscribe(_stopScroll, scope);

				if (hook != null)
					_book.scrollObserver.subscribe(hook, scope);

				if (_pane._conf.hscroll) {
					if (scrollAction > 0)
						// Scroll right.
						_pane._hScroll.start([this, cbStartScrollGrid], horScrollDir.RIGHT,
							(innerOffset == undefined) ? _calcScrollSpeed(gridScreenCoords[2][0] - gridScreenCoords[1][0], ev.clientX - gridScreenCoords[1][0]) : _defScrollSteps[1][1]
						);
					else
						// Scroll left.
						_pane._hScroll.start([this, cbStartScrollGrid], horScrollDir.LEFT, _calcScrollSpeed(gridScreenCoords[0][0], gridScreenCoords[0][0] - ev.clientX));

					_isScrolling.h = true;

					return;
				}
			}
		}

		cbStartScrollGrid();
	};

	this.syncActivePane = function() {
		_pane = _sheet._aPane;
	};

	this.getActivePane = function() {
		return _pane;
	};

	this.setActivePane = function(pane) {
		_pane = pane;
	};

	this.isScrolling = function() {
		return _isScrolling.h || _isScrolling.v;
	};
}