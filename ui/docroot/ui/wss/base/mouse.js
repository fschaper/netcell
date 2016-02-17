/*
 * \brief mouse event handling routines
 *
 * \file mouse.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: mouse.js 5152 2011-07-28 10:02:33Z predragm $
 *
 */

Jedox.wss.mouse.MouseIsOnCell = function (XPos, YPos, Coords){// TODO: Check/Rewrite
	return ( ((XPos >= Coords[0][0]) && (XPos <= Coords[0][1])) && ((YPos >= Coords[1][0]) && (YPos <= Coords[1][1])) );
}

Jedox.wss.mouse.updateLastCell = function(el, elCoords, pane) {
	if (pane == undefined) {
		var relPanes = Jedox.wss.app.activeSheet.getPanesByCoords(elCoords[0], elCoords[1]);
		pane = relPanes.length == 1 ? relPanes[0] : Jedox.wss.app.activePane;
	}

	var	env = pane._env.shared,
		mergeInfo = pane.getMergeInfo(elCoords[0], elCoords[1]);

	if (mergeInfo != undefined && !mergeInfo) {
		env.lastCellCoords = [mergeInfo[1], mergeInfo[2]];
		env.lastCell = pane.getCellByCoords(mergeInfo[1], mergeInfo[2]);
	} else {
		env.lastCell = el;
		env.lastCellCoords = [elCoords[0], elCoords[1]];
	}
}

Jedox.wss.mouse.overTracking = function(ev, pane) {
	if (!Jedox.wss.app.loaded || pane == undefined)
		return;

	if (document.all)
		ev = window.event;

	var el = (document.all) ? ev.srcElement : ev.target,
		elCoords;

	if (el.tagName != 'DIV')
		el = el.parentNode;

	if ((elCoords = pane.getCoordsByCell(el)) == undefined)
		return;

	Jedox.wss.mouse.updateLastCell(el, elCoords, pane);

	if (el.tagName == 'DIV' && el.className == 'gridCell')
		Jedox.wss.keyboard.preventEvent(ev);

	// cell comment
	Jedox.wss.cmnt.showComment(elCoords, pane);
}

Jedox.wss.mouse.rangeOverTracking = function (myEvent, activeSheet) {
	var env = activeSheet._env.shared;

	if(env.viewMode == Jedox.wss.grid.viewMode.USER || (activeSheet._panes.length > 1 && activeSheet._panes[0].hasFullSize() && activeSheet._autoScroll.isScrolling()))
		return;

	if (document.all)
		myEvent = window.event;

	var myElement = (document.all) ? myEvent.srcElement : myEvent.target,
		paneId = !myElement.className.search('rangeMask') ? myElement.parentNode._paneId : myElement._paneId,
		pane = activeSheet._panes[paneId],
		rangeStartCoords = env.defaultSelection.getActiveRange().getUpperLeft(),
		lastCellCoords = env.lastCellCoords,
		targetCoords = pane.getNeighByOffset(rangeStartCoords.getX(), rangeStartCoords.getY(), (document.all ? myEvent.offsetX : myEvent.layerX) + myElement.offsetLeft + 4, (document.all ? myEvent.offsetY : myEvent.layerY) + myElement.offsetTop + 4);

	if (lastCellCoords[0] != targetCoords[0] || lastCellCoords[1] != targetCoords[1]) {
//		var mergeInfo = pane.getMergeInfo(targetCoords[0], targetCoords[1]);
//
//		if (mergeInfo != undefined && !mergeInfo) {
//			env.lastCellCoords = [mergeInfo[1], mergeInfo[2]];
//			env.lastCell = pane.getCellByCoords(mergeInfo[1], mergeInfo[2]);
//		} else {
			env.lastCell = targetCoords[2];
			env.lastCellCoords = [targetCoords[0], targetCoords[1]];
//		}
//		Jedox.wss.mouse.updateLastCell(myElement, targetCoords, pane);
	}

	if (myElement.tagName == 'DIV' && myElement.className == 'gridCell')
		Jedox.wss.keyboard.preventEvent(myEvent);

	// cell comment
	Jedox.wss.cmnt.showOnMoveComment(lastCellCoords, pane);
}

Jedox.wss.mouse.mouseonCellDblClick = function(ev, pane) {
	if (document.all)
		ev = window.event;

	var el = (document.all) ? ev.srcElement : ev.target;
	if (el.tagName != 'DIV')
		el = el.parentNode;

	var	cellCoords = pane.getCoordsByCell(el);

	if (!cellCoords)
		return true;

	Jedox.wss.mouse.showCursorLayer('marker_sand_clock');

	var cbRes = pane.cbFire(cellCoords[0], cellCoords[1], 'dblclick', {
		c: cellCoords[0],
		r: cellCoords[1]
	});
	Jedox.wss.mouse.hideCursorLayer();

	if (!cbRes)
		return false;

	// Continue with other operations.

	//Jedox.wss.general.showInputField(null, false, true);
	//Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.INPUT);
}

