/*
 * \brief Form element base class.
 *
 * \file FormBase.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: FormBase.js 5086 2011-06-29 14:17:18Z mladent $
 *
 */

Jedox.wss.wsel.FormBase = (function ()
{
	// class constructor
	return function (conf) {
		Jedox.wss.wsel.FormBase.parent.constructor.call(this, conf);
	}
}
)();

// FormBase extends Base
Jedox.util.extend(Jedox.wss.wsel.FormBase, Jedox.wss.wsel.Base);

//public methods

Jedox.wss.wsel.FormBase.setUpdObj = function(updObj, el) {
	if (!el.n_target_ref) {
		updObj[el.e_id] = {n_target_ref: '='.concat(el.data.trange.length ? el.data.trange : el.data.tnamedrange)};

		var loc = el.n_location.split(',', 2);
		if (loc.length > 1)
			updObj[el.e_id]['n_location'] = loc[0];
	}

	if (el.data.tvar == undefined) {
		el.data.tvar = '';

		if (updObj[el.e_id])
			updObj[el.e_id]['data'] = el.data;
		else
			updObj[el.e_id] = {data: el.data};
	}
};

Jedox.wss.wsel.FormBase.loadAll = function(res) {
	if (!(res instanceof Array) || res[0] !== true || !res[1].length)
		return;

	res = res[1];

	var conn = Jedox.backend,
		activeBook = Jedox.wss.app.activeBook;

	conn.ccmdBuffer();

	for (var el, updObj = {}, i = res.length - 1, bookId = activeBook.id, conf; i >= 0; i--) {
		el = res[i];

		conf = {
			id: el.e_id,
			type: el.formel_type,
			name: el.formel_name,
			bookId: bookId,
			zindex: el.zindex,
			locked: el.locked
		};

		switch (el.formel_type) {

			case this.type.COMBO_BOX:
				if (!el.data)
					continue;

				conf.src = el.n_refers_to;
				conf._gendata = el._gendata ? el._gendata : [];
				conf.treeVal = el.n_get_val;
				conf.targetVal = el.n_target_val != undefined ? (el.n_target_val instanceof Array ? el.n_target_val[0] : el.n_target_val) : null;
				conf.trange = el.data.trange;
				conf.tnamedrange = el.data.tnamedrange;
				conf.selval = el.data.selval;
				conf.selpath = el.data.selpath;
				conf.formulaEnabled = el.n_use_locale;
				conf.singleCell = true;

				Jedox.wss.wsel.FormBase.setUpdObj(updObj, el);
				conf.tvar = el.data.tvar;

				break;

			case this.type.CHECK_BOX:
				conf.targetVal = el.n_target_val != undefined ? el.n_target_val : null;
				conf.trange = el.data.trange;
				conf.tnamedrange = el.data.tnamedrange;
				conf.state = el.data.selval;
				conf.label = el.data.label;
				conf.singleCell = true;

				Jedox.wss.wsel.FormBase.setUpdObj(updObj, el);
				conf.tvar = el.data.tvar;

				break;

			case this.type.BUTTON:
				conf.label = el.data.label;
				break;
		}

		conf.macros = el.macros ? el.macros : {};

		Jedox.wss.wsel.Base.loadDims(el, conf, updObj);
		Jedox.wss.wsel.Base.fixDims(conf);

		Jedox.wss.wsel.add(conf);
	}

	for (var updItem in updObj) {
		conn.ccmd(null, ['wupd', '', updObj]);
		break;
	}

	conn.ccmdFlush(true, true);
};

//public fields

Jedox.wss.wsel.FormBase.loadParams = {
	type: 'formel',
	attr: ['e_id', 'e_type', 'n_refers_to', 'n_get_val', 'n_target_ref', 'n_target_val', 'n_location', 'n_use_locale', 'pos_offsets', 'data', '_gendata', 'zindex', 'locked', 'size', 'formel_type', 'formel_name', 'macros'],
	cb: Jedox.wss.wsel.FormBase.loadAll
};

