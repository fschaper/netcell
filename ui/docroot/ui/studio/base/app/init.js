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
 * Srdjan Vukadinovic <srdjan.vukadinovic@develabs.com>
 *
 * \version
 * SVN: $Id: init.js 5152 2011-07-28 10:02:33Z predragm $
 *
 */

Ext.onReady(function(){
    Ext.QuickTips.init();

	Jedox.studio.backend.wssStudio = new Jedox.backend.rpc.Studio();
	Jedox.studio.frames = {};

	// join localization objects
	Ext.applyIf(Jedox.studio.i18n.strings, Jedox.wss.tmp.i18n_strings);
	delete Jedox.wss.tmp.i18n_strings;

	Jedox.gen.dynJSAutoload(Jedox.studio.app.dynJSRegistry);

	document.onkeydown = function (e){
		Jedox.kbd.ctxRegistry.getActive().handle(e);
	}


    Jedox.studio.app.viewport = new Ext.Viewport({
        layout:'border',
        items:Jedox.studio.app.initModules(),
		masked:false,
		listeners:{
	        render: function() {
				this.setReady(false); //mask on render
	        },
			afterrender: function(){
//				console.log('linkrequest || homepage');

				function doOpen(data){

					Ext.getCmp('sReports_treeHolder_pnl').expand();
					Ext.getCmp('reports-content-panel').fireEvent('quickview', true);
					if (Jedox.studio.access.rules.ste_reports & Jedox.studio.access.permType.WRITE)
						Ext.getCmp('sReports_tree_tr').fireEvent('switchToQV');

					setTimeout(function(){
						if (data) {
							var g = data.group;
							var h = data.hierarchy;
							var n = data.node;
							var p = data.path;
							var vars = data['var'];
							var type = data.type || 'spreadsheet';
							var preselect = data.preselect;

							if (Jedox.studio.app.params['var'])
								Ext.getCmp('reports-content-panel').fireEvent('openExternalHL', {g:g, h:h, n:n, v:vars}, p.split('/').pop(), type);
							else {
								if (preselect){
									Jedox.studio.reports.cbf = function(){
											Ext.getCmp('sReports_tree_tr').fireEvent('switchToQV', {g:g, h:h, n:n, rPath:p, open:true});
									}
									Ext.getCmp('sReports_treeHolder_pnl').expand();
								}
								else {
									setTimeout(function(){
										Ext.getCmp('reports-content-panel').fireEvent('openExternalHL', {g:g, h:h, n:n, p:p, v:vars}, p.split('/').pop(), type);
									});
								}
							}

						}
					}, 500);

				}

				var now = Math.round((new Date()).getTime() / 1000);
				var min=1;
				var max = 5*24*60*60;
				var open = max+1;
				var day = 24*60*60; //seconds
				var licence = Jedox.studio.app.license? Jedox.studio.app.license.expiredate - now:open;


				if (licence <= max){
						//TRUE expired, FALSE warning
						Jedox.gen.load(Jedox.studio.app.dynJSRegistry.openLicence, [(licence > min && licence < max)? (Math.round(licence/day)+1):0]);
				}


			}
		},
		setReady:function(ready){

			if(ready){
				if(this.masked){
					this.getEl().unmask();
				}
			}
			else{
				this.getEl().mask();
			}

			this.masked = !ready;

		}
    });

});