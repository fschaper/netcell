/*
 * \brief Keyboard General class.
 *
 * \file General.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: General.js 5008 2011-05-27 14:44:11Z predragm $
 *
 */

Jedox.kbd.General = (function () {

	// class constructor
	return function () {
		Jedox.kbd.General.parent.constructor.call(this);

		this.env = null;
		this.activeBook = null;
		this.activePane = null;

		this.result = true;
		this.copyToClp = false;
		this.pasteFromClp = false;
	};

}
)();

// General extends Base
Jedox.util.extend(Jedox.kbd.General, Jedox.kbd.Base);

//public methods
clsRef = Jedox.kbd.General;

clsRef.prototype.handle = function(event) {
	this.event = document.all ? window.event : event;
	this.keyCode = document.all ? this.event.keyCode : this.event.which;

	this.env = Jedox.wss.app.environment;
	this.activeBook = Jedox.wss.app.activeBook;
	this.activePane = Jedox.wss.app.activePane;

	Jedox.wss.app.lastKeyPressed = this.keyCode;
	this.result = true;
	this.copyToClp = false;
	this.pasteFromClp = false;

	if (this.env && this.env.inputMode != Jedox.wss.grid.GridMode.DIALOG && this.env.editingDirectly) {
		var lastInputField = Jedox.wss.app.lastInputField,
			selCellCoords = this.env.selectedCellCoords;

		if (this.env.viewMode != Jedox.wss.grid.viewMode.USER && (lastInputField == Jedox.wss.app.currFormula || !this.activePane.isCellVisible(selCellCoords[0], selCellCoords[1]))) {
			Jedox.wss.app.currFormula.focus();
			Jedox.wss.app.fromFormulaField = true;
		} else
			lastInputField.focus();
	}

	if (this.event.ctrlKey && !Jedox.wss.app.ctrlKeyPressed)
		Jedox.wss.app.ctrlKeyPressed = true;

	if (this.env && this.env.viewMode != Jedox.wss.grid.viewMode.USER && !Jedox.wss.app.ctrlKeyPressed) {
		this.env.defaultSelection.show();
		Jedox.wss.hb.setAllNormal();
	}

	var kHandler = '_'.concat(this.keyCode);

	if (this[kHandler])
		this[kHandler]();
	else
		this._handleDefault();
};

clsRef.prototype._handleDefault = function() {
	//if (this.keyCode == 8 || this.keyCode == 16 || this.keyCode == 32 ||
	if (this.keyCode == 8 || this.keyCode == 32 ||
		(this.keyCode > 41 && this.keyCode <= 90) ||
		(this.keyCode > 95 && this.keyCode <= 107) ||
		(this.keyCode > 108 && this.keyCode <= 111) ||
		(this.keyCode >= 187 && this.keyCode <= 226)
	) {
		if (this.env) {
			if (this.env.inputMode == Jedox.wss.grid.GridMode.READY) {
				if (this.env.viewMode == Jedox.wss.grid.viewMode.USER) {
					var selCoords = this.env.selectedCellCoords;

					if (this.activePane.isCellLocked(selCoords[0], selCoords[1]))
						return;
				}

				this.env.selectedCellValue = '';
				this.env.selectedCellFormula = '';
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.INPUT);
				Jedox.wss.general.showInputField(null, false, true, false, true);
				Jedox.wss.app.updateUndoState([1, 0], false);
			} else if (this.env.inputMode == Jedox.wss.grid.GridMode.EDIT || this.env.inputMode == Jedox.wss.grid.GridMode.INPUT)
				Jedox.wss.app.updateUndoState([ 1, 0 ], false);
		}
	}

	this._handleEnd();
};

clsRef.prototype._resetFocus = function() {
	Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
	Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
};

clsRef.prototype._setDefaultRange = function(rng) {
	if (this.env) {
		var defSel = this.env.defaultSelection;

		if (defSel)
			defSel.jumpTo(rng);
	}

	this._handleEnd();
};

