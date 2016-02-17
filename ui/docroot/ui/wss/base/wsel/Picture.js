/*
 * \brief pictures handling code
 *
 * \file Picture.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: Picture.js 5160 2011-07-29 13:00:33Z predragm $
 *
 */

Jedox.wss.wsel.img = new function() {

	this.moveTo = function(imgId, pos, offsets) {
		var img = Jedox.wss.wsel.wselRegistry.get(Jedox.wss.app.activeBook, Jedox.wss.app.activeSheet._uid, imgId),
			tlOffsetXY = img._sheet._aPane.getPixelsByCoords(pos[0], pos[1]),
			newX = tlOffsetXY[0] + offsets[0],
			newY = tlOffsetXY[1] + offsets[1];

		for (var i = img.wrapper.length - 1, wrpEl; i >= 0; i--)
			(img.isUserMode ? img.wrapper[i].getEl() : img.wrapperEl[i]).setLeftTop(''.concat(newX, 'px'), ''.concat(newY, 'px'));
	};

	this.showAlert = function(title, msg) {
		Ext.Msg.alert(title.localize(), msg.localize());
	};

	this.loadAll = function() {
		function _load (res) {
			if (!(res instanceof Array) || res[0] !== true)
				return;

			res = res[1];

			var jwwsel = Jedox.wss.wsel,
				activePane = Jedox.wss.app.activePane;

			for (var imgData, i = res.length - 1, rng, tlXY; i >= 0; --i) {
				imgData = res[i];

				rng = jwwsel.getRngFromNLoc(imgData.n_location);
				tlXY = activePane.getPixelsByCoords(rng[0], rng[1]);

				this.createImg(imgData.e_id, tlXY[1] + imgData.pos_offsets[1], tlXY[0] + imgData.pos_offsets[0], imgData.size[0], imgData.size[1], false, imgData.zindex, imgData.locked, imgData.hl, imgData.img_name);
			}
		}

		Jedox.backend.ccmd([this, _load], ['wget', '', [], ['e_id', 'n_location', 'pos_offsets', 'size', 'zindex', 'locked', 'hl', 'img_name'], {e_type: 'img'}]);
	};

	this.remove = function(imgId) {
		var img = Jedox.wss.wsel.wselRegistry.get(Jedox.wss.app.activeBook, Jedox.wss.app.activeSheet._uid, imgId);

		if (img)
			img.remove(true);
	};

	this.createImg = function(imgId, elTop, elLeft, elWidth, elHeight, setLoc, zindex, locked, hldata, name) {
		Jedox.wss.wsel.wselRegistry.add(new Jedox.wss.wsel.Picture(imgId, elTop, elLeft, elWidth, elHeight, setLoc, zindex, locked, hldata, name));
	};
};

