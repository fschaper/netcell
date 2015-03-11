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

#include <wss/define.hpp>
#include <wss/type.hpp>

#include "border_storage.hpp"
#include "wss/border_types.hpp"
#include "copy_fill_iterator.hpp"
#include "wss/non_instantiable.hpp"

#include <boost/cast.hpp>
#include <boost/type_traits/is_same.hpp>

/*!
 * \brief
 * border callbacks
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */

class get_border_callback
{
public:

    get_border_callback( border_storage::get_border_list_type& borders, const sheet_range& rect )
        : m_borders( borders ), m_rect( rect ) {}

    bool operator()( const r::r_tree_rectangle_type& r, const border_storage::border_index_type& index ) {
        m_borders.push_back( std::make_pair( r.intersection( m_rect ), index ) );
        return true;
    }

    border_storage::get_border_list_type& m_borders;
    const sheet_range& m_rect;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

namespace policy
{
    typedef boost::tuple<float, float, float> color_rgb_type;

    inline float convert_to_rgb( const std::string& s, const size_t start )
    {
        float value = 0.0;

        int a = 0;
        size_t b = start + 1;

        assert( s.length() > b );

        for ( int i = 0; i < 2; i++, a++, b-- ) {
            if ( s[b] >= '0' && s[b] <= '9' ) {
                value += ( s[b] - '0' ) * ( 1 << ( a * 4 ) );
            } else {
                switch ( s[b] ) {
                    case 'A':
                    case 'a':
                        value += 10 * ( 1 << ( a * 4 ) );
                        break;

                    case 'B':
                    case 'b':
                        value += 11 * ( 1 << ( a * 4 ) );
                        break;

                    case 'C':
                    case 'c':
                        value += 12 * ( 1 << ( a * 4 ) );
                        break;

                    case 'D':
                    case 'd':
                        value += 13 * ( 1 << ( a * 4 ) );
                        break;

                    case 'E':
                    case 'e':
                        value += 14 * ( 1 << ( a * 4 ) );
                        break;

                    case 'F':
                    case 'f':
                        value += 15 * ( 1 << ( a * 4 ) );
                        break;

                    default:
                        return 0.0;
                        break;
                }
            }
        }
        return value;
    }

    template<int dummy_val>
    inline color_rgb_type convert_to_rgb( const std::string& s )
    {
        const float float_dummy = static_cast<float>( dummy_val );
        const size_t start = s.find_first_of( '#' );
        if ( start == std::string::npos && s.size() > start + 6 ) {
            return color_rgb_type( float_dummy, float_dummy, float_dummy );
        }

        return color_rgb_type( convert_to_rgb( s, start + 1 ), convert_to_rgb( s, start + 3 ), convert_to_rgb( s, start + 5 ) );
    }

    template<int dummy_val>
    inline float calculate_luma( const border_style_flyweight_type& style )
    {
        static const float K_ry = 0.299f * 255.0f;
        static const float K_by = 0.114f * 255.0f;
        static const float K_gy = 255.0f - K_by - K_ry;

        const color_rgb_type rgb = convert_to_rgb<dummy_val>( style.get() );
        return K_ry * rgb.get<0>() + K_gy * rgb.get<1>() + K_gy * rgb.get<2>();
    }

    template<class T>
    class erase_all_policyT
    {
    protected:
        typedef int style_type;

        erase_all_policyT( const T&  ) {}
    public:
        enum {dummy = 0};
        static inline bool check_type( const T& /*current_type*/ ) {
            return true;
        }
    };

    typedef erase_all_policyT<border_types::type> erase_all_policy;
    typedef erase_all_policyT<int> erase_all_styles_policy;



    class erase_type_policy
    {
    protected:
        erase_type_policy( const border_types::type type_to_erase )
            : m_type_to_erase( type_to_erase ) {}
    public:
        inline bool check_type( const border_types::type current_type ) const {
            return current_type == m_type_to_erase;
        }
        const border_types::type m_type_to_erase;
    };

    class erase_style_policy
    {
    protected:
        typedef border_style_flyweight_type style_type;
        static const border_style_flyweight_type dummy;

        erase_style_policy( const border_style_flyweight_type& style_to_erase )
            : m_style_not_to_erase( style_to_erase ) {}
    public:
        inline bool check_type( const border_style_flyweight_type& current_style ) const {
            return current_style != m_style_not_to_erase;
        }
        const border_style_flyweight_type& m_style_not_to_erase;
    };

    class erase_style_if_less_luma_policy
    {
    public:
        inline bool check_type( const border_style_flyweight_type& current_style ) const {
            if ( calculate_luma<1>( current_style ) > m_given_luma ) {
                return true;
            } else {
                m_style_to_return = current_style;
                return false;
            }
        }

        inline const border_style_flyweight_type& style_to_return() const {
            return m_style_to_return;
        }

        static const border_style_flyweight_type dummy;
    private:


    protected:
        typedef border_style_flyweight_type style_type;


