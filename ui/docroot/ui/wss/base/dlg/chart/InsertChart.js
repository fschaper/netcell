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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: InsertChart.js 5033 2011-06-06 13:31:05Z drazenk $
 *
 */

Jedox.wss.dlg.chart.openChartDialog = function (mode, chartID) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.chart.Chart(mode, chartID));
};

Jedox.wss.dlg.chart.Chart = (function() {

	return function (mode, chartID) {

		Jedox.wss.dlg.chart.Chart.parent.constructor.call(this);
		this.id = 'Chart';
		var that = this;

		// Keeps current chart category and is used by ChartType DataView by its iterations in templete.
		var currentChartCategory = 'nocat';
		// Prevents focus switching from ChartCategories to ChartTypes by selecting item in ChartCategories.
		var fireSelectType = true;

		// Change input mode to DILAOG.
		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		Jedox.wss.app.currentDialogControl = 'chartcategories';

		// Handler functions.
		var onBeforeDestroyDialog = function (panel) {
			// Destroy all form elements and destroy self the form
			insChartForm.items.each(function(f) {
	            f.purgeListeners();
	            Ext.destroy(f);
	        });
	        insChartForm.purgeListeners();
			insChartForm.destroy();

			var selRangeDialog = Ext.getCmp('selRangeDlg');
			if (selRangeDialog)
				selRangeDialog.destroy();

			if (Jedox.wss.app.environment.inputMode == Jedox.wss.grid.GridMode.DIALOG) {
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
				clearCurDialogCntrl();
			}
			that.close();
			Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.chart);
		}

		var clearCurDialogCntrl = function () {
			Jedox.wss.app.currentDialogControl = null;
			Jedox.wss.app.currentDialogControlItemsCnt = 0;
		}

		var setSPData = function(cid){
			var typeIndex = chartTypesStore.find('charttype', cid);
			var spp = Ext.getCmp('FE-SE-panel');
			if (spp) {
				spp.setChartData(chartTypesStore.getAt((cid)? typeIndex : 0).data.WHRatio, false);
			}
		};

		var onCategorySelect = function (dView, node, selections) {
			Jedox.wss.app.currentDialogControl = dView.getId();
			Jedox.wss.app.currentDialogControlItemsCnt = chartCategoriesStore.getCount();

			currentChartCategory = 'nocat';
			if (node.id == 'All'.localize())
				chartTypesStore.clearFilter();
			else
				chartTypesStore.filter('catname', node.id);

			fireSelectType = false;
			Ext.getCmp('charttypes').select(0);
			fireSelectType = true;

			setSPData(false);
		}

		var onSelGroupBy = function(combo, record, index) {
			if (combo.getValue() == 'auto') {
				var fRowLbl = Ext.getCmp('firstRowLabels');
				fRowLbl.setValue('auto');
				fRowLbl.disable();

				var fColLbl = Ext.getCmp('firstColLabels');
				fColLbl.setValue('auto');
				fColLbl.disable();
			} else {
				Ext.getCmp('firstRowLabels').enable();
				Ext.getCmp('firstColLabels').enable();
			}
		}

		var onTypeSelect = function (dView, node, selections) {
			if (fireSelectType) {
				Jedox.wss.app.currentDialogControl = dView.getId();
				Jedox.wss.app.currentDialogControlItemsCnt = chartTypesStore.getCount();
				setSPData(node.id);
			}
		}

		var onContainerClick = function (dView, e) {
			e.stopEvent();
			return false;
		}

		var onFormCmpFocus = function (cmp) {
			clearCurDialogCntrl();
		}

		function selRangeHandleFnc(selected){
			that.win.show();
			Ext.getCmp('dataRange').setValue(selected);
		}

		var collectProperties = function() {
			// Create chart properties.
			var activeBook = Jedox.wss.app.activeBook;
			var selChartType = Ext.getCmp('charttypes').getSelectedRecords()[0];
			var whRatio = widthHeightRatio[selChartType.get('WHRatio')];

			// get dims
			var dims = Ext.getCmp('FE-SE-panel').getSPData();

			if (!dims){
				Ext.MessageBox.show({
					title: "Error".localize(),
					msg: "invalid_chart_sizepos".localize(),
					buttons: Ext.Msg.OK,
					icon: Ext.MessageBox.ERROR
				});
				return false;
			}

			var elWidth = dims.width;
			var elHeight = dims.height;
			var elTop = dims.top;
			var elLeft = dims.left;

			var nLoc = Jedox.wss.wsel.getNLoc(elLeft, elTop, elWidth, elHeight);


			var chartProps = {

				props: {

					ChartType:{
						General:{
							Type:selChartType.get('charttype')
						}
					},
					SourceData:{
						General:{
							Source:Ext.getCmp('dataRange').getValue(),
							GroupBy:Ext.getCmp('groupDataBy').getValue(),
							SeriesLabels:Ext.getCmp('firstRowLabels').getValue(),
							CategoryLabels:Ext.getCmp('firstColLabels').getValue()
						}
					},
					Title:{
						General:{
							HasTitle:Ext.getCmp('chartTitle').getValue()? true:false,
							Name:Ext.getCmp('chartTitle').getValue()
						}
					},
					Legend:{
						General:{
							HasLegend:Ext.getCmp('hasLegend').getValue()
						}
					},
					Axes:{
						HorizontalAxis:{
							Name:Ext.getCmp('horAxisLabel').getValue()
						},
						VerticalAxis:{
							Name:Ext.getCmp('verAxisLabel').getValue()
						}
					},

					General:{
						WH_ratio: whRatio,
						Layout: -1,
						Style: -1,
						ActiveSheet: Jedox.wss.app.activeSheetName

					}
				},
				n_location: nLoc.n_location,
				pos_offsets: nLoc.pos_offsets,
				size: [elWidth, elHeight],
				operation:'insert'
			}


			// Chart properties error checking.
			if (!chartProps.props.ChartType.General.Type.indexOf('xl') == 0) {
				Ext.MessageBox.show({
					title: 'Input Error'.localize(),
					msg: 'chartDlg_invalidChartType'.localize(),
					buttons: Ext.MessageBox.OK,
					icon: Ext.MessageBox.WARNING
				});
				return false;
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

			return chartProps;

		}

		var doInsertChart = function () {
			that.win.hide();

			var chartProps = collectProperties();
			chartProps.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();
			chartProps.locked = Jedox.wss.wsel.Chart.defLockedState;
			chartProps.name = '';

			if (chartProps != false) {
				// TODO: Show please wait...

				// Send chart Properites.
				var chartID = Jedox.backend.wss.wsel('add_chart', chartProps);
				Jedox.wss.wsel.chart.createChart(chartID, chartProps.n_location, chartProps.pos_offsets, chartProps.size, chartProps.props.ChartType.General.Type, chartProps.zindex, chartProps.locked, chartProps.name);
			}

			var defaultRange = Jedox.wss.app.environment.defaultSelection;
			if (!defaultRange.isSingleCell())
				defaultRange.selectFirstVisCell();

			that.win.close();
		}

		var doEditChart = function () {
			that.win.hide();
			var chartProps = collectProperties();

			if (chartProps != false) {
				chartProps.id = chartID;
				// TODO: Show please wait...

				// Send chart Properites.
				if (Jedox.backend.wss.wsel('update_chart', chartProps)) {
					var currDate = new Date(),
						chart = Jedox.wss.wsel.wselRegistry.get(Jedox.wss.app.activeBook, Jedox.wss.app.activeSheet._uid, chartID);

					for (var i = chart._panes.length - 1; i >= 0; i--)
						document.getElementById(chart._panes[i]._domId.concat('_wsel_cont_', chartID)).src = '/be/wss/gen_element.php?wam='.concat(
							Jedox.wss.app.appModeS,
							'&buid=', chart._book.uid,
							'&suid=', chart._sheet.getUid(),
							'&id=', chartID,
							'&w=', chartProps.size[0],
							'&h=', chartProps.size[1],
							'&ts=', currDate.getTime()
						);
				}
			}

			that.win.destroy();
		}

		var fillChartDialog = function (chartID) {
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
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.chart);
						}
				});
				that.win.destroy();
				return;
			}

			// Select chart type.
			var typeIndex = chartTypesStore.find('charttype', chartProps.type);
			Ext.getCmp('charttypes').select((typeIndex > 0) ? typeIndex : 0);

			Ext.getCmp('chartTitle').setValue(chartProps.title);
			Ext.getCmp('horAxisLabel').setValue(chartProps.xAxisLabel);
			Ext.getCmp('verAxisLabel').setValue(chartProps.yAxisLabel);
			Ext.getCmp('hasLegend').setValue(chartProps.hasLegend);

			Ext.getCmp('dataRange').setValue(chartProps.dataRange);
			Ext.getCmp('groupDataBy').setValue(chartProps.groupBy);

			Ext.getCmp('firstRowLabels').setValue(chartProps.firstRowLabels);
			Ext.getCmp('firstColLabels').setValue(chartProps.firstColLabels);
		}

		var chartCategoriesData = [
			['all', 'All'.localize(), 'ico_cat_all'],
			['column', 'Column'.localize(), 'ico_cat_column'],
			['line', 'Line'.localize(), 'ico_cat_line'],
			['pie', 'Pie'.localize(), 'ico_cat_pie'],
			['bar', 'Bar'.localize(), 'ico_cat_bar'],
			['area', 'Area'.localize(), 'ico_cat_area'],
			['xyscatter', 'X Y (Scatter)'.localize(), 'ico_cat_xyscatter'],
			['stock', 'Stock'.localize(), 'ico_cat_stock'],
			//['surface', 'Surface'.localize(), 'ico_cat_surface'],
			['doughnut', 'Doughnut'.localize(), 'ico_cat_doughnut'],
			['bubble', 'Bubble'.localize(), 'ico_cat_bubble'],
			['radar', 'Radar'.localize(), 'ico_cat_radar'],
			['meter', 'Meter'.localize(), 'ico_cat_meter']
		];

		var chartCategoriesStore = new Ext.data.SimpleStore({
									fields: ['catname', 'catlabel', 'icon'],
									data: chartCategoriesData
									});

		var tplChartCategories = new Ext.XTemplate(
			'<div class="charttypes" style="width: 92%;">','Categories'.localize(),'</div>',
			'<tpl for=".">',
	            '<div class="thumb-wrap" id="{catlabel}">',
			    '<div class="thumb"><img class="{icon}" width="16" height="16" src="../lib/ext/resources/images/default/s.gif" >&nbsp;&nbsp;&nbsp;{catlabel}</div></div>',
	        '</tpl>'
		);

		var chartTypesData = [
			['Column'.localize(), 'xlColumnClustered', 'Clustered Column'.localize(), 'defHor'],
			['Column'.localize(), 'xlColumnStacked', 'Stacked Column'.localize(), 'defHor'],
			['Column'.localize(), 'xlColumnStacked100', '100% Stacked Column'.localize(), 'defHor'],
			['Column'.localize(), 'xl3DColumnClustered', '3-D Clustered Column'.localize(), 'defHor'],
			['Column'.localize(), 'xl3DColumnStacked', 'Stacked Column in 3-D'.localize(), 'defHor'],
			['Column'.localize(), 'xl3DColumnStacked100', '100% Stacked Column in 3-D'.localize(), 'defHor'],
			['Column'.localize(), 'xlCylinderColClustered', 'Clustered Cylinder'.localize(), 'defHor'],
			['Column'.localize(), 'xlCylinderColStacked', 'Stacked Cylinder'.localize(), 'defHor'],
			['Column'.localize(), 'xlCylinderColStacked100', '100% Stacked Cylinder'.localize(), 'defHor'],
			['Line'.localize(), 'xlLine', 'Line'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineStacked', 'Stacked Line'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineStacked100', '100% Stacked Line'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineRotated', 'Rotated Line'.localize(), 'defVer'],
			['Line'.localize(), 'xlLineMarkers', 'Line with Markers'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineMarkersStacked', 'Stacked Line with Markers'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineMarkersStacked100', '100% Stacked Line with Markers'.localize(), 'defHor'],
			['Line'.localize(), 'xlLineMarkersRotated', 'Rotated Line with Markers'.localize(), 'defVer'],
			['Line'.localize(), 'xl3DLine', '3-D Line'.localize(), 'defHor'],
			['Pie'.localize(), 'xlPie', 'Pie'.localize(), 'defHor'],
			['Pie'.localize(), 'xl3DPie', 'Pie in 3-D'.localize(), 'defHor'],
			['Pie'.localize(), 'xlPieExploded', 'Exploded Pie'.localize(), 'defHor'],
			['Pie'.localize(), 'xl3DPieExploded', 'Exploded Pie in 3-D'.localize(), 'defHor'],
			['Bar'.localize(), 'xlBarClustered', 'Clustered Bar'.localize(), 'defHor'],
			['Bar'.localize(), 'xlBarStacked', 'Stacked Bar'.localize(), 'defHor'],
			['Bar'.localize(), 'xlBarStacked100', '100% Stacked Bar'.localize(), 'defHor'],
			['Bar'.localize(), 'xl3DBarClustered', 'Clustered Bar in 3-D'.localize(), 'defHor'],
			['Bar'.localize(), 'xl3DBarStacked', 'Stacked Bar in 3-D'.localize(), 'defHor'],
			['Bar'.localize(), 'xl3DBarStacked100', '100% Stacked Bar in 3-D'.localize(), 'defHor'],
			['Bar'.localize(), 'xlCylinderBarClustered', 'Clustered Horizontal Cylinder'.localize(), 'defHor'],
			['Bar'.localize(), 'xlCylinderBarStacked', 'Stacked Horizontal Cylinder'.localize(), 'defHor'],
			['Bar'.localize(), 'xlCylinderBarStacked100', '100% Stacked Horizontal Cylinder'.localize(), 'defHor'],
			['Area'.localize(), 'xlArea', 'Area'.localize(), 'defHor'],
			['Area'.localize(), 'xlAreaStacked', 'Stacked Area'.localize(), 'defHor'],
			['Area'.localize(), 'xlAreaStacked100', '100% Stacked Area'.localize(), 'defHor'],
			['Area'.localize(), 'xl3DArea', '3-D Area'.localize(), 'defHor'],
			['Area'.localize(), 'xl3DAreaStacked', 'Stacked Area in 3-D'.localize(), 'defHor'],
			['Area'.localize(), 'xl3DAreaStacked100', '100% Stacked Area in 3-D'.localize(), 'defHor'],
			['X Y (Scatter)'.localize(), 'xlXYScatter', 'Scatter with only Markers'.localize(), 'defHor'],
			['X Y (Scatter)'.localize(), 'xlXYScatterSmooth', 'Scatter with Smooth Lines and Markers'.localize(), 'defHor'],
			['X Y (Scatter)'.localize(), 'xlXYScatterSmoothNoMarkers', 'Scatter with Smooth Lines'.localize(), 'defHor'],
			['X Y (Scatter)'.localize(), 'xlXYScatterLines', 'Scatter with Straight Lines and Markers'.localize(), 'defHor'],
			['X Y (Scatter)'.localize(), 'xlXYScatterLinesNoMarkers', 'Scatter with Straight Lines'.localize(), 'defHor'],
			['Stock'.localize(), 'xlStockHLC', 'High-Low-Close'.localize(), 'defHor'],
			['Stock'.localize(), 'xlStockOHLC', 'Open-High-Low-Close'.localize(), 'defHor'],
			['Doughnut'.localize(), 'xlDoughnut', 'Doughnut'.localize(), 'defHor'],
			['Doughnut'.localize(), 'xlDoughnutExploded', 'Exploded Doughnut'.localize(), 'defHor'],
			['Bubble'.localize(), 'xlBubble', 'Bubble'.localize(), 'defHor'],
			['Bubble'.localize(), 'xlBubble3DEffect', 'Bubble with a 3-D Effect'.localize(), 'defHor'],
			['Radar'.localize(), 'xlRadar', 'Radar'.localize(), 'defHor'],
			['Radar'.localize(), 'xlRadarMarkers', 'Radar with Markers'.localize(), 'defHor'],
			['Radar'.localize(), 'xlRadarFilled', 'Filled Radar'.localize(), 'defHor'],
			['Meter'.localize(), 'xlMeterOdoFull', 'Odometer Full'.localize(), 'equal'],
			['Meter'.localize(), 'xlMeterOdoFull100', 'Odometer Full Percentage'.localize(), 'equal'],
			['Meter'.localize(), 'xlMeterOdoHalf', 'Odometer Half'.localize(), 'odoHalf'],
			['Meter'.localize(), 'xlMeterOdoHalf100', 'Odometer Half Percentage'.localize(), 'odoHalf'],
			['Meter'.localize(), 'xlMeterAngularWide', 'Wide Angular Meter'.localize(), 'angulWide'],
			['Meter'.localize(), 'xlMeterLineHorizontal', 'Horizontal Line Meter'.localize(), 'lineHor'],
			['Meter'.localize(), 'xlMeterLineVertical', 'Vertical Line Meter'.localize(), 'lineVer']
		];

		var chartTypesStore = new Ext.data.SimpleStore({
								fields: ['catname', 'charttype', 'chartlabel', 'WHRatio'],
								data: chartTypesData
								});

		var widthHeightRatio = Jedox.wss.wsel.chart.whRatio;

		var groupDataByData = [
			['Auto'.localize(), 'auto'],
			['Columns'.localize(), 'cols'],
			['Rows'.localize(), 'rows']
		];

		var labelPosData = [
			['Auto'.localize(), 'auto'],
			['Yes'.localize(), 'yes'],
			['No'.localize(), 'no']
		];

		var labelPosItems = new Ext.data.SimpleStore({
									fields: ['itemName', 'itemValue'],
									data: labelPosData
									});

		var tplChartTypes = new Ext.XTemplate(

			'<tpl for=".">',
				'<tpl if="this.isCurrCat(catname)">',
					'<div class="x-clear"></div>',
					'<div class="charttypes">{catname}</div>',
				'</tpl>',
	            '<div class="thumb-wrap" id="{charttype}">',
			    '<div class="thumb"><img class="{charttype}" src="../lib/ext/resources/images/default/s.gif" width="46" height="46" title="{chartlabel}"></div></div>',
	        '</tpl>',

	        '<div class="x-clear"></div>', {
	        	isCurrCat: function (cat) {
	        		var result = (cat != currentChartCategory);
	        		currentChartCategory = cat;

	         		return result;
	        	}
			}
		);

		var labelsPanel = new Ext.Panel({
        	baseCls: 'x-title-f',
        	items: [{
					xtype: 'fieldset',
		            title: 'Labels'.localize(),
		            collapsed: true,
		            collapsible: true,
		            autoHeight: true,
		            layout: 'form',
		            id: 'chartLabelsPan',
		            style: 'padding: 2px 3px 1px 10px;',
		            listeners: {
						expand: function(pan){
							that.containers.lblPanel = pan;
						},
						collapse: function(pan){
							delete that.containers.lblPan;
						}
					},
		            items: [{
		            	id: 'chartTitle',
		            	xtype: 'textfield',
		            	anchor: '80%',
		            	tabIndex: 20,
		            	fieldLabel: 'Chart title'.localize(),
		            	listeners: {
							focus: {fn: onFormCmpFocus, scope: this}
						}
		            }, {
		            	id: 'horAxisLabel',
		            	xtype: 'textfield',
		            	anchor: '80%',
		            	tabIndex: 21,
		            	fieldLabel: 'Horizontal axis'.localize(),
		            	listeners: {
							focus: {fn: onFormCmpFocus, scope: this}
						}
		            }, {
		            	id: 'verAxisLabel',
		            	xtype: 'textfield',
		            	anchor: '80%',
		            	tabIndex: 22,
		            	fieldLabel: 'Vertical axis'.localize(),
		            	listeners: {
							focus: {fn: onFormCmpFocus, scope: this}
						}
		            }, {
		            	id: 'hasLegend',
		            	xtype: 'checkbox',
		            	checked: true,
		            	tabIndex: 23,
		            	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		            	fieldLabel: 'Legend'.localize(),
		            	listeners: {
							focus: {fn: onFormCmpFocus, scope: this}
						}
		            }]
			}]
        });

//		function getSheetName(){
//			var sheetName = Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName();
//			return sheetName.search(/ /) >= 0? sheetName = '\''.concat(sheetName, '\''):sheetName
//		}

		var dataSourcePanel = this.containers.dsPanel = new Ext.Panel({
        	baseCls: 'x-title-f',
        	items:[
        	       {
					xtype: 'fieldset',
		            title: 'Data Source'.localize(),
		            collapsible: false,
		            autoHeight: true,
		            layout: 'column',
		            style: 'padding: 2px 3px 1px 10px;',
		            items: [new Ext.Panel({
		            	width: 510,
		            	layout: 'form',
		            	cls: 'chartdatasource',
		            	bodyStyle: 'background-color: transparent; border-style: none;',
						labelWidth: 120,
						labelAlign: 'left',
		            	items: [{
		            		id: 'dataRange',
		            		xtype: 'textfield',
		            		tabIndex: 10,
		            		fieldLabel: 'Chart data range'.localize(),
		            		width: 380,
		            		value: '='.concat(Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(true), '!', Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(true)),
		            		listeners: {
								focus: {fn: onFormCmpFocus, scope: this}
							}
		            	}, {
		           			xtype: 'combo',
							id: 'groupDataBy',
							tabIndex: 12,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							fieldLabel: 'Group data by'.localize(),
							store: new Ext.data.SimpleStore({
								fields: ['itemName', 'itemValue'],
								data: groupDataByData
							}),
							displayField: 'itemName',
							valueField: 'itemValue',
							mode: 'local',
							triggerAction: 'all',
							value: 'auto',
							listWidth: 70,
							width: 70,
							editable: false,
							allowBlank: false,
							selectOnFocus: false,
							listeners: {
								focus: {fn: onFormCmpFocus, scope: this},
								select: {fn: onSelGroupBy, scope: this}
							}
		           		}, {
							xtype: 'combo',
							id: 'firstRowLabels',
							fieldLabel: 'Use series labels'.localize(),
							store: labelPosItems,
							displayField: 'itemName',
							valueField: 'itemValue',
							mode: 'local',
							triggerAction: 'all',
							value: 'auto',
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 13,
							listWidth: 70,
							width: 70,
							editable: false,
							allowBlank: false,
							selectOnFocus: false,
							disabled: true,
							listeners: {
								focus: {fn: onFormCmpFocus, scope: this}
							}
						}, {
							xtype: 'combo',
							id: 'firstColLabels',
							fieldLabel: 'Use category labels'.localize(),
							store: labelPosItems,
							displayField: 'itemName',
							valueField: 'itemValue',
							mode: 'local',
							triggerAction: 'all',
							value: 'auto',
							tabIndex: 14,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							listWidth: 70,
							width: 70,
							editable: false,
							allowBlank: false,
							selectOnFocus: false,
							disabled: true,
							listeners: {
								focus: {fn: onFormCmpFocus, scope: this}
							}
		            	}]
		            }), new Ext.Panel({
		            	columnWidth: 1,
		            	layout: 'form',
		            	bodyStyle: 'background-color: transparent; border-style: none;',
		            	items: [new Ext.Toolbar.Button({
		            		id: 'selRangeBegin',
		            		tabIndex: 11,
		            		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		            		iconCls: 'select-range-icon',
		            		cls: 'x-btn-icon',
		            		tooltip: "Select Range".localize(),
							handler: function() {
			            			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
			            				fnc: [this, selRangeHandleFnc],
			            				format: '={Sheet}!{Range}',
			            				rng: Ext.getCmp('dataRange').getValue()
			            			}]);

			            			that.win.hide();
		            			}
		            	})]
		            })]
        	       } ]
        });

		var insChartForm = new Ext.FormPanel({
			id: 'insertChartForm',
			baseCls: 'x-plain',
			title: 'General'.localize(),
			labelWidth: 100,
			labelAlign: 'left',
			frame: true,
			bodyStyle: 'padding: 5px 5px 0px; font-size: 9pt;',
			width: 400,
			defaultType: 'textfield',
			buttonAlign: 'right',
			header: false,
			monitorValid: true,
			autoHeight: true,

			items: [new Ext.Panel({
				id: 'chartselectionpanel',
	            layout: 'column',
	            border: false,
				layoutConfig: {
		        	columns: 2
		    	},
	            bodyStyle: 'background-color: transparent;',
	            items: [
					new Ext.Panel({
		            	id: 'chartcategoriespanel',
		            	width: 130,
		            	layout: 'form',
		            	height: 280,
		            	autoScroll: true,
			            items: [new Ext.DataView({
			            	id: 'chartcategories',
							store: chartCategoriesStore,
							tpl: tplChartCategories,
							autoHeight: true,
							multiSelect: false,
							singleSelect: true,
							overClass: 'x-view-over',
							itemSelector: 'div.thumb-wrap',
							emptyText: 'No images to display'.localize(),
							listeners: {
								beforeselect: {fn: onCategorySelect, scope: this},
								containerclick: {fn: onContainerClick, scope: this}
							}
						})]
			        }),
					new Ext.Panel({
			        	id: 'charttypespanel',
						width:430,
		            	height: 280,
		            	autoScroll: true,
			            items: [
							new Ext.DataView({
				            	id: 'charttypes',
								store: chartTypesStore,
								tpl: tplChartTypes,
								autoHeight: true,
								autoWidth: true,
								multiSelect: false,
								singleSelect: true,
								overClass: 'x-view-over',
								itemSelector: 'div.thumb-wrap',
								emptyText: 'No images to display'.localize(),
								listeners: {
									beforeselect: {fn: onTypeSelect, scope: this},
									containerclick: {fn: onContainerClick, scope: this}
								}
							})
						]
					})
				]
	        }),
	        dataSourcePanel,
	        labelsPanel]
		});

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
			items: [insChartForm],
			listeners: {
				tabchange: function(p, t){
					//set containers
					if (t.id == 'SPPan'){
						that.win.setHeight();
						delete that.containers.dsPanel;
						delete that.containers.lblPanel;
						that.containers.sp = t;
					} else {
						delete that.containers.sp;
						that.containers.dsPanel = dataSourcePanel;
						if (!Ext.getCmp('chartLabelsPan').collapsed)that.containers.lblPanel = labelsPanel;
					}
				}
			}
		});

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
	        	items: [panel]
			});
			tabs.add(np);
			setSPData(false);
		};

		//conf.type, conf
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.FESizePositionPanel, [getSizePosPan, 'Chart', false]);

		this.win = new Ext.Window({
			id: 'insChartDlg',
			title: ((mode == 'insert') ? 'Insert Chart' : 'Edit Chart').localize(),
			cls: 'wssdialog default-format-window',
			layout: 'fit',
			width: 620,
			autoHeight: true,
			closeable: true,
			closeAction: 'close',
			autoDestroy: true,
			plain: true,
			constrain: true,
			modal: true,
			resizable:false,
			onEsc: Ext.emptyFn,
			items: [tabs],
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.chart);
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.FESizePositionPanel);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();},
				beforedestroy: {fn: onBeforeDestroyDialog, scope: this}
				//resize: {fn: onAfterWindowResize, scope: this}
			},
			buttons: [
					(this.components.OK = new Ext.Button({
						id: 'wInsChart_ok_btn',
						text: 'OK'.localize(),
						tabIndex: 102,
						handler: function(){
							(mode == 'insert') ? doInsertChart() : doEditChart();
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						id: 'wInsChart_cancel_btn',
						text: 'Cancel'.localize(),
						tabIndex: 103,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))
			          ]
		});

		//insChartForm.addButton({text: 'Cancel'.localize(), tabIndex: 4}, function() {that.win.close();});

		Ext.getCmp('chartcategories').select('All'.localize());

		if (mode == 'edit')
			fillChartDialog(chartID);


		that.setContext();
		that.win.show(that);
		Ext.getCmp('chartcategories').select(0, false, false);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.chart.Chart, Jedox.dlg.Dialog);