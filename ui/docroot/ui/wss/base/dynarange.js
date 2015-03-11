/*
 * \brief dynarange UI routines
 *
 * \file dynarange.js
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
 *
 * \version
 * SVN: $Id: dynarange.js 5042 2011-06-08 12:02:45Z predragm $
 *
 */

Jedox.wss.hb = new function ()
{
	var that = this;

	this.HBMode = {
	  DESIGNER:		0 // design mode
	, QUICKVIEW:	1 // preview mode
	, USER:				2 // user mode
	};

	// add dynarange
	this.addDynarange = function(item, ev) {
		function genHBName() {
			var env = Jedox.wss.app.environment,
				cnt = that.getHBCount() + 1;

			while (env.dynaranges['DynaRange'.concat(cnt)] != undefined && cnt < 1000)
				cnt++;

			return 'DynaRange'.concat(cnt);
		}

		var dir = item.getId().indexOf('newHBVert') >= 0 ? 0 : 1,
		hbdata = {
			id: genHBName(),
			dir: dir,
			drill: true,
			level: 2,
			border: '1px solid #000000',
			indent: dir == 0
		};

		Jedox.palo.utils.openSubsetEditor({mode: 1, dynarange: hbdata});
	};

	// delete dynarange
	this.delDynarange = function(hbid) {
		var env = Jedox.wss.app.environment, hbs = env.dynaranges;

		hbs[hbid].remove(true);
		delete hbs[hbid];

		env.defaultSelection.show();

		if (!that.getHBCount())
			that.enaDisHBQuickView('disable');

		// TODO: Notify Core.
	};

	this.setAllNormal = function(exceptId, redraw) {
		var env = Jedox.wss.app.environment;

		if (!env)
			return;

		var activeSheet = Jedox.wss.app.activeSheet;

		if (env.HBMode != that.HBMode.DESIGNER || activeSheet == undefined || activeSheet.isClone())
			return;

		var hbs = env.dynaranges;
		for (var hbid in hbs) {
			if (hbid == exceptId)
				continue;

			if (redraw)
				hbs[hbid].redraw();
			else
				hbs[hbid].show();
		}
	};

	this.hideAll = function() {
		var env = Jedox.wss.app.environment;

		if (env.HBMode != that.HBMode.QUICKVIEW)
			return;

		var hbs = env.dynaranges;

		for (var hbid in hbs)
			hbs[hbid].hide();
	};

	this.loadAll = function (sheet)
	{
		function _load (res)
		{
			if (!(res instanceof Array) || res[0] !== true)
				return;

			res = res[1];

			var jwgrid = Jedox.wss.grid;

			for (var elem, hbdata, i = res.length - 1; i >= 0; i--)
			{
				elem = res[i];

				hbdata = elem.hbdata;
				hbdata.wselid = elem.e_id;
				hbdata.id = elem.id;
				hbdata._gendata = elem._gendata;

				hbs[hbdata.id] = new jwgrid.DynarangeSelection(sheet, hbdata);

				if (sheet.isClone())
				{
					hbs[hbdata.id].hide();

					that.syncCntrl(true);
					that.enaDisHBAdd('disable');
				}
				else
				{
					hbs[hbdata.id].show();

					that.syncCntrl(false);
					that.enaDisHBAdd('enable');
				}
			}
		}

		var env = sheet._env.shared;

		if (!env) // IE
			return;

		var viewMode = Jedox.wss.grid.viewMode,

		// remove old dynaranges
		hbs = (env.dynaranges = {});

		switch (env.viewMode)
		{
			case viewMode.DESIGNER:
				Jedox.backend.ccmd([ that, _load ], [ 'wget', '', [], [ 'e_id', 'id', 'hbdata', '_gendata' ], { e_type: 'hb' } ]);
				break;

			case viewMode.USER:
				env.HBMode = that.HBMode.USER;
				break;
		}
	};

	this.unloadAll = function() {
		var hbs = Jedox.wss.app.environment.dynaranges;

		for (var hbid in hbs)
			hbs[hbid].remove(false);

		hbs = {};
	};

	this.move = function(id, pos) {
		if (Jedox.wss.app.environment.HBMode != that.HBMode.DESIGNER)
			return;

		var hbs = Jedox.wss.app.environment.dynaranges;

		for (var hbid in hbs)
			if (hbs[hbid].getProps().wselid == id) {
				hbs[hbid].move(pos);
				hbs[hbid].redraw();
				break;
			}
	};

	this.subsetDlgCB = function(hbdata) {
		// hbdata = {id: 1, dir: 0}

		var env = Jedox.wss.app.environment;

		if (env.dynaranges[hbdata.id] != undefined) {
			env.dynaranges[hbdata.id].setProps(hbdata);
			return;
		}

		env.defaultSelection.hide();
		var ulCoord = env.lastRangeStartCoord, lrCoord = env.lastRangeEndCoord;
		hbdata.src = [ulCoord[0], ulCoord[1], lrCoord[0], lrCoord[1]];

		env.dynaranges[hbdata.id] = new Jedox.wss.grid.DynarangeSelection(Jedox.wss.app.activeSheet, hbdata);

		that.enaDisHBQuickView('enable');
	};

	this.propDlgCB = function(hbdata) {
		// hbdata = {id: 1, dir: 0, ....}

		Jedox.wss.app.environment.dynaranges[hbdata.id].setProps(hbdata);
	};

	this.getHBCount = function() {
		var cnt = 0;
		for (var fld in Jedox.wss.app.environment.dynaranges)
			++cnt;

		return cnt;
	};

	this.syncActivePane = function() {
		if (Jedox.wss.app.environment.HBMode != that.HBMode.DESIGNER)
			return;

		var hbs = Jedox.wss.app.environment.dynaranges;

		for (var hbid in hbs)
			hbs[hbid].syncActivePane();
	};

	this.enaDisHBAdd = function(cmd) {
		if (!Jedox.wss.app.environment || Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER)
			return;

		var menubar = Jedox.wss.app.menubar,
			toolbar = Jedox.wss.app.toolbar;

		if (menubar) {
			menubar.newHBVert[cmd]();
			menubar.newHBHoriz[cmd]();
			menubar.userModeView[cmd]();
		}

		toolbar.newHBVert[cmd]();
		toolbar.newHBHoriz[cmd]();
		toolbar.userModeView[cmd]();

		that.enaDisHBQuickView(that.getHBCount() ? 'enable' : 'disable');
	};

	this.enaDisHBQuickView = function(cmd) {
		var menubar = Jedox.wss.app.menubar;
		if (menubar)
			menubar.hbQuickView[cmd]();

		Jedox.wss.app.toolbar.hbQuickView[cmd]();
	};

	this.syncCntrl = function(press) {
		if (!Jedox.wss.app.environment || Jedox.wss.app.environment.viewMode == Jedox.wss.grid.viewMode.USER)
			return;

		Jedox.wss.app.performItemToggle = false;

		var menubar = Jedox.wss.app.menubar;
		if (menubar)
			menubar.hbQuickView.setChecked(press, true);

		Jedox.wss.app.toolbar.hbQuickView.toggle(press);

		Jedox.wss.app.performItemToggle = true;
	};

	this.run = function(btn, state) {
		/*
		 * $dynarangeData structure example:
		 *
		 * [
		 *	{
		 *		id: 1,
		 *		src: [ 1, 1, 2, 2 ], // source coords
		 *		dir: 0|1, // 0 - down, 1 - right
		 *		dcell: [ 0, 0 ], // data cell offset from src[0]/src[1]
		 *		drill: false|true, // drill down enabled
		 *		level: 2, // drill down begin level
		 *		border: '1px solid #000000', // border css definition
		 *		cwidth: 50, // column width in pixels
		 *		indent: false|true // indent data enabled
		 *	}, ...
		 * ]
		 *
		 */

		if (!Jedox.wss.app.performItemToggle || that.getHBCount() <= 0)
			return;

		var env = Jedox.wss.app.environment,
			activeBook = Jedox.wss.app.activeBook,
			HBMode = env.HBMode;

		if (state) {
			try {
				env.HBMode = that.HBMode.QUICKVIEW;
				var hbs = env.dynaranges,
						hasHbs = false;

				for (var hbid in hbs)
				{
					hasHbs = true;
					break;
				}

				if (hasHbs) {
					// Create Worksheet clone.
					var clnRes = Jedox.backend.wss.addCloneWorksheet();

					if (clnRes !== false)
						activeBook.setClone(clnRes);

					that.hideAll();
					Jedox.backend.rpc_cb('hb_run', [ HBMode == that.HBMode.USER ? null : 3 ], Jedox.backend.Q_ALL, Jedox.backend.D_BOTH);
				}

				that.syncCntrl(true);

				// Disable adding new HB.
				that.enaDisHBAdd('disable');

				Jedox.wss.app.statusBar.setWorkingMode('QuickView'.localize());
			} catch (e) {
				env.HBMode = HBMode;
			}
		} else {
			try {
				env.HBMode = that.HBMode.DESIGNER;

				// Remove Worksheet clone.
				var sheetSelector = activeBook.getSheetSelector();
				sheetSelector.action = sheetSelector.actionTypes.UNCLONED;

				activeBook._actOnSheetSel();

				that.setAllNormal();
				that.syncCntrl(false);

				that.enaDisHBAdd('enable');

				Jedox.wss.app.statusBar.setWorkingMode('Designer'.localize());
			} catch (e) {
				env.HBMode = HBMode;
			}
		}
	};

	this.regECHandlers = function ()
	{
		Jedox.wss.grid.cbReg('hb_ec', [ that, that.expandCollapse ]);
	};

	this.expandCollapse = function(eventData, hbId, idxPath)
	{
		Jedox.backend.rpc_cb('hb_ec', [ hbId, [ eventData.c, eventData.r ], idxPath ], Jedox.backend.Q_ALL, Jedox.backend.D_BOTH);

		return false;
	};

};