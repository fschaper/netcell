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
 * SVN: $Id: loc_ru_RU.js 4664 2011-02-28 14:48:20Z l10n-tool $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Отмена",
"File": "Файл",
"New": "Новый",
"Open": "Открыть",
"Close": "Закрыть",
"Save": "Сохранить",
"Properties": "Свойства",
"Edit": "Редактировать",
"Cut": "Вырезать",
"Copy": "Копировать",
"Paste": "Вставить",
"View": "Просмотр",
"List": "Список",
"Hide": "Скрыть",
"Help": "Помощь",
"Create new document": "Создайте новый документ",
"Open document": "Открыть документ\n",
"Save document": "Сохранить документ",
"Bold": "Жирный",
"Italic": "Курсив",
"Underline": "Подчеркнутый",
"Delete": "Удалить",
"Rename": "Переименовать",
"Select All": "Выбрать все",
"Type": "Тип",
"Warning": "Предупреждение",
"Password": "Пароль",
"Layout": "Расположение",
"General": "Общее",
"Preview": "Предварительный просмотр",
"Refresh": "Обновить",
"None": "Нет",
"Bottom": "Вниз",
"Right": "Направо",
"Up": "Наверх",
"New Folder": "Новая папка",
"Thumbnails": "Пиктограммы",
"Details": "Детали",
"Description": "Описание",
"Options": "Опции",
"Modeller": "Конструктор",
"Home": "Главная страница",
"Size": "Размер",

"Quick View": "Предварительный просмотр администратора",
"Designer Preview": "Предварительный просмотр редактора",
"Active": "Активный",
"Path": "Путь",
"Apply": "Применить",
"Rename Sheet": "Переименуйте лист",

//Paste Subset Dialog
"_tit: hb List Editor": "DynaRange List Editor",
"Subset Editor": "Редактор подмножества",
"Subset General Settings": "Основные настройки подмножества",
"Dimension": "Измерение",
"Select First Alias": "Выберите первый псевдоним",
"Select Second Alias": "Выберите второй псевдоним",
"Alias": "Псевдоним",
"Optional Settings": "Дополнительные настройки",
"Hierarchy enumeration": "Нумерация иерархии",
"Hierarchy": "Иерархия",
"Text": "Текст",
"Picklist": "Picklist",
"Attribute": "Атрибут",
"Sort": "Сортировка",
"Level": "Уровень",
"Depth": "Глубина",
"Flat": "Плоский",
"Show parents below children": "Показывать родительские вершины после потомков",
"Show duplicates": "Показывать дубликаты",
"Show children of hidden elements": "Показывать потомков скрытых элементов",
"_msg: hb Lists": "DynaRange Lists",
"[_name: hb List]": "[DynaRange List]",
"Formula Subset": "Формула подмножества",
"[Formula Subset]": "[Формула подмножества]",
"Local Subsets": "Локальные подмножества",
"Global Subsets": "Глобальные подмножества",
"Stored Subsets": "Хранимые подмножества",
"Auto": "Автоматически",
"By Definition": "По определению",
"By Element name": "По имени элемента",
"By Alias": "По псевдониму",
"By Value": "По значению",
"By Attribute": "По атрибуту",
"All Elements": "Все элементы",
"Base Elements Only": "Только базовые элементы",
"Consolidated Elements Only": "Только консолидированные элементы",
"Reverse": "Обратить",
"Sort at Level": "Сортировать на уровне",
"Sorting behaviour": "Поведение сортировки",
"Reverse Order": "Обратный порядок",
"Type Limitation": "Введите ограничение",
"New Subset": "Новое подмножество",
"Enter name for Subset": "Введите имя подмножества",
"Delete Subset": "Удалить подмножество",
"_msg: Delete Subset": "Вы уверены, что хотите удалить подмножество?",
"Rename Subset": "Переименовать подмножество",
"Enter new name for Subset": "Введите новое имя подмножества",
"_msg: update Subset": "Сохранение подмножества.",
"_msg: new Subset": "Сохранение нового подмножества.",
"_msg: delete Subset": "Удаление подмножества.",
"_msg: rename Subset": "Сохранение нового имени подмножества.",
"[All Elements]": "[Все Элементы]",
"Filter elements hierarchically": "Фильтровать элементы иерархически",
"Cyclic list": "Циклический список",
"Below": "Под",
"Above": "Над",
"Consolidated": "Консолидированные элементы",
"Base Elements": "Базовые элементы",
"Activate this filter": "Активировать этот фильтр",
"Exclusive": "Исключительный",
"Filter Element by type": "Filter Element by type",
"Filter elements by Level": "Фильтровать элементы по уровню",
"List length": "Длина списка",
"Start level": "Начальный уровень",
"Indent Enumeration": "Нумерация отступа",
"End level": "Конечный уровень",
"Settings": "Настройки",
"_subsetTextTabExamples": 'Examples:<br>' +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "<b>PERL-Regular expressions</b>",
"Behaviour": "Поведение",
"Dimension Contents": "Содержание измерения",
"Please select how to insert choosen elements": "Укажите, как вставить выбранные элементы",
"_subsetAttrTabExample": '<br>Examples:<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Переменный",
"Alias 1": "Псевдоним 1",
"Alias 2": "Псевдоним 2",
"Level Start": "Начало уровня",
"Level End": "Конец уровня",
"Criteria": "Условие",
"Sort Attribute": "Атрибут сортировки",
"Sort Level": "Уровень сортировки",
"Quick": "Быстрый",
"SUM OF THE ELEMENTS": "СУММА ЭЛЕМЕНТОВ",
"ALL ELEMENTS": "ВСЕ ЭЛЕМЕНТЫ",
"AVEREGE OF THE ELEMENTS": "СРЕДНЕЕ ЗНАЧЕНИЕ ЭЛЕМЕНТОВ",
"MAXIMUM OF THE ELEMETNS": "МАКСИМУМ ЭЛЕМЕНТОВ",
"ANY ELEMENT": "ЛЮБОЙ ЭЛЕМЕНТ",
"MINIMUM OF THE ELEMENTS": "МИНИМУМ ЭЛЕМЕНТОВ",
"STRING": "СТРОКОВЫЙ",
"Please select and set attribute fields": "Пожалуйста, выберите и установите поля атрибута",
"Select Cube": "Выберите куб",
"Indent": "Отступ",
"FRONT": "Дополнение перед списком",
"BACK": "Дополнение после списка",
"MERGE": "Объединить со списком",
"SUBTRACT": "SUBTRACT",
"Take topmost elements": "Выбрать наивысшие элементы",
"Take all upper elements up to %": "Увеличить все агрегированные элементы на %",
"Take all lower elements up to %": "Увеличить все детализированные элементы на %",
"List Length": "Длина списка",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Picklist Type",
"Cube": "Куб",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Topmost",
"Upper": "Upper",
"Lower": "Lower",
"Slice operators": "Slice operators",
"AND": "И",
"Named Variables": "Named Variables",
"subset_Indent": "Отступ",
"Obtaining preview data": "Получение данных предварительного просмотра",
"Unable to resolve value for": "Unable to resolve value for",
"_msg: paloSbstDFilterEnabled": "When Data Filter is enabled, processing to get preview list can take more time",

