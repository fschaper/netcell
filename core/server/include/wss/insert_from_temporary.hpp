/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#include <boost\unordered\unordered_set.hpp>
#endif

/*!
 * \brief
 * specializations for std::set and boost::unordered_set
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<class object_T, class temp_T>
void insert_from_temporary( std::set<object_T>& v, const temp_T& i  )
{
    v.insert( i.begin(), i.end() );
}

template<class object_T, class temp_T>
void insert_from_temporary( boost::unordered_set<object_T>& v, const temp_T& i  )
{
    v.insert( i.begin(), i.end() );
}

/*!
 * \brief
 * insert values from temporary objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class object_T, class temp_T>
void insert_from_temporary( object_T& v, const temp_T& i  )
{
    v.insert( v.end(), i.begin(), i.end() );
}
