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
 * SVN: $Id: FormatColRow.js 4781 2011-03-29 08:16:54Z predragm $
 *
 */

Jedox.wss.dlg.openFormatColRow = function(type, size) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.FormatColRow(type, size));
};

Jedox.wss.dlg.FormatColRow = (function() {

	return function (type, size) {

		Jedox.wss.dlg.FormatColRow.parent.constructor.call(this);
		this.id = 'formatColRow';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var rowSize = new Ext.form.NumberField({
						id: 'wFormatColRow_rowSize_nf',
	                    fieldLabel: 'Row height'.localize(),
	                    width: 35,
	                    tabIndex: 1,
						layout: 'form',
						hideLabel : false,
						autoHeight: true,
						allowDecimals: false,
						enableKeyEvents: true,
						value: size,
						allowBlank: false,
						//maxValue: 128,
						labelSeparator: ':',
						labelStyle: 'margin: 0px;'
	                });

		var colSize = new Ext.form.NumberField({
						id: 'wFormatColRow_colSize_nf',
	                    //name: 'colsize',
	                    width: 35,
	                    tabIndex: 1,
						allowBlank: false,
						autoHeight: true,
						allowDecimals: false,
						value: size,
						layout: 'form',
						//maxValue: 128,
						hideLabel: false,
						enableKeyEvents: true,
						fieldLabel: 'Column width'.localize(),
						labelStyle: 'margin: 0px;'
	                });

		if (type == 0) {
			var displayField = this.cmpFocus = colSize;
			var winTitle = 'Column Width'.localize();
		}
		else if (type == 1) {
			var displayField = this.cmpFocus = rowSize;
			var winTitle = 'Row Height'.localize();
		};

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
	        id: 'sizetab',
	        bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
	        border: false,
	        frame: false,
			autoHeight: true,
			layout: 'form',
			items: [displayField]
		});

		/* *** Function *** */

		function doFormatColRow(){
			if (type == 0) {
				size = colSize.getValue();
			}
			else if (type == 1) {
				size = rowSize.getValue();
			};
				Jedox.wss.action.resizeRowCol(type, size);
		}

		/* *** */

		this.win = new Ext.Window({
			id: 'wFormatColRow_dlg_wnd',
	        title: winTitle,
	        closable: true,
	        cls: 'default-format-window',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
	        width: 180,
	        autoHeight: true,
	        // border:false,
	        layout: 'form',
	        items: [mainPanel],
	        onEsc: Ext.emptyFn,
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.wss.app.activeSheet._defaultSelection.getCursorField().refresh();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.formatColRow);
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
						id: 'wFormatColRow_ok_btn',
						text: 'OK'.localize(),
						tabIndex: 2,
						handler: function(){
							doFormatColRow();
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						id: 'wFormatColRow_cancel_btn',
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
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.FormatColRow, Jedox.dlg.Dialog);
