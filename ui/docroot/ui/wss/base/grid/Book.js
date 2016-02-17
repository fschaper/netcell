/*
 * \brief class Book representing workbook
 *
 * \file Book.js
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
 * SVN: $Id: Book.js 5035 2011-06-06 14:12:12Z predragm $
 *
 */

Jedox.wss.grid.Book = (function ()
{
	// private static fields
	var _id = 0;

	// private static methods

	// class constructor
	return function (cb, holder, uid, name, meta, opts)
	{
		var that = this;
		this._initted = false;

		this.holder = holder; this.id = ++_id; this.uid = uid; this._domId = holder._domId.concat('B', holder.getDomCnt('B')); this.dom = holder.getDom();
		this._name = name; this._meta = meta; this._opts = opts || {}; this._domCnts = {};
		this.scrollObserver = new Jedox.gen.Observer();


		// aliases
		this._viewMode = Jedox.wss.app.appMode; this._app = Jedox.wss.app; this._jwgrid = Jedox.wss.grid; this._jwbook = Jedox.wss.book; this._jwstyle = Jedox.wss.style;
		this._jwgen = Jedox.wss.general; this._json = Ext.util.JSON; this._conn = Jedox.backend; this._ha = Jedox.backend.wss;
		this._gmode_edit = this._viewMode == this._jwgrid.viewMode.DESIGNER;


		// opts
		this._marginHeight = !this._gmode_edit && this._opts.hideHorScrollbar == 'yes' && this._opts.hideSheetSelector == 'yes' ? 0 : 17;
		this._marginWidth = !this._gmode_edit && this._opts.hideVertScrollbar == 'yes' ? 0 : 17;


		// scrolling
		this._scrollPending = false;

		this._scrollDirectionMap = [];
		var scrollDir = this._jwgrid.ScrollDirection;
		this._scrollDirectionMap[scrollDir.UP] = [ this._SCROLL_VERT, this._SCROLL_RWD ];
		this._scrollDirectionMap[scrollDir.DOWN] = [ this._SCROLL_VERT, this._SCROLL_FWD ];
		this._scrollDirectionMap[scrollDir.LEFT] = [ this._SCROLL_HORIZ, this._SCROLL_RWD ];
		this._scrollDirectionMap[scrollDir.RIGHT] = [ this._SCROLL_HORIZ, this._SCROLL_FWD ];


		// generate content
		this._genContentEl();


		// scrollbars
		this._hsOCs = [ document.getElementById(this._domId.concat('_hs0')), document.getElementById(this._domId.concat('_hs1')) ];
		this._vsOCs = [ document.getElementById(this._domId.concat('_vs0')), document.getElementById(this._domId.concat('_vs1')) ];
		this._scrolls = [ this._hScrolls = {}, this._vScrolls = {} ]; this._hsCoef = 0.4;


		// sheets
		this._sheetsOC = document.getElementById(this._domId.concat('_sheets'));
		this._sheetCnt = 0;
		this._sheets = {};


		// cell comments
		this._dynCc = null;


		// sheet selector
		this._sheetSelOC = document.getElementById(this._domId.concat('_sheetSelectorOC'));
		this._sheetSelector = new Jedox.wss.grid.SheetSelector(this._domId, this);

		if (!this._gmode_edit && (this._opts.hideSheetSelector == 'yes' || (Jedox.wss.app.UPRestrictMode && Jedox.wss.app.userPreview)))
		{
			this._sheetSelOC.style.visibility = 'hidden';
			this._sheetSelOC.style.height = '0px';
		}


		this._fit();


		// select as active
		this._jwbook.reg[this.id] = this;
		this._select();


		// fetch sheet list
		this._conn.ccmdSetBuff('[["olst",2],["olst",3],["ocurr",2],["bget","",[],[],{"e_type":"conf"}]]');
		this._conn.ccmdFlush([ this, this._init_post, cb ]);
	};
}
)();

