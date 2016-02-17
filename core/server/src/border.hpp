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

#include "wss/define.hpp"
#include "wss/type.hpp"
#include "wss/define.hpp"
#include "wss/border_types.hpp"

/*!
 * \brief
 * border representation
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
  */
class border
{
    friend class conditional_format_storage;

public:
    typedef border_types border_type;
    typedef std::map<border_type::type, border_style_flyweight_type> border_style_map_type;

private:
    typedef border_style_map_type::const_iterator const_iterator;

public:

    inline border() : m_border_type( border_type::none ) {}


    inline border( const long t, const border_style_flyweight_type& style )
        : m_border_type( t ) {
        if ( !empty() ) {
            insert_into_map( t, style );
        }
    }

    inline border( border_style_map_type& s ) {
        m_style.swap( s );
        foreach( const border_style_map_type::value_type & v, m_style ) {
            m_border_type |= v.first;
        }
    }


    //a few static utility functions
    inline static bool check_border_type( const long b, const border_type::type b_type ) {
        return ( b & b_type ) == b_type;
    }

    inline void combine( const border& other ) {
        const_iterator it( other.m_style.begin() ), end_it( other.m_style.end() );
        for ( ; it != end_it; ++it  ) {
            m_style[it->first] = it->second;
            ++it;
        }
    }

    inline bool empty() const {
        return m_border_type == border_type::none;
    }

    inline long type() const {
        return m_border_type;
    }

    inline const border_style_flyweight_type& style( const border_type::type type ) const {
        static const border_style_flyweight_type dummy( "" );
        const_iterator it( m_style.find( type ) );
        return it == m_style.end() ? dummy : it->second;
    }

    inline const bool operator==( const border& other ) const {
        return m_border_type == other.m_border_type ? true :  m_style == other.m_style;
    }

    inline const bool operator!=( const border& other ) const {
        return !( operator==( other ) );
    }

    //this one is defined to be able to sort Borders in some way
    inline const bool operator<( const border& other ) const {
        if ( m_border_type == other.m_border_type ) {
            return m_style < other.m_style;
        }
        return m_border_type < other.m_border_type;
    }

    inline void insert_into_map( const long type, const border_style_flyweight_type& border_style ) {
        if ( type == border_type::none ) {
            return;
        }
        m_border_type |= type;
        if ( check_border_type( type, border_type::top ) ) {
            m_style[border_type::top ] = border_style;
        }
        if ( check_border_type( type, border_type::bottom ) ) {
            m_style[border_type::bottom ] = border_style;
        }
        if ( check_border_type( type, border_type::left ) ) {
            m_style[border_type::left ] = border_style;
        }
        if ( check_border_type( type, border_type::right ) ) {
            m_style[border_type::right ] = border_style;
        }
        if ( check_border_type( type, border_type::outside ) ) {
            m_style[border_type::outside ] = border_style;
        }
        if ( check_border_type( type, border_type::inside_horizontal ) ) {
            m_style[border_type::inside_horizontal ] = border_style;
        }
        if ( check_border_type( type, border_type::inside_vertical ) ) {
            m_style[border_type::inside_vertical ] = border_style;
        }
        if ( check_border_type( type, border_type::inside ) ) {
            m_style[border_type::inside ] = border_style;
        }
    }

    inline void insert_into_map( const border_type::type type, const border_style_flyweight_type& border_style ) {
        m_border_type |= type;
        m_style[type ] = border_style;
    }

    void remove_from_map( const long type ) {
        if ( type == border_type::none ) {
            return;
        }
        if ( check_border_type( type, border_type::top ) ) {
            m_style.erase( border_type::top );
        }
        if ( check_border_type( type, border_type::bottom ) ) {
            m_style.erase( border_type::bottom );
        }
        if ( check_border_type( type, border_type::left ) ) {
            m_style.erase( border_type::left );
        }
        if ( check_border_type( type, border_type::right ) ) {
            m_style.erase( border_type::right );
        }
        if ( check_border_type( type, border_type::outside ) ) {
            m_style.erase( border_type::outside );
        }
        if ( check_border_type( type, border_type::inside_horizontal ) ) {
            m_style.erase( border_type::inside_horizontal );
        }
        if ( check_border_type( type, border_type::inside_vertical ) ) {
            m_style.erase( border_type::inside_vertical );
        }
        if ( check_border_type( type, border_type::inside ) ) {
            m_style.erase( border_type::inside );
        }
    }

private:
    inline border( const long t, const border_style_map_type& s )
        : m_border_type( t )
        , m_style( s ) {}

private:
    long m_border_type;
    border_style_map_type m_style;
};



#ifdef _DEBUG
inline std::ostream& operator <<( std::ostream& os, const border& b )
{
    /* os <<  " { border, border_style = " << b.border_style << " | type = " << b.m_border_type <<" } ";*/
    os << b.type() << " ";
    return os;
}
inline std::ostream& operator <<( std::ostream& os, const border_vec_type& v )
{
    foreach( const border & b, v ) {
        os << b;
    }
    return os;
}
#endif
