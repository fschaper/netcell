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
 * SVN: $Id: RenameSheet.js 4585 2011-02-09 10:48:29Z srdjanv $
 *
 */
Jedox.wss.dlg.openRenameSheet = function(sheetID, sheetTitle) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.RenameSheet(sheetID, sheetTitle));
};

Jedox.wss.dlg.RenameSheet = (function() {

	return function(sheetID, sheetTitle){

		Jedox.wss.dlg.RenameSheet.parent.constructor.call(this);
		this.id = 'renameSheet';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		//================================ Components ============================================

		var sheetNewNameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'New Name'.localize(),
			//emptyText:sheetTitle,
			value:sheetTitle,
			enableKeyEvents: true,
			width: 135,
			tabIndex: 1
		});

		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						modal:true,
						layout: 'form',
						baseCls:'main-panel',
						border:false,
						items:sheetNewNameTxf
		});


		//================================Functions ============================================

		// TO DO (validating rules)
		function isNameValid(){
			var name=sheetNewNameTxf.getValue();
			if (name.length<3){
				sheetNewNameTxf.markInvalid('Sheet Name specified is not a valid!');
				return false;
			}
			else
				return true;
		}

		function rename ()
		{
			if (!isNameValid())
				return;

			var newName = sheetNewNameTxf.getValue();

			Jedox.backend.ccmd( [ this, rename_post, newName ], [ 'oren', 2, newName ]);
		}

		function rename_post (res, newName)
		{
			if (res[0][0] === true)
				Ext.getCmp(sheetID).setTitle(newName);

			that.win.close();
		}

		function showWarrningMessage(name){
			win.hide();
			var informationMsg = 'informationMsg'.localize();
			var adviceMsg = 'adviceMsg'.localize();
			Ext.Msg.show({
			   title:'Rename Sheet'.localize() + '?',
			   msg: '<b>' + name +'</b> '+ informationMsg +'?' +'<br>' + adviceMsg + '.',
			   buttons: Ext.Msg.OK,
			   fn: function() {win.show();sheetNewNameTxf.selectText();sheetNewNameTxf.focus(true, true);},
			   animEl: 'elId',
			   width:320,
			   icon: Ext.MessageBox.ERROR
			});
		}

		sheetNewNameTxf.on('specialKey', function(txf, e){
			if (e.getKey()==13)
				rename();
		});

		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'Rename Sheet'.localize(),
					closable: true,
					cls: 'default-format-window',
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 280,
					height: 110,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.renameSheet);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},
					buttons: [
							(this.components.OK = new Ext.Button({
								text: 'Rename'.localize(),
								tabIndex: 2,
								handler: function(){
									rename();
									that.win.close();
								}
							})),
							(this.components.Cancel = new Ext.Button({
								text: 'Cancel'.localize(),
								tabIndex: 3,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler: function(){
									that.win.close();
								}
							}))
					          ]

		});

		this.setContext();
		this.win.show(this);
	};
})();

Jedox.util.extend(Jedox.wss.dlg.RenameSheet, Jedox.dlg.Dialog);