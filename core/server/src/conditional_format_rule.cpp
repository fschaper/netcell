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
#include "conditional_format_rule.hpp"
#include "conditional_format_rule_parser.hpp"
#include <wss/rectangle.hpp>
#include "conditional_format_formula_writer.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0
#include "wss/invalid_worksheet_exception.hpp"

namespace cf
{
    inline std::string remove_leading_equal_sign( const std::string& formula )
    {
        if ( formula.compare( 0, 1, "=" ) == 0 ) {
            return formula.substr( 1 );
        }
        return formula;
    }

    class conditional_format_rule::cached_value
    {
        typedef sparse_vector<bool> cached_results_vec;

    public:
        cached_value()
            : has_vec( false )
            , m_cached_bool_value( false ) {}

        bool is_vector() const {
            return has_vec;
        }

        const bool get( const size_t idx ) const {
            assert( ( !has_vec && idx == 0 ) || ( has_vec && idx < m_cached_vec_value.size() ) );
            return has_vec ? m_cached_vec_value[idx] : m_cached_bool_value;
        }

        const bool get() const {
            assert( "wrong call, provide an idx if you want to work on arrays!" && !has_vec );
            return m_cached_bool_value;
        }

        void set( const ::locale& l, const variant& value ) {
            has_vec =  value.is_array();
            if ( has_vec ) {
                if ( value.array().size() > 1 ) {
                    m_cached_vec_value = transform_variant_vec_to_bool_vec( l, value );
                } else {
                    assert( "empty array returned by a cf rule!" && !value.array().empty() );
                    m_cached_bool_value = value.array()[0].as_boolean( l );
                    has_vec = false;
                }
            } else {
                m_cached_bool_value = value.as_boolean( l );
            }
        }

    private:
        static inline cached_results_vec transform_variant_vec_to_bool_vec( const ::locale& l, const variant& var ) {
            assert( "only variants of type array may be transformed here!" && var.is_array() );
            const bool default_value = var.array().default_value().is_error() ? false : var.array().default_value().as_boolean( l );
            cached_results_vec return_vec( var.array().size(), default_value );
            foreach( const variant::variant_array_type::mapping_type::value_type & v, var.array().direct() ) {
                if ( !v.second.is_error() ) {
                    return_vec.set( v.first, v.second.as_boolean( l ) );
                } else if ( true == default_value ) {
                    return_vec.set( v.first, false );
                }
            }
            return return_vec;
        }

    private:
        cached_results_vec m_cached_vec_value;
        bool has_vec;
        bool m_cached_bool_value;
    };

    conditional_format_rule::conditional_format_rule( session& s, const std::string& rule, const operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws, const sheet_range& range )
        : m_operands( operands )
        , m_parsing_successful( false )
        , m_ws( ws )
        , m_cached_value( new cached_value() )
    {
        try {
            conditional_format_rule_parser parser( rule, *this );
            m_parsing_successful = parser.parse( s, ws, position );
            if ( m_parsing_successful ) {
                m_formula = conditional_format_formula_writer::create_formula( s, *this, ws, range, position );
                if ( m_formula && m_formula->is_valid() ) {
                    m_parsing_successful = true;
                    if ( m_rule_type == FORMULA_TRUE ) {
                        m_operands.clear();
                    }
                } else {
                    m_parsing_successful = false;
                }
            }
        } catch ( const wss_runtime_exception& ) {
            m_parsing_successful = false;
        }
    }

    conditional_format_rule::conditional_format_rule( session& /* s */, const operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws )
        : m_operands( operands )
        , m_parsing_successful( false )
        , m_ws( ws )
        , m_cached_value( new cached_value() )
    {}

    cf::shared_conditional_format_rule_type conditional_format_rule::create( session& s, const std::string& rule, operand_vec_type& operands, const sheet_point& position, const shared_worksheet_type& ws, const sheet_range& range )
    {
        return boost::make_shared<conditional_format_rule>( boost::ref( s ), rule, operands, position, ws, range );
    }

