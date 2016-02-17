/*
 * @brief ajax
 *
 * @file Group.js
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
 * SVN: $Id: Toolbars.js 5117 2011-07-15 12:37:01Z drazenk $
 *
 */

Jedox.wss.app.initActiveToolbars = function () {
	Jedox.wss.app.toolbar = {};

	Jedox.wss.app.initStandardToolbar();
	Jedox.wss.app.initFormatToolbar();
	Jedox.wss.app.initDynarangeToolbar();
};

Jedox.wss.app.initStandardToolbar = function () {
	var tbar = Jedox.wss.app.toolbar;

	// Create StandardToolbar and place it in Jedox.wss.app namespace.
    Jedox.wss.app.standardToolbar = new Ext.Toolbar({
    	cls: 'exttoolbar',
    	renderTo: 'wssStandardToolbar',
    	items: [
			{id: 'wToolbar_New_btn', iconCls: 'icon_new_doc', tooltip: "Create new document".localize(), handler: Jedox.wss.action.newWorkbook},
			{id: 'wToolbar_Open_btn', iconCls: 'icon_open_doc', cls: 'x-btn-icon', tooltip: "Open document".localize(), handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.open, ['open']);}},
			(tbar.saveItem = new Ext.Toolbar.Button(
			    {id: 'wToolbar_Save_btn', iconCls: 'icon_save_doc', cls: 'x-btn-icon', tooltip: "Save document".localize(), handler: Jedox.wss.node.save}
			 )),
			//'-',
			(tbar.undoItem = new Ext.Toolbar.Button(
			    {id: 'wToolbar_Undo_btn', iconCls: 'icon_undo', cls: 'x-btn-icon', tooltip: "Undo".localize(), handler: Jedox.wss.sheet.undo, hidden: true}
			)),
			(tbar.redoItem = new Ext.Toolbar.Button(
				{id: 'wToolbar_Redo_btn', iconCls: 'icon_redo', cls: 'x-btn-icon', tooltip: "Redo".localize(), handler: Jedox.wss.sheet.redo, hidden: true}
			)),
			'-',
			{id: 'wToolbar_copy_btn', iconCls: 'icon_copy', cls: 'x-btn-icon', tooltip: "Copy".localize(), handler: function(){Jedox.wss.action.copy(false);}},
			{id: 'wToolbar_cut_btn', iconCls: 'icon_cut', cls: 'x-btn-icon', tooltip: "Cut".localize(), handler: function(){Jedox.wss.action.cut(false);}},
			(tbar.paste = new Ext.Toolbar.Button(
			    {id: 'wToolbar_paste_btn', iconCls: 'icon_paste', cls: 'x-btn-icon', tooltip: "Paste".localize(), disabled: true, handler: Jedox.wss.action.paste}
			)),
			(tbar.formatPainter = new Ext.Toolbar.Button({
				iconCls: 'icon_format_painter',
				cls: 'x-btn-icon',
				id: 'wToolbar_FmtPainter_btn',
				tooltip: "Format painter".localize(),
				enableToggle: true,
				pressed: false,
				timer:null,
				clicked:false,
				listeners:{
					click:function(){
						var that = this;

						if(this.clicked){//Dbl click
							clearTimeout(this.timer);
							this.toggle(true, true);
							Jedox.wss.app.formatPainter = 2;
							Jedox.wss.action.copy(false);
							Jedox.wss.action.setCursorCSS(true);
						}
						else {//click
							this.timer = setTimeout(function(){
								clearTimeout(that.timer);
								that.clicked = false;
								if(that.pressed){
									Jedox.wss.app.formatPainter = 1;
									Jedox.wss.action.copy(false);
									Jedox.wss.action.setCursorCSS(true);
								}
								else {
									Jedox.wss.action.exitFormatPainter();
								}

							}, 400);
						}

						this.clicked = !this.clicked;
					}
				}
			})),
			'  '
    	]
    });
};

