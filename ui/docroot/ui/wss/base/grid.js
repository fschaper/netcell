/*
 * @brief wss file
 *
 * Copyright (C) 2006-2009 Jedox AG
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: grid.js 4063 2010-10-19 09:48:09Z predragm $
 *
 */

Jedox.wss.grid = new function()
{
	// stores available scrolling directions
	this.ScrollDirection = {
		UP : 1,
		DOWN : 2,
		LEFT : 4,
		RIGHT : 8,
		DOWN_RIGHT : 10,
		UP_LEFT : 5,
		NONE : 11
	};

	// stores available modes in which the grid can be
	this.GridMode = {
		READY : 0, // inputElement is visible, user can navigate around
		EDIT  : 1, // like input, but formula is shown
		INPUT : 2, // textarea or formulafield is visible and has focus. User can enter data
		POINT : 3, // last mode was input or edit and user has just created a new formula range
		CNTRL : 4, // focus have control elements like dropdown lists in toolbar etc.
		DIALOG: 5  // dialog window has focus
	};

	// stores available iteration modes
	this.IterationMode = {
		NEXT  : 0, // select next horizontal cell (right)
		PREV  : 1, // select previous horizontal cell (left)
		NEXTX : 2, // select next vertical cell (down)
		PREVY : 3,  // select previous vertical cell (up)
		PREVX : 4,
		NEXTY : 5,
		FIRST : 6,
		LAST  : 7
	};

	// stores available view modes Jedox.wss.grid.viewMode
	this.viewMode = {
		DESIGNER: 'designer',
		USER: 'user',
		PREVIEW: 'preview'
	};

	this.headerType = {
		COLUMN: 0,
		ROW: 1,
		NONE: 2
	};

	this.scrollType = {
		HORIZ: 0,
		VERT: 1,
		ALL: 2
	};

	this.vertScrollDir = {
		UP: -1,
		DOWN: 1
	};

	this.horScrollDir = {
		LEFT: -1,
		RIGHT: 1
	};

	this.gridOperation = {
		COPY: 0,
		CUT: 1
	};

	this.permission = {
		PERM_NONE: 0,
		PERM_READ: 1,
		PERM_WRITE: 3,
		PERM_DELETE: 7,
		PERM_SPLASH: 15
	};

	var _cbHandles = {};

	this.defMaxCoords = [ 256, 65536 ];
	this.defCachePageSize = [ 256, 1024 ];
	this.defLoadTableCoef = 1.2;

	this.defDefColRowDims = [ 64, 20 ];
	this.defCellSizeIncr = [ 5, 5 ];

	this.defScrollbarBGOffset = [ 2 * 17, 2 * 17 ];
	this.defSliderBorderElemsSize = [ 8, 8 ];
	this.defSliderCenterElemSize = [ 8, 8 ];

	this.defDefScrollSpeed = 80;
	this.defScrollSteps = [[25, 250], [50, 150], [75, 50], [100, 25]];
	this.maxGridOffset = [41, 44];

	this.cbReg = function(handle, cb)
	{
		if (_cbHandles[handle] != undefined || typeof cb[0] != 'object' || typeof cb[1] != 'function')
			return false;

		_cbHandles[handle] = cb;

		return true;
	}

	this.cbGet = function(handle)
	{
		return _cbHandles[handle];
	}
}
