/*
 * \brief backend async request abstract base class
 *
 * \file AsyncRqst.js
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
 * SVN: $Id: AsyncRqst.js 5104 2011-07-10 18:11:11Z predragm $
 *
 */

Jedox.backend.AsyncRqst = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function ()
	{
		// private fields

		// private methods

		// public fields

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.backend.AsyncRqst.prototype = {

	  _DEF_TIMEOUT: 20000
	, _json: Ext.util.JSON
	, _err: Jedox.err
	, _httpMethod: 'POST'

	, _getXHRDesc: function (xhr)
	{
		return xhr.status ? xhr.statusText.concat(' (HTTP ', xhr.status, ')') : 'Server Unreachable (HTTP n/a)';
	}

	, _activityOff: function ()
	{
		if (!this._active)
			return;

		this._active = false;
		Jedox.backend.activityOff();
	}

	, _checkTimeout: function ()
	{
		delete this._timeoutId;

		if (this._xhr.readyState == 4)
			return;

		this.abort(true);

		if (this._onTimeout)
			this._onTimeout[1].apply(this._onTimeout[0], this._onTimeout.slice(2));
	}

	, _checkDone: function ()
	{
		var that = this,
				xhr = this._xhr;

		if (xhr.readyState != 4)
			return;

		if (Jedox.qa && this._PERF_TYPE && Jedox.qa.perf.on)
			Jedox.qa.perf.extern(this._PERF_TYPE, (+new Date()) - this._time);

		if (this._timeoutId)
			clearTimeout(this._timeoutId);

		for (var cb, len = this._onDone.length, i = 0; i < len; ++i)
		{
			cb = this._onDone[i];
			cb[1].apply(cb[0], cb.slice(2));
		}

		setTimeout(function () { that._activityOff(); }, 0);

		this._receive();
	}

	, hideErrors: function (state)
	{
		this._hideErrors = state;

		return this;
	}

	, setOnTimeout: function (cb, timeout)
	{
		if (cb instanceof Array && cb.length > 1)
		{
			this._onTimeout = cb;
			this._timeout = timeout ? timeout : this._DEF_TIMEOUT;
		}

		return this;
	}

	, setOnError: function (cb)
	{
		if (cb instanceof Array && cb.length > 1)
			this._onError = cb;

		return this;
	}

	, setOnSuccess: function (cb)
	{
		if (cb instanceof Array && cb.length > 1)
			this._onSuccess = cb;

		return this;
	}

	, setFlags: function (flags)
	{
		this._query = flags;

		return this;
	}

	, setCompat: function (compat)
	{
		this._compat = compat;

		return this;
	}

	, setHdr: function (name, val)
	{
		if (!this._hdrs)
			this._hdrs = {};

		this._hdrs[name] = val;
	}

	, send: function (body)
	{
		if (this._active)
			this.abort(true);

		this._active = true;
		Jedox.backend.activityOn();

		var that = this,
				xhr = this._xhr = new XMLHttpRequest(),
				uri = this._query ? this._uri.concat('?', this._query) : this._uri,
				val, cb;

		xhr.open(this._httpMethod, uri, true);

		this._onDone = [];

		for (var name in this._baseHdrs)
		{
			val = this._baseHdrs[name];

			if (val instanceof Function)
			{
				if (val = val())
				{
					cb = val;
					val = cb.shift();

					this._onDone.push(cb);
				}
				else
					continue;
			}

			if (!this._hdrs || !(name in this._hdrs))
				xhr.setRequestHeader(name, val);
		}

		for (var name in this._hdrs)
			xhr.setRequestHeader(name, this._hdrs[name]);

		xhr.onreadystatechange = function () { that._checkDone(); };

		if (this._timeout)
			this._timeoutId = setTimeout(function () { that._checkTimeout(); }, this._timeout);

		if (Jedox.qa && this._PERF_TYPE && Jedox.qa.perf.on)
			this._time = new Date().getTime();

		xhr.send(body);
	}

	, abort: function (full)
	{
		if (!this._xhr)
			return;

		var hideErrors = this._hideErrors;

		this._hideErrors = true;

		if (full)
			this._xhr.onreadystatechange = null;

		this._xhr.abort();

		this._hideErrors = hideErrors;

		this._activityOff();
	}
};