Jedox.wss.wsel.Picture = (function () {

	// private static fields
	var type = 'Picture';

	// class constructor
	return function (imgId, elTop, elLeft, elWidth, elHeight, setLoc, zindex, locked, hldata, name) {
		Jedox.wss.wsel.Picture.parent.constructor.call(this, {
			id: imgId,
			name: name,
			type: type,
			zindex: zindex,
			locked: locked,
			top: elTop,
			left: elLeft,
			width: elWidth,
			height: elHeight,

			setLoc: setLoc,
			hl: hldata
		});

		var convObj = {},
			dims = Jedox.wss.wsel.Picture.dims;

		if (this.conf.id == null) {
			Ext.MessageBox.show({
				title: 'Operation Error'.localize(),
				msg: 'imgDlg_genError'.localize(),
				buttons: Ext.MessageBox.OK,
				icon: Ext.MessageBox.ERROR
			});

			return;
		}

		if (this.conf.name == undefined || !this.conf.name.length) {
			this.generateName();
			convObj.img_name = this.conf.name;
		}

		if (this.conf.zindex == undefined) {
			this.conf.zindex = Jedox.wss.wsel.wselRegistry.getZIndex();
			convObj.zindex = this.conf.zindex;
		}

		if (this.conf.locked == undefined) {
			this.conf.locked = Jedox.wss.wsel.Picture.defLockedState;
			convObj.locked = this.conf.locked;
		}

		for (var conv in convObj) {
			var updObj = {};
			updObj[this.conf.id] = convObj;

			Jedox.backend.ccmd([this, function() {}], ['wupd', '', updObj]);
			break;
		}

		this.conf.zindex = parseInt(this.conf.zindex);
		this.conf.locked = ( this.conf.locked && this.conf.locked !== 'false' && this.conf.locked !== 'FALSE' );

		// Create Picture.
		var currDate = new Date();

		this.resCont = [];
		this.wrapper = [];

		if (!this.isUserMode)
			this.wrapperEl = [];

		// Create presentation for each pane.
		for (var i = 0, panesLen = this._panes.length, gridDivId, elContId, pane, contId; i < panesLen; i++) {
			pane = this._panes[i];
			contId = pane._domId;
			gridDivId = contId.concat('_IC');
			elContId = contId.concat('_wsel_cont_', this.conf.id);

			this.calcConstraints(pane);

			this.resCont[i] = Ext.DomHelper.insertFirst(
				Ext.DomQuery.selectNode('div[id=' + gridDivId + ']'),
				{
					tag: 'img',
					id: elContId,
					src: '/be/wss/gen_element.php?wam='.concat(
						Jedox.wss.app.appModeS,
						'&buid=', this._book.uid,
						'&suid=', this._sheet.getUid(),
						'&t=img',
						'&id=', this.conf.id,
						'&ts=', currDate.getTime()
					),
					width: this.conf.width,
					height: this.conf.height,
					cls: ((this.conf.locked || this.isUserMode) ? ((this.conf.hl || this.isUserMode) ? 'ws_element_locked_hyperlink' : 'ws_element_locked') : 'ws_element'),
					style: 'z-index: '.concat(this.conf.zindex, '; position: absolute; left:', this.conf.left, 'px; top:', this.conf.top, 'px;')
				},
				false
			);

			this.wrapper[i] = new Ext.ux.ResizableConstrained(elContId, {
				wrap: !this.isUserMode,
				dynamic: !this.isUserMode,
				pinned: false,
				width: this.conf.width,
				height: this.conf.height,
				minWidth: dims.minW,
				maxWidth: this.elConstr[i].lrCornerPx[0],
				minHeight: dims.minH,
				maxHeight: this.elConstr[i].lrCornerPx[1],
				preserveRatio: true,
				defaultRatio: true,
				transparent: false,
				handles: (document.all && this.isUserMode) ? 'none' : 'all',
				draggable: !this.isUserMode,
				enabled: !this.isUserMode,
				style: 'background-color: white;',
				resizeRegion: Ext.get(gridDivId).getRegion(),
				_paneId: i
			});

			// Add Tooltips for Hyperlink
			if (this.conf.hl)
				this.setHlTooltip(i);

			if (!this.isUserMode) {
				this.wrapper[i].on({
					'resize': {fn: this.afterResize, scope: this},
					'beforeresize': {fn: this.beforeResize, scope: this}
				});

				this.wrapper[i].dd.maintainOffset = true;
				this.wrapper[i].setXConstraint(this.elConstr[i].left, this.elConstr[i].right);
				this.wrapper[i].setYConstraint(this.elConstr[i].up, this.elConstr[i].down);

				this.wrapperEl[i] = this.wrapper[i].getEl();
				this.wrapperEl[i].dom.style.backgroundColor = '#FFFFFF';
				this.wrapperEl[i].dom.style.zIndex = this.conf.zindex;

				this.wrapperEl[i].on({
					'mousedown': {fn: this.onImgMouseDown, scope: this, options: {paneId: i}},
					'dblclick': {fn: this.edit, scope: this}
				});

				if (this.conf.locked)
					this.setLock(true, true, i);
			} else {
				var eHndls = {'mousedown': {fn: this.onMouseDownUM, scope: this, options: {paneId: i}}};

				if (this.conf.hl)
					eHndls['click'] = { fn: function() { Jedox.wss.hl.follow(null, this.conf.hl); }, scope: this };

				this.wrapper[i].getEl().on(eHndls);
			}
		}

		if (!this.conf.setLoc)
			return;

		var conn = Jedox.backend,
			imgData = {};

		imgData[this.conf.id] = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, this.conf.width, this.conf.height);
		conn.ccmd(true, [ 'wupd', '', imgData ]);
	}
}
)();