        erase_style_if_less_luma_policy( const border_style_flyweight_type& style_with_luma_to_check )
            : m_given_luma( calculate_luma<0>( style_with_luma_to_check ) )
            , m_style_to_return( dummy ) {}

        const float m_given_luma;
        mutable border_style_flyweight_type m_style_to_return;
    };


    const border_style_flyweight_type erase_style_policy::dummy = border_style_flyweight_type( "" );
    const border_style_flyweight_type erase_style_if_less_luma_policy::dummy = border_style_flyweight_type( "" );

    template<int use_style>
    struct select_style : non_instantiable {
        typedef border_style_flyweight_type style_type;
        typedef erase_style_policy policy_type;

        template<class T>
        static style_type get( const T& t ) {
            return t;
        }
    };

    template<>
    struct select_style<0> : non_instantiable {
        typedef int style_type;
        typedef policy::erase_all_styles_policy policy_type;
        enum {dummy = policy_type::dummy};

        template<class T>
        static style_type get( const T& ) {
            return dummy;
        }
    };

    template<>
    struct select_style<2> : non_instantiable {
        typedef border_style_flyweight_type style_type;
        typedef erase_style_if_less_luma_policy policy_type;

        template<class T>
        static style_type get( const T& t ) {
            return t;
        }
    };

    template<class erase_style_policyT>
    struct select_style_type: non_instantiable {
        enum { do_style_select =
                   boost::mpl::plus <
                   boost::mpl::times<boost::is_same<erase_style_policyT,  erase_style_policy>, boost::mpl::int_<1> >,
               boost::mpl::times<boost::is_same< erase_style_policyT, erase_style_if_less_luma_policy>, boost::mpl::int_<2> >
               >::type::value
             };
        typedef select_style< do_style_select > style_selector;
        typedef typename style_selector::style_type style_type;
        static style_type get( const border_style_flyweight_type& style ) {
            return style_selector::get( style );
        }
    };

    class list_only_rectangles_policy
    {
    public:
        typedef std::list<geometry::rectangle_type> list_type;
        list_only_rectangles_policy( list_type& return_list )
            : m_list( return_list ) {}

        void insert_into_list( const geometry::rectangle_type& r, const border_storage::border_index_type& i ) const {
            m_list.push_back( r );
        }
    private:
        mutable list_type& m_list;
    };

    class list_rectangles_and_types_policy
    {
    public:
        typedef border_storage::get_border_list_type list_type;
        list_rectangles_and_types_policy( list_type& return_list )
            : m_list( return_list ) {}

        void insert_into_list( const geometry::rectangle_type& r, const border_storage::border_index_type& i ) const {
            m_list.push_back( std::make_pair( r, i ) );
        }
    private:
        mutable list_type& m_list;
    };

} // namespace policy

template < class list_policyT, class erase_type_policyT = policy::erase_all_policy, class erase_style_policyT = policy::erase_all_styles_policy >
class erase_border_callback : list_policyT, erase_type_policyT, public erase_style_policyT
{
public:
    typedef typename list_policyT::list_type list_type;

    erase_border_callback( list_type& reinsertion_list, const border_types::type type_to_erase, const geometry::rectangle_type source_rect, const typename erase_style_policyT::style_type& style = erase_style_policyT::dummy  )
        : list_policyT( reinsertion_list )
        , erase_type_policyT( type_to_erase )
        , erase_style_policyT( style )
        , m_source_rect( source_rect )
    {}

    bool operator()( const r::r_tree_rectangle_type& r, const border_storage::border_index_type& i ) const {
        if ( erase_type_policyT::check_type( i.first ) && erase_style_policyT::check_type( policy::select_style_type<erase_style_policyT>::get( i.second ) ) ) {
            const r::r_tree_rectangle_type::rectangles_type cut_rect_list = r.cut( m_source_rect );
            typedef r::r_tree_rectangle_type::rectangles_type::const_iterator const_iterator;
            const_iterator it = cut_rect_list.begin(), end_it = cut_rect_list.end();
            for ( ; it != end_it; ++it ) {
                list_policyT::insert_into_list( *it, i );
            }
            return true;
        }
        return false;
    }

    const geometry::rectangle_type m_source_rect;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class copy_border_callback
{
public:
    copy_border_callback( border_storage::get_border_list_type& reinsertion_list, const sheet_range& source_rect, const sheet_range& target_rect )
        : m_reinsertion_list( reinsertion_list )
        , m_source_rect( source_rect )
        , m_target_rect( target_rect )
        , m_distance( source_rect.distance( target_rect ) ) {}

    bool operator()( const r::r_tree_rectangle_type& r, const border_storage::border_index_type& i ) {
        copy_fill_iterator it( m_source_rect, m_target_rect );
        const sheet_range intersection = r.intersection( m_source_rect );
        while ( it.is_valid() ) {
            m_reinsertion_list.push_back( std::make_pair( intersection.offset( *it ), i ) );
            ++it;
        }
        return true;
    }


    border_storage::get_border_list_type& m_reinsertion_list;
    const sheet_range& m_source_rect;
    const sheet_range& m_target_rect;
    const geometry::point m_distance;
};
