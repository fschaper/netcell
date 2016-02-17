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

#include <wss/define.hpp>
#include <wss/singleton.hpp>
class i_import_filter;
class i_export_filter;

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/scoped_ptr.hpp>
# include <boost/noncopyable.hpp>
#endif

/*!
 * \brief
 * server wide function catalog.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE filter_registry
    : public singleton<filter_registry>
{
    FRIEND_CLASS singleton<filter_registry>;
public:
    typedef boost::shared_ptr<i_import_filter> shared_import_filter_type;
    typedef boost::shared_ptr<i_export_filter> shared_export_filter_type;

    void register_import_filter( const shared_import_filter_type& filter );
    void register_export_filter( const shared_export_filter_type& filter );

    shared_import_filter_type get_import_filter( const std::string& file_extension );
    shared_export_filter_type get_export_filter( const std::string& file_extension );
private:
    filter_registry() {};
private:
    typedef std::map<std::string, shared_import_filter_type> import_filter_table_type;
    typedef std::map<std::string, shared_export_filter_type> export_filter_table_type;

    import_filter_table_type m_import_filter_table;
    export_filter_table_type m_export_filter_table;
};

