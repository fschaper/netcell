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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: ReferrersList.js 4546 2011-01-28 08:09:22Z srdjanv $
 *
 */

Jedox.studio.files.dlg.ReferrersList = function(itemsFlag, callBackFn, node){

// itemsFlag - true - folder, false - item
	var that = this;
	var reportListData = [['rGrp1/rHrh1/New folder/New workbook rprt'], ['rGrp1/rHrh1/New folder/New workbook rprt1'], ['rGrp1/rHrh1/New folder/New workbook rprt2']];
	var _itemsFlag = itemsFlag;
	var _referrersStore;


	var referrersItemStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'referrer', type: 'string'}
		]
	});

	var referrersItemListGP = new Ext.grid.GridPanel({
		id: 'referrers-item-list',
		colModel: new Ext.grid.ColumnModel([
			{header: "Referrers".localize(), width: 340, sortable: true, menuDisabled:true, dataIndex: 'referrer'}
		]),
		store: referrersItemStore,
		autoScroll:true,
		viewConfig: {
			autoFill:true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: true
		})
	});



	var referrersItemsStore = new Ext.data.SimpleStore({
		fields: [
			{name: 'subNode', type: 'string'},
			{name: 'referrer', type: 'string'}
		]
	});

	var referrersItemsListGP = new Ext.grid.GridPanel({
		id: 'referrers-items-list',
		colModel: new Ext.grid.ColumnModel([
			{header: "Sub Nodes".localize(), width: 150, sortable: true, dataIndex: 'subNode'},
			{header: "Referrers".localize(), width: 150, sortable: true, menuDisabled:true, dataIndex: 'referrer'}
		]),
		autoScroll:true,
		store: referrersItemsStore,
		viewConfig: {
			autoFill: true
		},
		sm: new Ext.grid.RowSelectionModel({
			singleSelect: true
		})
	});

	var mainPanel = new Ext.Panel({
		layout: 'fit',
		width:365,
		height:380,
		border:false
	});


	// ----------------- PUBLIC FUNCTIONS---------------------------

	function initData(nodes){

		var that = this;

		var wssStudioHandler = {
			getReferrers: function(result){
				_referrersStore.loadData(result);
			}
		}

		var wssStudioStub = new Jedox.backend.rpc.Studio(wssStudioHandler);
		wssStudioStub.getReferrers(nodes);
	}


	function setConfig(){
		if (_itemsFlag){
			_referrersStore = referrersItemsStore;
			mainPanel.add(referrersItemsListGP);
		}
		else {
			_referrersStore = referrersItemStore;
			mainPanel.add(referrersItemListGP)
		}
	}

	// ----------------- PRIVATE FUNCTIONS---------------------------


	this.getReferrersList = function(nodes){
		setConfig();
		initData(nodes);

		return mainPanel;
	}

	var pp = this.getReferrersList(node);
	callBackFn(pp);

}



