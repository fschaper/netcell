/*
 * \brief action handling routines
 *
 * \file action.js
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
 * SVN: $Id: action.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

// Copy range
Jedox.wss.action.copy = function(copyToClp) {
	var env = Jedox.wss.app.environment;

	if (env.inputMode == Jedox.wss.grid.GridMode.READY) {
		var viewMode = Jedox.wss.grid.viewMode;

		switch(env.viewMode) {

			case viewMode.DESIGNER:
				env.defaultSelection.copy(copyToClp);
				break;

			case viewMode.USER:
				if (!env.selectedCellCoords.length)
					return;

				// try to set red border on click
				var cursorField = Jedox.wss.app.activeSheet._cursorField;
				cursorField.setBorder('2px solid #F5B800');

				var cursorValue = Jedox.wss.app.activePane.getCellValue(env.selectedCellCoords[0], env.selectedCellCoords[1]);
				if (cursorValue == undefined)
					cursorValue = '';

				Jedox.wss.app.clipboard = {
					id: null,
					op: Jedox.wss.grid.gridOperation.COPY,
					value: cursorValue
				};

				var _highlightBackToNormalCell = function() {
					cursorField.setBorder('2px solid #7EADD9');
				}

				setTimeout (_highlightBackToNormalCell, 300);

				if (copyToClp)
					Jedox.wss.general.setSysClipboard(cursorValue);
		}
	} else {
		//Jedox.wss.general.setSysClipboard();
		var selText = Jedox.util.getSelected(env.inputField);

		if (selText != null) {
			Jedox.wss.app.clipboard = {
				id: null,
				op: Jedox.wss.grid.gridOperation.COPY,
				value: selText
			};
		}
	}

	Jedox.wss.action.togglePaste(true);
}

// Cut range
Jedox.wss.action.cut = function(copyToClp) {
	var env = Jedox.wss.app.environment;

	if (env.inputMode == Jedox.wss.grid.GridMode.READY) {
		var viewMode = Jedox.wss.grid.viewMode;

		switch(env.viewMode) {

			case viewMode.DESIGNER:
				env.defaultSelection.cut(copyToClp);
				break;

			case viewMode.USER:
				var selCellCoords = env.selectedCellCoords;
				if (selCellCoords.length == 0)
					return;

				var activePane = Jedox.wss.app.activePane,
						cursorValue = activePane.getCellValue(selCellCoords[0], selCellCoords[1]);

				if (cursorValue == undefined)
					cursorValue = '';

				Jedox.wss.app.clipboard = {
					id: null,
					op: Jedox.wss.grid.gridOperation.CUT,
					value: cursorValue
				};

				if (copyToClp)
					Jedox.wss.general.setSysClipboard(cursorValue);

				Jedox.wss.app.activeSheet._cursorField.setContent('');
				activePane.clrRange([ selCellCoords[0], selCellCoords[1], selCellCoords[0], selCellCoords[1] ]);
		}
	} else {
		var selText = Jedox.util.getSelected(env.inputField);

		if (selText != null) {
			Jedox.wss.app.clipboard = {
				id: null,
				op: Jedox.wss.grid.gridOperation.CUT,
				value: selText
			};
		}
	}

	Jedox.wss.action.togglePaste(true);
}

// Paste range
Jedox.wss.action.paste = function(pasteWhat) {
	var env = Jedox.wss.app.environment,
		grid = Jedox.wss.grid;

	if (env.inputMode != grid.GridMode.READY)
		return;

	var viewMode = grid.viewMode;

	switch(env.viewMode) {

		case viewMode.DESIGNER:
			env.defaultSelection.paste(pasteWhat ? pasteWhat : Jedox.wss.range.ContentType.ALL_PASTE);
			break;

		case viewMode.USER:
			var selCellCoords = env.selectedCellCoords;

			if (!selCellCoords.length)
				return;

			var clipboard = Jedox.wss.app.clipboard,
				defMaxCoords = grid.defMaxCoords,
				clpVal;

			if (clipboard == null)
				clpVal = Jedox.wss.general.parseSysClipboard(true);
			else
				clpVal = {
					value: [clipboard.value],
					markRngDim: {width: 1, height: 1}
				};

			var lrX = selCellCoords[0] + clpVal.markRngDim.width - 1,
				lrY = selCellCoords[1] + clpVal.markRngDim.height - 1;

			Jedox.wss.app.activePane.setRangeValue([selCellCoords[0], selCellCoords[1], lrX > defMaxCoords[0] ? defMaxCoords[0] : lrX, lrY > defMaxCoords[1] ? defMaxCoords[1] : lrY], clpVal.value);

			break;
	}

}


Jedox.wss.action.togglePaste = function(enabled) {
	if (Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER) return;

	var act = enabled ? 'enable' : 'disable',
		menubar = Jedox.wss.app.menubar,
		toolbar = Jedox.wss.app.toolbar,
		tbarLayouts = Jedox.wss.app.toolbarLayouts;

	switch (Jedox.wss.app.toolbarLayout) {
		case tbarLayouts.TOOLBAR:
			menubar.paste[act]();
			menubar.pasteSpec[act]();
			break;

		case tbarLayouts.RIBBON:
			toolbar.pasteSpec[act]();
			break;
	}

	toolbar.paste[act]();
};


// Format painter.
Jedox.wss.action.exitFormatPainter = function() {

	if(!Jedox.wss.app.formatPainter)
		return;

	var env = Jedox.wss.app.environment;

	if (env.inputMode != Jedox.wss.grid.GridMode.READY || env.viewMode == Jedox.wss.grid.viewMode.USER)
		return;

	env.defaultSelection.exitFormatPainter();
	Jedox.wss.action.toggleFormatPainter(false);
	Jedox.wss.action.setCursorCSS(false);
};

Jedox.wss.action.toggleFormatPainter = function(toggle) {

	if (Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER) return;

	var act = 'toggle',
		toolbar = Jedox.wss.app.toolbar;

		toolbar.formatPainter[act](toggle, true);
};

Jedox.wss.action.setCursorCSS = function(fp) {

	var myStyleSheet = document.styleSheets[document.styleSheets.length - 1],
		className = 'div.customCursor',
		classContent = 'cursor: url(/ui/wss/res/img/xlpainter.cur), default; #cursor: url(/ui/wss/res/img/xlpainter.cur), default;';

	if(fp){

		if (myStyleSheet.insertRule)
			myStyleSheet.insertRule(className.concat('{', classContent, '}'), myStyleSheet.cssRules.length);
		else if (myStyleSheet.addRule)
			myStyleSheet.addRule(className, classContent, myStyleSheet.rules.length);

	}
	else {

		if (myStyleSheet.deleteRule)
			myStyleSheet.deleteRule(myStyleSheet.cssRules.length - 1);
		else if (myStyleSheet.removeRule)
			myStyleSheet.removeRule(myStyleSheet.rules.length - 1);

	}
}

// Refresh window
Jedox.wss.action.refreshWindow = function() {
	window.onbeforeunload = function () { };

	window.location.href = window.location.href;
}

Jedox.wss.action.exportToPDF = function ()
{
	(new Jedox.backend.RPCAsyncRqst('common', 'checkFopperLicense', [])).setOnSuccess([this, function (result)
	{
		if (result[0])
		{
			var jwwnd = Jedox.wss.wnd,
				jwapp = Jedox.wss.app;

			window.open('/be/wss/export.php/'.concat(escape(jwwnd.active.getName()), '.pdf?format=pdf&wam=', jwapp.appModeS, '&buid=', jwapp.activeBook.uid, '&suid=', jwapp.activeSheet.getUid()),
					'exp2pdf', 'directories=no,menubar=no,toolbar=no,location=no,status=no,resizable=yes,scrollbars=no');
		}
		else
			Jedox.wss.general.showMsg('fopperLic'.localize(), fopperLic[1].localize(), Ext.MessageBox.WARNING);
	}]).send();
}

Jedox.wss.action.exportToHTML = function ()
{
	var jwwnd = Jedox.wss.wnd,
			jwapp = Jedox.wss.app;

	window.open('/be/wss/export.php/'.concat(escape(jwwnd.active.getName()), '.html?format=html&wam=', jwapp.appModeS, '&buid=', jwapp.activeBook.uid, '&suid=', jwapp.activeSheet.getUid()),
				'exp2html', 'directories=no,menubar=yes,toolbar=yes,location=no,status=yes,resizable=yes,scrollbars=yes');
}

Jedox.wss.action.exportToXLSX = function (as_snapshot)
{
	var frameID = 'tmpExportIFrame',
			frame = Ext.get(frameID);

	if (!frame)
	{
		frame = document.createElement('iframe');
		frame.id = frameID;
		frame.name = frameID;
		frame.className = 'x-hidden';

		if (Ext.isIE)
			frame.src = Ext.SSL_SECURE_URL;

		document.body.appendChild(frame);

		if (Ext.isIE)
			document.frames[frameID].name = frameID;
	}
	else
		frame = frame.dom;

	var jwwnd = Jedox.wss.wnd,
			jwapp = Jedox.wss.app,
			name = jwwnd.active.getName();

	if (as_snapshot)
	{
		as_snapshot = '&snapshot';
		name = name.concat('_snapshot');
	}
	else
		as_snapshot = '';

	frame.contentWindow.location.href = '/be/wss/export.php/'.concat(escape(name), '.xlsx?format=xlsx&wam=', jwapp.appModeS, as_snapshot, '&buid=', jwapp.activeBook.uid, '&suid=', jwapp.activeSheet.getUid());
}

// Insert/Delete Column/Row
Jedox.wss.action.insDelRowCol = function(action, type) {
	var activeSheet = Jedox.wss.app.activeSheet,
			activePane = Jedox.wss.app.activePane,
			env = Jedox.wss.app.environment,
			selStartCoord = env.lastRangeStartCoord,
			selEndCoord = env.lastRangeEndCoord,
			handler;

	if (action == 'ins')
		handler = (type == 'col') ? activeSheet.insertCol : activeSheet.insertRow;
	else
		handler = (type == 'col') ? activeSheet.deleteCol : activeSheet.deleteRow;

	if (selStartCoord[0] == selEndCoord[0] && selStartCoord[0] == selEndCoord[0]) {
		var mrgInfo = activePane.getMergeInfo(selStartCoord[0], selStartCoord[1]);

		if (mrgInfo && mrgInfo[0])
			selEndCoord = [selStartCoord[0] + mrgInfo[1] - 1, selStartCoord[1] + mrgInfo[2] - 1];
	}

	var pos = (type == 'col') ? selStartCoord[0] : selStartCoord[1],
		cnt = (type == 'col') ? selEndCoord[0] - selStartCoord[0] + 1 : selEndCoord[1] - selStartCoord[1] + 1;

	handler.call(activeSheet, pos, cnt);

	env.copySelection.removeAll();
	Jedox.wss.app.clipboard = null;
	Jedox.wss.action.togglePaste(false);
}

// Resize Column/Row
Jedox.wss.action.resizeRowCol = function (type, size) {

	var env = Jedox.wss.app.environment,
			selStartCoord = env.lastRangeStartCoord,
			selEndCoord = env.lastRangeEndCoord;

	if (typeof size == 'number' && size >= 0)
		Jedox.wss.app.activeSheet.resizeColRow(type, [ [ selStartCoord[type], selEndCoord[type] ] ], size);
	else
		Jedox.wss.app.activeSheet.autofitColRow(type, [ [ selStartCoord[type], selEndCoord[type] ] ]);
}

// Switch Theme
Jedox.wss.action.switchTheme = function(btn, state) {
	if (!state)
		return;

	Ext.util.CSS.swapStyleSheet('theme', '../lib/ext/resources/css/x'.concat(btn.id, '.css'));

	function uncheck(item, index, length) {
		if (item.id != btn.id)
			item.setChecked(false);
	}

	Jedox.wss.app[Jedox.wss.app.menubar ? 'menubar' : 'toolbar'].themeMenu.items.each(uncheck);
}

// Merge Cells
Jedox.wss.action.mergeCells = function(unmerge) {
	var defSelActRng = Jedox.wss.app.environment.defaultSelection.getActiveRange(),
		defSelCoords = defSelActRng.getCorners();

	Jedox.wss.app.activePane.merge([defSelCoords[0].getX(), defSelCoords[0].getY(), defSelCoords[1].getX(), defSelCoords[1].getY()], unmerge);
}

// Clear range
Jedox.wss.action.clear = function(type) {
	var defSelActRng = Jedox.wss.app.environment.defaultSelection.getActiveRange(),
		defSelCoords = defSelActRng.getCorners();

	Jedox.wss.app.activePane.clrRange([defSelCoords[0].getX(), defSelCoords[0].getY(), defSelCoords[1].getX(), defSelCoords[1].getY()], type);
}

// Create new Workbook.
Jedox.wss.action.newWorkbook = function() {
	function cbCreate() {
		try {
			for (var triggers = Jedox.wss.events.triggers.newWorkbook_after, i = triggers.length - 1, name = Jedox.wss.app.activeBook._name; i >= 0; i--)
				triggers[i][0]['newWorkbook_after'].call(parent, triggers[i][1], name);
		} catch (e) {
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	}

	try {
		for (var triggers = Jedox.wss.events.triggers.newWorkbook_before, i = triggers.length - 1; i >= 0; i--)
			triggers[i][0]['newWorkbook_before'].call(parent, triggers[i][1]);

		Jedox.wss.book.create([this, cbCreate]);
	} catch (e) {
		Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
	}
}

Jedox.wss.action.adjustToACL = function() {
	// Currently Save is not supported in UserMode. Coming soon.
	if (Jedox.wss.app.appMode == Jedox.wss.grid.viewMode.USER)
		return;

	var perms = Jedox.wss.grid.permission,
		perm = perms.PERM_NONE,
		menubar = Jedox.wss.app.menubar,
		toolbar = Jedox.wss.app.toolbar,
		tbarLayouts = Jedox.wss.app.toolbarLayouts,
		wndActive = Jedox.wss.wnd.active;

	if (wndActive)
		perm = Jedox.wss.node.getPerm(wndActive.node);

	var act = perm >= perms.PERM_WRITE ? 'enable' : 'disable';

	switch (Jedox.wss.app.toolbarLayout) {
		case tbarLayouts.TOOLBAR:
			if (menubar.saveItem)
				menubar.saveItem[act]();

			menubar.saveAsItem[act]();
			break;

		case tbarLayouts.RIBBON:
			toolbar.saveAsItem[act]();
			break;
	}

	toolbar.saveItem[act]();
};

Jedox.wss.action.followHL = function(rngStr) {
	Jedox.wss.hl.exec(rngStr);
};

Jedox.wss.action.sendGridInput = function(event, keyCode) {
	var env = Jedox.wss.app.environment,
		gridMode = Jedox.wss.grid.GridMode,
		result = true;

	if (!env) return;

	if (event == undefined)
		event = {ctrlKey: false, shiftKey: false};

	if (keyCode == undefined)
		keyCode = 13;

	if(env.inputMode == gridMode.EDIT || env.inputMode == gridMode.INPUT)
		result = Jedox.wss.keyboard.sendInput(env.inputField, keyCode == 13 && event.ctrlKey && event.shiftKey);

	if (env.inputMode != gridMode.CNTRL && env.inputMode != gridMode.DIALOG) {
		if (result) {
			Jedox.wss.keyboard.cancelInput(keyCode == 9 ? false : true);

			try {
				Jedox.wss.app.currFormula.getEl().blur();
			} catch (e) {}
		} else {
			alert('Invalid input!'.localize());
			Jedox.wss.general.focusInputField();
		}
	}

	return result;
};

Jedox.wss.action.cancelGridInput = function() {
	var env = Jedox.wss.app.environment;

	if (env.viewMode == Jedox.wss.grid.viewMode.DESIGNER && env.inputMode == Jedox.wss.grid.GridMode.EDIT)
		Jedox.wss.app.currFormula.getEl().blur();

	Jedox.wss.keyboard.skipInpFldBlur = true;
	Jedox.wss.keyboard.cancelInput();
	env.editingDirectly = false;
};