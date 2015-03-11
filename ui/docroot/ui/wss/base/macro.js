/*
 * \brief macro routines and constants
 *
 * \file macro.js
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
 * SVN: $Id: macro.js 4839 2011-04-13 12:41:30Z predragm $
 *
 */

Jedox.wss.macro = new function ()
{
	var that = this,
			_json = Ext.util.JSON,
			_conn = Jedox.backend,
			_re_findfunc = /function[ \t]+(\w+)[ \t]?\(/ig,

			msgIcons = { 'info': 'ext-mb-info', 'warn': 'ext-mb-warning', 'err': 'ext-mb-error' };

	this.listFmt = {
	  FLAT: 0
	, TREE: 1
	};


	// list
	this.list = function (cb, format)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.ccmdSetBuff('[["bget","",[],["e_id","name","funclist"],{"e_type":"macromdl"}]]');
		_conn.ccmdFlush([ that, _list_post, cb, format ]);
	}

	function _list_post (res, cb, format)
	{
		if (res[0][0] !== true || !(res[0][1] instanceof Array))
			return false;

		res = res[0][1];

		switch (format)
		{
			case that.listFmt.FLAT:

				var list = [];

				for (var i = res.length - 1; i >= 0; --i)
					for (var mdl = res[i], j = mdl.funclist.length - 1; j >= 0; --j)
						list.unshift(mdl.name.concat('.', mdl.funclist[j]));

				break;

			case that.listFmt.TREE:

				for (var mdl, i = res.length - 1; i >= 0; --i)
				{
					mdl = res[i];

					for (var func, j = mdl.funclist.length - 1; j >= 0; --j)
					{
						func = mdl.funclist[j];
						mdl.funclist[j] = { id: mdl.name.concat('.', func), text: func, leaf: true, iconCls: 'wss_macro_func' };
					}

					mdl.uid = mdl.e_id;
					delete mdl.e_id;

					mdl.id = mdl.name;

					mdl.text = mdl.name;
					delete mdl.name;

					mdl.leaf = false;

					mdl.iconCls = 'wss_macro_mdl';

					mdl.children = mdl.funclist;
					delete mdl.funclist;
				}

				var list = res;

				break;

			default:
				var list = false;
		}

		cb[1].apply(cb[0], [ list ].concat(cb.slice(2)));
	}


	// add
	this.add = function (cb, mdlName)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.ccmdSetBuff('[["badd","",{"e_type":"macromdl","name":"'.concat(mdlName, '","funclist":[],"src":"\\n"}]]'));
		_conn.ccmdFlush([ that, _add_post, cb ]);
	}

	function _add_post (res, cb)
	{
		res = res[0];

		if (res[0] !== true || !(res[1] instanceof Array) || res[1].length != 1)
			return false;

		cb[1].apply(cb[0], [ res[1][0] ].concat(cb.slice(2)));
	}


	// rename
	this.rename = function (cb, mdlUid, newMdlName)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.ccmdSetBuff('[["bupd","",{"'.concat(mdlUid, '":{"name":', _json.encode(newMdlName), '}}]]'));
		_conn.ccmdFlush([ that, _rename_post, cb ]);
	}

	function _rename_post (res, cb)
	{
		cb[1].apply(cb[0], [ res[0][0] ].concat(cb.slice(2)));
	}


	// del
	this.del = function (cb, mdlUid)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.ccmdSetBuff('[["bdel","",["'.concat(mdlUid, '"]]]'));
		_conn.ccmdFlush([ that, _del_post, cb ]);
	}

	function _del_post (res, cb)
	{
		cb[1].apply(cb[0], [ res[0][0] ].concat(cb.slice(2)));
	}


	// load
	this.load = function (cb, mdlUid)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.ccmdSetBuff('[["bget","",["'.concat(mdlUid, '"],["src"],{}]]'));
		_conn.ccmdFlush([ that, _load_post, cb ]);
	}

	function _load_post (res, cb)
	{
		res = res[0];

		if (res[0] !== true || typeof res[1][0] != 'object')
			return false;

		cb[1].apply(cb[0], [ res[1][0].src ].concat(cb.slice(2)));
	}


	// save
	this.save = function (cb, mdlUid, src)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		var funclist = [];

		for (var res; (res = _re_findfunc.exec(src)) != null; )
			funclist.push(res[1]);

		_conn.ccmdSetBuff('[["bupd","",{"'.concat(mdlUid, '":{"src":', _json.encode(src), ',"funclist":', _json.encode(funclist), '}}]]'));
		_conn.ccmdFlush([ that, _save_post, cb ]);
	}

	function _save_post (res, cb)
	{
		cb[1].apply(cb[0], [ res[0][0] ].concat(cb.slice(2)));
	}


	// export
	this.exprt = function (cb)
	{
		if (!(cb instanceof Array) || cb.length < 2)
			return false;

		_conn.rpc([ that, _exprt_post, cb ], 'WSS', 'exportMacros', []);
	}

	function _exprt_post (res, cb)
	{
		cb[1].apply(cb[0], [ res ].concat(cb.slice(2)));
	}

	// UI execute
	this.ui_exec = function (ccmd)
	{
		if (ccmd[0] !== true)
			return false;

		ccmd = ccmd[1];

		if (typeof ccmd == 'string' && ccmd.length && ccmd.charAt(0) != '#')
			return eval(ccmd);

		if (!(ccmd instanceof Array))
			return false;

		for (var cmd, cmdid, c = -1; (cmd = ccmd[++c]) != undefined; )
			switch (cmdid = cmd.shift())
			{
				case 'eval':

					eval(cmd[0]);

					break;

				case 'actn':

					var actions = Jedox.wss.action,
							name = cmd.shift();

					if (name in actions)
						actions[name].apply(actions, cmd);

					break;

				case 'msg':

					var icon = cmd[0];
					icon = icon in msgIcons ? msgIcons[icon] : msgIcons.info;

					Ext.MessageBox.show({ icon: icon, title: cmd[1], msg: cmd[2], buttons: Ext.MessageBox.OK });

					break;

				case 'hl':

					var link = cmd[0];

					if (link.match(/^\$?[a-z]+\$?[0-9]+$/i))
						Jedox.wss.hl.exec(link);
					else
						Jedox.wss.hl.execDyn(link, cmd[1]);

					break;
			}
	}

}