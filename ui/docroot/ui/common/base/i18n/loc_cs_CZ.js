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
 * SVN: $Id: loc_cs_CZ.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Storno",
"File": "Soubor",
"New": "Nový",
"Open": "Otevřít",
"Close": "Zavřít",
"Save": "Uložit",
"Properties": "Vlastnosti",
"Edit": "Úparvy",
"Cut": "Vyjmout",
"Copy": "Kopírovat",
"Paste": "Vložit",
"View": "Zobrazit",
"List": "Seznam",
"Hide": "Skrýt",
"Help": "Nápověda",
"Create new document": "Vytvořit nový dokument",
"Open document": "Otevřít dokument",
"Save document": "Uložit dokument",
"Bold": "Tučné",
"Italic": "Kurzíva",
"Underline": "Podrtžení",
"Delete": "Smazat",
"Rename": "Přejmenovat",
"Select All": "Vybrat vše",
"Type": "Typ",
"Warning": "Varování",
"Password": "Heslo",
"Layout": "Rozvržení",
"General": "Obecné",
"Preview": "Náhled",
"Refresh": "Obnovit",
"None": "Žádné",
"Bottom": "Dolní",
"Right": "Pravé",
"Up": "Horní",
"New Folder": "Nová složka",
"Thumbnails": "Ikony",
"Details": "Detaily",
"Description": "Popis",
"Options": "Předvolby",
"Modeller": "Návrhář",
"Home": "Domů",
"Size": "Velikost",

"Quick View": "Náhled administrátora",
"Designer Preview": "Náhled návrháře",
"Active": "Aktivní",
"Path": "Cesta",
"Apply": "Použít",
"Rename Sheet": "Přejmenovat list",

