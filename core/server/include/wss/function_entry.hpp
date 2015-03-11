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

#include <wss/interpreter_variant.hpp>
#include <wss/function_parameters.hpp>
#include <wss/i_function_wrapper.hpp>
#include <wss/return_type_format.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/algorithm/string.hpp>
# include <boost/function.hpp>
# include <typeinfo>
#endif // HAS_PRECOMPILED_HEADER == 0


//class function_parameter;
class base_node;

typedef boost::function<interpreter_variant( function_parameter& )> extension_function;

/*!
 * \brief
 * entry in the server-wide function catalog.
 *
 * provides information about the function and an
 * callback to access it.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE function_entry
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    function_entry( extension_function callback
                    , const utf8_ci_string& name
                    , const std::string& argument_mask
                    , bool is_volatile = false
                                         , bool is_lazy = false
                                                 , bool need_view_independent_calculation = false
                                                         , bool execute_on_set = false
                                                                 , return_type_format::type return_type = return_type_format::unspecified );

    /*!
     * \brief
     * internal name of the function
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const utf8_ci_string& internal_name() const {
        return m_name;
    }

    /*!
     * \brief
     * function argument mask
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const std::string& argument_mask() const {
        return m_argument_mask;
    }

    /*!
     * \brief
     * function is volatile or not
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_volatile() const {
        if ( const i_function_wrapper* ifw = m_callback.target<i_function_wrapper>() ) {
            return ifw->is_volatile();
        } else {
            return m_is_volatile;
        }
    }

    /*!
     * \brief
     * function requires lazy evaluation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_lazy() const {
        return m_is_lazy;
    }

    /*!
     * \brief
     * function needs to be calculated view independently
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline bool is_in_need_of_view_independent_calculation() const {
        if ( const i_function_wrapper* ifw = m_callback.target<i_function_wrapper>() ) {
            return ifw->is_view_independent();
        } else {
            return m_is_view_independent;
        }
    }

    inline return_type_format::type return_type() const {
        return m_return_type;
    }

    /*!
     * \brief
     * function callback.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_variant operator()( function_parameter& parameter ) {
        return m_callback( parameter );
    }

    /*!
     * \brief
     * function executes on set
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    inline bool execute_on_set() const {
        return m_execute_on_set;
    }
private:
    extension_function m_callback;
    // name of the function used in worksheet
    utf8_ci_string m_name;
    // list of arguments accepted by the function
    // if left empty the function accepts everything
    // S  = string
    // D  = double
    // R  = range reference
    // C  = cell reference
    // |  = or
    // [] = optional
    // f.ex. "S|DR[RC]" would take an string or double
    // as the first parameter followed by an range and
    // an optional range followed by an cell-reference.
    std::string m_argument_mask;
    // set to true if the function result should not be cached
    // by the interpreter (f.ex. NOW() or functions that query a database).
    bool m_is_volatile;
    // determines if the interpreter should evaluate subtrees.
    bool m_is_lazy;
    // determines if the function need be executed independent of the currently
    // selected view range on the server
    bool m_is_view_independent;
    //determines if the function will be executed when set
    bool m_execute_on_set;
    //function return type - determines if the function result should be formatted
    const return_type_format::type m_return_type;
};

