/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *    http://www.jedox.com/license_palo_bi_suite.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include "optional.hpp"
#include "zpackage.hpp"
#include "relations.hpp"
#include <oxml/dml-spreadsheetDrawing.hpp>
#include <wss/sheet_layout_manager.hpp>

class variant;
class session;
class worksheet_element;

namespace xlsx
{
    namespace dml = drawingml;

    typedef std::string key_type;
    typedef std::vector< key_type> key_vec_type;
    typedef variant value_type;
    typedef std::pair< key_type, value_type > key_value_type;
    typedef std::vector< key_value_type > key_value_vector_type;

    class persistent_drawing
    {
    private:
        struct persistent_marker {
            struct axis_coord {
                unsigned int pos;
                long offset;
            };
            axis_coord row;
            axis_coord col;
            void load( const dml::CT_Marker& src );
            void save( dml::CT_Marker& src );
        };

        struct persistent_two_cell_anchor {
        private:
            persistent_marker from;
            persistent_marker to;

            struct persistent_picture {
                unsigned int id;
                std::string name;
                std::string description;
                std::string relID;
                std::string img_type;
                optional< drawingml::CT_Hyperlink > hlinkClick;
                void deserialize( package::izpackage& package, export_helpers::relations& rels, key_value_vector_type& vals );
                void serialize( session& s, package::opackage& package, export_helpers::relations& rels, worksheet_element& wselt );
            };
            optional < persistent_picture > picture;
            bool nomove;

            sheet_point compute_geometry(
                sheet_layout_manager& layout,
                const sheet_point& top_left,
                const unsigned int width,
                const unsigned int height,
                unsigned int& bottom_row_offset,
                unsigned int& bottom_col_offset );
        public:
            unsigned int id;
            void load( const dml::CT_TwoCellAnchor& src );
            void save( dml::CT_TwoCellAnchor& src );

            void deserialize( session& s, package::izpackage& package, export_helpers::relations& rels, worksheet_element& wselt, sheet_layout_manager& layout, unsigned int zorder );
            void serialize( session& s, package::opackage& package, export_helpers::relations& rels, worksheet_element& wselt, sheet_layout_manager& layout );

            std::string media_type();
        };

        persistent_two_cell_anchor  two_cell_anchor;

        export_helpers::relations& rels;
        unsigned int id;
    public:
        persistent_drawing( const dml::CT_TwoCellAnchor& src, export_helpers::relations& rels, unsigned int id = 0 );
        void load( const dml::CT_TwoCellAnchor& src );
        void save( dml::CT_TwoCellAnchor& dst );

        void deserialize( session& s, package::izpackage& package, worksheet_element& wselt, sheet_layout_manager& layout, unsigned int zorder  );
        void serialize( session& s, package::opackage& package, worksheet_element& wselt, sheet_layout_manager& layout );

        std::string media_type();
    };

}
