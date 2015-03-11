/*
 * \brief application global variables
 *
 * \file globals.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: globals.js 4991 2011-05-24 13:55:35Z predragm $
 *
 */

Jedox.wss.app.environment = null;

Jedox.wss.app.numberToLetter = [ '', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'AA', 'AB', 'AC', 'AD', 'AE', 'AF', 'AG', 'AH', 'AI', 'AJ', 'AK', 'AL', 'AM', 'AN', 'AO', 'AP', 'AQ', 'AR', 'AS', 'AT', 'AU', 'AV', 'AW', 'AX', 'AY', 'AZ', 'BA', 'BB', 'BC', 'BD', 'BE', 'BF', 'BG', 'BH', 'BI', 'BJ', 'BK', 'BL', 'BM', 'BN', 'BO', 'BP', 'BQ', 'BR', 'BS', 'BT', 'BU', 'BV', 'BW', 'BX', 'BY', 'BZ', 'CA', 'CB', 'CC', 'CD', 'CE', 'CF', 'CG', 'CH', 'CI', 'CJ', 'CK', 'CL', 'CM', 'CN', 'CO', 'CP', 'CQ', 'CR', 'CS', 'CT', 'CU', 'CV', 'CW', 'CX', 'CY', 'CZ', 'DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG', 'DH', 'DI', 'DJ', 'DK', 'DL', 'DM', 'DN', 'DO', 'DP', 'DQ', 'DR', 'DS', 'DT', 'DU', 'DV', 'DW', 'DX', 'DY', 'DZ', 'EA', 'EB', 'EC', 'ED', 'EE', 'EF', 'EG', 'EH', 'EI', 'EJ', 'EK', 'EL', 'EM', 'EN', 'EO', 'EP', 'EQ', 'ER', 'ES', 'ET', 'EU', 'EV', 'EW', 'EX', 'EY', 'EZ', 'FA', 'FB', 'FC', 'FD', 'FE', 'FF', 'FG', 'FH', 'FI', 'FJ', 'FK', 'FL', 'FM', 'FN', 'FO', 'FP', 'FQ', 'FR', 'FS', 'FT', 'FU', 'FV', 'FW', 'FX', 'FY', 'FZ', 'GA', 'GB', 'GC', 'GD', 'GE', 'GF', 'GG', 'GH', 'GI', 'GJ', 'GK', 'GL', 'GM', 'GN', 'GO', 'GP', 'GQ', 'GR', 'GS', 'GT', 'GU', 'GV', 'GW', 'GX', 'GY', 'GZ', 'HA', 'HB', 'HC', 'HD', 'HE', 'HF', 'HG', 'HH', 'HI', 'HJ', 'HK', 'HL', 'HM', 'HN', 'HO', 'HP', 'HQ', 'HR', 'HS', 'HT', 'HU', 'HV', 'HW', 'HX', 'HY', 'HZ', 'IA', 'IB', 'IC', 'ID', 'IE', 'IF', 'IG', 'IH', 'II', 'IJ', 'IK', 'IL', 'IM', 'IN', 'IO', 'IP', 'IQ', 'IR', 'IS', 'IT', 'IU', 'IV' ];