// Picture extends Base
Jedox.util.extend(Jedox.wss.wsel.Picture, Jedox.wss.wsel.Base);

//public fields
Jedox.wss.wsel.Picture.defLockedState = false;
Jedox.wss.wsel.Picture.dims = {minW: 10, minH: 10, maxW: 1600, maxH: 1050};

//public methods

clsRef = Jedox.wss.wsel.Picture;

clsRef.prototype.onImgMouseDown = function(e, t, o) {
	this._env.shared.inputField.blur();

	if (!(e.button == 2 || (Ext.isMac && e.button == 0 && Jedox.wss.app.ctrlKeyPressed) || (Ext.isWebKit && e.button == 1))) {
		var bEv = e.browserEvent,
			el = document.all ? bEv.srcElement : bEv.target;

		el.className = this.conf.locked ? (this.conf.hl ? 'ws_element_locked_hyperlink' : 'ws_element_locked') : 'ws_element_move';

		if (this.conf.hl && this.conf.locked) {
			if (Jedox.wss.app.activeBook.id != this._book.id)
				Jedox.wss.book.selectById(this._book.id);

			if (Jedox.wss.app.activePane._id != o.options.paneId)
				this._panes[o.options.paneId].select();

			Jedox.wss.hl.follow(null, this.conf.hl);
			return;
		}
	}

	this.onMouseDown.call(this, e, t, o, this.onImgMouseUp);
};

clsRef.prototype.onImgMouseUp = function(e) {
	if (!this.handleElementMove)
		return;

	var	el = (document.all) ? e.srcElement : e.target,
		follHL = false;

	el.className = this.conf.locked ? (this.conf.hl ? 'ws_element_locked_hyperlink' : 'ws_element_locked') : 'ws_element';

	if (this.conf.hl && !this.conf.locked) {
		var size = this.getSize(),
			pos = this.getPosition(this._sheet._aPane._id),
			newLeft = pos[0],
			newTop = pos[1],
			elW = size.width,
			elH = size.height;

		// snap to grid if Alt key is pressed
		if (e.altKey) {
			var newXY = Jedox.wss.wsel.getSnapXY(newLeft, newTop, elW, elH);

			newLeft = newXY[0];
			newTop = newXY[1];
		}

		if (this.conf.hl && !this.conf.locked && newLeft == this.conf.left && newTop == this.conf.top) {
			follHL = true;
			Jedox.wss.hl.follow(null, this.conf.hl);
		}
	}

	this.onMouseUp.call(this, e, this.onImgMouseUp, follHL);
};

clsRef.prototype.edit = function() {
	Jedox.wss.dlg.openInsertPicture({id: this.conf.id, zindex: this.conf.zindex, locked: this.conf.locked, hldata: this.conf.hl});
};

clsRef.prototype.beforeResize = function(wrapper, e) {
	Jedox.wss.app.activeWrapper = wrapper;

	if (e.shiftKey)
		wrapper.preserveRatio = false;
};

