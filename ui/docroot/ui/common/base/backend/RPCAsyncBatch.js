/*
 * \brief backend RPC async batch class
 *
 * \file RPCAsyncBatch.js
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
 * SVN: $Id: RPCAsyncBatch.js 5104 2011-07-10 18:11:11Z predragm $
 *
 */

Jedox.backend.RPCAsyncBatch = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (doCBsBefore)
	{
		Jedox.backend.RPCAsyncBatch.parent.constructor.call(this);

		// private fields

		// private methods

		// public fields
		this._doCBsBefore = doCBsBefore;

		var rqsts = this._rqsts = [],
				rqstClass = this._rqstClass;

		for (var i = arguments.length - 1; i >= 1; --i)
			if (arguments[i] instanceof rqstClass)
				rqsts.unshift(arguments[i]);

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.RPCAsyncBatch, Jedox.backend.AsyncRqst);

// public static fields

// public fields & methods
var _prototype = Jedox.backend.RPCAsyncBatch.prototype;

_prototype._rqstClass = Jedox.backend.RPCAsyncRqst;
_prototype._uri = '/be/rpc.php';

_prototype._doCBs = function (err, res)
{
	if (err && this._onError)
		this._onError[1].apply(this._onError[0], [ res ].concat(this._onError.slice(2)));
	else if (this._onSuccess)
		this._onSuccess[1].apply(this._onSuccess[0], [ res ].concat(this._onSuccess.slice(2)));
};

_prototype._receive = function ()
{
	var xhr = this._xhr,
			res = xhr.status == 200 ? this._json.decode(xhr.responseText) : [ [ false, 'R1', this._getXHRDesc(xhr) ] ],
			err = false;

	if (!this._hideErrors)
		err = this._err.scan(res);
	else
		for (var i = res.length - 1; i >= 0; --i)
			if (!res[i][0])
			{
				err = true;
				break;
			}

	if (this._doCBsBefore)
		this._doCBs(err, res);

	for (var rqst, cres, len = res.length, i = 0; i < len; ++i)
	{
		rqst = this._rqsts[i];
		cres = res[i];

		if (!cres[0] && rqst._onError)
			rqst._onError[1].apply(rqst._onError[0], [ cres.slice(1) ].concat(rqst._onError.slice(2)));
		else if (rqst._onSuccess)
			rqst._onSuccess[1].apply(rqst._onSuccess[0], [ cres[1] ].concat(rqst._onSuccess.slice(2)));
	}

	if (!this._doCBsBefore)
		this._doCBs(err, res);
};

_prototype.add = function ()
{
	var rqsts = this._rqsts,
			rqstClass = this._rqstClass;

	for (var len = arguments.length, i = 0; i < len; ++i)
		if (arguments[i] instanceof rqstClass)
			rqsts.push(arguments[i]);

	return this;
};

_prototype.send = function ()
{
	if (arguments.length)
	{
		this._rqsts	= [];
		this.add.apply(this, arguments);
	}

	var batch = [];

	for (var rqst, i = this._rqsts.length - 1; i >= 0; --i)
		batch.unshift([ (rqst = this._rqsts[i])._class, rqst._method, rqst._args ]);

	Jedox.backend.RPCAsyncBatch.parent.send.call(this, this._json.encode(batch));
};
