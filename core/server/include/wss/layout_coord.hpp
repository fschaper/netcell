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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <wss/i_dependency.hpp>

class layout_coord : public i_dependency
{
    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );
private:
    layout_coord( weak_worksheet_type ws, bool is_row );
    void recompute( calculation_context& cc );
public:
    static shared_dependency_type create( weak_worksheet_type ws, bool is_row );

    void worksheet( weak_worksheet_type& ws );

    virtual dependency_type type() const;
    virtual bool has_formula() const;
    virtual bool has_precedents() const;
    virtual bool has_dependents() const;
    virtual referencetable_type precedents() const;
    virtual referencetable_type precedents( const shared_dependency_type& sd ) const;

    virtual const dependency_set_type& dependents() const;
    virtual variant value( calculation_context& cc ) const;
    virtual variant value( interpreter_context& ic ) const;
    virtual void value( session&, const variant&, const sheet_point& position = sheet_point( 0, 0 ) );
    virtual std::string formula( const locale& l ) const;
    virtual void calculate( interpreter_context& );
    virtual void calculate( calculation_context& );
    virtual weak_worksheet_type worksheet() const;
    virtual void register_dependent( const shared_dependency_type& dep );
    virtual void unregister_dependent( const shared_dependency_type& );
    virtual optional_variant_type fetch_cached_volatile( calculation_context& cc ) const;
    virtual bool is_dirty() const;
    virtual bool is_volatile() const;
    virtual bool is_array() const;
    virtual sheet_range array_coverage() const;
    virtual bool flag_dirty( const bool flag_dirty_even_if_volatile = false );
    virtual const sheet_point& position() const;
    virtual void flag_relative();
    virtual void raise_volatile_count();
    virtual void lower_volatile_count();
    virtual unsigned long volatile_count() const;
    virtual unsigned long volatile_count_without_formula() const;
    virtual void internal_flag_dirty();
    virtual void internal_raise_volatile_count();
    virtual void internal_lower_volatile_count();
    virtual void flag_moved();
    virtual optional_sheet_range_type coverage() const;
#ifdef _DEBUG
    std::string get_debug_identifier( void ) const;
#endif

    //i_lockable
    void lock();
    bool try_lock();
    void unlock();

private:
    bool m_is_dirty;
    unsigned int m_value;
    std::set< weak_dependency_type >  m_cells;
    weak_worksheet_type m_worksheet;
    bool m_is_row;
};
