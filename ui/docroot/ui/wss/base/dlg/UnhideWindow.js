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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: UnhideWindow.js 4784 2011-03-29 12:49:07Z lukap $
 *
 */

Jedox.wss.dlg.openUnhideDialog = function(){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.UnhideWindow());
};

Jedox.wss.dlg.UnhideWindow = (function() {

	return function () {

		Jedox.wss.dlg.UnhideWindow.parent.constructor.call(this);
		this.id = 'wUnhideWindow_dlg_wnd';
		var that = this;

		var _config = {
			winW: 200,
			listH: 100
		}

		var WinNameRecord = new Ext.data.Record.create([{
			name: 'index',
			name: 'name'
		}]);
		var storeWinNames = new Ext.data.SimpleStore({
			fields: [{
				name: 'index',
				name: 'name'
			}]
		});
		var dvWins = new Ext.DataView({
			id: 'wUnhideWindow_wbSel_dv',
			itemSelector: 'div.row-modeller',
			style: 'overflow:auto',
			singleSelect: true,
			store: storeWinNames,
			cls: 'modellerDataViewSelect',
			tpl: new Ext.XTemplate('<tpl for=".">', '<div class="row-modeller">', '<span>&#160;{name}</span>', '</div>', '</tpl>')
		});
		var paneldvWins = new Ext.Panel({
			layout: 'fit',
			style: 'margin-bottom: 5px',
			height: _config.listH,
			items: [dvWins]
		});

		function doUnhide(){
			if (dvWins.getSelectionCount() > 0)
			{
				try {
					var tmpWin = winList[storeWinNames.getAt(dvWins.getSelectedIndexes()[0]).get('index')],
							node = tmpWin.node;

					that.win.close();

					for (var triggers = Jedox.wss.events.triggers.unhideWorkbook_before, i = triggers.length - 1; i >= 0; i--)
						triggers[i][0]['unhideWorkbook_before'].call(parent, triggers[i][1], node._meta, node._name);

					tmpWin.show();
					tmpWin.toFront();
					Jedox.wss.wnd.active = tmpWin;
					Jedox.wss.action.adjustToACL();

					for (var triggers = Jedox.wss.events.triggers.unhideWorkbook_after, i = triggers.length - 1; i >= 0; i--)
						triggers[i][0]['unhideWorkbook_after'].call(parent, triggers[i][1], node._meta, node._name);
				} catch (e) {
					Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
				}
			}
		};

		// +++ Buttons +++ //
		var btnOk = (this.components.OK = new Ext.Button({
			id: 'wUnhideWindow_ok_btn',
			text: 'OK'.localize(),
			tabIndex: 2,
			handler: function(){
				doUnhide();
				that.win.close();
			}
		}));
		var btnClancel = (this.components.Cancel = new Ext.Button({
			id: 'wUnhideWindow_cancel_btn',
			text: 'Cancel'.localize(),
			tabIndex: 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(){
				that.win.close();
			}
		}));
		// --- Buttons --- //

		// *** Main Panel *** //
		var panelMain = this.containers.mainPanel = new Ext.Panel({
			autoHeight: true,
			layout: 'form',
			bodyStyle: 'padding: 5px 5px 0px; background-color: transparent;',
			items: [{bodyStyle: 'background-color:transparent;border:none;', html: "Unhide workbook".localize() + ':'}, paneldvWins]
		});

		// *** Window *** //
		this.win = new Ext.Window({
			id: 'wUnhideWindow_dlg_wnd',
			hidden: true,
			layout: 'fit',
			title: "Unhide".localize(),
			cls: 'default-format-window',
			width: _config.winW,
			autoHeight: true,
			closeAction: 'close',
			autoDestroy: true,
			plain: true,
			onEsc: Ext.emptyFn,
			modal: true,
			resizable: false,
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.unhideWindow);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
			items: [panelMain],
			buttons: [btnOk, btnClancel]
		});

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var winList = Jedox.wss.wnd.getHidden();
		for (var tmpRec, i=(winList.length - 1); i>=0; i--)
		{
			tmpRec = new WinNameRecord({
				index: i,
				name: winList[i].getName()
			});
			storeWinNames.add(tmpRec);
		}

		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.UnhideWindow, Jedox.dlg.Dialog);
