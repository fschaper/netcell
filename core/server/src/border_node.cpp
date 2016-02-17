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

#include "precompiled_header.hpp"
#include "border_node.hpp"
#include "border_utility.hpp"
#ifdef _SKIP_ME_

border_node::border_node( const sheet_range& rect, const border& b, const insertion_counter_type id )
    : rc::rectangle_node( rect )
    , m_border( b )
    , m_insertion_id( id )
{
    optimize_node();
}

border_node::border_node()
    : rc::rectangle_node( sheet_range( sheet_point( 0, 0 ) ) )
    , m_border()
    , m_insertion_id( 0 )
{}

void border_node::optimize_node()
{
    if ( rectangle().column_count() < 2 ) {
        if ( border::check_border_type( m_border.type(), border::border_type::inside_vertical ) ) {
            m_border.m_border_type -= border::border_type::inside_vertical;
            m_border.remove_from_map( border::border_type::inside_vertical );
        }
    }
    if ( rectangle().row_count() < 2 ) {
        if ( border::check_border_type( m_border.type(), border::border_type::inside_horizontal ) ) {
            m_border.m_border_type -= border::border_type::inside_horizontal;
            m_border.remove_from_map( border::border_type::inside_horizontal );
        }
    }

    if ( m_border.empty() ) {
        return;
    }

    sheet_range local_rect( rectangle() );

    if ( border::check_border_type( m_border.type(), border::border_type::top ) ) {
        if ( !
                ( border::check_border_type( m_border.type(), border::border_type::inside_vertical )
                  | border::check_border_type( m_border.type(), border::border_type::left )
                  | border::check_border_type( m_border.type(), border::border_type::right )
                  | border::check_border_type( m_border.type(), border::border_type::bottom ) )
           ) {
            if ( border::check_border_type( m_border.type(), border::border_type::inside_horizontal ) ) {
                //minor optimization
                if ( local_rect.row_count() > 1 ) {
                    local_rect = sheet_range( sheet_point( local_rect.upper_left() ), sheet_point( local_rect.lower_right() + geometry::point( - 1, 0 ) ) );
                }
            } else {
                //major optimization
                local_rect = local_rect.top();
            }
        }
    } else if ( border::check_border_type( m_border.type(), border::border_type::bottom ) ) {
        if ( !
                ( border::check_border_type( m_border.type(), border::border_type::inside_vertical )
                  | border::check_border_type( m_border.type(), border::border_type::left )
                  | border::check_border_type( m_border.type(), border::border_type::right )
                  /* don't have to check top here again */ )
           ) {
            if ( border::check_border_type( m_border.type(), border::border_type::inside_horizontal ) ) {
                //minor optimization
                if ( local_rect.row_count() > 1 ) {
                    local_rect = sheet_range( sheet_point( local_rect.upper_left() + geometry::point( 1, 0 ) ), sheet_point( local_rect.lower_right() ) );
                }
            } else {
                //major optimization
                local_rect = local_rect.bottom();
            }
        }
    } else if ( border::check_border_type( m_border.type(), border::border_type::left ) ) {
        if ( !
                ( border::check_border_type( m_border.type(), border::border_type::inside_horizontal )
                  | border::check_border_type( m_border.type(), border::border_type::top )
                  | border::check_border_type( m_border.type(), border::border_type::bottom )
                  |  border::check_border_type( m_border.type(), border::border_type::right ) )
           ) {
            if ( border::check_border_type( m_border.type(), border::border_type::inside_vertical ) ) {
                //minor optimization
                if ( local_rect.column_count() > 1 ) {
                    local_rect = sheet_range( sheet_point( local_rect.upper_left() ), sheet_point( local_rect.lower_right() + geometry::point( 0, -1 ) ) );
                }
            } else {
                //major optimization
                local_rect = local_rect.left();
            }
        }
    } else if ( border::check_border_type( m_border.type(), border::border_type::right ) ) {
        if ( !
                ( border::check_border_type( m_border.type(), border::border_type::inside_horizontal )
                  | border::check_border_type( m_border.type(), border::border_type::top )
                  | border::check_border_type( m_border.type(), border::border_type::bottom )
                  /* don't have to check left here again */ )
           ) {
            if ( border::check_border_type( m_border.type(), border::border_type::inside_vertical ) ) {
                if ( local_rect.column_count() > 1 ) {
                    //minor optimization
                    local_rect = sheet_range( sheet_point( local_rect.upper_left() + geometry::point( 0, 1 ) ), sheet_point( local_rect.lower_right() ) );
                }
            } else {
                //major optimization
                local_rect = local_rect.right();
            }
        }
    }
    rectangle( local_rect );
}

