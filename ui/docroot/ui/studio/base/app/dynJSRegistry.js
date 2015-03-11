/*
 * @brief ajax
 *
 * @file Group.js
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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: dynJSRegistry.js 5125 2011-07-18 13:10:22Z srdjanv $
 *
 */

Jedox.studio.app.dynJSRegistry = {
	// name: [filename, [folder, subfolder, subsubfolder], function_to_call ('' if nothing to call), autoload_on_startup, loaded, base_folder, base_namespace]
	// example - formatCells: ['Format.js', ['files', 'dlg'], 'formatCells', false, false, 'base', 'studio']
	selectionWizard: ['SelectionWizard.js', ['reports', 'dlg'], 'selectionWizard', false, false, 'base', 'studio']
	,manageHomePage: ['ManageHomepage.js', ['reports', 'dlg'], 'manageHomePage', false, false, 'base', 'studio']
	,groupHomepage: ['GroupHomepage.js', ['reports', 'dlg'], 'openGroupHomepage', false, false, 'base', 'studio']

	,openAddGroup: ['AddGroup.js', ['files', 'dlg'], 'openAddGroup', false, false, 'base', 'studio']
	,openAddHierarchy: ['AddHierarchy.js', ['files', 'dlg'], 'openAddHierarchy', false, false, 'base', 'studio']
	,openAddHyperlink: ['AddHyperlink.js', ['files', 'dlg'], 'openAddHyperlink', false, false, 'base', 'studio']
	,addTag: ['AddTag.js', ['files', 'dlg'], 'addTag', false, false, 'base', 'studio']
	,tagManager: ['TaggedMng.js', ['files', 'dlg'], 'tagManager', false, false, 'base', 'studio']
	,refList: ['ReferrersList.js', ['files', 'dlg'], 'ReferrersList', false, false, 'base', 'studio']
	,fileResources: ['Resources.js', ['files', 'dlg'], 'Resources', false, false, 'base', 'studio']
	,fileMarkers: ['Resources.js', ['files', 'dlg'], 'Markers', false, false, 'base', 'studio']
	,fileSecurity: ['Security.js', ['files', 'dlg'], 'Security', false, false, 'base', 'studio']
	,importFile: ['Import.js', ['files', 'dlg'], 'importFile', false, false, 'base', 'studio']

	,openLicence: ['Licence.js', ['dlg'], 'openLicence', false, false, 'base', 'studio']
	,openProperties: ['Properties.js', ['dlg'], 'openProperties', false, false, 'base', 'studio']
	,openPreferences: ['Preferences.js', ['dlg'], 'openPreferences', false, false, 'base', 'studio']

	,openConstListEditorWin:['ConstListEditorWin.js', ['dlg'], 'openConstListEditorWin', false, false, '../common/base', '']
};