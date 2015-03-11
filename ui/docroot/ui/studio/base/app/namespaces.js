/*
 * \brief namespaces definition
 *
 * \file namespaces.js
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 *
 * \version
 * SVN: $Id: namespaces.js 5087 2011-06-29 14:22:30Z mladent $
 *
 */


var Jedox;

if (!Jedox) {

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
			* Jedox style namespace, contains all style and formating routines
			*
			* @alias	Jedox.wss.style
			*/
			style: {},

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
			* Jedox events namespace, contains all objects used for sending events used outside of WSS.
			*
			* @alias	Jedox.wss.events
			*/
			events: {}
		},

        /**
		* Jedox studio namespace
		*
		* @alias	Jedox.studio
		*/
		studio: {

			/**
			* Jedox app namespace, contains all the application globals
			*
			* @alias	Jedox.studio.app
			*/
			app: {},

			/**
			* Jedox backend namespace, contains all backend connectivity functionality
			*
			* @alias	Jedox.studio.backend
			*/
			backend: {},

			/**
			* Jedox keyboard namespace, contains all keyboard functionality
			*
			* @alias	Jedox.studio.keyboard
			*/
			keyboard: {},

			/**
			* Jedox mouse namespace, contains all mouse functionality
			*
			* @alias	Jedox.studio.mouse
			*/
			mouse: {},

			/**
			* Jedox dialog namespace, contains all the application dialogs - to delete later
			*
			* @alias	Jedox.studio.dialog
			*/
			dialog: {},

			/**
			* Jedox dlg namespace, contains Studio application dialogs
			*
			* @alias	Jedox.studio.dialog
			*/
			dlg: {},

			/**
			* Jedox internationalization namespace, contains all the application localizations
			*
			* @alias	Jedox.studio.i18n
			*/
			i18n: {},

			/**
			* Jedox action namespace, contains action routines
			*
			* @alias	Jedox.studio.action
			*/
			action: {},

			/**
			* Jedox file namespace, contains all functionality related to File management.
			*
			* @alias	Jedox.studio.file
			*/
			files: {

				/**
				* Files dialogs namespace, contains all dialogs related to Files management.
				*
				* @alias	Jedox.studio.files.dlg
				*/

				dlg: {}

			},

			/**
			* Jedox report namespace, contains all functionality related to Reports management.
			*
			* @alias	Jedox.studio.report
			*/
			reports: {

				/**
				* Reports dialogs namespace, contains all dialogs related to Reports management.
				*
				* @alias	Jedox.studio.reports.dlg
				*/

				dlg: {}

			},

			/**
			* Jedox access namespace, contains all functionality related to User/Group management and Access Rights.
			*
			* @alias	Jedox.studio.access
			*/
			access: {},

			/**
			* Jedox access namespace, contains all functionality related to User/Group management and Access Rights.
			*
			* @alias	Jedox.studio.access
			*/
			users: {},

			/**
			* Jedox conn namespace, contains all functionality related to Connections management.
			*
			* @alias	Jedox.studio.conns
			*/
			conns: {},

			/**
			* Jedox plugin namespace, contains all functionality related to plugins.
			*
			* @alias	Jedox.studio.plugin
			*/
			plugin: {},

			/**
			* Jedox palo namespace, contains panels used for palo functionality.
			*
			* @alias	Jedox.studio.palo
			*/
			palo: {},

			/**
			* Jedox scheduler namespace, contains panels used for scheduler functionality.
			*
			* @alias	Jedox.studio.scheduler
			*/
			scheduler: {},

			/**
			* Jedox etl namespace, contains panels used for integrated ETL Web Client functionality.
			*
			* @alias	Jedox.studio.etl
			*/
			etl: {}
		}
    };
}