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
 * SVN: $Id: PictureProperties.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */

Jedox.wss.dlg.openPictureProperties = function(conf) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PitureProperties(conf));
};

Jedox.wss.dlg.PitureProperties = (function() {

	return function (conf) {

		Jedox.wss.dlg.PitureProperties.parent.constructor.call(this);
		this.id = 'PitureProperties';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		/* components */

		var spp = this.containers.mainp = new Ext.Panel({
			title: 'Size & Position'.localize(),
			border: false,
			id: 'SPPan',
			bodyStyle: 'background-color:transparent;',
			layout: 'form',
			labelWidth: 110,
        	autoWidth: true,
        	autoHeight: true,
        	style: 'padding:2px;',
        	items: [{}]
		});

		var tabs = new Ext.TabPanel({
			region: 'center',
			xtype: 'tabpanel',
			id: 'maintabspanel',
			layoutOnTabChange: true,
			activeTab: 0,
			ctCls: 'tb-no-bg',
			autoHeight: true,
			baseCls: 'x-plain',
			bodyStyle: 'background-color: transparent; padding: 5px;',
			defaults: {
				autoScroll: false
			},
			items: [spp],
			listeners: {
				tabchange: function(p, t){
				}
			}
		});

		var getSizePosPan = function(panel){
			spp.removeAll(true);
			spp.add(panel);
			spp.doLayout();
			Ext.getCmp('FE-SE-panel').setSPData(conf);
		};

		//conf.type, conf
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.FESizePositionPanel, [getSizePosPan, 'Picture', false]);


		var doFormatPicture = function(){
			var dims = Ext.getCmp('FE-SE-panel').getSPData();

			// error check
			if (!dims){
				Ext.MessageBox.show({
					title: "Error".localize(),
					msg: "invalid_picture_size".localize(),
					buttons: Ext.Msg.OK,
					icon: Ext.MessageBox.ERROR
				});
				return false;
			};

			// call handler for repositioning and resizing
			if (conf.psHnd)
				conf.psHnd.call(conf.scope, dims);

			// close win after success
			that.win.close();
		}

		/* *** */

		this.win = new Ext.Window({
	        title: 'Picture Properties'.localize(),
	        closable: true,
	        cls: 'default-format-window',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
	        width: 280,
	        height: 320,
	        // border:false,
	        layout: 'form',
	        items: [tabs],
	        onEsc: Ext.emptyFn,
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.pictureProperties);
				},
				show:function(){
					setTimeout(function(){
						//that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			},
	        buttons: [
					(this.components.OK = new Ext.Button({
						text: 'OK'.localize(),
						tabIndex: 100,
						handler: function(){
							doFormatPicture();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						text: 'Cancel'.localize(),
						tabIndex: 101,
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

Jedox.util.extend(Jedox.wss.dlg.PitureProperties, Jedox.dlg.Dialog);
