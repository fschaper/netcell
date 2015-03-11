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
#include "persistent_theme.hpp"
#include "persistent_styles.hpp"
#include "shared_strings.hpp"
#include "persistent_defined_names.hpp"
#include "paste_view_adapter.hpp"
#include "zpackage.hpp"
#include "persistent_version_info.hpp"
#include "row_agregator.hpp"

#include <xio/optional.hpp>
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#include <boost/filesystem/path.hpp>
#endif

#include <oxml/sml-workbook.hpp>
#include <oxml/sml-workbook_parser.hpp>
#include <oxml/sml-sheet.hpp>
#include <oxml/sml-sheet_parser.hpp>
#include <oxml/relationships_parser.hpp>
#include <oxml/custom_data_parser.hpp>
#include <oxml/dml-spreadsheetDrawing.hpp>
#include <oxml/dml-spreadsheetDrawing_parser.hpp>

namespace xlsx
{

    class xlsx_import_filter : private ::xio::xml::binding::parser
    {
    private:
        struct shared_formula {
            int r;
            int c;
        };

        persistent_styles                   m_styles;
        persistent_defined_names            m_defined_names;
        shared_strings                      m_shared_strings;
        persistent_theme                    m_theme;
        std::vector< shared_formula >       m_shared_formulas;
        std::set<std::string>               m_blocked_cells;
        persistent_version_info             m_version_info;
        locked_import_progress_list         m_import_progress_list;
        std::auto_ptr< paste_view_adapter > m_paste_view_adapter;
        bool                                m_is_native;
        row_agregator                       m_row_agregator;

        shared_workbook_type internal_import( session& s, application& a, package::izpackage& package, const boost::filesystem::path& in_file );
        bool internal_extended_data_import( session& s, application& a, package::izpackage& package, const boost::filesystem::path& in_file );
        void process_worksheet( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet, const sml::CT_Workbook& in_book );
        void do_one_row( session& s, shared_worksheet_type& ws, const sml::CT_Row& row, std::list<geometry::rectangle_type>& array_cell_ranges );
        void do_one_cell( session& s, shared_worksheet_type& ws, const sml::CT_Cell& cell, std::list<geometry::rectangle_type>& array_cell_ranges );
        void merge_cells( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet  );
        void do_cf( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet  );
        void import_defined_names( session& s, shared_workbook_type& wb, const xio::poptional< sml::CT_DefinedNames >& in_names, const std::vector< std::string > sheet_names );
        void add_worksheet_drawings( session& s, const size_t idx, package::izpackage& package, shared_worksheet_type& ws, const sml::CT_Drawing& in_sheet );
        void translate_hyperlinks( session& s, shared_worksheet_type& ws, const sml::CT_Worksheet& in_sheet );
    public:
        /*!
         * \brief
         * implements the import_filter interface for xlsx files
         *
         * \see
         * i_import_filter
         *
         * \author
         * Radu Ialovoi <ialovoi@yalos-solutions.com>
         */
#ifdef _WIN32
# pragma warning( disable : 4290 )
#endif
        shared_workbook_type do_import( session& s, application& a, const boost::filesystem::path& in_file, const bool is_native = true );
        bool extended_data_import( session& s, application& a, const boost::filesystem::path& in_file );
        std::vector<std::string> get_progress_list();
#ifdef _WIN32
# pragma warning( default : 4290 )
#endif
    };

}
