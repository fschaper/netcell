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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: utils.js 4837 2011-04-13 12:25:05Z predragm $
 *
 */

if (Jedox)
{
	if (Jedox.palo)
	{
		Jedox.palo.NONE = 0;
		Jedox.palo.GRID = 1;
		Jedox.palo.STUDIO = 2;
	}
	else
		Jedox.palo = {NONE: 0, GRID: 1, STUDIO: 2, workIn: 0};

	Jedox.palo.workIn = (Jedox.studio) ? Jedox.palo.STUDIO : Jedox.palo.GRID;
}
else
	Jedox = {palo: {NONE: 0, GRID: 1, STUDIO: 2, workIn: 0}};

Jedox.palo.utils = new function()
{
	if (Jedox.palo.workIn == Jedox.palo.GRID)
	{
		var gridModes = Jedox.wss.grid.viewMode,
			getParsedArgs = function(fnc, nonStrArgs)
			{
				var sFnc = fnc.split('('),
					fnc = fnc.substring(sFnc[0].length + 1, fnc.length - 1),
					quoted = fnc.match(/"(?:[^\\"]+|\\.)*"/g),
					nonQouted = fnc.replace(/"(?:[^\\"]+|\\.)*"/g, ''),
					args = nonQouted.split(Jedox.wss.i18n.separators[2]),
					isError = false;

				for (var i = 0, skipArgs = 0; i < args.length; i++)
				{
					if (args[i].length == 0)
						args[i] = quoted[i - skipArgs].substring(1, quoted[i - skipArgs].length - 1);
					else
					{
						skipArgs++;

						// Problem with non string values
						// TODO: Add if possible to get value of non string argument
						if (nonStrArgs && !nonStrArgs[i])
							isError = true;
					}
				}

				return { args: args, error: isError };
			};

		this.registerHandlers = function()
		{
			switch(Jedox.wss.app.appMode)
			{
				case gridModes.DESIGNER:
					Jedox.wss.grid.cbReg('hnd_dblCpvOpen', [this, Jedox.palo.utils.handleOpenPasteViewDblclick]);

				case gridModes.USER:
					Jedox.wss.grid.cbReg('hnd_openPaloTE', [this, Jedox.palo.utils.openPaloTextEditor]);
					Jedox.wss.grid.cbReg('hnd_dblCpv', [this, Jedox.palo.utils.handlePasteViewDblclick]);
					Jedox.wss.grid.cbReg('hnd_dblCceOpen', [this, Jedox.palo.utils.handleOpenPasteViewChooseElement]);
					Jedox.wss.grid.cbReg('hnd_dblCseOpen', [this, Jedox.palo.utils.handleOpenPasteViewSelectElements]);
			}
		}

		this.handlePasteViewDblclick = function(inObj, relX, relY, pasteViewId, dimName, elemName)
		{
			Jedox.backend.rpc_cb('palo_handlerExpandCollapsePasteView', [[inObj, relX, relY, pasteViewId, dimName, elemName]]);

			return false;
		}

		this.handleOpenPasteViewDblclick = function(inObj, pasteViewId, x, y)
		{
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.pasteView, [pasteViewId, x, y]);

			return false;
		}

		this.handleOpenPasteViewChooseElement = function(inObj, confData)
		{
			var argsData = getParsedArgs(Jedox.wss.app.activePane.getCellFormula(inObj.c, inObj.r), {3: true});
			if (!argsData.error)
			{
				var servDb = argsData.args[0].split('/');

				confData.serv_id = servDb[0];
				confData.db_name = servDb[1];
				confData.dim_name = argsData.args[1];

				confData.edit_data[0][0] = argsData.args[2];

				// attributes
				if (argsData.args.length > 5)
					confData.edit_data[0][1] = (argsData.args[5].length == 0) ? null : argsData.args[5];
			}

			confData['dblclick_data'] = inObj;
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.chooseElement, [confData]);

			return false;
		}

		this.handleOpenPasteViewSelectElements = function(inObj, confData)
		{
			confData['dblclick_data'] = inObj;
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.selectElements, [confData]);

			return false;
		}

		this.openSubsetEditor = function(conf)
		{
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.subsetEditor, [conf]);
		}

		this.openPaloTextEditor = function(inObj)
		{
			var	activePane = Jedox.wss.app.activePane,
					cellType = activePane.getCellType(inObj.c, inObj.r);

			if ((cellType == 's' || cellType == 'h') && (Jedox.wss.app.appMode == gridModes.DESIGNER || (Jedox.wss.app.appMode == gridModes.USER && !activePane.isCellLocked(inObj.c, inObj.r))))
			{
				Jedox.gen.load(Jedox.wss.app.dynJSRegistry.paloTextEditor, [ [inObj.c, inObj.r] ]);
				return false;
			}

			return true;
		}
	}

	// class for lists with onenter event
	this.OnEnterDataViewClass = Ext.extend(Ext.DataView, {
		focusedClass: "x-view-focused",
		focusEl: true,
		afterRender: function()
		{
			Jedox.palo.utils.OnEnterDataViewClass.superclass.afterRender.call(this);
			var that = this;

			if (this.singleSelect || this.multiSelect)
			{
				if (this.focusEl === true)
				{
					this.focusEl = this.el.parent().parent().createChild({
						tag : "a",
						href : "#",
						cls : "x-view-focus",
						tabIndex : "-1"
					});
					this.focusEl.insertBefore(this.el.parent());
					this.focusEl.swallowEvent('click', true);
					this.renderedFocusEl = true;
				}
				else if (this.focusEl)
					this.focusEl = Ext.get(this.focusEl);

				if (this.focusEl)
				{
					this.keyNav = new Ext.KeyNav(this.focusEl, {
						"up" : function(e) {
							var selection = that.getSelectedIndexes();
							if (selection.length > 0)
							{
								var lastIndex = selection[selection.length - 1];

								if (lastIndex <= selection[0])
								{
									if (lastIndex > 0)
									{
										if (that.multiSelect && e.shiftKey)
											that.select(lastIndex - 1, true, false);
										else
											that.select(lastIndex - 1);
									}
								}
								else
									that.deselect(lastIndex);
							}
						},
						"down" : function(e) {
							var selection = that.getSelectedIndexes();
							if (selection.length > 0)
							{
								var lastIndex = selection[selection.length - 1];

								if (lastIndex >= selection[0])
								{
									if (lastIndex < (that.getStore().getCount() - 1))
									{
										if (that.multiSelect && e.shiftKey)
											that.select(lastIndex + 1, true, false);
										else
											that.select(lastIndex + 1);
									}
								}
								else
									that.deselect(lastIndex);
							}
						},
						"enter": function()
						{
							if (that.events.onkeyenter)
								that.events.onkeyenter.fire();
						},
						scope: this,
						forceKeyDown: true
					});
				}
			}
		},
		onClick: function(e)
		{
			var item = e.getTarget(this.itemSelector, this.el);
			if (item)
			{
				var index = this.indexOf(item);
				if (this.onItemClick(item, index, e) !== false)
				{
					this.fireEvent("click", this, index, item, e);
					this.retainFocus();
				}
			}
			else
			{
				if (this.fireEvent("containerclick", this, e) !== false)
				{
					this.clearSelections();
					this.retainFocus();
				}
			}
		},
		retainFocus: function()
		{
			var that = this;
			if (this.focusEl)
			{
				setTimeout(function() {
					that.focusEl.focus();
				}, 0);
			}
		},
		doRetainFocus: function()
		{
			this.focusEl.focus();
		}
	});

	this.checkPaloName = function(name, type)
	{
		switch (type)
		{
			case 'database':
			case 'db':
					var res = name.match(/^[a-zA-Z0-9_-][a-zA-Z0-9\._-]*/);
					return ((res != null) && (res == name));
				break;

			case 'dimension':
			case 'dim':
			case 'cube':
				var res = name.match(/^[^\x00-\x1F\\*:|<>\/?\.\s][^\x00-\x1F\\*:|<>\/?]*/);
				if ((res != null) && (res == name))
					res = name.match(/[^\x00-\x1F\\*:|<>\/?]*[^\x00-\x1F\\*:|<>\/?\s]$/);
				else
					return false;

				return ((res != null) && (res == name));
				break;

			case 'element':
			case 'elem':
					var res = name.match(/^[^\x00-\x1F\s][^\x00-\x1F]*/);
					if ((res != null) && (res == name))
						res = name.match(/[^\x00-\x1F]*[^\x00-\x1F\s]$/);
					else
						return false;

					return ((res != null) && (res == name));
				break;
		}

		return false;
	}

	this.escHTML = function(str)
	{
		if (str)
			return str.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');

		return str;
	}

	this.showWaitMsg = function(msgText, onBarText)
	{
		Ext.MessageBox.show({
			msg: msgText,
			progressText: onBarText,
			width: 300,
			wait: true,
			waitConfig: {interval:200}
		});
	}

	this.showLoadingMsg = function(msgText)
	{
		Ext.MessageBox.show({
			title: "Please wait".localize(),
			msg: '<br>'.concat(msgText),
			closable: false,
			icon: 'largeLoadingImage'
		});
	}

	this.hideWaitMsg = function(showErr)
	{
		Ext.MessageBox.hide();

		if (showErr)
			Ext.MessageBox.show({
				title: "Error".localize(),
				msg: "_msg: Timer".localize(),
				buttons: Ext.Msg.OK,
				icon: Ext.MessageBox.ERROR
			});
	}
}

Jedox.palo.config =
{
	widthMidButtons: 38,
	imgsPath: '/ui/common/res/img/palo/',
	elementSize: 18, // height of Element in DataView
	numberOfElements: 10000, // number of elements per request
	fixWidth: 12.57 // used in Paste View Dialog
}
