/*
 * \brief perf QA routines
 *
 * \file perf.js
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
 * SVN: $Id: perf.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.qa.perf = new function ()
{
	var that = this,
			_auto, _cb, _cnt, _cap, _ts, _dur, _tid,
			_minbase, _maxbase,
			_extern;

	function calibrate ()
	{
		var ts = +new Date();

		_cap[--_cnt] = ts - _ts;

		_ts = ts;

		if (_cnt)
			return _tid = setTimeout(calibrate, 0);

		var map = {},
				dur;

		for (var i = _cap.length - 1; i >= 0; --i)
		{
			dur = _cap[i];

			if (!dur)
				continue;

			if (dur in map)
				++map[dur];
			else
				map[dur] = 1;
		}

		var min = { dur: 0, cnt: 0 },
				max = { dur: 0, cnt: 0 },
				cnt;

		for (dur in map)
		{
			cnt = map[dur];

			if (cnt > max.cnt)
			{
				min.cnt = max.cnt;
				min.dur = max.dur;

				max.cnt = cnt;
				max.dur = dur;
			}
			else if (cnt > min.cnt)
			{
				min.cnt = cnt;
				min.dur = dur;
			}
		}

		_minbase = min.dur;
		_maxbase = max.dur;

		if (_cb)
			_cb(_minbase, _maxbase);
	}

	this.calibrate = function (cb, iters)
	{
		_cb = cb;

		_cap = new Array(_cnt = iters);
		_ts = +new Date();

		_tid = setTimeout(calibrate, 0);
	};

	function start ()
	{
		var ts = +new Date(),
				dur = ts - _ts;

		if (dur > _maxbase)
			_dur += dur;
		else if (_auto && !Jedox.backend.isActive() && !--_cnt)
			that.stop();

		_ts = ts;
	}

	this.init = function (cb)
	{
		clearInterval(_tid);

		_dur = 0;
		_cnt = 10;
		_extern = {};

		var rqst = new Jedox.backend.RPCAsyncRqst('qa', 'initPerf', []);

		if (cb)
			rqst.setOnSuccess([ this, cb ]);

		rqst.send();
	}

	this.start = function (cb, auto)
	{
		this.on = true;

		_cb = cb;
		_auto = auto;

		_ts = +new Date();

		_tid = setInterval(start, 0);
	};

	function stop (res)
	{
		for (var type in _extern)
			_dur -= _extern[type];

		for (var type in res)
		{
			_dur -= res[type];

			if (_extern[type])
				_extern[type] += res[type];
			else
				_extern[type] = res[type];
		}

		_extern.js = _dur;

		if (_cb)
			_cb(Ext.util.JSON.encode(_extern));
	}

	this.stop = function ()
	{
		this.on = false;

		clearInterval(_tid);

		(new Jedox.backend.RPCAsyncRqst('qa', 'getPerf', [])).setOnSuccess([ this, stop ]).send();
	};

	this.extern = function (type, dur)
	{
		if (!_extern)
			return;

		if (_extern[type])
			_extern[type] += dur;
		else
			_extern[type] = dur;
	};

};
