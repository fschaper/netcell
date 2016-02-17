/*
 * @brief wss file
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: PageSetup.js 4912 2011-04-29 12:42:42Z mladent $
 *
 */


Jedox.wss.dlg.openPageSetup = function() {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PageSetup());
};

Jedox.wss.dlg.PageSetup = (function() {

	return function () {

		Jedox.wss.dlg.PageSetup.parent.constructor.call(this);
		this.id = 'PageSetup';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var _selectedData;
		var _preselctionChbValues = {'horizontallyChb':false, 'horizontallyChb':false, gridLinesChb:false};
		var _marginsPanelRenderFlag = false;

		//================================ Active containers =====================================

		var activeContainers = {};

		function setContainers(elements){
			// erase all containers, than add appropriate one

			for (var c in activeContainers){
				delete that.containers[c];
			}
			activeContainers = {};

			for (var nc in elements){
				that.containers[nc] = elements[nc];
				activeContainers[nc] = nc;
			}

		};

		//================================ Components ============================================

		var portraitRb = this.cmpFocus = new Ext.form.Radio({
			boxLabel: 'Portrait'.localize(),
			hideLabel: true,
			tabIndex: 101,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			name: 'rb-orientation',
			width:100,
			inputValue: 1
		});

		var landscapeRb=new Ext.form.Radio({
			boxLabel: 'Landscape'.localize(),
			hideLabel: true,
			checked: true,
			name: 'rb-orientation',
			width:100,
			tabIndex: 102,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler:centerPic,
			inputValue: 1
		});

		var adjustToRb=new Ext.form.Radio({
			hideLabel: true,
			boxLabel: '',
			tabIndex: 103,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			name: 'rb-scaling',
			style: 'height: 25px;',
			width:20,
			inputValue: 1
		});


		var adjustToSpn = new Ext.ux.form.SpinnerField({
	        name: 'adjust_to',
	        minValue: 0,
	        maxValue: 400,
	        allowBlank: false,
	        //fieldLabel: 'Adjust to',
			hideLabel:true,
			tabIndex: 104,
	        width:60,
	        border: false,
	        value: 100,
	        incrementValue: 5
	    });

		var fitToRb=new Ext.form.Radio({
			hideLabel: true,
			boxLabel: '',
	        style: 'height: 25px;',
			name: 'rb-scaling',
			tabIndex: 105,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			checked: true,
			width:20,
			inputValue: 1
		});


		var pageWideSpn = new Ext.ux.form.SpinnerField({
	        minValue: 1,
	        maxValue: 400,
	        name: 'adjust_to',
	        allowBlank: false,
	       // fieldLabel: 'Adjust to',
			hideLabel:true,
	        width:60,
	        tabIndex: 106,
	        border: false,
	        value: 1,
	        incrementValue: 5
	    });

		var pageTallSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 400,
	        name: 'adjust_to',
	        allowBlank: true,
	        //fieldLabel: 'Adjust to',
			hideLabel:true,
			tabIndex: 107,
	        width:60,
	        border: false,
	        value: 1,
	        incrementValue: 5
	    });


		var paperSizeCmb=new Ext.form.ComboBox({
			fieldLabel: 'Paper size'.localize(),
			width: 300,
			tabIndex: 108,
			store:new Ext.data.SimpleStore({
				data:[[0,'A4'],[1,'Letter'.localize()]],
				fields:[{name:'paperSizeID'}, {name:'paperSizeName'}]
			}),
			displayField:'paperSizeName',
			value:'A4',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			editable:false,
			mode: 'local',
		    triggerAction: 'all'
		});
	/*
		var printQualityCmb=new Ext.form.ComboBox({
			fieldLabel: 'Print quality'.localize(),
			width: 300,
			store:new Ext.data.SimpleStore({
				data:[[0,'100 dpi'],[1,'200 dpi'],[2,'300 dpi']],
				fields:[{name:'printQualityID'}, {name:'printQualityName'}]
			}),
			displayField:'printQualityName',
			editable:false,
			mode: 'local',
		    triggerAction: 'all'
		});
	*/

		var firstPageNumberTxf = new Ext.form.TextField({
			fieldLabel: 'First page'.localize(),
			name: 'userName',
			tabIndex: 109,
			value:'Auto',
			allowBlank: false,
			width: 100
		});

		//================================ Margins Components ============================================


		var topMarginSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 100,
	        name: 'top',
	        allowBlank: false,
	        tabIndex: 201,
			hideLabel:true,
	        width:60,
	        border: false,
	        value: 0.75,
	        incrementValue: 0.25,
	        listeners: {
	       	spin : function() {
						changePic(1);
						pageMarginsDV.select(2, false, false);
						}
		}
	    });


		var headerMarginSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 100,
	        name: 'header',
	        allowBlank: false,
			hideLabel:true,
			tabIndex: 202,
	        width:60,
	        border: false,
	        value: 0.3,
	        incrementValue: 0.25,
	        listeners: {
	       	spin : function() {
						changePic(2);
						pageMarginsDV.select(2, false, false);
						}
		}
	    });


		var leftMarginSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 100,
	        name: 'left',
	        allowBlank: false,
			hideLabel:true,
			tabIndex: 203,
	        width:60,
	        border: false,
	        value: 0.7,
	        incrementValue: 0.25,
	        listeners: {
			spin : function() {
		   				changePic(3);
						pageMarginsDV.select(2, false, false);
						}
		}
	    });


		var rightMarginSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 100,
	        name: 'right',
	        allowBlank: false,
	        hideLabel:true,
	        tabIndex: 204,
	        width:60,
	        border: false,
	        value: 0.7,
	        incrementValue: 0.25,
	        listeners: {
	       	spin : function() {
						changePic(4);
						pageMarginsDV.select(2, false, false);
						}
		}
	    });


		var bottomMarginSpn = new Ext.ux.form.SpinnerField({
	        minValue: 0,
	        maxValue: 100,
	        name: 'bottom',
	        allowBlank: false,
			hideLabel:true,
	        width:60,
	        tabIndex: 205,
	        border: false,
	        value: 0.75,
	        incrementValue: 0.25,
	        listeners: {
	       	spin : function() {
						changePic(5);
						pageMarginsDV.select(2, false, false);
						}
		}
	    });

		var footerMarginSpn = new Ext.ux.form.SpinnerField({
	        name: 'footer',
	        minValue: 0,
	        maxValue: 100,
	        allowBlank: false,
			hideLabel:true,
			tabIndex: 206,
	        width:60,
	        border: false,
	        value: 0.3,
	        incrementValue: 0.25,
	        listeners: {
	       	spin : function() {
						changePic(6);
						}
		}
	    });


		var horizontallyChb=new Ext.form.Checkbox({
			boxLabel: 'Horizontally'.localize(),
			hideLabel:true,
			//name: 'rb-order',
			tabIndex: 207,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler:centerPic,
			inputValue: 8
		});

		var verticallyChb=new Ext.form.Checkbox({
			boxLabel: 'Vertically'.localize(),
			hideLabel:true,
			//name: 'rb-order',
			handler:centerPic,
			tabIndex: 208,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			inputValue: 8
		})


		function centerPic () {

			if (!_marginsPanelRenderFlag)
				return;

			var record = pageMardinsStore.getAt(0);
			var hor=horizontallyChb.checked;
			var ver=verticallyChb.checked;
			var ls=landscapeRb.checked;

			if (ls) {
				pageMarginsDV.tpl = pageMarginsTemplateH;
				if (ver && hor)
					_selectedData = centerHorVerMardinsLSData
				else if (hor)
					_selectedData = centerHorMardinsLSData;
				else if (ver)
					_selectedData = centerVerMardinsLSData;
				else _selectedData = pageMardinsLSData;
			}

			else {
				pageMarginsDV.tpl = pageMarginsTemplateV;
				if (ver && hor)
					_selectedData = centerHorVerMardinsData
				else if (hor)
					_selectedData = centerHorMardinsData;
				else if (ver)
					_selectedData = centerVerMardinsData;
				else
					_selectedData = pageMardinsData;
			}

			changePic(0);
			pageMarginsDV.refresh();
		}


		function changePic(selectedIndex){
			var record = pageMardinsStore.getAt(0);
			record.set('pic', _selectedData[selectedIndex][1]);
		}

		//PORTRAIT icons
		var pageMardinsData=[
			['start', 'page_margins'],
		    ['top', 'page_margins_top'],
		    ['header', 'page_margins_header'],
		    ['left', 'page_margins_left'],
			['rignt', 'page_margins_right'],
			['bottom', 'page_margins_bottom'],
			['footer', 'page_margins_footer']
		]

		_selectedData = pageMardinsData;

		var centerHorMardinsData=[
			['center_horizontally', 'center_horizontally'],
			['center_horizontally_top', 'center_horizontally_top'],
			['center_horizontally_header', 'center_horizontally_header'],
			['center_horizontally_left', 'center_horizontally_left'],
			['center_horizontally_right', 'center_horizontally_right'],
			['center_horizontally_bottom', 'center_horizontally_bottom'],
			['center_horizontally_footer', 'center_horizontally_footer']
		]

		var centerVerMardinsData=[
			['center_vertically', 'center_vertically'],
			['center_vertically_top', 'center_vertically_top'],
			['center_vertically_header', 'center_vertically_header'],
			['center_vertically_left', 'center_vertically_left'],
			['center_vertically_right', 'center_vertically_right'],
			['center_vertically_bottom', 'center_vertically_bottom'],
			['center_vertically_footer', 'center_vertically_footer']
		]

		var centerHorVerMardinsData=[
			['center_hor_ver', 'center_hor_ver'],
			['center_hor_ver_header', 'center_hor_ver_header'],
			['center_hor_ver_top', 'center_hor_ver_top'],
			['center_hor_ver_left', 'center_hor_ver_left'],
			['center_hor_ver_right', 'center_hor_ver_right'],
			['center_hor_ver_bottom', 'center_hor_ver_bottom'],
			['center_hor_ver_footer', 'center_hor_ver_footer']
		]

		//LANDSCAPE icons
		var pageMardinsLSData=[
			['start', 'page_margins_ls'],
		    ['top_ls', 'page_margins_top_ls'],
		    ['header_ls', 'page_margins_header_ls'],
		    ['left_ls', 'page_margins_left_ls'],
			['rignt_ls', 'page_margins_right_ls'],
			['bottom_ls', 'page_margins_bottom_ls'],
			['footer_ls', 'page_margins_footer_ls']
		]


		var centerHorMardinsLSData=[
			['center_horizontally_ls', 'center_horizontally_ls'],
			['center_horizontally_top_ls', 'center_horizontally_top_ls'],
			['center_horizontally_header_ls', 'center_horizontally_header_ls'],
			['center_horizontally_left_ls', 'center_horizontally_left_ls'],
			['center_horizontally_right_ls', 'center_horizontally_right_ls'],
			['center_horizontally_bottom_ls', 'center_horizontally_bottom_ls'],
			['center_horizontally_footer_ls', 'center_horizontally_footer_ls']
		]

		var centerVerMardinsLSData=[
			['center_vertically_ls', 'center_vertically_ls'],
			['center_vertically_top_ls', 'center_vertically_top_ls'],
			['center_vertically_header_ls', 'center_vertically_header_ls'],
			['center_vertically_left_ls', 'center_vertically_left_ls'],
			['center_vertically_right_ls', 'center_vertically_right_ls'],
			['center_vertically_bottom_ls', 'center_vertically_bottom_ls'],
			['center_vertically_footer_ls', 'center_vertically_footer_ls']
		]

		var centerHorVerMardinsLSData=[
			['center_hor_ver_ls', 'center_hor_ver_ls'],
			['center_hor_ver_top_ls', 'center_hor_ver_top_ls'],
			['center_hor_ver_header_ls', 'center_hor_ver_header_ls'],
			['center_hor_ver_left_ls', 'center_hor_ver_left_ls'],
			['center_hor_ver_right_ls', 'center_hor_ver_right_ls'],
			['center_hor_ver_bottom_ls', 'center_hor_ver_bottom_ls'],
			['center_hor_ver_footer_ls', 'center_hor_ver_footer_ls']
		]

		var br=20;
		var pageMardinsStore=new Ext.data.SimpleStore({
	                fields: ['marginName', 'pic'],
					data: [['start', 'page_margins']]
	    });

		var pageMarginsTemplateV = new Ext.XTemplate(
					     '<div><tpl for=".">',
					     '<div class="thumb-wrap">',
					     '<div class="thumb" style="padding: 5px; width:145px; height:145px;  text-align: center; display: table-cell; vertical-align:middle;">',
					     '<img class="{pic}" src="../lib/ext/resources/images/default/s.gif" ', 'width="108" height="142"', ' /></div></div>',
					     '</tpl></div>'
					     );

		var pageMarginsTemplateH = new Ext.XTemplate(
			     '<div><tpl for=".">',
			     '<div class="thumb-wrap">',
			     '<div class="thumb" style="padding: 5px; width:145px; height:145px;  text-align: center; display: table-cell; vertical-align:middle;">',
			     '<img class="{pic}" src="../lib/ext/resources/images/default/s.gif" ', 'width="142" height="108"', ' /></div></div>',
			     '</tpl></div>'
			     );

		var pageMarginsDV = new Ext.DataView({
		     id: 'page-margins-dv',
		     store: pageMardinsStore,
		     tpl: pageMarginsTemplateV,
		     //height: 250,
		     multiSelect: false,
		     singleSelect: true,
		     overClass: 'x-view-over',
		     itemSelector: 'div.thumb-wrap',
		     emptyText: 'No images to display'.localize(),
			 listeners:{
				afterrender:function(){
					horizontallyChb.setValue(_preselctionChbValues['horizontallyChb']);
					verticallyChb.setValue(_preselctionChbValues['verticallyChb']);
					_marginsPanelRenderFlag = true;
					centerPic();
				}
			}
		});



		var pageMarginPanel = {
		    layout:'column',
			border:false,

		    items: [{
				layout:'absolute',
				border:false,
				columnWidth: .3,
				height:255,
				items: [{
					layout:'form',
					border:false,
					width:65,
					x:65,
					y:100,
					items:[
						new Ext.form.Label({
					        text: 'Left'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						leftMarginSpn
					]
				}]
		    },
			{
				layout:'absolute',
				border:false,
				columnWidth: .4,
				height:255,
				items:[
				{
					layout:'form',
					border:false,
					width:65,
					x:62,
					y:0,
					items:[
						new Ext.form.Label({
					        text: 'Top'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						topMarginSpn
					]
				},
				{
					layout:'fit',
					height:155,
					width:155,
					x:15,
					y:50,
					items:[pageMarginsDV]
				},
				{
					layout:'form',
					border:false,
					width:65,
					x:62,
					y:210,
					items:[
						new Ext.form.Label({
					        text: 'Bottom'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						bottomMarginSpn
					]
				}]
			},
			{
				layout:'absolute',
				border:false,
				columnWidth: .3,
				height:255,
				items:[
				{
					layout:'form',
					border:false,
					width:65,
					x:5,
					y:0,
					items:[
						new Ext.form.Label({
					        text: 'Header'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						headerMarginSpn
					]
				},
				{
					layout:'form',
					border:false,
					width:65,
					x:5,
					y:100,
					items:[
						new Ext.form.Label({
					        text: 'Right'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						rightMarginSpn
					]
				},
				{
					layout:'form',
					border:false,
					width:65,
					x:5,
					y:210,
					items:[
						new Ext.form.Label({
					        text: 'Footer'.localize().concat(':'),
					        baseCls: 'x-plain'
					    }),
						footerMarginSpn
					]
				}]
			}]
		};


		var centerOnPageFs=new Ext.form.FieldSet({
			title: 'Orientation'.localize(),
			layout:'form',
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			items: [horizontallyChb, verticallyChb]
		});


		//================================ Header and Footer Components ====================================


		var headerStore = new Ext.data.SimpleStore({
			fields: ['leftStyle','leftValue', 'leftPreview', 'centerStyle', 'centerValue', 'centerPreview', 'rightStyle', 'rightValue', 'rightPreview'],
			data: [['','','', '','','', '','','']]
		});

		var footerStore = new Ext.data.SimpleStore({
			fields: ['leftStyle','leftValue', 'leftPreview', 'centerStyle', 'centerValue', 'centerPreview', 'rightStyle', 'rightValue', 'rightPreview'],
			data: [['','','', '','','', '','','']]
		});


		var headerDV = new Ext.DataView({
		     id: 'header-dv',
			 store:headerStore,
		     tpl: new Ext.XTemplate(
			     '<div class="header"><tpl for=".">',
			     '<div class="thumb-wrap">',
			     '<div class="thumb" style="padding-left: 2px; text-align: left;"><table>',
				 '<tr><td width=145 height=50 align=left valign=top style="{leftStyle}">{leftPreview}</td><td width=145 height=50 align=center valign=top style="{centerStyle}">{centerPreview}</td><td width=140 height=50 align=right valign=top style="{rightStyle}">{rightPreview}</td></tr>',
				 '</table></div></div>',
	             '</tpl></div>'
		     ),
		     //height: 250,
		     multiSelect: false,
		     singleSelect: true,
		     overClass: 'x-view-over',
		     itemSelector: 'div.thumb-wrap',
		     emptyText: 'No images to display'.localize()
		});




		var headerCmb=new Ext.form.ComboBox({
			fieldLabel: 'Header'.localize(),
			width: 450,
			tabIndex: 301,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			store:new Ext.data.SimpleStore({
				data:[['', '', '(none)'.localize()],['font-size:8pt;', 'Page'.localize() + ' &[Page]', 'Page'.localize()+ ' 1'],['font-size:8pt;', 'Page'.localize() + ' &[Page] ' + 'of'.localize() + ' &[Pages]', 'Page'.localize()+ ' 1 ' + 'of'.localize()+ ' ?'], ['font-size:8pt;', '&[Tab]', 'Sheet'.localize()+ ' 1'], ['font-size:8pt;', '&[File]', 'Book'.localize()+ ' 1']],
				fields:[{name:'preDefHStyle'}, {name:'preDefHValue'}, {name:'preDefHPreview'}]
			}),
			value:'(none)'.localize(),
			displayField:'preDefHPreview',
			editable:false,
			mode: 'local',
		    triggerAction: 'all',
			listeners:{
				select:function(cmb, tmpRec, index){
					var record = headerStore.getAt(0);
					setCmbSelection(record, tmpRec, 'preDefH');
				}
			}
		});


		var footerDV = new Ext.DataView({
		     id: 'footer-dv',
		     store:footerStore,
		     tpl: new Ext.XTemplate(
			     '<div class="footer"><tpl for=".">',
			     '<div class="thumb-wrap">',
			     '<div class="thumb" style="padding-bottom: 2px; text-align: left;"><table>',
				 '<tr><td width=145 height=50 align=left valign=bottom style="{leftStyle}">{leftPreview}</td><td width=145 height=50 align=center valign=bottom style="{centerStyle}">{centerPreview}</td><td width=140 height=50 align=right valign=bottom style="{rightStyle}">{rightPreview}</td></tr>',
				 '</table></div></div>',
	             '</tpl></div>'
		     ),
		     //height: 250,
		     multiSelect: false,
		     singleSelect: true,
		     overClass: 'x-view-over',
		     itemSelector: 'div.thumb-wrap',
		     emptyText: 'No images to display'.localize()
		});


		var footerCmb=new Ext.form.ComboBox({
			fieldLabel: 'Footer'.localize(),
			width: 450,
			tabIndex: 304,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			store:new Ext.data.SimpleStore({
				data:[['', '', '(none)'.localize()],['font-size:8pt;', 'Page'.localize() + ' &[Page]', 'Page'.localize()+ ' 1'],['font-size:8pt;', 'Page'.localize() + ' &[Page] ' + 'of'.localize() + ' &[Pages]', 'Page'.localize()+ ' 1 ' + 'of'.localize()+ ' ?'], ['font-size:8pt;', '&[Tab]', 'Sheet'.localize()+ ' 1'], ['font-size:8pt;', '&[File]', 'Book'.localize()+ ' 1']],
				fields:[{name:'preDefFStyle'}, {name:'preDefFValue'}, {name:'preDefFPreview'}]
			}),
			value:'(none)'.localize(),
			displayField:'preDefFPreview',
			editable:false,
			mode: 'local',
		    triggerAction: 'all',
			listeners:{
				select:function(cmb, tmpRec, index){
					var record = footerStore.getAt(0);
					setCmbSelection(record, tmpRec, 'preDefF');
				}
			}
		});


		function setCmbSelection(record, tmpRec,  s){

			var preview = tmpRec.get(s + 'Preview') === '(none)'? '':tmpRec.get(s + 'Preview');

			record.set('leftStyle','');
			record.set('leftValue', '');
			record.set('leftPreview', '');
			record.set('centerStyle', tmpRec.get(s + 'Style'));
			record.set('centerValue', tmpRec.get(s +'Value'));
			record.set('centerPreview', preview);
			record.set('rightStyle', '');
			record.set('rightValue', '');
			record.set('rightPreview', '');

		}

		var customHFpan = new Ext.Toolbar({
			baseCls: 'x-plain',
			items: []
		});

		var headerFooterPanel={
			layout:'form',
			labelAlign:'top',
			border:false,
			defaults:{
				border:false
			},
			items:[{
				layout:'fit',
				height:60,
				width:455,
				items:headerDV
			},
			headerCmb,
			new Ext.Panel({
				layout:'column',
				baseCls: 'x-plain',
				style: 'padding-bottom: 10px;',
				items:[
				       new Ext.Panel({
				    	   baseCls: 'x-plain',
				    	   columnWidth: 0.5,
				    	   items:[new Ext.Button({
								text:'Custom Header'.localize().concat('...'),
								tabIndex: 302,
								width: 220,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler:function(){
									Jedox.gen.load(Jedox.wss.app.dynJSRegistry.customHeaderFooter, ['Header'.localize(), customHandleFunction, headerStore.getAt(0)]);
								}
							})]
				       }),
				       new Ext.Panel({
				    	   baseCls: 'x-plain',
				    	   columnWidth: 0.5,
				    	   items:[new Ext.Button({
								text:'Custom Footer'.localize().concat('...'),
								tabIndex: 303,
								width: 220,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler:function(){
									Jedox.gen.load(Jedox.wss.app.dynJSRegistry.customHeaderFooter, ['Footer'.localize(), customHandleFunction, footerStore.getAt(0)]);
								}
							})]
				       })
					]
			}),
			footerCmb,
			{
				layout:'fit',
				height:62,
				width:450,
				items:footerDV
			}]
		}

		var customHandleFunction=function(tmpRec, hORf){
			var record;

			if (hORf === 'Header'.localize())
				record = headerStore.getAt(0);
			else
				record = footerStore.getAt(0);

			record.set('leftStyle',tmpRec.get('leftStyle'));
			record.set('leftValue', tmpRec.get('leftValue'));
			record.set('leftPreview', tmpRec.get('leftPreview'));
			record.set('centerStyle', tmpRec.get('centerStyle'));
			record.set('centerValue', tmpRec.get('centerValue'));
			record.set('centerPreview', tmpRec.get('centerPreview'));
			record.set('rightStyle', tmpRec.get('rightStyle'));
			record.set('rightValue', tmpRec.get('rightValue'));
			record.set('rightPreview', tmpRec.get('rightPreview'));
		}


		function getPreview (value){
			var date = new Date();
			var today = date.getDate() + '/' + date.getMonth()+1 + '/' + date.getFullYear();
			var time = date.getHours() + ':' + date.getMinutes() + ":" + date.getSeconds();

			var v = ['&[Page]', '&[Pages]', '&[Date]', '&[Time]', '&[Tab]', '&[File]'];
			var p= ['1', '5', today, time, 'Sheet 1', 'Book 1'];

			var preview = _formatText(value);

			for (var i=0; i<v.length; i++)
				preview = preview.replace(v[i], p[i]);

			return preview;
		}




		//================================ Sheet Components ============================================

		var refersToTxf = new Ext.form.TextField({
			fieldLabel: 'Print area'.localize(),
		  	//value: Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName() + '!' + Jedox.wss.app.environment.defaultSelection.getActiveRange().getValue(),
		  	width: 315,
		  	tabIndex: 401
		});

		var selectRangeBtn=new Ext.Button({
		  	id: 'selRangeBegin',
		  	iconCls: 'select-range-icon',
		  	cls: 'x-btn-icon',
		  	tabIndex: 402,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Select Range".localize(),
		 	handler:function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [
				{
					fnc: [this, selRangeHandleFnc],
					format: '{$Range}',
					rng: refersToTxf.getValue()
				}
			]);
		 	that.win.hide();}
		});

		function selRangeHandleFnc(selected){
			that.win.show();
			refersToTxf.setValue(selected);
		}


		var gridLinesChb=new Ext.form.Checkbox({
			boxLabel: 'Gridlines'.localize(),
			hideLabel:true,
			tabIndex: 403,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler:centerPic
		});


		var cellErrorsCmb=new Ext.form.ComboBox({
			fieldLabel: 'Cell Errors As'.localize(),
			width: 190,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 404,
			store:new Ext.data.SimpleStore({
				data:[['displayed','displayed'.localize()],['blank','blank'.localize()],['--','--'], ['#N/A'.localize(),'#N/A'.localize()]],
				fields:[{name:'cellErrorID'}, {name:'cellErrorName'}]
			}),
			value:'displayed'.localize(),
			displayField:'cellErrorName',
			valueField:'cellErrorID',
			editable:false,
			mode: 'local',
		    triggerAction: 'all'
		});



		var downThenOverRb=new Ext.form.Radio({
			hideLabel:true,
			boxLabel: 'Down, then over'.localize(),
			checked:true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 405,
			name: 'rb-page-order',
			listeners:{
				check:function(chb, checked){
					if (checked)
						setPageOrderPic(0);
				}
			},
			inputValue: 0

		});

		var overThenDownRb=new Ext.form.Radio({
			hideLabel:true,
			boxLabel: 'Over, then down'.localize(),
			name: 'rb-page-order',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 406,
			listeners:{
				check:function(chb, checked){
					if (checked)
						setPageOrderPic(1);
				}
			},
			inputValue: 1
		});

		var pageOrderData=[
			['down_over', 'down_over'],
			['over_down', 'over_down']
		];


		var pageOrderStore=new Ext.data.SimpleStore({
	                fields: ['title', 'pic'],
					data: [['down_over', 'down_over']]
	    });



		function setPageOrderPic(selectedIndex) {
			var record = pageOrderStore.getAt(0);
			record.set('pic', pageOrderData[selectedIndex][1]);
		}


		var pageOrderDV = new Ext.DataView({
		     id: 'page-order-dv',
		     store: pageOrderStore,
		     tpl: new Ext.XTemplate(
			     '<div class="folder-navigation"><tpl for=".">',
			     '<div class="thumb-wrap">',
			     '<div class="thumb" style="padding: 5px; text-align: center; "><img class="{pic}" src="../lib/ext/resources/images/default/s.gif" width="59" height="49" /></div></div>',
			     '</tpl></div>'
		     ),
		     //height: 250,
		     multiSelect: false,
		     singleSelect: true,
		     overClass: 'x-view-over',
		     itemSelector: 'div.thumb-wrap',
		     emptyText: 'No images to display'.localize()
		});


		var printAreaPanel= {
			   layout:'column',
			   border:false,
			   baseCls:'x-plain',
			   bodyStyle:'padding-top:10px; padding-bottom:10px',
			   items:[{
			   		layout:'form',
			     	border:false,
			     	width: 425,
			     	baseCls:'main-panel',
			     	items:refersToTxf
		},
			    {
			     layout:'form',
			     border:false,
			     width: 30,
			     baseCls:'x-plain',
			     items:selectRangeBtn
		}]
			};


		var printFs=new Ext.form.FieldSet({
			title: 'Print'.localize(),
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			items:{
				layout:'column',
				defaults:{border:false
		},
				baseCls:'main-panel',
				items:[{
					layout:'form',
					//border:false,
					width:150,
					items:gridLinesChb,
					 listeners:{
						afterrender:function(){
							gridLinesChb.setValue(_preselctionChbValues['gridLinesChb']);
						}
					}
				 },
				 {
					layout:'form',
					width:300,
					items:cellErrorsCmb
				 }]
			}
		});


		var pageOrderFs=new Ext.form.FieldSet({
			title: 'Page order'.localize(),
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			items:{
				layout:'column',
				defaults:{border:false
		},
				baseCls:'main-panel',
				items:[{
					layout:'form',
					//border:false,
					width:150,
					height:60,
					items:[downThenOverRb, overThenDownRb]
				 },
				 {
					layout:'fit',
					width:150,
					height:60,
					items:pageOrderDV
				 }]
			}
		});


		//================================ Panels and Containers ============================================

		var orientationFs=new Ext.form.FieldSet({
			title: 'Orientation'.localize(),
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			items: {
				layout: 'column',
				baseCls: 'x-plain',
				columns: 2,
				items: [{
					html: '<img class="ico_portrait" src="../lib/ext/resources/images/default/s.gif" align="center" width="36" height="36" />',baseCls: 'x-plain',width: 50},
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						autoWidth: true,
						autoHeight: true,
						items: [
							portraitRb
						]
					}),
					{html: '<img class="ico_landscape" align="center" src="../lib/ext/resources/images/default/s.gif" width="36" height="36" />',baseCls: 'x-plain',width: 50},
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						autoWidth: true,
						autoHeight: true,
						items: [
							landscapeRb
						]
					})
				]
			}
		});


		var scalingFs=new Ext.form.FieldSet({
			//layout:'form',
			title: 'Scaling'.localize(),
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			autoWidth: true,
			items: [
			        new Ext.Panel({
				layout: 'column',
				border: false,
				baseCls: 'x-plain',
				height: 28,
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						baseCls: 'x-plain',
						width: 18,
						autoHeight: true,
						items: [
							adjustToRb
						]
					}),
					{html: 'Adjust to'.localize() + ':', baseCls: 'x-plain',width: 80, style: 'padding-top:4px;'},
					{border:false,items:adjustToSpn},
					{html: '&nbsp&nbsp% '.concat('normal size'.localize()),baseCls: 'x-plain', style: 'padding-top:4px;'}
				]
			}),
			new Ext.Panel({
				layout: 'column',
				border: false,
				baseCls: 'x-plain',
				items: [
					new Ext.Panel({
						border: false,
						layout: 'form',
						bodyStyle: 'background-color:transparent;',
						baseCls: 'x-plain',
						width: 18,
						items: [
							fitToRb
						]
					}),
					{html: 'Fit to'.localize() + ':',baseCls: 'x-plain',width: 80, style: 'padding-top:4px;'},
					{border:false,items:pageWideSpn},
					{html: '&nbsp&nbsp '.concat('page(s) wide by'.localize()),baseCls: 'x-plain',width: 120, style: 'padding-top:4px;'},
					{border:false,items:pageTallSpn},
					{html: '&nbsp&nbsp '.concat('tall'.localize()),baseCls: 'x-plain', style: 'padding-top:4px;'}]
			})]
		});

		var printOptionsFs=new Ext.form.FieldSet({
			cls: 'custom-title-fieldset',
			bodyStyle:'padding-top:10px;',
			autoHeight: true,
			items: [paperSizeCmb, firstPageNumberTxf]
		});



	    var pageSetupTbs = new Ext.TabPanel({
			region: 'center',
			//margins: '3 3 3 0',
			height: 385,
			layoutOnTabChange: true,
			baseCls:'x-plain',
			activeTab: 0,

			defaults: {
				//autoScroll: true,
				bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'

		},
			items: [{
				id: 'page',
				//layout: 'form',
				title: 'Page'.localize(),
				baseCls:'x-plain',
				items: [orientationFs, scalingFs, printOptionsFs]
			},
			{
				id: 'margins',
				title: 'Margins'.localize(),
				baseCls:'x-plain',
				items :[pageMarginPanel, centerOnPageFs]
			},
				{
					id: 'header-footer',
		            title: 'Header/Footer'.localize(),
					baseCls:'x-plain',
					items: [headerFooterPanel]
	        	},
				{
					id: 'sheet',
		            title: 'Sheet'.localize(),
					baseCls:'x-plain',
					items: [printAreaPanel, printFs, pageOrderFs]
	        	}],
	        listeners: {
				tabchange : function(el, e) {
					var toSet = {};
					toSet[e.id] = e;
					setContainers(toSet);
				}
			}

	    });


		var mainPanel=new Ext.Panel({
			modal:true,
			layout: 'form',
			baseCls:'main-panel',
			border:false,
			items:[
				pageSetupTbs,
				{
				//title: 'top-table-panel',

				layout:'form',
				border:false,
				height:30
	/*			//baseCls:'main-panel',
				buttons: [{
					text: 'Print'.localize().concat('...')
				},{
					text: 'Print Preview'.localize(),
					handler: function(){}
				},{
					text: 'Options'.localize(),
					handler: function(){}
				}]*/
			 	}
		]
		});




		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					id:'page-setup-dlg',
					defaults: {bodyStyle:'padding:2px'},
					title:'Page Setup'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        cls: 'default-format-window',
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 500,
					height: 500,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.pageSetup);

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
							text: 'OK'.localize(),
							tabIndex: 1001,
							handler: function()
							{
								(new Jedox.backend.RPCAsyncRqst('wss_sheet', 'storePageSetup', [_genSavingObj()])).send();
								that.win.close();
							}
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							tabIndex: 1002,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							handler: function(){
								that.win.close();
							}
						}))]
		});

		var _formatText = function(s)
		{
			s = s.replace(/\n/g,'<br>');
			return s;
		}

		var _unFormatText = function(s)
		{
			s = s.replace(/<br>/g,'\n');
			return s;
		}

		var _genSavingObj = function()
		{
			var tmpObj;
			var ps = {};

			// dialog
			ps.page = {};
			ps.margins = {};
			ps.hf = {};
			ps.sheet = {};

			// page
			tmpObj = ps.page;
			tmpObj.portrait = portraitRb.getValue(); // true = portrait; false = landscape
			tmpObj.adjust = {
				enabled: adjustToRb.getValue(),
				size: adjustToSpn.getValue()
			};
			tmpObj.fit = {
				enabled: fitToRb.getValue(),
				wide: pageWideSpn.getValue(),
				tall: pageTallSpn.getValue()
			};
			tmpObj.paper_size = paperSizeCmb.getValue();
			//tmpObj.print_quality = printQualityCmb.getValue();
			tmpObj.first_page = firstPageNumberTxf.getValue();

			// margins
			tmpObj = ps.margins;
			tmpObj.top = topMarginSpn.getValue();
			tmpObj.left = leftMarginSpn.getValue();
			tmpObj.bottom = bottomMarginSpn.getValue();
			tmpObj.right = rightMarginSpn.getValue();
			tmpObj.header = headerMarginSpn.getValue();
			tmpObj.footer = footerMarginSpn.getValue();
			tmpObj.horiz = horizontallyChb.getValue();
			tmpObj.vert = verticallyChb.getValue();

			// header/footer
			tmpObj = ps.hf;
			var tmpRec = headerStore.getAt(0);
				// header
			tmpObj.header = {};
			tmpObj.header.left_style = tmpRec.get('leftStyle');
			tmpObj.header.left_value = _unFormatText(tmpRec.get('leftValue'));
			tmpObj.header.center_style = tmpRec.get('centerStyle');
			tmpObj.header.center_value = _unFormatText(tmpRec.get('centerValue'));
			tmpObj.header.right_style = tmpRec.get('rightStyle');
			tmpObj.header.right_value = _unFormatText(tmpRec.get('rightValue'));
				// footer
			tmpRec = footerStore.getAt(0);
			tmpObj.footer = {};
			tmpObj.footer.left_style = tmpRec.get('leftStyle');
			tmpObj.footer.left_value = _unFormatText(tmpRec.get('leftValue'));
			tmpObj.footer.center_style = tmpRec.get('centerStyle');
			tmpObj.footer.center_value = _unFormatText(tmpRec.get('centerValue'));
			tmpObj.footer.right_style = tmpRec.get('rightStyle');
			tmpObj.footer.right_value = _unFormatText(tmpRec.get('rightValue'));

			// sheet
			tmpObj = ps.sheet;
			var tmpRngStr = refersToTxf.getValue(),
					refs = Jedox.wss.formula.parse(tmpRngStr);

			tmpObj.print_area = refs.length ? refs[0].rng : '';
			tmpObj.print_area_string = tmpRngStr;
			tmpObj.gridlines = gridLinesChb.getValue();
			tmpObj.cell_errors = cellErrorsCmb.getValue();
			tmpObj.page_order = downThenOverRb.getValue(); // true = down, then over; false = over, then down

			return ps;
		}

		var initPageSetupDlg = function(){
			var result = (new Jedox.backend.RPCSyncRqst('wss_sheet', 'getPageSetup', [_genSavingObj()])).send();
			if (result)
			{
				//inicijalizuj
				var ps = result;
				//console.log(ps);

				// Page tab
				portraitRb.setValue(ps.page.portrait);
				landscapeRb.setValue(!ps.page.portrait);
				adjustToRb.setValue(ps.page.adjust.enabled);
				adjustToSpn.setValue(ps.page.adjust.size);
				fitToRb.setValue(ps.page.fit.enabled);
				pageWideSpn.setValue(ps.page.fit.wide);
				pageTallSpn.setValue(ps.page.fit.tall);
				paperSizeCmb.setValue(ps.page.paper_size);
				firstPageNumberTxf.setValue(ps.page.first_page);

				//Header and Footer
				var  tmpHRec = new Ext.data.Record({
				  	'leftStyle': ps.hf.header.left_style,
					'leftValue': _formatText(ps.hf.header.left_value),
					'leftPreview': getPreview(ps.hf.header.left_value),
					'centerStyle': ps.hf.header.center_style,
					'centerValue': _formatText(ps.hf.header.center_value),
					'centerPreview': getPreview(ps.hf.header.center_value),
					'rightStyle': ps.hf.header.right_style,
					'rightValue': _formatText(ps.hf.header.right_value),
					'rightPreview': getPreview(ps.hf.header.right_value)
				});

				var  tmpFRec = new Ext.data.Record({
				  	'leftStyle': ps.hf.footer.left_style,
					'leftValue': _formatText(ps.hf.footer.left_value),
					'leftPreview': getPreview(ps.hf.footer.left_value),
					'centerStyle': ps.hf.footer.center_style,
					'centerValue': _formatText(ps.hf.footer.center_value),
					'centerPreview': getPreview(ps.hf.footer.center_value),
					'rightStyle': ps.hf.footer.right_style,
					'rightValue': _formatText(ps.hf.footer.right_value),
					'rightPreview': getPreview(ps.hf.footer.right_value)
				});

				customHandleFunction(tmpHRec, 'Header'.localize());
				customHandleFunction(tmpFRec, 'Footer'.localize());


				//Margins tab
				topMarginSpn.setValue(ps.margins.top);
				headerMarginSpn.setValue(ps.margins.header);
				leftMarginSpn.setValue(ps.margins.left);
				rightMarginSpn.setValue(ps.margins.right);
				bottomMarginSpn.setValue(ps.margins.bottom);
				footerMarginSpn.setValue(ps.margins.footer);
				_preselctionChbValues['horizontallyChb'] = ps.margins.horiz;
				_preselctionChbValues['verticallyChb'] = ps.margins.vert;


				//Sheet tab
				refersToTxf.setValue(ps.sheet.print_area_string);
				_preselctionChbValues['gridLinesChb'] = ps.sheet.gridlines;
				cellErrorsCmb.setValue(ps.sheet.cell_errors);
				downThenOverRb.setValue(ps.sheet.page_order);
				overThenDownRb.setValue(!ps.sheet.page_order);
				setPageOrderPic(ps.sheet.page_order? 0:1);
			}
		}

		initPageSetupDlg();

		//paperSizeCmb.setValue('A4');
		//printQualityCmb.setValue('100 dpi');
		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PageSetup, Jedox.dlg.Dialog);