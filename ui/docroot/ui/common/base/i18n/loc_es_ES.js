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
 * SVN: $Id: loc_es_ES.js 5019 2011-05-30 15:01:04Z l10n-tool $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "Confirmar",
"Cancel": "Cancelar",
"File": "Archivo",
"New": "Nuevo",
"Open": "Abrir",
"Close": "Cerrar",
"Save": "Guardar",
"Properties": "Propiedades     ",
"Edit": "Editar",
"Cut": "Cortar",
"Copy": "Copiar",
"Paste": "Pegar",
"View": "Vista",
"List": "Listar",
"Hide": "Ocultar",
"Help": "Ayuda",
"Create new document": "Crear Nuevo Documento",
"Open document": "Abrir Documento",
"Save document": "Guardar Documento",
"Bold": "Negrilla",
"Italic": "Itálica",
"Underline": "Subrayado",
"Delete": "Borrar",
"Rename": "Renombrar",
"Select All": "Seleccionar Todo",
"Type": "Tipo",
"Warning": "Advertencia ",
"Password": "Contraseña",
"Layout": "Disposición Paneles",
"General": "General",
"Preview": "Vista Previa",
"Refresh": "Refrescar",
"None": "Ninguno",
"Bottom": "Inferior",
"Right": "Derecha",
"Up": "Arriba",
"New Folder": "Nuevo folder",
"Thumbnails": "Iconos ",
"Details": "Detalles",
"Description": "Descripción",
"Options": "Opciones",
"Modeller": "Modelador",
"Home": "Inicio",
"Size": "Tamaño",

"Quick View": "Vista Previa Administrador",
"Designer Preview": "Vista Previa Diseñador",
"Active": "Activo",
"Path": "Ruta",
"Apply": "Aplicar",
"Rename Sheet": "Renombrar hoja",

//Paste Subset Dialog
"_tit: hb List Editor": "Editor de Listas DynaRange",
"Subset Editor": "Editor de Subconjuntos",
"Subset General Settings": "Parámetros Generales de Subconjunto",
"Dimension": "Dimensión",
"Select First Alias": "Seleccione Primer Alias",
"Select Second Alias": "Seleccione Segundo Alias",
"Alias": "Alias",
"Optional Settings": "Parámetros Opcionales",
"Hierarchy enumeration": "Enumeración de Jerarquía",
"Hierarchy": "Jerarquía\n",
"Text": "Texto",
"Picklist": "Selección",
"Attribute": "Atributo\n",
"Sort": "Orden",
"Level": "Nivel",
"Depth": "Profundidad",
"Flat": "Plana",
"Show parents below children": "Mostrar padres bajo los hijos\n",
"Show duplicates": "Mostrar duplicados",
"Show children of hidden elements": "Mostrar hijos de elementos ocultos\n\n",
"_msg: hb Lists": "Listas DynaRange\n",
"[_name: hb List]": "[Lista DynaRange]\n",
"Formula Subset": "Formula Subset",
"[Formula Subset]": "[Formula Subset]",
"Local Subsets": "Subconjuntos Locales",
"Global Subsets": "Subconjuntos Globales",
"Stored Subsets": "Subconjuntos Almacenados",
"Auto": "Auto",
"By Definition": "Por Definición",
"By Element name": "Por Nombre de Elemento",
"By Alias": "Por Alias",
"By Value": "Por Valor",
"By Attribute": "Por Atributo\n\n",
"All Elements": "Todos los Elementos",
"Base Elements Only": "Solo Elementos Base",
"Consolidated Elements Only": "Solo Elementos Consolidados\n",
"Reverse": "Inverso",
"Sort at Level": "Orden a Nivel\n",
"Sorting behaviour": "Comportamiento de Orden",
"Reverse Order": "Orden Inverso\n\n",
"Type Limitation": "Limitación de Tipo",
"New Subset": "Nuevo Subconjunto",
"Enter name for Subset": "Ingrese Nombre del Subconjunto",
"Delete Subset": "Borrar Subconjunto",
"_msg: Delete Subset": "¿Está seguro de desear eliminar el Subconjunto?",
"Rename Subset": "Renombrar Subconjunto",
"Enter new name for Subset": "Ingrese el nuevo nombre para el Subconjunto",
"_msg: update Subset": "Guardando Subconjunto.",
"_msg: new Subset": "Guardando nuevo Subconjunto.",
"_msg: delete Subset": "Borrando Subconjunto.",
"_msg: rename Subset": "Guardando nuevo nombre para el Subconjunto.",
"[All Elements]": "[Todos los Elementos]",
"Filter elements hierarchically": "Filtrar elementos jerárquicamente ",
"Cyclic list": "Lista Cíclica",
"Below": "Bajo  ",
"Above": "Sobre  ",
"Consolidated": "Consolidado    ",
"Base Elements": "Elementos Base ",
"Activate this filter": "Activar este filtro     ",
"Exclusive": "Exclusivo  ",
"Filter Element by type": "Filtrar Elementos por tipo",
"Filter elements by Level": "Filtrar Elementos por Nivel",
"List length": "Longitud de la Lista",
"Start level": "Nivel de Inicio",
"Indent Enumeration": "Indent Enumeration",
"End level": "Nivel Final",
"Settings": "Parámetros",
"_subsetTextTabExamples": 'Examples:<br>' +
							'- "Jan|Feb|Nov", to match "Jan", "Feb", "Nov"<br>' +
							'- "J.*", to match all elements starting with a "J"<br>' +
							'- "[s,d]", to match all elements with "s" or "d" in name<br>' +
							'- "n$", to match all elements witch ends with "n"',
