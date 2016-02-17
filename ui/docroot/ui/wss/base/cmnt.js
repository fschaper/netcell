/*
 * @brief Cell Comment handlers
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: cmnt.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.wss.cmnt = new function()
{
	var that = this;
	this.defVals = {
		size: [130, 80]
		, pos: [9, 1]
		, title: 'Comment' // this string is localized when it's used
	};

	// *** PRIVATE *** //
	var _checkActiveTt = function(cellCoord)
	{
		var actSheet = Jedox.wss.app.activeSheet;
		if (!actSheet._dynCc)
		{
			actSheet._dynCc = {
				list:[],
				inEdit:false
			};

			var panes = actSheet._panes,
				dynList = actSheet._dynCc.list;
			for (var i=panes.length-1, pane; i>=0; i--)
			{
				pane = panes[i];
				dynList[i] = _createTt(cellCoord, false, pane);
			}
		}
	};

	var _getPosOffsets = function(cellCoord, tt)
	{
		var ttPos = tt.getPosition(true),
			pane = tt._pane,
			cTl = pane.getPixelsByCoords(cellCoord[0], cellCoord[1]),
			cS = pane.getCellDims(cellCoord[0], cellCoord[1]);

		return [ttPos[0] - cTl[0] - cS[0], ttPos[1] - cTl[1]];
	};

	var _createStaticTt = function(cellCoord, e_id, text, pos, size)
	{
		var actSheet = Jedox.wss.app.activeSheet,
			panes = actSheet._panes;

		for (var i=panes.length-1, pane, tt, cTl, cS; i>=0; i--)
		{
			pane = panes[i];

			tt = _createTt(cellCoord, true, pane);
			tt.showAtWithTextAndSize(cellCoord, text, size);
			tt._e_id = e_id;

			// update new position
			cTl = pane.getPixelsByCoords(cellCoord[0], cellCoord[1]);
			cS = pane.getCellDims(cellCoord[0], cellCoord[1]);

			tt.setPosition(cTl[0] + cS[0] + pos[0], cTl[1] + pos[1]);

			// added new static comment into register
			if (!actSheet._cmnts[e_id])
				actSheet._cmnts[e_id] = [];
			actSheet._cmnts[e_id][i] = tt;
		}
	};

	var _createTt = function(cellCrd, isStatic, currPane)
	{
		var ttTa = new Ext.form.TextArea({
				style: 'padding:0px;'
				, enableKeyEvents: true
				, listeners: {
					blur: function(thisTtTa)
					{
						if (tt._editMode)
						{
							var ttTaVal = thisTtTa.getValue();

							// tooltip setup
							tt._editMode = false;
							if (!tt._isStatic)
								Jedox.wss.app.activeSheet._dynCc.inEdit = false;

							// set data to core
							if (ttTaVal != '')
							{
								if (tt._checkVal != ttTaVal || tt._dirty)
								{
									tt._dirty = false;
									tt._checkVal = ttTaVal;

									var conn = Jedox.wss.app.activeBook._conn,
										updData = [tt._cellCoord[0], tt._cellCoord[1], tt._cellCoord[0], tt._cellCoord[1]],
										cmds = [],
										ttPos = _getPosOffsets(tt._cellCoord, tt);

									// static comment
									if (tt._isStatic)
									{
										// Update all Comment representations
										var tts = Jedox.wss.app.activeSheet._cmnts[tt._e_id];
										for (var i=tts.length-1; i>=0; i--)
											someTt = tts[i]._ttTa.setValue(ttTaVal);

										var ccWselUpd = {};
										ccWselUpd[tt._e_id] = { pos_offsets: ttPos, size: tt._size, t: ttTaVal };
										cmds[cmds.length] = ['wupd', '', ccWselUpd];
									}

									// add/update data
									var cell = tt._pane.getCell(tt._cellCoord[0], tt._cellCoord[1]);
									if (cell && (typeof cell == 'object') && cell.a && cell.a.cc)
									{
										cell.a.cc.t = ttTaVal;
										cell.a.cc.v = tt._isStatic;
										cell.a.cc.s = tt._size;
										cell.a.cc.p = ttPos;

										updData.push( { a: cell.a } );
										cmds[cmds.length] = ['cdrn', {cm: true}, updData];
										conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
									}
									else
									{
										// case when cell info is not stored in js and adding of new comment
										var updCell = function(res)
										{
											if ( (res instanceof Array) && res[0] && res[0][0] === true)
											{
												var attr = (res[0][1]) ? res[0][1][3].a : {cc: {}};
												if (!attr.cc)
													attr.cc = {};

												attr.cc.t = ttTaVal;
												attr.cc.v = tt._isStatic;
												attr.cc.s = tt._size;
												attr.cc.p = ttPos;

												updData.push( { a: attr } );
												cmds[cmds.length] = ['cdrn', {cm: true}, updData];
												conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
											}
										};
										conn.ccmd([this, updCell], [ 'grar', 16, updData[0], updData[1], updData[2], updData[3] ]);
									}
								}
							}
							else if (tt._checkVal != '')
								that.del(tt._cellCoord, currPane);
						}

						if (!tt._isStatic)
						{
							var dynList = Jedox.wss.app.activeSheet._dynCc.list;
							for (var i=dynList.length-1; i>=0; i--)
							{
								dynList[i].hide();
								dynList[i].disable();
							}
						}

						// return to grid mode
						Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputMode);
						Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
					}
					, focus: function()
					{
						if (tt._isStatic)
							tt._editMode = true;

						Jedox.wss.app.lastInputMode = Jedox.wss.app.environment.inputMode;
						Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.CNTRL);
					}
					, keydown: function(thisTtTa, e)
					{
						// stop of key propagation to grid (even it's in CNTRL input mode)
						e.stopPropagation();
					}
				}
			})
			, ttConf = {
				renderTo: currPane._domId.concat('_IC')
				, _editMode: false
				, _checkVal: ''
				, _ttTa: ttTa
				, _cellCoord: cellCrd
				, _size: that.defVals.size
				, _isStatic: !!isStatic
				, _pane: currPane
				, getAnchorPosition: function()
				{
					// locked to left
					this.tipAnchor = 'l';

					return 'left';
				}
				, setGoodSize: function(size)
				{
					if (this._diffW && this._diffH && this._resizer)
						this._resizer.resizeTo(size[0] + this._diffW, size[1] + this._diffH);
					else
					{
						this._size = size;
						ttTa.setSize(size[0], size[1]);

						// problem with Chrome
						if (Ext.isWebKit)
						{
							var stl = ttTa.getEl().getStyles('height', 'width');
							stl.height = ''.concat(size[1], 'px !important');
							ttTa.getEl().set({style: stl});
						}
					}
				}
				, showAtWithTextAndSize: function(cellCoord, text, size)
				{
					this._checkVal = text;
					this.setGoodSize(size);
					this._cellCoord = cellCoord;
					this.setTitle(Jedox.wss.app.numberToLetter[cellCoord[0]].concat(cellCoord[1], ' ', that.defVals.title.localize()));
					this._ttTa.setValue(text);
					this.show();

					// set Position
					var cTl = this._pane.getPixelsByCoords(cellCoord[0], cellCoord[1]),
						cS = this._pane.getCellDims(cellCoord[0], cellCoord[1]);
					this.setPosition(cTl[0] + cS[0] + that.defVals.pos[0], cTl[1] + that.defVals.pos[1]);
				}

				, target: currPane._domId.concat('_IC')
				, title: that.defVals.title.localize()

				, anchor: 'left'
				, autoHide: false
				, closable: true
				, draggable: {
					endDrag: function(e)
					{
						if (!tt._editMode && tt._isStatic)
						{
							var cell = tt._pane.getCell(tt._cellCoord[0], tt._cellCoord[1]),
								ttPos = _getPosOffsets(tt._cellCoord, tt),
								conn = Jedox.wss.app.activeBook._conn,
								cmds = [],
								updData = [tt._cellCoord[0], tt._cellCoord[1], tt._cellCoord[0], tt._cellCoord[1]],
								ccWselUpd = {};

							ccWselUpd[tt._e_id] = { pos_offsets: ttPos };
							cmds[cmds.length] = ['wupd', '', ccWselUpd];

							// Update position of all Comments
							that.moveTo(tt._e_id, tt._cellCoord, ttPos);

							if (cell)
							{
								if (cell.a.cc.p[0] != ttPos[0] || cell.a.cc.p[1] != ttPos[1])
								{
									cell.a.cc.p = ttPos;
									updData.push( { a: cell.a } );
									cmds[cmds.length] = ['cdrn', {cm: true}, updData];
									conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
								}
							}
							else
							{
								var updCell = function(res)
								{
									if ( (res instanceof Array) && res[0] && res[0][0] === true)
									{
										var attr = res[0][1][3].a;
										if (attr.cc.p[0] != ttPos[0] || attr.cc.p[1] != ttPos[1])
										{
											attr.cc.p = ttPos;

											updData.push( { a: attr } );
											cmds[cmds.length] = ['cdrn', {cm: true}, updData];
											conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
										}
									}
								};
								conn.ccmd([this, updCell], [ 'grar', 16, updData[0], updData[1], updData[2], updData[3] ]);
							}
						}
						else if (tt._editMode)
						{
							tt._dirty = true;

							// Update position of all Comments
							if (tt._isStatic)
								that.moveTo(tt._e_id, tt._cellCoord, _getPosOffsets(tt._cellCoord, tt));
						}
					}
				}
				, hidden: true

				, autoWidth: true
				, autoHeight: true

				, layout: 'fit'
				, items: [ ttTa ]

				, listeners: {
					show: function(thisTt)
					{
						if (thisTt.tools.close.isVisible())
							thisTt.tools.close.hide();
					}
					, render: function(thisTt)
					{
						// TODO: Fix resizing to be supported by all browsers
/*
						thisTt._resizer = new Ext.Resizable(thisTt.id, {
							handles: 'all'
							, pinned: false
							, dynamic: false
							, transparent: true
							, listeners: {
								resize: function(thisRszer, newW, newH, e)
								{
									thisTt._size = [ newW - thisTt._diffW, newH - thisTt._diffH ];
									thisTt.setSize(newW, newH);
									ttTa.setSize( newW - thisTt._diffW, newH - thisTt._diffH );

									// problem with Chrome
									if (Ext.isWebKit)
									{
										var stl = ttTa.getEl().getStyles('height', 'width');
										stl.height = ''.concat(newH - thisTt._diffH, 'px !important');
										ttTa.getEl().set( { style: stl } );
									}

									// if it's not in EditMode and it's static Comment - then It needs to be updated
								}
								, beforeresize: function()
								{
									if (!thisTt._diffW && !thisTt._diffH)
									{
										thisTt._diffW = thisTt.getWidth() - ttTa.getWidth();
										thisTt._diffH = thisTt.getHeight() - ttTa.getHeight();
									}
								}
							}
						});
*/
					}
				}
			}
			, tt = null;

		return (tt = new Ext.ToolTip(ttConf));
	};

	// *** PUBLIC *** //
	this.loadAll = function()
	{
		var _showSCCmnts = function(res)
		{
//			res = res[0];
			if ((res instanceof Array) && res[0] === true)
			{
				res = res[1];
				for (var i=res.length-1, ccData; i>=0; i--)
				{
					ccData = res[i];
					_createStaticTt(Jedox.wss.wsel.getRngFromNLoc(res[i].n_location), ccData.e_id, ccData.t, ccData.pos_offsets, ccData.size);
				}
			}
		};

		Jedox.wss.app.activeBook._conn.ccmd([this, _showSCCmnts], ['wget', '', [], ['e_id', 'n_location', 'pos_offsets', 'size', 'v', 't'], {e_type: 'sccmnt'}]);
	};

	this.moveTo = function(e_id, cellCoord, pos)
	{
		var actSheet = Jedox.wss.app.activeSheet,
			tts = actSheet._cmnts[e_id];
		if (tts)
		{
			var panes = actSheet._panes;
			for (var i=panes.length-1, pane, tt; i>=0; i--)
			{
				pane = panes[i];
				tt = tts[i];

				// Adjust cellCord value
				tt._cellCoord = cellCoord;
				tt.setTitle(Jedox.wss.app.numberToLetter[cellCoord[0]].concat(cellCoord[1], ' ', that.defVals.title.localize()) );

				// update new position
				cTl = pane.getPixelsByCoords(cellCoord[0], cellCoord[1]);
				cS = pane.getCellDims(cellCoord[0], cellCoord[1]);

				tt.setPosition(cTl[0] + cS[0] + pos[0], cTl[1] + pos[1]);
			}
		}
	};

	this.showComment = function(cellCoord, currPane)
	{
		if (currPane)
		{
			var cell = currPane.getCell(cellCoord[0], cellCoord[1]),
				dynCc = Jedox.wss.app.activeSheet._dynCc;

			if (typeof cell == 'object' && cell.a && cell.a.cc && cell.a.cc.t && !cell.a.cc.v)
			{
				_checkActiveTt(cellCoord);
				if (!dynCc)
					dynCc = Jedox.wss.app.activeSheet._dynCc;

				if (!dynCc.inEdit)
				{
					var dynList = dynCc.list;
					for (var i=dynList.length-1, dynCcRec; i>=0; i--)
					{
						dynElem = dynList[i];
						if (dynElem.isVisible())
						{
							dynElem.hide();
							dynElem.disable();
						}
						dynElem.showAtWithTextAndSize(cellCoord, cell.a.cc.t, cell.a.cc.s);
					}
				}
			}
			else if (dynCc && dynCc.list.length > 0 && dynCc.list[currPane._id].isVisible() && !dynCc.inEdit)
			{
				var dynList = dynCc.list;
				for (var i=dynList.length-1, dynCcRec; i>=0; i--)
				{
					dynElem = dynList[i];

					dynElem.hide();
					dynElem.disable();
				}
			}
		}
	};

	this.showOnMoveComment = function(cellCoord, currPane)
	{
		var as = Jedox.wss.app.activeSheet;

		if (as && (as._cmntMoveCCoord[0] != cellCoord[0] || as._cmntMoveCCoord[1] != cellCoord[1]))
		{
			as._cmntMoveCCoord = [cellCoord[0], cellCoord[1]];
			that.showComment(cellCoord, currPane);
		}
	};

	this.showOnOverComment = function(e, currPane)
	{
		var elCoords;
		if (!Jedox.wss.app.loaded)
			return;

		if (document.all)
			e = window.event;

		var el = (document.all) ? e.srcElement : e.target;
		if (el.tagName != 'DIV')
		{
			var panePos = currPane.holder.getPosition(),
				elPos = Ext.get(el).getXY(),
				parentPos = Ext.get(el.parentNode).getXY();

			elCoords = currPane.getNeighByOffset(1, 1, elPos[0] - parentPos[0] + 1, elPos[1] - parentPos[1] + 1);
		}
		else
			elCoords = currPane.getCoordsByCell(el);

		if (elCoords == undefined)
			return;

		that.showOnMoveComment(elCoords, currPane);
	};

	this.getContextMenu = function(cellCoord)
	{
		var cntx =  [ '-' ],
			aPane = Jedox.wss.app.activePane,
			cell = aPane.getCell(cellCoord[0], cellCoord[1]);

		if (typeof cell == 'object' && cell.a && cell.a.cc && cell.a.cc.t)
		{
			cntx.push( {text: "Edit Comment".localize(), handler: function(){ that.set(cellCoord, aPane); } } );
			cntx.push( {text: "Delete Comment".localize(), handler: function(){ that.del(cellCoord, aPane); } } );
			cntx.push( {text: ( (cell.a.cc.v) ? "Hide Comment".localize() : "Show/Hide Comment".localize() ), handler: function(){ that.showHide(cellCoord, aPane); } } );
		}
		else
			cntx.push( {text: "Insert Comment".localize(), handler: function(){ that.set(cellCoord, aPane); } } );

		return cntx;
	};

	this.set = function(cellCoord, currPane)
	{
		_checkActiveTt(cellCoord);

		var cell = currPane.getCell(cellCoord[0], cellCoord[1]),
			editText = '',
			ttSize = that.defVals.size,
			isStatic = false;
		if (typeof cell == 'object' && cell.a && cell.a.cc)
		{
			if (cell.a.cc.t)
				editText = cell.a.cc.t;

			if (cell.a.cc.s)
				ttSize = cell.a.cc.s;

			if (cell.a.cc.v && cell.a.cc.e_id)
				isStatic = true;
		}

		if (isStatic)
			Jedox.wss.app.activeSheet._cmnts[cell.a.cc.e_id][currPane._id]._ttTa.focus();
		else
		{
			var dynCc = Jedox.wss.app.activeSheet._dynCc,
				dynList = dynCc.list,
				cPaneId = currPane._id;

			dynList[cPaneId]._editMode = dynCc.inEdit = true;
			for (var i = dynList.length-1; i>=0; i--)
				dynList[i].showAtWithTextAndSize(cellCoord, editText, ttSize);
			dynList[cPaneId]._ttTa.focus();
		}
	};

	this.del = function(cellCoord, currPane)
	{
		var cell = currPane.getCell(cellCoord[0], cellCoord[1]),
			updData = [cellCoord[0], cellCoord[1], cellCoord[0], cellCoord[1]],
			conn = Jedox.wss.app.activeBook._conn,
			isStatic = ( (cell && cell.a.cc.v && cell.a.cc.e_id) || !cell ),
			cmds = [];

		// remove Ext added 'id' attribute
//		currPane.getCellByCoords(cellCoord[0], cellCoord[1]).removeAttribute('id');

		// destroy tooltip for static comment and remove wsel
		if (isStatic && cell)
		{
			var asCs = Jedox.wss.app.activeSheet._cmnts,
				e_id = cell.a.cc.e_id,
				tts = asCs[e_id];

			cmds[cmds.length] = [ 'wdel', '', [e_id] ];

			for (var i=tts.length-1, tt; i>=0; i--)
			{
				tt = tts[i];

				tt.hide();
				tt.disable();
				tt.destroy();
			}
			delete asCs[e_id];
		}
		else if (!isStatic)
		{
			var dynList = Jedox.wss.app.activeSheet._dynCc.list;
			for (var i=dynList.length-1; i>=0; i--)
				dynList[i].disable();
		}

		// update cell attribute
		if (cell)
		{
			cell.a.cc = '';
			updData.push( { a: cell.a } );
			cmds[cmds.length] = ['cdrn', {cm: true}, updData];
			conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
		}
		else
		{
			// case when cell info is not stored in js
			var updCell = function(res)
			{
				if ( (res instanceof Array) && res[0] && res[0][0] === true)
				{
					var attr = res[0][1][3].a;

					if (isStatic)
					{
						var asCs = Jedox.wss.app.activeSheet._cmnts,
							e_id = attr.cc.e_id,
							tts = asCs[e_id];

						cmds[cmds.length] = [ 'wdel', '', [e_id] ];

						for (var i=tts.length-1, tt; i>=0; i--)
						{
							tt = tts[i];

							tt.hide();
							tt.disable();
							tt.destroy();
						}
						delete asCs[e_id];
					}

					attr.cc = '';
					updData.push( { a: attr } );
					cmds[cmds.length] = ['cdrn', {cm: true}, updData];
					conn.ccmd(null, cmds, true, conn.Q_ATTRS, conn.D_NONE);
				}
			};
			conn.ccmd([this, updCell], [ 'grar', 16, updData[0], updData[1], updData[2], updData[3] ]);
		}
	};

	this.showHide = function(cellCoord, currPane)
	{
		var cell = currPane.getCell(cellCoord[0], cellCoord[1]),
			updData = [cellCoord[0], cellCoord[1], cellCoord[0], cellCoord[1]],
			conn = Jedox.wss.app.activeBook._conn;

		if (typeof cell == 'object' && cell.a && cell.a.cc && cell.a.cc.t && cell.a.cc.v && cell.a.cc.e_id)
		{
			cell.a.cc.v = false;
			if (Jedox.wss.app.activeSheet._cmnts[cell.a.cc.e_id])
			{
				var asCs = Jedox.wss.app.activeSheet._cmnts,
					e_id = cell.a.cc.e_id,
					tts = asCs[e_id];

				for (var i=tts.length-1, tt; i>=0; i--)
				{
					tt = tts[i];

					tt.hide();
					tt.disable();
					tt.destroy();
				}
				delete asCs[e_id];
			}

			// update data to core and remove wsel for sccmnt
			updData.push( { a: cell.a } );
			conn.ccmd(null, [ ['cdrn', {cm: true}, updData], ['wdel', '', [cell.a.cc.e_id]] ], true, conn.Q_ATTRS, conn.D_NONE);

			delete cell.a.cc.e_id;
		}
		else
		{
			cell.a.cc.v = true;

			// disable dynamic tooltip (because last dynamic was on new static cell and it makes automatic show when mouse over that cell)
			var dynList = Jedox.wss.app.activeSheet._dynCc.list;
			for (var i=dynList.length-1; i>=0; i--)
				dynList[i].disable();

			// add wsel and update cell attribute
			var _updCell = 	function(res)
				{
					if ((res instanceof Array) && (res[0] instanceof Array) && res[0][0] === true)
					{
						_createStaticTt(cellCoord, res[0][1][0], cell.a.cc.t, cell.a.cc.p, cell.a.cc.s);

						cell.a.cc.e_id = res[0][1][0];
						updData.push( { a: cell.a } );
						conn.ccmd(null, ['cdrn', {cm: true}, updData], true, conn.Q_ATTRS, conn.D_NONE);
					}
				},
				cellId = '$'.concat(Jedox.wss.app.numberToLetter[cellCoord[0]], '$', cellCoord[1]);

			conn.ccmd([this, _updCell], ['wadd', '', {
				e_type: 'sccmnt'
				, n_location: '='.concat(cellId, ':', cellId)
				, pos_offsets: cell.a.cc.p
				, size: cell.a.cc.s
				, v: cell.a.cc.v
				, t: cell.a.cc.t
			}]);
		}
	};
}
