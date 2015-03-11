/*
 * @brief ajax
 *
 * @file ribbon.js
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
 *
 * \version
 * SVN: $Id: ribbon.js 4624 2011-02-14 21:59:31Z predragm $
 *
 */

Jedox.wss.app.initRibbon = function () {
	var ribbon = Jedox.wss.app.toolbar = {},
		enaRestr = !Jedox.wss.app.UPRestrictMode,
		fileItems = [
		    {
		        text: "Refresh".localize(),
		        scale: 'large',
		        rowspan: 3,
				width:40,
		        iconCls: 'refresh-icon',
		        iconAlign: 'top',
				tooltip: "Refresh / Recalculate".localize(),
				handler: function () {Jedox.wss.sheet.refresh();}
		    }
		];

	if (window.opener != null)
		fileItems.push(
			{
	            text: 'Close',
				iconCls: 'close-icon',
				tooltip: "Close".localize(),
				handler: function() {window.close();}
	        }
		);

	// Ribon Tabs.

	// ###############
	// #     HOME    #
	// ###############
   var home =  new Ext.Panel({
        title: 'Home',
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
            title: 'File',
            height: 90,
            items: fileItems
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Clipboard',
            height:90,
            items: [{
                text: 'Paste',
                scale: 'large',
                rowspan: 3,
                iconCls: 'paste-icon32',
                iconAlign: 'top',
				width:40,
                arrowAlign:'bottom',
				tooltip: "Paste".localize(),
				disabled: true,
				handler: Jedox.wss.action.paste
            },{
                text: 'Cut',
				iconCls: 'cut-icon',
				handler: function(){Jedox.wss.action.cut(false);}
            },{
                text: 'Copy',
				iconCls: 'copy-icon',
				handler: function(){Jedox.wss.action.copy(false);}
            }]
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Export'.localize(),
            height:90,
            items: [{
                text: 'HTML'.localize(),
                scale: 'large',
                rowspan: 3,
				width:40,
                iconCls: 'printpreview-icon32',
                iconAlign: 'top',
				handler: Jedox.wss.action.exportToHTML
            },{
				text: '&nbsp;'.concat('PDF'.localize(), '&nbsp;'),
                scale: 'large',
                rowspan: 3,
				width:40,
                iconCls: 'printtopdf-icon32',
                iconAlign: 'top',
				tooltip: "Print To PDF".localize(),
				handler: Jedox.wss.action.exportToPDF,
				disabled: !Jedox.wss.app.fopper
            }]
        }]
    });

   	// ###############
	// # PAGE LAYOUT #
	// ###############
	var pageLayout = new Ext.Panel({
        title: 'Page Layout',
        tbar: [{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Themes'.localize(),
			bodyStyle: 'padding:0px 10px 0px 10px',
			height:90,
            items: [{
				xtype:'splitbutton',
				text: "Theme".localize(),
				iconCls:'themeblue-icon32',
				scale: 'large',
				rowspan: 3,
				width:40,
				iconAlign: 'top',
				arrowAlign:'bottom',
				menu: (ribbon.themeMenu = new Ext.menu.Menu({
					items: [
							{text: "Blue (default)".localize(), id: 'theme-default', enableToggle: true, checked: true, checkHandler: Jedox.wss.action.switchTheme},
							{text: "Gray".localize(), id: 'theme-gray', enableToggle: true, checked: false, checkHandler: Jedox.wss.action.switchTheme},
							{text: "Dark".localize(), id: 'theme-slate', enableToggle: true, checked: false, checkHandler: Jedox.wss.action.switchTheme}
						]
				}))
			}]
        },{
            xtype: 'buttongroup',
            columns: 2,
            title: 'Page Setup',
            height:90,
            items: [{
                text: 'Print<br>Preview',
                scale: 'large',
                rowspan: 3,
				width:40,
                iconCls: 'printpreview-icon32',
                iconAlign: 'top',
				handler: Jedox.wss.action.exportToHTML
            },{
                text: 'Page Setup',
				iconCls: 'pagesetup-icon',
				handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pageSetup);}
            }]
        }]
    });


	// ################
	// #   FORMULAS   #
	// ################
	var formulas = new Ext.Panel({
        title: 'Formulas',
        tbar: [{
            xtype: 'buttongroup',
            columns: 2,
			height:90,
			title: 'Calculation',
            items: [{
                text: 'Refresh<br>Data'.localize(),
				iconCls:'refresh-icon',
				scale: 'large',
                rowspan: 3,
				width:50,
				iconAlign: 'top',
				handler: function () { Jedox.wss.sheet.refresh(); }
            }, {
				xtype: 'checkbox',
				id: 'autoRefreshDataMenu',
                boxLabel: 'Auto - Refresh Data',
 				enableToggle: true,
				checked: false,
				handler: function () { this.checked ? Jedox.gen.load(Jedox.wss.app.dynJSRegistry.autoRefreshStart) : Jedox.wss.book.autoRefresh(0); },
				listeners: {
					beforeshow: function () { this.items.get('autoRefreshDataMenu').setChecked(Jedox.wss.app.activeBook._autoRefresh > 0, true); }
				}
            }]
        }]
    });


	// ###############
	// #     VIEW    #
	// ###############
	var view = new Ext.Panel({
        title: 'View',
        tbar: [{
            xtype: 'buttongroup',
            columns: 1,
            title: 'Show/Hide',
			bodyStyle: 'padding:0px 10px 0px 10px; ',
			width:400,
			height:90,
            items: [
//	            {
//					xtype: 'checkbox',
//					boxLabel: "Toolbars".localize(),
//					enableToggle: true,
//					checked: true,
//					handler: function(btn, state){Jedox.wss.app.hideShowToolbar(state, '');}
//				},
				{
					xtype: 'checkbox',
					boxLabel: "Status Bar".localize(),
					enableToggle: true,
					checked: true,
					handler: function(btn, state){Jedox.wss.app.statusBar.hideShow(state);}
				}
			]
        },{
            xtype: 'buttongroup',
         	columns: 2,
			bodyStyle: 'padding:0px 10px 10px 10px; ',
			height:90,
            title: 'Window',
            items: [{
                text: 'Arrange <br>All',
                scale: 'large',
				width:50,
                rowspan: 3,
                iconCls: 'arrangeall-icon32',
                iconAlign: 'top',
				handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.arrangeWindows); }
            },{
                text: 'Hide',
				iconCls: 'hide-icon',
				 handler: function() { Jedox.wss.wnd.hideActive(); }
            },{
                text: 'Unhide',
				iconCls: 'unhide-icon',
				handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.unhideWindow); }
            },{
                xtype:'splitbutton',
                text: 'Open documents'.localize(),
				iconCls: 'unhide-icon',
				disabled: !enaRestr,
				menu: (ribbon.openDocs = new Ext.menu.Menu())
            }]
        }]
    });

	// ###############
	// #     HELP    #
	// ###############
	var help = new Ext.Panel({
        title: 'Help',
        tbar: [
			{
			    xtype: 'buttongroup',
			 	columns: 1,
				bodyStyle: 'padding:0px 10px 10px 10px; ',
				height:90,
			    title: 'Window',
			    items: [
				    {
				        text: "Jedox Online".localize(),
						iconCls: 'hide-icon',
						handler:function(){window.open("http://www.jedox.com" ,"_blank")}
				    }
//				  {
//						text: "About Palo Suite".localize(),
//						iconCls: 'hide-icon',
//					}
				]
			}
		]
	});


	//Ribbon panel
	Jedox.wss.app.ribbon = new Ext.TabPanel({
		id:'ribbon-view-panel',
		layoutOnTabChange: true,
		activeTab: 0,
		renderTo: 'ribbon',
		items: [home, pageLayout, formulas, view, help]
	});

};