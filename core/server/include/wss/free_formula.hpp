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
#include <wss/on_event_handler_helper.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/thread/mutex.hpp>
# include <boost/make_shared.hpp>
# include <boost/signal.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;
class variant;
class free_formula;
class worksheet_element;
class free_formula_impl;

typedef boost::shared_ptr<free_formula> shared_free_formula_type;
namespace free_formula_internal
{
    typedef boost::shared_ptr<free_formula_impl> shared_ff_impl_type;
};
/*!
 * \brief
 * class containing a named formula that is used outside of a cell
 * but should still be able to calculate and return its value, position, etc.
 *
 * \note this class is not thread safe! so locking needs to be done on a higher level!
 *
 * \details
 * TODO
 *
 * \see
 * named_formula | worksheet_element
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class free_formula
    : boost::noncopyable
{
    friend class worksheet_element;
    template< class T, class A1, class A2, class A3, class A4, class A5>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const& );
    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const&, A6 const&, A7 const& );

#ifdef _DEBUG
    friend class debug_logging_helper;
#endif // _DEBUG
    typedef free_formula_internal::shared_ff_impl_type shared_ff_impl_type;
public:
    ~free_formula();

    static shared_free_formula_type create( session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool adjust_legacy_references = false );

    static shared_free_formula_type create( const shared_free_formula_type& other, const geometry::point& distance, const bool is_rewrite_to_clone_sheet, const bool use_copy_move, const sheet_range& source_range, const sheet_point& position, const shared_worksheet_type& ws );

    bool is_dirty( session& s, const sheet_point& position = sheet_point( 0, 0 )  ) const;

    sheet_point position() const;

    std::string formula( const locale& l, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    std::string formula_without_sheet_references( const locale& l, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    variant value( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    void value( session& s, const variant& v, const sheet_point& position = sheet_point( 0, 0 ) );

    bool moved( session& s );

    bool is_valid() const;

    unsigned int number_of_covered_columns( const sheet_point& position = sheet_point( 0, 0 ) ) const;

    inline void flag_dirty() {}

    void set_special_caching();

    bool is_volatile() const;

private:
#ifdef _DEBUG
    void rename( const std::string& new_name );
    std::string get_debug_identifier() const;
#endif // _DEBUG
    free_formula( session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool adjust_legacy_references = false );
    free_formula( const shared_free_formula_type& other, const geometry::point& distance, const bool is_rewrite_to_clone_sheet, const bool use_copy_move, const sheet_range& source_range, const sheet_point& position, const shared_worksheet_type& ws );
    inline void flag_moved() {}
    inline void set_formula( const shared_ff_impl_type& new_formula );
    inline void unload_formula();


    shared_ff_impl_type m_formula;
    mutable boost::scoped_ptr<variant> m_cached_volatile_val;
    mutable bool m_unloading;
#ifdef _DEBUG
public:
    static size_t m_counter;
#endif // _DEBUG
};
