/*
 * \brief backend ccmd w/ diff async batch class
 *
 * \file CCmdDiffAsyncBatch.js
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
 * SVN: $Id: CCmdDiffAsyncBatch.js 5104 2011-07-10 18:11:11Z predragm $
 *
 */

Jedox.backend.CCmdDiffAsyncBatch = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (doCBsBefore, _propset, _dimset, _flags)
	{
		Jedox.backend.CCmdDiffAsyncBatch.parent.constructor.call(this);

		// private fields

		// private methods

		// public fields
		this._doCBsBefore = doCBsBefore;

		this._propset = _propset ? _propset : Jedox.backend.Q_ALL;
		this._dimset = _dimset ? _dimset : Jedox.backend.D_BOTH;
		this._flags = _flags;

		var rqsts = this._rqsts = [],
				rqstClass = this._rqstClass;

		for (var i = arguments.length - 1; i >= 5; --i)
			if (arguments[i] instanceof rqstClass)
				rqsts.unshift(arguments[i]);

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.CCmdDiffAsyncBatch, Jedox.backend.AsyncRqst);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.CCmdDiffAsyncBatch.prototype;

_prototype._rqstClass = Jedox.backend.CCmdAsyncRqst;
_prototype._uri = '/be/ccmd.php';

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
			reswdiff = xhr.status == 200 ? this._json.decode(xhr.responseText) : [ {}, [ [ false, 100, this._getXHRDesc(xhr) ] ] ],
			res = reswdiff[1],
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

	Jedox.wss.ccmd.mexec(reswdiff[0]);

	if (this._doCBsBefore)
		this._doCBs(err, res);

	for (var rqst, ccmd_len, cres, cres_len, cerr, pos = 0, len = this._rqsts.length, i = 0; i < len; ++i)
	{
		rqst = this._rqsts[i];

		if (!(ccmd_len = rqst._ccmd.length))
			continue;

		cres = res.slice(pos, pos += ccmd_len);

		if (!(cres_len = cres.length))
			break;

		cerr = false;

		for (var j = cres_len - 1; j >= 0; --j)
			if (!cres[j][0])
			{
				cerr = true;
				break;
			}

		if (this._compat && cres_len == 1)
			cres = cres[0];

		if (cerr && rqst._onError)
			rqst._onError[1].apply(rqst._onError[0], [ cres ].concat(rqst._onError.slice(2)));
		else if (rqst._onSuccess)
			rqst._onSuccess[1].apply(rqst._onSuccess[0], [ cres ].concat(rqst._onSuccess.slice(2)));
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

_prototype.send = function (propset, dimset, flags)
{
	this._vscroll = Jedox.wss.book.getVirtScroll();

	if (propset)
		this._propset = propset;

	if (dimset)
		this._dimset = dimset;

	if (flags)
		this._flags = flags;

	var args = this._json.encode([ this._vscroll, this._propset, this._dimset, this._flags ]);

	if (args.length > 2)
		this._hdrs = { 'X-WSS-Diff': args };

	if (arguments.length > 4)
	{
		this._rqsts	= [];
		this.add.apply(this, Array.prototype.slice.call(arguments, 4));
	}

	var batch = [];

	for (var rqst, i = this._rqsts.length - 1; i >= 0; --i)
	{
		rqst = this._rqsts[i];

		if (typeof rqst._ccmd == 'string')
			rqst._ccmd = this._json.decode(rqst._ccmd);

		for (var ccmd = rqst._ccmd, j = ccmd.length - 1; j >= 0; --j)
			batch.unshift(ccmd[j]);
	}

	Jedox.backend.CCmdAsyncBatch.parent.send.call(this, this._json.encode(batch));
};
