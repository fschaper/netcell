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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/type.hpp>
#include <wss/define.hpp>
#include <wss/locale.hpp>
#include <wss/free_formula.hpp>
#include <wss/reference_operation.hpp>

#include "named_formula_dependency_wrapper.hpp"
#include "abstract_dependency.hpp"
#include "named_formula.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/make_shared.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

#ifdef _DEBUG
#include "debug_logging_helper.hpp"
#endif // _DEBUG
#include "wss/named_formula_exception.hpp"
#include "wss/reference_table_coverage.hpp"
#include "wss/scoped_neutral_locale_enforcer.hpp"


class free_formula_impl
    : public abstract_dependency
    , boost::noncopyable
{

    typedef free_formula_internal::shared_ff_impl_type shared_ff_impl_type;

    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );
#ifdef _DEBUG
    friend class debug_logging_helper;
#endif // _DEBUG
public:
    static shared_ff_impl_type create( free_formula& parent_ff, const sheet_point& position = sheet_point( 0, 0 ) ) {
        return boost::make_shared<free_formula_impl>( boost::ref( parent_ff ), position );
    }

    static shared_ff_impl_type create( free_formula& parent_ff, session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position, const bool adjust_legacy_references )  {
        shared_ff_impl_type new_ff_impl( create( parent_ff ) );
        new_ff_impl->add_named_formula( s, v, ws, position, adjust_legacy_references );
        return new_ff_impl;
    }
    //     static geometry::point minus( const geometry::point& p ) {
    //         return geometry::point( -p.row(), -p.column() );
    //     }
    static shared_ff_impl_type create( free_formula& parent_ff, const shared_ff_impl_type& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const sheet_point& position, const shared_worksheet_type& ws )  {
        shared_ff_impl_type new_ff_impl( create( parent_ff, position ) );
        new_ff_impl->clone_named_formula( other, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, ws );
        return new_ff_impl;
    }

    ~free_formula_impl() {
        m_named_formula.reset();

#ifdef _DEBUG
        --m_counter;
#endif // _DEBUG
    }

    void add_named_formula( session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position, const bool adjust_legacy_references ) {
#ifdef _DEBUG
        friendly_name( v.as_string( s.locale() ) );
#endif // _DEBUG

        set_formula(
            named_formula::create( true, ws, create_random_name(), s, v, adjust_legacy_references ? sheet_point( 0, 0 ) : position, false, true ),
            position,
            adjust_legacy_references,
            true,
            false
        );
        if ( s.is_loading() ) {
            m_reinit_info.reset( new reinit_info( v ) );
        }
    }

    void clone_named_formula( const shared_ff_impl_type& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const shared_worksheet_type& ws ) {

#ifdef _DEBUG
        friendly_name( other->friendly_name() );
#endif // _DEBUG
        m_special_caching = other->m_special_caching;
        set_formula(
            named_formula::create(  other->get_real_nf(), distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, ws ),
            sheet_point( 0, 0 ),
            false,
            false,
            true
        );
    }

    void register_self() {
        if ( nf() ) {
            m_nf_dependency_wrapper->register_dependent( shared_from_this() );
        }
    }
    void unregister_self() {
        if ( nf() ) {
            m_nf_dependency_wrapper->unregister_dependent( shared_from_this() );
        }
    }

    void set_formula( const shared_dependency_type& formula, const sheet_point& position, const bool adjust_legacy_references, const bool set_position, const bool need_unload ) {
        if ( need_unload ) {
            unload();
        }
        m_named_formula = formula;
        if ( ! m_named_formula ) {
            throw named_formula_exception();
        }
        if ( set_position ) {
            m_position = position;
            if ( adjust_legacy_references ) {
                boost::static_pointer_cast<named_formula>( m_named_formula )->adjust_legacy_references( position );
            }
        }
        if ( m_special_caching ) {
            boost::static_pointer_cast<named_formula>( m_named_formula )->set_special_caching();
        }
        register_self();

    }

    void unload() {
        if ( m_named_formula ) {
            unregister_self();
            boost::shared_static_cast<named_formula>( m_named_formula )->unregister_reference( shared_from_this() );
            m_nf_dependency_wrapper.reset();
            boost::shared_static_cast<named_formula>( m_named_formula )->unload();
            m_named_formula.reset();
        }
    }


    inline const shared_dependency_type& nf() const {
        if ( !m_nf_dependency_wrapper && m_named_formula ) {
            const_cast<free_formula_impl*>( this )->m_nf_dependency_wrapper = boost::shared_static_cast<named_formula>( m_named_formula )->get_proxy( const_cast<free_formula_impl*>( this )->shared_from_this() );
        }
        return m_nf_dependency_wrapper;
    }

    inline void trigger_register_dependent() {
        if ( m_named_formula && m_reinit_info.get() != NULL ) {
            m_reinit_info->m_reinit_pending = true;
        }
        register_self();
    }

    shared_named_formula_type get_real_nf() const {
        if ( m_named_formula ) {
            return boost::shared_static_cast<named_formula>( m_named_formula );
        } else {
            return shared_named_formula_type();
        }
    }

    void position( const sheet_point& position ) const {
        m_position = position;
    }

    bool moved( session& s ) const {
        if ( m_named_formula ) {
            return boost::shared_static_cast<named_formula>( m_named_formula )->moved( s );
        }
        return false;
    }

    virtual dependency_type type() const {
        return i_dependency::free_formula_type;
    }

    bool has_formula() const {
        return true;
    }

    bool has_precedents() const {
        return false;
    }

    referencetable_type precedents() const {
        return referencetable_type();
    }

    void value( session&, const variant&, const sheet_point& ) {}

    variant value( interpreter_context& ic ) const {
        return variant();
    }

    variant value( calculation_context& cc ) const {
        if ( m_reinit_info.get() != NULL && m_reinit_info->m_reinit_pending && m_named_formula ) {
            // TODO: this isn't nice
            shared_scoped_neutral_locale_enforcer scnlf = shared_scoped_neutral_locale_enforcer( new scoped_neutral_locale_enforcer( cc.session() ) );
            boost::shared_static_cast<named_formula>( m_named_formula )->value( cc.session(), m_reinit_info->m_formula, m_position, false );
            m_reinit_info.reset();
        }
        return nf() ? nf()->value( cc ) : variant();
    }

    std::string formula( const locale& l ) const {
        return nf() ? nf()->formula( l ) : "";
    }

    std::string formula_without_sheet_references( const locale& l ) const {
        if ( nf() ) {
            return boost::shared_static_cast<named_formula_dependency_wrapper>( nf() )->formula_without_sheet_references( l );
        }
        return "";
    }

    void calculate( calculation_context& cc ) {
        if ( nf() ) {
            nf()->calculate( cc );
        }
    }

    void calculate( interpreter_context& ic ) {
        if ( nf() ) {
            nf()->calculate( ic );
        }
    }

    weak_worksheet_type worksheet() const {
        if ( m_named_formula ) {
            return m_named_formula->worksheet();
        }
        return weak_worksheet_type();
    }

    optional_variant_type fetch_cached_volatile( calculation_context& cc ) const {
        return nf() ? nf()->fetch_cached_volatile( cc ) : optional_variant_type();
    }

    bool is_dirty() const {
        if ( m_reinit_info.get() != NULL && m_reinit_info->m_reinit_pending ) {
            return true;
        }
        return nf() ? nf()->is_dirty() : false;
    }

    bool is_volatile() const {
        return nf() ? nf()->is_volatile() : false;
    }

    bool is_array() const {
        return false;
    }

    sheet_range array_coverage() const {
        return sheet_range( sheet_point( 0, 0 ) );
    }

    const sheet_point& position() const {
        return m_position;
    }

    void flag_relative() {}

    void internal_raise_volatile_count() {}

    void internal_lower_volatile_count() {}

    /*!
     * \brief
     * returns the current volatile count (including self)
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    unsigned long volatile_count() const {
        return nf() ? nf()->volatile_count() : 0;
    }

    /*!
    * \brief
    * returns the current volatile count (excluding self)
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    unsigned long volatile_count_without_formula() const {
        return nf() ? nf()->volatile_count_without_formula() : 0;

    }

    void internal_flag_dirty() {
        //m_parent.flag_dirty();
        if ( nf() ) {
            nf()->internal_flag_dirty();
        }
    }

    void flag_moved() {}

    bool update_position( const sheet_point& new_position ) {
        if ( new_position == m_position ) {
            return false;
        }
        const geometry::point distance = m_position.distance( new_position );
        m_position = new_position;
        if ( m_named_formula ) {
            unregister_self();

            boost::shared_static_cast<named_formula>( m_named_formula )->update_position( shared_from_this(), distance );

            register_self();
        }
        return true;
    }

    unsigned int number_of_covered_columns() const {
        return nf() ? reference_table_coverage::number_of_covered_columns( nf()->precedents() ) : 0;
    }

    void set_special_caching() {
        m_special_caching = true;
        if ( m_named_formula ) {
            boost::shared_static_cast<named_formula>( m_named_formula )->set_special_caching();
        }
    }

    bool put_in_general_cache() const {
        return !m_special_caching;
    }

#ifdef _DEBUG
    std::string get_debug_identifier() const {
        return "[free formula nf is " + debug_logging_helper::get_identifier( m_named_formula ) + "]";
    }
#endif // _DEBUG

protected:
    variant internal_value( interpreter_context& ic ) {
        return nf() ? nf()->value( ic ) : variant();
    }

    void internal_calculate( interpreter_context& ) {}
private:
    inline static std::string create_random_name() {
#ifdef _DEBUG
        return "ff" + boost::lexical_cast<std::string>( boost::uuids::random_generator()() );
#else
        return "";
#endif // _DEBUG
    }



private:
    free_formula_impl( free_formula& parent_ff, const sheet_point& position )
        : m_parent( parent_ff )
        , m_position( position )
        , m_special_caching( false ) {

#ifdef _DEBUG
        ++m_counter;
#endif // _DEBUG
    }

    free_formula& m_parent;
    shared_dependency_type m_named_formula;
    shared_dependency_type m_nf_dependency_wrapper;
    mutable sheet_point m_position;
    //this will only have one precedent (the named formula)
    referencetable_type m_precedents_dummy;
    bool m_special_caching;
    struct reinit_info {
        reinit_info( const variant& v ) : m_formula( v ), m_reinit_pending( false ) {}
        variant m_formula;
        bool m_reinit_pending;
    };
    typedef std::auto_ptr<reinit_info> reinit_info_type;
    mutable reinit_info_type m_reinit_info;
#ifdef _DEBUG
public:
    static size_t m_counter;
#endif // _DEBUG
};
