/*
 * \brief keyboard event handling routines
 *
 * \file keyboard.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: keyboard.js 5152 2011-07-28 10:02:33Z predragm $
 *
 */

if (!Jedox.wss.app.currentDialogControl)

Jedox.wss.keyboard.checkGlobalInput = function(ev) {
	if (!Jedox.wss.app.loaded)
		return;

	Jedox.kbd.ctxRegistry.getActive().handle(ev);
}

Jedox.wss.keyboard.calcCursorRng = function(ul, lr, act, key, shiftPressed) {
	var defMaxCoords = Jedox.wss.grid.defMaxCoords, focusCell;

	switch (key) {
		case 37: // left
			if (shiftPressed) {
				if (ul.equalsX(lr)) {
					ul.setX((ul.getX() > 1) ? ul.getX() - 1 : ul.getX());
					focusCell = ul;
				} else {
					if (ul.equalsX(act)) {
						lr.setX((lr.getX() > 1) ? lr.getX() - 1 : lr.getX());
						focusCell = lr;
					} else {
						ul.setX((ul.getX() > 1) ? ul.getX() - 1 : ul.getX());
						focusCell = ul;
					}
				}
			} else {
				var newX = (act.getX() > 1) ? act.getX() - 1 : act.getX();
				var newY = act.getY();

				ul.setX(newX); ul.setY(newY);
				lr.setX(newX); lr.setY(newY);
				focusCell = ul;
			}
			break;

		case 39: // right
			if (shiftPressed) {
				if (ul.equalsX(lr)) {
					lr.setX((lr.getX() < defMaxCoords[0]) ? lr.getX() + 1 : lr.getX());
					focusCell = ul;
				} else {
					if (lr.equalsX(act)) {
						ul.setX((ul.getX() < defMaxCoords[0]) ? ul.getX() + 1 : ul.getX());
						focusCell = ul;
					} else {
						lr.setX((lr.getX() < defMaxCoords[0]) ? lr.getX() + 1 : lr.getX());
						focusCell = lr;
					}
				}
			} else {
				var newX = (act.getX() < defMaxCoords[0]) ? act.getX() + 1 : act.getX();
				var newY = act.getY();

				ul.setX(newX); ul.setY(newY);
				lr.setX(newX); lr.setY(newY);
				focusCell = ul;
			}
			break;

		case 33: // page up
		case 38: // up
			if (shiftPressed) {
				if (ul.equalsY(lr)) {
					ul.setY((ul.getY() > 1) ? ul.getY() - 1 : ul.getY());
					focusCell = ul;
				} else {
					if (ul.equalsY(act)) {
						lr.setY((lr.getY() > 1) ? lr.getY() - 1 : lr.getY());
						focusCell = lr;
					} else {
						ul.setY((ul.getY() > 1) ? ul.getY() - 1 : ul.getY());
						focusCell = ul;
					}
				}
			} else {
				var newX = act.getX();
				var newY = (act.getY() > 1) ? act.getY() - 1 : act.getY();

				ul.setX(newX); ul.setY(newY);
				lr.setX(newX); lr.setY(newY);
				focusCell = ul;
			}
			break;

		case 34: // page down
		case 40: // down
			if (shiftPressed) {
				if (ul.equalsY(lr)) {
					lr.setY((lr.getY() < defMaxCoords[1]) ? lr.getY() + 1 : lr.getY());
					focusCell = lr;
				} else {
					if (lr.equalsY(act)) {
						ul.setY((ul.getY() < defMaxCoords[1]) ? ul.getY() + 1 : ul.getY());
						focusCell = ul;
					} else {
						lr.setY((lr.getY() < defMaxCoords[1]) ? lr.getY() + 1 : lr.getY());
						focusCell = lr;
					}
				}
			} else {
				var newX = act.getX();
				var newY = (act.getY() < defMaxCoords[1]) ? act.getY() + 1 : act.getY();

				ul.setX(newX); ul.setY(newY);
				lr.setX(newX); lr.setY(newY);
				focusCell = ul;
			}
			break;
	}

	return [ul, lr, focusCell];
}

Jedox.wss.keyboard.cursorKeys = { 16: true, 33: true, 34: true, 37: true, 38: true, 39: true, 40: true };

