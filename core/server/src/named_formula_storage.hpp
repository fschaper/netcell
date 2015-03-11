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

#include "wss/type.hpp"
#include "wss/worksheet.hpp"
#include "wss/named_formula_reference.hpp"
#include "named_formula.hpp"
#include "named_formula_wrapper.hpp"
#include "named_formula_utility.hpp"
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/multi_index_container.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/named_formula_not_found_exception.hpp"
#include "wss/named_formula_exception.hpp"

#ifndef _DEBUG
#include <boost/unordered/unordered_set.hpp>
#include <boost/unordered/unordered_map.hpp>
#endif
#include "wss/session_sheet_map.hpp"

using namespace named_formula_utils;

class named_formula_manager;
class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;
typedef boost::weak_ptr<named_formula> weak_named_formula_type;


namespace nf
{
    struct storage_node;
    typedef boost::shared_ptr<storage_node> shared_storage_node;
    struct storage_root_node;
    typedef boost::shared_ptr<storage_root_node> shared_storage_root_node;

    typedef boost::weak_ptr<i_dependency_reference> weak_named_formula_reference;
    typedef boost::shared_ptr<i_dependency_reference> shared_reference_type;
    namespace bbm = boost::bimaps;
    typedef bbm::bimap<bbm::unordered_set_of<i_dependency_reference*>, bbm::unordered_set_of<i_dependency*>, bbm::with_info<weak_named_formula_reference> > reference_set_type;

    //typedef std::set<weak_named_formula_reference> reference_set_type;
    typedef boost::shared_ptr<reference_set_type> shared_ptr_to_reference_set_type;
    typedef boost::weak_ptr<reference_set_type> weak_ptr_to_reference_set_type;
    typedef map_to_use<uuid_type, shared_storage_node>::type ws_nf_map_type;

} //namespace nf



class adjust_dependencies : non_instantiable
{
public:

    template<class D>
    static void register_dependents( const D& target, const shared_locked_dependency_type& source );

    template<class D>
    static void register_dependents( const D& target, const nf::reference_set_type& source );

    static void adjust_references( nf::shared_storage_node& node, const shared_named_formula_wrapper_type& nf, const bool check_redirect = false );
    static void adjust_references( nf::shared_storage_node& node, nf::shared_storage_node& target_node, const shared_named_formula_wrapper_type& nf, const bool check_redirect = false );

    static void adjust_references( nf::ws_nf_map_type& ws_nf_set, const shared_named_formula_wrapper_type& nf );
    static void adjust_references( nf::ws_nf_map_type& ws_nf_set, nf::shared_storage_node& target_node, const shared_named_formula_wrapper_type& nf );

    static void get_dangling_references( nf::shared_storage_node& node );
    template<bool check_for_better_fit>
    static void remove_if_not_set_update_wrapper_if_better_fit( nf::shared_storage_node& node, const shared_named_formula_wrapper_type& nf );
};

namespace nf
{

    struct storage_node
            : public boost::noncopyable {

        storage_node( const shared_ptr_to_reference_set_type& references )
            : nf_wrapper( new named_formula_wrapper() )
            , shared_references( references ) {}

        storage_node( shared_named_formula_type nf, const shared_ptr_to_reference_set_type& references )
            : nf_wrapper( new named_formula_wrapper( nf ) )
            , shared_references( references ) {}

        ~storage_node() {
            reference_set_type::left_iterator it( own_references.left.begin() ), end_it( own_references.left.end() );
            for ( ; it != end_it; ++it ) {
                if ( shared_reference_type snf = it->info.lock() ) {
                    boost::shared_static_cast<named_formula_reference>( snf )->unload();
                }
            }
        }

        inline void unload() {
            if ( nf_wrapper ) {
                nf_wrapper->unload();
            }
        }

        inline bool is_valid() const {
            return nf_wrapper && nf_wrapper->is_valid();
        }


        shared_reference_type get_reference( const shared_dependency_type& d ) const {
            if ( shared_ptr_to_reference_set_type srs = shared_references.lock() ) {
                reference_set_type::right_iterator it = srs->right.find( d.get() );
                if ( it != srs->right.end() ) {
                    //if it is expired we just return an empty shared_ptr.
                    return it->info.lock();
                }
            }
            return shared_reference_type();
        }

        //the actual nf_wrapper, this won't be set if no named formula with that name exists yet.
        shared_named_formula_wrapper_type nf_wrapper;
        //all the dependencies (cells/named_formulas...) that take an interest in this nf_wrapper
        // shared_locked_dependency_type dependents;
        //shared references
        weak_ptr_to_reference_set_type shared_references;

        reference_set_type own_references;
        size_t clear_expired_references_counter;
    };

