/*
 * \brief ComboBox class.
 *
 * \file ComboBox.js
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
 * SVN: $Id: ComboBox.js 5140 2011-07-22 10:44:05Z predragm $
 *
 */

Jedox.wss.wsel.ComboBox = (function ()
{
	// private static fields
	var type = 'ComboBox',
		defDims = {w: 150, h: 22},
		defLockedState = false;


	// class constructor
	return function (conf, cb) {
		Jedox.wss.wsel.ComboBox.parent.constructor.call(this, conf);

		var conn = Jedox.backend,
			env = this._env.shared,
			actCellCoords = env.selectedCellCoords,
			formulaParser = Jedox.wss.formula,
			trgTypes = Jedox.wss.wsel.Base.trgTypes,
			trgType = this.getTargetType(),
			that = this,
			hasCB = cb instanceof Array && cb.length > 1,
			dims = Jedox.wss.wsel.ComboBox.dims;

		this.preselectType = {
			LOAD: 0,
			REFR: 1,
			UTRG: 2
		};

		if (!this.conf.id) {
			if (this.conf == undefined)
				this.conf = {
					type: type
					//, name: 'ComboBoxN',
					, src: '=PALO.SUBSET("localhost/Demo","Years",1,,,,,,,PALO.SORT(0,0,,0,,0,1))'
					, _gendata: []
					//, src: '=Sheet1!$A$1:$D$4'
					, trange: ''
					//, trange: 'C2:D5'
					, tnamedrange: ''
//					, tnamedrange: 'ComboBox1'
					, tvar: 'ComboBox'
					, zindex: 50
					, locked: defLockedState
				};

			// Collect data.
			if (this.conf.name == undefined)
				this.conf.name = this.conf.type.concat(Jedox.wss.wsel.countEl(this.conf.type) + 1);

			if (this.conf.top == undefined)
				this.conf.top = env.selectedCell.parentNode.offsetTop;

			if (this.conf.left == undefined)
				this.conf.left = env.selectedCell.offsetLeft;

			if (this.conf.width == undefined)
				this.conf.width = dims.defW;

			if (this.conf.height == undefined)
				this.conf.height = dims.defH;

			if (this.conf.tvar == undefined)
				this.conf.tvar = '';

			if (this.conf.singleCell == undefined)
				this.conf.singleCell = true;

			if (!this.conf.macros)
				this.conf.macros = {};

			if (!this.conf._gendata)
				this.conf._gendata = [];

			if (this.conf.zindex == undefined)
				this.conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();

			if (this.conf.locked == undefined)
				this.conf.locked = defLockedState;

			this.conf.bookId = this._book.id;

			// Check conf data.

			// Check target cell or range.
			if (this.conf.trange.length > 0) {
				if (!this.conf.trange.search(/^=/))
					this.conf.trange = this.conf.trange.substr(1);

				var destRng = formulaParser.parse(this.conf.trange);

				if (!destRng.length) {
					if (hasCB) cb[1].call(cb[0], [false, 'wsel_inv_target', {}]);
					return;
				}

				destRng = destRng[0];

				if (destRng.sheet.length && !this._book._sheetSelector.getIdByName(destRng.sheet)) {
					if (hasCB) cb[1].call(cb[0], [false, 'wsel_inv_target_sheet', {name: destRng.sheet}]);
					return;
				}
			}

			conn.ccmdBuffer();
			conn.ccmd(0, ['wget', '', [], ['e_id'], {e_type: 'formel', formel_name: this.conf.name}]);

			if (this.conf.tnamedrange.length > 0)
				conn.ccmd(0, ["nexs", [this.conf.tnamedrange, this._sheet.getUid()]]);

			var chkRes = conn.ccmdFlush();

			// Check Worksheet Element.
			if (chkRes[0][1].length > 0) {
				if (hasCB) cb[1].call(cb[0], [false, 'formel_exists', {name: conf.name}]);
				return;
			}

			// Check Named Range.
			if (this.conf.tnamedrange.length > 0 && chkRes[1][1][0]) {
				if (hasCB) cb[1].call(cb[0], [false, 'wsel_nrange_exists', {name: conf.tnamedrange}]);
				return;
			}

			// gen n_location and pos_offset objects
			var posConf = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height, this.conf.singleCell);

			// Add Worksheet Element.
			var res = conn.ccmd(0, [ 'wadd', '', {
					e_type: 'formel',
					n_refers_to: this.conf.src,
					n_target_ref: '='.concat(trgType == trgTypes.VAR ? '@' : '', this.conf[trgType]),
					n_location: posConf.n_location,
					pos_offsets: posConf.pos_offsets,
					zindex: this.conf.zindex,
					locked: this.conf.locked,
					n_use_locale: this.conf.formulaEnabled,
					formel_name: this.conf.name,
					formel_type: this.conf.type,
					macros: this.conf.macros,
					_gendata: this.conf._gendata,
					size: posConf.size
				}])[0];

			if (res[0] && res[1].length > 0)
				this.conf.id = res[1][0];
			else {
				if (hasCB) cb[1].call(cb[0], [false, 'formel_add_wsel_err', {}]);
				return;
			}

			// Get values from Worksheet Element
			var wselData = conn.ccmd(0, [ 'wget', '', [], [ 'n_refers_to', 'n_get_val' ], { e_id: this.conf.id } ])[0][1][0];

			this.conf.src = wselData.n_refers_to;
			this.conf.treeVal = Jedox.util.cols2Tree(wselData.n_get_val instanceof Array ? wselData.n_get_val : [ wselData.n_get_val ], true);

			var hasItems = this.conf.treeVal.length;

			this.conf.selval = hasItems ? this.conf.treeVal[0]['val'] : '';
			this.conf.selalias = hasItems ? this.conf.treeVal[0]['text'] : '';
			this.conf.selpath = '/root'.concat(hasItems ? '/'.concat(this.conf.selval) : '');

			var updObj = {};
			updObj[this.conf.id] = {
				data: {
					trange: this.conf.trange,
					tnamedrange: this.conf.tnamedrange,
					tvar: this.conf.tvar,
					selval: this.conf.selval,
					selpath: this.conf.selpath
				}
			};

			conn.ccmdBuffer();
			conn.ccmd(null, ['wupd', '', updObj]);

			// Fill range values if needed.
			if (this.conf.trange.length > 0) {
				var doUpd = true;

				if (destRng.sheet.length && destRng.sheet != this._book._sheetSelector.getActiveSheetName()) {
					var actSheetId = this._sheet._uid,
						tSheetId = doUpd = this._book._sheetSelector.getIdByName(destRng.sheet);

					if (doUpd)
						conn.ccmd(null, ['osel', 2, tSheetId]);
				}

				if (doUpd) {
					var cdrnVal = {v: this.conf.selval};

					if (!this.conf.formulaEnabled)
						cdrnVal.a = {'palo_pe': {'type': 'dim', 'name': this.conf._gendata[0][2]}};

					conn.ccmd(null, ['cdrn', {cm: true}, destRng.rng.concat(cdrnVal)]);

					if (tSheetId)
						conn.ccmd(null, ['osel', 2, actSheetId]);
				}
			}

			// Create named range if needed.
			if (this.conf.tnamedrange.length > 0) {
				conn.ccmd(null, ["nadd", [actCellCoords[0], actCellCoords[1], {
					name: this.conf.tnamedrange,
					refers_to: '='.concat(typeof this.conf.selval == 'string' ? Ext.util.JSON.encode(this.conf.selval) : this.conf.selval),
					scope: this._book._sheetSelector.getActiveSheetName(),
					comment: 'Managed by form element '.concat(this.conf.name)
				}]]);
			}

			// Set variable if needed.
			if (this.conf.tvar.length > 0)
				conn.ccmd(null, ['svar', this.conf.tvar, this.conf.selval]);

			conn.ccmdFlush(true, true);
		} else {
			this.conf.treeVal = Jedox.util.cols2Tree(this.conf.treeVal instanceof Array ? this.conf.treeVal : [ this.conf.treeVal ], true);

			if (this.conf.tvar.length && this.conf.targetVal == '#VALUE!') {
				this.conf.targetVal = this.conf.selval;
				conn.ccmd(null, ['svar', this.conf.tvar, this.conf.selval]);
			}

			this.conf.selalias = this.getAlias(this.conf.treeVal, this.conf.targetVal == null ? this.conf.selval : this.conf.targetVal);

			var convObj = {};

			if (this.conf.zindex == undefined) {
				this.conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();
				convObj.zindex = this.conf.zindex;
			} else
				this.conf.zindex = parseInt(this.conf.zindex);

			if (this.conf.locked == undefined) {
				this.conf.locked = defLockedState;
				convObj.locked = this.conf.locked;
			}

			for (var conv in convObj) {
				var updObj = {};
				updObj[this.conf.id] = convObj;

				Jedox.backend.ccmd(null, ['wupd', '', updObj]);
				break;
			}
		}

		// Create element.
		var currDate = new Date(),
			treeNodeProvider = new Ext.tree.TreeNodeProvider({
				getNodes: function() {
					return this.data;
				}
			});

		this.myTreeLoader = new Ext.ux.tree.PagingTreeLoader({
			treeNodeProvider: treeNodeProvider,
			clearOnLoad: true
		});
		this.myTreeLoader.updateTreeNodeProvider(this.conf.treeVal);

		this.resCont = [];
		this.elem = [];
		this.cmbTreeList = [];

		if (!this.isUserMode) {
			this.wrapper = [];
			this.wrapperEl = [];
		}

		// Create presentation for each pane.
		for (var i = this._panes.length - 1, gridDivId, formelContId, pane, contId; i >= 0; i--) {
			pane = this._panes[i];
			contId = pane._domId;
			gridDivId = contId.concat('_IC');
			formelContId = contId.concat('_wsel_cont_', this.conf.id);

			this.calcConstraints(this._panes[i]);

			this.resCont[i] = Ext.DomHelper.append(
					Ext.DomQuery.selectNode('div[id=' + gridDivId + ']'),
					{
						tag: 'div',
						id: formelContId,
						width: this.conf.width,
						height: this.conf.height,
						cls: 'ws_element',
						style: 'z-index: '.concat(this.conf.zindex, '; position: absolute; left:', this.conf.left, 'px; top:', this.conf.top, 'px;')
					},
					false
				);

			this.elem[i] = new Ext.ux.TreeComboBox({
				id: contId.concat('_ComboBox_', this.conf.id),
				renderTo: formelContId,
				disabled: false,
				store: new Ext.data.SimpleStore({fields:[],data:[[]]}),
				hideLabel: true,
				editable: false,
				triggerAction: 'all',
				mode: 'local',
				shadow: false,
				maxHeight: 200,
				tpl: '<tpl for="."><div style="height:200px"><div class="cmbTreeList" id="'.concat(contId, '_cmbTreeList_', this.conf.id, '"></div></div></tpl>'),
				minListWidth: 250,
				selectedClass: '',
				onSelect: Ext.emptyFn,
				value: this.conf.selalias,
				width: this.conf.width,
				allowBlank: true,
				selectOnFocus: false,
				resizable: false,
				validateOnBlur: false,
				preventMark: true,
				_paneId: i,
				listeners: {
					expand: {fn: this.onExpandComboBox, scope: this},
					collapse: {fn: this.onCollapseComboBox, scope: this}
				}
			});

			this.cmbTreeList[i] = new Ext.tree.TreePanel({
				id: contId.concat('_cmbTreePanel_', this.conf.id),
				border: false,
				cls: 'x-tree-noicon',
				autoScroll: true,
				animate: true,
				height: 200,
				enableDD: false,
				containerScroll: true,
				plugins: new Ext.ux.tree.TreeNodeMouseoverPlugin(),
				loader: this.myTreeLoader,
				rootVisible: false,
				root: new Ext.tree.AsyncTreeNode({
					text: "[All Elements]".localize(),
					draggable: false,
					val: 'root'
				}),
				listeners: {
					click: {fn: this.onSelComboBox, scope: this}
					,beforeexpandnode: {fn: this.onBeforeExpColl, scope: this}
					,beforecollapsenode: {fn: this.onBeforeExpColl, scope: this}
				},
				initConf: this.conf
			});

			if (!this.isUserMode) {
				this.wrapper[i] = new Ext.ux.ResizableConstrained(formelContId, {
					wrap: !this.isUserMode,
					dynamic: !this.isUserMode,
					pinned: false,
					width: this.conf.width,
					height: this.conf.height,
					minWidth: dims.minW,
					maxWidth: dims.maxW,
					minHeight: dims.minH,
					maxHeight: dims.maxH,
					preserveRatio: false,
					transparent: true,
					handles: !this.isUserMode ? 'e w' : 'nw',
					draggable: !this.isUserMode,
					enabled: !this.isUserMode,
					style: 'background-color: white;',
					resizeRegion: Ext.get(gridDivId).getRegion(),
					_paneId: i
				});

				this.wrapper[i].on({
					'resize': {fn: that.afterResizeFormel, scope: this},
					'beforeresize': {fn: this.beforeResize, scope: this}
				});

				this.wrapper[i].dd.maintainOffset = true;
				this.wrapper[i].setXConstraint(this.elConstr[i].left, this.elConstr[i].right);
				this.wrapper[i].setYConstraint(this.elConstr[i].up, this.elConstr[i].down);

				this.wrapperEl[i] = this.wrapper[i].getEl();
				this.wrapperEl[i].dom.style.backgroundColor = '#FFFFFF';
				this.wrapperEl[i].dom.style.zIndex = this.conf.zindex;

				this.wrapperEl[i].on({
					'mousedown': {fn: this.onMouseDown, scope: this, options: {paneId: i}}
				});

				if (this.conf.locked)
					this.setLock(true, true, i);
			}

			this.elem[i].wsel = this;
		}

		if (this.conf.targetVal != null)
			this.preselect(this.conf.targetVal, this.preselectType.LOAD);

		Jedox.wss.wsel.wselRegistry.add(this);
		if (hasCB) cb[1].call(cb[0], [true]);
	};
}
)();