Jedox.wss.keyboard.setFieldContent = function (ev)
{
	var env = Jedox.wss.app.environment,
			currFormula = Jedox.wss.app.currFormula,
			changed;

	if (Jedox.wss.app.fromFormulaField)
		env.inputField.value = currFormula.getValue();
	else
		currFormula.setValue(env.inputField.value);

	if (changed = env.lastInputValue != currFormula.getValue())
	{
		Jedox.wss.keyboard.setFieldSize();
		env.lastInputValue = currFormula.getValue();
	}

	if (currFormula.getValue().substr(0, 1) != '=')
		return;

	var keyPressed = document.all ? (window.event? window.event.keyCode : -1) : (typeof ev == 'object' ? ev.which : -1);

	if (!(keyPressed in Jedox.wss.keyboard.cursorKeys))
		env.formulaSelection.activeToken = null;

	if (changed)
		Jedox.wss.range.drawDependingCells(currFormula.getValue());
}

Jedox.wss.keyboard.setFieldSize = function() {
	var env = Jedox.wss.app.environment;
	var selCellWidth = env.selectedCell.offsetWidth, selCellHeight = env.selectedCell.offsetHeight;
	var activePane = Jedox.wss.app.activePane;

	var inputField = env.inputField;
	var tm = Ext.util.TextMetrics.createInstance(inputField.id);
	var rightMargin = tm.getWidth('WWW');
	var contWidth = tm.getWidth(inputField.value.replace(/ /g, 't'));
	var contLineHeight = tm.getHeight('W');
	var fieldWidth = contWidth;
	var fieldHeight = contLineHeight;

	var lastVisCellCoords = activePane.getCoordsLastVCell();
	var lastVisCell = activePane.getCellByCoords(lastVisCellCoords[0], lastVisCellCoords[1]);
	var maxDims = {
		width: lastVisCell.offsetLeft + lastVisCell.offsetWidth - inputField.offsetLeft - 2,
		height: lastVisCell.parentNode.offsetTop + lastVisCell.offsetHeight - inputField.offsetTop
	}

	if (contWidth < selCellWidth - 8)
		fieldWidth = selCellWidth - ((env.viewMode == Jedox.wss.grid.viewMode.USER) ? 3 : 2);
	else if (contWidth < maxDims.width)
		fieldWidth += rightMargin;
	else {
		fieldWidth = maxDims.width;
		contWidth *= 1.3;
		fieldHeight = Math.round(contWidth / maxDims.width) * contLineHeight + ((contWidth % maxDims.width > 0) ? contLineHeight : 0);

		if (fieldHeight > maxDims.height)
			fieldHeight = maxDims.height;
	}

	inputField.style.width = fieldWidth + 'px';

	if (fieldHeight > selCellHeight)
		inputField.style.height = fieldHeight + 'px';
}

Jedox.wss.keyboard.skipInput = false;
Jedox.wss.keyboard.skipInpFldBlur = false;

Jedox.wss.keyboard.sendInput = function (myInputBox, isArrFrml, chkSkip)
{
	if (!chkSkip)
		this.skipInput = true;
	else if (this.skipInput) {
		this.skipInput = false;
		return;
	}

	var env = Jedox.wss.app.environment,
		activePane = Jedox.wss.app.activePane,
		cellValue = myInputBox.value,
		selCellCoords = env.selectedCellCoords;

	if (env.viewMode == Jedox.wss.grid.viewMode.USER && !cellValue.search(/^=/))
		return true;
	else if (isArrFrml === undefined || !isArrFrml) {
		if (cellValue == env.oldValue)
			return true;

		var hdata = Jedox.wss.hl.get(selCellCoords);

		if (hdata) {
			if (hdata.dyn) {
				if (cellValue.search(/^=HYPERLINK\(/) != 0)
					activePane.clrRange([selCellCoords[0], selCellCoords[1], selCellCoords[0], selCellCoords[1]], Jedox.wss.range.ContentType.ATTRS);
			} else {
				Jedox.wss.hl.updateText([selCellCoords[0], selCellCoords[1], selCellCoords[0], selCellCoords[1]], cellValue);
				cellValue = Jedox.wss.general.filterHLTags(selCellCoords[0], selCellCoords[1], cellValue, true);
			}
		}

		env.selectedCellValue = cellValue;
		activePane.setCellValue(selCellCoords[0], selCellCoords[1], cellValue);
	} else {
		activePane.setArrayFormula(env.defaultSelection.getActiveRange().getCoords(), cellValue);

		var selCellValue = activePane.getCellUVal(selCellCoords[0], selCellCoords[1]);
		env.selectedCellValue = (selCellValue == undefined) ? '' : selCellValue;

		var selCellFormula = activePane.getCellFormula(selCellCoords[0], selCellCoords[1]);
		env.selectedCellFormula = (selCellFormula == undefined) ? '' : selCellFormula;
		Jedox.wss.app.currFormula.setValue(env.selectedCellFormula);
	}

	Jedox.wss.keyboard.cancelInput();

	return true;
}

Jedox.wss.keyboard.cancelInput = function (delMarkRng){// TODO: Check/Rewrite
	var env = Jedox.wss.app.environment;
	var inputField = env.inputField;
	var isUserMode = (env.viewMode == Jedox.wss.grid.viewMode.USER);

	env.editingDirectly = false;
	if (!isUserMode) {
		if (inputField._paneId != undefined && Jedox.wss.app.activePane._id != inputField._paneId)
			Jedox.wss.app.activeSheet._panes[inputField._paneId].select();

		var selCellCoords = env.selectedCellCoords;
		Jedox.wss.app.currFormula.setValue(( (env.selectedCellFormula != '') && (env.selectedCellFormula != 'null') ) ? env.selectedCellFormula : Jedox.wss.general.filterHLTags(selCellCoords[0], selCellCoords[1], env.selectedCellValue, false));
	}

	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.READY);

	inputField.style.zIndex = '37';
	inputField.style.display = 'none';
	inputField.blur();

	env.lastInputValue = '';
	env.activeNewArea = false;

	if (!isUserMode) {
		Jedox.wss.app.activeSheet._defaultSelection.getCursorField().show();
		env.formulaSelection.removeAll();

		if (delMarkRng == undefined || delMarkRng) {
			env.copySelection.removeAll();

			if (Jedox.wss.app.clipboard != null && Jedox.wss.app.clipboard.id != null) {
				Jedox.wss.app.clipboard = null;
				Jedox.wss.action.togglePaste(false);
			}
		}
	} else
		Jedox.wss.app.clipboard = null;
}