"_subsetTextTabPerl": "<b>PERL-Expresiones regulares</b>   ",
"Behaviour": "Comportamiento",
"Dimension Contents": "Contenido de Dimensión",
"Please select how to insert choosen elements": "Por favor elija cómo insertar elementos seleccionados",
"_subsetAttrTabExample": "<br>Ejemplos:<br>- \">0\"<br>- \"<=1000\"<br>- \"<>10\"<br>- \"=10\"" +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Variable",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Comenzar en Nivel",
"Level End": "Finalizar en Nivel",
"Criteria": "Criterio ",
"Sort Attribute": "Ordenar Atributo",
"Sort Level": "Sort Level",
"Quick": "Rápido",
"SUM OF THE ELEMENTS": "SUMA DE LOS ELEMENTOS",
"ALL ELEMENTS": "TODOS LOS ELEMENTOS",
"AVEREGE OF THE ELEMENTS": "PROMEDIO DE LOS ELEMENTOS ",
"MAXIMUM OF THE ELEMETNS": "MÁXIMO DE LOS ELEMENTOS   ",
"ANY ELEMENT": "CUALQUIER ELEMENTO",
"MINIMUM OF THE ELEMENTS": "MINIMO DE LOS ELEMENTOS   ",
"STRING": "STRING",
"Please select and set attribute fields": "Por favor seleccione y configure campos de atributo",
"Select Cube": "Seleccione Cubo",
"Indent": "Indent",
"FRONT": "FRONT",
"BACK": "BACK",
"MERGE": "MERGE",
"SUBTRACT": "SUBTRACT",
"Take topmost elements": "Selección elementos superiores",
"Take all upper elements up to %": "Selección elementos superiores hasta %",
"Take all lower elements up to %": "Selección elementos inferiores hasta %",
"List Length": "Longitud de Lista",
"RegExes": "RegExes",
"RegEx": "RegEx",
"Picklist Type": "Picklist Type",
"Cube": "Cubo ",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Topmost",
"Upper": "Upper",
"Lower": "Lower",
"Slice operators": "Slice operators",
"AND": "AND",
"Named Variables": "Named Variables",
"subset_Indent": "Indent",
"Obtaining preview data": "Obteniendo vista previa de datos",
"Unable to resolve value for": "No es posible resolver valor para",
"_msg: paloSbstDFilterEnabled": "Cuando el Filtro de Datos está activo, el proceso para obtener la vista previa de lista puede tomar más tiempo",