Jedox.wss.mouse.mouseOnCellDown = function(myEvent, pane) {
	if (pane._book != Jedox.wss.app.activeBook)
		return false;

	if (document.all) {
		myEvent = window.event;
	}

	var myElement = (document.all) ? myEvent.srcElement : myEvent.target;
	if (myElement.tagName != 'DIV')
		myElement = myElement.parentNode;

	var env = pane._env.shared,
		elCoords = pane.getCoordsByCell(myElement);

	if (elCoords == undefined)
		return;

	var cbRes = pane.cbFire(elCoords[0], elCoords[1], 'mousedown', myEvent);

	if (!cbRes) {
		Jedox.wss.keyboard.preventEvent(myEvent);
		return false;
	}

	var value;

	// NOT CHECKED START - CEBITREV
	if ((env.inputMode == Jedox.wss.grid.GridMode.EDIT) || (env.inputMode == Jedox.wss.grid.GridMode.INPUT)) {
		value = env.inputField.value;

		if (value.length > 0 && value.substr(0,1) == '=' && env.viewMode != Jedox.wss.grid.viewMode.USER) {
			Jedox.wss.app.lastInputMode = env.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.POINT);

			var elemCoords = pane.getCoordsByCell(myElement);

			if (env.formulaSelection.activeToken != null)
			{
				var point, area = env.formulaSelection.getActiveRange();

				area.set(point = new Jedox.gen.Point(elemCoords[0], elemCoords[1]), point);
				area.formulaUpdate();

				area.draw();
			}
			else
			{
				var currFormula = Jedox.wss.app.currFormula,
						selection = Jedox.util.getSelection(Jedox.wss.app.fromFormulaField ? currFormula.el.dom : env.inputField),
						selStart = selection.start,
						selEnd = selection.end;

				if (selStart == 0 || value.substr(selStart - 1, 1).match(/^[a-z0-9]$/i) != null)
				{
					if (env.oldValue != value )
						Jedox.wss.keyboard.sendInput(env.inputField);
					else
						 Jedox.wss.keyboard.cancelInput();

					return Jedox.wss.mouse.mouseOnCellDown(myEvent, pane);
				}

				var elemCoordsA1 = Jedox.wss.app.numberToLetter[elemCoords[0]].concat(elemCoords[1]);

				env.inputField.value = value.substring(0, selStart).concat(elemCoordsA1, value.substring(selEnd));
				currFormula.setValue(env.inputField.value);

				Jedox.wss.range.drawDependingCells(currFormula.getValue());
				Jedox.wss.keyboard.setFieldSize();
				env.lastInputValue = currFormula.getValue();

				Jedox.util.setSelection(Jedox.wss.app.fromFormulaField ? currFormula.el.dom : env.inputField, selStart + elemCoordsA1.length);

				for (var tok, area, areas = env.formulaSelection.getRanges(), i = areas.length - 1; i >= 0; --i)
					if (selStart >= (tok = (area = areas[i]).formulaToken).start && selStart < tok.end)
					{
						env.formulaSelection.activeToken = tok;
						env.formulaSelection.setActiveRange(i);

						env.formulaSelection.setState(Jedox.wss.range.AreaState.NEW);
						area.repaint();

						break;
					}
			}

			Jedox.wss.app.environment.formulaSelection.registerForMouseMovement(myElement);

		}else{
			/**
			 * @TODO: perhaps avoid calling Jedox.wss.keyboard.cancelInput() and do in an
			 * more elegant way...
			 */
			if (Jedox.wss.app.environment.viewMode != Jedox.wss.grid.viewMode.USER)
				Jedox.wss.app.environment.formulaSelection.removeAll();
			else
				Jedox.wss.app.environment.inputField.style.display = 'none';

			if (Jedox.wss.app.environment.oldValue != value)
				Jedox.wss.keyboard.sendInput(Jedox.wss.app.environment.inputField);
			else
				Jedox.wss.keyboard.cancelInput();

			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.READY);
			Jedox.wss.hb.setAllNormal();
		}
	}

	if (env.viewMode == Jedox.wss.grid.viewMode.USER && pane.isCellLocked(elCoords[0], elCoords[1])) {
		Jedox.wss.keyboard.cancelInput();
		return;
	}

	if (Jedox.wss.app.environment.inputMode == Jedox.wss.grid.GridMode.DIALOG && Jedox.wss.app.sourceSel)
		Jedox.wss.mouse.initSourceRange(myElement, pane.getCoordsByCell(myElement));

	// NOT CHECKED STOP
	if(Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.DESIGNER &&
		Jedox.wss.app.environment.inputMode == Jedox.wss.grid.GridMode.READY){

		var elementCoords;

		if (pane != undefined) {
			var elementCoords = pane.getCoordsByCell(myElement);

			if (elementCoords == undefined)
				return;
		}

		Jedox.wss.app.environment.defaultSelection.set(
			new Jedox.gen.Point(elementCoords[0], elementCoords[1]),
			new Jedox.gen.Point(elementCoords[0], elementCoords[1])
		);

		//if(Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.DESIGNER){
			Jedox.wss.app.environment.defaultSelection.registerForMouseMovement(myElement);
		//}
		Jedox.wss.app.environment.defaultSelection.draw();
		Jedox.wss.app.environment.defaultSelection.getActiveRange().reposBgndMask(false);

		if (myEvent.button == 2 || (Ext.isMac && myEvent.button == 0 && Jedox.wss.app.ctrlKeyPressed))
			Jedox.wss.mouse.showMainCntxMenu(myEvent);

		Jedox.wss.hb.setAllNormal();
	}

	if(Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER) {
		var selectedCellCoords = pane.getCoordsByCell(myElement),
			mrgInfoSelCell = pane.getMergeInfo(selectedCellCoords[0], selectedCellCoords[1]);

		env.selectedCell = myElement;
		env.selectedCellCoords = selectedCellCoords;
		env.lastRangeStartCoord = env.lastRangeEndCoord = [selectedCellCoords[0], selectedCellCoords[1]];

		var selCellValue = pane.getCellUVal(selectedCellCoords[0], selectedCellCoords[1]);
		env.selectedCellValue = (selCellValue == undefined) ? '' : selCellValue;

		var actCellCoords = pane.getPixelsByCoords(selectedCellCoords[0], selectedCellCoords[1]),
			actCellIncCoords = pane.getPixelsByCoords(selectedCellCoords[0] + (mrgInfoSelCell && mrgInfoSelCell[0] ? mrgInfoSelCell[1] : 1), selectedCellCoords[1] + (mrgInfoSelCell && mrgInfoSelCell[0] ? mrgInfoSelCell[2] : 1));

		Jedox.wss.app.activeSheet._cursorField.draw(
			{
				ulX: actCellCoords[0],
				ulY: actCellCoords[1],
				lrX: actCellIncCoords[0],
				lrY: actCellIncCoords[1]
			}, new Jedox.gen.Point(selectedCellCoords[0], selectedCellCoords[1])
		);
	}

}

