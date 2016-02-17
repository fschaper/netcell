/*
 * \brief preferences dialog
 *
 * \file Preferences.js
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * SVN: $Id: Preferences.js 5120 2011-07-18 08:37:46Z srdjanv $
 *
 */
Jedox.studio.dlg.openPreferences = function(level, name){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.dlg.Preferences(level, name));
};

Jedox.studio.dlg.Preferences = (function(){

	// class constructor
	return function (level, name) {

		Jedox.studio.dlg.Preferences.parent.constructor.call(this);

		this.id = 'Preferences';
		var that = this;


		var prefs_level = {
		  SERVER: 0
		, GROUP: 1
		, USER: 2
		};


		function onSuccessCbHandler(data){

				if (!data) {
					//show feedback
					return false;
				}

				init(data); //initialize
		}

		(new Jedox.backend.RPCAsyncRqst('Studio', 'getPrefs', [level, name]))
			.setOnSuccess([this, onSuccessCbHandler]).send();


	// ==========================================================================

		function init(data){

			var _nnS = '<not set>'.localize();
			var _nnID = 'nn';
			var _nnHFS = '&lt;not set&gt;'.localize();
			var _Pdata = data;
			var _data = getInterfaceData(data);
	//		var _data = data;

			var General = function(general){

				//flags for selecting first hierarchy in list after group is selected (not work on init)
				var preselectFirstResourcesHierarchy = false;
				var preselectFirstReportsHierarchy = false;


				var BRLbl = {
					html: '<br/>',
					baseCls: 'x-plain'
				};

				var localizationLbl = new Ext.form.Label({
					text: 'Localization'.localize(),
					cls:'preferences-title'
				});

				var environmentLbl = new Ext.form.Label({
					text: 'Environment'.localize(),
					cls:'preferences-title'
				});

				var languageCmb = new Ext.form.ComboBox({
					fieldLabel: 'Language'.localize(),
					tabIndex: 1,
					width: 180,
					store: new Ext.data.SimpleStore({
						data: [[_nnID, _nnHFS], ['en_US', 'English'.localize()], ['de_DE', 'Deutsch'.localize()], ['fr_FR', 'Francais'.localize()]],
						fields: [{
							name: 'id'
						}, {
							name: 'desc'
						}]
					}),
					valueField:'id',
					displayField: 'desc',
					value: general.i18n,
					editable: false,
					mode: 'local',
					triggerAction: 'all',
					listeners:{
						select: function(cmb, record, index) {
							if (this.value == _nnID)
								this.setValue(_nnS);
						}
					}
				});


				var themeCmb = new Ext.form.ComboBox({
					fieldLabel: 'Theme'.localize(),
					tabIndex: 2,
					width: 180,
					store: new Ext.data.SimpleStore({
						data: [[_nnID, _nnHFS], ['default', 'Blue (default)'], ['gray', 'Gray'.localize()], ['slate', 'Slate'.localize()]],
						fields: [{
							name: 'id'
						}, {
							name: 'desc'
						}]
					}),
					valueField:'id',
					displayField: 'desc',
					value: general.theme,
					editable: false,
					mode: 'local',
					triggerAction: 'all',
					listeners:{
						select: function(cmb, record, index) {
							if (this.value == _nnID)
								this.setValue(_nnS);
						}
					}
				});


				var languageThemePanel = new Ext.Panel({
	//				border:false,
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;',
						labelStyle:'font-size:11px;'
					},
					baseCls:'x-plain',
					layout:'form',
					labelWidth:60,
	//				width:250,
					autoWidth:true,
					autoHeight:true,
	//				height:50,
					x:20,
					y:25,
					items:[languageCmb, themeCmb]
				});


	//			var themePanel = new Ext.Panel({
	////				border:false,
	//				defaults: {
	//					bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;',
	//					labelStyle:'font-size:11px;'
	//				},
	//				baseCls:'x-plain',
	//				layout:'form',
	//				labelWidth:60,
	////				width:250,
	//				autoWidth:true,
	//				autoHeight:true,
	////				height:50,
	//				x:20,
	//				y:25,
	//				items:[themeCmb]
	//			});


				var environmentPanel = new Ext.Panel({
	//				border:false,
					layout: 'absolute',
					baseCls: 'x-plain',
					width:400,
					height:75,
					items:[environmentLbl, languageThemePanel]
				});



				var resourcesLbl = new Ext.form.Label({
					text: 'File Manager - Default Folder'.localize(),
					cls:'preferences-title',
					x:0,
					y:30
				});


				var resourcesGroupStore = new Ext.data.SimpleStore({
				    fields: ['id', 'name']
			    });


				var resourcesHierarchyStore = new Ext.data.SimpleStore({
				    fields: ['id', 'name']
			    });


				var resourcesGroupCmb = new Ext.form.ComboBox({
					fieldLabel: 'Group'.localize(),
					width: 180,
					tabIndex: 3,
					store:resourcesGroupStore,
					valueField:'id',
					displayField: 'name',
					value: general.resources.group,
					editable: false,
					mode: 'local',
					triggerAction: 'all',
					listeners: {
						select: function(cmb, record, index) {
							if (this.value == _nnID || this.value == _nnS){
								this.setValue(_nnS);
								resourcesHierarchyStore.removeAll();
								resourcesHierarchyCmb.setValue(_nnS);
							}
							else {
								function onSuccessCbHandler(result){
									initResourcesHierarchy();
								}

								(new Jedox.backend.RPCAsyncRqst('Studio', 'treeSetGroup', ['prefs_file', record.data.id]))
									.setOnSuccess([this, onSuccessCbHandler]).send();
							}
						}
					}
				});

				var resourcesHierarchyCmb = new Ext.form.ComboBox({
					fieldLabel: 'Hierarchy'.localize(),
					width: 180,
					store:resourcesHierarchyStore,
					tabIndex: 4,
					valueField:'id',
					displayField: 'name',
					value:findInStore(general.resources.hierarchy, resourcesHierarchyStore).index == 0? _nnS:general.resources.hierarchy,
					editable: false,
					mode: 'local',
					triggerAction: 'all'
				});


				var resourcesCmbPanel = new Ext.Panel({
	//				border:false,
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;',
						labelStyle:'font-size:11px;'
					},
					baseCls:'x-plain',
					layout:'form',
					labelWidth:60,
					autoWidth:true,
					autoHeight:true,
					x:20,
					y:55,
					items:[resourcesGroupCmb, resourcesHierarchyCmb]
				});


				var resourcesPanel = new Ext.Panel({
	//				border:false,
					layout: 'absolute',
					baseCls: 'x-plain',
					width:400,
					height:105,
					items:[resourcesLbl, resourcesCmbPanel]
				});



				// Appearance

				var navigationLbl = new Ext.form.Label({
					text: 'Palo Web - View'.localize(),
					cls:'preferences-title'
				});

				var usersViewLbl = new Ext.form.Label({
					text: 'User Manager - View'.localize(),
					cls:'preferences-title'
				});


			    var navigationChb = new Ext.form.Checkbox({
			        boxLabel: 'Show navigation on load'.localize(),
			        hideLabel: true,
			        tabIndex: 10,
			        checked: general.panel.visibility != "closed"
			    });

				var viewLbl = new Ext.form.Label({
					text: 'File Manager - View'.localize(),
					cls:'preferences-title'
				});


				var listRb=new Ext.form.Radio({
					boxLabel: 'List'.localize(),
					hideLabel: true,
					tabIndex: 11,
					checked:true,
					name: 'general-view',
					width:100,
					inputValue: 1
				});

				var iconsRb=new Ext.form.Radio({
					x:10,
					y:150,
					boxLabel: 'Icons'.localize(),
					hideLabel: true,
					tabIndex: 12,
					name: 'general-view',
					width:100,
					inputValue: 1
				});

				var detailsRb=new Ext.form.Radio({
					boxLabel: 'Details'.localize(),
					hideLabel: true,
					tabIndex: 13,
					name: 'general-view',
					width:100,
					inputValue: 1
				});



				var viewRbsContainer = {
					layout: 'table',
					baseCls: 'x-plain',
	//				columns: 2,
			        layoutConfig: {
			            // The total column count must be specified here
			            columns: 2
			        },
					items: [
						{html: '<img class="view-list-icon" src="../lib/ext/resources/images/default/s.gif" align="center" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								listRb
							]
						}),
						{html: '<img class="view-thumbnails-icon" align="center" src="../lib/ext/resources/images/default/s.gif" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								iconsRb
							]
						}),
						{html: '<img class="view-details-icon" align="center" src="../lib/ext/resources/images/default/s.gif" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								detailsRb
							]
						})
					],
					listeners:{
						afterrender:function(){

							if (general.view) {
								switch (general.view) {
									case 'list':
										listRb.setValue(true);
										break;
									case 'icons':
										iconsRb.setValue(true);
										break;
									case 'details':
										detailsRb.setValue(true);
										break;
								}
							}
						}
					}
				}




				var horizontalRb=new Ext.form.Radio({
					boxLabel: 'Horizontal'.localize(),
					hideLabel: true,
					checked:true,
					tabIndex: 15,
					name: 'users-general-view',
					width:100,
					inputValue: 1
				});

				var verticalRb=new Ext.form.Radio({
					x:10,
					y:150,
					tabIndex: 16,
					boxLabel: 'Vertical'.localize(),
					hideLabel: true,
					name: 'users-general-view',
					width:100,
					inputValue: 1
				});

				var tabbedRb=new Ext.form.Radio({
					boxLabel: 'Tabbed'.localize(),
					hideLabel: true,
					tabIndex: 17,
					name: 'users-general-view',
					width:100,
					inputValue: 1
				});


				var usersViewRbsContainer = {
					layout: 'table',
					baseCls: 'x-plain',
	//				columns: 2,
			        layoutConfig: {
			            // The total column count must be specified here
			            columns: 2
			        },
					items: [
						{html: '<img class="preview-bottom-icon" src="../lib/ext/resources/images/default/s.gif" align="center" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								horizontalRb
							]
						}),
						{html: '<img class="preview-right-icon" align="center" src="../lib/ext/resources/images/default/s.gif" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								verticalRb
							]
						}),
						{html: '<img class="preview-hide-icon" align="center" src="../lib/ext/resources/images/default/s.gif" width="16" height="16" />',baseCls: 'x-plain',width: 25},
						new Ext.Panel({
							border: false,
							layout: 'form',
							bodyStyle: 'background-color:transparent;',
							autoWidth: true,
							autoHeight: true,
							items: [
								tabbedRb
							]
						})
					],
					listeners:{
						afterrender:function(){

							if (general.users.layout) {
								switch (general.users.layout) {
									case 'horizontal':
										horizontalRb.setValue(true);
										break;
									case 'vertical':
										verticalRb.setValue(true);
										break;
									case 'tabbed':
										tabbedRb.setValue(true);
										break;
								}
							}
						}
					}
				}



				var viewPanel = new Ext.Panel({
					layout: 'form',
					baseCls: 'x-plain',
					width:400,
					height:120,
					items:[viewLbl, BRLbl, viewRbsContainer]
				});

				var usersViewPanel = new Ext.Panel({
					layout: 'form',
					baseCls: 'x-plain',
					width:400,
					height:120,
					items:[usersViewLbl, BRLbl, usersViewRbsContainer]
				});

				var navigationPanel = new Ext.Panel({
					layout: 'form',
					baseCls: 'x-plain',
					width:400,
					height:80,
					items:[navigationLbl, BRLbl, navigationChb]
				});




				// Update

				var updateLbl = new Ext.form.Label({
					text: 'Update'.localize(),
					cls:'preferences-title'
				});

			    var updateDescriptionLbl = {
			        html: 'chb_updt_desc'.localize(),
			        baseCls: 'x-plain'
			    };


			    var updateChb = new Ext.form.Checkbox({
			        boxLabel: 'Check for updates'.localize(),
			        hideLabel: true,
			        checked:general.updatecheck != "no",
			        tabIndex: 10,
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });


				var generalTabPanel = {
					title: 'Default'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl, environmentPanel, resourcesPanel]
				}

				var appearanceTabPanel = {
					title: 'Appearance'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl, navigationPanel, viewPanel, usersViewPanel]
				}

				var updateTabPanel = {
						title: 'Update'.localize(),
						layout: 'form',
						baseCls: 'x-plain',
						items: [BRLbl, /*updateLbl, BRLbl,*/ updateDescriptionLbl, BRLbl, updateChb]
					}


				var mainPanel = new Ext.TabPanel({
					height: 370,
					width: 330,
					deferredRender:false,
					baseCls: 'options-tab-panel',
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
					},
					activeTab: 0,
					items: [generalTabPanel, appearanceTabPanel, updateTabPanel],
					listeners: {
						tabchange: function(t, p){
							that.containers.activeView = p;
						}
					}
				});


				function init(){

					function initResourcesGroupSuccessClbFnc(){
						var result = findInStore(general.resources.group, resourcesGroupStore);

						if(result.index == 0 && result.record.data.id == _nnID){
							resourcesGroupCmb.setValue(_nnS);
							resourcesHierarchyCmb.setValue(_nnS);
						}
						else{
							resourcesGroupCmb.fireEvent('select', this, result.record, result.index);
							resourcesGroupCmb.setValue(result.record.get('id') == _nnID? _nnS:result.record.get('id'));
						}
					}

					function initResourcesGroupErrorClbFnc(){
							resourcesGroupCmb.fireEvent('select', this, result.record, result.index);
							resourcesGroupCmb.setValue(result.record.get('id') == _nnID? _nnS:result.record.get('id'));
					}


					initResourcesGroup(this, initResourcesGroupSuccessClbFnc, initResourcesGroupErrorClbFnc);

				}


				function findInStore(value, store){
					var index = store.find('id', value);
					if (index == -1)
						index = 0;
					var record = store.getAt(index);

					return ({
						record: record,
						index: index
					});
				}


				function initResourcesGroup(scope, successClbHandler, errorClbHandler){

					var gData = [];
					gData.push([_nnID, _nnHFS]);

					function onSuccessCbHandler(result){
						if (result == null)
							errorClbHandler.apply(scope);

						if (result instanceof Array){
							//no data
							errorClbHandler.apply(scope);
						}

						groupExist = true;
						for (var i in result)
							gData.push([i, result[i].name]);


						resourcesGroupStore.loadData(gData);
						successClbHandler.apply(scope);
					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngGroup', ['', 'listGroups', ['file']]))
						.setOnSuccess([this, onSuccessCbHandler]).send();

				}

				function initResourcesHierarchy(){
					var hData = [];

					function onSuccessCbHandler(result){
						if (!result){
							resourcesHierarchyStore.loadData(hData);
							resourcesHierarchyCmb.setValue('');
							return false;
						}

						if (result instanceof Array){
							//no data
							resourcesHierarchyCmb.setValue(_nnS);
							return false;
						}

						for (var i in result)
							hData.push([i, result[i].name]);

						resourcesHierarchyStore.loadData(hData);

						if (preselectFirstResourcesHierarchy)
							resourcesHierarchyCmb.setValue(hData[0][0]);
						else {
							preselectFirstResourcesHierarchy = true;
							resourcesHierarchyCmb.setValue(resourcesHierarchyStore.find('id', general.resources.hierarchy) == -1? _nnS:general.resources.hierarchy);
						}
					}

					(new Jedox.backend.RPCAsyncRqst('Studio', 'treeMngHierarchy', ['prefs_file', 'listHierarchies']))
						.setOnSuccess([this, onSuccessCbHandler]).send();

				}


				init();


				function getViewValue(){

					if(listRb.getValue())
						return 'list';

					if(iconsRb.getValue())
						return 'icons';

					if (detailsRb.getValue())
						return 'details';
				}


				function getUsersViewValue(){

					if(horizontalRb.getValue())
						return 'horizontal';

					if(verticalRb.getValue())
						return 'vertical';

					if (tabbedRb.getValue())
						return 'tabbed';
				}


				function getGeneralValue(){

					var resetHomePage = (level==prefs_level.GROUP && (reportsGroupCmb.getValue() != _data.general.reports.group || reportsHierarchyCmb.getValue() != _data.general.reports.hierarchy)); //home page is set on other place and there is no interface control on this dlg to set this props (only on group level)

					return {
						i18n:languageCmb.getValue(),
						theme:themeCmb.getValue(),
						resources:{group:resourcesGroupCmb.getValue(), hierarchy:resourcesHierarchyCmb.getValue()},
						reports:{
							group:_nnS,
							hierarchy:_nnS,
							node:_nnS,
							type:_nnS,
							path:_nnS
						},
						view:getViewValue(),
						users:{layout:getUsersViewValue()},
						panel:{visibility:navigationChb.getValue()? "open":"closed"},
						updatecheck:updateChb.getValue()
					};
				}

				function setGeneralValue(obj){

				}

				this.getPanel = function(){
					return mainPanel;
				}

				this.getValue = function(){
					return getGeneralValue();
				}

				this.setValue = function(obj){
					setGeneralValue(obj);
				}
			}


			var Studio = function(){


				var BRLbl = {
					html: '<br/>',
					baseCls: 'x-plain'
				};


				var studioTabPanel = {
					title: 'General'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl]
				}


				var mainPanel = new Ext.TabPanel({
					height: 400,
					width: 330,
					layoutOnTabChange: true,
					baseCls: 'options-tab-panel',
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
					},
					activeTab: 0,
					items: [studioTabPanel]
				});


				function getStudioValue(){

				}

				function setStudioValue(obj){

				}

				this.getPanel = function(){
					return mainPanel;
				}

				this.getValue = function(){
					return getStudioValue();
				}

				this.setValue = function(obj){
					setStudioValue(obj);
				}
			}


			var Wss = function(wss){


				var BRLbl = {
					html: '<br/>',
					baseCls: 'x-plain'
				};

				var environmentLbl = new Ext.form.Label({
					text: 'Environment'.localize(),
					cls:'preferences-title'
	//				x:0,
	//				y:30
				});


				var toolbarCmb = new Ext.form.ComboBox({
					fieldLabel: 'Toolbar'.localize(),
					width: 180,
					tabIndex: 20,
					store: new Ext.data.SimpleStore({
						data: [[_nnID, _nnHFS], ['toolbar', 'Toolbar'.localize()], ['ribbon', 'Ribbon'.localize()]],
						fields: [{
							name: 'id'
						}, {
							name: 'desc'
						}]
					}),
					valueField:'id',
					displayField: 'desc',
					value: wss.toolbar,
					editable: false,
					mode: 'local',
					triggerAction: 'all',
					listeners:{
						select: function(cmb, record, index) {
							if (this.value == _nnID)
								this.setValue(_nnS);
						}
					}
				});


				var designerModeLbl = new Ext.form.Label({
					text: 'Designer mode'.localize(),
					cls:'preferences-title'
				});

				var viewerModeLbl = new Ext.form.Label({
					text: 'Viewer mode'.localize(),
					cls:'preferences-title'
				});


			    var showToolbarDChb = new Ext.form.Checkbox({
			        boxLabel: 'Show toolbar on load'.localize(),
			        hideLabel: true,
			        tabIndex: 21,
			        checked: wss.designer.showToolbar != "no",
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });

			    var showFormulabarDChb = new Ext.form.Checkbox({
			        boxLabel: 'Show formula bar on load'.localize(),
			        hideLabel: true,
			        tabIndex: 22,
			        checked: wss.designer.showFormulabar != "no",
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });

			    var showStatusbarDChb = new Ext.form.Checkbox({
			        boxLabel: 'Show status bar on load'.localize(),
			        hideLabel: true,
			        tabIndex: 23,
			        checked: wss.designer.showStatusbar != "no",
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });


			    var showToolbarVChb = new Ext.form.Checkbox({
			        boxLabel: 'Show toolbar on load'.localize(),
			        hideLabel: true,
			        tabIndex: 25,
			        checked: wss.viewer.showToolbar != "no",
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });


			    var showStatusbarVChb = new Ext.form.Checkbox({
			        boxLabel: 'Show status bar on load'.localize(),
			        hideLabel: true,
			        tabIndex: 26,
			        checked: wss.viewer.showStatusbar != "no",
					getValue:function(){
						return this.checked? "yes":"no";
					}
			    });



				var designerModePanel = new Ext.Panel({
					layout: 'form',
					baseCls: 'x-plain',
					width:400,
					height:110,
					items:[designerModeLbl, BRLbl, showToolbarDChb, showFormulabarDChb, showStatusbarDChb]
				});

				var viewerModePanel = new Ext.Panel({
					layout: 'form',
					baseCls: 'x-plain',
					width:400,
					height:100,
					items:[viewerModeLbl, BRLbl, showToolbarVChb, showStatusbarVChb]
				});


				var wssCmbPanel = new Ext.Panel({
	//				border:false,
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;',
						labelStyle:'font-size:11px;'
					},
					baseCls:'x-plain',
					layout:'form',
					labelWidth:60,
					autoWidth:true,
					autoHeight:true,
					x:20,
					y:25,
					items:[toolbarCmb]
				});


				var wssPanel = new Ext.Panel({
	//				border:false,
					layout: 'absolute',
					baseCls: 'x-plain',
					width:400,
					height:60,
					items:[environmentLbl, wssCmbPanel]
				});


				var wssTabPanel = {
					title: 'Default'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl, wssPanel, designerModePanel, viewerModePanel]
				}


				var mainPanel = new Ext.TabPanel({
					height: 370,
					width: 330,
					layoutOnTabChange: true,
					baseCls: 'options-tab-panel',
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
					},
					activeTab: 0,
					items: [wssTabPanel]
				});


				function getWssValue(){
					return {toolbar:toolbarCmb.getValue(), designer:{showToolbar:showToolbarDChb.getValue(), showFormulabar:showFormulabarDChb.getValue(), showStatusbar:showStatusbarDChb.getValue()}, viewer:{showToolbar:showToolbarVChb.getValue(), showStatusbar:showStatusbarVChb.getValue()}};
				}

				function setWssValue(obj){

				}

				this.getPanel = function(){
					return mainPanel;
				}

				this.getValue = function(){
					return getWssValue();
				}

				this.setValue = function(obj){
					setWssValue(obj);
				}
			}



			var PaloOnline = function(paloOnlineData){


				var BRLbl = {
					html: '<br/>',
					baseCls: 'x-plain'
				};

				var helpLbl = new Ext.form.Label({
					text: 'Help'.localize(),
					cls:'preferences-title'
				});

			    var noteLbl = {
			        html: 'Enter your online Palo access data'.localize(),
			        baseCls: 'x-plain'
			    };

				var userNameTxf = new Ext.form.TextField({
					fieldLabel: 'User Name'.localize(),
					labelStyle: 'font-size:11px;',
					tabIndex: 30,
					cls: 'preview-properties-panel',
					name:'username',
					value:paloOnlineData.username,
					width: 200
				});


				var passwordTxf = new Ext.form.TextField({
					fieldLabel: 'Set password'.localize(),
					labelStyle: 'font-size:11px;',
					inputType: 'password',
					tabIndex: 31,
					cls: 'preview-properties-panel',
					name:'password',
					width: 200
				});


				var paloOnlineTabPanel = {
					title: 'General'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl, helpLbl, BRLbl, noteLbl, BRLbl, BRLbl, userNameTxf, passwordTxf]
				}


				var mainPanel = new Ext.TabPanel({
					height: 370,
					width: 330,
					layoutOnTabChange: true,
					baseCls: 'options-tab-panel',
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
					},
					activeTab: 0,
					items: [paloOnlineTabPanel]
				});


				function getPaloOnlineValue(){

					var name = userNameTxf.getValue() || _nnID;
					var pass = passwordTxf.getValue() || _nnID;

					if(pass == _nnID)
						if(paloOnlineData.password)
							pass = paloOnlineData.password
						else
							name = pass = _nnID;

					return {username:name, password:pass}
				}

				function setPaloOnlineValue(obj){

				}

				this.getPanel = function(){
					return mainPanel;
				}

				this.getValue = function(){
					return getPaloOnlineValue();
				}

				this.setValue = function(obj){
					setPaloOnlineValue(obj);
				}
			}


			var Etl = function(){


				var BRLbl = {
					html: '<br/>',
					baseCls: 'x-plain'
				};


				var etlTabPanel = {
					title: 'General'.localize(),
					layout: 'form',
					baseCls: 'x-plain',
					items: [BRLbl ]
				}


				var mainPanel = new Ext.TabPanel({
					height: 370,
					width: 330,
					layoutOnTabChange: true,
					baseCls: 'options-tab-panel',
					defaults: {
						bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
					},
					activeTab: 0,
					items: [etlTabPanel]
				});


				function getEtlValue(){

				}

				function setEtlValue(obj){

				}

				this.getPanel = function(){
					return mainPanel;
				}

				this.getValue = function(){
					return getEtlValue();
				}

				this.setValue = function(obj){
					setEtlValue(obj);
				}
			}

			// ==========================================================================



			var navigationMenuData = [['General'.localize(), 'prefs-general'], ['WSS'.localize(), 'prefs-wss'], ['Palo Online'.localize(), 'prefs-palo-online']] //, ['ETL'.localize(), 'res/img/dialog/chart/source_data_icon.png']]


			var navigationMenuStore = new Ext.data.SimpleStore({
				fields: ['label', 'icon'],
				data: navigationMenuData
			});



			var navigationMenuDV = new Ext.DataView({
				id: 'options-menu-navigation',
				store: navigationMenuStore,
				tpl: new Ext.XTemplate('<div class="options-menu-navigation" style="width: 99%;"><div class="charttypes">Type</div><tpl for=".">', '<div class="thumb-wrap">', '<div class="thumb"><img class="{icon}" src="../lib/ext/resources/images/default/s.gif"/>&nbsp;&nbsp;&nbsp;{label}</div></div>', '</tpl></div>'),
				multiSelect: false,
				singleSelect: true,
				overClass: 'x-view-over',
				itemSelector: 'div.thumb-wrap',
				listeners: {
					containerclick: function(dView, e){
						e.stopEvent();
						return false;
					},
					click: function(dataView, index, node, e){
						setNavigationView(index);
					}
				}
			});


			function getInterfaceData(data){

				var _Mdata = {
					'general':{
						'i18n':_nnS,
						'theme':_nnS,
						'updatecheck':_nnS,
						'resources':{
							'group':_nnS,
							'hierarchy':_nnS
						},
						'reports':{
							'group':_nnS,
							'hierarchy':_nnS,
							'node':_nnS,
							'type':_nnS,
							'path':_nnS
						},
						'view':_nnS,
						'panel':{
							'visibility':_nnS
						},
						'users':{
							'layout':_nnS
						}
					},
					'wss':{
						'toolbar':_nnS,
						'designer':{
							'showToolbar':_nnS,
							'showFormulabar':_nnS,
							'showStatusbar':_nnS
						},
						'viewer':{
							'showToolbar':_nnS,
							'showStatusbar':_nnS
						}

					},
					'mypalo':{
						'username':'',
						'password':''
					}
				}


				if (data){
					if (data.general){
						if (data.general.l10n)
							_Mdata.general.i18n = data.general.l10n;
						if (data.general.theme)
							_Mdata.general.theme = data.general.theme;
						if (data.general.updatecheck)
							_Mdata.general.updatecheck = data.general.updatecheck;
					}

					if (data.studio){
						if (data.studio['default']) {
							if (data.studio['default'].files) {
								_Mdata.general.resources.group = data.studio['default'].files.group;
								_Mdata.general.resources.hierarchy = data.studio['default'].files.hierarchy;
							}
							if (data.studio['default'].reports){
								_Mdata.general.reports.group = data.studio['default'].reports.group;
								_Mdata.general.reports.hierarchy = data.studio['default'].reports.hierarchy;

								if(level==prefs_level.GROUP && data.studio['default'].reports.node && data.studio['default'].reports.type && data.studio['default'].reports.path){
									_Mdata.general.reports.node = data.studio['default'].reports.node;
									_Mdata.general.reports.type = data.studio['default'].reports.type;
									_Mdata.general.reports.path = data.studio['default'].reports.path;
								}

							}
							if (data.studio['default'].view)
								_Mdata.general.view = data.studio['default'].view;

						}

						if (data.studio['panel'])
							if(data.studio['panel'].visibility)
								_Mdata.general.panel.visibility = data.studio['panel'].visibility;

						if (data.studio['users'])
							if (data.studio['users'].layout)
								_Mdata.general.users.layout = data.studio['users'].layout;

					}

					if (data.wss){
						if (data.wss['interface']){
							_Mdata.wss['toolbar'] = data.wss['interface'];
	 					}
						if (data.wss['designer']) {
							if (data.wss['designer']['toolbar'])
								_Mdata.wss['designer']['showToolbar'] = data.wss['designer']['toolbar'];
							if (data.wss['designer']['formulabar'])
								_Mdata.wss['designer']['showFormulabar'] = data.wss['designer']['formulabar'];
							if (data.wss['designer']['status'])
								_Mdata.wss['designer']['showStatusbar'] = data.wss['designer']['status'];
						}
						if (data.wss['viewer']) {
							if (data.wss['viewer']['toolbar'])
								_Mdata.wss['viewer']['showToolbar'] = data.wss['viewer']['toolbar'];
							if (data.wss['viewer']['status'])
								_Mdata.wss['viewer']['showStatusbar'] = data.wss['viewer']['status'];
						}

					}

					if (data.mypalo){
						_Mdata.mypalo['username'] = data.mypalo['username'];
						_Mdata.mypalo['password'] = data.mypalo['password'];
					}
				}

				return _Mdata;

			}


			function setNavigationView(index){
				mainPanel.items.items[1].layout.setActiveItem(index);
				that.containers.activeView = mainPanel.items.items[1].layout.activeItem.getActiveTab();
			}

			var navigationMenuPanel = {
				layout: 'fit',
				width: 130,
				height: 380,
				border: true,
				items: navigationMenuDV
			}



			var general = new General(_data.general);
	//		var studio = new Jedox.backend.rpc.Studio();
			var wss = new Wss(_data.wss);
			var paloOnline = new PaloOnline(_data.mypalo);
	//		var etl = new Etl();


			function getOptionsData(){

				var generalData = general.getValue();
				var wssData = wss.getValue();
				var mypaloData = paloOnline.getValue();

				var nnValue = {};
					nnValue[_nnID] = true;
					nnValue[_nnS] = true;

				var _Pdata = {};
				var tmplData = [
					['general/l10n', generalData['i18n']],
					['general/theme', generalData['theme']],
					['general/updatecheck', generalData['updatecheck']],
					['studio/default/files/group', generalData['resources']['group']],
					['studio/default/files/hierarchy', generalData['resources']['hierarchy']],
					['studio/default/reports/group', generalData['reports']['group']],
					['studio/default/reports/hierarchy', generalData['reports']['hierarchy']],
					['studio/default/reports/node', generalData['reports']['node']],
					['studio/default/reports/type', generalData['reports']['type']],
					['studio/default/reports/path', generalData['reports']['path']],
					['studio/default/view', generalData['view']],
					['studio/users/layout', generalData['users']['layout']],
					['studio/panel/visibility', generalData['panel']['visibility']],
					['wss/interface', wssData['toolbar']],
					['wss/designer/toolbar', wssData['designer']['showToolbar']],
					['wss/designer/formulabar', wssData['designer']['showFormulabar']],
					['wss/designer/status', wssData['designer']['showStatusbar']],
					['wss/viewer/toolbar', wssData['viewer']['showToolbar']],
					['wss/viewer/status', wssData['viewer']['showStatusbar']],
					['mypalo/username', mypaloData['username']],
					['mypalo/password', mypaloData['password']]
				];


				function clearNodes(nodes){
					for (var i = 0; i < nodes.length; i++) {
						delete _Pdata[nodes[i]];
					}
				}


				function addNodes(data){

					var path, value, obj, node;

					for (var i = 0; i < data.length; i++) {
						if (data[i][1] in nnValue)
							continue;

						path = data[i][0].split('/');
						value = data[i][1]
						obj = _Pdata;
						node = path.pop();

						for (var j=0; j<path.length; j++){
							if (!obj[path[j]])
								obj[path[j]] = {};

							obj = obj[path[j]];
						}

						obj[node] = value;
					}
				}

				clearNodes(['general', 'studio', 'wss', 'mypalo']);
				addNodes(tmplData);

				return _Pdata;
			}


			var aboutBtn = that.components.About = {
				text: 'About'.localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 100,
				handler: function ()
				{
					function cb (ver)
					{
						var msg = [ '<b>Palo Suite Release ', ver.rel, '</b><br />(', ver.os, ' ', ver.arch, ')<br /><br /><b>Frontend</b><br />Version: <b>', ver.rel ];

						if (ver.ui)
							msg.push('.', ver.ui[0], '</b><br />Date: ', ver.ui[1]);
						else
							msg.push('-dev</b>');

						msg.push('<br /><br />');

						if (ver.core)
							msg.push('<b>Backend</b><br />Version: <b>', ver.core[0], '</b><br />Date: ', ver.core[1], '<br />Build Date: ', ver.core[2], '<br /><br />');

						if (ver.palosrv || ver.libpalo)
						{
							msg.push('<b>Palo</b><br />');

							if (ver.palosrv)
								msg.push('Server Version: <b>', ver.palosrv, '</b><br />');

							if (ver.libpalo)
								msg.push('Client Library Version: <b>', ver.libpalo, '</b>');

							msg.push('<br /><br />');
						}

						if (ver.etlsrv || ver.etlcln)
						{
							msg.push('<b>ETL</b><br />');

							if (ver.etlsrv)
								msg.push('Server Version: <b>', ver.etlsrv, '</b><br />');

							if (ver.etlcln)
								msg.push('Web Client Version: <b>', ver.etlcln, '</b><br />');
						}

						msg = msg.join('');

						var aboutPanel = { bodyStyle: 'padding:20px', html: msg, border: false };

						var aboutWin = new Ext.Window({
						  id: 'about-dlg'
						, title: 'About Palo Suite'.localize()
						, closable: true
						, closeAction: 'close'
						, autoDestroy: true
						, plain: true
						, modal: true
						, constrain: true
						, resizable: false
						, animCollapse: false
						, layout: 'fit'
						, width: 270
						, height: 360
						, items: aboutPanel
						, buttonAlign: 'center'
						, buttons: [ { text: 'OK'.localize(), handler: function () { aboutWin.close(); } } ]
						});

						aboutWin.show();
					}

					Jedox.backend.rpc([ this, cb ], 'verinfo', 'get');
				}
			}

			function isEmpty(object) {
				for(var i in object) { return true; }
					return false;
			}


			var okBtn = that.components.OK = {
				text: 'OK'.localize(),
				tabIndex: 101,
				handler: function(){

					var d = getOptionsData();

					that.win.close();

					var theme = false;

					if (!name) {
						if (d) {
							if (d.general)
								if (d.general.theme)
									theme = d.general.theme;
						}
						if (theme) {
							Ext.util.CSS.swapStyleSheet('theme', '../lib/ext/resources/css/xtheme-'.concat(theme, '.css'));
							//Ext.util.CSS.swapStyleSheet('themeFix', '../lib/ext/resources/css/xtheme-fix-'.concat(theme, '.css'));
							if (Jedox.studio.frames.files){
								Jedox.studio.frames.files.Ext.util.CSS.swapStyleSheet('theme', '../lib/ext/resources/css/xtheme-'.concat(theme, '.css'));
								//Jedox.studio.frames.files.Ext.util.CSS.swapStyleSheet('themeFix', '../lib/ext/resources/css/xtheme-fix-'.concat(theme, '.css'));
							}
							if (Jedox.studio.frames.reports){
								Jedox.studio.frames.reports.Ext.util.CSS.swapStyleSheet('theme', '../lib/ext/resources/css/xtheme-'.concat(theme, '.css'));
								//Jedox.studio.frames.reports.Ext.util.CSS.swapStyleSheet('themeFix', '../lib/ext/resources/css/xtheme-fix-'.concat(theme, '.css'));
							}
						}


						var helpBtn = Ext.getCmp('ps-help-btn');

						if (d.mypalo && d.mypalo.username && d.mypalo.password)
						{
							Jedox.studio.app.myPalo = { username: d.mypalo.username, password: d.mypalo.password };

							helpBtn.enable();
							helpBtn.setTooltip('Help'.localize());
						}
						else
						{
							delete Jedox.studio.app.myPalo;

							helpBtn.disable();
							helpBtn.setTooltip('nregmsg'.localize());
						}


						var url = '/be/studio/prefs.php';
	//					var params = Ext.util.JSON.encode({general: general.getValue(), wss: wss.getValue()});
						var params = Ext.util.JSON.encode(d);

						var xhttp = new XMLHttpRequest();
						xhttp.open("POST", url, true);
						xhttp.setRequestHeader("Content-length", params.length);

						xhttp.send(params);
					}
					else {
						(new Jedox.backend.RPCAsyncRqst('Studio', 'setPrefs', [level, name, d])).send();
					}
				}
			}

			var cancelBtn = that.components.Cancel = {
				text: 'Cancel'.localize(),
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 102,
				handler: function(){
					that.win.close();
				}
			}


			var mainPanel = new Ext.Panel({
				layout: 'absolute',
				baseCls: 'x-plain',
				border: false,
				items: [{
					//title: 'navigation panel',
					layout: 'column',
					border: false,
					baseCls: 'x-plain',
					x: 0,
					y: 0,
					items: [navigationMenuPanel]
				}, {
					//title: 'view panel',
					layout: 'card',
					baseCls: 'x-plain',
					border: false,
					width: 448,
					height: 380,
					activeItem: 0,
					x: 140,
					y: 0,
					items: [general.getPanel(), wss.getPanel(), paloOnline.getPanel()]
				}]
			});


			that.win = new Ext.Window({
				id: 'options-dlg',
				title: 'Options'.localize(),
				closable: true,
				closeAction: 'close',
				autoDestroy: true,
				plain: true,
				modal: true,
				constrain:true,
				animate: false,
				onEsc: Ext.emptyFn,
				resizable: false,
				animCollapse: false,
				layout: 'fit',
				width: 605,
				buttonAlign: 'left',
				height: 455,
				items: [mainPanel],
				listeners:{
					close:function(){
						function onSuccessCbHandler(result){
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openPreferences);
						}

						(new Jedox.backend.RPCAsyncRqst('Studio', 'removeUserPrefGroupsFromSession'))
							.setOnSuccess([this, onSuccessCbHandler]).send();
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 300);
						});
					},
					activate: function(win) {that.activate();}
				},
				buttons: [
				          aboutBtn,
				          '->',
				          okBtn,
				          cancelBtn
				          ]
			});



			that.setContext();
			that.win.show(that);

			navigationMenuDV.select(0, false, false);
		}

	};
}
)();

Jedox.util.extend(Jedox.studio.dlg.Preferences, Jedox.dlg.Dialog);