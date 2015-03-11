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
 * SVN: $Id: loc_fr_FR.js 4901 2011-04-28 10:07:16Z l10n-tool $
 *
 */

if (!Jedox.wss.tmp)
	Jedox.wss.tmp = {};

Jedox.wss.tmp.i18n_strings = {

// General
"OK": "OK",
"Cancel": "Annuler",
"File": "Fichier",
"New": "Nouveau",
"Open": "Ouvrir",
"Close": "Fermer",
"Save": "Enregistrer",
"Properties": "Propriétés",
"Edit": "Edition",
"Cut": "Couper",
"Copy": "Copier",
"Paste": "Coller",
"View": "Affichage",
"List": "Liste",
"Hide": "Masquer",
"Help": "Aide",
"Create new document": "Créer un nouveau document",
"Open document": "Ouvrir un document",
"Save document": "Enregistrer un document",
"Bold": "Gras",
"Italic": "Italique",
"Underline": "Souligner",
"Delete": "Supprimer",
"Rename": "Renommer",
"Select All": "Sélectionner tous",
"Type": "Type",
"Warning": "Avertissement",
"Password": "Mot de passe",
"Layout": "Mise en page",
"General": "Standard",
"Preview": "Aperçu",
"Refresh": "Actualiser",
"None": "Aucun",
"Bottom": "En bas",
"Right": "A droite",
"Up": "En haut",
"New Folder": "Nouveau dossier",
"Thumbnails": "Symboles",
"Details": "Détails",
"Description": "Description",
"Options": "Options",
"Modeller": "Outil de Modélisation",
"Home": "Page de démarrage",
"Size": "Taille",

"Quick View": "Aperçu rapide",
"Designer Preview": "Aperçu Designer",
"Active": "Actif",
"Path": "Chemin d'accès",
"Apply": "Appliquer",
"Rename Sheet": "Renommer la feuille",

//Paste Subset Dialog
"_tit: hb List Editor": "Editeur de listes DynaRange",
"Subset Editor": "Editeur de sous-ensemble",
"Subset General Settings": "Options générales du sous-ensemble",
"Dimension": "Dimension",
"Select First Alias": "Choisir le premier alias",
"Select Second Alias": "Choisir le deuxième alias",
"Alias": "Alias",
"Optional Settings": "Paramètres optionnels",
"Hierarchy enumeration": "Enumération de hiérarchie",
"Hierarchy": "Hiérarchie",
"Text": "Texte",
"Picklist": "Liste de choix",
"Attribute": "Attribut",
"Sort": "Tri",
"Level": "Niveau",
"Depth": "Profondeur",
"Flat": "Plat",
"Show parents below children": "Parents en-dessous des enfants",
"Show duplicates": "Montrer les doublons",
"Show children of hidden elements": "Montrer les enfants des éléments cachés",
"_msg: hb Lists": "Listes DynaRange",
"[_name: hb List]": "[Liste DynaRange]",
"Formula Subset": "Sous-ensemble de formule",
"[Formula Subset]": "[Sous-ensemble de formule]",
"Local Subsets": "Sous-ensembles privés",
"Global Subsets": "Sous-ensembles globaux",
"Stored Subsets": "Sous-ensembles enregistrés",
"Auto": "Auto",
"By Definition": "Par définition",
"By Element name": "Par nom d'élément",
"By Alias": "Par alias",
"By Value": "Par valeur",
"By Attribute": "Par attribut",
"All Elements": "Tous les éléments",
"Base Elements Only": "Éléments de base uniquement",
"Consolidated Elements Only": "Éléments consolidés uniquement",
"Reverse": "Inverser",
"Sort at Level": "Trier au niveau",
"Sorting behaviour": "Comportement du Tri",
"Reverse Order": "Inverser l'ordre",
"Type Limitation": "Limitation du type",
"New Subset": "Nouveau sous-ensemble",
"Enter name for Subset": "Indiquer le nom du sous-ensemble",
"Delete Subset": "Supprimer le sous-ensemble",
"_msg: Delete Subset": "Etes-vous sûr de vouloir supprimer définitivement le sous-ensemble ?",
"Rename Subset": "Renommer le sous-ensemble",
"Enter new name for Subset": "Indiquer le nouveau nom du sous-ensemble",
"_msg: update Subset": "Enregistrer le sous-ensemble.",
"_msg: new Subset": "Enregistrer le nouveau sous-ensemble.",
"_msg: delete Subset": "Supprimer le sous-ensemble.",
"_msg: rename Subset": "Enregistrer le nouveau nom du sous-ensemble.",
"[All Elements]": "[Tous les éléments]",
"Filter elements hierarchically": "Filtrer hiérarchiquement",
"Cyclic list": "Liste circulaire d\'éléments",
"Below": "Au-dessous",
"Above": "Au-dessus",
"Consolidated": "Éléments consolidés",
"Base Elements": "Éléments de base",
"Activate this filter": "Activer ce filtre",
"Exclusive": "Exclusif",
"Filter Element by type": "Filtrer par type",
"Filter elements by Level": "Filtrer par niveau",
"List length": "Longueur de la liste",
"Start level": "Premier niveau",
"Indent Enumeration": "",
"End level": "Dernier niveau",
"Settings": "Options",
"_subsetTextTabExamples": 'Exemples :<br>' +
							'- "Jan|Feb|Nov", pour correspondre à "Jan", "Feb", "Nov"<br>' +
							'- "J.*", pour correspondre à tous les éléments commençant par "J"<br>' +
							'- "[s,d]", pour correspondre à tous les éléments contenant un "s" ou un "d" dans le nom<br>' +
							'- "n$", pour correspondre à tous les éléments finissant par "n"',
"_subsetTextTabPerl": "<b>Expressions régulières</b>",
"Behaviour": "Comportement",
"Dimension Contents": "Elements de la dimension",
"Please select how to insert choosen elements": "Veuillez indiquer comment insérer les éléments choisis",
"_subsetAttrTabExample": '<br>Exemples :<br>' +
							'- ">0"<br>' +
							'- "<=1000"<br>' +
							'- "<>10"<br>' +
							'- "=10"',
"Variable": "Variable",
"Alias 1": "Alias 1",
"Alias 2": "Alias 2",
"Level Start": "Premier Niveau",
"Level End": "Dernier Niveau",
"Criteria": "Critére",
"Sort Attribute": "Tri attributs",
"Sort Level": "Niveau de tri",
"Quick": "Rapide",
"SUM OF THE ELEMENTS": "SOMME DES ELEMENTS",
"ALL ELEMENTS": "TOUS LES ELEMENTS",
"AVEREGE OF THE ELEMENTS": "MOYENNE DES ELEMENTS",
"MAXIMUM OF THE ELEMETNS": "MAXIMUM DES ELEMENTS",
"ANY ELEMENT": "TOUT ELEMENT",
"MINIMUM OF THE ELEMENTS": "MINIMUM DES ELEMENTS",
"STRING": "TEXTE",
"Please select and set attribute fields": "Veuillez choisir les champs d'attribut",
"Select Cube": "Sélectionnez le cube",
"Indent": "Indenté",
"FRONT": "DEVANT",
"BACK": "DERRIERE",
"MERGE": "FUSIONNER",
"SUBTRACT": "Présélection pour le sous-ensemble",
"Take topmost elements": "Afficher les N éléments supérieurs",
"Take all upper elements up to %": "Afficher les éléments supérieurs jusqu'à %",
"Take all lower elements up to %": "Afficher les éléments inférieurs jusqu'à %",
"List Length": "Longueur de la liste",
"RegExes": "Expr. régu.",
"RegEx": "Expr. régu.",
"Picklist Type": "Type de la liste de choix",
"Cube": "Cube",
"Par1": "Par1",
"Par2": "Par2",
"Topmost": "Le plus élevé",
"Upper": "Au-dessus",
"Lower": "En-dessous",
"Slice operators": "Opérateurs de tranche",
"AND": "ET",
"Named Variables": "Variables nommées",
"subset_Indent": "Indenté",
"Obtaining preview data": "Obtention de la prévisualistion des données",
"Unable to resolve value for": "Impossible de trouver la valeur de",
"_msg: paloSbstDFilterEnabled": "Si le filtre de données est activée, le processus pour obtenir la liste de prévisualisation peut prendre plus de temps.",

//PALO Modeller
"PALO Modeller": "Modeleur PALO",
"Error": "Erreur",
"Elements": "Eléments",
"Attributes": "Attributs",
"Subsets": "Sous-ensembles",
"Consolidated Elements": "Eléments consolidés",
"show Tree": "Affichage en mode liste à plat ou arbre",
"<< Database": "<< Base de données",
"Expand All": "Déplier tous",
"Collapse All": "Replier tous",
"Choose Server/Database": "Choisir Serveur/Base de données",
"Dimensions and Global Subsets": "Dimensions et sous-éléments globaux",
"Cubes": "Cubes",
"Database": "Base de données",
"system": "Système",
"attributes": "Attributs",
"normal": "normal",
"loaded": "chargé",
"not loaded": "non chargé",
"_err: Timer": "Interruption de la demande Serveur",
"_msg: Timer": "Attente terminée",
"Add": "Ajouter",
"Consolidate": "Consolider",
"Numeric": "Numérique",
"String": "Chaîne de caractères",
"Copy Elements": "Copier les éléments",
"Paste Elements": "Coller des éléments",
"Move Element to the Beginning": "Déplacer l'élément pour le mettre au début",
"Move Element to the End": "Déplacer l'élément pour le mettre à la fin",
"Count": "Compter",
"Search for Element": "Rechercher un élément",
"Moving Element": "Déplacer l'élément",
"Consolidation Factor": "Facteur de consolidation",
"Remove from source elements": "Supprimer des éléments sources",
"Add Cube": "Ajouter un cube",
"Delete Cube": "Supprimer le cube",
"Rename Cube": "Renommer cube",
"Clear Cube": "Réinitialiser le cube",
"Export Cube": "Exporter le cube",
"Rule Edit": "Editeur de règles",
"Cube Information": "Propriétés",
"Add Dimension": "Ajouter...",
"Delete Dimension": "Supprimer...",
"Rename Dimension": "Renommer",
"Edit Dimension": "Edition...",
"Export Dimension": "Export...",
"Dimension Information": "Propriétés",
"Total Number of Elements": "Nombre total d'éléments",
"Number of Numeric Elements": "Nombre d'éléments numériques",
"Number of String Elements": "Nombre d'éléments textes",
"Number of Consolidated Elements": "Nombre d'éléments consolidés",
"Delete Element": "Supprimer élément(s)",
"_msg: Delete Element": "Etes-vous sûr de vouloir supprimer définitivement l'élément suivant ?",
"Delete Attribute": "Supprimer l'attribut",
"_msg: Delete Attribute": "Etes-vous sûr de vouloir supprimer définitivement l'attribut suivant ?",
"_msg: Delete Dimension": "Etes-vous sûr de vouloir supprimer définitivement la dimension suivante ?",
"_msg: Delete Cube": "Etes-vous sûr de vouloir supprimer définitivement le cube suivant ?",
"Change Element Type": "Changer le type de l'élément",
"_msg: Change Element Type": "Changer le type de l'élément peut entraîner la perte de données .<br>Etes-vous bien sûr de vouloir changer le type de l'élément ?",
"Search Element": "Rechercher un élément",
"_msg: Search Element": "Veuillez indiquer le nom de l'élément pour la recherche",
"Search": "Recherche",
"Element": "Elément",
"was not find in dimension": "L\'élément n\'a pas été trouvé dans la dimension",
"New Element": "Nouvel élément",
"Enter name for new Element": "Veuillez indiquer le nom du nouvel élément",
"New Attribute": "Nouvel attribut",
"Enter name for new Attribute": "Veuillez indiquer le nom du nouvel attribut",
"Rename Element": "Renommer l'élément",
"Enter new name for Element": "Veuillez indiquer le nouveau nom de l'élément",
"Rename Attribute": "Renommer l'attribut",
"Enter new name for Attribute": "Veuillez indiquer le nouveau nom de l'attribut",
"New Dimension": "Nouvelle dimension",
"Enter name for Dimension": "Veuillez indiquer le nom de la nouvelle dimension",
"Enter new name for Dimension": "Veuillez indiquer le nouveau nom de la dimension",
"Enter new name for Cube": "Veuillez indiquer le nouveau nom du cube",
"Change Factor": "Changer le facteur",
"Enter new consolidation factor": "Veuillez indiquer le nouveau facteur de consolidation",
"Storing": "Créer",
"_msg: new Dim": "Création d'une nouvelle dimension dans la base de données.",
"_err: new Dim": "La création de la nouvelle dimension a échoué !",
"_msg: rename Dim": "Création d'un nouveau nom de dimension dans la base de données.",
"_err: rename Dim": "Le renommage de la dimension a échoué !",
"_msg: del Dim": "Supprimer la dimension.",
"_err: del Dim": "La suppression de la dimension a échoué !",
"_msg: ren Cube": "Création d'un nouveau cube dans la base de données.",
"_msg: del Cube": "Supprimer le cube.",
"_err: del Cube": "La suppression du cube a échoué !",
"_msg: new Elem": "Création d'un nouvel élément dans la base de données.",
"_msg: del Elem": "Supprimer un élément de la base de données.",
"_msg: cons Elem": "Création d'un élément consolidé.",
"_msg: rename Elem": "Création d'un nouveau nom d'élément dans la base de données.",
"_msg: change type Elem": "Création d'un nouveau type d'élément dans la base de données.",
"_msg: moving Element": "Création de l'élément à une nouvelle position.",
"Identifier": "Marqueur",
"Number of Elements": "Nombre d'éléments",
"Number of N elem.": "Nombre d'éléments N",
"Number of S elem.": "Nombre d'éléments S",
"Number of C elem.": "Nombre d'éléments C",
"Maximum Level": "Niveau Maximum",
"Maximum Indent": "Indentation Maximale",
"Maximum Depth": "Profondeur Maximale",
"Number of Dimensions": "Nombre de dimensions",
"Dimensions": "Dimensions",
"Number of Cells": "Nombre de cellules",
"Number of Filled Cells": "Nombre de cellules remplies",
"Filed Ratio": "Degré de remplissage",
"Status": "Statut",
"Add Subset": "Ajouter un sous-ensemble",
"is not allowed": "N'est pas autorisé",
"Hit RETURN to add Dimension": "Tapez la touche « Entrée » pour ajouter une dimension",
"Click on the \"New Cube\" button to add Cube": "Cliquez sur le bouton \" Nouveau Cube \" pour ajouter un Cube",
"Hit RETURN to add Elements": "Tapez la touche « Entrée » pour ajouter un élément",
"Add Element from list of Elements": "Ajouter un élément de la liste des éléments",

//PALO Cube Wizard
"PALO Cube Wizard": "Assistant de création de cube Palo",
"Finish >>": "Terminer >>",
"Available Dimensions": "Dimensions disponibles",
"Selected Dimensions": "Dimensions sélectionnées",
"Cube name": "Nom du cube",
"_tit: Cube Creation Wizard": "Assistant de création de cube",
"_msg: Cube Wizard": "Cet assistant vous permet de définir un nouveau cube.",
"Information": "Information",
"_msg: new Cube": "Créer un nouveau cube dans la base de données.",
"_err: create new Cube": "Il n'y a pas d'indications valides pour le cube. Nom ou dimensions manquantes.",
"_msg: Cube added": "Le cube a été enregistré dans la base de données avec succès.",
"Close Cube Wizard": "Quitter l'assistant de création de cube",
"_msg: close Cube Wizard": "Etes-vous bien sûr de vouloir terminer sans enregistrer ?",

//Choose Element
"[none]": "[aucun]",
"Element not found!": "L\'élément n\'a pas été trouvé !",
"Search & Select": "Rechercher et sélectionner",

//Palo Wizard
"PALO Wizard": "Assistant Palo",
"_msg: Palo Wizard": "Cet assistant vous permet d'à ajouter/supprimer des bases de données et des serveurs",
"_tit: Palo Wizard": "Assistant Palo",
"Select connection": "Choisir le serveur",
"New Database": "Créer une nouvelle base",
"Delete Database": "Supprimer une base existante",
"New Server": "Enregistrer un nouveau serveur",
"Delete Server": "Désenregistrer le serveur indiqué",
"Disconnect": "Déconnecter",
"Connect": "Connecter",
"_msg: Palo Wizard Delete Server": "Cette opération va supprimer le serveur de la liste !",
"Connection Name": "Nom de la connexion",
"Server": "Serveur",
"Port": "Port",
"Username": "Nom d'utilisateur",
"Confirm Password": "Mot de passe",
"Test Connection": "Test de connexion",
"_err: Wrong Pass": "Mot de passe invalide.",
"_msg: Test Conn Ok": "Test réussi.",
"_err: Test Conn Not Ok": "Echec du test.",
"_err: Db not added": "Erreur lors de la création de la base de données.",
"_msg: Db added": "Base créée avec succès.",
"_err: Db not deleted": "Suppression de la base de données impossible.",
"_msg: Db deleted": "Base de donnée supprimée avec succès.",
"_msg: Server added": "Serveur enregistré avec succès.",
"_err: Server not added": "Erreur lors de l'enregistrement du serveur.",
"_msg: Server edited": "Serveur modifié avec succès.",
"_err: Server not edited": "Erreur de modification du serveur.",
"_msg: Server deleted": "Enregistrement du serveur supprimé avec succès.",
"_err: Server not deleted": "Impossible de supprimer l'enregistrement du serveur.",
"_msg: Delete Database": "Etes-vous sûr de vouloir complètement supprimer la base de données du serveur ?",
"_msg: Delete Server": "Etes-vous sûr de vouloir supprimer le serveur de la liste ?",
"Edit Server": "Editer le serveur sélectionné",

//PALO Rule Editor
"Rule":"Règle",
"Updated":"Mis à jour",
"Rule Editor":"Editeur de règles",
"List of defined rules":"Liste des règles définies",
"Comment": "Commentaire",
"Import Rules": "Importer des Règles",
"impPaloRule_fieldLbl": "Le fichier à importer",
"impDlg_msgFieldBlank": "Veuillez sélectionner un fichier",

// Copied for app
"Choose Element": "Sélectionner un élément",
"Name": "Nom",
"New Database Name": "Nouveau nom de base de données",
"Select database to delete": "Sélectionner la base de données à supprimer",
"Store login data": "Enregistrer les données de connexion",
"Data": "Données",

//ConstListEditor class
"New Constant": "Nouvelle constante",
"Delete Constants": "Supprimer les constantes",
"_msg: Delete Constants": "Etes-vous sûr de vouloir supprimer définitivement les constantes sélectionnées ?",
"Indent Enumeration": "Niveau",
"Acquiring Server List": "Liste des serveurs est créé.",
"Opening dialog": "Ouverture de dialogue",
"Move Up": "Déplacer vers le haut",
"Move Down": "Déplacer vers le bas",
"No rule selected. Please select rule.": "Aucune règle est sélectionnée. S\'il vous plaît sélectionnez une règle.\n",
"No file selected. Please select file.": "Aucune fichier est sélectionné. S\'il vous plaît sélectionnez un fichier.",
"fopperLic": "Licence pour imprimante PDF",
"License could not be checked": "La licence ne peut pas être vérifiée.",
"License could not be found.": "La licence ne peut pas être trouvée.",
"License could not be read.": "La licence ne peut pas être lu.",
"License is not valid.": "La licence n\'est pas valide."

};

