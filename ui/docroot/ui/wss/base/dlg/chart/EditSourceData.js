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
 * \author
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: EditSourceData.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */



Jedox.wss.dlg.chart.editSourceDataDialog = function(mode, chartID){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.chart.EditSourceData(mode, chartID));
};

Jedox.wss.dlg.chart.EditSourceData = (function() {

	return function (mode, chartID) {

		Jedox.wss.dlg.chart.EditSourceData.parent.constructor.call(this);
		this.id = 'editSourceData';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

			var _chartProps;

			var generalLbl = new Ext.form.Label({
					text:'Source Data Options'.localize().concat(':'),
					cls:'edit-chart-title'
				});

			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var refersToTxf = this.cmpFocus = new Ext.form.TextField({
				fieldLabel: 'Chart Data Range'.localize(),
				tabIndex: 10,
	//			value: '='.concat(Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(), '!', Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(true)),
			  	width: 160
			});

			var selectRangeBtn=new Ext.Toolbar.Button({
			  	id: 'selRangeBegin',
			  	iconCls: 'select-range-icon',
			  	tabIndex: 11,
			  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			  	cls: 'x-btn-icon',
			  	tooltip: "Select Range".localize(),
				handler: function() {
	    			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
	    				fnc: [this, selRangeHandleFnc],
	    				rng: refersToTxf.getValue()
	    			}]);

	    			that.win.hide();
				}
			});


			var groupDataByCmb = new Ext.form.ComboBox({
				fieldLabel: 'Group Data By'.localize(),
				store: new Ext.data.SimpleStore({
					data: [['Auto'.localize(), 'auto'], ['Columns'.localize(), 'cols'], ['Rows'.localize(), 'rows']],
					fields: ['itemName', 'itemValue']
				}),
				displayField: 'itemName',
				valueField: 'itemValue',
				mode: 'local',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 12,
				triggerAction: 'all',
				value: 'auto',
				listWidth: 70,
				width: 70,
				editable: false,
				allowBlank: false,
				selectOnFocus: false,
				listeners: {
					select: {fn: onSelGroupBy,scope: this}
				}
			});

			var useSeriesLabelsCmb = new Ext.form.ComboBox({
				fieldLabel: 'Use series labels'.localize(),
				id: 'firstRowLabels',
				store: new Ext.data.SimpleStore({
					data: [['Auto'.localize(), 'auto'],['Yes'.localize(), 'yes'],['No'.localize(), 'no']],
					fields: ['itemName', 'itemValue']
				}),
				displayField: 'itemName',
				valueField: 'itemValue',
				mode: 'local',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 13,
				triggerAction: 'all',
				value: 'auto',
				listWidth: 70,
				width: 70,
				editable: false,
				allowBlank: false,
				selectOnFocus: false,
				disabled: true
			});

			var useCategoryLabelsCmb = new Ext.form.ComboBox({
				id: 'firstColLabels',
				fieldLabel: 'Use category labels'.localize(),
				store: new Ext.data.SimpleStore({
					data: [['Auto'.localize(), 'auto'],['Yes'.localize(), 'yes'],['No'.localize(), 'no']],
					fields: ['itemName', 'itemValue']
				}),
				displayField: 'itemName',
				valueField: 'itemValue',
				mode: 'local',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 14,
				triggerAction: 'all',
				value: 'auto',
				listWidth: 70,
				width: 70,
				editable: false,
				allowBlank: false,
				selectOnFocus: false,
				disabled: true
			});


			var sourceDataPanel = {
	//			layout: 'form',
				border:false,
				items: [{
					layout: 'form',
					baseCls: 'x-plain',
					labelWidth: 135,
					labelAlign: 'left',
					items: [
						BRLbl,
						generalLbl,
						BRLbl,
						{
							layout:'column',
							border:false,
							baseCls:'x-plain',
							items:[{
								layout:'form',
								labelWidth: 135,
								labelAlign: 'left',
							 	width: 305,
							 	baseCls:'x-plain',
							 	items:refersToTxf
							},{
							    layout:'form',
							    border:false,
							    width: 30,
							    baseCls:'x-plain',
							    items:selectRangeBtn
							}]
						},
						groupDataByCmb,
						useSeriesLabelsCmb,
						useCategoryLabelsCmb
					]
				}]
			}


			//private Methods
			function selRangeHandleFnc(selected){
				that.win.show();
				refersToTxf.setValue(selected);
			}

			function onSelGroupBy(combo, record, index){
				if (combo.getValue() == 'auto') {
					var fRowLbl = Ext.getCmp('firstRowLabels');
					fRowLbl.setValue('auto');
					fRowLbl.disable();

					var fColLbl = Ext.getCmp('firstColLabels');
					fColLbl.setValue('auto');
					fColLbl.disable();
				}
				else {
					Ext.getCmp('firstRowLabels').enable();
					Ext.getCmp('firstColLabels').enable();
				}
			}

			function getSourceDataOptionsValue(){
				var sourceData = refersToTxf.getValue();
				var groupBy = groupDataByCmb.getValue();
				var useSeriesLabels = useSeriesLabelsCmb.getValue();
				var useCategoryLabels = useCategoryLabelsCmb.getValue();

				return {
					General: {
						Source: sourceData,
						GroupBy: groupBy,
						SeriesLabels: useSeriesLabels,
						CategoryLabels: useCategoryLabels
					}
				}
			}


			function setSourceDataOptionsValue(obj){

				refersToTxf.setValue(obj.Source);

				groupDataByCmb.setValue(obj.GroupBy);

				if (obj.GroupBy != 'auto'){
					useSeriesLabelsCmb.enable();
					useSeriesLabelsCmb.setValue(obj.SeriesLabels);
					useCategoryLabelsCmb.enable();
					useCategoryLabelsCmb.setValue(obj.CategoryLabels);
				}
			}



		/************************************
		  **** Main componenets *****
		************************************/



		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			layout: 'fit',
			baseCls: 'x-plain',
			defaults: {
				bodyStyle: 'background-color: transparent; padding:0px 5px 5px 20px;'
			},
			border: false,
			items:[sourceDataPanel]
		});



		var okBtn = (this.components.OK = new Ext.Button({
			text: 'OK'.localize(),
			tabIndex: 20,
			handler: function(){
				doEditChart();
				that.win.close();
			}
		}));

		var cancelBtn = (this.components.Cancel = new Ext.Button({
			text: 'Cancel'.localize(),
			tabIndex: 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(){
				that.win.close();
			}
		}));

		function fillChartDialog(chartID) {
			var chartProps;

			if ((chartProps = Jedox.backend.wss.wsel('get_chart_properties', chartID)) == false) {
				Ext.MessageBox.show({
					title: 'Operation Error'.localize(),
					msg: 'chartDlg_EditError'.localize(),
					buttons: Ext.MessageBox.OK,
					icon: Ext.MessageBox.ERROR,
					fn: function(){
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editSourceData);
						}
				});
				that.win.close();
				return;
			}

	//		console.log(chartProps);
			that.win.show(that);
			setSourceDataOptionsValue(chartProps.SourceData.General);
			_chartProps = chartProps;
		}



		var doEditChart = function () {
			var chartProps = collectProperties();

			if (chartProps != false) {
				chartProps.id = chartID;
				var chart = Jedox.wss.wsel.wselRegistry.get(Jedox.wss.app.activeBook, Jedox.wss.app.activeSheet._uid, chartID);

				// TODO: Show please wait...

				var chartElem = chart.eElem[chart._sheet._aPane._id];
				chartProps.size = [chartElem.getWidth(), chartElem.getHeight()];

				// Send chart Properites.
				if (Jedox.backend.wss.wsel('update_chart', chartProps)) {
					// set new chart type minimum height and width

					var currDate = new Date();

					for (var i = chart._panes.length - 1; i >= 0; i--)
						document.getElementById(chart._panes[i]._domId.concat('_wsel_cont_', chartID)).src = '/be/wss/gen_element.php?wam='.concat(
							Jedox.wss.app.appModeS,
							'&buid=', chart._book.uid,
							'&suid=', chart._sheet.getUid(),
							'&id=', chartID,
							'&ts=', currDate.getTime()
						);
				}
			}
		}




		function collectProperties() {

			var chartProps = {
				props: {
					SourceData:getSourceDataOptionsValue()
				},
				operation:'ssd'
			}


			if (chartProps.props.SourceData.General.Source.length == 0) {
				Ext.MessageBox.show({
					title: 'Input Error'.localize(),
					msg: 'chartDlg_rangeEmpty'.localize(),
					buttons: Ext.MessageBox.OK,
					icon: Ext.MessageBox.WARNING,
					fn: function() {Ext.getCmp('dataRange').focus();}
				});
				return false;
			}

			// TODO: Implement complete data range error checking.
	//		console.log(chartProps);
			return chartProps;
		}


		this.win = new Ext.Window({
	//				id:'edit-source-data-dlg',
					title:'Select Source Data'.localize(),
					closable: true,
					closeAction: 'close',
					cls: 'default-format-window',
			        autoDestroy: true,
			        plain: true,
	//		        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 400,
					height: 300,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editSourceData);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},

					buttons: [okBtn, cancelBtn]

		});




	//	win.show(this);
	//	typeNavigationView.select(0, false, false);

		this.setContext();
		if (mode == 'edit')
			fillChartDialog(chartID);

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.chart.EditSourceData, Jedox.dlg.Dialog);










