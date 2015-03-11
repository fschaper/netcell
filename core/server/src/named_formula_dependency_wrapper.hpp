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

#include "wss/variant.hpp"
#include "wss/sheet_point.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/type.hpp"

#include "named_formula.hpp"
#include "abstract_dependency.hpp"

/*!
 * \brief
 * named formula dependency wrapper this one is created every time a named formula is used somewhere (i.e. in a cell)
 *
 * TODO more documentation
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */

class named_formula_dependency_wrapper
    : public abstract_dependency
{
    friend class named_formula_kernel;
    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );
    friend class debug_logging_helper;
    friend class named_formula;
    friend class range_lock;
    struct tag_on_dirty;
    struct tag_on_moved;
public:
    boost::signal < void( named_formula&, const tag_on_dirty& ) > on_flag_dirty;
    boost::signal < void( named_formula&, const tag_on_moved& ) > on_moved;

    ~named_formula_dependency_wrapper();

    const uuid_type& uuid() const;

    const utf8_ci_string& name() const;

    virtual dependency_type type() const;

    bool has_formula() const;

    bool has_precedents() const;

    referencetable_type precedents() const;

    void value( session&, const variant&, const sheet_point& );

    variant value( calculation_context& cc ) const;

    std::string formula( const locale& l ) const;

    std::string formula_without_sheet_references( const locale& l ) const;

    void calculate( calculation_context& cc );

    weak_worksheet_type worksheet() const;

    optional_variant_type fetch_cached_volatile( calculation_context& cc ) const;

    bool is_dirty() const;

    bool is_volatile() const;

    bool is_array() const;

    sheet_range array_coverage() const;

    const sheet_point& position() const;

    void flag_relative() {}

    void internal_raise_volatile_count();

    void internal_lower_volatile_count();

    unsigned long volatile_count() const;

    /*!
     * \brief
     * returns the current volatile count (excluding self)
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    unsigned long volatile_count_without_formula() const;

    void internal_flag_dirty();

    void flag_moved();

    void update_position( const geometry::point& distance );

    bool moved( session& s ) const;

    optional_sheet_range_type coverage() const;

    inline bool check_if_initiator_is_free_formula() const {
        if ( shared_dependency_type initiator = m_initiator.lock() ) {
            return initiator->type( ) == i_dependency::free_formula_type;
        }
        return false;
    }

    bool put_in_general_cache() const;

    inline const bool is_inside_ff() const {
        return m_is_inside_ff;
    }

    void trigger_register_dependent() const;

    inline shared_dependency_type parent_nf() const {
        return m_parent.lock();
    }

protected:
    virtual variant internal_value( interpreter_context& ic );

    virtual void internal_calculate( interpreter_context& );

private:
    void update_value( calculation_context& cc, const variant& v, long token_id );

#ifdef _DEBUG
    std::string get_debug_identifier() const;
#endif // _DEBUG

private:
    static shared_dependency_type create( const shared_dependency_type& initiator, const shared_dependency_type& parent_named_formula );

    named_formula_dependency_wrapper( const shared_dependency_type& initiator, const shared_dependency_type& parent_named_formula );
    void connect_precedents();
    inline void disconnect_precedents();
private:
    struct nf_dep_helper;
    typedef named_formula::locked_kernel_type locked_kernel_type;

    weak_dependency_type m_parent;
    weak_dependency_type m_initiator;

    long m_update_token;
    mutable variant m_cached_value;
    mutable bool m_got_moved;
    const bool m_is_inside_ff;
#ifdef _DEBUG
public:
    std::string m_debug_name;
    static size_t m_counter;
#endif
};