//PALO Modeller
"PALO Modeller": "PALO Modelador ",
"Error": "Error",
"Elements": "Elementos",
"Attributes": "Atributos   ",
"Subsets": "Subconjuntos",
"Consolidated Elements": "Elementos Consolidados  ",
"show Tree": "Mostrar árbol",
"<< Database": "<< Base de Datos",
"Expand All": "Expandir Todo",
"Collapse All": "Contraer Todo ",
"Choose Server/Database": "Seleccione Servidor/Base de Datos",
"Dimensions and Global Subsets": "Dimensiones y Subconjuntos Globales",
"Cubes": "Cubos",
"Database": "Base de Datos",
"system": "sistema",
"attributes": "atributos",
"normal": "normal",
"loaded": "cargado",
"not loaded": "no cargado  ",
"_err: Timer": "Tiempo finalizado para solicitud al Servidor.",
"_msg: Timer": "Tiempo de espera finalizado.",
"Add": "Add",
"Consolidate": "Consolidar   ",
"Numeric": "Numérico",
"String": "String",
"Copy Elements": "Copiar Elementos",
"Paste Elements": "Pegar Elementos ",
"Move Element to the Beginning": "Mover Elemento al Comienzo       ",
"Move Element to the End": "Mover Elemento al Final   ",
"Count": "Count",
"Search for Element": "Buscar Elemento     ",
"Moving Element": "Moving Element",
"Consolidation Factor": "Factor de Consolidación",
"Remove from source elements": "Remover de los elementos fuente",
"Add Cube": "Agregar Cubo",
"Delete Cube": "Borrar Cubo  ",
"Rename Cube": "Renombrar Cubo",
"Clear Cube": "Vaciar Cubo ",
"Export Cube": "Exportar Cubo",
"Rule Edit": "Editar Regla",
"Cube Information": "Propiedades",
"Add Dimension": "Agregar",
"Delete Dimension": "Delete Dimension",
"Rename Dimension": "Rename Dimension",
"Edit Dimension": "Editar",
"Export Dimension": "Exportar...",
"Dimension Information": "Propiedades",
"Total Number of Elements": "Cantidad Total de Elementos",
"Number of Numeric Elements": "Cantidad de Elementos Numéricos",
"Number of String Elements": "Cantidad de Elementos de tipo String",
"Number of Consolidated Elements": "Cantidad de Elementos Consolidados",
"Delete Element": "Borrar Elemento",
"_msg: Delete Element": "¿Está seguro de que desea borrar el Elemento?",
"Delete Attribute": "Borrar Atributo",
"_msg: Delete Attribute": "¿Está seguro de que desea borrar el Atributo?",
"_msg: Delete Dimension": "¿Está seguro de querer borrar la Dimensión?",
"_msg: Delete Cube": "¿Está seguro de querer borrar el Cubo?",
"Change Element Type": "Cambiar Tipo de Elemento",
"_msg: Change Element Type": "Al cambiar el tipo del elemento podrían perderse datos.<br>¿Está seguro de querer cambiar el tipo?",
"Search Element": "Buscar Elemento",
"_msg: Search Element": "Ingrese el nombre del Elemento a Buscar",
"Search": "Buscar",
"Element": "Elemento",
"was not find in dimension": "no fue encontrado en la dimensión",
"New Element": "Nuevo Elemento",
"Enter name for new Element": "Ingrese el nombre del nuevo Elemento",
"New Attribute": "Nuevo Atributo",
"Enter name for new Attribute": "Ingrese nuevo nombre para el Atributo",
"Rename Element": "Renombrar Elemento",
"Enter new name for Element": "Ingrese el nuevo nombre para el Elemento",
"Rename Attribute": "Renombrar Atributo",
"Enter new name for Attribute": "Ingrese nuevo nombre del Atributo",
"New Dimension": "Nueva Dimensión",
"Enter name for Dimension": "Ingrese Nombre de la Dimensión",
"Enter new name for Dimension": "Ingrese nuevo nombre de la Dimensión",
"Enter new name for Cube": "Ingrese nuevo nombre del Cubo",
"Change Factor": "Cambiar Factor",
"Enter new consolidation factor": "Ingrese nuevo factor de consolidación",
"Storing": "Almacenando",
"_msg: new Dim": "Almacenando nueva Dimensión en la Base de Datos.",
"_err: new Dim": "¡Agregar nueva Dimensión falló!",
"_msg: rename Dim": "Guardando nuevo Nombre de Dimensión en la Base de Datos.",
"_err: rename Dim": "¡Cambio de Nombre de Dimensión falló!",
"_msg: del Dim": "Borrando Dimensión.",
"_err: del Dim": "¡Borrado de la Dimensión falló!",
"_msg: ren Cube": "Guardando nuevo Nombre de Cubo en Base de Datos.",
"_msg: del Cube": "Borrando Cubo.",
"_err: del Cube": "¡Borrado de Cubo Falló!",
"_msg: new Elem": "Almacenando nuevo Elemento en la Base de Datos.",
"_msg: del Elem": "Borrando Elemento desde Base de Datos.",
"_msg: cons Elem": "Almacenando Elemento consolidado.",
"_msg: rename Elem": "Almacenando nuevo Nombre de Elemento en Base de Datos.",
"_msg: change type Elem": "Almacenando nuevo Tipo de Elemento en Base de Datos.",
"_msg: moving Element": "Almacenando Elemento en nueva posición.",
"Identifier": "Identificador",
"Number of Elements": "Cantidad de Elementos",
"Number of N elem.": "Cantidad de Elementos N",
"Number of S elem.": "Cantidad de Elementos S",
"Number of C elem.": "Cantidad de Elementos C",
"Maximum Level": "Maximum Level",
"Maximum Indent": "Maximum Indent",
"Maximum Depth": "Maximum Depth",
"Number of Dimensions": "Cantidad de Dimensiones",
"Dimensions": "Dimensiones",
"Number of Cells": "Cantidad de Celdas",
"Number of Filled Cells": "Cantidad de Celdas con datos",
"Filed Ratio": "Ratio de Llenado",
"Status": "Estatus",
"Add Subset": "Add Subset",
"is not allowed": "no está permitido",
"Hit RETURN to add Dimension": "Presione RETURN para agregar Dimensión",
"Click on the \"New Cube\" button to add Cube": "Haga click en \"Nuevo Cubo\" para agregar Cubo",
"Hit RETURN to add Elements": "Presione RETURN para agregar Elementos",
"Add Element from list of Elements": "Agregar Elemento desde la lista de Elementos",

