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

#include <wss/type.hpp>
#include <wss/sheet_range.hpp>
#include <wss/variant.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <map>
#endif

class range_reference;
class interpreter_context;

/*!
 * \brief
 * treats a range reference as an sparse array.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE sparse_range_array
{
    typedef std::map<unsigned int, shared_dependency_type> container_type;
public:
    typedef container_type::size_type size_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_range_array( range_reference& rr, interpreter_context& ic );

    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_range_array( const sparse_range_array& other );

    /*!
     * \brief
     * range size
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type size() const;

    /*!
     * \brief
     * range width
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type width() const;

    /*!
     * \brief
     * range position
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const sheet_range& position() const;

    /*!
     * \brief
     * direct access to the range element identified by 'x' and 'y'
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator ()( unsigned int x, unsigned int y ) const;

    /*!
     * \brief
     * linear access to the range element identified by it's ordinal.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator []( unsigned int index ) const;

private:
    container_type m_sparse_map;
    interpreter_context& m_ic;
    sheet_range m_position;
};


