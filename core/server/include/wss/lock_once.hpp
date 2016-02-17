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

#include <wss/object_not_found_exception.hpp>

/*!
 * \brief
 *
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class shared_T
, class exception_T = object_not_found_exception
>
class lock_once
{
public:
    typedef boost::shared_ptr<shared_T> shared_type;
    typedef boost::weak_ptr<shared_T> weak_type;

    /*!
     * \brief
     * will maintain an shared_ptr to the guardian object
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class scoped_reference
    {
    public:
        scoped_reference( const shared_type& g )
            : m_sp( g ) {
            if ( ! m_sp ) {
                throw exception_T();
            }
        }

        const typename shared_type::element_type* operator ->() const {
            return m_sp.operator ->();
        }

        typename shared_type::element_type* operator ->() {
            return m_sp.operator ->();
        }

    private:
        shared_type m_sp;
    };

    lock_once( const weak_type& wp )
        : m_wp( wp ) {}

    lock_once( const lock_once& other )
        : m_wp( other.m_wp ) {}

    scoped_reference operator ->() const {
        return scoped_reference( m_wp.lock() );
    }

    weak_type guardian_object() const {
        return m_wp;
    }

private:
    weak_type m_wp;
};

