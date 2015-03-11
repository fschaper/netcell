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
 * SVN: $Id: Find.js 4584 2011-02-09 10:39:11Z srdjanv $
 *
 */

Jedox.wss.dlg.openFindDialog = function(pattern, callBackFnc) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Find(pattern, callBackFnc));
};

Jedox.wss.dlg.Find = (function() {

	return function (pattern, callBackFnc) {

		Jedox.wss.dlg.Find.parent.constructor.call(this);
		this.id = 'findDlg';
		var that = this;



		var _fromDlgF = false;

		if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
			_fromDlgF=true;
		else {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}


		//================================ Components ============================================

		var patternTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Find what'.localize(),
			enableKeyEvents: true,
			tabIndex: 1,
			value:pattern,
			width: 170
		});


		var findBtn = this.components.OK = new Ext.Button({
			text: 'Find'.localize(),
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			width: 70,
			handler: function(){
				callBackFnc(patternTxf.getValue());
			}
		});

		var cancelBtn = this.components.Cancel = new Ext.Button({
			text: 'Cancel'.localize(),
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 3,
			width: 70,
			handler: function(){
				that.win.close();
			}
		});

		var findBtnPanel = new Ext.Panel({
			layout:'card',
			baseCls: 'x-plain',
			style: 'padding-top: 8px;',
			activeItem:0,
			items:[{
				layout:'form',
				border:false,
				baseCls: 'x-plain',
				items:[findBtn]
			}]
		});

		var cancelBtnPanel = new Ext.Panel({
			layout:'card',
			baseCls: 'x-plain',
			style: 'padding-top: 8px;',
			activeItem:0,
			items:[{
				layout:'form',
				border:false,
				baseCls: 'x-plain',
				items:[cancelBtn]
			}]
		});


		//================================ Main Panel ============================================

			var mainPanel = this.containers.mainPanel = new Ext.Panel({
				layout: 'absolute',
				baseCls: 'x-plain',
				border: false,
				items:[{
					layout: 'form',
					border: false,
					baseCls: 'x-plain',
					x: 5,
					y: 12,
					width: 285,
					height: 100,
					items: [patternTxf]
				},
				{
					layout:'form',
					baseCls: 'x-plain',
					x: 290,
					y: 5,
					height:90,
					items:[findBtnPanel, cancelBtnPanel]
	//				buttons:[findBtnPanel, ]
				}]
			});


		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
			defaults: {bodyStyle:'padding:10px'},
			title:'Find'.localize(),
			closable: true,
			closeAction: 'close',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        cls: 'default-format-window',
	        modal: true,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			onEsc: Ext.emptyFn,
			width: 400,
			height: 130,
			items: mainPanel,
			listeners: {
				close: function()
				{
					if (!_fromDlgF) {
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					}
						that.close();
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.find);
				},
				show:function(){
					setTimeout(function(){
						that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			}
		});


		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Find, Jedox.dlg.Dialog);