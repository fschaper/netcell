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
 * SVN: $Id: SizePosPanel.js 5117 2011-07-15 12:37:01Z drazenk $
 *
 */
Jedox.wss.dlg.FESizePos = function(callback, type, conf) {

	/*
	 * allowed types: CheckBox, ComboBox, Button, chart, img
	 */

	 //console.log('>>',conf);
	var dims = Jedox.wss.wsel[type].dims;
	var env = Jedox.wss.app.environment;

	var hideH = false;
	if (!conf) conf = {};

	switch (type){
	case 'Chart': case 'chart':
		dims.minW = 10;
		dims.defW = 100;
		dims.minH = 10;
		dims.defH = 100;
		break;
	case 'Picture':
		// define dimensions depending of picture
		break;
	default:
		hideH = true;
		break;
	};

	 //spinners:

	 var wSpinner = new Ext.ux.form.SpinnerField({
		 minValue: dims.minW,
		 maxValue: dims.maxW,
		 name: 'elWidth',
		 allowBlank: false,
		 xtype: 'number',
		 hideLabel: false,
		 width : 60,
		 fieldLabel: 'Width'.localize(),
		 border: false,
		 value: conf.width || dims.defW,
		 tabIndex: 10,
		 ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		 listeners: {
		 	spin: {
				fn: function(indentSpinner, newValue, oldValue){},
				scope: this
			 }
		 }
	 });

	var hSpinner = new Ext.ux.form.SpinnerField({
		 minValue: dims.minH,
		 maxValue: dims.maxH,
		 name: 'elHeight',
		 allowBlank: false,
		 hidden: hideH,
		 disabled: hideH,
		 width : 60,
		 xtype: 'number',
		 hideLabel: hideH,
		 fieldLabel: 'Height'.localize(),
		 border: false,
		 value: conf.height || dims.defH,
		 tabIndex: 11,
		 ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		 listeners: {
		 	spin: {
				fn: function(indentSpinner, newValue, oldValue){},
				scope: this
			 }
		 }
	});

	var lSpinner = new Ext.ux.form.SpinnerField({
		 minValue: 0,
		 maxValue: Jedox.wss.app.activeSheet._colWidths.getSumUpTo(Jedox.wss.grid.defMaxCoords[0])-dims.maxW,
		 name: 'elLeft',
		 allowBlank: false,
		 width : 100,
		 xtype: 'number',
		 hideLabel: false,
		 fieldLabel: 'Left'.localize(),
		 border: false,
		 value: (conf.left || conf.left==0)? conf.left : env.selectedCell.offsetLeft,
		 tabIndex: 12,
		 ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		 listeners: {
		 	spin: {
				fn: function(indentSpinner, newValue, oldValue){},
				scope: this
			 }
		 }
	 });

	var tSpinner = new Ext.ux.form.SpinnerField({
		 minValue: 0,
		 maxValue: Jedox.wss.app.activeSheet._rowHeights.getSumUpTo(Jedox.wss.grid.defMaxCoords[1])-dims.maxH,
		 name: 'elTop',
		 allowBlank: false,
		 xtype: 'number',
		 hideLabel: false,
		 width : 100,
		 fieldLabel: 'Top'.localize(),
		 border: false,
		 value: (conf.top || conf.top==0)? conf.top : env.selectedCell.parentNode.offsetTop,
		 tabIndex: 13,
		 ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		 listeners: {
		 	spin: {
				fn: function(indentSpinner, newValue, oldValue){},
				scope: this
			 }
		 }
	 });

	SPPanel = Ext.extend(Ext.Panel, {
	    constructor: function(config) {

	        config = Ext.apply({
	        	bodyStyle: 'padding: 10px;',
		   		border: false,
		   		frame: false,
		   		autoHeight: true,
		   		autoWidth: true,
		   		baseCls: 'x-title-f',
		   		header: false
	        }, config);

	        SPPanel.superclass.constructor.call(this, config);
	    },

	    getSPData: function(){
	 		if (tSpinner.validate() && lSpinner.validate() && wSpinner.validate() && hSpinner.validate()) {
		 		var d = {
			 			top: tSpinner.getValue(),
			 			left: lSpinner.getValue(),
			 			width: wSpinner.getValue(),
			 			height: hSpinner.getValue()
			 		};
		 		return d;
	 		}
	 		else return;
		},

		setChartData: function(subType, edit){
			var el = Jedox.wss.wsel.chart;

			dims.minW = wSpinner.minValue = parseInt(el.min_whRatio[subType][0]*el.min_sizeFactor);
			dims.defW = parseInt(el.whRatio[subType][0]*el.min_sizeFactor);
			dims.minH = parseInt(hSpinner.minValue = el.min_whRatio[subType][1]*el.min_sizeFactor);
			dims.defH = parseInt(el.whRatio[subType][1]*el.min_sizeFactor);

			wSpinner.setValue(edit.w || dims.defW);
			hSpinner.setValue(edit.h || dims.defH);

			// positioning
			var activePane = Jedox.wss.app.activePane;
			var vportPos = activePane.getViewportPos();

			var elTop = parseInt(vportPos[0][1] + (vportPos[1][1] - vportPos[0][1] - dims.defH) / 2);
			var elLeft = parseInt(vportPos[0][0] + (vportPos[1][0] - vportPos[0][0] - dims.defW) / 2);

			if (!conf.top) conf.top = elTop < 0 ? 0 : elTop;
			if (!conf.left) conf.left = elLeft < 0 ? 0 : elLeft;

			if (edit && edit.t > -1 && edit.l > -1)
			{
				tSpinner.setValue(edit.t);
				lSpinner.setValue(edit.l);
			}
			else
			{
				tSpinner.setValue(conf.top);
				lSpinner.setValue(conf.left);
			}
		},

		setSPData: function(edit){
			wSpinner.setValue(edit.w);
			hSpinner.setValue(edit.h);

			tSpinner.setValue(edit.t);
			lSpinner.setValue(edit.l);
		}
	});

	 // MAIN PANEL
	 var mainSPPanel = new SPPanel({
		 id: 'FE-SE-panel',
		 items: [
		         {
		        	 border: true,
		        	 autoHeight: true,
		        	 xtype: 'fieldset',
		        	 layout: 'form',
		        	 frame: false,
		        	 title: 'Size'.localize(),
		        	 items: [
		        	         wSpinner,
		        	         hSpinner
		        	         ]
		         },
		         {
		        	 border: true,
		        	 autoHeight: true,
		        	 xtype: 'fieldset',
		        	 layout: 'form',
		        	 frame: false,
		        	 title: 'Position'.localize(),
		        	 items: [
		        	         lSpinner,
		        	         tSpinner
		        	         ]
		         }
		         ]
	 });

	 callback(mainSPPanel);
}