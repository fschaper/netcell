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
 * SVN: $Id: ConstListEditorWin.js 4913 2011-04-29 12:53:16Z lukap $
 *
 */

Jedox.dlg.openConstListEditorWin = function(initArray, tof, from)
{
	Jedox.dlg.dlgRegistry.add(new Jedox.dlg.ConstListEditorWin(initArray, tof, from));
};

Jedox.dlg.ConstListEditorWin = (function () {

	// class constructor
	return function (initArray, tof, from) {

		Jedox.dlg.ConstListEditorWin.parent.constructor.call(this);

		this.id = 'wConstListSel_dlg_wnd';
		var that = this;

		this.win = new Ext.Window({
			title: 'Constants List Selection'.localize(),
			closable: true,
			id: 'wConstListSel_dlg_wnd',
			autoDestroy: true,
			plain: true,
			cls: 'default-format-window',
			constrain: true,
			modal: true,
			resizable: false,
			animCollapse: false,
			width: 450,
			height: 350,
			layout: 'fit',
			listeners: {
				close: function()
				{
					that.close();
					if (from == 'wss'){
						Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
						Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.openConstListEditorWin);
					} else {
						Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
						Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openConstListEditorWin);
					}
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
		items: [(this.containers.mp = new ConstListEditor({
			id: 'constListEditor',
			style: 'margin: 10px;',
			baseCls: 'x-plain',
			list: initArray
		}))],
		buttons: [(this.components.OK = new Ext.Button({
			text: 'OK'.localize(),
			id: 'wConstListSel_ok_btn',
			tabIndex: 101,
			handler: function() {
			//// here set map
			var lista = Ext.getCmp('constListEditor').getList();
			lista = lista.join(",");
			// set value in store
			Ext.getCmp(tof).setValue(lista);
			that.win.close();
		}
		})),
		(this.components.Cancel = new Ext.Button({
			text: 'Cancel'.localize(),
			id: 'wConstListSel_cancel_btn',
			tabIndex: 102,
			handler: function() {
				that.win.close();
			}
		}))]
		});

		this.setContext();
		this.win.show(this);

	};
}
)();

Jedox.util.extend(Jedox.dlg.ConstListEditorWin, Jedox.dlg.Dialog);