Jedox.wss.grid.Book.prototype =
{
	// consts
	  _SCROLL_HORIZ: 0
	, _SCROLL_VERT: 1
	, _SCROLL_RWD: -1
	, _SCROLL_FWD: 1

	// flags
	, _FLAG_RENEW: 1

	, _init_post: function (res, cb)
	{
		if (res[0][0] !== true || res[1][0] !== true || res[2][0] !== true || res[3][0] !== true)
			return;

		this._sheetUids = res[0][1];
		this._sheetsC2O = res[1][1];
		this._sheetsO2C = Jedox.util.objFlip(this._sheetsC2O);

		var aSheetUid = res[2][1];
		this._aSheetUid = aSheetUid in this._sheetsC2O ? this._sheetsC2O[aSheetUid] : aSheetUid;

		this._sheetSelector.readWorksheets();


		if (res[3][1].length)
		{
			this._conf = res[3][1][0];

			if (this._conf.autoRefresh)
			{
				if (this._conf.autoRefresh < 10)
					this._conf.autoRefresh = 10;

				this._autoRefresh = this._conf.autoRefresh * 1000;
			}
			else
				this._autoRefresh = 0;
		}
		else
		{
			this._conf = null;

			this._autoRefresh = 0;
		}

		if (this._autoRefresh)
			cb = [ this, Jedox.util.combineCBs, cb, [ this, this.autoRefresh ] ];

		this._showSheet(cb, this._aSheetUid);

		this._initted = true;
	}

	, _genContentEl: function ()
	{
		var html = [
		'<div id="', this._domId, '" class="bookOC">',
			'<div id="', this._domId, '_vs0" class="vsOC"></div>',
			'<div id="', this._domId, '_vs1" class="vsOC vs1OC" style="display: none;"></div>',

			'<div id="', this._domId, '_sheets" class="sheetsOC"> </div>',

			'<div id="gridBRSpacer"> </div>',

			'<div class="sheetSelectorOC" id="', this._domId, '_sheetSelectorOC">',
				'<div class="sheetSelectorTB" id="', this._domId, '_sheetSelectorTB"></div>',
				'<div class="sheetSelectorIC" id="', this._domId, '_sheetSelectorIC"></div>',
				'</div>',

			'<div id="', this._domId, '_hs1" class="hsOC hs1OC" style="display: none;"></div>',
			'<div id="', this._domId, '_hs0" class="hsOC"></div>',
		'</div>'
		];

		this.dom.innerHTML = html.join('');
	}

	, _fit: function ()
	{
		// set widths/heights
		this._sheetsOCWidth = this.holder.getInnerWidth() - this._marginWidth;
		this._sheetsOCHeight = this.holder.getInnerHeight() - this._marginHeight;

		this._sheetsOC.style.width = ''.concat(this._sheetsOCWidth, 'px');
		this._sheetsOC.style.height = ''.concat(this._sheetsOCHeight, 'px');


		// redraw sheet selector (needed for Safari)
		this._sheetSelector._refresh();


		// fit sheets
		for (var sheetUid in this._sheets)
			this._sheets[sheetUid]._fit();
	}

	, _showSheet: function (cb, uid, flags)
	{
		if (!(uid in this._sheetUids))
			return false;


		if (this._aSheet)
			this._aSheet.dom.style.visibility = 'hidden';


		if (flags & this._FLAG_RENEW && uid in this._sheets)
		{
			this._sheetsOC.removeChild(this._sheets[uid].dom);
			delete this._sheets[uid];
		}


		this._aSheetUid = uid;

		if (uid in this._sheets)
		{
			this._app.activeSheet = this._aSheet = this._sheets[uid];
			this._app.activePane = this._aPane = this._aSheet._aPane;
			this._app.environment = this._aPane._env.shared;

			this._aSheet.dom.style.visibility = '';
			this._sheetSelector.enable(true);

			this._aSheet._setupScroll();

			Jedox.wss.sheet.refresh(cb);
		}
		else
			this._sheets[uid] = new Jedox.wss.grid.Sheet(cb, this, uid);

		return true;
	}

	, setClone: function (cloneUid)
	{
		this._sheetsO2C[this._aSheetUid] = cloneUid;
		this._sheetsC2O[cloneUid] = this._aSheetUid;
	}

	, _actOnSheetSel: function (cb)
	{
		switch (this._sheetSelector.action)
		{
			case this._sheetSelector.actionTypes.SELECTED:

				var sheetUid = this._sheetSelector.getActiveSheetId(),
						res;

				if (!(sheetUid in this._sheetUids))
					break;

				if (sheetUid in this._sheetsO2C)
					this._ha.selectSheet(this._sheetsO2C[sheetUid], true, this._gmode_edit);
				else if ((res = this._ha.selectSheet(sheetUid, false, this._gmode_edit, null, cb instanceof Array && cb.length > 2 && !cb[2][0], !(sheetUid in this._sheets)))[1])
					this._sheetsO2C[sheetUid] = res[2], this._sheetsC2O[res[2]] = sheetUid;

				this._showSheet(cb, sheetUid);

				this._jwgen.syncCtrls();

				break;


			case this._sheetSelector.actionTypes.ADDED:

				var res = this._ha.addSheet(this._sheetSelector.actionData);

				if (res.errcode)
					break;

				this._sheetSelector.freeze(false);
				this._sheetSelector.insertEntry(res.name, res.wsid, this._sheetSelector.actionData);
				this._sheetSelector.freeze(true);

				this._sheetUids[res.wsid] = res.name;
				this._showSheet(cb, res.wsid);

				break;


			case this._sheetSelector.actionTypes.REMOVED:

				var sheetUid = this._sheetSelector.getActiveSheetId();

				if (sheetUid in this._sheetsO2C)
					this._ha.selectSheet(this._sheetsO2C[sheetUid], true, this._gmode_edit);
				else
					this._ha.selectSheet(sheetUid, false, this._gmode_edit, null, false, !(sheetUid in this._sheets));

				this._showSheet(cb, sheetUid);


				var removedSheetUid = this._sheetSelector.actionData;

				this._sheetsOC.removeChild(this._sheets[removedSheetUid].dom);
				delete this._sheetUids[removedSheetUid];
				delete this._sheets[removedSheetUid];
				this._conn.ccmd(true, [ 'odel', 2, removedSheetUid ]);

				break;


			case this._sheetSelector.actionTypes.COPIED:

				var data = this._sheetSelector.actionData,
						sameWb = typeof data.wbId != 'string' || !data.wbId.length,
						res = this._ha.copySheet(data.wsId, data.nextSheetId, data.wbId);

				if (res.errcode)
					break;

				if (sameWb)
				{
					this._sheetSelector.freeze(false);
					this._sheetSelector.insertEntry(res.name, res.wsid, data.nextSheetId);
					this._sheetSelector.freeze(true);

					this._sheetUids[res.wsid] = res.name;
					this._showSheet(cb, res.wsid);
				}
				else
				{
					this._sheetSelector.enable(true);

					this._jwgen.setInputMode(this._app.lastInputModeDlg);
					this._app.lastInputMode = this._jwgrid.GridMode.READY;

					this._jwbook.select(data.wbId);

					var destWb = this._app.activeBook;

					destWb._sheetUids[res.wsid] = res.name;
					destWb._sheetSelector.insertEntry(res.name, res.wsid, data.nextSheetId);
				}

				break;


			case this._sheetSelector.actionTypes.MOVED:

				var data = this._sheetSelector.actionData,
						sameWb = typeof data.wbId != 'string' || !data.wbId.length,
						res = this._ha.moveSheet(data.wsId, data.nextSheetId, data.wbId);

				if (res.errcode)
					break;

				if (sameWb)
				{
					this._sheetSelector.freeze(false);
					this._sheetSelector.insertEntry(res.name, res.wsid, data.nextSheetId);
					this._sheetSelector.freeze(true);

					this._sheetSelector.enable(true);

					if (cb instanceof Array && cb.length > 1)
						cb[1].apply(cb[0], cb.slice(2));
				}
				else
				{
					this._sheetsOC.removeChild(this._sheets[data.wsId].dom);
					delete this._sheetUids[data.wsId];
					delete this._sheets[data.wsId];

					this._sheetSelector.enable(true);

					this._jwgen.setInputMode(this._app.lastInputModeDlg);
					this._app.lastInputMode = this._jwgrid.GridMode.READY;

					this._jwbook.select(data.wbId);

					var destWb = this._app.activeBook;

					destWb._sheetUids[res.wsid] = res.name;
					destWb._sheetSelector.insertEntry(res.name, res.wsid, data.nextSheetId);
				}

				break;


			case this._sheetSelector.actionTypes.UNCLONED:

				Jedox.wss.wsel.unloadAll(this.id);

				if (this._ha.removeCloneWorksheet() === false)
					break;

				delete this._sheetsC2O[this._sheetsO2C[this._aSheetUid]];
				delete this._sheetsO2C[this._aSheetUid];

				this._ha.selectSheet(this._aSheetUid, false, this._gmode_edit);

				this._showSheet(cb, this._aSheetUid, this._FLAG_RENEW);

				break;
		}

		this._sheetSelector.action = this._sheetSelector.actionTypes.NONE;
	}

	, _select: function ()
	{
		var activeBook = this._app.activeBook;

		if (activeBook == this)
			return false;

		if (activeBook)
			activeBook._unselect();

		this._app.activeBook = this;
		this._app.activeSheet = this._aSheet;
		this._app.activePane = this._aPane;
		this._app.environment = this._aPane ? this._aPane._env.shared : undefined;

		if (!this._initted)
			return;

		if (this._aSheet)
		{
			if (this._aSheet._defaultSelection)
				this._aSheet._defaultSelection.show();

			this._aSheet.showActiveHdrs(true);

			this._jwgen.syncCtrls();
		}

		this._app.updateUndoState();

		Jedox.wss.action.adjustToACL();

		if (this._autoRefresh)
			this.autoRefresh();

		return true;
	}

	, _unselect: function ()
	{
		if (this._autoRefresh)
			clearTimeout(this._tid_autoRefresh);

		if (this._aSheet)
		{
			if (this._aSheet._defaultSelection)
				this._aSheet._defaultSelection.hide();

			this._aSheet.showActiveHdrs(false);
		}
	}

	, _unload: function ()
	{
		if (this._autoRefresh)
			clearTimeout(this._tid_autoRefresh);

		if (this._gmode_edit)
		{
			this._app.currFormula.setValue('');
			this._app.currCoord.setValue('');
		}

		Jedox.wss.wsel.unloadAll(this.id);

		if (this._app.activeBook == this)
			this._jwbook.unsetActive();

		delete this._jwbook.reg[this.id];

		while (this.dom.hasChildNodes())
			this.dom.removeChild(this.dom.lastChild);

		Jedox.wss.action.adjustToACL();
	}

	, _undo_redo: function (op, steps)
	{
		this._conn.ccmdBuffer();

		this._conn.ccmd(null, [ op, steps ]);
		this._conn.ccmd(null, [ 'gust' ]);

		this._conn.ccmdFlush(true, true);

		// TODO post: res = this._conn.ccmdFlush(...
//		if (res[1].length)
//		{
//			this._aPane._env.shared.undoState = res[1][1][1];
//			this._app.updateUndoState();
//		}
	}

	, undo: function (steps)
	{
		this._undo_redo('undo', steps);
	}

	, redo: function (steps)
	{
		this._undo_redo('redo', steps);
	}

	, autoRefresh: function ()
	{
		if (!this._autoRefresh)
			return;

		var that = this;

		this._tid_autoRefresh = setTimeout(
			function ()
			{
				Jedox.wss.sheet.refresh([ that, that.autoRefresh ]);
			},
			this._autoRefresh
		);
	}


	// MISC

	, select: function ()
	{
		Jedox.wss.app.switchContextObserver.notify(this);
		this._select();

		this.holder.select();
	}

	, refresh: function ()
	{
		Jedox.wss.sheet.refresh(null, true);
	}

	, getScrollDirMap: function ()
	{
		return this._scrollDirectionMap;
	}

	, setWbId: function (id)
	{
		this.uid = id;
	}

	, getUid: function ()
	{
		return this.uid;
	}

	, getWsId: function ()
	{
		return this._sheetSelector.getActiveSheetId();
	}

	, setMeta: function (meta)
	{
		this._meta = meta;
	}

	, setName: function (name)
	{
		this._name = name;
		this.holder.setName(name);
	}

	, getSheetSelector: function ()
	{
		return this._sheetSelector;
	}

	, getTopHolder: function ()
	{
		var holder = this.holder;

		while (holder.holder)
			holder = holder.holder;

		return holder;
	}

	, getSheetUids: function ()
	{
		var list = [];

		for (var uid in this._sheetUids)
			list.push(uid, this._sheetUids[uid]);

		return list;
	}

	, getDomCnt: function (id)
	{
		if (id in this._domCnts)
			return ++this._domCnts[id];

		return this._domCnts[id] = 0;
	}

	, getUidSgn: function ()
	{
		return this._aSheet ? this.uid.concat(' ', this._aSheet.getUid()) : this.uid;
	}

};