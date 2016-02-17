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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: Open.js 4892 2011-04-26 13:53:45Z lukap $
 *
 */

Jedox.wss.dlg.openOpenDialog = function(OSflag, cb) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.OpenDialog(OSflag, cb));
};

Jedox.wss.dlg.OpenDialog = (function() {
	//OSflag Open || Save As flag
	//alert(OSflag);

	return function(OSflag, cb) {

		Jedox.wss.dlg.OpenDialog.parent.constructor.call(this);
		this.id = 'openDialog';
		var that = this;

		if (Jedox.wss.app.environment != null) {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}


		var title;
		var btn;
		var _configObj = {
			winHeight:400
		}

		/*
		 * Win title Save As || Open
		 * Btn Save || Open
		 * Cmb Save as type || Files of type
		 */

		var closeWinFnc = function (){
			that.win.close();
			if (OSflag === 'saveqp') Jedox.gen.load(Jedox.wss.app.dynJSRegistry.quickPublish);
		}

		var browsePanel = this.containers.mainPanel = new Jedox.wss.dlg.Browse(OSflag, closeWinFnc);
		this.containers.browseTbar = Ext.getCmp('browseToolbarHolder').getTopToolbar();
		this.cmpFocus = Ext.getCmp('wFiles_fileNameBrowse_cmb');

		var openBtn = {
			id: 'wOpen_open_btn',
			text: 'Open'.localize(),
			tabIndex: 101,
			handler: function(){
				browsePanel.onOpen();
			}
		}

		var saveBtn = {
			id: 'wOpen_save_btn',
			text: 'Save'.localize(),
			tabIndex: 102,
			handler: function(){
				browsePanel.onSave(cb);
			}
		}

		var cancelBtn = this.components.CANCEL = {
			id: 'wOpen_cancel_btn',	
			text: 'Cancel'.localize(),
			tabIndex: 103,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(){
				that.win.close();
			}
		}


		function initInterface(){
			if (OSflag === 'open'){
				title = 'Open'.localize();
				btn = openBtn;
			}
			else {
				title = 'Save As'.localize();
				btn = saveBtn;
				_configObj.winHeight +=20;
			}

			that.components.OK = btn;
		}

		initInterface();


	//############################### Open Dialog window ######################################

		this.win = new Ext.Window({
					id:'open-dlg',
					title:title,
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        cls: 'default-format-window',
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 600,
					height: _configObj.winHeight,
					//plain: true,
					items: browsePanel,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.open);
							that.close();
							Jedox.backend.studio.removeFromSessionCurrGH('wss');
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},

					buttons: [btn, cancelBtn]

		});


		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.OpenDialog, Jedox.dlg.Dialog);