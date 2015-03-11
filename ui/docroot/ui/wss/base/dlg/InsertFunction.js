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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: InsertFunction.js 4720 2011-03-18 10:05:03Z andrejv $
 *
 */

Jedox.wss.dlg.openInsertFunctionDialog = function(from, preselection) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.InsertFunction(from, preselection));
};

Jedox.wss.dlg.InsertFunction = (function() {

	return function (from, preselection) {

		Jedox.wss.dlg.InsertFunction.parent.constructor.call(this);
		this.id = 'wInsFnc_dlg_wnd';
		var that = this;

		// Handler functions.
		var onBeforeDestroyDialog = function(panel) {
			// Destroy all form elements and destroy self the form
			insFuncForm.items.each( function(f) {
				f.purgeListeners();
				Ext.destroy(f);
			});
			insFuncForm.purgeListeners();
			insFuncForm.destroy();

			if (Jedox.wss.app.environment.inputMode == Jedox.wss.grid.GridMode.DIALOG) {
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}

			that.close();

			Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.insertFunction);
		}

		var onBeforeShowDialog = function(panel) {
			getFunctionsList(Ext.getCmp('wInsFnc_category_cmb').getValue);
		}

		var onCategorySelect = function(combo, record, index) {
			getFunctionsList(combo.getValue());
		}

		var onRowSelect = function(selModel, rowIndex, record) {
			setFunctionDescriptions(record);
		}

		var getFunctionsList = function(category) {
			var functionsGrid = Ext.getCmp('wInsFnc_fns_grd');
			var gridSelModel = functionsGrid.getSelectionModel();

			if (category != 'ALL')
				functionsGrid.store.filter('catid', category);
			else {
				functionsGrid.store.clearFilter();
				functionsGrid.store.sort('funcname');
			}

			gridSelModel.selectFirstRow();
			if (gridSelModel.getCount() > 0)
				setFunctionDescriptions(gridSelModel.getSelected());
		}
		var activeFnc;
		var setFunctionDescriptions = function(record) {
			var i;

			var formulaText = record.get('funcsyntax');
			activeFnc = record.get('funcname');
			Jedox.wss.app.selectedFormula = formulaText;

			var defPan = Ext.getCmp('funcdef');
			defPan.removeAll();
			defPan.add( {
				html : formulaText,
				baseCls : 'x-plain'
			});
			defPan.doLayout();

			var dscPan = Ext.getCmp('funcdesc');
			dscPan.removeAll();
			dscPan.add( {
				html : record.get('funcdesc'),
				baseCls : 'x-plain'
			});
			dscPan.doLayout();
		}

		var doInsertFunction = function() {

			var ffn = functions.lookup_func[activeFnc];
			var ff = functions.funcs[ffn];
			that.win.destroy();

			if (preselection && _pre.fn==activeFnc)
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ ff, from, preselection]);
			else
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ ff, from ]);
		}

		var xhr = new XMLHttpRequest();
		xhr.open('GET', '/be/fn_desc/'.concat(Jedox.wss.i18n.L10n, '.json'),
				false);
		xhr.send(null);

		var functions = Ext.util.JSON.decode(xhr.responseText);
		functions.cats.unshift( [ 'ALL', 'All'.localize() ]);

		/* ================ PRESELECTION =================== */

		if (preselection){
			var _pre = {
					fn: preselection.slice(1, preselection.indexOf('(')),
					args: preselection.slice(preselection.indexOf('(')+1, preselection.lastIndexOf(')')).split(',')
			}

			var preffn = functions.lookup_func[_pre.fn];
			if (preffn){
				var preff = functions.funcs[preffn];
				var preCat = functions.lookup_cat[preff[0]] + 1;

				// if from fbar, fire up function arguments dialog
				if (from.id == 'fbar' && preselection){
					Jedox.gen.load(Jedox.wss.app.dynJSRegistry.funcArgs, [ preff, from, preselection]);
					return false;
				}
			} else {
				preselection = false;
			}
		}

		/* ================================================= */


		var insFuncForm = this.containers.mainPanel = new Ext.FormPanel(
				{
					baseCls : 'x-plain',
					labelWidth : 110,
					labelAlign : 'left',
					frame : true,
					bodyStyle : 'padding:5px 5px 0',
					width : 400,
					defaultType : 'textfield',
					buttonAlign : 'right',
					header : false,
					monitorValid : true,
					items : [
					         (this.cmpFocus = new Ext.form.ComboBox({
					        	 xtype : 'combo',
					        	 id : 'wInsFnc_category_cmb',
					        	 fieldLabel : "Select a category".localize(),
					        	 store : new Ext.data.SimpleStore( {
					        		 fields : [ 'catid', 'catname' ],
					        		 data : functions.cats
					        	 }),
					        	 displayField : 'catname',
					        	 valueField : 'catid',
					        	 mode : 'local',
					        	 triggerAction : 'all',
					        	 listWidth : 260,
					        	 width : 230,
					        	 editable : false,
					        	 allowBlank : false,
					        	 selectOnFocus : false,
					        	 tabIndex : 1,
					        	 ctCls: Jedox.kbd.Base.tags.NO_ANY,
					        	 anchor : '100%',
					        	 listeners : {
					        	 render : function() {
						        	 if (this.store.getTotalCount() > 0)
						        		 this.setValue(this.store.getAt((preCat)? preCat:1).get(
						        		 'catid'));
						         },
						         select : {
						        	 fn : onCategorySelect,
						        	 scope : this
						         }
					         }

					         })),
					         new Ext.form.MiscField( {
					        	 fieldLabel : 'Select a function'.localize(),
					        	 id : 'funcLabel'

					         }),
					         new Ext.grid.GridPanel( {
					        	 id : 'wInsFnc_fns_grd',
					        	 cls : 'insfuncgrid',
					        	 hideLabel : true,
					        	 store : new Ext.data.SimpleStore( {
					        		 fields : [ 'catid', 'funcname', 'funcsyntax',
					        		            'funcdesc' ],
					        		            data : functions.funcs
					        	 }),
					        	 columns : [ {
					        		 id : 'functionname',
					        		 header : "Functions".localize(),
					        		 fixed : true,
					        		 width: 350,
					        		 resizable : false,
					        		 sortable : true,
					        		 dataIndex : 'funcname'
					        	 } ],
					        	 stripeRows : true,
					        	 autoExpandColumn : 'functionname',
					        	 height : 150,
					        	 width : 350,
					        	 viewConfig: {
					        	 	forceFit: true
						         },
					        	 header : false,
					        	 //tabindex : 2,
					        	 anchor : '100%',
					        	 selModel : new Ext.grid.RowSelectionModel( {
					        		 singleSelect : true,
					        		 listeners : {
					        		 rowselect : {
					        		 fn : onRowSelect,
					        		 scope : this
					        	 }
					        	 }
					        	 })

					         }),
					         new Ext.Panel(
					        		 {
					        			 id : 'funcdef',
					        			 autoHeight : true,
					        			 autoScroll : 'auto',
					        			 baseCls : 'x-plain',
					        			 style : 'font-weight: bold; margin: 5px 0px; word-wrap: break-word;',
					        			 items : [ {
					        				 html : '',
					        				 baseCls : 'x-plain'
					        			 } ]
					        		 }), new Ext.Panel( {
					        			 id : 'funcdesc',
					        			 autoScroll : 'auto',
					        			 baseCls : 'x-plain',
					        			 items : [ {
					        				 html : '',
					        				 baseCls : 'x-plain'
					        			 } ]
					        		 })

					         ]

				});

		this.win = new Ext.Window( {
			id : 'wInsFnc_dlg_wnd',
			title : (from.id == 'control')? 'Select Function'.localize() : 'Insert Function'.localize(),
			cls : 'wssdialog',
			layout : 'fit',
			width : 400,
			height : 400,
			minWidth : 300,
			minHeight : 300,
			closeable : true,
			closeAction : 'close',
			autoDestroy : true,
			plain : true,
			constrain : true,
			modal : true,
			items : [ insFuncForm ],
			listeners : {
				beforedestroy : {
					fn : onBeforeDestroyDialog,
					scope : this
				},
				beforeshow : {
					fn : onBeforeShowDialog,
					scope : this
				},
				show:function(){
					setTimeout(function(){
						Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
						Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
						that.initFocus(true, 100);
						var grid = Ext.getCmp('wInsFnc_fns_grd');
						if (preselection){
						 	var gi = grid.getStore().find('funcname', _pre.fn);
			 				grid.getSelectionModel().selectRow(gi);
			 				grid.getView().focusRow(gi);
						} else {
							grid.getSelectionModel().selectRow(0);
			 				grid.getView().focusRow(0);
						}
					});
				},
				activate: function(win) {that.activate();}
			},
			buttons : [(this.components.OK = new Ext.Button({
				text : "OK".localize(),
				id: "wInsFnc_ok_btn",
				handler : doInsertFunction,
				tabIndex : 3
			})), (this.components.Cancel = new Ext.Button({
				text : 'Cancel'.localize(),
				id: "wInsFnc_cancel_btn",
				tabIndex : 4,
				handler : function() {
				if (from.id == 'control') Ext.getCmp('formatControlDialog').show();
				that.win.destroy();
			}
			})) ]
		});

			this.setContext();
			this.win.show(this);
			getFunctionsList(Ext.getCmp('wInsFnc_category_cmb').getValue());

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.InsertFunction, Jedox.dlg.Dialog);