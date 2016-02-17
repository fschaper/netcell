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
 * SVN: $Id: PrivateVars.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */

Jedox.wss.dlg.privateVars = function() {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PrivateVariables());
};

Jedox.wss.dlg.PrivateVariables = (function() {

	return function () {

		Jedox.wss.dlg.PrivateVariables.parent.constructor.call(this);
		this.id = 'PrivateVariables';
		var that = this;


		var activeBook = Jedox.wss.app.activeBook,
				wb = activeBook ? activeBook._meta : undefined;

		//##########################	Extensions	- Active checkbox ##########################
		Ext.grid.CheckColumn = function(config){
			Ext.apply(this, config);
			if(!this.id){
				this.id = Ext.id();
			}
			this.renderer = this.renderer.createDelegate(this);
		};

		Ext.grid.CheckColumn.prototype ={
				init : function(grid){
			this.grid = grid;
			this.grid.on('render', function(){
				var view = this.grid.getView();
				view.mainBody.on('mousedown', this.onMouseDown, this);
			}, this);
		},
		onMouseDown : function(e, t){
			if(t.className && t.className.indexOf('x-grid3-cc-'+this.id) != -1){
				e.stopEvent();
				var index = this.grid.getView().findRowIndex(t);
				var record = this.grid.store.getAt(index);
				record.set(this.dataIndex, !record.data[this.dataIndex]);

				//enable Apply btn if wb
				if (wb) Ext.getCmp('applyBtn').enable();
			}
		},
		renderer : function(v, p, record){
			p.css += ' x-grid3-check-col-td';
			return '<div class="x-grid3-check-col' +
			(v?'-on':'') +
			' x-grid3-cc-' +
			this.id +
			'"> </div>';
		}
		};

		////////////////////////////////////////////////////////

		var gridData;

		var gridStore = new Ext.data.ArrayStore({
			fields: [
			         {name: 'name'},
			         {name: 'value'},
			         {name: 'privateVar'}
			         ]
		});

		function cbr(res){

			if(!res){
				//error
				return;
			}

			gridData = res;
			gridStore.loadData(gridData);
		}

		Jedox.backend.rpc([ this, cbr ], 'wss_book', 'getUsedVars', (wb)? [ wb.g, wb.h, wb.n ] : [false, false, false]);

		var cbPrivate = new Ext.grid.CheckColumn({
			header: 'Private'.localize(),
			dataIndex: 'privateVar',
			width: 70,
			sortable: true,
			align: 'center'
		});

		var grid = new Ext.grid.GridPanel({
			store: gridStore,
			clicksToEdit:1,
			plugins: cbPrivate,
			height: 350,
			cm: new Ext.grid.ColumnModel([
		                              cbPrivate,
		                              {id:'name',header: "Name".localize(), width: 180, dataIndex: 'name', sortable: true},
		                              {header: "Current Value".localize(), width: 180, dataIndex: 'value', sortable: true}
		                              ]),
	      stripeRows: true,
	      sm: new Ext.grid.RowSelectionModel({singleSelect: true}),
	      enableHdMenu: false,
	      autoExpandColumn: 'name',
	      autoWidth: true,
	      baseCls: 'x-plain',
	      viewConfig: {
		        forceFit: true
			}
		});

		this.win = new Ext.Window({
			title: 'Used Variables'.localize(),
			closable: true,
			id: 'private-variables',
			autoDestroy : true,
			cls: 'default-format-window',
			plain: true,
			constrain: true,
			modal: true,
			resizable: false,
			enableHdMenu: false,
			animCollapse: false,
			width: 440,
			height: 400,
			onEsc: Ext.emptyFn,
			layout: 'fit',
			bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
			listeners: {
				close: function() {
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.privateVars);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
			items: [grid],
	        buttons: [
					(this.components.OK = new Ext.Button({
						text: 'Apply'.localize(),
						tabIndex: 2,
						disabled: true,
						id: 'applyBtn',
						handler: function(){
							applyVars();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						text: 'Cancel'.localize(),
						tabIndex: 3,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))
					]
		});

		function applyVars(){
			// apply private variable changes
			var toApply = [];
			function ffn(rec, id){
				if (rec.data.privateVar) toApply.push(rec.data.name);
			};
			grid.getStore().each(ffn);
			function closefn(){that.win.close()};
			Jedox.backend.rpc([this, closefn], 'wss_book', 'setPrivVars', [ wb.g, wb.h, wb.n, toApply]);
		}

		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PrivateVariables, Jedox.dlg.Dialog);