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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: Properties.js 5095 2011-07-06 12:08:18Z mladent $
 *
 */
Jedox.studio.dlg.openProperties = function(type, data, renameHandleFnc, refreshHandleFnc){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.dlg.Properties(type, data, renameHandleFnc, refreshHandleFnc));
};

Jedox.studio.dlg.Properties = (function(){

	// class constructor
	return function (type, data, renameHandleFnc, refreshHandleFnc) {

		Jedox.studio.dlg.Properties.parent.constructor.call(this);

		this.id = 'Properties';
		var that = this;


	    Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
	    Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

	    var referrersDataTypeFlag = false;
		var resourcesDataTypeFlag = false;

		var _urlPluginParamsChangedFlag = false;
		var _urlParamsTab;

		var _resourcesObj;
		var _securityObj;
		var _framesetObj;

		var _listDateFormat = 'd.m.Y H:i:s';

	    var iconImg = {
	        html: 'Image'.localize(),
	        baseCls: 'x-plain'
	    }


	    var nameTxf = new Ext.form.TextField({
	        hideLabel: true,
	        tabIndex: 1,
	        allowBlank: false,
	        width: 260
	    });

	    var descriptionLbl = new Ext.form.Label({
	        text: 'Description'.localize().concat(':'),
	        hidden: true
	    });

	    var descriptionTxa = new Ext.form.TextArea({
	        hideLabel: true,
	        hidden: true,
	        tabIndex: 2,
	        width: 260
	    });



	    var splitLine = {
	        html: '<br><br>',
	        baseCls: 'split-line',
	        width: 350
	    };

	    var typeLbl = new Ext.form.Label({
	        text: 'Type'.localize().concat(':')
	    });

	    var typeVal = new Ext.form.Label({
	        text: ''
	    });

	    var locationLbl = new Ext.form.Label({
	        text: 'Location'.localize().concat(':')
	    });

	    var locationVal = new Ext.form.Label({
	        text: ''
	    });


	    var urlLbl = new Ext.form.Label({
	        text: 'URL target'.localize().concat(':'),
	        hidden: true
	    });

	    var urlTxf = new Ext.form.TextField({
	        hideLabel: true,
	        hidden: true,
	        tabIndex: 10,
	        allowBlank: false,
	        width: 180
	    });

	    var urlPanel = {
	        layout: 'column',
	        border: false,
	        baseCls: 'x-plain',
	        width: 300,
	        height: 25,
	        hidden: true,
	        items: [{
	            layout: 'form',
	            border: false,
	            baseCls: 'top-left-bottom-panel',
	            width: 183,
	            items: urlTxf
	        }, {
	            //title:'panel za toolbar',
	            border: false,
	            baseCls: 'toolbar-panel',
	            width: 100,
	            height: 25,
	            tbar: [{
	                tooltip: {
	                    title: 'Select'.localize(),
	                    text: 'Select URL'.localize()
	                },
	                //				iconCls: 'folder-up-icon',
	                text: 'Select URL'.localize(),
	                handler: function(){
	                    urlTxf.focus(true);
	                },
	                scope: this
	            }, {
	                tooltip: {
	                    title: 'Mail'.localize(),
	                    text: 'Send link to mail'.localize().concat('...')
	                },
	                iconCls: 'mail-link-icon',
	                handler: function(){
	                    var email = "Enter destination e-mail".localize().concat('...');
	                    var subject = "Link to".localize().concat('...');
	                    var body_message = urlTxf.getValue();
	                    var mailto_link = 'mailto:' + email + '?subject=' + subject + '&body=' + body_message;

						var win = window.open(mailto_link, 'emailWindow');
						if (win && win.open &&!win.closed) win.close();
	                },
	                scope: this
	            }]
	        }]
	    }


	    var locationTxf = new Ext.form.TextField({
	        hideLabel: true,
	        tabIndex: 11,
	        allowBlank: false,
	        width: 260
	    });

	    var locationCmp = locationVal;

	    var sizeLbl = new Ext.form.Label({
	        text: 'Size'.localize().concat(':'),
			hidden:true
	    });

	    var sizeVal = new Ext.form.Label({
	        text: '',
			hidden:true
	    });

	    var sizeOnDiskLbl = new Ext.form.Label({
	        text: 'Size on disk'.localize().concat(':'),
			hidden:true
	    });

	    var sizeOnDiskVal = new Ext.form.Label({
	        text: '',
			hidden:true
	    });

	    var createdLbl = new Ext.form.Label({
	        text: 'Created'.localize().concat(':'),
			hidden:true
	    });

	    var createdVal = new Ext.form.Label({
	        text: 'dd/mm/yyyy',
			hidden:true
	    });

	    var modifiedLbl = new Ext.form.Label({
	        text: 'Modified'.localize().concat(':'),
			hidden:true
	    });

	    var modifiedVal = new Ext.form.Label({
	        text: 'dd/mm/yyyy',
			hidden:true
	    });

	    var accessedLbl = new Ext.form.Label({
	        text: 'Accessed'.localize().concat(':'),
			hidden:true
	    });

	    var accessedVal = new Ext.form.Label({
	        text: 'dd/mm/yyyy',
			hidden:true
	    });

	    initIcon(data);

	    var generalPanel = new Ext.Panel({
	        layout: 'table',
	        bodyStyle: 'background-color: transparent;',
	        border: false,
	        defaults: {
	            bodyStyle: 'background-color: transparent;',
	            bodyStyle: 'padding:5px',
	            baseCls: 'x-plain'
	        },
	        layoutConfig: {
	            // The total column count must be specified here
	            columns: 3
	        },
	        items: [{
	            rowspan: 1,
	            items: iconImg
	        }, {
	            colspan: 2,
	            items: nameTxf
	        }, {
	            rowspan: 1,
	            items: descriptionLbl
	        }, {
	            colspan: 2,
	            items: descriptionTxa
	        }, {
	            colspan: 3,
	            bodyStyle: 'padding:2px',
	            items: splitLine
	        }, {
	            rowspan: 1,
	            items: typeLbl
	        }, {
	            colspan: 2,
	            items: typeVal
	        }, {
	            rowspan: 1,
	            items: locationLbl
	        }, {
	            colspan: 2,
	            items: locationCmp
	        }, {
	            rowspan: 1,
	            items: urlLbl
	            //	    },{
	            //	        colspan: 2,
	            //			items:urlTxf
	            //	    },{
	        }, {
	            colspan: 2,
	            items: urlPanel
	        }, {
	            rowspan: 1,
	            items: sizeLbl
	        }, {
	            colspan: 2,
	            items: sizeVal
	        }, {
	            rowspan: 1,
	            items: sizeOnDiskLbl
	        }, {
	            colspan: 2,
	            items: sizeOnDiskVal
	        }, {
	            colspan: 3,
	            bodyStyle: 'padding:2px',
	            items: splitLine
	        }, {
	            rowspan: 1,
	            items: createdLbl
	        }, {
	            colspan: 2,
	            items: createdVal
	        }, {
	            rowspan: 1,
	            items: modifiedLbl
	        }, {
	            colspan: 2,
	            items: modifiedVal
	        }, {
	            rowspan: 1,
	            items: accessedLbl
	        }, {
	            colspan: 2,
	            items: accessedVal
	        }]
	    });


	    //================================ Link Components =============================================

		var reportsConf = {
			sendToMailBtn:false,
			credentialsCmps:false,
			stf:false
		}

		var staticConf = {
			sendToMailBtn:true,
			credentialsCmps:true,
			stf:true
		}

		var objConf = type === 'qreport'? reportsConf:staticConf;

	    var urlLbl = new Ext.form.Label({
	        text: 'URL target'.localize().concat(':')
	    });

	    var urlTxa = new Ext.form.TextArea({
	        hideLabel: true,
	        width: 350,
	        tabIndex: 20,
	        height: 65,
	        columns: 20,
	        rows: 20,
	        preventScrollbars: true
	    });

	    //	var noteLbl = new Ext.form.Label({
	    //		text:'Note: Copy into clipboard is possible with Ctrl + C keyboard shortcut'.localize()
	    //	});

	    var noteLbl = {
	        html: 'Note: Copy into clipboard is possible with <b>ctrl + c</b> keyboard shortcut'.localize(),
	        width:350,
			baseCls: 'x-plain'
	    };

	    var inProjectRb = new Ext.form.Radio({
	        boxLabel: 'In project'.localize(),
	        hideLabel: true,
	        checked: true,
	        tabIndex: 23,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        name: 'mode',
	        width: 300,
	        handler: function(){
	            if (this.getValue()) {
					preselectChb.show();
					getWSSURL();
				}
	        },
	        inputValue: 1
	    });

	    var standaloneRb = new Ext.form.Radio({
	        boxLabel: 'Standalone'.localize(),
	        hideLabel: true,
	        checked: false,
	        tabIndex: 24,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        name: 'mode',
	        width: 300,
	        handler: function(){
	            if (this.getValue()) {
					preselectChb.hide();
					getWSSURL();
				}
	        },
	        inputValue: 1
	    });


	    var preselectChb = new Ext.form.Checkbox({
	        boxLabel: 'Preselect in tree'.localize(),
	        hideLabel: true,
	        tabIndex: 25,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        checked: false,
	        handler: function(){
				getWSSURL(credentialsChb.getValue()? (currentUserRb.getValue()? 1:2):0);
	        }
	    });

	    var showToolbarVChb = new Ext.form.Checkbox({
	        boxLabel: 'Show toolbar on load'.localize(),
	        hideLabel: true,
	        tabIndex: 26,
	        checked: true,
			getValue:function(){
				return this.checked? "yes":"no";
			},
	        handler: function(){
				getWSSURL(credentialsChb.getValue()? (currentUserRb.getValue()? 1:2):0);
	        }
	    });


	    var showStatusbarVChb = new Ext.form.Checkbox({
	        boxLabel: 'Show status bar on load'.localize(),
	        hideLabel: true,
	        tabIndex: 27,
	        checked: true,
			getValue:function(){
				return this.checked? "yes":"no";
			},
	        handler: function(){
				getWSSURL(credentialsChb.getValue()? (currentUserRb.getValue()? 1:2):0);
	        }
	    });

	    var credentialsChb = new Ext.form.Checkbox({
	        boxLabel: 'Include credentials'.localize(),
	        hideLabel: true,
	        tabIndex: 28,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        checked: false,
	        handler: function(){
	            if (this.getValue()) {
	                currentUserRb.show();
	                currentUserRb.setValue(true);
	                otherUserRb.show();
	                otherUserRb.setValue(false);
	            }
	            else {
	                currentUserRb.setValue(false);
	                otherUserRb.setValue(false);
	                currentUserRb.hide();
	                otherUserRb.hide();

					getWSSURL();
	            }
	        }
	    });

	    var currentUserRb = new Ext.form.Radio({
	        boxLabel: 'Current user'.localize(),
	        hideLabel: true,
	        checked: false,
	        tabIndex: 30,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        name: 'credentials',
			autoWidth:true,
	        handler: function(){
	            if (this.getValue())
	                getWSSURL(1);
	        },
	        inputValue: 1
	    });

	    var otherUserRb = new Ext.form.Radio({
	        boxLabel: 'Other user'.localize(),
	        hideLabel: true,
	        checked: false,
	        tabIndex: 29,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        name: 'credentials',
			autoWidth:true,
	        handler: function(){
	            if (this.getValue()) {
	                credentialsPanel.items.items[credentialsPanel.items.items.length - 1].show();
					credentialsPanel.items.items[credentialsPanel.items.items.length - 2].show();
	            }
	            else {
	                credentialsPanel.items.items[credentialsPanel.items.items.length - 1].hide();
					credentialsPanel.items.items[credentialsPanel.items.items.length - 2].hide();
	            }
	        },
	        inputValue: 1
	    });

	    var userTxf = new Ext.form.TextField({
	        fieldLabel: 'User name'.localize(),
	        tabIndex: 31,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        width: 100
	    });

	    var passTxf = new Ext.form.TextField({
	        fieldLabel: 'Password'.localize(),
	        tabIndex: 32,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        width: 100
	    });

	    var credentialsBtns = new Ext.Toolbar({
	    	buttons:[
				'->',
				new Ext.Button({
				    text: 'Select URL'.localize(),
				    tabIndex: 21,
				    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				    handler: function(){
				        urlTxa.focus(true);
				    }
				}), new Ext.Button({
				    text: 'Send to mail'.localize(),
				    tabIndex: 22,
				    ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					hidden:objConf.sendToMailBtn,
				    handler: function(){
				        var email = "Enter destination e-mail".localize().concat('...');
				        var subject = "Link to".localize().concat('...');
				        var body_message = urlTxa.getValue();
				        var mailto_link = 'mailto:' + email + '?subject=' + subject + '&body=' + body_message;

						var win = window.open(mailto_link, 'emailWindow');
						if (win && win.open &&!win.closed) win.close();

				    }
				})
	    	]
	    });


		var modePanel = {
            xtype: 'fieldset',
            title: 'Mode',
			cls: 'custom-title-fieldset',
            autoHeight: true,
			hidden:objConf.credentialsCmps,
			labelWidth:10,
            items: [{
	            xtype: 'radiogroup',
	            items: [{
	                columnWidth: '.5',
	                items: [
	                    inProjectRb,
						standaloneRb


	                ]
	            },{
	                columnWidth: '.5',
					hidden:objConf.credentialsCmps,
	                items: [
						preselectChb
	                ]
	            }]
	        }]
		}

		var interfacePanel = {
            xtype: 'fieldset',
            title: 'Interface',
			cls: 'custom-title-fieldset',
            autoHeight: true,
			labelWidth:10,
			hidden:objConf.credentialsCmps,
            items: [{
	            xtype: 'radiogroup',
	            items: [{
	                columnWidth: '.5',
	                items: [
	                    showToolbarVChb
	                ]
	            }, {
	                columnWidth: '.5',
	                items: [
						showStatusbarVChb
	                ]
	            }]
	        }]
		}


		var credentialsPanel = new Ext.Panel({
			layout: 'absolute',
			width: 360,
			height: 120,
			baseCls: 'x-plain',
			defaults: {
				baseCls: 'x-plain'
			},
			items: [{
				layout: 'form',
				x: 15,
				y: 5,
				width: 300,
				items: [credentialsChb]
			}, {
				layout: 'form',
				x: 40,
				y: 30,
				items: [otherUserRb]
			}, {
				layout: 'form',
				x: 190,
				y: 30,
				items: [currentUserRb]
			},{
				layout: 'form',
				labelWidth: 80,
				x: 60,
				y: 55,
				hidden: true,
				items: [userTxf, passTxf]
			}, {
				layout: 'form',
				labelWidth: 80,
				x: 250,
				y: 75,
				width: 110,
				hidden: true,
				buttons: ['->', new Ext.Button({
					text: 'Update URL'.localize(),
					width: 75,
					handler: function(){
						getWSSURL(2);
					}
				})]
			}],
			listeners:{
				render:function(){
					currentUserRb.hide();
	                otherUserRb.hide();
				}
			}
		})

		var credentialsFieldSet = {
			xtype: 'fieldset',
			title: 'Credentials',
			cls: 'custom-title-fieldset',
			autoHeight: true,
			items: [credentialsPanel]
		}


	    var urlTargetPanel = new Ext.Panel({
	        layout: 'absolute',
	        width: 360,
	        height: 135,
	        baseCls: 'x-plain',
	        defaults: {
	            baseCls: 'x-plain'
	        },
	        items: [{
	            layout: 'form',
	            x: 5,
	            y: 5,
	            items: [urlLbl]
	        }, {
	            layout: 'form',
	            x: 3,
	            y: 20,
	            width: 370,
	            items: [urlTxa]
	        }, {
	            layout: 'form',
	            x: 5,
	            y: 90,
	            width: 370,
	            items: [noteLbl]
	        }, {
	            layout: 'form',
	            x: 5,
	            y: 100,
	            fbar: credentialsBtns
	        }]
	    });



	    var linkPanel = new Ext.Panel({
	        layout: 'form',
	        baseCls: 'x-plain',
	        items: [urlTargetPanel, modePanel, interfacePanel, credentialsFieldSet]
	    });

		function getVars(){

			var vars = [];
			var varsData = data.var_VARNAME;



			if (varsData) {
				if (varsData.nodes)
					for (var i in varsData.nodes)
						vars.push({name:i, type:'nodes', val:varsData.nodes[i]});

				if (varsData.vars)
					for (var j in varsData.vars)
						vars.push({name:j, type:'vars', val:varsData.vars[j]});
			}

	//		console.log(vars);
			return vars;
		}



	    //================================ urlplugin  =======================================================

		function URLPluginParamsTab(){

			var urlPluginDesc = new Ext.form.Label({
				text: 'urlPluginPropsLbl'.localize()
			});

			var BRLbl = {
				html: '<br/>',
				baseCls: 'x-plain'
			};

			var URLPluginChb = function(name, checked){
				return new Ext.form.Checkbox({
					boxLabel: name.localize(),
					checked: checked == 1 ? true : false,
					handler: function(){
						_urlPluginParamsChangedFlag = true;
					}
				});
			}


			var hideToolbar = new URLPluginChb('Hide toolbar'.localize(), data.urlPluginParams.hideToolbar);
			var hideSave = new URLPluginChb('Hide save'.localize(), data.urlPluginParams.hideSave);
			var hideFilter = new URLPluginChb('Hide filter'.localize(), data.urlPluginParams.hideFilter);
			var hideStaticFilter = new URLPluginChb('Hide static filter'.localize(), data.urlPluginParams.hideStaticFilter);
			var hideAxes = new URLPluginChb('Hide axes'.localize(), data.urlPluginParams.hideHorizontalAxis || data.urlPluginParams.hideVerticalAxis);
			var hideConnectionPicker = new URLPluginChb('Hide connection picker'.localize(), data.urlPluginParams.hideConnectionPicker);


			var urlPluginPanel = new Ext.Panel({
				layout: 'form',
				baseCls: 'x-plain',
				labelWidth: 30,
				items: [urlPluginDesc, BRLbl, hideToolbar, hideSave, hideFilter, hideStaticFilter, hideAxes, hideConnectionPicker]
			});

			this.getPanel = function(){
				return urlPluginPanel;
			}

			this.getURLPluginParams = function(){
				return {
					hideToolbar: hideToolbar.getValue() ? 1 : 0,
					hideSave: hideSave.getValue() ? 1 : 0,
					hideFilter: hideFilter.getValue() ? 1 : 0,
					hideStaticFilter: hideStaticFilter.getValue() ? 1 : 0,
					hideHorizontalAxis: hideAxes.getValue() ? 1 : 0,
					hideVerticalAxis: hideAxes.getValue() ? 1 : 0,
					hideConnectionPicker:hideConnectionPicker.getValue() ? 1:0
				}
			}

		}

	    //================================ Panels and Containers ============================================

	    var _loadedCmp = {};
	    //this._setResources;

	    var propertiesTbs = new Ext.TabPanel({
	        region: 'center',
	        height: 430,
	        layoutOnTabChange: true,
	        border: false,
	        bodyStyle: 'background-color: transparent;',
	        activeTab: 0,
	        defaults: {
	            bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'
	        },
	        items: [{
	            title: 'General'.localize(),
	            layout: 'fit',
	            baseCls: 'x-plain',
	            items: [generalPanel]
	        }],
	        listeners: {
	        	tabchange: function(p, t){
	        		// here set active panel - containers
	        		that.containers.activePanel = t;

	        		switch(t.id){
	        		case 'referrers':
	        			if (_loadedCmp.refList) return;
	        			var itemsFlag = true;
	    				if (data.type in {'Workbook':true, 'Hyperlink':true, 'Urlplugin':true})
	    					itemsFlag = false;
	    				var node = data.type == 'File repository' ? 'root' : data.node;
	        			var callback = function(rPanel){

	        				that.referrersPanel.removeAll();
	        				that.referrersPanel.add(rPanel);
	        				that.referrersPanel.doLayout();
	        			}

	        			Jedox.gen.load(Jedox.studio.app.dynJSRegistry.refList, [itemsFlag, callback, [node]]);
	        			_loadedCmp['refList'] = true;
	        			break;

	        		case 'resources':
	        			if (_loadedCmp.fileResources) return;
	        			var callback = function(rPanel){
	        				that.resourcesPanel.removeAll();
	        				that.resourcesPanel.add(rPanel[0]);
	        				that.resourcesPanel.doLayout();
	        				that._setResources = rPanel[1];
	        			};

	        			Jedox.gen.load(Jedox.studio.app.dynJSRegistry.fileResources, ['resources', false, callback, [data.node], 100]);
	        			_loadedCmp['fileResources'] = true;
	        			break;

	        		case 'security':
	        			if (_loadedCmp.fileSecurity) return;
	        			var callBackFnSec = function(sPanel){
	    	            	that.securityPanel.removeAll();
	        				that.securityPanel.add(sPanel);
	        				that.securityPanel.doLayout();
	        				sPanel.setData(type, data);
	        				_securityObj = sPanel;
	    	            }

	    	            Jedox.gen.load(Jedox.studio.app.dynJSRegistry.fileSecurity, [2, callBackFnSec, 200]);

	        			_loadedCmp['fileSecurity'] = true;
	        			break;

					case 'frameset':
						if (_loadedCmp.frameset) return;
	        			var callBackFnSec = function(refObj){
	    	            	that.framesetPanel.removeAll();
	        				that.framesetPanel.add(refObj.getPanel());
	        				that.framesetPanel.doLayout();
	        				_framesetObj = refObj;
							_loadedCmp['frameset'] = true;
	    	            }

	    	           Jedox.gen.load(Jedox.studio.app.dynJSRegistry.frameset, [callBackFnSec, data.frameset]);
					   break;

	        		}

		        }
	        }
	    });


	    var mainPanel = new Ext.Panel({
	        modal: true,
	        layout: 'form',
	        bodyStyle: 'background-color: transparent;',
	        border: false,
	        items: [propertiesTbs]
	    });


	    //================================ functions ==============================================

	    function initIcon(data){
	    	switch (data.type) {
	            case 'Workbook':
	                iconImg.html = '<div class="' + 'w3s_workbook'.concat(data.props.hasAs? '_as':'', '32') + '"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                referrersDataTypeFlag = true;
					resourcesDataTypeFlag = true;
					typeVal.text = data.type.localize();
	                break;
	            case 'Folder':
	                iconImg.html = '<div class="folder-icon32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                referrersDataTypeFlag = true;
					typeVal.text = data.type.localize();
	                break;
	            case 'Rfolder':
	                iconImg.html = '<div class="folder-icon32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					typeVal.text = 'Folder'.localize();
	                break;
	            case 'Template':
	                iconImg.html = '<div class="workbook-icon32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                //				type == 'qreport'? showURLTxf():'';
					typeVal.text = data.type.localize();
	                break;
	            case 'File group':
	                iconImg.html = '<div class="w3s_group32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                showDecriptionCmp();
					locationLbl.hide();
					typeVal.text = data.type.localize();
	                break;
	            case 'File repository':
	                iconImg.html = '<div class="w3s_hierarchy32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                referrersDataTypeFlag = true;
	                showDecriptionCmp();
					typeVal.text = data.type.localize();
	                break;
	            case 'Report repository':
	                iconImg.html = '<div class="w3s_hierarchy32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                showDecriptionCmp();
					locationLbl.hide();
					typeVal.text = data.type.localize();
	                break;
	            case 'Report group':
	                iconImg.html = '<div class="w3s_group32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                showDecriptionCmp();
					locationLbl.hide();
					typeVal.text = data.type.localize();
	                break;
	            case 'Urlplugin':
	                iconImg.html = '<div class="new-pivot-icon32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					referrersDataTypeFlag = true;
	                showDecriptionCmp();
					typeVal.text = 'Palo Pivot'.localize();
	                break;
	            case 'Rurlplugin':
	                iconImg.html = '<div class="new-pivot-icon32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					typeVal.text = 'Palo Pivot'.localize();
	                break;
	            case 'Hyperlink':
	                iconImg.html = '<div class="w3s_rhyperlink32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                referrersDataTypeFlag = true;
	                showDecriptionCmp();
					typeVal.text = data.type.localize();
	                break;
				case 'Rhyperlink':
					iconImg.html = '<div class="w3s_rhyperlink32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
	                showDecriptionCmp();
					typeVal.text = 'Hyperlink'.localize();
					break;
				case 'Static':
				case 'Rstatic':
					iconImg.html = '<div class="w3s_' + data.subtype + '32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					typeVal.text = getStaticDescription(data.subtype);
					break;
				case 'Frameset':
					iconImg.html = '<div class="w3s_frameset32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					typeVal.text = data.type;
					showDecriptionCmp();
					break;
				case 'Rframeset':
					iconImg.html = '<div class="w3s_frameset32"><img src="../lib/ext/resources/images/default/s.gif" width="32px" height="32px"/></div>';
					typeVal.text = 'Frameset'.localize();
					showDecriptionCmp();
					break;

	        }

	        function showDecriptionCmp(){
	            descriptionTxa.hidden = false;
	            descriptionLbl.hidden = false;
	        }

	        function showURLTxf(){
	            urlLbl.hidden = false;
	            urlTxf.hidden = false;
	            urlPanel.hidden = false;
	        }


	        if (type == 'hierarchy') {
	            locationCmp = locationTxf;
	            locationCmp.setValue(data.sysPath)
	        }
	        else
	            if (type == 'hyperlink') {
	                locationCmp = locationTxf;
	                locationCmp.setValue(data.url.url)
	            }
	            else
	                locationVal.text = data.relPath;


	    }



		function getStaticDescription(subtype){

			var _return;

			switch (subtype){
				case 'csv':
					_return = 'Microsoft Office Excel Comma Separated Values File'.localize();
					break;
				case 'doc':
					_return = 'Microsoft Office Word 97 - 2003'.localize();
					break;
				case 'pdf':
					_return = 'Adobe Acrobat Document'.localize();
					break;
				case 'gif':
					_return = 'GIF Image'.localize();
					break;
				case 'htm':
				case 'html':
					_return = 'Firefox Document'.localize();
					break;
				case 'jpg':
					_return = 'JPEG Image'.localize();
					break;
				case 'png':
					_return = 'PNG Image'.localize();
					break;
				case 'pps':
					_return = 'Microsoft Office PowerPoint 97 - 2003 Show'.localize();
					break;
				case 'ppt':
					_return = 'Microsoft Office PowerPoint 97 - 2003 Presentation'.localize();
					break;
				case 'rar':
					_return = 'WinZip File'.localize();
					break;
				case 'rtf':
					_return = 'Rich Text Format'.localize();
					break;
				case 'txt':
					_return = 'Text Document'.localize();
					break;
				case 'xls':
					_return = 'Microsoft Office Excel 97 - 2003 Workbook'.localize();
					break;
				case 'xlsx':
					_return = 'Microsoft Office Excel Workbook'.localize();
					break;
				case 'zip':
					_return = 'WinZip File'.localize();
					break;
				case 'unknown':
					_return = 'Unknown File format'.localize();
					break;
				default :
					_return = 'Unknown File format'.localize();
					break;
			}

			return _return;

		}


	    function init(data){

	        nameTxf.setValue(data.name);
	        descriptionTxa.setValue(data.description);

			if(data.props){

				var props = data.props;

				sizeLbl.setVisible(true);
				sizeVal.setVisible(true);
				sizeVal.text = Ext.util.Format.fileSize(props.size).concat(' (', props.size, ' bytes)');
	//			if (data.props.blksize != -1){
	//				sizeOnDiskLbl.setVisible(true);
	//				sizeOnDiskVal.setVisible(true);
	//				sizeOnDiskVal.text = props.blksize;
	//			}

				createdLbl.setVisible(true);
				createdVal.setVisible(true);
				createdVal.text = Date.parseDate(props.ctime, _listDateFormat).format('date_format'.localize());
				modifiedLbl.setVisible(true);
				modifiedVal.setVisible(true);
				modifiedVal.text = Date.parseDate(props.mtime, _listDateFormat).format('date_format'.localize());
				accessedLbl.setVisible(true);
				accessedVal.setVisible(true);
				accessedVal.text = Date.parseDate(props.atime, _listDateFormat).format('date_format'.localize());
			}


	        if (type === 'qreport') {

	            nameTxf.disable();


				if (data.type =='Template' || data.type == 'Rframeset'){
		            propertiesTbs.add({
		                title: 'Link'.localize(),
		                baseCls: 'x-plain',
		                items: [linkPanel]
		            });

					getWSSURL();
				}

	        }



			if (data.type =='Static'){
	            propertiesTbs.add({
	                title: 'Link'.localize(),
	                baseCls: 'x-plain',
	                items: [linkPanel]
	            });

				getWSSURL();
			}


	        if (type === 'urlplugin') {
				_urlParamsTab = new URLPluginParamsTab();
	            propertiesTbs.add({
	                title: 'Options'.localize(),
	                baseCls: 'x-plain',
	                items: [_urlParamsTab.getPanel()]
	            });
	        }


	        if (referrersDataTypeFlag) {
	            that.referrersPanel = new Ext.Panel({
	            	baseCls: 'x-plain',
	            	items: [{baseCls: 'x-plain'}]
	        	});
	            propertiesTbs.add({
	                title: 'Referrers'.localize(),
	                baseCls: 'x-plain',
	                id: 'referrers',
	                items: [that.referrersPanel]
	            });
	        }


	        if (resourcesDataTypeFlag) {
	        	that.resourcesPanel = new Ext.Panel({
	            	baseCls: 'x-plain',
	            	items: [{baseCls: 'x-plain'}]
	        	});
	            propertiesTbs.add({
	                title: 'Resources'.localize(),
	                id: 'resources',
	                baseCls: 'x-plain',
	                items: [that.resourcesPanel]
	            });
	        }

			if (data.frameset) {

	        	that.framesetPanel = new Ext.Panel({
	            	baseCls: 'x-plain',
	            	items: [{baseCls: 'x-plain'}]
	        	});
	            propertiesTbs.add({
	                title: 'Frameset'.localize(),
	                id: 'frameset',
	                baseCls: 'x-plain',
	                items: [that.framesetPanel]
	            });

			}


	        if (Jedox.studio.access.rules.rights & Jedox.studio.access.permType.DELETE && type != 'qreport') {
				//_securityObj = new Jedox.studio.dialog.Security(true);
				that.securityPanel = new Ext.Panel({
	            	baseCls: 'x-plain',
	            	items: [{baseCls: 'x-plain'}]
	        	});

	            propertiesTbs.add({
	                title: 'Security'.localize(),
	                baseCls: 'x-plain',
	                id: 'security',
	                items: [that.securityPanel]
	            });
	        }

	    }


	    function trim(s){
	        return s.replace(/^\s+|\s+$/g, '');
	    }


	    function getWSSURL(flag){

			var stndaln = false, params = {}, stq = '';

			if(objConf.stf){
				stq = 't='.concat(type, '&g=', data.group, '&h=', data.hierarchy, '&n=', data.node, '&sr=yes');
			}
			else{

				if(inProjectRb.getValue()){

					stndaln = false;

					params = {
						studio:{
							'default': {
								reports: {
									group: data.group,
									hierarchy: data.hierarchy,
									node: data.node,
									path: data.rPath,
									'var': getVars(), //needs to send vars in correct format
									preselect:preselectChb.getValue(),
									type:data.type =='Template'? 'spreadsheet':'frameset'
								}
							}
						},
						wss:{
							viewer:{
								status:showStatusbarVChb.getValue(),
								toolbar:showToolbarVChb.getValue()
							}
						}
					}

				}
				else{
					//standalone
					stndaln = true;

					params = {
						wam:'user',
						wb:data.node,
						grp:data.group,
						hrc:data.hierarchy,
						ntype:data.type.toLowerCase(),
						'wss/viewer/status':showStatusbarVChb.getValue(),
						'wss/viewer/toolbar':showToolbarVChb.getValue()
					}

					fillVars(data.var_VARNAME);

				}

			}

			//credentials
	        if (credentialsChb.getValue()) {
	            if (currentUserRb.getValue())
	                var credentials = {
	                    flag: flag
	                };
	            else
	                var credentials = {
	                    flag: flag,
	                    user: userTxf.getValue(),
	                    pass: passTxf.getValue()
	                };
	        }
			else {
				var credentials = {
	            	flag: 0
	            };
			}


			function fillVars(varObj){

				var vempty = true; //flag if no variables are set

				if (varObj) {
					if (varObj.nodes) {
						vempty = false;
						for (var i in varObj.nodes)
							params['n_' + i] = varObj.nodes[i];
					}

					if (varObj.vars) {
						vempty = false;
						for (var j in varObj.vars)
							params['v_' + j] = varObj.vars[j];
					}

					if (varObj.rPath)
						params['rPath'] = varObj.rPath;
				}

				if(vempty)
					params['vempty'] = true;

			}



			function onSuccessCbHandler(result){
				if (result) {
					urlTxa.setValue(result);
					urlTxa.focus(true);
				}
			}

			function onErrorCbHandler(result){
				urlTxa.setValue("");
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'getExternURI', [stndaln, stq, params, credentials]))
				.setOnSuccess([this, onSuccessCbHandler]).setOnError([this, onErrorCbHandler]).send();


	    }


	    function onSetPermission(){
			if (_securityObj)
				_securityObj.savePermission();
	    }


	    function onRename(){

			if (!nameTxf.getValue()) {
				var msg = 'Name must start with a-z/A-Z character and must contain more than two character'.localize() + '...';
				nameTxf.markInvalid(msg);
			}

			else {

				if (data.name != nameTxf.getValue() || (descriptionTxa && descriptionTxa.getValue() != data.description) || (locationTxf.getValue() && data.sysPath != locationTxf.getValue()) || _urlPluginParamsChangedFlag || (_framesetObj && _framesetObj.isChanged())) {
					switch (type) {
						case 'group':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()));
							data.description = trim(descriptionTxa.getValue());
							break;
						case 'hierarchy':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()), trim(locationCmp.getValue()));
							data.sysPath = trim(locationCmp.getValue());
							break;
						case 'rhierarchy':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()));
							break;
						case 'hyperlink':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()), locationCmp.getValue(), data.url.target);
							break;
						case 'urlplugin':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()), _urlParamsTab.getURLPluginParams());
							break;
						case 'frameset':
							renameHandleFnc(trim(nameTxf.getValue()), trim(descriptionTxa.getValue()), _framesetObj? _framesetObj.getData():null);
							break;
						default:
							renameHandleFnc(trim(nameTxf.getValue()));
							break;
					}

					data.name = trim(nameTxf.getValue());
					if(data.description)
						data.description = trim(descriptionTxa.getValue());
				}
			}
	        //			data.name = trim(nameTxf.getValue());
	    }


		function onRefresh(){
			if(refreshHandleFnc && _securityObj)
				refreshHandleFnc(_securityObj.getPermission());
		}

		function onSetResources(){
			if (_loadedCmp.fileResources)
				that._setResources();
		}

	    function onSetFileProps(){

	    }


	    function onApply(){
	        onSetPermission();
	        onRename();
			onSetResources();
			if (_securityObj && _securityObj.getRefreshFlag() && _securityObj.getPermission() == 'N'){
				onRefresh();
				that.win.close();
			}
	    }

		function onCancel(){
			if (_securityObj && _securityObj.getRefreshFlag())
				onRefresh();
			that.win.close();
		}


	    function onSave(){
	        onSetPermission();
	        onRename();
			onSetResources();
			if (_securityObj && _securityObj.getRefreshFlag())
				onRefresh();
	        that.win.close();
	    }

	    //================================ Window (Dlg) ============================================

	    var unloadComponents = function(){
	    	for (var c in _loadedCmp){
	    		Jedox.gen.unload(Jedox.studio.app.dynJSRegistry[c]);
	    	}
	    };

	    this.win = new Ext.Window({
	        id: 'studio-files-properties-dlg',
	        title: 'Properties'.localize(),
	        closable: true,
	        closeAction: 'close',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
	        layout: 'fit',
	        width: 400,
	        height: 500,
	        items: mainPanel,
	        onEsc: Ext.emptyFn,
	        listeners: {
	            close: function(){
	                Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
					if (_securityObj && _securityObj.getRefreshFlag())
						onRefresh();
					that.close();
					unloadComponents();
					Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openProperties);
	            },
	            show:function(){
					setTimeout(function(){
						//that.initFocus(true, 300);
					});
				},
				activate: function(win) {that.activate();}
	        },

	        buttons: [
		        (this.components.OK = new Ext.Button({
		            text: 'OK'.localize(),
		            tabIndex: 1000,
		            handler: function(){
		                onSave();
		            }
		        })),
		        (this.components.Cancel = new Ext.Button({
		            text: 'Cancel'.localize(),
		            tabIndex: 1001,
		            ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		            handler: function(){
						onCancel();
		            }
		        })),
		        (this.components.Apply = new Ext.Button({
		            text: 'Apply'.localize(),
		            ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		            tabIndex: 1002,
		            handler: function(){
		                onApply();
		            }
		        }))
		        ]
	    });

	    init(data);
	    this.setContext();
	    this.win.show(this);

	};
}
)();

// Licence extends Dialog.
Jedox.util.extend(Jedox.studio.dlg.Properties, Jedox.dlg.Dialog);