border_node::auto_type border_node::clone() const
{
    return auto_type( new border_node( *this ) );
}

border_node::auto_type border_node::shallow_copy() const
{
    return auto_type( new border_node( rectangle(), m_border, m_insertion_id ) );
}

void border_node::update_rectangle( const geometry::rectangle_type& r )
{
    const geometry::rectangle_type& old_r( rectangle() );
    if ( old_r == r ) {
        return;
    }

    if ( old_r.does_intersect( r ) ) {
        border tmp;
        tmp.swap( m_border );

        //outside borders
        if ( border::check_border_type( tmp.type(), border::border_type::top ) ) {
            if ( old_r.upper_left().row() == r.upper_left().row() ) {
                m_border.insert_into_map( border::border_type::top, tmp.style( border::border_type::top ) );
            }
        }
        if ( border::check_border_type( tmp.type(), border::border_type::bottom ) ) {
            if ( old_r.lower_right().row() == r.lower_right().row() ) {
                m_border.insert_into_map( border::border_type::bottom, tmp.style( border::border_type::bottom ) );
            }
        }
        if ( border::check_border_type( tmp.type(), border::border_type::left ) ) {
            if ( old_r.upper_left().column() == r.upper_left().column() ) {
                m_border.insert_into_map( border::border_type::left, tmp.style( border::border_type::left ) );
            }
        }
        if ( border::check_border_type( tmp.type(), border::border_type::right ) ) {
            if ( old_r.lower_right().column() == r.lower_right().column() ) {
                m_border.insert_into_map( border::border_type::right, tmp.style( border::border_type::right ) );
            }
        }

        //inside
        const bool one_row = r.row_count() < 2;
        const bool one_col = r.column_count() < 2;
        if ( border::check_border_type( tmp.type(), border::border_type::inside_horizontal ) || border::check_border_type( tmp.type(), border::border_type::inside_vertical ) ) {
            //sheet_range inner_rect( old_r.inner() );
            const bool inside_horizontal = border::check_border_type( tmp.type(), border::border_type::inside_horizontal );
            const bool inside_vertical =  border::check_border_type( tmp.type(), border::border_type::inside_vertical );

            if ( inside_horizontal ) {
                if ( old_r.upper_left().row() == r.upper_left().row() && ! one_row ) {
                    m_border.insert_into_map( border::border_type::inside_horizontal, tmp.style( border::border_type::inside_horizontal ) );
                } else { /*if ( inner_rect.upper_left().row() == r.upper_left().row() + 1)*/
                    m_border.insert_into_map( border::border_type::top | ( one_col ? border::border_type::inside_horizontal : border::border_type::none ), tmp.style( border::border_type::inside_horizontal ) );
                }
                if ( old_r.lower_right().row() == r.lower_right().row() && ! one_row ) {
                    m_border.insert_into_map( border::border_type::inside_horizontal, tmp.style( border::border_type::inside_horizontal ) );
                } else { /*if ( inner_rect.lower_right().row() + 1 == r.lower_right().row() )*/
                    m_border.insert_into_map( border::border_type::bottom | ( one_col ? border::border_type::inside_horizontal : border::border_type::none ), tmp.style( border::border_type::inside_horizontal ) );
                }
            }
            if ( inside_vertical ) {
                if ( old_r.upper_left().column() == r.upper_left().column() && ! one_col  ) {
                    m_border.insert_into_map( border::border_type::inside_vertical, tmp.style( border::border_type::inside_vertical ) );
                } else { /*if ( inner_rect.upper_left().column() == r.upper_left().column() + 1 )*/
                    m_border.insert_into_map( border::border_type::left | ( one_row ? border::border_type::inside_vertical : border::border_type::none ), tmp.style( border::border_type::inside_vertical ) );
                }
                if ( old_r.lower_right().column() == r.lower_right().column() && ! one_col ) {
                    m_border.insert_into_map( border::border_type::inside_vertical, tmp.style( border::border_type::inside_vertical ) );
                } else { /*if ( inner_rect.lower_right().column() + 1 == r.lower_right().column() )*/
                    m_border.insert_into_map( border::border_type::right | ( one_row ? border::border_type::inside_vertical : border::border_type::none ), tmp.style( border::border_type::inside_vertical ) );
                }
            }
        }
    }
    rectangle( r );
    optimize_node();
}
#endif // _SKIP_ME_

