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
#include "precompiled_header.hpp"
#include "wss/worksheet_element.hpp"

#include "wss/server.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"
#include "wss/i_dependency.hpp"
#include "wss/non_instantiable.hpp"
#include "wss/core2_compatibility.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "wss/scoped_neutral_locale_enforcer.hpp"

#include "uuid_adjust.hpp"
#include "core_logging.hpp"
#include "worksheet_element_key_value_map.hpp"

#include <oxml/custom_data.hpp>
#include <boost/random.hpp>

/*!
* \brief
* special predefined keys
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
struct worksheet_element_special_keys : public non_instantiable {

    enum system_key_type {
        none
        , e_id
        , e_type
        , e_scope
        , n_is_dirty
        , n_gv
        , n_refers_to
        , n_location
        , n_has_moved
        , n_source_dims
        , n_use_locale
        , n_target_dirty
        , n_target_val
        , n_target_ref
        , count
    };

    static inline const std::string& key_to_string( const system_key_type k ) {
        switch ( k ) {
            case e_id:
                return e_id_string;
            case  e_type:
                return  e_type_string;
            case  e_scope:
                return e_scope_string;
            case  n_is_dirty:
                return n_is_dirty_string;
            case  n_gv:
                return n_gv_string;
            case  n_refers_to:
                return n_refers_to_string;
            case n_location:
                return n_location_string;
            case n_has_moved:
                return n_has_moved_string;
            case n_source_dims:
                return n_source_dims_string;
            case n_use_locale:
                return n_use_locale_string;
            case n_target_dirty:
                return n_target_dirty_string;
            case n_target_val:
                return n_target_val_string;
            case n_target_ref:
                return n_target_ref_string;
            default:
                break;
        }
        static std::string dummy;
        return dummy;
    }

    static inline const system_key_type string_to_key( const std::string& k ) {
        utf8_ci_string ci_k = convert_utf8_ci( k );
        if ( ci_k == e_id_string ) {
            return e_id;
        } else if ( ci_k == e_type_string ) {
            return e_type;
        } else if ( ci_k == e_scope_string ) {
            return e_scope;
        } else if ( ci_k == n_is_dirty_string ) {
            return n_is_dirty;
        } else if ( ci_k == n_gv_string ) {
            return n_gv;
        } else if ( ci_k == n_refers_to_string ) {
            return n_refers_to;
        } else if ( ci_k == n_location_string ) {
            return n_location;
        } else if ( ci_k == n_has_moved_string ) {
            return n_has_moved;
        } else if ( ci_k == n_source_dims_string ) {
            return n_source_dims;
        } else if ( ci_k == n_use_locale_string ) {
            return n_use_locale;
        } else if ( ci_k == n_target_dirty_string ) {
            return n_target_dirty;
        } else if ( ci_k == n_target_val_string ) {
            return n_target_val;
        } else if ( ci_k == n_target_ref_string ) {
            return n_target_ref;
        }
        return none;
    }

    static inline bool is_system_key( const std::string& k ) {
        return is_system_key( string_to_key( k ) );
    }

    static inline bool is_system_key( const system_key_type k ) {
        return k != none && k < count;
    }
    static inline bool is_we_key( const std::string& k ) {
        return is_we_key( string_to_key( k ) );
    }

    static inline bool is_we_key( const system_key_type k ) {
        return k != none && k <= 3;
    }
    static inline bool is_nf_key( const std::string& k ) {
        return is_nf_key( string_to_key( k ) );
    }

    static inline bool is_nf_key( const system_key_type k ) {
        return k > 3 && k < count;
    }

    static inline const bool is_const_key( const std::string& k ) {
        return is_const_key( string_to_key( k ) );
    }

    static inline const bool is_const_key( const system_key_type k ) {
        switch ( k ) {
            case e_id:

                /*!
                * \brief
                * this needs to be fixed on the ui side first.. remove the following line(s) if worksheet elements can change the uuid on load!
                *
                * \author
                * Frieder Hofmann <frieder.hofmann@jedox.com>
                */
                return false;
                //return true;
            case  e_type:
            case  e_scope:
            case  n_refers_to:
            case n_location:
            case n_use_locale:
            case n_target_ref:
                return false;
            case  n_is_dirty:
            case  n_gv:
            case n_has_moved:
            case n_source_dims:
            case n_target_dirty:
            case n_target_val:
                return true;
            default:
                break;
        }
        return false;
    }

    static const std::string e_id_string;
    static const std::string e_type_string;
    static const std::string e_scope_string;
    static const std::string n_is_dirty_string;
    static const std::string n_gv_string;
    static const std::string n_refers_to_string;
    static const std::string n_location_string;
    static const std::string n_has_moved_string;
    static const std::string n_source_dims_string;
    static const std::string n_use_locale_string;
    static const std::string n_target_dirty_string;
    static const std::string n_target_val_string;
    static const std::string n_target_ref_string;
};