Jedox.wss.app.letterToNumber = { A: '1', B: '2', C: '3', D: '4', E: '5', F: '6', G: '7', H: '8', I: '9', J: '10', K: '11', L: '12', M: '13', N: '14', O: '15', P: '16', Q: '17', R: '18', S: '19', T: '20', U: '21', V: '22', W: '23', X: '24', Y: '25', Z: '26', AA: '27', AB: '28', AC: '29', AD: '30', AE: '31', AF: '32', AG: '33', AH: '34', AI: '35', AJ: '36', AK: '37', AL: '38', AM: '39', AN: '40', AO: '41', AP: '42', AQ: '43', AR: '44', AS: '45', AT: '46', AU: '47', AV: '48', AW: '49', AX: '50', AY: '51', AZ: '52', BA: '53', BB: '54', BC: '55', BD: '56', BE: '57', BF: '58', BG: '59', BH: '60', BI: '61', BJ: '62', BK: '63', BL: '64', BM: '65', BN: '66', BO: '67', BP: '68', BQ: '69', BR: '70', BS: '71', BT: '72', BU: '73', BV: '74', BW: '75', BX: '76', BY: '77', BZ: '78', CA: '79', CB: '80', CC: '81', CD: '82', CE: '83', CF: '84', CG: '85', CH: '86', CI: '87', CJ: '88', CK: '89', CL: '90', CM: '91', CN: '92', CO: '93', CP: '94', CQ: '95', CR: '96', CS: '97', CT: '98', CU: '99', CV: '100', CW: '101', CX: '102', CY: '103', CZ: '104', DA: '105', DB: '106', DC: '107', DD: '108', DE: '109', DF: '110', DG: '111', DH: '112', DI: '113', DJ: '114', DK: '115', DL: '116', DM: '117', DN: '118', DO: '119', DP: '120', DQ: '121', DR: '122', DS: '123', DT: '124', DU: '125', DV: '126', DW: '127', DX: '128', DY: '129', DZ: '130', EA: '131', EB: '132', EC: '133', ED: '134', EE: '135', EF: '136', EG: '137', EH: '138', EI: '139', EJ: '140', EK: '141', EL: '142', EM: '143', EN: '144', EO: '145', EP: '146', EQ: '147', ER: '148', ES: '149', ET: '150', EU: '151', EV: '152', EW: '153', EX: '154', EY: '155', EZ: '156', FA: '157', FB: '158', FC: '159', FD: '160', FE: '161', FF: '162', FG: '163', FH: '164', FI: '165', FJ: '166', FK: '167', FL: '168', FM: '169', FN: '170', FO: '171', FP: '172', FQ: '173', FR: '174', FS: '175', FT: '176', FU: '177', FV: '178', FW: '179', FX: '180', FY: '181', FZ: '182', GA: '183', GB: '184', GC: '185', GD: '186', GE: '187', GF: '188', GG: '189', GH: '190', GI: '191', GJ: '192', GK: '193', GL: '194', GM: '195', GN: '196', GO: '197', GP: '198', GQ: '199', GR: '200', GS: '201', GT: '202', GU: '203', GV: '204', GW: '205', GX: '206', GY: '207', GZ: '208', HA: '209', HB: '210', HC: '211', HD: '212', HE: '213', HF: '214', HG: '215', HH: '216', HI: '217', HJ: '218', HK: '219', HL: '220', HM: '221', HN: '222', HO: '223', HP: '224', HQ: '225', HR: '226', HS: '227', HT: '228', HU: '229', HV: '230', HW: '231', HX: '232', HY: '233', HZ: '234', IA: '235', IB: '236', IC: '237', ID: '238', IE: '239', IF: '240', IG: '241', IH: '242', II: '243', IJ: '244', IK: '245', IL: '246', IM: '247', IN: '248', IO: '249', IP: '250', IQ: '251', IR: '252', IS: '253', IT: '254', IU: '255', IV: '256' };

/* This number contains the active sheet number (?) */
Jedox.wss.app.activeSheetName = 1;

/*
 * This number stores previous input mode and is used by switching to and from CNTRL mode.
 */
Jedox.wss.app.lastInputMode = 0;

/*
 * This number stores previous input mode and is used by switching to and from DIALOG mode.
 */
Jedox.wss.app.lastInputModeDlg = 0;

/*
 * Absolute letter(s) of first row in grid
 */
Jedox.wss.app.firstRow = 'A';

/*
 * Absolute number of first row in grid
 */
Jedox.wss.app.firstRowNumeric = 1;

/*
 * Absolute number of first row in grid
 */
Jedox.wss.app.firstColumn = 1;

/*
 * Number of x coordinate of current mouse position
 */
Jedox.wss.app.xPos = 0;

/*
 * Number of y coordinate of current mouse position
 */
Jedox.wss.app.yPos = 0;

/*
 * Flag indicating if left mouse button is hold down
 */
Jedox.wss.app.mouseButton1Down = false;

/*
 * Flag indicating if right mouse button is hold down
 */
Jedox.wss.app.mouseButton2Down = false;

/*
 * Flag indicating if user agent is Internet Explorer
 */
Jedox.wss.app.isIE = document.all ? true : false;

/*
 * Flag indicating if left mouse button is down and mousedown event hit on
 * row or column
 */
Jedox.wss.app.maybeDragging = false;

/*
 * Maximal absolute grid size
 */
Jedox.wss.app.cellAmount = [ 256, 1024 ];

/*
 * Default cell height in pixels
 */
Jedox.wss.app.defCellHeight = 16;

/*
 * Default cell width in pixels
 */
Jedox.wss.app.defCellWidth = 80;

/*
 * Array of loaded workbooks. Each entry contains
 * 0 : id of workbook
 * 1 : name of workbook
 */
Jedox.wss.app.workbookList = [];