    std::string conditional_format_rule::to_string( session& s, const bool solve_formulas /* = false */ ) const
    {
        std::ostringstream ostr;
        if ( m_op == none && m_rule_type == CELL_VALUE ) {
            ostr << "no_rule_set_error";
            return ostr.str();
        }
        ostr << m_rulename;
        ostr << '(';
        switch ( m_rule_type ) {
            case CELL_VALUE:
            case AVERAGE_VALUE:

                switch ( m_op ) {
                    case conditional_format_rule::EQ:
                        ostr << "=";
                        break;
                    case conditional_format_rule::NEQ:
                        ostr << "<>";
                        break;
                    case conditional_format_rule::GTE:
                        ostr << ">=";
                        break;
                    case conditional_format_rule::LTE:
                        ostr << "<=";
                        break;
                    case conditional_format_rule::GT:
                        ostr << ">";
                        break;
                    case conditional_format_rule::LT:
                        ostr << "<";
                        break;
                    case conditional_format_rule::BETWEEN:
                        ostr << "between";
                        break;
                    case conditional_format_rule::NBETWEEN:
                        ostr << "not_between";
                        break;
                    case conditional_format_rule::STD_DEV_ABOVE_1:
                        ostr << "std_dev_above_1";
                        break;
                    case conditional_format_rule::STD_DEV_ABOVE_2:
                        ostr << "std_dev_above_2";
                        break;
                    case conditional_format_rule::STD_DEV_ABOVE_3:
                        ostr << "std_dev_above_3";
                        break;
                    case conditional_format_rule::STD_DEV_BELOW_1:
                        ostr << "std_dev_below_1";
                        break;
                    case conditional_format_rule::STD_DEV_BELOW_2:
                        ostr << "std_dev_below_2";
                        break;
                    case conditional_format_rule::STD_DEV_BELOW_3:
                        ostr << "std_dev_below_3";
                        break;

                    default:
                        ostr << "ERROR";
                        break;
                }
                break;

            case TEXT:
                switch ( m_text_op ) {
                    case conditional_format_rule::CONTAINED:
                        ostr << "contained";
                        break;
                    case conditional_format_rule::NOT_CONTAINED:
                        ostr << "not_contained";
                        break;
                    case conditional_format_rule::BEGINS_WITH:
                        ostr << "begins_with";
                        break;
                    case conditional_format_rule::ENDS_WITH:
                        ostr << "ends_with";
                        break;
                    default:
                        ostr << "ERROR";
                        break;
                }
                break;
            case TOP:
            case BOTTOM:
            case TOP_PERCENT:
            case BOTTOM_PERCENT:
                if ( 1 == m_operands.size() ) {
                    const shared_free_formula_type& ff = m_operands[0];
                    if ( ff ) {
                        if ( solve_formulas ) {
                            ostr << ff->value( s, ff->position() ).as_string( ::locale::create( "en" ) );//return variant( ff->formula( s.locale(), position ) );
                        } else {
                            ostr << remove_leading_equal_sign( ff->formula_without_sheet_references( s.locale(), ff->position() ) );// ff->value( s ).as_string( ::locale::create( "en" ) );//return variant( ff->formula( s.locale(), position ) );
                        }
                    }
                }
                //ostr << m_nr_of.as_string( ::locale::create( "en" ) );
                break;
            default:
                break;
        }
        ostr << ";";

        if ( m_stop_if_true ) {
            ostr << "1";
        } else {
            ostr << "0";
        }
        ostr << ";";
        ostr << ")";
        std::string res = ostr.str();
        return res;
    }

    std::vector<std::string> conditional_format_rule::get_operand_as_string_array( session& s, const sheet_point& position ) const
    {
        std::vector<std::string> return_val;
        switch ( m_rule_type ) {

            case CELL_VALUE:
                if ( ! m_operands.empty() ) {
                    if ( m_operands.size() == 1 ) {
                        const shared_free_formula_type& ff = m_operands[0];
                        if ( ff ) {
                            return_val.push_back( ff->formula_without_sheet_references( s.locale(), position ) );
                        }
                    } else {
                        return_val.reserve( m_operands.size() );
                        foreach( const shared_free_formula_type & ff, m_operands ) {
                            if ( ff ) {
                                return_val.push_back( ff->formula_without_sheet_references( s.locale(), position ) );
                            } else {
                                return_val.push_back( "" );
                            }
                        }
                    }
                }
                break;
            case FORMULA_TRUE:
                if ( m_formula ) {
                    return_val.push_back( m_formula->formula_without_sheet_references( s.locale(), position ) );
                }
                break;

            case TEXT:
                if ( ! m_operands.empty() ) {
                    if ( m_operands.size() == 1 ) {
                        const shared_free_formula_type& ff = m_operands[0];
                        if ( ff ) {
                            return_val.push_back( ff->formula_without_sheet_references( s.locale(), position ) );
                        }
                    }
                }
                break;

            case TOP_PERCENT:
            case BOTTOM_PERCENT:
            case TOP:
            case BOTTOM:
                if ( ! m_operands.empty() ) {
                    if ( m_operands.size() == 1 ) {
                        const shared_free_formula_type& ff = m_operands[0];
                        if ( ff ) {
                            const std::string candidate = ff->formula_without_sheet_references( s.locale(), position );
                            try {
                                boost::lexical_cast< unsigned int >( remove_leading_equal_sign( candidate ) );
                            } catch ( std::bad_cast& ) {
                                return_val.push_back( candidate );
                            }
                        }
                    }
                }
                break;
            default:
                if ( ! m_operands.empty() ) {
                    if ( m_operands.size() == 1 ) {
                        const shared_free_formula_type& ff = m_operands[0];
                        if ( ff ) {
                            return_val.push_back( ff->formula_without_sheet_references( s.locale(), position ) );
                        }
                    }
                }
                break;
        }
        return return_val;
    }