//Paste Subset Dialog
"_tit: hb List Editor": "Editor seznamu dynamických oblastí",
"Subset Editor": "Editor subsetů",
"Subset General Settings": "Obecné nastavení subsetů",
"Dimension": "Dimenze",
"Select First Alias": "Vyberte první alias",
"Select Second Alias": "Vyberte druhý alias",
"Alias": "Alias",
"Optional Settings": "Volitelné nastavení",
"Hierarchy enumeration": "Výpis hierarchií",
"Hierarchy": "Hierarchie",
"Text": "Text",
"Picklist": "Výběr",
"Attribute": "Atribuce",
"Sort": "Seřadit",
"Level": "Úroveň",
"Depth": "Hloubka",
"Flat": "Ploché",
"Show parents below children": "Zobrazit rodiče pod prvky dětí",
"Show duplicates": "Zobrazit duplikáty",
"Show children of hidden elements": "Zobrazit prvky dětí pod skrytými prvky",
"_msg: hb Lists": "Seznam dynamických oblastí",
"[_name: hb List]": "[Seznam dynamických oblastí]",
"Formula Subset": "Subset vzorce",
"[Formula Subset]": "[Subset vzorce]",
"Local Subsets": "Místní subsety",
"Global Subsets": "Globální subsety",
"Stored Subsets": "Uložené subsety",
"Auto": "Automaticky",
"By Definition": "Podle definice",
"By Element name": "Podle jména prvku",
"By Alias": "Podle aliasu",
"By Value": "Podle hodnoty",
"By Attribute": "Podle atribuce",
"All Elements": "Všechny prvky",
"Base Elements Only": "Pouze základní prvky",
"Consolidated Elements Only": "Pouze konsolidované prvky",
"Reverse": "Obrátit",
"Sort at Level": "Třídit na úrovni",
"Sorting behaviour": "Chování",
"Reverse Order": "Obrátit pořadí",
"Type Limitation": "Omezení typů",
"New Subset": "Nový subset",
"Enter name for Subset": "Zadejte název pro subset",
"Delete Subset": "Smazat subset",
"_msg: Delete Subset": "Opravdu chcete subset smazat?",
"Rename Subset": "Přejmenovat subset",
"Enter new name for Subset": "Zadejte nový název pro subset",
"_msg: update Subset": "Ukládám subset.",
"_msg: new Subset": "Ukládám nový subset.",
"_msg: delete Subset": "Mažu subset.",
"_msg: rename Subset": "Ukládám nový název pro subset.",
"[All Elements]": "[Všechny prvky]",
"Filter elements hierarchically": "Hierarchické filtrování prvků",
"Cyclic list": "Cyklický seznam",
"Below": "Pod",
"Above": "Nad",
"Consolidated": "Konsolidované",
"Base Elements": "Základní prvky",
"Activate this filter": "Aktivovat tento filtr",
"Exclusive": "Exkluzivní",
"Filter Element by type": "Filtrovat prvky dle typu",
"Filter elements by Level": "Filtrovat prvky dle úrovně",
"List length": "Délka seznamu",
"Start level": "Počáteční úroveň",
"Indent Enumeration": "Odsazení",
"End level": "Koncová úroveň",
"Settings": "Nastavení",
"_subsetTextTabExamples": "Příklady:<br>- \"Jan|Feb|Nov\", odpovídá \"Jan\", \"Feb\", \"Nov\"<br>- \"J.*\", odpovídá všem prvkům začínajícím na \"J\"<br>- \"[s,d]\", odpovídá všem prvkům začínajícím na \"s\" nebo \"d\" ve jméně<br>- \"n$\", odpovídá všem prvkům končícím na \"n\"" +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "Masky",
"Behaviour": "Chování",
"Dimension Contents": "Obsah dimenze",
"Please select how to insert choosen elements": "Zvolte, jak si přejete vložit vybrané prvky",
"_subsetAttrTabExample": "<br>Příklady:<br>- \">0\"<br>- \"<=1000\"<br>- \"<>10\"<br>- \"=10\"" +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Proměnný",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Počáteční úroveň",
"Level End": "Koncová úroveň",
"Criteria": "Kritéria",
"Sort Attribute": "Řadící atribuce",
"Sort Level": "Řadící úroveň",
"Quick": "Rychlý",
"SUM OF THE ELEMENTS": "SOUČET PRVKŮ",
"ALL ELEMENTS": "VŠECHNY PRVKY",
"AVEREGE OF THE ELEMENTS": "PRŮMĚR PRVKŮ",
"MAXIMUM OF THE ELEMETNS": "MAXIMUM PRVKŮ",
"ANY ELEMENT": "LIBOVOLNÝ PRVEK",
"MINIMUM OF THE ELEMENTS": "MINIMUM PRVKŮ",
"STRING": "STRING",
"Please select and set attribute fields": "Vyberte a nastavte pole atribucí",
"Select Cube": "Vyberte kostku",
"Indent": "Odsadit",
"FRONT": "VPŘED",
"BACK": "ZPĚT",
"MERGE": "SLOUČIT",
"SUBTRACT": "ODEČÍST",
"Take topmost elements": "Vzít vrcholové prvky",
"Take all upper elements up to %": "Vzít všechny horní prvky až po %",
"Take all lower elements up to %": "Vzít všechny spodní prvky až po %",
"List Length": "Délka seznamu",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Typ výběru",
"Cube": "Kostka",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Vrcholový prvek",
"Upper": "Vyšší",
"Lower": "Nižší",
"Slice operators": "Operátory řezu",
"AND": "A",
"Named Variables": "Pojmenované proměnné",
"subset_Indent": "Odsazení",
"Obtaining preview data": "Získávám data pro náhled",
"Unable to resolve value for": "Nepodařilo se vyřešit hodnotu pro",
"_msg: paloSbstDFilterEnabled": "Když je aplikovaný filtr dat, zpracování informací pro náhled seznamu může trvat déle.",