clsRef.prototype.afterResize = function(wrapper, newWidth, newHeight, e) {
	var pRatio = wrapper.preserveRatio;
	if (Jedox.wss.app.activeWrapper) {
		wrapper.preserveRatio = true;
		delete Jedox.wss.app.activeWrapper;
	}

	var wrapperEl = wrapper.getEl(),
		newLeft = wrapperEl.getLeft(true),
		newTop = wrapperEl.getTop(true),
		paneId = wrapper._paneId == undefined ? this._sheet._aPane._id : wrapper._paneId,
		pane = this._panes[paneId],
		defMaxCoords = Jedox.wss.grid.defMaxCoords,
		lrCornerPx = pane.getPixelsByCoords(defMaxCoords[0] + 1, defMaxCoords[1] + 1),
		badPS = false;

	// check is image inside grid
	if (newLeft < 0) {
		newWidth += newLeft;
		newLeft = 0;
		badPS = true;
	}

	if (newTop < 0) {
		newHeight += newTop;
		newTop = 0;
		badPS = true;
	}

	if (newLeft + newWidth > lrCornerPx[0]) {
		newWidth = lrCornerPx[0] - newLeft;
		badPS = true;
	}

	if (newTop + newHeight > lrCornerPx[1]) {
		newHeight = lrCornerPx[1] - newTop;
		badPS = true;
	}

	// snap to grid
	if (e.browserEvent.altKey) {
		var newPS = Jedox.wss.wsel.getSnapXYandWH(this.conf.left, this.conf.top, this.conf.width, this.conf.height, newLeft, newTop, newWidth, newHeight, 3, pRatio);

		badPS = badPS || (newWidth != newPS[2]) ||  (newHeight != newPS[3]);

		newLeft = newPS[0];
		newTop = newPS[1];
		newWidth = newPS[2];
		newHeight = newPS[3];

		badPS = badPS || (this.conf.left != newLeft) || (this.conf.top != newTop);
	}

	// update img position data
	this.conf.left = newLeft;
	this.conf.top = newTop;

	for (var i = this.elConstr.length - 1; i >= 0; i--) {
		if (this.conf.width != newWidth)
			this.elConstr[i].right += this.conf.width - newWidth;

		if (this.conf.height != newHeight)
			this.elConstr[i].down += this.conf.height - newHeight;
	}

	this.conf.width = newWidth;
	this.conf.height = newHeight;

	if (badPS)
		this.setPositionSize({left: this.conf.left, top: this.conf.top, width: newWidth, height: newHeight}, paneId);
	else {
		for (var i = this._panes.length - 1; i >= 0; i--)
			if (i != paneId) {
				wrpEl = this.wrapperEl[i];

				// resize
				Ext.get(this.resCont[i]).setSize(this.conf.width, this.conf.height);
				wrpEl.setSize(this.conf.width, this.conf.height);

				// move
				wrpEl.dom.style.left = ''.concat(this.conf.left, 'px');
				wrpEl.dom.style.top = ''.concat(this.conf.top, 'px');
			}

		var conn = Jedox.backend,
			imgData = {};

		imgData[this.conf.id] = Jedox.wss.wsel.getNLoc(this.conf.left, this.conf.top, newWidth, newHeight);
		imgData[this.conf.id].size = [ newWidth, newHeight ];

		conn.ccmd(true, [ 'wupd', '', imgData ]);
	}
};

clsRef.prototype.setPositionSize = function(newDims, paneId) {
	if (paneId == undefined)
		paneId = this._sheet._aPane._id;

	var wrpEl = this.wrapperEl[paneId],
		newL = newDims.left,
		newT = newDims.top
		newW = newDims.width,
		newH = newDims.height;

	if (this.conf.left != newL || this.conf.top != newT || wrpEl.getWidth(true) != newW || wrpEl.getHeight(true) != newH) {
		for (var i = this._panes.length - 1; i >= 0; i--) {
			wrpEl = this.wrapperEl[i];

			// resize
			Ext.get(this.resCont[i]).setSize(newW, newH);
			wrpEl.setSize(newW, newH);

			// move
			wrpEl.dom.style.left = ''.concat(newL, 'px');
			wrpEl.dom.style.top = ''.concat(newT, 'px');
		}

		// set internal values
		this.conf.left = newL;
		this.conf.top = newT;

		// update data in core
		var imgData = {};

		imgData[this.conf.id] = Jedox.wss.wsel.getNLoc(newL, newT, newW, newH);
		imgData[this.conf.id].size = [newW, newH];

		Jedox.backend.ccmd(true, [ 'wupd', '', imgData ]);
	}
};

