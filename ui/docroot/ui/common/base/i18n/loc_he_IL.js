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
 * SVN: $Id: loc_he_IL.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "ביטול",
"File": "קובץ",
"New": "חדש",
"Open": "פתיחה",
"Close": "סגירה",
"Save": "שמירה",
"Properties": "מאפיינים",
"Edit": "עריכה",
"Cut": "גזירה",
"Copy": "העתקה",
"Paste": "הדבקה",
"View": "תצוגה",
"List": "רשימה",
"Hide": "הסתרה",
"Help": "עזרה",
"Create new document": "יצירת מסמך חדש",
"Open document": "פתיחת מסמך",
"Save document": "שמירת מסמך",
"Bold": "הבלטה",
"Italic": "נטוי",
"Underline": "קו תחתי",
"Delete": "מחיקה",
"Rename": "שינוי שם",
"Select All": "בחר הכל",
"Type": "סוג",
"Warning": "אזהרה",
"Password": "ססמה",
"Layout": "מערך",
"General": "כללי",
"Preview": "תצוגה מקדימה",
"Refresh": "ריענון",
"None": "ללא",
"Bottom": "תחתית",
"Right": "ימין",
"Up": "מעלה",
"New Folder": "תיקייה חדשה",
"Thumbnails": "צלמיות",
"Details": "פרטים",
"Description": "תיאור",
"Options": "אפשרויות",
"Modeller": "Modeller",
"Home": "בית",
"Size": "גודל",

"Quick View": "תצוגת מנהל",
"Designer Preview": "תצוגת פיתוח",
"Active": "פעיל",
"Path": "נתיב",
"Apply": "החל",
"Rename Sheet": "שינוי שם גיליון",

//Paste Subset Dialog
"_tit: hb List Editor": "DynaRange List Editor",
"Subset Editor": "עריכת Subset",
"Subset General Settings": "הגדרות Subset כלליות",
"Dimension": "מימד",
"Select First Alias": "בחר Alias ראשון",
"Select Second Alias": "בחר Alias שני",
"Alias": "כינוי",
"Optional Settings": "הגדרות אופציונליות",
"Hierarchy enumeration": "Hierarchy enumeration",
"Hierarchy": "היררכיה",
"Text": "טקסט",
"Picklist": "Picklist",
"Attribute": "תכונה",
"Sort": "מיין",
"Level": "רמה",
"Depth": "עומק",
"Flat": "שטוח",
"Show parents below children": "הראה אבות תחת הבנים",
"Show duplicates": "הראה כפילויות",
"Show children of hidden elements": "הראה בנים של אלמנטים מוסתרים",
"_msg: hb Lists": "DynaRange Lists",
"[_name: hb List]": "[DynaRange List]",
"Formula Subset": "Formula Subset",
"[Formula Subset]": "[Formula Subset]",
"Local Subsets": "Local Subsets",
"Global Subsets": "Global Subsets",
"Stored Subsets": "Stored Subsets",
"Auto": "אוטומטי",
"By Definition": "על פי הגדרה",
"By Element name": "לפי שם אלמנט",
"By Alias": "לפי כינוי",
"By Value": "לפי ערך",
"By Attribute": "לפי תכונה",
"All Elements": "כל האלמנטים",
"Base Elements Only": "אלמנטים בסיס בלבד",
"Consolidated Elements Only": "Consolidated Elements Only",
"Reverse": "הפוך",
"Sort at Level": "מיין לפי רמה",
"Sorting behaviour": "Sorting behavior",
"Reverse Order": "סדר הפוך",
"Type Limitation": "סוג הגבלה",
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
"[All Elements]": "[כל האלמנטים]",
"Filter elements hierarchically": "סנן אלמנטים לפי הירריכה",
"Cyclic list": "רשימה מחזורית",
"Below": "תחת",
"Above": "מעל\n",
"Consolidated": "מאוחד",
"Base Elements": "אלמנט בסיס",
"Activate this filter": "הפעל מסנן",
"Exclusive": "בלעדי",
"Filter Element by type": "סנן אלמנט לפי סוג",
"Filter elements by Level": "סנן אלמנטים לפי רמה",
"List length": "רשימת אורך",
"Start level": "רמה התחלתית",
"Indent Enumeration": "Indent Enumeration",
"End level": "רמה סופית",
"Settings": "הגדרות",
"_subsetTextTabExamples": 'Examples:<br>' +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "<b>PERL-Regular expressions</b>",
"Behaviour": "התנהגות",
"Dimension Contents": "תוכן המימד",
"Please select how to insert choosen elements": "אנא בחר כיצד להוסיף אלמנטים נבחרים",
"_subsetAttrTabExample": '<br>Examples:<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "משתנים",
"Alias 1": "כינוי 1",
"Alias 2": "כינוי 2",
"Level Start": "רמת התחלה",
"Level End": "רמת סיום",
"Criteria": "קריטריון",
"Sort Attribute": "Sort Attribute",
"Sort Level": "לפי רמה",
"Quick": "Quick",
"SUM OF THE ELEMENTS": "סכום האלמנטים",
"ALL ELEMENTS": "כל האלמנטים",
"AVEREGE OF THE ELEMENTS": "ממוצע של האלמנטים",
"MAXIMUM OF THE ELEMETNS": "מקסימום מהאלמנטים",
"ANY ELEMENT": "כל אלמנט",
"MINIMUM OF THE ELEMENTS": "מינימום מהאלמנטים",
"STRING": "סדרה",
"Please select and set attribute fields": "Please select and set attribute fields",
"Select Cube": "בחר קוביה",
"Indent": "Indent",
"FRONT": "קדימה",
"BACK": "אחורה",
"MERGE": "אחד",
"SUBTRACT": "SUBTRACT",
"Take topmost elements": "Take topmost elements",
"Take all upper elements up to %": "Take all upper elements up to %",
"Take all lower elements up to %": "Take all lower elements up to %",
"List Length": "List Length",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Picklist Type",
"Cube": "קוביה",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Topmost",
"Upper": "עליון",
"Lower": "תחתון",
"Slice operators": "Slice operators",
"AND": "וגם",
"Named Variables": "Named Variables",
"subset_Indent": "Indent",
"Obtaining preview data": "Obtaining preview data",
"Unable to resolve value for": "Unable to resolve value for",
"_msg: paloSbstDFilterEnabled": "When Data Filter is enabled, processing to get preview list can take more time",

