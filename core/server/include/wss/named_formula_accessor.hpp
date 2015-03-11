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
#include "wss/identifiable_object.hpp"
#include "wss/locale.hpp"

class named_formula_accessor;
typedef boost::shared_ptr<named_formula_accessor> shared_named_formula_accessor_type;
class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;
typedef boost::weak_ptr<named_formula> weak_named_formula_type;

class WSS_MODULE named_formula_accessor
    : boost::noncopyable
{
    friend class named_formula_manager;

    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );

public:
    const uuid_type uuid();

    void name( session& s, const std::string& new_name );

    const std::string name();

    void value( session& s, const variant& v, const sheet_point& position = sheet_point( 0, 0 )  ) ;

    variant value( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const ;

    variant formula( const locale& l, const sheet_point& position = sheet_point( 0, 0 ) ) const ;

    void comment( const std::string& comment ) ;

    const std::string& comment() const ;

    const bool is_valid() const;

    void remove( session& s );

    bool has_worksheet_scope( session& s );

    //will return the uuid if scope is worksheet and the worksheet exists, otherwise boost::uuids::nil_uuid()
    const uuid_type& get_scope_uuid( session& s );

private:
    static shared_named_formula_accessor_type create( const shared_workbook_type& managers_parent, const shared_named_formula_type& nf );

    named_formula_accessor( const shared_workbook_type& managers_parent, const shared_named_formula_type& nf );
    weak_workbook_type m_managers_parent;
    weak_named_formula_type m_nf;
};