//PALO Cube Wizard
"PALO Cube Wizard": "Asistente de Cubos de PALO",
"Finish >>": "Finalizar >>",
"Available Dimensions": "Dimensiones Disponibles",
"Selected Dimensions": "Dimensiones Seleccionadas",
"Cube name": "Nombre de Cubo",
"_tit: Cube Creation Wizard": "Asistente<br>Creación<br>Cubo",
"_msg: Cube Wizard": "Este Asistente le permitirá configurar un nuevo Cubo.",
"Information": "Información",
"_msg: new Cube": "Almacenando nuevo Cubo en la Base de Datos",
"_err: create new Cube": "Datos incorrectos para el Cubo. Falta el Nombre o Dimensiones.",
"_msg: Cube added": "Cubo almacenado exitosamente en la Base de Datos.",
"Close Cube Wizard": "Cerrar el Asistente de Cubos",
"_msg: close Cube Wizard": "¿Está seguro de que desea salir sin guardar?",

//Choose Element
"[none]": "[ninguno]",
"Element not found!": "¡Elemento no encontrado!",
"Search & Select": "Buscar & Seleccionar",

//Palo Wizard
"PALO Wizard": "Asistente de PALO",
"_msg: Palo Wizard": "Este asistente le permitirá agregar/eliminar bases de datos y servidores",
"_tit: Palo Wizard": "Asistente de Palo",
"Select connection": "Seleccione conexión",
"New Database": "Nueva Base de Datos",
"Delete Database": "Borrar Base de Datos",
"New Server": "Nuevo Servidor",
"Delete Server": "Eliminar Servidor",
"Disconnect": "Desconectar",
"Connect": "Conectar",
"_msg: Palo Wizard Delete Server": "¡Esta operación eliminará el servidor desde la lista!",
"Connection Name": "Nombre de Conexión",
"Server": "Servidor",
"Port": "Puerto",
"Username": "Usuario",
"Confirm Password": "Confirme Clave",
"Test Connection": "Probar Conexión",
"_err: Wrong Pass": "Password confirmada incorrecta.",
"_msg: Test Conn Ok": "Prueba exitosa.",
"_err: Test Conn Not Ok": "La prueba no fue exitosa.",
"_err: Db not added": "Error en la creación de la Base de Datos.",
"_msg: Db added": "Nueva Base de Datos agregada exitosamente.",
"_err: Db not deleted": "No fue posible eliminar la Base de Datos.",
"_msg: Db deleted": "Base de Datos eliminada exitosamente.",
"_msg: Server added": "Nuevo Servidor agregado exitosamente.",
"_err: Server not added": "Error en la creación del Servidor.",
"_msg: Server edited": "Servidor editado exitosamente.",
"_err: Server not edited": "Error en la edición del Servidor.",
"_msg: Server deleted": "Servidor eliminado exitosamente.",
"_err: Server not deleted": "No fue posible eliminar el Servidor.",
"_msg: Delete Database": "Está usted seguro de que desea eliminar completamente la base de datos desde el servidor.",
"_msg: Delete Server": "Está seguro de que necesita borrar el servidor de la lista.",
"Edit Server": "Editar Servidor",

