/*
 * \brief Keyboard Files class.
 *
 * \file Files.js
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
 * SVN: $Id: Files.js 4869 2011-04-19 11:15:47Z lukap $
 *
 */

Jedox.kbd.Files = (function () {

	// class constructor
	return function () {
		Jedox.kbd.Files.parent.constructor.call(this);
	};

}
)();

// Files extends General
Jedox.util.extend(Jedox.kbd.Files, Jedox.kbd.General);

//public methods
clsRef = Jedox.kbd.Files;



clsRef.prototype._handleSpecial = function() {

	switch(Jedox.studio.app.inputMode){
		case Jedox.studio.app.inputMode_navigation_FILES:
			Ext.getCmp('sFiles_tree_tr').fireEvent('keyPress', this.event);
			this._preventBubble();
			break;
		case Jedox.studio.app.inputMode_content_FILES:
			Ext.getCmp('wt-panel').keyboardDispacher(this.event);
			this._preventBubble();
			break;

	}

	this._handleEnd();
};


//DEL
clsRef.prototype._46 = function() {
	this._handleSpecial();
};

//enter
clsRef.prototype._13 = function() {
	this._handleSpecial();
};

//esc
clsRef.prototype._27= function() {
	this._handleSpecial();
};

//f2
clsRef.prototype._113 = function() {
	this._handleSpecial();
};





clsRef.prototype._handleOther = function(){

	switch(Jedox.studio.app.inputMode){
		case Jedox.studio.app.inputMode_navigation_FILES:
			Ext.getCmp('sFiles_tree_tr').fireEvent('keyPress', this.event);
			break;
		case Jedox.studio.app.inputMode_content_FILES:
			Ext.getCmp('wt-panel').keyboardDispacher(this.event);
			break;
	}

	this._handleEnd();
}



// other buttons

//pgup
clsRef.prototype._33 = function() {
	this._handleOther();
};

//pgdown
clsRef.prototype._34 = function() {
	this._handleOther();
};

//left
clsRef.prototype._37 = function() {
	this._handleOther();
};

//up
clsRef.prototype._38 = function() {
	this._handleOther();
};

//right
clsRef.prototype._39 = function() {
	this._handleOther();
};

//down
clsRef.prototype._40= function() {
	this._handleOther();
};



//keys with CTRL || SHIFT || ALT

clsRef.prototype._handleOtherWithKeyModifier = function(){

	if (this.event[this.keyModifier]){

		switch(Jedox.studio.app.inputMode){
			case Jedox.studio.app.inputMode_navigation_FILES:
				Ext.getCmp('sFiles_tree_tr').fireEvent('keyPress', this.event);
				break;
			case Jedox.studio.app.inputMode_content_FILES:
				Ext.getCmp('wt-panel').keyboardDispacher(this.event);
				break;
		}

	} else
		this._handleDefault();

	this._handleEnd();
}

//c
clsRef.prototype._67 = function() {
	this._handleOtherWithKeyModifier();
};

//x
clsRef.prototype._88 = function() {
	this._handleOtherWithKeyModifier();
};

//v
clsRef.prototype._86 = function() {
	this._handleOtherWithKeyModifier();
};

//a
clsRef.prototype._65 = function() {
	this._handleOtherWithKeyModifier();
};
clsRef = null;