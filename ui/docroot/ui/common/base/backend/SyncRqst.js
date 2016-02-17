/*
 * \brief backend sync request abstract base class
 *
 * \file SyncRqst.js
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
 * SVN: $Id: SyncRqst.js 5104 2011-07-10 18:11:11Z predragm $
 *
 */

Jedox.backend.SyncRqst = (function ()
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
Jedox.backend.SyncRqst.prototype = {

	  _json: Ext.util.JSON
	, _err: Jedox.err
	, _httpMethod: 'POST'

	, _getXHRDesc: function (xhr)
	{
		return xhr.status ? xhr.statusText.concat(' (HTTP ', xhr.status, ')') : 'Server Unreachable (HTTP n/a)';
	}

	, hideErrors: function (state)
	{
		this._hideErrors = state;

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
		var xhr = this._xhr = new XMLHttpRequest(),
				uri = this._query ? this._uri.concat('?', this._query) : this._uri,
				val;

		xhr.open(this._httpMethod, uri, false);

		for (var name in this._baseHdrs)
		{
			val = this._baseHdrs[name];

			if (val instanceof Function)
			{
				if (val = val())
					val = val[0];
				else
					continue;
			}

			xhr.setRequestHeader(name, val);
		}

		for (var name in this._hdrs)
			xhr.setRequestHeader(name, this._hdrs[name]);

		Jedox.backend.activityOn();

		if (Jedox.qa && this._PERF_TYPE && Jedox.qa.perf.on)
			this._time = new Date().getTime();

		try
		{
			xhr.send(body);
		}
		catch (e)
		{
		}

		if (Jedox.qa && this._PERF_TYPE && Jedox.qa.perf.on)
			Jedox.qa.perf.extern(this._PERF_TYPE, (+new Date()) - this._time);

		Jedox.backend.activityOff();
	}

};
