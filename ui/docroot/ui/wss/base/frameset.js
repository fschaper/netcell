/*
 * \brief frameset handling routines
 *
 * \file frameset.js
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
 * SVN: $Id: frameset.js 5123 2011-07-18 10:21:59Z drazenk $
 *
 */

Jedox.wss.frameset = new function ()
{
	var that = this;

	this.load = function (cb, name, group, hierarchy, ext, pc)
	{
		Jedox.wss.general.chkState();

		if (!ext)
			ext = {appmode: Jedox.wss.app.appMode};
		else
			ext.appmode = Jedox.wss.app.appMode;

		var rqst = new Jedox.backend.RPCAsyncRqst('WSS', 'loadFrameset', [ name, group, hierarchy, ext ]);

		rqst.setOnSuccess([ this, this.load_post, cb, { g: group, h: hierarchy, n: name, v: false }, pc, arguments ]).send();

		return true;
	};

	this.load_post = function (res, cb, meta, pc, args)
	{
		var wnd = Jedox.wss.wnd,
			hasCb = cb instanceof Array && cb.length > 1;

		if (!res[0])
		{
			if (!res[1].search(/^follHL*/i) && hasCb)
				cb[1].call(cb[0], res[1]);

			Jedox.wss.general.showMsg('Application Error'.localize(), 'errLoadFS_intro'.localize().concat(' ', res[1].localize()), Ext.MessageBox.ERROR, [this, wnd.triggerCloseEvt, null, meta]);

			return false;
		}
	};

	this.recover = function(cb, win) {
		win._execClose = false;
		win.close();

		if (cb instanceof Array && cb.length > 1)
			cb[1].apply(cb[0], cb.slice(2));
	};

};