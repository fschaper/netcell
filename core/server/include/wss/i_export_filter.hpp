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

#include <wss/session.hpp>
#include <wss/workbook.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#include <boost/filesystem/path.hpp>
#endif

/*!
 * \brief
 * filter to export data in some arbitrary format from an application.
 *
 * the filter will be registered for an file type and be called with an
 * output stream to serialize an workbook into the arbitrary format.
 *
 * \see
 * i_import_filter | server
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE i_export_filter
{
public:
    typedef std::vector< std::string > export_filter_extension_list_type;

    /*!
     * \brief
     * virtual destructor
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~i_export_filter() {}

    /*!
     * \brief
     * returns a string list of known file extensions.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual const export_filter_extension_list_type& extensions() const = 0;

    /*!
     * \brief
     * export will be called with an output stream for n file of the registered type with the users
     * context and the target workbook to export.
     *
     * \param session
     * users session.
     *
     * \param application
     * application object where the data shall be exported from.
     *
     * \param out_file
     * path to the file to serialize to.
     *
     * \throws export_exception
     * if an exception must be thrown in the export filter it should be derived by the ExportException
     * base class.
     *
     * \see
     * i_import_filter
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
#ifdef _WIN32
# pragma warning( disable : 4290 )
#endif
    virtual void do_export( session& s, workbook& wb, const boost::filesystem::path& out_file, const bool as_snapshoot = false, const bool is_native = true ) = 0;
#ifdef _WIN32
# pragma warning( default : 4290 )
#endif
};