//PALO Modeller
"PALO Modeller": "PALO Modeller",
"Error": "שגיאה",
"Elements": "אלמנטים",
"Attributes": "Attributes",
"Subsets": "Subsets",
"Consolidated Elements": "אלמנטי איחוד",
"show Tree": "הצג עץ",
"<< Database": "<< בסיס נתונים",
"Expand All": "הרחב הכל",
"Collapse All": "בווץ הכל",
"Choose Server/Database": "בחר שרת/בסיס נתונים",
"Dimensions and Global Subsets": "Dimensions and Global Subsets",
"Cubes": "קוביות",
"Database": "בסיס נתונים",
"system": "מערכת",
"attributes": "attributes",
"normal": "normal",
"loaded": "loaded",
"not loaded": "not loaded",
"_err: Timer": "Time out for Server request.",
"_msg: Timer": "Waiting time went off.",
"Add": "הוסף",
"Consolidate": "איחוד",
"Numeric": "מספר",
"String": "מחרוזת",
"Copy Elements": "העתק אלמנטים",
"Paste Elements": "הדבק אלמנטים",
"Move Element to the Beginning": "הזז אלמנט להתחלה",
"Move Element to the End": "הזז אלמנט לסוף",
"Count": "ספור",
"Search for Element": "חפש אלמנט",
"Moving Element": "הזז אלמנט",
"Consolidation Factor": "פקטור איחוד",
"Remove from source elements": "Remove from source elements",
"Add Cube": "הוסף קוביה",
"Delete Cube": "מחק קוביה",
"Rename Cube": "שנה שם קוביה",
"Clear Cube": "נקה קוביה",
"Export Cube": "יצוא קוביה",
"Rule Edit": "ערוך כלל",
"Cube Information": "Cube Information",
"Add Dimension": "Add Dimension",
"Delete Dimension": "Delete Dimension",
"Rename Dimension": "Rename Dimension",
"Edit Dimension": "ערוך מימד",
"Export Dimension": "יצוא מימד",
"Dimension Information": "מידע אודות המימד",
"Total Number of Elements": "Total Number of Elements",
"Number of Numeric Elements": "Number of Numeric Elements",
"Number of String Elements": "Number of String Elements",
"Number of Consolidated Elements": "Number of Consolidated Elements",
"Delete Element": "מחק אלמנט",
"_msg: Delete Element": "Are you sure you want to delete Element?",
"Delete Attribute": "Delete Attribute",
"_msg: Delete Attribute": "Are you sure you want to delete Attribute?",
"_msg: Delete Dimension": "Are you sure you want to delete Dimension?",
"_msg: Delete Cube": "האם הינך בטוח שברצונך למחוק את הקוביה?",
"Change Element Type": "שנה סוג אלמנט",
"_msg: Change Element Type": "Changing element type could lead to loss of data.<br>Are you sure you want to change type?",
"Search Element": "חפש אלמנט",
"_msg: Search Element": "הכנס שם אלמנט לחיפוש",
"Search": "חפש",
"Element": "אלמנט",
"was not find in dimension": "לא נמצא במימד",
"New Element": "אלמנט חדש",
"Enter name for new Element": "הכנס שם למימד חדש",
"New Attribute": "תכונה חדשה",
"Enter name for new Attribute": "הכנס שם לתכונה חדשה",
"Rename Element": "שנה שם אלמנט",
"Enter new name for Element": "הכנס שם חדש לאלמנט",
"Rename Attribute": "שנה שם תכונה",
"Enter new name for Attribute": "הכנס שם חדש",
"New Dimension": "מימד חדש",
"Enter name for Dimension": "הכנס שם למימד",
"Enter new name for Dimension": "הכנס שם חדש למימד",
"Enter new name for Cube": "הכנס שם חדש לקוביה",
"Change Factor": "שנה פקטור",
"Enter new consolidation factor": "Enter new consolidation factor",
"Storing": "אחסון",
"_msg: new Dim": "אחסון מימד חדש בבסיס הנתונים.",
"_err: new Dim": "הוספת מימד חדש נכשל!",
"_msg: rename Dim": "אחסון שם מימד חדש בבסיס הנתונים.",
"_err: rename Dim": "שינוי שם מימד נכשל!",
"_msg: del Dim": "מחיקת מימד.",
"_err: del Dim": "מחיקת מימד נכשל!",
"_msg: ren Cube": "אחסון שם קוביה חדש בבסיס הנתונים.",
"_msg: del Cube": "מחיקת קוביה.",
"_err: del Cube": "מחיקת קוביה נכשל.",
"_msg: new Elem": "אחסון אלמנט חדש בבסיס הנתונים.",
"_msg: del Elem": "מחיקת אלמנט מבסיס הנתונים.",
"_msg: cons Elem": "אחסון אלמנט מאוחד.",
"_msg: rename Elem": "אחסן שם אלמנט חדש בבסיס הנתונים.",
"_msg: change type Elem": "אחסן סוג אלמנט חדש בבסיס הנתונים.",
"_msg: moving Element": "אחסון אלמנט על המיקום החדש.",
"Identifier": "זהה",
"Number of Elements": "מספר אלמנטים",
"Number of N elem.": "Number of N elements",
"Number of S elem.": "Number of S elements",
"Number of C elem.": "Number of C elements",
"Maximum Level": "רמה מקסימלית",
"Maximum Indent": "Maximum Indent",
"Maximum Depth": "עמוק מקסימלי",
"Number of Dimensions": "מספר מימדים",
"Dimensions": "מימדים",
"Number of Cells": "מספר תאים",
"Number of Filled Cells": "Number of Filled Cells",
"Filed Ratio": "Filed Ratio",
"Status": "סטטוס",
"Add Subset": "Add Subset",
"is not allowed": "is not allowed",
"Hit RETURN to add Dimension": "Hit RETURN to add Dimension",
"Click on the \"New Cube\" button to add Cube": "Click on the \"New Cube\" button to add Cube",
"Hit RETURN to add Elements": "Hit RETURN to add Elements",
"Add Element from list of Elements": "הוסף אלמנט מתוך רשימה",

