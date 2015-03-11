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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: FormatControl.js 5111 2011-07-13 13:58:25Z lukap $
 *
 */

Jedox.wss.dlg.formatControl = function(conf){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Control(conf));
};

Jedox.wss.dlg.Control = (function() {

	return function (conf) {

		Jedox.wss.dlg.Control.parent.constructor.call(this);
		this.id = 'control';
		var that = this;
		var formElement = Jedox.wss.wsel;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		// format control dialog
		// data format
		/*
				ComboBox_conf = {
				 type: Jedox.wss.wsel.type.COMBO_BOX
				 , name: 'ComboBoxN'
				 , src: '=PALO.SUBSET("localhost/Demo","Years",1,,,,,,,PALO.SORT(0,0,,0,,0,1))'
				 //, src: '=Sheet1!$A$1:$D$4'
				 , trange: 'C2:D5'
				 , tnamedrange: 'ComboBox1'
				 , tvar: 'variable_name'
				};

				CheckBox_conf = {
				 type: Jedox.wss.wsel.type.CHECK_BOX
				 , name: 'CheckBoxN'
				 , state: 'unchecked' | 'checked' | 'mixed'
				 , trange: 'C2:D5'
				 , tnamedrange: 'ComboBox1'
				 , tvar: 'variable_name'
				}

				Button_conf = {
				 type: Jedox.wss.wsel.type.BUTTON,
				 name: 'ButtonN',
				 label: 'ButtonN'
				};

		*/

		//conf = {type:Jedox.wss.wsel.type.BUTTON};

		// =================================================================================================================================================
		// initial conf =========================

		// src
		this.typeDisabled = false;
		this.functionValue = '';
		this._gendata = [];
		//tar
		this.element_name = 'ComboBoxN';
		this.iconImgPath = '';
		this.rangeEnabled = false;
		this.varEnabled = false;
		////////

		var isEdit = !!(conf.id); // or conf.name
		if (isEdit) var _initialConf = conf;
		var cbState;
		var cbPreState = {
				unchecked: false,
				checked: false,
				mixed: false
		};


		var txNMVal, txLabel;

		if (conf)
		{

			that._gendata= (conf._gendata) ? conf._gendata : [];
			that.typeDisabled= (conf.type == Jedox.wss.wsel.type.WIDGET)? !!(conf.srctype=='custom'): !!conf.formulaEnabled;
			that.functionValue= conf.src;
			that.labelWidth= 75;
			that.comboWidth= 170;
			that.textWidth= 440;

			that.element_name= conf.name,
			that.rangeEnabled= ((conf.trange == '' || !conf.trange) ? false : true);
			that.rangeValue= ((conf.trange == '' || !conf.trange) ? '' : conf.trange);
			that.varEnabled= ((conf.tvar == '' || !conf.tvar) ? false : true);
			that.varValue= ((conf.tvar == '' || !conf.tvar) ? '' : conf.tvar);
		}

		switch (conf.type){
		case Jedox.wss.wsel.type.COMBO_BOX:
			var txtNM = "ComboBox Name".localize();
			txNMVal = ((conf.name) ? conf.name : formElement.type.COMBO_BOX.concat(formElement.countEl(formElement.type.COMBO_BOX) + 1));
			that.element_name = (conf.name)? conf.name : formElement.type.COMBO_BOX.concat(formElement.countEl(formElement.type.COMBO_BOX) + 1);
			break;
		case Jedox.wss.wsel.type.BUTTON:
			var txtNM = "Button Name".localize();
			labelNM = "Button Label".localize();
			txNMVal = ((conf.name) ? conf.name : formElement.type.BUTTON.concat(formElement.countEl(formElement.type.BUTTON) + 1));
			txLabel = ((conf.label) ? conf.label : txNMVal);
			break;
		case Jedox.wss.wsel.type.CHECK_BOX:
			cbPreState[conf.state] = true;
			var labelNM = "Checkbox Label".localize();
			txNMVal = ((conf.name) ? conf.name : formElement.type.CHECK_BOX.concat(formElement.countEl(formElement.type.CHECK_BOX) + 1));
			txLabel = ((conf.label) ? conf.label : txNMVal);
			that.element_name = (conf.name)? conf.name : formElement.type.CHECK_BOX.concat(formElement.countEl(formElement.type.CHECK_BOX) + 1);
			if (!isEdit) {cbState = 'unchecked'; cbPreState.unchecked=true;}
			else cbState = conf.state;
			var txtNM = "CheckBox Name".localize();
			break;
		case Jedox.wss.wsel.type.WIDGET:
			var txtNM = "Widget Name".localize();
			txNMVal = ((conf.name) ? conf.name : formElement.type.WIDGET.concat(formElement.countEl(formElement.type.WIDGET) + 1));
			that.element_name = (conf.name)? conf.name : formElement.type.WIDGET.concat(formElement.countEl(formElement.type.WIDGET) + 1);
			break;
		};


		var formElement = Jedox.wss.wsel;
		var _config =
		{
			winW: 300,
			mainPanelLabelWidth: 150,
			impPath: 'res/img/dialog/'
		}



		// ===========================================================================
		var txtName = this.cmpFocus = new Ext.form.TextField({
			value: txNMVal,
			id: 'wFCtrlDlg_name_txt',
			width: 250,
			tabIndex: 1,
			labelSeparator: '',
			fieldLabel: txtNM + ':',
			allowBlank: false,
			enableKeyEvents: true,
			listeners: {
				keyup: function(thisTf, e)
				{
					panTar = Ext.getCmp('tar_pan');
					if (panTar) panTar.setName(thisTf.getValue());
				}
			}
		});

		var labelName = new Ext.form.TextField({
			value: txLabel,
			width: 250,
			tabIndex: 2,
			labelSeparator: ':',
			fieldLabel: labelNM,
			allowBlank: true,
			enableKeyEvents: false
		});

		var sourceHolder = new Ext.Panel( {
			id : 'cHolder',
			baseCls: 'x-plain',
			items : [ {} ]
			          //contentPanel
		});

		var labelsItems = (conf.type == Jedox.wss.wsel.type.BUTTON || conf.type == Jedox.wss.wsel.type.CHECK_BOX)? [txtName, labelName] : [txtName];

		var labels = this.containers.labels = new Ext.Panel({
			baseCls: 'x-plain',
			layout: 'form',
			labelWidth: (conf.type == Jedox.wss.wsel.type.WIDGET)? 90:110,
			items: [labelsItems]
		});

		var contentPanel = new Ext.Panel({
			border: false,
			id: 'mainCP',
			bodyStyle: 'background-color:transparent;',
			layout: 'form',
			labelWidth: 110,
			title: 'General'.localize(),
        	autoWidth: true,
        	autoHeight: true,
        	style: 'padding:2px;',
        	items: [
        	        labels,
        	        sourceHolder
        	        ]
		});

		// implement in switch
/*
		function getSourcePanel(pan){
			contentPanel.add(pan);
			contentPanel.doLayout();
		};
*/
		//Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwSource, [getSourcePanel, false, 10]);

		var valuePanel = new Ext.form.FieldSet({
			title: "Value".localize(),
			collapsible: false,
			id: 'val_pan',
	    	autoWidth: true,
	    	autoHeight: true,
			items: [
					new Ext.form.Radio({
						checked: cbPreState.unchecked,
						name: 'radioSourceFormV',
						tabIndex: 5,
						boxLabel: 'Unchecked'.localize(),
						hideLabel: true,
						listeners: {
							check: function(thisRb, isChecked)
							{
								if (isChecked) cbState = 'unchecked';
							}
						}
					}),
					 new Ext.form.Radio({
							checked: cbPreState.checked,
							name: 'radioSourceFormV',
							boxLabel: 'Checked'.localize(),
							tabIndex: 6,
							hideLabel: true,
							listeners: {
								check: function(thisRb, isChecked)
								{
						 			if (isChecked) cbState = 'checked';
								}
							}
						})
			        ]
		});


		///// only for widgets: layout tab

		var userBorderCb = new Ext.form.Checkbox({
			boxLabel: 'Show borders in User mode'.localize(),
			checked: (conf.format)? conf.format.view.border : false,
			hideLabel: true,
			tabIndex: 10,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER
		});

		var layoutPanel = new Ext.Panel({
			title: 'Layout'.localize(),
			border: false,
			id: 'layoutPan',
			bodyStyle: 'background-color:transparent;',
			layout: 'form',
			labelWidth: 110,
        	autoWidth: true,
        	autoHeight: true,
        	style: 'padding:2px;',
        	items: [
        	        userBorderCb
        	        ]
		});

		var ctsPre = {};

		//////////////////////////////////////////////////////////

		var tabs = new Ext.TabPanel({
			region: 'center',
			xtype: 'tabpanel',
			id: 'maintabspanel',
			layoutOnTabChange: true,
			activeTab: 0,
			ctCls: 'tb-no-bg',
			autoHeight: true,
			baseCls: 'x-plain',
			bodyStyle: 'background-color: transparent; padding: 5px;',
			defaults: {
			autoScroll: false
		},
		items: [contentPanel],
		listeners: {
			tabchange: function(el, e)
			{
				if (e.id == 'layoutPan') {
					for (var c in that.containers){
						ctsPre[c] = that.containers[c];
						delete that.containers[c];
					}
					that.containers.layoutPan = e;
				} else if (e.id == 'SPPan') {
					for (var c in that.containers){
						ctsPre[c] = that.containers[c];
						delete that.containers[c];
					}
					that.containers.SPPan = e;
				} else {
					delete that.containers.layoutPan;

					if (ctsPre.labels) {
						that.containers = ctsPre;
						return;
					}

					sourceHolder.removeAll();

					var ccb = function(cPan) {
						sourceHolder.add(cPan);
						sourceHolder.doLayout();
					};

					var fcb = function(cPan) {
						sourceHolder.add(cPan);
						sourceHolder.doLayout();

						var addp = function(cPan){
							sourceHolder.add(cPan);
							sourceHolder.doLayout();
						}

						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwTarget, [addp, conf, 50, that]);
					};

					var ldwidget = function(cPan){
						sourceHolder.add(cPan);
						sourceHolder.doLayout();

						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwSource, [fcb, conf, 30, that]);
					}

					switch (conf.type){
					case Jedox.wss.wsel.type.COMBO_BOX:
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwSource, [fcb, conf, 30, that]);
						break;
					case Jedox.wss.wsel.type.BUTTON:
						break;
					case Jedox.wss.wsel.type.CHECK_BOX:
						ccb(valuePanel);
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwTarget, [ccb, conf, 50, that]);
						that.containers.valpan = valuePanel;
						break;
					case Jedox.wss.wsel.type.WIDGET:
						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.fwContent, [ldwidget, conf, 10, that]);
						break;
					};
				}
			}
		}
		});

		if (conf.type == Jedox.wss.wsel.type.WIDGET) tabs.add(layoutPanel);

		var getSizePosPan = function(panel){
			var np = new Ext.Panel({
				title: 'Size & Position'.localize(),
				border: false,
				id: 'SPPan',
				bodyStyle: 'background-color:transparent;',
				layout: 'form',
				labelWidth: 110,
	        	autoWidth: true,
	        	autoHeight: true,
	        	style: 'padding:2px;',
	        	items: [
	        	        panel
	        	        ]
			});
			tabs.add(np);
		}

		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.FESizePositionPanel, [getSizePosPan, conf.type, conf]);
		//TODO: uncomment after size&position panel is done

		//=============================== SAVE FUNCTION ==========================================

		var _handleSave = function(cb)
		{
			var panFnc = Ext.getCmp('src_pan'),
				panTar = Ext.getCmp('tar_pan'),
				cntPan = Ext.getCmp('cnt_pan'),
				hasCB = cb instanceof Array && cb.length > 1;

			// error Checking
			if (txtName.getValue() == '') {
				if (hasCB) cb[1].call(cb[0], [false, txtNM.concat(' ','WSS_Forms_empty_name'.localize()), {_type: 'info'}]);
				return;
			}

			if (conf.type == Jedox.wss.wsel.type.WIDGET)
			{
				var cnt = cntPan.getData().cnt;
				if (!cnt || cnt=='' || cnt=='\n') {
					if (hasCB) cb[1].call(cb[0], [false, 'WSS_Widget_empty_content', {_type: 'info'}]);
					return;
				}
			}

			if (panFnc){
				if (panFnc.getFuncText() == '' && (conf.type != Jedox.wss.wsel.type.WIDGET || (conf.type == Jedox.wss.wsel.type.WIDGET && panFnc.getSrcType()!='none'))) {
					if (hasCB) cb[1].call(cb[0], [false, 'WSS_FormComboBox_empty_source', {_type: 'info'}]);
					return;
				}
			}

			if (conf.type != Jedox.wss.wsel.type.BUTTON) {
				var tarData = panTar.getRangeValues();

				if ((tarData.range == '') && (tarData.name == '') && (tarData.variable == '') && (conf.type != Jedox.wss.wsel.type.WIDGET)) {
					if (hasCB) cb[1].call(cb[0], [false, 'WSS_FormComboBox_empty_target', {_type: 'info'}]);
					return;
				}
			}

			// check size and position
			var dims = Ext.getCmp('FE-SE-panel').getSPData();
			if (!dims){
				if (hasCB) cb[1].call(cb[0], [false, 'floatingElement_wrongSizePos', {_type: 'error'}]);
				return;
			}

			// END of Error Checking

			switch(conf.type){
			case Jedox.wss.wsel.type.COMBO_BOX:
				var genData = panFnc.getGenData(),
					formulaEna = panFnc.getTypeDisabled();

				conf = {
						_gendata: isEdit && !genData.length && !formulaEna ? conf._gendata : genData,
						type: Jedox.wss.wsel.type.COMBO_BOX,
						name: txtName.getValue(),
						src: panFnc.getFuncText(),
						formulaEnabled: formulaEna,
						trange: tarData.range,
						tnamedrange: tarData.name,
						tvar: tarData.variable,

						top: dims.top,
						left: dims.left,
						width: dims.width,
						height: dims.height

					};
				break;
			case Jedox.wss.wsel.type.BUTTON:
				conf = {
						type: Jedox.wss.wsel.type.BUTTON,
						name: txtName.getValue(),
						label: labelName.getValue(),

						top: dims.top,
						left: dims.left,
						width: dims.width,
						height: dims.height

					};
				break;
			case Jedox.wss.wsel.type.CHECK_BOX:
				conf = {
						type: Jedox.wss.wsel.type.CHECK_BOX,
						name: txtName.getValue(),
						label: labelName.getValue(),
						state: cbState,
						trange: tarData.range,
						tnamedrange: tarData.name,
						tvar: tarData.variable,

						top: dims.top,
						left: dims.left,
						width: dims.width,
						height: dims.height

					};
				break;
			case Jedox.wss.wsel.type.WIDGET:
				// get content
				var content = cntPan.getData();

				var genData = panFnc.getGenData(),
					formulaEna = panFnc.getTypeDisabled();

				conf = {
						type: Jedox.wss.wsel.type.WIDGET,
						subtype: 'custom',
						name: txtName.getValue(),

						cnttype: content.type,
						cnt: content.cnt,

						srctype: panFnc.getSrcType(), //!
						src: panFnc.getFuncText(),
						_gendata: isEdit && !genData.length && !formulaEna ? conf._gendata : genData,

						trange: tarData.range,
						tnamedrange: tarData.name,
						tvar: tarData.variable,

						top: dims.top,
						left: dims.left,
						width: dims.width,
						height: dims.height,

						format: {
							view: {
								border: userBorderCb.getValue()
							}
						}
					};
				break;
			};

			if (isEdit) {
				conf.id = _initialConf.id;
				Jedox.wss.wsel.update(conf, cb);
			} else {
				conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();
				Jedox.wss.wsel.add(conf, cb);
			}
		};



		//=======================================================================================

		this.win = new Ext.Window({
			title: (conf.type == Jedox.wss.wsel.type.WIDGET)? 'Format Widget'.localize() : 'Format Control'.localize(),
			closable: true,
			autoDestroy: true,
			id: 'formatControlDialog',
			cls: 'default-format-window',
			plain: true,
			constrain: true,
			modal: true,
			resizable: false,
			animCollapse: false,
			width: 500,
			height: (conf.type==Jedox.wss.wsel.type.WIDGET)? 420 : 410,
			//autoHeight: true,
			items:[tabs],
			onEsc: Ext.emptyFn,
			listeners: {
				close: function(){
					Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.READY);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					/* === unload components ==== */
					switch (conf.type){
					case Jedox.wss.wsel.type.COMBO_BOX:
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwSource);
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwTarget);
						break;
					case Jedox.wss.wsel.type.CHECK_BOX:
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwTarget);
						break;
					case Jedox.wss.wsel.type.WIDGET:
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwContent);
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwSource);
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.fwTarget);
						break;
					};
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.FESizePositionPanel);
					/* *** */
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatControl);
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
			        	    id: 'wFCtrlDlg_ok_btn',
							text: 'OK'.localize(),
							tabIndex: 101,
							handler: function() {
			        	  		var cbHandleSave = function(retData) {
									if (retData[0])
										that.win.close();
									else {
										Ext.MessageBox.show({
											title: ((retData[2]._type) && (retData[2]._type == 'info')) ? "Information".localize() : "Error".localize(),
											msg: retData[1].localize(retData[2]),
											buttons: Ext.Msg.OK,
											icon: ((retData[2]._type) && (retData[2]._type == 'info')) ? Ext.MessageBox.INFO : Ext.MessageBox.ERROR
										});
									}
			        	  		};

					        	_handleSave([this, cbHandleSave]);
							}
						})),
			          (this.components.Cancel = new Ext.Button({
			        	  	id: 'wFCtrlDlg_cancel_btn',
							text: 'Cancel'.localize(),
							tabIndex: 102,
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

Jedox.util.extend(Jedox.wss.dlg.Control, Jedox.dlg.Dialog);