/*
 * \brief horizontal scrollbar class
 *
 * \file HorizScrollbar.js
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
 * SVN: $Id: HorizScrollbar.js 5008 2011-05-27 14:44:11Z predragm $
 *
 */

Jedox.wss.grid.HorizScrollbar = (function ()
{
	return function (book, dom, panes, size)
	{
		Jedox.wss.grid.HorizScrollbar.parent.constructor.call(this, book, dom);

		if (!book._gmode_edit && book._opts.hideHorScrollbar == 'yes')
		{
			this.dom.style.visibility = 'hidden';
			this.dom.style.height = '0px';
		}

		var that = this,
				jwgrid = Jedox.wss.grid;

		this._scrollbarBGOffset = jwgrid.defScrollbarBGOffset[0];
		this._sliderBorderElemsSize = jwgrid.defSliderBorderElemsSize[0];
		this._sliderCenterElemSize = jwgrid.defSliderCenterElemSize[0];

		this._sliderFills.setSize = function (elem, size) { this[elem].style.width = ''.concat(size, 'px'); };
		this._sliderCenter.setSize = function (size) { this.style.width = ''.concat(size, 'px'); };

		this._slider = YAHOO.widget.Slider.getHorizSlider(this._domId.concat('_bg'), this._domId.concat('_slider'), 0, 1, 1);

		this._slider.subscribe('change', function (offset) { that._scroll(offset); });
		this._slider.subscribe('slideEnd', function () { that._slideEnd(); });
		this._slider.thumb.subscribe('mouseDownEvent', function () { book.select(); });
		this._slider.setConstraint = function (from, to, ticksize) { this.thumb.setXConstraint(from, to, ticksize); };
		this._slider.onMouseDown = function (ev) { that._slider_omd(ev) };
		this._slider.onMouseUp = function () { that._clr_tid_reach(); };
		this._slider.animate = false;
		this._slider.dragOnly = false;
		this._slider.enableKeys = false;

		this._switch(panes, size);
	};
}
)();

Jedox.util.extend(Jedox.wss.grid.HorizScrollbar, Jedox.wss.grid.Scrollbar);

// public static fields

// public fields & methods
var _prototype = Jedox.wss.grid.HorizScrollbar.prototype;

_prototype._type = 0;
_prototype._paneSize = '_ocWidth';
_prototype._paneProp = '_hScroll';
_prototype._paneScroll = '_scrollGridX';

_prototype._genContentEl = function ()
{
	var html = [
	'<img id="', this._domId, '_rwd" class="hscroll_left" src="/ui/lib/ext/resources/images/default/s.gif" width="17" height="17" />',
	'<div id="', this._domId, '_bg" class="hscroll_bg">',
		'<div id="', this._domId, '_slider" class="hscroll_slider">',
			'<img class="gridScrollImg_el_left" width="4" height="17" src="/ui/lib/ext/resources/images/default/s.gif" />',
			'<img class="gridScrollImg_el_hfill" height="17" width="1" id="', this._domId, '_begf" src="/ui/lib/ext/resources/images/default/s.gif" />',
			'<img class="gridScrollImg_el_hcenter" height="17" width="8" id="', this._domId, '_midf" src="/ui/lib/ext/resources/images/default/s.gif" />',
			'<img class="gridScrollImg_el_hfill" height="17" width="1" id="', this._domId, '_endf" src="/ui/lib/ext/resources/images/default/s.gif" />',
			'<img class="gridScrollImg_el_right" width="4" height="17" src="/ui/lib/ext/resources/images/default/s.gif" />',
		'</div>',
	'</div>',
	'<img id="', this._domId, '_fwd" class="hscroll_right" src="/ui/lib/ext/resources/images/default/s.gif" width="17" height="17" />'
	];

	this.dom.innerHTML = html.join('');
};

_prototype._resize = function (size)
{
	if (size == 0)
		return this.dom.style.display = 'none';

	this.dom.style.cssText = 'display:; position: relative; width: '.concat(size, 'px;');

	this._sliderSize = size - this._scrollbarBGOffset;
	this._bg.style.width = ''.concat(this._sliderSize, 'px');

	this.recalc();
};

_prototype.reach = function (pos)
{
	if (this._book._scrollPending)
		return false;

	var dir = 0;

	if (pos < this._slider.thumb.lastPageX)
		dir = this._RWD;
	else if (pos > this._slider.thumb.lastPageX + this._slider.thumb._domRef.offsetWidth)
		dir = this._FWD;

	return this._reach(pos, dir);
};

_prototype._slider_omd = function (ev)
{
	this.reach(ev.clientX);
};
