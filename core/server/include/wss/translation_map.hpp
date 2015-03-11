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

#include <wss/define.hpp>
#include <wss/locale.hpp>
#include <wss/ci_string.hpp>
#include <wss/variant.hpp>
#include <wss/non_instantiable.hpp>
#include <wss/translation_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <boost/scoped_ptr.hpp>
#   include <boost/shared_ptr.hpp>
#   include <boost/make_shared.hpp>
#   include <boost/multi_index_container.hpp>
#   include <boost/multi_index/member.hpp>
#   include <boost/multi_index/ordered_index.hpp>
#   include <stdexcept>
#   include <string>
#   include <vector>
#   include <list>
#   include <map>
#endif

#if defined(USING_VS_2010)
#include <boost/config/suffix.hpp>
#endif

class translation_map;
typedef boost::shared_ptr<translation_map> shared_translation_map_type;

namespace bmi = boost::multi_index;

/*!
 * \brief
 * provides a view into an map.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class map_T>
class lookup_view
{
public:
    typedef typename map_T::value_type::second_type value_type;
    typedef typename map_T::key_type key_type;

    lookup_view( map_T& ref )
        : m_map( ref ) {}

    const value_type& operator[]( const key_type& k ) const {
        typename map_T::const_iterator it( m_map.find( k ) );
        if ( it == m_map.end() ) {
            throw translation_exception();
        }
        return it->second;
    }

private:
    map_T& m_map;
};

/*!
 * \brief
 * translation map
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE translation_map
    : boost::noncopyable
{
    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const&, A6 const&, A7 const& );
public:
    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_translation_map_type create( const ::locale& l, const std::string& parameter_separator, const std::string& column_separator, const std::string& row_separator, bool use_dot, const std::string& t_true, const std::string& t_false );

    /*!
     * \brief
     * parameter information block.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct parameter_info {
        std::string name;
        std::string description;
    };

    /*!
     * \brief
     * translation entry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct WSS_MODULE function_translation_entry {
        function_translation_entry() {}

        function_translation_entry( const std::string& id
                                    , const std::string& transl
                                    , const std::string& long_desc = ""
                                            , const std::string& short_desc = ""
                                  );

        std::string identifier;                     // English notation (used internally) like 'sum'
        std::string translation;                    // translation (like in German 'summe')
        std::string description_long;               // function description
        std::string description_short;              // short description of the function
        std::vector<parameter_info> parameters;     // parameter information
    };

    /*!
     * \brief
     * mapping from of locale specific error types such as
     * #DIV/0! or #REF!
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct error_mapping
            : non_instantiable {
        struct code_tag {};
        struct string_tag {};

        /*!
         * \brief
         * error type to string mapping
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        typedef std::pair<variant::error_type, std::string> entity_type;

        /*!
         * \brief
         * error -> string / string -> error mapping.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */


#if defined(USING_VS_2010)
        BOOST_STATIC_CONSTANT( unsigned,
                               first_offset = offsetof( entity_type, first ) );
        BOOST_STATIC_CONSTANT( unsigned,
                               second_offset = offsetof( entity_type, second ) );

        typedef bmi::multi_index_container < entity_type
        , bmi::indexed_by <
        bmi::ordered_unique<bmi::tag<code_tag>, bmi::member_offset<entity_type, const entity_type::first_type, first_offset> >,
            bmi::ordered_unique<bmi::tag<string_tag>, bmi::member_offset<entity_type, const entity_type::second_type, second_offset> >
            >
            > type;
#else
        typedef bmi::multi_index_container < entity_type
        , bmi::indexed_by <
        bmi::ordered_unique<bmi::tag<code_tag>, bmi::member<entity_type, entity_type::first_type, &entity_type::first> >,
            bmi::ordered_unique<bmi::tag<string_tag>, bmi::member<entity_type, std::string, &entity_type::second> >
            >
            > type;
#endif
    };

    /*!
     * \brief
     * adds a translation enty to the map.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add( const function_translation_entry& entry );

    /*!
     * \brief
     * retreive the error mapping object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const error_mapping::type& error_translation() const;

    /*!
     * \brief
     * set the error mapping object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void error_translation( const error_mapping::type& map );

    /*!
     * \brief
     * retreive the associated locale object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::locale& locale() const;

    /*!
     * \brief
     * retreive the parameter separator for the locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& parameter_separator() const;

    /*!
     * \brief
     * retreive the column separator for the locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& column_separator() const;

    /*!
     * \brief
     * retreive the row separator for the locale.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& row_separator() const;

    /*!
     * \brief
     * text representation of boolean true.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& boolean_true() const;

    /*!
     * \brief
     * text representation of boolean false.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& boolean_false() const;

    /*!
     * \brief
     * determines if the 'dot' character should separate
     * the integral part and fractional part.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool use_dot_as_real_separator() const;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    translation_map( const ::locale& l, const std::string& parameter_separator, const std::string& column_separator, const std::string& row_separator, bool use_dot, const std::string& t_true, const std::string& t_false );

private:
    typedef std::map<utf8_ci_string, const function_translation_entry*> lookup_table_type;
    typedef std::list<function_translation_entry> function_translation_list_type;
    function_translation_list_type m_entry_map;
    ::locale m_locale;
    std::string m_parameter_separator;
    std::string m_column_separator;
    std::string m_row_separator;
    std::string m_boolean_true;
    std::string m_boolean_false;
    bool m_use_dot_as_real_separator;
    error_mapping::type m_error_translation_map;

    lookup_table_type m_internal_lookup;
    lookup_table_type m_external_lookup;

public:
    lookup_view< lookup_table_type > internal_name_lookup;
    lookup_view< lookup_table_type > external_name_lookup;
};

