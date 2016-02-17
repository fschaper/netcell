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
 * SVN: $Id: TaggedMng.js 4546 2011-01-28 08:09:22Z srdjanv $
 *
 */
Jedox.studio.files.dlg.tagManager = function(dlgFlag){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.TaggedMng(dlgFlag));
};

Jedox.studio.files.dlg.TaggedMng = (function(){

	// class constructor
	return function (dlgFlag) {

		Jedox.studio.files.dlg.TaggedMng.parent.constructor.call(this);

		this.id = 'tagManager';
		var that = this;

	    Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
	    Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		var that = this;


	    var contextStore = new Ext.data.SimpleStore({
	        fields: [
				{name: 'value', type: 'string'},
				{name: 'description', type: 'string'}],
			data:[
				['all', 'All'.localize()],
				['files', 'Files'.localize()],
				['reports', 'Reports'.localize()]
			]
	    });

	    var contextCmb = new Ext.form.ComboBox({
	        store: contextStore,
			fieldLabel:'Context'.localize(),
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        displayField:'description',
			valueField:'value',
	        typeAhead: false,
			triggerAction: 'all',
			mode: 'local',
			width: 85,
			value:'all',
	        onSelect: function(record, index){ // override default onSelect to do redirect
		        if(this.fireEvent('beforeselect', this, record, index) !== false){
		            this.setValue(record.data[this.valueField || this.displayField]);
		            this.collapse();
		            this.fireEvent('select', this, record, index);
		        }

				typeCmb.setValue('all');
				tagCmb.setValue('all');
				loadTagged(index == 0? null:record.data.value, null, null);
	    	},
			getValue:function(){
				return this.value == 'all'? null:this.value;
			}
	    });

	    var typeStore = new Ext.data.SimpleStore({
	        fields: [
				{name: 'value', type: 'string'},
				{name: 'description', type: 'string'}],
			data:[
				['all', 'All'.localize()],
				['spreadsheet', 'Spreadsheet'.localize()]
			]
	    });

	    var typeCmb = new Ext.form.ComboBox({
	        store: typeStore,
			fieldLabel:'Type'.localize(),
	        displayField:'description',
			valueField:'value',
			tabIndex: 2,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        typeAhead: false,
			triggerAction: 'all',
			mode: 'local',
			width: 85,
			value:'all',
	        onSelect: function(record, index){ // override default onSelect to do redirect
		        if(this.fireEvent('beforeselect', this, record, index) !== false){
		            this.setValue(record.data[this.valueField || this.displayField]);
		            this.collapse();
		            this.fireEvent('select', this, record, index);
		        }

				loadTagged(contextCmb.getValue(), index == 0? null:record.data.value, tagCmb.getValue());
	    	},
			getValue:function(){
				return this.value == 'all'? null:this.value;
			}
	    });


	    var tagStore = new Ext.data.SimpleStore({
	        fields: [
				{name: 'value', type: 'string'},
				{name: 'description', type: 'string'}
			]
	    });

	    var tagCmb = new Ext.form.ComboBox({
	        store: tagStore,
			fieldLabel:'Tag'.localize(),
	        displayField:'description',
			valueField:'value',
			tabIndex: 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        typeAhead: false,
			triggerAction: 'all',
			mode: 'local',
			width: 85,
			value:'All',
	        onSelect: function(record, index){ // override default onSelect to do redirect
		        if(this.fireEvent('beforeselect', this, record, index) !== false){
		            this.setValue(record.data[this.valueField || this.displayField]);
		            this.collapse();
		            this.fireEvent('select', this, record, index);
		        }

				loadTagged(contextCmb.getValue(), typeCmb.getValue(), index == 0? null:record.data.value);
	    	},
			getValue:function(){
				return (this.value in {'All':true, 'all':true})? null:this.value;
			}
	    });


	    var BRLbl = {
	        html: '<br>',
	        baseCls: 'x-plain'
	    }

	    var taggedStore = new Ext.data.SimpleStore({
	        fields: [
				{name: 'context', type: 'string'},
				{name: 'type', type: 'string'},
				{name: 'location'},
				{name: 'tag', type: 'string'}
			]
	    });


		var taggedGridPanel = new Ext.grid.GridPanel({
			colModel: new Ext.grid.ColumnModel([
				{header: "Path".localize(), width: 260, sortable: true, menuDisabled:true, dataIndex: 'location', renderer:function(c,f,g){

					return g.data.location.path;

				}},
				{header: "Context".localize(), width: 95, sortable: true, dataIndex: 'context'},
				{header: "Type".localize(), width: 95, sortable: true, dataIndex: 'type'},
				{header: "Tag".localize(), width: 95, sortable: true, dataIndex: 'tag'}
			]),
			autoScroll:true,
			store: taggedStore,
			height:315,
			viewConfig: {
				autoFill: true
			},
			sm: new Ext.grid.RowSelectionModel({
				singleSelect: false
			})
		});


	    var filterContainerPanel = {
	        layout: 'absolute',
	        border: false,
	        bodyStyle: 'background-color: transparent;',
	        width: 550,
	        height: 40,
	        defaults: {
	            baseCls: 'x-plain'
	        },
	        items: [{
	            x: 245,
	            y: 0,
				layout:'form',
				labelAlign:'top',
	            items: contextCmb
	        }, {
	            x: 335,
	            y: 0,
				layout:'form',
				labelAlign:'top',
	            items: typeCmb
	        }, {
	            x: 425,
	            y: 0,
				layout:'form',
				labelAlign:'top',
	            items: tagCmb
	        }]
	    }


	    var mainPanel = this.containers.mainPanel = new Ext.Panel({
	        layout: 'form',
	        border: false,
			autoWidth: true,
	        bodyStyle: 'background-color: transparent;',
	        items: [BRLbl, filterContainerPanel, BRLbl, taggedGridPanel]
	    });



		this.win = new Ext.Window({
			title:'Tag Manager'.localize(),
			closable: true,
			closeAction: 'close',
			cls: 'default-format-window',
	        autoDestroy: true,
	        plain: true,
	        modal: true,
			constrain:true,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			width: 550,
			height: 450,
			items: mainPanel,
			onEsc: Ext.emptyFn,
			listeners: {
				close: function()
				{
					Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
					that.close();
					Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.tagManager);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 300);
					});
				},
				activate: function(win) {that.activate();}
			},

			buttons: [
			          (this.components.ClAll = new Ext.Button({
			            text: 'Clear All'.localize(),
			            tabIndex: 10,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			            handler: function(){
			                onClearAll();
			            }
			        })),
			        (this.components.Cancel = new Ext.Button({
			            text: 'Cancel'.localize(),
			            tabIndex: 11,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			            handler: function(){
							onCancel();
			            }
			        })),
			        (this.components.RemoveSel = new Ext.Button({
			            text: 'Remove selected'.localize(),
			            tabIndex: 12,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			            handler: function(){
			                onRemoveSelected();
			            }
			        }))
			        ]

		});


		this.setContext();
		this.win.show(this);
		init();



		// private functions

		function init(){
			loadTagCmb();
			loadTagged();
		}

		function loadTagCmb(){

			function cb(result){
				var tagData = [['all', 'All'.localize()], ['RES', 'resource'.localize()], ['FRAME', 'frame'.localize()]];

				for (var i =0, count = result.length, t; i<count; i++){
					t = result[i];
					if (t != 'RES' && t != 'FRAME')
						tagData.push([t, t]);
				}

				tagStore.loadData(tagData);
			}

			Jedox.backend.rpc([this, cb], 'common', 'distinctTagged', []);
		}

		function loadTagged(context, type, tag){

			function onSuccessCbHandler(result){
				var taggedData = [];

				for (var i =0; i<result.length; i++){
					taggedData.push([result[i].context, result[i].type, result[i].location, result[i].tag])
				}

				taggedStore.loadData(taggedData);
			}

			(new Jedox.backend.RPCAsyncRqst('Studio', 'fetchTagged', [context, type, tag]))
				.setOnSuccess([this, onSuccessCbHandler]).send();

		}

		function onClearAll(){

			function cb(result){
				loadTagged(contextCmb.getValue(), typeCmb.getValue(), tagCmb.getValue());
				loadTagCmb();
			}

			Jedox.backend.rpc([this, cb], 'common', 'clearTagged', [contextCmb.getValue(), typeCmb.getValue(), tagCmb.getValue()]);

		}


		function onCancel(){

			that.win.close();
		}

		function onRemoveSelected(){

			var items = [];

			for (var i = 0, selections = taggedGridPanel.getSelectionModel().getSelections(), count = selections.length; i< count; i++)
				items.push(selections[i].data);

			function cb(result){
				loadTagged(contextCmb.getValue(), typeCmb.getValue(), tagCmb.getValue());
				loadTagCmb();
			}

			Jedox.backend.rpc([this, cb], 'common', 'removeTagged', [items]);
		}

	};
}
)();

Jedox.util.extend(Jedox.studio.files.dlg.TaggedMng, Jedox.dlg.Dialog);