Jedox.wss.mouse.initSourceRange = function(cell, ulCoords, lrCoords) {
	if (!lrCoords)
		lrCoords = ulCoords;

	var formSel = Jedox.wss.app.environment.formulaSelection;

	formSel.removeAll();
	formSel.addRange(new Jedox.gen.Point(ulCoords[0], ulCoords[1]), new Jedox.gen.Point(lrCoords[0], lrCoords[1]));
	formSel.setActiveRange(formSel.getRanges().length - 1);
	formSel.setState(Jedox.wss.range.AreaState.NEW);

	if (cell) {
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.POINT);
		formSel.registerForMouseMovement(cell);
	}

	formSel.draw();
}

Jedox.wss.mouse.mouseOnRangeDown = function (myEvent, activeSheet) {
	if (document.all) {
		myEvent = window.event;
	}

	var env = activeSheet._env.shared,
		myElement = (document.all) ? myEvent.srcElement : myEvent.target,
		isRangeMask = !myElement.className.search('rangeMask'),
		paneId = isRangeMask ? myElement.parentNode._paneId : myElement._paneId,
		pane = activeSheet._panes[paneId],
		srcRngMode = env.inputMode == Jedox.wss.grid.GridMode.DIALOG && Jedox.wss.app.sourceSel;

	if (Jedox.wss.app.activePane != pane) {
		pane.select();
		activeSheet._defaultSelection.draw();
	}

	if (!srcRngMode && myEvent.button == 2 && isRangeMask) {
		Jedox.wss.mouse.showMainCntxMenu(myEvent);
		Jedox.wss.keyboard.preventEvent(myEvent);
		return;
	}

	var rangeStartCoords = env.defaultSelection.getActiveRange().getUpperLeft(),
		targetCoords = pane.getNeighByOffset(rangeStartCoords.getX(), rangeStartCoords.getY(), ((document.all) ? myEvent.offsetX : myEvent.layerX) + myElement.offsetLeft + 4, ((document.all) ? myEvent.offsetY : myEvent.layerY) + myElement.offsetTop + 4),
		tX = targetCoords[0], tY = targetCoords[1],
		targetMrgInfo = pane.getMergeInfo(tX, tY);

	if (targetMrgInfo && !targetMrgInfo[0])
		tX = targetMrgInfo[1], tY = targetMrgInfo[2];

	if(env.inputMode == Jedox.wss.grid.GridMode.READY) {
		env.defaultSelection.set(
			new Jedox.gen.Point(tX, tY),
			new Jedox.gen.Point(tX, tY)
		);

		if(env.viewMode == Jedox.wss.grid.viewMode.DESIGNER){
			env.defaultSelection.registerForMouseMovement(targetCoords[2]);
		}
		env.defaultSelection.draw();
		env.defaultSelection.getActiveRange().reposBgndMask(false);
	}

	if (srcRngMode)
		Jedox.wss.mouse.initSourceRange(pane.getCellByCoords(targetCoords[0], targetCoords[1]), targetCoords);

	if((myElement.tagName == 'DIV') && (myElement.className == 'rangeMask')) {
		Jedox.wss.keyboard.preventEvent(myEvent);
	}
}

