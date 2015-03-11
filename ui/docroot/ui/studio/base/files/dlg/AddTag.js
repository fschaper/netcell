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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: AddTag.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */
Jedox.studio.files.dlg.addTag = function(tagData){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.Tag(tagData));
};

Jedox.studio.files.dlg.Tag = (function(){

	// class constructor
	return function (tagData) {

		Jedox.studio.files.dlg.Tag.parent.constructor.call(this);

		this.id = 'addTag';
		var that = this;

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;


		//================================ Components ============================================

		var tagNameTxf = this.cmpFocus = new Ext.form.TextField({
			fieldLabel: 'Tag Name'.localize(),
			tabIndex: 1,
			labelStyle: 'font-size:11px;',
			//emptyText:sheetTitle,
			enableKeyEvents: true,
			width: 150
		});


		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainpan = new Ext.Panel({
			modal:true,
			layout: 'form',
			baseCls:'main-panel',
			border:false,
			items:[tagNameTxf]
		});


		//================================Functions ============================================


		function onOK(){
			var name = tagNameTxf.getValue();

				Jedox.backend.rpc([this,Ext.emptyFn], 'common', 'addTagged', ['files', 'spreadsheet', tagData, name]);

				that.win.close()
		}

		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px'},
					title:'New Tag'.localize(),
					closable: true,
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 300,
					height: 110,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function(){
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.addTag);
						},
						show:function(){
							setTimeout(function(){
								that.initFocus(true, 300);
							});
						},
						activate: function(win) {that.activate();}
					},
					buttons: [
						(this.components.OK = new Ext.Button({
							text: 'OK'.localize(),
							tabIndex: 10,
							handler: onOK
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							tabIndex: 11,
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

Jedox.util.extend(Jedox.studio.files.dlg.Tag, Jedox.dlg.Dialog);
