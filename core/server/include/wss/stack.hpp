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

#include <wss/stack_underflow_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <stack>
#endif

/*!
 * \brief
 * convenience wrapper for the STL stack class.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class value_T
>
class stack
{
    typedef std::stack<value_T> stack_type;
public:
    typedef typename stack_type::size_type size_type;
    typedef typename stack_type::value_type value_type;

    /*!
     * \brief
     * return the element currently on top of the stack
     * without removing the element from the stack.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const value_type& peek() const {
        if ( m_stack.empty() ) {
            throw stack_underflow_exception();
        }
        return m_stack.top();
    }

    /*!
     * \brief
     * retrieve the currently top-most element from the stack.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    value_type pop() {
        if ( m_stack.empty() ) {
            throw stack_underflow_exception();
        }
        value_type return_value = m_stack.top();
        m_stack.pop();
        return return_value;
    }

    /*!
     * \brief
     * push the passed element on top of the stack.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void push( const value_type& v ) {
        m_stack.push( v );
    }

    /*!
     * \brief
     * current size of the stack.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type size() const {
        return m_stack.size();
    }

    /*!
     * \brief
     * returns true if the stack contains no elements.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool empty() const {
        return m_stack.empty();
    }

private:
    std::stack<value_type> m_stack;
};
