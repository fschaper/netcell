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
 * SVN: $Id: CustomHeaderFooter.js 3513 2010-07-13 15:09:50Z drazenk $
 *
 */

Jedox.wss.dlg.openCustomHeaderFooter = function (dialogTitle, customHandleFunction, tmpRecord) {
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.CustomHeaderFooter(dialogTitle, customHandleFunction, tmpRecord));
};

Jedox.wss.dlg.CustomHeaderFooter = (function() {

	return function (dialogTitle, customHandleFunction, tmpRecord) {

		Jedox.wss.dlg.CustomHeaderFooter.parent.constructor.call(this);
		this.id = 'customHeaderFooter';
		var that = this;

		var _fromDlgF = false;

		if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
			_fromDlgF=true;
		else {
			Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
		}


		var AttrRecord = new Ext.data.Record.create([
		 	{name: 'leftStyle'},
			{name: 'leftValue'},
			{name: 'centerStyle'},
			{name: 'centerValue'},
			{name: 'rightStyle'},
			{name: 'rightValue'}
		]);

		var _pageNumber='';
		var _numberOfPages='';
		var _date='';
		var _time='';
		var _fileName='';
		var _pictureName=''

		var _leftAlign='text-align: left;'
		var _centerAlign='text-align: center;'
		var _rightAlign='text-align: right;'

		var _activeTextArea;

		var _leftSectionFormatStyle='';
		var _centerSectionFormatStyle='';
		var _rightSectionFormatStyle='';

	/*
		var fontFamily = '';
		var fontStyle = '';
		var fontWeight = '';
		var textDecoration = '';
		var color= '';
		var fontSize = '';
	*/

		var label='customHFLbl'.localize();

		var formatTexteBtn=new Ext.Toolbar.Button({
		  	iconCls: 'ico_textcolor',
		  	cls: 'x-btn-icon',
		  	tooltip: "Format text".localize(),
		  	tabIndex: 1,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		 	handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells, ['fromPageSetup', 0, setFormatingStyle, getFormatingStyle()]);}
		});

		var pageNumberBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_page_nmb',
		  	cls: 'x-btn-icon',
		  	tabIndex: 2,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Page Number".localize(),
		 	handler:function() {appendTextArea('&[Page]');}
		});

		var numberOfPagesBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_nmb_of_pages',
		  	cls: 'x-btn-icon',
		  	tabIndex: 3,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Number of Pages".localize(),
		 	handler:function() {appendTextArea('&[Pages]');}
		});

		var dateBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_date',
		  	cls: 'x-btn-icon',
		  	tabIndex: 4,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Date".localize(),
		 	handler:function() {appendTextArea('&[Date]');}
		});

		var timeBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_time',
		  	cls: 'x-btn-icon',
		  	tabIndex: 5,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Time".localize(),
		 	handler:function() {appendTextArea('&[Time]');}
		});

		var fileNameBtn=new Ext.Toolbar.Button({
			iconCls: 'select-range-icon',
		  	cls: 'x-btn-icon',
		  	tabIndex: 6,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert File Name".localize(),
		 	handler:function() {appendTextArea('&[File]');}
		});

		var sheetNameBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_tab',
		  	cls: 'x-btn-icon',
		  	tabIndex: 7,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Sheet Name".localize(),
		 	handler:function() {appendTextArea('&[Tab]');}
		});

		var pictureBtn=new Ext.Toolbar.Button({
			iconCls: 'ico_ins_picture',
		  	cls: 'x-btn-icon',
		  	tabIndex: 8,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		  	tooltip: "Insert Picture".localize(),
			disabled:true,
		 	handler:function() {appendTextArea('&[Picture]');}
		});


		var leftSection = new Ext.form.TextArea({
			fieldLabel: 'Left section'.localize(),
			width: 200,
			style:_leftAlign,
			tabIndex: 10,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			listeners:{
				focus: function (txa){
					_activeTextArea=txa;
				}
			}
		});



		var centerSection = new Ext.form.TextArea({
			fieldLabel: 'Center section'.localize(),
			width: 200,
			tabIndex: 11,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			style:_centerAlign,
			listeners:{
				focus: function (txa){
					_activeTextArea=txa;
				}
			}
		});

		var rightSection = new Ext.form.TextArea({
			fieldLabel: 'Right section'.localize(),
			width: 200,
			tabIndex: 12,
		  	ctCls: Jedox.kbd.Base.tags.NO_ENTER,
			style:_rightAlign,
			listeners:{
				focus: function (txa){
					_activeTextArea=txa;
				}
			}
		});

		var buttonsPanel={
				layout:'column',
				defaults:{border:false,baseCls:'x-plain'},
				border:false,
				baseCls:'x-plain',
				//baseCls:'main-panel',
				items:[{
					layout:'form',
					width:30,
					items:formatTexteBtn
				 },
				 {
					layout:'form',
					width:30,
					items:pageNumberBtn
				 },
				 {
					layout:'form',
					width:30,
					items:numberOfPagesBtn
				 },
				 {
					layout:'form',
					width:30,
					items:dateBtn
		},
				 {
					layout:'form',
					width:30,
					items:timeBtn
		},
				 {
					layout:'form',
					width:30,
					items:fileNameBtn
				 },
				 {
					layout:'form',
					width:30,
					items:sheetNameBtn
		},
				 {
					layout:'form',
					width:30,
					items:pictureBtn
		}]
			}

		var textAreaPanel = {
			layout: 'column',
			//defaults:{border:false,},
			baseCls: 'main-panel',
			items: [{
				layout: 'form',
				labelAlign:'top',
				baseCls: 'x-plain',
				width: 205,
				items: leftSection
		},
			{
				layout: 'form',
				labelAlign:'top',
				baseCls: 'x-plain',
				width: 205,
				items: centerSection
		},
			{
				layout:'form',
				labelAlign:'top',
				baseCls: 'x-plain',
				width:205,
				items:rightSection
		}]
		}


		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			modal:true,
			layout: 'form',
			baseCls:'main-panel',
			border:false,
			items:[{
				html:label,
				baseCls:'x-plain'
				},
				buttonsPanel,
				{
					html:'<br>',
					baseCls:'x-plain'
				},
				textAreaPanel
			]
		});





		var setFormatingStyle = function(fmDesc){


			var fontFamily = 'font-family:'.concat(fmDesc.fontFamily, '; ');
			var fontStyle = 'font-style:'.concat(fmDesc.fontStyle, '; ');
			var fontWeight = 'font-weight:'.concat(fmDesc.fontWeight, '; ');
			var textDecoration = 'text-decoration:'.concat(fmDesc.textDecoration, '; ');
			var color = 'color:'.concat(fmDesc.color, ';');
			var fontSize = 'font-size:'.concat(fmDesc.fontSize, '; ');


			var sectionFormatStyle = fontFamily + fontStyle + fontSize +fontWeight +  textDecoration + color  + 'white-space: nowrap;';

			switch (_activeTextArea.fieldLabel.charAt(0)){
				case 'L':
					_leftSectionFormatStyle=sectionFormatStyle;
					break;
				case 'C':
					_centerSectionFormatStyle=sectionFormatStyle;
					break;
				case 'R':
					_rightSectionFormatStyle=sectionFormatStyle;
					break;
			}

			_activeTextArea.getEl().applyStyles(sectionFormatStyle);
			_activeTextArea.selectText();
			_activeTextArea.focus(true, true);
		}



		function formatText(s){
			s=s.replace(/\n/g,'<br>');
			return s;
		}


		function unFormatText(s){
			s=s.replace(/<br>/g,'\n');
			return s;
		}


		function setCustomHeaderFooter(){
			var  tmpRec = new AttrRecord({
				  	'leftStyle': _leftSectionFormatStyle,
					'leftValue':formatText(leftSection.getValue()),
					'leftPreview':getPreview(formatText(leftSection.getValue())),
					'centerStyle':_centerSectionFormatStyle,
					'centerValue':formatText(centerSection.getValue()),
					'centerPreview':getPreview(formatText(centerSection.getValue())),
					'rightStyle':_rightSectionFormatStyle,
					'rightValue':formatText(rightSection.getValue()),
					'rightPreview':getPreview(formatText(rightSection.getValue()))
			});
			customHandleFunction(tmpRec, dialogTitle);
		}


		function getPreview (value){
			var date = new Date();
			var today = date.getDate() + '/' + date.getMonth()+1 + '/' + date.getFullYear();
			var time = date.getHours() + ':' + date.getMinutes() + ":" + date.getSeconds();

			var v = ['&[Page]', '&[Pages]', '&[Date]', '&[Time]', '&[Tab]', '&[File]'];
			var p= ['1', '5', today, time, 'Sheet'.localize()+ ' 1', 'Book'.localize()+ ' 1'];

			var preview = value;

			for (var i=0; i<v.length; i++)
				preview = preview.replace(v[i], p[i]);

			return preview;
		}


		function getFormatingStyle(){
			var preFormated;
			if (_activeTextArea)
				preFormated=_activeTextArea.getEl().getStyles('fontFamily', 'fontStyle', 'fontWeight', 'textDecoration', 'color', 'fontSize')

			return preFormated;
		}


		function appendTextArea(s){
			var oldValue=_activeTextArea.getValue();
			_activeTextArea.setValue(oldValue + s);
		}


		function init(){
			_leftSectionFormatStyle=tmpRecord.get('leftStyle');
			leftSection.getEl().applyStyles(_leftSectionFormatStyle);
			leftSection.setValue(unFormatText(tmpRecord.get('leftValue')));
			_centerSectionFormatStyle= tmpRecord.get('centerStyle');
			centerSection.getEl().applyStyles(_centerSectionFormatStyle);
			centerSection.setValue(unFormatText(tmpRecord.get('centerValue')));
			_rightSectionFormatStyle=tmpRecord.get('rightStyle');
			rightSection.getEl().applyStyles(_rightSectionFormatStyle);
			rightSection.setValue(unFormatText(tmpRecord.get('rightValue')));
		}



		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					defaults: {bodyStyle:'padding:10px 5px 15px 10px'},
					title:dialogTitle,
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
					width: 650,
					height: 300,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							if (!_fromDlgF) {
								Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
								Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
							}
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.customHeaderFooter);
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
							tabIndex: 101,
							handler: function(){
								setCustomHeaderFooter();
								that.win.close();
							}
						})),
						(this.components.Cancel = new Ext.Button({
							text: 'Cancel'.localize(),
							tabIndex: 102,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							handler: function(){
								that.win.close();
							}
						}))]
		});

		//_activeTextArea=leftSection;

		this.setContext();
		this.win.show(this);
		init();

		leftSection.selectText();
		leftSection.focus(true, true);
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.CustomHeaderFooter, Jedox.dlg.Dialog);