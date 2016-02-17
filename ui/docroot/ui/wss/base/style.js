/*
 * \brief style routines and constants
 *
 * \file style.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: style.js 5038 2011-06-07 15:16:03Z predragm $
 *
 */

Jedox.wss.style = new function ()
{
	var that = this,
			_conn = Jedox.backend,
			_re_textAlign = /text-align: *(left|right|center);/i;

	this.mapJStoCSS = {
	  fontWeight: 'font-weight'
	, fontStyle: 'font-style'
	, textDecoration: 'text-decoration'
	, textAlign: 'text-align'
	, textIndent: 'text-indent'
	, fontSize: 'font-size'
	, fontFamily: 'font-family'
	, background: 'background'
	, backgroundColor: 'background-color'
	, backgroundImage: 'background-image'
	, color: 'color'
	, border: 'border'
	, borderTop: 'border-top'
	, borderLeft: 'border-left'
	, borderRight: 'border-right'
	, borderBottom: 'border-bottom'
	, whiteSpace: 'white-space'
	, verticalAlign: 'vertical-align'
	, direction: 'direction'
	};

	this.mapCSStoJS = {
	  'font-weight': 'fontWeight'
	, 'font-style': 'fontStyle'
	, 'text-decoration': 'textDecoration'
	, 'text-align': 'textAlign'
	, 'text-indent': 'textIndent'
	, 'font-size': 'fontSize'
	, 'font-family': 'fontFamily'
	, 'background': 'background'
	, 'background-color': 'backgroundColor'
	, 'background-image': 'backgroundImage'
	, 'color': 'color'
	, 'border': 'border'
	, 'border-top': 'borderTop'
	, 'border-left': 'borderLeft'
	, 'border-right': 'borderRight'
	, 'border-bottom': 'borderBottom'
	, 'white-space': 'whiteSpace'
	, 'vertical-align': 'verticalAlign'
	, 'direction': 'direction'
	};

	this.fonts = [
	  ['Arial', 'Arial,sans-serif']
	, ['Arial Black', 'Arial Black,sans-serif']
	, ['Comic Sans MS', 'Comic Sans MS,cursive']
	, ['Courier New', 'Courier New,monospace']
	, ['Garamond', 'Garamond,serif']
	, ['Georgia', 'Georgia,serif']
	, ['Lucida Console', 'Lucida Console,monospace']
	, ['Lucida Sans', 'Lucida Sans,monospace']
	, ['Palantino Linotype', 'Palantino Linotype,serif']
	, ['Tahoma', 'Tahoma,sans-serif']
	, ['Times New Roman', 'Times New Roman,serif']
	, ['Trebuchet MS', 'Trebuchet MS,sans-serif']
	, ['Verdana', 'Verdana,sans-serif']
	];

	this.fontCSSMap = {
	  'Arial,sans-serif': 0
	, 'Arial Black,sans-serif': 1
	, 'Comic Sans MS,cursive': 2
	, 'Courier New,monospace': 3
	, 'Garamond,serif': 4
	, 'Georgia,serif': 5
	, 'Lucida Console,monospace': 6
	, 'Lucida Sans,monospace': 7
	, 'Palantino Linotype,serif': 8
	, 'Tahoma,sans-serif': 9
	, 'Times New Roman,serif': 10
	, 'Trebuchet MS,sans-serif': 11
	, 'Verdana,sans-serif': 12
	};

	this.fontSizes = [
	  ['8']
	, ['9']
	, ['10']
	, ['11']
	, ['12']
	, ['14']
	, ['16']
	, ['18']
	, ['20']
	, ['22']
	, ['24']
	, ['26']
	, ['28']
	, ['36']
	, ['48']
	, ['72']
	];

	this.colorPalettes = {
	  main: [
		  "FFFFFF", "000000", "EEECE1", "1F497D", "4F81BD", "C0504D", "9BBB59", "8064A2", "4BACC6", "F79646"
		, "F2F2F2", "7F7F7F", "DDD9C3", "6CD9F0", "DBE5E1", "F2DCDB", "EBF1DD", "E5E0EC", "DBEEF3", "FDEADA"
		, "D8D8D8", "595959", "C4BD97", "8DB3E2", "B8CCE4", "E5B9B7", "D7E3BC", "CCC1D9", "B7DDE8", "FBD5B5"
		, "BFBFBF", "3F3F3F", "938953", "548DD4", "95B3D7", "D99694", "C3D69B", "B2A2C7", "92CDDC", "FAC08F"
		, "A5A5A5", "262626", "494429", "17365D", "366092", "953734", "76923C", "5F497A", "31859B", "E36C09"
		, "7F7F7F", "0C0C0C", "1D1B10", "0F243E", "244061", "632423", "4F6128", "3F3151", "205867", "974806"
		, "C00000", "FF0000", "FFC000", "FFFF00", "92D050", "00B050", "00B0F0", "0070C0", "002060", "7030A0"
		]
	, extjs: [
		  "000000", "993300", "333300", "003300", "003366", "000080", "333399", "333333"
		, "800000", "FF6600", "808000", "008000", "008080", "0000FF", "666699", "808080"
		, "FF0000", "FF9900", "99CC00", "339966", "33CCCC", "3366FF", "800080", "969696"
		, "FF00FF", "FFCC00", "FFFF00", "00FF00", "00FFFF", "00CCFF", "993366", "C0C0C0"
		, "FF99CC", "FFCC99", "FFFF99", "CCFFCC", "CCFFFF", "99CCFF", "CC99FF", "FFFFFF"
		]
	};

	this.defTextAlign = {
	  e: ''
	, n: ''
	, s: 'left'
	, b: 'center'
	, h: 'left'
	};

	this.borderType = {
	  NONE: 0
	, TOP: 1
	, BOTTOM: 2
	, LEFT: 4
	, RIGHT: 8
	, OUT: 1 | 2 | 4 | 8
	, INS_HORIZ: 16
	, INS_VERT: 32
	, INS: 16 | 32
	, ALL: 1 | 2 | 4 | 8 | 16 | 32
	};

	this.hyperlinkStyle = 'text-decoration:underline;color:#0000ff;font-style:normal;';
	this.delHyperlinkStyle = 'text-decoration:none;color:#000000;';

	this.convJStoCSS = function (style)
	{
		if (!(style instanceof Object) || 'length' in style)
			return '';

		var attr, attrCSS, styleCSS = '';

		for (attr in style)
			if ((attrCSS = that.mapJStoCSS[attr]) !== undefined)
				styleCSS = styleCSS.concat(attrCSS, ':', style[attr], ';');

		return styleCSS;
	};

	this.convCSStoJS = function (style)
	{
		if (style === '')
			return null;

		var pair, attrJS, styleJS = {},
				i = -1;

		style = style.split(';');

		while ((pair = style[++i]) !== undefined)
		{
			pair = pair.split(':');

			if ((attrJS = that.mapCSStoJS[pair[0]]) !== undefined)
				styleJS[attrJS] = pair[1];
		}

		return styleJS;
	};

	this.set = function (style)
	{
		var env = Jedox.wss.app.environment,
				activeSheet = Jedox.wss.app.activeSheet,
				activePane = activeSheet._aPane,
				cellCoords = env.selectedCellCoords,
				defSel = env.defaultSelection,
				styleCSS = that.convJStoCSS(style),
				cmdData = [],
				contentHeight;

		if (styleCSS == '')
			return;

		_conn.ccmdBuffer();

		if (defSel.isSingleCell())
		{
			var mi = activePane.getMergeInfo(cellCoords[0], cellCoords[1]);

			if (mi && mi[0])
			{
				var rangeCoords = [ cellCoords[0], cellCoords[1], cellCoords[0] + mi[1] - 1, cellCoords[1] + mi[2] - 1 ];

				activeSheet.setRangeStyle(rangeCoords, style);

				cmdData.push([ rangeCoords[0], rangeCoords[1], rangeCoords[2], rangeCoords[3], { s: styleCSS } ]);
			}
			else
			{
				activeSheet.setCellStyle(cellCoords[0], cellCoords[1], style);

				cmdData.push([ cellCoords[0], cellCoords[1], cellCoords[0], cellCoords[1], { s: styleCSS } ]);

				if (contentHeight = style.fontSize || style.fontFamily ? that.getContentHeight(env.selectedCell) : 0)
					activeSheet.adjustRowHeights(cellCoords[1], cellCoords[1], contentHeight);
			}
		}
		else
			for (var corners, rangeCoords, areas = defSel.getRanges(), i = areas.length - 1; i >= 0; --i)
			{
				corners = areas[i].getCorners();
				rangeCoords = [ corners[0].getX(), corners[0].getY(), corners[1].getX(), corners[1].getY() ];

				activeSheet.setRangeStyle(rangeCoords, style);

				cmdData.push([ rangeCoords[0], rangeCoords[1], rangeCoords[2], rangeCoords[3], { s: styleCSS } ]);

				if (contentHeight || (contentHeight == undefined && (contentHeight = style.fontSize || style.fontFamily ? that.getContentHeight(env.selectedCell) : 0)))
					activeSheet.adjustRowHeights(rangeCoords[1], rangeCoords[3], contentHeight);
			}

		if (cmdData.length)
			_conn.ccmd(null, [ 'cdrn', { cm: true } ].concat(cmdData));

		_conn.ccmdFlush(true);
		activeSheet.clearPaneCache();
	};

	this.setFromBar = function (code, val)
	{
		var env = Jedox.wss.app.environment,
				activePane = Jedox.wss.app.activePane,
				cellStyle = env.selectedCell.style,
				cellCoords = env.selectedCellCoords,
				setDefTextAlign = false,
				style = {},
				textAlign;

		if (code >= 4 && code <= 6)
			textAlign = (textAlign = activePane.getCellStyle(cellCoords[0], cellCoords[1])) != undefined && (textAlign = textAlign.match(_re_textAlign)) != null ? textAlign[1] : '';

		switch (code)
		{
			case 1:
				style['fontWeight'] = cellStyle.fontWeight != 'bold' ? 'bold' : '';
				break;

			case 2:
				style['fontStyle'] = cellStyle.fontStyle != 'italic' ? 'italic' : '';
				break;

			case 3:
				style['textDecoration'] = cellStyle.textDecoration != 'underline' ? 'underline' : '';
				break;

			case 4:
				style['textAlign'] = textAlign != 'left' ? 'left' : (setDefTextAlign = '');

				Jedox.wss.app.performItemToggle = false;
				Jedox.wss.app.toolbar.alignCenter.toggle(false);
				Jedox.wss.app.toolbar.alignRight.toggle(false);
				Jedox.wss.app.performItemToggle = true;
				break;

			case 5:
				style['textAlign'] = textAlign != 'center' ? 'center' : (setDefTextAlign = '');

				Jedox.wss.app.performItemToggle = false;
				Jedox.wss.app.toolbar.alignLeft.toggle(false);
				Jedox.wss.app.toolbar.alignRight.toggle(false);
				Jedox.wss.app.performItemToggle = true;
				break;

			case 6:
				style['textAlign'] = textAlign != 'right' ? 'right' : (setDefTextAlign = '');

				Jedox.wss.app.performItemToggle = false;
				Jedox.wss.app.toolbar.alignLeft.toggle(false);
				Jedox.wss.app.toolbar.alignCenter.toggle(false);
				Jedox.wss.app.performItemToggle = true;
				break;

			case 7:
				style['fontSize'] = val.concat('pt');
				break;

			case 8:
				style['fontFamily'] = val;
				break;

			case 9:
				style['backgroundColor'] = val == 'transparent' ? '' : '#'.concat(val);
				break;

			case 10:
				style['color'] = '#'.concat(val);
				break;

			default:
				return;
		}

		that.set(style);

		if (setDefTextAlign === '')
			env.selectedCell.style.textAlign = that.defTextAlign[activePane.getCellType(cellCoords[0], cellCoords[1])];

		Jedox.wss.app.activeSheet._defaultSelection.getCursorField().cloneStyle();

		Jedox.wss.hb.setAllNormal(null, true);
	};

	this.syncBar = function ()
	{
		var env = Jedox.wss.app.environment;

		if (env.viewMode == Jedox.wss.grid.viewMode.USER)
			return;

		var app = Jedox.wss.app,
				activePane = app.activePane,
				fTbar = app.toolbar,
				cellStyle = env.selectedCell.style,
				fontSize = cellStyle.fontSize.split('pt'),
				cellCoords = env.selectedCellCoords,
				textAlign, cellLocked, fontId;

		if (activePane != undefined)
		{
			if ((textAlign = activePane.getCellStyle(cellCoords[0], cellCoords[1])) != undefined)
			{
				textAlign = textAlign.match(_re_textAlign);

				if (textAlign != null)
					textAlign = textAlign[1];
			}

			cellLocked = activePane.isCellLocked(cellCoords[0], cellCoords[1]);
		}
		else
			textAlign = cellStyle.textAlign, cellLocked = true;

		app.performItemToggle = false;

		fTbar.bold.toggle(cellStyle.fontWeight == 'bold');
		fTbar.italic.toggle(cellStyle.fontStyle == 'italic');
		fTbar.underline.toggle(cellStyle.textDecoration == 'underline');
		fTbar.alignLeft.toggle(textAlign == 'left');
		fTbar.alignCenter.toggle(textAlign == 'center');
		fTbar.alignRight.toggle(textAlign == 'right');
		fTbar.lock.toggle(cellLocked);

		app.performItemToggle = true;

		fTbar.fontSizes.setValue(fontSize.length == 2 ? fontSize[0] : app.cnfDefaultFontSize);
		fTbar.fonts.setValue((fontId = that.fontCSSMap[cellStyle.fontFamily]) != undefined ? that.fonts[fontId][0] : app.cnfDefaultFont);
	};

	this.cellTransfer = function (dstCell, srcCell)
	{
		var env = Jedox.wss.app.environment;

		if (!env)
			return;

		var srcCellCoords = env.selectedCellCoords;

		if (!srcCell)
			srcCell = env.selectedCell ? env.selectedCell : Jedox.wss.app.activePane.getCellByCoords(srcCellCoords[0], srcCellCoords[1]);

		if (!srcCell || !srcCell.style)
			return;

		dstCell.style.fontWeight = srcCell.style.fontWeight;
		dstCell.style.fontStyle = srcCell.style.fontStyle;
		dstCell.style.fontSize = srcCell.style.fontSize;
		dstCell.style.fontFamily = srcCell.style.fontFamily;
		dstCell.style.textDecoration = srcCell.style.textDecoration;
		dstCell.style.color = srcCell.style.color;

		dstCell.style.whiteSpace = srcCell.style.whiteSpace;
		dstCell.style.textIndent = srcCell.style.textIndent;

		dstCell.style.textAlign = srcCell.style.textAlign;
		dstCell.style.verticalAlign = srcCell.style.verticalAlign;
		dstCell.style.direction = srcCell.style.direction;

		dstCell.style.backgroundColor = srcCell.style.backgroundColor;
		dstCell.style.backgroundImage = srcCell.style.backgroundImage;
	};

	this.borderStyle2CSS = function (edata)
	{
		if (!(edata instanceof Object) || 'length' in edata || edata.type == 'none')
			return '';

		var css = ('width' in edata ? edata.width : 'thin').concat(' ', ('type' in edata ? edata.type : 'solid'), ' ', ('color' in edata ? edata.color : '#000000'));

		return css.replace(/ /g, '') != '' ? css : '';
	};

	this.setBorder = function (bdata)
	{
		var activeBook = Jedox.wss.app.activeBook,
				ranges = Jedox.wss.app.environment.defaultSelection.getRanges();

		_conn.ccmdBuffer();

		for (var mi, range, i = ranges.length - 1; i >= 0; --i)
		{
			range = ranges[i].getCoords();

			if (range[0] == range[2] && range[1] == range[3] && (mi = activeBook._aPane.getMergeInfo(range[0], range[1])) && mi[0])
				range[2] += mi[1] - 1, range[3] += mi[2] - 1;

			if ('all' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.ALL, that.borderStyle2CSS(bdata.all) ]);

			if ('out' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.OUT, that.borderStyle2CSS(bdata.out) ]);

			if ('ins' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.INS, that.borderStyle2CSS(bdata.ins) ]);

			if ('top' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.TOP, that.borderStyle2CSS(bdata.top) ]);

			if ('bottom' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.BOTTOM, that.borderStyle2CSS(bdata.bottom) ]);

			if ('left' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.LEFT, that.borderStyle2CSS(bdata.left) ]);

			if ('right' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.RIGHT, that.borderStyle2CSS(bdata.right) ]);

			if ('ins_horiz' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.INS_HORIZ, that.borderStyle2CSS(bdata.ins_horiz) ]);

			if ('ins_vert' in bdata)
				_conn.ccmd(null, [ 'sbrd', range, that.borderType.INS_VERT, that.borderStyle2CSS(bdata.ins_vert) ]);
		}

		_conn.ccmdFlush(true, true, _conn.Q_STYLE, _conn.D_NONE);
	};

	this.getBorder = function ()
	{
		var ranges = Jedox.wss.app.environment.defaultSelection.getRanges(),
				types = [ 'top', 'bottom', 'left', 'right', 'ins_horiz', 'ins_vert' ],
				indices = { 0: true, 1: true, 2: true, 3: true, 4: true, 5: true },
				bdata = {},
				ccmd = [],
				css, type;

		for (var i = ranges.length - 1; i >= 0; --i)
			ccmd.unshift([ 'gbrd', ranges[i].getCoords() ]);

		var res = (new Jedox.backend.CCmdSyncRqst(ccmd)).send(),
				fres = res[0][1],
				cres;

		if (!fres.length)
			return {};

		for (var i = res.length - 1; i >= 1; --i)
		{
			cres = res[i][1];

			if (!cres.length)
				return {};

			for (var idx in indices)
				if (cres[idx] != fres[idx])
					fres[idx] = 'mixed';
		}

		for (var idx in indices)
		{
			if ((css = fres[idx]) == '')
				continue;

			type = types[idx];

			if (css == 'mixed')
				bdata[type] = { mixed: true };
			else if ((css = css.split(' ')).length == 3)
				bdata[type] = { width: css[0], type: css[1], color: css[2] };
		}

		return bdata;
	};

	this.getContentHeight = function (div)
	{
		var old_height = div.style.height,
				empty_div = false;

		if (div.innerHTML == '')
			empty_div = true, div.innerHTML = '_';

		div.style.height = 'auto';

		var height = div.offsetHeight - 2;

		div.style.height = old_height;

		if (empty_div)
			div.innerHTML = '';

		return height;
	};

	this.toggleLock = function ()
	{
		var app = Jedox.wss.app,
				env = app.environment,
				startCoord = env.lastRangeStartCoord,
				endCoord = env.lastRangeEndCoord;

		if (app.performItemToggle)
			app.activeSheet.setRangeLock([ startCoord[0], startCoord[1], endCoord[0], endCoord[1] ], app.toolbar.lock.pressed);
	};

};