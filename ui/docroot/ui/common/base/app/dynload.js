/*
 * @brief wss/studio file
 *
 * Copyright (C) 2006-2009 Jedox AG
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: dynload.js 4424 2010-12-09 12:25:35Z srdjanv $
 *
 */

Jedox.gen.load = function(cmd, args) {
	args= args || [0];

	function execFunc() {
		var func = cmd[6].length ? Jedox[cmd[6]] : Jedox;

		for (path = cmd[1], i = 0; i < path.length; i++)
			func = func[path[i]];

		func[cmd[2]].apply(document.all ? new Object() : this, args);
	}

	if (cmd[3] && cmd[4] && cmd[2].length > 0) {
		execFunc();
		return;
	}

	var that = this, url = cmd[5]
		allScripts = document.getElementsByTagName('script');

	for (var path = cmd[1], i = 0; i < path.length; i++)
		url = url.concat('/', path[i]);
	url = url.concat('/', cmd[0]);

	for (i = 0; i < allScripts.length; i++)
		if (allScripts[i].src && allScripts[i].src.indexOf(url) != -1) {
			cmd[4] = true;

			if (cmd[2].length > 0)
				execFunc();

			return;
		}

	var newJS = document.createElement('script');
	newJS.type = "text/javascript";
	newJS.src = url.concat('?', new Date().getTime());
	newJS.id = url;

	newJS.onload = newJS.onreadystatechange = function() {
		if (this.readyState && this.readyState == "loading")
			return;
		else {
			cmd[4] = true;
			if (cmd[2].length > 0)
					execFunc();
		}
	}

	newJS.onerror = function() {
		docBody.removeChild(newJS);
		cmd[4] = false;
		console.log('Loading error: '.concat(url));
	}

	var docBody = document.getElementsByTagName("body")[0];
	docBody.appendChild(newJS);
}

Jedox.gen.dynJSAutoload = function(dynJSReg) {
	var docBody = document.getElementsByTagName("body")[0];

	for (var dynjs in dynJSReg) {
		if (dynJSReg[dynjs][3]) {
			for (var url = dynJSReg[dynjs][5], path = dynJSReg[dynjs][1], i = 0; i < path.length; i++)
				url = url.concat('/', path[i]);
			url = url.concat('/', dynJSReg[dynjs][0]);

			var newJS = document.createElement('script');
			newJS.type = "text/javascript";
			newJS.src =	url.concat('?', new Date().getTime());
			newJS.id = url;
			docBody.appendChild(newJS);

			dynJSReg[dynjs][4] = true;
		}
	}
}

Jedox.gen.unload = function(cmd) {
	if (cmd[3] || !cmd[4])
		return;

	var url = cmd[5],
		allScripts = document.getElementsByTagName("script");

	for (var path = cmd[1], i = 0; i < path.length; i++)
		url = url.concat('/', path[i]);
	url = url.concat('/', cmd[0]);

	for (var i = allScripts.length - 1; 0 <= i; i--) {
		if (allScripts[i].id == url) {
			document.getElementsByTagName("body")[0].removeChild(allScripts[i]);
			cmd[4] = false;
			return;
		}
	}
}