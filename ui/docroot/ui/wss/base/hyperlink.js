/*
 * \brief hyperlink routines
 *
 * \file hyperlink.js
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
 *
 * \version
 * SVN: $Id: hyperlink.js 5160 2011-07-29 13:00:33Z predragm $
 *
 */

Jedox.wss.hl = new function() {
	var that = this,

		_defCnt = '_new';

	this.hlTag = {begin: '<span class="hl" onmouseover="Jedox.wss.hl.toolTip(event, true);" onmouseout="Jedox.wss.hl.toolTip(event, false);">', end: '</span>', oldBegin: '<span class="hl">'};

	/*

	hyperlink_data = {
		dyn: false,
		link:
			{type: 'ref', value: 'D1', cnt: '_new'} |
			{type: 'obj', value:
				{
					type: 'local',
					target:
						{
							path: '/Jedox/Financials/Accounting/Demo.wss',
							ghnt: {g: 'fgrp1', h: 'h1', n: 'n4', t: 'workbook'},
							sheet: 'Sheet2' | null (null = active sheet),
							range: 'D1' | 'D1:E2' | 'named_range' | null (null = A1)
						} | {
							path: '/Jedox/Financials/Accounting/Handbook.pdf',
							ghnt: {g: 'fgrp1', h: 'h1', n: 'n10', t: 'pdf'},
						}
				} | {
					type: 'url',
					target: 'http://www.google.com/'
				},
				cnt: '_blank'
			}

		text:
			{type: 'ref', value: 'D1'} |
			{type: 'string', value: 'Some Hyperlink caption'}

		tip:
			{type: 'ref', value: 'D4'} |
			{type: 'string', value: 'Some tip'} |
			{type: 'string', value: ''}

		trans: [
			{
				src:
					{type: 'range', value: 'A2' | 'A2:B3' | 'Sheet2!A2:B3'} |
					{type: 'nrange', value: 'named_range' | 'Sheet2!named_range'} |
					{type: 'var', value: '@var1'} |
					{type: 'cval', value: 'Some const'} |
					{type: 'clist', value: ['value1', 'value2', 'value3']}
				dst:
					{type: 'range', value: 'A2' | 'A2:B3' | 'Sheet2!A2:B3'} |
					{type: 'nrange', value: 'named_range' | 'Sheet2!named_range'} |
					{type: 'var', value: '@var1'}
			}, {
				src:
					{type: 'range', value: 'A2' | 'A2:B3' | 'Sheet2!A2:B3'} |
					{type: 'nrange', value: 'named_range' | 'Sheet2!named_range'} |
					{type: 'var', value: '@var1'} |
					{type: 'cval', value: 'Some const'} |
					{type: 'clist', value: ['value1', 'value2', 'value3']}
				dst:
					{type: 'range', value: 'A2' | 'A2:B3' | 'Sheet2!A2:B3'} |
					{type: 'nrange', value: 'named_range' | 'Sheet2!named_range'} |
					{type: 'var', value: '@var1'}
					--- URL target only ---
					{type: 'cval', value: 'Some const'} |
					{type: 'clist', value: ['value1', 'value2', 'value3']}
			}
		]
	}

	hyperlink_attribute = {
		dyn: true,
		link: ["D5", "[/FINANCE/Statements/Demo.wss]Sheet2!A2:B4"],
		text: ["D4", "Some hyperlink text"],
		tip: ["D3", "Some tip"],
		trans: [
			{src: ["A2:B4", [2, 3, 4, 5]], dst: "A2:B4"},
			{src: ["@var1", 50], dst: "A5"}
		]
	}

	hyperlink_attribute = {
		dyn: false,
		link: {type: 'obj', value: {
				type: 'local',
				target: {
					type: 'wb',
					path: '/Jedox/Financials/Accounting/Demo.wss',
					sheet: 'Sheet2',
					range: 'D1:E2'
				}
			},
			cnt: '_new'
		},
		text: {type: 'ref', value: 'D1'},
		tip: {type: 'string', value: 'Some tip'},
		trans: [
			{src: {type: 'var', value: '@var1'}, dst: {type: 'range', value: 'A2'}}
		]
	}

	*/

	/*#############
       Test data
  	#############*/

	var _dData = {
		dyn: true,
		link: ["abc.wss", "abc.wss hl"],
//		link: ["[abc.wss]A5", "abc.wss"],
//		link: ["SELF", "Place in this document"],
//		link: ["[SELF]A5", "Place in this document / A5"],
//		link: ["www.google.com", "www.google.com"],
//		link: ["/FINANCE/Statements/Demo.pdf", "/FINANCE/Statements/Demo.pdf"],
//		link: ["[/Jedox/Financials/Accounting/Pero/ComboTest2.wss]'Sheet test'!A2:B4", "[/Jedox/Financials/Accounting/Pero/ComboTest2.wss]'Sheet test'!A2:B4"],
//		link: ["/Jedox/Financials/Accounting/Pero/ComboTest2.wss", "/Jedox/Financials/Accounting/Pero/ComboTest2.wss"],
//		link: ["D5", "[/Jedox/Financials/Accounting/Pero/ComboTest2.wss]Sheet2!A2:B4"],
//		link: ["[/Jedox/Financials/Accounting/Pero/ComboTest2.wss]'Sheet test'!A2:B4#_new", "[/Jedox/Financials/Accounting/Pero/ComboTest2.wss]'Sheet test'!A2:B4#_new"],

		text: ["Some hyperlink text", "Some hyperlink text"],
	//	text: ["D4", "Some hyperlink text"],

	//	tip: ["Some tip", "Some tip"],
		tip: ["D3", "Some tip"],

		trans: [
			{src: ["A2:B4", [2, 3, 4, 5]], dst: "A2:B4"},
			{src: ["@var1", 50], dst: "A5"},
			{src: ["Sheet1!aaa", 50], dst: "Sheet1!A5"},
			{src: ["['value1', 'value2', 'value3']", "['value1', 'value2', 'value3']"], dst: 'Some const'}
		]
	},

	_sData = {
		dyn: false,

		link: {
			type:
//				'ref'
				'obj'

			, value:
//				'D5'
				{
					type:
						'local'
//						'url'

					, target:
					{
//						path: '/Jedox/Financials/Accounting/Demo.wss'
						path: '/Jedox/Financials/DeveLabs-praznici-odmori.pdf'
//						path: null
//						, ghnt: {g: 'fgrp1', h: 'h1', n: 'n4', t: 'workbook'}
						, ghnt: {g: 'fgrp1', h: 'h1', n: 'n36', t: 'pdf'}
//						, ghnt: null
						, sheet:
//							'Sheet2'
//							'Some sheet'
							null
						, range:
//							'D1'
//							'D1:E2'
//							'named_range'
							null
					}
//					'http://www.google.com/'
//					'mailto:john@johnson.com?subject=test&body=Testic'
				}
		},

		text: {
			type:
				'ref'
	//			'string'

			, value:
				'D1'
	//			'Some Hyperlink caption'
		},

		tip: {
			type:
	//			'ref'
				'string'

			, value:
	//			'D4'
				'Some tip'
	//			''
		},

		trans: [
			{
				src: {
					type:
						'range'
	//					'nrange'
//						'var'
	//					'cval'
//						'clist'

					, value:
						'B7'
	//					'A2:B3'
	//					'Sheet2!A2:B3'
	//
	//					'named_range'
	//					'Sheet2!named_range'
	//
//						'@var1'
	//
	//					'Some const'
	//
//						['value1', 'value2', 'value3']
				},
				dst: {
					type:
//						'range'
						'nrange'
//						'var'
//						'cval'
	//					'clist'

					, value:
//						'G3'
	//					'A2:B3'
	//					'Sheet2!A2:B3'
	//
						'testnr'
	//					'Sheet2!named_range'
	//
//						'@var1'
	//
//						'Some const'
	//
	//					['value1', 'value2', 'value3']
				}
			} , {
				src: {
					type:
						'range'
	//					'nrange'
	//					'var'
	//					'cval'
//						'clist'

					, value:
						'A2'
//						'A2:B3'
	//					'Sheet2!A2:B3'
	//
	//					'named_range'
	//					'Sheet2!named_range'
	//
	//					'@var1'
	//
	//					'Some const'
	//
//						['value1', 'value2', 'value3']
					},

				dst: {
					type:
						'range'
	//					'nrange'
	//					'var'
	//					'cval'
//						'clist'

					, value:
	//					'A2'
//						'B2:C3'
						'Sheet1!A2:B3'
	//
	//					'named_range'
	//					'Sheet2!named_range'
	//
	//					'@var1'
	//
	//					'Some const'
	//
//						['value1', 'value2', 'value3']
				}
			}
		]

	};

	function _sDataToFunc(data) {
		var loc, txt, tip, trans = '';

		//data = _sData;

		function convStrRef(val) {
			var isString = val.type == 'string';

			return (isString ? '"' : '').concat(val.value, isString ? '"' : '');
		}

		function convSrcDst(type, val) {
			var res = '', isDst = type == 'dst';

			switch (val.type) {
				case 'range':
				case 'nrange':
					var rngElems = val.value.split('!', 2);

					if (rngElems.length > 1)
						res = (rngElems[0].indexOf(' ') >= 0 ? '\''.concat(rngElems[0], '\'') : rngElems[0]).concat('!', rngElems[1]);
					else
						res = val.value;

					break;

				case 'var':
					res = (val.value.indexOf('@') ? '@' : '').concat(val.value);
					break;

				case 'cval':
					return '"'.concat(val.value, '"');

				case 'clist':
					return '"[\''.concat(val.value.join("','"), '\']"');
			}

			return (isDst ? '"' : '').concat(res, isDst ? '"' : '');
		}

		// Create link location.
		if (data.link.type == 'ref')
			loc = data.link.value;
		else {
			switch (data.link.value.type) {
				case 'local':
					switch (data.link.value.target.ghnt.t) {
						case 'workbook':
							var sheetExists = data.link.value.target.sheet != null, rangeExists = data.link.value.target.range != null;

							loc = '"'.concat(
									sheetExists || rangeExists ? '[' : ''
									, data.link.value.target.path
									, sheetExists || rangeExists ? ']' : ''
									, sheetExists ? (data.link.value.target.sheet.indexOf(' ') >= 0 ? '\''.concat(data.link.value.target.sheet, '\'') : data.link.value.target.sheet).concat('!') : ''
									, rangeExists ? data.link.value.target.range : ''
									, '"'
								);
							break;

						default:
							loc = '"'.concat(data.link.value.target.path, '"');
							break;
					}
					break;

				case 'url':
					loc = '"'.concat(data.link.value.target, '"');
					break;
			}
		}

		// Create link text.
		txt = convStrRef(data.text);

		// Create screen tip.
		tip = convStrRef(data.tip);

		// Create transfers.
		var sep = Jedox.wss.i18n.separators[2];

		for (var i = 0, trns = data.trans, trnsLen = trns.length; i < trnsLen; i++) {
			if (!trns[i].src || !trns[i].dst)
				continue;

			trans = trans.concat(sep, convSrcDst('src', trns[i].src), sep, convSrcDst('dst', trns[i].dst));
		}

		// Assemble HYPERLINK formula.
		return '=HYPERLINK('.concat(loc, sep, txt, sep, tip, trans, ')');
	}

	function _convertSDataLink(cb, link) {
		var cnt = _defCnt,
			hashIdx = link.lastIndexOf('#'),
			hasCb = cb instanceof Array && cb.length > 1;

		if (hashIdx >= 0) {
			cnt = link.substring(hashIdx + 1);
			link = link.substring(0, hashIdx);
		}

		var re_inSquareBracket = /^\[[\w\W]*\]/,
			wbType = link.match(re_inSquareBracket),
			path = wbType == null ? link : wbType[0].substring(1, wbType[0].length - 1),
			isSelf = !path.search(/^[^\/]+[\w\W]*.wss$/) || path.toUpperCase() == 'SELF',
			isLocal = wbType != null || !path.search(/^\/[\w]*/) || isSelf,

			cbConvert = function(res) {
				var locTarget = !isLocal ? path : {'path': path, 'ghnt': isSelf ? null : res};

				if (isLocal && !isSelf && locTarget.ghnt == null) {
					if (hasCb) {
						cb[1].call(cb[0], 'follHLInvalidWB');
						return;
					} else
						throw 'follHLInvalidWB';
				}

				if (!isLocal && !locTarget.length) {
					if (hasCb) {
						cb[1].call(cb[0], 'follHLInvalidURL');
						return;
					} else
						throw 'follHLInvalidURL';
				}

				var loc = {
						type: 'obj',
						value: {
							type: isLocal ? 'local' : 'url',
							target: locTarget
						},
						cnt: cnt
					};

				if (isLocal && (isSelf || loc.value.target.ghnt.t == 'workbook')) {
					var selStr = wbType == null ? '' : link.substr(wbType[0].length);

					if (selStr.length) {
						var selArr = selStr.split('!');

						if (selArr.length > 1) {
							loc.value.target.sheet = !selArr[0].search(/^'[^']*'$/) ? selArr[0].substring(1, selArr[0].length - 1) : selArr[0];
							loc.value.target.range = selArr[1];
						} else {
							loc.value.target.sheet = null;
							loc.value.target.range = selArr[0];
						}
					} else {
						loc.value.target.sheet = null;
						loc.value.target.range = null;
					}
				}

				if (hasCb)
					cb[1].call(cb[0], loc);
				else
					return loc;
			};

		if (isLocal && !isSelf) {
			if (hasCb) {
				var rqst = new Jedox.backend.RPCAsyncRqst('WSS', 'resolveNodePath', [path]);
				rqst.setOnSuccess([ that, cbConvert]).send();
			} else
				return cbConvert(Jedox.backend.wss.resolveNodePath(path));
		} else
			return cbConvert();
	}

	function _dDataToSData(cb, attr, incTrans) {
		var conn = Jedox.backend,
			activePane = Jedox.wss.app.activePane,
			hasCb = cb instanceof Array && cb.length > 1;

		//attr = _dData;

		function resolveRef(refStr) {
			if (!refStr.indexOf('@')) {
				var wbVar = conn.ccmd(0, ['gvar', refStr.substr(1)]);

				if (!wbVar[0][0] || !wbVar[0][1].length)
					throw 'badRef';

				return wbVar[0][1];
			} else {
				var ref = Jedox.wss.formula.parse(refStr);

				if (!ref.length)
					throw 'badRef';

				ref = ref[0];

				return activePane.getCellUVal(ref.rng[0], ref.rng[1]);
			}
		}

		function getPairVal(val) {
			try {
				return val[0] == val[1] ? val[0] : resolveRef(val[0]);
			} catch (e) {
				return val[0];
			}
		}

		function parseType(val) {
			if (val[0] == val[1])
				// cval
				return 'cval';
			else if (!val[0].search(/^\{[\w\W]*\}/))
				// clist
				return 'clist';
			else
				return !val[0].search(/^@/) ? 'var' : (formula.parse(val[0]).length ? 'range' : 'nrange');
		}

		// Get link text.
		var txt = attr.text[0] == attr.text[1] ? {type: 'string', value: getPairVal(attr.text)} : {type: 'ref', value: attr.text[0]};

		// Get screen tip.
		var tip = attr.tip[0] == attr.tip[1] ? {type: 'string', value: getPairVal(attr.tip)} : {type: 'ref', value: attr.tip[0]};

		// Get transfers.
		var trans = [];

		if (incTrans === true)
			for (var i = 0, trns = attr.trans, trnsLen = trns.length, inSqareBrack, trnsPair = {}, formula = Jedox.wss.formula, trgDstType; i < trnsLen; i++, trnsPair = {}) {
				if (!trns[i].src || !trns[i].dst || trns[i].src.length <= 1)
					continue;

				trgDstType = parseType(trns[i].dst);

				if (trgDstType != 'var' && !trns[i].src[0].length)
					continue;

				trnsPair.src = {type: parseType(trns[i].src), value: trns[i].src[0], rvalue: trns[i].src[1]};
				trnsPair.dst = {type: trgDstType, value: trns[i].dst[0], rvalue: trns[i].dst[1]};

				trans.push(trnsPair);
			}

		var cbConvert = function(res) {
			// Assemble hyperlink data object.
			var sData = {'dyn': false, 'link': res ? res : {type: 'ref', value: attr.link[0], cnt: _defCnt}, 'text': txt, 'tip': tip, 'trans': trans};

			if (hasCb)
				cb[1].call(cb[0], sData);
			else
				return sData;
		}

		if (attr.link[0] == attr.link[1]) {
			if (hasCb)
				_convertSDataLink([that, cbConvert], getPairVal(attr.link));
			else
				return cbConvert(_convertSDataLink(null, getPairVal(attr.link)));
		} else
			return cbConvert();
	}

	function _resolveFormula(frm) {
		var activeBook = Jedox.wss.app.activeBook,
			conn = activeBook._conn,
			actSheet = activeBook.getSheetSelector().getActiveSheetName(),
			tmpName = 'tmp_'.concat(Math.ceil(Math.random() * 10000000000)),

		res = conn.ccmd(0, ["nadd", [1, 1, {
			name: tmpName,
			refers_to: (!frm.search(/^=/) ? '' : '=').concat(frm),
			scope: actSheet,
			comment: 'Temporary Named Range'
		}]]);

		if (res[0][0])
			conn.ccmd(0, ['ndel', res[0][1][0].uuid]);

		return res[0][0] ? [res[0][0], res[0][1][0].uuid, res[0][1][0].value] : res[0];
	}

	function _resolveSData(cb, data, incTrans) {
		var resTarget = [], resData = [],
			hasCb = cb instanceof Array && cb.length > 1;

		// Resolve link.
		if (data.link.type == 'ref')
			resTarget.push([data.link, "rvalue"]), resData.push(data.link.value);

		// Resolve text.
		if (data.text.type == 'ref')
			resTarget.push([data.text, "rvalue"]), resData.push(data.text.value);

		// Resolve tip.
		if (data.tip.type == 'ref')
			resTarget.push([data.tip, "rvalue"]), resData.push(data.tip.value);

		// Resolve transfers.
		if (incTrans === true)
			for (var i = 0, trns = data.trans, trnsLen = trns.length, resTypes = 'range,nrange,var', parseDst = data.link.type == 'obj' && data.link.value.type == 'url',
					resT = resTarget, resD = resData; i < trnsLen; i++) {

				if (!trns[i].src || !trns[i].dst)
					continue;

				if (resTypes.search(trns[i].src.type) >= 0)
					resT.push([trns[i].src, "rvalue"]), resD.push(trns[i].src.value);
				else if (trns[i].src.type == 'clist')
					trns[i].src.rvalue = [trns[i].src.value.split(',')];

				if (parseDst) {
					if (resTypes.search(trns[i].dst.type) >= 0)
						resT.push([trns[i].dst, "rvalue"]), resD.push(trns[i].dst.value);
					else if (trns[i].dst.type == 'clist')
						trns[i].dst.rvalue = [trns[i].dst.value.split(',')];
				}
			}

		if (resData.length) {
			var rslVal = _resolveFormula('=RESOLVE('.concat(resData.join(Jedox.wss.i18n.separators[2]), ')'));

			if (!rslVal[0])
				throw 'resolveError';

			// Set values
			for (var j = 0, rT = resTarget, rVals = Ext.util.JSON.decode(rslVal[2]), rTLen = rT.length; j < rTLen; j++)
				rT[j][0][rT[j][1]] = rVals[j];
		}

		var cbConvert = function(res) {
			// Convert link.
			if (data.link.type == 'ref')
				data.link.rvalue = res['value'];

			var convRes = rslVal ? rslVal[1] : null;

			if (hasCb)
				cb[1].call(cb[0], convRes);
			else
				return convRes;
		};

		// Convert link.
		if (data.link.type == 'ref') {
			if (hasCb)
				_convertSDataLink([that, cbConvert], data.link.rvalue);
			else
				return cbConvert(_convertSDataLink(null, data.link.rvalue));
		} else
			return cbConvert();
	}

	function _isEmptyObj(obj) {
		for (var fld in obj)
			return false;

		return true;
	}

	this.set = function(hdata) {
		var	activeBook = Jedox.wss.app.activeBook,
			general = Jedox.wss.general,
			env = Jedox.wss.app.environment,
			conn = activeBook._conn,
			range = env.defaultSelection.getActiveRange().getCoords(),
			cell = activeBook._aPane.getCell(range[0], range[1]),
			txt = 'Hyperlink', rslVal = [false];

		if (hdata.text.type == 'string')
			txt = hdata.text.value;
		else {
			rslVal = _resolveFormula(hdata.text.value);

			if (rslVal[0])
				txt = rslVal[2];
		}

		hdata = ['hl', hdata];
		var rngUpd = {a: {mousedown: hdata}};

		if (cell == undefined || (!cell.t && (cell.m || cell.s)) || 's,h,e'.search(cell.t) >= 0)
			rngUpd.v = this.hlTag.begin.concat(txt, this.hlTag.end);

		rngUpd.s = Jedox.wss.style.hyperlinkStyle;
		range.push(rngUpd);

		conn.ccmdBuffer();

		conn.ccmd(null, ['cdrn', {cm: true}, range]);
		conn.ccmdFlush(true, true, conn.Q_VALUE | conn.Q_STYLE | conn.Q_FORMULA_WE | conn.Q_ATTRS | conn.Q_FMT_VAL, conn.D_NONE);

		Jedox.wss.app.environment.selectedCellValue = this.hlTag.begin.concat(txt, this.hlTag.end);
	};

	this.get = function(range) {
		if (!range)
			return undefined;

		var cell = Jedox.wss.app.activePane.getCell(range[0], range[1]);

		if (typeof cell == 'object' && ('a' in cell) && ('mousedown' in cell.a) && cell.a.mousedown[0] == 'hl')
			return cell.a.mousedown[1];

		return undefined;
	};

	this.remove = function() {
		var	env = Jedox.wss.app.environment,
			range = [env.lastRangeStartCoord[0], env.lastRangeStartCoord[1], env.lastRangeEndCoord[0], env.lastRangeEndCoord[1]],
			activePane = Jedox.wss.app.activePane,
			general = Jedox.wss.general,
			conn = activePane._conn,
			cell = activePane.getCell(range[0], range[1]);

		if (!cell)
			return;

		var txt = Jedox.wss.general.filterHLTags(range[0], range[1], activePane.getCellValue(range[0], range[1]), false),
			rngUpd = {s: Jedox.wss.style.delHyperlinkStyle};

		if (cell.t == 'h')
			rngUpd.v = txt;

		range.push(rngUpd);

		conn.ccmdBuffer();

		conn.ccmd(null, ['clat', [range[0], range[1], range[0], range[1]]]);
		conn.ccmd(null, ['cdrn', {cm: true}, range]);

		conn.ccmdFlush(true, true, conn.Q_VALUE | conn.Q_STYLE | conn.Q_FORMULA_WE | conn.Q_ATTRS | conn.Q_FMT_VAL, conn.D_NONE);
	};

	this.updateText = function(range, txt) {
		if (Jedox.wss.app.activePane.getCellType(range[0], range[1]) == 'h') {
			var hdata = this.get(range);

			if (hdata == undefined)
				return;

			hdata.text.type = 'string';
			hdata.text.value = txt;

			range.push({a: {mousedown: ['hl', hdata]}});
			Jedox.backend.ccmd(0, [ 'cdrn', { cm: true }, range ]);
		}
	}

	this.followURL = function(data, cnt) {
		// Follow mailto URL.
		if (!data.link.value.target.search(/^mailto:*/i)) {
			window.location = data.link.value.target;
			return false;
		}

		// Append transfers.
		function getSDVals(val) {
			var resTypes = 'range,nrange,var',
				res = val.type == 'clist' ? val.rvalue[0] : val[resTypes.search(val.type) >= 0 ? 'rvalue' : 'value'];

			return Ext.isArray(res) ? res : [res];
		}

		// Check transfer value.
		function chkTrnsVal(val) {
			return !val.length || (val.length == 1 && val[0] instanceof Object && _isEmptyObj(val[0]));
		}

		var transData = {},
			trg = data.link.value.target;

		if (!cnt)
			cnt = data.link.cnt == undefined ? _defCnt : data.link.cnt;

		for (var i = 0, trns = data.trans, trnsLen = trns.length, src, dst; i < trnsLen; i++) {
			if (!trns[i].src || !trns[i].dst || chkTrnsVal(src = getSDVals(trns[i].src)) || chkTrnsVal(dst = getSDVals(trns[i].dst)))
				continue;

			for (var j = 0, k = 0, tData = transData, srcLen = src.length; j < srcLen; j++, k++)
				tData[src[j]] = !dst[k] ? dst[k = 0] : dst[k];
		}

		var url = Ext.urlAppend((trg.search(/:\/\//) < 0 ? 'http://' : '').concat(trg.replace(/\/$/, '')), Ext.urlEncode(transData));

		// Follow other URLs.
		if (Jedox.wss.app.standalone)
			window.open(url, 'winURL', 'directories=yes,menubar=yes,toolbar=yes,location=yes,status=yes,resizable=yes,scrollbars=yes');
		else {
			try {
				for (var triggers = Jedox.wss.events.triggers.openURL, i = triggers.length - 1, hlURL = url; i >= 0; i--)
					triggers[i][0]['openURL'].call(parent, triggers[i][1], hlURL, cnt, data.text[data.text.type == 'string' ? 'value' : 'rvalue'], true);
			} catch (e) {
				Jedox.wss.general.showMsg('Application Error'.localize(), e.localize()/*e.message.localize()*/, Ext.MessageBox.WARNING);
			}
		}

		return false;
	};

	this.followOther = function(link, cnt) {
		// Follow other URLs.
		if (Jedox.wss.app.standalone)
			Jedox.wss.general.showMsg('follHLInvalidRef'.localize(), 'follHLNotSuppInStandalone'.localize(), Ext.MessageBox.WARNING);
		else {
			try {
				for (var triggers = Jedox.wss.events.triggers.openOther, i = triggers.length - 1, ghnt = link.target.ghnt; i >= 0; i--)
					triggers[i][0]['openOther'].call(parent, triggers[i][1], ghnt, cnt ? cnt : _defCnt, true);
			} catch (e) {
				Jedox.wss.general.showMsg('Application Error'.localize(), e.localize()/*e.message.localize()*/, Ext.MessageBox.WARNING);
			}
		}

		return false;
	};

	this.followWb = function(data) {
		var activeBook = Jedox.wss.app.activeBook,
			showMsg = Jedox.wss.general.showMsg,
			linkVal = data.link.type == 'ref' ? data.link.rvalue : data.link.value,
			rng = [], ext = {cbkey: 'hl', appmode: Jedox.wss.app.appMode},
			srcWsId = Jedox.wss.app.activeSheet.getUid(),
			hasAfterTrans = false;

		if (linkVal.target.sheet != null) {
			if (Jedox.wss.app.UPRestrictMode && linkVal.target.sheet != activeBook._sheetSelector.getActiveSheetName()) {
				showMsg('follHLTmpDisabledRef'.localize(), 'follHLTmpDisabledWS'.localize(), Ext.MessageBox.WARNING);
				return false;
			}

			ext['sheet_name'] = linkVal.target.sheet;
		}

		if (linkVal.target.range == null || !linkVal.target.range.length)
			rng = [1, 1, 1, 1];
		else {
			var rngParsed = Jedox.wss.formula.parse(linkVal.target.range);

			if (!rngParsed.length)
				ext['nrange'] = linkVal.target.range;
			else {
				if (rngParsed.length > 1) {
					showMsg('follHLInvalidRef'.localize(), 'follHLInvalidRng'.localize(), Ext.MessageBox.WARNING);
					return false;
				}

				rng = rngParsed[0].rng;
			}
		}

		var transExec = function(params, cb) {
			var conn = Jedox.backend,
				isFullTrans = params != undefined && params.fullTrans != undefined && params.fullTrans,
				isBeforeLoad = !isFullTrans && params != undefined && params.beforeLoad != undefined && params.beforeLoad;

			// Set resolved named range.
			if (!params[linkVal.target.range]) {
				if (!rng.length)
					rng = [1, 1, 1, 1];
			} else {
				var paramsNR = !params[linkVal.target.range].search(/^=/) ? params[linkVal.target.range].substr(1) : params[linkVal.target.range],
						rngP = Jedox.wss.formula.parse(paramsNR);

				rng = rngP.length ? rngP[0].rng : [1, 1, 1, 1];
			}

			// Transfer values.
			if (!data.trans.length || (!isFullTrans && !isBeforeLoad && !hasAfterTrans)) {
				if (cb instanceof Array && cb.length > 1)
					cb[1].call(cb[0]);

				return;
			}

			if (isFullTrans || !isBeforeLoad) {
				Jedox.wss.app.activeBookTmp = Jedox.wss.app.activeBook;
				delete Jedox.wss.app.activeBook;
			}

			/*
			sheetPool = {
					'453769b8-944d-11dd-b9f9-2d8ea2c036d0': {
						rngs: [[5, 5, 6, 6, {v: "value1"}, {v: "value2"}, {v: "value3"}, {v: "valu4"}], [5, 5, 6, 6, {v: "value1"}, {v: "value2"}, {v: "value3"}, {v: "valu4"}]],
						vars: [['var1', 'value1'], ['var2', 'value2']]
					},

					'453769b8-944d-11dd-b9f9-2d8ea2c036d0': {
						rngs: [[5, 5, 6, 6, {v: "value1"}, {v: "value2"}, {v: "value3"}, {v: "valu4"}], [5, 5, 6, 6, {v: "value1"}, {v: "value2"}, {v: "value3"}, {v: "valu4"}]]
					}
				};

			nrPool = [
					{
						name: 'some_named_range',
						uuid: '453769b8-944d-11dd-b9f9-2d8ea2c036d0',
						src: ...
					},

					{
						name: 'some_named_range',
						uuid: '',
						src: ...
					}
				];
			 */

			var sheetPool = {}, namedRangePool = [], sheets = {},
			sheetList = Jedox.backend.wss.getSheets(null, true),
			actSheetId = sheetList[1], actSheetName;

			for (var i = 0, sheetListLen = sheetList[0].length; i < sheetListLen; i += 2) {
				sheets[sheetList[0][i + 1]] = sheetList[0][i];

				if (sheetList[0][i] == sheetList[1])
					actSheetName = sheetList[0][i + 1];
			}

			var resolveRange = function(range) {
				var refs = Jedox.wss.formula.parse(range);

				return refs.length == 1 ? refs : false;
			},

			genSrcData = function(src, len, plVal) {
				var srcVal = src.type == 'cval' || src.type == 'clist' ? src.value : src.rvalue;

				srcVal = srcVal == null ? '' : srcVal;
				srcVal = Ext.isArray(srcVal) ? srcVal : [srcVal];

				var srcObjs = [], res = [];
				for (var i = 0, sArr = srcVal, srcLen = sArr.length, j, subSrcLen; i < srcLen; i++) {
					if (sArr[i] instanceof Array)
						for (j = 0, subSrcLen = sArr[i].length; j < subSrcLen; j++)
							srcObjs.push(plVal ? Jedox.wss.general.str2var(sArr[i][j]).v : { v: Jedox.wss.general.str2var(sArr[i][j]).v });
					else
						srcObjs.push(plVal ? Jedox.wss.general.str2var(sArr[i]).v : { v: Jedox.wss.general.str2var(sArr[i]).v });
				}

				while (res.length < len)
					res = res.concat(srcObjs);

				return res.slice(0, len);
			},

			splitRange = function(fullRng) {
				var rngElems = fullRng.split('!', 2);

				return rngElems.length > 1 ? {sheet: !rngElems[0].search(/^'[^']*'$/) ? rngElems[0].substring(1, rngElems[0].length - 1) : rngElems[0], range: rngElems[1]} : {sheet: actSheetName, range: rngElems[0]};
			},

			appendRange = function(dstRng, src) {
				dstRng = !dstRng.search(/^=/) ? dstRng.substr(1) : dstRng;
				var rngElems = splitRange(dstRng);

				if (!sheets[rngElems.sheet])
					return;

				var parsedDstRng = resolveRange(rngElems.range);

				if (!parsedDstRng)
					return;

				var dataArr = parsedDstRng[0].rng;
				dataArr = dataArr.concat(genSrcData(src, (dataArr[2] - dataArr[0] + 1) * (dataArr[3] - dataArr[1] + 1), false));

				if (sheetPool[sheets[rngElems.sheet]])
					sheetPool[sheets[rngElems.sheet]].rngs.push(dataArr);
				else
					sheetPool[sheets[rngElems.sheet]] = {rngs: [dataArr], vars: []};
			};

			for (var i = 0, trns = data.trans, trnsLen = trns.length, shts = sheets, splitRng = splitRange, sPool = sheetPool, nPool = namedRangePool,
					genSData = genSrcData, actSId = actSheetId, parsedDstRng, dataArr, rngElems; i < trnsLen; i++) {

				if (!trns[i].src || !trns[i].dst || (!isFullTrans && !isBeforeLoad && trns[i].dst.type == 'var'))
					continue;

				if (!isFullTrans && isBeforeLoad && trns[i].dst.type != 'var') {
					hasAfterTrans = true;
					continue;
				}

				switch (trns[i].dst.type) {

					case 'cval':
						if (srcWsId != Jedox.wss.app.activeSheet.getUid())
							break;
					case 'range':
						appendRange(trns[i].dst.value, trns[i].src);
						break;

					case 'nrange':
						rngElems = splitRng(trns[i].dst.value);
						nPool.push({name: rngElems.range, uuid: shts[rngElems.sheet], src: trns[i].src});

						break;

					case 'var':
						dataArr = [!trns[i].dst.value.search(/^@/) ? trns[i].dst.value.substr(1) : trns[i].dst.value, genSData(trns[i].src, 1, true)[0]];

						if (sPool[actSId])
							sPool[actSId].vars.push(dataArr);
						else
							sPool[actSId] = {rngs: [], vars: [dataArr]};

						break;
				}
			}

			// Resolve Named Ranges.
			if (namedRangePool.length) {
				conn.ccmdBuffer();

				for (var i = 0, nrPool = namedRangePool, nrPoolLen = nrPool.length; i < nrPoolLen; i++) {
					conn.ccmd(0, ['nget', [1, 1, nrPool[i].name, nrPool[i].uuid == undefined ? '' : nrPool[i].uuid, true]]);
					conn.ccmd(0, ['nget', [1, 1, nrPool[i].name, '', true]]);
				}

				for (var i = 0, nrRes = conn.ccmdFlush(), nrResLen = nrRes.length, nrPool = namedRangePool, refTo, refToElems; i < nrResLen; i += 2) {
					if (!nrRes[i][0] && !nrRes[i + 1][0])
						continue;

					try {
						refTo = nrRes[nrRes[i][0] ? i : i + 1][1][0].refers_to;
						appendRange(refTo, nrPool[i / 2].src);
					} catch (e) {}
				}
			}

			// Set values
			if (!_isEmptyObj(sheetPool)) {
				conn.ccmdBuffer();

				if (params.wbid)
					conn.ccmd(0, ['osel', 1, params.wbid]);

				if (sheetPool[actSheetId]) {
					for (var rngs = sheetPool[actSheetId].rngs, i = rngs.length - 1; i >= 0; i--)
						conn.ccmd(0, ['cdrn', {cm: true}, rngs[i]]);

					for (var vars = sheetPool[actSheetId].vars, i = vars.length - 1; i >= 0; i--)
						conn.ccmd(0, ['svar'].concat(vars[i]));

					delete(sheetPool[actSheetId]);
				}

				var sheetChanged = false;
				for (var oSheet in sheetPool) {
					conn.ccmd(0, ['osel', 2, oSheet]);
					sheetChanged = true;

					for (var rngs = sheetPool[oSheet].rngs, i = rngs.length - 1; i >= 0; i--)
						conn.ccmd(0, ['cdrn', {cm: true}, rngs[i]]);
				}

				if (sheetChanged)
					conn.ccmd(0, ['osel', 2, actSheetId]);

				if (isFullTrans || !isBeforeLoad)
					Jedox.wss.app.activeBook = Jedox.wss.app.activeBookTmp;

				conn.ccmdFlush(cb, true);
			}

			if (isFullTrans || !isBeforeLoad) {
				if (!Jedox.wss.app.activeBook)
					Jedox.wss.app.activeBook = Jedox.wss.app.activeBookTmp;

				delete Jedox.wss.app.activeBookTmp;
			}
		};

		// Make selection.
		function makeSelection(cb, err) {
			if (err) {
				showMsg('follHLInvalidRef'.localize(), err.localize(), Ext.MessageBox.WARNING);
				return false;
			}

			var env = Jedox.wss.app.environment,
				callFnCb = function() {
					if (cb instanceof Array && cb.length > 1)
						cb[1].call(cb[0]);
				};

			if (env.viewMode == Jedox.wss.grid.viewMode.DESIGNER) {
				var defSel = env.defaultSelection,
					cbScroll = function() {
						defSel.set(new Jedox.gen.Point(rng[0], rng[1]), new Jedox.gen.Point(rng[2], rng[3]));
						defSel.draw();

						callFnCb();
					};

				// Scroll grid if necessary.
				var activePane = Jedox.wss.app.activePane;

				if (!activePane.isCellVisible(rng[0], rng[1]))
					activePane.scrollTo([this, cbScroll], rng[0], rng[1], true, false);
				else
					cbScroll();

				return;
			} else if (!activeBook._aPane.isCellVisible(rng[0], rng[1]))
				activeBook._aPane.scrollTo([this, callFnCb], rng[0], rng[1], true, false);
			else
				callFnCb();
		}

		// Load workbook.
		try {
			var ghnt = linkVal.target.ghnt,
				cnt = data.link.cnt == undefined ? _defCnt : data.link.cnt;

			if (ghnt == null) {
				var sheetSelector = activeBook.getSheetSelector(),
					path = linkVal.target.path, sheetId;

				if (!path.search(/^[\w\W]*.wss$/) && path != Jedox.wss.app.activeBook._name)
					throw 'follHLInvalidWB';

				var cbTransExec = function() {
					if (ext.nrange) {
						var conn = Jedox.backend,
							targSheetId = ext.sheet_name ? sheetSelector.getIdByName(ext.sheet_name) : sheetSelector.getActiveSheetId();

						if (!targSheetId)
							throw 'follHLInvalidSheet';

						conn.ccmdBuffer();

						conn.ccmd(0, ['nget', [1, 1, ext.nrange, targSheetId, true]]);
						conn.ccmd(0, ['nget', [1, 1, ext.nrange, '', true]]);

						var ngetRes = conn.ccmdFlush(),
							sheetNREmpty;

						if ((sheetNREmpty = _isEmptyObj(ngetRes[0][1][0])) && _isEmptyObj(ngetRes[1][1][0]))
							throw 'follHLInvTrgNRange';

						var nrRef = ngetRes[sheetNREmpty ? 1 : 0][1][0].refers_to;

						if (!nrRef.search(/^=/))
							nrRef = nrRef.substr(1);

						var nrRefSplit = (!nrRef.search(/^=/) ? nrRef.substr(1) : nrRef).split('!', 2);
						if (nrRefSplit.length > 1) {
							sheetId = sheetSelector.getIdByName(nrRefSplit[0]);
							nrRefRng = nrRefSplit[1];
						} else
							nrRefRng = nrRefSplit[0];

						rngParsed = Jedox.wss.formula.parse(nrRefRng);

						if (!rngParsed.length)
							throw 'follHLInvTrgNRange';
						else {
							if (rngParsed.length > 1)
								throw 'follHLInvTrgNRange';

							rng = rngParsed[0].rng;
						}

						if (nrRefSplit.length > 1 && sheetSelector.getActiveSheetId() != sheetId) {
							if (!sheetId)
								throw 'follHLInvalidSheet';

							Jedox.wss.sheet.select([this, makeSelection], sheetId, activeBook, true);
						} else
							makeSelection();
					} else if (ext.sheet_name) {
						sheetId = sheetSelector.getIdByName(ext.sheet_name);

						if (!sheetId)
							throw 'follHLInvalidSheet';

						if (sheetSelector.getActiveSheetId() != sheetId)
							Jedox.wss.sheet.select([this, makeSelection], sheetId, activeBook, true);
						else
							makeSelection();
					} else
						makeSelection();
				}

				transExec({fullTrans: true}, [this, cbTransExec]);
			} else {
				if (Jedox.wss.app.UPRestrictMode) {
					var actBookMetaData = activeBook._meta;

					if (actBookMetaData == null || actBookMetaData.n != ghnt.n || actBookMetaData.h != ghnt.h || actBookMetaData.g != ghnt.g) {
						showMsg('follHLTmpDisabledRef'.localize(), 'follHLTmpDisabledWB'.localize(), Ext.MessageBox.WARNING);
						return false;
					}
				}

				var cntObj = this.resolveTarget(cnt);

				if (!cntObj) {
					for (var triggers = Jedox.wss.events.triggers.openWorkbook_before, i = triggers.length - 1; i >= 0; i--)
						triggers[i][0]['openWorkbook_before'].call(parent, triggers[i][1], ghnt, '', true);

					function afterWbOpen(err) {
						if (err) {
							showMsg('follHLInvalidRef'.localize(), err.localize(), Ext.MessageBox.WARNING);
							return false;
						}

						var name = Jedox.wss.wnd.active.node._name;
						for (var triggers = Jedox.wss.events.triggers.openWorkbook_after, i = triggers.length - 1; i >= 0; i--)
							triggers[i][0]['openWorkbook_after'].call(parent, triggers[i][1], ghnt, name);
					}
				}

				switch (ghnt.t) {
					case 'workbook':
						transExec({beforeLoad: true});
						var hlres = Jedox.wss.node.load([this, makeSelection, cntObj ? undefined : [this, afterWbOpen]], ghnt.t, ghnt.n, ghnt.g, ghnt.h, ext, {tag: 'hl', func: transExec, scope: this, params: [], cnt: cntObj});
						break;

					case 'frameset':
						var hlres = Jedox.wss.node.load(cntObj ? undefined : [this, afterWbOpen], ghnt.t, ghnt.n, ghnt.g, ghnt.h, ext, {tag: 'hl', params: [], cnt: cntObj});
						break;
				}

				if (!hlres)
					return false;
			}
		} catch (e) {
			showMsg('follHLInvalidRef'.localize(), e.localize(), Ext.MessageBox.WARNING);
			return false;
		}
	};

	this.follow = function(ev, data) {
		if (!data)
			return false;

		if (ev) {
			if (ev.button == 2 || (Ext.isMac && ev.button == 0 && Jedox.wss.app.ctrlKeyPressed))
				return true;

			var targEl = (Ext.isGecko2) ? ev.explicitOriginalTarget.parentNode : document.elementFromPoint(ev.clientX, ev.clientY);
			if (targEl == undefined || targEl.tagName.toUpperCase() != 'SPAN' || targEl.className != 'hl')
				return true;
		}

		try {
			if (data.dyn)
				data = _dDataToSData(null, data, true);
			else
				var tmpNRId = _resolveSData(null, data, true);
		} catch (e) {
			Jedox.wss.general.showMsg('follHLInvalidRef'.localize(), e.localize(), Ext.MessageBox.WARNING);
			return false;
		}

		var linkVal = data.link.type == 'ref' ? data.link.rvalue : data.link.value;

		// URL
		if (linkVal.type == 'url')
			return Jedox.wss.hl.followURL(data);

		// Workbook & Other
		if (linkVal.type == 'local')
			return linkVal.target.ghnt == null || linkVal.target.ghnt.t == 'workbook' || linkVal.target.ghnt.t == 'frameset' ? Jedox.wss.hl.followWb(data) : Jedox.wss.hl.followOther(linkVal, data.link.cnt == undefined ? _defCnt : data.link.cnt);

		return false;
	};

	this.exec = function(rngStr) {
		var rng = Jedox.wss.formula.parse(rngStr);

		if (!rng.length) {
			Jedox.wss.general.showMsg('follHLInvalidRef'.localize(), 'execHLInvRange'.localize(), Ext.MessageBox.WARNING);
			return false;
		}

		this.follow(null, this.get(rng[0].rng.slice(0, 2)));
	};

	this.execDyn = function(link, text) {
		if (text == undefined)
			text = 'Title'.localize();

		var dData = {
			dyn: true,
			link: [link, link],
			text: [text, text],
			tip: [text, text],
			trans: []
		};

		this.follow(null, dData);
	};

	this.getContextMenu = function(conf) {
//		conf: {
//			defName: - default name (used in InsertHyperlink dialog)
//			withOpen: - true/false to show Open option in context menu
//			data: - Hyperblock Data
//			handlers: { - Keep all handlers
//				scope: - scope of handler functions
//				set: - handler for setting hyperblock
//				remove: - handler for removing hyperblock
//			}
//		}

		var data = conf.data,
			dynData = data != undefined && data.dyn,
			insEditCapt = data ? 'Edit Hyperlink' : 'Hyperlink',
			cntx = ['-'];

		if (conf && conf.data && conf.withOpen) {
			if (dynData)
				data = _dDataToSData(null, data);
			else
				var tmpNRId = _resolveSData(null, data, true);

			var linkVal = data.link.type == 'ref' ? data.link.rvalue : data.link.value;

			// URL
			if (linkVal.type == 'url') {
				if (!Jedox.wss.app.standalone)
					cntx.push({text: 'HLCntxNewTab'.localize(), iconCls: 'ico_hl_target_tab', handler: function(){Jedox.wss.hl.followURL(data, '_new');}});

				cntx.push({text: 'HLCntxNewWin'.localize(), iconCls: 'ico_hl_target_win', handler: function(){Jedox.wss.hl.followURL(data, '_blank');}});
			}

			if (linkVal.type == 'local') {
				// Workbook
				if (linkVal.target.ghnt == null || linkVal.target.ghnt.t == 'workbook')
					cntx.push({text: 'Open'.localize(), iconCls: 'ico_hl_open', handler: function(){Jedox.wss.hl.followWb(data);}});
				else if (!Jedox.wss.app.standalone) {
					// Other
					if (Jedox.wss.app.fileTypesReg[linkVal.target.ghnt.t] || linkVal.target.ghnt.t == 'hyperlink') {
						cntx.push({text: 'HLCntxNewTab'.localize(), iconCls: 'ico_hl_target_tab', handler: function(){Jedox.wss.hl.followOther(linkVal, '_new');}});
						cntx.push({text: 'HLCntxNewWin'.localize(), iconCls: 'ico_hl_target_win', handler: function(){Jedox.wss.hl.followOther(linkVal, '_blank');}});
					}

					if ('hyperlink,ahview'.search(linkVal.target.ghnt.t) < 0)
						cntx.push({text: 'Export'.localize().concat('...'), handler: function(){Jedox.wss.hl.followOther(linkVal, '_export');}});
				}
			}
		}

		if (Jedox.wss.app.environment.viewMode != Jedox.wss.grid.viewMode.USER) {
			if (!dynData) // TODO: When ready, open Function Arguments dialog for dynData.
				cntx.push({id: 'wHyperlink_insert_btn', text: insEditCapt.localize().concat('...'), iconCls: 'ico_hl_insert', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.openHL, [conf]);}});

			if (data)
				cntx.push( {id: 'wHyperlink_del_btn', text: 'HLCntxRemove'.localize(), iconCls: 'ico_hl_remove', handler: function() { conf.handlers.remove.call(conf.handlers.scope); } } );
		}

		return cntx;
	};

	this.toolTip = function(ev, show)
	{
		if(document.all)
			ev = window.event;

		if (show)
		{
			var elParent = document.all ? ev.srcElement.parentNode : ev.target.parentNode,
				activeBook = Jedox.wss.app.activeBook, rng;

			if (elParent.id.search(/_cursorField$/) >= 0)
				rng = Jedox.wss.app.environment.selectedCellCoords;
			else if (activeBook._aPane)
				rng = activeBook._aPane.getCoordsByCell(elParent);
			else
				return;

			var data = this.get(rng);
		}

		this.setToolTip(ev, data, show);
	};

	this.setToolTip = function(ev, data, show) {
		var el = document.all ? ev.srcElement : ev.target;

		if (show && data) {
			var tipTitle, tipText,
				isDyn = data.dyn,
				showToolTip = function() {
					if (el.tooltip)
						return;

					el.tooltip = new Ext.ToolTip({
						target: el,
						renderTo: Jedox.wss.app.activePane._domId.concat('_IC'),
						title: tipTitle,
						html: tipText,
						trackMouse: true,
						anchorToTarget: false,
						autoDestroy: true,
						dismissDelay: 10000
					});

					el.tooltip.anchorEl.hide();

					if (el.noTooltip) {
						delete el.noTooltip;
						return;
					}

					el.tooltip.showAt([ev.clientX + 15, ev.clientY + 18]);
				};

			var cbConvert = function(res) {
				try {
					if (isDyn)
						data = res;
					else
						var tmpNRId = res;

					if (!(data.link instanceof Object))
						throw data.link;

					tipTitle = data.tip[data.tip.type == 'ref' ? 'rvalue' : 'value'];

					if (!tipTitle)
						tipTitle = data.text[data.text.type == 'ref' ? 'rvalue' : 'value'];

					var linkSrc = data.link.type == 'ref' ? 'rvalue' : 'value';

					if (data.link[linkSrc].type == 'local')
						tipText = !data.link[linkSrc].target.path ?
								'Place in This Document'.localize().concat(' - ', !data.link[linkSrc].target.sheet ? Jedox.wss.app.activeBook.getSheetSelector().getActiveSheetName() : data.link[linkSrc].target.sheet) :
								data.link[linkSrc].target.path;
					else
						tipText = data.link[linkSrc].target;

					showToolTip();
				} catch (e) {
					tipTitle = tipTitle ? tipTitle : 'follHLInvalidRef'.localize();
					tipText = 'HLInvalidRefNotice'.localize();
					showToolTip();
				}
			};

			if (isDyn)
				_dDataToSData([that, cbConvert], data);
			else
				_resolveSData([that, cbConvert], data);
		} else if (el.tooltip && el.tooltip.isVisible()) {
			el.tooltip.destroy();
			delete el.tooltip;
			delete el.noTooltip;
		} else
			el.noTooltip = true;
	};

	this.resolveTarget = function (target)
	{
		var activeBook = Jedox.wss.app.activeBook,
				holder = activeBook.holder;

		switch (target)
		{
			case '_self':
				return holder;

			case '_top':
				return activeBook.getTopHolder();

			case '_parent':
				return holder.holder ? holder.holder : holder;

			case '_blank':
			case '_new':
				return undefined;
		}

		return undefined;
	};

	this.getTargets = function (destType)
	{
		switch (destType)
		{
			case 'workbook':
				return [ '_new', '_self', '_parent', '_top' ];

			default:
				return [ '_new', '_blank' ];
		}
	};

	this.getRules = function(conf) {
		/*
		 conf = {
		 	lType: 'ref' | 'obj',
		 	lVType: 'local' | 'url',
		 	lVSubType: (lVType == 'local') ? 'self' | 'workbook' | 'frameset' | 'folder' | 'hyperlink' | 'static' | 'urlplugin' : 'web' | 'mail'
		 };
		 */

		if (!conf || !conf.lType || (conf.lType == 'obj' && (!conf.lVType || !conf.lVSubType)))
			return conf;

		conf.hasTarg = true;
		conf.targets = [];
		conf.hasTrans = true;
		conf.hasSel = true;

		var destType = undefined;

		// lType
		switch (conf.lType) {
			case 'ref':
				conf.hasTarg = false;
				break;

			case 'obj':
				// lVType
				switch (conf.lVType) {
					case 'local':
						// lVSubType
						switch (conf.lVSubType) {
							case 'self':
								conf.hasTarg = false;
								break;

							case 'workbook':
								destType = conf.lVSubType;
								break;

							case 'folder':
								conf.hasTarg = conf.hasTrans = conf.hasSel = false;

							case 'frameset':
							case 'hyperlink':
							case 'static':
							case 'urlplugin':
								destType = conf.lVSubType;
								conf.hasTrans = conf.hasSel = false;
								break;
						}

						break;

					case 'url':
						destType = 'static';

						// lVSubType
						switch (conf.lVSubType) {
							case 'web':
								conf.hasSel = false;
								break;

							case 'mail':
								conf.hasTarg = conf.hasTrans = conf.hasSel = false;
								break;
						}

						break;
				}

				break;
		}

		if (conf.hasTarg && destType)
			conf.targets = this.getTargets(destType);

		return conf;
	};

}