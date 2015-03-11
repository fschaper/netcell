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
#include <wss/interpreter_context.hpp>
#include <wss/opcode.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <vector>
#endif

/*!
 * \brief
 * function parameter object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE function_parameter
    : boost::noncopyable
{
    typedef std::list<interpreter_variant> container_type;
public:
    typedef container_type::iterator iterator;
    typedef container_type::const_iterator const_iterator;
    typedef boost::shared_ptr<positioned_op_codes> positioned_op_codes_auto_type;
    typedef std::vector<positioned_op_codes_auto_type> subtree_vector_type;
    typedef std::auto_ptr<subtree_vector_type> subtree_vector_auto_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    function_parameter( interpreter_context& ic, unsigned int parameter_count, subtree_vector_auto_type subtree = subtree_vector_auto_type() );

    /*!
     * \brief
     * passed argument count
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    container_type::size_type count() const;

    /*!
     * \brief
     * interpreter context.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_context& context() const;

    /*!
     * \brief
     * current session object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::session& session() const;

    /*!
     * \brief
     * direct accessor to an parameter to the function
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_variant& operator[]( container_type::size_type index );

    /*!
     * \brief
     * partial subtree for lazy evaluation (mainly used for the IF function)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const subtree_vector_type& subtree() const;

    /*!
     * \brief
     * begin iterator over the function parameters
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    iterator begin();

    /*!
     * \brief
     * end iterator over the function parameters.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    iterator end();

    /*!
     * \brief
     * const begin iterator over the function parameters
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator begin() const;

    /*!
     * \brief
     * const end iterator over the function parameters
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator end() const;

private:
    interpreter_context& m_ic;
    container_type m_parameters;
    subtree_vector_auto_type m_subtree;
};

