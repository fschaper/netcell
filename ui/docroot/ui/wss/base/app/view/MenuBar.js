/*
 * @brief ajax
 *
 * @file MenuBar.js
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
 * SVN: $Id: MenuBar.js 5128 2011-07-18 14:31:43Z predragm $
 *
 */

Jedox.wss.app.initMenuBar = function () {
	var menu = Jedox.wss.app.menubar = {};

	// Create Menubar and place it in Jedox.wss.app namespace.
	Jedox.wss.app.Menu = new Ext.Toolbar({
		cls: "extmenubar"
	});

    // Create FileMenu items.
    var fileMenuItems = [
		{text: "Export".localize(), menu: {
				items: [
				  {text: "XLSX Snapshot".localize(), iconCls: "icon_file_xlsx", handler: function () { Jedox.wss.action.exportToXLSX(true); } },
					{text: "PDF".localize(), iconCls: "icon_file_pdf", handler: Jedox.wss.action.exportToPDF, disabled: !Jedox.wss.app.fopper},
					{text: "HTML".localize(), iconCls: "icon_file_html", handler: Jedox.wss.action.exportToHTML}
				]
			}
		},
		//"-",
		//{text: "Save Workspace".localize().concat('...'), disabled: true},
		//{text: "File Search".localize(), disabled: true},
		"-",
		//{text: "Page Setup".localize().concat('...'), disabled: true},
		//{text: "Print Area".localize(), disabled: true},
		{text: "Print Preview".localize(), handler: Jedox.wss.action.exportToHTML}
		//{text: "Print".localize().concat('...'), disabled: true},
		//"-",
		//{text: "Send to".localize(), disabled: true},
		//{text: "Properties".localize(), disabled: true}
	],
		enaRestr = !Jedox.wss.app.UPRestrictMode,
		theme = Jedox.wss.app.theme;

//	if (enaRestr)
//		fileMenuItems.splice(0, 0, {text: "Close".localize(), disabled: true}, '-');

	if (!enaRestr && window.opener != null)
		fileMenuItems.splice(0, 0, {iconCls: 'iconclose', text: "Close".localize(), tooltip: "Close".localize(), handler: function() {window.close();}}, '-');

	// Create menu items.
    Jedox.wss.app.Menu.add(

		// ###############
		// #     FILE    #
		// ###############

    	{
			text: "File".localize(),
			cls: "extmenubaritem",
			menu: (menu.fileMenu = new Ext.menu.Menu({
		        id: "wMenuBar_file_mn",
		        items: fileMenuItems
			}))
		},


		// ###############
		// #     EDIT    #
		// ###############

        {text: "Edit".localize(),
        cls: "extmenubaritem",
		menu: new Ext.menu.Menu({
        	id: "wMenuBar_edit_mn",
        	items: [
				//{text: "Can\'t Undo".localize(), disabled: true},
				//{text: "Can\'t Repeat".localize(), disabled: true},
				//"-",
				{text: "Cut".localize(), iconCls: 'icon_cut', handler: function(){Jedox.wss.action.cut(false);}},
				{text: "Copy".localize(), iconCls: 'icon_copy', handler: function(){Jedox.wss.action.copy(false);}},
				//{text: "WSS Clipboard".localize().concat('...'), disabled: true},
				{text: "Paste".localize(), iconCls: 'icon_paste', handler: Jedox.wss.action.paste}
			]
        })},

        // ###############
		// #     VIEW    #
		// ###############
        {text: "View".localize(),
        cls: "extmenubaritem",
		menu: new Ext.menu.Menu({
        	id: "wMenuBar_view_mn",
        	items: [
				//{text: "Normal".localize(), disabled: true},
				//{text: "Page Break Preview".localize(), disabled: true},
				//"-",
				{text: "Toolbars".localize(), enableToggle: true, checked: !Jedox.wss.app.initHideToolbar, checkHandler: function(btn, state){Jedox.wss.app.hideShowToolbar(state, '');}},
				{text: "Status Bar".localize(), enableToggle: true, checked: !Jedox.wss.app.initHideStatusBar, checkHandler: function(btn, state){Jedox.wss.app.statusBar.hideShow(state);}}
				//,
				//"-",
				//{text: "Full Screen".localize(), disabled: true}
				//{text: "Zoom".localize().concat('...'), disabled: true}
			]
        })},

        // ###############
		// #     DATA    #
		// ###############
        {
        	text: "Data".localize(),
            cls: "extmenubaritem",
    		menu: new Ext.menu.Menu({
	        	id: "wMenuBar_data_mn",
	        	items: [
		  			  { text: 'Refresh Data'.localize(), id:'wMenuBar_dataRDt_btn', handler: function () { Jedox.wss.sheet.refresh(); } }
		    		, { text: 'Auto-Refresh Data'.localize(), id: 'wMenuBar_dataARDt_btn', enableToggle: true, checked: false,
		    				checkHandler: function () { this.checked ? Jedox.gen.load(Jedox.wss.app.dynJSRegistry.autoRefreshStart) : Jedox.wss.book.autoRefresh(0); }
		  			  }
						, '-'
						, { text: 'Auto-Calculate Data'.localize(), id: 'wMenuBar_dataACDt_btn', enableToggle: true, checked: false,
								checkHandler: function () { Jedox.wss.general.autoCalc(this.checked); }
							}
	    		],
				listeners: {
					beforeshow: function ()
					{
						var aBook = Jedox.wss.app.activeBook;
						this.items.get('wMenuBar_dataARDt_btn').setChecked(aBook && aBook._autoRefresh > 0, true);

						this.items.get('wMenuBar_dataACDt_btn').setChecked(Jedox.wss.app.autoCalc, true);
					}
				}
    		})
        }
    );

    // ###############
	// #    WINDOW   #
	// ###############
	if (enaRestr)
		Jedox.wss.app.Menu.add(
	        {
	        	text: "Window".localize(),
	        	cls: "extmenubaritem",
	        	menu: (menu.windowMenu = new Ext.menu.Menu(
	        		{
	        			id: "wMenuBar_window_mn",
	        		    items: [
        					//{text: "New Window".localize(), disabled: true},
        					{ text: 'Arrange'.localize().concat('...'), handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.arrangeWindows); } },
        					//{text: "Compare Side by Side with".localize().concat('...'), disabled: true},
        					{ text: 'Hide'.localize(), handler: function() { Jedox.wss.wnd.hideActive(); } },
        					{ text: 'Unhide'.localize().concat('...'), handler: function() { Jedox.gen.load(Jedox.wss.app.dynJSRegistry.unhideWindow); } }
	        			],
	    					listeners: {
	    						beforeshow: function ()
	    						{
	    							var wndReg = Jedox.wss.wnd.reg,
	    									lnks = this.find('_lnk', ''),
	    									cnt = 0;

	    							for (var i = lnks.length - 1; i >= 0; --i)
	    								this.remove(lnks[i]);

	    							for (var id in wndReg)
	    								this.addMenuItem({ _lnk: '', _id: id, text: ''.concat(++cnt, '. ', wndReg[id].getName()), handler: function (item) { Jedox.wss.wnd.selectById(item.initialConfig._id); } });
	    						}
	    					}
	        		}
	        	))
			}
	    );

	// ###############
	// #     HELP    #
	// ###############

	Jedox.wss.app.Menu.add({
		text: "Help".localize(),
        cls: "extmenubaritem",
		menu: new Ext.menu.Menu({
        	id: "wMenuBar_help_mn",
        	items: [
				//{text: "Worksheet-Server Help".localize(), disabled: true},
				//"-",
				{text: "Jedox Online".localize(), href: "http://www.jedox.com"}
				//{text: "Contact us".localize(), disabled: true},
				//"-",
				//{text: "Check for Updates".localize(), disabled: true},
				//{text: "Customer Feedback Options".localize(), disabled: true},
				//"-",
				//{text: "About Palo Suite".localize(), disabled: true}
			]
        })}
	);

	Jedox.wss.app.Menu.render("MenuPlaceholder");
};