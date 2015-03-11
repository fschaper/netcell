/*
 * @brief ajax
 *
 * @file Group.js
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: WSSPlugin.js 4017 2010-10-14 12:28:14Z drazenk $
 *
 */

// implements WSSPlugin
Jedox.studio.plugin.WSSPlugin = (function ()
{



	// class constructor
	return function ()
	{
		this.handlerMethods = {
			  'openWorkbook_before': ['default']
			, 'openWorkbook_after': ['default']
			, 'closeWorkbook_before': ['default']
			, 'closeWorkbook_after': ['default']
            , 'switchWorkbook_before': ['default']
   			, 'switchWorkbook_after': ['default']
   			, 'saveAsWorkbook_before': ['default']
   			, 'saveAsWorkbook_after': ['default']
   			, 'newWorkbook_before': ['default']
   			, 'newWorkbook_after': ['default']
   			, 'hideWorkbook_before': ['default']
   			, 'hideWorkbook_after': ['default']
   			, 'unhideWorkbook_before': ['default']
   			, 'unhideWorkbook_after': ['default']
   			, 'importWorkbook_before': ['default']
   			, 'importWorkbook_after': ['default']
   			, 'openURL': ['default']
   			, 'openOther': ['default']
            , 'replaceNode_before': ['default']
   			, 'replaceNode_after': ['default']
		};

	}
}
)();



//public methods
Jedox.studio.plugin.WSSPlugin.prototype =
{

	getTriggerInfo: function() {
		return this.handlerMethods;
	},

	// Open Workbook.
	openWorkbook_before: function(ident, ghn, name, chkACLs) {

	},

	openWorkbook_after: function(ident, ghn, name) {

	},

	// Close Workbook.
	closeWorkbook_before: function(ident, ghn, name) {

	},

	closeWorkbook_after: function(ident, ghn, name) {

	},

	// Switch Workbook.
	switchWorkbook_before: function(ident, ghn, name) {

	},

	switchWorkbook_after: function(ident, ghn, name) {

	},

	// SaveAs Workbook.
	saveAsWorkbook_before: function(ident, oldGhn, oldName) {

	},

	saveAsWorkbook_after: function(ident, newGhn, oldName, newName) {

	},

	// New Workbook.
	newWorkbook_before: function(ident) {

	},

	newWorkbook_after: function(ident, name) {

	},

	// Hide Workbook.
	hideWorkbook_before: function(ident, ghn, name) {

	},

	hideWorkbook_after: function(ident, ghn, name) {

	},

	// Unhide Workbook.
	unhideWorkbook_before: function(ident, ghn, name) {

	},

	unhideWorkbook_after: function(ident, ghn, name) {

	},

	// Import Workbook.
	importWorkbook_before: function(ident, name) {

	},

	importWorkbook_after: function(ident, name, importOk) {

	},

	// Open URL.
	openURL: function(ident, url, target, title, chkACLs) {

	},

	// Open Other.
	openOther: function(ident, ghnt, target, chkACLs) {

	},

	// Replace Node.
	replaceNode_before: function(ident, oldGhn, oldName) {

	},

	replaceNode_after: function(ident, oldGhn, newGhn, newName) {

	}

}