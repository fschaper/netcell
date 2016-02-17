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
 *
 * \version
 * SVN: $Id: Toolbars.js 4676 2011-03-07 14:47:33Z lukap $
 *
 */

Jedox.wss.app.initActiveToolbars = function () {
	Jedox.wss.app.initStandardToolbar();
};

Jedox.wss.app.initStandardToolbar = function () {
	// Create StandardToolbar and place it in Jedox.wss.app namespace.
    var stdTbar = Jedox.wss.app.standardToolbar = new Ext.Toolbar({
    	cls: "wssUserMenubar",
    	renderTo: 'wssStandardToolbar',
    	items: [
			//{iconCls: 'iconback', text: "Back".localize(), tooltip: "Back To".localize().concat('...')},
			//{icon: 'res/img/bar/ico_home.png', cls: 'x-btn-icon', tooltip: "Home".localize()},
			{iconCls: 'iconrecalcnow', text: "Refresh".localize(), tooltip: "Refresh / Recalculate".localize(), handler: function () {Jedox.wss.sheet.refresh();}},
			'-',
			{iconCls: 'icon_copy', cls: 'x-btn-icon', tooltip: "Copy".localize(), handler: function(){Jedox.wss.action.copy(false);}},
			{iconCls: 'icon_cut', cls: 'x-btn-icon', tooltip: "Cut".localize(), handler: function(){Jedox.wss.action.cut(false);}},
			{iconCls: 'icon_paste', cls: 'x-btn-icon', tooltip: "Paste".localize(), handler: Jedox.wss.action.paste},
			'-',
			//{iconCls: 'iconprint', text: "Print".localize(), tooltip: "Print".localize()},
			{iconCls: 'iconprintpreview', text: "Print Preview".localize(), tooltip: "Print Preview".localize(), handler: Jedox.wss.action.exportToHTML},
			{iconCls: 'iconprinttopdf', text: "PDF".localize(), tooltip: "Print To PDF".localize(), handler: Jedox.wss.action.exportToPDF, disabled: !Jedox.wss.app.fopper}
			//'-',
			//{iconCls: 'icondownload', text: "Download".localize(), tooltip: "Download Workbook".localize()},
			//{iconCls: 'iconoptions', text: "Options".localize(), tooltip: "Options".localize()},
			//{iconCls: 'iconhelp', text: "Help".localize(), tooltip: "Help".localize()},
    	]
    });

    if (window.opener != null)
    	stdTbar.add(
			'-',
			{id: 'wUserMode_close_btn', iconCls: 'iconclose', text: "Close".localize(), tooltip: "Close".localize(), handler: function() {window.close();}}
    	);

    stdTbar.doLayout();
};