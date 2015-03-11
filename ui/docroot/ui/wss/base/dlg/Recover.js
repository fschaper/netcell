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
 * Drazen Kljajic <sdrazen.kljajic@develabs.com
 *
 * \version
 * SVN: $Id: Recover.js 4972 2011-05-20 10:51:17Z lukap $
 *
 */

Jedox.wss.dlg.openRecoverDialog = function(asList, loadArgs, cb, nLoadArgs) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Recover(asList, loadArgs, cb, nLoadArgs));
};

Jedox.wss.dlg.Recover = (function() {

	return function (asList, loadArgs, cb, nLoadArgs) {

		Jedox.wss.dlg.Recover.parent.constructor.call(this);

		this.id = 'Recover';
		var that = this,
			isFs = cb != undefined,
			env = Jedox.wss.app.environment,
			listDateFormat = 'd.m.Y H:i:s',
			radioOrig, radioRecov, grid;

		if (env != null) {
			Jedox.wss.app.lastInputModeDlg = env.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		/*
		if (!asList)
			asList = {
			    orig: {meta: {ghn: {g: 'fgrp1', h: 'h1', n: 'n168'}, name: 'Car sales'}, date: '15.01.2010 15:30:43', size: 17304},
			    recov: [
				    ['admin.c78f10d8-1ad5-11df-8aca-7f29fb458835.~0', '15.01.2010 15:30:43', 17304],
				    ['admin.c78f10d8-1ad5-11df-8aca-7f29fb458835.~1', '15.01.2010 13:22:20', 17154],
				    ['admin.c78f10d8-1ad5-11df-8aca-7f29fb458835.~2', '14.01.2010 08:20:43', 13601]
				]
			};
		*/

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			modal: true,
			layout: 'form',
			baseCls: 'x-plain',
			bodyStyle : 'padding: 5px 5px 0',
			border: false,
			items: [

			    new Ext.Panel({
					 autoHeight : true,
					 baseCls : 'x-plain',
					 style : 'margin: 10px 0px; word-wrap: break-word;',
					 items : [ {
						 html : 'as_msg'.localize(),
						 baseCls : 'x-plain'
					 }]
			    })

			    // Radio - original file.
				, (radioOrig = new Ext.form.Radio({
					checked: true,
					name: 'ftype',
					tabIndex: 1,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					boxLabel: 'astype_orig'.localize({date: Date.parseDate(asList.orig.date, listDateFormat).format('date_format'.localize()), size: Ext.util.Format.fileSize(asList.orig.size)}),
					hideLabel: true
				}))

				// Radio - recovery file.
				, (radioRecov = new Ext.form.Radio({
					checked: false,
					name: 'ftype',
					tabIndex: 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					boxLabel: 'astype_recov'.localize(),
					hideLabel: true,
					listeners: {
						check: function(cmp, checked) {
							if (checked) {
								var selModel = grid.getSelectionModel();

								if (!selModel.hasSelection())
									selModel.selectFirstRow();
							}
						}
					}
				}))

			    // Grid with autosave list.
				, (grid = new Ext.grid.GridPanel({
					 id: 'asgrid',

					 store: new Ext.data.ArrayStore({
						 fields: [
						     {name: 'idx', type: 'string'},
						     {name: 'date', type: 'date', dateFormat: listDateFormat},
						     {name: 'size', type: 'int'}
						 ],
						 data: asList.recov
					 }),

					 columns : [
					     {
					    	 id: 'asDate',
					    	 header : 'Date'.localize(),
					    	 width: 200,
					    	 resizable : true,
					    	 sortable : true,
					    	 renderer: Ext.util.Format.dateRenderer('date_format'.localize()),
					    	 dataIndex : 'date'
					     }
					     , {
					    	 header : 'Size'.localize(),
					    	 width: 150,
					    	 resizable : true,
					    	 sortable : true,
					    	 renderer: Ext.util.Format.fileSize,
					    	 dataIndex : 'size'
					     }
					 ],

					 hideLabel: true,
					 stripeRows : true,
					 autoExpandColumn : 'asDate',
					 height: 220,
					 width: 350,
					 viewConfig: {forceFit: true},
					 header: false,
					 tabindex: 1,
					 anchor: '100%',
					 selModel: new Ext.grid.RowSelectionModel({
						 singleSelect : true,
						 listeners : {
						 	rowselect: function() {
							 	if (!radioRecov.getValue())
							 		radioRecov.setValue(true);
						 	}
					 	 }
					 })
				}))
			]
		});

		this.resetInputMode = function() {
			var env = Jedox.wss.app.environment;

			if (env && env.inputMode == Jedox.wss.grid.GridMode.DIALOG) {
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}
		};

		this.win = new Ext.Window({
			id: 'recoverDlg',
			title: 'Open and Repair'.localize().concat(' - ', asList.orig.meta.name),
			closable: true,
			cls: 'default-format-window',
			closeAction: 'close',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			width: 450,
			height: 400,
			onEsc: Ext.emptyFn,
			items: mainPanel,
			_execClose: true,
			listeners: {
				beforedestroy: function(panel) {
					mainPanel.items.each( function(f) {
						f.purgeListeners();
						Ext.destroy(f);
					});
					mainPanel.purgeListeners();
					mainPanel.destroy();

					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.recover);
				},

				destroy: function(cmp) {
					if (that.win._execClose)
						try {
							var wbMeta = isFs ? {ghn: {g: loadArgs[2], h: loadArgs[3], n: loadArgs[1]}, name: loadArgs[6]}  : asList.orig.meta;

							for (var triggers = Jedox.wss.events.triggers.closeWorkbook_before, i = triggers.length - 1; i >= 0; --i)
								triggers[i][0]['closeWorkbook_before'].call(parent, triggers[i][1], wbMeta.ghn, wbMeta.name);

							for (var triggers = Jedox.wss.events.triggers.closeWorkbook_after, i = triggers.length - 1; i >= 0; --i)
								triggers[i][0]['closeWorkbook_after'].call(parent, triggers[i][1], wbMeta.ghn, wbMeta.name);
						} catch (e) {
							Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
						}
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
						id: 'sRecoverDlg_ok_btn',
						text: 'OK'.localize(),
						tabIndex: 10,
						handler: function(){
							var asIdx = '';

				    		if (radioRecov.getValue()) {
				    			var selModel = grid.getSelectionModel();

				    			if (selModel.getCount())
				    				asIdx = selModel.getSelected().get('idx');
				    		}

			    			var obj = typeof loadArgs[4] == 'object' ? loadArgs[4] : {};

		    				if (isFs) {
		    					if (!obj.frames)
		    						obj.frames = {};

		    					obj.frames[nLoadArgs.g.concat('-', nLoadArgs.h, '-', nLoadArgs.n)] = {asid: asIdx};
		    				} else
		    					obj.asid = asIdx;

			    			if (loadArgs[4])
			    				loadArgs[4] = obj;
			    			else {
				    			var loadArgsCopy = [];

				    			for (var i = 0, largs = loadArgs, lalen = loadArgs.length; i < lalen; i++)
				    				loadArgsCopy.push(largs[i]);

				    			loadArgs = loadArgsCopy;

				    			loadArgs.splice(4, 0, obj);
				    		}

			    			that.resetInputMode();

				    		Jedox.wss.node.recover(cb, that.win, loadArgs);
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						id: 'sRecoverDlg_cancel_btn',
						text: 'Cancel'.localize(),
						tabIndex: 11,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.resetInputMode();
							Jedox.wss.events.enableEvents(['switchWorkbook_before', 'switchWorkbook_after']);
							that.win.close();
						}
					}))
			]
		});

		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Recover, Jedox.dlg.Dialog);