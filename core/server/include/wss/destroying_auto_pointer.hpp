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
#   include <algorithm> // std::swap
#endif

#ifndef NULL
# define NULL 0
#endif

/*!
 * \brief
 * auto pointer that will call a destroy method
 * on the object being held on destruction.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class base_T
>
class destroying_auto_pointer
{
    typedef base_T* pointer_type;
    typedef base_T& reference_type;
public:
    destroying_auto_pointer( pointer_type pointer = NULL )
        : m_pointer( pointer ) {}

    destroying_auto_pointer<base_T>( const destroying_auto_pointer<base_T>& other )
        : m_pointer( NULL ) {
        reset( other.m_pointer );
        other.m_pointer = NULL;
    }

    ~destroying_auto_pointer() {
        reset();
    }

    destroying_auto_pointer<base_T>& operator =( const destroying_auto_pointer<base_T>& other ) {
        destroying_auto_pointer<base_T> tmp( other );
        swap( tmp );
        return *this;
    }

    void swap( destroying_auto_pointer<base_T>& other ) {
        std::swap( m_pointer, other.m_pointer );
    }

    void reset( pointer_type pointer = NULL ) {
        if ( m_pointer ) {
            m_pointer->destroy();
        }
        m_pointer = pointer;
    }

    pointer_type release() {
        pointer_type return_value = m_pointer;
        m_pointer = NULL;
        return return_value;
    }

    pointer_type get() const {
        return m_pointer;
    }

    reference_type operator * () const {
        return *m_pointer;
    }

    pointer_type operator ->() const {
        return m_pointer;
    }

    operator bool() const {
        return m_pointer != NULL;
    }

private:
    mutable pointer_type m_pointer;
};