    const bool conditional_format_rule::is_dirty( session& s, const sheet_point& position  ) const
    {
        return  m_formula && ( m_formula->is_dirty( s, position )
                               ||
                               ( m_rule_type == conditional_format_rule::CELL_VALUE )
                               ||
                               ( m_rule_type == conditional_format_rule::FORMULA_TRUE ) );
    }

    const bool conditional_format_rule::stop_if_true() const
    {
        return m_stop_if_true;
    }

    const bool conditional_format_rule::does_match( const sheet_point& position, const sheet_range::rectangles_type& ranges ) const
    {
        //first sort the ranges
        typedef std::set<sheet_range> sorted_rectangles_type;
        sorted_rectangles_type sorted_ranges( ranges.begin(), ranges.end() );
        //calculate the position inside the rectangle
        if ( m_cached_value->is_vector() ) {
            size_t idx = 0;
            sorted_rectangles_type::const_iterator it( sorted_ranges.begin() ), end_it( sorted_ranges.end() );
            while ( it != end_it && !it->covers( position ) ) {
                idx += it->count();
                ++it;
            }
            if ( it == end_it ) {
                return false;
            }
            assert( it->covers( position ) );
            const sheet_point upper_left_corner = it->upper_left();
            sheet_point local_position = position.offset( - upper_left_corner.row(), - upper_left_corner.column() );
            idx += local_position.row() * it->column_count() + local_position.column();
            return m_cached_value->get( idx );
        }
        return m_cached_value->get();
    }

    inline variant get_variant_save( session& s, const shared_free_formula_type& formula_, const sheet_point& position )
    {
        try {
            return formula_->value( s, position );
        } catch ( const std::exception& ) {
            return false;
        }
    }

    bool get_bool_save( session& s, const shared_free_formula_type& formula_, const sheet_point& position )
    {
        return formula_->value( s, position ).as_boolean( s.locale() );
    }

    const bool conditional_format_rule::does_match( session& s, const sheet_point& position, const sheet_range::rectangles_type& ranges ) const
    {
        assert( m_formula && "conditional_format_rule not initialized!" );

        switch ( m_rule_type ) {
            case conditional_format_rule::CELL_VALUE:
            case conditional_format_rule::FORMULA_TRUE: {
                return m_formula->value( s, position ).as_boolean( s.locale() );
                //return get_bool_save( s, m_formula, position );
            }
            break;

            default:
                if ( m_formula->is_dirty( s, position ) ) {
                    try {
                        m_cached_value->set( s.locale(), get_variant_save( s, m_formula, position ) );
                    } catch ( const std::exception& ) {
                        return false;
                    }
                }
                return does_match( position, ranges );
        }
    }

    shared_conditional_format_rule_type conditional_format_rule::clone_with_new_range_for_copy( session& s, const sheet_range& range, const sheet_range& old_range, const shared_worksheet_type& target_ws ) const
    {
        shared_worksheet_type ws = target_ws ? target_ws : m_ws.lock();
        if ( ! ws ) {
            throw invalid_worksheet_exception();
        }
        const geometry::point local_distance = old_range.distance( range );
        operand_vec_type new_operands;
        if ( ! m_operands.empty() ) {
            new_operands.reserve( m_operands.size() );
            for ( operand_vec_type::const_iterator it = m_operands.begin(), end_it = m_operands.end(); it != end_it; ++it ) {
                shared_free_formula_type new_op( free_formula::create( *it, local_distance, false, false, old_range, range.upper_left(), target_ws ) );
                new_operands.push_back( new_op );
            }
        }
        shared_conditional_format_rule_type clone_rule( boost::make_shared<conditional_format_rule>( boost::ref( s ), new_operands, range.upper_left(), ws ) );
        clone_rule->m_rule_type = m_rule_type;
        clone_rule->m_op = m_op;
        clone_rule->m_text_op = m_text_op;
        clone_rule->m_nr_of = m_nr_of;
        clone_rule->m_stop_if_true = m_stop_if_true;
        clone_rule->m_rulename = m_rulename;
        //clone_rule->m_formula = conditional_format_formula_writer::create_formula( s, *this, ws, range, range.upper_left() );
        clone_rule->m_formula = free_formula::create( m_formula, local_distance, false, false, old_range, range.upper_left(), target_ws ); // conditional_format_formula_writer::create_formula_for_move( s, *this, ws, range, range.upper_left(), range.upper_left() );
        clone_rule->m_parsing_successful = ( clone_rule->m_formula && clone_rule->m_formula->is_valid() );
        return clone_rule;
    }

