/*
 * @brief wss file
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: SelectRange.js 4674 2011-03-07 09:58:50Z djordjez $
 *
 */

Jedox.wss.dlg.openSelectRangeDialog = function(confObj){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.SelectRange(confObj));
};

Jedox.wss.dlg.SelectRange = (function() {

	return function (confObj) {

		Jedox.wss.dlg.SelectRange.parent.constructor.call(this);
		this.id = 'selectRange';

		// Default conf.
		var that = this,
			env = Jedox.wss.app.environment,
			actSheetName = Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName(),
			conf = Jedox.wss.app.sourceSel = {
				singleCell: false,
				format: '={Sheet}!{$Range}', // {Sheet}, {$Range}, {Range}
				rng: actSheetName + '!' + env.defaultSelection.getActiveRange().getValue(true),
				initSheet: actSheetName,
				omitInitSheet: false,
				fromDlg: env.inputMode === Jedox.wss.grid.GridMode.DIALOG,

				fnc: [this, function(tmpText) {
					alert(tmpText);
				}],

				beforeSheetChange: function(cb, oldSheetName) {
					Jedox.wss.app.environment.formulaSelection.removeAll();

					if (Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName() != this.initSheet || !this.fromDlg) {
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					}

					this.oldSheet = oldSheetName;

					if (cb instanceof Array && cb.length > 1)
						cb[1].call(cb[0]);
				},

				afterSheetChange: function(newSheetName) {
					var env = Jedox.wss.app.environment;

					if (env.inputMode === Jedox.wss.grid.GridMode.DIALOG)
						this.fromDlg = true;
					else {
						Jedox.wss.app.lastInputModeDlg = env.inputMode;
						Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
					}

					// Preselect Source Range.
					var sel = resolveRange(this.rng);
					Jedox.wss.mouse.initSourceRange(undefined, [sel.rng[0], sel.rng[1]], [sel.rng[2], sel.rng[3]]);

					// Update range in dialog.
					if (this.format.search('{Sheet}') >= 0) {
						this.rng = this.rng.replace(this.oldSheet, newSheetName.search(/ /) >= 0 ? '\''.concat(newSheetName, '\'') : newSheetName);
						selRangeTxf.setValue(this.rng);
						selRangeTxf.selectText();
						selRangeTxf.focus();

						delete this.oldSheet;
					}
				}
			};

		// apply setup
		Ext.apply(conf, confObj, {});

		if (!conf.rng.length)
			conf.rng = actSheetName + '!' + env.defaultSelection.getActiveRange().getValue(true);

		//================================ Functions ============================================

		function resolveRange(range) {
			var refs = Jedox.wss.formula.parse(range);

			return refs.length == 1 ? refs[0] : false;
		}

		// format range preview
		var formatPreview = function(rawVal) {
			var sel = resolveRange(rawVal);

			if (!sel)
				return rawVal;

			var sheetName = sel.sheet,
				rangeValues = [sel.ul, sel.lr];

			if (sheetName.search(/ /) >= 0)
				sheetName = '\''.concat(sheetName, '\'');

			if (conf.singleCell || sel.ul == sel.lr)
				rangeValues.length = 1;

			// replace values
			var formatedValue = ''.concat(conf.format);

			if (conf.omitInitSheet && Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName() == conf.initSheet)
				formatedValue = formatedValue.replace('{Sheet}!', '');
			else
				formatedValue = formatedValue.replace('{Sheet}', sheetName);

			if (rangeValues.length > 1)
			{
				formatedValue = formatedValue.replace('{Range}', rangeValues[0] + ':' + rangeValues[1]);
				formatedValue = formatedValue.replace('{$Range}', (cellDollarFormat(rangeValues[0]) + ':' + cellDollarFormat(rangeValues[1])));
			}
			else
			{
				formatedValue = formatedValue.replace('{Range}', rangeValues[0]);
				formatedValue = formatedValue.replace('{$Range}', cellDollarFormat(rangeValues[0]));
			}

			return formatedValue;
		}

		var cellDollarFormat = function(cellValue)
		{
			var formatedRange = '';
			if (cellValue)
			{
				for (var i=0; i<cellValue.length; i++) {
					if (i == 0 || (parseInt(cellValue.charAt(i)) && !(parseInt(cellValue.charAt(i-1)))))
						formatedRange += '$' + cellValue.charAt(i);
					else
						formatedRange += cellValue.charAt(i);
				}
			}

			return formatedRange;
		}

		//================================ Components ============================================

		var LocalTextField = Ext.extend(Ext.form.TextField, {
			initComponent: function()
			{
				LocalTextField.superclass.initComponent.call(this);
			},
			setValue: function(val)
			{
				LocalTextField.superclass.setValue.call(this, formatPreview(val));
			}
		});
		var selRangeTxf = this.cmpFocus = new LocalTextField({
			id: 'selRange',
			hideLabel: true,
			tabIndex: 1,
			value: conf.rng,
			width: 430
		});

		//================================ Handler functions ============================================

		// Destroy all form elements and destroy self the form
		var onBeforeDestroySelRangeDlg = function(panel) {
			selRangeForm.items.each(function(f) {
	        	f.purgeListeners();
	            Ext.destroy(f);
		    });

	    	selRangeForm.purgeListeners();
			selRangeForm.destroy();
		}

		var closeAndStoreRange = function() {
			that.win.close();
		}

		var onBeforeCloseSelRangeDlg = function() {
			Jedox.wss.app.environment.formulaSelection.removeAll();

			var activeBook = Jedox.wss.app.activeBook,
				sheetSelector = activeBook.getSheetSelector();

			if (sheetSelector.getActiveSheetName() != conf.initSheet || !conf.fromDlg) {
				Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
				Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
			}

			function cbCloseSelRng(rng) {
				conf.fnc[1].call(conf.fnc[0], rng);

				Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.selectRange);
				Jedox.wss.app.activeBook._sheetSelector.enableAddTab();
				delete Jedox.wss.app.sourceSel;
			}

			// Switch back to init sheet.
			if (sheetSelector.getActiveSheetName() != conf.initSheet) {
				var sheetId = sheetSelector.getIdByName(conf.initSheet);

				if (sheetId)
					Jedox.wss.sheet.select([that, cbCloseSelRng, selRangeTxf.getValue()], sheetId, activeBook, true);
			} else
				cbCloseSelRng(selRangeTxf.getValue());
			that.close();
		}

		//================================ Main Panel ============================================
		var selRangeForm = this.containers.mainPanel = new Ext.FormPanel({
			baseCls: 'x-plain',
			labelWidth: 100,
			labelAlign: 'left',
			frame: true,
			bodyStyle: 'padding: 5px; color: #15428B; font-size: 9pt;',
			defaultType: 'textfield',
			header: false,
			monitorValid: true,
			autoHeight: true,
			layout: 'column',
			items: [new Ext.Panel({
				width: 440,
				layout: 'form',
				cls: 'chartdatasource',
				bodyStyle: 'background-color: transparent; border-style: none; padding-left: 5px;',
				items: [selRangeTxf]
			}), new Ext.Panel({
				columnWidth: 1,
				layout: 'form',
				bodyStyle: 'background-color: transparent; border-style: none;',
				items: [new Ext.Toolbar.Button({
					id: 'wSelDataSource_icon_btn',
					iconCls: 'ico_end_select_range',
					cls: 'x-btn-icon',
					tabIndex: 2,
					ctCls: Jedox.kbd.Base.tags.NO_ENTER,
					tooltip: "End Select Range".localize(),
					handler: closeAndStoreRange
				})]
			})]
		});

		//================================ Window (Dlg) ============================================
		this.win = new Ext.Window({
			title: 'Select Data Source'.localize(),
			alwaysOnTop:true,
			cls: 'wssdialog default-format-window',
			layout: 'fit',
			width: 505,
			autoHeight: true,
			minWidth: 200,
			minHeight: 30,
			closeable: true,
			closeAction: 'close',
			autoDestroy: true,
			plain: true,
			constrain: true,
			modal: false,
			items: [selRangeForm],
			listeners: {
				beforedestroy: {fn: onBeforeDestroySelRangeDlg, scope: this},
				close: {fn: onBeforeCloseSelRangeDlg, scope: this},
				show:function(){
					setTimeout(function(){
						that.initFocus(true, 100);
					});
				},
				activate: function(win) {that.activate();}
			}
		});

		this.setContext();

		var sel = resolveRange(conf.rng);

		if (!sel) {
			conf.rng = actSheetName + '!' + env.defaultSelection.getActiveRange().getValue(true);
			sel = resolveRange(conf.rng);
		}

		function init() {
			var env = Jedox.wss.app.environment;

			if (env.inputMode === Jedox.wss.grid.GridMode.DIALOG)
				conf.fromDlg = true;
			else {
				Jedox.wss.app.lastInputModeDlg = env.inputMode;
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
			}

			Jedox.wss.app.activeBook._sheetSelector.disableAddTab();

			that.win.show(that);

			selRangeTxf.selectText();

			var dlgPosition = that.win.getPosition();
			that.win.setPagePosition(dlgPosition[0], 50);

			// Preselect Source Range.
			Jedox.wss.mouse.initSourceRange(undefined, [sel.rng[0], sel.rng[1]], [sel.rng[2], sel.rng[3]]);
		}

		// Switch sheet if necessary.
		if (sel.sheet.length && sel.sheet != actSheetName) {
			var activeBook = Jedox.wss.app.activeBook,
				sheetId = activeBook.getSheetSelector().getIdByName(sel.sheet);

				if (sheetId)
					Jedox.wss.sheet.select([this, init], sheetId, activeBook, true);
				else
					init();
		} else
			init();
	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.SelectRange, Jedox.dlg.Dialog);