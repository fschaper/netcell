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

#include "wss/non_instantiable.hpp"

#include "border_storage.hpp"
#include "border.hpp"
#include "border_utility.hpp"
#include "border_locked_storage.hpp"
#include "border_callbacks.hpp"
#include "conditional_format_style_unlock_type.hpp"

using namespace geometry;

/*!
 * \brief
 * map border_type->border_style
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef std::map<border_types::type, border_style_flyweight_type> border_index_map_type;

/*!
 * \brief
 * map sheet_point->border_index_map_type
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef std::map<sheet_point, border_index_map_type> border_map_type;

/*!
 * \brief
 * convenience
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef border_map_type::iterator iterator;
typedef border_map_type::const_iterator const_iterator;

/*!
 * \brief
 * optional border style type
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef boost::optional<border_style_flyweight_type> optional_border_idx_type;


namespace policy
{
    struct return_border_vec_simple_type;
    struct return_border_vec_type;
    struct return_insert_col_row_vec_type;
}
template<class T>
class border_collectorT;

/*!
 * \brief
 * collect borders for a rectangle and only return the style for one
 * side if its the same for the whole side of the rectangle
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef border_collectorT<policy::return_border_vec_simple_type> simple_border_collector_type;

/*!
 * \brief
 * collect borders for a rectangle and return the border for each sheet_point inside the rectangle
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef border_collectorT<policy::return_border_vec_type> border_collector_type;

/*!
 * \brief
 * collect borders for insert column or insert row operations
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */

typedef border_collectorT<policy::return_insert_col_row_vec_type> insert_col_row_border_collector_type;

static const std::string mixed_border_string = "mixed";

struct border_storage_helper : non_instantiable {

    typedef erase_border_callback<policy::list_only_rectangles_policy, policy::erase_type_policy> erase_one_type_list_only_rects_callback_type;
    typedef erase_border_callback<policy::list_rectangles_and_types_policy, policy::erase_type_policy> erase_one_type_list_rects_and_type_callback_type;
    typedef erase_border_callback<policy::list_rectangles_and_types_policy, policy::erase_type_policy, policy::erase_style_if_less_luma_policy> erase_one_type_check_luma_list_rects_and_type_callback_type;

    template<class erase_style_policyT>
    struct erase_border_callback_with_style_as_template {
        typedef erase_border_callback<policy::list_only_rectangles_policy, policy::erase_type_policy, erase_style_policyT> erase_one_type_list_only_rects_callback_type;
        typedef erase_border_callback<policy::list_rectangles_and_types_policy, policy::erase_type_policy, erase_style_policyT> erase_one_type_list_rects_and_type_callback_type;
    };

