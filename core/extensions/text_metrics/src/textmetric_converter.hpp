////////////////////////////////////////////////////////////////////////////////
/// @brief
///             Implements a quick converter between UTF8 and 21 bit Unicode.
/// @file
///             textmetric_converter.h
///
/// Copyright (C) 2006, 2007 Jedox GmbH
///
/// This program is free software; you can redistribute it and/or modify it
/// under the terms of the GNU General Public License (Version 2) as published
/// by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
/// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
/// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
/// more details.
///
/// You should have received a copy of the GNU General Public License along with
/// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
/// Place, Suite 330, Boston, MA 02111-1307 USA
///
/// You may obtain a copy of the License at
///
/// <a href="http://www.jedox.com/license_palo_bi_suite.txt">
///   http://www.jedox.com/license_palo_bi_suite.txt
/// </a>
///
/// If you are developing and distributing open source applications under the
/// GPL License, then you are free to use Palo under the GPL License.  For OEMs,
/// ISVs, and VARs who distribute Palo with their products, and do not license
/// and distribute their source code under the GPL, Jedox provides a flexible
/// OEM Commercial License.
///
/// @author
///             Radu Ialovoi
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTMETRIC_CONVERTER_H__
#define __TEXTMETRIC_CONVERTER_H__

#include <iterator>
#include <string>

namespace textmetric_internal
{
    class Converter
    {
    private:
        std::string             m_String;
    public:
        class conversion_iterator: public std::iterator< std::forward_iterator_tag, unsigned int >
        {
            friend class Converter;
        private:
            static const int END = 0xFFFFFFFF;              //something that has no UNICODE meaning
            std::string     m_String;
            const char*     m_Chars;
            size_t          m_Pos;
            size_t          m_CharsLen;
            unsigned int    m_Crt;

            void copy( const conversion_iterator& src ) {
                if ( this == &src ) {
                    return;
                }

                m_String    = src.m_String;
                m_Chars     = m_String.c_str();
                m_Pos       = src.m_Pos;
                m_Crt       = src.m_Crt;
                m_CharsLen  = src.m_CharsLen;
            }

            void increment() {
                if ( m_Pos == m_CharsLen ) {
                    m_Crt = END;
                } else if ( m_Chars[m_Pos] > 0 ) {
                    m_Crt = m_Chars[m_Pos];
                    m_Pos++;
                } else if ( 0xC0 == ( m_Chars[m_Pos] & 0xE0 ) ) {
                    if ( m_Pos >= m_CharsLen - 1 ) {
                        throw std::runtime_error( std::string( "Invalid input" ) );
                    }
                    m_Crt =
                        ( m_Chars[m_Pos + 1] & 0x3F ) +
                        ( ( m_Chars[m_Pos] & 0x03 ) << 6 ) +
                        ( ( int )( m_Chars[m_Pos] & 0x1C ) << 6 );
                    m_Pos += 2;
                } else if ( 0xE0 == ( m_Chars[m_Pos] & 0xF0 ) ) {
                    if ( m_Pos >= m_CharsLen - 2 ) {
                        throw std::runtime_error( std::string( "Invalid input" ) );
                    }
                    m_Crt =
                        ( m_Chars[m_Pos + 2] & 0x3F ) +
                        ( ( m_Chars[m_Pos +1] & 0x03 ) << 6 ) +
                        ( ( int )( m_Chars[m_Pos+1] & 0x3C ) << 6 ) +
                        ( ( int )( m_Chars[m_Pos] & 0x0F ) << 12 );
                    m_Pos += 3;
                } else if ( 0xF0 == ( m_Chars[m_Pos] & 0xF8 ) ) {
                    if ( m_Pos >= m_CharsLen - 3 ) {
                        throw std::runtime_error( std::string( "Invalid input" ) );
                    }
                    m_Crt =
                        ( m_Chars[m_Pos + 3] & 0x3F ) +
                        ( ( m_Chars[m_Pos +2] & 0x03 ) << 6 ) +
                        ( ( int )( m_Chars[m_Pos+2] & 0x3C ) << 6 ) +
                        ( ( int )( m_Chars[m_Pos+1] & 0x0F ) << 12 ) +
                        ( ( int )( m_Chars[m_Pos+1] & 0x30 ) << 12 ) +
                        ( ( int )( m_Chars[m_Pos] & 0x07 ) << 18 );
                    m_Pos += 4;
                } else {
                    throw std::runtime_error( std::string( "Invalid input" ) );
                }
            }
        public:
            conversion_iterator( std::string& string ) {
                m_String    = string;
                m_Chars     = m_String.c_str();
                m_Pos       = 0;
                m_CharsLen  = m_String.size();
                increment();
            }

            conversion_iterator() {
                m_String    = "";
                m_Chars     = m_String.c_str();
                m_Pos       = 0;
                m_CharsLen  = m_String.size();
                increment();
            }

            conversion_iterator( const conversion_iterator& src ) {
                copy( src );
            }

            conversion_iterator& operator=( const conversion_iterator& src ) {
                copy( src );
                return *this;
            }

            unsigned int operator*() {
                return m_Crt;
            }

            bool operator==( const conversion_iterator& right ) {
                return m_Crt == right.m_Crt;
            }

            bool operator!=( const conversion_iterator& right ) {
                return m_Crt != right.m_Crt;
            }

            conversion_iterator& operator++() {
                increment();
                return *this;
            }
        };
        Converter( const std:: string& string ) {
            m_String = string;
            m_end = conversion_iterator( m_String );
            m_end.m_Crt = conversion_iterator::END;
        }

        conversion_iterator begin() {
            return conversion_iterator( m_String );
        }

        const conversion_iterator& end() {
            return m_end;
        }
    private:
        conversion_iterator     m_end;
    };
}; // namespace textmetric_internal

#endif //__TEXTMETRIC_CONVERTER_H__
