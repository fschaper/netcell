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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: Import.js 5110 2011-07-11 18:24:40Z djordjez $
 *
 */

Jedox.wss.dlg.openImportDialog = function () {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Import());
};

Jedox.wss.dlg.Import = (function() {

	return function () {

		Jedox.wss.dlg.Import.parent.constructor.call(this);
		this.id = 'import';
		var that = this;

		// Change input mode to DILAOG.
		if (Jedox.wss.app.environment != null) {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}

		// Handler functions.
		var onBeforeDestroyDialog = function (panel) {
			// Destroy all form elements and destroy self the form
			importForm.items.each(function(f) {
	            f.purgeListeners();
	            Ext.destroy(f);
	        });
	        importForm.purgeListeners();
			importForm.destroy();

			Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
			Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;

			Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.importFile);


		}

		var validateFile = function (fieldValue) {
			if ((fieldValue.length > 5) && (fieldValue.lastIndexOf('.xlsx') == fieldValue.length - 5))
				return true;
			else
				return "impDlg_msgWrongType".localize();
		}

		var doUploadFile = function () {
			var frameID = 'tmpUploadIFrame';
			var frame = Ext.get('tmpUploadIFrame')

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
			form.action = '/be/wss/upload.php?wam=designer';
	        form.enctype = form.encoding = 'multipart/form-data';

	        var fileName = fileUpload.value.split('.')[0];
	        try {
				for (var triggers = Jedox.wss.events.triggers.importWorkbook_before, i = triggers.length - 1, name = fileName; i >= 0; i--)
					triggers[i][0]['importWorkbook_before'].call(parent, triggers[i][1], name);

				form.submit();

				// set statusbar
				// please wait

				//that.win.hide();
				that.win.close();
			} catch (e) {
				Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
				return false;
			}
		}

		var fileUpload = this.cmpFocus = new Ext.ux.form.FileUploadField({
	        fieldLabel: "impDlg_fieldLbl".localize(),
	        tabIndex: 1,
			emptyText: "impDlg_msgFieldBlank".localize().concat('!'),
			defaultAutoCreate: {tag: "input", type: "text", size: "65", autocomplete: "off", accept: "*.xlsx"},
			width:420,
			id: 'filepath',
			name: 'workbook_file',
			validator: validateFile
	    });

		var importForm = this.containers.mainPanel = new Ext.FormPanel({
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
			})]
		});

		this.win = new Ext.Window({
			id: 'importDlg',
			title: 'Import'.localize(),
			cls: 'wssdialog default-format-window',
			layout: 'fit',
			width: 450,
			height: 160,
			closeable: true,
			closeAction: 'close',
			autoDestroy: true,
			onEsc: Ext.emptyFn,
			plain: true,
			constrain: true,
			modal: true,
			items: [
				new Ext.Panel({
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
		        items:[importForm]
				})
			],
			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
					Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.importFile);
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
						id: 'wImportDlg_import_btn',
						text: 'Upload'.localize(),
						tabIndex: 10,
						handler: function(){
							doUploadFile();
							that.win.close();
						}
					})),
					(this.components.Cancel = new Ext.Button({
						id: 'wImportDlg_cancel_btn',
						text: 'Cancel'.localize(),
						tabIndex: 11,
						ctCls: Jedox.kbd.Base.tags.NO_ENTER,
						handler: function(){
							that.win.close();
						}
					}))
			          ]
		});

		this.win.on('beforedestroy', onBeforeDestroyDialog);
		this.win.on('show', function() { var f = Ext.get('filepath'); f.focus.defer(100, f); });

		//that.win.show(this);
		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Import, Jedox.dlg.Dialog);

Jedox.wss.dlg.processImport = function (res, fileName)
{
	res = res[0];

	var importOk = res[0];

	if (importOk) {

		function cb(){

			try {
				fileName = fileName.split('.')[0];

				for (var triggers = Jedox.wss.events.triggers.importWorkbook_after, i = triggers.length - 1, name = fileName; i >= 0; i--)
					triggers[i][0]['importWorkbook_after'].call(parent, triggers[i][1], name, importOk);

				setTimeout(function(){
					Jedox.wss.general.showLogMsg('Import'.localize(), 'imp_success_msg'.localize().concat('<br><br>', 'Import log'.localize()), Ext.MessageBox.INFO, res[1].join ? res[1].join('\n') : res[1]);
				}, 200);

			}
			catch (e){
				Jedox.wss.general.showMsg('Application Error'.localize(), e.message.localize(), Ext.MessageBox.ERROR);
			}

		}

		Jedox.wss.book.load([this, cb], fileName);

	}
	else
		Jedox.wss.general.showMsg('Import Error'.localize(), 'imp_err_msg'.localize({name: fileName}), Ext.MessageBox.ERROR);

}