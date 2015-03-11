/*
 * @brief ajax
 *
 * @file Group.js
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
 * SVN: $Id: loc_de_DE.js 5012 2011-05-30 08:47:15Z l10n-tool $
 *
 */

Jedox.studio.i18n.L10n = 'de_DE';

Jedox.studio.i18n.strings = {

// main/view
"leaving_app_msg":"Sie sollten sich ausloggen bevor Sie die Anwendung schließen.",

//contentMain.js
"Document Manager":"Datei-Manager",
"File Manager":"Datei-Manager",
"Files and folders":"Ordner und Dateien verwalten",
"Report Manager":"Berichts-Manager",
"Palo Manager":"OLAP-Manager",
"Palo server administration":"Palo Datenbanken <br>modellieren und verwalten",
"User Manager":"Benutzer-Manager",

"Users":"Benutzer",

"Roles":"Rollen",
"Users and Groups administration":"Benutzer und Gruppen administrieren",
"Connection":"Verbindung",
"ETL":"ETL Manager",
"ETL administration":"ETL Server Administration",
"Database connection administration":"Datenbankverbindungen <br>anlegen und verwalten",
"internal_conn": "Interne Verbindung",
"Home Page": "Homepage",

"Explore To":"Gehe zu",
"Recent Documents":"Letzte Dokumente",
"Clear list":"Liste löschen",
"location unknown (opened throught hyperlink)":"Das vom Hyperlink angegebene Ziel ist unbekannt",
"unknown":"unbekannt",

//User.js
"General informations about user":"Allgemeine Informationen über den Benutzer",

"Full Name":"Vollständiger Name",
"English":"English",
"German":"German",

"Locale":"Lokal",
"Active":"Aktiv",
"Member Of":"Gruppenmitglieder",
"Available Groups":"Verfügbare Gruppen",
"Choose the group you want to join user":"Wählen Sie die Gruppe, zu welcher Sie den Benutzer hinzufügen möchten",
"User data":"Benutzerdaten",
"Members":"Mitglieder",
"Add user":"Benutzer hinzufügen",
"Sign in name must start with a-z/A-Z character and must contain more than two character":"Der Anmeldenamen muss mit a-z/A-Z beginnen und muss mindestens 3 Zeichen enthalten",
"Full name must start with a-z/A-Z character and must contain more than one word":"Der vollständige Name muss mit a-z/A-Z beginnen und muss mehr als ein Wort enthalten",
"Full name must start with a-z/A-Z character":"Der vollständige Name muss mit a-z/A-Z beginnen",
"Password must start with a-z/A-Z character and must contain 6 char min":"Das Passwort muss mit a-z/A-Z beginnen und muss mindestens 5 Zeichen enthalten",
"User added successefully":"Der Benutzer wurde erfolgreich hinzugefügt",
"User updated successefully":"Der Benutzer wurde erfolgreich aktualisiert",

//Group.js
"Enter the General informations about Group":"Geben Sie allgemeine Informationen über die Gruppe ein",

"Admin Role":"Rolle Admin",
"Group active":"Gruppe aktiv",
"Choose the users you want to asign to this group":"Wählen Sie die Benutzer, welche Sie der Gruppe hinzufügen möchten",
"Available Users":"Verfügbare Benutzer",
"Group data":"Gruppendaten",
"Add group":"Gruppe hinzufügen",
"Update group":"Gruppe aktualisieren",
"Group name must start with a-z/A-Z character and must contain at least two character":"Der Gruppennamen muss mit a-z/A-Z beginnen und muss mindestens 2 Zeichen enthalten",
"Group added successefully":"Die Gruppe wurde erfolgreich hinzugefügt",
"Group updated successefully":"Die Gruppe wurde erfolgreich aktualisiert",

//UGPanel.js
"All Groups": "Alle Gruppen",

"All Roles": "Alle Rollen",
"Add User":"Benutzer hinzufügen",
"Creates new user":"Neuen Benutzer anlegen",
"Remove User":"Benutzer löschen",
"Removes the user from users list":"Löscht den Benutzer von der Benutzerliste",
"Add Group":"Gruppe hinzufügen",
"Creates new group":"Neue Gruppe anlegen",
"Remove Group":"Gruppe löschen",
"Removes the group from groups list":"Löscht die Gruppe von der Gruppeliste",
"Show, move or hide":"Anzeigen, verschieben oder ausblenden",
"View in New Tab":"Anzeige in neuem Register",
"Open this panel in new tab":"Dieses Objekt in einer neuen Registerkarte öffnen",
"Select All from the list":"Alle Listeneinträge markieren",
"Clear Selection":"Auswahl löschen",
"Clear all selection":"Gesamte Auswahl löschen",

"Full name":"Vollständiger Name",
"Group name":"Gruppenname",
"All Users":"Alle Benutzer",
"Users data":"Benutzerdaten",
"Groups data":"Gruppendaten",
"Add New User":"Neuen Benutzer hinzufügen",
"Add New Group":"Neue Gruppe hinzufügen",
"User removed successefully":"Der Benutzer wurde erfolgreich gelöscht",
"Group removed successefully":"Die Gruppe wurde erfolgreich gelöscht",
"Group status":"Gruppenstatus",
"User status":"Benutzerstatus",
"active":"aktiv",
"no":"nein",
"no_connection_rights": "Sie haben keine Rechte um die Verbindung \"{conn_name}\" zu benutzen. Bitte wählen Sie eine andere Verbindung oder wenden Sie sich an den Administrator",
"Can not read data":"Daten können nicht gelesen werden",
"delete_data_err":"Befehl misslungen. Daten konnten nicht gelöscht werden!",

"Can not write data":"Daten können nicht geschrieben werden",

// Role.js

"Add Role": "Rolle hinzufügen",
"Creates new role": "Neue Rolle erstellen",
"Removes the role from role list": "Rolle von der Liste entfernen",

"Add New Role": "Neue Rolle hinzufügen",
"Enter the General informations about Role": "Allgemeine Informationen über die Rolle eingeben",
"Role Name": "Name der Rolle",
"Role name must start with a-z/A-Z character and must contain at least two character": "Der Rollenname muss mit a-z/A-Z Buchstaben beginnen und muss mindestens zwei Zeichen enthalten",
"Remove Role": "Rolle entfernen",
"Role removed successefully": "Rolle erfolgreich entfernt",
"Role added successefully": "Rolle erfolgreich hinzugefügt",
"Role updated successefully": "Rolle erfolgreich aktualisiert",
"Assigned rights": "Zugeteilte Rechte",
"Roles data": "Rollendaten",
"Role Status": "Rollenstatus",
"Member Of Role": "Mitglied der Rolle",
"Object permission": "Objektberechtigung",
"Object description": "Objektbeschreibung",
"Object name": "Objektname",
"Choose the roles you want to asign to this group": "Wählen Sie die Rollen, die Sie dieser Gruppe zuordnen wollen",
"Splash": "Splash",
"Full Access": "Voller Zugriff",
"Writable": "Schreibrecht",
"Read Only": "Leserecht",
"No Access": "Kein Zugriff",
"Choose the groups you want to asign to this role": "Wählen Sie die Gruppen, die Sie zu dieser Rolle zuordnen möchten",
"Connection_users": "Verbindung",
"Role Members":"Mitglieder der Rolle",


// object descriptions

"robj_desc_user": "Zugang zu Benutzernamen",
"robj_desc_password": "Zugang zu Passwörtern",
"robj_desc_group": "Zugang zu Gruppen",
"robj_desc_database": "Zugang zu Datenbanken",
"robj_desc_cube": "Zugang zu Würfeln",
"robj_desc_dimension": "Zugang zu Dimensionen",
"robj_desc_dimElements": "Zugang zu Dimensionselementen",
"robj_desc_cellData": "Zugang zu Datenzellen",
"robj_desc_rights": "Zugang zu den Rechten",
"robj_desc_sysOperations": "Zugang zu Systemoperationen",
"robj_desc_eventProc": "Zugang zu Ereignissen",
"robj_desc_subsetView": "Zugang zu Subsetansichten",
"robj_desc_userInfo": "Zugang zu Benutzer-Infos",
"robj_desc_rule": "Zugang zu Rules",
"robj_desc_report": "Zugang zum Berichts-Manager",
"robj_desc_file": "Zugang zum Datei-Manager",
"robj_desc_olap": "Zugang zum OLAP-Manager",
"robj_desc_userManager": "Zugang zum Benutzer-Manager",
"robj_desc_etl": "Zugang zum ETL-Manager",
"robj_desc_connection": "Zugang zum Verbindungs-Manager",

//menubar.js
"Exit":"Ausgang",
"Help Topics":"Hilfethemen",
"Action":"Aktion",
"New User": "Neuer Benutzer",

//navigationPanel
"Files":"Dateien",
"Report Repository":"Berichts-Manager",
"Users and Groups":"Benutzer-Manager",

"Admin mode":"Navigation",
"View mode":"Anzeigemodus",
"Private Reports":"Persönliche Berichte",

//navigationPanel bottom bar
"Logout": "Abmelden",
"logout_prompt": "Wollen Sie sich wirklich abmelden?",

//	ReportsTree.js
"Edit Hierarchy":"Hierarchie bearbeiten",
"Edit Hierarchy Options...":"Hierarchieoptionen bearbeiten...",
"Move Node": "Knotenpunkt verschieben",
"Copy Node": "Knotenpunkt kopieren",
"Rename Node": "Knotenpunkt umbenennen",
"Delete Node": "Knotenpunkt löschen",
"Add New Static Folder": "Neuen statischen Ordner hinzufügen",
"Add New Dynamic Folder": "Neuen dynamischen Ordner hinzufügen",
"Add new Item": "Neues Objekt hinzufügen",
"_alert: Select Item": "Bitte wählen Sie das Objekt, nach dem Sie ein neues Objekt hinzufügen möchten.",
"New Item": "Neues Objekt",
"Delete Item": "Objekt löschen",
"_alert: Select Delete": "Bitte wählen Sie das zu löschende Objekt.",
"Confirm your action": "Bestätigen Sie Ihre Aktion",
"_msg: Confirm Delete": "Wollen Sie wirklich dieses Objekt (und seine Kinder) löschen?",
"Rename Item": "Objekt umbenennen",
"_alert: Select Rename": "Bitte wählen Sie das Objekt das Sie umbenennen möchten.",
"Refresh tree and reload data": "Daten neu laden und Ansicht aktualisieren",
"_warning: double group": "Eine Gruppe mit diesem Namen existiert schon. Bitte wählen Sie einen anderen Namen.",
"_warning: double hierarchy": "Eine Hierarchie mit diesem Namen existiert schon. Bitte wählen Sie einen anderen Namen.",
"_alert: delete group": "Das Löschen dieser Gruppe löscht auch alle Hierarchien in dieser Gruppe. Wollen Sie fortfahren?",
"_error: could not rename": "Der ausgewählte Knoten konnte nicht umbenannt werden. Versuchen Sie es noch einmal oder überprüfen Sie Ihre Rechte.",
"_error: node must have name": "Der Knoten benötigt einen Namen. Bitte geben Sie im Bearbeitungsfeld einen Namen ein.",

"New Report Group": "Neue Berichtsgruppe",
"Rename Report Group": "Berichtsgruppe umbenennen",
"Delete Report Group": "Berichtsgruppe löschen",
"New Report Hierarchy": "Neue Berichtshierarchie",
"New Hierarchy": "Neue Hierarchie",
"Rename Report Hierarchy": "Berichtshierarchie umbenennen",
"Delete Report Hierarchy": "Berichtshierarchie löschen",
"_alert: delete hierarchy": "Wollen Sie wirklich diese Hierarchie löschen?",
"_warning: folder drag": "Es ist nicht möglich, den Ordner zu verschieben",
"Constant": "Konstante",
"Constants List": "Konstanten-Liste",
"Palo List": "Palo-Liste",
"Select type": "Typ auswählen",
"_warning: double rename": "{oldValue} kann nicht umbenannt werden: Eine Datei mit dem eingegebenen Namen existiert schon. Bitte geben Sie einen anderen Namen ein.",
"_warning: double name copy": "{oldValue} kann nicht gespeichert werden: Eine Datei oder ein Ordner mit diesem Namen exisiert bereits.",
"Edit Template": "Vorlage bearbeiten",
"Template Mapping": "Verknüpfungsvorlage",
"Add New Folder": "Neuen Ordner hinzufügen",
"none": "kein",
"Constants List Selection": "Konstantenlistenauswahl",
"Constant value": "Konstanter Wert",
"Quick View": "Benutzervorschau",
"Designer Preview": "Designervorschau",
"_warning: no permissions to write": "Sie haben keine Erlaubnis in den Zielordner zu schreiben",
"You are mapping": "Variablen-Zuordnung erstellen für",

"Rename Hierarchy": "Hierarchie umbenennen",
"_warning: rename hierarchy wrong btn": "Bitte benutzen Sie das Hierarchie-Drop-down-Menu zum Umbenennen.",
"Set as Default Homepage": "Als Standard-Homepage festlegen",
"Set as Group Homepage": "Als Gruppen-Homepage festlegen",
"Export": "Export",
"Open": "Öffnen",
"Open in new window": "In einem neuen Fenster öffnen",
"Root node": "Wurzelknoten",
"Data node": "Datenknoten",
"template": "Vorlage",
"folder": "Ordner",
"_report_confirm_delete":"Sind Sie sicher, das Sie diese Berichts-Datei entfernen möchten?",
"_reportFolder_confirm_delete":"Sind Sie sicher, das Sie diese Berichts-Ordner entfernen möchten? <br>Beachten Sie, dass Berichte und Ordner, die im Ordner enthalten sind, auch gelöscht werden. Vorlagen werden nicht gelöscht.",
"Edit Report Group":"Berichtsgruppe bearbeiten",

//toolbar.js
"Go to home":"Zur Startseite gehen",
"Refresh the page":"Seite aktualisieren",

//FTreePanel.js
"New Folder Group":"Neue Ordner-Gruppe",
"Edit File Group":"Dateigruppe bearbeiten",
"Edit File Group...":"Dateigruppe bearbeiten...",
"Creates New Group":"Neue Gruppe erstellen",

"Delete Folder Group":"Ordner-Gruppe löschen",
"Refresh Folder Group":"Ordner-Gruppe aktualisieren",
"New Root Folder":"Neues Stamm-Verzeichnis",

"Delete Root Folder":"Stamm-Verzeichnis löschen",
"Move":"Verschieben",
"Confirm Item Replece":"Objektersetzung bestätigen",
"replace_folder_warning_msg":"Der Ordner enthält bereits ein Objekt <b> {Name}</b> .<br>Alle Objekte werden ersetzt. </b>Wollen Sie trotzdem das Objekt verschieben oder kopieren?",
"remove_group_warning_msg":"Sie sind dabei, die Gruppe <b> {name}</b> zu löschen . Dies löscht auch alle enthaltenen Hierarchien und Dateien.<br>Wollen Sie trotzdem fortfahren?",
"Can not delete group!":"Die Gruppe kann nicht gelöscht werden!",
"Can not remove group":"Gruppe kann nicht entfernt werden",
"An error occured? Can not delete Folder Group!":"Ein Fehler ist aufgetreten. Ordner-Gruppe kann nicht gelöscht werden!",
"An error occured? Can not delete this item!":"Ein Fehler ist aufgetreten. Item kann nicht gelöscht werden!",
"Remove Hierarchy":"Hierarchie löschen",
"remove_hierarchy_warning_msg":"Sie sind dabei, die Hierarchie <b> {name}</b>  zu löschen. Dies löscht auch alle enthaltenen Dateien.<br>Wollen Sie trotzdem fortfahren?",
"Hierarchy removed successefully":"Hierarchie wurde erfolgreich gelöscht",
"An error occured? Can not delete this hierarchy!":"Ein Fehler ist aufgetreten! Diese Hierarchie kann nicht gelöscht werden!",
"Remove Folder":"Ordner löschen",
"remove_folder_warning_msg":"Sie sind dabei, <b> {name}</b> zu löschen.<br>Wollen Sie fortfahren?",
"Folder removed successefully":"Der Ordner wurde erfolgreich gelöscht",

"Error Renaming Folder":"Fehler beim Umbenennen des Ordners",
"rename_folder_error_msg":"<b> {old_name}</b> kann nicht umbenannt werden.<br>Eine Datei mit dem Namen <b> {new_name}</b> existiert schon. <br>Geben Sie einen anderen Namen für die Datei ein.",
"Copy folder":"Ordner kopieren",
"Move folder":"Ordner verschieben",
"copy_folder_error_msg":"Der Ordner {folder_name} kann nicht kopiert werden. <br> Ein Fehler ist aufgetreten.",
"cut_folder_error_msg":"Der Ordner {folder_name} kann nicht verschoben werden. <br> Ein Fehler ist aufgetreten.",
"Error Renaming Group":"Fehler beim Umbenennen der Gruppe",
"rename_group_error_msg":"Gruppe kann nicht umbenannt werden. Gruppe mit dem Namen <b>{new_name}</b> existiert schon.",
"Error Renaming Hierarchy":"Fehler beim Umbenennen der Hierarchie",
"rename_hierarchy_error_msg":"Umbennung nicht möglich. Stammverzeichnis mit dem Namen <b>{new_name}</b> existiert schon.",

//WTPanel.js
"New": "Neu",
"Palo Suite":"Palo Web",
"New Workbook":"Neue Arbeitsmappe",
"Creates new workbook":"Erstellt eine neue Arbeitsmappe",
"New Pivot":"Neuer Palo Analysebericht",


"Creates new folder":"Erstellt einen neuen Ordner",
"Remove selected":"Auswahl löschen",

"Removes node from list":"Löscht den Knotenpunkt von der Liste",
"Up one level":"Eine Ebene nach oben",
"Last Modified":"Zuletzt geändert",
"New Workbook description":"Beschreibung der neuen Arbeitsmappe",
"of":"von",
"copy_of_name":"Kopie von",
"copy_num_of_name":"Kopie ({num}) von",
"Remove Item":"Objekt löschen",
"Import file":"Datei importieren",
"Import .wss file to filesystem":"Lokale Dateien auf dem Server importieren",
"remove_item_warning_msg":"Sie sind dabei, <b> {name}</b> zu löschen. <br>Wollen Sie fortfahren?",
"remove_items_warning_msg":"Sie sind dabei, <b> {nmb}</b>  zu entfernen. <br>Wollen Sie fortfahren?",
"You did\'t select an item. Select an Item and try again.":"Sie haben nichts ausgewählt. Treffen Sie eine Auswahl aus und versuchen Sie es erneut.",
"Open in New Window": "In einem neuen Fenster öffnen",
"Confirm Item Replace":"Ersetzung des Objektes bestätigen",
"Error Renaming File or Folder":"Fehler beim Umbenennen der Datei bzw. des Ordners",
"rename_item_format_err_msg":"Der Dateiname <b>\"{fileName}\"</b> ist ungültig. Bitte ändern Sie ihn.",
"rename_item_error_msg":"<b>{old_name}</b> kann nicht umbenannt werden.<br>Eine Datei mit dem Namen <b> {new_name}</b> existiert schon. <br>Geben Sie einen anderen Namen für die Datei ein.",
"rename_item_long_error_msg":"<b> {old_name}</b> kann nicht umbenannt werden.<br>Der angegebene Name <b> {new_name}</b> ist zu lang. Maximale Länge ist 64 Zeichen. <br>Geben Sie bitte einen anderen Namen ein.",
"Item removed successefully": "Das Objekt wurde erfolgreich gelöscht",
"Insert hyperlink":"Hyperlink erstellen",
"File Folder":"Ordner",


"Microsoft Office Excel Comma Separated Values File":"Microsoft Office Excel mit Komma getrennte Werte-Datei",
"Microsoft Office Word 97 - 2003":"Microsoft Office Word 97 - 2003 ",
"Adobe Acrobat Document":"Adobe Acrobat Dokument",
"GIF Image":"GIF-Bilddatei",
"Firefox Document":"Firefox-Dokument",
"JPEG Image":"JPEG-Bilddatei",
"PNG Image":"PNG-Bilddatei",
"Microsoft Office PowerPoint 97 - 2003 Show":"Microsoft Office PowerPoint 97 - 2003 Darstellung",
"Microsoft Office PowerPoint 97 - 2003 Presentation":"Microsoft Office PowerPoint 97 - 2003 Präsentation",

"Rich Text Format":"Rich Text Format-Datei",
"Text Document":"Text-Dokument",
"Microsoft Office Excel 97 - 2003 Workbook":"Microsoft Office Excel 97 - 2003 Arbeitsmappe",
"Microsoft Office Excel Workbook":"Microsoft Office Excel Arbeitsmappe",
"WinZip File":"WinZip-Datei",
"Unknown File format":"Unbekannter Dateityp",
"wb_in_dlg_mode": "Die aktuelle Arbeitsmappe hat einen geöffneten Dialog.<br>Um weiterzumachen schließen Sie bitte den Dialog.",
"wb_in_suspend_mode": "Aktuelle Arbeitsmappe ist im Aussetzungs-Modus. <br>Um weiterzumachen schließen Sie bitte den Anwendermodus.",
"session_expired":"Ihre Sitzung wird beendet.<br>Sie werden ausgeloggt und zum Login-Fenster geführt.",
"wss_open_wait": "Bitte warten Sie bis die Arbeitsmappe geladen ist.",
"wss_openrp_wait": "Bitte warten Sie bis der Bericht geladen ist.",
"wss_openhl_wait": "Bitte warten Sie bis der Hyperlink geladen ist.",
"wss_openpivot_wait": "Bitte warten Sie bis die Pivottabelle geladen ist.",
"Palo Pivot":"Palo Pivottabelle",
"Creates new pivot grid":"Erstellt eine neue Pivottabelle",
"You have no permission for this operation":"Für diese Operation haben Sie keine Erlaubnis",
"Warning":"Warnung",
"noRightsERRMsg":"Unzureichende Zugriffsrechte auf diese Datei",
"follHLInvalidDoc": "Das Dokument, auf welches der Hyperlink verweist, wurde nicht gefunden.",
"Mark":"Markieren",
"Sort Ascending": "Aufsteigend sortieren",
"Sort Descending": "Absteigend sortieren",
"Columns": "Spalten",
"Group by": "Gruppieren nach",
"add_hpl_err_file_exists": "Eine Datei mit dem Namen <b> {new_name} </b> existiert schon. <br>Geben Sie einen anderen Dateinamen an.",
"Hyperlink name error":"Fehler Hyperlinkname",
"read_data_err":"Datenbank kann nicht gelesen werden. Bitte aktualisieren Sie die Ordner-Gruppe",
"Database read error":"Datenbanklesefehler",
"write_data_err":"In die Datenbank kann nicht geschrieben werden. Bitte aktualisieren Sie die Ordner-Gruppe.",
"Database write error":"Datenbankschreibfehler",
"New Tag":"Neuer Tag",

// dailog.js
//"informationMsg": "Info-Meldung", ???
//"adviceMsg": "Vorschlag", ???
"New File Repository":"Neues Stamm-Verzeichnis",
"Edit File Repository":"Stamm-Verzeichnis bearbeiten",
"Location (path)": "Speicherort (Pfad)",

"Hierarchy Name": "Name der Hierarchie",
"New Group":"Neue Ordner-Gruppe",
"Edit Group":"Ordner-Gruppe bearbeiten",
"Group Name":"Benutzer-Gruppenname",
"group_name_name_format_err_msg":"Der Gruppennamen muss mit a-z/A-Z beginnen und muss mindestens 3 Zeichen enthalten",
"group_name_name_exits_err_msg":"Eine Gruppe mit diesem Namen existiert bereits. Wählen Sie einen anderen Namen",
"hierarchy_name_name_format_err_msg":"Der Stammverzeichnisnamen muss mit a-z/A-Z beginnen und muss mindestens 3 Zeichen enthalten",
"hierarchy_name_name_exits_err_msg":"Ein Stammverzeichnis mit diesem Namen existiert bereits. Wählen Sie einen anderen Namen",


"New Hyperlink":"Neuer Hyperlink",
"Target":"Öffnen",
"URL (path)":"URL (Adresse)",

"Hiperlink Name":"Hyperlinkname",
"open in Studio":"Im Studio öffnen",
"open in New window": "In einem neuen Fenster öffnen",

// properties.js

"Resources":"Ressourcen",
"File Manager - Default Folder":"Datei-Manager - Standardverzeichnis",
"Image":"Bild",

"URL target":"URL-Ziel",






"Permissions":"Zugriffsrechte",






"Default":"Standard",





"Include credentials":"Enthaltene Anmeldeinformationen",
"Current user":"Aktueller Benutzer",
"Other user":"Weiterer Benutzer",
"User name":"Benutzername",




"Send link to mail":"Link an email-Adresse senden",
"Link":"Link ",
"Note: Copy into clipboard is possible with <b>ctrl + c</b> keyboard shortcut":"Hinweis: Eine Kopie in die Zwischenablage ist mit der Tastenkombination <b>Strg + c</b> möglich",
"Update URL":"URL aktualisieren",
"Send to mail":"An email-Adresse senden",
"urlPluginPropsLbl":"Dem Projekt sind möglicherweise zusätzliche Funktionalitäten zugeordnet . Auf dieser Seite können Sie angeben, welche Funktionalitäten dem Projekt zugewiesen werden und welche nicht.",
"Hide toolbar":"Symbolleiste verbergen",
"Hide save":"Speichern verbergen",
"Hide filter":"Filter verbergen",
"Hide static filter":"Statischer Filter verbergen",
"Hide axes":"Achsen verbergen",
"Hide connection picker":"Verbindungsschalter verbergen",

"date_format": "d.m.Y H:i:s",

//Refderrers.js
"Sub Nodes":"Subknoten",
"Referrers":"Verweise",

//Resources.js
"Spreadsheet":"Tabellenkalkulation",
"Path":"Pfad",
"Add From Markers":"Mit markierten Dateien verknüpfen",
"Insert": "Einfügen",

//feedback.js
"Show Referrers":"Verweise anzeigen",
"Hide Referrers":"Verweise verbergen",
"Show Dependents":"Abhängigkeiten anzeigen",
"Hide Dependents":"Abhängigkeiten verbergen",
"Yes":"Ja",
"No":"Nein",



"File group":"Ordner-Gruppe",
"File repository":"Datei-Verzeichnis",
"Report group":"Berichtsgruppe",
"Report repository":"Berichtshierarchie",
"Hyperlink":"Hyperlink ",
"Workbook":"Arbeitsmappe",
"Static":"Statisch",
"Folder":"Ordner",
"Select":"Auswahl",
"Select URL":"URL auswählen",
"Mail":"Mail ",

"Enter destination e-mail":"E-mail-Adresse eingeben",
"Link to":"Link zu",



//#########
// Backend
//#########
"W3S_Backend-err_type": "Ungültiger Systemtyp.",
"W3S_Backend-err_location": "Systemort ist nicht angegeben.",
"W3S_Backend-empty_paramlist": "Die Parameterliste ist leer.",

"W3S_BaseData-err_sysname": "Wirklicher Elementname ist nicht eingetragen.",
"W3S_BaseData-no_mandatory_el": "Es ist nicht möglich, ein verbindliches Element \"{name}\" zu finden.",
"W3S_BaseData-too_many_el": "Mehr als ein Element mit Namen \"{name}\" existiert.",
"W3S_BaseData-import_no_data": "Es existieren keine Daten für den Import.",
"W3S_BaseData-inv_el_data": "Ungültige Elementdaten.",
"W3S_BaseData-no_el_data": "Keine Elementdaten.",

"W3S_ExternalList-no_conn": "Keine Verbindung angegeben.",
"W3S_ExternalList-no_db": "Keine DB angegeben.",

"W3S_GroupData-inv_el": "Ungültiges Element.",
"W3S_GroupData-inv_el_type": "Ungültiger Elementtyp.",

"W3S_HierarchyData-inv_el": "Ungültiges Element.",
"W3S_HierarchyData-inv_el_type": "Ungültiger Elementtyp.",
"W3S_HierarchyData-backend_unsupported": "Es ist nicht möglich, System hierarchisch anders festzulegen als \"file\".",

"W3S_LinkList-inv_el": "Ungültiges Element.",

"W3S_NodeData-inv_el": "Ungültiges Element.",
"W3S_NodeData-inv_el_type": "Ungültiger Elementtyp.",
"W3S_NodeData-inv_list": "Ungültige Liste.",
"W3S_NodeData-el_no_attr": "Es gibt kein Attribut \"{attr}\" im  Element {el}.",
"W3S_NodeData-no_linklist_on_rfolder": "Der Berichtsordner kann nicht zur Verbindungsliste hinzugefügt werden.",
"W3S_NodeData-elvals_empty": "Es gibt keinen Inhalt im Listen/Wert-Element.",
"W3S_NodeData-unsupported_list_type": "Listentyp \"{type}\" wird nicht unterstützt.",
"W3S_NodeData-err_addmap": "Es ist nicht möglich, den Plan einem normalen Ordner hinzuzufügen.",
"W3S_NodeData-no_tpl_var": "Vorlagenvariable ist nicht angegeben.",
"W3S_NodeData-err_del_map": "Es ist nicht möglich, den Plan von normalen Ordner zu löschen.",
"W3S_NodeData-err_get_map": "Es ist nicht möglich, den Plan von einem normalen Ordner zu bekommen.",
"W3S_NodeData-err_ordnum": "Es ist nicht möglich, Pläne neu anzuordnen. Die Variable Ordnungszahl ist nicht erlaubt.",
"W3S_NodeData-err_ordnum_not_supported": "Es ist nicht möglich, Pläne auf diesem Knotenpunkt neu anzuordnen.",
"W3S_NodeData-no_hyperlink_type": "Es ist nicht möglich, einen Hyperlink zu setzen. Es ist kein Typ angegeben.",
"W3S_NodeData-inv_hyperlink_type": "Es ist nicht möglich, einen Hyperlink zu setzen. Ungültiger Typ.",
"W3S_NodeData-hldata_empty": "Hyperlink-/Datenelement hat keinen Inhalt.",
"W3S_NodeData-err_set_hyperlink": "Es ist nicht möglich, einen Hyperlink für diesen Knotentyp zu setzen.",
"W3S_NodeData-inv_static_type": "Ungültiger Subtyp beim statischen Knoten.",
"W3S_NodeData-inv_plugin_type": "Ungültiger Subtyp beim Plugin-Knoten.",
"W3S_NodeData-err_referrer_not_supported": " Bei diesen Knoten-Typ werden Verweise nicht unterstützt.",
"W3S_NodeData-err_resource_not_supported": "Bei diesen Knoten-Typ werden Ressourcen nicht unterstützt.",
"W3S_NodeData-err_dependent_not_supported": "Bei diesen Knoten-Typ werden Abhängigkeiten nicht unterstützt.",
"W3S_NodeData-err_params_not_supported": "Bei diesen Knoten-Typ werden Parameter nicht unterstützt.",

"W3S_BaseLink-inv_target": "Ungültiges Hyperlinkziel.",

"W3S_URLLink-no_url": "URL ist nicht angegeben.",

"W3S_NodeLink-err_group": "Ungültiger Namen der Gruppe.",
"W3S_NodeLink-err_hierarchy": "Ungültiger Namen der Hierarchie.",
"W3S_NodeLink-err_node": " Namen des Knotenpunktes.",
"W3S_NodeLink-err_type": "Ungültiger Knotentyp.",

"W3S_ODBCList-inv_el": "Ungültiger Listentyp.",
"W3S_ODBCList-no_list_name": "Listenname ist nicht angegeben.",

"W3S_PaloList-inv_list_type": "Ungültiger Listentyp.",
"W3S_PaloList-no_dim_name": "Dimensionsname ist nicht angegeben.",

"W3S_PaloSubsetList-no_data": "Subsetdaten sind nicht angegeben.",

"W3S_FSPlugin-no_newname": "Es ist nicht möglich, {type} zu erstellen oder umzubenennen, weil kein neuer Name eingegeben wurde.",
"W3S_FSPlugin-dir_exists": "Es ist nicht möglich, {type} Ordner {dir} zu erstellen, weil er schon existiert.",
"W3S_FSPlugin-unable_mkdir": "Es ist nicht möglich, {type} Ordner {dir} zu erstellen.",
"W3S_FSPlugin-unable_rmdir": "Es ist nicht möglich, {type} Ordner {dir} zu löschen.",
"W3S_FSPlugin-file_exists": "Es ist nicht möglich, die Arbeitsmappe {wb} zu erstellen, weil sie schon existiert.",
"W3S_FSPlugin-unable_add_wb": "Es ist nicht möglich, die Arbeitsmappe {wb} zu erstellen.",
"W3S_FSPlugin-unable_rm_file": "Es ist nicht möglich, die Arbeitsmappe {wb} zu löschen.",
"W3S_FSPlugin-unable_rm_recov_file": "Die  Wiederherrstellungsdatei {file} kann nicht aus dem Dateisystem entfernt werden.",
"W3S_FSPlugin-no_srcnode": "Es ist nicht möglich, {act} {type} {node}, weil es nicht existiert.",
"W3S_FSPlugin-dstnode_exists": "Es ist nicht möglich, {act} {type}, da der Knotenpunkt {node} schon existiert.",
"W3S_FSPlugin-unable_move": "Es ist nicht möglich, {type} {src} nach {dst} zu verschieben.",
"W3S_FSPlugin-unable_copy": "Es ist nicht möglich, {type} {src} nach {dst} zu kopieren.",
"W3S_FSPlugin-unable_rename": "Es ist nicht möglich, {type} {src} nach {dst} umzubenennen.",
"W3S_FSPlugin-no_srchierarchy": "Es ist nicht möglich, {hierarchy} umzubenennen, weil sie nicht existiert.",
"W3S_FSPlugin-dsthierarchy_exists": "Es ist nicht möglich, die Hierarchie umzubenennen, weil {hierarchy} schon nicht existiert.",

// Studio errors










// TemplateMapping.js

"ODBC list": "ODBC-Liste",
"_warning: valid list": "Wählen Sie zunächst eine gültige Liste",
"Invalid path": "Ungültiger Pfad",
"List type": "Listentyp",
"Default value": "Vorgabewert",
"List/Dynamic Folder": "Liste/Dynamischer Ordner",
"Report List": "Berichts-Liste",



// VarMapping.js
"Choose Type": "Wählen Sie den Typ",
"Select Connection": "Wählen Sie die Verbindung",
"Palo Subset List": "Palo Subset Liste",





"Set map or enter manually": "Zuordnung festlegen oder manuell eingeben",
"Set list or enter manually": "Liste festlegen oder manuell eingeben",

// ReportsPanel.js
"_warning: manage files disabled": "In diesem Bereich können Sie keine Dateien verwalten",
"Variable Mapping": "Variablen-Zuordnung",
"This operation will delete all mappings on all variables": "Dieser Befehl wird alle Zuordnungen zu allen Variablen löschen",
"Template": "Vorlage",
"Mapping": "Zuordnen",
"Apply mapping": "Zuordnung anwenden",
"Delete mapping": "Zuordnung aufheben",
"linked_wb_opened_warrning":"Es ist bereits ein anderer Bericht geöffnet, welcher zur gleichen Arbeitsmappe verknüpft ist. Möchten Sie diesen zuerst schließen?",
"Warrning":"Warnung",

//manageHomepage.js

"defHP_manager_howto": "Wählen Sie die Gruppe, die Sie verwalten möchten, und verwenden Sie die Schalter um Einstellungen bearbeiten.",
"defHP_manager_curr": "Zur Zeit ausgewählte Standard-Startseite",
"No Default Homepage": "Keine Standard-Startseite",
"No Group Homepage": "Keine Gruppen-Startseite",
"Manage Group Homepage": "Gruppen-Startseite managen",
"Unset": "Zurückstellen",
"Manage Home Page": "Startseite managen",
"Manage Default Homepage": "Standard-Startseite managen",

//	SelectionWizard.js

"Connection Error": "Verbindungsfehler",
"Menu error": "Menüfehler",
"List selector": "Listenauswahl",
"Palo List Selection": "Palo Listenauswahl",
"Palo List Error": "Palo-Listenfehler",
"Please select dimension or subset": "Bitte wählen Sie die Dimension oder das Subset",

// PALO
"Palo Admin": "OLAP-Manager",
"Subset Admin": "Subseteditor",
"Database Admin": "Datenbankverwaltung",

//Properties Dlg



"Location":"Ort",
"Size":"Größe",
"Size on disk":"Größe auf Datenträger",
"Created":"Erstellt",
"Modified":"Geändert",
"Accessed":"Zugriff",
"Groups":"Gruppen",

"Allow":"Erlauben",
"Deny":"Verweigern",
"Full Control":"Vollzugriff",
"Write":"Schreiben",
"Read":"Lesen",
"No groups":"Keine Gruppen",
"Add":"Hinzufügen",


"Security":"Sicherheit",
"Properties":"Eigenschaften",
"OK":"OK",
"Cancel":"Abbrechen",
"Apply":"Übernehmen",
"Can not read groups data from database":"Gruppendaten können nicht aus der Datenbank gelesen werden.",
"Database error":"Datenbankfehler",

// Node Export
"nodeExp_err": "Datei bzw. Ordner kann nicht exportiert werden.",
"nodeExp_no_params": "Fehlendende Knotenpunkt-Parameters",
"nodeExp_no_node": "Kann Knotenpunkt mit der ID = \"{id}\" nicht finden",
"nodeExp_no_file": "Knotenpunkt existiert nicht im Dateisystem",
"nodeExp_proc_error": "Verarbeitungsfehler",



//CPanel.js
//"Connections":"Verbindungen",
"Connection active":"Verbindung aktiv",
"Password":"Passwort",
"User Name":"Benutzername",
"Port":"Port ",
"Host":"Host ",
"Description":"Beschreibung",
"Connection Name":"Verbindungsname",
"Type":"Typ",
"Connection data":"Verbindungsdaten",

"added":"hinzugefügt",
"Update connection":"Update-Verbindung",
"updated":"aktualisiert",
"Connection name must start with a-z/A-Z character and cannot contain...":" und er darf Folgendes nicht enthalten: ...",
"Host name must start with a-z/A-Z character and must contain more than one word...":"Der Hostnamen muss mit a-z/A-Z beginnen und er darf nur ein Wort enthalten...",
"Port name must be a number...":"Der Portnamen muss eine Zahl sein ...",
"User name must start with a-z/A-Z character and cannot contain...":"Der Benutzernamen muss mit a-z/A-Z beginnen und darf Folgendes nicht enthalten: ...",
"Password must start with a-z/A-Z character and must contain 5 char min...":"Das Passwort muss mit a-z/A-Z beginnen und muss mindestens 5 Zeichen lang sein.",
"Use login credentials": "Anmeldedaten verwenden",



//CTreePanel
"Remove connection":"Verbindung löschen",
"Remove":"Löschen",
"Removes connection from list":"Löscht die Verbindung aus der Liste",
"Remove Connection":"Verbindung löschen",
"remove_connection_warning_msg":"Dies wird die Verbindung <b> {conn}</b>  löschen. <br>Möchten Sie fortfahren?",
"New Connection":"Neue Verbindung",
"Creates new connection":"Neue Verbindung anlegen",

//import dialog - studio
"upload_err_file_exists": "Die Datei kann nicht importiert werden. Der Dateiname wird bereits verwendet.",
"Application Error": "Anwendungsfehler",
"File to Import": "Datei für den Import",
"Upload": "Importieren",
"error_importerror": "Fehler beim importieren - bitte versuchen Sie es erneut",
"Error": "Fehler",
"Browse": "Durchsuchen",

//ETL
"ETL Manager": "ETL-Manager",
"Login problem": "Loginproblem",
"_info: etl: bad username": "Für die ETL Administration wurden Benutzername und Passwort nicht akzeptiert. Versuchen Sie sich neu einzuloggen oder benutzen Sie andere Anmeldeinformationen für die ETL Administration.",
"ETL Login service is not available.": "Der ETL Login-Service ist nicht erreichbar.",
"ETL is loading, please wait": "Bitte warten, ETL wird geladen",
"loading": "Es wird geladen",

//preferences
"Localization":"Lokalisation",
"Deutsch":"Deutsch",
"Francais":"Français",
"Group":"Gruppe",
"Hierarchy":"Hierarchie",
"Reports":"Berichts-Manager - Standardverzeichnis",
"Access your dynamic reports":"Zugang zu dynamischen Berichten",

"General":"Allgemein",
"Environment":"Umgebung",
"Theme":"Design",
"Toolbar":"Symbolleiste",
"Classic":"Klassisch",
"Ribbon":"Ribbon ",
"Options":"Optionen",

"WSS":"Tabellenblatt",
"About":"Über",
"About Palo Suite":"Über Palo Suite",
"<not set>":"<nicht gesetzt>",
"&lt;not set&gt;":"<nicht gesetzt>",
"Palo Online":"Palo Online",
"Help":"Hilfe",
"Enter your online Palo access data":"Geben Sie Ihre Palo-Online-Zugangsdaten ein",
"nregmsg":"Um Zugang zur Hilfe zu bekommen müssen Sie Ihr Konto auf www.jedox.com registrieren",
"Assigned Groups": "Zugewiesene Gruppen",
"Choose the group which the user is part of": "Wählen Sie die Gruppe, der der Benutzer angehört",
"Assigned Users": "Zugewiesene Benutzer",
"Assigned Roles": "Zugewiesene Rollen",
"Connection Manager": "Verbindungsmanager",
"Copy": "Kopieren",
"Rename": "Umbenennen",
"Delete": "Löschen",
"Rename Folder Group": "Ordnergruppe umbenennen",
"Create new item": "Neues Objekt anlegen",
"Remove selected items": "Markierte Okjekte entfernen ",
"One level up": "Eine Ebene nach oben",
"Import workbook (.wss)": "Arbeitsmappe importieren (.wss)",
"View": "Ansicht",
"Change view mode": "Ansichtmodus ändern",
"Root Folder Name": "Verzeichnisname",
"Studio-err_bad_palo_conn_type": "Verbindung nicht möglich. Typ der Verbindung {conn_name} ist nicht korrekt.",
"Studio-err_no_conn": "Verbindung {conn_name} nicht möglich.",
"Studio-err_no_list_of_databases": "Datenbankliste der Verbindung {conn_name} kann nicht erstellt werden..",
"Studio-err_no_list_of_dimensions": "Dimensionsliste von {conn_name}/{db_name} kann nicht erstellt werden..",
"Studio-err_no_list_of_elements": "Elementliste der Dimension {dim_name} kann nicht erstellt werden.",
"Studio-err_no_list_of_subsets": "Subsetliste der Dimension {dim_name} kann nicht erstellt werden.",
"Studio-err_no_subset_list_empty_subset": "Subset {ss_name} ist nicht definiert.",
"Studio-err_no_subset_list": "Subset {ss_name} kann nicht erstellt werden.",
"Studio-err_no_list_by_palo_path": "Liste kann nicht erstellt werden.",
"Report Manager - Default Folder": "Report Manager - Standardordner",
"Appearance": "Ansicht",
"File Manager - View": "Datei-Manager - Ansicht",
"List": "Liste",
"Icons": "Symbole",
"Details": "Details ",
"Tags": "Tags ",
"Manage Tagged files": "Mit Tags versehene Dateien verwalten",
"All": "Alle ",
"Context": "Kontext",
"Tag Manager": "Tag-Manager",
"Clear All": "Alles löschen",
"Mark/Tag": "Tag zuweisen",
"Tag": "Tag ",
//license
"licenceHeaderTitle": "Excel mit Palo optimieren: Open Source BI für Planung, Analyse und Reporting",
"licenceWarningTitle": "Ihre Palo Premium Lizenz wird in 5 Tagen auslaufen",
"msg1": "Nehmen Sie Kontakt mit Jedox auf. Fordern Sie noch heute ein Angebot für die Palo Premium Edition an.",
"msg2": "Oder nutzen Sie die Palo COmmunity Edition als 100% Open Source Version. Hier geht's zum download der Community Edition",
"msg3": "Informieren Sie sich über die Vorteile und alle Unterschiede der Premium Version gegenüber der Open Source Version von Palo.",
"licenceHeaderWarningTitle": "Excel mit Palo optimieren: Open Source BI für Planung, Analyse und Reporting",
"licenceErrorTitle": "Premium-Lizenz ist abgelaufen",
"quoteMsg": "Nehmen Sie Kontakt mit Jedox auf. Fordern Sie noch heute ein Angebot für die Palo Premium Edition an.",
"communityMsg": "Oder nutzen Sie die Palo Community Edition als 100% Open Source Version. Hier geht's zum Download der Community Edition",
"comparisonMsg": "Informieren Sie sich über die Vorteile und alle Unterschiede der Premium Version gegenüber der Open Source Version von Palo.",
"Palo web licence": "Palo Web Lizenz",
"Angebot Palo Premium anfordern": "Angebot Palo Premium anfordern",
"Download Palo for exel - Community edition": "Palo Community Edition herunterladen",
"Funktionsubersicht Premium / Community": "Funktionsübersicht Premium / Community",
"licenceHeaderErrorTitle": "Excel mit Palo optimieren: Open Source BI für Planung, Analyse und Reporting",
//links
"quoteURL":"http://www.jedox.com/de/produkte/price-wizard/price-wizard.html",
"communityURL":"http://www.jedox.com/de/download/palo-downloads-current-version/weitere-downloads-3.1.html",
"comparisonURL":"http://www.jedox.com/de/produkte/Uebersicht-palo-supported-open-source-vs-premium.html",
"Set password": "Passwort festlegen",
"Preselect in tree": "Vorauswahl im Baum",
"Palo Web - View": "Ansicht Palo Web ",
"Show navigation on load": "Navigationsleiste anzeigen",
"User Manager - View": "Ansicht Benutzermanager",
"Horizontal": "Horizontal",
"Vertical": "Vertikal",
"Tabbed": "Registerkarten extra",
"Designer mode": "Designermodus",
"Viewer mode": "Benutzermodus",
"Show toolbar on load": "Symbolleiste anzeigen",
"Show formula bar on load": "Bearbeitungsleiste anzeigen",
"Show status bar on load": "Statusleiste anzeigen",
"Sign in name must start with a-z/A-Z/09 character and must contain more than two character": "Der Login-Namen muss mit einem Zeichen a-z/A-Z beginnen und muss mehr als zwei Zeichen enthalten.",
"Group name must start with a-z/A-Z/0-9 character and must contain at least two character": "Der Gruppennamen muss mit einem Zeichen a-z/A-Z beginnen und muss mindestens zwei Zeichen enthalten.",
"Connection name must start with a-z/A-Z/0-9 character and cannot contain...": "Der Verbindungsnamen muss mit einem Zeichen a-z/A-Z beginnen und darf Folgende nicht enthalten…",
"Host name must start with a-z/A-Z character": "Der Hostnamen muss mit einem Zeichen a-z/A-Z/0-9 beginnen.",
"Logout_tt": "<u>L</u>ogout (Ctrl+L)",
"Options_tt": "<u>O</u>ptionen (Ctrl+O)",
"Connection Manager nav": "Verbi<u>n</u>dungsmanager",
"Only for this folder": "Nur für diesen Ordner",
"Group Name-new": "Ordnergruppenname",
"W3S_Frameset-no_frames": "Keine Frames im Frameset.",
"W3S_Frame-inv_frame_src": "Ungültige Frame-Quelle.",
"W3S_Frameset-inv_frameset_rowcol": "Ungültige Informationen (ungültiger Typ) für Frameset.",
"W3S_NodeData-inv_frameset": "Ungültiges Frameset.",
"W3S_Frameset-inv_frame": "Ungültiges Frame im Frameset.",
"W3S_Frameset-inv_frame_count": "Ungültige Frameanzahl im Frameset.",
"Data missing": "Daten fehlen",
"data_missing_err": "Sie haben nicht alle Daten eingegeben. Es fehlen Daten!",
"Custom": "Benutzerdefiniert",
"Templates": "Vorlagen",
"Rows": "Zeilen",
"Not set": "Nicht festgelegt",
"Set source from tagged": "Quelldatei festlegen",
"Set properties for source": "Eigenschaften der Quelle festlegen.",
"Hide scroolbars": "Laufleisten verbergen",
"Hide sheet selector": "Blattauswahl verbergen",
"Params": "Eigenschaften",
"New Frameset": "Neues Frameset",
"Hide scrollbars": "Laufleisten verbergen",
"files_ref_err_msg": "Die Datei wurde nicht gefunden. Wenn Sie eine Datei aus der Liste der zuletzt verwendeten Dateien auswählen, dann darf die Datei nicht umbenannt, verschoben oder gelöscht worden sein.",
"ref_err_msg": "<b> {file} </b> wurde nicht gefunden. Wenn Sie eine Datei aus der Liste der zuletzt verwendeten Dateien auswählen, dann darf die Datei nicht umbenannt, verschoben oder gelöscht worden sein.",
"unknown right object": "Unbekanntes Rechte-Objekt",
"robj_desc_drillthrough": "Drill Through Objekt",
"W3S_Frameset-duplicate_frame_name": "Doppelter Frame-Name \"{name}\".",
"W3S_Frame-err_name": "Der Frame-Name ist nicht definiert.",
"reports_ref_err_msg": "Der Bericht konnte nicht gefunden werden. Wenn Sie versuchen, einen Bericht aus der Liste der zuletzt verwendeten Dokumente zu öffnen, dann stellen Sie sicher, dass der Bericht nicht umbenannt, verschoben oder gelöscht wurde.",
"Report Reference error": "Bericht-Referenz-Fehler",
"frameset_alowed_charset_err_msg": "Der Framenamen muss mit einem Zeichen a-z/A-Z/0-9 beginnen.",
"frameset_alowed_name_err_msg": "Der Name muss im Frameset einmalig sein.",
"Insert and Untag": "Einfügen und Tag entfernen",
"Load/Refresh": "Laden / Aktualisieren",
"Language": "Sprache",
"As Resource": "Als Ressource",
"As Frame": "Als Frame",
"frame": "Frame",
"resource": "Ressource",
"Hide horizontal scrollbar": "Horizontale Laufleiste verbergen",
"Hide vertical scrollbar": "Vertikale Laufleiste verbergen",
"widths": "Breiten",
"heights": "Höhen",
"Edit Frameset": "Frameset bearbeiten",
"invalid_frameset_err": "Falscher Frameset. Frameset muss mindestens zwei Frames enthalten.",
"rows_data_missing_err": "Sie haben nicht alle Daten eingegeben. Information über die Höhe fehlt!",
"columns_data_missing_err": "Sie haben nicht alle Daten eingegeben. Information über die Breite fehlt!",
"source_data_missing_err": "Sie haben nicht alle Daten eingegeben. Information über die Quelle fehlt!",
"Group Status": "Gruppen Status",
"User Status": "Benutzer Status",
"inactive": "inaktive",
"imp_success_msg": "Datei wurde erfolgreich importiert.",
"Import log": "Import Log",
"remove_items_no_perms_err_msg": "<b> {names} </b> wurden nicht entfernt. <br>Sie haben dafür keine Berechtigung.",
"paste_items_no_perms_err_msg": "<b> {names} </b> können nicht eingefügt werden. <br>Sie haben dafür keine Berechtigung.",
"Use for export": "Für Export benutzen",
"full_name_validation_err":"Der vollständige Name muss mit einem Buchstaben beginnen und darf folgende Zeichen nicht enthalten:<b>#$%^&*\"+=<>!?~:;|/\(){}[]</b>",

"In project": "In Projekt",
"Standalone": "Standalone",
"Mode": "Modus",
"Interface": "Oberfläche",
"Credentials": "Anmeldung",

"Studio-err_read_def_loc_path": "Standard-Speicherverzeichnis kann nicht ermittelt werden",
"sign_in_name_validation_err": "Der Login-Name muss mehr als zwei Zeichen enthalten. Nicht erlaubt sind <b>@#$%^&*\"\'+=<>!?, ~:;|/\(){}[]</b>.",
"password_validation_err": "Das Passwort muss mindestens 5 Zeichen enthalten.",
"chb_updt_desc": "Palo Suite Versionsüberprüfung",
"Refresh": "Aktualisieren.",
"Refresh this folder": "Ordner aktualisieren.",
"updateCheckTitle": "Überprüfung auf Updates.",
"updateCheckText": "Es gibt eine neue Palo Suite Version. Wollen Sie sie herunterladen?",
"_msg: new Varset": "Neues Varset speichern.",
"Design View": "Design-Ansicht",
"_report_refreshGH": "Gruppe/Hierarchie aktualisieren",
"Export All Report Groups": "Alle Berichts-Gruppen exportieren",
"Export Report Group": "Berichts-Gruppe exportieren",
"Batch": "Batch",
"Batch PDF Wizard": "PDF-Batch Assistent",
"Quick Varset": "Schnelles Varset",
"Private Varsets": "Private Varsets",
"Global Varsets": "Globale Varsets",
"Private Variable": "Private Variable",
"All Values": "Alle Werte",
"New Varset": "Neues Varset",
"Enter name for Varset": "Varsetname eingeben",
"Delete Varset": "Varset löschen",
"_msg: Delete Verset": "Sie sind sicher, dass Sie das Varset löschen möchten?",
"Rename Varset": "Varset umbenennen",
"Enter new name for Varset": "Neuer Name des Varsets eingeben",
"Back": "Zurück",
"Next": "Weiter",
"Unable to generate report": "Bericht kann nicht erzeugt werden",
"Group by Report": "Gruppieren nach Bericht",
"Group by Varset": "Gruppieren nach Varset",
"Generation Order": "Auftrag generieren",
"Unable to save Varset": "Das Varset kann nicht gespeichert werden",
"Unable to delete Varset": "Das Varset kann nicht gelöscht werden",
"Unable to rename Varset": "Das Varset kann nicht umbenannt werden",
"Create": "Erstelle",
"Stored Varsets": "Gespeicherte Varsets",
"Used Variables": "Verwendete Variablen",
"Selected Values": "Ausgewählte Werte",
"_lbl:repTree": "Wählen Sie Ordner und/oder Berichte für das PDF-Batch aus (es sind jeweils mehrere  möglich).",
"_desc:CustRepHeader": "Klicken Sie in den Bearbeitungsbereich und dann auf den entsprechenden Schalter um Datum, Uhrzeit, Varset-Beschreibung oder Dateiname einzutragen. ",
"Left section": "Linker Bereich",
"Right section": "Rechter Bereich",
"Custom Report Header": "Benutzerdefinierter Berichtskopf",
"Format text": "Text formatieren",
"Insert Date": "Datum einfügen",
"Insert Time": "Uhrzeit einfügen",
"Insert File Name": "Filialname einfügen",
"Insert Varset Description": "Varset-Beschreibung einfügen",
"Export All Folder Groups": "Alle Ordner-Gruppen exportieren",
"Export Folder Group": "Ordner-Gruppe exportieren ",
"Import": "Import",
"Import Into Group": "Importieren in Gruppe",
"Select report from the tree": "Wählen Sie einen Bericht aus dem Baum",
"im_bndl_msg_imported": "Importiert",
"im_bndl_msg_modified": "Importiert**",
"im_bndl_msg_failed": "Fehlgeschlagen",
"Content of the bundle": "Inhalt des Pakets",
"Log result": "Ergebnismeldung",
"imp_into_fldr_bndl_file_info": "Das Paket wird in den Ordner importiert. Namensgleiche Dateien werden überschrieben!",
"imp_into_hrc_bndl_file_info": "Das Paket wird in das Stamm-Verzeichnis importiert. Namensgleiche Dateien werden überschrieben!",
"imp_into_grp_bndl_file_info": "Das Paket wird in die Ordner-Gruppe importiert. Ein neues Stamm-Verzeichnis wird angelegt oder benutzt, wenn es schon existiert. Schon vorhandene gleichnamige Dateien werden  überschrieben!",
"imp_bndl_file_info": "Das Paket wird oberhalb der existierenden Ordner-Gruppen importiert. Neue Ordner-Gruppen werden angelegt oder benutzt, wenn sie schon existieren. Vorhandene gleichnamige Dateien werden überschrieben!",
"imp_into_fldr_bndl_report_info": "Das Paket wird in den Ordner importiert. Dateien werden im Datei-Manager hinzugefügt und schon vorhandene gleichnamige Dateien werden überschrieben!",
"imp_into_hrc_bndl_repor_info": "Das Paket wird in die Berichtshierarchie importiert. Dateien werden im Datei-Manager hinzugefügt und schon vorhandene gleichnamige Dateien werden überschrieben!",
"imp_into_grp_bndl_repor_info": "Das Paket wird in die Berichtsgruppe importiert. Eine neue Berichtshierarchie wird angelegt oder benutzt, wenn sie schon existiert. Gleichnamige Berichte werden ersetzt. Dateien werden im Datei-Manager hinzugefügt und schon vorhandene gleichnamige Dateien werden überschrieben!",
"imp_bndl_repor_info": "Das Paket wird oberhalb der existierenden Berichtsgruppen importiert. Neue Berichtsgruppen werden angelegt oder benutzt, wenn sie schon existieren. Gleichnamige Berichte werden ersetzt. Dateien werden im Datei-Manager hinzugefügt und schon vorhandene gleichnamige Dateien werden überschrieben!",
"imp_bndl_type_err_msg": "Nur <b>*.pb</b> Dateien.",
"bndl_file_type": "(*.pb)",
"Extract": "Auszug",
"Select report from the tree.": "Wählen Sie einen Bericht aus dem Baum.",
"This wizard will help you import a file.": "Dieser Assistent hilft Ihnen, eine Datei zu importieren.",
"Bundle contents": "Paketinhalt",
"Extract bundle": "Paket auspacken",
"Status": "Status",
"im_bndl_msg_modified_legend": "** existierte auf dem Dateisytem und wurde überschrieben",
"Show import log": "Importprotokoll anzeigen",
"imp_bndl_content_err_msg": "Nur <b>pb</b>-Dateien mit Berichten als Inhalt.",
"imp_bndl_no_rep_cnt_err_msg": "Kann pb-Datei nicht importieren. <br>Sie enthält keine Berichte.",
"W3S_FSPlugin-replace_no_srcnode": "Kann {act} {typ} {node} auf Dateisystem nicht durchführen, weil die neue Datei nicht existiert."
};