// ComboBox extends FormBase
Jedox.util.extend(Jedox.wss.wsel.ComboBox, Jedox.wss.wsel.FormBase);

// public fields
Jedox.wss.wsel.ComboBox.events = [{name: 'select', funcname: 'Select'}];
Jedox.wss.wsel.ComboBox.dims = {minW: 80, minH: 22, maxW: 700, maxH: 22, defW: 150, defH: 22};

//public methods
clsRef = Jedox.wss.wsel.ComboBox;

clsRef.prototype.updateWSElData = function() {
	var conn = Jedox.backend,
			updObj = {};

	updObj[this.conf.id] = {
		data: {
			trange: this.conf.trange,
			tnamedrange: this.conf.tnamedrange,
			tvar: this.conf.tvar,
			selval: this.conf.selval,
			selpath: this.conf.selpath
		}
	};

	conn.ccmd(true, [ 'wupd', '', updObj ]);
};

clsRef.prototype.beforeShowCtxMenu = function() {
	for (var i = this.elem.length - 1; i >= 0; i--)
		this.elem[i].collapse();
};

clsRef.prototype.collapse = function() {
	for (var i = this.elem.length - 1; i >= 0; i--) {
		this.elem[i].collapse();

		if (this.elem[i].isExpanded())
			this.elem[i].collapse();
	}
};

