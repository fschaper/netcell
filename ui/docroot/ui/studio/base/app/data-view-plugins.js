/*
 * Ext JS Library 2.2
 * Copyright(c) 2006-2008, Ext JS, LLC.
 * licensing@extjs.com
 *
 * http://extjs.com/license
 */

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
 * Mladen Todorovic <mladen.todorovic@develabs.com>
 *
 * \version
 * SVN: $Id: data-view-plugins.js 4962 2011-05-17 07:22:05Z srdjanv $
 *
 */


Ext.DataView.LabelEditor = function(cfg, field){
    Ext.DataView.LabelEditor.superclass.constructor.call(this,
        field || new Ext.form.TextField({
            allowBlank: false,
            growMin:120,
            growMax:240,
            grow:true,
            selectOnFocus:true
        }), cfg
    );
}

Ext.extend(Ext.DataView.LabelEditor, Ext.Editor, {
    alignment: "tl-tl",
    hideEl : false,
    cls: "x-small-editor",
    id: 'small-editor',
    shim: false,
    completeOnEnter: true,
    cancelOnEsc: true,
    labelSelector: 'span.x-editable',

    init : function(view){
        this.view = view;
        view.on('render', this.initEditor, this);
        this.on('complete', this.onSave, this);
		this.on('canceledit', this.onESC, this);
    },

    initEditor : function(){
        this.view.getEl().on('mousedown', this.onMouseDown, this, {delegate: this.labelSelector});
    },

    onMouseDown : function(e, target){
        if(!e.ctrlKey && !e.shiftKey){
			var wt_panel = Ext.getCmp('wt-panel');
			if (wt_panel._renameFlag){ // if in edit mode and other file is clicked
				this.cancelEdit();
				wt_panel._renameFlag = false;
			}

            var item = this.view.findItemFromChild(target);
            e.stopEvent();
            var record = this.view.store.getAt(this.view.indexOf(item));
//            this.startEdit(target, record.data[this.dataIndex]);
            this.activeRecord = record;
        }
		else{
            e.preventDefault();
        }
    },


//    onMouseDown : function(e, target){
//        if(!e.ctrlKey && !e.shiftKey && e.button == 0){
//	        var item = this.view.findItemFromChild(target);
//	        e.stopEvent();
//			var record = this.view.store.getAt(this.view.indexOf(item));
//			if (this.activeRecord == record) {
//			var nowClickTime = new Date().getTime();
//				if (nowClickTime - this.startClickTime > 500 && nowClickTime - this.startClickTime < 1500) // interval between two clicks for rename
//					this.startEdit(target, record.data[this.dataIndex]);
//				else
//					this.startClickTime = new Date().getTime();
//			}
//			else {
//				this.startClickTime = new Date().getTime();
//				this.cancelEdit();
//				this.activeRecord = record;
//			}
//        }
//		else {
//            e.preventDefault();
//        }
//    },


    onSave : function(ed, value){
		var trimValue =  this.trim(value);
		var newFlag = Ext.getCmp('wt-panel').newNodeFlag;
		var wt_panel = Ext.getCmp('wt-panel');
		var oldValue = this.activeRecord.data.text;

		if(oldValue != trimValue && wt_panel.validateName(trimValue, this.activeRecord.data.iconCls)){
			this.activeRecord.set(this.dataIndex, trimValue);
		}
		else
			wt_panel._renameFlag = false;
    },

	onESC : function(){
		var wt_panel = Ext.getCmp('wt-panel');
		wt_panel._renameFlag = false;
	},

	trim:function(s){
		return s.replace(/^\s+|\s+$/g, '');
	}

});


Ext.DataView.DragSelector = function(cfg){
    cfg = cfg || {};
    var view, regions, proxy, tracker;
    var rs, bodyRegion, dragRegion = new Ext.lib.Region(0,0,0,0);
    var dragSafe = cfg.dragSafe === true;

    this.init = function(dataView){
        view = dataView;
        view.on('render', onRender);
    };

    function fillRegions(){
        rs = [];
        view.all.each(function(el){
            rs[rs.length] = el.getRegion();
        });
        bodyRegion = view.el.getRegion();
    }

    function cancelClick(){
        return false;
    }

    function onBeforeStart(e){
		if (e.button > 0 && e.target == view.el.dom){
			view.clearSelections();
			Ext.getCmp('wt-panel').onContainerContextMenu(e);
			//onContainerContext(e);
		}

		else
        	return !dragSafe || e.target == view.el.dom;
    }

    function onStart(e){
		if (e.button > 0) {
			e.stopEvent();
			return false;
		}
        view.on('containerclick', cancelClick, view, {single:true});
		Jedox.studio.app.inputMode = Jedox.studio.app.inputMode_content_FILES;

        if(!proxy){
            proxy = view.el.createChild({cls:'x-view-selector'});
        }else{
			proxy = view.el.createChild({cls:'x-view-selector'});
//            proxy.setDisplayed('block');
        }
        fillRegions();
        view.clearSelections();
    }

    function onDrag(e){
        var startXY = tracker.startXY;
        var xy = tracker.getXY();

        var x = Math.min(startXY[0], xy[0]);
        var y = Math.min(startXY[1], xy[1]);
        var w = Math.abs(startXY[0] - xy[0]);
        var h = Math.abs(startXY[1] - xy[1]);

        dragRegion.left = x;
        dragRegion.top = y;
        dragRegion.right = x+w;
        dragRegion.bottom = y+h;

        dragRegion.constrainTo(bodyRegion);
        proxy.setRegion(dragRegion);

        for(var i = 0, len = rs.length; i < len; i++){
            var r = rs[i], sel = dragRegion.intersect(r);
            if(sel && !r.selected){
                r.selected = true;
                view.select(i, true);
            }else if(!sel && r.selected){
                r.selected = false;
                view.deselect(i);
            }
        }
    }

    function onEnd(e){
        if(proxy){
            proxy.setDisplayed(false);
        }
    }

    function onRender(view){
        tracker = new Ext.dd.DragTracker({
            onBeforeStart: onBeforeStart,
            onStart: onStart,
            onDrag: onDrag,
            onEnd: onEnd
        });
        tracker.initEl(view.el);
    }
};