/*
 * \brief CheckBox class.
 *
 * \file CheckBox.js
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
 * SVN: $Id: CheckBox.js 5004 2011-05-27 10:26:48Z drazenk $
 *
 */

Jedox.wss.wsel.CheckBox = (function ()
{
	// private static fields
	var type = 'CheckBox',
		defLockedState = false;

	// class constructor
	return function (conf, cb) {
		Jedox.wss.wsel.CheckBox.parent.constructor.call(this, conf);

		this.states = {'unchecked': {g: false, c: false}, 'checked': {g: true, c: true}, 'mixed': {g: '#N/A', c: null}};

		var conn = Jedox.backend,
			env = this._env.shared,
			actCellCoords = env.selectedCellCoords,
			formulaParser = Jedox.wss.formula,
			trgTypes = Jedox.wss.wsel.Base.trgTypes,
			trgType = this.getTargetType(),
			that = this,
			hasCB = cb instanceof Array && cb.length > 1,
			dims = Jedox.wss.wsel.CheckBox.dims;

		// Check state.
		if (this.states[this.conf.state])
			this.conf.selval = this.states[this.conf.state].g;
		else {
			if (hasCB) cb[1].call(cb[0], [false, 'checkbox_inv_state', {}]);
			return;
		}

		if (!this.conf.id) {
			var isNew = true;

			if (this.conf == undefined)
				this.conf = {
					type: type
					//, name: 'CheckBoxN'
					, label: 'CheckBoxN'
					, trange: ''
					//, trange: 'C2:D5'
					, tnamedrange: ''
					// , tnamedrange: 'ComboBox1'
					, tvar: 'ComboBox'
					, state: 'unchecked'// | 'checked' | 'mixed'
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

			if (this.conf.height == undefined)
				this.conf.height = dims.defH;

			if (this.conf.tvar == undefined)
				this.conf.tvar = '';

			if (!this.conf.macros)
				this.conf.macros = {};

			if (this.conf.zindex == undefined)
				this.conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();

			if (this.conf.locked == undefined)
				this.conf.locked = defLockedState;

			if (this.conf.singleCell == undefined)
				this.conf.singleCell = true;

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

			// Add Worksheet Element.
			var res = conn.ccmd(0, [ 'wadd', '', {
					e_type: 'formel',
					n_target_ref: '='.concat(trgType == trgTypes.VAR ? '@' : '', this.conf[trgType]),
					formel_name: this.conf.name,
					formel_type: this.conf.type,
					zindex: this.conf.zindex,
					locked: this.conf.locked,
					macros: this.conf.macros,
					data: {
						trange: this.conf.trange,
						tnamedrange: this.conf.tnamedrange,
						tvar: this.conf.tvar,
						selval: this.conf.state,
						label: this.conf.label
					}
				}])[0];

			if (res[0] && res[1].length > 0)
				this.conf.id = res[1][0];
			else {
				if (hasCB) cb[1].call(cb[0], [false, 'formel_add_wsel_err', {}]);
				return;
			}

			// Fill range values if needed.
			if (this.conf.trange.length > 0) {
				conn.ccmdBuffer();

				if (destRng.sheet.length && destRng.sheet != this._book._sheetSelector.getActiveSheetName()) {
					var actSheetId = this._sheet._uid,
						tSheetId = this._book._sheetSelector.getIdByName(destRng.sheet);

					conn.ccmd(null, ['osel', 2, tSheetId]);
				}

				conn.ccmd(null, ['cdrn', {cm: true}, destRng.rng.concat({v: Ext.decode(this.conf.selval)})]);

				if (tSheetId)
					conn.ccmd(null, ['osel', 2, actSheetId]);

				conn.ccmdFlush(true, true);
			}

			// Create named range if needed.
			if (this.conf.tnamedrange.length > 0) {
				conn.ccmd(true, ["nadd", [actCellCoords[0], actCellCoords[1], {
					name: this.conf.tnamedrange,
					refers_to: '='.concat(Jedox.wss.i18n.bool[(typeof this.conf.selval == 'string' ? Ext.util.JSON.encode(this.conf.selval) : this.conf.selval) ? 'true' : 'false']),
					scope: this._book._sheetSelector.getActiveSheetName(),
					comment: 'Managed by form element '.concat(this.conf.name)
				}]], true, conn.Q_ALL, conn.D_NONE);
			}

			// Set variable if needed.
			if (this.conf.tvar.length > 0)
				conn.ccmd(null, ['svar', this.conf.tvar, this.conf.selval]);
		} else if (this.conf.targetVal != null) {
			var isNew = false;

			if (this.conf.tvar.length && this.conf.targetVal == '#VALUE!') {
				this.conf.targetVal = this.states[this.conf.state].g;
				conn.ccmd(null, ['svar', this.conf.tvar, this.conf.selval]);
			}

			this.preselect(this.conf.targetVal, false);
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
		var currDate = new Date();

		this.resCont = [];
		this.elem = [];

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

			this.elem[i] = new Ext.form.Checkbox({
	    		id: contId.concat('_CheckBox_', this.conf.id),
	    		renderTo: formelContId,
	    		fieldLabel: '',
		        labelSeparator: '',
		        boxLabel: this.conf.label,
	    		checked: this.states[this.conf.state].c,
	    		width: this.conf.width ? this.conf.width : 'auto',
	    		_paneId: i,
	    		listeners: {
					check: {fn: this.onCheck, scope: this}
				}
	    	});

			if (isNew && i == 0) {
				this.conf.width = this.elem[i].wrap.dom.offsetWidth;

				// gen n_location and pos_offset objects
				var posConf = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height, this.conf.singleCell),
					updObj = {};
				updObj[this.conf.id] = posConf;

				conn.ccmd(true, [ 'wupd', '', updObj ]);
			}

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
					'resize': {fn: this.afterResizeFormel, scope: this},
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

		Jedox.wss.wsel.wselRegistry.add(this);
		if (hasCB) cb[1].call(cb[0], [true]);
	};
}
)();

// CheckBox extends FormBase
Jedox.util.extend(Jedox.wss.wsel.CheckBox, Jedox.wss.wsel.FormBase);

// public fields
Jedox.wss.wsel.CheckBox.events = [{name: 'check', funcname: 'Check'}];
Jedox.wss.wsel.CheckBox.dims = {minW: 25, minH: 22, maxW: 700, maxH: 22, defW: 150, defH: 22};

//public methods
clsRef = Jedox.wss.wsel.CheckBox;

clsRef.prototype.updateWSElData = function() {
	var conn = Jedox.backend,
			updObj = {};

	updObj[this.conf.id] = {
		data: {
			trange: this.conf.trange,
			tnamedrange: this.conf.tnamedrange,
			tvar: this.conf.tvar,
			selval: this.conf.state,
			label: this.conf.label
		}
	};

	conn.ccmd(true, [ 'wupd', '', updObj ]);
};

clsRef.prototype._resState = function(val) {
	for (var state in this.states)
		if (this.states[state].c == val)
			return state;

	return false;
};

clsRef.prototype.onCheck = function(comp, checked) {
	var paneId = comp._paneId == undefined ? this._sheet._aPane._id : comp._paneId;

	if (this.isCmpMoved(comp)) {
		this.elem[paneId].suspendEvents();
		this.elem[paneId].setValue(!checked);
		this.elem[paneId].resumeEvents();

		return;
	}

	var selState = this._resState(checked),
		conn = Jedox.backend;

	if (!selState || selState == this.conf.state)
		return;

	for (var i = this.elem.length - 1, cmpVal = this.states[selState].c; i >= 0; i--)
		if (i != paneId) {
			this.elem[i].suspendEvents();
			this.elem[i].setValue(cmpVal);
			this.elem[i].resumeEvents();
		}

	this.conf.state = selState;
	this.conf.selval = this.states[selState].g;

	conn.ccmdBuffer();
	this.updateDependencies();

	// Update Worksheet Element.
	this.updateWSElData();

	if (this.conf.macros.check) {
		var jwmacro = Jedox.wss.macro;
		conn.ccmd([ jwmacro, jwmacro.ui_exec ], [ 'em', 'php', 'base/macro/em.php', 'em', [ this.conf.macros.check, this.states[selState].c ], this._book._gmode_edit ? this._sheet._defaultSelection.getActiveRange().getValue() : 'A1' ]);
	}

	conn.ccmdFlush(true, true);
};

clsRef.prototype.update = function(editConf, cb) {
	var conn = Jedox.backend,
		paneId = this._sheet._aPane._id,
		actCellCoords = this._env.shared.selectedCellCoords,
		hasCB = cb instanceof Array && cb.length > 1,
		wsel = {}, updObj = {},
		chkNameAndRng = chkNRng = false,
		batchStarted = updWsel = updData = updDep = false;

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

		// Check Named Range.
//		if (chkNRng && chkRes[chkName ? 1 : 0][1][0]) {
//			if (hasCB) cb[1].call(cb[0], [false, 'wsel_nrange_exists', {name: editConf.tnamedrange}]);
//			return;
//		}

		batchStarted = false;
	}

	// Update name.
	if (editConf.name != this.conf.name) {
		this.conf.name = editConf.name;
		wsel['formel_name'] = this.conf.name;
	}

	// Update label.
	if (editConf.label != this.conf.label) {
		startBatch();

		for (var i = this._panes.length - 1; i >= 0; i--) {
			this.elem[i].wrap.child('.x-form-cb-label').update(editConf.label);

			this.wrapper[i].resizeTo(editConf.label.length * 20 + 50, this.conf.height);

			if (i == 0)
				this.conf.width = this.elem[i].wrap.dom.offsetWidth;

			this.wrapper[i].resizeTo(this.conf.width, this.conf.height);
		}

		this.conf.label = editConf.label;
		updData = true;
	}

	// Update state.
	if (editConf.state != this.conf.state) {
		this.conf.state = editConf.state;
		this.conf.selval = this.states[this.conf.state].g;

		for (var i = this.elem.length - 1; i >= 0; i--) {
			this.elem[i].suspendEvents();
			this.elem[i].setValue(this.states[this.conf.state].c);
			this.elem[i].resumeEvents();
		}

		updData = updDep = true;

		if (this.conf.macros.check) {
			startBatch();

			var jwmacro = Jedox.wss.macro;
			conn.ccmd([ jwmacro, jwmacro.ui_exec ], [ 'em', 'php', 'base/macro/em.php', 'em', [ this.conf.macros.check, this.states[this.conf.state].c ], this._book._gmode_edit ? this._sheet._defaultSelection.getActiveRange().getValue() : 'A1' ]);
		}
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
		this.conf.tnamedrange = editConf.tnamedrange;

		if (this.conf.tnamedrange.length) {
			if (!chkRes[chkNameAndRng ? 1 : 0][1][0]) {
				startBatch();
				conn.ccmd(null, ["nadd", [actCellCoords[0], actCellCoords[1], {
					name: this.conf.tnamedrange,
					refers_to: '='.concat(Jedox.wss.i18n.bool['true']),
					scope: this._book._sheetSelector.getActiveSheetName(),
					comment: 'Managed by form element '.concat(this.conf.name)
				}]]);
			}

			wsel['n_target_ref'] = '='.concat(this.conf.tnamedrange);
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

	if (updWsel || updData) {
		if (updData)
			wsel['data'] = {
				trange: this.conf.trange,
				tnamedrange: this.conf.tnamedrange,
				tvar: this.conf.tvar,
				selval: this.conf.state,
				label: this.conf.label
			};

		updObj[this.conf.id] = wsel;

		startBatch();
		conn.ccmd(null, ['wupd', '', updObj]);
	}

	if (updDep) {
		startBatch();
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

clsRef.prototype.preselect = function(tVal, updEl) {
	var selState = this._resState(tVal instanceof Array ? tVal[0] : tVal);

	if (!selState || selState == this.conf.state)
		return false;

	this.conf.state = selState;
	this.conf.selval = this.states[selState].g;

	if (updEl)
		for (var i = this.elem.length - 1; i >= 0; i--)
			this.elem[i].setValue(this.states[selState].c);

	this.updateWSElData();

	return true;
}

clsRef.prototype.updateTarget = function(data) {
	var trgType = this.getTargetType(),
		selState = this._resState(data.n_target_val instanceof Array ? data.n_target_val[0] : data.n_target_val),
		tRefIdx = data.n_target_ref.search(/^=/) + 1,
		updData = false;

	if (!data.n_target_ref.search(/^=@/))
		tRefIdx++;

	data.n_target_ref = data.n_target_ref.substr(tRefIdx);

	if (this.conf[trgType] != data.n_target_ref) {
		this.conf[trgType] = data.n_target_ref;
		updData = true;
	}

	if (!this.preselect(data.n_target_val, true) && updData)
		this.updateWSElData();
};

clsRef = null;