Jedox.wss.keyboard.sendInputAndReset = function() {
	var env = Jedox.wss.app.environment,
		val = env.inputField.value;

	if (this.skipInpFldBlur || (val.length > 0 && val.charAt(0) == '=' && env.viewMode != Jedox.wss.grid.viewMode.USER)) {
		this.skipInpFldBlur = false;
		return;
	}

	this.sendInput(env.inputField, undefined, true);
	this.cancelInput();

	try {
		Jedox.wss.app.currFormula.getEl().blur();
	} catch (e) {}
}

Jedox.wss.keyboard.shiftDirection = function (direction) {

	switch(direction){

		case Jedox.wss.grid.ScrollDirection.DOWN:
			direction = Jedox.wss.grid.ScrollDirection.UP;
		break;

		case Jedox.wss.grid.ScrollDirection.UP:
			direction = Jedox.wss.grid.ScrollDirection.DOWN;
		break;

		case Jedox.wss.grid.ScrollDirection.LEFT:
			direction = Jedox.wss.grid.ScrollDirection.RIGHT;
		break;

		case Jedox.wss.grid.ScrollDirection.RIGHT:
			direction = Jedox.wss.grid.ScrollDirection.LEFT;
		break;

	}

	return direction;
}

Jedox.wss.keyboard.preventKeyEvent = function (myKeyEvent){// TODO: Check/Rewrite
	if(Jedox.wss.app.environment.inputMode != Jedox.wss.grid.GridMode.EDIT){
	    if(document.all){
			window.event.returnValue = false;
			window.event.cancelBubble = true;
		}else{
			myKeyEvent.preventDefault();
		}
	}

	return false;
}

Jedox.wss.keyboard.handleCursorKey = function (keyEvent){// TODO: Check/Rewrite

	var keyPressed = ((document.all) ? keyEvent.keyCode : keyEvent.which);
	var amount = 1;

	switch(keyPressed){

		case 37: // left
			if(Jedox.wss.app.environment.selectedAbsRowNameNumeric > 1) {
				Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.LEFT, keyEvent.shiftKey, amount, keyPressed);
			}
		break;

		case 33: // page up

		case 38: // up
			if(Jedox.wss.app.environment.selectedAbsColumnName > 1) {
				Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.UP, keyEvent.shiftKey, amount, keyPressed);
			}
		break;

		case 39: // right
			if(Jedox.wss.app.environment.selectedAbsRowNameNumeric < Jedox.wss.grid.defMaxCoords[0]){
				Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.RIGHT, keyEvent.shiftKey, amount, keyPressed);
			}
		break;

		case 34: // page down

		case 40: // down
			if(Jedox.wss.app.environment.selectedAbsColumnName < Jedox.wss.grid.defMaxCoords[1]){
				Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.DOWN, keyEvent.shiftKey, amount, keyPressed);
			}
		break;
	}
}

