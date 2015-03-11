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
#include <wss/i_cloneable.hpp>
#include <wss/variant.hpp>
#include <wss/non_instantiable.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/any.hpp>
#endif

/*!
 * \brief
 * maintains clipboard information.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE clipboard_entry
{
public:
    /*!
     * \brief
     * operation mode
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct method
            : non_instantiable {
        enum type { undefined
                    , copy
                    , cut
                    , copy_fill
                    , copy_move
                  };
    };

    /*!
     * \brief
     * entry type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct entry
            : non_instantiable {
        enum type { undefined
                    , range
                    , callback
                  };
    };

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    clipboard_entry( const boost::any& e = boost::any(), method::type mt = method::undefined, entry::type et = entry::undefined );

    /*!
     * \brief
     * get the content.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const boost::any& get() const;

    /*!
     * \brief
     * get the content.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    boost::any get();

    /*!
     * \brief
     * get the method type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    method::type method() const;

    /*!
     * \brief
     * get the entry type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    entry::type type() const;

private:
    boost::any m_entry;
    method::type m_method;
    entry::type m_type;
};

/*!
 * \brief
 * server-side clipboard to be used during copy/move-paste
 * operations.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE clipboard
{
    typedef std::vector<clipboard_entry> clipboard_container_type;
    static const clipboard_container_type::size_type clipboard_ring_size = 32;

public:
    typedef clipboard_container_type::size_type clipboard_id_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    clipboard();

public:
    /*!
     * \brief
     * add a new clipboard entry and retrieve it's id.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    long add( const clipboard_entry& entry );

    /*!
     * \brief
     * retrieve the clipboard entry identified by ID
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const clipboard_entry& get( clipboard_id_type index ) const;

    /*!
     * \brief
     * clear the clipboard.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void clear();

    /*!
     * \brief
     * returns true in case the clipboard is empty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_empty() const;

private:
    clipboard_container_type m_container;
    clipboard_container_type::size_type m_index;
};

