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
 * iterates over the AST using an bottom-up approach.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class visitor_T
, class node_T
, bool use_lazy_evaluation = false
>
class bottom_top_visitor;

/*!
 * \brief
 * iterates over the AST using an bottom-up approach.
 *
 * \remarks
 * skips nodes that are marked for lazy evaluation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class visitor_T
, class node_T
>
class bottom_top_visitor<visitor_T, node_T, true>
{
public:
    void operator()( node_T& node ) {
        if ( node.has_children() && node.lazy_evaluation() == false ) {
            typename node_T::shallow_iterator current( node.begin_shallow() );
            typename node_T::shallow_iterator end( node.end_shallow() );
            for ( ; current != end; ++current ) {
                ( *this )( *current );
            }
        }
        node.accept( static_cast<visitor_T&>( *this ) );
    }
};

/*!
 * \brief
 * iterates over the AST using an bottom-up approach.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class visitor_T
, class node_T
>
class bottom_top_visitor<visitor_T, node_T, false>
{
public:
    void operator()( node_T& node ) {
        if ( node.has_children() ) {
            typename node_T::shallow_iterator current( node.begin_shallow() );
            typename node_T::shallow_iterator end( node.end_shallow() );
            for ( ; current != end; ++current ) {
                ( *this )( *current );
            }
        }
        node.accept( static_cast<visitor_T&>( *this ) );
    }
};
