/*
 * \brief backend ccmd w/ diff sync request class
 *
 * \file CCmdDiffSyncRqst.js
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
 * SVN: $Id: CCmdDiffSyncRqst.js 3955 2010-10-07 10:38:04Z predragm $
 *
 */

Jedox.backend.CCmdDiffSyncRqst = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (_ccmd, _propset, _dimset, _flags)
	{
		Jedox.backend.CCmdDiffSyncRqst.parent.constructor.call(this, _ccmd);

		// private fields

		// private methods

		// public fields
		this._propset = _propset ? _propset : Jedox.backend.Q_ALL;
		this._dimset = _dimset ? _dimset : Jedox.backend.D_BOTH;
		this._flags = _flags;

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.CCmdDiffSyncRqst, Jedox.backend.CCmdSyncRqst);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.CCmdDiffSyncRqst.prototype;

_prototype._uri = '/be/ccmd.php';

_prototype.send = function (ccmd, propset, dimset, flags)
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

	var res = Jedox.backend.CCmdDiffSyncRqst.parent.send.call(this, ccmd);

	if (!this._hideErrors)
		this._err.scan(res[1]);

	Jedox.wss.ccmd.mexec(res[0]);

	return res[1];
};