//PALO Modeller
"PALO Modeller": "Návrhář PALO",
"Error": "Chyba",
"Elements": "Prvky",
"Attributes": "Atribuce",
"Subsets": "Subsety",
"Consolidated Elements": "Konsolidované prvky",
"show Tree": "Zobrazit strom",
"<< Database": "<< Databáze",
"Expand All": "Rozbalit vše",
"Collapse All": "Sbalit vše",
"Choose Server/Database": "Vyberte server/databázi",
"Dimensions and Global Subsets": "Dimenze a globální subsety",
"Cubes": "Kostky",
"Database": "Databáze",
"system": "systém",
"attributes": "atribuce",
"normal": "normalní",
"loaded": "načteno",
"not loaded": "nenačteno",
"_err: Timer": "Vypršel čas požadavku serveru.",
"_msg: Timer": "Čekám, až vyprší čas.",
"Add": "Přidat",
"Consolidate": "Konsolidace",
"Numeric": "Numeric",
"String": "String",
"Copy Elements": "Kopírovat prvky",
"Paste Elements": "Vložit prvky",
"Move Element to the Beginning": "Přesunout prvek na začátek",
"Move Element to the End": "Přesunout prvek na konec",
"Count": "Počet",
"Search for Element": "Vyhledat prvek",
"Moving Element": "Přesouvám prvek",
"Consolidation Factor": "Váha prvku pro konsolidaci",
"Remove from source elements": "Odebrat ze zdrojových prvků",
"Add Cube": "Přidat kostku",
"Delete Cube": "Smazat kostku",
"Rename Cube": "Přejmenovat kostku",
"Clear Cube": "Vyčistit kostku",
"Export Cube": "Exportovat kostku",
"Rule Edit": "Upravit pravidlo",
"Cube Information": "Vlastnosti",
"Add Dimension": "Přidat",
"Delete Dimension": "Smazat",
"Rename Dimension": "Přejmenovat",
"Edit Dimension": "Upravit",
"Export Dimension": "Exportovat...",
"Dimension Information": "Vlastnosti",
"Total Number of Elements": "Celkový počet prvků",
"Number of Numeric Elements": "Počet číselných prvků",
"Number of String Elements": "Počet textových prvků",
"Number of Consolidated Elements": "Počet konsolidovaných prvků",
"Delete Element": "Smazat prvek",
"_msg: Delete Element": "Jste si jistí, že chcete prvek smazat?",
"Delete Attribute": "Smazat atribuci",
"_msg: Delete Attribute": "Jste si jisti, že chcete atribuci smazat?",
"_msg: Delete Dimension": "Jste si jisti, že chcete dimenzi smazat?",
"_msg: Delete Cube": "Jste si jisti, že chcete kostku smazat?",
"Change Element Type": "Změnit typ prvku",
"_msg: Change Element Type": "Změna typu prvku může vést ke ztrátě dat.<br>Opravdu chcete změnit typ prvku?",
"Search Element": "Vyhledat prvek",
"_msg: Search Element": "Zadejte jméno prvku, který chcete vyhledat",
"Search": "Hledání",
"Element": "Prvek",
"was not find in dimension": "nebyl v dimezi nalezen.",
"New Element": "Nový prvek",
"Enter name for new Element": "Zadejte název nového prvku",
"New Attribute": "Nová atribuce",
"Enter name for new Attribute": "Zadejte název nové atribuce",
"Rename Element": "Přejmenovat prvek",
"Enter new name for Element": "Zadejte nový název prvku",
"Rename Attribute": "Přejmenovat atribuci",
"Enter new name for Attribute": "Zadejte nový název atribuce",
"New Dimension": "Nová dimenze",
"Enter name for Dimension": "Zadejte název dimenze",
"Enter new name for Dimension": "Zadejte nový název dimenze",
"Enter new name for Cube": "Zadejte název kostky",
"Change Factor": "Změnit váhu prvku",
"Enter new consolidation factor": "Zadejte váhu prvku pro konsolidaci",
"Storing": "Ukládám",
"_msg: new Dim": "Ukládám novou dimenzi do databáze.",
"_err: new Dim": "Přidání nové dimenze se nezdařilo!",
"_msg: rename Dim": "Ukládám nový název dimenze do databáze.",
"_err: rename Dim": "Přejmenování dimenze se nezdařilo!",
"_msg: del Dim": "Mažu dimenzi.",
"_err: del Dim": "Smazání dimenze se nezdařilo!",
"_msg: ren Cube": "Ukládám novou kostku do databáze.",
"_msg: del Cube": "Mažu kostku.",
"_err: del Cube": "Smazání kostky se nezdařilo",
"_msg: new Elem": "Ukládám nový prvek do databáze.",
"_msg: del Elem": "Mažu prvek z databáze.",
"_msg: cons Elem": "Ukládám konsolidovaný prvek.",
"_msg: rename Elem": "Ukládám nový název prvku do databáze.",
"_msg: change type Elem": "Ukládám nový typ prvku do databáze.",
"_msg: moving Element": "Přemisťuji prvek na novou pozici.",
"Identifier": "Identifikátor",
"Number of Elements": "Počet prvků",
"Number of N elem.": "Počet N prvků",
"Number of S elem.": "Počet S prvků",
"Number of C elem.": "Počet C prvků",
"Maximum Level": "Maximální úroveň",
"Maximum Indent": "Maximální odsazení",
"Maximum Depth": "Maximální hloubka",
"Number of Dimensions": "Počet dimenzí",
"Dimensions": "Dimenze",
"Number of Cells": "Počet buněk",
"Number of Filled Cells": "Počet neprázdných buněk",
"Filed Ratio": "Poměr výplně",
"Status": "Status",
"Add Subset": "Přidat subset",
"is not allowed": "není povolen",
"Hit RETURN to add Dimension": "Pro přidání dimenze stiskněte klávesu ENTER.",
"Click on the \"New Cube\" button to add Cube": "Pro přidání kostky klepněte na \"Nová kostka\"",
"Hit RETURN to add Elements": "Pro přidání prvků stiskněte klávesu ENTER.",
"Add Element from list of Elements": "Přidat prvek ze seznamu prvků",