const std::string worksheet_element_special_keys::e_id_string = "e_id";
const std::string worksheet_element_special_keys::e_type_string = "e_type";
const std::string worksheet_element_special_keys::e_scope_string = "e_scope";
const std::string worksheet_element_special_keys::n_is_dirty_string = "n_is_dirty";
const std::string worksheet_element_special_keys::n_gv_string = "n_get_val";
const std::string worksheet_element_special_keys::n_refers_to_string = "n_refers_to";
const std::string worksheet_element_special_keys::n_location_string = "n_location";
const std::string worksheet_element_special_keys::n_has_moved_string = "n_has_moved";
const std::string worksheet_element_special_keys::n_source_dims_string = "n_source_dims";
const std::string worksheet_element_special_keys::n_use_locale_string = "n_use_locale";
const std::string worksheet_element_special_keys::n_target_dirty_string = "n_target_dirty";
const std::string worksheet_element_special_keys::n_target_val_string = "n_target_val";
const std::string worksheet_element_special_keys::n_target_ref_string = "n_target_ref";

struct worksheet_element::worksheet_element_impl
        : boost::noncopyable {

    typedef map_to_use<std::string, variant>::type key_val_map_value_type;

    typedef bool dirty_state_type;
    typedef boost::optional<variant> cached_value_type;


    worksheet_element_impl( const shared_worksheet_type& ws, worksheet_element& parent  )
        : m_type( "chart" )
        , m_ws( ws )
        , m_wb( ws->parent() )
        , m_wb_scope( false )
        , m_parent( parent )
        , m_use_locale( false )

        , m_is_dirty( false )
        , m_has_moved( false )
        , m_target_is_dirty( false )

        , m_was_copied( false )
        , m_last_valid_location( "=$A$1:$A$1" ) {}

    worksheet_element_impl( const shared_workbook_type& wb, worksheet_element& parent   )
        : m_type( "chart" )
        , m_wb( wb )
        , m_wb_scope( true )
        , m_parent( parent )
        , m_use_locale( false )

        , m_is_dirty( false )
        , m_has_moved( false )
        , m_target_is_dirty( false )

        , m_was_copied( false )
        , m_last_valid_location( "=$A$1:$A$1" ) {}

    ~worksheet_element_impl() {
        m_formula.reset();
        m_location_formula.reset();
    }

    inline shared_scoped_neutral_locale_enforcer switch_locale( session& s, const bool use_locale, const bool enforce_no_switch ) const {
        if ( enforce_no_switch || ( use_locale && m_use_locale ) ) {
            static shared_scoped_neutral_locale_enforcer dummy;
            return dummy;
        } else {
            return shared_scoped_neutral_locale_enforcer( new scoped_neutral_locale_enforcer( s ) );
        }
    }

    inline bool has_nf() const {
        return m_formula.get() != 0;
    }

    inline bool has_target_nf() const {
        return 0 != m_target_formula.get();
    }

    inline bool has_location_nf() const {
        return m_location_formula.get() != 0;
    }

    inline const std::string& scope() const {
        static const std::string wb = "wb";
        static const std::string ws = "ws";
        return m_wb_scope ? wb : ws;
    }

    inline const std::string& type() const {
        return m_type;
    }

    inline void set_type( const std::string& type  ) {
        m_type = type;
    }

    void do_rename_if_debug( session &s, const value_type&v ) {
#ifdef _DEBUG
        std::string prefix = v.as_string( s.locale() );
        do_rename( m_formula, prefix );
        do_rename( m_location_formula, prefix );
        do_rename( m_target_formula, prefix );
#endif // _DEBUG
    }

    void do_rename_if_debug( session &s, shared_free_formula_type& ff ) {
#ifdef _DEBUG
        if ( !ff ) {
            return;
        }
        //make it easier to see where we are in debug node
        std::string prefix;
        key_val_map_value_type::const_iterator it = m_properties.find( "formel_name" );
        if ( it != m_properties.end() ) {
            prefix = it->second.as_string( s.locale() );
        }
        do_rename( ff, prefix );
#endif // _DEBUG
    }
    void do_rename( const shared_free_formula_type& ff, const std::string& prefix ) {
#ifdef _DEBUG
        if ( ff ) {
            if ( ff == m_formula ) {
                ff->rename( prefix + " formula" );
            } else if ( ff == m_location_formula ) {
                ff->rename( prefix + " location_formula" );
            } else if ( ff == m_target_formula ) {
                ff->rename( prefix + " target_formula" );
            }
        }
#endif // _DEBUG
    }

    inline void add_nf( shared_free_formula_type& ff, session& s, const value_type& v, sheet_point& position ) {
        shared_worksheet_type ws = m_ws.lock();
        if ( !ws ) {
            throw worksheet_element_exception( "worksheet_element - error, named formula couldn't be added - worksheet no longer present!" );
        }
        if ( ! ff ) {
            ff = free_formula::create( s, v, ws, position );
            ff->set_special_caching();

            do_rename_if_debug( s, ff );
        }
    }

    inline variant get_nf_value( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const {
        return get_formula_value<false, true>( s, m_formula, m_is_dirty, m_cached_volatile_value, position );
    }

    inline variant get_target_nf_value( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const {
        return get_formula_value<false, false>(  s, m_target_formula, m_target_is_dirty, m_target_cached_value, position );
    }

    inline const bool is_dirty( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const {
        return update_cached_value_and_check_for_value_change<false, true>( s, m_formula, m_is_dirty, m_cached_volatile_value, position );
    }


    inline const bool is_target_dirty( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const {
        return update_cached_value_and_check_for_value_change<false, false>( s, m_target_formula, m_target_is_dirty, m_target_cached_value, position );
    }

    inline const bool has_moved( session& s ) const {
        return m_location_formula ? m_location_formula->moved( s ) : false;
    }

    template<bool use_locale_switch, bool enforce_no_locale_switch>
    inline const bool update_cached_value_and_check_for_value_change( session& s, const shared_free_formula_type& ff, dirty_state_type& current_dirty_state, cached_value_type& cached_value, const sheet_point& position ) const {
        if ( ff  ) {
            if ( cached_value ) {
                const variant tmp_val = get_formula_value<use_locale_switch, enforce_no_locale_switch>( s, ff, position );
                if ( tmp_val != *cached_value ) {
                    cached_value.reset( tmp_val );
                    current_dirty_state = true;
                } else {
                    current_dirty_state = false;
                }
            } else {
                current_dirty_state = true;
            }
        } else {
            current_dirty_state = false;
        }
        return current_dirty_state;
    }

    template<bool use_locale_switch, bool enforce_no_locale_switch>
    inline variant get_formula_value( session& s, const shared_free_formula_type& ff, dirty_state_type& current_dirty_state, cached_value_type& cached_value, const sheet_point& position = sheet_point( 0, 0 ) ) const {
        if ( cached_value ) {
            const variant tmp_val = get_formula_value<use_locale_switch, enforce_no_locale_switch>( s, ff, position );
            if ( tmp_val != *cached_value ) {
                cached_value.reset( tmp_val );
            }
        } else {
            cached_value.reset( get_formula_value<use_locale_switch, enforce_no_locale_switch>( s, ff, position ) );
        }
        current_dirty_state = false;
        return *cached_value;
    }

    template<bool use_locale_switch>
    inline std::string get_formula_formula( session& s, const shared_free_formula_type& ff ) const {
        if ( ff ) {
            shared_scoped_neutral_locale_enforcer nle = switch_locale( s, use_locale_switch, false );
            return ff->formula_without_sheet_references( s.locale() );
        }
        return "";
    }

    template<bool use_locale_switch, bool enforce_no_locale_switch>
    inline variant get_formula_value( session& s, const shared_free_formula_type& ff, const sheet_point& position ) const {
        shared_scoped_neutral_locale_enforcer nle = switch_locale( s, use_locale_switch, enforce_no_locale_switch );
        return ff->value( s, position );
    }

    inline const bool match_vals( session& s, const key_value_vector_type& vals ) const {
        if ( vals.empty() ) {
            return true;
        }
        key_value_vector_type::const_iterator it( vals.begin() );
        key_value_vector_type::const_iterator end_it( vals.end() );
        key_val_map_value_type::const_iterator m_end = m_properties.end();
        for ( ; it != end_it; ++it ) {
            if ( check_system_key( it->first ) ) {
                if ( !handle_match_system_key( s, *it ) ) {
                    return false;
                }
            } else {
                key_val_map_value_type::const_iterator m_it( m_properties.find( it->first ) );
                if ( m_it == m_end || m_it->second != it->second ) {
                    return false;
                }
            }
        }
        return true;
    }

    inline const bool check_we_key( const key_type& k ) const {
        return worksheet_element_special_keys::is_we_key( k );
    }

    inline const bool check_nf_key( const key_type& k ) const {
        return worksheet_element_special_keys::is_nf_key( k );
    }

    inline const bool check_system_key( const key_type& k ) const {
        return worksheet_element_special_keys::is_system_key( k );
    }

    inline key_value_type handle_get_system_key( session& s, const key_type& k ) const {
        key_value_vector_type ret_vec;
        handle_get_system_key( ret_vec, s, worksheet_element_special_keys::string_to_key( k ) );
        return ret_vec[0];
    }

    inline void handle_get_system_key( key_value_vector_type& ret_vec, session& s, const key_type& k ) const {
        handle_get_system_key( ret_vec, s, worksheet_element_special_keys::string_to_key( k ) );
    }

    inline void handle_get_system_key( key_value_vector_type& ret_vec, session& s, const worksheet_element_special_keys::system_key_type k ) const {
        switch ( k ) {
            case worksheet_element_special_keys::e_id:
                ret_vec.push_back( key_value_type( worksheet_element_special_keys::e_id_string, uuid_adjust::cast_uuid( m_parent.uuid() ) ) );
                return ;
            case  worksheet_element_special_keys::e_type:
                ret_vec.push_back( key_value_type( worksheet_element_special_keys::e_type_string, type() ) );
                return ;
            case worksheet_element_special_keys::e_scope:
                ret_vec.push_back( key_value_type( worksheet_element_special_keys::e_scope_string, scope() ) );
                return ;

            case worksheet_element_special_keys::n_is_dirty:
                ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_is_dirty_string, variant( is_dirty( s ) ) ) );
                return;
            case worksheet_element_special_keys::n_gv:
                if ( has_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_gv_string,  get_nf_value( s ) ) );
                }
                return;
            case worksheet_element_special_keys::n_refers_to:
                if ( has_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_refers_to_string, get_formula_formula<true>( s, m_formula ) ) );
                }
                return;
            case worksheet_element_special_keys::n_target_dirty:
                if ( has_target_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_target_dirty_string, variant( is_target_dirty( s ) ) ) );
                }
                return;
            case worksheet_element_special_keys::n_target_val:
                if ( has_target_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_target_val_string,  get_target_nf_value( s ) ) );
                }
                return;
            case worksheet_element_special_keys::n_target_ref:
                if ( has_target_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_target_ref_string, get_formula_formula<false>( s, m_target_formula ) ) );
                }
                return;
            case worksheet_element_special_keys::n_location:
                if ( has_location_nf() ) {
                    m_has_moved = false;
                    shared_scoped_neutral_locale_enforcer nle = switch_locale( s, false, false );
                    std::string computed_location = m_location_formula->formula_without_sheet_references( s.locale() );
                    if ( std::string::npos  != computed_location.find( "#REF!" ) ) {
                        computed_location = m_last_valid_location;
                        static sheet_point dummy( 0, 0 );
                        static key_value_type k;
                        k.second = computed_location;
                        const_cast< worksheet_element_impl* >( this )->set_formula_value<false>( s, const_cast< worksheet_element_impl* >( this )->m_location_formula, k, dummy );
                    } else {
                        m_last_valid_location = computed_location;
                    }
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_location_string, computed_location ) );

                }
                return;
            case worksheet_element_special_keys::n_has_moved:
                if ( has_location_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_has_moved_string, has_moved( s ) ) );
                }
                return;
            case worksheet_element_special_keys::n_source_dims: {
                if ( has_nf() ) {
                    ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_source_dims_string, variant( static_cast<double>( m_formula->number_of_covered_columns() ) ) ) );
                }
                return;
            }
            case worksheet_element_special_keys::n_use_locale: {
                ret_vec.push_back( key_value_type( worksheet_element_special_keys::n_use_locale_string, variant( m_use_locale ) ) );

            }
            default:
                break;
        }
    }

    inline const bool handle_match_system_key( session& s, const key_value_type& k ) const {
        switch ( worksheet_element_special_keys::string_to_key( k.first ) ) {
            case worksheet_element_special_keys::e_id:
                return uuid_adjust::cast_uuid( k.second.as_string( s.locale() ) ) == m_parent.uuid();
            case  worksheet_element_special_keys::e_type:
                return k.second.as_string( s.locale() ) == type();
            case worksheet_element_special_keys::e_scope:
                return k.second.as_string( s.locale() ) == scope();
            case worksheet_element_special_keys::n_is_dirty:
                return k.second.as_boolean( s.locale() ) == is_dirty( s );
            case worksheet_element_special_keys::n_gv:
                return m_formula && get_nf_value( s ) == k.second;
            case worksheet_element_special_keys::n_refers_to:
                return m_formula && ( get_formula_formula<true>( s, m_formula ) == k.second.as_string( s.locale() ) );
            case worksheet_element_special_keys::n_target_dirty:
                return k.second.as_boolean( s.locale() ) == is_target_dirty( s );
            case worksheet_element_special_keys::n_target_val:
                return m_target_formula &&  get_target_nf_value( s ) == k.second;
            case worksheet_element_special_keys::n_target_ref:
                return m_target_formula && get_formula_formula<false>( s, m_target_formula ) == k.second.as_string( s.locale() );
            case worksheet_element_special_keys::n_location:
                return m_location_formula &&  get_formula_formula<false>( s, m_location_formula ) == k.second.as_string( s.locale() );
            case worksheet_element_special_keys::n_has_moved:
                return k.second.as_boolean( s.locale() ) == has_moved( s );
            case worksheet_element_special_keys::n_source_dims: {
                if ( has_nf() ) {
                    return static_cast<double>( m_formula->number_of_covered_columns() ) == k.second.as_double();
                }
            }
            default:
                break;
        }
        return false;
    }

    template<bool use_locale_switch>
    inline void set_formula_value( session& s, shared_free_formula_type& ff, const key_value_type& k, sheet_point& position  ) {
        if ( k.second.is_of_empty_value() || k.second.string().size() <= 1 ) {
            return;
        }
        shared_scoped_neutral_locale_enforcer nle = switch_locale( s, use_locale_switch, false );
        if ( ff ) {
            ff->value( s, k.second, position );
            return;
        } else {
            add_nf( ff, s, k.second, position );
        }

        s.clear_cache();
    }

    inline void handle_set_system_key( session& s, const key_value_type& k, sheet_point& position ) {
        switch ( worksheet_element_special_keys::string_to_key( k.first ) ) {
            case worksheet_element_special_keys::e_type:
                set_type( k.second.as_string( s.locale() ) );
                break;

            case worksheet_element_special_keys::n_refers_to: {
                set_formula_value<true>( s, m_formula, k, position );
            }
            break;

            case worksheet_element_special_keys::n_target_ref: {
                set_formula_value<false>( s, m_target_formula, k, position );
            }
            break;

            case worksheet_element_special_keys::n_location: {
                set_formula_value<false>( s, m_location_formula, k, position );
                std::string computed_location = m_location_formula->formula_without_sheet_references( s.locale() );
                if ( std::string::npos  == computed_location.find( "#REF!" ) ) {
                    m_last_valid_location = computed_location;
                }
            }
            break;

            case worksheet_element_special_keys::n_use_locale: {
                m_use_locale = k.second.as_boolean( s.locale() );
            }
            break;

            default:
                //ignore all other keys here!
                break;
        }
    }

    inline void property( session& s, const key_value_type& k ) {
#ifdef _DEBUG
        if ( k.first == "formel_name" ) {
            do_rename_if_debug( s, k.second );
        }
#endif // _DEBUG
        if ( k.second.is_empty() ) {
            m_properties.erase( k.first );
        } else if ( check_system_key( k.first ) ) {
            static sheet_point dummy( 0, 0 );
            handle_set_system_key( s, k, dummy );
        } else {
            m_properties.erase( k.first );
            m_properties.insert( k );
        }
    }

    inline key_value_type property( session& s, const key_type& key ) {
        key_value_vector_type return_vec;
        if ( check_system_key( key ) ) {
            handle_get_system_key( return_vec, s, key );
        }
        if ( !return_vec.empty() ) {
            return return_vec[0];
        }
        key_val_map_value_type::const_iterator it( m_properties.find( key ) );
        if ( it != m_properties.end() ) {
            return  *it;
        }
        throw worksheet_element_exception( "property: \"" + key + "\"doesn't exist!" );
    }

    template<bool do_const_keys>
    inline key_value_vector_type properties( session& s, const key_vec_type& keys, const key_value_vector_type& vals ) {
        //match the values
        if ( !match_vals( s, vals ) ) {
            return key_value_vector_type();
        }

        key_value_vector_type return_vec;
        bool getall = keys.empty();
        size_t return_size = ( getall ? m_properties.size() + 9 : keys.size() ) ;
        return_vec.reserve( return_size );
        if ( getall ) {
            handle_get_system_key( return_vec, s, worksheet_element_special_keys::e_id );
            handle_get_system_key( return_vec, s, worksheet_element_special_keys::e_type );
            handle_get_system_key( return_vec, s, worksheet_element_special_keys::e_scope );
            handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_use_locale );
            if ( has_nf() ) {
                if ( do_const_keys ) {
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_is_dirty );
                }
                handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_refers_to );
                if ( do_const_keys ) {
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_gv );
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_source_dims );
                }
            }
            if ( has_target_nf() ) {
                if ( do_const_keys ) {
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_target_dirty );
                }
                handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_target_ref );
                if ( do_const_keys ) {
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_target_val );
                }
            }
            if ( has_location_nf() ) {
                if ( do_const_keys ) {
                    handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_has_moved );
                }
                handle_get_system_key( return_vec, s, worksheet_element_special_keys::n_location );
            }
            return_vec.insert( return_vec.end(), m_properties.begin(),  m_properties.end() );

        } else {
            std::vector< std::string >::const_iterator k_end = keys.end();
            for ( std::vector< std::string >::const_iterator k_it = keys.begin(); k_it != k_end; ++k_it ) {
                if ( check_nf_key( *k_it ) || check_we_key( *k_it )  ) {
                    handle_get_system_key( return_vec, s, *k_it );
                } else {
                    key_val_map_value_type::const_iterator it( m_properties.find( *k_it ) );
                    if ( it !=  m_properties.end() ) {
                        return_vec.push_back( *it );
                    }
                }
            }
        }
        return return_vec;
    }

    inline void properties( session& s, const key_value_vector_type& vals ) {
        foreach( const key_value_type & k, vals ) {
            property( s, k );
        }
    }


    inline void operator()( free_formula&, const tag_on_dirty& ) {
        m_is_dirty = true;
    }

    inline void operator()( free_formula&, const tag_on_moved& ) {
    }

    inline const weak_workbook_type get_wb() {
        return m_wb;
    }


    key_val_map_value_type m_properties;

    std::string m_type;
    shared_free_formula_type m_formula;
    shared_free_formula_type m_location_formula;
    shared_free_formula_type m_target_formula;
    weak_worksheet_type m_ws;
    weak_workbook_type m_wb;
    bool m_wb_scope;
    worksheet_element& m_parent;
    /* if set to true, m_formula will be handled using the users locale
    all other formulas (m_location_formula and m_target_formula)
    always use en_US locale! */
    bool m_use_locale;
    mutable dirty_state_type m_is_dirty;
    mutable dirty_state_type m_has_moved;
    mutable dirty_state_type m_target_is_dirty;
    //we need this to check if the value of the formula changed...
    mutable cached_value_type m_cached_volatile_value;
    mutable cached_value_type m_target_cached_value;
    mutable cached_value_type m_location_cached_value;
    mutable bool m_was_copied;
    mutable std::string m_last_valid_location;
};

