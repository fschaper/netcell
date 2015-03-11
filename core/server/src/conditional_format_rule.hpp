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
#include <wss/variant.hpp>
#include <wss/free_formula.hpp>
#include <wss/session.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/enable_shared_from_this.hpp>
#   include <boost/scoped_ptr.hpp>
#   include <boost/shared_ptr.hpp>
#   include <boost/make_shared.hpp>
#   include <string>
#   include <vector>
#endif // HAS_PRECOMPILED_HEADER == 0

namespace cf
{
    class conditional_format_rule_parser;
    class conditional_format_rule;
    class conditional_format_formula_writer;

    typedef boost::shared_ptr<conditional_format_rule> shared_conditional_format_rule_type;

    class conditional_format_rule
        : boost::noncopyable
        , public boost::enable_shared_from_this<conditional_format_rule>
    {
    public:
        typedef shared_free_formula_type operand_type;
        typedef std::vector< operand_type > operand_vec_type;

        friend class conditional_format_rule_parser;
        friend class conditional_format_formula_writer;
#ifndef WIN32
        // (fschaper) MSVC8 has problems with template friends if they belong to
        // another namespace. workaround provided by explicit declaration.
        template< class T, class A1, class A2, class A3, class A4 >
        friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const& );

        template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
        friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const&, A4 const&, A5 const&, A6 const& );
#endif

        /*!
        * \brief
        * create a conditional format rule
        *
        * \param s - session context
        *
        * \param rule - the conditional formatting rule
        *
        * \param operand_vec - a vector holding the free formulas involved
        *
        * \param position
        *
        * \param ws - the worksheet
        *
        * \param rule_operands - operands the rule might need
        *
        * \param range - the rectangles the rule is applied on
        *
        * \return a shared_conditional_format_rule_type holding the newly created rule
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        static shared_conditional_format_rule_type create( session& s, const std::string& rule, operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws, const sheet_range& range );

        shared_conditional_format_rule_type clone_with_new_range_for_copy( session& s, const sheet_range& range, const sheet_range& old_range, const shared_worksheet_type& target_ws ) const;
        shared_conditional_format_rule_type clone_with_new_range_for_move( session& s, const sheet_range& range, const sheet_range& old_range, const shared_worksheet_type& target_ws ) const;
        shared_conditional_format_rule_type clone_with_new_range_for_copy_move( session& s, const sheet_range& range, const sheet_range& old_range, const sheet_range& source_range, const geometry::point& distance ) const;

        bool matches( session& s, const variant& val, const sheet_point& position ) const;

        /*!
        * \brief
        * convert the rule to string representation
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        std::string to_string( session& s, const bool solve_formulas  = false  ) const;

        /*!
        * \brief
        * convert the operands into a variant given a specific position
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        std::vector<std::string> get_operand_as_string_array( session& s, const sheet_point& position ) const;

        const bool does_match( session& s, const sheet_point& position, const sheet_range::rectangles_type& ranges ) const;

        /*!
         * \brief
         * the different types of rules
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        enum rule_types {
            UNDEFINED_TYPE
            , CELL_VALUE
            , TEXT
            , BLANKS, NO_BLANKS
            , ERRORS, NO_ERRORS
            , TOP, BOTTOM, TOP_PERCENT, BOTTOM_PERCENT
            , DUPLICATE_VALUE, UNIQUE_VALUE
            , FORMULA_TRUE
            , COLOR_SCALE
            , DATA_BAR, ICON_SETS
            , AVERAGE_VALUE
        };

        /*!
        * \brief
        * the different operators used in rules
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        enum value_rule_operators {
            none, EQ, NEQ, GTE, LTE, GT, LT, BETWEEN, NBETWEEN
            , STD_DEV_ABOVE_1, STD_DEV_ABOVE_2, STD_DEV_ABOVE_3, STD_DEV_BELOW_1, STD_DEV_BELOW_2, STD_DEV_BELOW_3
        };

        /*!
        * \brief
        * the different text-operators used in text-rules
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        enum text_rule_operators {
            undefined, CONTAINED, NOT_CONTAINED, BEGINS_WITH, ENDS_WITH
        };

        /*!
        * \brief
        * returns true if the rule is dirty because i.e. some values changed
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        const bool is_dirty( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const;

        /*!
        * \brief
        * returns the stop_if_true parameter of the rule
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        const bool stop_if_true() const;

        /*!
        * \brief
        * returns the worksheet
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        weak_worksheet_type worksheet();

        bool parsing_successful() const {
            return m_parsing_successful;
        }

#ifdef WIN32
        // (fschaper) MSVC8 broken compiler workaround for template friends from
        // foreign namespaces (C2888).
    public:
#else
    private:
#endif
        /*!
         * \brief
         * constructor - don't use this function! use conditional_format_rule::create to get a new rule!
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        conditional_format_rule( session& s, const std::string& rule, const operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws, const sheet_range& range );

        conditional_format_rule( session& s, const operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws );

#ifdef WIN32
    private:
#endif
        const bool does_match( const sheet_point& position, const sheet_range::rectangles_type& ranges ) const;
        //the type of rule we're dealing with
        rule_types m_rule_type;
        //the operands (only used in combination with some rule types
        operand_vec_type m_operands;
        //the rule operator (i.e. ">", "<=", ..)
        value_rule_operators m_op;
        //the operator used when doing text comparisons
        text_rule_operators m_text_op;
        //nr of top elements when rule type is one of TOP, BOTTOM
        //in case of TOP_PERCENT or BOTTOM_PERCENT the nr is interpreted as percentage
        variant m_nr_of;
        //indicates if we should stop after this rule
        bool m_stop_if_true;
        //the rulename as string
        std::string m_rulename;
        //indicates if parsing was successfully finished
        bool m_parsing_successful;
        //the worksheet this rule belongs to
        weak_worksheet_type m_ws;
        //the formula that
        shared_free_formula_type m_formula;
        //the cached value
        class cached_value;
        mutable boost::scoped_ptr<cached_value> m_cached_value;
    };
}
