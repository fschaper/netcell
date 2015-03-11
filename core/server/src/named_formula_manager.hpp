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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *
 */

#pragma once

#include "wss/i_named_formula_manager.hpp"
#include "named_formula_utility.hpp"
#include "wss/ci_string.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/shared_ptr.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class named_formula_reference;
class named_formula;
class worksheet;
class workbook;

typedef boost::shared_ptr<named_formula> shared_named_formula_type;
typedef boost::weak_ptr<named_formula> weak_named_formula_type;

namespace nf
{
    class named_formula_storage;
} //namespace named_formula_storage

class named_formula_manager
    : public i_named_formula_manager
{
    FRIEND_CLASS worksheet;
    FRIEND_CLASS workbook;

public:
    named_formula_manager( workbook* parent );

    ~named_formula_manager();

    void create( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool hidden = false );
    void create( session& s, const named_formula& nf, const shared_worksheet_type& target_ws );

    shared_named_formula_accessor_type create_and_get_accessor( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position = sheet_point( 0, 0 ), const bool hidden = false );

    shared_named_formula_accessor_type get_accessor( session& s, const named_formula_identifier& nf_identifier );

    shared_named_formula_accessor_type get_accessor( session& s, const uuid_type& id );

    void remove( session& s, const named_formula_identifier& nf_identifier );

    void remove( session& s, const uuid_type& id );

    void rename( session& s, const named_formula_identifier& nf_identifier, const std::string& new_name );

    void rename( session& s, const uuid_type& id, const std::string& new_name );

    void value( session& s, const named_formula_identifier& nf_identifier, const variant& v, const sheet_point& position = sheet_point( 0, 0 ) );

    variant value( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    variant formula( const locale& l, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    key_val_vec_type get_key_val_vec( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    key_val_vec_type get_key_val_vec( session& s, const uuid_type& id, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    named_formula_list_type get_all( session& s, const uuid_type& sheet_id =  boost::uuids::nil_uuid(), const sheet_point& position = sheet_point( 0, 0 ), const bool show_hidden = false );

    key_val_vec_vec_type get_all_as_strings( session& s, const uuid_type& sheet_id =  boost::uuids::nil_uuid(), const sheet_point& position = sheet_point( 0, 0 ), const bool show_hidden = false );

    void comment( const std::string& comment, const named_formula_identifier& nf_identifier );

    const std::string& comment( const named_formula_identifier& nf_identifier ) const;

    shared_reference_type register_dependency( const shared_dependency_type& d, const named_formula_identifier& nf_identifier, const named_formula_scope::type scope );

    shared_reference_type register_dependency( const shared_dependency_type& d, const utf8_ci_string& name, const uuid_type& sheet_id, const named_formula_scope::type scope );

    void update( session& s, const uuid_type& id, const std::string& name, const variant& formula, const std::string& comment, const sheet_point& position );

    bool exists( const named_formula_identifier& nf_identifier ) const;

protected:
    void unload_sheet( const uuid_type& sheet_id );

private:
    shared_named_formula_type internal_create( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws,  const sheet_point& position, const bool hidden, const bool get_if_already_defined = false );

    void copy_to_sheet( session& s, const uuid_type& source_ws_id, const shared_worksheet_type& target_ws ) const;

    void clone_to_session_sheet( session& s, const uuid_type& source_ws_id, const shared_worksheet_type& target_ws ) const;

    void unload();

    typedef boost::recursive_mutex mutex_type;
    typedef locked_object<nf::named_formula_storage,  trait::boost_lock_trait<mutex_type > > locked_store_type;
    typedef boost::scoped_ptr<locked_store_type> store_type;
    store_type m_store;
    workbook* m_parent;
};
