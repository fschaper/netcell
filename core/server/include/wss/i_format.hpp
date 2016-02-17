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

#include <wss/exception.hpp>
#include <wss/session.hpp>
#include <wss/application.hpp>

/*!
 * \brief
 * interface to an abstract format engine.
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
class WSS_MODULE i_format
{
public:
    typedef std::vector< std::string > import_filter_extension_list_type;

    /*!
     * \brief
     * virtual destructor
     *
     * \author
      * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual ~i_format() {}

    /*!
     * \brief
     * returns the a string containing a formatted value.
     *
     * \param server
     * server instance.
     *
     * \param format
     * a format string in the general locale.
     *
     * \param value
     * a value to be formatted.
     *
     * \param ret_val
     * a string representing the format string applied to the value.
     *
     * \returns
     * nothing
     *
     * \throws std::exception
     * will throw an exception format cannot be parsed
     *
     * \author
      * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual std::string formatted_value( session& s, const std::string& format, const variant& value ) = 0;

    /*!
     * \brief
     * returns the a string containing a format color.
     *
     * \param server
     * server instance.
     *
     * \param format
     * a format string in the general locale.
     *
     * \param value
     * a value to be formatted.
     *
     * \param ret_val
     * a string representing the format color applied to the value.
     *
     * \returns
     * nothing
     *
     * \throws std::exception
     * will throw an exception format cannot be parsed
     *
     * \author
      * Vali Nitu <vali@yalos-solutions.com>
     */
    virtual std::string formatted_color( session& s, const std::string& format, const variant& value ) = 0;


    /*!
     * \brief
     * returns the a string containing a formatted value.
     *
     * \param server
     * server instance.
     *
     * \param format
     * a format string in the user locale
     *
     * \param value
     * a value to be formatted.
     *
     * \param ret_val
     * a string representing the format string applied to the value.
     *
     * \returns
     * nothing
     *
     * \throws std::exception
     * will throw an exception format cannot be parsed
     *
     * \author
      * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual std::string formatted_value_locale( session& s, const std::string& format, const variant& value ) = 0;

    /*!
     * \brief
     * translates a language dependent format descriptor to a language independent one.
     *
     * \param server
     * server instance.
     *
     * \param format
     * a format string.
     *
     * \param ret_val
     * a string representing the language independent format string
     *
     * \returns
     * a string representing the language independent format string
     *
     * \throws std::exception
     * will throw an exception format cannot be parsed
     *
     * \author
      * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual std::string generic_format_string( session& s, const std::string& format ) = 0;

    /*!
     * \brief
     * tries to revert a formatted string to its original value and format..
     *
     * \param session
     * session.
     *
     * \param formatted_value
     * the formatted string to revert.
     *
     * \param value
     * the original value
     *
     * \param format
     * the original format
     *
     * \returns
     * true if a value/format was found
     *
     * \author
      * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    virtual bool find_format( session& s, const std::string& formatted_value, variant& value, std::string& format ) = 0;

    /*!
     * \brief
     * get the language dependent default format.
     *
     * \param locale
     * a locale string.
     *
     * \param format_if
     * format to retreive.
     *
     * \param ret_val
     * a string representing the language dependent format string
     *
     * \returns
     * a string representing the language independent format string
     *
     * \throws std::exception
     * will throw an exception format cannot be parsed
     *
     * \author
      * Vali Nitu <vali@yalos-solutions.com>
     */
    virtual std::string default_format_string( const locale& l, const unsigned int format_id ) = 0;


};