Jedox.wss.keyboard.isCursorkey = function (keyCode){// TODO: Check/Rewrite
	return ( (keyCode >= 37) && (keyCode <= 40) );
}

Jedox.wss.keyboard.moveCursor = function (direction, shiftKey, amount, keyCode){// TODO: Check/Rewrite

	if (Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER)
		return;

	var range = Jedox.wss.app.environment.activeNewArea ? Jedox.wss.app.environment.formulaSelection : Jedox.wss.app.environment.defaultSelection,
		activeBook = Jedox.wss.app.activeBook,
		activePane = activeBook._aSheet._aPane,
		activeCell = range.getActiveRange().getActiveCell(),
		lastActiveCell = range.getActiveRange().getLastActiveCell(),
		coords = activeCell.clone(),
		lastCell = activeCell.clone(),
		isCursorKey = Jedox.wss.keyboard.isCursorkey(keyCode),
		i=0;

	// Hide selection and show cell marker.
	if(!Jedox.wss.app.environment.defaultSelection.isSingleCell() && !(keyCode == 13 || keyCode == 9) && !shiftKey)
		range.set(activeCell, activeCell);

	// Reverse direction.
	if (shiftKey) {
		if (isCursorKey)
			coords = lastActiveCell.clone();
		else
			direction = Jedox.wss.keyboard.shiftDirection(direction);
	}

	var rangeSingleCell = range.isSingleCell(),
		chkHiddenColRow = Jedox.wss.general.chkHiddenColRow;

	switch(direction){

		case Jedox.wss.grid.ScrollDirection.DOWN:
			if (rangeSingleCell || (shiftKey && isCursorKey)) {
				var newYCoord = chkHiddenColRow(true, coords.getY(), amount, true), newXCoord = chkHiddenColRow(false, coords.getX(), 0, true),
					mergeInfoSrc = activePane.getMergeInfo(coords.getX(), coords.getY()),
					mergeInfo = activePane.getMergeInfo(newXCoord, newYCoord);

				if (!mergeInfoSrc)
					range.setRefActiveCell(coords);

				if (mergeInfo && !mergeInfo[0]) {
					var mergeInfoMa = mergeInfoSrc && mergeInfoSrc[0] ? mergeInfoSrc : activePane.getMergeInfo(mergeInfo[1], mergeInfo[2]);

					if (mergeInfoMa && mergeInfoMa[0]) {
						if (mergeInfoSrc && mergeInfoSrc[0]) {
							if (rangeSingleCell)
								newYCoord = mergeInfo[2] + mergeInfoMa[2];

							if (!shiftKey) {
								var refCell = range.getRefActiveCell();

								if (refCell && refCell.getX() >= mergeInfo[1] && refCell.getX() <= (mergeInfo[1] + mergeInfoMa[1] - 1))
									newXCoord = refCell.getX();

								var mergeInfoShiftCell = activePane.getMergeInfo(newXCoord, newYCoord);
								if (mergeInfoShiftCell && !mergeInfoShiftCell[0]) {
									newXCoord = mergeInfoShiftCell[1];
									newYCoord = mergeInfoShiftCell[2];
								}
							}
						} else {
							newXCoord = mergeInfo[1];
							newYCoord = mergeInfo[2];
						}
					}
				}

				if (newXCoord <= Jedox.wss.grid.defMaxCoords[0] && newYCoord <= Jedox.wss.grid.defMaxCoords[1]) {
					coords.setX(newXCoord);
					coords.setY(newYCoord);
				}
			}else{
				for (i=0; i<amount; i++){
					range.nextY();
				}
			}
		break;

		case Jedox.wss.grid.ScrollDirection.UP:
			if (rangeSingleCell || (shiftKey && isCursorKey)) {
				var newYCoord = chkHiddenColRow(true, coords.getY(), amount, false), newXCoord = chkHiddenColRow(false, coords.getX(), 0, false),
					mergeInfoSrc = activePane.getMergeInfo(coords.getX(), coords.getY()),
					mergeInfo = activePane.getMergeInfo(newXCoord, newYCoord);

				if (!mergeInfoSrc)
					range.setRefActiveCell(coords);

				if (!shiftKey || (shiftKey && !isCursorKey))
					if (!mergeInfo) {
						if (mergeInfoSrc && mergeInfoSrc[0]) {
							var refCell = range.getRefActiveCell();

							if (refCell && refCell.getX() >= coords.getX() && refCell.getX() <= (coords.getX() + mergeInfoSrc[1] - 1))
								newXCoord = refCell.getX();

							var mergeInfoShiftCell = activePane.getMergeInfo(newXCoord, newYCoord);
							if (mergeInfoShiftCell && !mergeInfoShiftCell[0]) {
								newXCoord = mergeInfoShiftCell[1];
								newYCoord = mergeInfoShiftCell[2];
							}
						}
					} else if (!mergeInfo[0]) {
						newXCoord = mergeInfo[1];
						newYCoord = mergeInfo[2];
					}

				if (newXCoord >= 1 && newYCoord >= 1) {
					coords.setX(newXCoord);
					coords.setY(newYCoord);
				}
			} else {
				for (i=0; i<amount; i++){
					range.prevY();
				}
			}
		break;

		case Jedox.wss.grid.ScrollDirection.RIGHT:
			if (rangeSingleCell || (shiftKey && isCursorKey)) {
				var newYCoord = chkHiddenColRow(true, coords.getY(), 0, true), newXCoord = chkHiddenColRow(false, coords.getX(), amount, true),
					mergeInfoSrc = activePane.getMergeInfo(coords.getX(), coords.getY()),
					mergeInfo = activePane.getMergeInfo(newXCoord, newYCoord);

				if (!mergeInfoSrc)
					range.setRefActiveCell(coords);

				if (mergeInfo && !mergeInfo[0]) {
					var mergeInfoMa = mergeInfoSrc && mergeInfoSrc[0] ? mergeInfoSrc : activePane.getMergeInfo(mergeInfo[1], mergeInfo[2]);

					if (mergeInfoMa && mergeInfoMa[0]) {
						if (mergeInfoSrc && mergeInfoSrc[0]) {
							if (rangeSingleCell)
								newXCoord = mergeInfo[1] + mergeInfoMa[1];

							if (!shiftKey) {
								var refCell = range.getRefActiveCell();

								if (refCell && refCell.getY() >= mergeInfo[2] && refCell.getY() <= (mergeInfo[2] + mergeInfoMa[2] - 1))
									newYCoord =  refCell.getY();

								var mergeInfoShiftCell = activePane.getMergeInfo(newXCoord, newYCoord);
								if (mergeInfoShiftCell && !mergeInfoShiftCell[0]) {
									newXCoord = mergeInfoShiftCell[1];
									newYCoord = mergeInfoShiftCell[2];
								}
							}
						} else {
							newXCoord = mergeInfo[1];

							if (!shiftKey)
								newYCoord = mergeInfo[2];
						}
					}
				}

				if (newXCoord <= Jedox.wss.grid.defMaxCoords[0] && newYCoord <= Jedox.wss.grid.defMaxCoords[1]) {
					coords.setX(newXCoord);
					coords.setY(newYCoord);
				}
			} else {
				for (i=0; i<amount; i++) {
					range.next();
				}
			}
		break;

		case Jedox.wss.grid.ScrollDirection.LEFT:
			if (rangeSingleCell || (shiftKey && isCursorKey)) {
				var newYCoord = chkHiddenColRow(true, coords.getY(), 0, false), newXCoord = chkHiddenColRow(false, coords.getX(), amount, false),
					mergeInfoSrc = activePane.getMergeInfo(coords.getX(), coords.getY()),
					mergeInfo = activePane.getMergeInfo(newXCoord, newYCoord);

				if (!mergeInfoSrc)
					range.setRefActiveCell(coords);

				if (!shiftKey || (shiftKey && !isCursorKey))
					if (!mergeInfo) {
						if (mergeInfoSrc && mergeInfoSrc[0]) {
							var refCell = range.getRefActiveCell();

							if (refCell != undefined && refCell.getY() >= coords.getY() && refCell.getY() <= (coords.getY() + mergeInfoSrc[2] - 1))
								newYCoord = refCell.getY();

							var mergeInfoShiftCell = activePane.getMergeInfo(newXCoord, newYCoord);
							if (mergeInfoShiftCell && !mergeInfoShiftCell[0]) {
								newXCoord = mergeInfoShiftCell[1];
								newYCoord = mergeInfoShiftCell[2];
							}
						}
					} else if (!mergeInfo[0]) {
						newXCoord = mergeInfo[1];
						newYCoord = mergeInfo[2];
					}

				if (newXCoord >= 1 && newYCoord >= 1) {
					coords.setX(newXCoord);
					coords.setY(newYCoord);
				}
			} else {
				for (i=0; i<amount; i++) {
					range.prev();
				}
			}
		break;

		default:
			console.error("Invalid cursor direction!");
			return ;

	}

	if ((rangeSingleCell || (shiftKey && isCursorKey)) && !activePane.isCellVisible(coords.getX(), coords.getY()) && activeBook._scrollPending)
		return;

	var cbScrollTo = function() {
		if (shiftKey && isCursorKey)
			range.expandToCell(coords, false);
		else if (rangeSingleCell)
			range.set(coords, coords);
		else
			range._setLegacyVars();

		range.draw();
	};

	if ((rangeSingleCell || (shiftKey && isCursorKey)) && !activePane.isCellVisible(coords.getX(), coords.getY())) {
		if (!activePane.isInsideRange(coords.getX(), coords.getY())) {
			var relPanes = activePane._sheet.getPanesByCoords(coords.getX(), coords.getY());

			if (relPanes.length == 1) {
				activePane = relPanes[0];
			}
		}

		activePane.scrollTo([this, cbScrollTo], coords.getX(), coords.getY(), true, false);
	} else
		cbScrollTo();
}

