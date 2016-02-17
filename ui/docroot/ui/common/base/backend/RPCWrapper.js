/*
 * \brief backend RPC wrapper abstract base class
 *
 * \file RPCWrapper.js
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
 * SVN: $Id: RPCWrapper.js 3427 2010-06-23 10:47:27Z predragm $
 *
 */

Jedox.backend.RPCWrapper = (function ()
{
	// private static fields

	// private static methods

	// class constructor
	return function (onSuccess, onError, onTimeout)
	{
		// private fields

		// private methods

		// public fields
		this._onSuccess = onSuccess;
		this._onError = onError;
		this._onTimeout = onTimeout;

		this._isAsync = (onSuccess || onError || onTimeout) ? true : false;

		// privileged methods

		// constructor code
	};
}
)();

// public static fields

// public fields & methods
Jedox.backend.RPCWrapper.prototype = {

	  _dispatch: function (name, _class, _method, _args)
	{
		_args = Array.prototype.slice.call(_args);

		if (this._isAsync)
		{
			var rqst = new Jedox.backend.RPCAsyncRqst(_class, _method, _args),
					onSuccess, onError, onTimeout;

			if (this._onSuccess && (onSuccess = this._onSuccess[name]))
				rqst.setOnSuccess([ this._onSuccess, onSuccess ]);

			if (this._onError && (onError = this._onError[name]))
				rqst.setOnError([ this._onError, onError ]);

			if (this._onTimeout && (onTimeout = this._onTimeout[name]))
				rqst.setOnTimeout([ this._onTimeout, onTimeout ], this._timeout ? this._timeout : undefined);
		}
		else
			var rqst = new Jedox.backend.RPCSyncRqst(_class, _method, _args);

		if (this._hideErrors)
			rqst.hideErrors(this._hideErrors);

		return rqst.send();
	}

	, hideErrors: function (state)
	{
		this._hideErrors = state;

		return this;
	}

	, setTimeout: function (timeout)
	{
		this._timeout = timeout;

		return this;
	}

};