    /*!
     * \brief
     * convenience function
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline bool is_row_operation( const insert_shift_direction::type shift ) {
        return insert_shift_direction::entire_row == shift || insert_shift_direction::vertically == shift;
    }

    /*!
     * \brief
     * convenience function
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline bool is_column_operation( const insert_shift_direction::type shift ) {
        return insert_shift_direction::entire_column == shift || insert_shift_direction::horizontally == shift;
    }

    /*!
     * \brief
     * given an index and a type, return the corresponding border
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline border border_from_idx( const border_types::type type, const optional_border_idx_type& idx ) {
        return idx ? border( type , *idx ) : border();
    }

    /*!
     * \brief
     * given a map of indexes, return the corresponding border
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline border border_from_idx( const border_index_map_type& idx ) {
        border return_val;
        foreach( const border_index_map_type::value_type & i, idx ) {
            return_val.insert_into_map( i.first, i.second );
        }
        return return_val;
    }

    /*!
     * \brief
     * return a logical AND of both maps
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline border_index_map_type combine_sub( const border_index_map_type& lhs, const border_index_map_type& rhs ) {
        border_index_map_type return_val;
        std::insert_iterator<border_index_map_type> insert_it( return_val, return_val.begin() );
        std::set_intersection( lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), insert_it );
        return return_val;
    }

    /*!
     * \brief
     * this will check if all the borders of type_to_check are the same in the area covered by rect
     *
     * \param rect - the rectangle to check
     *
     * \param borders - vector with the borders found by a query
     *
     * \param type_to_check - the type we're looking for (i.e. border_top)
     *
     * \param style_to_check - optional style to check for, every border we find of
     *                         type_to_check needs to have the same style or we return an empty
     *                         optional_border_idx_type
     *
     * \return an optional_border_idx_type with the right style and type if every border we
     *         found matched what we were looking for
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<bool return_mixed_if_mixed>
    static inline optional_border_idx_type check_border_same( const geometry::rectangle_type& rect, const border_map_type& borders, const border::border_type::type type_to_check, optional_border_idx_type style_to_check = optional_border_idx_type() ) {
        static const optional_border_idx_type mixed_border_style = return_mixed_if_mixed ? border_style_flyweight_type( mixed_border_string ) : optional_border_idx_type();
        if ( return_mixed_if_mixed ) {
            if ( style_to_check && style_to_check == mixed_border_style ) {
                return mixed_border_style;
            }
        }
        geometry::rectangle_type::const_iterator it( rect.begin() ), end_it( rect.end() );
        bool found_an_empty_one = false;
        const_iterator map_end( borders.end() );
        for ( ; it != end_it; ++it ) {
            const_iterator b_it( borders.find( *it ) );
            if ( b_it != map_end ) {
                border_index_map_type::const_iterator find_type_iter( b_it->second.find( type_to_check ) );
                if ( find_type_iter != b_it->second.end() ) {
                    if ( found_an_empty_one ) {
                        //we already saw an empty one, now a real one.. this is a mixed border.
                        return mixed_border_style;
                    }
                    if ( !style_to_check ) {
                        style_to_check.reset( find_type_iter->second );
                    } else {
                        if ( find_type_iter->second != *style_to_check ) {
                            //we already saw a different style here, this is a mixed border.
                            return mixed_border_style;
                        }
                    }
                } else {
                    if ( style_to_check ) {
                        //we already saw a real style, now an empty one.. this is a mixed border.
                        return mixed_border_style;
                    }
                    found_an_empty_one = true;
                }
            } else {
                if ( style_to_check ) {
                    //we already saw a real style, now an empty one.. this is a mixed border.
                    return mixed_border_style;
                }
                found_an_empty_one = true;
            }
        }
        return style_to_check;
    }

    static inline border_types::type opposite_border( const border_types::type b ) {
        switch ( b ) {
            case border_types::top:
                return border_types::bottom;
            case border_types::bottom:
                return border_types::top;
            case border_types::left:
                return border_types::right;
            case border_types::right:
                return border_types::left;
            default:
                assert( !"error opposite_border asked for wrong type" );
        }
        //to avoid a VS warning
        return border_types::top;
    }

    /*!
     * \brief
     * add a border
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template< bool need_clearing_first, bool overwrite_only_if_darker>
    static inline void add_border( const sheet_range& rect,  const border_storage::border_index_type& index, border_storage::container_type& container ) {
        if ( need_clearing_first ) {
            if ( overwrite_only_if_darker ) {
                //first check if we don't need to insert (we only insert if we're "darker" then the border already there)
                border_storage::get_border_list_type tmp_list;
                const geometry::rectangle_type helper_r = geometry::rectangle_type( rect );
                const border_types::type b_type = index.first;
                boost::optional<sheet_range> offset_helper;
                try {
                    offset_helper.reset( helper_r.offset(
                                             b_type == border_types::top ? -1 : ( b_type == border_types::bottom ? 1 : 0 ),
                                             b_type == border_types::left ? -1 : ( b_type == border_types::right ? 1 : 0 ) ) );
                } catch ( const position_out_of_range_exception& ) {}

                get_border_callback gb_strat( tmp_list, offset_helper ? sheet_range( helper_r.enclose( *offset_helper ) ) : rect );
                container.query( offset_helper ? sheet_range( helper_r.enclose( *offset_helper ) ) : rect, gb_strat );
                if ( !tmp_list.empty() ) {
                    border_storage::get_border_list_type::const_iterator it( tmp_list.begin() ), end_it( tmp_list.end() );
                    for ( ; it != end_it; ++it ) {
                        if ( (
                                    //either we match our own position
                                    ( it->second.first == b_type && it->first.covers( rect ) )
                                    ||
                                    //or we much the adjusting one
                                    ( offset_helper && opposite_border( it->second.first ) == b_type && it->first.covers( *offset_helper ) )
                                )
                                &&
                                policy::calculate_luma<1>( it->second.second ) <  policy::calculate_luma<0>( index.second )
                           ) {
                            //nothing to do;
                            return;
                        }
                    }
                }

                typedef erase_one_type_check_luma_list_rects_and_type_callback_type erase_policy_type;
                erase_policy_type::list_type reinsertion_list;
                erase_policy_type strat( reinsertion_list, index.first, rect, index.second );
                container.remove( rect, strat );
                insert_border_list( reinsertion_list, container, true );
            } else {
                typedef erase_one_type_list_rects_and_type_callback_type erase_policy_type;
                erase_policy_type::list_type reinsertion_list;
                erase_policy_type strat( reinsertion_list, index.first, rect );
                container.remove( rect, strat );
                insert_border_list( reinsertion_list, container, true );
            }
        }
        container.insert( rect, index, true );
    }

    /*!
     * \brief
     * if the style is empty, borders will be removed, else this will add a border
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template< bool need_clearing_first, bool overwrite_only_if_darker>
    static inline void add_border( const sheet_range& rect, const border_types::type type, const border_style_flyweight_type& style, border_storage::container_type& container/* , border_storage::value_map_type& val_map */ ) {
        static const border_style_flyweight_type empty_string( "" );
        if ( empty_string == style ) {
            remove_borders_plus_adjacent<0>( type, rect, container, policy::select_style<0>::dummy );
        } else {
            BOOST_STATIC_CONSTANT( int, style_selector_ = 1 + static_cast<int>( overwrite_only_if_darker ) );
            if ( style_selector_ < 2 ) {
                remove_borders_plus_adjacent < 1 + static_cast<int>( overwrite_only_if_darker ) > ( type, rect, container, style );
                add_border<need_clearing_first, overwrite_only_if_darker>( rect, std::make_pair( type, style ), container );
            } else if ( style_selector_ == 2 ) {
                const border_style_flyweight_type style_to_set = remove_borders_plus_adjacent_check_and_return_style_to_use( type, rect, container, style );
                add_border<need_clearing_first, false>( rect, std::make_pair( type, style_to_set == policy::erase_style_if_less_luma_policy::dummy ? style : style_to_set ), container );
            }
        }
    }

    /*!
     * \brief
     * remove borders in the rectangle and adjacent borders, for instance if the rect is A1:A1 we have to remove top
     * borders at A2 and left borders at B1...
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline border_style_flyweight_type remove_borders_plus_adjacent_check_and_return_style_to_use( const border_types::type type, const sheet_range& rect, border_storage::container_type& container, const border_style_flyweight_type& style ) {

        typedef border_storage_helper::erase_border_callback_with_style_as_template<policy::erase_style_if_less_luma_policy>::erase_one_type_list_rects_and_type_callback_type erase_callback_type;
        erase_callback_type::list_type reinsertion_list;
        erase_callback_type strat( reinsertion_list, type, rect, style );
        container.remove( rect, strat );
        border_style_flyweight_type return_style = strat.style_to_return();

        // then remove all the adjacent borders for this type
        switch ( type ) {
            case border_types::top: {
                const rectangle_type top_rect = rect.top().offset( -1, 0 );
                erase_callback_type inner_strat( reinsertion_list, border_types::bottom, top_rect, style );
                container.remove( top_rect, inner_strat );
                if ( strat.style_to_return() == policy::erase_style_if_less_luma_policy::dummy && inner_strat.style_to_return() != policy::erase_style_if_less_luma_policy::dummy ) {
                    return_style = inner_strat.style_to_return();
                }
            }
            break;
            case border_types::bottom: {
                const rectangle_type bottom_rect = rect.bottom().offset( 1, 0 );
                erase_callback_type inner_strat( reinsertion_list, border_types::top, bottom_rect, style );
                container.remove( bottom_rect, inner_strat );
                if ( strat.style_to_return() == policy::erase_style_if_less_luma_policy::dummy && inner_strat.style_to_return() != policy::erase_style_if_less_luma_policy::dummy ) {
                    return_style = inner_strat.style_to_return();
                }
            }
            break;
            case border_types::left: {
                const rectangle_type left_rect = rect.left().offset( 0, -1 );
                erase_callback_type inner_strat( reinsertion_list, border_types::right, left_rect, style );
                container.remove( left_rect, inner_strat );
                if ( strat.style_to_return() == policy::erase_style_if_less_luma_policy::dummy && inner_strat.style_to_return() != policy::erase_style_if_less_luma_policy::dummy ) {
                    return_style = inner_strat.style_to_return();
                }
            }
            break;
            case border_types::right: {
                const rectangle_type right_rect = rect.right().offset( 0, 1 ) ;
                erase_callback_type inner_strat( reinsertion_list, border_types::left, right_rect, style );
                container.remove( right_rect, inner_strat );
                if ( strat.style_to_return() == policy::erase_style_if_less_luma_policy::dummy && inner_strat.style_to_return() != policy::erase_style_if_less_luma_policy::dummy ) {
                    return_style = inner_strat.style_to_return();
                }
            }
            break;
            default:
                throw std::logic_error( "invalid case" );
        }
        //reinsert all the border_nodes that got split by the removal
        insert_border_list( reinsertion_list, container );
        return return_style;
    }

    /*!
     * \brief
     * remove borders in the rectangle and adjacent borders, for instance if the rect is A1:A1 we have to remove top
     * borders at A2 and left borders at B1...
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<int use_style>
    static inline void remove_borders_plus_adjacent( const border_types::type type, const sheet_range& rect, border_storage::container_type& container, const typename policy::select_style<use_style>::style_type& style ) {
        typedef typename border_storage_helper::erase_border_callback_with_style_as_template<typename policy::select_style<use_style>::policy_type>::erase_one_type_list_rects_and_type_callback_type erase_callback_type;
        typename erase_callback_type::list_type reinsertion_list;
        erase_callback_type strat( reinsertion_list, type, rect, style );
        container.remove( rect, strat );

        // then remove all the adjacent borders for this type
        switch ( type ) {
            case border_types::top: {
                if ( rect.upper_left().row() == 0 ) {
                    break;
                }
                const rectangle_type top_rect = rect.top().offset( -1, 0 );
                erase_callback_type strat( reinsertion_list, border_types::bottom, top_rect, style );
                container.remove( top_rect, strat );
            }
            break;
            case border_types::bottom: {
                if ( rect.lower_right().row() == static_cast<sheet_point::integer_type>( sheet_dimension::max_row ) ) {
                    break;
                }
                const rectangle_type bottom_rect = rect.bottom().offset( 1, 0 );
                erase_callback_type strat( reinsertion_list, border_types::top, bottom_rect, style );
                container.remove( bottom_rect, strat );
            }
            break;
            case border_types::left: {
                if ( rect.upper_left().column() == 0 ) {
                    break;
                }
                const rectangle_type left_rect = rect.left().offset( 0, -1 );
                erase_callback_type strat( reinsertion_list, border_types::right, left_rect, style );
                container.remove( left_rect, strat );
            }
            break;
            case border_types::right: {
                if ( rect.lower_right().column() == static_cast<sheet_point::integer_type>( sheet_dimension::max_column ) ) {
                    break;
                }
                const rectangle_type right_rect = rect.right().offset( 0, 1 ) ;
                erase_callback_type strat( reinsertion_list, border_types::left, right_rect, style );
                container.remove( right_rect, strat );
            }
            break;
            default:
                throw std::logic_error( "invalid case" );
        }

        //reinsert all the border_nodes that got split by the removal
        insert_border_list( reinsertion_list, container );
    }

    /*!
     * \brief
     * convenience function
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline void insert_border_list( const erase_one_type_list_only_rects_callback_type::list_type& insertion_list, const border_storage::border_index_type& index, border_storage::container_type& container, const bool try_merge = true ) {
        typedef erase_one_type_list_only_rects_callback_type::list_type list_type;
        typedef list_type::const_iterator const_iterator;

        if ( ! insertion_list.empty() ) {
            const_iterator it = insertion_list.begin(), end_it = insertion_list.end();
            for ( ; it != end_it; ++it ) {
                container.insert( *it, index, try_merge );
            }
        }
    }

    /*!
     * \brief
     * convenience function
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static inline void insert_border_list( const erase_one_type_list_rects_and_type_callback_type::list_type& insertion_list, border_storage::container_type& container, const bool try_merge = true ) {
        typedef erase_one_type_list_rects_and_type_callback_type::list_type list_type;
        typedef list_type::const_iterator const_iterator;

        if ( ! insertion_list.empty() ) {
            const_iterator it = insertion_list.begin(), end_it = insertion_list.end();
            for ( ; it != end_it; ++it ) {
                container.insert( it->first, it->second, try_merge );
            }
        }
    }

    /*!
     * \brief
     * split and add nodes to the container, for instance if left and top are set,
     * there will be two nodes added, one for the top with rect.top() as rectangle and
     * one for the left with rect.left() as rectangle.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<bool need_clearing_first, bool overwrite_only_if_darker>
    static inline void split_and_add_border_nodes( const sheet_range& rect, const ::border& b, border_storage::container_type& container ) {
        typedef rectangle_type::integer_type int_type;

        const long current_border_types = b.type();
        if ( current_border_types == border_types::none ) {
            return;
        }

        if ( border::check_border_type( current_border_types, border_types::inside_horizontal ) ) {
            //split INSIDE_HORIZONTAL into top and bottom
            const int_type start_row = rect.upper_left().row();
            const int_type end_row = rect.lower_right().row();;
            if ( ( end_row - start_row ) > 0 ) {
                const int_type start_col = rect.upper_left().column();
                const int_type end_col = rect.lower_right().column();;

                add_border<need_clearing_first, overwrite_only_if_darker>(
                    rectangle_type( point( start_row + 1, start_col ), point( end_row, end_col ) )
                    , border_types::top, b.style( border_types::inside_horizontal ), container );

                add_border<need_clearing_first, overwrite_only_if_darker>(
                    rectangle_type( point( start_row, start_col ), point( end_row - 1, end_col ) )
                    , border_types::bottom, b.style( border_types::inside_horizontal ), container );
            }
        }
        if ( border::check_border_type( current_border_types, border_types::inside_vertical ) ) {
            //split INSIDE_VERTICAL into left and right
            const int_type start_col = rect.upper_left().column();
            const int_type end_col = rect.lower_right().column();;
            if ( ( end_col - start_col ) > 0 ) {
                const int_type start_row = rect.upper_left().row();
                const int_type end_row = rect.lower_right().row();;

                add_border<need_clearing_first, overwrite_only_if_darker>(
                    rectangle_type( point( start_row, start_col + 1 ), point( end_row, end_col ) )
                    , border_types::left, b.style( border_types::inside_vertical ), container );

                add_border<need_clearing_first, overwrite_only_if_darker>(
                    rectangle_type( point( start_row, start_col ), point( end_row, end_col - 1 ) )
                    , border_types::right, b.style( border_types::inside_vertical ), container );
            }
        }
        if ( border::check_border_type( current_border_types, border_types::top ) ) {
            add_border<need_clearing_first, overwrite_only_if_darker>(
                rect.top(), border_types::top, b.style( border_types::top ), container );

        }
        if ( border::check_border_type( current_border_types, border_types::bottom ) ) {
            add_border<need_clearing_first, overwrite_only_if_darker>(
                rect.bottom(), border_types::bottom, b.style( border_types::bottom ), container );
        }
        if ( border::check_border_type( current_border_types, border_types::right ) ) {
            add_border<need_clearing_first, overwrite_only_if_darker>(
                rect.right(), border_types::right, b.style( border_types::right ), container );
        }
        if ( border::check_border_type( current_border_types, border_types::left ) ) {
            add_border<need_clearing_first, overwrite_only_if_darker>(
                rect.left(), border_types::left, b.style( border_types::left ), container );
        }
    }

    /*!
     * \brief
     * this function will look at the two rows or columns that are relevant to decide which
     * borders to insert when inserting a column or row and using copy format from left_or_above
     * or right _or_below. The returned value is compressed into one row or column with a
     * column-/row-count equal to the used range.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<typename vec_type, typename border_collector_type>
    static inline optional_sheet_range_type accumulate_borders_to_insert( vec_type& border_to_set, border_storage::container_type& container, const rectangle_type& used_range, const sheet_range& source_range, copy_format_from::type format_from, insert_shift_direction::type shift ) {
        if ( copy_format_from::none != format_from ) {
            if ( border_storage_helper::is_row_operation( shift ) ) {
                const bool row_is_zero = source_range.upper_left().row() == 0;
                //in this case, theres nowhere to copy from
                if ( row_is_zero && copy_format_from::left_or_above == format_from ) {
                    return optional_sheet_range_type();
                }
                sheet_range row_rect(
                    sheet_range::point_type( source_range.upper_left().row() - 1, used_range.upper_left().column() ),
                    sheet_range::point_type( source_range.upper_left().row(), used_range.lower_right().column() )
                );
                border_collector_type return_vec( false, false );
                border_storage::get_border_list_type tmp_list;
                get_border_callback strat( tmp_list, row_rect );
                container.query( row_rect, strat );
                foreach( const border_storage::get_border_list_type::value_type & v, tmp_list ) {
                    return_vec.insert( v.first, v.second );
                }
                const vec_type v = return_vec.to_vec( row_rect, true );
                border_to_set = v;
                return row_rect;
            } else if ( border_storage_helper::is_column_operation( shift ) ) {
                const bool col_is_zero = source_range.upper_left().column() == 0;
                //in this case, theres nowhere to copy from
                if ( col_is_zero && copy_format_from::left_or_above == format_from ) {
                    return optional_sheet_range_type();
                }
                sheet_range col_rect(
                    sheet_range::point_type( used_range.upper_left().row(), source_range.upper_left().column() - 1 ),
                    sheet_range::point_type( used_range.lower_right().row(), ( source_range.upper_left().column() ) )
                );

                border_collector_type return_vec( false, false );
                border_storage::get_border_list_type tmp_list;
                get_border_callback strat( tmp_list, col_rect );
                container.query( col_rect, strat );
                foreach( const border_storage::get_border_list_type::value_type & v, tmp_list ) {
                    return_vec.insert( v.first, v.second );
                }
                border_to_set = return_vec.to_vec( col_rect, false );
                return col_rect;
            }
        }
        return optional_sheet_range_type();
    }


    /*!
     * \brief
     * insert the list of borders after a column/row insertion at the appropriate places
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    template<typename vec_type>
    static inline void insert_borders_after_col_row_insert( vec_type& border_to_set, border_storage::container_type& container, const sheet_range& acc_rect, const sheet_range& source_range,  const sheet_range& target_range, copy_format_from::type format_from, insert_shift_direction::type shift ) {
        if ( copy_format_from::none != format_from && ! border_to_set.empty() ) {
            if ( border_storage_helper::is_row_operation( shift ) ) {
                int left_row = source_range.upper_left().row();
                int right_row = target_range.upper_left().row() - 1;

                typename vec_type::const_iterator it( border_to_set.begin() );
                typename vec_type::const_iterator end_it( border_to_set.end() );

                const typename vec_type::key_type offset = acc_rect.upper_left().column();

                for ( ; it != end_it; ++it ) {
                    const typename vec_type::key_type current_column = it->first + offset;
                    const rectangle_type current_rect( point( left_row, current_column ), point( right_row, current_column ) );
                    foreach( const typename vec_type::mapped_type::value_type & v, it->second ) {
                        border_storage_helper::add_border<false, false>( current_rect, v, container );
                    }
                }
            } else if ( border_storage_helper::is_column_operation( shift ) ) {
                int left_col = source_range.upper_left().column();
                int right_col = target_range.upper_left().column() - 1;

                typename vec_type::const_iterator it( border_to_set.begin() );
                typename vec_type::const_iterator end_it( border_to_set.end() );

                const typename vec_type::key_type offset = acc_rect.upper_left().row();

                for ( ; it != end_it; ++it ) {
                    const typename vec_type::key_type current_column = it->first + offset;
                    const rectangle_type current_rect( point( current_column, left_col ), point( current_column, right_col ) );
                    foreach( const typename vec_type::mapped_type::value_type & v, it->second ) {
                        border_storage_helper::add_border<false, false>( current_rect, v, container );
                    }
                }
            }
        }
    }

    static inline void remove_area( const sheet_range& rect, border_storage::container_type& container ) {
        typedef erase_border_callback<policy::list_rectangles_and_types_policy> erase_all_policy_type;
        erase_all_policy_type::list_type reinsertion_list;
        erase_all_policy_type strat( reinsertion_list, border_types::none, rect );
        container.remove( rect, strat );
        border_storage_helper::insert_border_list( reinsertion_list, container );
    }

    static inline void remove_areas( const sheet_range::rectangles_type& rects,  border_storage::container_type& container ) {
        foreach( const sheet_range & rect, rects ) {
            remove_area( rect, container );
        }
    }
};

namespace policy
{

    struct return_border_vec_simple_type : non_instantiable {
        typedef border_vec_type return_vec_type;
        template<bool add_inside_borders>
        static inline return_vec_type to_vec( const border_map_type& borders, const geometry::rectangle_type& rect/* , border_storage::value_map_type& val_map */ ) {
            return_vec_type return_vec;
            // special treatment of the result see declaration of m_simple_mode
            return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::top, border_storage_helper::check_border_same<add_inside_borders>( rect.top(), borders, border::border_type::top  ) ) );
            return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::bottom , border_storage_helper::check_border_same<add_inside_borders>( rect.bottom(), borders, border::border_type::bottom  ) ) );
            return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::left, border_storage_helper::check_border_same<add_inside_borders>( rect.left(), borders, border::border_type::left  ) ) );
            return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::right, border_storage_helper::check_border_same<add_inside_borders>( rect.right(), borders, border::border_type::right  ) ) );

            if ( add_inside_borders ) {

                if ( rect.row_count() < 2 ) {
                    return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::inside_horizontal, optional_border_idx_type() ) );
                } else {
                    optional_border_idx_type inside_horizontal = border_storage_helper::check_border_same<add_inside_borders>( rect.bottom(), borders, border::border_type::top );
                    inside_horizontal = border_storage_helper::check_border_same<add_inside_borders>( rect.top(), borders, border::border_type::bottom, inside_horizontal );
                    inside_horizontal = border_storage_helper::check_border_same<add_inside_borders>( geometry::rectangle_type(
                                            static_cast<sheet_point>( rect.upper_left().offset( 1, 0 ) ),
                                            static_cast<sheet_point>( rect.lower_right().offset( -1, 0 ) ) ), borders, border::border_type::top, inside_horizontal );
                    if ( ! inside_horizontal ) {
                        border_storage_helper::check_border_same<add_inside_borders>( geometry::rectangle_type(
                                    static_cast<sheet_point>( rect.upper_left().offset( 1, 0 ) ),
                                    static_cast<sheet_point>( rect.lower_right().offset( -1, 0 ) ) ), borders, border::border_type::bottom, inside_horizontal );
                    }
                    return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::inside_horizontal, inside_horizontal ) );
                }

                if ( ( rect.column_count() < 2 )  ) {
                    return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::inside_vertical, optional_border_idx_type() ) );
                } else {
                    optional_border_idx_type inside_vertical = border_storage_helper::check_border_same<add_inside_borders>( rect.left(), borders, border::border_type::right );
                    inside_vertical = border_storage_helper::check_border_same<add_inside_borders>( rect.right(), borders, border::border_type::left, inside_vertical );
                    inside_vertical = border_storage_helper::check_border_same<add_inside_borders>( geometry::rectangle_type(
                                          static_cast<sheet_point>( rect.upper_left().offset( 0, 1 ) ),
                                          static_cast<sheet_point>( rect.lower_right().offset( 0, -1 ) ) ), borders, border::border_type::right, inside_vertical );
                    if ( ! inside_vertical ) {
                        inside_vertical = border_storage_helper::check_border_same<add_inside_borders>( geometry::rectangle_type(
                                              static_cast<sheet_point>( rect.upper_left().offset( 0, 1 ) ),
                                              static_cast<sheet_point>( rect.lower_right().offset( 0, -1 ) ) ), borders, border::border_type::left, inside_vertical );
                    }
                    return_vec.push_back( border_storage_helper::border_from_idx( border::border_type::inside_vertical, inside_vertical ) );
                }

            }
            return return_vec;
        }
    };

    struct return_insert_col_row_vec_type : non_instantiable {
        typedef std::map<size_t, border_index_map_type> return_vec_type;
        template<bool is_row_vec>
        static inline return_vec_type to_vec( const border_map_type& borders, const geometry::rectangle_type& rect ) {
            return_vec_type return_vec;
            size_t idx = 0;
            const_iterator map_end( borders.end() );
            geometry::rectangle_type::const_iterator it1( rect.begin() ), it2( rect.begin() + ( is_row_vec ? ( rect.count() / 2 ) : 1 ) ), end_it( rect.end() );
            while ( it1 != end_it && it2 != end_it ) {
                const_iterator map_it1( borders.find( *it1 ) );
                const_iterator map_it2( borders.find( *it2 ) );
                if ( ( map_it1 != map_end ) && ( map_it2 != map_end ) ) {
                    const border_index_map_type combined_map = border_storage_helper::combine_sub( map_it1->second, map_it2->second );
                    if ( !combined_map.empty() ) {
                        return_vec[idx] = combined_map;
                    }
                }
                if ( is_row_vec ) {
                    ++it1;
                    ++it2;
                } else {
                    it1 += 2;
                    it2 += 2;
                }
                ++idx;
            }
            return return_vec;
        }

    };

    struct return_border_vec_type : non_instantiable {
        typedef border_vec_type return_vec_type;
        template<bool add_inside_borders>
        static inline return_vec_type to_vec( const border_map_type& borders, const geometry::rectangle_type& rect/* , border_storage::value_map_type& val_map */ ) {
            if ( !borders.empty() ) {
                return_vec_type return_vec;
                return_vec.resize( rect.count() );
                size_t idx = 0;
                const_iterator map_end( borders.end() );
                geometry::rectangle_type::const_iterator it( rect.begin() ), end_it( rect.end() );
                while ( it != end_it ) {
                    const_iterator map_it( borders.find( *it ) );
                    if ( map_it != map_end ) {
                        return_vec.set( idx, border_storage_helper::border_from_idx( map_it->second ) );
                    }
                    ++it;
                    ++idx;
                }
                return return_vec;
            }
            return return_vec_type();
        }
    };
} //namespace policy