template<class uuid_t>
struct select_id : non_instantiable {
    static ws_elem_id_type select( const uuid_type& id ) {
        return id;
    }
    static ws_elem_id_type select() {
        static boost::uuids::basic_random_generator<boost::taus88> gen;
        return gen();
    }
};

template<>
struct select_id<long> : non_instantiable {
    ws_elem_id_type select( const uuid_type& ) {
        return server::instance().next_id();
    }

    ws_elem_id_type select() {
        return server::instance().next_id();
    }
};

typedef select_id<ws_elem_id_type> id_selector_type;

worksheet_element::worksheet_element( const shared_worksheet_type& ws )
    : m_store( ws->elements() )
    , m_id( id_selector_type::select() )
{
    lock_type lock( m_mutex );
    m_impl.reset( new worksheet_element_impl( ws, *this ) );
    LOG_CORE_TRACE( "created worksheet element [" << uuid_adjust::cast_uuid( this->uuid() ) << "]" );
}

worksheet_element::worksheet_element( const shared_worksheet_type& ws, const uuid_type& id )
    : m_store( ws->elements() )
    , m_id( id_selector_type::select( id ) )
{
    lock_type lock( m_mutex );
    m_impl.reset( new worksheet_element_impl( ws, *this ) );
    LOG_CORE_TRACE( "created worksheet element [" << uuid_adjust::cast_uuid( this->uuid() ) << "]" );
}

