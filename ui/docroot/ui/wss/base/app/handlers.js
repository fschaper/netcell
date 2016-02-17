/*
 * @brief ajax
 *
 * @file handlers.js
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
 *
 * \version
 * SVN: $Id: handlers.js 4672 2011-03-04 13:58:54Z andrejv $
 *
 */

Jedox.wss.app.onFormatDropdownSelect = function (item, record, index) {
	var styleType = Jedox.wss.app.getToolbarItemID(item.getId());

	if (styleType != null)
		Jedox.wss.style.setFromBar(styleType, item.getValue());

	Ext.get('wToolbar_fontSize_cmb').blur();
	Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
	Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
};

Jedox.wss.app.onFormatDropdownFocus = function (item){
	Jedox.wss.app.lastInputMode = Jedox.wss.app.environment.inputMode;
	Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.CNTRL);

	Jedox.wss.app.switchContextObserver.subscribe(Jedox.wss.app.updateBar, this);
};

Jedox.wss.app.onFormatDropdownBlur = function (item){
	var oldFontSize = Jedox.wss.app.environment.selectedCell.style.fontSize;

	if((oldFontSize != '') && (oldFontSize.indexOf('pt') != -1))
		oldFontSize = oldFontSize.substr(0, oldFontSize.indexOf('pt'));
	else
		oldFontSize = Jedox.wss.app.cnfDefaultFontSize;

	if (oldFontSize != item.getRawValue()) {
		var styleType = Jedox.wss.app.getToolbarItemID(item.getId());

		if (styleType != null)
			Jedox.wss.style.setFromBar(styleType, item.getRawValue());
	}

	//Ext.get(item.getEl()).blur();
	Ext.get('wToolbar_fontSize_cmb').blur();
	Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
	Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;

	Jedox.wss.app.switchContextObserver.unsubscribe(Jedox.wss.app.updateBar);
};

Jedox.wss.app.onFormatDropdownChange = function (item, newValue, oldValue) {
	var styleType = Jedox.wss.app.getToolbarItemID(item.getId());

	if (styleType != null)
		Jedox.wss.style.setFromBar(styleType, newValue);

	Ext.get('wToolbar_fontSize_cmb').blur();
	Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
	Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
};

Jedox.wss.app.onFormatDropdownSpecKey = function (item, e) {
	//e.stopEvent();
	var key = Jedox.wss.app.lastKeyPressed;

	if (key == e.ENTER || key == e.TAB) {
		var oldFontSize = Jedox.wss.app.environment.selectedCell.style.fontSize;
		if((oldFontSize != '') && (oldFontSize.indexOf('pt') != -1))
			oldFontSize = oldFontSize.substr(0, oldFontSize.indexOf('pt'));
		else
			oldFontSize = Jedox.wss.app.cnfDefaultFontSize;

		if (oldFontSize != item.getRawValue()) {
			var styleType = Jedox.wss.app.getToolbarItemID(item.getId());

			if (styleType != null)
				Jedox.wss.style.setFromBar(styleType, item.getRawValue());
		}

		Ext.get('wToolbar_fontSize_cmb').blur();
		Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
		Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
	}
};

Jedox.wss.app.updateBar = function() {
	Ext.getCmp('wToolbar_fontName_cmb').collapse();
	Ext.getCmp('wToolbar_fontSize_cmb').collapse();

	Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
	Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
};

Jedox.wss.app.getToolbarItemID = function (itemName) {
	// Create associative array to map item names to IDs
	var toolbarItems = {
		'wToolbar_bold_btn': 1, 'wToolbar_italic_btn': 2, 'wToolbar_uLine_btn': 3, 'wToolbar_alignLeft_btn': 4, 'wToolbar_alignCenter_btn': 5,
		'wToolbar_alignRight_btn': 6, 'wToolbar_fontSize_cmb': 7, 'wToolbar_fontName_cmb': 8, 'wToolbar_bgColor_mn': 9, 'wToolbar_bgColor_btn': 9,
		'wToolbar_txtColor_mn': 10, 'wToolbar_txtColor_btn': 10
	};

	return toolbarItems[itemName];
};

// ==========================================
//==========================================
//==========================================

Jedox.wss.app.onFormatItemToggle = function (item, pressed){
	var styleType = Jedox.wss.app.getToolbarItemID(item.getId());

	if (styleType != null && Jedox.wss.app.performItemToggle)
		Jedox.wss.style.setFromBar(styleType, pressed);
};

Jedox.wss.app.onColorSelect = function (item, color) {
	var bgColor = Jedox.wss.app.toolbar.bgColor;
	if (bgColor)
		bgColor.hide();

	var styleType = Jedox.wss.app.getToolbarItemID(item.getId());
	if (!styleType)
		styleType = Jedox.wss.app.getToolbarItemID(item.ownerCt.getId());

	if (item.id == 'bgNoColor') {
		color = 'transparent';
		Jedox.wss.app.cnfDefaultBgColor = color;
		Ext.DomQuery.selectNode('*[class*=iconbgcolor]').style.borderLeft = "solid 4px " + color;
		Jedox.wss.style.setFromBar(9, color);
	}
	else if (typeof color == 'string') {
		if (styleType == Jedox.wss.app.getToolbarItemID('wToolbar_bgColor_mn')) {
			Jedox.wss.app.cnfDefaultBgColor = color;
			Ext.DomQuery.selectNode('*[class*=iconbgcolor]').style.borderLeft = "solid 4px #" + color;
		} else {
			Jedox.wss.app.cnfDefaultTextColor = color;
			Ext.DomQuery.selectNode('*[class*=icontextcolor]').style.borderLeft = "solid 4px #" + color;
		}
	} else {
		color = (styleType == Jedox.wss.app.getToolbarItemID('wToolbar_bgColor_mn')) ? Jedox.wss.app.cnfDefaultBgColor : Jedox.wss.app.cnfDefaultTextColor;
	}

	if (styleType != null)
		Jedox.wss.style.setFromBar(styleType, color);
};

