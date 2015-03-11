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
#include <wss/variant.hpp>
#include <wss/formula.hpp>
#include "named_formula.hpp"

class named_formula_calculation;

class named_formula_kernel
    : public boost::enable_shared_from_this<named_formula_kernel>
{
    friend class named_formula;
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    named_formula_kernel( const shared_dependency_type& container, ast_formula& ast, const referencetable_type& references );

    named_formula_kernel( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet );

    named_formula_kernel( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references );
public:
    ~named_formula_kernel();

    void connect_precedents();

    void connect_precedents( const shared_dependency_type& d );

    void disconnect_precedents( const shared_dependency_type& d );

    void disconnect_precedents(  );

    bool has_precedents() const;

    referencetable_type precedents() const;

    referencetable_type precedents( const shared_dependency_type& d ) const;

    std::string formula( const locale& l ) const;
    std::string formula_without_sheet_references( const locale& l ) const;

    std::string formula( const locale& l, const shared_dependency_type& d ) const;
    std::string formula_without_sheet_references( const locale& l, const shared_dependency_type& d ) const;

    variant value() const;

    named_formula_calculation delayed_calculation( calculation_context& cc );

    optional_variant_type fetch_cached_volatile( calculation_context& cc ) const;

    optional_variant_type fetch_cached_volatile( calculation_context& cc, const shared_dependency_type& d ) const;

    inline bool is_dirty( const shared_dependency_type& d ) const {
        return m_formula.is_relative() ? m_formula.is_dirty( d ) : m_is_dirty;
    }

    bool is_dirty() const {
        return m_is_dirty;
    };

    bool is_volatile() const;

    bool is_volatile( const shared_dependency_type& d ) const;

    inline unsigned long volatile_count() const {
        return m_volatile_count + ( m_formula.is_volatile() ? 1 : 0 );
    }

    unsigned long volatile_count( const shared_dependency_type& d ) const;

    inline unsigned long volatile_count_without_formula() const {
        return m_volatile_count;
    }
    unsigned long volatile_count_without_formula( const shared_dependency_type& d ) const;

    void flag_dirty( const shared_dependency_type& d );
    void flag_dirty();

    inline void internal_raise_volatile_count() {
        ++m_volatile_count;
    }

    void internal_raise_volatile_count( const shared_dependency_type& d );

    void internal_lower_volatile_count( const shared_dependency_type& d );

    inline void internal_lower_volatile_count() {
        if ( --m_volatile_count == 0 ) {
            flag_dirty();
        }
    }

    optional_sheet_range_type coverage() const;

    optional_sheet_range_type coverage( const shared_dependency_type& d ) const;

    void update_value( calculation_context& cc, const variant& v, long token_id );

    static shared_named_formula_kernel_type create( const shared_dependency_type& parent, ast_formula& ast, const referencetable_type& reference_table = referencetable_type() );

    static shared_named_formula_kernel_type create( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet );

    static shared_named_formula_kernel_type create ( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references );

    void register_reference( const shared_dependency_type& d );

    void unregister_reference( i_dependency* d );

    void update_position( const shared_dependency_type& d, const geometry::point& distance, const bool move_absolute_references = false );

    void unflag_dirty( const shared_dependency_type& d );

    void update_value( calculation_context& cc, const variant& v, long token_id, const shared_dependency_type& different_initiator );

    void adjust_legacy_references( const sheet_point& position );

    inline bool is_relative() const {
        return m_formula.is_relative();
    }
private:
    inline void register_variables() const;
    inline void unregister_variables() const;
    void unload( const std::list<shared_dependency_type>& m );
    inline void internal_disconnect_precedents( const shared_dependency_type& d );
    shared_dependency_type m_container;
protected:
    ::formula m_formula;
private:
    long m_update_token;
    unsigned int m_volatile_count;
    variant m_cached_value;
    bool m_unload_triggered;
    bool m_is_dirty;

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    template< class T, class A1, class A2, class A3>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const& );

    template< class T, class A1, class A2, class A3, class A4>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const& );

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const&, A6 const&, A7 const& );
};


