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

#pragma once

/*!
 * \brief
 * wrapper treat pointer to pointer as reference.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class contained_T>
class as_reference
{
public:
    typedef contained_T type;

    explicit as_reference( contained_T*& p )
        : m_ptr( &p ) {}

    operator contained_T& () const {
        return **m_ptr;
    }

private:
    contained_T** m_ptr;
};

/*!
 * \brief
 * wrapper treat pointer to pointer as reference.
 *
 * helper function for automatic type deduction.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class pointer_T>
inline as_reference<pointer_T> ref_pointer( pointer_T*& ptr )
{
    return as_reference<pointer_T>( ptr );
}
