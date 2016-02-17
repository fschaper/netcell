/**
 *  \file
 *  Copyright (C) 2006-2008 Jedox AG, Freiburg i.Br., Germany
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *   by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
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
 *   You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#include "FormattedCell.hpp"

namespace cell_format
{
#ifdef _DEBUG
    /*! debug output  */
    std::ostream& operator<<( std::ostream& ostr, const FormattedCell& fc )
    {
        ostr << fc.value << " [" << fc.color << ", "
             << "(pad: " << fc.padding.idx << "/"
             << ( fc.padding.idx == static_cast<size_t>( -1 ) ?  ' ' : fc.padding.value )
             << ", spaces:";

        for ( FormattedCell::MeasuredSpaces::const_iterator i = fc.spacing.begin(); i != fc.spacing.end(); ++i ) {
            ostr << " " << i->idx << '/' << i->width;
        }

        return ostr << ")]";
    }
#endif // _DEBUG
}