Jedox.wss.mouse.checkForResize = function (ev, sheet) {
	if (document.all)
		ev = window.event;

	var el = (document.all) ? ev.srcElement : ev.target,
		env = sheet._env.shared;

	if (env.inputMode == Jedox.wss.grid.GridMode.EDIT)
		return ;

	function checkPosition() {
		var XOffset = 5, YOffset = 4;

		if(el.parentNode.className == 'gridColHdrsIC') {
			var resizeIndex = (el.className + '').indexOf(' col_resize'),
				targetX = (document.all) ? ev.offsetX : ev.layerX,
				hdr = sheet.locateHdr(Jedox.wss.grid.headerType.COLUMN, el);

			if((targetX <= XOffset && (hdr[0] != hdr[1].getCoordsFirstVCell()[0])) ||
				(el.offsetWidth - targetX <= XOffset)){

				env.mousePosition = 'colResize';

				if (resizeIndex == -1)
					el.className += ' col_resize';
			} else {
				env.mousePosition = 'colMark';

				if (resizeIndex > -1)
					el.className = el.className.substring(0, resizeIndex);
			}
		}

		if (el.parentNode.className == 'gridRowHdrsIC') {
			var resizeIndex = (el.className + '').indexOf(' row_resize'),
				targetY = (document.all) ? ev.offsetY : ev.layerY,
				hdr = sheet.locateHdr(Jedox.wss.grid.headerType.ROW, el);

			if((targetY <= YOffset && (hdr[0] != hdr[1].getCoordsFirstVCell()[1])) ||
				(el.offsetHeight - targetY  <= YOffset)) {

				env.mousePosition = 'rowResize';

				if (resizeIndex == -1)
					el.className += ' row_resize';
			} else {
				env.mousePosition = 'rowMark';

				if (resizeIndex > -1)
					el.className = el.className.substring(0, resizeIndex);
			}
		}
	}

	/* Only check the position if the move has moved */
	if (Jedox.wss.app.xPos != ev.clientX || Jedox.wss.app.yPos != ev.clientY) {
		if(Jedox.wss.app.mouseButton1Down) {
        	if(env.headerMarkMode === '')
        		Jedox.wss.mouse.fetchGlobalMouseMove(ev);
		} else {
			Jedox.wss.app.xPos = ev.clientX;
			Jedox.wss.app.yPos = ev.clientY;

			checkPosition();
		}
	}
}


Jedox.wss.mouse.fetchMove = function (MouseEvent){// TODO: Check/Rewrite

  	if(Jedox.wss.app.maybeDragging ||
  		Jedox.wss.app.environment.headerResizeType == Jedox.wss.grid.headerType.COLUMN ||
  		Jedox.wss.app.environment.headerResizeType == Jedox.wss.grid.headerType.ROW) {
		return ;
	}

	var Coords = null;

	if(Jedox.wss.app.environment.lastCell === null){
		Jedox.wss.app.xPos = MouseEvent.clientX;
		Jedox.wss.app.yPos = MouseEvent.clientY;
	}else{
		Coords = Jedox.wss.range.getCellCoord(Jedox.wss.app.environment.lastCell);

		if(!(Jedox.wss.mouse.MouseIsOnCell(MouseEvent.clientX, MouseEvent.clientY, Coords))){
			Jedox.wss.app.xPos = MouseEvent.clientX;
			Jedox.wss.app.yPos = MouseEvent.clientY;
		}
	}
}

Jedox.wss.mouse.calcGridScreenCoords = function(ev, el, offsets, pane, skipStore) {
	if (!offsets)
		offsets = [0, 0];

	if (!pane)
		pane = Jedox.wss.app.activePane;

	var viewportPos = pane.getViewportPos(),
		gridScreenX = ev.clientX - (el.offsetLeft + (document.all ? ev.offsetX : ev.layerX) + offsets[0] - viewportPos[0][0]),
		gridScreenY = ev.clientY - ((el.className == 'gridCell' ? el.parentNode.offsetTop : el.offsetTop) + (document.all ? ev.offsetY : ev.layerY)  + offsets[1] - viewportPos[0][1]),

		gsCoords = [
			[gridScreenX, gridScreenY],

			[gridScreenX + viewportPos[1][0] - viewportPos[0][0],
			gridScreenY + viewportPos[1][1] - viewportPos[0][1]],

			[(document.all) ? document.body.clientWidth : window.innerWidth,
			(document.all) ? document.body.clientHeight : window.innerHeight]
		];

	if (skipStore)
		return gsCoords;
	else
		Jedox.wss.app.environment.gridScreenCoords = gsCoords;
}

