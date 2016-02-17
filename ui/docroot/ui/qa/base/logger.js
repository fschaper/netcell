/*
 * \brief QA globals
 *
 * \file qa.js
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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: logger.js 5134 2011-07-20 13:17:32Z predragm $
 *
 */

Jedox.qa.logger = new function ()
{
	var that = this;

	var errors = {
		refresh: false
		,error: []
	};

	// start listening to JS errors
	this.start = function() {

		// put all errors in storage object
		window.onerror = function(msg, url, linenumber){
			errors.error.push("JS Error: ".concat(msg, " in file: ", url, " on line: ", linenumber));

			if (msg.indexOf("Jedox") === 0) errors.refresh = true;
		}

	}

	// stop listening to JS errors
	this.stop = function() {

		window.onerror = undefined;

	}


	// get all errors and clean storage
	// Boolean clean : do errors object cleanup
	this.dump = function(clean){
		var toRet = errors;

		if (clean) this.clean();

		return toRet;
	}

	// cleans errors object
	this.clean = function(){
		errors = {
			refresh: false
			,error: []
		};
	}

};