//PALO Cube Wizard
"PALO Cube Wizard": "PALO Cube Wizard",
"Finish >>": "סיום >>",
"Available Dimensions": "Available Dimensions",
"Selected Dimensions": "מימדים שנבחרו",
"Cube name": "שם קוביה",
"_tit: Cube Creation Wizard": "Cube<br>Creation<br>Wizard",
"_msg: Cube Wizard": "This Wizard will allow you to setup new Cube.",
"Information": "מידע",
"_msg: new Cube": "אחסון קוביה חדשה בבסיס הנתונים.",
"_err: create new Cube": "Not Correct data for Cube. Name or Dimensions missing.",
"_msg: Cube added": "הקוביה אוחסנה בהצלחה בבסיס הנתונים.",
"Close Cube Wizard": "סגור את אשף הקוביה",
"_msg: close Cube Wizard": "האם הינך בטוח שברצונך לצאת ללא שמירה?",

//Choose Element
"[none]": "[none]",
"Element not found!": "אלמנט לא נמצא!",
"Search & Select": "חפש ובחר",

//Palo Wizard
"PALO Wizard": "PALO Wizard",
"_msg: Palo Wizard": "This wizard will allow you to add/delete databases and servers",
"_tit: Palo Wizard": "Palo Wizard",
"Select connection": "בחר חיבור",
"New Database": "בסיס נתונים חדש",
"Delete Database": "מחק בסיס נתונים",
"New Server": "שרת חדש",
"Delete Server": "מחק שרת",
"Disconnect": "התנתק",
"Connect": "התחבר",
"_msg: Palo Wizard Delete Server": "פעולה זו תמחק את השרת מהרשימה!",
"Connection Name": "שם חיבור",
"Server": "שרת",
"Port": "פורט",
"Username": "שם משתמש",
"Confirm Password": "אשר סיסמה",
"Test Connection": "בדיקת חיבור",
"_err: Wrong Pass": "אישור סיסמה שגויה.",
"_msg: Test Conn Ok": "הבדיקה עברה בהצלחה",
"_err: Test Conn Not Ok": "הבדיקה נכשלה.",
"_err: Db not added": "שגיאה ביצירת בסיס הנתונים",
"_msg: Db added": "בסיס נתונים חדש נוסף בהצלחה.",
"_err: Db not deleted": "לא ניתן למחוק את בסיס הנתונים.",
"_msg: Db deleted": "בסיס הנתונים נמחק בהצלחה.",
"_msg: Server added": "שרת חדש נוסף בהצלחה.",
"_err: Server not added": "שגיאה ביצירת השרת.",
"_msg: Server edited": "השרת נערך בהצלחה.",
"_err: Server not edited": "שגיאה בעריכת השרת.",
"_msg: Server deleted": "שרת נמחק בהצלחה.",
"_err: Server not deleted": "לא ניתן למחוק את השרת.",
"_msg: Delete Database": "האם אתה בטוח שברצונך למחוק לגמרי את בסיס הנתונים משרת?",
"_msg: Delete Server": "האם אתה בטוח שברצונך להסיר את השרת מהרשימה?",
"Edit Server": "ערוך שרת",

