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
 * SVN: $Id: Target.js 4443 2010-12-10 14:17:20Z andrejv $
 *
 */

Jedox.wss.dlg.control.target = function(callback, _pre, tabOffset, thats) {

	if (!tabOffset) tabOffset = 0;



	if (_pre.type == Jedox.wss.wsel.type.WIDGET){
		var tarComboData = [
		                    ['none', 'None'.localize()],
		                    ['range', 'Cell/Range'.localize()],
		                    ['nrange', 'Named Range'.localize()],
		                    ['var', 'Variable'.localize()]
		                   ];

		var tarDatReg = {
				'none': 0,
				'None': 0,
				'': 0,
				'range': 1,
				'nrange': 2,
				'var': 3
		};



		var tartype = 'none';
		if (_pre.tvar) tartype = 'var';
		if (_pre.trange) tartype = 'range';
		if (_pre.tnamedrange) tartype = 'nrange';

		var tarPreType = (tarDatReg[tartype])? tarDatReg[tartype] : 0;

		var tarComboStore = new Ext.data.ArrayStore({
		    fields: ['tar', 'desc'],
		    idIndex: 0,
		    data: tarComboData
		});

		var tarCombo = new Ext.form.ComboBox({
		    typeAhead: false,
		    editable: false,
		    tabIndex: tabOffset + 1,
		    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		    triggerAction: 'all',
		    width: 150,
		    value: tarComboData[tarPreType][1],
		    lazyRender:true,
		    mode: 'local',
		    store: tarComboStore,
		    valueField: 'tar',
		    displayField: 'desc',
		    listeners: {
				select: function(c, r, i){
					targetCardHolder.layout.setActiveItem(i);
					targetCardHolder.doLayout();
					targetCardHolder.layout.activeItem.doLayout();
					tartype = tarComboData[i][0];
				}
			}
			});


		//========================= CARD ELEMENTS ====================

		// range

		function selRange(selected){
			Ext.getCmp('formatControlDialog').show();
			setTimeout(function() {
				rangeFld.setValue(selected);
			}, 1);
		};

		var selectorBtn = new Ext.Button({
			id: 'selBtn',
			iconCls: 'select-range-icon',
			cls: 'x-btn-icon',
			tabIndex: tabOffset + 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tooltip: "Select Range".localize(),
			handler: function() {
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
					fnc: [this, selRange]
	  					,format: '{Sheet}!{Range}'
	  					,rng: rangeFld.getValue()
	  					,omitInitSheet: true
	  				}]);
				Ext.getCmp('formatControlDialog').hide();
		}
		});

		var rangeFld = new Ext.form.Field({
			hideLabel: true,
			tabIndex: tabOffset + 2,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			width: 150,
			value: (_pre.trange)? _pre.trange:''
		});

		var cardRangeHolder = new Ext.Panel({
			layout: 'column',
			baseCls: 'x-plain',
			bodyStyle: 'padding-left: 10px;',
			autoWidth: true,
			items: [
					new Ext.Panel({
						baseCls: 'x-plain',
						width: 150,
						border:false,
						layout: 'form',
						items: [rangeFld]
					}),
					new Ext.Panel({
						baseCls: 'x-plain',
						layout:'form',
						border:false,
						width: 50,
						items: [selectorBtn]
					})
			        ]
		});

		var cardRange = new Ext.Panel({
			layout: 'form',
			xtype: 'fieldset',
			autoHeight: true,
			baseCls: 'x-plain',
			autoWidth: true,
			items: [cardRangeHolder]
		});

		// variable

		var varFld = new Ext.form.Field({
			width: 150,
			tabIndex: tabOffset + 4,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			hideLabel: true,
			value: (_pre.tvar)? _pre.tvar : ''
		});

		var cardVar = new Ext.Panel({
			baseCls: 'x-plain',
			bodyStyle: 'padding-left: 10px;',
			items: [varFld]
		});

		/////

		var cardNameFld = new Ext.form.MiscField({
			value: thats.element_name,
			width: 150,
			id: 'cnfld',
			hideLabel: true,
			labelSeparator: ''
		});

		var cardName = new Ext.Panel({
			baseCls: 'x-plain',
			bodyStyle: 'padding-top: 4px; padding-left: 10px;',
			layout: 'form',
			width: 200,
			autoHeight: true,
			items: [cardNameFld]
		});


		//========================= E O CE ===========================

		var targetCardHolder = new Ext.Panel({
			layout: 'card',
			baseCls: 'x-plain',
			autoWidth: true,
			activeItem: tarPreType,
			deferredRender: true,
			items:[
			       {baseCls: 'x-plain', autoWidth: true},//none
			       cardRange,
			       cardName,
			       cardVar
			       ],
	       listeners: {
				afterLayout: function(p, l){
					thats.containers.tarCard = p.layout.activeItem;
				}
		}
		});


		var tarPan = new Ext.Panel({
			layout: 'column',
			baseCls: 'x-plain',
			border: false,
			items: [
			        (thats.containers.tarCmb = new Ext.Panel({
			        	baseCls: 'x-plain',
			        	width: 150,
			        	items: [tarCombo]
			        })),
			        new Ext.Panel({
			        	baseCls: 'x-plain',
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	width: 250,
			        	items: [targetCardHolder]
			        })
			        ]
		});
	} else {
		// ========================== OLD LAYOUT =============================

			var _rbRange = new Ext.form.Radio({
				checked: thats.rangeEnabled,
				name: 'radioTargetForm',
				tabIndex: tabOffset + 1,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Cell/Range".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							thats.rangeEnabled = true;

							_txtRange.enable();
							_btnTargetSelect.enable();
							_fldName.disable();

							_fldVar.disable();
						}
					}
				}
			});

			var _txtRange = new Ext.form.TextField({
				disabled: !thats.rangeEnabled,
				hideLabel: true,
				width: 210,
				tabIndex: tabOffset + 2,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				allowBlank: true,
				value: thats.rangeValue
			});

			var _btnTargetSelect = new Ext.Toolbar.Button({
				disabled: !thats.rangeEnabled,
				iconCls: 'select-range-icon',
				cls: 'x-btn-icon',
				tabIndex: tabOffset + 3,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tooltip: "Select Cell".localize(),
				listeners: {
					click: function()
					{
						if (Ext.getCmp('formatControlDialog'))
							Ext.getCmp('formatControlDialog').hide();

						Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [
							{
								fnc: [this, function(tmpStr)
								{
									_txtRange.setValue(tmpStr);
									if (Ext.getCmp('formatControlDialog'))
										Ext.getCmp('formatControlDialog').show();
								}],
								format: '{Sheet}!{$Range}',
								omitInitSheet: true,
								rng: _txtRange.getValue()
							}
						]);
					}
				}
			});

			var _rbName = new Ext.form.Radio({
				checked: !(thats.rangeEnabled || thats.varEnabled),
				name: 'radioTargetForm',
				tabIndex: tabOffset + 4,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Named Range".localize().concat(':'),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							thats.rangeEnabled = false;
							thats.varEnabled = false;

							_txtRange.disable();
							_btnTargetSelect.disable();
							_fldName.enable();

							_fldVar.disable();
						}
					}
				}
			});

			var _rbVar = new Ext.form.Radio({
				checked: thats.varEnabled,
				name: 'radioTargetForm',
				tabIndex: tabOffset + 5,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Variable".localize(),
				hideLabel: true,
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
						{
							thats.rangeEnabled = false;

							_fldVar.enable();

							_txtRange.disable();
							_btnTargetSelect.disable();
							_fldName.disable();
						}
					}
				}
			});

			var _fldName = new Ext.form.MiscField({
				disabled: (thats.rangeEnabled || thats.varEnabled),
				style: 'padding:3px 3px 3px 0px;',
				value: thats.element_name,
				id: 'formElementTargetNRFld',
				hideLabel: true,
				labelSeparator: '',
				listeners: {
					disable: function(thisMf)
					{
						Ext.DomHelper.applyStyles(thisMf.el.dom.parentNode.parentNode.childNodes[0], 'color:gray;opacity:0.6;' );
					},
					enable: function(thisMf)
					{
						Ext.DomHelper.applyStyles(thisMf.el.dom.parentNode.parentNode.childNodes[0], 'color:black;opacity:1;' );
					}
				}
			});

			var _fldVar = new Ext.form.TextField({
				disabled: !thats.varEnabled,
				tabIndex: tabOffset + 6,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				value: thats.varValue,
				hideLabel: true,
				labelSeparator: '',
				listeners: {

				}
			});



			////
			var tarPan = thats.containers.tarpanmain = new Ext.Panel({
				layout: 'form',
				baseCls: 'x-plain',
				border: false,
				items: [
						_rbRange,
						new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_txtRange]
								        }),
								        {
								        	border: false,
								        	bodyStyle: 'background-color:transparent;',
								        	html: '&nbsp;&nbsp;&nbsp;'
								        },
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_btnTargetSelect]
								        })
							        ]
						}),
						new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_rbName]
								        }),
								        {
								        	border: false,
								        	bodyStyle: 'background-color:transparent;',
								        	html: '&nbsp;&nbsp;&nbsp;'
								        },
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_fldName]
								        })
							        ]
						}),
						new Ext.Panel({
							border: false,
							layout: 'column',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_rbVar]
								        }),
								        {
								        	border: false,
								        	bodyStyle: 'background-color:transparent;',
								        	html: '&nbsp;&nbsp;&nbsp;'
								        },
								        new Ext.Panel({
								        	border: false,
								        	layout: 'form',
								        	bodyStyle: 'background-color:transparent;',
								        	autoWidth: true,
								        	autoHeight: true,
								        	items: [_fldVar]
								        })
							        ]
						})
				        ]
			});
	}

	var fsTarget = Ext.extend(Ext.form.FieldSet, {

		setWindowToHide: function(winToH)
		{
			this.winToHide = winToH;
		},

		setName: function(nameValue)
		{
			(_pre.type == Jedox.wss.wsel.type.WIDGET)? cardNameFld.setValue(nameValue) : _fldName.setValue(nameValue);
		},

		getRangeValues: function()
		{
			var retData = {
					name: '',
					range: '',
					variable: ''
			};

			if (_pre.type == Jedox.wss.wsel.type.WIDGET){
				var active = tartype;
				switch(active){
				case 'nrange':
					retData.name = cardNameFld.getValue();
					break;
				case 'range':
					retData.range = rangeFld.getValue();
					break;
				case 'var':
					retData.variable = varFld.getValue();
					break;
				case 'none':
					break;
				};
			} else {
				retData.name = ((_rbName.checked) ? _fldName.getValue() : '');
				retData.range = ((_rbRange.checked) ? _txtRange.getValue() : '');
				retData.variable = ((_rbVar.checked) ? _fldVar.getValue() : '');
			}

			return retData;
		},

		initComponent: function(){
			Ext.apply(this, {});
			fsTarget.superclass.initComponent.call(this);
		}
	});


	var retPanel = new fsTarget({
		title: "Target_formElems".localize(),
		id: 'tar_pan',
		collapsible: false,
    	autoWidth: true,
    	autoHeight: true,
		items: [tarPan]
	});

	callback(retPanel);

}