    struct storage_root_node
            : public boost::noncopyable {
        typedef ws_nf_map_type::iterator iterator;
        typedef ws_nf_map_type::const_iterator const_iterator;

        storage_root_node() : references( new reference_set_type() ), clear_expired_references_counter( 0 ) {}
        storage_root_node( const shared_named_formula_type& nf ) : references( new reference_set_type() ), clear_expired_references_counter( 0 ) {
            set_nf( nf );
        }

        ~storage_root_node() {
            reference_set_type::left_const_iterator it( references->left.begin() ), end_it( references->left.end() );
            for ( ; it != end_it; ++it ) {
                shared_reference_type snf = it->info.lock();
                if ( snf ) {
                    boost::shared_static_cast<named_formula_reference>( snf )->unload();
                }
            }
            references.reset();
        }

        shared_storage_node get( const named_formula_identifier& nf_identifier ) const {
            if ( nf_identifier.is_worksheet_scope() ) {
                const_iterator it( get( nf_identifier.scope_ws_id() ) );
                if ( it != end() ) {
                    return it->second;
                }
                return shared_storage_node();
            }
            return wb_nf ? wb_nf : shared_storage_node();
        }

        inline void unload() {
            if ( wb_nf ) {
                wb_nf->unload();
            }
            const_iterator it( ws_nf_map.begin() ), end_it( ws_nf_map.end() );
            for ( ; it != end_it; ++it ) {
                it->second->unload();
            }
        }

        inline void set_wb_nf( const shared_named_formula_type& nf ) {
            if ( !wb_nf ) {
                wb_nf = boost::make_shared<storage_node>( nf, boost::ref( references ) );
            } else {
                assert( wb_nf->nf_wrapper );
                wb_nf->nf_wrapper->set_named_formula( nf );
            }
            adjust_dependencies::adjust_references( ws_nf_map, wb_nf->nf_wrapper );
            adjust_dependencies::get_dangling_references( wb_nf );
            if ( place_holder_node ) {
                adjust_dependencies::adjust_references( place_holder_node, wb_nf->nf_wrapper, true );
            }
        }

        inline void set_ws_nf( const uuid_type& scope_ws_id, const shared_named_formula_type& nf, const bool scope_sheet_hidden ) {
            iterator it( ws_nf_map.find( scope_ws_id ) );
            if ( it != ws_nf_map.end() ) {
                if ( it->second.get() ) {
                    assert( it->second->nf_wrapper );
                    it->second->nf_wrapper->set_named_formula( nf, named_formula_wrapper::is_hidden( scope_sheet_hidden ) );
                } else {
                    it->second = boost::make_shared<storage_node>( nf, boost::ref( references ) );
                }
            } else {
                it = ws_nf_map.insert( std::make_pair( scope_ws_id, boost::make_shared<storage_node>( nf, boost::ref( references ) ) ) ).first;
            }

            adjust_dependencies::adjust_references( ws_nf_map, it->second, it->second->nf_wrapper );

            if ( place_holder_node ) {
                iterator it( ws_nf_map.find( scope_ws_id ) );
                assert( it != ws_nf_map.end() );
                adjust_dependencies::adjust_references( place_holder_node, it->second, it->second->nf_wrapper, true );
            }
        }

        inline void set_nf( const shared_named_formula_type& nf ) {
            if ( boost::shared_static_cast<named_formula>( nf )->scope() == named_formula_scope::workbook_scope ) {
                set_wb_nf( nf );
            } else {
                shared_worksheet_type ws = boost::shared_static_cast<named_formula>( nf )->worksheet().lock();
                if ( ! ws ) {
                    throw invalid_worksheet_exception();
                }
                set_ws_nf( ws->uuid(), nf, ws->hidden() );
            }
        }

        inline bool is_valid_wb_node() const {
            return wb_nf;
        }

        inline iterator get( const uuid_type& scope_ws_id ) {
            return ws_nf_map.find( scope_ws_id );
        }

        inline const_iterator get( const uuid_type& scope_ws_id ) const {
            return ws_nf_map.find( scope_ws_id );
        }

        inline const_iterator end() const {
            return ws_nf_map.end();
        }

        inline void insert( const uuid_type& scope_ws_id, const shared_storage_node& nf ) {
            if ( shared_ptr_to_reference_set_type srs = nf->shared_references.lock() ) {
                references->insert( srs->begin(), srs->end() );
                nf->shared_references = references;
            }
            if ( scope_ws_id.is_nil() ) {
                wb_nf = nf;
            } else {
                ws_nf_map[scope_ws_id] = nf;
            }
            //just to force adjustment of references
            set_nf( nf->nf_wrapper->named_formula() );
        }

        inline void remove( const uuid_type& scope_ws_id = boost::uuids::nil_uuid() ) {
            if ( ! scope_ws_id.is_nil() ) {
                iterator it( ws_nf_map.find( scope_ws_id ) );
                if ( it != end() ) {
                    it->second->nf_wrapper->unload();
                    if ( wb_nf && wb_nf->nf_wrapper && wb_nf->nf_wrapper->is_valid() ) {
                        adjust_dependencies::adjust_references( it->second, wb_nf->nf_wrapper/*, true*/ );
                    }
                }
            } else {
                wb_nf->nf_wrapper->unload();
            }
        }

        inline const shared_storage_node& create_wrapper( const uuid_type& scope_ws_id ) {
            assert( "wrong call of storage_root_node::create_ws_wrapper"
                    && get( scope_ws_id ) == end() );
            return ws_nf_map.insert( ws_nf_map_type::value_type( scope_ws_id, boost::make_shared<storage_node>( boost::ref( references ) ) ) ).first->second;
        }

        inline const shared_storage_node& create_wrapper() {
            assert( "wrong call of storage_root_node::create_wrapper"
                    && !wb_nf.get() );
            wb_nf = boost::make_shared<storage_node>( boost::ref( references ) );
            return wb_nf;
        }

        inline const shared_storage_node& create_place_holder_wrapper() {
            assert( "wrong call of storage_root_node::create_place_holder_wrapper"
                    && !place_holder_node.get() );
            place_holder_node = boost::make_shared<storage_node>( boost::ref( references ) );
            return place_holder_node;
        }

        inline const shared_storage_node& get_wb_wrapper() {
            return wb_nf.get() ? wb_nf : create_wrapper();
        }
        inline const shared_storage_node& get_place_holder_wrapper() {
            return place_holder_node.get() ? place_holder_node : create_place_holder_wrapper();
        }

        inline const shared_storage_node& get_wrapper( const uuid_type& id, const named_formula_scope::type scope ) {
            if ( !id.is_nil() ) {
                iterator it( get( id ) );
                if ( it != end() && scope != named_formula_scope::workbook_scope ) {
                    return it->second;
                }
                if ( is_valid_wb_node() && wb_nf->is_valid() ) {
                    return get_wb_wrapper();
                }
            }
            if ( scope == named_formula_scope::workbook_scope ) {
                return get_wb_wrapper();
            }
            return get_place_holder_wrapper();
        }

        inline void add_reference( const shared_dependency_type& d, const shared_reference_type& ref, const named_formula_scope::type scope, const shared_worksheet_type ws, const shared_workbook_type& /*wb*/ ) {
            clear_expired_references();
            references->insert( reference_set_type::value_type( ref.get(), d.get(), ref ) );
            if ( scope != named_formula_scope::workbook_scope ) {
                iterator it ( get( ws->uuid() ) );
                if ( it != end() ) {
                    if ( it->second->nf_wrapper.get() && it->second->nf_wrapper->is_valid() ) {
                        adjust_dependencies::register_dependents( it->second->nf_wrapper->named_formula(), *references );
                    }
                    return;
                } else if ( scope == named_formula_scope::worksheet_scope ) {
                    shared_storage_node node = create_wrapper( ws->uuid() );
                    return;
                }
            }
            if ( wb_nf && wb_nf->nf_wrapper.get() && wb_nf->nf_wrapper->is_valid() ) {
                adjust_dependencies::register_dependents( wb_nf->nf_wrapper->named_formula(), *references );
            }
        }

        inline void clear_expired_references() {
            if ( ++clear_expired_references_counter > clear_expired_references_counter_max ) {
                clear_expired_references_counter = 0;
                clear_expired_references( *references );
                for ( iterator it = ws_nf_map.begin(), end_it = ws_nf_map.end(); it != end_it; ++it ) {
                    if ( shared_ptr_to_reference_set_type srs =  it->second->shared_references.lock() ) {
                        clear_expired_references( *srs );
                    }
                    clear_expired_references( it->second->own_references );
                }
            }

        }

        static inline void clear_expired_references( reference_set_type& refs ) {
            typedef reference_set_type set_type;
            set_type::iterator it = refs.begin();
            while ( it != refs.end() ) {
                if ( it->info.expired() ) {
                    refs.erase( it++ );
                } else {
                    ++it;
                }
            }
        }

        inline shared_reference_type get_reference( const shared_dependency_type& d, const named_formula_scope::type scope, const shared_worksheet_type ws, const shared_workbook_type& /*wb*/ ) {
            if ( scope != named_formula_scope::workbook_scope ) {
                iterator it ( get( ws->uuid() ) );
                if ( it != end() ) {
                    return it->second->get_reference( d );
                } else if ( scope == named_formula_scope::worksheet_scope ) {
                    return shared_reference_type();
                }
            }
            if ( !wb_nf ) {
                return shared_reference_type();
            }
            return wb_nf->get_reference( d );
        }

        //this is used to remove a whole shared_named_formula_storage_node!
        inline bool erase( const uuid_type& scope_ws_id ) {
            if ( scope_ws_id.is_nil() ) {
                wb_nf.reset();
                return references->empty() && ws_nf_map.empty();
            } else {
                ws_nf_map.erase( scope_ws_id );
                return references->empty() && ws_nf_map.empty() && ( !wb_nf );
            }
        }

        shared_storage_node wb_nf;
        shared_storage_node place_holder_node;
        ws_nf_map_type ws_nf_map;
        shared_ptr_to_reference_set_type references;
        size_t clear_expired_references_counter;
        //initialized to 1000 in implementation file
        static const size_t clear_expired_references_counter_max;
    };

