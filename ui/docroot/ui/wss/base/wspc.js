/*
 * \brief routines handling workspace
 *
 * \file wspc.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: wspc.js 4206 2010-10-27 13:58:41Z srdjanv $
 *
 */

Jedox.wss.wspc = new function ()
{
	var that = this;

	this.dom = document.getElementById('workspace');

	this.resize = function ()
	{
		var height = (window.innerWidth ? window.innerHeight : document.documentElement.clientHeight)
								 - document.getElementById('barsContainer').offsetHeight - document.getElementById('statusBarContainer').offsetHeight;

		that.dom.style.height = ''.concat(height, 'px');

		var wndreg = Jedox.wss.wnd.reg,
				width = that.dom.offsetWidth,
				win;

		for (var id in wndreg)
		{
			win = wndreg[id];

			if (win._minimized)
				win.setPosition(win.getPosition()[0], height - win.header.getSize().height - 2);
			else if (win.maximized)
				win.setSize(width, height);
		}

		if(Jedox.wss.app.toolbar && Jedox.wss.app.toolbar.resize)
			Jedox.wss.app.toolbar.resize();
	}

	this.getHeight = function ()
	{
		return parseInt(this.dom.style.height);
	};

	this.resize();
}