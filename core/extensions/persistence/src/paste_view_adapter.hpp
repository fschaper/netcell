/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#ifdef _MSC_VER
# pragma warning ( disable : 4244 ) // 'include\boost\iostreams
# pragma warning (push, 2)
#endif

#include <oxml/sml-sheet.hpp>

#include "shared_strings.hpp"
#include <wss/variant.hpp>
#include <wss/a1conversion.hpp>

namespace xlsx
{
    namespace sml = spreadsheetml;

    class paste_view_adapter
    {
    private:
        struct ename_with_pos {
            std::string name;
            unsigned int row;
            unsigned int col;
            ename_with_pos( const std::string& name, const unsigned int row, const unsigned int col ) : name( name ), row ( row ), col ( col ) {};
        };

        struct match_point {
            const unsigned int row;
            const unsigned int col;
            match_point( const unsigned int row, const unsigned int col ) : row ( row ), col ( col ) {};
            bool operator ()( const ename_with_pos& other ) {
                return ( row == other.row && col == other.col );
            }
        };

        enum detection_state {
            ds_idle,
            ds_data_source,
            ds_cube,
            ds_axes,
            ds_valid,
            ds_fail
        };

        detection_state                 m_state;
        unsigned int                    m_max_row;
        unsigned int                    m_max_col;
        shared_strings&                 m_strings;
        std::vector< ename_with_pos >   m_enames;

        std::vector< std::vector< ename_with_pos >  >   m_x_axis;
        std::vector< std::vector< ename_with_pos >  >   m_y_axis;

        std::vector< ename_with_pos >   m_page;

        unsigned int                    m_right;
        unsigned int                    m_bottom;

        std::string                     m_connection;
        std::string                     m_database;
        std::string                     m_cube;

        std::string                     m_payload;

        variant                         m_encoded_payload;

        std::string                     m_fixed_width;

        detection_state advance_from_idle( const int row, const int col, const sml::CT_Cell& cell );
        detection_state advance_from_data_source( const int row, const int col, const sml::CT_Cell& cell );
        detection_state advance_from_cube( const int row, const int col, const sml::CT_Cell& cell );

        void cast_table();

        const std::string quote( const std::string& label );
        const std::string serialize_label( const ename_with_pos& label );
        const std::string serialize_pages( const std::vector< ename_with_pos >& axis );
        const std::string serialize_axis( const std::vector< std::vector< ename_with_pos > >& meta_axis );

        const std::string& serialize();
    public:
        paste_view_adapter( shared_strings& strings, const sml::CT_Workbook& in_book, const utf8_ci_string& sheet_name );

        bool active();
        void visit( const int row, const int col, const sml::CT_Cell& cell );
        bool validate();

        const variant& encoded_payload();
        const std::string location();
        const sheet_range pivot();
        const std::vector< sheet_point > enames() const;
    };

}