// get picture properties (id, size and position)
clsRef.prototype.getPropsData = function() {
	var wrpEl = this.wrapperEl[this._sheet._aPane._id],
		props = {
			scope: this,
			psHnd: this.setPositionSize,
			w: wrpEl.getWidth(true),
			h: wrpEl.getHeight(true),
			t: parseInt(wrpEl.dom.style.top.replace(/px/i, "")),
			l: parseInt(wrpEl.dom.style.left.replace(/px/i, ""))
	};

	return props;
};

clsRef.prototype.remove = function(presOnly) {
	var cbRemove = function(res) {
		if (res instanceof Array && (res = res[0]) instanceof Array && res[0] === true) {
			for (var i = this._panes.length - 1, rzwrap; i >= 0; i--) {
				this.wrapperEl[i].remove();

				rzwrap = document.getElementById(this._panes[i]._domId.concat('_wsel_cont_', this.conf.id, '-rzwrap-rzproxy'));

				if (rzwrap != null)
					rzwrap.parentNode.removeChild(rzwrap);
			}

			Jedox.wss.wsel.wselRegistry.remove(this._book, this._sheet._uid, this.conf.id);
		} else {
			Ext.MessageBox.show({
				title: 'Operation Error'.localize(),
				msg: 'imgDlg_deleteError'.localize(),
				buttons: Ext.MessageBox.OK,
				icon: Ext.MessageBox.ERROR
			});
		}
	}

	if (presOnly === true)
		cbRemove.call(this, [[true]]);
	else
		Jedox.backend.ccmd([this, cbRemove], ['wdel', '', [this.conf.id]]);
};

clsRef.prototype.showContextMenu = function(e, paneId, pos) {
	if (this.isUserMode && !Jedox.wss.app.isIE)
		return;

	var contextMenu = new Ext.menu.Menu({
		items: this.isUserMode ? [] : [
			{id: 'wPictureContext_edit_btn', text: "Edit Picture".localize().concat('...'), iconCls: 'icon_edit', scope: this, handler: this.edit},
			'-',
			new Ext.menu.Item(
				{id: 'wPictureContext_bToFrnt_btn', text: "Bring to Front".localize(), iconCls: 'ico_bring_to_front', disabled: this.conf.locked, menu: {
						items: [
							{id: 'wPictureContextSub_bToFrnt_btn', text: "Bring to Front".localize(), iconCls: 'ico_bring_to_front', scope: this, handler: function() {Jedox.wss.wsel.wselRegistry.bringToFront(this.conf.id);}},
							{id: 'wPictureContextSub_bFwd_btn', text: "Bring Forward".localize(), iconCls: 'ico_bring_forward', scope: this, handler: function() {Jedox.wss.wsel.wselRegistry.bringForward(this.conf.id);}}
						]
					}
				}
			),
			new Ext.menu.Item(
				{id: 'wPictureContext_sToBck_btn', text: "Send to Back".localize(), iconCls: 'ico_send_to_back', disabled: this.conf.locked, menu: {
						items: [
							{id: 'wPictureContextSub_sToBack_btn', text: "Send to Back".localize(), iconCls: 'ico_send_to_back', scope: this, handler: function() {Jedox.wss.wsel.wselRegistry.sendToBack(this.conf.id);}},
							{id: 'wPictureContextSub_sBckwd_btn', text: "Send Backward".localize(), iconCls: 'ico_send_backward', scope: this, handler: function() {Jedox.wss.wsel.wselRegistry.sendBackward(this.conf.id);}}
						]
					}
				}
			),
			{id: this.conf.locked ? 'wPictureContext_unlock_btn' : 'wPictureContext_lock_btn', text: (this.conf.locked ? 'Unlock' : 'Lock').localize(), iconCls: 'icon_lock', scope: this, handler: function(item, e) {
					item.setText((this.conf.locked ? 'Lock' : 'Unlock').localize());

					for (var i = this._panes.length - 1; i >= 0; i--)
						this.setLock(!this.conf.locked, i, i);
				}
			},
			'-',
			{id: 'wPictureContext_del_btn', text: "Delete Picture".localize(), iconCls: 'icon_delete', scope: this, handler: this.remove}
		].concat(Jedox.wss.hl.getContextMenu({
					defName: "Picture Hyperlink".localize(),
					data: this.conf.hl,
					withOpen: true,
					handlers: {
						scope: this,
						set: this.setHl,
						remove: this.removeHl
					}
				}),
				'-',
				{id: 'wPictureContext_prop_btn', text: "Properties".localize(), iconCls: 'icon_edit', scope: this, handler: function(){Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pictureProperties, [this.getPropsData()]);}}
		),
		enableScrolling: false,
		cls: 'default-format-window',
		listeners: {
			hide: function(menu){
				menu.destroy();
			}
		}
	});

	if (Jedox.wss.app.isIE)
		contextMenu.insert(this.isUserMode ? 0 : 6, new Ext.menu.Item({id: 'wChartContext_cpToClp_btn', text: 'Copy to Clipboard'.localize(), iconCls: 'icon_copy', scope: this, handler: function() {this.copyToClipboard(paneId);}}));

	var coords = e ? e.getXY() : (pos instanceof Array ? pos : [100, 100]);
	contextMenu.showAt([coords[0], coords[1]]);
};

