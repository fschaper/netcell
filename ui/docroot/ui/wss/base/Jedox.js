/*
 * \brief namespaces definition
 *
 * \file Jedox.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 *
 * \version
 * SVN: $Id: Jedox.js 4381 2010-12-02 12:48:26Z predragm $
 *
 */

if (!Jedox)
{
	/**
	* Root Jedox namespace
	*
	* @alias		Jedox
	*/
	var Jedox = {

		/**
		* Jedox util namespace
		*
		* @alias	Jedox.util
		*/
		util: {},

		/**
		* Jedox gen namespace, contains generic classes not necessarily related to WSS
		*
		* @alias	Jedox.gen
		*/
		gen: {},

		/**
		* Jedox backend namespace
		*
		* @alias	Jedox.backend
		*/
		backend: {
			rpc: {}
		},

		/**
		* Jedox kbd namespace
		*
		* @alias	Jedox.kbd
		*/
		kbd: {},

		/**
		* Jedox dlg namespace
		*
		* @alias	Jedox.dlg
		*/
		dlg: {},

		/**
		* Jedox palo namespace, contains head objects related to Palo dailogs
		*
		* @alias	Jedox.palo
		*/
		palo: {},

		/**
		* Jedox wss namespace
		*
		* @alias	Jedox.wss
		*/
		wss: {
			/**
			* Jedox app namespace, contains all the application globals
			*
			* @alias	Jedox.wss.app
			*/
			app: {},

			/**
			* Jedox general namespace
			*
			* @alias	Jedox.wss.general
			*/
			general: {},

			/**
			* Jedox grid namespace, contains all grid functionality
			*
			* @alias	Jedox.wss.grid
			*/
			grid: {},

			/**
			* Jedox keyboard namespace, contains all keyboard functionality
			*
			* @alias	Jedox.wss.keyboard
			*/
			keyboard: {},

			/**
			* Jedox mouse namespace, contains all mouse functionality
			*
			* @alias	Jedox.wss.mouse
			*/
			mouse: {},

			/**
			* Jedox range namespace, contains all range handling routines
			*
			* @alias	Jedox.wss.range
			*/
			range: {},

			/**
			* Jedox sheet namespace, contains all sheet handling routines
			*
			* @alias	Jedox.wss.sheet
			*/
			sheet: {},

			/**
			* Jedox style namespace, contains all style and formating routines
			*
			* @alias	Jedox.wss.style
			*/
			style: {},

			/**
			* Jedox book namespace, contains all workbook management routines
			*
			* @alias	Jedox.wss.book
			*/
			book: {},

			/**
			* Jedox wnd namespace, contains all window related routines
			*
			* @alias	Jedox.wss.wnd
			*/
			wnd: {},

			/**
			* Jedox dlg namespace, contains all the application dialog classes.
			*
			* @alias	Jedox.wss.dlg
			*/
			dlg: {

				/**
				* Jedox chart namespace, contains all chart dialog classes.
				* Jedox format namespace, contains all formatting elements.
				*
				* @alias	Jedox.wss.dlg.chart
				* @alias	Jedox.wss.dlg.format
				* @alias	Jedox.wss.dlg.control
				*/
				chart: {},
				format: {},
				control: {}
			},

			/**
			* Jedox internationalization namespace, contains all the application localizations
			*
			* @alias	Jedox.wss.i18n
			*/
			i18n: {},

			/**
			* Jedox palo namespace, contains all objects used for comunication with palo
			*
			* @alias	Jedox.wss.palo
			*/
			palo: {},

			/**
			* Jedox action namespace, contains action routines
			*
			* @alias	Jedox.wss.action
			*/
			action: {},

			/**
			* Jedox dynarange namespace, contains all objects used for building dynaranges.
			*
			* @alias	Jedox.wss.hb
			*/
			hb: {},

			/**
			* Jedox hyperlink namespace, contains all objects used for handling hyperlinks.
			*
			* @alias	Jedox.wss.hl
			*/
			hl: {},

			/**
			* Jedox format namespace, contains all objects used for value formatting.
			*
			* @alias	Jedox.wss.format
			*/
			format: {},

			/**
			* Jedox cndfmt namespace, contains all objects used for conditional formatting.
			*
			* @alias	Jedox.wss.cndfmt
			*/
			cndfmt: {},

			/**
			* Jedox formel namespace, contains all objects used for handling form elements.
			*
			* @alias	Jedox.wss.formel
			*/
			formel: {},

			/**
			* Jedox events namespace, contains all objects used for sending events used outside of WSS.
			*
			* @alias	Jedox.wss.events
			*/
			events: {},

			/**
			* Jedox wsel namespace, contains all objects used for worksheet elements.
			*
			* @alias	Jedox.wss.wsel
			*/
			wsel: {},

			/**
			* Jedox cmnts namespace, contains all objects and methods used for cell comments.
			*
			* @alias	Jedox.wss.cmnts
			*/
			cmnt: {}
		}
	};
}