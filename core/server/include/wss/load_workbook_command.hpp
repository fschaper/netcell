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

#include <wss/define.hpp>
#include <wss/base_command.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/uuid/uuid.hpp>
#include <boost/filesystem/path.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * save workbook command.
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE load_workbook_command
    : public base_command<i_command>
{
public:
    typedef std::string result_type;

    load_workbook_command( session& s, const boost::filesystem::path& file_path, const std::string& meta_data, const bool overwrite_existing = true, const bool is_temp = false );

    virtual void execute();

    const result_type& value() const;

    DECLARE_CLONEABLE( load_workbook_command );

private:
    const boost::filesystem::path   m_file_path;
    const std::string               m_meta_data;
    const bool                      m_overwrite_existing;
    const bool m_is_temp;
    result_type      m_uuid;
};

