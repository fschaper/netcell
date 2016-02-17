/*
 * @brief GoTo dialog class.
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
 * SVN: $Id: GoTo.js 3513 2010-07-13 15:09:50Z drazenk $
 *
 */

Jedox.wss.dlg.openGoTo = function() {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.GoTo());
};

Jedox.wss.dlg.GoTo = (function () {

	// class constructor
	return function () {

		Jedox.wss.dlg.GoTo.parent.constructor.call(this);

		this.id = 'goTo';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		//================================ Components ============================================

		var goToTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Reference'.localize(),
			enableKeyEvents: true,
			width: 178,
			tabIndex: 1
		});

		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			labelWidth:60,
			modal:true,
			layout: 'form',
			baseCls:'main-panel',
			border:false,
			items:goToTxf
		});

		//================================Functions ============================================

		function doGoTo(){
			Jedox.wss.book.goTo(goToTxf.getValue());
		}


		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'Go To'.localize(),
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
					width: 280,
					height: 110,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;

							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.goTo);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 100);
							});
						},
						activate: function(win) {that.activate();}
					},
					buttons: [(this.components.OK = new Ext.Button({
						text: 'OK'.localize(),
						tabIndex: 2,
						handler: function(){
							doGoTo();
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						text: 'Cancel'.localize(),
						tabIndex: 3,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))]

		});

		this.setContext();
		this.win.show(this);

	};

}
)();

// GoTo extends Dialog.
Jedox.util.extend(Jedox.wss.dlg.GoTo, Jedox.dlg.Dialog);
