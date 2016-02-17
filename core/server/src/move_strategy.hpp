/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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

#include "wss/sheet_range.hpp"
#include <vector>

#include "i_lookup_callback_strategy.hpp"

class dependency_node;

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class move_node_info
{
public:
    move_node_info( dependency_node* p, const sheet_range& position )
        : m_node( p )
        , m_new_position( position ) {}

    dependency_node* node() const {
        return m_node;
    }

    const sheet_range& position() const {
        return m_new_position;
    }

private:
    dependency_node* m_node;
    sheet_range m_new_position;
};

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class move_strategy
    : public rectangle_container::i_lookup_callback_strategy
{
public:
    typedef std::vector<move_node_info> node_info_block_type;

    move_strategy( const sheet_range& move_range, const sheet_point& target, node_info_block_type& block );

    /*!
     * \brief
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual bool operator()( rectangle_container::rectangle_node& n ) const;

private:
    const sheet_range& m_selection_range;
    const sheet_point& m_target;
    node_info_block_type& m_node_info_block;
};