clsRef = Jedox.wss.wsel.FormBase;

clsRef.prototype.getId = function() {
	return this.conf.id;
};

clsRef.prototype.updateDependencies = function() {
	var conn = Jedox.backend,
		env = this._env.shared,
		curBUID, curSUID,

		setBook = function() {
			if (this._book != Jedox.wss.app.activeBook) {
				curBUID = Jedox.wss.app.activeBook.uid;
				curSUID = Jedox.wss.app.activeSheet.getUid();

				conn.ccmd(0, ['osel', 1, this._book.uid]);
			}
		}

	if (this.conf.trange.length > 0) {
		setBook.call(this);

		var destRng = Jedox.wss.formula.parse(this.conf.trange)[0],
			doUpd = true;

		if (destRng.sheet.length && destRng.sheet != this._book._sheetSelector.getActiveSheetName()) {
			var actSheetId = this._sheet._uid,
				tSheetId = doUpd = this._book._sheetSelector.getIdByName(destRng.sheet);

			if (doUpd)
				conn.ccmd(0, ['osel', 2, tSheetId]);
		}

		if (doUpd) {
			var cdrnVal = {v: this.conf.selval};

			if (!this.conf.formulaEnabled && this.conf._gendata && this.conf._gendata.length)
				cdrnVal.a = {'palo_pe': {'type': 'dim', 'name': this.conf._gendata[0][2]}};

			conn.ccmd(0, ['cdrn', {cm: true}, destRng.rng.concat(cdrnVal)]);

			if (tSheetId)
				conn.ccmd(0, ['osel', 2, actSheetId]);
		}
	}

	if (this.conf.tnamedrange.length > 0) {
		setBook.call(this);

		var actCellCoords = this.isUserMode ? [1, 1] : env.selectedCellCoords,
			nrVal = typeof this.conf.selval == 'string' ? Ext.util.JSON.encode(this.conf.selval) : this.conf.selval;

		if (this.conf.type == 'CheckBox')
			nrVal = Jedox.wss.i18n.bool[nrVal ? 'true' : 'false'];

		conn.ccmd(0, ["nupd", [[this.conf.tnamedrange, this._sheet.getUid()], actCellCoords[0], actCellCoords[1], {refers_to: '='.concat(nrVal)}]]);
	}

	if (curBUID) {
		conn.ccmd(0, ['osel', 1, curBUID]);
		conn.ccmd(0, ['osel', 2, curSUID]);
	}

	if (this.conf.tvar.length > 0)
		conn.ccmd(null, ['svar', this.conf.tvar, this.conf.selval]);
};

clsRef.prototype._getMacroData = function() {
	return {
		id: this.conf.id,
		type: this.conf.type,
		name: this.conf.name,
		macros: this.conf.macros
	};
};

clsRef.prototype._assignMacro = function(data){
	Jedox.wss.wsel.assignMacro(data);
}

