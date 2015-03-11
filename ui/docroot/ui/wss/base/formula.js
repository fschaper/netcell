/*
 * \brief formulas utility code
 *
 * \file formula.js
 *
 * Copyright (C) 2006-2011 Jedox AG
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
 * SVN: $Id: formula.js 4662 2011-02-27 18:44:45Z predragm $
 *
 */

Jedox.wss.formula = new function ()
{
	var _MAX_COL = Jedox.wss.grid.defMaxCoords[0],
			_MAX_ROW = Jedox.wss.grid.defMaxCoords[1],
			_re_dquoted = /"[^"]*"/g,
			_re_squoted = /'[^']*'(?!!)/g,
			_re_dollar = /\$/g,
			_re_tokenize = /(?:^|[^\w����:\$!])((?:[a-z����][\w����]+!)|(?:'[^']+'!))?(\$?[A-Z]+\$?[0-9]+)(:\$?[A-Z]+\$?[0-9]+)?(?![\w����:\$!])/ig,
			_re_separate = /^([A-Z]+)([0-9]+)$/i;

	this.ltrs2num = function (ltrs)
	{
		var num = 0;

		for (var f = 1, i = (ltrs = ltrs.toUpperCase()).length - 1; i >= 0; --i, f *= 26)
			num += (ltrs.charCodeAt(i) - 64) * f;

		return num;
	};

	this.parseCell = function (refstr)
	{
		if ((refstr = refstr.replace(_re_dollar, '').match(_re_separate)) == null)
			return undefined;

		var col = this.ltrs2num(refstr[1]),
				row = parseInt(refstr[2]);

		if (col < 1 || col > _MAX_COL || row < 1 || row > _MAX_ROW)
			return undefined;

		return [ refstr.input, col, row ];
	};

	function _gen_padding (str)
	{
		return Array(str.length + 1).join(' ');
	}

	this.parse = function (fstr, nfs)
	{
		var refs = [];

		refs.sgn = '';
		refs.tbl = {};

		if (!fstr)
			return refs;

		fstr = fstr.replace(_re_dquoted, _gen_padding).replace(_re_squoted, _gen_padding);

		nf_off = { next: null };

		if (nfs instanceof Array && nfs.length)
		{
			var names = [],
					vals = {};

			for (var nf, i = nfs.length - 1; i >= 0; --i)
			{
				nf = nfs[i];
				names.push(nf[0]);
				vals[nf[0]] = nf[1].substr(1);
			}

			var re_names = new RegExp(names.join('|'), 'g'),
					off = nf_off,
					corr = 0;

			fstr = fstr.replace(re_names,
				function (name, start)
				{
					var val = vals[name],
							len = val.length;

					off = off.next = { name: name, start: start += corr, end: start + len, corr: corr += len - name.length, next: null };

					return val;
				}
			);
		}

		nf_off = nf_off.next;

		var cnt = -1,
				sgn = '',
				tbl = {};

		for (var res, ul, lr, tok, key, sheet, tmp, corr_s = 0, corr_e = 0, off = {}; (res = _re_tokenize.exec(fstr)) != null; )
		{
			if ((ul = this.parseCell(res[2])) == undefined)
				continue;

			if (!res[1])
				sheet = '';
			else if (res[1].charAt(0) == '\'')
				sheet = res[1].substr(1, res[1].length - 3);
			else
				sheet = res[1].substr(0, res[1].length - 1);

			tok = {
				sheet: sheet,
				ul: ul.shift(),
				start: _re_tokenize.lastIndex - res[0].length + 1,
				end: _re_tokenize.lastIndex
			};

			if (nf_off && tok.start >= nf_off.end)
			{
				corr_s = corr_e = nf_off.corr;
				nf_off = nf_off.next;
			}

			if (nf_off)
			{
				if (tok.start < nf_off.start)
					tok.id = ++cnt, off = {};
				else if (tok.end > nf_off.end)
					tok.id = ++cnt, off = {}, corr_s = corr_e = nf_off.corr;
				else
				{
					tok.nf = true;

					tok.id = off.name == nf_off.name && off.start == nf_off.start ? cnt : ++cnt;
					off = nf_off;

					if (tok.start > nf_off.start)
						corr_s = nf_off.corr;

					corr_e = nf_off.corr;
				}
			}
			else
				tok.id = ++cnt;

			tok.start -= corr_s;
			tok.end -= corr_e;

			if (res[3])
			{
				if ((lr = this.parseCell(res[3].substr(1))) == undefined)
					continue;

				tok.lr = lr.shift(), tok.rng = ul.concat(lr), key = sheet.length ? sheet.concat('!', tok.ul, ':', tok.lr) : tok.ul.concat(':', tok.lr);

				if (tok.rng[2] < tok.rng[0])
				{
					tmp = tok.rng[0];
					tok.rng[0] = tok.rng[2];
					tok.rng[2] = tmp;
				}

				if (tok.rng[3] < tok.rng[1])
				{
					tmp = tok.rng[1];
					tok.rng[1] = tok.rng[3];
					tok.rng[3] = tmp;
				}
			}
			else
				tok.lr = tok.ul, tok.rng = ul.concat(ul), key = sheet.length ? sheet.concat('!', tok.ul) : tok.ul;

			tok.key = key;

			if (tbl[key])
				tbl[key].push(tok), tok.id = tbl[key][0].id;
			else
				tbl[key] = [ tok ];

			tok.idx = refs.push(tok) - 1;

			sgn = sgn.concat(key, '@', tok.start);
		}

		refs.sgn = sgn;
		refs.tbl = tbl;

		return refs;
	};

}
