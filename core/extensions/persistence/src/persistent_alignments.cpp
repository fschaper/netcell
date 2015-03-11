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

#include "persistent_alignments.hpp"
#include "string_utils.hpp"

namespace xlsx
{
    int persistent_alignments::register_alignment( const ssmap& props )
    {
        std::string key = string_utils::combine( props );
        std::map<std::string, int>::iterator fit = m_align_map.find( key );
        if ( fit != m_align_map.end() ) {
            return fit->second;
        }

        int i = ( int )m_aligns.size();
        m_aligns.push_back( persistent_alignment( props ) );
        m_align_map[key] = i;
        return i;
    }

    const persistent_alignment& persistent_alignments::at( const size_t idx ) const
    {
        return m_aligns.at( idx );
    }

    const std::string persistent_alignments::str( const size_t idx ) const
    {
        return m_aligns.at( idx ).str();
    }

    void persistent_alignments::clear()
    {
        m_aligns.clear();
        m_align_map.clear();
    }
}
