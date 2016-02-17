/*
 * @brief Cell editor for large Palo text values (with new line, etc.)
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: CellTextEditor.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */

Jedox.wss.palo.openCellTE = function(cellCords) { Jedox.dlg.dlgRegistry.add(new Jedox.wss.palo.CellTextEditor(cellCords)); };

Jedox.wss.palo.CellTextEditor = function(cellCords)
{
	Jedox.wss.palo.CellTextEditor.parent.constructor.call(this);
	this.id = 'paloTextEditor';
	var that = this;

	Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

	//================================ Components ============================================
	var activePane = Jedox.wss.app.activePane,
		tmpVal = activePane.getCellValue(cellCords[0], cellCords[1]);

	var editAreaConf = {
		tabIndex: 1,
		hideLabel: true,
		width: 500,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		value: tmpVal
	};

	if (Ext.isWebKit)
		editAreaConf.style = 'height: 200px !important;';
	else
		editAreaConf.height = 200;

	var editArea = this.cmpFocus = new Ext.form.TextArea(editAreaConf);

	//================================ Main Panel ============================================
	var mainPanel = this.containers.mainPanel = new Ext.Panel({
		modal: true,
		layout: 'form',
		baseCls: 'main-panel',
		border: false,
		items: editArea
	});

	//================================ Window (Dlg) ============================================
	this.win = new Ext.Window({
		defaults: {bodyStyle: 'padding:10px'},
		title: 'String Editor'.localize(),
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
		width: 536,
		height: 288,
		items: mainPanel,
		onEsc: Ext.emptyFn,
		listeners:
		{
			close: function()
			{
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;

				that.close();

				Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.paloTextEditor);
			},
			show: function()
			{
				setTimeout(function()
				{
					that.initFocus(true, 100);
				});
			},
			activate: function(win) { that.activate(); }
		},
		buttons:
		[
			(this.components.OK = new Ext.Button({
				text: 'OK'.localize(),
				tabIndex: 2,
				handler: function()
				{
					// Set Value for Edited function
//					activePane.setCellValue(cellCords[0], cellCords[1], editArea.getValue());
//					that.win.close();

					var col = cellCords[0],
						row = cellCords[1],
						fnc = activePane.getCellFormula(col, row),
						fncParts = fnc.match(new RegExp('^=PALO.DATAC?\\((.*)\\)$')),
						numericSeps = Jedox.wss.i18n.separators,
						bknd = Jedox.backend,
						ccmdReq = new Jedox.backend.CCmdDiffAsyncRqst(
							[ [ 'cdrn', { cm: true }, [ col, row, col, row, { v: '=PALO.SETDATA("'.concat(editArea.getValue().replace(/"/g, '""').replace(/\r/g, ''), '"', numericSeps[2], Jedox.wss.i18n.bool[false], numericSeps[2], fncParts[1], ')') } ], [ col, row, col, row, { v: fnc } ] ] ],
							bknd.Q_VALUE | bknd.Q_STYLE | bknd.Q_ATTRS | bknd.Q_FMT_VAL | bknd.Q_LOCK,
							bknd.D_NONE
						);

					ccmdReq.setOnSuccess([ that.win, that.win.close ]);
					ccmdReq.send();
				}
			})),
			(this.components.Cancel = new Ext.Button({
				text: 'Cancel'.localize(),
				tabIndex: 3,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function()
				{
					that.win.close();
				}
			}))
		]
	});

	this.setContext();
	this.win.show(this);
};

Jedox.util.extend(Jedox.wss.palo.CellTextEditor, Jedox.dlg.Dialog);