//PALO Cube Wizard
"PALO Cube Wizard": "Průvodce kostkou Palo",
"Finish >>": "Konec >>",
"Available Dimensions": "Dostupné dimenze",
"Selected Dimensions": "Vybrané dimenze",
"Cube name": "Název kostky",
"_tit: Cube Creation Wizard": "Průvodce<br>vytvořením<br>kostky",
"_msg: Cube Wizard": "Průvodce vám nyní umožní nastavit kostku.",
"Information": "Informace",
"_msg: new Cube": "Ukládám novou kostku do databáze.",
"_err: create new Cube": "Data pro vytvoření kostky nejsou správná. Chybí jméno kostky nebo kostka neobsahuje žádné dimenze.",
"_msg: Cube added": "Kostka byla úspěšně uložena do databáze.",
"Close Cube Wizard": "Zavřít Průvodce kostkou",
"_msg: close Cube Wizard": "Opravdu chcete skončit bez uložení změn?",

//Choose Element
"[none]": "[žádný]",
"Element not found!": "Prvek nebyl nalezen.",
"Search & Select": "Vyhledat & vybrat",

//Palo Wizard
"PALO Wizard": "Průvodce PALO",
"_msg: Palo Wizard": "Průvodce umožní přidat nebo smazat databáze a servery",
"_tit: Palo Wizard": "Průvodce Palo",
"Select connection": "Vyberte připojení",
"New Database": "Nová databáze",
"Delete Database": "Smazat databázi",
"New Server": "Nový server",
"Delete Server": "Smazat server",
"Disconnect": "Odpojit",
"Connect": "Připojit",
"_msg: Palo Wizard Delete Server": "Tato operace smaže server ze seznamu!",
"Connection Name": "Název připojení",
"Server": "Server",
"Port": "Port",
"Username": "Uživatelské jméno",
"Confirm Password": "Potvrďte heslo",
"Test Connection": "Test připojení",
"_err: Wrong Pass": "Nesprávné heslo.",
"_msg: Test Conn Ok": "Test byl úspěšný.",
"_err: Test Conn Not Ok": "Test nebyl úspěšný.",
"_err: Db not added": "Chyba při vytváření databáze.",
"_msg: Db added": "Nová databáze byla úspěšně přidána.",
"_err: Db not deleted": "Nebylo možné smazat databázi.",
"_msg: Db deleted": "Databáze byla úspěšně smazána.",
"_msg: Server added": "Nový server byl úspěšně přidán.",
"_err: Server not added": "Chyba při vytváření serveru.",
"_msg: Server edited": "Nový server byl úspěšně přidán.",
"_err: Server not edited": "Chyba při editaci serveru.",
"_msg: Server deleted": "Server byl úspěšně smazán.",
"_err: Server not deleted": "Nepodařilo se odstranit server.",
"_msg: Delete Database": "Chcete opravdu smazat celou databázi ze serveru?",
"_msg: Delete Server": "Chcete opravdu smazat server ze seznamu?",
"Edit Server": "Editovat vybraný server",

//PALO Rule Editor
"Rule":"Pravidlo",
"Updated":"Aktualizováno",
"Rule Editor":"Editor pravidel",
"List of defined rules":"Seznam definovaných pravidel",
"Comment": "Komentář",
"Import Rules": "Importovat pravidla",
"impPaloRule_fieldLbl": "Soubor pro import",
"impDlg_msgFieldBlank": "Vyberte soubor",

// Copied for app
"Choose Element": "Vyberte prvek",
"Name": "Název",
"New Database Name": "Nový název databáze",
"Select database to delete": "Vyberte databázi ke smazání",
"Store login data": "Uložit přihlašovací údaje",
"Data": "Data",

//ConstListEditor class
"New Constant": "Nová konstanta",
"Delete Constants": "Smazat konstanty",
"_msg: Delete Constants": "Opravdu chcete smazat vybrané konstanty?",
"No rule selected. Please select rule.": "Není vybráno žádné pravidlo. Prosím, vyberte jej.",
"No file selected. Please select file.": "Není vybrán žádný soubor. Prosím, vyberte jej.",
"Acquiring Server List": "Přistupuji na seznam serverů",
"Opening dialog": "Otevírám dialogové okno",
"Move Up": "Přesunout nahoru",
"Move Down": "Přesunout dolů",
"fopperLic": "Licence PDF tiskárny",
"License could not be checked": "Licenci nebylo možné ověřit",
"License could not be found.": "Nepodařilo se nalézt licenci.",
"License could not be read.": "Nepodařilo se přečíst licenci.",
"License is not valid.": "Licence není platná."

};