Jedox.err.i18n = {
     1: 'Erreur-ExceptionGénérique'
,  100: 'Erreur-ExceptionRuntime'
,  101: 'Erreur-ParsingFailedException'
,  102: 'Erreur-NotImplementedException'
,  103: 'Erreur-ExceptionInvalidSession'
, 1000: 'Erreur-ExceptionDroitsInsuffisants'
, 1100: 'Erreur-ExceptionEvènementInterrompu'
, 1200: 'Erreur-ExceptionIndexNonValidePressePapiers'
, 1300: 'Erreur-ExceptionNomNonValide'
, 1400: 'Erreur-ExécutionInterrompue'
, 1500: 'Erreur-ExceptionFormuleNonValide'
, 1600: 'Erreur-ExceptionDépendanceCyclique'
, 1700: 'Erreur-ExceptionRéseau'
, 1800: 'Erreur-ExceptionAucunClasseurSélectionné'
, 1801: 'Erreur-ExceptionAucuneFeuilleSélectionnée'
, 1802: 'Erreur-ExceptionAucuneApplicationSélectionnée'
, 1900: 'Erreur-ExceptionChargementApplication'
, 1901: 'Erreur-ExceptionChargement'
, 1902: 'Erreur-ExceptionEnregistrement'
, 2000: 'Erreur-ExceptionMiseEnFormeConditionnelle'
, 2100: 'Erreur-ExceptionFormuleNommée'
, 2101: 'Erreur-ExceptionNomDeFormuleNExistePas'
, 2200: 'Erreur-ExceptionCopieFeuille'
, 2300: 'Erreur-ExceptionChamp'
, 2400: 'Erreur-ExceptionCelluleFusionnée'
, 2500: 'Erreur-ExceptionAuthentification'
, 2600: 'Erreur-ExceptionDimensionCellule'
, 2700: 'Erreur-ExceptionSession'
, 2800: 'Erreur-ExceptionGroupeNonValide'
, 2900: 'Erreur-ExceptionUtilisateurNonValide'
, 3000: 'Erreur-ExceptionTableauTraduction'
, 3100: 'Erreur-ExceptionCopieFeuille'
, 3200: 'Erreur-ExceptionCopieClasseur'
, 3300: 'Erreur-ExceptionExtensionRegistre'
, 3400: 'Erreur-ExceptionExtensionAppelant'
, 3500: 'Erreur-ExceptionChampCyclique'
, 3600: 'Erreur-ExceptionElémentFeuille'
, 3700: 'Erreur-ExceptionFormat'
, 3800: 'Erreur-ExceptionStyleManager'
, 3900: 'Erreur-ExceptionPointLié'
, 4000: 'Erreur-ExceptionFiltreRegistre'
, 4100: 'Erreur-ExceptionPortePapier'
, 4200: 'Erreur-ExceptionSélectionTropGrande'
, 4300: 'Erreur-ExceptionExtensionÉchec'
, 4400: 'Erreur-ExceptionPaloConnexion'
, 4500: 'Erreur-FatalException'
, 4600: 'Erreur-ArrayFormulaOnMergedCellException'
, 4700: 'Erreur-ValueConversionException'
,   R1: 'Erreur-GenericException'
,   R2: 'Erreur dans {FILE} à ligne  {LINE}!'
, P0_0: 'L\'action de Palo a échoué.'
, P1_0: 'Le nom de base de données n\'est pas correct.'
, P1_1: 'Dimension existe déjà.'
, P1_2: 'Dimension n\'existe pas.'
, P1_3: 'La dimension est utilisée par quelques cubes.'
, P1_4: 'Élément existe déjà.'
, P1_5: 'Le sous-ensemble n\'est pas supprimé.'
, P1_6: 'Le sous-ensemble n\'est pas renommé.'
, P1_7: 'Impossible d\'obtenir la liste des bases de données pour connexion "{conn_name}".'
, P1_8: 'Sous-élément {ss_name} n\'a pas pu être créé.'
, P1_9:	'Vous n\'avez pas assez de droits pour cette action!'
, P1_10: 'Impossible de changer le statut de la connexion.'
, P1_11: 'Il n\'est pas possible d\'établir la connexion de Palo enregistrée.'
, P1_12: 'La connexion {conn_name} a un mauvais type de Palo-connexion.'
, P1_13: 'Impossible d\'établir la connexion avec le nom : {conn_name}.'
, P1_14: 'Impossible d\'obtenir d\'utilisateur pour la connexion avec le nom  {conn_name}.'
, P1_15: 'Impossible de créer une nouvelle base de données avec le nom {db_name}.'
, P1_16: 'Impossible d\'obtenir des données pour la vue consignée.'
, P1_17: 'Impossible de supprimer la base de données : {db_name}.'
, P1_18: 'Impossible de générer la liste de sous-ensemble!'
};
