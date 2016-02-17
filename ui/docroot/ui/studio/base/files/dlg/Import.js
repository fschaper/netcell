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
 * SVN: $Id: Import.js 5130 2011-07-19 10:03:10Z srdjanv $
 *
 */

Jedox.studio.files.dlg.importFile = function(arr, ghp){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.files.dlg.Import(arr, ghp));
};

Jedox.studio.files.dlg.Import = (function(){

	//class constructor
	return function (arr, ghp) {

		Jedox.studio.files.dlg.Import.parent.constructor.call(this);

		this.id = 'importFile';
		var that = this;

	    Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
	    Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		//Handler functions.
		var onBeforeDestroyDialog = function (panel) {
			// Destroy all form elements and destroy self the form
			importForm.items.each(function(f) {
	            f.purgeListeners();
	            Ext.destroy(f);
	        });
	        importForm.purgeListeners();
			importForm.destroy();
		}

		// file validation
		/*
		var validateFile = function (fieldValue) {
			if ((fieldValue.length > 4) && (fieldValue.lastIndexOf('.wss') == fieldValue.length - 4))
				{
				Ext.getCmp('import-upload-btn').enable();
				return true;
				}
			else {
				Ext.getCmp('import-upload-btn').disable();
				return "Wrong File Type! Please choose .wss file!".localize();
			}
		}
		*/

		// Upload file
		var doUploadFile = function () {

			var convert = (!convertChb.hidden && convertChb.getValue())? 1:0;

			for (var i = 0, file = fileUpload.getValue().split('.'), count = arr.length, name, ext; i < count; i++) {
				name = arr[i].data.text;
				ext = (arr[i].data.iconCls.split('_').pop());
				if (file[0] == name && ((ext == 'workbook')? 'wss':ext) == (convert? 'wss':file[1])) {
					Jedox.studio.app.showMessageERROR('Error'.localize(), 'upload_err_file_exists'.localize());
					return false;
				}
			}

			var frameID = 'studioImportFrame';
			var frame = Ext.get('studioImportFrame');

			if (!frame) {
				frame = document.createElement('iframe');
				frame.id = frameID;
				frame.name = frameID;
				frame.className = 'x-hidden';

				if(Ext.isIE){
					frame.src = Ext.SSL_SECURE_URL;
				}

				document.body.appendChild(frame);

				if(Ext.isIE){
					document.frames[frameID].name = frameID;
				}
			}

	        var form = Ext.getDom(importForm.getForm().getEl());
	        form.target = frameID;
	        form.method = 'POST';
			form.action = '/be/studio/import.php?convert='.concat(convert);
	        form.enctype = form.encoding = 'multipart/form-data';

	        var fileName = fileUpload.value.split('.')[0];
	        try {
				form.submit();
				dialogWindow.close();
			} catch (e) {
				Jedox.studio.app.showMessageERROR('Application Error'.localize(), e.message.localize());
				return false;
			}
		}

		var fileUpload = this.cmpFocus = new Ext.ux.form.FileUploadField({
	        fieldLabel: "File to Import".localize(),
			emptyText: "impDlg_msgFieldBlank".localize().concat('!'),
			buttonText: "Browse".localize().concat('...'),
			defaultAutoCreate: {tag: "input", type: "text", size: "65", autocomplete: "off"},
			width:420,
			id: 'filepath',
			name: 'import_file',
			//validator: validateFile,
			listeners:{
				fileselected:function(fld, val){
					convertChb.setValue(false);
					val.split('.').pop() == 'xlsx' ? convertChb.show():convertChb.hide();

				}
			}
	    });


		var convertChb=new Ext.form.Checkbox({
			boxLabel: 'Convert'.localize(),
			tabIndex: 3,
			ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			hideLabel:true,
			hidden:true,
			checked:false
		});


		var convertPanel = new Ext.Panel({
			bodyStyle: 'padding:0px 7px 0',
			baseCls:'x-plain',
			items:[convertChb]
		})

		var importForm = new Ext.FormPanel({
			baseCls: 'x-plain',
			labelWidth: 50,
			labelAlign: 'top',
			frame: true,
			bodyStyle: 'padding:5px 5px 0',
			width: 450,
			defaults: {width: 410},
			defaultType: 'textfield',
			buttonAlign: 'right',
			header: false,
			headerAsText: false,
			monitorValid: true,
			title: null,
			items: [
			fileUpload,
			 new Ext.form.Hidden({
				name: 'MAX_FILE_SIZE',
				value: '30000'
			}),
			new Ext.form.Hidden({
				name: 'importParentNode',
				value: ghp.p
			})]
		});

		var dialogWindow = this.win = new Ext.Window({
			id: 'importDlg',
			title: 'Import'.localize(),
			cls: 'wssdialog',
			layout: 'fit',
			width: 450,
			height: 160,
			closeable: true,
			closeAction: 'close',
			autoDestroy: true,
			plain: true,
			constrain: true,
			modal: true,
			items: [
				this.containers.mainPanel = new Ext.Panel({
			        baseCls: 'x-title-f',
			        labelWidth: 100,
			        labelAlign: 'left',
					layout: 'form',
					bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
			        frame: false,
			        header: false,
			        monitorValid: true,
			        autoHeight: true,
			        autoWidth: true,
			        items:[importForm, convertPanel]
				})
			],
			listeners: {
				close: function()
				{
					Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
					that.close();
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
					text: "Upload".localize(),
					id: 'import-upload-btn',
					tabIndex: 10,
					handler:doUploadFile,
					formBind: true
				})),
				(this.components.Cancel = new Ext.Button({
		            text: 'Close'.localize(),
					tabIndex: 11,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		            handler: function(){
						Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
						dialogWindow.destroy();
		            }
		        }))
			]
		});


		dialogWindow.on('beforedestroy', onBeforeDestroyDialog);
		dialogWindow.on('show', function() { var f = Ext.get('filepath'); f.focus.defer(100, f); });

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		this.setContext();
		this.win.show(this);
	}
})();

Jedox.util.extend(Jedox.studio.files.dlg.Import, Jedox.dlg.Dialog);

Jedox.studio.files.processImport = function(res) {
	if (!res || !res[0]) {
		Jedox.studio.app.showMessageALERT('Error'.localize(), 'error_importerror'.localize());
	}
	else{
		Ext.getCmp('wt-panel').importHandleFnc(res[1], !!(res[1].log));
	}

}