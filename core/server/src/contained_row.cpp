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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include <wss/contained_row.hpp>
#include <wss/sheet_dimension.hpp>

contained_row::closed_interval::closed_interval( size_t point, size_t style ) : left( point ), right( point ), style( style )
{
    //nothing
}

contained_row::closed_interval::closed_interval( const size_t left, const size_t right, const size_t style ) : left( left ), right( right ), style( style )
{
}

contained_row::contained_row()
{
    clear();
}

void contained_row::clear()
{
    m_background = NOTHING;
    m_row_data.clear();
}

void contained_row::unset( const size_t pos )
{
    for ( row_data_type::iterator i = m_row_data.begin(), e = m_row_data.end(); i != e; i++ ) {
        if ( i->right < pos ) {
            continue;
        } else if ( i->left > pos ) {
            break;
        } else {
            if ( i->is_point() ) {
                m_row_data.erase( i );
            } else {
                if ( pos == i->left ) {
                    i->left++;
                } else if ( pos == i->right ) {
                    i->right--;
                } else {
                    size_t left = i->left;
                    i->left = pos + 1;
                    m_row_data.insert( i,  closed_interval( left, pos - 1, i->style ) );
                }
            }
            break;
        }
    }
}

void contained_row::unset( const size_t start, const size_t stop )
{
    if ( m_row_data.empty() ) {
        m_row_data.push_back( closed_interval( start, stop, NOTHING ) );
        return;
    }
    if ( start > max() ) {
        m_row_data.push_back( closed_interval( start, stop, NOTHING ) );
        return;
    }
    row_data_type::iterator i = m_row_data.begin();
    while ( i != m_row_data.end() ) {
        if ( i->right < start ) {
            ++i;
            continue;
        } else if ( i->left > stop ) {
            break;
        } else if ( i->left < start ) {
            if ( i->right > stop ) {
                size_t left = i->left;
                i->left = stop + 1;
                m_row_data.insert( i, closed_interval( left, start - 1, i->style ) );
                break;
            } else {
                i->right = start - 1;
                ++i;
            }
        } else if ( i->right > stop ) {
            i->left = stop + 1;
            ++i;
        } else {
            i = m_row_data.erase( i );
        }
    }

    if ( NOTHING != background() ) {
        row_data_type::iterator i = m_row_data.begin();
        while ( i != m_row_data.end() ) {
            if ( i->left >= stop ) {
                break;
            }
            ++i;
        }
        m_row_data.insert( i, closed_interval( start, stop, NOTHING ) );
    }
}

void contained_row::copy( const contained_row& src, const size_t from, const size_t to, const size_t width, const bool left_to_right/* = true*/ )
{
    //TODO: this has a lot of passes. there is an option to write a single pass alg
    size_t actual_width = width;
    if ( to + actual_width - 1 > sheet_dimension::max_column ) {
        actual_width = sheet_dimension::max_column - to + 1;
    }
    if ( left_to_right ) {
        for ( size_t idx = 0; idx < actual_width; ++idx ) {
            set( to + idx, src.get( from + idx ) );
        }
    } else {
        for ( int idx = actual_width - 1; idx >= 0; --idx ) {
            set( to + ( size_t ) idx, src.get( from + ( size_t ) idx ) );
        }
    }
}

void contained_row::extend( const size_t from, const size_t from_width, const size_t to_width )
{
    //TODO: this has a lot of passes. there is an option to write a single pass alg
    for ( size_t offset = from_width; offset < to_width; ++offset ) {
        set( from + offset, get( from + ( offset - from_width ) % from_width ) );
    }
}

bool contained_row::empty() const
{
    return m_row_data.empty();
}

const size_t contained_row::get( const size_t pos ) const
{
    for ( row_data_type::const_iterator i = m_row_data.begin(), e = m_row_data.end(); i != e; ++i ) {
        if ( i->contains( pos ) ) {
            m_last_result = true;
            return i->style;
        }
    }

    m_last_result = m_background != NOTHING;
    return m_background;
}

