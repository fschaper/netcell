/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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


#include <float.h>

//I really want this class in a header. Don't expect to change and it should be inlined
//corectly prints doubles up to a 19 digits precision.
//at the time this was written the usual precision was 15 digits
class double_to_string
{
private:
    template < typename T >
    class m_simple_stack
    {
        //simple stack designed for speed.
        //no checks whatsoever
    private:
        T*          m_buf;
        size_t      m_pointer;
        size_t      m_size;
    public:
        m_simple_stack( size_t size = DBL_DIG ) {
            m_buf = new T[ size + 1 ];
            m_pointer = m_size = size;
            push( 0 );
        }

        ~m_simple_stack() {
            delete[] m_buf;
        }

        void push( T& val ) {
            m_buf[ m_pointer-- ] = val;
        }

        void push( T val ) {
            m_buf[ m_pointer-- ] = val;
        }

        T& pop() {
            return m_buf[ ++m_pointer ];
        }

        bool empty() {
            return m_size - 1 == m_pointer;
        }

        size_t size() {
            return m_size - 1 - m_pointer;
        }

        void clear() {
            m_pointer = m_size - 1;
        }

        T* stream() {
            return m_buf + m_pointer + 1;
        }
    };

    long long                   m_limit;
    unsigned char               m_precision;
    std::stringstream           m_convertor;

    m_simple_stack< char >      m_integral;
    m_simple_stack< char >      m_fractional;
    unsigned char               m_fractional_zeros;

    void fractional( double val ) {
        if ( 0 == val ) {
            return;
        }

        m_fractional_zeros = m_precision;
        long long divisor = m_limit;
        for ( size_t i = 0 ; i < m_integral.size(); i++ ) {
            divisor /= 10;
            m_fractional_zeros--;
        }


        val *= divisor;
        long long  int_val = ( long long ) val;

        while ( 0 != int_val && 0 == int_val % 10 ) {
            int_val /= 10;
            m_fractional_zeros--;
        }

        while ( 0 != int_val ) {
            m_fractional.push( '0' + ( char )( int_val % 10 ) );
            int_val /= 10;
            m_fractional_zeros--;
        }
    }

    void integral( double val ) {
        if ( 0 == val ) {
            return;
        }
        long long  int_val = ( long long ) val;
        while ( 0 != int_val ) {
            m_integral.push( '0' + ( char )( int_val % 10 ) );
            int_val /= 10;
        }
    }
public:
    double_to_string( unsigned char precision = DBL_DIG ) : m_precision( precision ) {
        m_limit = 1;
        for ( unsigned int i = 0; i < m_precision; i++ ) {
            m_limit *= 10;
        }
    }

    std::string operator()( double val ) {
        if ( val >= m_limit || val <= -m_limit ) {
            m_convertor.str( "" );
            m_convertor << val;
            return m_convertor.str();
        }

        bool add_sign = false;
        if ( val < 0 ) {
            val = -val;
            add_sign = true;
        }

        double before;
        double after = modf( val, &before );

        integral( before );
        fractional( after );


        std::string res;
        if ( !m_integral.empty() ) {
            res += m_integral.stream();
            m_integral.clear();
        }

        if ( res.empty() ) {
            res += '0';
        }

        if ( !m_fractional.empty() ) {
            res += '.';
            for ( unsigned char i = 0; i < m_fractional_zeros; i++ ) {
                res += '0';
            }

            res += m_fractional.stream();
            m_fractional.clear();
        }
        if ( add_sign ) {
            res = '-' + res;
        }

        return res;
    }

};