    class named_formula_storage
    {
        typedef map_to_use<utf8_ci_string, nf::shared_storage_root_node>::type container_type;
        typedef map_to_use<uuid_type, weak_named_formula_type>::type uuid_lookup_type;

        typedef container_type::iterator iterator;
        typedef container_type::const_iterator const_iterator;
        ////////////////
        /////////static helpers - should go into their own class later
    public:
        inline static shared_worksheet_type lookup_worksheet( const weak_worksheet_type& weak_ws ) {
            shared_worksheet_type ws = weak_ws.lock();
            if ( !ws ) {
                throw named_formula_not_found_exception( "worksheet not found!" );
            }
            return ws;
        }

        inline static shared_worksheet_type lookup_worksheet( const shared_worksheet_type& first_try, const weak_worksheet_type& second_try ) {
            return first_try ? first_try : lookup_worksheet( second_try );
        }


    private:
        inline static const std::string to_lower_copy( const std::string& s ) {
            return boost::to_lower_copy( s );
        }

        static inline bool is_valid_wb_node( const shared_storage_root_node& super_node ) {
            return super_node && is_valid_node( super_node->wb_nf );
        }

        static inline shared_named_formula_type get_wb_nf( const shared_storage_root_node& super_node ) {
            assert( is_valid_wb_node( super_node ) );
            return get_nf( super_node->wb_nf );
        }

