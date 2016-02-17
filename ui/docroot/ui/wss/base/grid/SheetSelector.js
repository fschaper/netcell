/*
 * \brief class representing workbook sheet selector
 *
 * \file SheetSelector.js
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: SheetSelector.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.grid.SheetSelector = function (winId, book)
{
	var that = this,
			_sheetSelOC = document.getElementById(winId.concat('_sheetSelectorOC')),
			_sheetList = [],
			_handleTabChange = true,
			_handleEvent = true,
			_loadMark = false,
			_activeSheetId,
			_tabView,
			_toolbar;

	this.actionTypes =
	{
	  NONE: 0
	, SELECTED: 1
	, ADDED: 2
	, REMOVED: 3
	, COPIED: 4
	, MOVED: 5
	, UNCLONED: 6
	};

	this.action = that.actionTypes.NONE;
	this.actionData = undefined;

	function _posById (sheetId)
	{
		for (var i = _sheetList.length - 1; i >= 0; --i)
			if (_sheetList[i].id == sheetId)
				return i;

		return -1;
	}

	function _posByName (sheetName)
	{
		for (var i = _sheetList.length - 1; i >= 0; --i)
			if (_sheetList[i].title == sheetName)
				return i;

		return -1;
	}

	function _tabById (sheetId)
	{
		for (var i = _sheetList.length - 1; i >= 0; --i)
			if (_sheetList[i].id == sheetId)
				return _sheetList[i];

		return false;
	}

	this.readWorksheets = function ()
	{
		_handleTabChange = false;

		var sheetUids = book._sheetUids;

		for (var sheetUid in sheetUids)
		{
			var tab = _tabView.add({
				id: sheetUid,
				title: sheetUids[sheetUid],
				html: '',
				closable: false,
				cls: 'extbottomtab'
			}).show();

			_sheetList.push(tab);
		}

		if (book._viewMode != Jedox.wss.grid.viewMode.USER)
		{
			_tabView.add({
				id: 'addSheet',
				cls: 'addsheet',
				title: '&nbsp;',
				html: '',
				iconCls: 'newtab',
				closable: false
			}).show();
		}

		_activeSheetId = book._aSheetUid;
		_tabView.setActiveTab(_activeSheetId);

		_handleTabChange = _handleEvent = true;
	}

	this.selectFirstSheet = function ()
	{
		book.select();

		_tabView.setActiveTab(0);
	}

	this.selectPreviousSheet = function ()
	{
		book.select();

		var curPos = _posById(_activeSheetId);

		if (curPos > 0)
			_tabView.setActiveTab(--curPos);
	}

	this.selectNextSheet = function ()
	{
		book.select();

		var curPos = _posById(_activeSheetId);

		if (curPos < _sheetList.length - 1)
			_tabView.setActiveTab(++curPos);
	}

	this.selectLastSheet = function ()
	{
		book.select();

		_tabView.setActiveTab(_sheetList.length - 1);
	}

	function _selectByPos (pos)
	{
		if (pos < 0)
			return false;

		_tabView.setActiveTab(pos);

		return true;
	}

	this.selectByName = function (sheetName)
	{
		if (sheetName == '')
			return true;

		var selRes = _selectByPos(_posByName(sheetName));;

		if (selRes)
			_activeSheetId = this.getIdByName(sheetName);

		return selRes;
	}

	this.selectById = function (sheetId, loadMark)
	{
		if (sheetId == '')
			return true;

		_loadMark = loadMark;

		var selRes = _selectByPos(_posById(sheetId));

		if (selRes)
			_activeSheetId = sheetId;

		return selRes;
	}

	this.getLoadMark = function (doReset)
	{
		var lm = _loadMark;

		if (doReset)
			_loadMark = false;

		return lm;
	}

	this.getActiveSheetId = function ()
	{
		return _activeSheetId;
	}

	this.getActiveSheetName = function (check4quotes)
	{
		var sheetName = _tabById(_activeSheetId).title;
		return check4quotes? sheetName.indexOf(' ') >= 0?  '\''.concat(sheetName, '\''):sheetName:sheetName;
	}

	this.getIdByName = function (sheetName)
	{
		for (var i = _sheetList.length - 1; i >= 0; --i)
			 if (_sheetList[i].title == sheetName)
				 return _sheetList[i].id;

		return false;
	}

	this.insertEntry = function (sheetName, sheetId, nextSheetId)
	{
		if (typeof nextSheetId == 'string' && nextSheetId.length > 0)
		{
			var sheetPos = _posById(nextSheetId),
					pos;

			if (sheetPos >= 0)
				pos = sheetPos;
		}
		else
			var pos = _sheetList.length;

		var tab = _tabView.insert(pos, {
			id: sheetId,
			title: sheetName,
			html: '',
			closable: false,
			cls: 'extbottomtab'
		}).show();

		_sheetList.splice(pos, 0, tab);

		_activeSheetId = sheetId;
	}

	this.addSheet = function (nextSheetId)
	{
		_handleTabChange = _handleEvent = false;

		that.action = that.actionTypes.ADDED;
		that.actionData = nextSheetId == undefined ? '' : nextSheetId;

		book._actOnSheetSel();
	}

	this.removeSheet = function (sheetId)
	{
		if (_sheetList.length < 2)
		{
			Ext.MessageBox.show({
				title: 'Delete Worksheet'.localize(),
				msg: 'delLastWorksheet'.localize(),
				icon: Ext.MessageBox.WARNING,
				modal: true,
				buttons: Ext.MessageBox.OK
			});

			return;
		}

		that.action = that.actionTypes.REMOVED;
		that.actionData = sheetId;

		var pos = _posById(sheetId);

		_tabView.setActiveTab(pos + 1 == _sheetList.length ? pos - 1 : pos + 1);
		_tabView.remove(_sheetList[pos]);
		_sheetList.splice(pos, 1);
	}

	this.copySheet = function (wsId, nextSheetId, wbId)
	{
		_handleTabChange = _handleEvent = false;

		that.action = that.actionTypes.COPIED;
		that.actionData = { wsId: wsId, nextSheetId: nextSheetId, wbId: wbId };

		book._actOnSheetSel();
	}

	this.moveSheet = function (wsId, nextSheetId, wbId)
	{
		var toOtherWB = typeof wbId == 'string' && wbId.length;

		if (toOtherWB && _sheetList.length < 2)
		{
			Ext.MessageBox.show({
				title: 'Move Worksheet'.localize(),
				msg: 'moveLastWorksheet'.localize(),
				icon: Ext.MessageBox.WARNING,
				modal: true,
				buttons: Ext.MessageBox.OK
			});

			return;
		}

		var pos = _posById(wsId);

		if (toOtherWB)
			_tabView.setActiveTab(pos + 1 == _sheetList.length ? pos - 1 : pos + 1);

		_handleTabChange = _handleEvent = false;

		_tabView.remove(_sheetList[pos]);
		_sheetList.splice(pos, 1);

		that.action = that.actionTypes.MOVED;
		that.actionData = { wsId: wsId, nextSheetId: nextSheetId, wbId: wbId };

		book._actOnSheetSel();
	}

	this._refresh = function ()	// SheeetSelector position & rendering fix for Safari
	{
		if (Jedox.wss.app.browser == 'sf')
			_tabView.render(winId + '_sheetSelectorIC');
	}

	this.enable = function (enable)
	{
		_handleTabChange = _handleEvent = enable != false;
	}

	this.freeze = function (freeze)
	{
		_handleEvent = freeze == false;
	}

	this.setWidth = function (width)
	{
		_sheetSelOC.style.width = ''.concat(width, 'px');
		_tabView.setWidth(width - _toolbar.getSize().width);
	}

	this.disableAddTab = function () {
		_tabView.getItem(_sheetList.length).disable();
	}

	this.enableAddTab = function () {
		_tabView.getItem(_sheetList.length).enable();
	}

	function _showContextMenu (tabPanel, tab, ev)
	{
		book.select();

		if (tab.id == 'addSheet' || book._viewMode != Jedox.wss.grid.viewMode.DESIGNER || Jedox.wss.app.sourceSel)
			return;

		tabPanel.activate(tab);

		var contextMenu = new Ext.menu.Menu({
    		id: 'chartContextMenu',
    		cls: 'default-format-window',
    		enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
    		items: [
				{ text: 'Insert'.localize(), handler: function() { that.addSheet(tab.id); } },
				{ text: 'Delete'.localize(), iconCls: 'delete_sheet', handler: function() { that.removeSheet(tab.id); } },
				{ text: 'Rename'.localize(), handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.renameSheet, [ tab.id, tab.title ]); } },
				{ text: 'Move or Copy'.localize().concat('...'), handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.sheetMoveCopy); } }
			]
		});

		contextMenu.showAt(ev.getPoint());
	}

	function _beforeTabChange (tabPanel, newTab, currTab)
	{
		book.select();

		return _handleEvent;
	}

	function _onTabChange (tabPanel, tab)
	{
		if (!_handleTabChange)
			return;

		var sourceSel = Jedox.wss.app.sourceSel;

		if (tab.getId() == 'addSheet') {
			if (sourceSel)
				return;
			else
				return that.addSheet();
		}

		_handleTabChange = _handleEvent = false;

		var env = book._aPane._env.shared,
			gridMode = Jedox.wss.grid.GridMode;

		switch (env.inputMode) {
			case gridMode.INPUT:
				Jedox.wss.keyboard.sendInput(env.inputField, false);
				break;

			case gridMode.CNTRL:
				Jedox.wss.general.setInputMode(gridMode.READY);
				break;
		}

		Jedox.wss.app.switchContextObserver.notify(this);

		env.inputField.style.display = 'none';

		function cbTabChange() {
			_activeSheetId = tab.getId();

			if (that.action == that.actionTypes.NONE)
				that.action = that.actionTypes.SELECTED;

			book._actOnSheetSel(sourceSel ? [ this, function () { sourceSel.afterSheetChange(this.getActiveSheetName()); }, [false] ] : null);
		}

		if (sourceSel)
			sourceSel.beforeSheetChange([this, cbTabChange], this.getActiveSheetName());
		else
			cbTabChange();
	}

	this.getToolbar = function ()
	{
		return _toolbar;
	};

	this.getTabPanel = function ()
	{
		return _tabView;
	};

	_toolbar = new Ext.Toolbar({
		cls: 'extsheetselector',
		renderTo: winId + '_sheetSelectorTB'
	});

	_toolbar.add(
		{ iconCls: 'shsel_first', scale: 'xsmall', tooltip: 'First Sheet'.localize(), handler: that.selectFirstSheet },
		{ iconCls: 'shsel_prev', scale: 'xsmall', tooltip: 'Previous Sheet'.localize(), handler: that.selectPreviousSheet },
		{ iconCls: 'shsel_next', scale: 'xsmall', tooltip: 'Next Sheet'.localize(), handler: that.selectNextSheet },
		{ iconCls: 'shsel_last', scale: 'xsmall', tooltip: 'Last Sheet'.localize(), handler: that.selectLastSheet }
	);



	_toolbar.doLayout();

 	_tabView = new Ext.TabPanel({
		cls: 'extsheettabs',
		renderTo: winId + '_sheetSelectorIC',
		resizeTabs: false,
		minTabWidth: 70,
		tabWidth: 90,
		enableTabScroll: true,
		height: 0,
		tabPosition: 'bottom',
		collapsed: false,
		bodyBorder: false,
		border: false,
		hideBorders: true,
		autoWidth: true,
		autoScroll: true,
		footerStyle: 'border-width: 0px',
		listeners: {
			tabchange: { fn: _onTabChange, scope: this },
			beforetabchange: { fn: _beforeTabChange, scope: this },
			contextmenu: { fn: _showContextMenu, scope: this }
		}
	});

	_tabView.getEl().on({
			mouseover: { fn: function() { Jedox.wss.app.showBrowserCtx = true; }, scope: this },
			mouseout: { fn: function() { Jedox.wss.app.showBrowserCtx = false; }, scope: this }
	});
}