worksheet_element::worksheet_element( const shared_workbook_type& wb )
    : m_store( wb->elements() )
    , m_id( id_selector_type::select() )
{
    lock_type lock( m_mutex );
    m_impl.reset( new worksheet_element_impl( wb, *this ) );
    LOG_CORE_TRACE( "created worksheet element [" << uuid_adjust::cast_uuid( this->uuid() ) << "]" );
}

worksheet_element::worksheet_element( const shared_workbook_type& wb, const uuid_type& id )
    : m_store( wb->elements() )
    , m_id( id_selector_type::select( id ) )
{
    lock_type lock( m_mutex );
    m_impl.reset( new worksheet_element_impl( wb, *this ) );
    LOG_CORE_TRACE( "created worksheet element [" << uuid_adjust::cast_uuid( this->uuid() ) << "]" );
}

worksheet_element::~worksheet_element()
{
    m_impl.reset();
    LOG_CORE_TRACE( "removed worksheet element [" << uuid_adjust::cast_uuid( this->uuid() ) << "]" );
}

shared_worksheet_element_type worksheet_element::create( const shared_worksheet_type& ws )
{
    shared_worksheet_element_type e( boost::make_shared<worksheet_element>( ws ) );
    ws->elements().add_worksheet_element( e );
    ws->parent()->flag_changed();
    return e;
}

