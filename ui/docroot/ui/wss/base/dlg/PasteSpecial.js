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
 * SVN: $Id: PasteSpecial.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */

Jedox.wss.dlg.openPasteSpecial = function(sheetID, sheetTitle) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PasteSpecial(sheetID, sheetTitle));
};

Jedox.wss.dlg.PasteSpecial = (function() {

	return function (sheetID, sheetTitle) {

		Jedox.wss.dlg.PasteSpecial.parent.constructor.call(this);
		this.id = 'PasteSpecial';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
		Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);


		var allRb=new Ext.form.Radio({
			hideLabel: true,
			checked:true,
			tabIndex: 1,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			boxLabel: 'All'.localize(),
			name: 'rb-paste',
			handler:function(){if (this.getValue())onRBCheck(true);}
		});

		var contentTypesRb=new Ext.form.Radio({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 2,
			boxLabel: 'Content Types'.localize(),
			name: 'rb-paste',
			handler:function(){if (this.getValue())onRBCheck(false);}
		});

		var formulasChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 3,
			boxLabel: 'Formulas'.localize(),
			checked:true
		});

		var valuesChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 4,
			boxLabel: 'Values'.localize(),
			checked:true
		});

		var stylesChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 5,
			boxLabel: 'Styles'.localize(),
			checked:true
		});

		var formatsChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 6,
			boxLabel: 'Formats'.localize(),
			checked:true
		});

		var conditionalFormatsChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 7,
			boxLabel: 'Conditional Formats'.localize(),
			checked:true
		});

		var cellMetadataChb=new Ext.form.Checkbox({
			hideLabel: true,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			tabIndex: 8,
			boxLabel: 'Cell Metadata'.localize(),
			checked:true
		});

		var rbPanel = new Ext.Panel({
			layout: 'form',
			border: false,
			defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
			baseCls: 'x-plain',
			x:10,
			y:10,
			items: [allRb, contentTypesRb]
		});

		var contentTypePanel = new Ext.Panel({
			layout: 'form',
			border: false,
			defaults: {bodyStyle: 'background-color: transparent; padding:10px 5px 5px 10px;'},
			baseCls: 'x-plain',
			x:30,
			y:65,
			items: [formulasChb, valuesChb, stylesChb, formatsChb, conditionalFormatsChb, cellMetadataChb]
		});

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			layout: 'absolute',
			baseCls:'main-panel',
			border:false,
			items:[
				rbPanel,
				contentTypePanel
			]
		});


		this.win = new Ext.Window({
			id:'paste-special-dlg',
			defaults: {bodyStyle:'padding:10px'},
			cls: 'default-format-window',
			title:'Paste Special'.localize(),
			closable: true,
			closeAction: 'close',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			width: 200,
			height: 330,
			items: mainPanel,
			onEsc: Ext.emptyFn,
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.pasteSpecial);
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
						tabIndex: 10,
						handler: function(){
							var paste = getPasteValue();
							that.win.close();
							Jedox.wss.action.paste(paste);
						}
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
		onRBCheck(true);

		function onRBCheck(all){
			if (all){
				formulasChb.disable();
				formulasChb.setValue(all);
				valuesChb.disable();;
				valuesChb.setValue(true);
				stylesChb.disable();;
				stylesChb.setValue(all);
				formatsChb.disable();;
				formatsChb.setValue(all);
				conditionalFormatsChb.disable();;
				conditionalFormatsChb.setValue(all);
				cellMetadataChb.disable();;
				cellMetadataChb.setValue(all);
			}
			else {
				formulasChb.enable();
				formulasChb.setValue(false);
				valuesChb.enable();
				valuesChb.setValue(true);
				stylesChb.enable();
				stylesChb.setValue(false);
				formatsChb.enable();
				formatsChb.setValue(false);
				conditionalFormatsChb.enable();
				conditionalFormatsChb.setValue(false);
				cellMetadataChb.enable();
				cellMetadataChb.setValue(false);
			}

		}

		function getPasteValue(){

			var contType = Jedox.wss.range.ContentType;

			if (allRb.getValue())
				var paste = contType.ALL_PASTE;
			else {
				var formulas = formulasChb.getValue() ? contType.FORMULA : 0;
				var values = valuesChb.getValue() ? contType.VALUE : 0;
				var styles = stylesChb.getValue() ? contType.STYLE : 0;
				var format = formatsChb.getValue() ? contType.FORMAT : 0;
				var conditionalFormat = conditionalFormatsChb.getValue() ? contType.CNDFMT : 0;
				var cellMetadata = cellMetadataChb.getValue() ? contType.ATTRS : 0;
				var paste =  formulas | values | styles | format | conditionalFormat | cellMetadata;
			}

			return paste;
		}

	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PasteSpecial, Jedox.dlg.Dialog);