        static inline bool is_valid_node( const shared_storage_node& node ) {
            return node && node->is_valid();
        }

        static inline shared_named_formula_type get_nf( const shared_storage_node& node ) {
            assert( is_valid_node( node ) );
            return node->nf_wrapper->named_formula();
        }


        ////////////////
        /////////functions to access the underlying container - private and hidden later on
        inline shared_storage_root_node find_or_add_root_node( const utf8_ci_string& name ) {
            shared_storage_root_node node( find_root_node( name ) );
            if ( !node ) {
                node = add_root_node( name );
            }
            return node;
        }

        inline shared_storage_root_node add_root_node( const utf8_ci_string& name ) {
            shared_storage_root_node node = boost::make_shared<storage_root_node>();
            m_container[name] = node;
            return node;
        }

        inline shared_storage_root_node find_root_node( const utf8_ci_string& name ) const {
            return find_root_node<false>( name );
        }

        inline shared_storage_root_node find_root_node_and_throw_if_not_found( const utf8_ci_string& name ) const {
            return find_root_node<true>( name );
        }


        template<bool throw_if_not_found>
        inline shared_storage_root_node find_root_node( const utf8_ci_string& name ) const {
            container_type::const_iterator it( m_container.find( name ) );
            if ( it == m_container.end() ) {
                if ( throw_if_not_found ) {
                    throw named_formula_not_found_exception( convert_utf8_ci( name ) );
                } else {
                    static shared_storage_root_node dummy;
                    return dummy;
                }
            }
            return it->second;
        }

