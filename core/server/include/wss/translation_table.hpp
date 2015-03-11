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
#include <wss/translation_map.hpp>
#include <wss/singleton.hpp>
#include <wss/locale.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <map>
#endif

/*!
 * \brief
 * function translation table.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE translation_table
    : public singleton<translation_table>
{
    FRIEND_CLASS singleton<translation_table>;
    typedef std::map< ::locale, shared_translation_map_type> language_map_type;
public:
    /*!
     * \brief
     * retreive a translation table entry for the given locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const shared_translation_map_type& operator[] ( const ::locale& l ) const;

    /*!
     * \brief
     * has a translation table for the given locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has( const ::locale& l ) const;

    /*!
     * \brief
     * add a translation table entry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add( const shared_translation_map_type& map );

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    translation_table();

private:
    language_map_type m_entry_map;
};