clsRef.prototype._handleEnd = function() {
	if (
		this.env && !this.pasteFromClp &&
		this.env.inputMode != Jedox.wss.grid.GridMode.EDIT &&
		this.env.inputMode != Jedox.wss.grid.GridMode.INPUT &&
		this.env.inputMode != Jedox.wss.grid.GridMode.CNTRL &&
		this.env.inputMode != Jedox.wss.grid.GridMode.DIALOG
	)
		Jedox.wss.keyboard.preventKeyEvent(this.event);

	if (this.env && this.env.viewMode == Jedox.wss.grid.viewMode.USER)
		Jedox.wss.keyboard.handleUMFocus(this.keyCode, this.event.shiftKey);

	if (this.copyToClp)
		this._resetFocus();

	if (this.pasteFromClp) {
		setTimeout('Jedox.wss.action.paste()', 1);
		this._resetFocus();
	}
};

// tab
clsRef.prototype._9 = function() {
	if (Jedox.wss.action.sendGridInput(this.event, this.keyCode)) {
		if(this.keyCode == 9)
			Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.RIGHT, this.event.shiftKey, 1, this.keyCode);
		else if (!(this.event.ctrlKey && this.event.shiftKey))
			Jedox.wss.keyboard.moveCursor(Jedox.wss.grid.ScrollDirection.DOWN, this.event.shiftKey, 1, this.keyCode);
	}

	this._handleEnd();
};

// enter
clsRef.prototype._13 = function() {
	this._9();
};

// escape
clsRef.prototype._27 = function() {
	Jedox.wss.action.cancelGridInput();
	Jedox.wss.action.exitFormatPainter();
	this._handleEnd();
};

// home
clsRef.prototype._36 = function() {
	if (this.event.ctrlKey) {
		Jedox.wss.keyboard.preventKeyEvent(this.event);
		this.activePane.scrollTo([ this, this._setDefaultRange, [1, 1, 1, 1]], 1, 1, true, false);
	}
};

// end
clsRef.prototype._35 = function() {
	if (this.event.ctrlKey) {
		Jedox.wss.keyboard.preventKeyEvent(this.event);
		var fuc = this.activePane.getFarthestUsedCell();
		this.activePane.scrollTo([ this, this._setDefaultRange, [fuc[0], fuc[1], fuc[0], fuc[1]]], fuc[0], fuc[1], true, false);
	}
};