shared_worksheet_element_type worksheet_element::create( const shared_worksheet_type& ws, const uuid_type& id )
{
    shared_worksheet_element_type e( boost::make_shared<worksheet_element>( ws, id ) );
    ws->elements().add_worksheet_element( e );
    ws->parent()->flag_changed();
    return e;
}

shared_worksheet_element_type worksheet_element::create( const shared_workbook_type& wb )
{
    shared_worksheet_element_type e( boost::make_shared<worksheet_element>( wb ) );
    wb->elements().add_worksheet_element( e );
    wb->flag_changed();
    return e;
}

shared_worksheet_element_type worksheet_element::create( const shared_workbook_type& wb, const uuid_type& id )
{
    shared_worksheet_element_type e( boost::make_shared<worksheet_element>( wb, id ) );
    wb->elements().add_worksheet_element( e );
    wb->flag_changed();
    return e;
}

void worksheet_element::property( session& s, const key_value_type& k  )
{
    lock_type lock( m_mutex );
    m_impl->property( s, k );
}
worksheet_element::key_value_type worksheet_element::property( session& s, const key_type& k )
{
    lock_type lock( m_mutex );
    return m_impl->property( s, k );
}

worksheet_element::key_value_vector_type worksheet_element::properties( session& s, const key_vec_type& keys, const key_value_vector_type& vals )
{
    lock_type lock( m_mutex );
    return m_impl->properties<true>( s, keys, vals );
}

