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
 * SVN: $Id: feedback.js 4608 2011-02-11 13:41:12Z srdjanv $
 *
 */

	Jedox.studio.app.msgCt = null;
	Jedox.studio.app.showTopMsg = function(title, format) {

		function createBox(t, s){
	        return ['<div class="topmsg">',
	                '<div class="x-box-tl"><div class="x-box-tr"><div class="x-box-tc"></div></div></div>',
	                '<div class="x-box-ml"><div class="x-box-mr"><div class="x-box-mc" style="text-align: center"><h3>', t, '</h3>', s, '</div></div></div>',
	                '<div class="x-box-bl"><div class="x-box-br"><div class="x-box-bc"></div></div></div>',
	                '</div>'].join('');
	    }

		var msgCt = Jedox.studio.app.msgCt;
		if(!msgCt)
			msgCt = Ext.DomHelper.insertFirst(document.body, {id:'topmsg'}, true);

		msgCt.alignTo(document, 'c-c');
		var s = String.format.apply(String, Array.prototype.slice.call(arguments, 1)),
			m = Ext.DomHelper.append(msgCt, {html: createBox(title, s)}, true);

		m.fadeIn({ duration: .5 }).pause(2).ghost("t",{remove:true});

	}

	Jedox.studio.app.onMsgDlgClose = function(){
		Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
	}


	Jedox.studio.app.showMessageERROR = function (title, message){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.OK,
			animEl: 'elId',
			icon: Ext.MessageBox.ERROR
		});
	}

	Jedox.studio.app.showMessageALERT = function (title, message){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.OK,
			fn:function(btn){Jedox.studio.app.onMsgDlgClose();},
			animEl: 'elId',
			icon: Ext.MessageBox.WARNING
		});
	}


	Jedox.studio.app.showMessageQUESTIONERROR = function (title, message, fn){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.OK,
			fn:function(btn){if(btn=='ok')fn();Jedox.studio.app.onMsgDlgClose();},
			animEl: 'elId',
			closable:false,
			icon: Ext.MessageBox.ERROR
		});
	}


	Jedox.studio.app.showMessageQUESTION = function (title, message, fn){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.YESNO,
			fn:function(btn){if(btn=='yes')fn();Jedox.studio.app.onMsgDlgClose();},
			animEl: 'elId',
			icon: Ext.MessageBox.WARNING
		});
	}


	Jedox.studio.app.showMessageQUESTION_YN = function (title, message, fnYES, fnNO){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: Ext.Msg.YESNO,
			fn:function(btn){if(btn=='yes')fnYES();else fnNO();Jedox.studio.app.onMsgDlgClose();},
			animEl: 'elId',
			icon: Ext.MessageBox.WARNING
		});
	}


	Jedox.studio.app.showMsg = function (title, message, icon, buttons, ok_cb, cancel_cb){

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		function btnHandler(cb){
			if (cb instanceof Array && cb.length > 1)
				cb[1].apply(cb[0], cb.slice(2));
		}

		Ext.Msg.show({
			title:title,
			msg: message,
			buttons: buttons,
			fn:function(btn){
				if (ok_cb && btn == 'yes' || btn == 'ok')
					btnHandler(ok_cb);
				else {
					if(cancel_cb)
						btnHandler(cancel_cb);

					Jedox.studio.app.onMsgDlgClose();
				}
			},
			animEl: 'elId',
			icon: icon,
			listeners:{
				close:function(){
					Jedox.studio.app.onMsgDlgClose();
				}
			}
		});


	}


	Jedox.studio.app.showMessageR_QUESTION_YND = function(data, title, message, fnYES){
		Jedox.dlg.dlgRegistry.add(new Jedox.studio.app.showMessageRQYND(data, title, message, fnYES));
	};

	Jedox.studio.app.showMessageRQYND = (function(){

		// class constructor
		return function (data, title, message, fnYES) {

			Jedox.studio.app.showMessageRQYND.parent.constructor.call(this);

			this.id = 'addGroup';
			var that = this;

		Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		var showRefLblCONST = 'Show Referrers'.localize();
		var hideRefLblCONST = 'Hide Referrers'.localize();

		var showDepLblCONST = 'Show Dependents'.localize();
		var hideDepLblCONST = 'Hide Dependents'.localize();

		var warningIcn = {
			html: '<div class="properties-icon-img"><img src="../lib/ext/resources/images/default/window/icon-warning.gif" width="32px" height="32px"/></div>',
			baseCls: 'x-plain',
			x:20,
			y:20
		};

		var messageLbl = {
			html: message,
			baseCls:'remove-item-dlg-label',
			x:80,
			y:10
		};

		var getReferrers = function(rPanel){
			referrersPanel.removeAll();
			rPanel.setSize(420, 100);
			referrersPanel.add(rPanel);
			referrersPanel.doLayout();
		};

		var referrersPanel = new Ext.Panel({
			baseCls: 'x-plain',
			items: [{}]
		});

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.refList, [data.container, getReferrers, data.nodes]);

		referrersPanel.setSize(420, 100);
		referrersPanel.doLayout();

		var getDependents = function(rPanel){
			dependentsPanel.removeAll();
			rPanel[0].setSize(420, 100);
			dependentsPanel.add(rPanel[0]);
			dependentsPanel.doLayout();
		};

		var dependentsPanel = new Ext.Panel({
			baseCls: 'x-plain',
			items: [{}]
		});

		Jedox.gen.load(Jedox.studio.app.dynJSRegistry.fileResources, ['dependents', data.container, getDependents, data.nodes]);

		dependentsPanel.setSize(420, 110);
		dependentsPanel.doLayout();


		var hiddenContainer = new Ext.Panel({
			layout: 'card',
			x:7,
			y:100,
			width:420,
			border: false,
			id: 'hiddenCt',
			baseCls: 'x-plain',
			activeItem:0,
			items:[referrersPanel, dependentsPanel]
		});


		var mainPanel = new Ext.Panel({
			layout: 'absolute',
			border: false,
			baseCls: 'x-plain',
			width:375,
			height:380,
			items:[warningIcn, messageLbl, hiddenContainer]
		});

		this.win = new Ext.Window({
			id:'remove-item-dlg',
			title:title,
			closable: true,
			closeAction: 'close',
	        autoDestroy: true,
	        plain: true,
			bodyBorder:false,
	        constrain: true,
	        modal: true,
			border:false,
	        resizable: false,
	        animCollapse: false,
			layout: 'fit',
			width: 450,
			height: 150,
			onEsc: Ext.emptyFn,
			items: [mainPanel],
			listeners: {
				close: function(){
					Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.refList);
					Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.fileResources);
					that.close();
				},
				show:function(){
					setTimeout(function(){
						that.initFocus(true, 500);
					});
				},
				activate: function(win) {that.activate();}
			},
			buttons: [(that.components.OK = that.cmpFocus = new Ext.Button({
				text: 'Yes'.localize(),
				tabIndex: 101,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					that.win.close();
					fnYES();
					Jedox.studio.app.onMsgDlgClose();
				}
			})), (that.components.Cancel = new Ext.Button({
				text: 'No'.localize(),
				tabIndex: 102,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					that.win.close();
				}
			})), (that.components.SRF = new Ext.Button({
				text: showRefLblCONST,
				minWidth:100,
				tabIndex: 104,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				handler: function(){
					showHideReferrers();
				}
			})), (that.components.SDP = new Ext.Button({
				text: showDepLblCONST,
				tabIndex: 105,
				ctCls: Jedox.kbd.Base.tags.NO_ENTER,
				minWidth:100,
				handler: function(){
					showHideDependents();
				}
			}))]
		});

		this.setContext();
		this.win.show();

		function showHideReferrers(){

			hiddenContainer.getLayout().setActiveItem(0);
			hiddenContainer.doLayout();
			that.win.buttons[3].setText(showDepLblCONST);

			if (that.win.buttons[2].getText() == showRefLblCONST){
				that.win.setHeight(270);
				that.win.buttons[2].setText(hideRefLblCONST);
			}
			else {
				that.win.setHeight(150);
				that.win.buttons[2].setText(showRefLblCONST);
			}

		}


		function showHideDependents(){

			hiddenContainer.getLayout().setActiveItem(1);
			hiddenContainer.doLayout();
			that.win.buttons[2].setText(showRefLblCONST);

			if (that.win.buttons[3].getText() == showDepLblCONST){
				that.win.setHeight(270);
				that.win.buttons[3].setText(hideDepLblCONST);
			}
			else {
				that.win.setHeight(150);
				that.win.buttons[3].setText(showDepLblCONST);
			}

		}
		};
	}
)();

Jedox.util.extend(Jedox.studio.app.showMessageRQYND, Jedox.dlg.Dialog);