    shared_conditional_format_rule_type conditional_format_rule::clone_with_new_range_for_move( session& s, const sheet_range& range, const sheet_range& old_range, const shared_worksheet_type& target_ws ) const
    {
        shared_worksheet_type ws = target_ws ? target_ws : m_ws.lock();
        if ( ! ws ) {
            throw invalid_worksheet_exception();
        }
        const bool target_is_clone_sheet = target_ws ? target_ws->hidden() : false;
        const geometry::point local_distance = old_range.distance( range );
        operand_vec_type new_operands;
        if ( ! m_operands.empty() ) {
            new_operands.reserve( m_operands.size() );
            for ( operand_vec_type::const_iterator it = m_operands.begin(), end_it = m_operands.end(); it != end_it; ++it ) {
                shared_free_formula_type new_op( free_formula::create( *it, local_distance, target_is_clone_sheet, false, old_range, range.upper_left(), target_ws  ) );
                new_operands.push_back( new_op );
            }
        }


        shared_conditional_format_rule_type clone_rule( boost::make_shared<conditional_format_rule>( boost::ref( s ), new_operands, old_range.upper_left(), ws ) );
        clone_rule->m_rule_type = m_rule_type;
        clone_rule->m_op = m_op;
        clone_rule->m_text_op = m_text_op;
        clone_rule->m_nr_of = m_nr_of;
        clone_rule->m_stop_if_true = m_stop_if_true;
        clone_rule->m_rulename = m_rulename;
        // clone_rule->m_formula = conditional_format_formula_writer::create_formula_for_move( s, *this, ws, range, old_range.upper_left(), range.upper_left() );
        clone_rule->m_formula = free_formula::create( m_formula, local_distance, target_is_clone_sheet, false, old_range, range.upper_left(), target_ws ); // conditional_format_formula_writer::create_formula_for_move( s, *this, ws, range, range.upper_left(), range.upper_left() );
        clone_rule->m_parsing_successful = ( clone_rule->m_formula && clone_rule->m_formula->is_valid() );
        return clone_rule;
    }

    shared_conditional_format_rule_type conditional_format_rule::clone_with_new_range_for_copy_move( session& s, const sheet_range& range, const sheet_range& old_range, const sheet_range& source_range, const geometry::point& distance ) const
    {
        shared_worksheet_type ws = m_ws.lock();
        if ( ! ws ) {
            throw invalid_worksheet_exception();
        }
        const geometry::point local_distance = old_range.distance( range );
        operand_vec_type new_operands;
        if ( ! m_operands.empty() ) {
            new_operands.reserve( m_operands.size() );
            for ( operand_vec_type::const_iterator it = m_operands.begin(), end_it = m_operands.end(); it != end_it; ++it ) {
                shared_free_formula_type new_op( free_formula::create( *it, local_distance, false, true, source_range, range.upper_left(), ws ) );
                new_operands.push_back( new_op );
            }
        }
        shared_conditional_format_rule_type clone_rule( boost::make_shared<conditional_format_rule>( boost::ref( s ), new_operands, range.upper_left(), ws ) );
        clone_rule->m_rule_type = m_rule_type;
        clone_rule->m_op = m_op;
        clone_rule->m_text_op = m_text_op;
        clone_rule->m_nr_of = m_nr_of;
        clone_rule->m_stop_if_true = m_stop_if_true;
        clone_rule->m_rulename = m_rulename;
        clone_rule->m_formula = free_formula::create( m_formula, local_distance, false, true, source_range, range.upper_left(), ws );// conditional_format_formula_writer::create_formula_for_move( s, *this, ws, range, range.upper_left(), range.upper_left() );
        clone_rule->m_parsing_successful = ( clone_rule->m_formula && clone_rule->m_formula->is_valid() );
        return clone_rule;
    }


    weak_worksheet_type conditional_format_rule::worksheet()
    {
        return m_ws;
    }
}
