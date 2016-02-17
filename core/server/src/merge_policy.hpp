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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include "wss/rectangle.hpp"

namespace rectangle_container
{
    class rectangle_node;

    namespace policy
    {

        namespace custom_merge
        {

            /*!
            * \brief
            * no merge policy to be used with rectangle_container
            *
            * \see rectangle_container
            * \author
            * Frieder Hofmann <frieder.hofmann@jedox.com>
            */
            class no_merge_policy
            {
            public:
                inline bool check_merge( const rectangle_node&, const rectangle_node& ) const {
                    return false;
                }

                inline bool do_merge( rectangle_node& lhs, const rectangle_node& rhs ) const {
                    return false;
                }
            };

            /*!
            * \brief
            * simple merge policy to be used with rectangle_container
            *
            * \see rectangle_container
            * \author
            * Frieder Hofmann <frieder.hofmann@jedox.com>
            */
            class simple_merge_policy
            {
            public:
                /*!
                * \brief
                * will be called when inserting for every two nodes that either overlap
                * and have the same border or are adjacent to each other
                * the operator== should be overloaded in the node_type
                *
                * \param const rectangle_node& rhs
                * node that will be compared to lhs and if true is returned they will be merged
                *
                * \param const rectangle_node& lhs
                * node that will be compared to rhs and if true is returned they will be merged
                *
                * \returns
                * true if the two nodes should be merged, false otherwise.
                *
                * \author
                * Frieder Hofmann <frieder.hofmann@jedox.com>
                */
                inline bool check_merge( const rectangle_node& lhs, const rectangle_node& rhs ) const {
                    return lhs == rhs;
                }

                /*!
                * \brief
                * will be called for every two nodes that need to be merged
                *
                * \param const rectangle_node& lhs
                * node that will be merged with rhs (lhs will be merged into lhs, and lhs will be the resulting node)
                *
                * \param const rectangle_node& rhs
                * node that will be merged with lhs (note this node should be removed afterwards)
                *
                * \returns
                * true if the two nodes were successfully merged, false otherwise.
                * if true was returned, rhs should be added at the top node again and lhs should be removed
                *
                * \author
                * Frieder Hofmann <frieder.hofmann@jedox.com>
                */
                inline bool do_merge( rectangle_node& lhs, const rectangle_node& rhs ) const {
                    //this is a really simple merge, that will just combine the two rectangles into a bigger one
                    lhs.rectangle( lhs.rectangle().enclose( rhs.rectangle() ) );
                    return true;
                }
            };
        }
    }
}
