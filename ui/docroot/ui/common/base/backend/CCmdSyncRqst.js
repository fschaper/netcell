/*
 * \brief backend ccmd sync request class
 *
 * \file CCmdSyncRqst.js
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
 * SVN: $Id: CCmdSyncRqst.js 5104 2011-07-10 18:11:11Z predragm $
 *
 */

Jedox.backend.CCmdSyncRqst = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (_ccmd)
	{
		Jedox.backend.CCmdSyncRqst.parent.constructor.call(this);

		// private fields

		// private methods

		// public fields
		if (_ccmd instanceof Array)
			this._ccmd = _ccmd[0] instanceof Array ? _ccmd : [ _ccmd ];
		else if (typeof _ccmd == 'string')
			this._ccmd = _ccmd;

		// privileged methods

		// constructor code
	};
}
)();

Jedox.util.extend(Jedox.backend.CCmdSyncRqst, Jedox.backend.SyncRqst);

//public static fields

// public fields & methods
var _prototype = Jedox.backend.CCmdSyncRqst.prototype;

_prototype._uri = '/ub/ccmd';
_prototype._PERF_TYPE = 'ccmd';

_prototype.send = function (ccmd)
{
	if (ccmd && ccmd instanceof Array)
		this._ccmd = ccmd[0] instanceof Array ? ccmd : [ ccmd ];
	else if (typeof ccmd == 'string')
		this._ccmd = ccmd;

	Jedox.backend.CCmdSyncRqst.parent.send.call(this, typeof this._ccmd != 'string' ? this._json.encode(this._ccmd) : this._ccmd);

	var xhr = this._xhr,
			res = xhr.status == 200 ? this._json.decode(xhr.responseText) : [ [ false, 100, this._getXHRDesc(xhr) ] ];

	if (!this._hideErrors)
		this._err.scan(res);

	return res;
};
