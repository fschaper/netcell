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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
#endif

#include <wss/type.hpp>
#include <wss/define.hpp>
#include <wss/reference.hpp>
#include <wss/sheet_point.hpp>
#include <wss/sheet_range.hpp>

namespace a1conversion
{
    typedef std::vector<sheet_range> multi_rect_vector_type;

    /*!
     * \brief
     * conversion from a1 notation to POD.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class WSS_MODULE from_a1
    {
    public:
        static unsigned int column( const std::string& column );
        static multi_rect_vector_type ranges( const std::string& a1 );
        static sheet_point cell( const std::string& a1 );
        static sheet_range range( const std::string& a1 );
    };

    /*!
     * \brief
     * conversion point or POD to A1 notation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class WSS_MODULE to_a1
    {
    public:
        /*!
         * \brief
         * provides point to a1 string conversion.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static std::string from_point( const sheet_point& p );

        /*!
         * \brief
         * provides range to a1 string conversion.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static std::string from_range( const sheet_range& p );

        /*!
        * \brief
        * conversion point or POD to A1 notation - encode a column
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static std::string column( unsigned int column, reference::type ref = reference::relative );

        /*!
        * \brief
        * conversion point or POD to A1 notation - encode a row
        *
        * \author
        * Florian Schaper <florian.schaper@jedox.com>
        */
        static std::string row( unsigned int row, reference::type ref = reference::relative );

        /*!
         * \brief
         * tests a workbook or worksheet name if it would
         * need to be put into quotes.
         *
         * f.ex. cell a1 on a sheet named 1sheet1 needs to be refered as '1sheet1'!A1
         * whereas a cell on a sheet named sheet1 would be refered to as sheet1!A1
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static bool needs_quotes( const utf8_ci_string& name );
    };

    /*!
     * \brief
     * stream formatting options
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class formatting
    {
    public:
        /*!
         * \brief
         * format the stream should be switched to.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        enum type {
            numeric
            , a1
        };

        /*!
         * \brief
         * constructor.
         *
         * when set to "a1" sheet_point and sheet_range classes will
         * serialize themselves using A1 notation.
         *
         * \see
         * formatting::as_a1 | formatting::as_numeric
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        formatting( type format );

        /*!
         * \brief
         * return the current formatting setting of the stream.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        type format() const;

        /*!
         * \brief
         * set the stream iword to the requested format
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class char_T, class traits_T>
        friend std::basic_ostream<char_T, traits_T> & operator <<( std::basic_ostream<char_T, traits_T>& os, const formatting& f ) {
            os.iword( formatting::allocator() ) = f.format();
            return os;
        }

        /*!
         * \brief
         * convenience function. set the stream to use the A1 format.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static formatting& as_a1();

        /*!
         * \brief
         * convenience function. set the stream to use the numeric format.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static formatting& as_numeric();

        /*!
         * \brief
         * iostream allocator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        static int allocator();

    private:
        static const int m_a1_stream_ident;
        type m_format;
    };

}