Jedox.err.i18n = {
     1: 'Chyba GenericException'
,  100: 'Chyba RuntimeException'
,  101: 'Chyba ParsingFailedException'
,  102: 'Chyba NotImplementedException'
,  103: 'Chyba InvalidSessionException'
, 1000: 'Chyba InsufficientRightsException'
, 1100: 'Chyba EventHandlerAbortException'
, 1200: 'Chyba ClipboardInvalidIndexException'
, 1300: 'Chyba InvalidNameException'
, 1400: 'Chyba InterpreterRuntimeError'
, 1500: 'Chyba InvalidFormulaException'
, 1600: 'Chyba CyclicDependencyException'
, 1700: 'Chyba ArrayException'
, 1800: 'Chyba NoWorkbookSelectedException'
, 1801: 'Chyba GenericException'
, 1802: 'Chyba NoApplicationSelectedException'
, 1900: 'Chyba LoadApplicationException'
, 1901: 'Chyba GenericException'
, 1902: 'Chyba SaveException'
, 2000: 'Chyba ConditionalFormatException'
, 2100: 'Chyba RuntimeException'
, 2101: 'Chyba ParsingFailedException'
, 2200: 'Chyba CopyWorksheetException'
, 2300: 'Chyba RangeException'
, 2400: 'Chyba MergedCellException'
, 2500: 'Chyba AuthenticationException'
, 2600: 'Chyba CellDimensionException'
, 2700: 'Chyba SessionException'
, 2800: 'Chyba InvalidGroupException'
, 2900: 'Chyba InvalidUserException'
, 3000: 'Chyba TranslationTableException'
, 3100: 'Chyba RuntimeException'
, 3200: 'Chyba WorkbookCloneException'
, 3300: 'Chyba ExtensionRegistryException'
, 3400: 'Chyba ExtensionCallerException'
, 3500: 'Chyba CyclicArrayException'
, 3600: 'Chyba WorksheetElementException'
, 3700: 'Chyba FormatException'
, 3800: 'Chyba StyleManagerException'
, 3900: 'Chyba BoundedPointException'
, 4000: 'Chyba FilterRegistryException'
, 4100: 'Chyba RuntimeException'
, 4200: 'Chyba SelectionToLargeException'
, 4300: 'Chyba ExtensionFailureException'
, 4400: 'Chyba PaloConnectorException'
, 4500: 'Chyba FatalException'
, 4600: 'Chyba ArrayFormulaOnMergedCellException'
, 4700: 'Chyba ValueConversionException'
,   R1: 'Chyba GenericException'
,   R2: 'Chyba v souboru {FILE} na řádku {LINE}!'
, P0_0: 'Operace aplikace Palo se nezdařila.'
, P1_0: 'Název databáze není správné.'
, P1_1: 'Chyba GenericException'
, P1_2: 'Dimenze neexistuje.'
, P1_3: 'Dimenze je používána v některé kostce.'
, P1_4: 'Prvek již existuje.'
, P1_5: 'Subset nebyl smazán.'
, P1_6: 'Subset nebyl přejmenován.'
, P1_7: 'Nepodařilo se načíst seznam databází pro připojení s názvem \"{conn_name}\".'
, P1_8: 'Subset {ss_name} nemůže být vytvořen.'
, P1_9:	'Pro tuto akci nemáte dostatečná práva.'
, P1_10: 'Nepodařilo se změnit stav připojení.'
, P1_11: 'Chyba GenericException'
, P1_12: 'Špatný typ připojení PALO pro připojení s názvem: {conn_name}.'
, P1_13: 'Nepodařilo se vytvořit připojení pro připojení s názvem: {conn_name}.'
, P1_14: 'Nepodařilo se získat uživatele pro připojení s názvem: {conn_name}.'
, P1_15: 'Nepodařilo se vytvořit databázi: {db_name}.'
, P1_16: 'Nepodařilo se získat konfigurační data funkce Vložit pohled'
, P1_17: 'Nepodařilo se smazat databázi: {db_name}.'
, P1_18: 'Nepodařilo se vygenerovat seznam subsetů!'
};
