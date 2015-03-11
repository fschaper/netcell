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
 * SVN: $Id: AutoRefresh.js 4426 2010-12-09 13:34:27Z srdjanv $
 *
 */

Jedox.wss.dlg.autoRefreshStart = function(){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.AutoRefresh());
};

Jedox.wss.dlg.AutoRefresh = (function() {

	return function () {

		Jedox.wss.dlg.AutoRefresh.parent.constructor.call(this);
		this.id = 'AutoRefresh';
		var that = this;


		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		var autoRefreshLbl = new Ext.form.Label({
			text:'Refresh every'.localize().concat(':')
		});

		var unitTxf = this.cmpFocus = new Ext.form.TextField({
			hideLabel: true,
			tabIndex: 1,
			allowBlank: false,
			width: 50
		});

		var unitLbl = new Ext.form.Label({
			text:'seconds'.localize().concat(' ', '(', 'min 10'.localize(), ').')
		});

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			layout:'column',
			border:false,
			baseCls: 'x-plain',
			bodyStyle: 'background-color: transparent;',
			autoWidth:true,
			height:100,
			defaults: {
				baseCls:'x-plain',
				autoWidth:true,
				bodyStyle:'padding:4px;'
		    },
			items:[{
			    items:autoRefreshLbl
			},{
			    items:unitTxf
			},{
			    items:unitLbl
			}]
		});

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px 5px 5px 5px'},
					title:'Auto Refresh'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        cls: 'default-format-window',
			        plain: true,
			        onEsc: Ext.emptyFn,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 340,
					height: 115,
					items: mainPanel,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.autoRefreshStart);
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
								text: 'OK'.localize(),
								tabIndex: 2,
								handler: function(){
									if (validate()) {
										startTimer();
										that.win.close();
									}
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

		function validate(){
			var v = unitTxf.getValue();
			if(parseInt(v)){
				 if (parseInt(v) < 10) {
				 	unitTxf.markInvalid('Minimum value is 10'.localize());
				 	return false;
				 }
			}
			else {
				unitTxf.markInvalid('Not correct format'.localize());
				return false;
			}

			return true;
		}

		function startTimer(){
			Jedox.wss.book.autoRefresh(unitTxf.getValue());
		}

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.AutoRefresh, Jedox.dlg.Dialog);