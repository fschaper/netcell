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
 *  Marko Stijak <marko.stijak@jedox.com>
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once
#include "zpackage.hpp"

#include "persistent_styles.hpp"
#include "shared_strings.hpp"
#include "persistent_defined_names.hpp"

#include "relations.hpp"
#include "content_types.hpp"

#include <xio/optional.hpp>
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#include <boost/filesystem/path.hpp>
#endif

#include <vector>

#include <oxml/sml-workbook_serializer.hpp>
#include <oxml/sml-sheet_serializer.hpp>
#include <oxml/sml-sharedStringTable_serializer.hpp>
#include <oxml/sml-styles_serializer.hpp>
#include <oxml/dml-spreadsheetDrawing.hpp>
#include <oxml/custom_data_serializer.hpp>

#include "wss/range.hpp"
#include "wss/worksheet.hpp"

namespace xlsx
{
    namespace sml = spreadsheetml;
    namespace dml = drawingml;

    class xlsx_export_filter
        :   private ::xio::xml::binding::serializer
    {
    private:
        static const int                    VERSION_HI = 1;
        static const int                    VERSION_LO = 8;
        persistent_styles                   m_styles;
        persistent_defined_names            m_defined_names;
        shared_strings                      m_shared_strings;

        export_helpers::relations           m_doc_rels;
        export_helpers::relations           m_wb_rels;
        export_helpers::content_types       m_doc_ctypes;
        boost::filesystem::path             m_export_file;
        unsigned int                        m_pic_id;

        std::map<std::string, std::string> array_formula_master_cells; //used for master array formulas
        bool                                m_is_native;

        sheet_point::integer_type           m_min_style_col;
        sheet_point::integer_type           m_max_style_col;

        sheet_point::integer_type           m_min_val_col;
        sheet_point::integer_type           m_max_val_col;

        std::vector<size_t>                 m_full_cols;
        std::vector< range >                m_hyperlink_cells;
    private:
        void stamp_default_height( const shared_worksheet_type& ws, sml::CT_SheetFormatPr& out_sfpr );

        void init_relations();
        void store_core_properties( std::ostream& os );
        void store_extended_properties( std::ostream& os );
        void write_globals( package::opackage& package );
        void clear();
        void set_dummy_styles();
        void internal_export( session& s, workbook& wb, package::opackage& package, const bool as_snapshoot = false );
        bool add_row( session& s, sml::CT_Row& out_row, const shared_worksheet_type& ws, const sheet_point::integer_type row, const sheet_point::integer_type min_col, const sheet_point::integer_type max_col, const std::map<sheet_point, bool>& all_val_cells, const bool as_snapshoot = false );
        void do_one_worksheet( session& s, sml::CT_Sheets& sheets, int sheet_id, const shared_worksheet_type& ws, package::opackage& package, const bool as_snapshoot = false );
        void translate_worksheetelements( session& s, sml::CT_Worksheet& out_ws, int sheet_id, const shared_worksheet_type& ws, package::opackage& package, export_helpers::relations& sheet_rels );
        void process_conditional_formats( session& s, const shared_worksheet_type& ws, sml::CT_Worksheet& out_ws );
        void process_merged_cells( const shared_worksheet_type& ws, sml::CT_Worksheet& out_ws );
    public:
        /*!
         * \brief
         * implements the export_filter interface for xlsx files
         *
         * \see
         * i_export_filter
         *
         * \author
         * Radu Ialovoi <ialovoi@yalos-solutions.com>
         */
#ifdef _WIN32
# pragma warning( disable : 4290 )
#endif
        void do_export( session& s, workbook& wb, const boost::filesystem::path& out_file, const bool as_snapshoot = false, const bool is_native = true );
#ifdef _WIN32
# pragma warning( default : 4290 )
#endif
    };
}