//PALO Modeller
"PALO Modeller": "Конструктор PALO",
"Error": "Ошибка",
"Elements": "Элементы",
"Attributes": "Атрибуты",
"Subsets": "Подмножества",
"Consolidated Elements": "Консолидированные элементы",
"show Tree": "Show tree",
"<< Database": "<< БД",
"Expand All": "Развернуть все",
"Collapse All": "Свернуть все",
"Choose Server/Database": "Выбрать Сервер/БД",
"Dimensions and Global Subsets": "Dimensions and Global Subsets",
"Cubes": "Кубы",
"Database": "БД",
"system": "система",
"attributes": "атрибуты",
"normal": "обычный",
"loaded": "загружено",
"not loaded": "не загружено",
"_err: Timer": "Time out for Server request.",
"_msg: Timer": "Waiting time went off.",
"Add": "Добавить",
"Consolidate": "Consolidate",
"Numeric": "Numeric",
"String": "Строковый тип",
"Copy Elements": "Копировать элементы",
"Paste Elements": "Вставить элементы",
"Move Element to the Beginning": "Move Element to the Beginning",
"Move Element to the End": "Переместить элемент в конец",
"Count": "Count",
"Search for Element": "Поиск элемента",
"Moving Element": "Переместить элемент",
"Consolidation Factor": "Коэффициент консолидации",
"Remove from source elements": "Remove from source elements",
"Add Cube": "Добавить куб",
"Delete Cube": "Удалить куб",
"Rename Cube": "Переименовать куб",
"Clear Cube": "Очистить куб",
"Export Cube": "Export Cube",
"Rule Edit": "Rule Edit",
"Cube Information": "Свойства",
"Add Dimension": "Добавить",
"Delete Dimension": "Удалить",
"Rename Dimension": "Переименовать",
"Edit Dimension": "Редактировать",
"Export Dimension": "Экспорт...",
"Dimension Information": "Свойства",
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
"Change Element Type": "Изменить тип элемента",
"_msg: Change Element Type": "Changing element type could lead to loss of data.<br>Are you sure you want to change type?",
"Search Element": "Поиск элемента",
"_msg: Search Element": "Enter name of Element for Search",
"Search": "Search",
"Element": "Элемент",
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
"Finish >>": "Конец >>",
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
"Element not found!": "Элемент не найден!",
"Search & Select": "Search & Select",

//Palo Wizard
"PALO Wizard": "PALO Wizard",
"_msg: Palo Wizard": "This wizard will allow you to add/delete databases and servers",
"_tit: Palo Wizard": "Мастер Palo",
"Select connection": "Выберите соединение",
"New Database": "Новая БД",
"Delete Database": "Удалить БД",
"New Server": "Новый сервер",
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
"_msg: Delete Constants": "Are you sure you want to delete selected constants?",
"Acquiring Server List": "Acquiring Server List",
"Opening dialog": "Открытие диалога",
"Move Up": "Переместить вверх",
"Move Down": "Переместить вниз",
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