/*!
 * \brief
 * vector to collect all the borders for a given rectangle
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<class return_vec_policy>
class border_collectorT
{
    typedef return_vec_policy return_type_policy;
public:
    typedef typename return_type_policy::return_vec_type return_vec_type;

    border_collectorT()
        : m_borders()
        , m_add_surrounding_borders( false )
        , m_add_inside_borders_in_simple_mode( false ) {}

    border_collectorT( const bool add_surrounding_borders, const bool add_inside_borders_in_simple_mode )
        : m_borders()
        , m_add_surrounding_borders( add_surrounding_borders )
        , m_add_inside_borders_in_simple_mode( add_inside_borders_in_simple_mode ) {}
    typedef boost::uint_fast32_t size_type;

    void insert( const sheet_point& position, const border_storage::border_index_type& b ) {
        calc_surrounding_borders( position, b );
        internal_insert( position, b );
    }

    void insert( const rectangle_type& rect, const border_storage::border_index_type& b ) {
        rectangle_type::const_iterator it( rect.begin() ), end_it( rect.end() );
        while ( it != end_it ) {
            insert( static_cast<sheet_point>( *it ), b );
            ++it;
        }
    }

    void insert( const rectangle_type& rect, const cf::optional_border_type& b ) {
        insert_if_non_empty( rect, b, ::border::border_type::top );
        insert_if_non_empty( rect, b, ::border::border_type::bottom );
        insert_if_non_empty( rect, b, ::border::border_type::left );
        insert_if_non_empty( rect, b, ::border::border_type::right );
    }

    void insert_if_non_empty( const rectangle_type& rect, const cf::optional_border_type& b, const ::border::border_type::type type ) {
        static const border_style_flyweight_type empty_dummy( "" );
        const border_style_flyweight_type idx = b->style( type );
        if ( idx != empty_dummy ) {
            insert( rect, std::make_pair( type, idx ) );
        }
    }
    inline return_vec_type to_vec( const geometry::rectangle_type& rect ) const {
        if ( m_add_inside_borders_in_simple_mode ) {
            return return_type_policy::template to_vec<true>( m_borders, rect );
        } else {
            return return_type_policy::template to_vec<false>( m_borders, rect );
        }
    }

    inline return_vec_type to_vec( const geometry::rectangle_type& rect, const bool is_row_vec ) const {
        if ( is_row_vec ) {
            return return_type_policy::template to_vec<true>( m_borders, rect );
        } else {
            return return_type_policy::template to_vec<false>( m_borders, rect );
        }
    }

    const bool empty() const {
        return m_borders.empty();
    }

    /* \brief simple mode
    * this mode is used when collecting borders for the GetBorderCommand.
    * the difference is that the returned vector always is of size 6 and
    * will return only one style for TOP, LEFT, BOTTOM, RIGHT, INSIDE_HORIZONTAL and INSIDE_VERTICAL.
    */

