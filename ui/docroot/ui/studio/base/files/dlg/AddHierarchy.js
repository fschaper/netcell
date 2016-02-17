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
 * SVN: $Id: AddHierarchy.js 5013 2011-05-30 09:27:32Z srdjanv $
 *
 */

Jedox.studio.files.dlg.openAddHierarchy = function(group, fn, hierarchyNameList){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.AddHierarchy(group, fn, hierarchyNameList));
};

Jedox.studio.files.dlg.AddHierarchy = (function(){

	// class constructor
	return function (group, fn, hierarchyNameList) {

		Jedox.studio.files.dlg.AddHierarchy.parent.constructor.call(this);

		this.id = 'addHr';
		var that = this;

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		//================================ Components ============================================

		var hierarchyNameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Root Folder Name'.localize(),
			labelStyle: 'font-size:11px;',
			tabIndex: 1,
			id: 'sFilesAddHierarchy_name_txt',
			//emptyText:sheetTitle,
			enableKeyEvents: true,
			width: 200
		});

		var descriptionTxa = new Ext.form.TextArea({
			fieldLabel: 'Description'.localize(),
			tabIndex: 2,
			id: 'sFilesAddHierarchy_desc_tx',
			labelStyle: 'font-size:11px;',
			cls: 'preview-properties-panel',
			name: 'description',
			width: 200
		});

		var splitLine = {
			html: '<br><br>',
			baseCls: 'split-line',
			width: 305
		};

		var typeTxf = new Ext.form.TextField({
			fieldLabel: 'Type'.localize(),
			tabIndex: 3,
			labelStyle: 'font-size:11px;',
			//emptyText:sheetTitle,
			enableKeyEvents: true,
			width: 150
		});

		var locationLbl = {
			html:'Location',
			baseCls:'x-plain'
		}

		var locationTxf = new Ext.form.TextField({
			fieldLabel: 'Location (path)'.localize(),
			labelStyle: 'font-size:11px;',
			id: 'sFilesAddHierarchy_location_txt',
			tabIndex: 4,
			//emptyText:sheetTitle,
			//hideLabel: true,
			enableKeyEvents: true,
			width: 200
		});


		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						modal:true,
						layout: 'form',
						baseCls:'main-panel',
						border:false,
						items:[hierarchyNameTxf, descriptionTxa, splitLine, locationTxf]
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

	//			function initEdit(){
	//				hierarchyNameTxf.setValue(args.name);
	//				descriptionTxa.setValue(args.desc);
	//				locationTxf.setValue(args.path);
	//				win.setTitle("Edit File Repository");
	//			}


		function validateHierarchy(name){

				var _return = true;

				function isFormatAllowed(){
					var msg = 'hierarchy_name_name_format_err_msg'.localize() +'...';
					var my_regexp = /^[a-zA-Z][a-zA-Z0-9_\-@\.\ ]+$/;
					var value = name;
					if (!my_regexp.test(value)){
						hierarchyNameTxf.markInvalid(msg);
						_return=false;
					}
				}


				function isNameAllowed(){
					var msg = 'hierarchy_name_name_exits_err_msg'.localize() +'...';
					if (name in hierarchyNameList){
						hierarchyNameTxf.markInvalid(msg);
						_return=false;
					}
				}


			isFormatAllowed();
			isNameAllowed();

			return _return;
		}

		function initNew(){

			function onSuccessCbHandler(result){
				locationTxf.setValue(result.concat('\\',  group));
			}

			function onErrorCbHandler(result){
				this.win.close();
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'getDefaultLocalPath'))
				.setOnSuccess([this, onSuccessCbHandler]).setOnError([that, onErrorCbHandler]).send();


		}

		function onOK(){
			var name = hierarchyNameTxf.getValue();
			var desc = descriptionTxa.getValue();
			var path = locationTxf.getValue();


			if(validateHierarchy(name)){
				fn(name, desc, path);
				that.win.close();
			}
		}


		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'New File Repository'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 350,
					height: 230,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function(){
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.addTag);
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
							id: 'sFilesAddHierarchy_ok_btn',
							tabIndex: 10,
							handler: onOK
						})),
						(this.components.Cancel = new Ext.Button({
							id: 'sFilesAddHierarchy_cancel_btn',
							text: 'Cancel'.localize(),
							tabIndex: 11,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							handler: function(){
								that.win.close();
							}
						}))
					]

		});

		initNew();


		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.studio.files.dlg.AddHierarchy, Jedox.dlg.Dialog);