Jedox.wss.keyboard.preventEvent = function(ev) {
	var env = Jedox.wss.app.environment;

	if (!env)
		return;

	if(Jedox.wss.app.environment.inputMode != Jedox.wss.grid.GridMode.EDIT){
	    if(document.all){
			window.event.returnValue = false;
			window.event.cancelBubble = true;
		}else{
			ev.preventDefault();
			ev.stopPropagation();
		}
	}

	return false;
}

Jedox.wss.keyboard.focusInput = function(currX, currY, direction) {
	var actSheet = Jedox.wss.app.activeSheet,
		paneId = actSheet._aPane._id,
		iterMode = Jedox.wss.grid.IterationMode,
		realRngs = actSheet.getVirtScroll(),
		rngs = [];

	// realRngs - FP: [[1, 1, 5, 6], [6, 1, 28, 6], [1, 7, 5, 20], [6, 7, 28, 20]]
	// realRngs - SP: [[1, 1, 4, 6], [1, 1, 24, 6], [1, 1, 4, 14], [1, 1, 24, 14]]

	// rngs - FP | SP: [
	//					{ulX: 1, ulY: 1, lrX: 5, lrY: 6},
	//					{ulX: 6, ulY: 1, lrX: 28, lrY: 6},
	//					{ulX: 1, ulY: 7, lrX: 5, lrY: 20},
	//					{ulX: 6, ulY: 7, lrX: 28, lrY: 20}
	//				   ]

	if (realRngs[0] instanceof Array)
		for (var i = 0, rRLen = realRngs.length; i < rRLen; i++)
			rngs.push({ulX: realRngs[i][0], ulY: realRngs[i][1], lrX: realRngs[i][2], lrY: realRngs[i][3]});
	else
		rngs.push({ulX: realRngs[0], ulY: realRngs[1], lrX: realRngs[2], lrY: realRngs[3]});

	function iterForHor(x, y) {
		var i = sPane = paneId,
			isBeg = true,
			pX = x - rngs[i].ulX + 1, pY = y - rngs[i].ulY + 1,
			sPX = pX, sPY = pY;

		while (true) {
			for (; x <= rngs[i].lrX; ++x, ++pX) {
				if (!isBeg && i == sPane && pX == sPX && pY == sPY)
					return;

				if (!actSheet._panes[i].isCellLocked(x, y) && actSheet.isCellHidden(x, y)) {
					Jedox.wss.mouse.mimicCellMouseEvent(x, y, 'mousedown', actSheet._panes[i]);
					return;
				}
			}

			isBeg = false;

			if (rngs.length == 4) {
				if (i % 2) {
					// Panes 1 & 3.
					if (y == rngs[i].lrY)
						pX = 1, pY = 1, x = rngs[i == 3 ? (i = 0) : ++i].ulX, y = rngs[i].ulY;
					else
						pX = 1, pY++, x = rngs[--i].ulX, y = rngs[i].ulY + pY - 1;
				} else
					// Panes 0 & 2.
					pX = 1, x = rngs[++i].ulX, y = rngs[i].ulY + pY - 1;
			} else {
				if (y == rngs[i].lrY)
					pX = 1, pY = 1, x = rngs[rngs.length == 1 ? i : (i ? --i : ++i)].ulX, y = rngs[i].ulY;
				else
					pX = 1, pY++, x = rngs[i].ulX, y++;
			}
		}
	}

	function iterBackHor(x, y) {
		var i = sPane = paneId,
			isBeg = true,
			pX = x - rngs[i].ulX + 1, pY = y - rngs[i].ulY + 1,
			sPX = pX, sPY = pY;

		while (true) {
			for (; pX >= 1; --x, --pX) {
				if (!isBeg && i == sPane && pX == sPX && pY == sPY)
					return;

				if (!actSheet._panes[i].isCellLocked(x, y) && actSheet.isCellHidden(x, y)) {
					Jedox.wss.mouse.mimicCellMouseEvent(x, y, 'mousedown', actSheet._panes[i]);
					return;
				}
			}

			isBeg = false;

			if (rngs.length == 4) {
				if (i % 2)
					// Panes 1 & 3.
					pX = rngs[--i].lrX - rngs[i].ulX + 1, x = rngs[i].lrX, y = rngs[i].ulY + pY - 1;
				else
					// Panes 0 & 2.
					if (pY == 1)
						pX = rngs[i == 0 ? (i = 3) : --i].lrX - rngs[i].ulX + 1, pY = rngs[i].lrY - rngs[i].ulY + 1, x = rngs[i].lrX, y = rngs[i].lrY;
					else
						pX = rngs[++i].lrX - rngs[i].ulX + 1, pY--, x = rngs[i].lrX, y = rngs[i].ulY + pY - 1;
			} else {
				if (pY == 1)
					pX = rngs[rngs.length == 1 ? i : (i ? --i : ++i)].lrX - rngs[i].ulX + 1, pY = rngs[i].lrY - rngs[i].ulY + 1, x = rngs[i].lrX, y = rngs[i].lrY;
				else
					pX = rngs[i].lrX - rngs[i].ulX + 1, pY--, x = rngs[i].lrX, y--;
			}
		}
	}

	function iterForVert(x, y) {
		var i = sPane = paneId,
			isBeg = true,
			pX = x - rngs[i].ulX + 1, pY = y - rngs[i].ulY + 1,
			sPX = pX, sPY = pY;

		while (true) {
			for (; y <= rngs[i].lrY; ++y, ++pY) {
				if (!isBeg && i == sPane && pX == sPX && pY == sPY)
					return;

				if (!actSheet._panes[i].isCellLocked(x, y) && actSheet.isCellHidden(x, y)) {
					Jedox.wss.mouse.mimicCellMouseEvent(x, y, 'mousedown', actSheet._panes[i]);
					return;
				}
			}

			isBeg = false;

			switch (rngs.length) {
				case 4:
					if (i >= 2) {
						// Panes 2 & 3.
						if (x == rngs[i].lrX)
							pX = 1, pY = 1, x = rngs[i == 3 ? (i = 0) : --i].ulX, y = rngs[i].ulY;
						else
							pX++, pY = 1, x = rngs[(i -= 2)].ulX + pX - 1, y = rngs[i].ulY;
					} else
						// Panes 0 & 1.
						pY = 1, x = rngs[(i += 2)].ulX + pX - 1, y = rngs[i].ulY;

					break;

				case 2:
					if (x == rngs[i].lrX && i)
						pX = 1, pY = 1, x = rngs[--i].ulX, y = rngs[i].ulY;
					else
						pX = i ? pX + 1 : pX, pY = 1, x = i ? x + 1 : x, y = rngs[i ? --i : ++i].ulY;

					break;

				default:
					if (x == rngs[i].lrX)
						pX = 1, pY = 1, x = rngs[i].ulX, y = rngs[i].ulY;
					else
						pX++, pY = 1, x++, y = rngs[i].ulY;
			}
		}
	}

	function iterBackVert(x, y) {
		var i = sPane = paneId,
			isBeg = true,
			pX = x - rngs[i].ulX + 1, pY = y - rngs[i].ulY + 1,
			sPX = pX, sPY = pY;

		while (true) {
			for (; pY >= 1; --y, --pY) {
				if (!isBeg && i == sPane && pX == sPX && pY == sPY)
					return;

				if (!actSheet._panes[i].isCellLocked(x, y) && actSheet.isCellHidden(x, y)) {
					Jedox.wss.mouse.mimicCellMouseEvent(x, y, 'mousedown', actSheet._panes[i]);
					return;
				}
			}

			isBeg = false;

			switch (rngs.length) {
				case 4:
					if (i >= 2)
						// Panes 2 & 3.
						pY = rngs[(i -= 2)].lrY - rngs[i].ulY + 1, x = rngs[i].ulX + pX - 1, y = rngs[i].lrY;
					else
						// Panes 0 & 1.
						if (pX == 1)
							pX = rngs[i == 0 ? (i = 3) : ++i].lrX - rngs[i].ulX + 1, pY = rngs[i].lrY - rngs[i].ulY + 1, x = rngs[i].lrX, y = rngs[i].lrY;
						else
							pX--,  pY = rngs[(i += 2)].lrY - rngs[i].ulY + 1, x = rngs[i].ulX + pX - 1, y = rngs[i].lrY;

					break;

				case 2:
					if (pX == 1 && !i)
						pX = rngs[++i].lrX - rngs[i].ulX + 1, pY = rngs[i].lrY - rngs[i].ulY + 1, x = rngs[i].lrX, y = rngs[i].lrY;
					else
						pX = i ? pX : pX - 1, x = i ? x : x - 1, pY = rngs[i ? --i : ++i].lrY - rngs[i].ulY + 1, y = rngs[i].lrY;

					break;

				default:
					if (pX == 1)
						pX = rngs[i].lrX - rngs[i].ulX + 1, pY = rngs[i].lrY - rngs[i].ulY + 1, x = rngs[i].lrX, y = rngs[i].lrY;
					else
						pX--, pY = rngs[i].lrY - rngs[i].ulY + 1, x--, y = rngs[i].lrY;
			}
		}
	}

	switch(direction) {
		case iterMode.NEXTX:
			iterForHor(currX + 1, currY);
			break;

		case iterMode.PREVX:
			iterBackHor(currX - 1, currY);
			break;

		case iterMode.NEXTY:
			iterForVert(currX, currY + 1);
			break;

		case iterMode.PREVY:
			iterBackVert(currX, currY - 1);
			break;

		case iterMode.FIRST:
			paneId = rngs.length - 1;

			iterForHor(rngs[paneId].lrX + 1, rngs[paneId].lrX)
			break;

		case iterMode.LAST:
			paneId = 0;

			iterBackHor(rngs[paneId].ulX - 1, rngs[paneId].ulX);
			break;
	}

}

