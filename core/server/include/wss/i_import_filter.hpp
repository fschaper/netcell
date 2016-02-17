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
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#include <boost/filesystem/path.hpp>
#endif

/*!
 * \brief
 * filter to import data in some arbitrary format into an application.
 *
 * the filter will be registered for an file type and be called with an
 * input stream that it needs to handle to modify the application.
 *
 * \see
 * i_export_filter | server
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE i_import_filter
{
public:
    typedef std::vector< std::string > import_filter_extension_list_type;

    /*!
     * \brief
     * virtual destructor
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~i_import_filter() {}

    /*!
     * \brief
     * returns a string list of known file extensions.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual const import_filter_extension_list_type& extensions() const = 0;

    /*!
     * \brief
     * import will be called with an input stream for a file of the registered type with the users
     * context and the target application to import to.
     *
     * \param session
     * users session context.
     *
     * \param application
     * application object where the data shall be imported.
     *
     * \param in_stream
     * path to the file to interpret.
     *
     * \return
     * returns the uuid of the imported workbook
     *
     * \throws import_exception
     * if an exception must be thrown in the import filter it should be derived by the import_exception
     * base class.
     *
     * \see
     * i_export_filter
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
#ifdef _WIN32
# pragma warning( disable : 4290 )
#endif
    virtual shared_workbook_type do_import( session& s, application& a, std::vector<std::string> & report, const boost::filesystem::path& in_file, const bool is_native = true ) = 0;
    virtual bool extended_data_import( session& s, application& a, const boost::filesystem::path& in_file ) = 0;
#ifdef _WIN32
# pragma warning( default : 4290 )
#endif
};
