/*
 * \brief scrollbar abstract base class
 *
 * \file Scrollbar.js
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 *
 * \version
 * SVN: $Id: Scrollbar.js 5028 2011-06-02 14:34:20Z predragm $
 *
 */

Jedox.wss.grid.Scrollbar = (function ()
{
	return function (book, dom)
	{
		this._book = book; this.dom = dom; this._domId = dom.id;

		this._defScrollSpeed = Jedox.wss.grid.defDefScrollSpeed; this._currScrollSpeed = 0;
		this._doCheck = false; this._tid_start = 0; this._tid_reach = 0;

		this._genContentEl();

		this._bg = document.getElementById(this._domId.concat('_bg'));
		this._sliderFills = [ document.getElementById(this._domId.concat('_begf')), document.getElementById(this._domId.concat('_endf')) ];
		this._sliderCenter = document.getElementById(this._domId.concat('_midf'));
		this._sliderSize = 0; this._sliderTicks = 0;

		this._flattenedCenterElem = false; this._sliderThumbSize = 0;
		this._scrollSpace = 0; this._scrollSpaceCorr = 0;

		var that = this;

		var rwd = document.getElementById(this._domId.concat('_rwd'));
		rwd.onmousedown = function () { that._rwd_omd(); };
		rwd.onmouseup = function () { that.stop(); };
		rwd.onmouseout = function () { that.stop(); };

		var fwd = document.getElementById(this._domId.concat('_fwd'));
		fwd.onmousedown = function () { that._fwd_omd(); };
		fwd.onmouseup = function () { that.stop(); };
		fwd.onmouseout = function () { that.stop(); };
	};
}
)();

// public static fields