Jedox.wss.app.onBorderSelect = function(item, ev) {
	var env = Jedox.wss.app.environment,
		rngStartCoord = env.lastRangeStartCoord,
		rngEndCoord = env.lastRangeEndCoord,
		btnBorders = Jedox.wss.app.toolbar.border,
		itemID = (item.getId() == btnBorders.getId()) ? Jedox.wss.app.cnfDefaultBorder : item.getId(), brdConf;

	switch(itemID) {
		case 'brd-bottom-norm':
			brdConf = {bottom: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-top-norm':
			brdConf = {top: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-left-norm':
			brdConf = {left: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-right-norm':
			brdConf = {right: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-all-none':
			brdConf = {all: {type: 'none'}};
			break;
		case 'brd-all-norm':
			brdConf = {all: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-out-norm':
			brdConf = {out: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-out-thick':
			brdConf = {out: {width: '2px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-bottom-thick':
			brdConf = {bottom: {width: '2px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-top-bottom-norm':
			brdConf = {top: {width: '1px', type: 'solid', color: '#000000'}, bottom: {width: '1px', type: 'solid', color: '#000000'}};
			break;
		case 'brd-top-norm-bottom-thick':
			brdConf = {top: {width: '1px', type: 'solid', color: '#000000'}, bottom: {width: '2px', type: 'solid', color: '#000000'}};
	}


	Jedox.wss.style.setBorder(brdConf);

	btnBorders.setIconClass('icon-'.concat(itemID));
	btnBorders.getEl().child(btnBorders.buttonSelector).dom.qtip = Ext.getCmp(itemID).text;
	Jedox.wss.app.cnfDefaultBorder = itemID;
};

Jedox.wss.app.openViewMode = function() {
	/*if (Jedox.wss.hb.getHBCount() > 0) {
		var quickViewBtn = Jedox.wss.app.toolbar.hbQuickView;
		if (!quickViewBtn.pressed) {
			var env = Jedox.wss.app.environment,
				HBMode = env.HBMode;

			env.HBMode = Jedox.wss.hb.HBMode.USER;
			quickViewBtn.toggle(true);
			if (env.HBMode == Jedox.wss.hb.HBMode.USER)
				env.HBMode = HBMode;
		}
	}*/

	var actNode = Jedox.wss.wnd.active.node,
		actMeta = actNode._meta,
		node = actMeta ? actMeta.g.concat('-', actMeta.h, '-', actMeta.n) : actNode.uid;

	window.open('/ui/wss/view.php?wam=designer&node='.concat(node), 'winUserMode', 'directories=no,menubar=no,toolbar=no,location=no,status=no,resizable=yes,scrollbars=no');
};

Jedox.wss.app.updateUndoState = function (undoState, updState) {
	var env = Jedox.wss.app.environment;

	if (env == null)
		return;

	if (undoState == undefined)
		undoState = env.undoState;
	else if (updState == undefined || updState)
		env.undoState = undoState;

	// Undo state.
	//if (undoState[0] > 0) {
	if (true) {
		this.toolbar.undoItem.enable();

		if (this.menubar) {
			this.menubar.undoItem.setText('Undo'.localize());
			this.menubar.undoItem.enable();
		}
	} else {
		this.toolbar.undoItem.disable();

		if (this.menubar) {
			this.menubar.undoItem.setText('Can\'t Undo'.localize());
			this.menubar.undoItem.disable();
		}
	}

	// Redo state.
	//if (undoState[1] > 0) {
	if (true) {
		this.toolbar.redoItem.enable();

		if (this.menubar) {
			this.menubar.redoItem.setText('Redo'.localize());
			this.menubar.redoItem.enable();
		}
	} else {
		this.toolbar.redoItem.disable();

		if (this.menubar) {
			this.menubar.redoItem.setText('Can\'t Redo'.localize());
			this.menubar.redoItem.disable();
		}
	}
};

//+++ Functions for HIDE/SHOW Bars +++ //
Jedox.wss.app.hideBar = function(barId)
{
	var bar = Ext.get(barId);
	bar.setVisibilityMode(Ext.Element.DISPLAY);
	bar.hide();

	Jedox.wss.wspc.resize();
};

Jedox.wss.app.showBar = function(barId)
{
	var bar = Ext.get(barId);
	bar.setVisibilityMode(Ext.Element.DISPLAY);
	bar.show();

	Jedox.wss.wspc.resize();
};

Jedox.wss.app.hideToolbar = function(toolbar)
{
	Jedox.wss.app.hideBar('Toolbar');
};

Jedox.wss.app.showToolbar = function(toolbar)
{
	Jedox.wss.app.showBar('Toolbar');
};

Jedox.wss.app.expandCollapseFormulaBar = function(){
	Jedox.wss.wspc.resize();
}

// Show hide from MenuBar
Jedox.wss.app.hideShowToolbar = function(state, toolbar)
{
	if (state)
		Jedox.wss.app.showToolbar(toolbar);
	else
		Jedox.wss.app.hideToolbar(toolbar);
};

// *** FORMULA BAR *** Show hide from MenuBar
Jedox.wss.app.hideShowFormulaBar = function(state)
{
	if (state)
		Jedox.wss.app.showBar('formulaBar');
	else
		Jedox.wss.app.hideBar('formulaBar');
};