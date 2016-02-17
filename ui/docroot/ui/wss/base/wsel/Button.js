/*
 * \brief Button class.
 *
 * \file Button.js
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
 * SVN: $Id: Button.js 4776 2011-03-28 14:25:45Z predragm $
 *
 */

Jedox.wss.wsel.Button = (function ()
{
	// private static fields
	var type = 'Button',
		defLockedState = false;

	// class constructor
	return function (conf, cb) {
		Jedox.wss.wsel.Button.parent.constructor.call(this, conf);

		var conn = Jedox.backend,
			env = this._env.shared,
			hasCB = cb instanceof Array && cb.length > 1,
			dims = Jedox.wss.wsel.Button.dims;

		if (!this.conf.id) {
			var isNew = true;

			if (this.conf == undefined)
				this.conf = {
					type: type,
					name: 'ButtonN',
					label: 'ButtonN',
					zindex: 50,
					locked: defLockedState
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

			if (this.conf.fixedH == undefined)
				this.conf.fixedH = true;

			if (!this.conf.macros)
				this.conf.macros = {};

			if (this.conf.zindex == undefined)
				this.conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();

			if (this.conf.locked == undefined)
				this.conf.locked = defLockedState;

			this.conf.bookId = this._book.id;

			// Check conf data.

			// Check Worksheet Element.
			if (conn.ccmd(0, ['wget', '', [], ['e_id'], {e_type: 'formel', formel_name: this.conf.name}])[0][1].length > 0) {
				if (hasCB) cb[1].call(cb[0], [false, 'formel_exists', {name: conf.name}]);
				return;
			}

			// Add Worksheet Element.
			var res = conn.ccmd(0, [ 'wadd', '', {
					e_type: 'formel',
					n_refers_to: '',
					formel_name: this.conf.name,
					formel_type: this.conf.type,
					zindex: this.conf.zindex,
					locked: this.conf.locked,
					macros: this.conf.macros,
					data: {
						label: this.conf.label
					}
				}])[0];

			if (res[0] && res[1].length > 0)
				this.conf.id = res[1][0];
			else {
				if (hasCB) cb[1].call(cb[0], [false, 'formel_add_wsel_err', {}]);
				return;
			}
		} else {
			var isNew = false,
				convObj = {};

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
		for (var i = 0, panesLen = this._panes.length, gridDivId, formelContId, pane, contId; i < panesLen; i++) {
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

			this.elem[i] = new Ext.Button({
	    		id: contId.concat('_Button_', this.conf.id),
	    		renderTo: formelContId,
	    		text: this.conf.label,
	    		_paneId: i,
	    		listeners: {
					click: {fn: this.onClick, scope: this}
				}
	    	});

			if (i == 0) {
				if (this.conf.width != dims.defW)
					this.elem[i].getEl().dom.style.width = ''.concat(this.conf.width, 'px');

				this.conf.width = this.elem[i].getEl().dom.offsetWidth;
				this.conf.height = this.elem[i].getEl().dom.offsetHeight;

				// gen n_location and pos_offset objects if button is new
				if (isNew) {
					var posConf = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height);

					var updObj = {};
					updObj[this.conf.id] = {
						n_location: posConf.n_location,
						pos_offsets: posConf.pos_offsets
					};

					conn.ccmd(true, [ 'wupd', '', updObj ]);
				}
			} else
				this.elem[i].getEl().dom.style.width = ''.concat(this.conf.width, 'px');

			if (!this.isUserMode) {
				this.wrapper[i] = new Ext.ux.ResizableConstrained(formelContId, {
					wrap: !this.isUserMode,
					dynamic: !this.isUserMode,
					pinned: false,
					width: this.conf.width,
					height: this.conf.height,
					minWidth: this.conf.width,
					maxWidth: dims.maxW,
					minHeight: this.conf.height,
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

// Button extends FormBase
Jedox.util.extend(Jedox.wss.wsel.Button, Jedox.wss.wsel.FormBase);

// public fields
Jedox.wss.wsel.Button.events = [{name: 'click', funcname: 'Click'}];
Jedox.wss.wsel.Button.dims = {minW: 20, minH: 22, maxW: 500, maxH: 22, defW: 70, defH: 22};

//public methods
clsRef = Jedox.wss.wsel.Button;

clsRef.prototype.onClick = function(comp, e) {
	if (this.isCmpMoved(comp) || !this.conf.macros.click)
		return;

	var jwmacro = Jedox.wss.macro,
		conn = Jedox.backend;

	conn.ccmdBuffer();

	conn.ccmd([ jwmacro, jwmacro.ui_exec ], [ 'em', 'php', 'base/macro/em.php', 'em', [ this.conf.macros.click ], this._book._gmode_edit ? this._sheet._defaultSelection.getActiveRange().getValue() : 'A1' ]);

	conn.ccmdFlush(true, true);
};

clsRef.prototype.remove = function() {
	// Remove Form Element component.
	for (var i = this._panes.length - 1; i >= 0; i--) {
		this.elem[i].destroy();
		this.wrapperEl[i].remove();
	}

	Jedox.wss.wsel.wselRegistry.remove(this._book, this._sheet._uid, this.conf.id);

	// Remove Worksheet Element.
	var conn = Jedox.backend;
	conn.ccmd(true, [ 'wdel', '', [ this.conf.id ] ]);
};

clsRef.prototype.update = function(editConf, cb) {
	var conn = Jedox.backend,
		paneId = this._sheet._aPane._id,
		hasCB = cb instanceof Array && cb.length > 1,
		wsel = {}, updObj = {},
		batchStarted = updWsel = updData = false;

	function startBatch() {
		if (!batchStarted) {
			conn.ccmdBuffer();
			batchStarted = true;
		}
	}

	// Check name and named range.
	if (editConf.name != this.conf.name) {
		if (conn.ccmd(0, ['wget', '', [], ['e_id'], {e_type: 'formel', formel_name: editConf.name}])[0][1].length) {
			if (hasCB) cb[1].call(cb[0], [false, 'formel_exists', {name: editConf.name}]);
			return;
		}

		else {
			this.conf.name = editConf.name;
			wsel['formel_name'] = this.conf.name;
		}
	}

	if (editConf.label != this.conf.label) {
		startBatch();

		for (var i = this._panes.length - 1, elDom; i >= 0; i--) {
			this.elem[i].setText(editConf.label);

			elDom = this.elem[i].getEl().dom;
			this.wrapper[i].resizeTo(elDom.offsetWidth, elDom.offsetHeight);

			if (i == 0) {
				this.conf.width = elDom.offsetWidth;
				this.conf.height = elDom.offsetHeight;
			}

			this.wrapper[i].minWidth = this.conf.width;
			this.wrapper[i].minHeight = this.conf.height;
		}

		this.conf.label = editConf.label;
		updData = true;
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
				label: this.conf.label
			};

		updObj[this.conf.id] = wsel;

		startBatch();
		conn.ccmd(0, ['wupd', '', updObj]);
	}

	if (batchStarted)
		conn.ccmdFlush();

	if (hasCB) cb[1].call(cb[0], [true]);
};

clsRef.prototype.setCmpSize = function(w, h) {
	for (var i = this.elem.length - 1; i >= 0; i--)
		this.elem[i].getEl().dom.style.width = ''.concat(w, 'px');

	this.conf.width = w;
	this.conf.height = h;
};

clsRef = null;