// public fields & methods
Jedox.wss.grid.Scrollbar.prototype = {

	  _HORIZ: 0
	, _VERT: 1
	, _RWD: -1
	, _FWD: 1

	, _switch: function (panes, size)
	{
		this._panes = panes;

		if (!panes)
		{
			this._numPanes = 0;
			this._refPane = undefined;
			this._resize(0);

			return;
		}

		this._numPanes = panes.length;
		this._refPane = panes[0];

		var paneProp = this._paneProp;

		for (var i = this._numPanes - 1; i >= 0; --i)
			panes[i][paneProp] = this;

		this._resize(size);
	}

	, _scroll: function (offset, destCellAbs, cb)
	{
		var book = this._book,
				sheet = this._refPane._sheet,
				paneScroll = this._paneScroll,
				res;

		// cancel curr rqst
		if (sheet._loadRqst)
		{
			sheet._loadRqst.abort(true);

			delete sheet._loadRqst;
		}

		clearTimeout(this._tid_scroll);

		// if one pane
		if (this._numPanes == 1)
		{
			res = this._refPane[paneScroll](offset, destCellAbs, cb);

			if (res == undefined)
				return;

			if (res instanceof Array)
				res[1].apply(res[0], res.slice(2));
			else
			{
				res.setHdr('X-WSS-Book', book.getUidSgn());

				this._tid_scroll = setTimeout(function () { res.send(); sheet._loadRqst = res; }, 200);
				this._scheduled = true;
			}

			return;
		}

		// multi-pane
		var panes = this._panes,
				rqsts = [],
				cbs = [];

		for (var i = this._numPanes - 1; i >= 0; --i)
		{
			res = panes[i][paneScroll](offset, destCellAbs);

			if (res == undefined)
				continue;

			if (res instanceof Array)
				cbs.push(res);
			else
				rqsts.push(res);
		}

		// no rqsts needed
		if (!rqsts.length)
		{
			for (var cbs_c, i = cbs.length - 1; i >= 0; --i)
			{
				cbs_c = cbs[i];
				cbs_c[1].apply(cbs_c[0], cbs_c.slice(2));
			}

			if (cb instanceof Array && cb.length > 1)
				cb[1].apply(cb[0], cb.slice(2));

			return;
		}

		// schedule batch
		this._tid_scroll = setTimeout(function ()
		{
			var batch = new Jedox.backend.CCmdAsyncBatch(false, true);

			batch.add.apply(batch, rqsts);

			for (var i = cbs.length - 1; i >= 0; --i)
				batch.add((new Jedox.backend.CCmdAsyncRqst([ 'gsi' ])).setOnSuccess([ batch, function (res, cb) { cb[1].apply(cb[0], cb.slice(2)); }, cbs[i] ]));

			batch.setOnSuccess(cb);
			batch.setHdr('X-WSS-Book', book.getUidSgn());

			batch.send();
			sheet._loadRqst = batch;
		}, 200);

		this._scheduled = true;
	}

	, check: function ()
	{
		if (!this._refPane)
			return false;

		var type = this._type;

		if (this._refPane._farthestSeenCell[type] > this._refPane._sheet._farthestUsedCell[type] && this._refPane._lastDestCell[type] + this._refPane._cppi[type] < this._refPane._farthestSeenCell[type])
			this._refPane._farthestSeenCell[type] = Math.max(this._refPane._sheet._farthestUsedCell[type], this._refPane._lastDestCell[type] + this._refPane._cppi[type], this._refPane._minCoords[type] + this._refPane._cppi[type] + 1);

		this.recalc();

		this._doCheck = false;

		return true;
	}

	, recalc: function (no_repos)
	{
		if (!this._refPane)
			return false;

		var type = this._type,
				virtSize = this._refPane.getVirtSize(type);

		this._sliderThumbSize = parseInt(this._refPane[this._paneSize] / virtSize.sum * this._sliderSize);

		if (this._sliderThumbSize < this._sliderBorderElemsSize)
			this._sliderThumbSize = this._sliderBorderElemsSize;

		this._scrollSpace = this._sliderSize - this._sliderThumbSize;
		this._sliderTicks = this._scrollSpace / (virtSize.edc - this._refPane._minCoords[type]);

		this._scrollSpaceCorr = 0;
		var ticksi = Math.round(this._sliderTicks);

		if (ticksi > 0)
		{
			var mod = this._scrollSpace % ticksi;

			if (mod > ticksi / 2)
				this._scrollSpaceCorr = ticksi - mod;
			else
				this._scrollSpaceCorr = -mod;
		}
		else
			ticksi = 1;

		this._slider.setConstraint(0, this._scrollSpace + this._scrollSpaceCorr, ticksi);

		var thumbexcfill = this._sliderBorderElemsSize + this._sliderCenterElemSize;

		if (this._sliderThumbSize < thumbexcfill)
		{
			if (this._flattenedCenterElem == false)
			{
				this._sliderCenter.setSize(0);
				this._flattenedCenterElem = true;
			}

			thumbexcfill = this._sliderBorderElemsSize;
		}
		else
		{
			if (this._flattenedCenterElem == true)
			{
				this._sliderCenter.setSize(this._sliderCenterElemSize);
				this._flattenedCenterElem = false;
			}
		}

		var fillsize = this._sliderThumbSize - thumbexcfill - this._scrollSpaceCorr;

		if (fillsize > 0)
		{
			var fillhalf = Math.round(fillsize / 2);

			this._sliderFills.setSize(1, fillhalf);
			this._sliderFills.setSize(0, fillsize - fillhalf);
		}
		else
		{
			this._sliderFills.setSize(1, 0);
			this._sliderFills.setSize(0, 0);
		}

		if (no_repos)
			return;

		this._slider.setValue((this._refPane._lastDestCell[type] - this._refPane._minCoords[type] + 1) * this._sliderTicks, true, true, true);
	}

	, start: function (cb, dir, speed)
	{
		if (arguments[3] !== true)
		{
			if (this._book._scrollPending)
				return false;

			if (speed == undefined || speed == NaN || speed <= 0)
				speed = this._defScrollSpeed;

			if (speed == this._currScrollSpeed)
				return true;

			if (this._currScrollSpeed)
				clearTimeout(this._tid_start);

			this._currScrollSpeed = speed;

			this._book._scrollPending = true;
		}

		var type = this._type;

		if (dir == this._RWD)
		{
			if (this._refPane._lastDestCell[type] >= this._refPane._minCoords[type])
			{
				this._doCheck = true;
				return this._scroll(0, this._refPane._lastDestCell[type] - 1, [ this, this._start_post, cb, dir, speed ]);
			}
		}
		else if (this._scrollSpace + this._scrollSpaceCorr - this._slider.getValue() < this._sliderTicks)
		{
			if (this._book._gmode_edit)
			{
			 	if (this._refPane._farthestSeenCell[type] < this._refPane._maxCoords[type])
				{
					this._refPane._farthestSeenCell[type]++;
					return this._scroll(0, this._refPane._lastDestCell[type] + 1, [ this, this._start_post, cb, dir, speed, true ]);
				}
				else if (this._refPane._lastDestCell[type] + this._refPane._cppi[type] < this._refPane._maxCoords[type])
					return this._scroll(0, this._refPane._lastDestCell[type] + 1, [ this, this._start_post, cb, dir, speed ]);
			}
			else if (this._refPane._lastDestCell[type] + this._refPane._cppi[type] < this._refPane._farthestSeenCell[type])
				return this._scroll(0, this._refPane._lastDestCell[type] + 1, [ this, this._start_post, cb, dir, speed ]);
		}
		else
			return this._scroll(0, this._refPane._lastDestCell[type] + 1, [ this, this._start_post, cb, dir, speed ]);

		this._currScrollSpeed = 0;
		this._book._scrollPending = false;

		return true;
	}

	, _start_post: function (cb, dir, speed, mode)
	{
		if (mode)
			this.recalc(true), this._slider.setValue(this._scrollSpace + this._scrollSpaceCorr, true, true, true);
		else
			this._slider.setValue((this._refPane._lastDestCell[this._type] - this._refPane._minCoords[this._type] + 1) * this._sliderTicks, true, true, true);

		if (this._currScrollSpeed)
		{
			var that = this;

			this._tid_start = setTimeout(
					function ()
					{
						that.start(cb, dir, speed, true);
					},
					speed
				);
		}

		if (cb instanceof Array && cb.length > 1)
			cb[1].apply(cb[0], cb.slice(2));

		this._book._scrollPending = false;
	}

	, stop: function ()
	{
		this._currScrollSpeed = 0;
	}

	, _reach: function (pos, dir)
	{
		var type = this._type;

		if (dir == this._RWD)
		{
			var interimDestCell = this._refPane._lastDestCell[type] - this._refPane._cppi[type];

			if (interimDestCell < this._refPane._minCoords[type] - 1)
				interimDestCell = this._refPane._minCoords[type] - 1;

			this._book._scrollPending = true;
			this._doCheck = true;
			this._scroll(0, interimDestCell, [ this, this._reach_post, pos, dir, interimDestCell ]);
		}
		else if (dir == this._FWD)
		{
			var interimDestCell = this._refPane._lastDestCell[type] + this._refPane._cppi[type];

			if (interimDestCell + this._refPane._cppi[type] > this._refPane._farthestSeenCell[type])
			{
				if (this._book._gmode_edit)
				{
					this._refPane._farthestSeenCell[type] = interimDestCell + this._refPane._cppi[type];

					if (this._refPane._farthestSeenCell[type] > this._refPane._maxCoords[type])
						this._refPane._farthestSeenCell[type] = this._refPane._maxCoords[type];

					this.recalc();
				}
				else
					interimDestCell = this._refPane._farthestSeenCell[type] - this._refPane._cppi[type];
			}

			this._book._scrollPending = true;
			this._doCheck = true;
			this._scroll(0, interimDestCell, [ this, this._reach_post, pos, dir, interimDestCell ]);
		}
		else
			this._book._scrollPending = false, this.check();
	}

	, _reach_post: function (pos, dir, interimDestCell)
	{
		this._slider.setValue((interimDestCell - this._refPane._minCoords[this._type] + 1) * this._sliderTicks, true, true, true);

		if (!this._book._scrollPending)
			return;

		var that = this;

		this._tid_reach = setTimeout(
			function ()
			{
				that._reach(pos, dir);
			},
			50
		);

		this._book._scrollPending = false;
	}

	, hidden: function ()
	{
		return this.dom.style.display == 'none';
	}

	, _clr_tid_reach: function ()
	{
		clearTimeout(this._tid_reach);

		this._book._scrollPending = false;
	}

	, _rwd_omd: function ()
	{
		this.start(null, -1);
	}

	, _fwd_omd: function ()
	{
		this.start(null, 1);
	}

	, _slideEnd: function ()
	{
		this._scheduled ? this._doCheck = true : this.check();
	}

};
