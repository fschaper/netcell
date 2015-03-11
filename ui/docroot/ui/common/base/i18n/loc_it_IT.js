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
 * SVN: $Id: loc_it_IT.js 4659 2011-02-25 08:01:13Z l10n-tool $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Anulla",
"File": "File",
"New": "Nuovo",
"Open": "Apri",
"Close": "Chiudi",
"Save": "Salva",
"Properties": "Proprietà",
"Edit": "Modifica",
"Cut": "Taglia",
"Copy": "Copia",
"Paste": "Incolla",
"View": "Vista",
"List": "Lista",
"Hide": "Nascondi",
"Help": "Aiuto",
"Create new document": "Crea nuovo documento",
"Open document": "Apri documento",
"Save document": "Salva documento",
"Bold": "Grassetto",
"Italic": "Corsivo",
"Underline": "Underline",
"Delete": "Elimina",
"Rename": "Rinomina",
"Select All": "Seleziona Tutto",
"Type": "Tipo",
"Warning": "Alarme",
"Password": "Password",
"Layout": "Layout",
"General": "Generale",
"Preview": "Anteprima",
"Refresh": "Aggiorna",
"None": "Nessuno",
"Bottom": "Bottom",
"Right": "Right",
"Up": "Su",
"New Folder": "Nuova cartella",
"Thumbnails": "Icone",
"Details": "Dettagli",
"Description": "Descrizione",
"Options": "Opzioni",
"Modeller": "Modella",
"Home": "Home",
"Size": "Size",

"Quick View": "Anteprima Admin",
"Designer Preview": "Anteprima Designer",
"Active": "Attivo",
"Path": "Path",
"Apply": "Applica",
"Rename Sheet": "Rinomina foglio",

//Paste Subset Dialog
"_tit: hb List Editor": "DynaRange List Editor",
"Subset Editor": "Subset Editor",
"Subset General Settings": "Subset Impostazioni Generali",
"Dimension": "Dimensione",
"Select First Alias": "Seleziona Alias 1",
"Select Second Alias": "Seleziona Alias 2",
"Alias": "Alias",
"Optional Settings": "Impostazioni opzionali",
"Hierarchy enumeration": "Enumerazione gerarchia",
"Hierarchy": "Gerarchia",
"Text": "Testo",
"Picklist": "Picklist",
"Attribute": "Attributo",
"Sort": "Ordina",
"Level": "Livello",
"Depth": "Profondità",
"Flat": "Profondità",
"Show parents below children": "Show parents below children",
"Show duplicates": "Show duplicates",
"Show children of hidden elements": "Show children of hidden elements",
"_msg: hb Lists": "Liste DynaRange",
"[_name: hb List]": "[Lista DynaRange]",
"Formula Subset": "Formula Subset",
"[Formula Subset]": "[Formula Subset]",
"Local Subsets": "Subset locali",
"Global Subsets": "Subset globali",
"Stored Subsets": "Subset salvati",
"Auto": "Auto",
"By Definition": "Per Definizione",
"By Element name": "Per Nome Elemento",
"By Alias": "Per Alias",
"By Value": "Per Valore",
"By Attribute": "Per Attributo",
"All Elements": "Tutti gli elementi",
"Base Elements Only": "Solo Elementi Base",
"Consolidated Elements Only": "Solo Elementi consolidati",
"Reverse": "Reverse",
"Sort at Level": "Ordina al Livello",
"Sorting behaviour": "Sorting behavior",
"Reverse Order": "Reverse Order",
"Type Limitation": "Type Limitation",
"New Subset": "Subset Nuovo",
"Enter name for Subset": "Inserisci il nome per il Subset",
"Delete Subset": "Elimina Subset",
"_msg: Delete Subset": "Are you sure you want to delete Subset?",
"Rename Subset": "Rinomina Subset",
"Enter new name for Subset": "Inserire il nome nuovo per il Subset",
"_msg: update Subset": "Salvo Subset.",
"_msg: new Subset": "Salvo Subset Nuovo.",
"_msg: delete Subset": "Elimino Subset.",
"_msg: rename Subset": "Storing new name for Subset.",
"[All Elements]": "[Tutti gli elementi]",
"Filter elements hierarchically": "Filter elements hierarchically",
"Cyclic list": "Cyclic list",
"Below": "Sotto",
"Above": "Sopra",
"Consolidated": "Consolidato",
"Base Elements": "Elementi base",
"Activate this filter": "Attiva questo filtro",
"Exclusive": "Exclusive",
"Filter Element by type": "Filtra elementi per tipo",
"Filter elements by Level": "Filtra elementi per livello",
"List length": "Lunghezza lista",
"Start level": "Livello di partenza",
"Indent Enumeration": "Indento Enumerazione",
"End level": "Livello finale",
"Settings": "Impostazioni",
"_subsetTextTabExamples": 'Examples:<br>' +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "<b>PERL-Regular expressions</b>",
"Behaviour": "Comportamento",
"Dimension Contents": "Contenuto Dimensioni",
"Please select how to insert choosen elements": "Please select how to insert selected elements",
"_subsetAttrTabExample": '<br>Examples:<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Variabile",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Livello di partenza",
"Level End": "Livello finale",
"Criteria": "Criterio",
"Sort Attribute": "Attributo ordinamento",
"Sort Level": "Livello ordinamento",
"Quick": "Quick",
"SUM OF THE ELEMENTS": "SUM OF THE ELEMENTS",
"ALL ELEMENTS": "ALL ELEMENTS",
"AVEREGE OF THE ELEMENTS": "AVEREGE OF THE ELEMENTS",
"MAXIMUM OF THE ELEMETNS": "MAXIMUM OF THE ELEMETNS",
"ANY ELEMENT": "ANY ELEMENT",
"MINIMUM OF THE ELEMENTS": "MINIMUM OF THE ELEMENTS",
"STRING": "STRING",
"Please select and set attribute fields": "Please select and set attribute fields",
"Select Cube": "Seleziona Cubo",
"Indent": "Indento",
"FRONT": "FRONT",
"BACK": "BACK",
"MERGE": "MERGE",
"SUBTRACT": "SUBTRACT",
"Take topmost elements": "Take topmost elements",
"Take all upper elements up to %": "Take all upper elements up to %",
"Take all lower elements up to %": "Take all lower elements up to %",
"List Length": "Lunghezza Lista",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Tipo Picklist",
"Cube": "Cubo",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Topmost",
"Upper": "Upper",
"Lower": "Lower",
"Slice operators": "Operatori slice",
"AND": "AND",
"Named Variables": "Named Variables",
"subset_Indent": "Indento",
"Obtaining preview data": "Obtaining preview data",
"Unable to resolve value for": "Unable to resolve value for",
"_msg: paloSbstDFilterEnabled": "When Data Filter is enabled, processing to get preview list can take more time",