Jedox.wss.mouse.fetchGlobalMouseDown = function (myMouseEvent) {// TODO: Check/Rewrite
	if(!Jedox.wss.app.loaded)
		return;

	if (document.all)
		myMouseEvent = window.event;

	Jedox.wss.app.mouseDownObserver.notify(this, myMouseEvent);

	var mouseEl = (document.all) ? myMouseEvent.srcElement : myMouseEvent.target,
		trigCls = ['gridCell', 'rangeEdge', 'HBRangeBorder', 'HBSubDataCell'];

	if (trigCls.indexOf(mouseEl.className) >= 0)
		Jedox.wss.mouse.calcGridScreenCoords(myMouseEvent, mouseEl);

    Jedox.wss.app.mouseButton1Down = false;
    Jedox.wss.app.mouseButton2Down = false;

    if ( (document.all && myMouseEvent.button == 1) || (myMouseEvent.button === 0) ){
        Jedox.wss.app.mouseButton1Down = true;
	}else if(myMouseEvent.button == 2){
        Jedox.wss.app.mouseButton2Down = true;
    }

	try{
	    var ParentElementId = mouseEl.parentNode.childNodes[0].id;
		if( (typeof(ParentElementId) != 'undefined') && (ParentElementId.length > 5) && (ParentElementId.substring(0, 6) != "column") ){
			Jedox.wss.app.maybeDragging = true;
		}else{
			Jedox.wss.app.maybeDragging = false;
		}
	}catch(Exception){
		Jedox.wss.app.maybeDragging = true;
	}

}

Jedox.wss.mouse.fetchGlobalMouseUp = function (myMouseEvent) {
	if(!Jedox.wss.app.loaded)
		return;

	if (document.all)
		myMouseEvent = window.event;

	Jedox.wss.app.mouseUpObserver.notify(this, myMouseEvent);

	var isBtn1 = (document.all && myMouseEvent.button == 1) || myMouseEvent.button === 0,
		env = Jedox.wss.app.environment;

	if (isBtn1) {
		Jedox.wss.app.mouseButton1Down = false;
    	Jedox.wss.app.mouseButton2Down = false;
	}

	if (env == null)
		return;

	if (isBtn1 && env.headerResizeType != Jedox.wss.grid.headerType.NONE)
    		Jedox.wss.mouse.stopHeaderResize();

    Jedox.wss.app.maybeDragging = false;

    Jedox.wss.app.mouseButton2Down = false;

	if (env.headerMarkMode.length > 0)
		Jedox.wss.mouse.hideCursorLayer();

	env.headerMarkMode = '';

	if (env.viewMode != Jedox.wss.grid.viewMode.USER) {
		if (env.defaultSelection)
			env.defaultSelection.getActiveRange().reposBgndMask(true);

		Jedox.wss.wsel.moveSave();
	}
}

Jedox.wss.mouse.fetchGlobalMouseMove = function (MyMouseEvent){// TODO: Check/Rewrite
	if(!Jedox.wss.app.loaded)
		return;

	if (document.all)
		MyMouseEvent = window.event;

	Jedox.wss.app.mouseMovementObserver.notify(this, MyMouseEvent);

	if (Jedox.wss.app.mimicOvertracking) {
		var elCoords = Jedox.wss.mouse.getGridPos(MyMouseEvent);

		if (elCoords[0] > 0 && elCoords[1] > 0)
			Jedox.wss.mouse.updateLastCell(elCoords[2], [elCoords[0], elCoords[1]]);
	}

	var elem = (document.all) ? MyMouseEvent.srcElement : MyMouseEvent.target,
		env = Jedox.wss.app.environment, i;

	if (env == null)
		return;

	Jedox.wss.app.xPos = MyMouseEvent.clientX;
	Jedox.wss.app.yPos = MyMouseEvent.clientY;

	var hdrResType = env.headerResizeType;
	if (hdrResType == Jedox.wss.grid.headerType.COLUMN)
		Jedox.wss.mouse.doHeaderResize(hdrResType, MyMouseEvent.clientX);
	else if (hdrResType == Jedox.wss.grid.headerType.ROW)
		Jedox.wss.mouse.doHeaderResize(hdrResType, MyMouseEvent.clientY);

	if (env.headerMarkMode == 'column' || env.headerMarkMode == 'row')
		env.defaultSelection.resizeByHeader(MyMouseEvent);
}

Jedox.wss.mouse.appendtoScrollwheel = function (){// TODO: Check/Rewrite
	if (window.addEventListener){
		window.addEventListener('DOMMouseScroll', Jedox.wss.mouse.fetchWheel, false);
	}
	window.onmousewheel = document.onmousewheel = Jedox.wss.mouse.fetchWheel;
}

Jedox.wss.mouse.fetchWheel = function (ev){// TODO: Check/Rewrite
	if (Jedox.wss.app.environment.inputMode != Jedox.wss.grid.GridMode.DIALOG) {
		var value = 0;

		if (!ev) {
			ev = window.event;
		}

		if (ev.wheelDelta){
			value = ev.wheelDelta;

			/**
			 * @TODO: Browser detection needed at this point!
			 * We need to differ Opera from IE
			*/
			// IE only:
			if(!(  typeof HTMLElement != 'undefined' && HTMLElement.prototype )){
				value *= -1;
			}
		}else if (ev.detail) {
			value = ev.detail;
		}

		if(value > 0){
			Jedox.wss.sheet.scrollYBy(1, Jedox.wss.grid.ScrollDirection.DOWN);
		}else if( value < 0 ){
			Jedox.wss.sheet.scrollYBy(1, Jedox.wss.grid.ScrollDirection.UP);
		}

		Jedox.wss.keyboard.preventKeyEvent(ev);
	}
}