void worksheet_element::properties( session& s, const key_value_vector_type& vals )
{
    lock_type lock( m_mutex );
    m_impl->properties( s, vals );
    boost::shared_ptr<workbook> wb( m_impl->get_wb() );
    wb->flag_changed();
}

void worksheet_element::properties( session& s, const key_value_vector_type& vals, const copied_ws_element& )
{
    lock_type lock( m_mutex );

    m_impl->properties( s, vals );
    m_impl->m_was_copied = true;
}

variant worksheet_element::get_nf_value( session& s, const sheet_point& position ) const
{
    lock_type lock( m_mutex );
    return m_impl->get_nf_value( s, position );
}

const bool worksheet_element::is_dirty( session& s, const sheet_point& position ) const
{
    lock_type lock( m_mutex );
    return m_impl->is_dirty( s, position );
}

const bool worksheet_element::has_moved( session& s ) const
{
    lock_type lock( m_mutex );
    return m_impl->has_moved( s );
}


bool worksheet_element::has_nf() const
{
    lock_type lock( m_mutex );
    return m_impl->has_nf();
}

bool worksheet_element::has_location_nf() const
{
    lock_type lock( m_mutex );
    return m_impl->has_location_nf();
}

const std::string& worksheet_element::scope() const
{
    lock_type lock( m_mutex );
    return m_impl->scope();
}

