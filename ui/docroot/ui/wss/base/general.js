/*
 * \brief general purpose routines
 *
 * \file general.js
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: general.js 5152 2011-07-28 10:02:33Z predragm $
 *
 */

Jedox.wss.general = new function ()
{
	var that = this,

			_l10nSeps = undefined,
			_l10nBool = undefined,
			_reNumeric = undefined,
			_reThouSep = undefined;

	this.startUp = function ()
	{
		_l10nSeps = Jedox.wss.i18n.separators;
		_l10nBool = Jedox.wss.i18n.bool;
		_reNumeric = new RegExp('^ *[0-9]{1,3}(?:\\'.concat(_l10nSeps[1], '?[0-9]{3})*(?:\\', _l10nSeps[0], '[0-9]+)? *$'));
		_reThouSep = new RegExp('\\'.concat(_l10nSeps[1]), 'g');

		if (Ext.isGecko)
			Jedox.wss.app.browser = 'ff';
		else if (Ext.isSafari)
			Jedox.wss.app.browser = 'sf';
		else if (Ext.isIE)
			Jedox.wss.app.browser = 'ie';
		else if (Ext.isChrome)
			Jedox.wss.app.browser = 'ch';

		Jedox.wss.app.UPRestrictMode = Jedox.wss.app.UPRestrictModeEnabled && Jedox.wss.app.appMode == Jedox.wss.grid.viewMode.USER && Jedox.wss.app.standalone;

		// join localization objects
		Ext.applyIf(Jedox.wss.i18n.strings, Jedox.wss.tmp.i18n_strings);
		delete Jedox.wss.tmp.i18n_strings;

		Jedox.gen.dynJSAutoload(Jedox.wss.app.dynJSRegistry);

		window.onresize = Jedox.wss.wspc.resize;
		window.onbeforeunload = function() {
			if (Jedox.wss.app.environment && Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER && Jedox.wss.app.activeSheet.isClone())
				Jedox.backend.wss.removeCloneWorksheet();
		};

		document.onkeydown = Jedox.wss.keyboard.checkGlobalInput;
		document.onkeyup = Jedox.wss.keyboard.fetchGlobalKeyUp;
		document.onmouseup = Jedox.wss.mouse.fetchGlobalMouseUp;
		document.onmousedown = Jedox.wss.mouse.fetchGlobalMouseDown;
		document.onmousemove = Jedox.wss.mouse.fetchGlobalMouseMove;

		Jedox.backend.wss = new Jedox.backend.rpc.WSS();
		Jedox.backend.studio = new Jedox.backend.rpc.Studio();

		if(!Jedox.wss.app.serverAvailable){
			//document.getElementsByTagName('body').style.display = 'none';
			alert("srvNotRespond".localize());
			return ;
		}

		Jedox.wss.app.mouseMovementObserver = new Jedox.gen.Observer();
		Jedox.wss.app.mouseUpObserver = new Jedox.gen.Observer();
		Jedox.wss.app.mouseDownObserver = new Jedox.gen.Observer();
		Jedox.wss.app.switchContextObserver = new Jedox.gen.Observer();

		Ext.QuickTips.init();

		var tbarLayouts = Jedox.wss.app.toolbarLayouts;
		switch (Jedox.wss.app.toolbarLayout) {
			case tbarLayouts.TOOLBAR:
				Jedox.wss.app.initMenuBar();
				Jedox.wss.app.initActiveToolbars();
				break;

			case tbarLayouts.RIBBON:
				Jedox.wss.app.initRibbon();
				break;
		}

		var isUserMode = Jedox.wss.app.appMode == Jedox.wss.grid.viewMode.USER;

		if (!isUserMode)
			Jedox.wss.app.initFormulaBar();

		Jedox.wss.app.initStatusBar();

		// Register PALO Handlers
		Jedox.palo.utils.registerHandlers();

		// register HB E-C handlers
		Jedox.wss.hb.regECHandlers();

		// Register Hyperlink handlers.
		Jedox.wss.mouse.regHyperlinkHandlers();

		Jedox.wss.app.screenPosition = [0, 0];

		// Load all workbooks loaded in core.
		var wbList = Jedox.backend.wss.getLoadedNodes(!isUserMode, Jedox.wss.app.UPRestrictMode),
			currWbId = Jedox.backend.wss.getCurrWbId();

		Jedox.wss.app.workbookList = wbList;

		if (opener != null && isUserMode) {
			try {
				opener.Jedox.wss.general.switchSuspendMode(true);
				Jedox.wss.app.userPreview = true;
			} catch (e) {}
		}

		function spawn (idx)
		{
			if (idx < 0)
				return that.startUp_post(currWbId);

			var wbMeta = wbList[idx].meta;

			if (wbMeta && wbMeta.v) {
				spawn(idx - 1);
				return;
			}

			Jedox.wss.node.spawn([ this, function () { spawn(idx - 1); } ], wbList[idx].type, wbList[idx].meta, wbList[idx].ext);
		}

		spawn(wbList.length - 1);
	};

	this.startUp_post = function (currWbId)
	{
		var wbList = Jedox.wss.app.workbookList,
			wbListLen = wbList.length,
			hasVisNode = false;

		if (currWbId != null && currWbId.length)
			Jedox.wss.book.select(currWbId);

		Jedox.wss.action.adjustToACL();

		if (wbListLen)
			for (var i = 0; i < wbListLen; i++)
				if (wbList[i].meta && !wbList[i].meta.v) {
					hasVisNode = true;
					break;
				}

		if (!wbList.length || !hasVisNode) {
			var preload = Jedox.backend.wss.getPreload();

			if (preload) {
				if (preload[1][1].frames) {
					// Preload Frameset.
					Jedox.wss.frameset.load_post(preload[1], null, {g: preload[0][1], h: preload[0][2], n: preload[0][0], v: false}, null, [null].concat(preload[0]));

				} else if (!preload[1][0]) {
					// Preload Workbook.
					if (!preload[1][1].search(/^recovery*/i))
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.recover, [preload[1][2], [null].concat(preload[0])]);
					else
						Jedox.wss.general.showMsg('Application Error'.localize(), 'errLoadWB_intro'.localize().concat(' ', preload[1][1].localize()), Ext.MessageBox.ERROR, [this, Jedox.wss.wnd.triggerCloseEvt, null, {g: preload[0][1], h: preload[0][2], n: preload[0][0]}]);
				}
			}
		}

		Jedox.wss.app.loaded = true;
	};

	/**
	 * same as setCoords() plus this function als updates to formula bar value.
	 */
	this.setCurrentCoord = function (book)
	{
		var activeBook = book ? book : Jedox.wss.app.activeBook,
				env = activeBook._aPane._env.shared,
				selCellCoords = env.selectedCellCoords,
				value = env.defaultSelection.getValue();

		env.inputField.value = value[0];

		Jedox.wss.app.currCoord.setValue(env.selectedRowName + env.selectedAbsColumnName);

		Jedox.wss.app.currFormula.setValue(value[1] != '' ? value[1] : that.filterHLTags(selCellCoords[0], selCellCoords[1], value[0], false));
	};

	this.setCoords = function (){// TODO: Check/Rewrite
		Jedox.wss.app.currCoord.setValue(Jedox.wss.app.numberToLetter[Jedox.wss.app.environment.selectedCellCoords[0]] + Jedox.wss.app.environment.selectedCellCoords[1]);
	};

	/**
	 * Sets global input mode var to specified value and updates status bar.
	 */
	this.setInputMode = function (inputMode) {
		var env = Jedox.wss.app.environment,
			activeBook = Jedox.wss.app.activeBook,
			sheetSel = activeBook ? activeBook.getSheetSelector() : undefined,
			modeDesc = '';

		function removeMarkRng() {
			if (env.copySelection != null) {
				env.copySelection.removeAll();
				Jedox.wss.app.clipboard = null;
				Jedox.wss.action.togglePaste(false);
			}
		}

		function saveInitVal() {
			Jedox.wss.app.updateUndoState([ 0, 0 ]);
			env.undoValue = env.inputField.value;
		}

		if(Jedox.wss.app.formulaTlb && inputMode != Jedox.wss.grid.GridMode.EDIT && inputMode != Jedox.wss.grid.GridMode.INPUT)
			Jedox.wss.app.formulaTlb.setMode(false);

		switch(inputMode){
			case Jedox.wss.grid.GridMode.EDIT:
				if (sheetSel) sheetSel.enable(false);
				removeMarkRng();
				saveInitVal();
				modeDesc = 'Edit';
				if (Jedox.wss.app.formulaTlb) Jedox.wss.app.formulaTlb.setMode(true);

				break;

			case Jedox.wss.grid.GridMode.INPUT:
				if (sheetSel) sheetSel.enable(false);
				removeMarkRng();
				saveInitVal();
				modeDesc = 'Enter';
				if (Jedox.wss.app.formulaTlb) Jedox.wss.app.formulaTlb.setMode(true);

				break;

			case Jedox.wss.grid.GridMode.POINT:
				modeDesc = 'Point';

				break;

			default:
				if (sheetSel) sheetSel.enable(true);
				Jedox.wss.app.updateUndoState();
				modeDesc = 'Ready';
		}

		if (env != null)
			env.inputMode = inputMode;

		Jedox.wss.app.statusBar.setInputMode(modeDesc);
	};

	/**
	 * Function is called when formula bar gets focus. It updates the formular bar with the value of input field
	 * @param {Object} event Mouse event which calls this function. obsolete
	 */
	this.mouseDownOnFormFld = function(event) {
		var env = Jedox.wss.app.environment;
		var range = env.defaultSelection;
		var gridMode = Jedox.wss.grid.GridMode;

		function cbMain() {
			Jedox.wss.app.fromFormulaField = true;
			Jedox.wss.app.lastInputField = Jedox.wss.app.currFormula;

			env.formulaSelection.activeToken = null;

			Jedox.wss.app.currFormula.focus();
		}

		function cbInputEdit() {
			Jedox.wss.keyboard.setFieldSize();
			cbMain();
		}

		if (env.inputMode == gridMode.INPUT) {
			that.setInputMode(gridMode.EDIT);
		} else {
			if (env.inputMode != gridMode.EDIT) {
				var value = range.getValue();
				env.inputField.value = value[1];
				that.setInputMode(gridMode.EDIT);

				Jedox.wss.keyboard.setFieldContent();
				that.showInputField([this, cbInputEdit], false, true);
				return;
			}
		}

		cbMain();
	};

	this.focusOnFormFld = function(event){
		Jedox.wss.keyboard.setFieldSize();
	};

	this.focusInputField = function (){
		if (Jedox.wss.app.fromFormulaField)
			Jedox.wss.app.currFormula.focus();
		else {
			var inputField = Jedox.wss.app.environment.inputField,
				fieldLen = inputField.value.length;

			inputField[Ext.isSafari ? 'select' : 'focus']();

			if (document.all) {
				var selRng = document.selection.createRange();
				selRng.move('character', fieldLen);
				selRng.select();
			} else
				inputField.setSelectionRange(fieldLen, fieldLen);
		}
	};

	this.isRngSingleCell = function() {
		var env = Jedox.wss.app.environment;
		var rngStartCoords = env.lastRangeStartCoord;
		var rngEndCoords = env.lastRangeEndCoord;

		return (rngStartCoords[0] == rngEndCoords[0] && rngStartCoords[1] == rngEndCoords[1]);
	};

	this.updateInputFieldPosition = function () {
		var activeSheet = Jedox.wss.app.activeSheet,
			inputField = Jedox.wss.app.environment.inputField,
			cursorField = activeSheet._defaultSelection ? activeSheet._defaultSelection.getCursorField() : activeSheet._cursorField,
			cfPos = cursorField.getPosition();

		if (this.isRngSingleCell()) {
			inputField.style.left = cfPos.l + (document.all ? 0 : 1) + 'px';
			inputField.style.top = cfPos.t + (document.all ? 0 : 0) + 'px';
		} else {
			inputField.style.left = cfPos.l + (document.all ? 3 : 1) + 'px';
			inputField.style.top = cfPos.t + (document.all ? 3 : 0) + 'px';
		}

		inputField.style.height = cursorField.getSize().h + 'px';
	};

	this.showInputField = function (cb, moveToFirstChar, directly, fetchFormula, skipFetchValue) {
		var env = Jedox.wss.app.environment,
			activeBook = Jedox.wss.app.activeBook,
			activePane = Jedox.wss.app.activePane,
			vMode = Jedox.wss.grid.viewMode,
			inputField = env.inputField,
			selectedCell = env.selectedCell,
			selectedCellCoords = env.selectedCellCoords,
			extraXOffset = (Jedox.wss.app.isIE) ? 1 : 0,
			extraYOffset = (Jedox.wss.app.isIE) ? 1 : 0,
			myPosition, oldValue = null,
			calculatedCellContent = false,
			selectedCellValue = env.selectedCellValue,
			selCellValue = activePane.getCellUVal(selectedCellCoords[0], selectedCellCoords[1]),
			selCellFormula = activePane.getCellFormula(selectedCellCoords[0], selectedCellCoords[1]);

		if (!skipFetchValue) {
			selectedCellValue = env.selectedCellValue = (selCellValue == undefined) ? '' : selCellValue;
			env.selectedCellFormula = (selCellFormula == undefined) ? '' : selCellFormula;
		}

		fetchFormula = (fetchFormula == undefined) ? true : fetchFormula;

		inputField.style.visibility = 'hidden';

		function delArrForm(formVal) {
			if (formVal.charAt(0) == '{' && formVal.charAt(formVal.length - 1) == '}') {
				oldValue = formVal;
				formVal = formVal.substring(1, formVal.length - 1);
			}

			return formVal;
		}

		var cbScrollTo = function() {
			env.editingDirectly = directly;

			if (env.viewMode == vMode.USER) {
				inputField.style.top = selectedCell.parentNode.offsetTop - 1 + 'px';
				inputField.style.left = selectedCell.offsetLeft - 1 + 'px';

				inputField.style.width = selectedCell.offsetWidth - 3 + 'px';
				inputField.style.height = selectedCell.offsetHeight - 4 + 'px';
			} else {
				that.updateInputFieldPosition();
				inputField.style.height = selectedCell.offsetHeight - (that.isRngSingleCell() ? 4 : 5) + 'px';
				inputField.style.borderStyle = 'none';
			}

			var selFormulaSet = (env.selectedCellFormula != 'null' && env.selectedCellFormula.length > 0);

			if (fetchFormula && env.viewMode == vMode.DESIGNER && !selFormulaSet) {
				var rngFormulaVal = env.defaultSelection.getValue()[1];

				if (rngFormulaVal != env.selectedCellFormula) {
					env.selectedCellFormula = rngFormulaVal;
					selFormulaSet = true;
				}
			}

			inputField.value = env.viewMode == vMode.DESIGNER && selFormulaSet ? delArrForm(env.selectedCellFormula) :
				(selectedCellValue.length ? that.filterHLTags(selectedCellCoords[0], selectedCellCoords[1], selectedCellValue, false) : ' ');

			Jedox.wss.style.cellTransfer(inputField);

			var c = selectedCellCoords[0], r = selectedCellCoords[1];
			if (inputField.style.textAlign == '' && (activePane.getCellValue(c, r) == undefined || activePane.getCellFormula(c, r) != undefined))
				inputField.style.textAlign = 'left';

			inputField.style.zIndex = '40';
			inputField.style.display = 'block';
			inputField.style.visibility = 'visible';
			inputField._paneId = activePane._id;

			if (moveToFirstChar) {
				// Move cursor to the first position:
				if (document.all) {
					var selRng = document.selection.createRange();
					selRng.move('character', 0);
					selRng.select();
				} else
					inputField.setSelectionRange(0,0);
			}

			if (env.viewMode != vMode.USER)
				Jedox.wss.keyboard.setFieldContent();
			else
				Jedox.wss.keyboard.setFieldSize();

			env.oldValue = (oldValue == null) ? inputField.value : oldValue;
			env.lastInputValue = inputField.value;

			if (selectedCellValue.length == 0 && !selFormulaSet) {
				inputField.value = '';

				if (env.viewMode == vMode.DESIGNER)
					Jedox.wss.app.currFormula.setValue('');
			}

			that.focusInputField();

			if (cb instanceof Array && cb.length > 1)
				cb[1].call(cb[0]);
		};

		if (env.viewMode == vMode.DESIGNER) {
			if (activeBook._scrollPending)
				return;

			activeBook._aSheet._defaultSelection.getCursorField().hide();
			activePane.scrollTo([this, cbScrollTo], selectedCellCoords[0], selectedCellCoords[1], false, false);
		} else
			cbScrollTo();
	};

	// USED
	this.addFileMenuEntry = function(entryText) {// TODO: Check/Rewrite
		var fixedItemsCount = (Jedox.wss.app.appMode == Jedox.wss.grid.viewMode.USER) ? 8 : 13;
		var itemName = (entryText.length > 30) ? (entryText.substring(0, 14) + '...' + entryText.substring(entryText.length - 9)) : entryText;
		var menuPosition = Jedox.wss.app.menubar.fileMenu.items.length - fixedItemsCount + 1;

		Jedox.wss.app.menubar.fileMenu.add({
			text: menuPosition + '. ' + itemName + '.wss',
			href: "javascript: Jedox.wss.book.load(null,'"+entryText+"');"
		});
	};

	this.createWorksheetElements = function ()
	{
		function _load (res)
		{
			if (!(res instanceof Array) || res[0] !== true)
				return;

			res = res[1];

			for (var chartData, i = res.length - 1, createChart = Jedox.wss.wsel.chart.createChart; i >= 0; --i)
				createChart((chartData = res[i]).e_id, chartData.n_location, chartData.pos_offsets, chartData.size, chartData.subtype, chartData.zindex, chartData.locked, chartData.chart_name);
		}

		Jedox.backend.ccmd([ this, _load ], [ 'wget', '', [], [ 'e_id', 'size', 'subtype', 'n_location', 'pos_offsets', 'zindex', 'locked', 'chart_name' ], { e_type: 'chart' } ]);
	};

	this.getSysClipboard = function() {
		var pasteFld = document.getElementById("_paste_field_");
		return (pasteFld == null) ? null : document.getElementById("_paste_field_").value;
	};

	this.setSysClipboard = function(value) {
		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			that.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
			if (!document.getElementById("_copy_field_")) {
				_cinput = document.createElement("textarea");
				_cinput.setAttribute("id", "_copy_field_");
				_cinput.setAttribute("name", "_copy_field_");
				_cinput.setAttribute("style", "position: float; width: 1px; height: 1px; user-select: text; -moz-user-select: text; -webkit-user-select: text; z-index: 999;");
				_cinput.setAttribute("value", "1");
				document.getElementById("mainBody").appendChild(_cinput);
			}
		if (Jedox.wss.app.browser=='ie') {
			var copyfld = document.getElementById("_copy_field_");
			copyfld.value = value;
			copyfld.select();
			document.selection.createRange();
		}
		else {
			var copyfld = document.getElementById("_copy_field_");
			copyfld.value = value;
			copyfld.select();
			copyfld.selectionStart = 0;
			copyfld.selectionEnd = 65535;
		}
	};

	this.parseSysClipboard = function(flat) {
		var	clpVal = this.getSysClipboard();

		if (clpVal == null)
			return clpVal;

		var rows = clpVal.split('\n'),
			maxRowLen = 0;

		for (var i = rows.length - 1, subLen; i >= 0; i--) {
			rows[i] = rows[i].split('\t');

			subLen = rows[i].length;

			if (subLen > maxRowLen)
				maxRowLen = subLen;
		}

		if (rows[rows.length - 1] == '')
			rows.splice(rows.length - 1, 1);

		for (var i = rows.length - 1; i >= 0; i--)
			for (var j = 0, cnt = maxRowLen - rows[i].length; j < cnt; j++)
				rows[i].push('');

		if (flat) {
			var flatRows = [];

			for (var i = 0, rowsLen = rows.length; i < rowsLen; i++)
				if (rows[i] instanceof Array)
					for (var j = 0, subLen = rows[i].length; j < subLen; j++)
						flatRows.push(rows[i][j]);
				else
					flatRows.push(rows[i]);
		}

		return {
			id: null,
			op: null,
			value: flat ? flatRows : rows,
			markRngDim: {width: maxRowLen, height: rows.length}
		}
	};

	this.filterHLTags = function(x, y, val, addTags) {

		if (Jedox.wss.app.activeBook == undefined)
			return val;

		var valType = Jedox.wss.app.activePane.getCellType(x, y),
			hlTag = Jedox.wss.hl.hlTag;

		if (addTags) {
			if (valType == 'h' && val.search(/^=HYPERLINK\(/))
				return hlTag.begin.concat(val, hlTag.end);
		} else if (valType == undefined || valType == 'h') {
			var bStrs = [hlTag.oldBegin, hlTag.begin];

			for (var bStr in bStrs)
				if (val.indexOf(bStrs[bStr]) == 0)
					return val.replace(bStrs[bStr], '').replace(hlTag.end, '');
		}

		return val;
	};

	this.switchSuspendMode = function(status) {
		if (status) {
			if (!that.switchSuspendModeAlert) {
				that.switchSuspendModeAlert = new Ext.Window({
			        title: 'Suspend Mode'.localize(),
					id: 'ext-el-mask-suspend-win',
					cls: 'default-format-window',
			        closable: false,
			        autoDestroy: true,
			        plain: true,
					draggable: false,
			        constrain: true,
			        modal: true,
			//		ctCls: 'ext-el-mask-suspend-win',
			        resizable: false,
			        animCollapse: false,
			        width: 400,
			        autoHeight: true,
			        layout: 'fit',
			        items: [
						new Ext.Panel({
					        bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
					        border: false,
					        frame: false,
							autoHeight: true,
							layout: 'fit',
							items: [{html: 'suspModeMsg'.localize(), baseCls: 'x-plain'}]
						})
					]
			    });

				Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
				that.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
				that.switchSuspendModeAlert.show(this);
			}
		} else if (that.switchSuspendModeAlert) {
			var ha = Jedox.backend.wss,
					activeBook = Jedox.wss.app.activeBook,
					activeSheet = Jedox.wss.app.activeSheet;

			ha.selectBook(activeBook.getUid());
			ha.selectSheet(activeBook.getWsId(), activeSheet.isClone());

			that.setInputMode(Jedox.wss.app.lastInputModeDlg);
			Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			Jedox.wss.sheet.refresh();

			that.switchSuspendModeAlert.destroy();
			that.switchSuspendModeAlert = null;
		}
	};

	this.appUnload = function() {
		var env = Jedox.wss.app.environment;

		if (env && env.viewMode == Jedox.wss.grid.viewMode.USER) {
			try {
				opener.Jedox.wss.general.switchSuspendMode(false);
			} catch (e) {}
		}

		document.getElementById('mainBody').style.display = 'none';
	};

	this.showMsg = function(title, msg, dlgIcon, cb) {
		var env = Jedox.wss.app.environment;

		function resetInput() {
			if (env && env.inputMode == Jedox.wss.grid.GridMode.DIALOG) {
				that.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}

			if (cb instanceof Array && cb.length > 1)
				cb[1].apply(cb[0], cb.slice(2));
		}

		// Change input mode to DILAOG.
		if (env && env.inputMode != Jedox.wss.grid.GridMode.DIALOG) {
			Jedox.wss.app.lastInputModeDlg = env.inputMode;
			that.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		Ext.MessageBox.show({
			title: title,
			msg: msg,
			icon: dlgIcon,
			modal: true,
			buttons: Ext.MessageBox.OK,
			fn: resetInput
		});
	};


	this.showLogMsg = function (title, msg, dlgIcon, value, cb){

		var env = Jedox.wss.app.environment;

		function resetInput() {
			if (env && env.inputMode == Jedox.wss.grid.GridMode.DIALOG) {
				that.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}

			if (cb instanceof Array && cb.length > 1)
				cb[1].apply(cb[0], cb.slice(2));
		}

		// Change input mode to DILAOG.
		if (env && env.inputMode != Jedox.wss.grid.GridMode.DIALOG) {
			Jedox.wss.app.lastInputModeDlg = env.inputMode;
			that.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		Ext.MessageBox.show({
			title: title,
			msg: msg,
			icon: dlgIcon,
			modal: true,
			width:400,
			buttons: Ext.MessageBox.OK,
			fn: resetInput,
            prompt:true,
            multiline: true,
			value:value
		});
	}

	this.chkState = function() {
		var env = Jedox.wss.app.environment;

		if (env && env.inputMode.inputMode == Jedox.wss.grid.GridMode.DIALOG)
			throw {key: 'wb_in_dlg_mode', params: {}};

		if (that.switchSuspendModeAlert)
			throw {key: 'wb_in_suspend_mode', params: {}};
	};

	this.chkHiddenColRow = function(isRow, pos, amount, isInc) {
		var dim = isRow ? Jedox.wss.app.activeSheet._rowHeights : Jedox.wss.app.activeSheet._colWidths,
			maxCoords = Jedox.wss.grid.defMaxCoords[isRow ? 1 : 0],
			dirIdx = isInc ? 1 : -1,
			foundUnhidden = false;

		for (var i = pos + amount * dirIdx; isInc ? i <= maxCoords : i >= 0; i += dirIdx)
			if (dim.getElemAt(i) > 0) {
				foundUnhidden = true;
				break;
			}

		return foundUnhidden ? (isInc ? pos + (i - pos) : pos - (pos - i)) : pos;
	};

	this.syncCtrls = function ()
	{
		var activeSheet = Jedox.wss.app.activeSheet;

		if (Jedox.wss.app.appMode == Jedox.wss.grid.viewMode.DESIGNER)
		{
			if (Jedox.wss.app.environment)
			{
				if (activeSheet == undefined || !activeSheet.isClone())
				{
					Jedox.wss.hb.syncCntrl(false);
					Jedox.wss.hb.enaDisHBAdd('enable');
				}
				else
				{
					Jedox.wss.hb.syncCntrl(true);
					Jedox.wss.hb.enaDisHBAdd('disable');
				}
			}
		}
	};

	this.loadRecent = function (item)
	{
		var conf = item.initialConfig;

		try
		{
			for (var triggers = Jedox.wss.events.triggers.openWorkbook_before, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['openWorkbook_before'].call(parent, triggers[i][1], conf._ghn, conf.text, false);

			Jedox.wss.node.load(null, conf._type, conf._ghn.n, conf._ghn.g, conf._ghn.h);

			for (var triggers = Jedox.wss.events.triggers.openWorkbook_after, i = triggers.length - 1; i >= 0; i--)
				triggers[i][0]['openWorkbook_after'].call(parent, triggers[i][1], conf._ghn, conf.text);
		}
		catch (e)
		{
			Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
		}
	};

	this.showRecent = function (res, menu, alignEl, alignPos, parentMenu)
	{
		menu.removeAll();

		var icons = { spreadsheet: 'w3s_workbook', frameset: 'w3s_frameset' },
				types = { spreadsheet: 'workbook', frameset: 'frameset' };

		for (var item, lctn, name, i = res.length - 1; i >= 0; --i)
		{
			item = res[i];
			lctn = item.location;
			name = lctn.path.substr(lctn.path.lastIndexOf('/') + 1);

			menu.addMenuItem({
			  _type: types[item.type]
			, _ghn: { g: lctn.group, h: lctn.hierarchy, n: lctn.node }
			, text: name
			, iconCls: icons[item.type]
			, qtip: lctn.path
			, listeners: { afterrender: function () { Ext.QuickTips.register({ target: this.getEl(), text: this.initialConfig.qtip, showDelay: 500 }); } }
			, handler: this.loadRecent
			});
		}

		menu.loaded = true;
		menu.show(alignEl, alignPos, parentMenu);
	};

	this.autoCalc = function (state)
	{
		var conn = Jedox.backend;

		conn.ccmd(true, [ 'sac', state ? 1 : 0 ]);

		Jedox.wss.app.autoCalc = state;
	};

	// Core2 version
//	this.str2var = function (str)
//	{
//		if (str === '' || str === null || str === undefined)
//			return { v: '', t: 'e' };
//
//		if (typeof str != 'string')
//			return { v: str };
//
//		var n, n_l10n;
//
//		if (str.match(_reNumeric) !== null && (n_l10n = str.replace(_reThouSep, '')) && !isNaN(n = _l10nSeps[0] != '.' ? n_l10n.replace(_l10nSeps[0], '.') : n_l10n))
//			return { v: n * 1, t: 'n', l10n: n_l10n };
//
//		if (str.toUpperCase() == _l10nBool[true])
//			return { v: true, t: 'b', str: _l10nBool[true] };
//
//		if (str.toUpperCase() == _l10nBool[false])
//			return { v: false, t: 'b', str: _l10nBool[false] };
//
//		return { v: str, t: str[0] == '<' && /\w/.test(str[1]) ? 'h' : 's' };
//	};

	// Core3 version
	this.str2var = function (str)
	{
		if (str === '' || str === null || str === undefined)
			return { v: '', t: 'e' };

		if (typeof str != 'string')
			return { v: str };

		var n, n_l10n;

		if (str.match(_reNumeric) !== null && (n_l10n = str.replace(_reThouSep, '')) && !isNaN(n = _l10nSeps[0] != '.' ? n_l10n.replace(_l10nSeps[0], '.') : n_l10n))
			return { v: str, t: 'n', l10n: n_l10n };

		if (str.toUpperCase() == _l10nBool[true])
			return { v: str, t: 'b', str: _l10nBool[true] };

		if (str.toUpperCase() == _l10nBool[false])
			return { v: str, t: 'b', str: _l10nBool[false] };

		return { v: str, t: str[0] == '<' && /\w/.test(str[1]) ? 'h' : 's' };
	};

};

Jedox.wss.format.getSample = function (format, val)
{
	var numericSeps = Jedox.wss.i18n.separators, l10nBool = Jedox.wss.i18n.bool, reThouSep = new RegExp('\\'.concat(numericSeps[1]), 'g'),
			num = numericSeps[0] != '.' ? val.replace(reThouSep, '').replace(numericSeps[0], '.') : val.replace(reThouSep, ''),
			res;

	if (val === '' || val === null || val === undefined)
		val = '';
	else if (!isNaN(num))
		val = num * 1;
	else if (val.toUpperCase() == l10nBool[true])
		val = true;
	else if (val.toUpperCase() == l10nBool[false])
		val = false;

	res = Jedox.backend.ccmd(0, [ 'gfs', format, val ])[0];

	return typeof res == 'object' && res[0] == true ? res[1] : '';
};
