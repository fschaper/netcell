/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

namespace xlsx
{

    struct persistent_version_info {
        long m_major;
        long m_minor;
        bool m_valid;
        persistent_version_info() : m_major( 0 ), m_minor( 0 ), m_valid( false ) {};
        persistent_version_info( long major, long minor ) : m_major( major ), m_minor( minor ), m_valid( true ) {};
        inline persistent_version_info& operator=( const persistent_version_info& other ) {
            if ( this == &other ) {
                return *this;
            }

            m_valid = other.m_valid;
            m_minor = other.m_minor;
            m_major = other.m_major;

            return *this;
        }

        bool is_core3() {
            return m_valid && m_major >= 1 && m_minor >= 6;
        }
    };

}