void contained_row::set( const size_t pos, const size_t style )
{
    if ( empty() ) {
        m_row_data.push_front( closed_interval( pos, style ) );
        return;
    }

    if ( pos < min() ) {
        if ( pos == min() - 1 && m_row_data.begin()->style == style ) {
            m_row_data.begin()->left--;
        } else {
            m_row_data.push_front( closed_interval( pos, style ) );
        }
        return;
    }

    if ( pos > max() ) {
        if ( pos == max() + 1 && m_row_data.rbegin()->style == style ) {
            m_row_data.rbegin()->right++;
        } else {
            m_row_data.push_back( closed_interval( pos, style ) );
        }
        return;
    }

    for ( row_data_type::iterator i = m_row_data.begin(), e = m_row_data.end(), b = m_row_data.begin(); i != e; ++i ) {
        if ( i->left  > pos ) {
            if ( i->left == pos + 1 && i->style == style ) {
                i->left--;

                if ( i != b && i->style == ( i - 1 )->style && i->left == ( i - 1 )->right ) {
                    ( i - 1 )->right = i->right;
                    m_row_data.erase( i );
                }
            } else {
                m_row_data.insert( i, closed_interval( pos, style ) );
            }
            return;
        } else if ( i->contains( pos ) ) {
            if ( i->style == style ) {
                return;
            }
            if ( i->left < pos && i->right > pos ) {
                size_t right = i->right;
                i->right = pos - 1;
                row_data_type::iterator ret = m_row_data.insert( i + 1, closed_interval( pos + 1, right, i->style ) );
                m_row_data.insert( ret, closed_interval( pos, style ) );
            } else if ( i->left == pos ) {
                if ( i->is_point() ) {
                    i->style = style;
                    return;
                }
                i->left++;
                if ( b == i ) {
                    m_row_data.push_front( closed_interval( pos, style ) );
                } else {
                    row_data_type::iterator prev = i - 1;
                    if ( prev->right == pos - 1 && prev->style == style ) {
                        prev->right++;
                    } else {
                        m_row_data.insert( i, closed_interval( pos, style ) );
                    }
                }
            } else if ( i->right == pos ) {
                i->right--;
                row_data_type::iterator next = i + 1;
                if ( e == next ) {
                    m_row_data.push_back( closed_interval( pos, style ) );
                } else {
                    if ( next->left == pos + 1 && next->style == style ) {
                        next->left--;
                    } else {
                        m_row_data.insert( i + 1, closed_interval( pos, style ) );
                    }
                }
            }
            return;
        }
    }
}

void contained_row::set( const size_t start, const size_t stop, const size_t style )
{
    if ( empty() ) {
        m_row_data.push_front( closed_interval( start, stop, style ) );
        return;
    }

    for ( size_t i = start; i <= stop; ++i ) {
        set( i, style );
    }
}

void contained_row::shift( const size_t column, const size_t column_count )
{
    for ( row_data_type::iterator i = m_row_data.begin(), e = m_row_data.end(); i != e; ++i ) {
        if ( i->right + 1 >= column ) {
            i->right += column_count;
        }
        if ( i->left >= column ) {
            i->left += column_count;
        }
    }

    row_data_type::iterator i = m_row_data.begin();
    while ( i != m_row_data.end() ) {
        if ( i->left > sheet_dimension::max_column ) {
            i = m_row_data.erase( i );
        } else {
            if ( i->right > sheet_dimension::max_column ) {
                i->right = sheet_dimension::max_column;
            }
            ++i;
        }
    }
}

void contained_row::unshift( const size_t column, const size_t column_count )
{
    const size_t right = column + column_count - 1;

    row_data_type::iterator i = m_row_data.begin();

    while ( i != m_row_data.end() ) {
        if ( i->left > right ) {
            i->left -= column_count;
            i->right -= column_count;
            ++i;
        } else if ( i->left >= column ) {
            if ( i->right <= right ) {
                i = m_row_data.erase( i );
            } else {
                i->left = column;
                i->right = i->left + i->right - right - 1;
                ++i;
            }
        } else {
            if ( i->right >= right ) {
                i->right -= column_count;
                ++i;
            } else if ( i->right >= column ) {
                i->right = column - 1;
                ++i;
            } else {
                ++i;
            }
        }
    }

}
