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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *
 */

#include "precompiled_header.hpp"
#include "named_formula_storage.hpp"

template<bool check_for_better_fit>
void adjust_dependencies::remove_if_not_set_update_wrapper_if_better_fit( nf::shared_storage_node& node, const shared_named_formula_wrapper_type& nf )
{
    if ( nf::shared_ptr_to_reference_set_type srs = node->shared_references.lock() ) {
        nf::reference_set_type::left_iterator it( srs->left.begin() );
        while ( it != srs->left.end() ) {
            shared_reference_type ref( it->info.lock() );
            if ( ! ref ) {
                srs->left.erase( it++ );
            } else {
                if ( !check_for_better_fit || !boost::shared_static_cast<named_formula_reference>( ref )->is_valid() || boost::shared_static_cast<named_formula_reference>( ref )->better_fit( nf ) ) {
                    boost::shared_static_cast<named_formula_reference>( ref )->update_wrapper( nf );
                    node->own_references.insert( nf::reference_set_type::value_type( it->get_left(), it->get_right(), it->info ) );
                    srs->left.erase( it++ );
                } else {
                    ++it;
                }
            }
        }
    }
}

void adjust_dependencies::adjust_references( nf::shared_storage_node& source_node, const shared_named_formula_wrapper_type& nf, const bool check_redirect )
{
    remove_if_not_set_update_wrapper_if_better_fit<true>( source_node, nf );
}

void adjust_dependencies::adjust_references( nf::shared_storage_node& source_node, nf::shared_storage_node& target_node, const shared_named_formula_wrapper_type& nf, const bool check_redirect )
{
    remove_if_not_set_update_wrapper_if_better_fit<true>( source_node, nf );
    if ( source_node != target_node ) {
        nf::reference_set_type::left_iterator it( source_node->own_references.left.begin() );
        while ( it != source_node->own_references.left.end() ) {
            shared_reference_type ref( it->info.lock() );
            if ( ! ref ) {
                source_node->own_references.left.erase( it++ );
            } else if ( ( ! boost::shared_static_cast<named_formula_reference>( ref )->is_valid() ) ||  boost::shared_static_cast<named_formula_reference>( ref )->better_fit( nf ) ) {
                boost::shared_static_cast<named_formula_reference>( ref )->update_wrapper( nf );
                target_node->own_references.insert( nf::reference_set_type::value_type( it->get_left(), it->get_right(), it->info ) );
                source_node->own_references.left.erase( it++ );
            } else {
                ++it;
            }
        }
    }
}

void adjust_dependencies::get_dangling_references( nf::shared_storage_node& node )
{
    remove_if_not_set_update_wrapper_if_better_fit<false>( node, node->nf_wrapper );
}

void adjust_dependencies::adjust_references( nf::ws_nf_map_type& ws_nf_set, const shared_named_formula_wrapper_type& nf )
{
    nf::ws_nf_map_type::iterator it( ws_nf_set.begin() ), end_it( ws_nf_set.end() );
    for ( ; it != end_it; ++it ) {
        adjust_references( it->second, nf );
    }
}

void adjust_dependencies::adjust_references( nf::ws_nf_map_type& ws_nf_set, nf::shared_storage_node& target_node, const shared_named_formula_wrapper_type& nf )
{
    nf::ws_nf_map_type::iterator it( ws_nf_set.begin() ), end_it( ws_nf_set.end() );
    for ( ; it != end_it; ++it ) {
        adjust_references( it->second, target_node, nf );
    }
}

const size_t nf::storage_root_node::clear_expired_references_counter_max = 1000;