//PALO Rule Editor
"Rule":"Regla",
"Updated":"Actualizado",
"Rule Editor":"Editor de Reglas",
"List of defined rules":"Lista de reglas definidas",
"Comment": "Comentario",
"Import Rules": "Importar Reglas",
"impPaloRule_fieldLbl": "El archivo a importar",
"impDlg_msgFieldBlank": "Por favor seleccione un archivo",

// Copied for app
"Choose Element": "Elejir Elemento",
"Name": "Nombre",
"New Database Name": "Nuevo Nombre de Base de Datos",
"Select database to delete": "Seleccione base de datos a eliminar",
"Store login data": "Almacenar datos de login",
"Data": "Datos",

//ConstListEditor class
"New Constant": "Nueva Constante",
"Delete Constants": "Borrar Constantes",
"_msg: Delete Constants": "¿Está seguro de que desea borrar las constantes seleccionadas?"

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
,   R2: 'Error en {FILE} en la linea {LINE}!'
, P0_0: 'Acción Palo falló.'
, P1_0: 'El nombre de la base de datos es incorrecto.'
, P1_1: 'Dimensión ya existe.'
, P1_2: 'Dimensión no existe.'
, P1_3: 'Dimensión utilizada por algunos Cubos.'
, P1_4: 'Elemento ya existe.'
, P1_5: 'Subconjunto no eliminado.'
, P1_6: 'Subconjunto no renombrado.'
, P1_7: 'No es posible obtener lista de bases de datos para conexión \"{conn_name}\".'
, P1_8: 'Subset {ss_name} can\'t be created.'
, P1_9:	'¡Usted no tiene privilegios suficientes para esta acción!'
, P1_10: 'No es posible cambiar estatus para conexión.'
, P1_11: 'No es posible obtener configuración de conexión palo.'
, P1_12: 'Bad PALO connection type for connection name: {conn_name}.'
, P1_13: 'Unable to make connection for connection name: {conn_name}.'
, P1_14: 'Unable to get user for connection name: {conn_name}.'
, P1_15: 'No es posible crear nueva base de datos: {db_name}.'
, P1_16: 'No es posible obtener datos configuración Paste View.'
, P1_17: 'No es posible borrar base de datos: {db_name}.'
, P1_18: 'Unable to generate Subset List!'
};