//PALO Rule Editor
"Rule":"כלל",
"Updated":"מעודכן",
"Rule Editor":"עריכת כלל",
"List of defined rules":"List of defined rules",
"Comment": "הערה",
"Import Rules": "יבוא כלל",
"impPaloRule_fieldLbl": "קובץ ליבוא",
"impDlg_msgFieldBlank": "בחר קובץ",

// Copied for app
"Choose Element": "בחר אלמנט",
"Name": "שם",
"New Database Name": "שם בסיס נתונים חדש",
"Select database to delete": "בחר בסיס נתונים למחיקה",
"Store login data": "Store login data",
"Data": "נתונים",

//ConstListEditor class
"New Constant": "New Constant",
"Delete Constants": "Delete Constants",
"_msg: Delete Constants": "Are you sure you want to delete selected constants?",
"Move Up": "הזז למעלה",
"Move Down": "הזז למטה",
"No rule selected. Please select rule.": "כלל לא נבחרו. נא לבחור כלל.",
"No file selected. Please select file.": "קובץ לא נבחרו. נא לבחור קובץ.",
"Acquiring Server List": "Acquiring Server List",
"Opening dialog": "Opening dialog",
"fopperLic": "PDF printer license",
"License could not be checked": "License could not be checked",
"License could not be found.": "License could not be found.",
"License could not be read.": "License could not be read.",
"License is not valid.": "License is not valid."

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
, P1_0: 'שם בסיס נתונים לא נכן.'
, P1_1: 'מימד כבר קיים.'
, P1_2: 'מימד לא קיים.'
, P1_3: 'מימד נמצא בשימוש בקוביה.'
, P1_4: 'אלמנט כבר קיים.'
, P1_5: 'Subset not deleted.'
, P1_6: 'Subset not renamed.'
, P1_7: 'Unable to get list of databases for "{conn_name}" connection.'
, P1_8: 'Subset {ss_name} can\'t be created.'
, P1_9:	'אין לך הרשאות לפעולה זו!'
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
