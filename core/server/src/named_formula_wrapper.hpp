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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include "wss/type.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/noncopyable.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class named_formula;
typedef boost::shared_ptr<named_formula> shared_named_formula_type;
typedef boost::weak_ptr<named_formula> weak_named_formula_type;

/*!
 * \brief
 *
 *
 * \author
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct named_formula_wrapper
        : public boost::noncopyable {
    struct is_redirected {
        explicit is_redirected( bool v ) : my_val( v ) {}
        bool my_val;
    };
    struct is_hidden {
        explicit is_hidden( bool v ) : my_val( v ) {}
        bool my_val;
    };
    named_formula_wrapper();

    ~named_formula_wrapper();

    named_formula_wrapper( const shared_named_formula_type& nf );

    inline const bool is_valid() const {
        return !m_named_formula.expired();
    }

    inline void set_named_formula( const shared_named_formula_type& nf, const is_redirected& r ) {
        m_named_formula = nf;
        redirected( r.my_val );
    }

    void set_named_formula( const shared_named_formula_type& nf, const is_hidden& h = is_hidden( false ) );

    inline shared_named_formula_type named_formula() {
        shared_named_formula_type d( m_named_formula.lock() );
        if ( d ) {
            return d;
        }
        static shared_named_formula_type dummy;
        return dummy;
    }

    shared_dependency_type named_formula( const shared_dependency_type& d );

    inline bool redirected() const {
        return m_redirected;
    }

    void redirected( bool val );

    const bool scope_sheet_hidden() const {
        return m_scope_sheet_hidden;
    }

    void unload();
private:
    bool m_redirected;
    bool m_scope_sheet_hidden;
    weak_named_formula_type m_named_formula;
};

typedef boost::shared_ptr<named_formula_wrapper> shared_named_formula_wrapper_type;