clsRef.prototype.onSelComboBox = function(node, e) {
	var paneId = this._sheet._aPane._id;

	for (var i = this.elem.length - 1; i >= 0; i--)
		this.elem[i].setValue(node.text);

	this.elem[paneId].collapse();

	if (node.getPath('val') == this.conf.selpath)
		return;

	this.conf.selval = node.attributes.val;
	this.conf.selalias = node.attributes.text;
	this.conf.selpath = node.getPath('val');

	var conn = Jedox.backend;

	conn.ccmdBuffer();
	this.updateDependencies();

	// Update Worksheet Element.
	this.updateWSElData();

	if (this.conf.macros.select) {
		var jwmacro = Jedox.wss.macro;
		conn.ccmd([ jwmacro, jwmacro.ui_exec ], [ 'em', 'php', 'base/macro/em.php', 'em', [ this.conf.macros.select, this.conf.selval ], this._book._gmode_edit ? this._sheet._defaultSelection.getActiveRange().getValue() : 'A1' ]);
	}

	conn.ccmdFlush(true, true);
};

clsRef.prototype.onExpandComboBox = function(combo) {
	var that = this,
		paneId = combo._paneId == undefined ? this._sheet._aPane._id : combo._paneId;

	if (this.isCmpMoved(combo)) {
		combo.collapse();
		return;
	}

	if (!this.cmbTreeList[paneId].rendered)
		this.cmbTreeList[paneId].render(this._panes[paneId]._domId.concat('_cmbTreeList_', this.conf.id));

	this.cmbTreeList[paneId].getRootNode().reload();

	Jedox.wss.app.switchContextObserver.subscribe(this.collapse, this);

	setTimeout(
		function () {
			that.cmbTreeList[paneId].selectPath(that.conf.selpath, 'val');
		}, 0
	);
};

