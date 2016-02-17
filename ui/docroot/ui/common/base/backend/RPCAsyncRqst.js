/*
 * \brief backend RPC async request class
 *
 * \file RPCAsyncRqst.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: RPCAsyncRqst.js 3955 2010-10-07 10:38:04Z predragm $
 *
 */

Jedox.backend.RPCAsyncRqst = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (_class, _method, _args)
	{
		Jedox.backend.RPCAsyncRqst.parent.constructor.call(this);

		// private fields

		// private methods

		// public fields
		this._class = _class;
		this._method = _method;
		this._args = _args;

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.RPCAsyncRqst, Jedox.backend.AsyncRqst);

// public static fields

// public fields & methods
var _prototype = Jedox.backend.RPCAsyncRqst.prototype;

_prototype._uri = '/be/rpc.php';

_prototype._receive = function ()
{
	var xhr = this._xhr,
			res = xhr.status == 200 ? this._json.decode(xhr.responseText) : [ [ false, 'R1', this._getXHRDesc(xhr) ] ],
			err = false;

	if (!this._hideErrors)
		err = this._err.scan(res);
	else if (!res[0][0])
		err = true;

	if (err)
	{
		if (this._onError)
			this._onError[1].apply(this._onError[0], [ res[0].slice(1) ].concat(this._onError.slice(2)));
		else if (this._onSuccess)
			this._onSuccess[1].apply(this._onSuccess[0], [ res[0] ].concat(this._onSuccess.slice(2)));
	}
	else if (this._onSuccess)
		this._onSuccess[1].apply(this._onSuccess[0], [ res[0][1] ].concat(this._onSuccess.slice(2)));
};

_prototype.send = function (args)
{
	if (args)
		this._args = args;

	Jedox.backend.RPCAsyncRqst.parent.send.call(this, this._json.encode([ [ this._class, this._method, this._args ] ]));
};
