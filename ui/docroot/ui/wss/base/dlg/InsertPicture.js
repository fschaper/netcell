/*
 * \brief pictures handling code
 *
 * \file insertPicture.js
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: InsertPicture.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */

Jedox.wss.dlg.openInsertPicture = function (editObj) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.Picture(editObj));
};

Jedox.wss.dlg.Picture = (function() {

	return function (editObj) {

		Jedox.wss.dlg.Picture.parent.constructor.call(this);
		this.id = 'insPicture';
		var that = this;

		Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
	  	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);

		var validateFile = function (fieldValue)
		{
			var nameSize = fieldValue.length - 4;
			fieldValue = fieldValue.toUpperCase();
			if ((nameSize > 0) && ((fieldValue.lastIndexOf('.PNG') == nameSize) || (fieldValue.lastIndexOf('.GIF') == nameSize) || (fieldValue.lastIndexOf('.JPG') == nameSize) || (fieldValue.lastIndexOf('.JPEG') == (nameSize - 1))))
				return true;
			else
				return "impImg_msgWrongType".localize();
		}

		var fileUpload = new Ext.ux.form.FileUploadField({
	        emptyText: 'Select a picture'.localize(),
	        tabIndex: 1,
	        ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	        fieldLabel: '_lbl: picToImport'.localize(),
	        defaultAutoCreate: {tag: "input", type: "text", size: "65", autocomplete: "off"},
			width:420,
	        name: 'img_filename',
			validator: validateFile
	    });

		var formPanel = new Ext.form.FormPanel({
			layout: 'form',
			border:false,
			baseCls:'x-plain',
			labelWidth: 50,
			labelAlign: 'top',
			width: 450,
			defaults: {width: 410},
			defaultType: 'textfield',
			buttonAlign: 'right',
			items: [
				fileUpload
			]
		});

		var mainPanel = this.containers.mainpanel = new Ext.Panel({
			baseCls: 'main-panel',
			border: false,
			items: formPanel
		});

		this.win = new Ext.Window({
			defaults: {bodyStyle:'padding:10px 5px 5px 15px'},
			title: 'Insert Picture'.localize(),
			closable: true,
			closeAction: 'close',
			cls: 'default-format-window',
	        autoDestroy: true,
	        plain: true,
	        constrain: true,
	        modal: true,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			width: 450,
			height: 140,
			items: mainPanel,

			listeners: {
				close: function()
				{
					Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
					Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					that.close();
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
	            	text: 'Insert'.localize(),
	            	tabIndex: 10,
					handler: function()
					{
					 	if(formPanel.getForm().isValid())
		                {
		            		var frameID = 'tmpImportIFrame';
		            		var frame = Ext.get(frameID);

		            		if (!frame)
		            		{
		            			frame = document.createElement('iframe');
		            			frame.id = frameID;
		            			frame.name = frameID;
		            			frame.className = 'x-hidden';

		            			if(Ext.isIE)
		            				frame.src = Ext.SSL_SECURE_URL;

		            			document.body.appendChild(frame);

		            			if(Ext.isIE)
		            				document.frames[frameID].name = frameID;
		            		}

		            		if (editObj && editObj.id)
		            		{
		            			var imgWrapper = Ext.get(Jedox.wss.app.activePane._domId.concat('_wsel_cont_', editObj.id, '-rzwrap')),
		            				elX = imgWrapper.dom.offsetLeft,
		            				elY = imgWrapper.dom.offsetTop,
		            				zIndex = editObj.zindex,
		            				locked = editObj.locked,
		            				hldata = Ext.encode(editObj.hldata);
		            		}
		            		else
		            		{
			            		// get centered position of sheet
			            		var vportPos = Jedox.wss.app.activePane.getViewportPos(),
			            			elX = parseInt((vportPos[1][0] - vportPos[0][0]) / 2),
			            			elY = parseInt((vportPos[1][1] - vportPos[0][1]) / 2),
			            			zIndex = Jedox.wss.wsel.wselRegistry.getZIndex(),
			            			locked = Jedox.wss.wsel.Picture.defLockedState,
			            			hldata = "";
		            		}

		                    var form = Ext.getDom(formPanel.getForm().getEl());
		                    form.target = frameID;
		                    form.method = 'POST';
		                    form.action = '/be/wss/import.php?wam=designer&buid='.concat(Jedox.wss.app.activeBook.uid, '&suid=', Jedox.wss.app.activeSheet.getUid(), '&t=img&x_pos=', elX, '&y_pos=', elY, (editObj && editObj.id ? '&img_id='.concat(editObj.id) : ''), '&zindex=', zIndex, '&locked=', locked, '&hldata=', hldata);
		                    form.enctype = form.encoding = 'multipart/form-data';

		                    try
		                    {
		            			form.submit();

	            				// show wait msg
	            				Ext.MessageBox.show({
	            					msg: "_msg: PaloImport Wait".localize(),
	            					progressText: "Importing".localize().concat('...'),
	            					width:300,
	            					wait:true,
	            					waitConfig: {interval:200},
	            					fn: function(){}
	            				});

		            		}
		                    catch (e)
		                    {
		            			Jedox.wss.general.showMsg("Application Error".localize(), e.message.localize(), Ext.MessageBox.ERROR);
		            		}
		                }
		            }
		        })),
		        (this.components.Cancel = new Ext.Button({
	            	text: 'Close'.localize(),
	            	tabIndex: 11,
	            	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
	            	handler: function()
	            	{
		        		that.win.close();
	            	}
	        	}))
			]
		});
		this.setContext();
		this.win.show();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.Picture, Jedox.dlg.Dialog);