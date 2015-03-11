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
 * SVN: $Id: EditChart.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */



Jedox.wss.dlg.chart.editChartDialog = function(mode, chartID) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.chart.EditChart(mode, chartID));
};

Jedox.wss.dlg.chart.EditChart = (function() {

	return function (mode, chartID) {

		Jedox.wss.dlg.chart.EditChart.parent.constructor.call(this);
		this.id = 'editChart';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var _charProps;

		var _axis_group = 0;

		var chartTypesSizeDefs = Jedox.wss.wsel.chart.type_sizeDefs,
			chartMinSizeFactor = Jedox.wss.wsel.chart.min_sizeFactor,
			chartsMinWidthHeightRatio = Jedox.wss.wsel.chart.min_whRatio,
			widthHeightRatio = Jedox.wss.wsel.chart.whRatio;

		function getWHRatio(){
			var selChartType = _chartProps.ChartType.General.Type;
			var whRatio = widthHeightRatio[chartTypesSizeDefs[selChartType]];
			return whRatio;
		}

		var _reg = {
			1:{HorizontalAxisScale:true}, //Other
			2:{Legend:true, Title:true, HorizontalAxisName:true, VericalAxis:true}, //Pie, Doughnt
			3:{Legend:true, HorizontalAxisName:true, VericalAxis:true}, //Meter
			4:{} //Bubble, Stock, Radar, Scatter
		}

		// Chart Types definitions
		var _chartTypesInterfaceDate = {
			'xlColumnClustered': 1,
			'xlColumnStacked': 1,
			'xlColumnStacked100': 1,
			'xl3DColumnClustered': 1,
			'xl3DColumnStacked': 1,
			'xl3DColumnStacked100': 1,
			'xlCylinderColClustered': 1,
			'xlCylinderColStacked': 1,
			'xlCylinderColStacked100': 1,
			'xlLine': 1,
			'xlLineStacked': 1,
			'xlLineStacked100': 1,
			'xlLineRotated': 5,
			'xlLineMarkers': 1,
			'xlLineMarkersStacked': 1,
			'xlLineMarkersStacked100': 1,
			'xlLineMarkersRotated': 5,
			'xl3DLine': 1,
			'xlPie': 2,
			'xl3DPie': 2,
			'xlPieExploded': 2,
			'xl3DPieExploded': 2,
			'xlBarClustered': 5,
			'xlBarStacked': 5,
			'xlBarStacked100': 5,
			'xl3DBarClustered': 5,
			'xl3DBarStacked': 5,
			'xl3DBarStacked100': 5,
			'xlCylinderBarClustered': 5,
			'xlCylinderBarStacked': 5,
			'xlCylinderBarStacked100': 5,
			'xlArea': 1,
			'xlAreaStacked': 1,
			'xlAreaStacked100': 1,
			'xl3DArea': 1,
			'xl3DAreaStacked': 1,
			'xl3DAreaStacked100': 1,
			'xlXYScatter': 4,
			'xlXYScatterSmooth': 4,
			'xlXYScatterSmoothNoMarkers': 4,
			'xlXYScatterLines': 4,
			'xlXYScatterLinesNoMarkers': 4,
			'xlStockHLC': 4,
			'xlStockOHLC': 4,
			'xlDoughnut': 2,
			'xlDoughnutExploded': 2,
			'xlBubble': 4,
			'xlBubble3DEffect': 4,
			'xlRadar':  6,
			'xlRadarMarkers':  6,
			'xlRadarFilled':  6,
			'xlMeterOdoFull': 3,
			'xlMeterOdoFull100': 3,
			'xlMeterOdoHalf': 3,
			'xlMeterOdoHalf100': 3,
			'xlMeterAngularWide': 3,
			'xlMeterLineHorizontal': 3,
			'xlMeterLineVertical': 3
		};


		/************************************
		  **** Fill componenets *****
		************************************/

		var Fill = function(type, obj) {

			var typesData = {
				chartArea:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'chart-area-fill', rbBorderGroup:'chart-area-border', defaultColor:'#FFFFFF', noFillCONST:'0x000100'},
				plotArea:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'plot-area-fill', rbBorderGroup:'plot-area-border', defaultColor:'#FFFFFF', noFillCONST:'0xFFFFFFEFE7'},
				title:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'title-fill', rbBorderGroup:'title-border', noFillCONST:'0x000100'},
				legend:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'legend-fill', rbBorderGroup:'legend-border', defaultColor:'#FFFFFF', noFillCONST:'0xFFFFFFEFE7'}
			}

			var _fillColor = typesData[type].defaultColor;
			var _obj;
			var _flags = {preselect:false, setValueCall:false}

			var _noFillCONST = '0x000100';


			var fillLbl = new Ext.form.Label({
				text:typesData[type].fillLbl.concat(':'),
				cls:'edit-chart-title'
			});

			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var noFillRb = new Ext.form.Radio({
				boxLabel: 'No fill'.localize(),
				hideLabel: true,
				tabIndex: 10,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked:false,
				name:typesData[type].rbFillGroup,
				width:200,
				handler:function(){if (this.getValue())switchSolid(solidFillColorSwitchPanel, 0);},
				inputValue: 1
			});

			var solidFillRb = new Ext.form.Radio({
				boxLabel: 'Solid fill'.localize(),
				hideLabel: true,
				tabIndex: 11,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked:false,
				name:typesData[type].rbFillGroup,
				width:100,
				handler:function(){if (this.getValue())switchSolid(solidFillColorSwitchPanel, 1);},
				inputValue: 1
			});

			var automaticFillRb = new Ext.form.Radio({
				boxLabel: 'Automatic'.localize(),
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 12,
				checked:false,
				name:typesData[type].rbFillGroup,
				width:100,
				handler:function(){if (this.getValue())switchSolid(solidFillColorSwitchPanel, 0);},
				inputValue: 1
			});

			var fillColorLbl = new Ext.form.Label({
				text:'Color'.localize().concat(':')
			});

			var solidFillBtn = new Ext.Toolbar.SplitButton({
				minWidth: 100,
				tabIndex: 13,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				menu: new Ext.menu.ColorMenu({
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					listeners: {
						select: function(colorP, colorStr){
							_fillColor = '#' + colorStr;
							setColorButton(solidFillBtn, _fillColor, false);
						},
						beforeshow: function(thisMenu){
	//						if (_fillColor.replace('#','') in thisMenu.palette.colors)
								thisMenu.palette.select(_fillColor);
						}
					}
				})
			});

			var solidFillColorPanel = new Ext.Panel({
				layout: 'column',
				border: false,
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				baseCls: 'x-plain',
				width: 400,
				height: 100,
				items: [{
					//title panel
					border: false,
					width: 50,
					items: fillColorLbl
				}, {
					//button panel',
					border: false,
					width: 200,
					height: 50,
					items:solidFillBtn
				}]
			});



			var solidFillColorSwitchPanel = new Ext.Panel({
				layout: 'card',
				border: false,
				baseCls: 'x-plain',
				activeItem:1,
				items: [
					{html:'', baseCls:'x-plain'},
					solidFillColorPanel
				]
			});


			var fillPanel = new Ext.Panel({
				title: 'Fill'.localize(),
				layout: 'form',
				baseCls: 'x-plain',
				items: [BRLbl, fillLbl, BRLbl, noFillRb, solidFillRb, automaticFillRb, solidFillColorSwitchPanel],
				listeners:{
					render:function(panel){
						setTimeout(function(){
							if (_flags.setValueCall && !_flags.preselect)
								setFillValue(_obj);
						});
					}
				}
			});


			//private methodes
			function switchSolid (panel, index){
				solidFillColorSwitchPanel.getLayout().setActiveItem(index);
			}

			function setColorButton(colorBtn, color, setWidth){
				var tmpElem = Ext.DomQuery.selectNode('*[id=' + colorBtn.btnEl.id + ']');
				tmpElem.style.background = color;
				tmpElem.style.width = "80px";
				tmpElem.style.height= "15px";
			};

			function getFillValue(){

				if (fillPanel.rendered) //if rendered than interface is set and gets value
					return {BackColor: noFillRb.getValue()? typesData[type].noFillCONST:solidFillRb.getValue()? _fillColor.replace('#', '0x'):typesData[type].defaultColor.replace('#', '0x')} //if set to -1 no color is set}

				return _obj; // else returns set _obj
			}

			function setFillValue(obj){
				_flags.setValueCall = true;
				if (fillPanel.rendered) {
					_flags.preselect = true;
					switch (obj.BackColor) {
						case typesData[type].noFillCONST:
						case 'Transparent':
							noFillRb.setValue(true);
							break;
						case 'automatic':
							automaticFillRb.setValue(true);
							break;
						default:
							_fillColor = obj.BackColor.replace('0x', '#');
							solidFillRb.setValue(true);
							setColorButton(solidFillBtn, _fillColor, false);
							solidFillBtn.fireEvent('select', _fillColor, obj.Color)
							break;
					}
				}
				else {
					_obj = obj;
				}
			}


			//public methods
			this.getPanel = function(){
				return fillPanel;
			}

			this.getValue = function(){
				return getFillValue();
			}

			this.setValue = function(obj){
				setFillValue(obj);
			}
		}



		/************************************
		  **** Border componenets *****
		************************************/

		var Border = function(type, color){

			var typesData = {
				chartArea:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'chart-area-fill', rbBorderGroup:'chart-area-border', defaultColor:'#FFFFFF'},
				plotArea:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'plot-area-fill', rbBorderGroup:'plot-area-border', defaultColor:'#868686'},
				title:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'title-fill', rbBorderGroup:'title-border', defaultColor:'#FFFFFF'},
				legend:{fillLbl: 'Fill'.localize(), borderLbl: 'Border Color'.localize(), rbFillGroup:'legend-fill', rbBorderGroup:'legend-border', defaultColor:'#FFFFFF'}
			}

			var _borderColor = typesData[type].defaultColor;
			var _obj;
			var _flags = {preselect:false, setValueCall:false}

			var _noBorderCONST = '0x000100';

			var borderColorLbl = new Ext.form.Label({
				text:'Border Color'.localize().concat(':'),
				cls:'edit-chart-title'
			});

			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var noLineRb = new Ext.form.Radio({
				boxLabel: 'No line'.localize(),
				hideLabel: true,
				checked:false,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 20,
				name:typesData[type].rbBorderGroup,
				width:100,
				handler:function(){if (this.getValue())switchSolid(solidLineColorSwitchPanel, 0);},
				inputValue: 1
			});

			var solidLineRb = new Ext.form.Radio({
				boxLabel: 'Solid line'.localize(),
				hideLabel: true,
				tabIndex: 21,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				checked:false,
				name:typesData[type].rbBorderGroup,
				width:100,
				handler:function(){if (this.getValue())switchSolid(solidLineColorSwitchPanel, 1);},
				inputValue: 1
			});

			var automaticLineRb = new Ext.form.Radio({
				boxLabel: 'Automatic'.localize(),
				hideLabel: true,
				checked:false,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 22,
				name:typesData[type].rbBorderGroup,
				width:100,
				handler:function(){if (this.getValue())switchSolid(solidLineColorSwitchPanel, 0);},
				inputValue: 1
			});


			var lineColorLbl = new Ext.form.Label({
				text:'Color'.localize().concat(':')
			});

			var solidLineBtn = new Ext.Toolbar.SplitButton({
				minWidth: 100,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 23,
				menu: new Ext.menu.ColorMenu({
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					listeners: {
						select: function(colorP, colorStr){
							_borderColor = '#' + colorStr;
							setColorButton(solidLineBtn, _borderColor, false);
						},
						beforeshow: function(thisMenu){
							if (_borderColor in thisMenu.palette.colors)
								thisMenu.palette.select(_borderColor);
						}
					}
				})
			});

			var solidLineColorPanel = new Ext.Panel({
				layout: 'column',
				border: false,
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				baseCls: 'x-plain',
				width: 400,
				height: 100,
				items: [{
					//title panel
					border: false,
					width: 50,
					items: lineColorLbl
				}, {
					//button panel',
					border: false,
					width: 200,
					height: 50,
					items:solidLineBtn
				}]
			});


			var solidLineColorSwitchPanel = new Ext.Panel({
				layout: 'card',
				border: false,
				baseCls: 'x-plain',
				activeItem:1,
				items: [
					{html:'', baseCls:'x-plain'},
					solidLineColorPanel
				]
			});


			var borderPanel = new Ext.Panel({
				title: 'Border Color'.localize(),
				layout: 'form',
				baseCls:'x-plain',
				items: [BRLbl, borderColorLbl , BRLbl, noLineRb, solidLineRb, automaticLineRb, solidLineColorSwitchPanel],
				listeners:{
					render:function(panel){
						setTimeout(function(){
							if (_flags.setValueCall && !_flags.preselect)
								setBorderValue(_obj);
						});
					}
				}
			});


			//private methods
			function switchSolid (panel, index){
				solidLineColorSwitchPanel.getLayout().setActiveItem(index);
			}

			function setColorButton(colorBtn, color, setWidth){
	//			var tmpElem = Ext.DomQuery.selectNode('*[id=' + colorBtn.id + '] button[class=x-btn-text]');
				var tmpElem = Ext.DomQuery.selectNode('*[id=' + colorBtn.btnEl.id + ']');
				tmpElem.style.background = color;
				tmpElem.style.width = "80px";
				tmpElem.style.height= "15px";
			};

			function getBorderValue(){
				if (borderPanel.rendered) //if rendered than interface is set and gets value
					return {Color: noLineRb.getValue() ? _noBorderCONST : solidLineRb.getValue() ? _borderColor.replace('#', '0x') : automaticLineRb.getValue() ? typesData[type].defaultColor.replace('#', '0x') : false} //if set to -1 no color is set}

				return _obj; // else returns set _obj
			}

			function setBorderValue(obj){
				_flags.setValueCall = true;
				if (borderPanel.rendered) {
					_flags.preselect = true;
					switch (obj.Color) {
						case _noBorderCONST:
						case 'Transparent':
							noLineRb.setValue(true);
							break;
						case 'automatic':
							automaticLineRb.setValue(true);
							break;
						default:
							_borderColor = obj.Color.replace('0x', '#');
							solidLineRb.setValue(true);
							setColorButton(solidLineBtn, _borderColor, false);
							solidLineBtn.fireEvent('select', _borderColor, obj.Color);
							break;
					}
				}
				else{
					_obj = obj;
				}
			}

			//public methods
			this.getPanel = function(){
				return borderPanel;
			}

			this.getValue = function(){
				return getBorderValue();
			}

			this.setValue = function(obj){
				setBorderValue(obj);
			}

		}




		/************************************
		  *** Series options componenets ***
		************************************/

		var SeriesOptions = function(pointsFlag){

			var _pointsFlag = pointsFlag;
			var _paletteData;
			var _seriesData;
			var _renderColor = {color:'', border:''} // first color container to set on buttonsplit after render button
			var _handsColor;
			var _customPalette = {color:[], border:[]};

			var seriesOptionsLbl = new Ext.form.Label({
				text: 'Series Options'.localize().concat(':'),
				cls: 'edit-chart-title'
			});


			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};


			var paletteCmb = new Ext.form.ComboBox({
				fieldLabel: 'Palette'.localize(),
				tabIndex: 50,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				store: new Ext.data.SimpleStore({
					data: [['Custom'.localize(), 'custom'], ['Office'.localize(), 'office'], ['Apex'.localize(), 'apex'], ['Aspect'.localize(), 'aspect']],
					fields: ['itemName', 'itemValue']
				}),
				displayField: 'itemName',
				valueField: 'itemValue',
				mode: 'local',
				triggerAction: 'all',
				value: 'custom',
				listWidth: 120,
				width: 120,
				editable: false,
				allowBlank: false,
				selectOnFocus: false,
				listeners: {
					select: function(){
						setPalette(this.getValue());
					}
				}
			});



			var seriesStore = new Ext.data.SimpleStore({
				fields: [
				    {name: 'name'},
				    {name: 'color'},
				    {name: 'border'}
				],
				listeners:{
					update: function(store, record, operation) {
						var index = this.indexOf(record);
						_seriesData[index][1] = record.get('color');
						_seriesData[index][2] = record.get('border');

						paletteCmb.setValue('custom');
						_customPalette = null;
					}
				}
			});



			Ext.ux.MySplitButton = Ext.extend(Ext.Toolbar.SplitButton,{

			    setValue : function(value){
					if (this.btnEl){
						var tmpElem = Ext.DomQuery.selectNode('*[id=' + this.btnEl.id + ']');
						tmpElem.style.background = value;
						tmpElem.style.width = "80px";
						tmpElem.style.height= "15px";
					}
					else { // first time btn is not rendered yet
						if (this.type == 'color')
							_renderColor.color = value;
						else
							_renderColor.border = value;
					}
			    },

				getValue:function(){
					var tmpElem = Ext.DomQuery.selectNode('*[id=' + this.btnEl.id + ']');
					if (tmpElem.style.background.search('transparent') != -1)
						return 'none';

					var color = tmpElem.style.backgroundColor;
					return color.charAt(0) == '#' ? color : rgbToHex(color);
				},

				isValid:function(){
					return true;
				}

			});


		   var colorEditor = new Ext.ux.MySplitButton({
				minWidth: 100,
				type:'color',
				menu: new Ext.menu.Menu({
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					items: [
						new Ext.ColorPalette({
							colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
							allowReselect:true,
							listeners: {
								select: function(colorP, colorStr){
									var fillColor = '#' + colorStr;
									colorEditor.setValue(fillColor);
									colorEditor.menu.hide();
								}
							}
						})
					],
					listeners:{
						beforeshow:function(){
							var color = colorEditor.getValue().replace('#', '').toUpperCase();
							if (this.items.items[0].colors.join(',').indexOf(color)>0)
								this.items.items[0].select(color);
						}
					}
				}),
				listeners:{ //button listeners
					render:function(btn){
						if (this.btnEl){
							var tmpElem = Ext.DomQuery.selectNode('*[id=' + this.btnEl.id + ']');
							tmpElem.style.background = _renderColor.color;;
							tmpElem.style.width = "80px";
							tmpElem.style.height= "15px";
						}
					}
				}
			});




		    var borderEditor = new Ext.ux.MySplitButton({
				minWidth: 100,
				type:'border',
				menu: new Ext.menu.Menu({
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					iconCls: 'no-icon',
					handler: Jedox.wss.app.onColorSelect,
					items: [{
						text: 'No Color'.localize(),
						id: 'bgNoColor',
						handler:onNoColorSelect
					},
						new Ext.ColorPalette({
							colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
							allowReselect:true,
							listeners: {
								select: function(colorP, colorStr){
									var fillColor = '#' + colorStr;
									borderEditor.setValue(fillColor);
									borderEditor.menu.hide();
								}
							}
						})
					],
					listeners:{
						beforeshow:function(){
							var color = borderEditor.getValue().replace('#', '').toUpperCase();
							if (this.items.items[1].colors.join(',').indexOf(color)>0)
								this.items.items[1].select(color);
						}
					}
				}),
				listeners:{
					render:function(btn){
						if (this.btnEl){
							var tmpElem = Ext.DomQuery.selectNode('*[id=' + this.btnEl.id + ']');
							tmpElem.style.background = _renderColor.border;
							tmpElem.style.width = "80px";
							tmpElem.style.height= "15px";
						}
					}
				}
			});



		    var editor = new Ext.ux.grid.RowEditor({
		        saveText: 'Update'.localize()
		    });


			var columns = [{
		        header: 'Name'.localize(),
		        dataIndex: 'name',
		        width: 150,
		        sortable: true
		//            editor: {
		//                xtype: 'textfield',
		//                allowBlank: false
		//            }
		    },{
		        header: 'Color'.localize(),
		        dataIndex: 'color',
		        width: 120,
		        sortable: false,
		        editor: colorEditor,
				renderer:function(c,f,g){

					var id = Ext.id();

					return '<div id="' + id + '" style="position: relative; background:'+ g.data.color +';">'+
						'<div style="display: block; width:50px; margin-left: 20px;">' + ' &nbsp ' + '</div></div>'

				}
		    },{
		        header: 'Border'.localize(),
		        dataIndex: 'border',
		        width: 120,
		        sortable: false,
		        editor: borderEditor,
				renderer:function(c,f,g){

					var id = Ext.id();

					var cellValue = g.data.border == 'none'? 'No border'.localize():'&nbsp';//g.data.border;

					return '<div id="' + id + '" style="position: relative; background:'+ g.data.border +';">'+
						'<div style="display: block; width:50px; margin-left: 20px;">' + cellValue + '</div></div>'

				}
		    }];


		   var grid = new Ext.grid.GridPanel({
			   //id:'series-grid',
			   //tabIndex: 51,
		        store: seriesStore,
		        width: 400,
		        margins: '0 5 5 5',
		        plugins: [editor],
				columns:columns,
				viewConfig: {
					forceFit: true,
					sortAscText: 'Sort Ascending'.localize(),
					sortDescText: 'Sort Descending'.localize(),
					columnsText: 'Columns'.localize(),
					groupByText: 'Group by'.localize()
				}
		    });


			var gridPanel = new Ext.Panel({
				border:false,
		        layout: 'fit',
		        width:425,
		        height: 240,
		        items: [grid]
		    });


			function rgbToHex(colorStr){
				var str = colorStr.replace(/rgb\(|\)/g, "").split(",");
				str[0] = parseInt(str[0], 10).toString(16).toLowerCase();
				str[1] = parseInt(str[1], 10).toString(16).toLowerCase();
				str[2] = parseInt(str[2], 10).toString(16).toLowerCase();
				str[0] = (str[0].length == 1) ? '0' + str[0] : str[0];
				str[1] = (str[1].length == 1) ? '0' + str[1] : str[1];
				str[2] = (str[2].length == 1) ? '0' + str[2] : str[2];
				return ('#' + str.join(""));
			}

			function onNoColorSelect(){
				borderEditor.setValue('none');
			}



			var seriesOptionsPanel = {
				title: 'General'.localize(),
				layout: 'form',
				labelWidth:60,
				baseCls: 'x-plain',
				items: [
					BRLbl,
					seriesOptionsLbl,
					BRLbl,
					paletteCmb,
					BRLbl,
					gridPanel
				]
			}

			function setPalette(pKey){

				if (pKey == 'custom'){
					if (_customPalette){
						for (var i= 0; i<_customPalette['color'].length; i++){
							_seriesData[i][1] = _customPalette['color'][i];
							_seriesData[i][2] = _customPalette['border'][i];
						}
						seriesStore.loadData(_seriesData);
					}
					return;
				}

	//			seriesStore.loadData(seriesData[pKey]);
				var palette = _paletteData[pKey];

				for (var i= 0; i<_seriesData.length; i++){
					_seriesData[i][1] = palette[i%32];
					_seriesData[i][2] = 'none';
				}

				seriesStore.loadData(_seriesData);
			}


			function getSeriesOptionsValue(chartTypeIndex){

				var seriesOptionsProps;

				switch (chartTypeIndex){
					case 3:
						if (_pointsFlag)
							 seriesOptionsProps = {SeriesCollection:_seriesData};
						else
							_seriesData.unshift(_handsColor);
					default:
						seriesOptionsProps = {SeriesCollection:_seriesData};
						break;
				}

				return seriesOptionsProps;
			}


			function setSeriesOptionsValue(obj, chartTypeIndex){
				_paletteData = obj.Palette;

				_seriesData = obj.SeriesCollection;

				switch (chartTypeIndex){
					case 3:
						if (_pointsFlag)
							 _seriesData = _seriesData[0];
						else
							_handsColor = _seriesData.shift();
						break;
					default:
						break;
				}

				for (var i=0, count=_seriesData.length; i<count; i++){
					_customPalette['color'].push(_seriesData[i][1]);
					_customPalette['border'].push(_seriesData[i][2]);
				}

				seriesStore.loadData(_seriesData);
			}

			function setSeriesOptionsInterface(chartType){

				var noSeriesBorderChartTypes = {
					'xlLine': 1,'xlLineStacked': 1,'xlLineStacked100': 1,'xlLineRotated': 5,'xlLineMarkers': 1,'xlLineMarkersStacked': 1,'xlLineMarkersStacked100': 1, 'xlLineMarkersStacked100': 1, 'xlLineMarkersRotated': 5,
					'xl3DLine': 1, 'xlLineMarkersRotated': 5, 'xlPie': 2, 'xl3DPie': 2, 'xlPieExploded': 2, 'xl3DPieExploded': 2, 'xlDoughnut': 2, 'xlDoughnutExploded': 2,
					'xlMeterOdoFull': 3, 'xlMeterOdoFull100': 3, 'xlMeterOdoHalf': 3, 'xlMeterOdoHalf100': 3, 'xlMeterAngularWide': 3, 'xlMeterLineHorizontal': 3, 'xlMeterLineVertical': 3,
					'xlXYScatterSmooth': 4, 'xlXYScatterSmoothNoMarkers': 4, 'xlXYScatterLines': 4, 'xlXYScatterLinesNoMarkers': 4
				}

				if (chartType in noSeriesBorderChartTypes)
						grid.getColumnModel().setConfig(columns.slice(0, 2), true);

			}


			this.getPanel = function(){
				return seriesOptionsPanel;
			}

			this.getValue = function(chartTypeIndex){
				return getSeriesOptionsValue(chartTypeIndex);
			}

			this.setValue = function(obj, chartTypeIndex){
				setSeriesOptionsValue(obj, chartTypeIndex);
			}

			this.setLabel = function(label){
				seriesOptionsLbl.setText(label);
			}

			this.setSeriesInterface = function(chartType){
				setSeriesOptionsInterface(chartType);
			}

		}



		/************************************
		  **** Font componenets *****
		************************************/

		var Font = function(type){

			var type = type;
			var _obj;
			var _obj_fontPanel = {};
			var _flags = {preselect:false, setValueCall:false}

			var _default = {Type:'Arial', Size:10, Color:'0x000000', Weight:false, Style:'regular'}

			var fontOptionsLbl = new Ext.form.Label({
				text: 'Font Options'.localize().concat(':'),
				cls: 'edit-chart-title'
			});

			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var TitleTxf = function (label){
				return new Ext.form.TextField({
					fieldLabel: label,
					value: 'Title',
				  	width: 180
				});
			};

			var fontOptionsPanel = new Ext.Panel({
				title: 'Font'.localize(),
				layout: 'form',
				baseCls: 'x-plain',
				items: [
					BRLbl,
					fontOptionsLbl,
					BRLbl
				],
				listeners:{
					render:function(panel){
						setTimeout(function(){
							if (_flags.setValueCall && !_flags.preselect)
								setFontValue(_obj);
								if (_fontLoaded)
									Jedox.wss.dlg.format.font(callBackFnc, _obj_fontPanel, {effects:true, style:type ==='title'? false:true}, true, 70);
								else {
									Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatFont, [callBackFnc, _obj_fontPanel, {effects:true, style:type ==='title'? false:true}, true, 70]);
									_fontLoaded = true;
								}


						});
					}
				}
			});



			var callBackFnc = function (fontPan){
				fontOptionsPanel.add(fontPan);
				fontOptionsPanel.doLayout();
				Ext.getCmp('strikethroughCB').disable();
				Ext.getCmp('underlineCB').disable();
			};


	//		function setFontValue(obj){
	//			fontPreFormatting = {
	//				type: 'Trebuchet MS, sans-serif',
	//				style: 'italic',
	//				size: '14pt',
	//				weight: 'bold',
	//				textDecoration: 'underline overline line-through',
	//				color: 'rgb(0, 0, 255)'
	//			};
	//		}

			function convert(obj){

				var fontProps = {};
				fontProps['Type'] = obj.fontFamily.split(',')[0] || _default.Type;
				fontProps['Size'] = eval(obj.fontSize.replace('pt', '')) || _default.Size;
				fontProps['Color'] = obj.color.replace('#', '0x') || _defautl.Color;
				if (type == 'title'){
					fontProps['Style'] = obj.fontStyle || _default.Style;
	//				fontProps['Decoration'] = obj.textDecoration || _default.Decoration;
					fontProps['Weight'] = obj.fontWeight || _default.Weight;
				}

	//			console.log(fontProps);
				return fontProps;
			}


			function hexToDecCONVERTER(hex){


				function getDec(hex){

					var value;

					if(hex == "A")
					  value = 10;
					else
					if(hex == "B")
					  value = 11;
					else
					if(hex == "C")
					  value = 12;
					else
					if(hex == "D")
					  value = 13;
					else
					if(hex == "E")
					  value = 14;
					else
					if(hex == "F")
					  value = 15;
					else
					  value = eval(hex)

					return value;
				}

				hex = hex.replace('0x', '').toUpperCase();
				var a = getDec(hex.substring(0, 1));
				var b = getDec(hex.substring(1, 2));
				var c = getDec(hex.substring(2, 3));
				var d = getDec(hex.substring(3, 4));
				var e = getDec(hex.substring(4, 5));
				var f = getDec(hex.substring(5, 6));

				var x = (a * 16) + b;
				var y = (c * 16) + d;
				var z = (e * 16) + f;

				return 'rgb('.concat(x, ',', y, ',', z, ')');

			}

			function getFontValue(){

				function getFont(val) {
				        _obj_fontPanel = val;
				}
				if (_flags.preselect) {
					fontOptionsPanel.items.items[fontOptionsPanel.items.items.length-1].fireEvent('doFontSelect', getFont);
					return convert(_obj_fontPanel);
				}
				else {
					return _obj;
				}
			}


	//		function setFontValue(obj){
	//			_flags.setValueCall = true;
	//			if (fontOptionsPanel.rendered) {
	//				_flags.preselect = true;
	//				_obj_fontPanel['type'] = obj.Type;
	//				_obj_fontPanel['color'] = hexToDecCONVERTER(obj.Color);
	//				_obj_fontPanel['size'] = obj.Size + 'pt';
	//				_obj_fontPanel['style'] = obj.Style;
	//				_obj_fontPanel['weight'] = obj.Weight;
	//				_obj_fontPanel['textDecoration'] = obj.Decoration;
	//			}
	//			else {
	//				_obj = obj;
	//			}
	//		}


			function setFontValue(obj){
				_flags.setValueCall = true;
				if (fontOptionsPanel.rendered) {
					_flags.preselect = true;
					_obj_fontPanel['fontFamily'] = obj.Type;
					_obj_fontPanel['color'] = hexToDecCONVERTER(obj.Color);
					_obj_fontPanel['fontSize'] = obj.Size + 'pt';
					_obj_fontPanel['fontStyle'] = obj.Style;
					_obj_fontPanel['fontWeight'] = obj.Weight;
					_obj_fontPanel['textDecoration'] = obj.Decoration;
				}
				else {
					_obj = obj;
				}
			}




			this.getPanel = function(){
				return fontOptionsPanel;
			}

			this.getValue = function(){
				return getFontValue();
			}

			this.setValue = function(obj){
				setFontValue(obj);
			}
		}


		/************************************
		  *** Title options componenets ***
		************************************/

		var TitleOptions = function(label){

			var typesData = {
				title:{titleOptionsLbl: 'Title Options'.localize(), titleTxf: 'Title'.localize(), titleChb:'Title'.localize()},
				legend:{titleOptionsLbl: 'Legend Options'.localize(), titleTxf: 'Legend'.localize(), titleChb:'Legend'.localize()}
			}

			var titleOptionsLbl = new Ext.form.Label({
				text: typesData[label].titleOptionsLbl.localize().concat(':'),
				cls: 'edit-chart-title'
			});


			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};


			var titleTxf = new Ext.form.TextField({
					fieldLabel: typesData[label].titleTxf,
					value: 'Title',
					tabIndex: 60,
				  	width: 180
				});

			var titleChb=new Ext.form.Checkbox({
				fieldLabel: typesData[label].titleChb,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 61,
				checked:true
			});


			var titleOptionsPanel = {
				title: 'General'.localize(),
				layout: 'form',
				baseCls: 'x-plain',
				items: [
					BRLbl,
					titleOptionsLbl,
					BRLbl,
					titleTxf,
					titleChb
				]
			}


			function getTitleOptionsValue(){
				if (label === 'legend')
					return {HasLegend:titleChb.getValue()}
				else
					return {Name:titleTxf.getValue(), HasTitle:titleChb.getValue()}
			}


			function setTitleOptionsValue(obj){
				titleTxf.setValue(obj.Name);
				titleChb.setValue(obj.HasTitle || obj.HasLegend);
			}


			this.getPanel = function(){
				return titleOptionsPanel;
			}

			this.getValue = function(){
				return getTitleOptionsValue();
			}

			this.setValue = function(obj){
				setTitleOptionsValue(obj);
			}

		}



		/************************************
		  *** Legend options componenets ***
		************************************/

		var LegendOptions = function(){

			var _reset = true; //flag to triger events on legendChb check/uncheck

			var legendOptionsLbl = new Ext.form.Label({
				text: 'Legend Options'.localize().concat(':'),
				cls: 'edit-chart-title'
			});


			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};

			var legendChb=new Ext.form.Checkbox({
				boxLabel: 'Show legend'.localize(),
				hideLabel: true,
				tabIndex: 80,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					if (_reset) {
						if (this.getValue()) {
							positionPanel.show();
							rightRb.setValue(true);
							includeInLayoutChb.setValue(true);
						}
						else {
							positionPanel.hide();
						}
					}
				}
			});


			var PositionRB = function (label, toff){
				return new Ext.form.Radio({
					boxLabel: label,
					hideLabel: true,
					name: 'position',
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 80 + toff,
					autoWidth:true,
					inputValue: 1
				});
			}


			var topRb = new PositionRB('Top'.localize(), 1);
			var bottomRb = new PositionRB('Bottom'.localize(), 2);
			var leftRb = new PositionRB('Left'.localize(), 3);
			var rightRb = new PositionRB('Right'.localize(), 4);
			var topRightRb = new PositionRB('Top Right'.localize(), 5);

			var includeInLayoutChb=new Ext.form.Checkbox({
				boxLabel: 'Show the legend without overlapping the chart'.localize(),
				hideLabel: true,
				tabIndex: 90,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				autoWidth:true
			});

			var positionPanel = new Ext.Panel({
				layout:'form',
				baseCls:'x-plain',
				bodyStyle:'padding:10px',
				items:[topRb, bottomRb, leftRb, rightRb, topRightRb, includeInLayoutChb]
			});


			var legendOptionsPanel = {
				title: 'General'.localize(),
				layout: 'form',
				baseCls: 'x-plain',
				items: [
					BRLbl,
					legendOptionsLbl,
					BRLbl,
					legendChb,
					positionPanel
				]
			}

			function setPosition(value){

				switch (value){
					case -4160:
						topRb.setValue(true);
						break;
					case -4107:
						bottomRb.setValue(true);
						break;
					case -4131:
						leftRb.setValue(true);
						break;
					case -4152:
						rightRb.setValue(true);
						break;
					case 2:
						topRightRb.setValue(true);
						break;
					default:
						rightRb.setValue(true);
						break;
				}
			}

			function getPosition(){

				if(topRb.getValue())return -4160;
				if(bottomRb.getValue())return -4107;
				if(leftRb.getValue())return -4131;
				if(rightRb.getValue())return -4152;
				if(topRightRb.getValue())return 2;

				return -4152;
			}

			function getLegendOptionsValue(){
				return {HasLegend:legendChb.getValue(), IncludeInLayout:includeInLayoutChb.getValue(), Position:getPosition()}
			}

			function setLegendOptionsValue(obj){
				_reset = false;
				legendChb.setValue(obj.HasLegend);
				if(obj.HasLegend){
					setPosition(obj.Position);
					includeInLayoutChb.setValue(obj.IncludeInLayout);
				}
				else {
					rightRb.setValue(true);
					includeInLayoutChb.setValue(true);
					positionPanel.hide();
				}
				_reset = true;
			}


			this.getPanel = function(){
				return legendOptionsPanel;
			}

			this.getValue = function(){
				return getLegendOptionsValue();
			}

			this.setValue = function(obj){
				setLegendOptionsValue(obj);
			}

		}



		/************************************
		  **** Axis options componenets ****
		************************************/

		var AxisOptions = function(type){

			var _type = type;
			var _obj;
	//		var _flags = {preselect:false, setValueCall:false}
			var _flags = {hideName:false, hideOptions:false, setValue:false}
			var _showPropsInterfaceflag;
			var _chartTypeIndex;


			var typesData = {
				horizontal:{axisOptionsLbl: 'Horizontal Axis'.localize(), axisTitleTxf: 'Horizontal axis'.localize(), title:'Horizontal Axis'.localize()},
				vertical:{axisOptionsLbl: 'Vertical Axis'.localize(), axisTitleTxf: 'Vertical axis'.localize(), title:'Vertical Axis'.localize()},
				scale:{axisOptionsLbl: 'Scale'.localize(), axisTitleTxf: 'Scale'.localize(), title:'Scale'.localize()}
			}

			var axisOptionsLbl = new Ext.form.Label({
				text:typesData[type].axisOptionsLbl.concat(':'),
				cls: 'edit-chart-title'
			});


			var BRLbl = {
				html:'<br/>',
				baseCls:'x-plain'
			};


			var RadioLbl = function (text){
				return new Ext.form.Label({
					text: text
				});
			}


			var AutoRB = function (name, txf, toff){
				return new Ext.form.Radio({
					boxLabel: 'Auto'.localize(),
					hideLabel: true,
					name: name,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 1 + toff,
					width: 60,
					handler: function(){
						if (this.getValue())
							changeStatus(txf, false);
					},
					inputValue: 1
				});
			}

			var FixedRB = function (name, txf, toff){
				return new Ext.form.Radio({
					boxLabel: 'Fixed'.localize(),
					hideLabel: true,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tabIndex: 2 + toff,
					name: name,
					width: 60,
					handler: function(){
						if (this.getValue())
							changeStatus(txf, true);
					},
					inputValue: 1
				});
			}

			var FixedTxf = function (toff){
				return new Ext.form.TextField({
					hideLabel: true,
					disabled:true,
					tabIndex: 3 + toff,
					width: 80
				});
			}

			var TitleTxf = function (label){
				return new Ext.form.TextField({
					fieldLabel: label,
					tabIndex: 90,
					value: '',
				  	width: 220
				});
			}

			_axis_group++;

			var axisTitleTxf = new TitleTxf(typesData[type].axisTitleTxf);

			var minimumLbl = new RadioLbl('Minimum'.localize().concat(':'));
			var minimumFixedTxf = new FixedTxf(100);
			var minimumAutoRb = new AutoRB('axis-options-minimum' + _axis_group, minimumFixedTxf, 100);
			var minimumFixedRb = new FixedRB('axis-options-minimum' + _axis_group, minimumFixedTxf, 100);
			var maximumLbl = new RadioLbl('Maximum'.localize().concat(':'));
			var maximumFixedTxf = new FixedTxf(105);
			var maximumAutoRb = new AutoRB('axis-options-maximum' + _axis_group, maximumFixedTxf, 105);
			var maximumFixedRb = new FixedRB('axis-options-maximum' + _axis_group, maximumFixedTxf, 105);
			var majorUnitLbl = new RadioLbl('Major Unit'.localize().concat(':'));
			var majorUnitFixedTxf = new FixedTxf(110);
			var majorUnitAutoRb = new AutoRB('axis-options-major-unit' + _axis_group, majorUnitFixedTxf, 110);
			var majorUnitFixedRb = new FixedRB('axis-options-major-unit' + _axis_group, majorUnitFixedTxf, 110);
			var minorUnitLbl = new RadioLbl('Minor Unit'.localize().concat(':'));
			var minorUnitFixedTxf = new FixedTxf(115);
			var minorUnitAutoRb = new AutoRB('axis-options-minor-unit' + _axis_group, minorUnitFixedTxf, 115);
			var minorUnitFixedRb = new FixedRB('axis-options-minor-unit' + _axis_group, minorUnitFixedTxf, 115);




			var ColumnPanel = function (cmp1, cmp2, cmp3, cmp4){
				return {
					layout:'column',
					border:false,
					width:350,
					baseCls:'x-plain',
					defaults:{
						border:false,
						height:25,
						baseCls:'x-plain'
					},
					items:[{
						columnWidth: .30,
						items:[cmp1]
					},{
						columnWidth: .20,
						items:[cmp2]
					},{
						columnWidth: .20,
						items:[cmp3]
					},{
						columnWidth: .30,
						items:[cmp4]
					}]
				}
			}

			var namePanelContainer = new Ext.Panel({
				layout:'card',
				baseCls:'x-plain',
				activeItem:1,
				items:[
					{html:' ', baseCls:'x-plain'},
					{layout:'form', baseCls:'x-plain', items:axisTitleTxf}
				]
			});

			var optionsPanel = {
				layout:'form',
				baseCls:'x-plain',
				items:[
					new ColumnPanel(minimumLbl, minimumAutoRb, minimumFixedRb, minimumFixedTxf),
					new ColumnPanel(maximumLbl, maximumAutoRb, maximumFixedRb, maximumFixedTxf),
					new ColumnPanel(majorUnitLbl, majorUnitAutoRb, majorUnitFixedRb, majorUnitFixedTxf),
					new ColumnPanel(minorUnitLbl, minorUnitAutoRb, minorUnitFixedRb, minorUnitFixedTxf)
				]
			}


			var optionsPanelContainer = new Ext.Panel({
				layout:'card',
				baseCls:'x-plain',
				activeItem:1,
				items:[
					{html:' ', baseCls:'x-plain'},
					optionsPanel
				]
			});


	//----------------------

			var alignmentOptionsLbl = new Ext.form.Label({
				text: 'Alignment'.localize().concat(':'),
				cls: 'edit-chart-title'
			});



			var txtDirectionStore = new Ext.data.SimpleStore({
				fields: [
					{name: 'id', type: 'string'},
					{name: 'img_src',type: 'string'},
					{name: 'text',type: 'string'}
				],
				data:[
					['horizontal', 'text_horizontal', 'Horizontal'.localize()],
					['rotateLeft', 'text_rotate_left', 'Rotate all text 90'.localize()],
					['rotateRight', 'text_rotate_right', 'Rotate all text 270'.localize()]
				]
			});


		    var cmbTpl = new Ext.XTemplate(
				'<div class="chart-axis-text-direction"><tpl for=".">', '<div class="thumb-wrap">',
				'<div class="thumb" style="padding: 0px; text-align: left;"><div style="width: 45px; height: 35px; display: inline;"><img class="{img_src}" src="../lib/ext/resources/images/default/s.gif" width="45" height="35"></div>',
				'<div style="display: inline; position: absolute; padding-top: 10px;">&nbsp;{text}</div></div></div>', '</tpl></div>'
		    );


		    var textDirectionCmb = new Ext.form.ComboBox({
		        store: txtDirectionStore,
				fieldLabel:'Data labels orientation'.localize(),
		        displayField:'text',
		        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		        tabIndex: 120,
		        typeAhead: false,
				triggerAction: 'all',
				mode: 'local',
		        tpl: cmbTpl,
				width: 180,
				value:'horizontal',
		        itemSelector: 'div.thumb-wrap',
		        onSelect: function(record, index){ // override default onSelect to do redirect
			        if(this.fireEvent('beforeselect', this, record, index) !== false){
			            this.setValue(record.data[this.valueField || this.displayField]);
			            this.collapse();
			            this.fireEvent('select', this, record, index);

						switch(index){
							case 0:
								customAngleSpn.setValue(0)
								customAngleSpn.enable();
								break;
							case 1:
								customAngleSpn.setValue(90)
								customAngleSpn.disable();
								break;
							case 2:
								customAngleSpn.setValue(-90)
								customAngleSpn.disable();
								break;
						}
			        }
		    	}
		    });

			var customAngleSpn = new Ext.ux.form.SpinnerField({
		        minValue: -90,
		        maxValue: 90,
		        allowBlank: false,
		        fieldLabel: 'Custom angle',
		        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		        tabIndex: 121,
		        width:60,
		        border: false,
		        value: 0,
		        incrementValue: 1
		    });


			var alignmentOptionsPanel = {
				layout: 'form',
				labelWidth:140,
				baseCls: 'x-plain',
				items: [
					textDirectionCmb,
					customAngleSpn
				]
			}



	//------------------------






			var axisPanel = new Ext.Panel({
				title:typesData[type].title,
				layout:'form',
				baseCls:'x-plain',
				items:[
					BRLbl,
					axisOptionsLbl,
					BRLbl,
					namePanelContainer,
					BRLbl,
					optionsPanelContainer,
					BRLbl,
					alignmentOptionsPanel
				],
				listeners:{
					render:function(panel){
						setTimeout(function(){
							if (_flags.hideName)
								hideName();
							if (_flags.hideOptions)
								hideOptions();
							if (_flags.setValue)
								setAxisOptionsValue(_obj, _chartTypeIndex);
						});
					}
				}

			});


			function changeStatus(txf, status){
				status ? txf.enable() : txf.disable();
			}


			function getAxisOptionsValue(){

				if (axisPanel.rendered)
					return {
							Name: _flags.hideName? null:axisTitleTxf.getValue(),
							MinimumScaleIsAuto: _flags.hideOptions? null:minimumAutoRb.getValue(),
							MaximumScaleIsAuto: _flags.hideOptions? null:maximumAutoRb.getValue(),
							MinimumScale: _flags.hideOptions? null:minimumFixedTxf.getValue(),
							MaximumScale: _flags.hideOptions? null:maximumFixedTxf.getValue(),
							MajorUnitIsAuto: _flags.hideOptions? null:majorUnitAutoRb.getValue(),
							MinorUnitIsAuto: _flags.hideOptions? null:minorUnitAutoRb.getValue(),
							MajorUnit: _flags.hideOptions? null:majorUnitFixedTxf.getValue(),
							MinorUnit: _flags.hideOptions? null:minorUnitFixedTxf.getValue(),
							Orientation:customAngleSpn.getValue()
					}
				return _obj;

			}


			function setAxisOptionsValue(obj, chartTypeIndex){

				if (axisPanel.rendered) {

					axisTitleTxf.setValue(obj.Name);

					customAngleSpn.setValue(getAngle(obj.Orientation));

					if (obj.MinimumScaleIsAuto)
						minimumAutoRb.setValue(obj.MinimumScaleIsAuto);
					else {
						minimumFixedRb.setValue(!obj.MinimumScaleIsAuto);
						minimumFixedTxf.setValue(obj.MinimumScale);
					}

					if (obj.MaximumScaleIsAuto)
						maximumAutoRb.setValue(obj.MaximumScaleIsAuto);
					else {
						maximumFixedRb.setValue(!obj.MaximumScaleIsAuto);
						maximumFixedTxf.setValue(obj.MaximumScale);
					}

					if (obj.MajorUnitIsAuto)
						majorUnitAutoRb.setValue(obj.MajorUnitIsAuto);
					else {
						majorUnitFixedRb.setValue(!obj.MajorUnitIsAuto);
						majorUnitFixedTxf.setValue(obj.MajorUnit);
					}

					if (obj.MinorUnitIsAuto)
						minorUnitAutoRb.setValue(obj.MinorUnitIsAuto);
					else {
						minorUnitFixedRb.setValue(!obj.MinorUnitIsAuto);
						minorUnitFixedTxf.setValue(obj.MinorUnit);
					}
				}

				else {
					_flags.setValue = true;
					_obj = obj;
					_chartTypeIndex = chartTypeIndex;
				}
			}

			function getAngle(value){
				var angle = value;

				switch(value){
					case -4105:
					case -4128:
						angle = 0;
						break;
					case -4170:
						angle = 90;
						break;
					case -4166:
						angle = -90;
						break;
				}

				return angle;
			}


			function setDefault(){
				minimumAutoRb.setValue(true);
				maximumAutoRb.setValue(true);
				majorUnitAutoRb.setValue(true);
				minorUnitAutoRb.setValue(true);
			}

			function hideName(){
				if (axisPanel.rendered)
					namePanelContainer.getLayout().setActiveItem(0);
				else
					_flags.hideName = true;
			}

			function hideOptions(){
				if (axisPanel.rendered)
					optionsPanelContainer.getLayout().setActiveItem(0);
				else
					_flags.hideOptions = true;
			}


			this.getPanel = function(){
				return axisPanel;
			}

			this.getValue = function(){
				return getAxisOptionsValue();
			}

			this.setValue = function(obj, chartTypeIndex){
				setAxisOptionsValue(obj, chartTypeIndex);
			}

			this.hideAxisName = function(){
				hideName();
			}

			this.hideAxisScale = function(){
				hideOptions();
			}

			this.setLabel = function(label){
				axisOptionsLbl.setText(label);
				axisPanel.setTitle(label);
			}

		}


		var ChartArea = function(){

			var fillPanel = new Fill('chartArea');
			var borderPanel = new Border('chartArea');

			var chartArea = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[fillPanel.getPanel(), borderPanel.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});

			this.addSizePosPan = function(t,d){
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
					chartArea.add(np);
					if (t && d) panel.setChartData(t, d);
				};

				//conf.type, conf
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.FESizePositionPanel, [getSizePosPan, 'Chart', false]);
			}

			if (mode != 'edit') this.addSizePosPan();


			function getChartAreaValue(){
				var chartAreaProps = {Fill:fillPanel.getValue(), Border:borderPanel.getValue()}
				return chartAreaProps;
			}

			function setChartAreaValue(obj){
				fillPanel.setValue(obj.Fill);
				borderPanel.setValue(obj.Border);
			}


			this.getPanel = function(){
				return chartArea;
			}

			this.getValue = function(){
				return getChartAreaValue();
			}

			this.setValue = function(obj){
				setChartAreaValue(obj);
			}
		}



		var PlotArea = function(){

			var fillPanel = new Fill('plotArea');
			var borderPanel = new Border('plotArea');

			var plotArea = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[fillPanel.getPanel(), borderPanel.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});


			function getPlotAreaValue(){
				var plotAreaProps = {Fill:fillPanel.getValue(), Border:borderPanel.getValue()}
				return plotAreaProps;
			}

			function setPlotAreaValue(obj){
				fillPanel.setValue(obj.Fill);
				borderPanel.setValue(obj.Border)
			}

			this.getPanel = function(){
				return plotArea;
			}

			this.getValue = function(){
				return getPlotAreaValue();
			}

			this.setValue = function(obj){
				setPlotAreaValue(obj);
			}
		}




		var Title = function(){

			var titleOptions = new TitleOptions('title');
			var font = new Font('title');

			var title = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[titleOptions.getPanel(), font.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});


			function getTitleValue(chartTypeIndex){

				var titleProps;

				switch (chartTypeIndex){
					case 2:
						titleProps = null;
						break;
					default:
						titleProps = {General:titleOptions.getValue(), Font:font.getValue()}
						break;
				}

				return titleProps;
			}

			function setTitleValue(obj){
				titleOptions.setValue(obj.General);
				font.setValue(obj.Font);
			}

			this.getPanel = function(){
				return title;
			}

			this.getValue = function(chartTypeIndex){
				return getTitleValue(chartTypeIndex);
			}

			this.setValue = function(obj){
				setTitleValue(obj);
			}
		}


		var Series = function(pointsFlag){

			var seriesOptions = new SeriesOptions(pointsFlag);

			var series = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[seriesOptions.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});


			function getSeriesValue(chartTypeIndex){
				var seriesProps = {General:seriesOptions.getValue(chartTypeIndex)}
				return seriesProps;
			}

			function setSeriesValue(obj, chartTypeIndex){
				seriesOptions.setValue(obj.General, chartTypeIndex);
			}

			this.getPanel = function(){
				return series;
			}

			this.getValue = function(chartTypeIndex){
				return getSeriesValue(chartTypeIndex);
			}

			this.setValue = function(obj, chartTypeIndex){
				setSeriesValue(obj, chartTypeIndex);
			}

			this.getSeriesOptions = function(){
				return seriesOptions;
			}

		}

		var Legend = function(){

			var legendOptions = new LegendOptions();
			var font = new Font('legend');
			var fillPanel = new Fill('legend');
			var borderPanel = new Border('legend');

			var legend = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[legendOptions.getPanel(), font.getPanel(), fillPanel.getPanel(), borderPanel.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});


			function getLegendValue(chartTypeIndex){

				var legendProps;

				switch (chartTypeIndex){
					case 2:
					case 3:
						legendProps = null;
						break;
					default:
						legendProps = {General:legendOptions.getValue(), Font:font.getValue(), Fill:fillPanel.getValue(), Border:borderPanel.getValue()};
						break;
				}

				return legendProps;
			}

			function setLegendValue(obj){
				legendOptions.setValue(obj.General);
				fillPanel.setValue(obj.Fill);
				borderPanel.setValue(obj.Border);
				font.setValue(obj.Font);
			}


			this.getPanel = function(){
				return legend;
			}

			this.getValue = function(chartTypeIndex){
				return getLegendValue(chartTypeIndex);
			}

			this.setValue = function(obj){
				setLegendValue(obj);
			}
		}



		var Axes = function(){

			var horizontalAxisOptions = new AxisOptions('horizontal');
			var verticalAxisOptions = new AxisOptions('vertical');
			var font = new Font('axis');

			var _cmp;
			var _no = -1;
			var _operationStack = [];

			var axes = new Ext.TabPanel({
				height: 370,
				width:345,
				layoutOnTabChange: true,
				baseCls:'edit-chart-tab-panel',
				defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
				activeTab: 0,
				items:[horizontalAxisOptions.getPanel(), verticalAxisOptions.getPanel(), font.getPanel()],
				listeners: {
					tabChange: function(pan, tab){
						that.containers.activePanel = tab;
					}
				}
			});



			function getAxesValue(chartTypeIndex){

				var axesProps;

				switch (chartTypeIndex){
					case 2:
						axesProps = {HorizontalAxis:horizontalAxisOptions.getValue(), Font:font.getValue()}
						break;
					case 5:
						axesProps = {HorizontalAxis:verticalAxisOptions.getValue(), VerticalAxis:horizontalAxisOptions.getValue(), Font:font.getValue()}
	//					axesProps = {HorizontalAxis:horizontalAxisOptions.getValue(), VerticalAxis:verticalAxisOptions.getValue(), Font:font.getValue()}
						break;
					default:
						axesProps = {HorizontalAxis:horizontalAxisOptions.getValue(), VerticalAxis:verticalAxisOptions.getValue(), Font:font.getValue()}
						break;
				}

				return axesProps;
			}

			function setAxesValue(obj, chartTypeIndex){


				switch (chartTypeIndex){
					case 5:
						horizontalAxisOptions.setValue(obj.VerticalAxis, chartTypeIndex);
						verticalAxisOptions.setValue(obj.HorizontalAxis, chartTypeIndex);
						break;
					default:
						horizontalAxisOptions.setValue(obj.HorizontalAxis, chartTypeIndex);
						verticalAxisOptions.setValue(obj.VerticalAxis, chartTypeIndex);
						break;
				}

				font.setValue(obj.Font);
			}


			this.getPanel = function(){
				return axes;
			}

			this.getValue = function(chartTypeIndex){
				return getAxesValue(chartTypeIndex);
			}

			this.setValue = function(obj, chartTypeIndex){
				setAxesValue(obj, chartTypeIndex);
			}

			this.getHorizontalAxis = function(){
				return horizontalAxisOptions;
			}

			this.getVerticalAxis = function(){
				return verticalAxisOptions;
			}

			this.removeVerticalAxis = function(){
				axes.remove(1);
			}

			this.removeHorizontalAxis = function(){
				axes.remove(0);
			}

			this.removeFont = function(){
				axes.remove(2);
			}


		}





		/************************************
		  **** Main componenets *****
		************************************/

		var _fontLoaded = false

		var typeData = [
			['Chart Area'.localize(), 'chart_area_icon', 0],
			['Plot Area'.localize(), 'plot_area_icon', 1],
			['Points'.localize(), 'points_options_icon', 2],
			['Series'.localize(), 'series_options_icon', 3],
			['Title'.localize(), 'title_icon', 4],
			['Legend'.localize(), 'legend_icon', 5],
			['Axes'.localize(), 'axis_icon', 6]
		]


		var typeNavigationStore = new Ext.data.SimpleStore({
			fields: ['label', 'icon', 'pindex'],
			data: typeData
		});



		var typeNavigationView = new Ext.DataView({
			id: 'chart-type-navigation',
			store: typeNavigationStore,
			tpl: new Ext.XTemplate(
					'<div class="chart-type-navigation" style="width: 99%;"><div class="charttypes">','Type'.localize(),'</div><tpl for=".">',
					'<div class="thumb-wrap">',
					'<div class="thumb"><img class="{icon}" src="../lib/ext/resources/images/default/s.gif" width="29" height="27" />&nbsp;&nbsp;&nbsp;{label}</div></div>',
					'</tpl></div>'),
			multiSelect: false,
			singleSelect: true,
			overClass: 'x-view-over',
			itemSelector: 'div.thumb-wrap',
			listeners: {
				containerclick: function (dView, e){
					e.stopEvent();
					return false;
				},
				click: function(dataView, index, node, e){
					setNavigationView(this.store.getAt(index).get('pindex'));
					if (index != 0){
						Jedox.wss.app.currentDialogControl = null; //dataView.getId();
						Jedox.wss.app.currentDialogControlItemsCnt = 0; //dataView.getStore().getCount();
					}
				}
			}
		});


		function setNavigationView(index){
			mainPanel.items.items[1].layout.setActiveItem(index);
			that.containers.activePanel = mainPanel.items.items[1].layout.activeItem.activeTab;
		}

		var typeNavigationPanel = {
			layout:'fit',
			width:130,
			height: 380,
			border:true,
			items:typeNavigationView
		}



		var chartArea = new ChartArea();
		var plotArea = new PlotArea();
		var points = new Series(true); //flag that series are points (needed for Odo charts)
		var series = new Series(false);
		var title = new Title();
		var legend = new Legend();
		var axes = new Axes();



		var mainPanel=new Ext.Panel({
			layout: 'absolute',
			baseCls: 'x-plain',
			border: false,
			items:[{
				//title: 'navigation panel',
				layout: 'column',
				border: false,
				baseCls: 'x-plain',
				x: 0,
				y: 0,
				items: [typeNavigationPanel]
			},
			{
				//title: 'view panel',
				layout: 'card',
				baseCls: 'x-plain',
				border:false,
				width: 450,
				height: 380,
				activeItem:0,
				x: 140,
				y: 0,
				items: [chartArea.getPanel(), plotArea.getPanel(), points.getPanel(), series.getPanel(), title.getPanel(), legend.getPanel(), axes.getPanel()]
			}]
		});

		var okBtn = (this.components.OK = new Ext.Button({
			text: 'OK'.localize(),
			tabIndex: 1001,
			handler: function(){
				doEditChart();
				//that.win.close();
			}
		}));

		var cancelBtn = (this.components.Cancel = new Ext.Button({
			text: 'Cancel'.localize(),
			tabIndex: 1002,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(){
				that.win.close();
			}
		}));

		//functions

		function switchSolid(panel, index){
			panel.layout.setActiveItem(index);
		}

	/*
	 *
	 * 	var _reg = {
		++	1:{HorizontalAxisScale:true}, //Other
		++	2:{Legend:true, Title:true, Axes:true}, //Pie, Doughnt -- finished
		++	3:{Title:true, Legend:true, HorizontalAxisName:true, VericalAxis:true}, //Meter
		++	4:{} //Bubble, Stock, Radar, Scatter
		++	5:{VerticalAxisScale:true} //Vertical line
		}
	 *
	 */


		function setNavigationInterface(indexToRmv){
			var newTypeData = [];
			for (var i=0, j=0; i<typeData.length; i++){
				if(i in indexToRmv)
					continue;
				newTypeData[j++] = typeData[i];
			}

			typeNavigationStore.loadData(newTypeData);
			typeNavigationView.select(0, false, false);
		}

		function _setInterface(chartType){

			var remove = _chartTypesInterfaceDate[chartType];

				switch(remove){
					case 1://Other horizontalaxisscale
						setNavigationInterface({2:true});
						series.getSeriesOptions().setSeriesInterface(chartType);
						axes.getHorizontalAxis().hideAxisScale();
						break;
					case 2: //Pie, Doughnt
						setNavigationInterface({2:true, 4:true, 5:true});
						typeNavigationView.getStore().getAt(2).set('label', 'Points'.localize());
						typeNavigationView.getStore().getAt(3).set('label', 'Data labels'.localize());
						series.getSeriesOptions().setLabel('Points options'.localize());
						series.getSeriesOptions().setSeriesInterface(chartType);
						axes.getHorizontalAxis().setLabel('Orientation'.localize());
						axes.getHorizontalAxis().hideAxisName();
						axes.getHorizontalAxis().hideAxisScale();
						axes.removeVerticalAxis();
						break;
					case 3: // Meter
						setNavigationInterface({5:true});
						typeNavigationView.getStore().getAt(3).set('label', 'Zones'.localize());
						typeNavigationView.getStore().getAt(5).set('label', 'Scales'.localize());
						points.getSeriesOptions().setLabel('Points options'.localize());
						points.getSeriesOptions().setSeriesInterface(chartType);
						series.getSeriesOptions().setLabel('Zones options'.localize());
						series.getSeriesOptions().setSeriesInterface(chartType);
						axes.getHorizontalAxis().setLabel('Scale'.localize());
						axes.getHorizontalAxis().hideAxisName();
						axes.removeVerticalAxis();
						break;
					case 4:
						setNavigationInterface({2:true});
						series.getSeriesOptions().setSeriesInterface(chartType);
						break;
					case 5://Vertical line
						setNavigationInterface({2:true});
						series.getSeriesOptions().setSeriesInterface(chartType);
						axes.getVerticalAxis().hideAxisScale();
						break;
					case 6: //Radar
						setNavigationInterface({2:true});
						axes.getHorizontalAxis().setLabel('Radial Axis'.localize());
	//					axes.getHorizontalAxis().hideAxisName();
						axes.getHorizontalAxis().hideAxisScale();
						axes.removeFont();
						axes.removeVerticalAxis();
						break;
				}

		}

		function _setValue(chartProps, chartType){

			var chartTypeIndex = _chartTypesInterfaceDate[chartType];

				switch(chartTypeIndex){
					case 1://Other horizontalaxisscale
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						series.setValue(chartProps.Series, chartTypeIndex);
						title.setValue(chartProps.Title);
						legend.setValue(chartProps.Legend);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
					case 2: //Pie, Doughnt
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						series.setValue(chartProps.Series, chartTypeIndex);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
					case 3: // horizontal axis name, and vertical axis
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						points.setValue(chartProps.Series, chartTypeIndex);
						series.setValue(chartProps.Series, chartTypeIndex);
						title.setValue(chartProps.Title);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
					case 4: // Bubble, Stock
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						series.setValue(chartProps.Series, chartTypeIndex);
						title.setValue(chartProps.Title);
						legend.setValue(chartProps.Legend);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
					case 5:// vertical line
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						series.setValue(chartProps.Series, chartTypeIndex);
						title.setValue(chartProps.Title);
						legend.setValue(chartProps.Legend);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
					case 6://radar
						chartArea.setValue(chartProps.ChartArea);
						plotArea.setValue(chartProps.PlotArea);
						series.setValue(chartProps.Series, chartTypeIndex);
						title.setValue(chartProps.Title);
						legend.setValue(chartProps.Legend);
						axes.setValue(chartProps.Axes, chartTypeIndex);
						break;
				}
		}



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
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editChart);
						}
				});
				that.win.close();
				return;
			}


			_setInterface(chartProps.ChartType.General.Type);
			_setValue(chartProps, chartProps.ChartType.General.Type);

			// get chart dimensions and position
			var cObj = Ext.get(Jedox.wss.app.activePane._domId.concat('_wsel_cont_', chartID, '-rzwrap'));

			chartProps.dims = {
					w: cObj.getWidth(),
					h: cObj.getHeight(),
					t: parseInt(cObj.dom.style.top.replace(/px/g, "")),
					l: parseInt(cObj.dom.style.left.replace(/px/g, ""))
			};

			chartArea.addSizePosPan(chartTypesSizeDefs[chartProps.ChartType.General.Type], chartProps.dims);

			_chartProps = chartProps;

			that.win.show(that);
			typeNavigationView.select(0, false, false);
			that.containers.activePanel = mainPanel.items.items[1].layout.activeItem.activeTab;
		}



		var doEditChart = function () {
			var chartProps = collectProperties();

			if (chartProps != false) {
				chartProps.id = chartID;
				// TODO: Show please wait...

				// Position and Resize chart by given properties
				Jedox.wss.wsel.chart.reMovize(chartProps.id, Jedox.wss.wsel.getRngFromNLoc(chartProps.n_location), chartProps.pos_offsets);

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
							'&ts=', currDate.getTime()
						);
				}
			}
		}

		function collectProperties() {
	//		Create chart properties.
			var chartTypeIndex = _chartTypesInterfaceDate[_chartProps.ChartType.General.Type];
			var whRatio = getWHRatio();

			var dims = Ext.getCmp('FE-SE-panel').getSPData() || _chartProps.dims;

			if (!dims){
				Ext.MessageBox.show({
					title: "Error".localize(),
					msg: "invalid_chart_sizepos".localize(),
					buttons: Ext.Msg.OK,
					icon: Ext.MessageBox.ERROR
				});
				return false;
			}

			var elWidth = dims.width || dims.w || 0;
			var elHeight = dims.height || dims.h || 0;
			var elTop = dims.top || dims.t || 0;
			var elLeft = dims.left || dims.l || 0;

			var nLoc = Jedox.wss.wsel.getNLoc(elLeft, elTop, elWidth, elHeight);

			var chartProps = {
				props: {
					ChartType: _chartProps.ChartType,
					ChartArea: chartArea.getValue(),
					PlotArea: plotArea.getValue(),
					SourceData: _chartProps.SourceData,
					Series: series.getValue(chartTypeIndex),
					Title: title.getValue(chartTypeIndex),
					Legend: legend.getValue(chartTypeIndex),
					Axes:axes.getValue(chartTypeIndex),
					General: {
						WH_ratio: whRatio,
						Layout: _chartProps.General.Layout,
						Style: _chartProps.General.Style,
						ActiveSheet: Jedox.wss.app.activeSheetName
					}
				},
				n_location: nLoc.n_location,
				pos_offsets: nLoc.pos_offsets,
				size: [elWidth, elHeight],
				operation: 'format'
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
			//console.log(chartProps);
			that.win.close();
			return chartProps;
		}


		this.win = new Ext.Window({
					id:'edit-chart-dlg',
					title:'Format Chart Properties'.localize(),
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
					width: 605,
					height: 455,
					items: mainPanel,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editChart);
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 100);
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

Jedox.util.extend(Jedox.wss.dlg.chart.EditChart, Jedox.dlg.Dialog);


	/************************************
	  ****  Chart object structure ****
	************************************/
	/*

	Chart:{
		ChartType:{
			General:{
				Type:'value'
			}
		}
		ChartArea:{
			Fill:{
				BackColor:'value'
			},
			Border:{
				Color:'value'
			}
		},
		PlotArea:{
			Fill:{
				NoFill:'value',
				BackColor:'value'
			},
			Border:{
				NoBorder:'value',
				Color:'value'
			}
		},
		SourceData:{
			General:{
				Source:'value',
				GroupBy:'value',
				SeriesLabels:'value',
				CategoryLabels:'value'
			}
		},
		Title:{
			General:{
				HasTitle:'value',
				Name:'value'
			},
			Font:{

			}

		},
		Legend:{
			General:{
				HasLegend:'value',
				Name:'value'
			},
			Font:{

			},
			Fill:{
				BackColor:'value'
			},
			Border:{
				Color:'value'
			}
		},
		Axis:{
			Genaral:{
				HorizotalAxis:'value',
				VerticalAxis:'value',
				MinimumScaleIsAuto:'value',
				MaximumScaleIsAuto:'value',
				MinimumScale:'value',
				MaximumScale:'value',
				MajorUnitiIsAuto:'value',
				MinorUnitIsAuto:'value',
				MajorUnit:'value',
				MinorUnit:'value'
			},
			Font:{

			},
			Fill:{
				BackColor:'value'
			},
			Border:{
				Color:'value'
			}
		}
	}


	*/