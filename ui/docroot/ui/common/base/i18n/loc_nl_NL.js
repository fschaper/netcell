/*
 * @brief wss file
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: loc_nl_NL.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Cancel",
"File": "File",
"New": "New",
"Open": "Open",
"Close": "Close",
"Save": "Save",
"Properties": "Properties",
"Edit": "Edit",
"Cut": "Cut",
"Copy": "Copy",
"Paste": "Paste",
"View": "View",
"List": "List",
"Hide": "Hide",
"Help": "Help",
"Create new document": "Create new document",
"Open document": "Open document",
"Save document": "Save document",
"Bold": "Bold",
"Italic": "Italic",
"Underline": "Underline",
"Delete": "Delete",
"Rename": "Rename",
"Select All": "Select All",
"Type": "Type",
"Warning": "Warning",
"Password": "Password",
"Layout": "Layout",
"General": "General",
"Preview": "Preview",
"Refresh": "Refresh",
"None": "None",
"Bottom": "Bottom",
"Right": "Right",
"Up": "Up",
"New Folder": "New Folder",
"Thumbnails": "Icons",
"Details": "Details",
"Description": "Description",
"Options": "Options",
"Modeller": "Modeller",
"Home": "Home",
"Size": "Size",

"Quick View": "Admin preview",
"Designer Preview": "Designer Preview",
"Active": "Active",
"Path": "Path",
"Apply": "Apply",
"Rename Sheet": "Rename Sheet",

//Paste Subset Dialog
"_tit: hb List Editor": "DynaRange List Editor",
"Subset Editor": "Subset Editor",
"Subset General Settings": "Subset General Settings",
"Dimension": "Dimension",
"Select First Alias": "Select First Alias",
"Select Second Alias": "Select Second Alias",
"Alias": "Alias",
"Optional Settings": "Optional Settings",
"Hierarchy enumeration": "Hierarchy enumeration",
"Hierarchy": "Hierarchy",
"Text": "Text",
"Picklist": "Picklist",
"Attribute": "Attribute",
"Sort": "Sort",
"Level": "Level",
"Depth": "Depth",
"Flat": "Flat",
"Show parents below children": "Show parents below children",
"Show duplicates": "Show duplicates",
"Show children of hidden elements": "Show children of hidden elements",
"_msg: hb Lists": "DynaRange Lists",
"[_name: hb List]": "[DynaRange List]",
"Formula Subset": "Formula Subset",
"[Formula Subset]": "[Formula Subset]",
"Local Subsets": "Local Subsets",
"Global Subsets": "Global Subsets",
"Stored Subsets": "Stored Subsets",
"Auto": "Auto",
"By Definition": "By Definition",
"By Element name": "By Element name",
"By Alias": "By Alias",
"By Value": "By Value",
"By Attribute": "By Attribute",
"All Elements": "All Elements",
"Base Elements Only": "Base Elements Only",
"Consolidated Elements Only": "Consolidated Elements Only",
"Reverse": "Reverse",
"Sort at Level": "Sort at Level",
"Sorting behaviour": "Sorting behavior",
"Reverse Order": "Reverse Order",
"Type Limitation": "Type Limitation",
"New Subset": "New Subset",
"Enter name for Subset": "Enter name for Subset",
"Delete Subset": "Delete Subset",
"_msg: Delete Subset": "Are you sure you want to delete Subset?",
"Rename Subset": "Rename Subset",
"Enter new name for Subset": "Enter new name for Subset",
"_msg: update Subset": "Storing Subset.",
"_msg: new Subset": "Storing new Subset.",
"_msg: delete Subset": "Deleting Subset.",
"_msg: rename Subset": "Storing new name for Subset.",
"[All Elements]": "[All Elements]",
"Filter elements hierarchically": "Filter elements hierarchically",
"Cyclic list": "Cyclic list",
"Below": "Below",
"Above": "Above",
"Consolidated": "Consolidated",
"Base Elements": "Base Elements",
"Activate this filter": "Activate this filter",
"Exclusive": "Exclusive",
"Filter Element by type": "Filter Element by type",
"Filter elements by Level": "Filter elements by Level",
"List length": "List length",
"Start level": "Start level",
"Indent Enumeration": "Indent Enumeration",
"End level": "End level",
"Settings": "Settings",
"_subsetTextTabExamples": 'Examples:<br>' +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "<b>PERL-Regular expressions</b>",
"Behaviour": "Behaviour",
"Dimension Contents": "Dimension Contents",
"Please select how to insert choosen elements": "Please select how to insert selected elements",
"_subsetAttrTabExample": '<br>Examples:<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Variable",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Level Start",
"Level End": "Level End",
"Criteria": "Criteria",
"Sort Attribute": "Sort Attribute",
"Sort Level": "Sort Level",
"Quick": "Quick",
"SUM OF THE ELEMENTS": "SUM OF THE ELEMENTS",
"ALL ELEMENTS": "ALL ELEMENTS",
"AVEREGE OF THE ELEMENTS": "AVEREGE OF THE ELEMENTS",
"MAXIMUM OF THE ELEMETNS": "MAXIMUM OF THE ELEMETNS",
"ANY ELEMENT": "ANY ELEMENT",
"MINIMUM OF THE ELEMENTS": "MINIMUM OF THE ELEMENTS",
"STRING": "STRING",
"Please select and set attribute fields": "Please select and set attribute fields",
"Select Cube": "Select Cube",
"Indent": "Indent",
"FRONT": "FRONT",
"BACK": "BACK",
"MERGE": "MERGE",
"SUBTRACT": "SUBTRACT",
"Take topmost elements": "Take topmost elements",
"Take all upper elements up to %": "Take all upper elements up to %",
"Take all lower elements up to %": "Take all lower elements up to %",
"List Length": "List Length",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Picklist Type",
"Cube": "Cube",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Topmost",
"Upper": "Upper",
"Lower": "Lower",
"Slice operators": "Slice operators",
"AND": "AND",
"Named Variables": "Named Variables",
"subset_Indent": "Indent",
"Obtaining preview data": "Obtaining preview data",
"Unable to resolve value for": "Unable to resolve value for",
"_msg: paloSbstDFilterEnabled": "When Data Filter is enabled, processing to get preview list can take more time",

//PALO Modeller
"PALO Modeller": "PALO Modeller",
"Error": "Error",
"Elements": "Elements",
"Attributes": "Attributes",
"Subsets": "Subsets",
"Consolidated Elements": "Consolidated Elements",
"show Tree": "Show tree",
"<< Database": "<< Database",
"Expand All": "Expand All",
"Collapse All": "Collapse All",
"Choose Server/Database": "Choose Server/Database",
"Dimensions and Global Subsets": "Dimensions and Global Subsets",
"Cubes": "Cubes",
"Database": "Database",
"system": "system",
"attributes": "attributes",
"normal": "normal",
"loaded": "loaded",
"not loaded": "not loaded",
"_err: Timer": "Time out for Server request.",
"_msg: Timer": "Waiting time went off.",
"Add": "Add",
"Consolidate": "Consolidate",
"Numeric": "Numeric",
"String": "String",
"Copy Elements": "Copy Elements",
"Paste Elements": "Paste Elements",
"Move Element to the Beginning": "Move Element to the Beginning",
"Move Element to the End": "Move Element to the End",
"Count": "Count",
"Search for Element": "Search for Element",
"Moving Element": "Moving Element",
"Consolidation Factor": "Consolidation Factor",
"Remove from source elements": "Remove from source elements",
"Add Cube": "Add Cube",
"Delete Cube": "Delete Cube",
"Rename Cube": "Rename Cube",
"Clear Cube": "Clear Cube",
"Export Cube": "Export Cube",
"Rule Edit": "Rule Edit",
"Cube Information": "Cube Information",
"Add Dimension": "Add Dimension",
"Delete Dimension": "Delete Dimension",
"Rename Dimension": "Rename Dimension",
"Edit Dimension": "Edit Dimension",
"Export Dimension": "Export Dimension",
"Dimension Information": "Dimension Information",
"Total Number of Elements": "Total Number of Elements",
"Number of Numeric Elements": "Number of Numeric Elements",
"Number of String Elements": "Number of String Elements",
"Number of Consolidated Elements": "Number of Consolidated Elements",
"Delete Element": "Delete Element",
"_msg: Delete Element": "Are you sure you want to delete Element?",
"Delete Attribute": "Delete Attribute",
"_msg: Delete Attribute": "Are you sure you want to delete Attribute?",
"_msg: Delete Dimension": "Are you sure you want to delete Dimension?",
"_msg: Delete Cube": "Are you sure you want to delete Cube?",
"Change Element Type": "Change Element Type",
"_msg: Change Element Type": "Changing element type could lead to loss of data.<br>Are you sure you want to change type?",
"Search Element": "Search Element",
"_msg: Search Element": "Enter name of Element for Search",
"Search": "Search",
"Element": "Element",
"was not find in dimension": "was not find in dimension",
"New Element": "New Element",
"Enter name for new Element": "Enter name for new Element",
"New Attribute": "New Attribute",
"Enter name for new Attribute": "Enter name for new Attribute",
"Rename Element": "Rename Element",
"Enter new name for Element": "Enter new name for Element",
"Rename Attribute": "Rename Attribute",
"Enter new name for Attribute": "Enter new name for Attribute",
"New Dimension": "New Dimension",
"Enter name for Dimension": "Enter name for Dimension",
"Enter new name for Dimension": "Enter new name for Dimension",
"Enter new name for Cube": "Enter new name for Cube",
"Change Factor": "Change Factor",
"Enter new consolidation factor": "Enter new consolidation factor",
"Storing": "Storing",
"_msg: new Dim": "Storing new Dimension in Database.",
"_err: new Dim": "Adding new Dimension failed!",
"_msg: rename Dim": "Storing new Dimension Name in Database.",
"_err: rename Dim": "Renaming Dimension failed!",
"_msg: del Dim": "Deleting Dimension.",
"_err: del Dim": "Deleting Dimension failed!",
"_msg: ren Cube": "Storing new Cube Name in Database.",
"_msg: del Cube": "Deleting Cube.",
"_err: del Cube": "Deleting Cube failed!",
"_msg: new Elem": "Storing new Element in Database.",
"_msg: del Elem": "Deleting Element from Database.",
"_msg: cons Elem": "Storing consolidated Element.",
"_msg: rename Elem": "Storing new Element Name in Database.",
"_msg: change type Elem": "Storing new Element Type in Database.",
"_msg: moving Element": "Storing Element on new position.",
"Identifier": "Identifier",
"Number of Elements": "Number of Elements",
"Number of N elem.": "Number of N elements",
"Number of S elem.": "Number of S elements",
"Number of C elem.": "Number of C elements",
"Maximum Level": "Maximum Level",
"Maximum Indent": "Maximum Indent",
"Maximum Depth": "Maximum Depth",
"Number of Dimensions": "Number of Dimensions",
"Dimensions": "Dimensions",
"Number of Cells": "Number of Cells",
"Number of Filled Cells": "Number of Filled Cells",
"Filed Ratio": "Filed Ratio",
"Status": "Status",
"Add Subset": "Add Subset",
"is not allowed": "is not allowed",
"Hit RETURN to add Dimension": "Hit RETURN to add Dimension",
"Click on the \"New Cube\" button to add Cube": "Click on the \"New Cube\" button to add Cube",
"Hit RETURN to add Elements": "Hit RETURN to add Elements",
"Add Element from list of Elements": "Add Element from list of Elements",

//PALO Cube Wizard
"PALO Cube Wizard": "PALO Cube Wizard",
"Finish >>": "Finish >>",
"Available Dimensions": "Available Dimensions",
"Selected Dimensions": "Selected Dimensions",
"Cube name": "Cube name",
"_tit: Cube Creation Wizard": "Cube<br>Creation<br>Wizard",
"_msg: Cube Wizard": "This Wizard will allow you to setup new Cube.",
"Information": "Information",
"_msg: new Cube": "Storing new Cube in Database.",
"_err: create new Cube": "Not Correct data for Cube. Name or Dimensions missing.",
"_msg: Cube added": "Cube is successfully stored in Database.",
"Close Cube Wizard": "Close Cube Wizard",
"_msg: close Cube Wizard": "Are you sure, you want to exit without saving?",

//Choose Element
"[none]": "[none]",
"Element not found!": "Element is not found!",
"Search & Select": "Search & Select",

//Palo Wizard
"PALO Wizard": "PALO Wizard",
"_msg: Palo Wizard": "This wizard will allow you to add/delete databases and servers",
"_tit: Palo Wizard": "Palo Wizard",
"Select connection": "Select connection",
"New Database": "New Database",
"Delete Database": "Delete Database",
"New Server": "New Server",
"Delete Server": "Delete Server",
"Disconnect": "Disconnect",
"Connect": "Connect",
"_msg: Palo Wizard Delete Server": "This operation will delete server from list!",
"Connection Name": "Connection Name",
"Server": "Server",
"Port": "Port",
"Username": "Username",
"Confirm Password": "Confirm Password",
"Test Connection": "Test Connection",
"_err: Wrong Pass": "Incorrect confirmed password.",
"_msg: Test Conn Ok": "Test successful.",
"_err: Test Conn Not Ok": "Test wasn't successful.",
"_err: Db not added": "Error on Database creation.",
"_msg: Db added": "New Database is successfully added.",
"_err: Db not deleted": "Wasn't able to delete Database.",
"_msg: Db deleted": "Database is successfully deleted.",
"_msg: Server added": "New Server is successfully added.",
"_err: Server not added": "Error on Server creation.",
"_msg: Server edited": "Server is successfully edited.",
"_err: Server not edited": "Error on Server editing.",
"_msg: Server deleted": "Server is successfully deleted.",
"_err: Server not deleted": "Wasn't able to delete Server.",
"_msg: Delete Database": "Are you sure you wont to completely delete the database from the server.",
"_msg: Delete Server": "Are you sure you wont to remove server from list.",
"Edit Server": "Edit Server",

//PALO Rule Editor
"Rule":"Rule",
"Updated":"Updated",
"Rule Editor":"Rule Editor",
"List of defined rules":"List of defined rules",
"Comment": "Comment",
"Import Rules": "Import Rules",
"impPaloRule_fieldLbl": "The file to import",
"impDlg_msgFieldBlank": "Please choose a file",

// Copied for app
"Choose Element": "Choose Element",
"Name": "Name",
"New Database Name": "New Database Name",
"Select database to delete": "Select database to delete",
"Store login data": "Store login data",
"Data": "Data",

//ConstListEditor class
"New Constant": "New Constant",
"Delete Constants": "Delete Constants",
"_msg: Delete Constants": "Are you sure you want to delete selected constants?"

};

Jedox.err.i18n = {
     1: 'GenericException Error'
,  100: 'RuntimeException Error'
,  101: 'ParsingFailedException Error'
,  102: 'NotImplementedException Error'
,  103: 'InvalidSessionException Error'
, 1000: 'InsufficientRightsException Error'
, 1100: 'EventHandlerAbortException Error'
, 1200: 'ClipboardInvalidIndexException Error'
, 1300: 'InvalidNameException Error'
, 1400: 'InterpreterRuntimeError Error'
, 1500: 'InvalidFormulaException Error'
, 1600: 'CyclicDependencyException Error'
, 1700: 'ArrayException Error'
, 1800: 'NoWorkbookSelectedException Error'
, 1801: 'NoWorksheetSelectedException Error'
, 1802: 'NoApplicationSelectedException Error'
, 1900: 'LoadApplicationException Error'
, 1901: 'LoadException Error'
, 1902: 'SaveException Error'
, 2000: 'ConditionalFormatException Error'
, 2100: 'NamedFormulaException Error'
, 2101: 'NamedFormulaDoesNotExistException Error'
, 2200: 'CopyWorksheetException Error'
, 2300: 'RangeException Error'
, 2400: 'MergedCellException Error'
, 2500: 'AuthenticationException Error'
, 2600: 'CellDimensionException Error'
, 2700: 'SessionException Error'
, 2800: 'InvalidGroupException Error'
, 2900: 'InvalidUserException Error'
, 3000: 'TranslationTableException Error'
, 3100: 'WorksheetCopyException Error'
, 3200: 'WorkbookCloneException Error'
, 3300: 'ExtensionRegistryException Error'
, 3400: 'ExtensionCallerException Error'
, 3500: 'CyclicArrayException Error'
, 3600: 'WorksheetElementException Error'
, 3700: 'FormatException Error'
, 3800: 'StyleManagerException Error'
, 3900: 'BoundedPointException Error'
, 4000: 'FilterRegistryException Error'
, 4100: 'ContainerWrapperException Error'
, 4200: 'SelectionToLargeException Error'
, 4300: 'ExtensionFailureException Error'
, 4400: 'PaloConnectorException Error'
, 4500: 'FatalException Error'
, 4600: 'ArrayFormulaOnMergedCellException Error'
, 4700: 'ValueConversionException Error'
,   R1: 'GenericException Error'
,   R2: 'Error in {FILE} on line {LINE}!'
, P0_0: 'Palo Action failed.'
, P1_0: 'Database name is not correct.'
, P1_1: 'Dimension already exists.'
, P1_2: 'Dimension doesn\'t exist.'
, P1_3: 'Dimension used by some Cubes.'
, P1_4: 'Element already exists.'
, P1_5: 'Subset not deleted.'
, P1_6: 'Subset not renamed.'
, P1_7: 'Unable to get list of databases for "{conn_name}" connection.'
, P1_8: 'Subset {ss_name} can\'t be created.'
, P1_9:	'You don\'t have enough rights for this action!'
, P1_10: 'Unabe to change connection status.'
, P1_11: 'Unable to get config palo connection.'
, P1_12: 'Bad PALO connection type for connection name: {conn_name}.'
, P1_13: 'Unable to make connection for connection name: {conn_name}.'
, P1_14: 'Unable to get user for connection name: {conn_name}.'
, P1_15: 'Unable to create new database: {db_name}.'
, P1_16: 'Unable to get Paste View config data.'
, P1_17: 'Unable to delete database: {db_name}.'
, P1_18: 'Unable to generate Subset List!'
};
