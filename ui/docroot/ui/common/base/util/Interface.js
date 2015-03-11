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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: Interface.js 1485 2009-04-16 15:33:53Z vladislavm $
 *
 */

Jedox.util.Interface = function(name, methods) {
	if (arguments.length != 2)
		throw new Error('Interface constructor called with '.concat(arguments.length, 'arguments, but expected exactly 2.'));

	this.name = name;
	this.methods = [];

	for (var i = 0, len = methods.length; i < len; i++) {
		if(typeof methods[i] !== 'string')
			throw new Error('Interface constructor expects method names to be passed in as a string.');

		this.methods.push(methods[i]);
	}
};

// Static class method.
Jedox.util.Interface.ensureImplements = function(object) {
	if (arguments.length < 2)
		throw new Error('Function Interface.ensureImplements called with '.concat(arguments.length, 'arguments, but expected at least 2.'));

	for (var i = 1, len = arguments.length; i < len; i++) {
		var _interface = arguments[i];

		if (_interface.constructor !== Jedox.util.Interface)
			throw new Error('Function Interface.ensureImplements expects arguments two and above to be instances of Interface.');

		for (var j = 0, methodsLen = _interface.methods.length; j < methodsLen; j++) {
			var method = _interface.methods[j];

			if (!object[method] || typeof object[method] !== 'function')
				throw new Error('Function Interface.ensureImplements: object does not implement the '.concat(_interface.name, ' interface. Method ', method, ' was not found.'));
		}
	}
};