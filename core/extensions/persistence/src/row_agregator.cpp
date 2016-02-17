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

#include "row_agregator.hpp"

namespace xlsx
{
    row_agregator::interval::interval( int min, int max, int style_id ) : min( min ), max( max ), style_id( style_id )
    {
    }

    void row_agregator::register_style( const int col, const int style_id )
    {
        if ( 0 == style_id ) {
            return;
        }

        if ( m_row.empty() ) {
            m_row.push_back( interval( col, col, style_id ) );
            return;
        }

        interval& tail = m_row[m_row.size()-1];

        if ( col - 1 == tail.max && style_id == tail.style_id ) {
            tail.max = col;
        } else {
            m_row.push_back( interval( col, col, style_id ) );
        }
    }

    void row_agregator::clear()
    {
        m_row.clear();
    }

    row_agregator::row_data_vector::const_iterator row_agregator::begin()
    {
        return m_row.begin();
    }

    row_agregator::row_data_vector::const_iterator row_agregator::end()
    {
        return m_row.end();
    }

}
