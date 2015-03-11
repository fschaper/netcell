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

#include <streambuf>
#include <string>

/*!
 * \brief
 * ties two output streams.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<typename char_T>
class basic_tied_buffer
    : public std::basic_streambuf<char_T, std::char_traits<char_T> >
{
    typedef std::basic_streambuf<char_type,  std::char_traits<char_T> > streambuffer_type;
    typedef typename  std::char_traits<char_T>::int_type int_type;
    typedef typename std::char_traits<char_T> traits_T;
public:

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    basic_tied_buffer( streambuffer_type* buffer1, streambuffer_type* buffer2 )
        : m_streambuffer_1( buffer1 )
        , m_streambuffer_2( buffer2 ) {}

protected:
    /*!
     * \brief
     * try to write character in the case of overflow.
     *
     * a character has to be written but the output pointer has reached at least
     * one of our streams end marker. we forward the request to the underlaying
     * buffers so they can make room.
     *
     * a value different than traits_T::eof() signifies success.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual int_type overflow( int_type c = traits_T::eof() ) {
        // swallow the eof character.
        if ( traits_T::eq_int_type( c, traits_T::eof() ) ) {
            // return anything but eof.
            return traits_T::not_eof( c );
        } else {
            // try to write the character to the stream buffers.
            const int_type s1_result = m_streambuffer_1->sputc( traits_T::to_char_type( c ) );
            const int_type s2_result = m_streambuffer_2->sputc( traits_T::to_char_type( c ) );

            // in case one of the buffers signaled eof, return eof even
            // if the other stream is still operational. otherwise return our character.
            return ( traits_T::eq_int_type( s1_result, traits_T::eof() )
                     || traits_T::eq_int_type( s2_result, traits_T::eof() ) ) ? traits_T::eof() : c;
        }
    }

    /*!
     * \brief
     * called to synchronize the buffer with the underlaying sequence.
     *
     * returns 0 on success.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual int sync() {
        const int_type s1_result = m_streambuffer_1->pubsync();
        const int_type s2_result = m_streambuffer_2->pubsync();
        return ( s1_result == 0 && s2_result == 0 ) ? 0 : -1;
    }

private:
    streambuffer_type* m_streambuffer_1;
    streambuffer_type* m_streambuffer_2;
};

typedef basic_tied_buffer<char> tied_buffer_type;