const std::string& worksheet_element::type() const
{
    lock_type lock( m_mutex );
    return  m_impl->type();
}

void worksheet_element::type( const std::string& t  )
{
    lock_type lock( m_mutex );
    m_impl->set_type( t );
}

void worksheet_element::deserialize( session& s, const spreadsheetml::CT_worksheet_element& data )
{
    lock_type lock( m_mutex );
    //the n_use_locale key needs to be set BEFORE formulas are parsed!
    m_impl->property( s, key_value_type( worksheet_element_special_keys::n_use_locale_string, data.wse_use_locale ) );

    for ( std::vector< spreadsheetml::CT_wse_property >::const_iterator i = data.wse_properties.wse_property.begin(); i != data.wse_properties.wse_property.end(); i++ ) {
        value_type in_val;
        if ( !i->key.present() ) {
            continue;
        } else if ( worksheet_element_special_keys::is_const_key( i->key.get() ) ) {
            continue;
        }
        in_val.deserialize( i->vt_value );
        m_impl->property( s, key_value_type( i->key.get(), in_val ) );
    }

    if ( data.wse_named_formula.present() ) {
        variant formula;
        formula.deserialize( data.wse_named_formula.get().vt_value );
        m_impl->property( s, key_value_type( worksheet_element_special_keys::n_refers_to_string, formula.string() ) );
    }

    if ( data.wse_location_named_formula.present() ) {
        variant formula;
        formula.deserialize( data.wse_location_named_formula.get().vt_value );
        m_impl->property( s, key_value_type( worksheet_element_special_keys::n_location_string, formula.string() ) );
    }

    if ( data.wse_target_named_formula.present() ) {
        variant formula;
        formula.deserialize( data.wse_target_named_formula.get().vt_value );
        m_impl->property( s, key_value_type( worksheet_element_special_keys::n_target_ref_string, formula.string() ) );
    }

    m_impl->set_type( data.wse_type.value.get() );

}

