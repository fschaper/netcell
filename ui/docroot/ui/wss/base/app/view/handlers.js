/*
 * @brief ajax
 *
 * @file handlers.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: handlers.js 3593 2010-07-29 18:35:20Z predragm $
 *
 */

Jedox.wss.app.updateUndoState = function(undoState, updState){};

// +++ Functions for HIDE/SHOW Bars +++ //
Jedox.wss.app.hideBar = function(barId)
{
	var bar = Ext.get(barId);
	bar.setVisibilityMode(Ext.Element.DISPLAY);
	bar.hide();

	Jedox.wss.wspc.resize();
};

Jedox.wss.app.showBar = function(barId)
{
	var bar = Ext.get(barId);
	bar.setVisibilityMode(Ext.Element.DISPLAY);
	bar.show();

	Jedox.wss.wspc.resize();
};

Jedox.wss.app.hideToolbar = function(toolbar)
{
	Jedox.wss.app.hideBar('Toolbar');
};

Jedox.wss.app.showToolbar = function(toolbar)
{
	Jedox.wss.app.showBar('Toolbar');
};

// Show hide from MenuBar
Jedox.wss.app.hideShowToolbar = function(state, toolbar)
{
	if (state)
		Jedox.wss.app.showToolbar(toolbar);
	else
		Jedox.wss.app.hideToolbar(toolbar);
};