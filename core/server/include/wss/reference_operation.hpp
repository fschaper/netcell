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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */
#pragma once

#include <wss/type.hpp>

#include <wss/range_reference.hpp>
#include <wss/named_formula_reference.hpp>
#include <wss/invalid_reference_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0
typedef boost::unordered_set<i_dependency*> raw_dependency_set_type;
/*!
 * \brief
 * forwards contained shared_dependency_type's to the passed callback function
 * based on the type of reference.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<class operation_T>
inline void reference_operation( const shared_dependency_type& issueing_dependency, const shared_reference_type& sr, dependency_set_type& collected_dependencies, const operation_T& op, const bool ignore_invalid_references, raw_dependency_set_type& visited_nfs )
{
#ifdef _DEBUG
    assert( "uninitialized reference passed to 'reference_operation'!" && sr );
#endif // _DEBUG
    switch ( sr->type() ) {
        case i_dependency_reference::range_reference: {
            range_reference::actual rra = range_reference_cast( sr ).actualize();
            if ( rra.is_valid() ) {
                const dependency_set_type& deps = *( rra->lock() );
                collected_dependencies.insert( deps.begin(), deps.end() );
            }
            break;
        }
        case i_dependency_reference::named_formula_reference: {
            if ( named_formula_reference_cast( sr ).is_valid() ) {
                if ( shared_dependency_type nf =  named_formula_reference_cast( sr ).real_nf() ) {
                    if ( visited_nfs.insert( nf.get() ).second ) {
                        reference_operation( issueing_dependency, nf->precedents( issueing_dependency ), op, ignore_invalid_references, collected_dependencies, visited_nfs );
                    }
                }
            }
        }
        break;
        default:
            assert( ! "unsupported reference type in precedents_walker!" );
    }
}

/*!
 * \brief
 * calls a reference operation for every shared_reference in the referencetable_type.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<class operation_T>
void reference_operation( const shared_dependency_type& issueing_dependency, const referencetable_type& references, const operation_T& op, const bool ignore_invalid_references = false )
{
    if ( !references.empty() ) {
        dependency_set_type collected_dependencies;
        raw_dependency_set_type visited_nfs;
        reference_operation( issueing_dependency, references, op, ignore_invalid_references, collected_dependencies, visited_nfs );
        std::for_each( collected_dependencies.begin(), collected_dependencies.end(), const_cast<operation_T&>( op ) );
    }
}

template<class operation_T>
void reference_operation( const shared_dependency_type& issueing_dependency, const referencetable_type& references, const operation_T& op, const bool ignore_invalid_references, dependency_set_type& collected_dependencies, raw_dependency_set_type& visited_nfs )
{
    referencetable_type::const_iterator it( references.begin() ), end_it( references.end() );
    for ( ; it != end_it; ++it ) {
        // (fhofmann) changed this to ignore null pointers, because ref errors are stored that way
        if ( !( *it ) ) {
            continue;
        }
#ifdef _DEBUG
        try {
#endif // _DEBUG
            reference_operation( issueing_dependency, *it, collected_dependencies, op, ignore_invalid_references, visited_nfs );

#ifdef _DEBUG
        } catch ( const invalid_reference_exception& e ) {
            assert( !"tried to access uninitialized or invalidated reference in 'reference_operation'!" );
        }
#endif // _DEBUG
    }
}

template<class operation_T>
void reference_operation_for_stack_calculation( const shared_dependency_type& issueing_dependency, const referencetable_type& references, const operation_T& op, const bool ignore_invalid_references = false )
{
    if ( !references.empty() ) {
        dependency_set_type collected_dependencies;
        raw_dependency_set_type visited_nfs;
        referencetable_type::const_iterator it( references.begin() ), end_it( references.end() );
        for ( ; it != end_it; ++it ) {
            // (fhofmann) changed this to ignore null pointers, because ref errors are stored that way
            if ( !( *it ) ) {
                continue;
            }
#ifdef _DEBUG
            try {
#endif // _DEBUG
                reference_operation( issueing_dependency, *it, collected_dependencies, op, ignore_invalid_references, visited_nfs );

#ifdef _DEBUG
            } catch ( const invalid_reference_exception& e ) {
                assert( !"tried to access uninitialized or invalidated reference in 'reference_operation'!" );
            }
#endif // _DEBUG
        }

        std::for_each( collected_dependencies.begin(), collected_dependencies.end(), boost::bind( &operation_T::operator(), boost::ref( const_cast<operation_T&>( op ) ), _1  ) );
    }
}