void worksheet_element::serialize( session& s, spreadsheetml::CT_worksheet_element& data ) const
{
    lock_type lock( m_mutex );

    data.wse_type.value = m_impl->type();
    data.wse_id.value = boost::lexical_cast<std::string>( uuid() );

    foreach( const key_value_type & v, m_impl->properties<false>( s, key_vec_type(), key_value_vector_type() ) ) {
        if ( worksheet_element_special_keys::n_refers_to_string == v.first  ) {
            spreadsheetml::CT_named_formula out_named_formula;
            variant formula( v.second );
            formula.serialize( out_named_formula.vt_value );
            data.wse_named_formula = out_named_formula;
        } else if ( worksheet_element_special_keys::n_location_string == v.first  ) {
            spreadsheetml::CT_named_formula out_named_formula;
            variant formula( v.second );
            formula.serialize( out_named_formula.vt_value );
            data.wse_location_named_formula = out_named_formula;
        } else if ( worksheet_element_special_keys::n_target_ref_string == v.first ) {
            spreadsheetml::CT_named_formula out_named_formula;
            variant formula( v.second );
            formula.serialize( out_named_formula.vt_value );
            data.wse_target_named_formula = out_named_formula;
        } else if ( worksheet_element_special_keys::n_use_locale_string == v.first ) {
            data.wse_use_locale = v.second.boolean();
        } else {
            spreadsheetml::CT_wse_property  out_prop;
            out_prop.key = v.first;
            v.second.serialize( out_prop.vt_value );
            data.wse_properties.wse_property.push_back( out_prop );
        }
    }
}