/*
 * Flag indicating if grid has loaded completely
 */
Jedox.wss.app.loaded = false;

/*
 * Flag indicating if server is resonding at startup. If not, gui will stop.
 */
Jedox.wss.app.serverAvailable = true;

/*
 * Flag indicating if auto-calculation of formulas is turned on.
 */
Jedox.wss.app.autoCalc = true;

/*
 * Available wdith in browser window minus height of vertical scrollbar
 */
Jedox.wss.app.xCellOffset = 17;

/*
 * Available height in browser window minus height of toolbar, statusbar, horizontal scrollbar and sheet selector
 */
Jedox.wss.app.yCellOffset = 108;

/*
 * Temporary string used for inserting a formula string via "Insert formula" dialog
 */
Jedox.wss.app.selectedFormula = '';

/*
 *  Reference to <input> element which shows the formula of active cell
 */
Jedox.wss.app.currFormula = null;

/*
 *  Reference to <input> element which indicates active cell or range
 */
Jedox.wss.app.currCoord = null;

/*
 *  Reference to status bar
 */
Jedox.wss.app.statusBar = null;

/*
 *  Flag indicating if input field has had focus before textarea was focused
 */
Jedox.wss.app.fromFormulaField = false;

/*
 * Observer reacting on "onmousemove" events on body element
 */
Jedox.wss.app.mouseMovementObserver = null;

/*
 * Observer reacting on "onmouseup" events on body element
 */
Jedox.wss.app.mouseUpObserver = null;

/*
 * Observer reacting on "onmousedown" events on body element
 */
Jedox.wss.app.mouseDownObserver = null;

/*
 * Observer reacting on switching sheets for any sheet selector.
 */
Jedox.wss.app.switchContextObserver = null;

/*
 * Toolbar buttons toggle switch.
 */
Jedox.wss.app.performItemToggle = true;

// default font
Jedox.wss.app.cnfDefaultFont = 'Arial';

// default font size
Jedox.wss.app.cnfDefaultFontSize = '10';

// active color palette
Jedox.wss.app.activeColorPalette = 'main';

// default bgColor
Jedox.wss.app.cnfDefaultBgColor = 'FF0000';

// default textColor
Jedox.wss.app.cnfDefaultTextColor = 'FFFF00';

// default predefined border style
Jedox.wss.app.cnfDefaultBorder = 'brd-bottom-norm';

/*
 * Predefined data.
 */

Jedox.wss.app.lastKeyPressed = null;

Jedox.wss.app.currentDialogControl = null;
Jedox.wss.app.currentDialogControlItemsCnt = 0;

// Flag indicating which one of the input fields was last used.
Jedox.wss.app.lastInputField = null;

// Flag indicating global view mode (DESIGNER or USER).
Jedox.wss.app.appMode = Jedox.wss.grid.viewMode.USER;

// Reference to active mark range.
Jedox.wss.app.copySelection = null;

// Reference to Clipboard object {id: [clipboardID], op: [operation (copy | cut)]}
Jedox.wss.app.clipboard = null;

// Flag indicating pressed CTRL key
Jedox.wss.app.ctrlKeyPressed = false;

// Flag indicating if mouse right click will show browser's default context menu.
Jedox.wss.app.showBrowserCtx = false;

// Suspend Mode window
Jedox.wss.general.switchSuspendModeAlert = null;

// Flag indicating browser engine ('ff' - Mozila Firefox, 'ie' - MS Internet Explorer, 'sf' - Safari, 'ch' - Chrome)
Jedox.wss.app.browser = 'ff';

// Switch for mimic overtracking in Firefox3.
Jedox.wss.app.mimicOvertracking = false;

// active book, sheet & pane
Jedox.wss.app.activeBook = undefined;
Jedox.wss.app.activeSheet = undefined;
Jedox.wss.app.activePane = undefined;

Jedox.wss.app.standalone = window == parent;
Jedox.wss.app.userPreview = false;
Jedox.wss.app.UPRestrictMode = false;
Jedox.wss.app.UPRestrictModeEnabled = true;

// Toolbar layouts.
Jedox.wss.app.toolbarLayouts = {TOOLBAR: 'toolbar', RIBBON: 'ribbon'};

// Flag indication toolbar layout (classic | ribbon).
Jedox.wss.app.toolbarLayout = Jedox.wss.app.toolbarLayouts.TOOLBAR;

// Flag indicating Fopper exists.
Jedox.wss.app.fopper = false;

// flag indicating that application is ready (TODO)
Jedox.wss.app.ready = true;
