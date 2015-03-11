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
 * SVN: $Id: InsertHyperlink.js 5082 2011-06-24 14:01:57Z lukap $
 *
 */
Jedox.wss.dlg.openHL = function(conf) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.InsertHyperlink(conf));
};

Jedox.wss.dlg.InsertHyperlink = (function() {

	return function (conf) {

		Jedox.wss.dlg.InsertHyperlink.parent.constructor.call(this);
		this.id = 'wInsHyperlink_dlg_wnd';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		Array.prototype.findIndex = function(value){
			var ctr = "";
			for (var i=0; i < this.length; i++) {
				// use === to check for Matches. ie., identical (===), ;
				if (this[i][0] == value) {
					return i;
				}
			}
			return ctr;
		};

		Array.prototype.clean = function(deleteValue) {
			for (var i = 0; i < this.length; i++) {
			    if (this[i] == deleteValue) {
			      this.splice(i, 1);
			      i--;
			    }
			}
			return this;
		};

		var onSelectDVFn = function(el){
			var tlst = ['workbook', 'frameset', 'folder', 'hyperlink', 'static', 'urlplugin'];
			var type = (tlst.indexOf(el.t)>-1)? el.t : 'static';
			handleComponents({ftype: type});
		}


		// ################# OPEN DIALOG #####################
		// var openPanel = Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open,
		// ['open', true]);
		// #######################################END OF OPEN DIALOG
		// PANEL###############################################

		// TODO: check communication from grid to dlg
		var _pre = conf.data;
		var openDlg = this.containers.browsePanel = new Jedox.wss.dlg.Browse('hyperlink', false, (_pre && _pre.link.value.target.ghnt)? true:false, 20, onSelectDVFn);
		this.containers.browseTbar = Ext.getCmp('browseToolbarHolder').getTopToolbar();

		var _activeMode = 0;
		var _urlSel;
		var hldata = {
				dyn: false,
				link:{},
				text:{},
				tip:{},
				trans:[]
		};
		var cellRefChildren = [];
		var definedNames = [];
		var definedNamesStore = [];
		var activeContainers = {};
		var isNR = false;
		var initCellValue = (_pre) ? _pre.text.value : ( ( conf.defName ) ? conf.defName : "" );

		var _txtSrc = 'string';
		var _tipSrc = 'string';

		// get predefined Names
		var position = Jedox.wss.app.environment.defaultSelection.getActiveRange().getActiveCell();
		var tmpResponse = Jedox.backend.ccmd(0, ["nlst", [position._x, position._y]]);
		var names = tmpResponse[0][1][0];
		for (var i = 0; i < names.length; i++) {
			//tmpRec = names[i].name;
			var tmpProp = {
					text: names[i].name,
					leaf: true,
					id: 'N_'.concat(i),
					scope: names[i].scope
			};
			definedNamesStore.push(names[i].scope);
			definedNames.push(tmpProp);
		}

		//	get worksheets function
		var worksheets = Jedox.backend.wss.getSheets()[0];
		for (i = 1; worksheets[i] != null; i = i + 2) {
			// add to tree funct.
			var tmpProp = {
					text: worksheets[i],
					leaf: true
			}
			if (i == 1)
				var firstNode = worksheets[i];
			cellRefChildren.push(tmpProp);
		};

		var towhat = 'towb';

		function validateTransfer(){
			//
			for (var t=0; t<gridData.length; t++){
				if (gridData[t][5] == 'cval' || gridData[t][5] == 'clist')
					// splice
					gridData.splice(t, 1);
			}
			gridStore.loadData(gridData);
		};

		var onCategorySelect = function(dView, index, node, ev){
			Ext.getCmp('main_field').layout.setActiveItem(index);
			tabs.setActiveTab('target');
			typeStoreFrom.loadData(typeData);
			typeStoreTo.loadData(typeData);
			_activeMode = index;
			var _params;

			for (var k in activeContainers){
				delete that.containers[k];
			}

			if (index == 3) {

				activeContainers = {
						emailHolder: true
				};
				this.containers.emailHolder = emailHolder;

				if (eMail.getValue() != '')
					_urlSel = 'mailto:'.concat(eMail.getValue());
				towhat = 'tomail';
				isNR = false;
				gridData=[];
				gridStore.loadData(gridData);
			}
			else if (index == 2) {
				activeContainers = {
						webPageContainer: true
				};
				this.containers.webPageContainer = webPageHolder;
				_urlSel = newDocName.getValue();
				towhat = 'tourl';
				isNR = false;
			}
			else if (index == 1) {
				activeContainers = {
						placeInThisDoc: true
				};
				this.containers.placeInThisDoc = placeInThisDocHolder;

				if (!_pre) {
					_urlSel = firstNode.concat('!A1');
					// select first Node
					var ch = tree.getNodeById('cellref').findChild('text', firstNode);
					if (ch) tree.selectPath(ch.getPath());
				}
				towhat = 'tosel';
				typeStoreTo.removeAt(4);
				typeStoreTo.removeAt(3);
				validateTransfer();
			}
			else if (index == 0) {
				activeContainers = {
						browsePanel: true,
						browseTbar: true,
						refToFileCell: true
				};

				this.containers.refToFileCell = cellRefFld3Panel;
				this.containers.browsePanel = openDlg;
				this.containers.browseTbar = Ext.getCmp('browseToolbarHolder').getTopToolbar();
				// add for browser container too

				that.win.setHeight(580);
				towhat = 'towb';
				isNR = false;
				typeStoreTo.removeAt(4);
				typeStoreTo.removeAt(3);
				var data = openDlg.onInsertHyperlink(true) || {t: 'folder'};
				_params = {ftype: data.t};
				validateTransfer();
			}
			else if (index == 4) {
				activeContainers = {
						fromCellHolder: true
				};
				this.containers.fromCellHolder = fromCellHolder;
				that.win.setHeight(580);
				towhat = 'tocell';
				isNR = false;
			}
			gridData = [];

			handleComponents(_params);
		};

		// ### MAIN FIELD COMPONENTS ###

		var refSelData = [
		                  ['text', 'Text'.localize(), 'Plain text'],
		                  ['cref', 'Cell Reference'.localize(), 'Reference to a cell, or formula']];

		var refSelStore = new Ext.data.SimpleStore({
			fields: ['ref', 'desc', 'ttip'],
			data: refSelData
		});

		var refSelCombo = new Ext.form.ComboBox({
			id: 'wInsHyperlink_text_cmb',
			typeAhead: true,
			triggerAction: 'all',
			lazyRender: true,
			editable: false,
			value: 'Text',
			width: 120,
			hideLabel: true,
			store: refSelStore,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			displayField: 'desc',
			tabIndex: 10,
			listeners: {
			select: function (el, rec, index) {
			if (index==0) _txtSrc = 'string'; else _txtSrc = 'ref';
		}
		}
		});

		var refSelComboTip = new Ext.form.ComboBox({
			id: 'wInsHyperlink_tip_cmb',
			typeAhead: true,
			triggerAction: 'all',
			lazyRender: true,
			editable: false,
			value: 'Text',
			width: 120,
			hideLabel: true,
			store: refSelStore,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			displayField: 'desc',
			tabIndex: 12,
			listeners: {
			select: function (el, rec, index) {
			if (index==0) _tipSrc = 'string'; else _tipSrc = 'ref';
		}
		}
		});

		var cellReferenceField = new Ext.form.TextField({
			id: 'wInsHyperlink_specCell_txt',
			name: 'cell_reference',
			width: 415,
			fieldLabel: 'Text to display'.localize(),
			hideLabel: true,
			value: 'A1',
			enableKeyEvents: true,
			tabIndex: 22
		});

		var cellReferenceField2 = new Ext.form.TextField({
			id: 'wInsHyperlink_specCell2_txt',
			name: 'cell_reference2',
			width: 415,
			value: 'A1',
			hideLabel: true,
			tabIndex: 45,
			enableKeyEvents: true
		});

		var cellReferenceField3 = new Ext.form.TextField({
			id: 'wInsHyperlink_specCell3_txt',
			name: 'cell_reference3',
			width: 385,
			value: 'A1',
			tabIndex: 50,
			hideLabel: false,
			labelStyle: 'width: 210px; margin-top:10px;',
			fieldLabel: '_cell_sheet_reference'.localize(),
			style: 'margin-top: 10px;',
			enableKeyEvents: true
		});

		var cellRefFld3Panel = new Ext.Panel({
			id: 'crf3p',
			baseCls: 'x-plain',
			layout: 'form',
			border: false,
			frame: false,
			autoHeight: true,
			autoWidth: true,
			items: [cellReferenceField3]
		});

		cellReferenceField.on('keyup', function(){
			var tmpName = cellReferenceField.getValue();
			if (tree.getSelectionModel().getSelectedNode()){
				var activeNode = tree.getSelectionModel().getSelectedNode().text;
				_urlSel = ((activeNode)? activeNode : firstNode).concat('!', tmpName);
			}
		});

		var eMail = new Ext.form.TextField({
			name: 'e_mail',
			width: 415,
			fieldLabel: 'E-mail address'.localize(),
			hideLabel: true,
			tabIndex: 41,
			vtype: 'email',
			enableKeyEvents: true
		});

		eMail.on('keyup', function(){
			var tmpName = eMail.getValue();
			tmpName = 'mailto:'.concat(tmpName);
			if (mailSubject.getValue() != '')
				_urlSel = tmpName.concat('?subject=', mailSubject.getValue());
			else
				_urlSel = tmpName;
		});

		var mailSubject = new Ext.form.TextField({
			name: 'mail_subject',
			width: 415,
			tabIndex: 42,
			fieldLabel: 'Subject'.localize(),
			hideLabel: true,
			enableKeyEvents: true
		});

		mailSubject.on('keyup', function(){
			var tmpName = mailSubject.getValue();
			tmpName = '?subject='.concat(tmpName);
			if ((mailSubject.getValue() != '') && (eMail.getValue() != ''))
				_urlSel = 'mailto:'.concat(eMail.getValue(), '?subject=', mailSubject.getValue());
		});

		var newDocName = new Ext.form.TextField({
			name: 'document_name',
			width: 415,
			fieldLabel: 'Subject'.localize(),
			hideLabel: true,
			enableKeyEvents: true
		});

		newDocName.on('keyup', function(){
			var tmpName = newDocName.getValue();
			_urlSel = tmpName;
		});

		var editDocLater = new Ext.form.Radio({
			name: 'edit_doc',
			boxLabel: 'Edit the new document later'.localize(),
			hideLabel: true
		});

		var editDocNow = new Ext.form.Radio({
			name: 'edit_doc',
			boxLabel: 'Edit the new document now'.localize(),
			hideLabel: true
		});

		var treeNodes = new Ext.tree.AsyncTreeNode({
			children: [{
				text: 'Cell Reference'.localize(),
				expanded: true,
				id: 'cellref',
				children: cellRefChildren
			}, {
				text: 'Defined Names'.localize(),
				expanded: true,
				id: 'defname',
				children: definedNames
			}]
		});

		var SampleTreePanel = Ext.extend(Ext.tree.TreePanel, {
			width: 415,
			height: 123,
			loader: new Ext.tree.TreeLoader(),
			rootVisible: false,
			border: false,
			lines: true,
			id: 'wInsHyperlink_tree_tr',
			//tabIndex: 21, !tabIndexProblem
			autoScroll: true,
			singleExpand: false,
			useArrows: true,
			initComponent: function(){
			Ext.apply(this, {

				root: treeNodes
			})

			SampleTreePanel.superclass.initComponent.apply(this, arguments);
		}
		});
		Ext.reg('tree_panel', SampleTreePanel);


		// Instantiate the tree panel, then attach an event listener..
		var _tmpName;
		var _tmp;
		var tree = new SampleTreePanel();
		var _actNRScope;

		tree.on('click', function(node, e){
			if ((node.text == 'Cell Reference'.localize()) || (node.text == 'Defined Names'.localize())) {
				cellReferenceField.disable();
				isNR = false;
			}
			else
				if (node.id.charAt(0) == 'N') {
					_actNRScope = node.attributes.scope;
					cellReferenceField.disable();
					textToDisplay.setRawValue(node.text);
					isNR = true;
					_urlSel = node.text;

					// getting and setting link format
					_tmp = node.id.replace(/N_/i, "");
					_tmp = parseInt(_tmp);
					if (definedNamesStore[_tmp] != 'Workbook')
						_tmpName = definedNamesStore[_tmp].concat('!', node.text);
				}
				else {
					cellReferenceField.enable();
					firstNode = node.text;
					_urlSel = (node.text).concat('!', cellReferenceField.getValue());
					isNR = false;
				}
		}, this);

		var webaddress = new Ext.form.TextField({
			name: 'web_address',
			width: 415,
			tabIndex: 31,
			fieldLabel: 'Web Address'.localize(),
			hideLabel: true,
			enableKeyEvents: true
		});


		// ### END of MAIN FIELD COMPONENTS ###

		var placeInThisDocHolder = new Ext.Panel({
			// Place in this document
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 0px;',
	    	border: true,
	    	//id: 'placeInThisDoc',
	    	baseCls: 'x-plain',
	    	autoHeight: true,
	    	autoWidth: true,
	    	xtype: 'fieldset',
	    	id: 'thisDoc',
	    	layout: 'form',
	    	frame: false,
	    	items: [
				{
					html: 'Select a place in this document'.localize().concat(':'),
					baseCls: 'x-plain'
				},
				tree,
				{
					html: 'Type the cell reference'.localize().concat(':'),
					baseCls: 'x-plain',
					bodyStyle: 'margin-top: 10px;'
				},
				cellReferenceField
			]
	    });

		var webPageHolder = new Ext.Panel({ //	web page
	    	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 10px;',
	    	border: true,
	    	autoHeight: true,
	    	autowidth: true,
	    	xtype: 'fieldset',
	    	layout: 'form',
	    	baseCls: 'x-plain',
	    	id: 'webPage',
	    	frame: false,
	    	//title: 'Link to'.localize().concat(':'),
	    	items: [{
	    		html: 'Address'.localize().concat(':'),
	    		baseCls: 'x-plain'
	    	}, webaddress]
	    	});

		var emailHolder = new Ext.Panel({ //	email
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 10px;',
			border: true,
			autoHeight: true,
			autowidth: true,
			xtype: 'fieldset',
			id: 'eMail',
			layout: 'form',
			baseCls: 'x-plain',
			frame: false,
			//title: 'Link to'.localize().concat(':'),
			items: [{
				html: 'E-mail address'.localize().concat(':'),
				baseCls: 'x-plain'
			}, eMail, {
				html: 'Subject'.localize().concat(':'),
				baseCls: 'x-plain'
			}, mailSubject]
		});

		var fromCellHolder = new Ext.Panel({ // to from cell
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 10px;',
			border: true,
			autoHeight: true,
			autowidth: true,
			xtype: 'fieldset',
			baseCls: 'x-plain',
			layout: 'form',
			id: 'fromCell',
			frame: false,
			items: [{
				html: 'Type the cell reference'.localize().concat(':'),
				baseCls: 'x-plain'
			}, cellReferenceField2]
		});

		// ### MAIN FIELD ###
		var mainFields = new Ext.Panel({
			id: 'main_field',
			layout: 'card',
			deferredRender: true,
			//width: 750,
			baseCls: 'x-plain',
			bodyStyle: 'padding-left: 10px;',
			defaults: {
				bodyStyle: 'padding-top: 0px;'
			},
			border: false,
			activeItem: 0,
			items: [
		        { // open dlg
		        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 10px;',
		        	border: false,
		        	id: 'open-dlgss',
		        	layout: 'form',
		        	autoHeight: true,
		        	width: 605,
		        	frame: false,
		        	//labelWidth: 150,
		        	items: [
		        	        {
		        	        	border: true,
		        	        	id: 'open-dlg',
		        	        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; #margin-top: 0px;',
		        	        	height: 310,
		        	        	width: 600,
		        	        	layout: 'fit',
		        	        	frame: false,
		        	        	items: [openDlg]
		        	        },
		        	        cellRefFld3Panel
		        	        ]
		        },
		        placeInThisDocHolder,
		        	//{//	Create New Documents
		        	// bodyStyle: 'color: #000000; font-size: 9pt; background-color:
		        	// transparent; #margin-top: 10px;',
		        	// border: true,
		        	// autoHeight: true,
		        	// autowidth: true,
		        	// xtype: 'fieldset',
		        	// layout: 'form',
		        	// frame: false,
		        	// items: [
		        	// {html: 'Name of new document:', baseCls: 'x-plain'},
		        	// newDocName,
		        	// {html: '', bodyStyle: ' margin-bottom: 42px;', baseCls:
		        	// 'x-plain'},
		        	// {
		        	// bodyStyle: 'color: #000000; font-size: 9pt; background-color:
		        	// transparent;',
		        	// border: true,
		        	// autoHeight: true,
		        	// autowidth: true,
		        	// xtype: 'fieldset',
		        	// layout: 'form',
		        	// frame: false,
		        	// title: 'When to edit'.localize().concat(':'),
		        	// items: [
		        	// editDocLater,editDocNow
		        	// ]
		        	// }
		        	// ]
		        	// },
		        	webPageHolder,
		        	emailHolder,
		        	fromCellHolder]
		        });

		var navigation = [
		                  ['Existing File'.localize(), 'hl_file_web'],
		                  ['Place in This Document'.localize(), 'hl_place_this'],
		                  // ['Create New Document'.localize(), 'hl_create_new'], --------- Hidden until implementation
		                  ['Web page'.localize(), 'hl_file_web'],
		                  ['E-mail Address'.localize(), 'hl_email']
		                   ];

		var navigationStore = new Ext.data.SimpleStore({
			fields: ['description', 'image'],
			data: navigation
		});

		var navigationView = new Ext.DataView({
			id: 'wInsHyperlink_hlCat_dv',
			store: navigationStore,
			//tabIndex: 1, TODO: uncomment when extended in ExtJS
			tpl: new Ext.XTemplate(
					'<div class="hyperlink-navigation"><tpl for=".">','<div class="thumb-wrap">',
					'<div class="thumb" style="padding: 5px; text-align: center; font-size: 11px;"><img class="{image}" width="18" height="18" src="../lib/ext/resources/images/default/s.gif" /><br />{description}</div></div></tpl>'
//					,'<div style="margin: 0px; padding: 0px; font-size: 1px;"><img class="hl_nav_sep" width="134" height="1" src="../lib/ext/resources/images/default/s.gif" /></div>',
//					'<div class="thumb-wrap">',
//					'<div class="thumb" style="padding: 5px; text-align: center; font-size: 11px;"><img class="hl_place_this" width="18" height="18" src="../lib/ext/resources/images/default/s.gif" /><br />',
//					'From Cell'.localize(),'</div></div>'
					,'</div>'
					),
					autoHeight: true,
					multiSelect: false,
					singleSelect: true,
					overClass: 'x-view-over',
					itemSelector: 'div.thumb-wrap',
					emptyText: 'No images to display'.localize(),
					listeners: {
			click: {
			fn: onCategorySelect,
			scope: this
		}
		}
		});

		var textToDisplay = this.cmpFocus = new Ext.form.TextField({
			id: 'wInsHyperlink_textToDisplay_txt',
			name: 'text_to_display',
			width: 370,
			value: initCellValue,
			hideLabel: true,
			tabIndex: 11,
			blankText: 'This field is required'.localize(),
			fieldLabel: 'Text to display'.localize()
		});

		var screenTip = new Ext.form.TextField({
			id: 'wInsHyperlink_screenTip_txt',
			name: 'screen_tip',
			width: 370,
			tabIndex: 13,
			hideLabel: true,
			fieldLabel: 'Screen tip'.localize()
		});

		var textToDisplayHld = new Ext.Panel({
			id: 'txt_fld_holder',
			layout: 'column',
			baseCls: 'x-plain',
			bodyStyle: 'margin-top: 5px;',
			border: false,
			frame: false,
			items: [
			        // here be combobox, textfield
			        {
			        	//columnWidth: 0.17,
			        	width: 95,
			        	//xtype: 'fieldset',
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	style: 'text-align: right; margin-right: 10px;',
			        	frame: false,
			        	items: [{html: 'Text to display'.localize().concat(':'), baseCls: 'x-plain'}]
			        },
			        {
			        	//columnWidth: 0.21,
			        	//layout: 'form',
			        	width: 130,
			        	xtype: 'fieldset',
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	items: [refSelCombo]
			        },
			        {
			        	//columnWidth: 0.62,
			        	width: 370,
			        	layout: 'form',
			        	xtype: 'fieldset',
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	items: [textToDisplay]
			        }
			        ]
		});

		var screenTipHld = new Ext.Panel({
			id: 'tip_fld_holder',
			layout: 'column',
			baseCls: 'x-plain',
			bodyStyle: 'margin-top: 5px; display: inline;',
			border: false,
			frame: false,
			items: [
			        // here be combobox, textfield
			        {
			        	//columnWidth: 0.17,
			        	//xtype: 'fieldset',
			        	width: 95,
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	style: 'text-align: right; margin-right: 10px;',
			        	items: [{html: 'Screen tip'.localize().concat(':'), baseCls: 'x-plain'}]
			        },
			        {
			        	//columnWidth: 0.21,
			        	//layout: 195,
			        	width: 130,
			        	xtype: 'fieldset',
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	items: [refSelComboTip]
			        },
			        {
			        	//columnWidth: 0.62,
			        	layout: 'form',
			        	width: 370,
			        	xtype: 'fieldset',
			        	autoHeight: true,
			        	baseCls: 'x-plain',
			        	border: false,
			        	frame: false,
			        	items: [screenTip]
			        }
			        ]
		});

		var staticFields = this.containers.topPanel = new Ext.Panel({
			id: 'static_fields',
			bodyStyle: 'padding-left: 5px; color: #000000; font-size: 9pt; background-color: transparent; margin-bottom: 5px; margin-top: 5px;',
			border: false,
			frame: false,
			autoHeight: true,
			autoWidth: true,
			layout: 'form',
			items: [textToDisplayHld, screenTipHld]
		});

		// /////////////////////////////////////////////////////////////
		// TRANSFER TAB ///////////////////////////////////////////
		// /////////////////////////////////////////////////////////////

		var gridData = [
	//	                ['Selection', 'sel', 'range', 'Selection', 'sel', 'range'],
	//	                ['Named Range', 'sel', 'nrange', 'Selection', 'sel', 'range'],
	//	                ['Variable', 'sel', 'var', 'Selection', 'sel', 'range'],
	//	                ['Constant Value', 'sel', 'cval', 'Selection', 'sel', 'range'],
	//	                ['Constant List', 'sel', 'clist', 'Selection', 'sel', 'range']
		                ];

		var gridStore = new Ext.data.SimpleStore({
			fields: [
			         {name: 'seleFrom'},
			         {name: 'trFrom'},
			         {name: 'te'},
			         {name: 'seleTo'},
			         {name: 'trTo'},
			         {name: 'tf'}
			         ]
			         // ,sortInfo:{field:'ordNum', direction:'ASC'}
		});

		gridStore.loadData(gridData);

		var typeData = [
		                ['range', 'Selection'.localize()],
		                ['nrange', 'Named Range'.localize()],
		                ['var', 'Variable'.localize()],
		                ['cval', 'Constant Value'.localize()],
		                ['clist', 'Constant List'.localize()]
		                 ];

		var rowEditorTriggerClss = {
				'range': 'hl-triggerFld-shSel',
				'nrange': 'hl-triggerFld-namedRange',
				'var': 'hl-triggerFld-atVar',
				'clist': 'hl-triggerFld-cList',
				'cval': 'hl-triggerFld-cVal'
		}

		var typeStoreFrom = new Ext.data.SimpleStore({
			fields: ['type', 'name']
		});

		var typeStoreTo = new Ext.data.SimpleStore({
			fields: ['type', 'name']
		});

		typeStoreFrom.loadData(typeData);
		typeStoreTo.loadData(typeData);

		var _activeRow = 0;
		var _activeColumn = 0;


		var editor = new Ext.ux.grid.RowEditor({
	        saveText: 'Update'.localize(),
	        cancelText: 'Cancel'.localize(),
	        id: 'gridRowEditor',
	        listeners: {
				afteredit: function(el, changed){
					var ndat = grid.getSelectionModel().getSelected().data;
					////////////////
					var tmpArray = [ndat.seleFrom, ndat.trFrom, ndat.te, ndat.seleTo, ndat.trTo, ndat.tf];
					gridData[_activeRow] = tmpArray;
					gridStore.loadData(gridData);
		}
		}
	    });

		////////////////// TRANSFER GRID ! - Experimental

		var rColEdit = false;

		function displayTrigger(trigger, display){
			var trg = Ext.getCmp(trigger);
			var w = trg.wrap.getWidth();
			if (!display){
				trg.trigger.dom.style.display = 'none';
		        trg.el.setWidth(w-trg.trigger.getWidth());
			} else {
				// show trigger
				trg.trigger.dom.style.display = '';
		        trg.el.setWidth(w-17);
			}
		}

		var grid = new Ext.grid.GridPanel({
	        store: gridStore,
	        width: 600,
	        height: 350,
	        hideHeaders: true,
	        //region:'center',
	        //tabIndex: 90, TODO: uncomment when extended in ExtJS
	        ctCls: 'insertHyperlink-Grid',
			id: 'wInsHyperlink_transfer_grd',
	        clicksToEdit: 1,
	        autoExpandColumn: 'seleFrom',
	        plugins: [editor],
	        viewConfig: {
	            forceFit: true
			},
	        listeners: {
				rowclick: function(th, index, ev){
				},
				cellclick: function(grid, rowIndex, columnIndex, e) {

					_activeRow = rowIndex;
					_activeColumn = columnIndex;
				}
			},
	        columns: [
	        {
	            id: 'seleFrom',
	            header: "Transfer From".localize(),
	            dataIndex: 'seleFrom',
	            width: 100,
	            sortable: false,
	            editor: new Ext.form.ComboBox({
	            	id: 'wInsHyperlink_from_cmb',
	                editable: false,
	                triggerAction: 'all',
	                //transform: 'light',
	                store: typeStoreFrom,
	                mode: 'local',
					displayField: 'name',
	                lazyRender: true,
	                listClass: 'x-combo-list-small',
	                listeners: {
						select: function (el, rec, index) {
		            		grid.getSelectionModel().getSelected().data.te = typeData[index][0];
		            		var rEditor = Ext.getCmp('wInsHyperlink_transTrFrom_tfl');
		            		var stil = rowEditorTriggerClss[typeData[index][0]];
		            		rEditor.trigger.dom.innerHTML = "<img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ".concat(stil,"\"><img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ",stil,"\">");
		            		if (typeData[index][0] == 'cval') displayTrigger('wInsHyperlink_transTrFrom_tfl', false);
		            		else displayTrigger('wInsHyperlink_transTrFrom_tfl', true);
						}
					}
	            })
	        },{
	        	header: "Key".localize(),
	            id: 'trFrom',
	            dataIndex: 'trFrom',
	            width: 140,
	            sortable: false,
	            editor: new Ext.form.TriggerField({
	            	triggerClass: '',
	            	id: 'wInsHyperlink_transTrFrom_tfl',
	            	onTriggerClick : function(){
		            	// function for trigger click

		            	var stil = grid.getSelectionModel().getSelected().data.te;
		            	var tData = grid.getSelectionModel().getSelected().data;
		            	switch(stil){
		    			case 'range':
		    				//open range dlg
		    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
		    					fnc: [this, selSetRange]
		    					,format: '{Sheet}!{Range}'
		    					,rng: Ext.getCmp('wInsHyperlink_transTrFrom_tfl').getValue()
		    				}]);
		    				_wf = '';
		    				that.win.hide();
		    				break;
		    			case 'clist':
		    				// Constant list dlg
		    				var initArray = tData.trFrom.replace(/ /g, '').split(',').clean("");

		    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openConstListEditorWin, [initArray, 'wInsHyperlink_transTrFrom_tfl', 'wss']);

		    				break;
		    			case 'var':
		    				//
		    				var preselection = tData.trFrom;
		    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.hlVarList, [selSetVar, preselection]);
		    				break;
		    			case 'nrange':
		    				var presele = tData.trFrom;
		    				presele = presele.split('!');
		    				if (presele.length>1)
		    					presele = presele[1];
		    				else
		    					presele = presele[0];
		    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.nameManager, [genNRGrid, presele]);
		    				break;
		    			}
		            },
	            	triggerConfig: {
	                        tag: 'span',
	                        cls: 'hl-triggerFld-shSel',
	                        cn: [{
	                            tag: 'img',
	                            src: Ext.BLANK_IMAGE_URL,
	                            cls: 'x-form-trigger ' + this.triggerClass
	                        }, {
	                            tag: 'img',
	                            src: Ext.BLANK_IMAGE_URL,
	                            cls: 'x-form-trigger hl-triggerFld-shSel'
	                        }]
	                    },
	            listeners: {
	                    	beforeshow: function(ed){
	                    	var stil = rowEditorTriggerClss[grid.getSelectionModel().getSelected().data.te];
	                    	if (this.trigger) this.trigger.dom.innerHTML = "<img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ".concat(stil,"\"><img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ",stil,"\">");
	                    	this.triggerClass = stil;
	                    	this.triggerConfig = {
	                            tag: 'span',
	                            cls: stil,
	                            cn: [{
	                                tag: 'img',
	                                src: Ext.BLANK_IMAGE_URL,
	                                cls: 'x-form-trigger ' + this.triggerClass
	                            }, {
	                                tag: 'img',
	                                src: Ext.BLANK_IMAGE_URL,
	                                cls: 'x-form-trigger '.concat(stil)
	                            }]
	                        }
	                    	},
	                    	show: function(ed){
	                     		var st = grid.getSelectionModel().getSelected().data.te;
	                     		setTimeout(function(){if (st=='cval') displayTrigger('wInsHyperlink_transTrFrom_tfl', false); else displayTrigger('wInsHyperlink_transTrFrom_tfl', true);}, 1);
	                     	}
	                    }
	            })
	        },{
	            id: 'seleTo',
	            header: "Transfer to".localize(),
	            dataIndex: 'seleTo',
	            width: 100,
	            sortable: false,
	            editor: new Ext.form.ComboBox({
	            	id: 'wInsHyperlink_tfto_cmb',
	            	editable: false,
	                triggerAction: 'all',
	                //transform: 'light',
	                store: typeStoreTo,
	                mode: 'local',
					displayField: 'name',
	                lazyRender: true,
	                listClass: 'x-combo-list-small',
	                listeners: {
						select: function (el, rec, index) {
	            		grid.getSelectionModel().getSelected().data.tf = typeData[index][0];
	            		var rEditor = Ext.getCmp('wInsHyperlink_transTrTo_tfl');
	            		var stil = rowEditorTriggerClss[typeData[index][0]];
	            		rEditor.trigger.dom.innerHTML = "<img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ".concat(stil,"\"><img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ",stil,"\">");
	            		if (typeData[index][0] == 'cval') displayTrigger('wInsHyperlink_transTrTo_tfl', false);
	            		else if ((_activeMode==0) && (typeData[index][0]=='range' || typeData[index][0]=='nrange')) displayTrigger('wInsHyperlink_transTrTo_tfl', false);
	            		else displayTrigger('wInsHyperlink_transTrTo_tfl', true);
					}
					}
	            })
	        },
	        {
	            header: "Value".localize(),
	            id: 'trTo',
	            dataIndex: 'trTo',
	            width: 140,
	            sortable: false,
	            editor: new Ext.form.TriggerField({
	            	id: 'wInsHyperlink_transTrTo_tfl',
	            	onTriggerClick : function(){
	            	// function for trigger click
	            	var stil = grid.getSelectionModel().getSelected().data.tf;
	            	var tData = grid.getSelectionModel().getSelected().data;
	            	switch(stil){
	            	case 'range':
	    				if (_activeMode == 0) return;
	    				rColEdit = true;
	    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectRange, [{
	    					fnc: [this, selSetRange]
	    					,format: '{Sheet}!{Range}'
	    					,rng: Ext.getCmp('wInsHyperlink_transTrTo_tfl').getValue()
	    				}]);
	    				_wf = '';
	    				that.win.hide();
	    				break;
	            	case 'nrange':
	            		if (_activeMode == 0) return;
	    				var presele = tData.trTo;
	    				presele = presele.split('!');
	    				if (presele.length>1)
	    					presele = presele[1];
	    				else
	    					presele = presele[0];
	    				rColEdit = true;
	    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.nameManager, [genNRGrid, presele]);
	    				break;
	    			case 'clist':
	    				// Constant list dlg
	    				var initArray = tData.trFrom.replace(/ /g, '').split(',').clean("");

	    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openConstListEditorWin, [initArray, 'wInsHyperlink_transTrTo_tfl', 'wss']);

	    				break;
	    			case 'var':
	    				//
	    				var preselection = tData.trFrom;
	    				rColEdit = true;
	    				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.hlVarList, [selSetVar, preselection]);
	    				break;
	    			}
	            },
	            	triggerClass: 'hl-triggerFld-shSel', // rowEditorTriggerClss[grid.getSelectionModel().getSelected().data.tf]
	            	                                                         	triggerConfig: {
	            	                                                                     tag: 'span',
	            	                                                                     cls: 'hl-triggerFld-shSel',
	            	                                                                     cn: [{
	            	                                                                         tag: 'img',
	            	                                                                         src: Ext.BLANK_IMAGE_URL,
	            	                                                                         cls: 'x-form-trigger ' + this.triggerClass
	            	                                                                     }, {
	            	                                                                         tag: 'img',
	            	                                                                         src: Ext.BLANK_IMAGE_URL,
	            	                                                                         cls: 'x-form-trigger hl-triggerFld-shSel'
	            	                                                                     }]
	            	                                                                 },
	                 listeners: { beforeshow: function(ed){
	                         	var stil = rowEditorTriggerClss[grid.getSelectionModel().getSelected().data.tf];
	                        	if (this.trigger) this.trigger.dom.innerHTML = "<img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ".concat(stil,"\"><img src=\"/ui/lib/ext/resources/images/default/s.gif\" class=\"x-form-trigger ",stil,"\">");
	                         	this.triggerClass = stil;
	                         	this.triggerConfig = {
	                                 tag: 'span',
	                                 cls: stil,
	                                 cn: [{
	                                     tag: 'img',
	                                     src: Ext.BLANK_IMAGE_URL,
	                                     cls: 'x-form-trigger ' + this.triggerClass
	                                 }, {
	                                     tag: 'img',
	                                     src: Ext.BLANK_IMAGE_URL,
	                                     cls: 'x-form-trigger '.concat(stil)
	                                 }]
	                             }
	                         	},
	                         	show: function(ed){
	                         		var st = grid.getSelectionModel().getSelected().data.tf;
	                         		setTimeout(function(){if ((_activeMode==0) && (st=='range' || st=='nrange')) displayTrigger('wInsHyperlink_transTrTo_tfl', false); else displayTrigger('wInsHyperlink_transTrTo_tfl', true)}, 1);
	                         	}
	                         }
	                 })
	        }
	        ]
	    });

		///////////////////////////// E O Transfer Grid !~!!

		function genNRGrid(gpan, _pre){

			var nGrid = gpan;

			var nrWin = new Ext.Window({
				title: 'Named Range Selection'.localize(),
				closable: true,
				id: 'nrangeListSelWin',
				autoDestroy: true,
				plain: true,
				cls: 'default-format-window',
				constrain: true,
				modal: true,
				resizable: false,
				animCollapse: false,
				width: 500,
				height: 400,
				layout: 'fit',
				items: [nGrid],
				buttons: [{
					id: 'wNRangeSelWin_ok_btn',
					text: 'OK'.localize(),
					handler: function() {
					//// here set map

					var hp = nGrid.getSelectionModel().getSelected();
					var fld = (rColEdit) ? 'wInsHyperlink_transTrTo_tfl':'wInsHyperlink_transTrFrom_tfl';
					if (hp.data.scope != 'Workbook'.localize())
						Ext.getCmp(fld).setValue((hp.data.scope).concat('!',hp.data.name));
					else
						Ext.getCmp(fld).setValue(hp.data.name);
					Ext.getCmp('nrangeListSelWin').destroy();
				}
				},
				{
					id: 'wNRangeSelWin_cancel_btn',
					text: 'Cancel'.localize(),
					handler: function() {
					Ext.getCmp('nrangeListSelWin').destroy();
				}
				}]
			});
			// Ext.getCmp('main-details-view').setHeight(300);
			nrWin.show(this);
			if (_pre && _pre!=''){
				// preselection named ranges
				var store = nGrid.getStore();
				var ind = store.find('name', _pre);
				setTimeout(function(){nGrid.getSelectionModel().selectRow(ind);}, 1)
			}
		}

		function selSetRange(selected){
			that.win.show();
			setTimeout(function() {
				//selected = selected.replace(/=/i, "");
				if (rColEdit)
					Ext.getCmp('wInsHyperlink_transTrTo_tfl').setValue(selected);
				else
					Ext.getCmp('wInsHyperlink_transTrFrom_tfl').setValue(selected);
				rColEdit = false;
			}, 1);
		};

		function selSetVar(selVar){
			setTimeout(function(){
				if (rColEdit)
					Ext.getCmp('wInsHyperlink_transTrTo_tfl').setValue(selVar);
				else
					Ext.getCmp('wInsHyperlink_transTrFrom_tfl').setValue(selVar);
				rColEdit = false;
			}, 1)
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		var addBtn = new Ext.Button({
			id: 'wInsHyperlink_trAdd_btn',
			disabled: false,
			//style: 'display: inline;',
			ctCls: 'stdButtons',
			text: 'Add'.localize(),
			tabIndex: 91,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(b,e) {
			gridData.push(['Selection'.localize(), '', 'range', 'Selection'.localize(), '', 'range']);
			gridStore.loadData(gridData);
		}
		});

		var deleBtn = new Ext.Button({
			id: 'wInsHyperlink_trDel_btn',
			disabled: false,
			ctCls: 'stdButtons',
			tabIndex: 92,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			//style: 'display: inline; margin-left: 5px;',
			text: 'Delete'.localize(),
			handler: function(b,e) {
			gridData.splice(_activeRow,1);
			gridStore.loadData(gridData);
		}
		});

		var addDeleBtn = new Ext.Panel({
			id: 'tr_buttons',
			baseCls: 'x-plain',
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; padding-top: 0px;',
			border: false,
			frame: false,
			buttonAlign: 'left',
			fbar: new Ext.Toolbar({items:[addBtn, deleBtn]})
		});

		var gridTitleHolder = new Ext.Panel({
			id: 'gridTitleHolder',
			layout: 'column',
			baseCls: 'x-plain',
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; margin-top: 10px; margin-bottom: 5px;',
			border: false,
			frame: false,
			items: [{
				columnWidth: 0.48,
				layout: 'form',
				//bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; padding-top: 10px;',
				autoHeight: true,
				baseCls: 'x-plain',
				border: false,
				frame: false,
				items: [{baseCls: 'x-plain', html: 'Transfer From (Key)'.localize()}]
			},
			{
				columnWidth: 0.52,
				layout: 'form',
				//bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; padding-top: 10px;',
				autoHeight: true,
				baseCls: 'x-plain',
				border: false,
				frame: false,
				items: [{baseCls: 'x-plain', html: 'Transfer To (Key)'.localize()}]
			}]
		});

		var gridHolder = new Ext.Panel({
			id: 'grid_holder',
			baseCls: 'x-plain',
			border: false,
			frame: false,
			autoHeight: true,
			width: 600,
			items: [gridTitleHolder, grid, addDeleBtn]
		});

		// END OF TRANSFER TAB #######################################
		var prevTabState, prevContainers;
		// TABPANEL TABS
		var tabs = new Ext.TabPanel({
			id: 'wInsHyperlink_tabP_tbp',
			region: 'center',
			xtype: 'tabpanel',
			id: 'wInsHyperlink_tabP_tbp',
			layoutOnTabChange: true,
			activeTab: 0,
			ctCls: 'tb-no-bg',
			height: 450,
			baseCls: 'x-plain',
			bodyStyle: 'background-color: transparent; padding: 5px;',
			defaults: {
			autoScroll: false
		},
		items: [{
			id: 'target',
			title: 'Destination'.localize(),
			baseCls: 'x-plain',
			items: [staticFields, mainFields] // target (base) tab
		}, {
			id: 'transfer',
			title: 'Transfer'.localize(),
			baseCls: 'x-plain',
			items: [gridHolder] // transfer
		}],
		listeners: {
			tabchange: function(el, e)
			{
				if (e.id == 'transfer') {
					gridStore.loadData(gridData);
				}
			},
			beforetabchange: function(pan, newtab, oldtab){

				if (newtab.id == 'transfer'){
					prevContainers = {}; prevTabState = {};
					for (var k in activeContainers){
						prevTabState[k] = activeContainers[k];
						prevContainers[k] = that.containers[k];
						delete that.containers[k];
					}
					delete that.containers['topPanel'];
					that.containers.transferHandle = addDeleBtn.getFooterToolbar();
					activeContainers = {transferHandle: true}
				} else {
					if (prevContainers){
						delete that.containers['transferHandle'];
						that.containers = prevContainers;
						that.containers.topPanel = staticFields;
						activeContainers = prevTabState;

						prevContainers = false; prevTabState = false;
						}
				}
			}
		}
		});

		/* handler function for OK button */

		function handleHyperlink(){
			if (Ext.getCmp('gridRowEditor').isVisible()) Ext.getCmp('gridRowEditor').stopEditing(true);
			if (isNR) {
				var named_range = _urlSel;
				_urlSel = '';
			}
			else
				var named_range = '';
			var screenTipVal = screenTip.getValue();

			// set automatic screentip if empty

			var textVal = textToDisplay.getValue();

			// verify is there name!
			if (!textVal || textVal==''){
				// stop function
				Ext.Msg.show({
					title:'Hyperlink Error',
					msg: "_error: empty hl name".localize(),
					buttons: Ext.Msg.OK,
					fn: function() {textToDisplay.focus();},
					animEl: 'elId',
					width:320,
					icon: Ext.MessageBox.ERROR
				});
				return false;
			}

			var targ = targetECombo.getValue();
			if (!targetECombo.disabled && (!targ || targ=='')){
				// stop function
				Ext.Msg.show({
					title:'Hyperlink Error',
					msg: "_error: empty targ name".localize(),
					buttons: Ext.Msg.OK,
					fn: function() {targetECombo.focus();},
					animEl: 'elId',
					width:320,
					icon: Ext.MessageBox.ERROR
				});
				return false;
			}

			initCellValue = textToDisplay.getValue();
			switch(towhat){
			case 'towb':
				var ghn = openDlg.onInsertHyperlink();
				// if (!ghn) ghn = _pre.link.value.target.ghnt;
				if (!ghn) return;
				var lType;
				var lPath;
				var lSh = null;
				var cRef = cellReferenceField3.getValue();
				var lRng;

				cRef = cRef.split('!');
				if (cRef[1]) {lSh = cRef[0];
				cRef = cRef[1];} else
					cRef = cRef[0];

				if (isNR) {
					lRng = _urlSel;
					_urlSel = '';
				}
				else
					lRng = cRef;

				hldata.link = {
						type: 'obj',
						cnt: targ,
						value: {
					type: 'local',
					target: {
					path: ghn.p,
					sheet: lSh,
					range: lRng,
					ghnt: {
					g: ghn.g,
					h: ghn.h,
					n: ghn.n,
					t: ghn.t
				}
				}
				}
				}
				if (hldata.link.value.target.ghnt.t != 'workbook') {
					// delete sheet, range
					delete hldata.link.value.target['range'];
					delete hldata.link.value.target['sheet'];

				}
				break;
			case 'tourl':
				var trg = webaddress.getValue();
				hldata.link = {
						type: 'obj',
						cnt: targ,
						value:{
					type: 'url',
					target: trg
				}
				}
	//			if (!screenTipVal || screenTipVal=='') {
	//				screenTipVal = 'Webpage'.localize().concat(': ', trg);
	//			}
				break;
			case 'tomail':
				var trg = _urlSel;
				hldata.link = {
						type: 'obj',
						value:{
					type: 'url',
					target: trg
				}
				}
	//			if (!screenTipVal || screenTipVal=='') {
	//				screenTipVal = 'Mail Address'.localize().concat(': ', trg);
	//			}
				break;
			case 'tosel':
				var ts = _urlSel.split('!');
				if (isNR) {
					if (_actNRScope!='Workbook') var _ash=_actNRScope; else var _ash=null;
					hldata.link = {
							type: 'obj',
							cnt: targ,
							value: {
						type: 'local',
						target: {
						//type: 'wb',
						path: 'SELF',
						sheet: _ash,
						range: named_range
					}
					}
					};
	//				if (!screenTipVal || screenTipVal=='') {
	//					screenTipVal = 'Named Range'.localize().concat(': ', named_range);
	//				}
				} else {
					if (ts[1] == undefined)
						ts[1] = '';
					hldata.link = {
							type: 'obj',
							value: {
						type: 'local',
						target: {
						//type: 'wb',
						path: 'SELF',
						sheet: ts[0],
						range: ts[1]
					}
					}
					};
	//				if (!screenTipVal || screenTipVal=='') {
	//					screenTipVal = 'Selection Range'.localize().concat(': ', _urlSel);
	//				}
				}
					hldata.link.value.target.ghnt = null;

				break;
			case 'tocell':
				var cRef = cellReferenceField2.getValue();
				hldata.link = {
						type: 'ref',
						value: cRef
				}
	//			if (!screenTipVal || screenTipVal=='') {
	//				screenTipVal = 'Reference to Cell'.localize().concat(': ', cRef);
	//			}
				break;
			default:
				break;
			}

			// here setting of text, tip and trans attribs - same for every option!
			// check if string or reference
			hldata.text = {
					type: _txtSrc,
					value: textVal
			};

			hldata.tip = {
					type: _tipSrc,
					value: screenTipVal
			}

			//hldata.trans
			hldata.trans = [];
			for (var w=0; w<gridData.length; w++){
				var tobj = {
						src: {
					type: gridData[w][2],
					value: (gridData[w][2] == 'var')? '@'.concat(gridData[w][1].replace(/@/g, "")) : gridData[w][1]
				},
				dst: {
					type: gridData[w][5],
					value: (gridData[w][5] == 'var')? '@'.concat(gridData[w][4].replace(/@/g, "")) : gridData[w][4]
				}
				};
				if (tobj.src.value != '' && tobj.dst.value != '')
					hldata.trans.push(tobj);
				else {
					// check transfer tab
					Ext.Msg.show({
						title:'Hyperlink Error',
						msg: "One or more entries in Transfer tab are empty. Please check and edit values, or delete entry.",
						buttons: Ext.Msg.OK,
						fn: function() {},
						animEl: 'elId',
						width:320,
						icon: Ext.MessageBox.ERROR
					});
					return false;
				}
			}
			if (conf && conf.handlers && conf.handlers.set)
				conf.handlers.set.call(conf.handlers.scope, hldata);

			that.win.close();
		};

		/* end handler function */

		/*
		 * handle components function
		 */

		var handleComponents = function(params){
			// components to handle: Target panel, Cell/WS field, Transfer tab
			var type, VType, VSubType;
			// get conf obj
			switch(towhat){
			case 'towb':
				type = 'obj';
				VType = 'local';
				VSubType = params.ftype
				break;
			case 'tourl':
				type = 'obj';
				VType = 'url';
				VSubType = 'web'
				break;
			case 'tomail':
				type = 'obj';
				VType = 'url';
				VSubType = 'mail'
				break;
			case 'tosel':
				type = 'obj';
				VType = 'local';
				VSubType = 'self'
				break;
			case 'tocell':
				type = 'ref';
				break;
			default:
				break;
			}

			var gr = {
					lType: type,
					lVType: VType,
					lVSubType: VSubType
			}
			Jedox.wss.hl.getRules(gr);

			var enableCR = function(ena){
				if (ena) {
					cellReferenceField.enable();
					cellReferenceField2.enable();
					cellReferenceField3.enable();
				} else {
					cellReferenceField.disable();
					cellReferenceField2.disable();
					cellReferenceField3.disable();
				}
			}

			enableCR(gr.hasSel);
			(gr.hasTarg)? targetECombo.enable() : targetECombo.disable();
			(gr.hasTrans)? Ext.getCmp('transfer').enable() : Ext.getCmp('transfer').disable();

			targetECData = [];
			for (var l=0; l<gr.targets.length; l++){
				targetECData.push([gr.targets[l]]);
			}
			targetECDataStore.loadData(targetECData);
			if (!_pre) targetECombo.setValue(targetECData[0]);
		}

		// end of handleComponents

		/* *** TARGET PANEL *** */

		var targetECData = [];

		var targetECDataStore = new Ext.data.ArrayStore({
			fields: ['target'],
			data: targetECData
		});

		var targetECombo = new Ext.form.ComboBox({
			id: 'wInsHyperlink_target_cmb',
			typeAhead: true,
			triggerAction: 'all',
			lazyRender: true,
			editable: true,
			value: (_pre)? _pre.link.cnt : '',
			width: 135,
			hideLabel: true,
			store: targetECDataStore,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			mode: 'local',
			displayField: 'target',
			tabIndex: 2
		});

		/* END OF target panel */

		var navigationPanel = this.containers.navigationPanel = new Ext.Panel({
			//	right side of border tab - column start
			columnWidth: 0.20,
			layout: 'form',
			xtype: 'fieldset',
			bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; padding-top: 10px;',
			autoHeight: true,
			baseCls: 'x-plain',
			border: false,
			frame: false,
			items: [
			        {
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			    		border: true,
			    		autoHeight: true,
			    		//baseCls: 'x-title-f',
			    		xtype: 'fieldset',
			    		layout: 'form',
			    		frame: false,
			    		title: 'Link to'.localize().concat(':'),
			    		items: [navigationView]
			    	},
			    	{
			        	bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent;',
			    		border: true,
			    		autoHeight: true,
			    		//baseCls: 'x-title-f',
			    		xtype: 'fieldset',
			    		layout: 'form',
			    		frame: false,
			    		title: 'Target'.localize(),
			    		items: [
			    		        {
			    		        	baseCls: 'x-plain',
			    		        	html: 'Select target or <br />input frame name'.localize().concat(':'),
			    		        	bodyStyle: 'margin-bottom: 5px;'
			    		        },
			    		        targetECombo
			    		        ]
			    	}
			        ]
		});

		this.win = new Ext.Window({
			title: 'Insert Hyperlink'.localize(),
			closable: true,
			autoDestroy: true,
			id: 'wInsHyperlink_dlg_wnd',
			plain: true,
			constrain: true,
			modal: true,
			cls: 'default-format-window',
			resizable: false,
			animCollapse: false,
			width: 830,
			height: 580,
			autoHeight: true,
			onEsc: Ext.emptyFn,
			items: [new Ext.Panel({
				baseCls: 'x-title-f',
				labelWidth: 100,
				labelAlign: 'left',
				bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
				frame: false,
				header: false,
				monitorValid: true,
				autoScroll: false,
				autoHeight: true,
				autoWidth: true,
				items: [new Ext.Panel({
					id: 'hyperlink-window',
					layout: 'column',
					baseCls: 'x-plain',
					border: false,
					frame: false,
					items: [navigationPanel, {
						//	right side of border tab - column start
						columnWidth: 0.80,
						layout: 'form',
						xtype: 'fieldset',
						bodyStyle: 'color: #000000; font-size: 9pt; background-color: transparent; padding-left: 10px;',
						autoHeight: true,
						autoScroll: false,
						border: false,
						frame: false,
						//HERE MUST BE TAB PANEL
						items: [tabs]
					}]
				})]
			})],
			listeners: {
			close: function(){
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
				that.close();
				Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.openHL);
			},
			show:function(){
				setTimeout(function(){
					that.initFocus(true, 800);
				});
			},
			activate: function(win) {that.activate();}
		},
		buttons: [
			(this.components.OK = new Ext.Button({
				text: 'OK'.localize(),
				id: 'wInsHyperlink_ok_btn',
				tabIndex: 102,
				handler: function(){
					handleHyperlink();
				}
			})),
			(this.components.Cancel = new Ext.Button({
				text: 'Cancel'.localize(),
				id: 'wInsHyperlink_cancel_btn',
				tabIndex: 103,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					if (Ext.getCmp('gridRowEditor').isVisible()) Ext.getCmp('gridRowEditor').stopEditing(false);
					that.win.close();
				}
			}))
			]
		});

		this.setContext();
		this.win.show(this);

		this.containers.refToFileCell = cellRefFld3Panel;
		activeContainers = {
				browsePanel: true,
				browseTbar: true,
				refToFileCell: true
		};

		// here be setting of preselection
		if (_pre) {
			hldata = _pre;
			// preselection - tooltip
			screenTip.setValue(_pre.tip.value);
			textToDisplay.setValue(_pre.text.value);
			var _params = {ftype: 'folder'};

			if (_pre.tip.type=='ref')
				{refSelComboTip.setValue('Cell Reference'.localize());
				_tipSrc = 'ref';
				}
			else
				{refSelComboTip.setValue('Text'.localize());
				_tipSrc = 'string';
				}

			if (_pre.text.type=='ref')
				{refSelCombo.setValue('Cell Reference'.localize());
				_txtSrc = 'ref';
				}
			else
				{refSelCombo.setValue('Text'.localize());
				_txtSrc = 'string';
				}

			switch(_pre.link.type){
			case 'ref':
				_pre = false;
				hldata = {
						dyn: false,
						link:{},
						text:{},
						tip:{},
						trans:[]
				};
				navigationView.select(0);
				navigationView.fireEvent('click', this, 0);
//				navigationView.fireEvent('click', this, 4);
//				navigationView.select(4);
//				cellReferenceField2.setValue(_pre.link.value);
//				towhat = 'tocell';
				break;
			case 'obj':
				if (_pre.link.value.type == 'local'){
					// here object
					var wd = _pre.link.value.target;
					typeStoreTo.removeAt(4);
					typeStoreTo.removeAt(3);
					if (wd.ghnt == null){
						// here tosel
						navigationView.select(1);
						navigationView.fireEvent('click', this, 1);
						towhat = 'tosel';
						cellReferenceField.setValue(wd.range);
						_urlSel = (wd.sheet)? wd.sheet.concat('!',wd.range) : wd.range;
						var ch = tree.getNodeById('cellref').findChild('text', wd.sheet);
						if (!ch) ch = tree.getNodeById('defname').findChild('text', wd.range);
						if (ch)
							tree.selectPath(ch.getPath());
						else{
							// feedback - no sheet or named range
							Ext.Msg.show({
								   title:'Hyperlink Error'.localize(),
								   msg: '_hl_missing_target_sheet_nr'.localize(),
								   buttons: Ext.Msg.OK,
								   fn: function(btn){},
								   animEl: 'elId',
								   icon: Ext.MessageBox.ERROR
								});
						}

					} else {

						towhat = 'towb';
						var preghn = _pre.link.value.target.ghnt;
						_params = {ftype: preghn.t};
						navigationView.select(0);
						var myMask = new Ext.LoadMask(Ext.getBody(), {msg:"Please wait..."});
						myMask.show(); that.win.disable();
						openDlg.preselectPath({g: preghn.g, h: preghn.h, n: preghn.n});
						myMask.hide(); that.win.enable();
						if (_pre.link.value.target.sheet)
							cellReferenceField3.setValue(_pre.link.value.target.sheet.concat('!',_pre.link.value.target.range));
						else
							cellReferenceField3.setValue(_pre.link.value.target.range);
					}
				} else if (_pre.link.value.type == 'url') {
					var e = _pre.link.value.target.indexOf('@',0);
					if (e<0) {
						// webpage
						navigationView.fireEvent('click', this, 2);
						navigationView.select(2);
						towhat = 'tourl';
						webaddress.setValue(_pre.link.value.target);
					} else {
						// mail
						var rawmail = _pre.link.value.target.split(/[:?=]/);
						eMail.setValue(rawmail[1]);
						mailSubject.setValue(rawmail[3]);
						_urlSel = _pre.link.value.target;
						navigationView.fireEvent('click', this, 3);
						navigationView.select(3);
						towhat = 'tomail';
					}
				}
				break;
			}

			handleComponents(_params);

			// preselection of transfer
			if (_pre.trans.length > 0){
				gridData = [];
				var _types = {
						'range': 'Selection'.localize(),
						'nrange': 'Named Range'.localize(),
						'var': 'Variable'.localize(),
						'cval': 'Constant Value'.localize(),
						'clist': 'Constant List'.localize()
				};
				for (var e=0; e<_pre.trans.length; e++){
					if (_pre.trans[e].src.type == 'var') _pre.trans[e].src.value =  _pre.trans[e].src.value.replace(/@/g, "");
					if (_pre.trans[e].dst.type == 'var') _pre.trans[e].dst.value =  _pre.trans[e].dst.value.replace(/@/g, "");
					gridData.push([_types[_pre.trans[e].src.type], _pre.trans[e].src.value, _pre.trans[e].src.type, _types[_pre.trans[e].dst.type], _pre.trans[e].dst.value, _pre.trans[e].dst.type]);
					gridStore.loadData(gridData);

				}}
		} else {
			navigationView.select(0);
			typeStoreTo.removeAt(4);
			typeStoreTo.removeAt(3);
			handleComponents({ftype: 'folder'});
		}

	}
	}
)();

Jedox.util.extend(Jedox.wss.dlg.InsertHyperlink, Jedox.dlg.Dialog);