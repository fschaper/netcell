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

#include "styles_agregator.hpp"
#include <wss/range.hpp>

namespace xlsx
{

    void styles_agregator::compute( session& s, const shared_worksheet_type& ws, persistent_styles& styles )
    {
        optional_sheet_range_type used_range = ws->used_range( used_range::all );

        m_rows.clear();
        m_cols.clear();

        if ( used_range ) {
            const sheet_point&                                  ul = used_range->upper_left();
            const sheet_point&                                  lr = used_range->lower_right();

            for ( sheet_point::integer_type row =  ul.row(); row <= lr.row(); row++ ) {
                int style = row_style( s, ws, row, styles );
                if ( -1 != style ) {
                    m_rows.push_back( entry_type( row, style ) );
                }
            }


            for ( sheet_point::integer_type col =  ul.column(); col <= lr.column(); col++ ) {
                int style = col_style( s, ws, col, styles );
                if ( -1 != style ) {
                    m_cols.push_back( entry_type( col, style ) );
                }
            }
        }
    }

    int  styles_agregator::extract_row( sheet_point::integer_type row )
    {
        for ( std::vector< entry_type >::iterator crt = m_rows.begin(); crt != m_rows.end(); crt++ ) {
            if ( crt->first == row ) {
                int result = crt->second;
                m_rows.erase( crt );
                return result;
            }
        }

        return -1;
    }

    int  styles_agregator::test_col( sheet_point::integer_type col )
    {
        for ( std::vector< entry_type >::const_iterator crt = m_cols.begin(); crt != m_cols.end(); crt++ ) {
            if ( crt->first == col ) {
                return crt->second;
            }
        }

        return -1;
    }

    int styles_agregator::row_style( session& s, const shared_worksheet_type& ws, const int row, persistent_styles& styles )
    {
        sparse_vector<variant>  def_style = ws->range( sheet_range( sheet_point( row, sheet_dimension::max_column ) ) ).style( s, true );
        if ( !def_style.empty() ) {
            const variant& def = *def_style.begin();
            return styles.register_style( def.as_string( s.locale() ) );
        }

        return -1;
    }

    int styles_agregator::col_style( session& s, const shared_worksheet_type& ws, const int col, persistent_styles& styles )
    {
        sparse_vector<variant>  def_style = ws->range( sheet_range( sheet_point( sheet_dimension::max_row, col ) ) ).style( s, true );
        if ( !def_style.empty() ) {
            const variant& def = *def_style.begin();
            return styles.register_style( def.as_string( s.locale() ) );
        }

        return -1;
    }

}
