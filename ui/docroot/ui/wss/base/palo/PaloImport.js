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
 * SVN: $Id: PaloImport.js 4310 2010-11-18 07:52:20Z mladent $
 *
 */

Jedox.wss.palo.openPaloImport = function()
{
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.PaloImport());
};

Jedox.wss.dlg.PaloImport = (function() {

	return function () {

		Jedox.wss.dlg.PaloImport.parent.constructor.call(this);
		this.id = 'PaloImport';

		var that = this, servId,
			panelMain, logoImg, btnClose, btnBack, btnFinish, lblImportDesc, panelStart, panelMiddle, panelEnd, panelGrouped,
			lbl1Source, rb1Textfile, rb1ODBC, rb1Cube, rb1InternalLoop,
			rb21Tab, rb21Comma, rb21Semicolon, rb21Blank, rb21User_defined, txt21User_defined, validate21File, file21Upload, txt21Decimalpoint, chb21Header,
			chb3StepByStep, pbar3,
			firstStep, stepPBarSize, doCleanUp;

		var _init = function()
		{
			// flag to clean up on close
			doCleanUp = false;

			// left image logo
			logoImg = new Ext.BoxComponent({
				autoEl: {tag: 'img', src: Jedox.palo.config.imgsPath + 'wizard_logo.png'}
			});

			// *** UPLOAD File ***
			validate21File = function (fieldValue)
			{
				var nameSize = fieldValue.length - 4;
				if ((nameSize > 0) && ((fieldValue.lastIndexOf('.txt') == nameSize) || (fieldValue.lastIndexOf('.csv') == nameSize)))
					return true;
				else
					return "impPalo_msgWrongType".localize();
			};

			file21Upload = new Ext.ux.form.FileUploadField({
				hideLabel: true,
				emptyText: "impPalo_msgFieldBlank".localize(),
				defaultAutoCreate: {tag: "input", type: "text", size: "65", autocomplete: "off"},
				width: 250,
				autoWidth: false,
				//tabIndex: 20,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'palo_import_file',
				validator: validate21File
		    });

			// *** Progress Bar ***
			pbar3 = new Ext.ProgressBar({
				id: 'palo_imp_pbar3',
				width: 500
			});

			// *** BUTTONS *** //
			// Cancel button and panel
			btnClose = that.components.Cancel = new Ext.Button({
				text: "Close".localize(),
				ctCls: 'stdButtons '.concat(Jedox.kbd.Base.tags.NO_ENTER),
				tabIndex: 102,
				handler: function()
					{
						that.win.close();
					}
			});

			// back button
			btnBack = that.components.Back = new Ext.Button({
				disabled: true,
				tabIndex: 100,
				ctCls: 'stdButtons '.concat(Jedox.kbd.Base.tags.NO_ENTER),
				text: ''.concat('<< ').concat("Back".localize()),
				handler: _handlebtnBack
			});

			// finish button and panel
			btnFinish = that.components.OK = new Ext.Button({
				text: "Next".localize().concat(' >>'),
				ctCls: 'stdButtons'.concat(Jedox.kbd.Base.tags.NO_ENTER),
				tabIndex: 101,
				handler: _handlebtnFinish
			});
			// --- BUTTONS --- //

			// *** TextFields *** //
			txt21User_defined = new Ext.form.TextField({
				name: 'user_separator',
				disabled: true,
				allowBlank: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 28,
				width: 50,
				hideLabel: true
			});
			txt21Decimalpoint = new Ext.form.TextField({
				name: 'decimal_point',
				allowBlank: true,
				width: 15,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 29,
				fieldLabel: "Decimalpoint".localize(),
				value: '.'
			});
			// --- TextFields --- //

			// *** LABLES *** //
			lblImportDesc =  new Ext.form.MiscField({
				value: "_msg: Palo Import 1".localize(),
				height: 22,
				bodyStyle: 'background-color: transparent;',
				style: 'font-weight: bold;',
				hideLabel: true
			});
			lbl1Source =  new Ext.form.MiscField({
				value: "Select Data Source".localize(),
				height: 22,
				bodyStyle: 'background-color: transparent;',
				style: 'font-weight: bold;',
				hideLabel: true
			});
			lbl21SourceFile =   new Ext.form.MiscField({
				value: "Select the sourcefile (*.txt, *.csv)".localize(),
				height: 22,
				bodyStyle: 'background-color: transparent;',
				style: 'font-weight: bold;',
				hideLabel: true
			});
			// --- LABLES --- //

			// *** Radio Buttons *** //
			// 1st panel
			rb1Textfile = new Ext.form.Radio({
				name: 'radioImportType',
				tabIndex: 10,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				boxLabel: "Flat Textfile (*.txt, *.csv)".localize(),
				hideLabel: true,
				checked: true
			});
			rb1ODBC = new Ext.form.Radio({
				disabled: true,
				tabIndex: 11,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioImportType',
				boxLabel: "ODBC Query".localize(),
				hideLabel: true
			});
			rb1Cube = new Ext.form.Radio({
				disabled: true,
				tabIndex: 12,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioImportType',
				boxLabel: "Cube".localize(),
				hideLabel: true
			});
			rb1InternalLoop = new Ext.form.Radio({
				disabled: true,
				tabIndex: 13,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				name: 'radioImportType',
				boxLabel: "Internal Loop (increse A1 until error in B1)".localize(),
				hideLabel: true
			});

			// 2nd panel
			rb21Tab = new Ext.form.Radio({
				name: 'radioImportSeparateType',
				boxLabel: "Tab".localize(),
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 22,
				inputValue: 'tab',
				checked: true
			});
			rb21Comma = new Ext.form.Radio({
				name: 'radioImportSeparateType',
				boxLabel: "Comma".localize(),
				inputValue: 'comma',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 23,
				hideLabel: true
			});
			rb21Semicolon = new Ext.form.Radio({
				name: 'radioImportSeparateType',
				boxLabel: "Semicolon".localize(),
				inputValue: 'semi',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 24,
				hideLabel: true
			});
			rb21Blank = new Ext.form.Radio({
				name: 'radioImportSeparateType',
				boxLabel: "Blank".localize(),
				inputValue: 'blank',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 25,
				hideLabel: true
			});
			rb21User_defined = new Ext.form.Radio({
				name: 'radioImportSeparateType',
				boxLabel: "User-defined".localize(),
				hideLabel: true,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 26,
				inputValue: 'user',
				listeners: {
					check: function(thisRb, isChecked)
					{
						if (isChecked)
							txt21User_defined.enable();
						else
							txt21User_defined.disable();
					}
				}
			});
			// --- Radio Buttons --- //

			// *** Checkboxes *** //
			//	2nd panel
			chb21Header = new Ext.form.Checkbox({
				name: 'header',
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				tabIndex: 30,
				boxLabel: "Header exists".localize(),
				hideLabel: true
			});
			// 3rd panel
			chb3StepByStep = new Ext.form.Checkbox({
				hidden: true,
				boxLabel: "Step by Step".localize(),
				hideLabel: true,
				checked: true,
				listeners: {
					check: function(thisChb, isChecked)
					{
					}
				}
			});
			// --- Checkboxes --- //

			// *** Card Panels *** //
			panelStart = that.containers.activePanel = new Ext.Panel({
				border: false,
				layout: 'form',
				bodyStyle: 'background-color: transparent;',
				items: [
					lbl1Source,
					{
						border: false,
						bodyStyle: 'background-color:transparent;',
						html: '&nbsp;'
					},
					rb1Textfile, rb1ODBC, rb1Cube, rb1InternalLoop
				]
			});

			panelMiddle = new Ext.FormPanel({
				border: false,
				layout: 'form',
				id: 'middlePanel',
				bodyStyle: 'background-color: transparent;',
		        defaults: {
		            anchor: '95%',
		            allowBlank: false
		        },
				items: [
					lbl21SourceFile, file21Upload,
					{
						border: false,
						bodyStyle: 'background-color:transparent;',
						html: '&nbsp;'
					},
					new Ext.Panel({
						border: false,
						layout: 'column',
						bodyStyle: 'background-color: transparent;',
						items: [
							new Ext.Panel({
								columnWidth: .5,
								border: false,
								layout: 'form',
								bodyStyle: 'background-color: transparent;',
								items: [
									rb21Tab, rb21Comma, rb21Semicolon,
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									txt21Decimalpoint,
									{
										border: false,
										bodyStyle: 'background-color:transparent;',
										html: '&nbsp;'
									},
									chb21Header
								]
							}),
							new Ext.Panel({
								columnWidth: .5,
								border: false,
								layout: 'form',
								bodyStyle: 'background-color: transparent;',
								items: [rb21Blank, rb21User_defined, txt21User_defined]
							})
						]
					})
				]
			});

			panelEnd = new Ext.FormPanel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				items: [chb3StepByStep, pbar3]
			});

			panelGrouped = new Ext.Panel({
				border: false,
				layout: 'card',
				activeItem: 0,
				width: 540,
				bodyStyle: 'background-color: transparent;',
				defaults: {
					hideMode: 'offsets'
				},
				items: [panelStart, panelMiddle, panelEnd]
			});
			// --- Card Panels --- //

			// *** MAIN panel
			panelMain = new Ext.Panel({
				border: false,
				bodyStyle: 'background-color: transparent;',
				layout: 'absolute',
				anchor: '100% 100%',
				monitorResize: true,
				listeners: {
					resize: _resizeAll
				},
				items: [logoImg, lblImportDesc, panelGrouped]
			});

			// Wizard Window
			that.win = new Ext.Window({
				layout: 'fit',
				title: "PALO Import Wizard".localize(),
				cls: 'default-format-window',
				width: 750,
				minWidth: 750,
				minHeight: 432,
				closeAction: 'close',
				autoDestroy: true,
				plain: true,
				onEsc: Ext.emptyFn,
				height: 470,
				modal: true,
				resizable: false,
				listeners: {
					activate: _resizeAll,
					close: function()
					{
						if (Jedox.palo.workIn == Jedox.palo.GRID)
						{
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.paloImport);
						}

						if (Jedox.wss.palo.numOfUploadedLines)
							delete Jedox.wss.palo.numOfUploadedLines;

						if (doCleanUp)
							setTimeout(function(){(new Jedox.backend.RPCAsyncRqst('palo_misc', 'doImportCleanup')).send();},0);
					}
				},
				items: [panelMain],
				buttons: [
				          btnBack,
				          btnFinish,
				          btnClose
				          ]
			});

			if (Jedox.palo.workIn == Jedox.palo.GRID)
			{
				Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
			}
		}

		// *** Handler functions ***
		var _handlebtnBack =  function()
		{
			if (panelMiddle.isVisible())
			{
				lblImportDesc.setValue("_msg: Palo Import 1".localize());
				panelGrouped.layout.setActiveItem(0);
				btnBack.disable();
				that.containers.activePanel = panelStart;
				btnFinish.setText("Next".localize().concat(' >>'));
				btnBack.setText(''.concat('<< ').concat("Back".localize()));
			}
			else
			{
				// do step by step
				if (Jedox.wss.palo.numOfUploadedLines)
				{
					if (firstStep)
					{
						stepPBarSize = pbar3.value;
						firstStep = false;
					}

					// call handler
					Jedox.wss.palo.numOfUploadedLines--;
					if (Jedox.wss.palo.numOfUploadedLines)
					{
						pbar3.updateProgress(pbar3.value + stepPBarSize);
						Jedox.backend.rpc_cb('palo_handlerImportPaloDataFunc', [Jedox.wss.palo.numOfUploadedLines]);
					}

					if ((Jedox.wss.palo.numOfUploadedLines == 1) || (chb21Header.getValue() && (Jedox.wss.palo.numOfUploadedLines == 2)))
						that.win.close();
				}
				else
				{
					firstStep = true;
					doCleanUp = true;
					_do_upload('partial');
				}
			}
		}

		var _handlebtnFinish = function()
		{
			if (panelStart.isVisible())
			{
				lblImportDesc.setValue("_msg: Palo Import 21".localize());
				panelGrouped.layout.setActiveItem(1);
				btnBack.enable();
				that.containers.activePanel = panelMiddle;
			}
			else if (panelMiddle.isVisible())
			{
				lblImportDesc.setValue("_msg: Palo Import 3".localize());
				panelGrouped.layout.setActiveItem(2);
				btnFinish.setText("Finish".localize().concat(' >>'));
				btnBack.setText("Next".localize().concat(' >>'));
				that.containers.activePanel = panelEnd;
				that.win.setHeight(150);
			}
			else
				_do_upload('full');
		}

		var _do_upload = function(type)
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

	        var form = Ext.getDom(panelMiddle.getForm().getEl());
	        form.target = frameID;
	        form.method = 'POST';
			form.action = '/be/wss/import.php?wam=designer&t=palo&f=textfile&o=' + type;
	        form.enctype = form.encoding = 'multipart/form-data';

	        try
	        {
				form.submit();

				if (type == 'full')
				{
					// show wait msg
					Ext.MessageBox.show({
						msg: "_msg: PaloImport Wait".localize(),
						progressText: "Importing".localize().concat('...'),
						width:300,
						wait:true,
						waitConfig: {interval:200}
					});

					doCleanUp = false;
					that.win.close();
				}
				else
				{
					Ext.MessageBox.show({
						msg: "_msg: PaloImport Upload".localize(),
						progressText: "Uploading".localize().concat('...'),
						width:300,
						wait:true,
						waitConfig: {interval:200}
					});
				}
			}
	        catch (e)
	        {
				Jedox.wss.general.showMsg("Application Error".localize(), e.message.localize(), Ext.MessageBox.ERROR);
			}
		}

		// *** RESIZE *** //
		var _resizeAll = function()
		{
			if (panelMain.rendered)
			{
				//panelMain.getEl().unselectable();

				// additional local vars
				var lineH = 23; // in pixels (height of lines [buttons, text fields, combo boxes, etc])
				var marginSize = 3; // size in pixels for spacing

				// function body
				var pSize = panelMain.getSize();

				var w = pSize.width;
				var h = pSize.height;
				var logoSize = {
					width: 160,
					height: 400
				}

				// card panel
				panelGrouped.setPosition(logoSize.width + 2*lineH + marginSize, 2*lineH + marginSize);

				// left logo image
				logoImg.setPosition(0, 0);

				// Description text
				if (lblImportDesc.rendered)
					lblImportDesc.setPosition(logoSize.width + 5*marginSize, 5);

			}
			that.activate();
		}

		_init();
		this.setContext();
		this.win.show(this);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.PaloImport, Jedox.dlg.Dialog);