/*
 * \brief error definitions and handling
 *
 * \file err.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: err.js 3472 2010-07-06 15:05:17Z predragm $
 *
 */

Jedox.err = new function ()
{
	var that = this;

	var _types = {
	  INFO: 0
	, WARN: 1
	, ERR: 2
	};

	var _flags = {
	  SILENT: 1
	, FATAL: 2
	};

	var _origins = {
		NA: 0
	,	UI: 1
	, UI_B: 2
	, CORE: 3
	, RPC: 4
	};

	var _origins_desc = [ 'General', 'Application', 'Application Backend', 'Server', 'RPC Backend' ];

	var _db = {

			   1:
		{
			name: 'GenericException'
		,	type: _types.ERR
		, origin: _origins.NA
		}

		,  100:
		{
		  name: 'RuntimeException'
		, type: _types.ERR
		, origin: _origins.UI_B
		}

		,  101:
		{
		  name: 'ParsingFailedException'
		, type: _types.ERR
		, origin: _origins.UI_B
		}

		,  102:
		{
		  name: 'NotImplementedException'
		, type: _types.ERR
		, origin: _origins.UI_B
		}

		,  103:
		{
		  name: 'InvalidSessionException'
		, type: _types.ERR
		, flag: _flags.FATAL
		, origin: _origins.UI_B
		}

		, 1000:
		{
		  name: 'InsufficientRightsException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1100:
		{
		  name: 'EventHandlerAbortException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1200:
		{
		  name: 'ClipboardInvalidIndexException'
		, type: _types.WARN
		, origin: _origins.CORE
		}

		, 1300:
		{
		  name: 'InvalidNameException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1400:
		{
		  name: 'InterpreterRuntimeError'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1500:
		{
		  name: 'InvalidFormulaException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1600:
		{
		  name: 'CyclicDependencyException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1700:
		{
		  name: 'ArrayException'
		, type: _types.WARN
		, origin: _origins.CORE
		}

		, 1800:
		{
		  name: 'NoWorkbookSelectedException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1801:
		{
		  name: 'NoWorksheetSelectedException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1802:
		{
		  name: 'NoApplicationSelectedException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1900:
		{
		  name: 'LoadApplicationException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1901:
		{
		  name: 'LoadException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 1902:
		{
		  name: 'SaveException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2000:
		{
		  name: 'ConditionalFormatException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2100:
		{
		  name: 'NamedFormulaException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2101:
		{
		  name: 'NamedFormulaDoesNotExistException'
		, type: _types.WARN
		, origin: _origins.CORE
		}

		, 2200:
		{
		  name: 'CopyWorksheetException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2300:
		{
		  name: 'RangeException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2400:
		{
		  name: 'MergedCellException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2500:
		{
		  name: 'AuthenticationException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2600:
		{
		  name: 'CellDimensionException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2700:
		{
		  name: 'SessionException'
		, type: _types.ERR
		, flag: _flags.FATAL
		, origin: _origins.CORE
		}

		, 2800:
		{
		  name: 'InvalidGroupException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 2900:
		{
		  name: 'InvalidUserException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3000:
		{
		  name: 'TranslationTableException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3100:
		{
		  name: 'WorksheetCopyException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3200:
		{
		  name: 'WorkbookCloneException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3300:
		{
		  name: 'ExtensionRegistryException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3400:
		{
		  name: 'ExtensionCallerException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3500:
		{
		  name: 'CyclicArrayException'
		, type: _types.WARN
		, origin: _origins.CORE
		}

		, 3600:
		{
		  name: 'WorksheetElementException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3700:
		{
		  name: 'FormatException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3800:
		{
		  name: 'StyleManagerException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 3900:
		{
		  name: 'BoundedPointException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4000:
		{
		  name: 'FilterRegistryException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4100:
		{
		  name: 'ContainerWrapperException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4200:
		{
		  name: 'SelectionToLargeException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4300:
		{
		  name: 'ExtensionFailureException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4400:
		{
		  name: 'PaloConnectorException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4500:
		{
		  name: 'FatalException'
		, type: _types.ERR
		, flag: _flags.FATAL
		, origin: _origins.CORE
		}

		, 4600:
		{
		  name: 'ArrayFormulaOnMergedCellException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		, 4700:
		{
		  name: 'ValueConversionException'
		, type: _types.ERR
		, origin: _origins.CORE
		}

		,   R1:
		{
		  name: 'GenericException'
		, type: _types.ERR
		, origin: _origins.RPC
		}

		,   R2:
		{
		  name: 'SystemException'
		, type: _types.ERR
		, origin: _origins.RPC
		}

	};

	function _relogin ()
	{
		window.parent.onbeforeunload = function () { };

		window.parent.location.href = '/ui/login/?r';
	}

	this.show = function (code, msg, params)
	{
		if (!(code in _db) || !(code in this.i18n))
			code = 1;

		var err = _db[code];

		if (err.flag & _flags.SILENT)
			return;

		var icons = [ Ext.MessageBox.INFO, Ext.MessageBox.WARNING, Ext.MessageBox.ERROR ],
				mb_conf = { title: _origins_desc[err.origin].concat(' Error').localize().concat(' ', code), icon: icons[err.type], buttons: Ext.MessageBox.OK },
				desc = this.i18n[code];

		if (params instanceof Object)
			for (var p in params)
				desc = desc.replace('{'.concat(p, '}'), params[p]);

		if (typeof msg == 'string' && msg.length)
			desc = desc.concat('<br/><br/><br/>', 'Error Data'.localize(), ':<br/>', msg, '<br/>');
		else
			desc = desc.concat('<br/>');

		if (err.flag & _flags.FATAL)
		{
			desc = desc.concat('<br/><b>', 'This is a fatal error, re-login will be required!'.localize(), '</b><br/>');
			mb_conf.fn = _relogin;
		}

		mb_conf.msg = desc;

		Ext.MessageBox.show(mb_conf);
	};

	this.scan = function (res)
	{
		var found = false,
				el;

		for (var i in res)
			if ((el = res[i])[0] === false)
				found = true, that.show(el[1], el[2], el[3]);

		return found;
	};

};