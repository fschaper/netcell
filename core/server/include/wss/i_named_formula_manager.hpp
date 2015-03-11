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

#include <wss/named_formula_scope.hpp>
#include <wss/type.hpp>
#include <wss/friend.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/uuid/uuid.hpp>
# include <boost/uuid/uuid_generators.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class locale;
class variant;
class worksheet;
class named_formula_accessor;
typedef boost::shared_ptr<named_formula_accessor> shared_named_formula_accessor_type;

class WSS_MODULE named_formula_identifier
{

public:
    named_formula_identifier( const std::string& name, const uuid_type& scope_ws_id = boost::uuids::nil_uuid() )
        : m_name( convert_utf8_ci( name ) )
        , m_worksheet_scope_id( scope_ws_id )
    {}

    named_formula_identifier( const utf8_ci_string& name, const uuid_type& scope_ws_id = boost::uuids::nil_uuid() )
        : m_name( name )
        , m_worksheet_scope_id( scope_ws_id )
    {}

    named_formula_identifier( const char* name, const uuid_type& scope_ws_id = boost::uuids::nil_uuid() )
        : m_name( name )
        , m_worksheet_scope_id( scope_ws_id )
    {}

    inline const uuid_type& scope_ws_id() const {
        return m_worksheet_scope_id;
    }

    inline const utf8_ci_string& name() const {
        return m_name;
    }

    inline const bool is_worksheet_scope() const {
        return !is_workbook_scope();
    }

    inline const bool is_workbook_scope() const {
        return m_worksheet_scope_id.is_nil();
    }

private:
    utf8_ci_string m_name;
    uuid_type m_worksheet_scope_id;
};
/*!
 * \brief
 * interface class to interact with named formulas
 *
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE i_named_formula_manager
{
    FRIEND_CLASS worksheet;

public:
    typedef utf8_ci_string string_type;
    typedef std::vector< std::pair<std::string, std::string> > key_val_vec_type;
    typedef std::vector< std::pair<std::string, variant> > named_formula_key_val_vec_type;
    typedef std::vector< key_val_vec_type > key_val_vec_vec_type;

    typedef std::vector < named_formula_key_val_vec_type > named_formula_list_type;

    virtual ~i_named_formula_manager() {}

    virtual shared_reference_type register_dependency( const shared_dependency_type& d, const named_formula_identifier& nf_identifier, const named_formula_scope::type scope ) = 0;

    virtual void create( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool hidden = false ) = 0;

    //will throw if a named formula of that name is already present in this scope!
    virtual shared_named_formula_accessor_type create_and_get_accessor( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool hidden = false ) = 0;

    virtual shared_named_formula_accessor_type get_accessor( session& s, const named_formula_identifier& nf_identifier ) = 0;

    virtual shared_named_formula_accessor_type get_accessor( session& s, const uuid_type& id ) = 0;

    virtual void remove( session& s, const named_formula_identifier& nf_identifier ) = 0;

    virtual void remove( session& s, const uuid_type& id ) = 0;

    virtual void rename( session& s, const uuid_type& id, const std::string& new_name ) = 0;

    virtual void rename( session& s, const named_formula_identifier& nf_identifier, const std::string& new_name ) = 0;

    virtual void comment( const std::string& comment, const named_formula_identifier& nf_identifier ) = 0;

    virtual const std::string& comment( const named_formula_identifier& nf_identifier ) const = 0;

    virtual void value( session& s, const named_formula_identifier& nf_identifier, const variant& v, const sheet_point& position = sheet_point( 0, 0 )  ) = 0;

    virtual variant value( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const = 0;

    virtual variant formula( const locale& l, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const = 0;

    virtual key_val_vec_type get_key_val_vec( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const = 0;

    virtual key_val_vec_type get_key_val_vec( session& s, const uuid_type& id, const sheet_point& position = sheet_point( 0, 0 ) ) const = 0;

    virtual named_formula_list_type get_all( session& s, const uuid_type& sheet_id =  boost::uuids::nil_uuid(), const sheet_point& position = sheet_point( 0, 0 ), const bool show_hidden = false ) = 0;

    virtual key_val_vec_vec_type get_all_as_strings( session& s, const uuid_type& sheet_id =  boost::uuids::nil_uuid(), const sheet_point& position = sheet_point( 0, 0 ), const bool show_hidden = false ) = 0;

    virtual void update( session& s, const uuid_type& id, const std::string& name, const variant& formula, const std::string& comment, const sheet_point& position ) = 0;

    virtual bool exists( const named_formula_identifier& nf_identifier ) const = 0;

protected:
    virtual void unload_sheet( const uuid_type& sheet_id ) = 0;
};
