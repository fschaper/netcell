/*
 * @brief wss file
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: loc_de_DE.js 4901 2011-04-28 10:07:16Z l10n-tool $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Abbrechen",
"File": "Datei",
"New": "Neu",
"Open": "Öffnen",
"Close": "Schließen",
"Save": "Speichern",
"Properties": "Eigenschaften",
"Edit": "Bearbeiten",
"Cut": "Ausschneiden",
"Copy": "Kopieren",
"Paste": "Einfügen",
"View": "Ansicht",
"List": "Liste",
"Hide": "Ausblenden",
"Help": "Hilfe",
"Create new document": "Neues Dokument erstellen",
"Open document": "Dokument öffnen",
"Save document": "Dokument speichern",
"Bold": "Fett",
"Italic": "Kursiv",
"Underline": "Unterstrichen",
"Delete": "Löschen",
"Rename": "Umbenennen",
"Select All": "Alle auswählen",
"Type": "Typ",
"Warning": "Warnung",
"Password": "Passwort",
"Layout": "Layout ",
"General": "Standard",
"Preview": "Vorschau",
"Refresh": "Aktualisieren",
"None": "Kein",
"Bottom": "Unten",
"Right": "Rechts",
"Up": "Nach oben",
"New Folder": "Neuer Ordner",
"Thumbnails": "Symbole",
"Details": "Details ",
"Description": "Beschreibung",
"Options": "Optionen",
"Modeller": "Modeller ",
"Home": "Startseite",
"Size": "Größe",

"Quick View": "Admin Vorschau",
"Designer Preview": "Designervorschau",
"Active": "Aktiv",
"Path": "Pfad",
"Apply": "Anwenden",
"Rename Sheet": "Blatt umbenennen",

//Paste Subset Dialog
"_tit: hb List Editor": "DynaRange Listen-Editor",
"Subset Editor": "Subseteditor",
"Subset General Settings": "Subset Grundeinstellungen",
"Dimension": "Dimension",
"Select First Alias": "Wählen Sie den 1.Alias",
"Select Second Alias": "Wählen Sie den 2.Alias",
"Alias": "Alias",
"Optional Settings": "Optionale Angaben",

"Hierarchy": "Hierarchie",
"Text": "Text ",
"Picklist": "Pickliste",
"Attribute": "Attribut",
"Sort": "Sortierung",
"Level": "Niederste Ebene ist 0",
"Depth": "Höchste Ebene ist 0",
"Flat": "Listendarstellung",
"Show parents below children": "Eltern unterhalb ihrer Kinder",
"Show duplicates": "Mit Duplikaten",
"Show children of hidden elements": "Verborgene Kinder anzeigen",
"_msg: hb Lists": "DynaRange-Listen",
"[_name: hb List]": "[DynaRange-Liste]",
"Formula Subset": "Formel-Subset",
"[Formula Subset]": "[Formel-Subset]",
"Local Subsets": "Private Subsets",
"Global Subsets": "Globales Subset",
"Stored Subsets": "Gespeichertes Subset",
"Auto": "Auto",
"By Definition": "Nach Definition",
"By Element name": "Alphabetisch",
"By Alias": "Nach Alias",
"By Value": "Nach Wert",
"By Attribute": "Nach Attribut",
"All Elements": "Alle Elemente",
"Base Elements Only": "Nur Basis-Elemente",
"Consolidated Elements Only": "Nur konsolidierte Elemente",
"Reverse": "Umkehrung",
"Sort at Level": "Sortiert nach Ebene",
"Sorting behaviour": "Subset Sortierung",
"Reverse Order": "Umkehr-Anweisung",
"Type Limitation": "Auswahl Hierarchie-Ebene",
"New Subset": "Neues Subset",
"Enter name for Subset": "Geben Sie den Namen für das Subset ein",
"Delete Subset": "Subset löschen",
"_msg: Delete Subset": "Wollen Sie wirklich das Subset löschen?",
"Rename Subset": "Subset umbenennen",
"Enter new name for Subset": "Geben Sie den neuen Namen für das Subset ein",
"_msg: update Subset": "Subset speichern.",
"_msg: new Subset": "Neues Subset speichern.",
"_msg: delete Subset": "Subset löschen.",
"_msg: rename Subset": "Den neuen Namen für das Subset speichern.",
"[All Elements]": "[Alle Elemente]",
"Filter elements hierarchically": "Hierarchisch filtern",
"Cyclic list": "Auflistung wiederholen",
"Below": "Unter",
"Above": "Über",
"Consolidated": "Konsolidierte Elemente",
"Base Elements": "Basis-Elemente",
"Activate this filter": "Diesen Filter aktivieren",
"Exclusive": "Exklusiv",
"Filter Element by type": "Nach Typ filtern",
"Filter elements by Level": "Nach Hierarchie-Ebene filtern",
"List length": "Länge der Liste",
"Start level": "Beginn mit",
"Indent Enumeration": "",
"End level": "Ende mit",
"Settings": "Einstellungen",
"_subsetTextTabExamples": 'Beispiele:<br>' +
							'- "Jan|Feb|Nov" bringt im Filter "Jan", "Feb", "Nov"<br>' +
							'- "J.*" bringt im Filter alle Elemente die mit "J" beginnen<br>' +
							'- "[s,d]" bringt im Filter alle Elemente, die ein "s" oder "d" im Namen haben<br>' +
							'- "n$" bringt im Filter alle Elemente, die mit "n" enden',
"_subsetTextTabPerl": "<b>PERL-Reguläre Ausdrücke</b>",
"Behaviour": "Einstellungen",
"Dimension Contents": "Ausgewählte Elemente",
"Please select how to insert choosen elements": "Auswahl, wie die Pickliste verwendet wird",
"_subsetAttrTabExample": '<br>Beispiele:<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Variable",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Startebene",
"Level End": "Level Ende",
"Criteria": "Kriterium",
"Sort Attribute": "Sortierung Attribute",
"Sort Level": "Sortierungsebene",
"Quick": "Schnell",
"SUM OF THE ELEMENTS": "SUMME DER ELEMENTE",
"ALL ELEMENTS": "ALLE ELEMENTE",
"AVEREGE OF THE ELEMENTS": "DURCHSCHNITT DER ELEMENTE",
"MAXIMUM OF THE ELEMETNS": "MAXIMUM DER ELEMENTE",
"ANY ELEMENT": "EIN ELEMENT",
"MINIMUM OF THE ELEMENTS": "MINIMUM DER ELEMENTE",
"STRING": "TEXT",
"Please select and set attribute fields": "Bitte Attribute auswählen",
"Select Cube": "Würfelauswahl",
"Indent": "Eingerückt",
"FRONT": "Hinzufügung vor der Liste",
"BACK": "Hinzufügung nach der Liste",
"MERGE": "Einsortierung in die Liste",
"SUBTRACT": "Als Vorauswahl für das Subset",
"Take topmost elements": "Zeige Topelemente bis n",
"Take all upper elements up to %": "Zeige große Elemente bis %",
"Take all lower elements up to %": "Zeige kleine Elemente bis %",
"List Length": "Länge der Liste",
"RegExes": "RegExes ",
"RegEx": "RegEx ",
"Picklist Type": "Typ der Pickliste",
"Cube": "Würfel",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Höchste",
"Upper": "Obere",
"Lower": "Untere",
"Slice operators": "Kriterium",
"AND": "UND",
"Named Variables": "Benannte Variable",
"subset_Indent": "Eingerückt",
"Obtaining preview data": "Empfang der Vorschaudaten",
"Unable to resolve value for": "Es kann kein Wert ermittelt werden",
"_msg: paloSbstDFilterEnabled": "Bei aktiviertem Daten-Filter kann das Abrufen der Vorschau-Daten einige Zeit benötigen.",

//PALO Modeller
"PALO Modeller": "PALO Modeller ",
"Error": "Fehler",
"Elements": "Elemente",
"Attributes": "Attribute",
"Subsets": "Subsets ",
"Consolidated Elements": "Konsolidierte Elemente",
"show Tree": "Hierarchieanzeige",
"<< Database": "<< Datenbank",
"Expand All": "Alle aufklappen",
"Collapse All": "Alle zuklappen",
"Choose Server/Database": "Server/Datenbank wählen",
"Dimensions and Global Subsets": "Dimensionen und Globale Subsets",
"Cubes": "Würfel",
"Database": "Datenbank",
"system": "System",
"attributes": "Attribute",
"normal": "Normal",
"loaded": "geladen",
"not loaded": "nicht geladen",
"_err: Timer": "Unterbrechung für Server-Anfrage.",
"_msg: Timer": "Wartezeit beendet.",
"Add": "Hinzufügen",
"Consolidate": "Konsolidieren",
"Numeric": "Numerisch",
"String": "Text",
"Copy Elements": "Elemente kopieren",
"Paste Elements": "Elemente einfügen",
"Move Element to the Beginning": "Element an den Anfang stellen",
"Move Element to the End": "Element an das Ende stellen",
"Count": "Zählen",
"Search for Element": "Element suchen",
"Moving Element": "Element verschieben",
"Consolidation Factor": "Konsolidierungsfaktor",
"Remove from source elements": "Von den Quellelementen entfernen",
"Add Cube": "Würfel hinzufügen",
"Delete Cube": "Würfel löschen",
"Rename Cube": "Würfel umbenennen",
"Clear Cube": "Würfel leeren",
"Export Cube": "Würfel exportieren",
"Rule Edit": "Rule editieren",
"Cube Information": "Eigenschaften",
"Add Dimension": "Hinzufügen...",
"Delete Dimension": "Löschen...",
"Rename Dimension": "Umbenennen",
"Edit Dimension": "Bearbeiten...",
"Export Dimension": "Exportiere Dimension... ",
"Dimension Information": "Eigenschaften",
"Total Number of Elements": "Gesamtanzahl der Elemente",
"Number of Numeric Elements": "Anzahl der numerischen Elemente",
"Number of String Elements": "Anzahl der Textelemente",
"Number of Consolidated Elements": "Anzahl der konsolidierten Elemente",
"Delete Element": "Element löschen",
"_msg: Delete Element": "Wollen Sie das Element wirklich löschen?",
"Delete Attribute": "Attribut löschen",
"_msg: Delete Attribute": "Wollen Sie das Attribut wirklich löschen?",
"_msg: Delete Dimension": "Wollen Sie die Dimension wirklich löschen?",
"_msg: Delete Cube": "Wollen Sie den Würfel wirklich löschen?",
"Change Element Type": "Elementtyp ändern",
"_msg: Change Element Type": "Änderung des Elementtyps kann zu Datenverlust führen.<br>Wollen Sie den Elementtyp wirklich ändern?",
"Search Element": "Element suchen",
"_msg: Search Element": "Bitte den Elementnamen für die Suche eingeben",
"Search": "Suche",
"Element": "Element ",
"was not find in dimension": "wurde nicht gefunden in der Dimension",
"New Element": "Neues Element",
"Enter name for new Element": "Bitte den Namen für das neue Element eingeben",
"New Attribute": "Neues Attribut",
"Enter name for new Attribute": "Bitte den Namen für das neue Attribut eingeben",
"Rename Element": "Element umbenennen",
"Enter new name for Element": "Bitte den neuen Namen für das Element eingeben",
"Rename Attribute": "Attribut umbenennen",
"Enter new name for Attribute": "Bitte den neuen Namen für das Attribut eingeben",
"New Dimension": "Neue Dimension",
"Enter name for Dimension": "Bitte den Namen für die Dimension eingeben",
"Enter new name for Dimension": "Bitte den neuen Namen für die Dimension eingeben",
"Enter new name for Cube": "Bitte den Namen für den Würfel eingeben",
"Change Factor": "Faktor ändern",
"Enter new consolidation factor": "Bitte den neuen Konsolidierungsfaktor eingeben",
"Storing": "Anlegen",
"_msg: new Dim": "Neue Dimension in der Datenbank anlegen.",
"_err: new Dim": "Das Anlegen der neuen Dimension ist misslungen!",
"_msg: rename Dim": "Anlegen eines neuen Dimensionsnamens in der Datenbank.",
"_err: rename Dim": "Das Umbenennen der Dimension ist misslungen!",
"_msg: del Dim": "Dimension wird gelöscht.",
"_err: del Dim": "Das Löschen der Dimension ist misslungen!",
"_msg: ren Cube": "Anlegen eines neuen Würfels in der Datenbank.",
"_msg: del Cube": "Würfel löschen.",
"_err: del Cube": "Das Löschen des Würfels ist misslungen!",
"_msg: new Elem": "Anlegen eines neuen Elementes in der Datenbank.",
"_msg: del Elem": "Element aus der Datenbank löschen.",
"_msg: cons Elem": "Anlegen eines konsolidierten Elementes.",
"_msg: rename Elem": "Anlegen eines neuen Elementnamens in der Datenbank.",
"_msg: change type Elem": "Anlegen eines neuen Elementtyps in der Datenbank.",
"_msg: moving Element": "Anlage des Elementes an neuer Position.",
"Identifier": "Bezeichner",
"Number of Elements": "Anzahl der Elemente",
"Number of N elem.": "Anzahl der N Elemente",
"Number of S elem.": "Anzahl der S Elemente",
"Number of C elem.": "Anzahl der C Elemente",
"Maximum Level": "Maximum Hierarchie-Nummerierung Variante 2",
"Maximum Indent": "Maximum Hierarchie-Nummerierung Variante 1",
"Maximum Depth": "Maximum Hierarchie-Nummerierung Variante 3",
"Number of Dimensions": "Anzahl der Dimensionen",
"Dimensions": "Dimensionen",
"Number of Cells": "Anzahl der Zellen",
"Number of Filled Cells": "Anzahl der gefüllten Zellen",
"Filed Ratio": "Befüllungsgrad",
"Status": "Status ",
"Add Subset": "Subset hinzufügen",
"is not allowed": "ist nicht erlaubt",
"Hit RETURN to add Dimension": "Drücken Sie ENTER zum Hinfügen einer Dimension",
"Click on the \"New Cube\" button to add Cube": "Klicken Sie auf \"Neuer Würfel\" , um einen Würfel hinzu zu fügen",
"Hit RETURN to add Elements": "Drücken Sie ENTER zum Hinfügen von Elementen",
"Add Element from list of Elements": "Fügt ein Element aus der Elementeliste hinzu",

//PALO Cube Wizard
"PALO Cube Wizard": "PALO Würfel-Assistent",
"Finish >>": "Fertigstellen >>",
"Available Dimensions": "Verfügbare Dimensionen",
"Selected Dimensions": "Ausgewählte Dimensionen",
"Cube name": "Würfelname",
"_tit: Cube Creation Wizard": "Würfel-<br>Assistent",
"_msg: Cube Wizard": "Dieser Assistent ermöglicht Ihnen den Bau eines neuen Würfels.",
"Information": "Information",
"_msg: new Cube": "Anlegen eines neuen Würfels in der Datenbank.",
"_err: create new Cube": "Es gibt keine korrekten Angaben für den Würfel. Der Name oder die Dimensionen fehlen.",
"_msg: Cube added": "Der Würfel wurde erfolgreich angelegt.",
"Close Cube Wizard": "Würfel-Assistent beenden",
"_msg: close Cube Wizard": "Sind Sie sicher, daß Sie ohne Speichern herausgehen möchten?",

//Choose Element
"[none]": "[kein]",
"Element not found!": "Element wurde nicht gefunden!",
"Search & Select": "Suchen & Auswählen",

//Palo Wizard
"PALO Wizard": "PALO Assistent",
"_msg: Palo Wizard": "Dieser Assistent ermöglicht Ihnen, Datenbanken und Server hinzuzufügen und zu löschen",
"_tit: Palo Wizard": "Palo Assistent",
"Select connection": "Verbindung wählen",
"New Database": "Neue Datenbank anlegen",
"Delete Database": "Vorhandene Datenbank löschen",
"New Server": "Neuen Server eintragen",
"Delete Server": "Servereintrag löschen",
"Disconnect": "Trennen",
"Connect": "Verbinden",
"_msg: Palo Wizard Delete Server": "Dies wird den Server von der Liste löschen!",
"Connection Name": "Bezeichnung",
"Server": "Server ",
"Port": "Port",
"Username": "Benutzername",
"Confirm Password": "Passwort bestätigen",
"Test Connection": "Verbindung testen",
"_err: Wrong Pass": "Falsche Passwortbestätigung.",
"_msg: Test Conn Ok": "Test erfolgreich.",
"_err: Test Conn Not Ok": "Test war nicht erfolgreich.",
"_err: Db not added": "Fehler bei der Datenbankerstellung.",
"_msg: Db added": "Neue Datenbank wurde erfolgreich angelegt.",
"_err: Db not deleted": "Löschung der Datenbank war nicht möglich.",
"_msg: Db deleted": "Datenbank wurde erfolgreich gelöscht.",
"_msg: Server added": "Neuer Server wurde erfolgreich eingetragen.",
"_err: Server not added": "Fehler bei Servereintragung.",
"_msg: Server edited": "Server wurde erfolgreich geändert.",
"_err: Server not edited": "Fehler bei Serveränderung.",
"_msg: Server deleted": "Servereintrag wurde erfolgreich gelöscht.",
"_err: Server not deleted": "Servereintrag konnte nicht gelöscht werden.",
"_msg: Delete Database": "Wollen Sie wirklich die Datenbank vollständig vom Server löschen.",
"_msg: Delete Server": "Wollen Sie wirklich den Server aus der Liste löschen.",
"Edit Server": "Servereintrag bearbeiten",

//PALO Rule Editor
"Rule":"Rule ",
"Updated":"Aktualisiert",
"Rule Editor":"Rule_Editor",
"List of defined rules":"Liste der definierten Rules",
"Comment": "Kommentar",
"Import Rules": "Import Rules",
"impPaloRule_fieldLbl": "Datei für den Import",
"impDlg_msgFieldBlank": "Bitte wählen Sie eine Datei aus",

// Copied for app
"Choose Element": "Element auswählen",
"Name": "Name ",
"New Database Name": "Neuer Datenbankname",
"Select database to delete": "Wählen Sie die zu löschende Datenbank aus",
"Store login data": "Anmeldedaten speichern",
"Data": "Daten",

//ConstListEditor class
"New Constant": "Neue Konstante",
"Delete Constants": "Konstante löschen",
"_msg: Delete Constants": "Wollen Sie wirklich die ausgewählten Konstanten löschen?",
"Hierarchy enumeration": "Hierarchie-Nummerierung",
"Indent Enumeration": "Ebene",
"Acquiring Server List": "Serverliste wird erstellt.",
"Opening dialog": "Dialog wird geöffnet.",
"Move Up": "Gehe nach oben",
"Move Down": "Gehe nach unten",
"No rule selected. Please select rule.": "Keine Rule ausgewählt. Bitte wählen Sie eine Rule aus.",
"No file selected. Please select file.": "Keine Datei ausgewählt. Bitte wählen Sie eine Datei aus.",
"fopperLic": "PDF Drucker Lizenz",
"License could not be checked": "Lizenz konnte nicht überprüft werden.",
"License could not be found.": "Lizenz konnte nicht gefunden werden.",
"License could not be read.": "Lizenz konnte nicht gelesen werden.",
"License is not valid.": "Lizenz ist nicht gültig."

};

Jedox.err.i18n = {
     1: 'GenericException-Fehler'
,  100: 'RuntimeException-Fehler'
,  101: 'ParsingFailedException-Fehler'
,  102: 'NotImplementedException-Fehler'
,  103: 'InvalidSessionException-Fehler'
, 1000: 'InsufficientRightsException-Fehler'
, 1100: 'EventHandlerAbortException-Fehler'
, 1200: 'ClipboardInvalidIndexException-Fehler'
, 1300: 'InvalidNameException-Fehler'
, 1400: 'InterpreterRuntimeError-Fehler'
, 1500: 'InvalidFormulaException-Fehler'
, 1600: 'CyclicDependencyException-Fehler'
, 1700: 'ArrayException-Fehler'
, 1800: 'NoWorkbookSelectedException-Fehler'
, 1801: 'NoWorksheetSelectedException-Fehler'
, 1802: 'NoApplicationSelectedException-Fehler'
, 1900: 'LoadApplicationException-Fehler'
, 1901: 'LoadException-Fehler'
, 1902: 'Speicher-Ausnahme-Fehler'
, 2000: 'ConditionalFormatException-Fehler'
, 2100: 'NamedFormulaException-Fehler'
, 2101: 'NamedFormulaDoesNotExistException-Fehler'
, 2200: 'CopyWorksheetException-Fehler'
, 2300: 'RangeException-Fehler'
, 2400: 'MergedCellException-Fehler'
, 2500: 'AuthenticationException-Fehler'
, 2600: 'CellDimensionException-Fehler'
, 2700: 'SessionException-Fehler'
, 2800: 'InvalidGroupException-Fehler'
, 2900: 'InvalidUserException-Fehler'
, 3000: 'TranslationTableException-Fehler'
, 3100: 'WorksheetCopyException-Fehler'
, 3200: 'WorkbookCloneException-Fehler'
, 3300: 'ExtensionRegistryException-Fehler'
, 3400: 'ExtensionCallerException-Fehler'
, 3500: 'CyclicArrayException-Fehler'
, 3600: 'WorksheetElementException-Fehler'
, 3700: 'FormatException-Fehler'
, 3800: 'StyleManagerException-Fehler'
, 3900: 'BoundedPointException-Fehler'
, 4000: 'FilterRegistryException-Fehler'
, 4100: 'ContainerWrapperException-Fehler'
, 4200: 'SelectionToLargeException-Fehler'
, 4300: 'ExtensionFailureException-Fehler'
, 4400: 'PaloConnectorException-Fehler'
, 4500: 'FatalException-Fehler'
, 4600: 'ArrayFormulaOnMergedCellException-Fehler'
, 4700: 'ValueConversionException-Fehler'
,   R1: 'GenericException-Fehler'
,   R2: 'Fehler in {FILE} in Zeile {LINE}!'
, P0_0: 'Palo Aktion ist fehlgeschlagen.'
, P1_0: 'Datenbankname ist nicht korrekt.'
, P1_1: 'Die Dimension existiert schon.'
, P1_2: 'Dimension existiert nicht.'
, P1_3: 'Die Dimension wird von Würfeln benutzt.'
, P1_4: 'Das Element existiert schon.'
, P1_5: 'Subset wurde nicht gelöscht.'
, P1_6: 'Subset wurde nicht umbenannt.'
, P1_7: 'Es steht keine Datenbankliste der Verbindung "{conn_name}" zur Verfügung.'
, P1_8: 'Subset {ss_name} konnte nicht erstellt werden.'
, P1_9:	'Für diesen Befehl haben Sie keine ausreichenden Rechte!'
, P1_10: 'Der Verbindungsstatus kann nicht geändert werden.'
, P1_11: 'Die konfigurierte Palo-Verbindung ist nicht erreichbar.'
, P1_12: 'Die Verbindung {conn_name} hat einen falschen PALO Verbindungstyp.'
, P1_13: 'Die Verbindung {conn_name} kann nicht hergestellt werden.'
, P1_14: 'Für die Verbindung {conn_name} ist kein Benutzer vorhanden.'
, P1_15: 'Neue Datenbank {db_name} kann nicht erstellt werden.'
, P1_16: 'Es ist nicht möglich,  für Ansicht einfügen Daten zu erhalten.'
, P1_17: 'Die Datenbank {db_name} kann nicht gelöscht werden.'
, P1_18: 'Es kann keine Subset-Liste generiert werden!'
};