        inline shared_storage_node find_node_and_throw_if_not_found( const named_formula_identifier& nf_identifier ) const {
            const shared_storage_root_node& super_node = find_root_node_and_throw_if_not_found( nf_identifier.name() );
            return find_node_and_throw_if_not_found( super_node, nf_identifier );
        }

        inline shared_storage_node find_node( const named_formula_identifier& nf_identifier ) const {
            static const shared_storage_node dummy;
            const shared_storage_root_node& super_node = find_root_node<false>( nf_identifier.name() );
            return super_node ? find_node( super_node, nf_identifier ) : dummy;
        }

        inline shared_storage_node find_node_and_throw_if_not_found( const shared_storage_root_node& source_super_node, const named_formula_identifier& nf_identifier ) const {
            shared_storage_node source = source_super_node->get( nf_identifier );
            if ( !source ) {
                throw named_formula_not_found_exception( convert_utf8_ci( nf_identifier.name() ) );
            }
            return source;
        }

        inline shared_storage_node find_node( const shared_storage_root_node& source_super_node, const named_formula_identifier& nf_identifier ) const {
            static const shared_storage_node dummy;
            shared_storage_node source = source_super_node->get( nf_identifier );
            return source ? source : dummy;
        }

        inline named_formula_identifier named_formula_identifier_from_nf( const shared_named_formula_type& nf ) const {
            if ( nf->scope() == named_formula_scope::worksheet_scope ) {
                shared_worksheet_type ws = nf->worksheet().lock();
                if ( ws ) {
                    return named_formula_identifier( nf->name(), ws->uuid() );
                }
            }
            return named_formula_identifier( nf->name(), uuid_type() );

        }

        inline named_formula_identifier find_identifier_by_id( const uuid_type& id ) const {
            uuid_lookup_type::const_iterator it( m_uuid_lookup.find( id ) );
            if ( it != m_uuid_lookup.end() ) {
                shared_named_formula_type nf = it->second.lock();
                if ( nf ) {
                    return named_formula_identifier_from_nf( nf );
                }
            }
            throw named_formula_not_found_exception( id );
        }

