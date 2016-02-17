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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

template<class derived_T>
template<class other_T>
inline derived_T generic_point<derived_T>::distance( const other_T& other ) const
{
    return derived_T( ( other.row() - row() ), ( other.column() - column() ) );
}

template<class derived_T>
template<class other_T>
inline derived_T generic_point<derived_T>::offset( const other_T& other ) const
{
    return offset( other.row(), other.column() );
}

template<class derived_T>
template<class other_T>
inline derived_T generic_point<derived_T>::offset_move_absolute_references( const other_T& other ) const
{
    return offset_move_absolute_references( other.row(), other.column() );
}

template<class derived_T>
template<class other_T>
inline derived_T generic_point<derived_T>::checked_offset( const other_T& other ) const
{
    return checked_offset( other.row(), other.column() );
}

template<class derived_T>
template<bool move_absolute_references, class sheet_dimensionT, class other_T>
inline derived_T generic_point<derived_T>::cyclic_offset( const other_T& other ) const
{
    return cyclic_offset<move_absolute_references, sheet_dimensionT>( other.row(), other.column() );
}

template<class derived_T>
std::ostream& operator <<( std::ostream& os, const generic_point<derived_T>& p )
{
    os << "[" << p.row() << "," << p.column() << "]";
    return os;
}
