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

//#include <wss/i_dependency.hpp>
#include <wss/sheet_point.hpp>
#include <wss/destroying_auto_pointer.hpp>
#include <wss/ast_formula.hpp>
#include <wss/variant.hpp>
#include <wss/variable_map.hpp>
#include <wss/opcode.hpp>
#include <wss/friend.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <string>
#endif // HAS_PRECOMPILED_HEADER == 0

class locale;
class base_node;
class named_formula;

/*!
 * \brief
 * formula implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE formula : boost::noncopyable
{
    FRIEND_CLASS named_formula;
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula( ast_formula& ast, const shared_dependency_type& container, const sheet_point& created_at_position, const referencetable_type& references = referencetable_type(), const bool inside_nf = false );

    /*!
     * \brief
     * used for copy operations.
     *
     * the references of the passed formula (the one to be copied) will be 'rewritten'
     * to their new target destination (using 'distance').
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    formula( const formula& other, const shared_dependency_type& container, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range = sheet_range( sheet_point( 0, 0 ) ), const referencetable_type& references = referencetable_type() );

    /*!
     * \brief
     * used for rewriting named_formula formulas.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    formula( const formula& other, const shared_dependency_type& container, const geometry::point& distance, bool is_rewrite_to_clone_sheet );

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~formula();

    /*!
     * \brief
     * returns true in case the formula contains precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_precedents() const;

    /*!
     * \brief
     * returns true in case the formula is of volatile value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_volatile() const;

    /*!
     * \brief
     * return the formulas precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    referencetable_type precedents() const;
    referencetable_type precedents( const shared_dependency_type& d ) const;

    /*!
     * \brief
     * return the pretty printed formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string pretty_print( const locale& l, const bool always_add_sheet_references = false ) const;
    std::string pretty_print( const locale& l, const shared_dependency_type& d, const bool always_add_sheet_references = true ) const;

    variant calculate( interpreter_context& ic ) const;

    /*!
     * \brief
     * return a list of variables defined in the formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const variable_map& variable() const;

    /*!
     * \brief
     * return the coverage of the formula. (f.ex. A1:C5)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type coverage() const;
    optional_sheet_range_type coverage( const shared_dependency_type& d ) const;

    inline bool is_relative() const {
        return m_opcode.is_relative;
    }

    /*!
     * \brief
     * this will add/remove/update a positional opcode, only used inside named formulas!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void add_position( const shared_dependency_type& target_dependency );
    void remove_position( i_dependency* target_dependency );
    void update_position( const shared_dependency_type& target_dependency,  const geometry::point& distance, const bool move_absolute_references );
    void update_position_without_rewrite( const shared_dependency_type& target_dependency,  const geometry::point& distance );

    /*!
     * \brief
     * more functions needed to handle named_formulas used at different positions
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void lower_volatile_count( const shared_dependency_type& d );
    void raise_volatile_count( const shared_dependency_type& d );
    size_t volatile_count( const shared_dependency_type& d ) const;
    size_t volatile_count_without_formula( const shared_dependency_type& d ) const;
    void flag_dirty( const shared_dependency_type& d );
    bool is_dirty( const shared_dependency_type& d ) const;
    void unflag_dirty( const shared_dependency_type& d );
    bool is_view_independent() const;
    bool executes_on_set() const;
    void adjust_legacy_references( const sheet_point& position );

private:
    positioned_op_codes m_opcode;
    weak_dependency_type m_container;
    bool m_is_volatile;
    variable_map m_variable;
    bool m_is_view_independent;
    bool m_execute_on_set;
};