        inline named_formula_identifier find_identifier_by_id_and_remove_from_id_store( const uuid_type& id ) {
            uuid_lookup_type::iterator it( m_uuid_lookup.find( id ) );
            if ( it != m_uuid_lookup.end() ) {
                shared_named_formula_type nf = it->second.lock();
                m_uuid_lookup.erase( it );
                if ( nf ) {
                    return named_formula_identifier_from_nf( nf );
                }
            }
            throw named_formula_not_found_exception( id );
        }

        ////////////////
        /////////functions that should be accessible to the outside
    public:
        inline void remove( const named_formula_identifier& nf_identifier ) {
            const shared_storage_root_node& node = find_root_node_and_throw_if_not_found( nf_identifier.name() );
            node->remove( nf_identifier.scope_ws_id() );
        }

        inline void remove( const uuid_type& id ) {
            remove( find_identifier_by_id_and_remove_from_id_store( id ) );
        }

        inline void rename( const named_formula_identifier& nf_identifier, const std::string& new_name ) {

            if ( ( convert_utf8_ci( nf_identifier.name() ) == new_name ) ) {
                return;
            }
            if ( name_invalid_or_taken( named_formula_identifier( new_name,  nf_identifier.scope_ws_id() ), convert_utf8_ci( nf_identifier.name() ) ) ) {
                throw named_formula_exception( "rename went wrong! old name: '" + convert_utf8_ci( nf_identifier.name() ) + "', new name: '" + new_name + "' !" );
            }

            const utf8_ci_string ci_new_name = convert_utf8_ci( new_name );

            shared_storage_root_node source_super_node = find_root_node_and_throw_if_not_found( nf_identifier.name() );
            shared_storage_node source = find_node_and_throw_if_not_found( source_super_node, nf_identifier );

            shared_storage_root_node target_super_node = find_or_add_root_node( ci_new_name );
            target_super_node->insert( nf_identifier.scope_ws_id(), source );

            if ( target_super_node != source_super_node ) {
                if ( shared_ptr_to_reference_set_type srs = source->shared_references.lock() ) {
                    srs->clear();
                }
                if ( source_super_node->erase( nf_identifier.scope_ws_id() ) ) {
                    if ( source_super_node->place_holder_node ) {
                        if ( target_super_node->place_holder_node ) {
                            target_super_node->place_holder_node->own_references.insert( source_super_node->place_holder_node->own_references.begin(),
                                    source_super_node->place_holder_node->own_references.end() );
                            source_super_node->place_holder_node->own_references.clear();
                            if ( shared_ptr_to_reference_set_type srs = source_super_node->place_holder_node->shared_references.lock() ) {
                                srs->clear();
                            }
                        } else {
                            target_super_node->place_holder_node = source_super_node->place_holder_node;
                            target_super_node->place_holder_node->shared_references = target_super_node->references;
                        }
                    }
                    m_container.erase( nf_identifier.name() );
                }
            }
            shared_named_formula_type nf = get( named_formula_identifier( ci_new_name, nf_identifier.scope_ws_id() ) );
            if ( !nf ) {
                throw named_formula_exception( "rename went wrong! old name: '" + convert_utf8_ci( nf_identifier.name() ) + "', new name: '" + new_name + "' !" );
            }
            nf->name( ci_new_name );
            nf->internal_flag_dirty();
        }

        inline void rename( const uuid_type& id, const std::string& new_name ) {
            rename( find_identifier_by_id( id ), new_name );
        }

        inline void set( const utf8_ci_string& name, const shared_named_formula_type& nf ) {
            shared_storage_root_node super_node = find_or_add_root_node( name );
            super_node->set_nf( nf );
            m_uuid_lookup[boost::shared_static_cast<named_formula>( nf )->uuid()] = boost::shared_static_cast<named_formula>( nf );
        }

        shared_named_formula_type get_and_throw_if_not_found( const named_formula_identifier& nf_identifier ) const {
            shared_storage_node node = find_node_and_throw_if_not_found( nf_identifier );
            if ( !is_valid_node( node ) ) {
                throw named_formula_not_found_exception( convert_utf8_ci( nf_identifier.name() ) );
            }
            shared_named_formula_type nf = get_nf( node );
            if ( !nf ) {
                throw named_formula_not_found_exception( convert_utf8_ci( nf_identifier.name() ) );
            }
            return nf;
        }

