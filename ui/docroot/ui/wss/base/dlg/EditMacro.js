/*
 * @brief wss file
 *
 * Copyright (C) 2006-2009 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope thats it will be useful, but WITHOUT
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com
 *
 * \version
 * SVN: $Id: EditMacro.js 4593 2011-02-10 10:03:34Z srdjanv $
 *
 */


Jedox.wss.dlg.openEditMacro = function(obj, callBackFnc, from, callBackFn){
	Jedox.dlg.dlgRegistry.add(new Jedox.wss.dlg.EditMacro(obj, callBackFnc, from, callBackFn));
};

Jedox.wss.dlg.EditMacro = (function() {

	return function (obj, callBackFnc, from, callBackFn) {

		Jedox.wss.dlg.EditMacro.parent.constructor.call(this);
		this.id = 'editMacro';
		var that = this;

		this.components.Cancel = {
				handler: function(){that.win.close();}
		}

		var html_tb = {
				// true to display, false to hide
				save: false,
				newm: false,
				rename: false,
				deletem: false,

				undo: true,
				redo: true,
				cut: true,
				copy: true,
				paste: true,
				find: true,
				apply: true,

				macroList: false,

				width: 520,
				winTitle: 'Editor'.localize(),
				initModules:false,

				editorParser: ["../js/parsexml.js", "../js/parsecss.js", "../js/tokenizejavascript.js", "../js/parsejavascript.js", '../js/parsehtmlmixed.js'],
				editorStyle: ['/ui/lib/cm/css/xmlcolors.css', '/ui/lib/cm/css/jscolors.css', '/ui/lib/cm/css/csscolors.css']
		};

		var default_tb = {
				save: true,
				newm: true,
				rename: true,
				deletem: true,

				undo: true,
				redo: true,
				cut: true,
				copy: true,
				paste: true,
				find: true,
				apply: false,

				macroList: true,

				width: 750,
				winTitle: 'Macro Editor'.localize(),
				initModules:true,

				editorParser: [ '../contrib/php/js/tokenizephp.js', '../contrib/php/js/parsephp.js' ],
				editorStyle: '/ui/lib/cm/contrib/php/css/phpcolors.css'
		};

		var tbConfig = (from=='html')? html_tb:default_tb;


		//initialization and chaining
		if(tbConfig.initModules)
			Jedox.wss.macro.list([ this, initModulesTree_post, obj, callBackFnc], Jedox.wss.macro.listFmt.TREE);
		else
			openDialog_post('', null, obj, callBackFnc);


		function initModulesTree_post(treeData, obj, callBackFnc){

			if (treeData.length == 0) {
				Jedox.wss.macro.add([this, loadModulesTree_post, obj, callBackFnc], 'Module1');
			}
			else {
				if (obj){
					if (obj.operation == 'new'){
						Jedox.wss.macro.load([this, addMacro_inner_post, treeData, obj, callBackFnc], treeData[0].uid);
					}
					else {
						var module = obj.macro.split('.')[0];

						for (var i=0; i<treeData.length; i++)
							if (module == treeData[i].text){
								Jedox.wss.macro.load([this, openDialog_post, treeData, obj, callBackFnc], treeData[i].uid);
								break;
							}
					}
				}
				else {
					Jedox.wss.macro.load([this, openDialog_post, treeData, obj, callBackFnc], treeData[0].uid);
				}
			}


			function addMacro_inner_post(src, treeData, obj, callBackFnc){
				var macro ='function '.concat(obj.macro, ' ()\n{\n\n}\n');
				var moduleSrc = src.length === 1 ? macro:src.concat('\n\n', macro);
				Jedox.wss.macro.save([this, loadModulesTree_post, {operation:'edit', macro:treeData[0].id.concat('.', obj.macro)}, callBackFnc], treeData[0].uid, moduleSrc); //need module id
			}
		}

		function loadModulesTree_post(moduleID, obj, callBackFnc){
			Jedox.wss.macro.list([ this, initModulesTree_post, obj, callBackFnc], Jedox.wss.macro.listFmt.TREE);
		}


		function openDialog_post(src, treeData, obj, callBackFnc){

			var thats = this;

			var _fromDlgF = false;

			if (Jedox.wss.app.environment.inputMode === Jedox.wss.grid.GridMode.DIALOG)
				_fromDlgF=true;
			else {
				Jedox.wss.app.lastInputModeDlg = Jedox.wss.app.environment.inputMode;
				Jedox.wss.general.setInputMode(Jedox.wss.grid.GridMode.DIALOG);
			}

			var treeData = treeData;
			var obj = obj;
			var _module;
			var _clipboard;

			var mainToolbar = new Ext.Toolbar({
				items: [{
							tooltip: {
							title: 'New Module'.localize(),
							text: 'Add New Module'.localize()
							},
							iconCls: 'new-macro-mdl-icon',
							handler: onAddModule,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 1,
							hidden: !tbConfig.newm,
							scope: this
						},
						{
							tooltip: {
								title: 'Delete Module'.localize(),
								text: 'Delete Module'.localize().concat('...')
							},
							iconCls: 'delete-macro-mdl-icon',
							handler:deleteModule,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 2,
							hidden: !tbConfig.deletem,
							scope: this
						},
						{
							tooltip: {
								title: 'Rename Module'.localize(),
								text: 'Rename Module'.localize().concat('...')
							},
							iconCls: 'rename-macro-mdl-icon',
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 3,
							hidden: !tbConfig.rename,
							handler: function(){
								onRenameModule();
							},
							scope: this
						},
						{
							tooltip: {
								title: 'Save'.localize(),
								text: 'Save'.localize().concat('...')
							},
							iconCls: 'save-macro-mdl-icon',
							handler:onApply,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							hidden: !tbConfig.save,
							tabIndex: 4,
							scope: this
						},
						(tbConfig.save)? '-':'',
						{
							tooltip: {
								title: 'Undo'.localize(),
								text: 'Undo'.localize().concat('...')
							},
							iconCls: 'undo-macro-icon',
							handler:function(){editor.undo();},
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							hidden: !tbConfig.undo,
							tabIndex:5,
							scope: this
						},
						{
							tooltip: {
								title: 'Redo'.localize(),
								text: 'Redo'.localize().concat('...')
							},
							iconCls: 'redo-macro-icon',
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 6,
							hidden: !tbConfig.redo,
							handler:function(){editor.redo();},
							scope: this
						},
						'-',
						{
							tooltip: {
								title: 'Cut'.localize(),
								text: 'Cut'.localize().concat('...')
							},
							iconCls: 'cut-macro-icon',
							handler:onCut,
							hidden: !tbConfig.cut,
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 7,
							scope: this
						},
						{
							tooltip: {
								title: 'Copy'.localize(),
								text: 'Copy'.localize().concat('...')
							},
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 8,
							hidden: !tbConfig.copy,
							iconCls: 'copy-macro-icon',
							handler:onCopy,
							scope: this
						},{
							tooltip: {
								title: 'Paste'.localize(),
								text: 'Paste'.localize().concat('...')
							},
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 9,
							hidden: !tbConfig.paste,
							iconCls: 'paste-macro-icon',
							handler:onPaste,
							scope: this
						},'-',{
							tooltip: {
								title: 'Find'.localize(),
								text: 'Find'.localize().concat('...')
							},
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 10,
							hidden: !tbConfig.find,
							iconCls: 'find-in-module-icon',
							handler:openFindDialog,
							scope: this
						},
						(tbConfig.apply)? '-' : '',
						{
							tooltip: {
								title: 'Apply'.localize(),
								text: 'Apply code'.localize().concat('...')
							},
							ctCls: Jedox.kbd.Base.tags.NO_ENTER,
							tabIndex: 11,
							hidden: !tbConfig.apply,
							text: 'Apply'.localize(),
							handler:function(){that.win.close();},
							scope: this
				}
						]
			});


			var toolbarPanel = {
				//title:'panel za toolbar',
				border: false,
				baseCls: 'x-plain',
				x: 5,
				y: 5,
				width: 400,
				height: 30,
				items: [mainToolbar]
			}


			var root = new Ext.tree.TreeNode({
				text: 'Modules Repository'.localize(),
				draggable: false, // disable root node dragging
				editable:false,
				id: 'root',
				expanded:true
			});


			if(treeData) //html mode
				loadMacroTreeData(treeData);

			var macrosTP = new Ext.tree.TreePanel({
				id: 'macros-tree',
				animate:false,
				lines: true,
				hidden: !tbConfig.macroList,
				containerScroll: true,
				ddScroll: true,
				autoScroll: true,
				collapseFirst: false,
				root:root,
				rootVisible:false,
				collapseFirst: true,
				listeners:{
					load:function(node){
	//					console.log('load');
	//					preselect();
					},
					contextmenu: function(node, e){
						if (!node.leaf)
							onModuleCtxMnu(node, e);
					}
				}
			});

			macrosTP.on('click', function(n){
	//			console.log(n);
				n.expand();
					var sn = macrosTP.selModel.getSelectedNode() || {}; // selNode is null on initial selection
					if (n.id != sn.id && n.id != 'root') {
						if (n.attributes.leaf)
							selectMacroInText(n);
						else {
							loadModule(n.attributes.uid);
							_module = n.attributes;
						}
					}
			});



			var moduleEditor = new Ext.tree.TreeEditor(macrosTP, null, {
				id: 'module-tree-node-editor',
				editDelay: 0,
				cancelOnEsc: true,
				allowBlank: false,
				ignoreNoChange: true,
				completeOnEnter: true,
				beforeNodeClick: Ext.emptyFn,
		        onNodeDblClick: Ext.emptyFn,
		        onNodeClick: Ext.emptyFn
			});

			moduleEditor.on({
				complete : function(moduleEditor, newName, oldName){
					if (newName != oldName) {
						if (validateName(moduleEditor.editNode, oldName, newName)) {
							var id = moduleEditor.editNode.attributes.id;
							//RENAME OPERATION
							Jedox.wss.macro.rename([this, afterRename_inner_post], moduleEditor.editNode.attributes.uid, newName); //need module id
						}
						else
							moduleEditor.cancelEdit();
					}

					function afterRename_inner_post(result){
						if (!result)
							showMsgERROR('Error Renaming Module', 'rename_module_error_msg');
					}
				}

			});


			var descriptionTxa = new Ext.form.TextArea({
				id:'macro-txa',
				hideLabel: true,
				autoWidth:true,
				height:420,
				style:Ext.isWebKit? 'height:417px !important;':'',
				value:src
			});


			var	editor;



			var mainPanel = that.containers.mainPanel = new Ext.Panel({
				layout: 'absolute',
				baseCls: 'x-plain',
				border: false,
				items:[
				toolbarPanel,
				{
					layout: 'fit',
					border: false,
					hidden: !tbConfig.macroList,
					baseCls: 'x-plain',
					x: 5,
					y: 30,
					width: 230,
					height: 418,
					items: [macrosTP]
				},
				{
					layout: 'fit',
					x: (tbConfig.macroList)? 240: 5,
					y: 30,
					items: [descriptionTxa]
				}]
			});



			that.win = new Ext.Window({
				id:'edit-macro-dlg',
				title: tbConfig.winTitle,
				closable: true,
				maximizable:true,
				closeAction: 'close',
		        autoDestroy: true,
		        cls: 'default-format-window',
		        plain: true,
		        constrain: true,
		        modal: true,
		        animCollapse: false,
				layout: 'fit',
				onEsc: Ext.emptyFn,
				width: tbConfig.width,
				height: 490,
				minWidth:500,
				minHeight:400,
				//plain: true,
				items: mainPanel,
				listeners: {
					close: function(){
						if (!_fromDlgF) {
							Jedox.wss.general.setInputMode(Jedox.wss.app.lastInputModeDlg);
							Jedox.wss.app.lastInputMode = Jedox.wss.grid.GridMode.READY;
						}

						if (from == 'html'){
							callBackFn(editor.getCode());
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editMacro);
						} else {
							setTimeout(function(){Jedox.wss.macro.exprt([this,Ext.emptyFn]);}, 0);
							that.close();
							Jedox.gen.unload(Jedox.wss.app.dynJSRegistry.editMacro);

							showInsertDialog();
						}
					},
					show:function(){
						setTimeout(function(){
							//that.initFocus(true, 100);
						});
					},
					activate: function(win) {that.activate();},
					resize : function(window, width, height){
						if (mainPanel.rendered){
							mainPanel.items.items[1].setHeight(height-73);
							var parentEl = descriptionTxa.getEl().parent();
							parentEl.dom.children[1].style.height = (height - 75) + 'px';
							mainPanel.doLayout();
						}
						else {
							this.setSize(750, 490);
						}
					}
				}
	//			buttons: [okBtn, cancelBtn, applyBtn]
			});


	//		initDlg(treeData);
			that.setContext();
			that.win.show(that);
	//		initDlg(treeData);


			setTimeout(function(){
				editor = CodeMirror.fromTextArea('macro-txa', {
					stylesheet: tbConfig.editorStyle,
					path: '/ui/lib/cm/js/',
					parserfile: tbConfig.editorParser,
					textWrapping: false,
					lineNumbers: true,
					content: document.getElementById('macro-txa').value,
					initCallback: function () { initDlg(treeData); }
				});
			});



	//		document.getElementById('x-form-el-macro-txa').style.backgroundColor = '#f8f8f8';
	//		setTimeout(function(){
	//			initDlg(treeData);
	//		}, 1000);
	//		initDlg_afterLayout();




		/************************************
		  *****       Funcitons        *****
		************************************/

			function initDlg(treeData){

				if(!treeData) //html mode
				{
					setTimeout(function(){editor.setCode(obj.macro || "\n"); editor.focus();}, 200);
					return;
				}

				if (obj) {
					if (obj.operation == 'new') {
						setTimeout(function(){preselect(obj.macro);editor.focus();}, 200);
					}
					else {
						setTimeout(function(){preselect(obj.macro);editor.focus();}, 200);
					}
				}
				else
					setTimeout(function(){preselect();editor.focus();}, 200);
			}


			function loadMacroTreeData(treeData){
	//			console.log('loadMacroTreeData');
				root.appendChild(treeData);
			}

			function preselect(macro){
					if (macro){
						var path = '/root/'.concat(macro.split('.')[0], '/', macro);
		//				console.log(path);
						macrosTP.expandPath(path);
						setTimeout(function(){
							macrosTP.fireEvent('click', macrosTP.getNodeById(macro));
						});
					}
					else
						macrosTP.fireEvent('click', macrosTP.getRootNode().hasChildNodes()? macrosTP.getRootNode().firstChild:null);

			}

			function loadModule(module){
				Jedox.wss.macro.load([this, loadTxtArea_inner_post], module);

				function loadTxtArea_inner_post(src){
					editor.setCode(src);
				}
			}



		function onModuleCtxMnu(node, e){
			var thats = this;
	//		console.log(node);

			var moduleCtxMnu = new Ext.menu.Menu({
				id: 'edit-macro-module-ctx-mnu',
				enableScrolling: false,
				items: [{
					text: 'Rename Module'.localize(),
					handler: function(){onRenameModule(node);},
					scope: thats
				},
					'-',
				{
					text: 'Delete Module'.localize(),
					handler: function(){deleteModule(node);},
					scope: thats
				}]
			});
			moduleCtxMnu.on('hide', onContextHide, moduleCtxMnu);

			e.stopEvent();
			moduleCtxMnu.showAt(e.getXY());
		}

		function onContextHide(ctxMnu){
	        if(ctxMnu){
	            ctxMnu.destroy();
	            ctxMnu = null;
	        }
	    }

		function onRenameModule(node){
			if (!node){
				node = macrosTP.getSelectionModel().getSelectedNode();
			}
			if (!node.leaf)
				moduleEditor.triggerEdit(node);
		}

		function onAddModule() {
			var _thats = this;
			var moduleName = getNewModuleName('Module'.localize());
			Jedox.wss.macro.add([_thats, refreshModule_inner_post, moduleName], moduleName);


			function refreshModule_inner_post(result, moduleName){

				var nodes =[];
				macrosTP.root.eachChild(function(node){nodes.push(node);}, [macrosTP]);
				for (var i=0; i<nodes.length; i++)
					nodes[i].remove();

				Jedox.wss.macro.list([ _thats, reloadMacroTreeData_inner_post, moduleName], Jedox.wss.macro.listFmt.TREE);
			}

			function reloadMacroTreeData_inner_post(treeData, moduleName){
	//			console.log(treeData);
				root.appendChild(treeData);
				macrosTP.root.expand();
				var node = macrosTP.getNodeById(moduleName);
				macrosTP.fireEvent('click', macrosTP.getNodeById(moduleName));
				moduleEditor.triggerEdit(node);
			}
		}



		function getNewModuleName(tmplName){
			var br = 1;
			var exist = true;
			var name = tmplName.toLowerCase();

			while (exist){
				exist = false;
				if (br >=1) name = tmplName.toLowerCase() + br;

				macrosTP.root.eachChild(function(node){
					if (node.attributes.text.toLowerCase() == name){
						br= br+1;
						exist = true;
						return false;
					}
				}, [this]);
			}

	//		return br>1? tmplName + ' (' + br + ')':tmplName;
			return tmplName + br;
		}

		function validateName(){

		}

		function checkNameAvailable(target, name){
			for (var i=0; i<target.childNodes.length; i++)
				if (name === target.childNodes[i].attributes.text)
					return false;

			return true;
		}




		function validateName(node, oldName, newName){
			var parent = node.parentNode;
			var _return = true;
			if (oldName != newName) {
				if (newName.length < 64) {
					parent.eachChild(function(node){
						if (node.attributes.text.toLowerCase() == newName.toLowerCase()) {
							_return = false;
						}
					}, [this]);
				}
				else {
					var title = 'Error Renaming Module'.localize();
					var msg = 'rename_module_error_msg'.localize({'old_name':oldName, 'new_name':newName});
					var fn = function(){
						node.setText(oldName);
						editor.triggerEdit(node);
					}
					showMsgQUESTIONERROR(title, msg, fn);
					return false;
				}
			}


			if (!_return){
				var title = 'Error Renaming Module'.localize();
				var msg = 'rename_module_error_msg'.localize({'old_name':oldName, 'new_name':newName});
				var fn = function(){
					node.setText(oldName);
					moduleEditor.triggerEdit(node);
				}
				showMsgQUESTIONERROR(title, msg, fn);
			}

			return _return;
		}

		function trim(s){
			return s.replace(/^\s+|\s+$/g, '');
		}




			function onApply(){

				if (_module){
					var moduleName = _module.id;
					var moduleID = _module.uid;
					var src = editor.getCode();
					Jedox.wss.macro.save([this, refreshModule_inner_post, moduleName], moduleID, src); //need module id
				}
				else {
					showMsgERROR('Error'.localize(), 'edit_macro_no_module_selected_err'.localize());
				}


				function refreshModule_inner_post(result, moduleName){

					var nodes =[];
					macrosTP.root.eachChild(function(node){nodes.push(node);}, [macrosTP]);
					for (var i=0; i<nodes.length; i++)
						nodes[i].remove();

					Jedox.wss.macro.list([ this, reloadMacroTreeData_inner_post, moduleName], Jedox.wss.macro.listFmt.TREE);

				}

				function reloadMacroTreeData_inner_post(treeData, moduleName){
	//				console.log(treeData);
					root.appendChild(treeData);
					macrosTP.root.expand();
					var node = macrosTP.getNodeById(moduleName);
					if (node)
						macrosTP.fireEvent('click', node);
				}
			}



			function onOK(){

				if (_module){
					var moduleName = _module.id;
					var moduleID = _module.uid;
					var src = editor.getCode();
					Jedox.wss.macro.save([this, closeDlg_inner_post], moduleID, src); //need module id
				}
				else {
					showMsgERROR('Error'.localize(), 'edit_macro_no_module_selected_err'.localize());
				}


				function closeDlg_inner_post(result, moduleName){
					that.win.close();
				}
			}

			function onCut() {
				_clipboard = editor.selection();
				editor.replaceSelection('');
			}

			function onCopy() {
				_clipboard = editor.selection();
			}

			function onPaste(){
				if (_clipboard){
					editor.insertIntoLine(editor.cursorPosition(true).line, editor.cursorPosition(true).character, _clipboard);
					_clipboard = ''
				}
			}






			function showMsgERROR(title, message){
	//			Jedox.studio.app.lastInputMode = Jedox.studio.app.inputMode;
	//			Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_studio_DEFAULT;

				Ext.Msg.show({
					title:title,
					msg: message,
					buttons: Ext.Msg.OK,
					animEl: 'elId',
					icon: Ext.MessageBox.ERROR
				});
			}

		function showMsgQUESTIONERROR (title, message, fn){

			Ext.Msg.show({
				title:title,
				msg: message,
				buttons: Ext.Msg.OK,
				fn:function(btn){if(btn=='ok')fn();},
				animEl: 'elId',
				closable:false,
				icon: Ext.MessageBox.ERROR
			});
		}


			function deleteModule(){

				if (_module)
					Jedox.wss.macro.del([this, refreshModule_inner_post], _module.uid);
				else
					showMsgERROR('Error'.localize(), 'edit_macro_no_module_selected_err'.localize());


				function refreshModule_inner_post(result){

					var nodes =[];
					macrosTP.root.eachChild(function(node){nodes.push(node);}, [macrosTP]);
					for (var i=0; i<nodes.length; i++)
						nodes[i].remove();

					Jedox.wss.macro.list([ this, reloadMacroTreeData_inner_post], Jedox.wss.macro.listFmt.TREE);
				}

				function reloadMacroTreeData_inner_post(treeData){
					root.appendChild(treeData);
					macrosTP.root.expand();
					editor.setCode('');
					_module = null;
				}
			}

			function showInsertDialog(){
				if (obj && callBackFnc)callBackFnc();
			}


			function selectMacroInText(node){

				if (node.parentNode.attributes != _module){
					Jedox.wss.macro.load([this, loadTxtArea_inner_post, node.attributes.text], node.parentNode.attributes.uid);
					_module = node.parentNode.attributes;
				}
				else {
					var pattern = 'function '.concat(node.attributes.text);
					var o = editor.getSearchCursor(pattern, false);
					if (o.findNext())
						o.select();
				}


				function loadTxtArea_inner_post(src, name){
					editor.setCode(src);
					var pattern = 'function '.concat(name);
					var o = editor.getSearchCursor(pattern, false);
					if (o.findNext())
						o.select();
				}
			}

			function find(pattern){
				var o = editor.getSearchCursor(pattern, true);
				if (o.findNext())
					o.select();
				else{
					o = editor.getSearchCursor(pattern, false);
					if (o.findNext())
						o.select();
					else{
						Jedox.wss.general.showMsg(tbConfig.winTitle.localize(), 'Cannot find '.concat('"', pattern, '"'), Ext.MessageBox.INFO);
					}
				}
			}

			function openFindDialog(){
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.find, [editor.selection(), find]);
			}


		}


	};
}
)();

Jedox.util.extend(Jedox.wss.dlg.EditMacro, Jedox.dlg.Dialog);