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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#pragma once
#include <wss/interpreter_variant.hpp>
#include <wss/type.hpp>
#include <wss/return_type_format.hpp>
#include <wss/stack.hpp>
#include <wss/key_value_set.hpp>
#include <wss/default_format_serializer.hpp>
#include <wss/default_format_unserializer.hpp>


#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#endif

class session;

/*!
 * \brief
 * user preferred return functions format.
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
class WSS_MODULE user_return_format
{
public:
    typedef ::stack<interpreter_variant> calculation_stack_type;

    typedef key_value_set<default_format_serializer, default_format_unserializer> default_format_set_type;

    user_return_format( const session& session  );

    const std::string& format( const return_type_format::type rt );

    default_format_set_type& default_format();

    void default_format( const default_format_set_type new_format );

    void load_user_format( const locale& l );

private:

private:
    std::string m_numeric_return_format;
    std::string m_date_return_format;
    std::string m_datetime_return_format;
    std::string m_unspecified_format;
    bool m_loaded;
    calculation_stack_type m_stack;
    default_format_set_type m_default_format_map;
    const   session&            m_session;
};

