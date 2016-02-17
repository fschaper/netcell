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
 * SVN: $Id: Alignment.js 4719 2011-03-18 09:35:41Z lukap $
 *
 */

Jedox.wss.dlg.format.alignment = function(callback, _pre, toDisable, tabOffset) {

	var alignHorizontal = [ [ 'none', 'General'.localize() ],
	                        [ 'left', 'Left (Indent)'.localize() ],
	                        [ 'center', 'Center'.localize() ],
	                        [ 'right', 'Right'.localize() ],
	                        //[ 'fill', 'Fill'.localize() ],
	                        [ 'justify', 'Justify'.localize() ]
	                        //[ 'center-across', 'Center across section'.localize() ],
	                        //[ 'distributed', 'Distributed (Indent)'.localize() ]
	                        ];

	var alignVertical = [ [ 'top', 'Top'.localize() ],
	                      [ 'center', 'Center'.localize() ],
	                      [ 'bottom', 'Bottom'.localize() ],
	                      [ 'justify', 'Justify'.localize() ],
	                      [ 'distributed', 'Distributed'.localize() ] ];

	var textDirection = [ [ 'context', 'Context'.localize() ],
	                      [ 'ltr', 'Left-to-Right'.localize() ],
	                      [ 'rtl', 'Right-to-Left'.localize() ] ];

	var textDirectionStore = new Ext.data.SimpleStore( {
		fields : [ 'direction', 'description' ],
		data : textDirection
	});

	var alignVerticalStore = new Ext.data.SimpleStore( {
		fields : [ 'format', 'formatType' ],
		data : alignVertical
	});

	var alignHorizontalStore = new Ext.data.SimpleStore( {
		fields : [ 'format', 'formatType' ],
		data : alignHorizontal
	});

	// ##### ALIGN tab #####

	// align tab functions:
	var horAlignGridDesc = 'General'.localize();
	var verAlignGridDesc = 'Top'.localize();
	var textDirectionVarDesc = 'Context'.localize();

	var textDirectionVar;
	var horAlignGrid;
	var horAlignGrid;
	var horAlignGrid;
	var textWrap;
	var verAlignGrid;
	var isSetWrap = false;
	if (textWrap == 'pre-wrap') isSetWrap=true;
	else if (textWrap == 'pre') isSetWrap=false;


	var format = {};
	if (!_pre) _pre={};
	else format = _pre;


	// eventual preselection

	if (_pre.whiteSpace==null) _pre.whiteSpace='pre';
	var textWrap = _pre.whiteSpace;
	var isSetWrap=false;
	if (textWrap == 'pre-wrap') isSetWrap=true;
	else if (textWrap == 'pre') isSetWrap=false;

	if (_pre.textAlign==null) _pre.textAlign='';
	var horAlignGrid = _pre.textAlign;

	if (_pre.verticalAlign==null) _pre.verticalAlign='';
	var verAlignGrid = _pre.verticalAlign;

	if (_pre.textIndent==null) _pre.textIndent=0;
	if (_pre.textIndent=='') _pre.textIndent=0;
	var indentGrid = _pre.textIndent;
	if (indentGrid != 0) indentGrid = indentGrid.replace(/em/i, "");


	// work area

	for ( var HAC = 0; HAC < 5; HAC++) {
		if (alignHorizontal[HAC][0] == horAlignGrid)
			horAlignGridDesc = alignHorizontal[HAC][1];
	}
	;

	for ( var HAC = 0; HAC < 5; HAC++) {
		if (alignVertical[HAC][0] == verAlignGrid)
			verAlignGridDesc = alignVertical[HAC][1];
	}
	;

	for ( var HAC = 0; HAC < 3; HAC++) {
		if (textDirection[HAC][0] == textDirectionVar)
			textDirectionVarDesc = textDirection[HAC][1];
	}
	;

	function setHorizontalAlignment(combo, record, index) {
		horAlignGrid = alignHorizontal[index][0];
	}
	;

	function setTextDirection(combo, record, index) {
		textDirectionVar = textDirection[index][0];
	}

	function setWrap() {
		if (wrapTextCB.getValue())
			textWrap = 'pre-wrap';
		else
			textWrap = 'pre';
	}

	function setVerticalAlignment(combo, record, index) {
		verAlignGrid = alignVertical[index][0];
	}
	;

	function setTextIndent(indentSpinner, newValue, oldValue) {
		indentGrid = newValue;
		indentGrid = ''.concat(indentGrid, 'em');
	}
	;

	// align tab display

	var wrapTextCB = new Ext.form.Checkbox( {
		id: 'wFormatAlignment_wrap_chk',
		name : 'wrapText',
		boxLabel : 'Wrap text'.localize(),
		tabIndex: 10 + tabOffset,
		handler : setWrap,
		checked : isSetWrap
	});

	var indentSpinner = new Ext.ux.form.SpinnerField( {
		id: 'wFormatAlignment_indent_spn',
		minValue : 0,
		maxValue : 250,
		name : 'text_indent',
		allowBlank : false,
		xtype : 'number',
		width : 60,
		hideLabel: true,
		border : false,
		value : indentGrid,
		tabIndex: 3 + tabOffset,
		listeners : {
		spin : {
		fn : setTextIndent,
		scope : this
	}
	}
	});

	var cellsMerged = Jedox.wss.sheet.getMergeState();
	cellsMerged = (cellsMerged==undefined)? null : cellsMerged;
	var newMerge = cellsMerged;

	// triCheckBox
	var formTriCB = new Ext.ux.form.TriCheckbox({
		id: 'wFormatAlignment_merge_chk',
		name : 'tri-check1',
		xtype: 'tri-checkbox',
		boxLabel: 'Merge cells'.localize(),
		id: 'tribox',
		//tabIndex: 11 + tabOffset,
		fieldLabel : 'Merge'.localize(),
		hideLabel : true,
		checked : cellsMerged
		// values: null, true, false
		,listeners: {
			check: function(cmp, state){newMerge = state;}
		}
	});

	var mergeCells = function(){
		if (newMerge != cellsMerged){
			switch (newMerge){
			case true:
				Jedox.wss.sheet.merge();
				break;
			case false:
				Jedox.wss.sheet.unMerge();
				break;
			case null:
				if (!cellsMerged) Jedox.wss.sheet.merge();
				break;
			}
		}
	};

	var alignTab = new Ext.Panel(
			{
				layout : 'column',
				baseCls : 'x-plain',
				id: 'alignTabMain',
				listeners: {
					doSelectAlignment: function(callback) {
						//select alg

						if (_pre.textIndent == indentSpinner.getRawValue())
							var ind = '';
						else
							var ind = indentSpinner.getRawValue().concat('em');

						format = {
								textAlign: horAlignGrid,
								verticalAlign: verAlignGrid,
								textIndent: ind,
								whiteSpace: textWrap,
								direction: textDirectionVar
						};
						mergeCells();
						callback(format);
					}
				},
				items : [ {
					columnWidth : 0.99,
					baseCls : 'x-plain',
					items : [ new Ext.Panel(
							{
								id : 'alignTab',
								bodyStyle : 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
								border : false,
								frame : false,
								autoHeight : true,
								//width: 400,
								autoWidth : true,
								baseCls : 'x-title-f',
								header : false,
								items : [
								         {
								        	 bodyStyle : 'padding: 0px; color: #000000; font-size: 9pt; background-color: transparent;',
								        	 border : true,
								        	 autoHeight : true,
								        	 xtype : 'fieldset',
								        	 layout : 'form',
								        	 frame : false,
								        	 title : 'Text alignment'.localize(),
								        	 items : [ new Ext.Panel(
								        			 {
								        				 layout : 'column',
								        				 baseCls : 'x-plain',
								        				 items : [
								        				          {
								        				        	  columnWidth : .6,
								        				        	  baseCls : 'x-plain',
								        				        	  items : [
								        				        	           {
								        				        	        	   html : 'Horizontal'.localize().concat(':'),
								        				        	        	   baseCls : 'x-plain'
								        				        	           },
								        				        	           {
								        				        	        	   layout : 'form',
								        				        	        	   baseCls : 'x-plain',
								        				        	        	   autoWidth : true,
								        				        	        	   items : new Ext.form.ComboBox(
								        				        	        			   {
								        				        	        				   id : 'wFormatAlignment_horizontal_cmb',
								        				        	        				   store : alignHorizontalStore,
								        				        	        				   displayField : 'formatType',
								        				        	        				   hideLabel : true,
								        				        	        				   editable : false,
								        				        	        				   typeAhead : true,
								        				        	        				   mode : 'local',
								        				        	        				   triggerAction : 'all',
								        				        	        				   value : horAlignGridDesc,
								        				        	        				   selectOnFocus : true,
								        				        	        				   listWidth : 150,
								        				        	        				   width : 150,
								        				        	        				   tabIndex: 1 + tabOffset,
								        				        	        				   listeners : {
								        				        	        				   select : {
								        				        	        				   fn : setHorizontalAlignment,
								        				        	        				   scope : this
								        				        	        			   }
								        				        	        			   }
								        				        	        			   })
								        				        	           }
//								        				        	           {
//								        				        	        	   baseCls : 'x-plain',
//								        				        	        	   html : 'Vertical'.localize().concat(':'),
//								        				        	        	   bodyStyle : 'padding-top: 2px'
//								        				        	           },
//								        				        	           {
//								        				        	        	   layout : 'form',
//								        				        	        	   baseCls : 'x-plain',
//								        				        	        	   autoWidth : true,
//								        				        	        	   items : new Ext.form.ComboBox(
//								        				        	        			   {
//								        				        	        				   store : alignVerticalStore,
//								        				        	        				   displayField : 'formatType',
//								        				        	        				   hideLabel : true,
//								        				        	        				   editable : false,
//								        				        	        				   typeAhead : true,
//								        				        	        				   mode : 'local',
//								        				        	        				   triggerAction : 'all',
//								        				        	        				   value : verAlignGridDesc,
//								        				        	        				   selectOnFocus : true,
//								        				        	        				   listWidth : 150,
//								        				        	        				   width : 150,
//																								tabIndex: 2 + tabOffset,
//								        				        	        				   listeners : {
//								        				        	        				   select : {
//								        				        	        				   fn : setVerticalAlignment,
//								        				        	        				   scope : this
//								        				        	        			   }
//								        				        	        			   }
//								        				        	        			   })
//								        				        	           }
								        				        	           //					new Ext.form.Checkbox({
								        				        	           //			        		        		name: 'justifyDistr',
								        				        	           //			        		        		boxLabel: 'Justify distributed'
								        				        	           // })
								        				        	           // this
								        				        	           // property
								        				        	           // requires
								        				        	           // CSS3 -
								        				        	           // wait for
								        				        	           // it
								        				        	           ]
								        				          } // new column
								        				          ,
								        				          {
								        				        	  columnWidth : .3,
								        				        	  baseCls : 'x-plain',
								        				        	  items : [
								        				        	           {
								        				        	        	   html : 'Indent'.localize().concat(':'),
								        				        	        		   baseCls : 'x-plain'
								        				        	        		   //,bodyStyle : 'margin-top: 22px;' --- uncomment after vertical align is enabled
								        				        	           },
								        				        	           new Ext.Panel({
								        				        	        	   layout: 'form',
								        				        	        	   baseCls: 'x-plain',
								        				        	        	   width: 60,
								        				        	        	   items: [indentSpinner]
								        				        	           })
								        				        	            ]
								        				          } ]
								        			 }) ]
								         }, // text control part
								         {
								        	 bodyStyle : 'padding: 0px; color: #000000; font-size: 9pt; background-color: transparent;',
								        	 border : true,
								        	 autoHeight : true,
								        	 xtype : 'fieldset',
								        	 layout : 'form',
								        	 frame : false,
								        	 title : 'Text control'.localize(),
								        	 items : [// text align elements - items
								        	          // little column here

								        	          new Ext.Panel( {
								        	        	  layout : 'form',
								        	        	  baseCls : 'x-plain',
								        	        	  items : [ {
								        	        		  //columnWidth: .4,
								        	        		  baseCls : 'x-plain',
								        	        		  items : [ wrapTextCB,
								        	        		            formTriCB ]
								        	        	  } // new column
								        	        	  ]
								        	          }) ]
								         },
								         {
								        	 bodyStyle : 'padding: 0px; color: #000000; font-size: 9pt; background-color: transparent;',
								        	 border : true,
								        	 autoHeight : true,
								        	 xtype : 'fieldset',
								        	 layout : 'form',
								        	 frame : false,
								        	 title : 'Right-to-Left'.localize(),
								        	 items : [
								        	          // little column here
								        	          new Ext.Panel(
								        	        		  {
								        	        			  layout : 'column',
								        	        			  baseCls : 'x-plain',
								        	        			  items : [ {
								        	        				  columnWidth : .4,
								        	        				  baseCls : 'x-plain',
								        	        				  items : [
								        	        				           {
								        	        				        	   html : 'Text direction'.localize().concat(':'),
								        	        				        	   baseCls : 'x-plain'
								        	        				           },
								        	        				           new Ext.form.ComboBox({
								        	        				        			   store : textDirectionStore,
								        	        				        			   displayField : 'description',
								        	        				        			   hideLabel : true,
								        	        				        			   editable : false,
								        	        				        			   disabled: true,
								        	        				        			   typeAhead : true,
								        	        				        			   mode : 'local',
								        	        				        			   triggerAction : 'all',
								        	        				        			   value : textDirectionVarDesc,
								        	        				        			   selectOnFocus : true,
								        	        				        			   listWidth : 100,
								        	        				        			   width : 100,
								        	        				        			   tabIndex: 20 + tabOffset,
								        	        				        			   listeners : {
								        	        				        			   select : {
								        	        				        			   fn : setTextDirection,
								        	        				        			   scope : this
								        	        				        		   }
								        	        				        		   }
								        	        				        		   }) ]
								        	        			  } ]
								        	        		  }) ]
								         }

								         ]
							}) ]
				}
				//	this feature requires either CSS3 or advanced object formatting, unconvenient for grid
				// {
				// columnWidth: 0.275,
				// baseCls:'x-title-f',
				// items:[
				// new Ext.Panel({
				// id: 'alignTab',
				// bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt;
				// background-color: transparent;',
				// border: false,
				// frame: false,
				// autoHeight: true,
				// width: 50,
				// baseCls: 'x-title-f',
				// header: false,
				// items: [{
				// bodyStyle: 'padding: 0px; color: #000000; font-size: 9pt;
				// background-color: transparent;',
				// border: true,
				// autoHeight: true,
				// width: 115,
				// xtype: 'fieldset',
				// layout: 'form',
				// frame: false,
				// title: 'Orientation'.localize(),
				// items: [{html: 'Degrees:',
				// baseCls:'x-plain'},
				// new Ext.ux.form.SpinnerField({
				// strategy: new Ext.ux.form.Spinner.NumberStrategy({
				// xtype: 'number',
				// minValue: -90,
				// maxValue: 90
				// }),
				// name: 'degrees',
				// hideLabel: true,
				// allowBlank: false,
				// width: 90,
				// border: false,
				// value: 0,
				// listeners: {
				// click: {
				// fn: chDecimals,
				// scope: this
				// }
				// }
				// })]
				// }]
				// })
				// ]
				// }
				]
			});
	// ##### END of ALIGN tab ######

	// alignment panel
	callback(alignTab);
}