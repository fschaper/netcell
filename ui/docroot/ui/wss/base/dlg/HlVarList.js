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
 * SVN: $Id: HlVarList.js 4785 2011-03-29 13:19:34Z djordjez $
 *
 */

Jedox.wss.dlg.hlVarList = function(getVar, preselection) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.HlVarList(getVar, preselection));
};

Jedox.wss.dlg.HlVarList = (function() {

	return function (getVar, preselection) {

		Jedox.wss.dlg.HlVarList.parent.constructor.call(this);
		this.id = 'wHlVarList_dlg_wnd';
		var that = this;
	//
		var rawData = Jedox.backend.ccmd(0, ["gvls"]);

		var vGridData = [];
		if (rawData[0][0]) {
			var vars = rawData[0][1];
			for (var q=0; q<vars.length; q++)
				vGridData.push([vars[q]]);
			// end
			if (vars.length < 1) vGridData = [];
		}

		var vGridStore = new Ext.data.SimpleStore({
			fields: [
			         {name: 'variable'}
			         ]
		});

		vGridStore.loadData(vGridData);

		var _selectedVar;

		var vGrid = new Ext.grid.GridPanel({
			id:'wHlVarList_vlist_grd',
			store: vGridStore,
			columns: [
			          {id:'vars', header: "Variable name", width: 200, sortable: false, dataIndex: 'variable'}
			          ],
			          sm: new Ext.grid.RowSelectionModel({singleSelect:true}),
			          width:215,
			          height:210,
			          frame:true,
			          autoExpandColumn: 'vars',
			          baseCls: 'x-plain',
			          listeners: {
			rowclick: function(gr, index, e) {
			_selectedVar = vGridData[index][0];
		}
		}
		});

		this.win = new Ext.Window({
			id: 'wHlVarList_dlg_wnd',
			title: 'Variable list'.localize(),
			closable: true,
			autoDestroy: true,
			plain: true,
			onEsc: Ext.emptyFn,
			constrain: true,
			modal: true,
			resizable: false,
			enableHdMenu: false,
			animCollapse: false,
			width: 250,
			height: 300,
			// border:false,
			layout: 'form',
			items: [
			        new Ext.Panel({
			        	id: 'grid_varis',
			        	bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
			        	border: false,
			        	frame: false,
			        	autoHeight: true,
			        	layout: 'form',
			        	items: [vGrid]
			        })
			        ],
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.hlVarList);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
			buttons: [
					(this.components.OK = new Ext.Button({
						text: 'OK'.localize(),
						tabIndex: 2,
						handler: function(){
							that.win.close();
							getVar(_selectedVar);
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

		this.setContext();
		this.win.show(this);
		// do preselection
		//console.log(preselection);
		if (preselection && preselection!=''){
			for (var q=0; q<vGridData.length; q++){
				if (vGridData[q][0] == preselection){
					setTimeout(function(){vGrid.getSelectionModel().selectRow(q);}, 1)
					break;
				}
			}
		}

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.HlVarList, Jedox.dlg.Dialog);