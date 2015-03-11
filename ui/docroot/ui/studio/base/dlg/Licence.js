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
 * SVN: $Id: Licence.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */
Jedox.studio.dlg.openLicence = function(days){
	Jedox.dlg.dlgRegistry.add(new Jedox.studio.dlg.Licence(days));
};

Jedox.studio.dlg.Licence = (function(){

	// class constructor
	return function (days) {

		Jedox.studio.dlg.Licence.parent.constructor.call(this);

		this.id = 'Licence';
		var that = this;
		var expired = days == 0;

	    Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
	    Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

		var EN = 'en_US';
		var DE = 'de_DE';
		var FR = 'fr_FR';


		//================================ Licence components ============================================

		var headerWarningTitle = '<div class="licence-header-title" style="text-align: right;">' + 'licenceHeaderWarningTitle'.localize() + '</div>';
		var headerErrorTitle = '<div class="licence-header-title" style="text-align: right;">' + 'licenceHeaderErrorTitle'.localize() + '</div>';

		var headerTitle = expired? headerErrorTitle:headerWarningTitle;


		var headerContainer = {
			layout: 'absolute',
			baseCls: 'x-plain',
			width:623,
			height:180,
			items: [{
				x: 0,
				y: 0,
				width: 640,
				html: '<img class="licence-header-icon" src="../lib/ext/resources/images/default/s.gif" align="center" width="644" height="175" />'
			}, {
				x: 320,
				y: 20,
				width:280,
				baseCls:'x-plain',
				html:[headerTitle]
			}]
		}


		var Lbl = function (t){
			return new Ext.form.Label({
				text:t
			});
		}

		var Btn = function(t, ti, h) {
			return new Ext.Button({
				text: t,
				width:240,
				tabIndex: ti,
				handler: h
			});
		}


		var warningTitle = new Ext.form.Label({
			text:'licenceWarningTitle'.localize({'days':days}),
			cls:'licence-title'
		});

		var quoteMsg = new Lbl('quoteMsg'.localize());
		var communityMsg = new Lbl('communityMsg'.localize());
		var comparisonMsg = new Lbl('comparisonMsg'.localize());


		var errorTitle = new Ext.form.Label({
			text:'licenceErrorTitle'.localize(),
			cls:'licence-title'
		});


		var quoteBtn = new Btn('Angebot Palo Premium anfordern'.localize(), 1, quoteBtnHandler);
		var communityBtn = new Btn('Download Palo for exel - Community edition'.localize(), 2, communityBtnHandler);
		var comparisonBtn = new Btn('Funktionsubersicht Premium / Community'.localize(), 3, comparisonBtnHandler);


		var warningPanel = {
			layout: 'table',
			width:600,
			height:300,
			baseCls:'x-plain',
			layoutConfig: {
				columns: 2
			},
			defaults:{
				baseCls:'x-plain',
				height:50
			},
			items: [{
				colspan:2,
				items:expired? errorTitle:warningTitle
			},{
				width:350,
				items:quoteMsg
			}, {
				width:240,
				items:quoteBtn
			}, {
				items:communityMsg
			}, {
				items:communityBtn
			},{
				items:comparisonMsg
			}, {
				items:comparisonBtn
			}]
		}


		var licenceContainer = {
			baseCls:'x-plain',
			bodyStyle:{
				padding:'10px'
			},
			items:[warningPanel]
		}




		//================================ Main Panel ============================================

		var mainPanel = this.containers.mainPanel = new Ext.Panel({
			layout: 'form',
			baseCls:'main-panel',
			border:false,
			items:[headerContainer, licenceContainer]
		});



		//================================ Window (Dlg) ============================================

		this.win = new Ext.Window({
					title:'Palo web licence'.localize(),
					closable: true,
//					cls: 'default-format-window',
					closeAction: 'close',
			        autoDestroy: true,
			        plain: true,
			        constrain: true,
			        modal: true,
			        resizable: false,
			        animCollapse: false,
					layout: 'fit',
					width: 640,
					height: 470,
					items: mainPanel,
					onEsc: Ext.emptyFn,
					listeners: {
						close: function()
						{
							Jedox.studio.app.inputMode = Jedox.studio.app.lastInputMode;
							that.close();
							Jedox.gen.unload(Jedox.studio.app.dynJSRegistry.openLicence);
						},
						show:function(){
							setTimeout(function(){
								//that.initFocus(true, 300);
							});
						},
						activate: function(win) {that.activate();}
					},
					buttons: [(this.components.OK = new Ext.Button({
						text: 'OK'.localize(),
						tabIndex: 10,
						handler: function(){
							that.win.close();
						}
					}))]

		});

		this.setContext();
		this.win.show(this);


		//================================ Handler functions ============================================

		function quoteBtnHandler(){

			var url = 'quoteURL'.localize();
			window.open(url ,"_blank");
		}

		function communityBtnHandler(){

			var url = 'communityURL'.localize();
			window.open(url ,"_blank");
		}

		function comparisonBtnHandler(){

			var url = 'comparisonURL'.localize();
			window.open(url ,"_blank");

		}

	};
}
)();

// Licence extends Dialog.
Jedox.util.extend(Jedox.studio.dlg.Licence, Jedox.dlg.Dialog);