//PALO Modeller
"PALO Modeller": "PALO Modeller",
"Error": "Errore",
"Elements": "Elementi",
"Attributes": "Attributi",
"Subsets": "Subset",
"Consolidated Elements": "Elementi consolidati",
"show Tree": "Mostra albero",
"<< Database": "<< Database",
"Expand All": "Espandi tutto",
"Collapse All": "Riduci tutto",
"Choose Server/Database": "Seleziona Server/Database",
"Dimensions and Global Subsets": "Dimensioni e Subset globali",
"Cubes": "Cubi",
"Database": "Database",
"system": "system",
"attributes": "attributi",
"normal": "normale",
"loaded": "loaded",
"not loaded": "not loaded",
"_err: Timer": "Time out for Server request.",
"_msg: Timer": "Waiting time went off.",
"Add": "Aggiungi",
"Consolidate": "Consolida",
"Numeric": "Numerico",
"String": "Stringa",
"Copy Elements": "Copia Elementi",
"Paste Elements": "Incolla Elementi",
"Move Element to the Beginning": "Move Element to the Beginning",
"Move Element to the End": "Move Element to the End",
"Count": "Conta",
"Search for Element": "Cerca elementi",
"Moving Element": "Moving Element",
"Consolidation Factor": "Consolidation Factor",
"Remove from source elements": "Remove from source elements",
"Add Cube": "Aggiungi Cubo",
"Delete Cube": "Elimina Cubo",
"Rename Cube": "Rinomina Cubo",
"Clear Cube": "Svuota Cubo",
"Export Cube": "Esporta Cubo",
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
"Delete Element": "Elimina Elemento",
"_msg: Delete Element": "Sicuro di voler eliminare questo Elemento?",
"Delete Attribute": "Elimina Attributo",
"_msg: Delete Attribute": "Sicuro di voler eliminare questo Attributo?",
"_msg: Delete Dimension": "Sicuro di voler eliminare questa Dimensione?",
"_msg: Delete Cube": "Sicuro di voler eliminare questo Cubo",
"Change Element Type": "Modifica tipo elemento",
"_msg: Change Element Type": "Changing element type could lead to loss of data.<br>Are you sure you want to change type?",
"Search Element": "Cerca Elemento",
"_msg: Search Element": "Enter name of Element for Search",
"Search": "Cerca",
"Element": "Elemento",
"was not find in dimension": "was not find in dimension",
"New Element": "Nuovo Element",
"Enter name for new Element": "Inserire nome per l\'elemento nuovo",
"New Attribute": "Nuovo Attributo",
"Enter name for new Attribute": "Enter name for new Attribute",
"Rename Element": "Rinomina Elemento",
"Enter new name for Element": "Inserire nome per l\'elemento",
"Rename Attribute": "Rinomina Attributo",
"Enter new name for Attribute": "Inserire nome per l\'attributo",
"New Dimension": "Nuova Dimensione",
"Enter name for Dimension": "Inserire nome per la Dimensione",
"Enter new name for Dimension": "Inserire nome per la Dimensione",
"Enter new name for Cube": "Inserire nome nuovo per il Cubo",
"Change Factor": "Change Factor",
"Enter new consolidation factor": "Enter new consolidation factor",
"Storing": "Salvo",
"_msg: new Dim": "Storing new Dimension in Database.",
"_err: new Dim": "Adding new Dimension failed!",
"_msg: rename Dim": "Salvo nuovo nome Dimensione nel Database.",
"_err: rename Dim": "Rinominazione Dimensione fallita!",
"_msg: del Dim": "Elimino Dimensione.",
"_err: del Dim": "Eliminazione Dimensione fallita!",
"_msg: ren Cube": "Salvo nuovo nome Cubo nel Database.",
"_msg: del Cube": "Elimino Cubo.",
"_err: del Cube": "Eliminazione Cubo fallita!",
"_msg: new Elem": "Salvo Elemento nuovo nel Database.",
"_msg: del Elem": "Elimino Elemento dal Database.",
"_msg: cons Elem": "Salvo Elementi Consolidati.",
"_msg: rename Elem": "Salvo nuovo nome Elemento nel Database.",
"_msg: change type Elem": "Salvo nuovo Tipo Elemento nel Database.",
"_msg: moving Element": "Salvo Elemento sulla posizione nuova.",
"Identifier": "Identifier",
"Number of Elements": "Numero di Elementi",
"Number of N elem.": "Numero di Elementi N",
"Number of S elem.": "Numero di Elementi S",
"Number of C elem.": "Number of C elements",
"Maximum Level": "Maximum Level",
"Maximum Indent": "Maximum Indent",
"Maximum Depth": "Maximum Depth",
"Number of Dimensions": "Number of Dimensions",
"Dimensions": "Dimensions",
"Number of Cells": "Number of Cells",
"Number of Filled Cells": "Number of Filled Cells",
"Filed Ratio": "Filed Ratio",
"Status": "Stato",
"Add Subset": "Aggiungi Subset",
"is not allowed": "non permesso",
"Hit RETURN to add Dimension": "Hit RETURN to add Dimension",
"Click on the \"New Cube\" button to add Cube": "Click on the \"New Cube\" button to add Cube",
"Hit RETURN to add Elements": "Hit RETURN to add Elements",
"Add Element from list of Elements": "Add Element from list of Elements",