clsRef.prototype.onCollapseComboBox = function(combo) {
	Jedox.wss.app.switchContextObserver.unsubscribe(this.collapse);
};

clsRef.prototype.refresh = function(data) {
	var dataIsArray = data instanceof Array;

	this.myTreeLoader.updateTreeNodeProvider((this.conf.treeVal = Jedox.util.cols2Tree(dataIsArray ? data : [data], true)));
	this.preselect(dataIsArray ? data[0] : data, this.preselectType.REFR);
};

clsRef.prototype.getSelPath = function(data, selVal, path) {

	function getPath(data, selVal, path) {
		if (data.val == selVal)
			return path.concat('/', selVal);

		if (data.leaf)
			return '';
		else {
			path = path.concat('/', data.val);
			var subpath = '';

			for (var child in data.children) {
				subpath = getPath(data.children[child], selVal, path);

				if (subpath.length)
					return subpath;
			}

			return subpath;
		}
	}

	for (var i = 0, dataLen = data.length, path; i < dataLen; i++) {
		path = getPath(data[i], selVal, '');

		if (path.length)
			return path;
	}

	return '';
};

clsRef.prototype.getAlias = function(data, selVal) {

	function getAlias(data, selVal) {
		if (data.val == selVal)
			return data.text;

		if (data.leaf)
			return '';
		else {
			var subalias = '';

			for (var j = 0, childLen = data.children.length; j < childLen; j++) {
				subalias = getAlias(data.children[j], selVal);

				if (subalias.length)
					return subalias;
			}

			return subalias;
		}
	}

	for (var i = 0, dataLen = data.length, alias; i < dataLen; i++) {
		alias = getAlias(data[i], selVal);

		if (alias.length)
			return alias;
	}

	return selVal;
};