clsRef.prototype.showContextMenu = function (e, pos) {
	var that = this,
		contextMenu = new Ext.menu.Menu({
			id: 'formelContextMenu',
			enableScrolling: false,
    		listeners: {
				hide: function(menu){
					menu.destroy();
				}
			},
			items: [
			    {id: 'wFormElContext_edit_btn', text: 'formel_edit'.localize({type: this.conf.type}).concat('...'), iconCls: 'icon_edit', handler: function(){that.edit.call(that)}}
			    , {id: 'wFormElContext_del_btn', text: 'formel_delete'.localize({type: this.conf.type}), iconCls: 'icon_delete', handler: function(){that.remove.call(that)}}
			    , '-'
				, new Ext.menu.Item(
					{id: 'wFormElContext_bToFrnt_btn', text: "Bring to Front".localize(), iconCls: 'ico_bring_to_front', disabled: that.conf.locked, menu: {
							items: [
								{id: 'wFormElContextSub_bToFrnt_btn', text: "Bring to Front".localize(), iconCls: 'ico_bring_to_front', handler: function() {Jedox.wss.wsel.wselRegistry.bringToFront(that.conf.id);}},
								{id: 'wFormElContextSub_bForward_btn', text: "Bring Forward".localize(), iconCls: 'ico_bring_forward', handler: function() {Jedox.wss.wsel.wselRegistry.bringForward(that.conf.id);}}
							]
						}
					}
				)
				, new Ext.menu.Item(
					{id: 'wFormElContext_sToBack_btn', text: "Send to Back".localize(), iconCls: 'ico_send_to_back', disabled: that.conf.locked, menu: {
							items: [
								{id: 'wFormElContextSub_sToBack_btn', text: "Send to Back".localize(), iconCls: 'ico_send_to_back', handler: function() {Jedox.wss.wsel.wselRegistry.sendToBack(that.conf.id);}},
								{id: 'wFormElContextSub_sBackward_btn', text: "Send Backward".localize(), iconCls: 'ico_send_backward', handler: function() {Jedox.wss.wsel.wselRegistry.sendBackward(that.conf.id);}}
							]
						}
					}
				)
			    , {id: that.conf.locked ? 'wFormElContext_unlock_btn' : 'wFormElContext_lock_btn', text: (that.conf.locked ? 'Unlock'.localize() : 'Lock'.localize()).localize(), iconCls: 'icon_lock', handler: function(item, e) {
						item.setText((that.conf.locked ? 'Lock'.localize() : 'Unlock'.localize()).localize());

						for (var i = that._panes.length - 1; i >= 0; i--)
							that.setLock(!that.conf.locked, i, i);
					}
				}
			    , '-'
			    , {id: 'wFormElContext_assignMacro_btn', text: 'Assign Macro'.localize().concat('...'), iconCls: 'icon_macro', handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.insertMacro, [that._getMacroData.call(that), false, that._assignMacro]);}}
			]
		});

	var coords = e ? e.getXY() : (pos instanceof Array ? pos : [100, 100]);
	contextMenu.showAt([coords[0], coords[1]]);

	return contextMenu;
};

clsRef.prototype.remove = function() {
	var conn = Jedox.backend;

	// Remove Form Element component.
	for (var i = this._panes.length - 1; i >= 0; i--) {
		this.elem[i].destroy();
		this.wrapperEl[i].remove();
	}

	Jedox.wss.wsel.wselRegistry.remove(this._book, this._sheet._uid, this.conf.id);

	// Check for associated Named Range.
	if (this.conf.tnamedrange.length > 0)
		var ngetRes = conn.ccmd(0, ['nget', [1, 1, this.conf.tnamedrange, this._sheet.getUid()]])[0];

	conn.ccmdBuffer();

	// Remove associated Named Range if necessary.
	if (this.conf.tnamedrange.length > 0 && ngetRes[0])
		conn.ccmd(0, ['ndel', ngetRes[1][0].uuid]);

	// Remove Worksheet Element.
	conn.ccmd(0, ['wdel', '', [this.conf.id]]);

	conn.ccmdFlush(true, true);
};

clsRef.prototype.unload = function() {
	var env = this._env.shared,
		viewMode = Jedox.wss.grid.viewMode;

	try {
		for (var i = this._panes.length - 1, gridIC, contId; i >= 0; i--) {
			gridIC = this.panes[i].getIC();
			contId = this._panes[i]._domId;

			if (env.viewMode == viewMode.DESIGNER || env.viewMode == viewMode.PREVIEW) {
				this.elem[i].destroy();

				gridIC.removeChild(document.getElementById(contId.concat('_wsel_cont_', this.conf.id, '-rzwrap')));
				gridIC.removeChild(document.getElementById(contId.concat('_wsel_cont_', this.conf.id, '-rzwrap-rzproxy')));
			} else
				gridIC.removeChild(document.getElementById(contId.concat('_wsel_cont_', this.conf.id)));
		}
	} catch (e) {}
};

