/*
 * \brief backend connection related
 *
 * \file backend.js
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
 *
 * \version
 * SVN: $Id: backend.js 5101 2011-07-08 13:46:57Z predragm $
 *
 */

Jedox.backend = new function ()
{
	var that = this,
			_ccmd_buffd = 0,
			_ccmd = [],
			_ccmd_cbs = [],
			_ccmd_cbs_any = false,
			_ccmd_noRes2CBs;

	this.Q_NONE = 0;
	this.Q_VALUE = 1;
	this.Q_FORMULA = 2;
	this.Q_STYLE = 4;
	this.Q_FORMULA_WE = 8;
	this.Q_ATTRS = 16;
	this.Q_DIMS = 32;
	this.Q_FMT_VAL = 64;
	this.Q_FMT = 128;
	this.Q_MERGE = 256;
	this.Q_FORMULA_NF = 512;
	this.Q_LOCK = 1024;
	this.Q_ALL = 2013; // all except FORMULA and DIMS

	this.D_NONE = 0;
	this.D_COLS = 1;
	this.D_ROWS = 2;
	this.D_BOTH = 3;

	this.ccmdBuffer = function (noRes2CBs)
	{
		++_ccmd_buffd;

		_ccmd_noRes2CBs = noRes2CBs;
	};

	this.ccmd = function (cb, ccmd, diff, propset, dimset)
	{
		if (_ccmd_buffd)
		{
			_ccmd_cbs.push(cb);

			if (cb && !_ccmd_cbs_any)
				_ccmd_cbs_any = true;

			return _ccmd.push(ccmd) - 1;
		}

		if (cb)
		{
			var rqst = diff ? new Jedox.backend.CCmdDiffAsyncRqst(ccmd, propset, dimset) : new Jedox.backend.CCmdAsyncRqst(ccmd);

			rqst.setOnSuccess(cb).send();

			return true;
		}

		var rqst = diff ? new Jedox.backend.CCmdDiffSyncRqst(ccmd, propset, dimset) : new Jedox.backend.CCmdSyncRqst(ccmd);

		return rqst.send();
	};

	this.ccmdSetBuff = function (ccmd)
	{
		_ccmd_buffd = 1;
		_ccmd = ccmd;
		_ccmd_cbs = [];
		_ccmd_cbs_any = false;
	};

	this.ccmdFlush = function (cb, diff, propset, dimset)
	{
		if (_ccmd_buffd > 1)
		{
			--_ccmd_buffd;
			return true;
		}

		_ccmd_buffd = 0;

		if (!_ccmd.length)
			return undefined;

		if (_ccmd_cbs_any)
		{
			var batch = diff ? new Jedox.backend.CCmdDiffAsyncBatch(true, propset, dimset) : new Jedox.backend.CCmdAsyncBatch(false, _ccmd_noRes2CBs);

			batch.setCompat(true);

			for (var rqst, num = _ccmd.length, i = 0; i < num; ++i)
			{
				rqst = new Jedox.backend.CCmdAsyncRqst(_ccmd[i]);

				if (_ccmd_cbs[i])
					rqst.setOnSuccess(_ccmd_cbs[i]);

				batch.add(rqst);
			}

			if (cb)
				batch.setOnSuccess(cb);

			batch.send();

			_ccmd = [];
			_ccmd_cbs = [];
			_ccmd_cbs_any = false;

			return true;
		}
		else if (cb)
		{
			var rqst = diff ? new Jedox.backend.CCmdDiffAsyncRqst(_ccmd, propset, dimset) : new Jedox.backend.CCmdAsyncRqst(_ccmd);

			rqst.setOnSuccess(cb).send();

			_ccmd = [];
			_ccmd_cbs = [];

			return true;
		}

		var rqst = diff ? new Jedox.backend.CCmdDiffSyncRqst(_ccmd, propset, dimset) : new Jedox.backend.CCmdSyncRqst(_ccmd);

		_ccmd = [];
		_ccmd_cbs = [];

		return rqst.send();
	};

	this.rpc = function (cb, _class, _method, _args)
	{
		var rqst = new Jedox.backend.RPCAsyncRqst(_class, _method, _args);

		rqst.setOnSuccess(cb).send();

 		return true;
	};

	this.rpc_cb = function (handle, params, propset, dimset)
	{
		var rqst = new Jedox.backend.RPCAsyncRqst('WSS', 'cb', [ handle, params, Jedox.wss.book.getVirtScroll(), propset ? propset : Jedox.backend.Q_ALL, dimset ? dimset : Jedox.backend.D_BOTH ]);

		rqst.setOnSuccess([ this, function (res) { Jedox.err.scan(res[1]); Jedox.wss.ccmd.mexec(res[0]); } ]).send();
	};


	// ping
	this.ping_interval = 240000;

	this.ping = function ()
	{
		(new Jedox.backend.CCmdAsyncRqst(that.ping_cmd)).send();

		setTimeout(that.ping, that.ping_interval);
	};

	this.php_ping = function ()
	{
		var xhr = new XMLHttpRequest();

		xhr.open('GET', '/be/ping.php', true);
 		xhr.send(null);

 		setTimeout(that.php_ping, that.php_ping_interval);
	};


	// activity indicator
	var activityCnt = 0;

	this.activityOn = function ()
	{
		if (!this.activityIndctr)
			return;

		if (!activityCnt)
			this.activityIndctr.style.visibility = 'visible';

		++activityCnt;
	};

	this.activityOff = function ()
	{
		if (!this.activityIndctr)
			return;

		if (activityCnt)
			--activityCnt;

		if (!activityCnt)
			this.activityIndctr.style.visibility = 'hidden';
	};

	this.isActive = function ()
	{
		return activityCnt;
	};

};