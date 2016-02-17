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
#include <wss/i_dependency_reference.hpp>
#include <wss/dependency_node_reference.hpp>
#include <wss/named_formula_scope.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/enable_shared_from_this.hpp>
# include <boost/scoped_ptr.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class adjust_dependencies;
class locale;

struct named_formula_wrapper;
typedef boost::shared_ptr<named_formula_wrapper> shared_named_formula_wrapper_type;

class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;

class named_formula_reference;

typedef boost::shared_ptr<named_formula_reference> shared_named_formula_reference_type;
typedef boost::weak_ptr<named_formula_reference> weak_named_formula_reference_type;

/*!
 * \brief
 * named formula reference.
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class named_formula_reference
    : public i_dependency_reference
    , public boost::enable_shared_from_this<named_formula_reference>
{
    friend class adjust_dependencies;
    template< class T, class A1, class A2, class A3, class A4, class A5 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const& );
    template<bool t>
    friend class opcode_interpreterT;
    friend class opcode_pretty_printer;

public:
    ~named_formula_reference();

    virtual reference_type type() const;

    virtual weak_worksheet_type worksheet() const;
    weak_worksheet_type nf_worksheet() const;

    const utf8_ci_string name() const;

    const std::string formula( const locale& l ) const;

    const weak_dependency_type& dependent();

    const bool is_valid() const;

    shared_dependency_type named_formula() const;
    shared_dependency_type real_nf() const;

    static shared_reference_type create( const shared_dependency_type& dependent, const shared_worksheet_type& ws, const utf8_ci_string& name, /*const shared_locked_dependency_type& precedents,*/ const named_formula_scope::type scope, const shared_named_formula_wrapper_type& nf );

    void unload();

    const named_formula_scope::type scope() const;

    bool has_relative_references() const;

    shared_dependency_type precedent() const;

    void update_position( const geometry::point& distance );

    bool nf_is_workbook_scope() const;

private:
    void update_wrapper( const shared_named_formula_wrapper_type& other );
    const bool better_fit( const shared_named_formula_wrapper_type& other ) const;

    named_formula_reference( const shared_dependency_type& dependent, const shared_worksheet_type& ws, const utf8_ci_string& name, /*const shared_locked_dependency_type& precedents,*/ const named_formula_scope::type scope, const shared_named_formula_wrapper_type& nf );

    named_formula_reference& operator =( const named_formula_reference& );

    const shared_named_formula_wrapper_type& internal_access() const;
private:
    //references to the manager and the name
    weak_worksheet_type m_target_worksheet;
    utf8_ci_string m_name;
    weak_dependency_type m_dependent;
    shared_named_formula_wrapper_type m_nf;
    bool unload_called;
    named_formula_scope::type m_scope;
    boost::scoped_ptr<ci_string> m_scope_name;
    bool m_is_redirected;
#ifdef _DEBUG
public:
    static size_t m_counter;
#endif
};

inline named_formula_reference& named_formula_reference_cast( const shared_reference_type& srr )
{
    assert( "reference is not of named formula type!" && srr->type() == i_dependency_reference::named_formula_reference );
    return *boost::shared_static_cast<named_formula_reference>( srr ).get();
}
