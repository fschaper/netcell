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

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/i_dependency.hpp>
#include <wss/variable_map.hpp>
#include <wss/session.hpp>


#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/noncopyable.hpp>
# include <string>
#endif

class locale;
class translation_map;

/*!
 * \brief
 * parsing context.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE parsing_context
    : boost::noncopyable
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    parsing_context( ::session& s, const weak_worksheet_type& current_worksheet, const std::string& formula );

    /*!
     * \brief
     * formula to be parsed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& formula() const;

    /*!
     * \brief
     * user session object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::session& session() const;

    /*!
     * \brief
     * users locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::locale& locale() const;

    /*!
     * \brief
     * currently selected worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type worksheet() const;

    /*!
     * \brief
     * active translation map.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::translation_map& active_translation() const;

private:
    mutable ::session& m_session;
    weak_worksheet_type m_current_worksheet;
    const std::string& m_formula;
    ::translation_map& m_translation_map;
};