// arrow left
clsRef.prototype._37 = function() {
	if (this.env) {
		if(this.env.inputMode == Jedox.wss.grid.GridMode.INPUT){
			var value = this.env.inputField.value;

			if ((value.length > 0) && (value.substr(0, 1) == '=')) {
				var elemCoords;
				if (this.env.formulaSelection.activeToken != null) {
					var point, area = this.env.formulaSelection.getActiveRange(), areaCorners = area.getCorners();

					elemCoords = Jedox.wss.keyboard.calcCursorRng(areaCorners[0].clone(), areaCorners[1].clone(), area.getAnchorCell().clone(), this.keyCode, this.event.shiftKey);
					area.set(elemCoords[0], elemCoords[1]);
					if (elemCoords[0].equals(elemCoords[1]))
						area.setAnchorCell(elemCoords[0]);

					area.formulaUpdate();

					area.draw();
				} else {
					var defRngActCell = this.env.defaultSelection.getActiveRange().getActiveCell().clone();
					elemCoords = Jedox.wss.keyboard.calcCursorRng(defRngActCell, defRngActCell, defRngActCell, this.keyCode, this.event.shiftKey);

					if (!this.activePane.isCellVisible(elemCoords[2].getX(), elemCoords[2].getY()) && this.activeBook._scrollPending)
						return;

					var currFormula = Jedox.wss.app.currFormula,
							cursorPos = Jedox.util.getSelection(Jedox.wss.app.fromFormulaField ? currFormula.el.dom : this.env.inputField).start;

					if (cursorPos < currFormula.getValue().length || value.substr(-1, 1).match(/^[a-z0-9]$/i) != null) {
						if (this.env.oldValue != value)
							Jedox.wss.keyboard.sendInput(this.env.inputField);
						else
							Jedox.wss.keyboard.cancelInput();

						return Jedox.wss.keyboard.checkGlobalInput(this.event);
					}

					var area_id = this.env.formulaSelection.addRange(new Jedox.gen.Point(elemCoords[0].getX(), elemCoords[0].getY())) - 1;
					this.env.formulaSelection.setActiveRange(area_id);

					var area = this.env.formulaSelection.getActiveRange(), areaVal = area.getValue();

					this.env.inputField.value = value.concat(areaVal);
					currFormula.setValue(this.env.inputField.value);

					var refs = Jedox.wss.formula.parse(currFormula.getValue(), Jedox.wss.app.activePane.getCellNFs(elemCoords[0].getX(), elemCoords[0].getY()));

					this.env.formulaSelection.lastParseRes = refs;
					this.env.formulaSelection.activeToken = area.formulaToken = refs[refs.length - 1];

					this.env.formulaSelection.setState(Jedox.wss.range.AreaState.NEW);
					area.draw();

					Jedox.wss.keyboard.setFieldSize();
					this.env.lastInputValue = currFormula.getValue();
				}

				// Scroll grid if necessary.
				if (!this.activePane.isCellVisible(elemCoords[2].getX(), elemCoords[2].getY())) {
					Jedox.wss.keyboard.preventKeyEvent(this.event);
					this.activePane.scrollTo([this, this._handleEnd], elemCoords[2].getX(), elemCoords[2].getY(), true, false);
					return;
				}
			} else {
				this.result = Jedox.wss.keyboard.sendInput(this.env.inputField);

				if (this.result) {
					Jedox.wss.keyboard.cancelInput(false);

					try {
						Jedox.wss.app.currFormula.getEl().blur();
					} catch (e) {}

					Jedox.wss.keyboard.handleCursorKey(this.event);
				} else {
					alert('Invalid input!'.localize());
					Jedox.wss.general.focusInputField();
				}
			}

			Jedox.wss.keyboard.preventKeyEvent(this.event);
		}else{
			if(!this.env.editingDirectly &&
				(this.env.inputMode != Jedox.wss.grid.GridMode.CNTRL) &&
				(this.env.inputMode != Jedox.wss.grid.GridMode.DIALOG)) {
				Jedox.wss.keyboard.handleCursorKey(this.event);
			}

			if ((this.env.inputMode == Jedox.wss.grid.GridMode.DIALOG) && Jedox.wss.app.currentDialogControl != null) {
				var selCmp = Ext.getCmp(Jedox.wss.app.currentDialogControl);

				if (selCmp.getXType() == 'dataview') {
					var currIndex = selCmp.getSelectedIndexes()[0];

					switch(this.keyCode) {
						case 33:
						case 37:
						case 38:
							selCmp.select((currIndex > 0) ? --currIndex : Jedox.wss.app.currentDialogControlItemsCnt - 1);
							break;

						case 34:
						case 39:
						case 40:
							selCmp.select((currIndex < Jedox.wss.app.currentDialogControlItemsCnt - 1) ? ++currIndex : 0);
							break;
					}

					Jedox.wss.keyboard.preventKeyEvent(this.event);
				}
			}
		}
	}

	this._handleEnd();
};


// arrow up
clsRef.prototype._38 = function() {
	this._37();
};

//arrow right
clsRef.prototype._39 = function() {
	this._37();
};

//arrow down
clsRef.prototype._40 = function() {
	this._37();
};

// page up
clsRef.prototype._33 = function() {
	this._37();
};

//page down
clsRef.prototype._34 = function() {
	this._37();
};

// delete
clsRef.prototype._46 = function() {
	if(this.env &&
		(this.env.inputMode != Jedox.wss.grid.GridMode.INPUT) &&
		(this.env.inputMode != Jedox.wss.grid.GridMode.EDIT) &&
		(this.env.inputMode != Jedox.wss.grid.GridMode.CNTRL) &&
		(this.env.inputMode != Jedox.wss.grid.GridMode.DIALOG) &&
		(!this.env.editingDirectly)
	)
		if (this.env.viewMode == Jedox.wss.grid.viewMode.USER) {
			this.env.inputField.value = '';
			this.env.selectedCellValue = '';
			Jedox.wss.app.activeSheet._cursorField.setContent('');

			var cellCoords = this.env.lastRangeStartCoord;

			this.activePane.clrCell(cellCoords[0], cellCoords[1]);
		} else
			this.env.defaultSelection.emptyCellContent();

	this._handleEnd();
};

// f2
clsRef.prototype._113 = function() {
	if (this.env) {
		if (this.env.inputMode != Jedox.wss.grid.GridMode.EDIT && this.env.inputMode != Jedox.wss.grid.GridMode.INPUT) {
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.EDIT);
			Jedox.wss.general.showInputField(null, false, true);
		} else
			Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode[this.env.inputMode == Jedox.wss.grid.GridMode.EDIT ? 'INPUT' : 'EDIT']);
	}

	this._handleEnd();
};