clsRef.prototype.assignMacro = function(macros) {
	var updObj = {};
	updObj[this.conf.id] = {
		macros: macros
	};

	if (!Jedox.backend.ccmd(0, ['wupd', '', updObj]))
		throw ['formel_assign_macro_err', {}];

	this.conf.macros = macros;
};

clsRef.prototype.isCmpMoved = function(comp) {
	if (this.isUserMode)
		return false;

	if (this.isMoved) {
		this.isMoved = false;
		return true;
	}

	var targetEl = comp.getEl().dom,
		targetId = this._panes[comp._paneId == undefined ? this._sheet._aPane._id : comp._paneId]._domId.concat('_wsel_cont_', this.conf.id, '-rzwrap');

	while (targetEl.id != targetId)
		targetEl = targetEl.parentNode;

	return targetEl.offsetTop != this.conf.top || targetEl.offsetLeft != this.conf.left;
};

clsRef.prototype.removize = function(data) {
	// TL cell.
	var pane = this._sheet._aPane,
		tlOffsetXY = pane.getPixelsByCoords(data.pos[0], data.pos[1]),
		newX = tlOffsetXY[0] + data.offsets[0],
		newY = tlOffsetXY[1] + data.offsets[1],
		setWH = false;

	this.conf.left = newX;
	this.conf.top = newY;

	if (!this.conf.singleCell) {
		var lrOffsetXY = pane.getPixelsByCoords(data.pos[2], data.pos[3]),
			newW = lrOffsetXY[0] + data.offsets[2] - newX,
			newH = (this.conf.fixedH) ? this.conf.height : lrOffsetXY[1] + data.offsets[3] - newY;

		if (newW != this.conf.width || newH != this.conf.height) {
			setWH = true;
			this.setCmpSize(newW, newH);
		}
	}

	for (var i = this.wrapperEl.length - 1, style; i >= 0; i--) {
		style = this.wrapperEl[i].dom.style;

		style.left = ''.concat(newX, 'px');
		style.top = ''.concat(newY, 'px');

		if (setWH) {
			if (newW != this.conf.width)
				style.width = ''.concat(newW, 'px');

			if (newH != this.conf.height)
				style.height = ''.concat(newH, 'px');
		}
	}
};

clsRef.prototype.setLock = function(locked, skipSave, paneId) {
	if (this.isUserMode)
		return;

	locked = locked !== false;
	var wrapper = this.wrapper[paneId];

	wrapper.dd.locked = locked;
	wrapper.enabled = !locked;
	wrapper.handles = locked ? 'none' : 'e w';

	if (!locked) {
		wrapper.east.el.dom.className = 'x-resizable-handle x-resizable-handle-east x-unselectable';
		wrapper.west.el.dom.className = 'x-resizable-handle x-resizable-handle-west x-unselectable';

		wrapper.east.el.dom.style.cursor = '';
		wrapper.west.el.dom.style.cursor = '';

		this.resCont[paneId].className = 'ws_element';
	} else {
		wrapper.east.el.dom.style.cursor = 'default';
		wrapper.west.el.dom.style.cursor = 'default';

		this.resCont[paneId].className = 'ws_element_locked';
	}

	if (!skipSave) {
		var updObj = {};
		updObj[this.conf.id] = {
			'locked': locked
		};

		Jedox.backend.ccmd(null, ['wupd', '', updObj]);
	}

	this.conf.locked = locked;
};

clsRef.prototype.afterResizeFormel = function (wrapper, newWidth, newHeight, e) {
	this.afterResize.call(this, wrapper, newWidth, newHeight, e);

	this.setCmpSize(this.conf.width, this.conf.height);
	wrapper.dynamic = !this.isUserMode;

	var wselData = {};
	wselData[this.conf.id] = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height, this.conf.singleCell);

	var conn = Jedox.backend;
	conn.ccmd(true, [ 'wupd', '', wselData ]);
};

clsRef = null;