Jedox.wss.mouse.showCursorLayer = function(cls) {
	var cursorMarker = document.getElementById('CursorMarker');

	cursorMarker.style.top = '0px';
	cursorMarker.style.left = '0px';
	cursorMarker.style.width = (document.all) ? document.body.clientWidth : window.innerWidth + 'px';
	cursorMarker.style.height = (document.all) ? document.body.clientHeight : window.innerHeight + 'px';
	cursorMarker.className = cls;
	cursorMarker.style.display = 'block';

}

Jedox.wss.mouse.hideCursorLayer = function() {
	var cursorMarker = document.getElementById('CursorMarker');

	cursorMarker.style.width = '0px';
	cursorMarker.style.height = '0px';
	cursorMarker.style.display = 'none';
}

/**
 * This function is called when mouse down event on row or column header is fired
 * and mouse position is at a resize position.
 * It only runs once and prepares elements for resizing of rows or columns.
 * @param {Number} type type header that has been reised (column or row)
 * @param {Object} elem header DIV element on which the mousedown event was fired
 * @param {Number} coord coordinate of selected header element
 * @param {Number} cursorOffset cursors offset from the window boundaries in pixels
 */
Jedox.wss.mouse.startHeaderResize = function (type, elem, coord, cursorOffset, hdrOffset, pane) {
	Jedox.wss.app.environment.headerResizeType = type;
	Jedox.wss.app.environment.headerResizeCoord = coord;

	var hdrType = Jedox.wss.grid.headerType,
		paneIC = pane._ic,
		activeSheet = pane._sheet,
		sheetDomId = activeSheet._domId,
		viewportPos = pane.getViewportPos(),

		startMarkerLeft = (type == hdrType.COLUMN) ? elem.offsetLeft - viewportPos[0][0] + pane._oc.offsetLeft : 0,
		startMarkerTop = (type == hdrType.ROW) ? elem.offsetTop - viewportPos[0][1] + pane._oc.offsetTop : -1,
		stopMarkerLeft = (type == hdrType.COLUMN) ? startMarkerLeft + elem.offsetWidth : 0,
		stopMarkerTop = (type == hdrType.ROW) ? startMarkerTop + elem.offsetHeight : -1,

		markerHeight = ((type == hdrType.COLUMN) ? paneIC.offsetHeight : 1) + 'px',
		markerWidth = ((type == hdrType.ROW) ? paneIC.offsetWidth : 1) + 'px',
		borderTopWidth = (type == hdrType.ROW) ? '1px' : '0px',
		borderLeftWidth = (type == hdrType.COLUMN) ? '1px' : '0px',

		startMarker = document.getElementById("".concat(sheetDomId, '_startMarker')),
		stopMarker = document.getElementById("".concat(sheetDomId, '_stopMarker'));

	startMarker.style.left = startMarkerLeft + 'px';
	startMarker.style.top = startMarkerTop + 'px';
	startMarker.style.height = markerHeight;
	startMarker.style.width = markerWidth;
	startMarker.style.borderTopWidth = borderTopWidth;
	startMarker.style.borderLeftWidth = borderLeftWidth;
	startMarker.style.display = 'block';

	stopMarker.style.left = stopMarkerLeft + 'px';
	stopMarker.style.top = stopMarkerTop + 'px';
	stopMarker.style.height = markerHeight;
	stopMarker.style.width = markerWidth;
	stopMarker.style.borderTopWidth = borderTopWidth;
	stopMarker.style.borderLeftWidth = borderLeftWidth;
	stopMarker.style.display = 'block';

	this.showCursorLayer((type == hdrType.ROW) ? 'marker_row_resize' : 'marker_col_resize');

	if (type == hdrType.ROW)
		Jedox.wss.app.environment.headerResize = [
			startMarkerTop, stopMarkerTop,
			hdrOffset,
			viewportPos[0][1], pane._oc.parentNode.offsetHeight,
			stopMarkerTop, cursorOffset - hdrOffset
		];
	else
		Jedox.wss.app.environment.headerResize = [
			startMarkerLeft, stopMarkerLeft,
			hdrOffset,
			viewportPos[0][0], pane._oc.parentNode.offsetWidth,
			stopMarkerLeft, cursorOffset - hdrOffset
		];
}

/**
 * This function is called if resizing is in progress and mousemove event is fired
 * It will just move the marker element on X or Y axis to mouse position
 */
Jedox.wss.mouse.doHeaderResize = function (type, cursorOffset) {
	var activeSheet = Jedox.wss.app.activeSheet,
		hdrRes = Jedox.wss.app.environment.headerResize,
		stopMarker = document.getElementById(activeSheet._domId.concat('_stopMarker')),
		hdrSize = type == Jedox.wss.grid.headerType.COLUMN ? activeSheet._HDRS_WIDTH : activeSheet._HDRS_HEIGHT,

		newPos = hdrRes[1] - (hdrRes[6] - cursorOffset);

	if (newPos > hdrRes[4])
		newPos = hdrRes[1];
	else if (newPos < hdrRes[0] + 5)
		newPos = hdrRes[0] + 5;

	if(type == Jedox.wss.grid.headerType.COLUMN)
		stopMarker.style.left = newPos + 'px';
	else
		stopMarker.style.top = newPos + 'px';

	hdrRes[5] = newPos;
}