// f9
clsRef.prototype._120 = function() {
	if (this.env && this.env.inputMode != Jedox.wss.grid.GridMode.EDIT && this.env.inputMode != Jedox.wss.grid.GridMode.INPUT)
		Jedox.wss.sheet.refresh();

	this._handleEnd();
};

// f11
clsRef.prototype._122 = function() {
 // <ALT>+<F11> => open macro editor
 if (this.event.altKey && this.env && this.env.viewMode != Jedox.wss.grid.viewMode.USER)
  Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro);

	this._handleEnd();
};

// shift
clsRef.prototype._16 = function() {
	var wrapper = Jedox.wss.app.activeWrapper;

	if (wrapper)
		wrapper.preserveRatio = !wrapper.defaultRatio;
};

// ctrl
clsRef.prototype._17 = function() {
	var mousePos = this.env ? this.env.mousePosition : null;
	if (mousePos == 'rngBorder' || mousePos == 'magicDot')
		this.env.defaultSelection.setCursor(mousePos, (mousePos == 'rngBorder') ? 'rng_copy' : 'md_curr_plus');

	this._handleEnd();
};

// c
clsRef.prototype._67 = function() {
	if (this.event.ctrlKey && this.env) {
		Jedox.wss.action.copy(true);

		if (this.env.inputMode == Jedox.wss.grid.GridMode.READY || this.env.inputMode == Jedox.wss.grid.GridMode.DIALOG)
			this.copyToClp = true;
	} else
		this._handleDefault();

	this._handleEnd();
};

// g
clsRef.prototype._71 = function() {
	if (this.event.ctrlKey && this.env && this.env.viewMode != Jedox.wss.grid.viewMode.USER)
		Jedox.gen.load(Jedox.wss.app.dynJSRegistry.goTo);
	else
		this._handleDefault();

	this._handleEnd();
};

// v
clsRef.prototype._86 = function() {
	if (this.event.ctrlKey && this.env && this.env.inputMode == Jedox.wss.grid.GridMode.READY) {
		if (Jedox.wss.app.clipboard == null) {
			var pomdiv = document.createElement('div');
			pomdiv.setAttribute('id', 'pomdiv');
			pomdiv.style.width = "1px";
			pomdiv.style.height = "1px";
			pomdiv.style.position = "relative";
			pomdiv.style.overflow = "hidden";

			var _pinput = document.createElement("textarea");
			_pinput.setAttribute("id", "_paste_field_");
			_pinput.setAttribute("name", "_paste_field_");
			_pinput.setAttribute("style", "position: float; width: 1px; height: 1px; z-index: 999; overflow: hidden;");
			pomdiv.appendChild(_pinput);

			document.body.appendChild(pomdiv);
			document.getElementById("_paste_field_").focus();
			document.getElementById("_paste_field_").select();

			this.pasteFromClp = true;
		} else
			Jedox.wss.action.paste();
	} else
		this._handleDefault();

	this._handleEnd();
};

// x
clsRef.prototype._88 = function() {
	if (this.event.ctrlKey && this.env) {
		Jedox.wss.action.cut(true);

		if (this.env.inputMode == Jedox.wss.grid.GridMode.READY || this.env.inputMode == Jedox.wss.grid.GridMode.DIALOG)
			this.copyToClp = true;
	} else
		this._handleDefault();

	this._handleEnd();
};

// y
clsRef.prototype._89 = function() {
	if (this.event.ctrlKey && this.env) {
		//if (this.env.undoState[1] > 0) {
			Jedox.wss.sheet.redo();
			Jedox.wss.keyboard.preventKeyEvent(this.event);
		//}
	} else
		this._handleDefault() ;

	this._handleEnd();
};

// z
clsRef.prototype._90 = function() {
	if (this.event.ctrlKey && this.env) {
		//if (this.env.undoState[0] > 0) {
			Jedox.wss.sheet.undo();
			Jedox.wss.keyboard.preventKeyEvent(this.event);
		//}
	} else
		this._handleDefault();

	this._handleEnd();
};

clsRef = null;