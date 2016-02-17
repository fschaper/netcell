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
 * SVN: $Id: Protection.js 4798 2011-04-03 02:09:27Z predragm $
 *
 */

Jedox.wss.dlg.format.protection = function(callback, _pre, isFromOther, tabOffset) {

	// protection tab
	var env = Jedox.wss.app.environment,
			rngStartCoord = env.lastRangeStartCoord,
			rngEndCoord = env.lastRangeEndCoord,
			inputCheckBoxValue = isFromOther ? _pre : Jedox.wss.app.activePane.getRangeLock([ rngStartCoord[0], rngStartCoord[1], rngEndCoord[0], rngEndCoord[1] ]);

	//	###### PROTECTION TAB ########

	inputCheckBoxValue = (inputCheckBoxValue == undefined || inputCheckBoxValue === '')? null : inputCheckBoxValue;

	var isLockedTriCB = new Ext.ux.form.TriCheckbox({
		name : 'isLockedcb',
		xtype: 'tri-checkbox',
		boxLabel: 'Locked'.localize(),
		id: 'tribox',
		//tabIndex: 1 + tabOffset,
		fieldLabel : 'Locked'.localize(),
		hideLabel : true,
		checked: inputCheckBoxValue
		// values: null, true, false
		,listeners: {
			check: function(cmp, state){}
		}
	});

	var protectionTab = new Ext.Panel({
		baseCls: 'x-title-f',
		labelWidth: 100,
		labelAlign: 'left',
		frame: false,
		bodyStyle: 'padding: 10px; color: #000000; font-size: 9pt; background-color: transparent;',
		header: false,
		monitorValid: true,
		autoHeight: true,
		autoWidth: true,
		listeners: {
			doLock: function(callback){
				var outputCheckBoxValue = isLockedTriCB.getValue();


					if (!isFromOther)
						{
						if (outputCheckBoxValue == null) return;
						if (inputCheckBoxValue!=outputCheckBoxValue)
							Jedox.wss.app.activeSheet.setRangeLock([ rngStartCoord[0], rngStartCoord[1], rngEndCoord[0], rngEndCoord[1] ], outputCheckBoxValue);
						}
					else
						{callback((inputCheckBoxValue!=outputCheckBoxValue)? outputCheckBoxValue : null);}
			}
		},
		items: [
		        isLockedTriCB,
		        new Ext.form.Checkbox({
		        	hideLabel: true,
		        	name: 'hidden',
		        	tabIndex: 2 + tabOffset,
		        	disabled : true,
		        	boxLabel: 'Hidden'.localize()
		        }),
		        {html:'Locking cells or hiding formulas has no effect until you protect the worksheet.'.localize(),
		        	baseCls: 'x-plain'}
		        ]
	});
//	END of PROTECTION tab

	callback(protectionTab);

}