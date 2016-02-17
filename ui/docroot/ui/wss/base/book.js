/*
 * \brief workbook handling routines
 *
 * \file book.js
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
 *
 * \version
 * SVN: $Id: book.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.book = new function ()
{
	var that = this;

	this.reg = {};

	this.spawn = function (cb, uid, name, meta)
	{
		new Jedox.wss.wnd.Window(cb, { type: 'workbook', uid: uid, name: name, meta: meta });

		Jedox.wss.action.adjustToACL();
	};

	this.create = function (cb)
	{
		var rqst = new Jedox.backend.RPCAsyncRqst('WSS', 'load_workbook', [null]);
		rqst.setOnSuccess([ that, that.create_post, cb]).send();
	};

	this.create_post = function (res, cb)
	{
		if (!res[0])
		{
			Jedox.wss.general.showMsg('Application Error'.localize(), 'errLoadWB_intro'.localize().concat(' ', res[1].localize()), Ext.MessageBox.ERROR);
			return false;
		}

		that.spawn(cb, res[1].wbid, res[1].name, null);
	};

	this.load = function (cb, wb, group, hierarchy, ext, pc)
	{
		Jedox.wss.general.chkState();

		if (!ext)
			ext = { appmode: Jedox.wss.app.appMode };
		else
			ext.appmode = Jedox.wss.app.appMode;

		var rqst = new Jedox.backend.RPCAsyncRqst('WSS', 'load_workbook', [wb, group ? group : null, hierarchy ? hierarchy : null, ext ? ext : null]);
		rqst.setOnSuccess([ that, that.load_post, cb, { g: group, h: hierarchy, n: wb }, pc, arguments ]).send();

		return true;
	};

	this.load_post = function (res, cb, meta, pc, args)
	{
		var wnd = Jedox.wss.wnd;
			hasCb = cb instanceof Array && cb.length > 1;

		if (!res[0])
		{
			if (!res[1].search(/^follHL*/i) && hasCb)
				cb[1].call(cb[0], cb[2], res[1]);

			if (!res[1].search(/^recovery*/i)) {
				Jedox.wss.events.disableEvents(['switchWorkbook_before', 'switchWorkbook_after']);
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.recover, [res[2], args]);
			} else
				Jedox.wss.general.showMsg('Application Error'.localize(), 'errLoadWB_intro'.localize().concat(' ', res[1].localize()), Ext.MessageBox.ERROR, [this, wnd.triggerCloseEvt, null, meta]);

			return false;
		}

		if (pc)
		{
			pc.params.unshift(res[1][pc.tag]);
			pc.func.apply(pc.scope, pc.params);
		}

		if (res[1].fgroup) {
			meta.fg = res[1].fgroup;
			meta.fh = res[1].fhierarchy;
			meta.fn = res[1].fnode;
		}

		if (!pc || pc.cnt == undefined) {
			var book = that.find(res[1].wbid, meta, res[1].name);

			if (res[1].imp && book)
			{
				if (res[1].wsid)
					Jedox.wss.sheet.select(cb, res[1].wsid, book);
				else if (hasCb)
					cb[1].call(cb[0]);

				book.holder.select();
			}
			else {
				if (meta.g == undefined || meta.h == undefined)
					meta = null;
				else
					meta.p = res[1].perm;

				that.spawn(cb, res[1].wbid, res[1].name, meta);
			}
		} else {
			if (pc.cnt instanceof wnd.Window) {
				var existWin = wnd.findByMeta(res[1].name, meta);

				if (existWin) {
					if (wnd.active._id == existWin._id)
						return true;
					else if (res[1].imp) {
						wnd.active.unload();
						existWin.select();
						return true;
					}
				}

				var data = {
					type: 'workbook',
					uid: res[1].wbid,
					name: res[1].name,
					meta: meta
				};
			}

			pc.cnt.replaceNode(cb, data);
		}

		return true;
	};

	this.unload = function (cb, uid)
	{
		(new Jedox.backend.RPCAsyncRqst('WSS', 'removeBook', [uid])).setOnSuccess(cb).send();
	};

	this.save = function (cb, node)
	{
		var active = true;

		if (!node)
			node = Jedox.wss.wnd.active.node;
		else
			active = false;

		var ghn = node._meta;

		if (!ghn)
		{
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['save', cb]);
			return;
		}

		(new Jedox.backend.RPCAsyncRqst('WSS', 'save_workbook', [ghn.g, ghn.h, ghn.n, null, null, active])).setOnSuccess([that, that.save_post, cb]).send();
	};

	this.save_post = function (res, cb)
	{
		if (!res[0]) {
			Ext.MessageBox.show({
				title: 'Save'.localize(),
				msg: res[1].localize(res[2]),
				modal: true,
				buttons: Ext.MessageBox.OK,
				icon: Ext.MessageBox.WARNING,
				fn: Ext.emptyFn,
				minWidth: 300
			});
		}

		if (cb instanceof Array && cb.length > 1)
			cb[1].call(cb[0]);
	};

	this.find = function (uid, meta, name)
	{
		var book, node;

		for (var id in that.reg)
		{
			book = that.reg[id];

			if (book.uid != uid)
				continue;

			if (meta)
			{
				node = book.getTopHolder().node;

				if (!node || !node._meta || !(
						(node._meta.g == meta.g && node._meta.h == meta.h && node._meta.n == meta.n) ||
						(!meta.g.search(/^f/) ? node._meta.fg == meta.g && node._meta.fh == meta.h && node._meta.fn == meta.n : false)
					)
				)
					continue;
			}

			if (name && name != book._name)
				continue;

			return book;
		}

		return undefined;
	};

	this.findByName = function (name)
	{
		var book;

		for (var id in that.reg)
		{
			book = that.reg[id];

			if (book._name == name)
				return book;
		}

		return false;
	};

	this.select = function (uid, meta, name)
	{
		var book = that.find(uid, meta, name);

		if (book)
			that.selectById(book.id);
	};

	this.selectById = function (id)
	{
		if (id in that.reg)
			that.reg[id].select();
	};

	this.autoRefresh = function (secs)
	{
		var activeBook = Jedox.wss.app.activeBook;

		if (activeBook._autoRefresh)
			clearTimeout(activeBook._tid_autoRefresh);

		if ((secs |= 0) && secs < 10)
			secs = 10;

		activeBook._autoRefresh = secs * 1000;

		if (secs)
			activeBook.autoRefresh();

		if (activeBook._conf == null)
		{
			activeBook._conf = { e_type: 'conf', autoRefresh: secs };

			var ccmd = '[["badd","",{"e_type":"conf","autoRefresh":'.concat(secs, '}]]'),
					post = [ that, function (res) { if (res[0][0]) activeBook._conf.e_id = res[0][1][0]; } ];
		}
		else
		{
			activeBook._conf.autoRefresh = secs;

			var e_id = activeBook._conf.e_id;
			delete activeBook._conf.e_id;

			var ccmd = '[["bupd","",{"'.concat(e_id, '":', Ext.util.JSON.encode(activeBook._conf), '}]]'),
					post = null;

			activeBook._conf.e_id = e_id;
		}

		var conn = Jedox.backend;

		conn.ccmdSetBuff(ccmd);
		conn.ccmdFlush(post);
	};

	this.recover = function (win, args)
	{
		win._execClose = false;
		win.close();

		var argsCopy = [];
		for (var i = 0, alen = args.length; i < alen; i++)
			argsCopy.push(args[i]);

		Jedox.wss.events.enableEvents(['switchWorkbook_before', 'switchWorkbook_after']);
		that.load.apply(this, argsCopy);
	};

	this.goTo = function (ref)
	{

		var result = false,
			pref = Jedox.wss.formula.parse(ref);

		if (pref.length != 1)
			searchNames(ref);
		else
			doGoTo(pref);

		return result;


		function searchNames(name)
		{
			var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
			var tmpResponse=Jedox.backend.ccmd(0, ["nlst", [position._x, position._y]]);
			var names=tmpResponse[0][1][0];

			for (var i=0, count=names.length; i<count; i++)
				if(names[i]['name'] == name)
					doGoTo(Jedox.wss.formula.parse(names[i]['refers_to']));
		}

		function doGoTo(pref)
		{
			ref = pref[0];

			var activeBook = Jedox.wss.app.activeBook,
					activePane = Jedox.wss.app.activePane,
					defSel = Jedox.wss.app.environment.defaultSelection;

			if (ref.sheet.length && ref.sheet != activeBook._sheetUids[activeBook._aSheetUid])
				result = false;

			activePane.scrollTo(defSel ? [ defSel, defSel.jumpTo, ref.rng] : null, ref.rng[0], ref.rng[1], true, false);

			result = true;
		}

	};

	this.autoSwitch = function (id, sheetUid)
	{
		if (id && id in that.reg && that.reg[id] != Jedox.wss.app.activeBook)
			return that.reg[id].select();

		var activeBook = Jedox.wss.app.activeBook;

		if (!activeBook)
			return undefined;

		var cb = [ that, that.autoSwitch, activeBook.id ];

		if (activeBook._aSheet)
		{
			var sheetsO2C = activeBook._sheetsO2C,
					aSheetUid = activeBook._aSheetUid;

			if (aSheetUid in sheetsO2C)
				aSheetUid = sheetsO2C[aSheetUid];

			cb.unshift(activeBook.uid.concat(' ', aSheetUid));
			cb.push(aSheetUid);
		}
		else
			cb.unshift(activeBook.uid);

		return cb;
	};

	this.unsetActive = function ()
	{
		var app = Jedox.wss.app;

		app.activeBook = app.activeSheet = app.activePane = app.environment = undefined;
	};

	this.getVirtScroll = function (onlyActive)
	{
		var activeBook = Jedox.wss.app.activeBook,
				activeWnd = Jedox.wss.wnd.active,
				vscroll = {},
				book;

		vscroll['.'.concat(activeBook.id)] = activeBook._aSheet.getVirtScroll();

		if (!onlyActive)
			for (var id in that.reg)
				if ((book = that.reg[id]) != activeBook && book.getTopHolder() == activeWnd)
					vscroll[book.uid.concat('.', book.id)] = book._aSheet.getVirtScroll();

		return vscroll;
	};

	this.chkSaved = function (cb, node)
	{
		function cbBns(res) {
			if (cb instanceof Array && cb.length > 1)
				cb[1].call(cb[0], !res[1][0] || !res[1][1]);
		}

		(new Jedox.backend.CCmdAsyncRqst([['osel', 1, node.uid], ['bns']])).setOnSuccess([this, cbBns]).send();
	};

	this.getPerm = function (node)
	{
		return node._meta ? node._meta.p : Jedox.wss.grid.permission.PERM_DELETE;
	};

};