        inline shared_named_formula_type get_and_throw_if_not_found( const uuid_type& id ) {
            return get_and_throw_if_not_found( find_identifier_by_id( id ) );
        }

        const shared_named_formula_type& get( const named_formula_identifier& nf_identifier ) const {
            static const shared_named_formula_type dummy;
            shared_storage_node node = find_node( nf_identifier );
            if ( is_valid_node( node ) ) {
                const shared_named_formula_type& nf = get_nf( node );
                if ( nf ) {
                    return nf;
                }
            }
            return dummy;
        }

        inline bool name_invalid_or_taken( const named_formula_identifier& nf_identifier, const std::string& old_name = "" ) const {
            shared_named_formula_type nf = get( nf_identifier );
            if ( !nf ) {
                return false;
            }
            bool return_val = false;
            if ( nf->scope() == named_formula_scope::worksheet_scope && nf_identifier.is_worksheet_scope() ) {
                shared_worksheet_type ws = nf->worksheet().lock();
                if ( ws ) {
                    if ( nf_identifier.scope_ws_id() == ws->uuid() ) {
                        return_val = true;
                    }
                }
            } else if ( nf->scope() == named_formula_scope::workbook_scope && nf_identifier.is_workbook_scope() ) {
                return_val = true;
            }
            if ( return_val && !old_name.empty() ) {
                return_val = ( nf->name() != old_name );
            }
            return return_val;
        }

        template<typename return_type>
        return_type get_all( session& s, const uuid_type& sheet_id, const sheet_point& position /* = sheet_point */, const bool show_hidden/* = false */ ) {
            return_type return_vec;
            const bool get_all_nfs = sheet_id.is_nil();

            uuid_type skip_id = boost::uuids::nil_uuid();

            shared_worksheet_type ws = s.selected().worksheet().lock();
            if ( ws && ws->hidden() ) {
                session_sheet_map::session_to_original_sheet_id_map_type::const_iterator find_it = s.session_sheets().list_sheets_with_their_session_sheet().find( ws->uuid() );
                if ( find_it != s.session_sheets().list_sheets_with_their_session_sheet().end() ) {
                    skip_id = find_it->second;
                }
            }

            for ( const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
                assert( "ERROR - shared_named_formula_storage_node in named_formula_manager::m_container not initialized!" && it->second.get() );

                if ( get_all_nfs && is_valid_wb_node( it->second ) ) {
                    shared_named_formula_type crt_nf = get_wb_nf( it->second );
                    if ( show_hidden || !crt_nf->hidden() ) {
                        return_vec.push_back( named_formula_utility::to_vector<typename return_type::value_type>( s, *crt_nf, position ) );
                    }
                }

                for (
                    nf::ws_nf_map_type::const_iterator node_it = it->second->ws_nf_map.begin(),
                    node_end_it = it->second->ws_nf_map.end();
                    node_it != node_end_it; ++node_it
                ) {
                    assert( "ERROR - shared_named_formula_storage_node in named_formula_manager::m_container not initialized!" && node_it->second.get() );

                    if ( is_valid_node( node_it->second ) ) { //check if the wrapper is there and valid
                        //check if we want all, and the scope sheet isn't hidden, or if we want exactly that sheet
                        if (
                            (
                                get_all_nfs
                                &&
                                ( !node_it->second->nf_wrapper->scope_sheet_hidden() || !skip_id.is_nil() )
                                &&
                                (
                                    skip_id.is_nil()
                                    ||
                                    !named_formula_utility::check_scope_ws_same( skip_id, *get_nf( node_it->second ) )
                                )

                            )
                            || named_formula_utility::check_scope_ws_same( sheet_id, *get_nf( node_it->second ) ) ) {
                            shared_named_formula_type crt_nf = get_nf( node_it->second );
                            if ( show_hidden || !crt_nf->hidden() ) {
                                return_vec.push_back( named_formula_utility::to_vector<typename return_type::value_type>( s, *crt_nf, position ) );
                            }
                        }
                    }
                }
            }
            return return_vec;
        }