//PALO Cube Wizard
"PALO Cube Wizard": "Assistente PALO Cube",
"Finish >>": "Finish >>",
"Available Dimensions": "Dimensioni disponibili",
"Selected Dimensions": "Dimensioni selezionati",
"Cube name": "Nome Cubo",
"_tit: Cube Creation Wizard": "Assistente<br>Creazione<br>Cubo",
"_msg: Cube Wizard": "This Wizard will allow you to setup new Cube.",
"Information": "Informazioni",
"_msg: new Cube": "Storing new Cube in Database.",
"_err: create new Cube": "Not Correct data for Cube. Name or Dimensions missing.",
"_msg: Cube added": "Cube is successfully stored in Database.",
"Close Cube Wizard": "Chiudi Assistente Cubo",
"_msg: close Cube Wizard": "Are you sure, you want to exit without saving?",

//Choose Element
"[none]": "[nessuno]",
"Element not found!": "Elemento non trovato!",
"Search & Select": "Cerca & Seleziona",

//Palo Wizard
"PALO Wizard": "Assistente PALO",
"_msg: Palo Wizard": "This wizard will allow you to add/delete databases and servers",
"_tit: Palo Wizard": "Assistente Palo",
"Select connection": "Seleziona Connessione",
"New Database": "Nuovo Database",
"Delete Database": "Elimina Database",
"New Server": "Server Nuovo",
"Delete Server": "Elimina Server",
"Disconnect": "Disconnetti",
"Connect": "Connetti",
"_msg: Palo Wizard Delete Server": "This operation will delete server from list!",
"Connection Name": "Nome Connessione",
"Server": "Server",
"Port": "Porta",
"Username": "Nome utente",
"Confirm Password": "Conferma Password",
"Test Connection": "Verifica Connessione",
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
"Edit Server": "Modifica Server",

//PALO Rule Editor
"Rule":"Regola",
"Updated":"Aggiornato",
"Rule Editor":"Rule Editor",
"List of defined rules":"List of defined rules",
"Comment": "Commento",
"Import Rules": "Importa Regole",
"impPaloRule_fieldLbl": "The file to import",
"impDlg_msgFieldBlank": "Please choose a file",

// Copied for app
"Choose Element": "Seleziona Elemento",
"Name": "Nome",
"New Database Name": "New Database Name",
"Select database to delete": "Select database to delete",
"Store login data": "Store login data",
"Data": "Data",

//ConstListEditor class
"New Constant": "New Constant",
"Delete Constants": "Delete Constants",
"_msg: Delete Constants": "Are you sure you want to delete selected constants?",
"Acquiring Server List": "Acquiring Server List",
"Opening dialog": "Opening dialog",
"Move Up": "Move Up",
"Move Down": "Move Down",
"No rule selected. Please select rule.": "No rule selected. Please select rule.",
"No file selected. Please select file.": "No file selected. Please select file."

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