clsRef.prototype.setLock = function(locked, skipSave, paneId) {
	if (this.isUserMode)
		return;

	locked = locked !== false;

	Jedox.wss.wsel.setLock(this.conf.id, this.wrapper[paneId], this.resCont[paneId], locked, skipSave);
	this.conf.locked = locked;

	if (this.conf.locked && this.conf.hl)
		this.resCont[paneId].className = 'ws_element_locked_hyperlink';
};

//clsRef.prototype.getPos = function (type) {
//	var paneId = this._sheet._aPane._id,
//		wrpEl = this.wrapperEl[paneId] || this.wrapper[paneId].getEl();
//
//	return wrpEl[type ? 'getTop' : 'getLeft'](true);
//};
//
//clsRef.prototype.getSize = function (type) {
//	var paneId = this._sheet._aPane._id,
//		wrpEl = this.wrapperEl[paneId] || this.wrapper[paneId].getEl();
//
//	return wrpEl[type ? 'getHeight' : 'getWidth'](true);
//};

clsRef.prototype.getSize = function() {
	var paneId = this._sheet._aPane._id,
		wrpEl = this.wrapperEl[paneId] || this.wrapper[paneId].getEl();

	return wrpEl.getSize(true);
};

clsRef.prototype.setHl = function(hldata) {
	this.conf.hl = hldata;

	for (var i = this.resCont.length - 1; i >= 0; i--) {
		this.setHlTooltip(i);

		if (this.conf.locked)
			this.resCont[i].className = (this.conf.hl) ? 'ws_element_locked_hyperlink' : 'ws_element_locked';
	}

	var imgData = {};
	imgData[this.conf.id] = { hl: hldata };
	Jedox.backend.ccmd(true, [ 'wupd', '', imgData ]);
};

clsRef.prototype.removeHl = function() {
	this.setHl.call(this, null);
};

clsRef.prototype.setHlTooltip = function(paneId) {
	var imgElem = Ext.get(this.resCont[paneId]);

	if (this.conf.hl) {
		imgElem.on('mouseenter', this.hlTtipSet, this);
		imgElem.on('mouseleave', this.hlTtipRemove, this);
	} else {
		imgElem.un('mouseenter', this.hlTtipSet, this);
		imgElem.un('mouseleave', this.hlTtipRemove, this);
	}
};

clsRef.prototype.hlTtipSet = function(ev, evTarget, optObj) {
	ev.clientX = ev.getPageX();
	ev.clientY = ev.getPageY();

	Jedox.wss.hl.setToolTip(ev, this.conf.hl, true);
};

clsRef.prototype.hlTtipRemove = function(ev, evTarget, optObj) {
	ev.clientX = ev.getPageX();
	ev.clientY = ev.getPageY();

	Jedox.wss.hl.setToolTip(ev, this.conf.hl, false);
};

clsRef = null;