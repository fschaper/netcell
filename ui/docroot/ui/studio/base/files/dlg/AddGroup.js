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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: AddGroup.js 4854 2011-04-15 13:53:28Z lukap $
 *
 */

Jedox.studio.files.dlg.openAddGroup = function(operation, fn, groupNameList){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.AddGroup(operation, fn, groupNameList));
};

Jedox.studio.files.dlg.AddGroup = (function(){

	// class constructor
	return function (operation, fn, groupNameList) {

		Jedox.studio.files.dlg.AddGroup.parent.constructor.call(this);

		this.id = 'addGroup';
		var that = this;


		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;


		//================================ Components ============================================

		var groupNameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Group Name-new'.localize(),
			tabIndex: 1,
			id: 'sFilesAddGroup_name_txt',
			labelStyle: 'font-size:11px;',
			//emptyText:sheetTitle,
			enableKeyEvents: true,
			width: 150
		});


		var descriptionTxa = new Ext.form.TextArea({
			fieldLabel: 'Description'.localize(),
			labelStyle: 'font-size:11px;',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			id: 'sFilesAddGroup_desc_tx',
			cls: 'preview-properties-panel',
			name: 'description',
			width: 150
		});

		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						modal:true,
						layout: 'form',
						baseCls:'main-panel',
						border:false,
						items:[groupNameTxf, descriptionTxa]
		});


		//================================Functions ============================================

		// TO DO (validating rules)
		function showWarrningMessage(name){
			that.win.hide();
			var informationMsg = 'informationMsg'.localize();
			var adviceMsg = 'adviceMsg'.localize();
			Ext.Msg.show({
			   title:'Rename Sheet'.localize() + '?',
			   msg: '<b>' + name +'</b> '+ informationMsg +'?' +'<br>' + adviceMsg + '.',
			   buttons: Ext.Msg.OK,
			   fn: function() {that.win.show();sheetNewNameTxf.selectText();sheetNewNameTxf.focus(true, true);},
			   animEl: 'elId',
			   width:320,
			   icon: Ext.MessageBox.ERROR
			});
		}

	//	function initEdit(){
	//		groupNameTxf.setValue(args.name);
	//		descriptionTxa.setValue(args.desc);
	//		win.setTitle("Edit Group");
	//	}


		function validateGroup(name){

				var _return = true;

				function isFormatAllowed(){
					var msg = 'group_name_name_format_err_msg'.localize() +'...';
					var my_regexp = /^[a-zA-Z][a-zA-Z0-9_\-@\.\ ]+$/;
					var value = name;
					if (!my_regexp.test(value)){
						groupNameTxf.markInvalid(msg);
						_return=false;
					}
				}


				function isNameAllowed(){
					var msg = 'group_name_name_exits_err_msg'.localize() +'...';
					if (name in groupNameList){
						groupNameTxf.markInvalid(msg);
						_return=false;
					}
				}


			isFormatAllowed();
			isNameAllowed();

			return _return;
		}


		function onOK(){
			var name = groupNameTxf.getValue();
			var desc = descriptionTxa.getValue();

			if (validateGroup(name)){
				fn(name, desc);
				that.win.close();
			}
		}

		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'New Folder Group'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 300,
					height: 180,
					onEsc: Ext.emptyFn,
					items: mainPanel,
					listeners: {
						close: function(){
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openAddGroup);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 300);
							});
						},
						activate: function(win) {that.activate();}
					},
					buttons: [
						(this.components.OK = new Ext.Button({
							text: 'OK'.localize(),
							id: 'sFilesAddGroup_ok_btn',
							tabIndex: 100,
							handler: function(){onOK();}
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							id: 'sFilesAddGroup_cancel_btn',
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 101,
							handler: function(){
								that.win.close();
							}
						}))
					]

		});



		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.studio.files.dlg.AddGroup, Jedox.dlg.Dialog);