/**
 * This function is called if header resizing is in progress and mouseup event is fired
 * It will resize the rows/columns to calculated value.
*/
Jedox.wss.mouse.stopHeaderResize = function () {
	var env = Jedox.wss.app.environment,
		hdrRes = env.headerResize,
		resizedHdr = env.headerResizeCoord,
		sheetDomId = Jedox.wss.app.activeSheet._domId,
		startMarker = document.getElementById("".concat(sheetDomId, '_startMarker')),
		stopMarker = document.getElementById("".concat(sheetDomId, '_stopMarker')),

		hdrCoords = env.defaultSelection.getSelHeaderFromRange(env.headerResizeType, resizedHdr);

	if (hdrRes[1] != hdrRes[5]) {
		Jedox.wss.app.activeSheet.resizeColRow(env.headerResizeType, hdrCoords, hdrRes[5] - hdrRes[0]); // oldsize: hdrRes[1] - hdrRes[0]
		Jedox.wss.hb.setAllNormal(null, true);
	}

	startMarker.style.display = 'none';
	stopMarker.style.display = 'none';

	this.hideCursorLayer();

	env.headerResizeType = Jedox.wss.grid.headerType.NONE;
	env.headerResize = [];
}

Jedox.wss.mouse.autoSizeCell = function(ev) {
	var mousePosition = Jedox.wss.app.environment.mousePosition;

	if (!(mousePosition == 'colResize' || mousePosition == 'rowResize'))
		return;

	if (document.all)
		ev = window.event;

	if (!((document.all && ev.button == 1) || (ev.button === 0)))
		return;

	var myElement = (document.all) ? ev.srcElement : ev.target;
	var XOffset = 5; var YOffset = 5;
	var activeSheet = Jedox.wss.app.activeSheet;
	var headerType = Jedox.wss.grid.headerType;
	var hdrCoords = undefined;

	if (mousePosition == 'colResize') {
		var selHdr = activeSheet.getCoordByHdr(headerType.COLUMN, myElement);
		var targetOffsetX = (document.all) ? ev.offsetX : ev.layerX;
		if (targetOffsetX <= XOffset)
			--selHdr;

		hdrCoords = Jedox.wss.app.environment.defaultSelection.getSelHeaderFromRange(headerType.COLUMN, selHdr);
	} else if (mousePosition == 'rowResize') {
		var selHdr = activeSheet.getCoordByHdr(headerType.ROW, myElement);
		var targetOffsetY = (document.all) ? ev.offsetY : ev.layerY;
		if (targetOffsetY <= YOffset)
			--selHdr;

		hdrCoords = Jedox.wss.app.environment.defaultSelection.getSelHeaderFromRange(headerType.ROW, selHdr);
	}

	Jedox.wss.app.activeSheet.autofitColRow(mousePosition == 'colResize' ? 0 : 1, hdrCoords);
}

