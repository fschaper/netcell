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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: ArrangeWindows.js 4692 2011-03-11 14:53:13Z lukap $
 *
 */

Jedox.wss.dlg.openArrangeWindows = function()
{
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.ArrangeWindows());
};

Jedox.wss.dlg.ArrangeWindows = (function() {

	return function () {

		Jedox.wss.dlg.ArrangeWindows.parent.constructor.call(this);
		this.id = 'ArrangeWindows';
		var that = this;

		var _config = {
			winW: 200,

			tiled: {
				1: [
					{w:1, h:1}
				],
				2: [
					 {w:1/2, h:1}, {w:1/2, h:1}
				],
				3: [
					 {w:1/2, h:1}, {w:1/2, h:1/2}, {w:1/2, h:1/2}
				],
				4: [
					 {w:1/2, h:1/2}, {w:1/2, h:1/2}, {w:1/2, h:1/2}, {w:1/2, h:1/2}
				],
				5: [
					 {w:1/3, h:1}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}
				],
				6: [
					 {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}
				],
				7: [
					 {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}
				],
				8: [
					 {w:1/3, h:1/2}, {w:1/3, h:1/2}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}
				],
				9: [
					 {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}, {w:1/3, h:1/3}
				],
				10: [
					 {w:1/4, h:1/2}, {w:1/4, h:1/2}, {w:1/4, h:1/2}, {w:1/4, h:1/2}, {w:1/4, h:1/3}, {w:1/4, h:1/3}, {w:1/4, h:1/3}, {w:1/4, h:1/3}, {w:1/4, h:1/3}, {w:1/4, h:1/3}
				]
		}
		}
		var winsArrangement = ((Jedox.wss.wnd.arrangement) ? Jedox.wss.wnd.arrangement : 'tiled');

		function doArrangeWins(){
			var arrWins = Jedox.wss.wnd.getVisible();
			var numOfWins = arrWins.length;

			if (numOfWins > 0)
			{
				var workspaceSize = Ext.get('workspace').getSize();
				if (Jedox.wss.wnd.hasMinimized())
					workspaceSize.height -= arrWins[0].header.getSize().height + 4;

				if (rbTiled.getValue())
				{
					if (Jedox.wss.wnd.arrangement)
						Jedox.wss.wnd.arrangement = 'tiled';

					var widthAdjuster = ((arrWins.length == 1) ? 1 : 0); // workaround for Max window
					if (arrWins.length <= 10)
					{
						for (var winW, winH, cordX=0, cordY=0, i=0; i<arrWins.length; i++)
						{
							winW = workspaceSize.width * _config.tiled[arrWins.length][i].w - widthAdjuster;
							winH = workspaceSize.height * _config.tiled[arrWins.length][i].h;

							if (arrWins[i].maximized)
								arrWins[i].restore();
							arrWins[i].setSize(winW, winH);
							arrWins[i].setPosition(cordX, cordY);

							if ((cordY + winH + 1) > workspaceSize.height)
							{
								cordY = 0;
								cordX += winW;
							}
							else
								cordY += winH;
						}
					}
				}
				else if (rbHorizontal.getValue())
				{
					if (Jedox.wss.wnd.arrangement)
						Jedox.wss.wnd.arrangement = 'horizontal';

					var winW = workspaceSize.width  - ((arrWins.length == 1) ? 1 : 0);;
					var winH = workspaceSize.height / numOfWins;

					var cordX = 0;
					var cordY = 0;
					for (var i = 0; i < numOfWins; i++)
					{
						if (arrWins[i].maximized)
							arrWins[i].restore();
						arrWins[i].setSize(winW, winH);
						arrWins[i].setPosition(cordX, cordY);

						cordY += winH;
					}
				}
				else if (rbVertical.getValue())
				{
					if (Jedox.wss.wnd.arrangement)
						Jedox.wss.wnd.arrangement = 'vertical';

					var winW = workspaceSize.width / numOfWins  - ((arrWins.length == 1) ? 1 : 0);;
					var winH = workspaceSize.height;

					var cordX = 0;
					var cordY = 0;
					for (var i = 0; i < numOfWins; i++)
					{
						if (arrWins[i].maximized)
							arrWins[i].restore();
						arrWins[i].setSize(winW, winH);
						arrWins[i].setPosition(cordX, cordY);

						cordX += winW;
					}
				}
				else if (rbCascade.getValue())
				{
					if (Jedox.wss.wnd.arrangement)
						Jedox.wss.wnd.arrangement = 'cascade';

					if (arrWins.length)
					{
						var menuH = arrWins[0].header.getSize().height;
					}
					else
					{
						var menuH = 0;
					}

					var winW = workspaceSize.width - (menuH * (numOfWins - 1)) - ((arrWins.length == 1) ? 1 : 0);;
					var winH = workspaceSize.height - (menuH * (numOfWins - 1));

					var cordX = 0;
					var cordY = 0;
					for (var i = (numOfWins - 1); i >= 0; i--)
					{
						if (arrWins[i].maximized)
							arrWins[i].restore();
						arrWins[i].setSize(winW, winH);
						arrWins[i].setPosition(cordX, cordY);

						cordX += menuH;
						cordY += menuH;
					}
				}
			}

		};

		// +++ Buttons +++ //
		var btnOk = (this.components.OK = new Ext.Button({
			id: 'wArrangeWin_ok_btn',
			text: 'OK'.localize(),
			tabIndex: 10,
			handler: function(){
				doArrangeWins();
				that.win.close();
			}
		}));

		var btnCancel = (this.components.Cancel = new Ext.Button({
			id: 'wArrangeWin_cancel_btn',
			text: 'Cancel'.localize(),
			tabIndex: 11,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			handler: function(){
				that.win.close();
			}
		}));
		// --- Buttons --- //

		// +++ Radio Buttons +++ //
		var rbTiled = new Ext.form.Radio({
			id: 'wArrangeWin_tiled_rd',
			checked: (winsArrangement == 'tiled'),
			name: 'radioArrange',
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			boxLabel: "Tiled".localize(),
			hideLabel: true
		});
		var rbHorizontal = new Ext.form.Radio({
			id: 'wArrangeWin_horizontal_rd',
			checked: (winsArrangement == 'horizontal'),
			name: 'radioArrange',
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			boxLabel: "Horizontal".localize(),
			hideLabel: true
		});
		var rbVertical = new Ext.form.Radio({
			id: 'wArrangeWin_vertical_rd',
			checked: (winsArrangement == 'vertical'),
			name: 'radioArrange',
			tabIndex: 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			boxLabel: "Vertical".localize(),
			hideLabel: true
		});
		var rbCascade = new Ext.form.Radio({
			id: 'wArrangeWin_cascade_rd',
			checked: (winsArrangement == 'cascade'),
			name: 'radioArrange',
			tabIndex: 4,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			boxLabel: "Cascade".localize(),
			hideLabel: true
		});
		// --- Radio Buttons --- //

		// *** Arange FieldSet *** //
		var fsArrange = new Ext.form.FieldSet({
			title: "Arrange".localize(),
			autoHeight: true,
			collapsible: false,
			items: [rbTiled, rbHorizontal, rbVertical, rbCascade]
		});

		// *** Main Panel *** //
		var panelMain = this.containers.mainPanel = new Ext.Panel({
			autoHeight: true,
			layout: 'fit',
			bodyStyle: 'padding: 5px 5px 0px; background-color: transparent;',
			items: [fsArrange]
		});

		// *** Window *** //
		this.win = new Ext.Window({
			hidden: true,
			layout: 'fit',
			title: "Arrange Windows".localize(),
			width: _config.winW,
			autoHeight: true,
			closeAction: 'close',
			cls: 'default-format-window',
			autoDestroy: true,
			plain: true,
			onEsc: Ext.emptyFn,
			modal: true,
			resizable: false,
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.arrangeWindows);

				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
			items: [panelMain],
			buttons: [btnOk, btnCancel]
		});

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.ArrangeWindows, Jedox.dlg.Dialog);