Jedox.wss.app.initFormatToolbar = function () {
	var tbar = Jedox.wss.app.toolbar;

	// Create FormatToolbar and place it in Jedox.wss.app namespace.
	// N.B: absolute layout is mandatory in this particular toolbar due to combobox rendering problem. -andrejv
    Jedox.wss.app.formatToolbar = new Ext.Toolbar({
    	cls: 'exttoolbar',
    	renderTo: 'wssFormatToolbar',
    	layout: 'absolute',
    	width: 566,
    	height: 27,
    	items: [

	        // Add dropdown list - Fonts.
	        // TODO: Apply font style to items in the dropdown list.
	    	// TODO: Make font-family dropdown list editable.
	        (tbar.fonts = new Ext.form.ComboBox({
	        	id: 'wToolbar_fontName_cmb',
	    		displayField: 'fontname',
	    		valueField: 'fontdef',
	    		typeAhead: true,
	    		x: 2, y: 3,
	    		editable: true,
	    		mode: 'local',
	    		triggerAction: 'all',
	    		ctCls: 'toolbar-combo',
	    		selectOnFocus: true,
	    		forceSelection: true,
	    		value: Jedox.wss.app.cnfDefaultFont,
	    		listWidth: 160,
	    		width: 120,
	    		//style: 'margin-bottom: 1px',
	    		tpl: '<tpl for="."><div class="x-combo-list-item" style="font-family: {fontdef}; color: #15428B;">{fontname}</div></tpl>',

	    		store: new Ext.data.SimpleStore({
		            fields: ['fontname', 'fontdef'],
		            data: Jedox.wss.style.fonts
		        }),

		        listeners: {
		        	select: {fn: Jedox.wss.app.onFormatDropdownSelect, scope: this},
		        	focus: {fn: Jedox.wss.app.onFormatDropdownFocus, scope: this},
		        	blur: {fn: Jedox.wss.app.onFormatDropdownBlur, scope: this}
	        	}
	        })),
	        ' ',

	        // Add dropdown list - Font Sizes.
	    	// TODO: Make font-size dropdown list editable.
	        (tbar.fontSizes = new Ext.form.ComboBox({
	        	id: 'wToolbar_fontSize_cmb',
	    		displayField: 'fontsize',
	    		valueField: 'fontsize',
	    		typeAhead: true,
	    		x: 124, y: 3,
	    		editable: true,
	    		selectOnFocus: true,
	    		mode: 'local',
	    		triggerAction: 'all',
	    		forceSelection: false,
	    		value: Jedox.wss.app.cnfDefaultFontSize,
	    		listWidth: 110,
	    		width: 40,
	    		//style: 'margin-bottom: 1px',
	    		allowBlank: false,
	    		applyTo: tbar.fontSizes,
	    		tpl: '<tpl for="."><div class="x-combo-list-item" style="font-size: {fontsize}pt; color: #15428B;">{fontsize}</div></tpl>',

	    		store: new Ext.data.SimpleStore({
		            fields: ['fontsize'],
		            data : Jedox.wss.style.fontSizes
		        }),

		        listeners: {
		        	'change': {fn: Jedox.wss.app.onFormatDropdownChange, scope: this},
		        	'select': {fn: Jedox.wss.app.onFormatDropdownSelect, scope: this},
		        	'focus': {fn: Jedox.wss.app.onFormatDropdownFocus, scope: this},
		        	'blur': {fn: Jedox.wss.app.onFormatDropdownBlur, scope: this},
		        	'specialkey': {fn: Jedox.wss.app.onFormatDropdownSpecKey, scope: this}
	        	}
	        })),
	        ' ',

	        (tbar.bold = new Ext.Toolbar.Button(
	           	{id: 'wToolbar_bold_btn', x: 166, y: 2, iconCls: 'icon_font'.concat('_bold'.localize()), cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Bold".localize()}
	        )),
	        (tbar.italic = new Ext.Toolbar.Button(
	            {id: 'wToolbar_italic_btn', x: 187, y: 2, iconCls: 'icon_font'.concat('_italic'.localize()), cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Italic".localize()}
	        )),
	        (tbar.underline = new Ext.Toolbar.Button(
	           	{id: 'wToolbar_uLine_btn', x: 208, y: 2, iconCls: 'icon_font_underline', cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Underline".localize()}
	        )),
	        {xtype: 'tbseparator', x: 230, y: 4},
	        (tbar.alignLeft = new Ext.Toolbar.Button(
	           	{id: 'wToolbar_alignLeft_btn', x: 238, y: 2, iconCls: 'icon_align_left', cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Align Text Left".localize()}
	        )),
	        (tbar.alignCenter = new Ext.Toolbar.Button(
	        	{id: 'wToolbar_alignCenter_btn', x: 259, y: 2, iconCls: 'icon_align_center', cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Center text".localize()}
	        )),
	        (tbar.alignRight = new Ext.Toolbar.Button(
	            {id: 'wToolbar_alignRight_btn', x: 280, y: 2, iconCls: 'icon_align_right', cls: 'x-btn-icon', enableToggle: true, pressed: false, toggleHandler: Jedox.wss.app.onFormatItemToggle, tooltip: "Align Text Right".localize()}
	        )),
	        {xtype: 'tbseparator', x: 302, y: 4},
	        (tbar.border = new Ext.Toolbar.SplitButton({
	    		id: 'wToolbar_Border_btn',
	    		x: 310, y: 2,
	    		iconCls: 'icon-brd-bottom-norm',
	    		tooltip: 'Bottom Border'.localize(),
	    		handler: this.onBorderSelect,
	    		menu: {
	        		cls: 'default-format-window',
	        		items: [
	    				{id: 'brd-bottom-norm', text: 'Bottom Border'.localize(), iconCls: 'icon-brd-bottom-norm', handler: this.onBorderSelect},
	    				{id: 'brd-top-norm', text: 'Top Border'.localize(), iconCls: 'icon-brd-top-norm', handler: this.onBorderSelect},
	    				{id: 'brd-left-norm', text: 'Left Border'.localize(), iconCls: 'icon-brd-left-norm', handler: this.onBorderSelect},
	    				{id: 'brd-right-norm', text: 'Right Border'.localize(), iconCls: 'icon-brd-right-norm', handler: this.onBorderSelect},
	    				'-',
	    				{id: 'brd-all-norm', text: 'All Borders'.localize(), iconCls: 'icon-brd-all-norm', handler: this.onBorderSelect},
	    				{id: 'brd-out-norm', text: 'Outside Borders'.localize(), iconCls: 'icon-brd-out-norm', handler: this.onBorderSelect},
	    				{id: 'brd-out-thick', text: 'Thick Outside Border'.localize(), iconCls: 'icon-brd-out-thick', handler: this.onBorderSelect},
	    				{id: 'brd-all-none', text: 'No Border'.localize(), iconCls: 'icon-brd-all-none', handler: this.onBorderSelect},
	    				'-',
	    				{id: 'brd-top-bottom-norm', text: 'Top and Bottom Border'.localize(), iconCls: 'icon-brd-top-bottom-norm', handler: this.onBorderSelect},
	    				{id: 'brd-bottom-thick', text: 'Thick Bottom Border'.localize(), iconCls: 'icon-brd-bottom-thick', handler: this.onBorderSelect},
	    				{id: 'brd-top-norm-bottom-thick', text: 'Top and Thick Bottom Border'.localize(), iconCls: 'icon-brd-top-norm-bottom-thick', handler: this.onBorderSelect},
	    				'-',
	    				{id: 'formatCellsBorders', text: 'More Borders'.localize().concat('...'), iconCls: 'icon-brd-more', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.formatCells, ['formatCellsBorders']);}}
	    			]
	    		}
	    	})),
	    	new Ext.Toolbar.Button(
	    	    {id: 'wToolbar_MergeCells_btn', x: 346, y: 2, iconCls: 'icon_merge_cells', cls: 'x-btn-icon', handler: function(){Jedox.wss.action.mergeCells(false);}, tooltip: "Merge Cells".localize()}
	    	),
	    	new Ext.Toolbar.Button(
	    	   	{id: 'wToolbar_UnmergeCells_btn', x: 367, y: 2, iconCls: 'icon_unmerge_cells', cls: 'x-btn-icon', handler: function(){Jedox.wss.action.mergeCells(true);}, tooltip: "Unmerge Cells".localize()}
	    	),
	    	{xtype: 'tbseparator', x: 389, y: 4},
	        new Ext.Toolbar.SplitButton({
				id: 'wToolbar_bgColor_btn',
				iconCls: 'iconbgcolor',
				x: 397, y: 2,
				tooltip: "Fill Color".localize(),
				handler: Jedox.wss.app.onColorSelect,
				menu: (tbar.bgColor = new Ext.menu.Menu({
					id: 'wToolbar_bgColor_mn',
					colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
					cls: 'wide-color-palette',
					iconCls: 'no-icon',
					handler: Jedox.wss.app.onColorSelect,
					items: [
						{
							text: 'No Color'.localize(),
							id: 'bgNoColor',
							handler: Jedox.wss.app.onColorSelect
						},
						new Ext.ColorPalette({
							colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
							handler: Jedox.wss.app.onColorSelect,
							allowReselect: true
						})
					]
				}))
	    	}),
	        new Ext.Toolbar.SplitButton({
	    		id: 'wToolbar_txtColor_btn',
	    		iconCls: 'icontextcolor',
	    		x: 437, y: 2,
	    		tooltip: "Font Color".localize(),
	    		handler: Jedox.wss.app.onColorSelect,
	    		menu: new Ext.menu.ColorMenu({
	    			id: 'wToolbar_txtColor_mn',
	    			allowReselect: true,
	    			iconCls: 'no-icon',
	    			colors: Jedox.wss.style.colorPalettes[Jedox.wss.app.activeColorPalette],
	    			cls: 'wide-color-palette',
	    			handler: Jedox.wss.app.onColorSelect
	    		})
	    	}),
	    	{xtype: 'tbseparator', x: 477, y: 4},
	    	new Ext.Toolbar.Button(
	    	    	{id: 'wToolbar_Chart_btn', x: 485, y: 2, iconCls: 'icon_insert_chart', cls: 'x-btn-icon', tooltip: "Insert Chart".localize(), handler: function() {Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chart, ['insert', 0]);}}
	    	),
	    	{xtype: 'tbseparator', x: 507, y: 4},
	    	(tbar.lock = new Ext.Toolbar.Button(
	    		{id: 'wToolbar_Lock_btn', x: 515, y: 2, iconCls: 'icon_lock', cls: 'x-btn-icon', enableToggle: true, pressed: true, toggleHandler: Jedox.wss.style.toggleLock, tooltip: "Item Lock/Unlock".localize()}
	    	)),
	    	{xtype: 'tbseparator', x: 537, y: 4}
    	]
    });

	Ext.DomQuery.selectNode('*[class*=iconbgcolor]').style.borderLeft = "solid 4px #FF0000";
	Ext.DomQuery.selectNode('*[class*=icontextcolor]').style.borderLeft = "solid 4px #FFFF00";
};

Jedox.wss.app.initDynarangeToolbar = function () {
	var tbar = Jedox.wss.app.toolbar;

	// Create DynarangeToolbar and place it in Jedox.wss.app namespace.
    Jedox.wss.app.hbToolbar = new Ext.Toolbar({
    	cls: 'exttoolbar',
    	renderTo: 'wssDynarangeToolbar',
    	items: [
    	    (tbar.newHBVert = new Ext.Toolbar.Button(
    	    	{id: 'wToolbar_newHBVert_btn', iconCls: 'icon_vert_dynarange', cls: 'x-btn-icon', tooltip: "Vertical Dynarange".localize(), handler: Jedox.wss.hb.addDynarange}
    	    )),
    	    (tbar.newHBHoriz = new Ext.Toolbar.Button(
    	    	{id: 'wToolbar_newHBHoriz_btn', iconCls: 'icon_hor_dynarange', cls: 'x-btn-icon', tooltip: "Horizontal Dynarange".localize(), handler: Jedox.wss.hb.addDynarange}
        	)),
        	(tbar.hbQuickView = new Ext.Toolbar.Button(
        		{id: 'wToolbar_HBQuickView_btn', iconCls: 'icon_designer_preview', cls: 'x-btn-icon', tooltip: "Designer Preview".localize(), enableToggle: true, pressed: false, toggleHandler: Jedox.wss.hb.run}
        	)),
        	'-',
        	(tbar.userModeView = new Ext.Toolbar.Button(
        		{id: 'wToolbar_ViewMode_btn', iconCls: 'icon_user_mode', cls: 'x-btn-icon', tooltip: "Open User Mode".localize(), handler: Jedox.wss.app.openViewMode}
        	))
        ]
    });
};