clsRef.prototype.preselect = function(selVal, type) {
	var paneId = this._sheet._aPane._id,
		data = this.cmbTreeList[paneId].loader.getTreeNodeProvider().getData(),
		pSelType = this.preselectType,
		renderedPaneId = -1,

		updateAndStore = function() {
			var conn = Jedox.backend;

			conn.ccmdBuffer();

			// Update dependencies.
			if (type <= this.preselectType.REFR)
				this.updateDependencies();

			// Update Worksheet Element.
			this.updateWSElData();

			conn.ccmdFlush(true, true);

			// Set form element.
			this.conf.selalias = this.getAlias(this.conf.treeVal, this.conf.selval);

			for (var i = this.elem.length - 1; i >= 0; i--)
				this.elem[i].setValue(this.conf.selalias);
		};

	if (!data.length) {
		this.conf.selval = '';
		this.conf.selpath = '/root';

		for (var i = this.cmbTreeList.length - 1; i >= 0; i--)
			if (this.cmbTreeList[i].rendered) {
				this.cmbTreeList[i].getRootNode().reload();
				this.cmbTreeList[i].selectPath('/root', 'val');
			}

		updateAndStore.call(this);
		return;
	}

	for (var i = this.cmbTreeList.length - 1; i >= 0; i--)
		if (this.cmbTreeList[i].rendered) {
			renderedPaneId = i;
			break;
		}

	if (renderedPaneId < 0) {
		switch(type) {
			case pSelType.LOAD:
				var selPath = this.getSelPath(data, selVal),
					selPathLen = selPath.length;

				if (selVal == null || (selPathLen && this.conf.selval == selVal))
					return;

				if (selPath.length) {
					this.conf.selval = selVal;
					this.conf.selpath = '/root'.concat(selPath);
				} else {
					this.conf.selval = data[0].val;
					this.conf.selpath = '/root/'.concat(data[0].val);
				}

				break;

			case pSelType.REFR:
				var selPath = this.getSelPath(data, this.conf.selval);

				if (selPath.length)
					return;
				else {
					this.conf.selval = data[0].val;
					this.conf.selpath = '/root/'.concat(data[0].val);
				}

				break;

			case pSelType.UTRG:
				if (selVal == null || this.conf.selval == selVal)
					return;

				var selPath = this.getSelPath(data, selVal);

				if (selPath.length) {
					this.conf.selval = selVal;
					this.conf.selpath = '/root'.concat(selPath);
				} else
					return;

				break;
		}

		updateAndStore.call(this);
	} else if (type == this.preselectType.REFR) {
		var selNode = this.cmbTreeList[renderedPaneId].getSelectionModel().getSelectedNode(),
			selPath = selNode == null ? 'abc' : selNode.getPath('val'),
			that = this,
			i = 0,

			cbSelectPathHandler = function(bSuccess, oSelNode, tree, iterator) {
				if (!bSuccess) {
					tree.selectPath('/root/'.concat(data[0].val), 'val');
					var selNode = tree.getSelectionModel().getSelectedNode();

					tree.fireEvent('click', selNode, null);
				}
			},

			cbSelectPath = function(bSuccess, oSelNode) {
				cbSelectPathHandler(bSuccess, oSelNode, that.cmbTreeList[i]);
			};

		if (selPath == '/root')
			selPath = '';

		for (i = this.cmbTreeList.length - 1; i >= 0; i--) {
			if (this.cmbTreeList[i].rendered) {
				this.cmbTreeList[i].getRootNode().reload();
				this.cmbTreeList[i].selectPath(selPath, 'val', cbSelectPath);
			}
		}
	} else {
		var selPath = this.getSelPath(data, selVal),
			that = this;

		if (selPath.length)
			selPath = '/root'.concat(selPath);
		else
			return;

		var cbSelectPathHandler = function(bSuccess, oSelNode, wsel) {
				if (bSuccess) {
					wsel.conf.selval = selVal;
					wsel.conf.selalias = wsel.getAlias(wsel.conf.treeVal, wsel.conf.selval);
					wsel.conf.selpath = selPath;

					for (var i = wsel.elem.length - 1; i >= 0; i--)
						wsel.elem[i].setValue(wsel.conf.selalias);

					wsel.updateWSElData();
				}
			},

			cbSelectPath = function(bSuccess, oSelNode) {
				cbSelectPathHandler(bSuccess, oSelNode, that);
			};

		for (var i = this.cmbTreeList.length - 1; i >= 0; i--) {
			if (this.cmbTreeList[i].rendered)
				this.cmbTreeList[i].selectPath(selPath, 'val', cbSelectPath);
			else
				this.elem[i].setValue(this.getAlias(this.conf.treeVal, selVal));
		}
	}
};