Jedox.wss.mouse.showMainCntxMenu = function (ev) {
	var defMaxCoords = Jedox.wss.grid.defMaxCoords,
	env = Jedox.wss.app.environment, selEndCoord = env.lastRangeEndCoord,
	selType = (selEndCoord[0] == defMaxCoords[0] && selEndCoord[1] == defMaxCoords[1]) ? 'all' : (selEndCoord[0] == defMaxCoords[0]) ? 'row' : (selEndCoord[1] == defMaxCoords[1]) ? 'col' : null,
	insItem, delItem;

	if (selType == null) {
		insItem = new Ext.menu.Item(
			{text: "Insert".localize(), menu: {
					items: [
						{text: "Shift cells right".localize(), handler: function() { Jedox.wss.sheet.ins(Jedox.wss.sheet.insDelMode.SHIFT_HOR); }},
						{text: "Shift cells down".localize(), handler: function() { Jedox.wss.sheet.ins(Jedox.wss.sheet.insDelMode.SHIFT_VER); }},
						{text: "Entire row".localize(), iconCls: 'ico_ins_row', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'row');}},
						{text: "Entire column".localize(), iconCls: 'ico_ins_column', handler: function() {Jedox.wss.action.insDelRowCol('ins', 'col');}}
					]
				}
			}
		);

		delItem = new Ext.menu.Item(
			{text: "Delete".localize(), menu: {
					items: [
						{text: "Shift cells left".localize(), handler: function() { Jedox.wss.sheet.del(Jedox.wss.sheet.insDelMode.SHIFT_HOR); }},
						{text: "Shift cells up".localize(), handler: function() { Jedox.wss.sheet.del(Jedox.wss.sheet.insDelMode.SHIFT_VER); }},
						{text: "Entire row".localize(), iconCls: 'ico_del_row', handler: function() {Jedox.wss.action.insDelRowCol('del', 'row');}},
						{text: "Entire column".localize(), iconCls: 'ico_del_column', handler: function() {Jedox.wss.action.insDelRowCol('del', 'col');}}
					]
				}
			}
		);
	} else {
		insItem = new Ext.menu.Item(
			{text: "Insert".localize(), handler: function() {Jedox.wss.action.insDelRowCol('ins', selType);}, disabled: (selType == 'all')}
		);

		delItem = new Ext.menu.Item(
			{text: "Delete".localize(), handler: function() {Jedox.wss.action.insDelRowCol('del', selType);}, disabled: (selType == 'all')}
		);
	}

	var clpExs = Jedox.wss.app.clipboard == null ? false : true,
		targEl = (Ext.isGecko2) ? ev.explicitOriginalTarget.parentNode : document.elementFromPoint(ev.clientX, ev.clientY),
		selCoord = env.selectedCellCoords,
		hlCMenu = Jedox.wss.hl.getContextMenu({
			defName: Jedox.wss.general.filterHLTags(selCoord[0], selCoord[1], env.selectedCellValue, false),
			data: Jedox.wss.hl.get(env.lastRangeStartCoord),
			withOpen: !(targEl == undefined || targEl.tagName.toUpperCase() != 'SPAN' || targEl.className != 'hl'),
			handlers: {
				scope: Jedox.wss.hl,
				set: Jedox.wss.hl.set,
				remove: Jedox.wss.hl.remove
			}
		}),
		cmntMenu = Jedox.wss.cmnt.getContextMenu(selCoord),
		mainCntxMenu = new Ext.menu.Menu({
			id: 'chartContextMenu',
			cls: 'default-format-window',
			enableScrolling: false,
			listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			items: [
				{text: "Cut".localize(), iconCls: 'icon_cut', handler: function(){Jedox.wss.action.cut(false);}},
				{text: "Copy".localize(), iconCls: 'icon_copy', handler: function(){Jedox.wss.action.copy(false);}},
				{text: "Paste".localize(), iconCls: 'icon_paste', disabled: !clpExs, handler: Jedox.wss.action.paste},
				{text: "Paste Special".localize().concat('...'), disabled: !clpExs, handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteSpecial, []);}},
				'-',
				insItem,
				delItem,
				'-',
				{id: 'formatCellsContext', text: 'Format Cells'.localize().concat('...'), iconCls: 'icon_edit', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells, []);}}
			].concat(cmntMenu, hlCMenu)
		});

	if (env.selectedCellFormula.indexOf('=SPARK') == 0)
		mainCntxMenu.insert(7, new Ext.menu.Item({text: 'Edit Micro Chart'.localize().concat('...'), iconCls: 'icon_insert_chart', handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openMicroChart, [true]);}}));

	mainCntxMenu.showAt([ev.clientX, ev.clientY]);
}

Jedox.wss.mouse.getGridPos = function(ev, pane) {
	var activePane = Jedox.wss.app.activePane,
		isPaneSet = pane != undefined;

	if (!isPaneSet)
		pane = activePane;

	var env = pane._env.shared,
		gridScreenCoords = this.calcGridScreenCoords(ev, document.all ? ev.srcElement : ev.target, null, pane, true),
		gridPosOffset = env.gridPosOffset,
		firstVCell = pane.getCoordsFirstVCell();

	if (ev.clientX < gridScreenCoords[0][0] || ev.clientX > gridScreenCoords[1][0] || ev.clientY < gridScreenCoords[0][1] || ev.clientY > gridScreenCoords[1][1]) {
		if (!isPaneSet)
			for (var panes = activePane._sheet._panes, i = panes.length - 1, elCoords; i >= 0; i--) {
				if (i == activePane._id)
					continue;

				elCoords = this.getGridPos(ev, panes[i]);

				if (elCoords[0] > 0 && elCoords[1] > 0)
					return elCoords;
			}

		return [0, 0];
	}

	return pane.getNeighByOffset(firstVCell[0], firstVCell[1], ev.clientX - gridScreenCoords[0][0] + gridPosOffset[0], ev.clientY - gridScreenCoords[0][1] + gridPosOffset[1]);
}

Jedox.wss.mouse.mimicCellMouseEvent = function(x, y, evName, activePane) {
	var activePane = activePane ? activePane : Jedox.wss.app.activePane,
		cbScrollTo = function() {
			var target = activePane.getCellByCoords(x, y);

			if(document.dispatchEvent) { // W3C
			    var oEvent = document.createEvent( "MouseEvents" );
			    oEvent.initMouseEvent(evName, true, true,window, 1, 1, 1, 1, 1, false, false, false, false, 0, target);
			    target.dispatchEvent( oEvent );
		    } else if(document.fireEvent) { // IE
		    	target.fireEvent('on'.concat(evName));
		    }
		};

	if (!activePane.isCellVisible(x, y)) {
		if (activePane._book._scrollPending)
			return;

		activePane.scrollTo([this, cbScrollTo], x, y, true, false);
	} else
		cbScrollTo();
}

Jedox.wss.mouse.regHyperlinkHandlers = function() {
	Jedox.wss.grid.cbReg('hl', [this, Jedox.wss.hl.follow]);
}