Jedox.wss.keyboard.handleUMFocus = function(keyCode, shiftKey) {
	var selCellCoords = Jedox.wss.app.environment.selectedCellCoords;

	if (selCellCoords.length == 0)
		selCellCoords = [1, 1];

	switch(keyCode) {
		// Tab
		case 9:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], shiftKey ? Jedox.wss.grid.IterationMode.PREVX : Jedox.wss.grid.IterationMode.NEXTX);
			break;

		// Enter
		case 13:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], shiftKey ? Jedox.wss.grid.IterationMode.PREVY : Jedox.wss.grid.IterationMode.NEXTY);
			break;

		// Arrow Right
		case 39:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], Jedox.wss.grid.IterationMode.NEXTX);
			break;

		// Arrow Left
		case 37:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], Jedox.wss.grid.IterationMode.PREVX);
			break;

		// Arrow Down
		case 40:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], Jedox.wss.grid.IterationMode.NEXTY);
			break;

		// Arrow Down
		case 38:
			Jedox.wss.keyboard.focusInput(selCellCoords[0], selCellCoords[1], Jedox.wss.grid.IterationMode.PREVY);
			break;
	}
}

Jedox.wss.keyboard.fetchGlobalKeyUp = function(ev) {
	if (document.all)
		ev = window.event;

	if (!ev.ctrlKey) {
		Jedox.wss.app.ctrlKeyPressed = false;

		var env = Jedox.wss.app.environment;
		var mousePos = (env)? env.mousePosition : null;
		if (mousePos == 'rngBorder' || mousePos == 'magicDot')
			env.defaultSelection.setCursor(mousePos, (mousePos == 'rngBorder') ? 'rng_move' : 'md_curr');
	}

	var wrapper = Jedox.wss.app.activeWrapper;
	if (wrapper && !ev.shiftKey)
		wrapper.preserveRatio = wrapper.defaultRatio;
}

// Generate keyboard event (just a sample; currently not used)
Jedox.wss.keyboard.genKbdEvent = function(keyCode, ctrlKey, altKey, shiftKey, metaKey) {

	if(window.KeyEvent) {

		var evObj = document.createEvent('KeyEvents');
		evObj.initKeyEvent('keydown', true, true, window, ctrlKey, altKey, shiftKey, metaKey, keyCode, 0);
		fireOnThis.dispatchEvent(evObj);

	} else {
		var evObj = document.createEventObject();
		evObj.ctrlKey = true;
		evObj.keyCode = keyCode;

  		document.fireEvent("onkeydown", evObj);
	}
}
