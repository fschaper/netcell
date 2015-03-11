/*
 * \brief export files from Studio
 *
 * \file export.js
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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: export.js 4939 2011-05-11 12:42:25Z predragm $
 *
 */

Jedox.studio.files.exportFile = function (ghn, from)
{
	var frameID = 'tmpExportIFrame',
			frame = Ext.get('tmpExportIFrame');

	if (!frame)
	{
		frame = document.createElement('iframe');
		frame.id = frameID;
		frame.name = frameID;
		frame.className = 'x-hidden';

		if (Ext.isIE)
			frame.src = Ext.SSL_SECURE_URL;

		document.body.appendChild(frame);

		if (Ext.isIE)
			document.frames[frameID].name = frameID;
	}
	else
		frame = frame.dom;

	frame.contentWindow.location.href = '/be/studio/export.php?'.concat('t=', from, '&g=', ghn.g, '&h=', ghn.h, '&n=', ghn.n);
};

Jedox.studio.files.exportError = function (err, params)
{
	Jedox.studio.app.showMessageALERT('Error'.localize(), err.localize(params));
};
