/*
 * \brief class representing application shared environment
 *
 * \file SharedEnvironment.js
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
 * SVN: $Id: SharedEnvironment.js 4976 2011-05-20 14:12:05Z drazenk $
 *
 */

Jedox.wss.app.SharedEnvironment = function () {

	// moved from globals.js / NS Jedox.wss.app

	/**
	 * Selection object which is responsible for selecting cells.
	 */
	this.defaultSelection = null; // prev: defaultRange

	/**
	 * Selection object which is responsible for displaying and changing formula cells.
	 */
	this.formulaSelection = null; // prev: formulaRange

	/**
	 * Selection object which is responsible for marking cells for some action like copy/cut/paste.
	 */
	this.copySelection = null; // prev: markRange

	/**
	 * String indicating which elements are selected:
	 * values: "row", "column" or "all"
	 */
	this.headerMarkMode = '';

	/**
	 * Number which holds the mode of cell selction
	 * 0 = mark all cells, 1 = mark column(s), 2 = mark row(s)
	 */
	this.headerStyle = 0;

	/**
	 * String indicating elements were selected the last time
	 * values:
	 * 0 : none
	 * 1 : rows and columns (all cells)
	 * 2 : rows
	 * 3 : column
	 */
	this.lastMarkMode = 0;

	/**
	 *  Reference to <textarea> element which shows formula in edit mode or value of active cell.
	 */
	this.inputField = null;

	/**
	 * Reference to selected cell element (<div>).
	 */
	this.selectedCell = '';

	/**
	 * Coordinates array (grid indices) of selected cell.
	 */
	this.selectedCellCoords = [];

	/**
	 * Reference to <div> element which was the last active cell in previous default range.
	 */
	this.lastCell = null;

	/**
	 * Coordinates array of the last active cell in previous default range.
	 */
	this.lastCellCoords = [];

	/**
	 * String which contains value of selected cell.
	 */
	this.selectedCellValue = '';

	/**
	 * String which contains formula of selected cell.
	 */
	this.selectedCellFormula = '';

	/**
	 * Relative number of the selected row.
	 */
	this.selectedRowNumericName = '';

	/**
	 * Relative number of the selected column.
	 */
	this.selectedColumnName = '';

	/**
	 * Absolute number of the selected row.
 	 */
	this.selectedAbsRowNameNumeric = '';

	/**
	 * Absolute number of the selected column.
	 */
	this.selectedAbsColumnName = '';

	/**
	 * Relative letter(s) of the selected row.
	 */
	this.selectedRowName = ''; //TODO: Used only once. Try to remove completely.

	/**
	 * This number stores the view mode: DESIGNER, USER, PREVIEW, etc.
	 */
	this.viewMode = Jedox.wss.grid.viewMode.USER;

	/**
	 * This number stores current input mode: READY, EDIT, INPUT or POINT.
	 */
	this.inputMode = Jedox.wss.grid.GridMode.READY;

	/**
	 * Array with absolute numeric start coordinates of default range.
	 */
	this.lastRangeStartCoord = [];

	/**
	 * Array with absolute numeric end coordinates of default range.
	 */
	this.lastRangeEndCoord = [];

	/**
	 * Flag indicating if textarea is visible and has focus.
	 * If true, input will be filled in textarea.
	 */
	this.editingDirectly = false;

	/**
	 * This string keeps the value before the focus is set on the textarea.
	 */
	this.oldValue = '';

	/**
	 * Last value entered in textarea (only filled if input mode is enter or edit).
	 */
	this.lastInputValue = '';

	/**
	 * Flag indicating if active formula range has just been created
	 * and is still in resize mode.
	 */
	this.activeNewArea = false;

	/**
	 * String filled with special mouse position
	 * ("colResize", "rowResize", "colMark", "rowMark", "rngBorder", "magicDot") or blank.
	 */
	this.mousePosition = '';

	/**
	 * Flag indicating type of header that has just been resized.
	 */
	this.headerResizeType = Jedox.wss.grid.headerType.NONE;

	/**
	 * Coordinate of column or row that has been reised.
	 */
	this.headerResizeCoord = 0;

	/**
	 * Array containing params used by col/row resize presentation.
	 */
	this.headerResize = [];

	/**
	 * Array containing top/left and bottom/right screen coordinates of the grid.
	 */
	this.gridScreenCoords = [[], []];

	/**
	 * Array containing top/left coordinates of the grid when grid window is maximized.
	 */
	this.gridScreenCoordsMax = null;

	/**
	 * Array containing temporary offsets for mouse grid position.
	 */
	this.gridPosOffset = [0, 0];

	/**
	 * Reference to auto-scroll object.
	 */
	this.autoScroll = null;

	/**
	 * Current undo/redo state
	 */
	this.undoState = [ 0, 0 ];

	/**
	 * Undo value in INPUT/EDIT mode.
	 */
	this.undoValue = null;

	/**
	 * Redo value in INPUT/EDIT mode.
	 */
	this.redoValue = null;

	/**
	 * The register of created dynaranges.
	 */
	this.dynaranges = {};

	/**
	 * Current dynarange Mode.
	 */
	this.HBMode = Jedox.wss.hb.HBMode.DESIGNER;

}
