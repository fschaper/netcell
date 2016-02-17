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
 * SVN: $Id: AddHyperlink.js 4854 2011-04-15 13:53:28Z lukap $
 *
 */

Jedox.studio.files.dlg.openAddHyperlink = function(callBackFnc){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.AddHyperlink(callBackFnc));
};

Jedox.studio.files.dlg.AddHyperlink = (function(){

	// class constructor
	return function (callBackFnc) {

		Jedox.studio.files.dlg.AddHyperlink.parent.constructor.call(this);

		this.id = 'addHl';
		var that = this;

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		//================================ Components ============================================

		var hyperlinkNameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Hiperlink Name'.localize(),
			labelStyle: 'font-size:11px;',
			tabIndex: 1,
			//emptyText:sheetTitle,
			enableKeyEvents: true,
			width: 200
		});

		var descriptionTxa = new Ext.form.TextArea({
			fieldLabel: 'Description'.localize(),
			labelStyle: 'font-size:11px;',
			tabIndex: 2,
			cls: 'preview-properties-panel',
			name: 'description',
			width: 200
		});

		var splitLine = {
			html: '<br><br>',
			baseCls: 'split-line',
			width: 305
		};


		var locationTxf = new Ext.form.TextField({
			fieldLabel: 'URL (path)'.localize(),
			labelStyle: 'font-size:11px;',
			tabIndex: 3,
			//emptyText:sheetTitle,
			//hideLabel: true,
			enableKeyEvents: true,
			width: 200
		});

		var targetData = [
			['self', 'open in Studio'.localize()], ['blank', 'open in New window'.localize()]
		]

		var targetStore = new Ext.data.SimpleStore({
		    fields: ['id', 'name'],
			data:targetData
	    });

		var targetCmb = new Ext.form.ComboBox({
			//id: 'sReports_group_cmb',
			fieldLabel: 'Target'.localize(),
			store: targetStore,
			tabIndex: 4,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			displayField: 'name',
			valueField: 'id',
			value:'self',
	//				hideLabel: true,
			readOnly: false,
			editable: false,
			//lazyRender: true,
			typeAhead: true,
			mode: 'local',
			triggerAction: 'all',
			selectOnFocus: true,
			listWidth: 140,
			width: 140
		});

	//			var targetDescriptionLbl = new Ext.form.Label({
	//				text:'(target where to open Hyperlink...)'.localize().concat(':'),
	//				hidden:true
	//			});


		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
						modal:true,
						layout: 'form',
						baseCls:'main-panel',
						border:false,
						items:[hyperlinkNameTxf, descriptionTxa, splitLine, locationTxf, targetCmb]
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


		function onOK(){
			var name = hyperlinkNameTxf.getValue();
			var desc = descriptionTxa.getValue();
			var url = locationTxf.getValue();
			var target = targetCmb.getValue();

			if(callBackFnc(name, desc, url, target))
				that.win.close();
		}


		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'New Hyperlink'.localize(),
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
					height: 260,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function(){
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openAddHyperlink);
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
							tabIndex: 20,
							handler: onOK
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							tabIndex: 21,
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
}
)();

Jedox.util.extend(Jedox.studio.files.dlg.AddHyperlink, Jedox.dlg.Dialog);