        inline void unload_sheet( const uuid_type& sheet_id ) {
            assert( !sheet_id.is_nil() );
            for ( const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
                it->second->remove( sheet_id );
                //it->second->clear_expired_references();
            }
        }

        inline void unload() {
            for ( const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
                it->second->unload();
            }
            m_container.clear();
            m_uuid_lookup.clear();
        }

        void copy_to_sheet( session& s, const uuid_type& source_ws_id, const shared_worksheet_type& target_ws ) const {
            const bool is_clone_sheet = target_ws->hidden();
            typedef std::list<shared_named_formula_type> tmp_list_type;
            tmp_list_type tmp_list;
            for ( const_iterator it = m_container.begin(), end_it = m_container.end(); it != end_it; ++it ) {
                if( const shared_storage_root_node& node = it->second ) {
                    for (
                        ws_nf_map_type::const_iterator node_it = node->ws_nf_map.begin(),
                        node_end_it = node->ws_nf_map.end();
                        node_it != node_end_it; ++node_it
                    ) {
                        assert( "ERROR - shared_named_formula_storage_node in named_formula_manager::m_container not initialized!" && node_it->second.get() );

                        if ( is_valid_node( node_it->second ) && named_formula_utility::check_scope_ws_same( source_ws_id, *get_nf( node_it->second ) ) ) {
                            tmp_list.push_back( get_nf( node_it->second ) );
                        }
                    }
                }
            }
            for ( tmp_list_type::const_iterator it = tmp_list.begin(), end_it = tmp_list.end(); it != end_it; ++it ) {
                named_formula_utility::copy_to_sheet( s, **it, target_ws, is_clone_sheet );
            }
        }

        shared_reference_type register_dependency( const shared_dependency_type& d, const named_formula_identifier& nf_identifier, const named_formula_scope::type scope, const shared_worksheet_type& ws ) {
            return register_dependency( d, nf_identifier.name(), nf_identifier.scope_ws_id(), scope, ws );
        }

        shared_reference_type register_dependency( const shared_dependency_type& d, const utf8_ci_string& name, const uuid_type& sheet_id, const named_formula_scope::type scope, const shared_worksheet_type& ws  ) {
            nf::shared_storage_root_node nf_super_node = find_or_add_root_node( name );
            nf::shared_storage_node node;

            // if scope is none, we don't care about scope, in that case we first try to find a worksheet scoped nf and if
            // that fails we try a workbook scoped one.
            switch ( scope ) {
                case named_formula_scope::worksheet_scope: {
                    node = nf_super_node->get_wrapper( sheet_id, scope );
                }
                break;

                case named_formula_scope::workbook_scope: {
                    node = nf_super_node->get_wrapper( boost::uuids::nil_uuid(), scope );
                }
                break;

                default: {
                    node = nf_super_node->get_wrapper( ws->uuid() , scope );
                }
            }
            shared_reference_type return_value = node->get_reference( d );

            if ( !return_value ) {
                return_value = named_formula_reference::create( d, ws, name,  static_cast<named_formula_scope::type>( scope ), node->nf_wrapper );
            }

            nf_super_node->add_reference( d, return_value, scope, ws, ws->parent() );

            return return_value;
        }

    private:
        container_type m_container;
        uuid_lookup_type m_uuid_lookup;
    };
} //namespace nf


template<class dependency_T>
void adjust_dependencies::register_dependents( const dependency_T& target, const shared_locked_dependency_type& source )
{
    const dependency_set_type& dependencies = *source->lock();
    for ( dependency_set_type::const_iterator it = dependencies.begin(), end_it = dependencies.end(); it != end_it; ++it ) {
        target->register_dependent( *it );
    }
}

template<class dependency_T>
void adjust_dependencies::register_dependents( const dependency_T& target, const nf::reference_set_type& source )
{}