private:
    inline void calc_surrounding_borders( const sheet_point& position, const border_storage::border_index_type& b ) {
        if ( m_add_surrounding_borders ) {
            switch ( b.first ) {
                case border::border_type::top:
                    if ( position.row() != 0 ) {
                        internal_insert( sheet_point( position.row() - 1, position.column() ), border::border_type::bottom, b.second );
                    }
                    break;
                case border::border_type::bottom:
                    if ( position.row() != ( sheet_point::integer_type )( sheet_dimension::max_row )  ) {
                        internal_insert( sheet_point( position.row() + 1, position.column() ), border::border_type::top, b.second );
                    }
                    break;
                case border::border_type::left:
                    if ( position.column() != 0 ) {
                        internal_insert( sheet_point( position.row(), position.column() - 1 ), border::border_type::right, b.second );
                    }
                    break;
                case border::border_type::right:
                    if ( position.column() != ( sheet_point::integer_type )( sheet_dimension::max_column ) ) {
                        internal_insert( sheet_point( position.row(), position.column() + 1 ), border::border_type::left, b.second );
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void internal_insert( const sheet_point& position, const border_storage::border_index_type& b  ) {
        internal_insert( position, b.first, b.second );
    }

    void internal_insert( const sheet_point& position, const border_types::type type, const border_style_flyweight_type idx ) {
        m_borders[position][type] = idx;
    }

    border_map_type m_borders;

    const bool m_add_surrounding_borders;
    const bool m_add_inside_borders_in_simple_mode;
};

border_storage::border_storage() {}

border_storage::~border_storage() {}

const border_vec_type border_storage::border( const sheet_range& rect, const cf::cf_vec_type& cf_vec, bool add_surrounding_borders /* = false */, bool simple_mode /* = false */, bool add_inside_borders /* = true */ )
{
    get_border_list_type tmp_list;
    optional_sheet_range_type bigger_rect;
    if ( add_surrounding_borders ) {
        bigger_rect.reset( rect.enclose( sheet_range( rect.upper_left().checked_offset( -1, -1 ), rect.lower_right().checked_offset( 1, 1 ) ) ) );
    }
    const sheet_range& rect_to_use = add_surrounding_borders ? *bigger_rect : rect;
    get_border_callback strat( tmp_list, rect_to_use );
    m_container.query( rect_to_use, strat );
    const cf::cf_vec_type& cf_vec_direct = cf_vec;
    if ( tmp_list.empty() && cf_vec_direct.empty() ) {
        return border_vec_type();
    }

    if ( simple_mode ) {
        simple_border_collector_type return_vec( add_surrounding_borders, add_inside_borders );
        get_border_list_type::const_iterator it_start( tmp_list.begin() ), it_end( tmp_list.end() );
        for ( ; it_start != it_end; ++it_start ) {
            return_vec.insert( it_start->first,  it_start->second );
        }
        return return_vec.to_vec( rect );
    }

    border_collector_type return_vec( add_surrounding_borders, add_inside_borders );
    {
        get_border_list_type::const_iterator it_start( tmp_list.begin() ), it_end( tmp_list.end() );
        for ( ; it_start != it_end; ++it_start ) {
            return_vec.insert( it_start->first,  it_start->second );
        }
    }

    //add conditional format borders

    if ( !cf_vec_direct.empty() ) {
        size_t last_idx = 0;
        sheet_range::const_iterator rect_it( rect.begin() ), rect_end( rect.end() );
        cf::cf_vec_type::const_iterator cfm_it( cf_vec_direct.begin() ), cfm_end( cf_vec_direct.end() );
        for ( ; cfm_it != cfm_end; ++cfm_it ) {
            if ( cfm_it->second->border ) {
                rect_it += cfm_it->first - last_idx;
                last_idx = cfm_it->first;
                return_vec.insert( static_cast<geometry::rectangle_type>( *rect_it ), cfm_it->second->border );
            }
        }
    }

    return return_vec.to_vec( rect );
}

void border_storage::border( const sheet_range& rect, const ::border& b, const bool overwrite_only_if_darker /* = false */ )
{
    if ( overwrite_only_if_darker ) {
        border_storage_helper::split_and_add_border_nodes<true, true>( rect, b, m_container );
    } else {
        border_storage_helper::split_and_add_border_nodes<true, false>( rect, b, m_container );
    }
}

void border_storage::border( const sheet_range& rect, const long border_type, const border_style_flyweight_type& border_style )
{
    border_storage_helper::split_and_add_border_nodes<true, false>( rect, ::border( border_type, border_style ), m_container );
}

void border_storage::move( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from /*= copy_format_from::left_or_above*/, insert_shift_direction::type shift /*= insert_shift_direction::automatic */ )
{
    rectangle_type local_target( source_range.checked_offset( source_range.upper_left().distance( target_range.upper_left() ) ) );
    rectangle_type local_source( local_target.checked_offset( target_range.upper_left().distance( source_range.upper_left() ) ) );


    copy( local_source, local_target, target_sheet, shift );

    insert_col_row_border_collector_type::return_vec_type border_to_set;
    container_type::optional_rectangle_type used_range = m_container.used_range();
    if ( !used_range ) {
        return;
    }

    optional_sheet_range_type acc_rect = border_storage_helper::accumulate_borders_to_insert<insert_col_row_border_collector_type::return_vec_type, insert_col_row_border_collector_type>( border_to_set, m_container, *used_range, source_range, format_from, shift );

    const bool same_sheet = ( !target_sheet );
    border_locked_storage::auto_type locked_target(
        same_sheet ? NULL : border_locked_storage::create_locked_store( target_sheet ).release() );
    border_storage& target_store = same_sheet ? *this : locked_target->store();

    if ( same_sheet ) {
        border_storage_helper::remove_areas( source_range.cut( local_target ), m_container );
    } else {
        border_storage_helper::remove_area( source_range, m_container );
    }

    if ( copy_format_from::none != format_from && acc_rect ) {
        border_storage_helper::insert_borders_after_col_row_insert( border_to_set, target_store.m_container, *acc_rect, source_range, target_range, format_from, shift );
    }
}

void border_storage::erase( const sheet_range& source_range, erase_shift_direction::type /*shift*/ /* = erase_shift_direction::automatic */ )
{
    border_storage_helper::remove_area( source_range, m_container );
}

void border_storage::copy( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, insert_shift_direction::type /*shift*/ /*= insert_shift_direction::automatic */ )
{
    const bool same_sheet = ( !target_sheet );
    get_border_list_type copied_borders;
    copy_border_callback strat( copied_borders, source_range, target_range );
    m_container.query( source_range, strat  );
    border_locked_storage::auto_type locked_target(
        same_sheet ? NULL : border_locked_storage::create_locked_store( target_sheet ).release() );
    border_storage::container_type& target_container = same_sheet ? m_container : locked_target->store().m_container;

    border_storage_helper::remove_area( target_range, target_container );
    border_storage_helper::insert_border_list( copied_borders, target_container );
}

optional_sheet_range_type border_storage::used_range() const
{
    const border_storage::container_type::optional_rectangle_type used_range = m_container.used_range();

    if ( used_range ) {
        return sheet_range( sheet_point( used_range->upper_left() ), sheet_point( used_range->lower_right() ).checked_offset( 1, 1 ) );
    }
    return optional_sheet_range_type();
}

void border_storage::copy_fill( const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet )
{
    const bool same_sheet = ( !target_sheet );

    border_locked_storage::auto_type locked_target(
        same_sheet ? NULL : border_locked_storage::create_locked_store( target_sheet ).release() );
    border_storage::container_type& target_container = same_sheet ? m_container : locked_target->store().m_container;

    border_storage_helper::remove_areas( target_range.cut( source_range ), target_container );
    get_border_list_type reinsertion_list;
    copy_border_callback strat( reinsertion_list, source_range, target_range );
    m_container.query( source_range, strat );
    border_storage_helper::insert_border_list( reinsertion_list, m_container );
}

void border_storage::dump() const
{
#if defined(_DEBUG) && defined(DEBUG_BORDER_MANAGER)
    std::cout << " ---------- starting dump of borders tree " << std::endl << std::endl;
    std::cout << m_container;
    std::cout << std::endl << " ---------- done with dump of borders tree " << std::endl;
#endif
}

border_storage::undo_list_type border_storage::get_list_for_undo( const sheet_range& r )
{
    const container_type::optional_rectangle_type used_range = m_container.used_range();
    if ( used_range ) {
        if ( used_range->does_intersect( r ) ) {
            undo_list_type undo_list;
            get_border_callback strat( undo_list, r );
            m_container.query( r, strat );
            return undo_list;
        }
    }
    return undo_list_type();
}

void border_storage::apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list )
{
    erase( r );
    border_storage_helper::insert_border_list( undo_list, m_container );
}

void border_storage::release_memory( bool purge )
{
    container_type::release_memory( purge );
}