clsRef.prototype.update = function(editConf, cb) {
	var conn = Jedox.backend,
		paneId = this._sheet._aPane._id,
		actCellCoords = this._env.shared.selectedCellCoords,
		hasCB = cb instanceof Array && cb.length > 1,
		wsel = {}, updObj = {},
		chkNameAndRng = chkNRng = false,
		batchStarted = updWsel = updData = updDep = updSrc = false;

	if (editConf.tvar == undefined)
		editConf.tvar = '';

	function startBatch() {
		if (!batchStarted) {
			conn.ccmdBuffer();
			batchStarted = true;
		}
	}

	// Check range
	if (editConf.trange.length && editConf.trange != this.conf.trange) {
		if (!editConf.trange.search(/^=/))
			editConf.trange = editConf.trange.substr(1);

		var destRng = Jedox.wss.formula.parse(editConf.trange);

		if (!destRng.length) {
			if (hasCB) cb[1].call(cb[0], [false, 'wsel_inv_target', {}]);
			return;
		}

		destRng = destRng[0];

		if (destRng.sheet.length && !this._book._sheetSelector.getIdByName(destRng.sheet)) {
			if (hasCB) cb[1].call(cb[0], [false, 'wsel_inv_target_sheet', {name: destRng.sheet}]);
			return;
		}
	}

	// Check name and named range.
	if (editConf.name != this.conf.name || editConf.trange != this.conf.trange) {
		startBatch();
		conn.ccmd(0, ['wget', '', [], ['e_id'], {e_type: 'formel', formel_name: editConf.name}]);
		chkNameAndRng = true;
	}

	if (editConf.tnamedrange.length && editConf.tnamedrange != this.conf.tnamedrange) {
		startBatch();
		conn.ccmd(0, ["nexs", [editConf.tnamedrange, this._sheet.getUid()]]);
		chkNRng = true;
	}

	if (chkNameAndRng || chkNRng) {
		var chkRes = conn.ccmdFlush();

		// Check Worksheet Element.
		if (chkNameAndRng && chkRes[0][1].length && chkRes[0][1][0]['e_id'] != this.conf.id) {
			if (hasCB) cb[1].call(cb[0], [false, 'formel_exists', {name: editConf.name}]);
			return;
		}

		batchStarted = false;
	}

	// Update formulaEnabled
	if (editConf.formulaEnabled != this.conf.formulaEnabled) {
		this.conf.formulaEnabled = editConf.formulaEnabled;
		wsel['n_use_locale'] = this.conf.formulaEnabled;
	}

	// Update name.
	if (editConf.name != this.conf.name) {
		this.conf.name = editConf.name;
		wsel['formel_name'] = this.conf.name;
	}

	// Update src.
	if (editConf.src != this.conf.src) {
		this.conf.src = editConf.src;
		wsel['n_refers_to'] = this.conf.src;
		updSrc = true;
	}

	// Update _gendata.
	if (editConf._gendata != this.conf._gendata) {
		this.conf._gendata = editConf._gendata;
		wsel['_gendata'] = this.conf._gendata;
	}

	// Update trange.
	if (editConf.trange != this.conf.trange) {
		if (editConf.trange.length)
			wsel['n_target_ref'] = '='.concat(editConf.trange);

		this.conf.trange = editConf.trange;
		updData = updDep = true;
	}

	// Update tnamedrange.
	if (editConf.tnamedrange != this.conf.tnamedrange) {
		if (editConf.tnamedrange.length)
			wsel['n_target_ref'] = '='.concat(editConf.tnamedrange);

		this.conf.tnamedrange = editConf.tnamedrange;

		if (this.conf.tnamedrange.length && !chkRes[chkNameAndRng ? 1 : 0][1][0]) {
			startBatch();
			conn.ccmd(0, ["nadd", [actCellCoords[0], actCellCoords[1], {
				name: this.conf.tnamedrange,
				refers_to: '=TRUE',
				scope: this._book._sheetSelector.getActiveSheetName(),
				comment: 'Managed by form element '.concat(this.conf.name)
			}]]);
		}

		updData = updDep = true;
	}

	// Update variable.
	if (editConf.tvar != this.conf.tvar) {
		if (editConf.tvar.length)
			wsel['n_target_ref'] = '=@'.concat(editConf.tvar);

		this.conf.tvar = editConf.tvar;
		updData = updDep = true;
	}

	// Update size (size should be updated first, because it's used for n_location calculation)
	if (editConf.width != this.conf.width && this.wrapperEl[paneId] && editConf.width > 0) {
		this.setCmpSize(editConf.width, this.conf.height);

		// set Element width
		for (var i = this.wrapperEl.length - 1; i >= 0; i--)
			this.wrapperEl[i].dom.style.width = ''.concat(this.conf.width, 'px');

		// update wsel in core
		wsel['size'] = [this.conf.width, this.conf.height];
	}

	// Update position
	if (this.wrapperEl[paneId] && ((editConf.left != this.conf.left  && editConf.left > -1) || (editConf.top != this.conf.top && editConf.top > -1))) {
		this.conf.left = editConf.left > -1 ? editConf.left : 0;
		this.conf.top = editConf.top > -1 ? editConf.top : 0;

		// set Element position
		for (var i = this.wrapperEl.length - 1, style; i >= 0; i--) {
			style = this.wrapperEl[i].dom.style;

			style.left = ''.concat(this.conf.left, 'px');
			style.top = ''.concat(this.conf.top, 'px');
		}

		// update wsel in core
		var posConf = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height, this.conf.singleCell);
		wsel['n_location'] = posConf.n_location;
		wsel['pos_offsets'] = posConf.pos_offsets;
	}

	for (var fld in wsel) {
		updWsel = true;
		break;
	}

	if (updSrc) {
		updObj[this.conf.id] = wsel;

		startBatch();
		conn.ccmd(0, ['wupd', '', updObj]);
		conn.ccmd(0, ['wget', '', [], ['n_get_val', 'n_refers_to'], {e_id: this.conf.id}]);

		var updRes = conn.ccmdFlush(),
			nVal = updRes[updRes.length - 1][1][0].n_get_val;

		batchStarted = false;

		this.conf.src = updRes[updRes.length - 1][1][0].n_refers_to;
		this.refresh(Ext.isArray(nVal) ? nVal : [nVal]);
	} else if (updWsel || updData) {
		if (updData)
			wsel['data'] = {
				trange: this.conf.trange,
				tnamedrange: this.conf.tnamedrange,
				tvar: this.conf.tvar,
				selval: this.conf.selval,
				selpath: this.conf.selpath
			};

		updObj[this.conf.id] = wsel;

		startBatch();
		conn.ccmd(null, ['wupd', '', updObj]);

		if (updDep)
			this.updateDependencies();
	}

	if (batchStarted)
		conn.ccmdFlush(true, true);

	if (hasCB) cb[1].call(cb[0], [true]);
};

clsRef.prototype.setCmpSize = function(w, h) {
	for (var i = this.elem.length - 1; i >= 0; i--)
		this.elem[i].setSize(w, h);

	this.conf.width = w;
	this.conf.height = h;
};

clsRef.prototype.updateTarget = function(data) {
	var trgType = this.getTargetType(),
		updVal = data.n_target_val instanceof Array ? data.n_target_val[0] : data.n_target_val,
		tRefIdx = data.n_target_ref.search(/^=/) + 1,
		updData = false;

	if (!data.n_target_ref.search(/^=@/))
		tRefIdx++;

	data.n_target_ref = data.n_target_ref.substr(tRefIdx);

	if (this.conf[trgType] != data.n_target_ref) {
		this.conf[trgType] = data.n_target_ref;
		updData = true;
	}

	if (this.conf.selval != updVal)
		this.preselect(updVal, this.preselectType.UTRG);
	else if (updData)
		this.updateWSElData();
};

clsRef.prototype.onBeforeExpColl = function() {
	var paneId = this._sheet._aPane._id,
		blurField = function(el) {
			el.blur();
		};

	this.elem[paneId].doCollapse = false;
	blurField.defer(1, this.elem[paneId], [this.elem[paneId].el]);
};

clsRef = null;