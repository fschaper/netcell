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
 * Andrej Vrhovac <andrej.vrhovac@develabs.com>
 *
 * \version
 * SVN: $Id: Content.js 4195 2010-10-26 22:37:54Z predragm $
 *
 */

Jedox.wss.dlg.control.content = function(callback, _pre, tabOffset, thats) {

	if (!tabOffset) tabOffset = 0;

	var urlRadio = new Ext.form.Radio({
		checked: (_pre.cnttype == 'url' || !_pre.cnttype)? true:false,
		name: 'radioContent',
		tabIndex: tabOffset + 1,
		hideLabel: false,
		boxLabel: 'URL'.localize(),
		listeners: {
			check: function(thisRb, isChecked)
			{
				if (isChecked)
				{
					urlFld.enable();
					htmlBtn.disable();
				}
			}
		}
	});

	var urlFld = new Ext.form.Field({
		width: 380,
		tabIndex: tabOffset + 2,
		hideLabel: true,
		disabled: (_pre.cnttype == 'url' || !_pre.cnttype)? false:true
	});

	var urlPan = new Ext.Panel({
		layout: 'column',
		baseCls: 'x-plain',
		border: false,
		items: [
		        new Ext.Panel({
		        	baseCls: 'x-plain',
		        	width: 60,
		        	labelWidth: 30,
		        	items: [urlRadio]
		        }),
		        new Ext.Panel({
		        	baseCls: 'x-plain',
		        	//width: 250,
		        	autoWidth: true,
		        	items: [urlFld]
		        })
		        ]
	});

	//=====================================

	var htmlRadio = new Ext.form.Radio({
		//checked: this.typeDisabled,
		name: 'radioContent',
		hideLabel: false,
		tabIndex: tabOffset + 3,
		checked: (_pre.cnttype == 'html')? true:false,
		boxLabel: 'HTML',
		listeners: {
			check: function(thisRb, isChecked)
			{
				if (isChecked)
				{
					urlFld.disable();
					htmlBtn.enable();
				}
			}
		}
	});
	var tmpHtml = '';

	var setFn = function(src){
		tmpHtml = src;
	};

	var htmlBtn = new Ext.Button({
		id: 'htmlBtn',
		iconCls: 'icon_macro',
		disabled: (_pre.cnttype == 'url' || !_pre.cnttype)? true:false,
		tabIndex: tabOffset + 4,
		ctCls: Jedox.kbd.Base.tags.NO_ENTER,
		text: 'Editor'.localize(),
		cls: 'x-btn-icon-text',
		handler: function(){
			//" +
			htmlRadio.setValue(true);
			Jedox.gen.load(Jedox.wss.app.dynJSRegistry.editMacro, [{operation:'edit', macro:tmpHtml}, false, 'html', setFn]);
		}
	});

	var htmlPan = new Ext.Panel({
		layout: 'column',
		baseCls: 'x-plain',
		bodyStyle: 'padding-top: 10px;',
		labelWidth: 30,
		border: false,
		items: [
		        new Ext.Panel({
		        	baseCls: 'x-plain',
		        	width: 60,
		        	labelWidth: 30,
		        	items: [htmlRadio]
		        }),
		        new Ext.Panel({
		        	baseCls:100,
		        	items: [htmlBtn]
		        })
		        ]
	});

	// ==================================

	var fsCnt = Ext.extend(Ext.form.FieldSet,{

		getData: function()
		{
			var data = {
					type: (urlRadio.checked)? 'url' : 'html',
					cnt: (urlRadio.checked)? urlFld.getValue() : tmpHtml
			};
			return data;
		},

		initComponent: function(){
			Ext.apply(this, {});
			fsCnt.superclass.initComponent.call(this);
		}
	});

	var fsContent = thats.containers.contentpan = new fsCnt({
		title: "Content".localize(),
		collapsible: false,
		id: 'cnt_pan',
    	autoWidth: true,
    	autoHeight: true,
		items: [urlPan, htmlPan]
	});


	// PRESELECTION

	if (_pre.cnttype == 'url')
		urlFld.setValue(_pre.cnt);
	else
		tmpHtml = _pre.cnt;



	// end preselection

	callback(fsContent);
}