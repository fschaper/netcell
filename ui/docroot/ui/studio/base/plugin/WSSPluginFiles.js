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
 * SVN: $Id: WSSPluginFiles.js 4964 2011-05-17 09:39:54Z srdjanv $
 *
 */

// implements WSSPlugin
Jedox.studio.plugin.WSSPluginFiles = (function ()
{
	// class constructor
	return function ()
	{
		Jedox.studio.plugin.WSSPluginFiles.parent.constructor.call(this);

		var that = this;
	}
}
)();

// WSSPluginFiles extends WSSPlugin
Jedox.util.extend(Jedox.studio.plugin.WSSPluginFiles, Jedox.studio.plugin.WSSPlugin);

//public methods
clsRef = Jedox.studio.plugin.WSSPluginFiles;

//clsRef.prototype.closeWorkbook_after = function(ident, ghn, name) {
//	console.log('WSSPluginFiles - closeWorkbook_after | '.concat('ident=', ident[0], ' ghn=', ghn.g, '/', ghn.h, '/', ghn.n, ' name=', name));
//};




	clsRef.prototype.openWorkbook_before = function(ident, ghn, name, chkACLs) {
			if(chkACLs)
				Ext.getCmp('wt-panel').triggerOpenWB_beforeFromWSS(ghn, name);
	};

	clsRef.prototype.openWorkbook_after = function(ident, ghn, name) {
		openWorkbook_before_flag = true;
		Ext.getCmp('wt-panel').triggerOpenWBFromWSS(ghn, name);
	};


	// Close Workbook.
	clsRef.prototype.closeWorkbook_before = function(ident, ghn, name) {

	};

	clsRef.prototype.closeWorkbook_after = function(ident, ghn, name) {

		Ext.getCmp('wt-panel').triggerCloseWBFromWSS(ghn, name);

	};

	// Switch Workbook.
	clsRef.prototype.switchWorkbook_before = function(ident, ghn, name) {

		Ext.getCmp('wt-panel').triggerSwitchWBFromWSS(ghn, name);

	};

	clsRef.prototype.switchWorkbook_after = function(ident, ghn, name) {

	};

	// SaveAs Workbook.
	clsRef.prototype.saveAsWorkbook_before = function(ident, oldGhn, oldName) {

	};

	clsRef.prototype.saveAsWorkbook_after = function(ident, newGhn, oldName, newName) {

		Ext.getCmp('wt-panel').triggerSaveAsFromWSS(newGhn, oldName, newName);

	};

	// New Workbook.
	clsRef.prototype.newWorkbook_before = function(ident) {

	};

	clsRef.prototype.newWorkbook_after = function(ident, name) {

		Ext.getCmp('wt-panel').triggerNewWBFromWSS(name);

	};

	// Hide Workbook.
	clsRef.prototype.hideWorkbook_before = function(ident, ghn, name) {

		Ext.getCmp('wt-panel').triggerHideWBFromWSS(ghn, name);

	};

	clsRef.prototype.hideWorkbook_after = function(ident, ghn, name) {

	};

	// Unhide Workbook.
	clsRef.prototype.unhideWorkbook_before = function(ident, ghn, name) {

		Ext.getCmp('wt-panel').triggerUnhideWBFromWSS(ghn, name);

	};

	clsRef.prototype.unhideWorkbook_after = function(ident, ghn, name) {

	};

	// Import Workbook.
	clsRef.prototype.importWorkbook_before = function(ident, name) {

	};

	clsRef.prototype.importWorkbook_after = function(ident, name, importOk) {

		Ext.getCmp('wt-panel').triggerImportWBFromWSS(name);

	};

	//Open hyperlink
	clsRef.prototype.openURL = function(ident, url, target, title, chkACLs) {

		Ext.getCmp('wt-panel').triggerOpenURLFromWSS(url, title, target, chkACLs);

	};

	clsRef.prototype.openOther = function(ident, ghnt, target, chkACLs) {

		Ext.getCmp('wt-panel').triggerOpenStaticFromWSS(ghnt, target, chkACLs);

	};

	// Replace Node.
	clsRef.prototype.replaceNode_before = function(ident, oldGhn, oldName) {

	};

	clsRef.prototype.replaceNode_after = function(ident, oldGhn, newGhn, newName) {

		Ext.getCmp('wt-panel').triggerReplaceNodeFromWSS(oldGhn, newGhn, newName);

	};


clsRef = null;