/*
 * @brief wss file
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: events.js 4267 2010-11-08 12:57:52Z drazenk $
 *
 */

Jedox.wss.events = new function() {

	this.WSSPlugin = new Jedox.util.Interface('WSSPlugin', [
		                   'openWorkbook_before'
		                 , 'openWorkbook_after'
		                 , 'closeWorkbook_before'
		                 , 'closeWorkbook_after'
		                 , 'switchWorkbook_before'
		                 , 'switchWorkbook_after'
		                 , 'saveAsWorkbook_before'
		                 , 'saveAsWorkbook_after'
		                 , 'newWorkbook_before'
		                 , 'newWorkbook_after'
		                 , 'hideWorkbook_before'
		                 , 'hideWorkbook_after'
		                 , 'unhideWorkbook_before'
		                 , 'unhideWorkbook_after'
		                 , 'importWorkbook_before'
		                 , 'importWorkbook_after'
		                 , 'openURL'
		                 , 'openOther'
		                 , 'replaceNode_before'
		                 , 'replaceNode_after'
		              ]);

	this.triggers = {
		  'openWorkbook_before': []
		, 'openWorkbook_after': []
		, 'closeWorkbook_before': []
		, 'closeWorkbook_after': []
		, 'switchWorkbook_before': []
		, 'switchWorkbook_after': []
		, 'saveAsWorkbook_before': []
		, 'saveAsWorkbook_after': []
		, 'newWorkbook_before': []
		, 'newWorkbook_after': []
		, 'hideWorkbook_before': []
		, 'hideWorkbook_after': []
		, 'unhideWorkbook_before': []
		, 'unhideWorkbook_after': []
		, 'importWorkbook_before': []
		, 'importWorkbook_after': []
		, 'openURL': []
		, 'openOther': []
		, 'replaceNode_before': []
		, 'replaceNode_after': []
	};

	var _disabled = {};

	this.registerPlugin = function (plugin) {
		try {
			Jedox.util.Interface.ensureImplements(plugin, this.WSSPlugin);

			var events = plugin.getTriggerInfo();

			for (var event in events)
				if (this.triggers[event] != undefined)
					this.triggers[event].push([plugin, events[event]]);

			return true;
		} catch (e) {
			console.log(e);
			return false;
		}
	};

	this.disableEvents = function (events) {
		for (var i = events.length - 1; i >= 0; i--) {
			if (this.triggers[events[i]]) {
				_disabled[events[i]] = this.triggers[events[i]];
				this.triggers[events[i]] = [];
			}
		}
	};

	this.enableEvents = function (events) {
		for (var i = events.length - 1; i >= 0; i--) {
			if (_disabled[events[i]]) {
				this.triggers[events[i]] = _disabled[events[i]];
				delete _disabled[events[i]];
			}
		}
	};

}