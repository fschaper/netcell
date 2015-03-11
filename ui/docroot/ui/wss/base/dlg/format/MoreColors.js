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
 * SVN: $Id: MoreColors.js 3458 2010-07-02 13:51:23Z drazenk $
 *
 */

Jedox.wss.dlg.format.moreColors = function(backgroundColorValue, cbFunc) {
		Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.format.MoreColors(backgroundColorValue, cbFunc));
	};

Jedox.wss.dlg.format.MoreColors = (function() {

		return function (backgroundColorValue, cbFunc) {

			Jedox.wss.dlg.format.MoreColors.parent.constructor.call(this);
			this.id = 'more-colors-window';
			var that = this;

			colorPicker = new Ext.ux.ColorPicker( {
				xtype : 'colorpicker',
				title : 'ColorPicker',
				id : 'panelPicker',
				opacity: false,
				value : backgroundColorValue
			});

			var mainCPPanel = new Ext.Panel({
				baseCls: 'x-plain',
				items: [colorPicker]
			});

			this.win = new Ext.Window( {
				title : 'More Colors'.localize().concat('...'),
				closable : true,
				id : 'colorPickerField',
				autoDestroy : true,
				plain : true,
				constrain : true,
				modal : true,
				resizable : false,
				animCollapse : false,
				width : 340,
				heigh : 200,
				// border:false,
				layout : 'form',
				onEsc: Ext.emptyFn,
				listeners: {
					close: function()
					{
						that.close();
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 100);
						});
					},
					activate: function(win) {that.activate();}
				},
				items : [ mainCPPanel ],
				buttons : [
				           (this.components.OK = new Ext.Button({
								text: 'OK'.localize(),
								tabIndex: 100,
								handler: function(){
					        	   var tmpColor = Ext.getCmp('panelPicker__iHexa').getValue();
					        	   that.win.close();
					        	   cbFunc(0, tmpColor, 0, 0);
								}
							})),
				           (this.components.Cancel = new Ext.Button({
								text: 'Cancel'.localize(),
								tabIndex: 101,
								ctCls: Jedox.kbd.Base.tags.NO_ENTER,
								handler: function(){
									that.win.close();
								}
							}))]
			});


			this.setContext();
			this.win.show(this);
			this.containers.rgbPan = Ext.getCmp('colorPickerFormContainer');
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.format.MoreColors, Jedox.dlg.Dialog);