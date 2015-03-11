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

#include "precompiled_header.hpp"
#include "wss/formula_parser.hpp"
#include "wss/application.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
// these defines have to be duplicated in the precompiled
// header file.
# ifdef _DEBUG
#  define BOOST_SPIRIT_DEBUG
# endif
# define BOOST_SPIRIT_THREADSAFE
# define PHOENIX_LIMIT 8
# define BOOST_SPIRIT_CLOSURE_LIMIT 8
# define BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT 2
# include <boost/spirit.hpp>

# include <boost/pool/singleton_pool.hpp>
# include <boost/spirit/phoenix.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/bind.hpp>

# include <stack>
#endif // HAS_PRECOMPILED_HEADER == 0

#include "wss/non_instantiable.hpp"
#include "wss/rectangle.hpp"
#include "wss/reference.hpp"
#include "wss/a1conversion.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "wss/type.hpp"
#include "wss/sheet_dimension.hpp"
#include "wss/allocation.hpp"
#include "wss/syntax.hpp"
#include "wss/formula_parsing_context.hpp"
#include "wss/translation_table.hpp"
#include "object_lookup.hpp"
#include "wss/invalid_translation_table_exception.hpp"

#if defined( WIN32 )
#   pragma inline_depth(255)
#   pragma inline_recursion(on)
# pragma warning ( push )
# pragma warning ( disable : 4503 ) // decorated name truncation warning
#endif // WIN32
namespace bs = boost::spirit::classic;

/*!
 * \brief
 * formula parsing result.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class changeable_formula_parsing_result
    : public formula_parsing_result
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    changeable_formula_parsing_result()
        : formula_parsing_result() {}

    /*!
     * \brief
     * the formula is volatile.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void flag_volatile() {
        m_has_volatile = true;
    }

    /*!
     * \brief
     * flips the view independent flag.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void flag_view_independent() {
        m_has_view_independent = true;
    }

    /*!
     * \brief
     * flips the view independent flag.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void flag_executes_on_set() {
        m_execute_on_set = true;
    }

    /*!
     * \brief
     * parsing of the formula did succeed.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void flag_success() {
        m_is_success = true;
    }

    /*!
     * \brief
     * return the list of identified variables in the formula.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variable_map& variable() {
        return m_variable;
    }

    /*!
     * \brief
     * return the AST root node.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    base_node* root() {
        return m_root.get();
    }
};

/*!
 * \brief
 * formula parser
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class formula_parser::parser
{
private:
    /*!
     * \brief
     * AST tree
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct tree
            : non_instantiable {

        /*!
         * \brief
         * helper class to generate the AST.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        class tree_builder
            : boost::noncopyable
        {
        public:
            typedef base_node::auto_type auto_type;

            tree_builder( base_node& node )
                : m_root_node( node ) {}

            void start_parent() {
                m_tree_state.enter();
            }

            void finalize_parent( auto_type node ) {
                if ( *m_tree_state ) {
                    append_parent( node, *m_tree_state );
                } else {
                    m_root_node.attach( node );
                }
                m_tree_state.leave();
                ++m_tree_state;

                const base_node::shallow_iterator first_child = m_root_node.begin_shallow();

                if ( m_root_node.end_shallow() != first_child ) {
                    if ( !first_child->validate () ) {
                        throw std::logic_error( "Array rows have different size." );
                    }
                }
            }

            void remove_first() {
                if ( *m_tree_state > 0 ) {
                    --m_tree_state;
                    m_root_node.remove_first();
                }
            }

            void remove_last() {
                if ( *m_tree_state > 0 ) {
                    --m_tree_state;
                    m_root_node.remove_last();
                }
            }

            void append( auto_type node ) {
                m_root_node.attach( node );
                ++m_tree_state;
            }

            void append_parent( auto_type node, unsigned int collect_child_nodes = 2 ) {
                assert( "parser problem! trying to collect more child-nodes to form a parent node then there are leaves on the tree!"
                        && m_root_node.size() >= collect_child_nodes );

                m_tree_state -= ( collect_child_nodes - 1 );
                while ( collect_child_nodes-- ) {
                    node->attach_front( ( --m_root_node.end_shallow() )->release().release()  );
                }
                m_root_node.attach( node );
            }

        private:
            /*!
             * \brief
             * node tracking
             *
             * \author
             * Florian Schaper <florian.schaper@jedox.com>
             */
            class tree_state
                : boost::noncopyable
            {
                typedef std::stack<unsigned int> container_type;
            public:
                tree_state()
                    : m_current_child_count( 0 ) {}

                unsigned int operator ++() {
                    return ++m_current_child_count;
                }

                unsigned int operator --() {
                    return --m_current_child_count;
                }

                tree_state operator -( unsigned int value ) {
                    tree_state tmp( *this );
                    tmp.m_current_child_count -= value;
                    return tmp;
                }

                tree_state& operator -=( unsigned int value ) {
                    m_current_child_count -= value;
                    return *this;
                }

                unsigned int operator *() {
                    return m_current_child_count;
                }

                void enter() {
                    m_state_stack.push( m_current_child_count );
                    m_current_child_count = 0;
                }

                unsigned int leave() {
                    unsigned int tmp = m_current_child_count;
                    m_current_child_count = static_cast<unsigned int>( m_state_stack.top() );
                    m_state_stack.pop();
                    return tmp;
                }

            private:
                tree_state( const tree_state& );

                container_type m_state_stack;
                unsigned int m_current_child_count;
            } m_tree_state;

        private:
            base_node& m_root_node;
        };

        template
        <
        class node_T
        , typename parameter_type = void
        >
        class add_child;

        /*!
         * \brief
         * add an regular child/leaf node without parameter.
         *
         * boolean_false node f.ex.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template
        <
        class node_T
        >
        class add_child<node_T, void>
        {
        public:
            add_child( parser& p )
                : m_tb( p.m_builder ) {}

            template<typename iterator_base_T>
            void operator()( iterator_base_T /*p*/ ) const {
                m_tb.append( node_T::create() );
            }

            template <typename IteratorT>
            void operator()( IteratorT /*begin*/, IteratorT /*end*/ ) const {
                m_tb.append( node_T::create() );
            }

        private:
            add_child& operator =( const add_child& );

            tree_builder& m_tb;
        };

        /*!
         * \brief
         * add an regular child/leaf node with an parameter.
         *
         * will be used f.ex. for double_nodes.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template
        <
        class node_T
        , typename parameter_type
        >
        class add_child
        {
        public:
            add_child( parser& p )
                : m_tb( p.m_builder ) {}

            template<typename iterator_base_T>
            void operator()( iterator_base_T p ) const {
                m_tb.append( node_T::create( parameter_type( p ) ) );
            }

            template <typename IteratorT>
            void operator()( IteratorT begin, IteratorT end ) const {
                m_tb.append( node_T::create( parameter_type( begin, end ) ) );
            }

        private:
            add_child& operator =( const add_child& );

            tree_builder& m_tb;
        };

        /*!
         * \brief
         * add a parent node with a known number of child nodes.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template
        <
        class node_T
        , unsigned int parameter_count = 2
        >
        class add_parent
        {
        public:
            add_parent( parser& p )
                : m_tb( p.m_builder ) {}

            template<typename iterator_base_T>
            void operator()( iterator_base_T /*p*/ ) const {
                m_tb.append_parent( node_T::create(), parameter_count );
            }

            template <typename IteratorT>
            void operator()( IteratorT /*begin*/, IteratorT /*end*/ ) const {
                m_tb.append_parent( node_T::create(), parameter_count );
            }

        private:
            add_parent& operator =( const add_parent& );

            tree_builder& m_tb;
        };

        /*!
         * \brief
         * start collecting child nodes. the nodes will be appended
         * to an parent node that will be added with finalize_parent.
         *
         * used when the number of child nodes can not be known beforehand.
         * as for function parameters or braces.
         *
         * \see
         * finalize_parent
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        class start_parent
        {
        public:
            start_parent( parser& p )
                : m_tb( p.m_builder ) {}

            template<typename iterator_base_T>
            void operator()( iterator_base_T /*p*/ ) const {
                m_tb.start_parent();
            }

            template <typename IteratorT>
            void operator()( IteratorT /*begin*/, IteratorT /*end*/ ) const {
                m_tb.start_parent();
            }

        private:
            start_parent& operator =( const start_parent& );

            tree_builder& m_tb;
        };

        /*!
         * \brief
         * used in conjunction with start_parent will add the collected
         * number of child nodes to the specified parent node.
         *
         * \see
         * start_parent
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template
        <
        class node_T
        >
        class finalize_parent
        {
        public:
            finalize_parent( parser& p )
                : m_tb( p.m_builder ) {}

            template<typename iterator_base_T>
            void operator()( iterator_base_T /*p*/ ) const {
                m_tb.finalize_parent( node_T::create() );
            }

            template <typename IteratorT>
            void operator()( IteratorT /*begin*/, IteratorT /*end*/ ) const {
                m_tb.finalize_parent( node_T::create() );
            }
        private:
            finalize_parent& operator =( const finalize_parent& );

            tree_builder& m_tb;
        };

        /*!
         * \brief
         * add column or row range (Format: 1:10 or A:B)
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct add_row_or_column_range {
            add_row_or_column_range( parser& p )
                : m_p( p ) {}

            template<class P1, class P2, class P3, class P4, class P5, class P6>
            struct result {
                typedef void type;
            };

            void operator()( const std::string& workbook_name, const std::string& worksheet_name, unsigned int row_lhs, unsigned int flags_lhs, unsigned int row_rhs, unsigned int flags_rhs ) {
                const sheet_point lhs_bp( ( row_lhs - 1 ), 0, static_cast<reference::type>( flags_lhs ) );
                const sheet_point rhs_bp( ( row_rhs - 1 ), sheet_dimension::max_column, static_cast<reference::type>( flags_rhs ) );

                weak_worksheet_type weak_target_worksheet( m_p.m_context.worksheet() );
                if ( !worksheet_name.empty() ) {
                    try {
                        if ( !workbook_name.empty() ) {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( workbook_name ), convert_utf8_ci( worksheet_name ) );
                        } else {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( worksheet_name ) );
                        }
                    } catch ( const object_not_found_exception& ) {
                        weak_target_worksheet.reset();
                    }
                }

                m_p.m_builder.append( range_node::create( weak_target_worksheet, sheet_range( lhs_bp, rhs_bp ), false, false, workbook_name, worksheet_name ) );
            }

            void operator()( const std::string& workbook_name, const std::string& worksheet_name, const std::string& column_lhs, unsigned int flags_lhs, const std::string& column_rhs, unsigned int flags_rhs ) {
                const sheet_point lhs_bp( 0, a1conversion::from_a1::column( column_lhs ), static_cast<reference::type>( flags_lhs ) );
                const sheet_point rhs_bp( sheet_dimension::max_row, a1conversion::from_a1::column( column_rhs ), static_cast<reference::type>( flags_rhs ) );

                weak_worksheet_type weak_target_worksheet( m_p.m_context.worksheet() );
                if ( !worksheet_name.empty() ) {
                    try {
                        if ( !workbook_name.empty() ) {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( workbook_name ), convert_utf8_ci( worksheet_name ) );
                        } else {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( worksheet_name ) );
                        }
                    } catch ( const object_not_found_exception& ) {
                        weak_target_worksheet.reset();
                    }
                }

                m_p.m_builder.append( range_node::create( weak_target_worksheet, sheet_range( lhs_bp, rhs_bp ), false, false, workbook_name, worksheet_name ) );
            }

            add_row_or_column_range& operator =( const add_row_or_column_range& );

            parser& m_p;
        };

        /*!
         * \brief
         * add range node (Format: A1:C10).
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct add_regular_range {
            add_regular_range( parser& p )
                : m_p( p ) {}

            template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
            struct result {
                typedef void type;
            };

            void operator()( const std::string& workbook_name, const std::string& worksheet_name, unsigned int row_lhs, const std::string& column_lhs, unsigned int flags_lhs, unsigned int row_rhs, const std::string& column_rhs, unsigned int flags_rhs, bool is_single_cell ) {
                const sheet_point lhs_bp( ( row_lhs - 1 ), a1conversion::from_a1::column( column_lhs ), static_cast<reference::type>( flags_lhs ) );
                const sheet_point rhs_bp( ( row_rhs - 1 ), a1conversion::from_a1::column( column_rhs ), static_cast<reference::type>( flags_rhs ) );

                weak_worksheet_type weak_target_worksheet( m_p.m_context.worksheet() );
                if ( !worksheet_name.empty() ) {
                    try {
                        if ( !workbook_name.empty() ) {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( workbook_name ), convert_utf8_ci( worksheet_name ) );
                        } else {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( worksheet_name ) );
                        }
                    } catch ( const object_not_found_exception& ) {
                        weak_target_worksheet.reset();
                    }
                }

                m_p.m_builder.append( range_node::create( weak_target_worksheet, sheet_range( lhs_bp, rhs_bp ), is_single_cell, false, workbook_name, worksheet_name ) );
            }

            add_regular_range& operator =( const add_regular_range& );

            parser& m_p;
        };

        /*!
         * \brief
         * add range node (Format: A1:C10).
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct add_error_cell {
            add_error_cell( parser& p )
                : m_p( p ) {}

            template<class P1, class P2>
            struct result {
                typedef void type;
            };

            void operator()( const std::string& workbook_name, const std::string& worksheet_name ) {

                weak_worksheet_type weak_target_worksheet( m_p.m_context.worksheet() );
                if ( !worksheet_name.empty() ) {
                    try {
                        if ( !workbook_name.empty() ) {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( workbook_name ), convert_utf8_ci( worksheet_name ) );
                        } else {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( worksheet_name ) );
                        }
                    } catch ( const object_not_found_exception& ) {
                        weak_target_worksheet.reset();
                    }
                }

                m_p.m_builder.append( range_node::create( weak_target_worksheet, sheet_range( sheet_point( 0, 0 ) ), true, true, workbook_name, worksheet_name ) );
            }

            add_error_cell& operator =( const add_error_cell& );

            parser& m_p;
        };

        /*!
         * \brief
         * add function node.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct add_function {
            add_function( parser& p )
                : m_p( p ) {}

            template<class P1>
            struct result {
                typedef void type;
            };

            void operator()( const std::string& function_name ) {
                std::string mapping( function_name );

                try {
                    const translation_map::function_translation_entry* translation_entry = translation_table::instance()[ m_p.m_context.locale() ]->internal_name_lookup[ convert_utf8_ci( function_name ) ];
                    if ( NULL != translation_entry ) {
                        mapping = translation_entry->identifier;
                    }
                } catch ( const invalid_translation_table_exception& ) {
                } catch ( const translation_exception& ) {}


                function_node::auto_type node( function_node::create( mapping ) );

                function_node* crt = static_cast<function_node*>( node.get() );

                if ( crt->is_volatile() ) {
                    m_p.result().flag_volatile();
                }
                if ( crt->is_view_independent() ) {
                    m_p.result().flag_view_independent();
                }
                if ( crt->executes_on_set() ) {
                    m_p.result().flag_executes_on_set();
                }
                m_p.m_builder.finalize_parent( node );

            }

            add_function& operator =( const add_function& );

            parser& m_p;
        };


        /*!
         * \brief
         * add variable node.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct add_variable {
            add_variable( parser& p )
                : m_p( p ) {}

            template
            <
            typename iterator_T
            >
            void operator()( iterator_T begin, iterator_T end ) const {
                const std::string var_name( begin, end );
                variable_node::auto_type node( variable_node::create( var_name ) );
                m_p.result().variable().add( var_name );
                m_p.result().flag_volatile();
                m_p.m_builder.append( node );
            }

            add_variable& operator =( const add_variable& );

            parser& m_p;
        };

        /*!
         * \brief
         * named formula node creation.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        struct add_named_formula {
            add_named_formula( parser& p )
                : m_p( p ) {}

            template<class P1, class P2, class P3>
            struct result {
                typedef void type;
            };

            void operator()( const std::string& workbook_name, const std::string& worksheet_name, const std::string& name ) {
                weak_worksheet_type weak_target_worksheet( m_p.m_context.worksheet() );
                if ( !worksheet_name.empty() ) {
                    try {
                        if ( !workbook_name.empty() ) {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( workbook_name ), convert_utf8_ci( worksheet_name ) );
                        } else {
                            weak_target_worksheet = object_lookup::worksheet( m_p.context().session(), m_p.m_context.worksheet().lock(), convert_utf8_ci( worksheet_name ) );
                        }
                    } catch ( const object_not_found_exception& ) {
                        weak_target_worksheet.reset();
                        if ( workbook_name.empty() ) {
                            //this should match a formula given as [workbook]name.
                            session& s = m_p.m_context.session();
                            shared_workbook_type swb;
                            try {
                                weak_workbook_type wb = s.selected().application()->get( s, convert_utf8_ci( worksheet_name ) );
                                swb = wb.lock();
                            } catch ( const object_not_found_exception& ) {}
                            if ( swb ) {
                                weak_target_worksheet = *( swb->locking_iterator().begin() );
                                shared_worksheet_type sws = weak_target_worksheet.lock();
                                if ( sws ) {
                                    m_p.m_builder.append(
                                        named_formula_node::create( named_formula_scope::workbook_scope, weak_target_worksheet, worksheet_name, sws->name().c_str(), name )
                                    );
                                    return;
                                }
                            }
                        }
                    }
                }

                named_formula_scope::type scope = worksheet_name.size() ? named_formula_scope::worksheet_scope : ( workbook_name.size() ? named_formula_scope::workbook_scope : named_formula_scope::none );

                m_p.m_builder.append( named_formula_node::create( scope, weak_target_worksheet, workbook_name, worksheet_name, name ) );
            }

            add_named_formula& operator =( const add_named_formula& );

            parser& m_p;
        };
    };

    /*!
     * \brief
     * excel grammar
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct formula_grammar
            : bs::grammar<formula_grammar> {

        formula_grammar( formula_parser::parser& p )
            : bs::grammar<formula_grammar>()
            , m_p( p ) {}

        /*!
         * \brief
         * cell parsing context.
         *
         * TODO replace with the cell_range_parser_context.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct cell_parser_context :
                bs::closure
                <
                cell_parser_context
                , unsigned int
                , unsigned int
                , std::string
                , std::string
                , std::string
                > {
            member1 flag;
            member2 row;
            member3 column;
            member4 workbook;
            member5 worksheet;
        };

        /*!
         * \brief
         * cell range parsing context.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct cell_range_parser_context :
                bs::closure
                <
                cell_range_parser_context
                , unsigned int
                , unsigned int
                , unsigned int
                , unsigned int
                , std::string
                , std::string
                , std::string
                , std::string
                > {
            member1 flag_lhs;
            member2 flag_rhs;
            member3 row_lhs;
            member4 row_rhs;
            member5 column_lhs;
            member6 column_rhs;
            member7 workbook;
            member8 worksheet;
        };

        /*!
         * \brief
         * cell ref error parsing context.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        struct cell_ref_error_parser_context :
                bs::closure
                <
                cell_range_parser_context
                , std::string
                , std::string
                > {
            member1 workbook;
            member2 worksheet;
        };

        /*!
         * \brief
         * named formula parsing context.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        struct named_formula_parser_context
                : bs::closure
                <
                named_formula_parser_context
                , std::string
                , std::string
                > {
            member1 workbook;
            member2 worksheet;
        };

        /*!
         * \brief
         * used when parsing extension functions.
         *
         * stores the name of the extension function.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct formula_parser_context :
                bs::closure
                <
                formula_parser_context
                , std::string
                > {
            member1 name;
        };

        /*!
         * \brief
         * parse locale specific booleans (TRUE, FALSE, WAHR, FALSCH, ...)
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<bool bool_to_get>
        struct locale_dependent_boolean_p
                : public bs::parser<locale_dependent_boolean_p<bool_to_get> > {
            locale_dependent_boolean_p( const formula_parser::parser& p )
                : m_mapping( boost::to_lower_copy( bool_to_get ? p.context().active_translation().boolean_true() : p.context().active_translation().boolean_false() ) ) {}

            typedef locale_dependent_boolean_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                return bs::as_lower_d[bs::chseq<char const*>( m_mapping.c_str(), m_mapping.c_str() + m_mapping.length() )].parse( scan );
            }

            locale_dependent_boolean_p& operator =( const locale_dependent_boolean_p& );
            const std::string m_mapping;
        };

        /*!
         * \brief
         * parse locale specific error values.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct locale_dependent_error_p
                : public bs::parser<locale_dependent_error_p> {
            locale_dependent_error_p( const formula_parser::parser& p )
                : m_p( p ) {}

            typedef locale_dependent_error_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                const translation_map::error_mapping::type& mapping = m_p.context().active_translation().error_translation();
                typedef typename ScannerT::iterator_t iterator_type;
                iterator_type save_it = scan.first;
                foreach( const translation_map::error_mapping::entity_type & entity, mapping.get<translation_map::error_mapping::string_tag>() ) {
                    // skips the '#' char that has been already matched by the parser.
                    typename bs::parser_result<self_t, ScannerT>::type match = bs::as_lower_d[bs::chseq<char const*>( entity.second.c_str() + 1, entity.second.c_str() + entity.second.length() )].parse( scan );
                    if ( match != scan.no_match() ) {
                        return match;
                    } else {
                        scan.first = save_it;
                    }
                }
                return scan.no_match();
            }

            locale_dependent_error_p& operator =( const locale_dependent_error_p& );
            const formula_parser::parser& m_p;
        };

        /*!
         * \brief
         * parse locale specific ref error values.
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        struct locale_dependent_ref_error_p
                : public bs::parser<locale_dependent_ref_error_p> {
            locale_dependent_ref_error_p( const formula_parser::parser& p )
                : m_p( p ) {}

            typedef locale_dependent_ref_error_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                typedef typename ScannerT::iterator_t iterator_type;
                const std::string& ref_error = m_p.context().active_translation().error_translation().get<translation_map::error_mapping::code_tag>().find( variant::error_ref )->second;
                // skips the '#' char that has been already matched by the parser.
                typename bs::parser_result<self_t, ScannerT>::type match = bs::as_lower_d[bs::chseq<char const*>( ref_error.c_str() + 1, ref_error.c_str() + ref_error.length() )].parse( scan );
                if ( match != scan.no_match() ) {
                    return match;
                }
                return scan.no_match();
            }

            locale_dependent_ref_error_p& operator =( const locale_dependent_ref_error_p& );
            const formula_parser::parser& m_p;
        };

        /*!
         * \brief
         * policy class for language_dependent_numeric_parser_p
         *
         * \see
         * language_dependent_numeric_parser_p
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template <typename T, char separator_T>
        struct localized_real_parser_policy
                : public bs::real_parser_policies<T> {
            template <typename ScannerT>
            static typename bs::parser_result<bs::chlit<>, ScannerT>::type
            parse_dot( ScannerT& scan ) {
                return bs::ch_p( separator_T ).parse( scan );
            }
        };

        /*!
         * \brief
         * parse locale dependent real numbers.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct language_dependent_numeric_parser_p
                : public bs::parser<language_dependent_numeric_parser_p> {
            language_dependent_numeric_parser_p( const formula_parser::parser& p )
                : m_use_dot( p.context().active_translation().use_dot_as_real_separator() ) {}

            typedef language_dependent_numeric_parser_p self_t;

            template <typename ScannerT>
            struct result {
                typedef typename bs::match_result<ScannerT, double>::type type;
            };

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                if ( m_use_dot ) {
                    return bs::real_p.parse( scan );
                } else {
                    return bs::real_parser < double, localized_real_parser_policy < double, ',' > > ().parse( scan );
                }
            }

            language_dependent_numeric_parser_p& operator =( const language_dependent_numeric_parser_p& );
            bool m_use_dot;
        };

        /*!
         * \brief
         * locale dependent parameter separator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct locale_dependent_parameter_separator_p
                : public bs::parser<locale_dependent_parameter_separator_p> {
            locale_dependent_parameter_separator_p( const formula_parser::parser& p )
                : m_mapping( p.context().active_translation().parameter_separator() ) {}

            typedef locale_dependent_parameter_separator_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                return bs::chseq<char const*>( m_mapping.c_str(), m_mapping.c_str() + m_mapping.length() ).parse( scan );
            }

            locale_dependent_parameter_separator_p& operator =( const locale_dependent_parameter_separator_p& );
            const std::string& m_mapping;
        };

        /*!
         * \brief
         * locale dependent column separator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct locale_dependent_column_separator_p
                : public bs::parser<locale_dependent_column_separator_p> {
            locale_dependent_column_separator_p( const formula_parser::parser& p )
                : m_mapping( p.context().active_translation().column_separator() ) {}

            typedef locale_dependent_column_separator_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                return bs::chseq<char const*>( m_mapping.c_str(), m_mapping.c_str() + m_mapping.length() ).parse( scan );
            }

            locale_dependent_column_separator_p& operator =( const locale_dependent_column_separator_p& );
            const std::string& m_mapping;
        };

        /*!
         * \brief
         * locale dependent row separator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        struct locale_dependent_row_separator_p
                : public bs::parser<locale_dependent_row_separator_p> {
            locale_dependent_row_separator_p( const formula_parser::parser& p )
                : m_mapping( p.context().active_translation().row_separator() ) {}

            typedef locale_dependent_row_separator_p self_t;

            template <typename ScannerT>
            typename bs::parser_result<self_t, ScannerT>::type
            parse( ScannerT const& scan ) const {
                return bs::chseq<char const*>( m_mapping.c_str(), m_mapping.c_str() + m_mapping.length() ).parse( scan );
            }

            locale_dependent_row_separator_p& operator =( const locale_dependent_row_separator_p& );
            const std::string& m_mapping;
        };

        /*!
         * \brief
         * excel formula grammar.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<typename ScannerT>
        struct definition {
            definition( formula_grammar const& self ) {
                using namespace bs;
                using namespace phoenix;

                //ASTYLE_IGNORE
                // a cell matches
                // single cell with and without absolute flag for row and column
                //   f.ex. a1, a$1, $a1, $a$1
                // sheet + cell reference with whitespace characters or 'special' characters and without
                //  worksheet!a1
                //  'some worksheet'!a1 - needs be escaped since contains whitespace
                // worksheet + sheet + cell reference
                //  [workbook_1]sheet1!a1
                //  '[workbook_1]sheet 1'!a1 - whole subpart needs be enclosed in '' since "sheet 1" contains whitespace or special characters
                //  '[workbook 1]sheet1'!a1 - whole subpart needs be enclosed in '' since "workbook 1" contains whitespace or special characters

                generic_name = ( ( + ( ~range_p( '0', '9' ) & ~ch_p( '(' ) & ~ch_p( '#' ) & ~ch_p( '{' ) & ~ch_p( '}' ) & ~ch_p( ')' ) & ~ch_p( ':' ) & ~ch_p( '!' ) & ~ch_p( '@' ) & ~ch_p( '<' ) & ~ch_p( '>' ) & ~ch_p( '[' ) & ~ch_p( ']' ) & ~ch_p( '*' ) & ~ch_p( '/' ) & ~ch_p( '^' ) & ~ch_p( '%' ) & ~ch_p( '=' ) & ~ch_p( '&' ) & ~ch_p( '+' ) & ~ch_p( ' ' ) & ~ch_p( '-' ) & ~ch_p( ';' ) & ~ch_p( ',' ) & ~ch_p( '\'' ) & ~ch_p( '"' ) & ~ch_p( '$' ) ) )
                                 >>
                                 ( *( ~ch_p( '(' ) & ~ch_p( '#' ) & ~ch_p( '{' ) & ~ch_p( '}' ) & ~ch_p( ')' ) & ~ch_p( ':' ) & ~ch_p( '!' ) & ~ch_p( '@' ) & ~ch_p( '<' ) & ~ch_p( '>' ) & ~ch_p( '[' ) & ~ch_p( ']' ) & ~ch_p( '*' ) & ~ch_p( '/' ) & ~ch_p( '^' ) & ~ch_p( '%' ) & ~ch_p( '=' ) & ~ch_p( '&' ) & ~ch_p( '+' ) & ~ch_p( ' ' ) & ~ch_p( '-' ) & ~ch_p( ';' ) & ~ch_p( ',' ) & ~ch_p( '\'' ) & ~ch_p( '"' ) & ~ch_p( '$' ) ) ) );

                workbook_name  = generic_name;
                worksheet_name = generic_name;

                cell           =   (
                                       reference =
                                           !(
                                               (
                                                   // [workbook_1]sheet1 or sheet1
                                                   (
                                                       !(
                                                           ch_p( '[' )
                                                           >> workbook_name[ cell.workbook = construct_<std::string>( arg1, arg2 ) ]
                                                           >> ch_p( ']' )
                                                       )
                                                       >> eps_p( worksheet_name >> ch_p( '!' ) ) >> worksheet_name[ cell.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                                   )
                                                   |
                                                   // '[workbook 1]sheet 1' or 'sheet 1'
                                                   (
                                                       ch_p( '\'' )
                                                       >> !(
                                                           ch_p( '[' )
                                                           >> ( + ( ~ch_p( ']' ) ) )[ cell.workbook = construct_<std::string>( arg1, arg2 ) ]
                                                           >> ch_p( ']' )
                                                       )
                                                       >> ( + ( ~ch_p( '\'' ) ) )[ cell.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                                       >> ch_p( '\'' )
                                                   )
                                               )
                                               >> ch_p( '!' )
                                           )
                                           >> !ch_p( '$' )[ cell.flag = reference::absolute_column ]
                                           >> column[ cell.column = construct_<std::string>( arg1, arg2 ) ]
                                           >> !ch_p( '$' )[ cell.flag |= reference::absolute_row ]
                                           >> limit_d( 1u, sheet_dimension::max_row + 1 )[ uint_p ][ cell.row = arg1 ][ function<tree::add_regular_range>( tree::add_regular_range( self.m_p ) )( cell.workbook, cell.worksheet, cell.row, cell.column, cell.flag, cell.row, cell.column, cell.flag, true ) ]
                                           >> ~eps_p( as_lower_d[range_p( 'a', 'z' )] )
                                           //A-Z, AA-ZZ, AAA-XFD
                                           //                                           , column = ( as_lower_d[( range_p( 'a', 'x' ) >> range_p( 'a', 'f' )  >> range_p( 'a', 'd' ) ) | ( range_p( 'a', 'z' ) >> range_p( 'a', 'z' ) ) | range_p( 'a', 'z' )] )
                                           //A_Z, AA-IV
                                           , column = ( as_lower_d[( range_p( 'a', 'h' ) >> range_p( 'a', 'z' ) ) | ( ch_p( 'i' ) >> range_p( 'a', 'v' ) ) | range_p( 'a', 'z' )] )
                                   );

                cell_ref_error =
                    (
                        reference =
                            !(
                                (
                                    // [workbook_1]sheet1 or sheet1
                                    (
                                        !(
                                            ch_p( '[' )
                                            >> workbook_name[ cell_ref_error.workbook = construct_<std::string>( arg1, arg2 ) ]
                                            >> ch_p( ']' )
                                        )
                                        >> eps_p( worksheet_name >> ch_p( '!' ) ) >> worksheet_name[ cell_ref_error.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                    )
                                    |
                                    // '[workbook 1]sheet 1' or 'sheet 1'
                                    (
                                        ch_p( '\'' )
                                        >> !(
                                            ch_p( '[' )
                                            >> ( + ( ~ch_p( ']' ) ) )[ cell_ref_error.workbook = construct_<std::string>( arg1, arg2 ) ]
                                            >> ch_p( ']' )
                                        )
                                        >> ( + ( ~ch_p( '\'' ) ) )[ cell_ref_error.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                        >> ch_p( '\'' )
                                    )
                                )
                                >> ch_p( '!' )
                            ) >> ch_p( '#' ) >> locale_dependent_ref_error_p( self.m_p )[ function<tree::add_error_cell>( tree::add_error_cell( self.m_p ) )( cell_ref_error.workbook, cell_ref_error.worksheet ) ]
                    );

                cell_range     =   (
                                       reference =
                                           !(
                                               (
                                                   // [workbook_1]sheet1 or sheet1
                                                   (
                                                       !(
                                                           ch_p( '[' )
                                                           >> workbook_name[ cell_range.workbook = construct_<std::string>( arg1, arg2 ) ]
                                                           >> ch_p( ']' )
                                                       )
                                                       >> eps_p( worksheet_name >> ch_p( '!' ) ) >> worksheet_name[ cell_range.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                                   )
                                                   |
                                                   // '[workbook 1]sheet 1' or 'sheet 1'
                                                   (
                                                       ch_p( '\'' )
                                                       >> !(
                                                           ch_p( '[' )
                                                           >> ( + ( ~ch_p( ']' ) ) )[ cell_range.workbook = construct_<std::string>( arg1, arg2 ) ]
                                                           >> ch_p( ']' )
                                                       )
                                                       >> ( + ( ~ch_p( '\'' ) ) )[ cell_range.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                                       >> ch_p( '\'' )
                                                   )
                                               )
                                               >> ch_p( '!' )
                                           )
                                           >>
                                           (
                                               (
                                                   !ch_p( '$' )[ cell_range.flag_lhs = reference::absolute_column ]
                                                   >> column[ cell_range.column_lhs = construct_<std::string>( arg1, arg2 ) ]
                                                   >> !ch_p( '$' )[ cell_range.flag_lhs |= reference::absolute_row ]
                                                   >> limit_d( 1u, sheet_dimension::max_row + 1 )[ uint_p ][ cell_range.row_lhs = arg1 ]
                                                   >> ch_p( ':' )
                                                   >> !ch_p( '$' )[ cell_range.flag_rhs = reference::absolute_column ]
                                                   >> column[ cell_range.column_rhs = construct_<std::string>( arg1, arg2 ) ]
                                                   >> !ch_p( '$' )[ cell_range.flag_rhs |= reference::absolute_row ]
                                                   >> limit_d( 1u, sheet_dimension::max_row + 1 )[ uint_p ][ cell_range.row_rhs = arg1 ]
                                               )[ function<tree::add_regular_range>( tree::add_regular_range( self.m_p ) )( cell_range.workbook, cell_range.worksheet, cell_range.row_lhs, cell_range.column_lhs, cell_range.flag_lhs, cell_range.row_rhs, cell_range.column_rhs, cell_range.flag_rhs, false ) ]
                                               |
                                               (
                                                   !ch_p( '$' )[ cell_range.flag_lhs = reference::absolute_column ]
                                                   >> column[ cell_range.column_lhs = construct_<std::string>( arg1, arg2 ) ]
                                                   >> ch_p( ':' )
                                                   >> !ch_p( '$' )[ cell_range.flag_rhs = reference::absolute_column ]
                                                   >> column[ cell_range.column_rhs = construct_<std::string>( arg1, arg2 ) ]
                                               )[ function<tree::add_row_or_column_range>( tree::add_row_or_column_range( self.m_p ) )( cell_range.workbook, cell_range.worksheet, cell_range.column_lhs, cell_range.flag_lhs, cell_range.column_rhs, cell_range.flag_rhs ) ]
                                               |
                                               (
                                                   !ch_p( '$' )[ cell_range.flag_lhs = reference::absolute_row ]
                                                   >> limit_d( 1u, sheet_dimension::max_row + 1 )[ uint_p ][ cell_range.row_lhs = arg1 ]
                                                   >> ch_p( ':' )
                                                   >> !ch_p( '$' )[ cell_range.flag_rhs = reference::absolute_row ]
                                                   >> limit_d( 1u, sheet_dimension::max_row + 1 )[ uint_p ][ cell_range.row_rhs = arg1 ]
                                               )[ function<tree::add_row_or_column_range>( tree::add_row_or_column_range( self.m_p ) )( cell_range.workbook, cell_range.worksheet, cell_range.row_lhs, cell_range.flag_lhs, cell_range.row_rhs, cell_range.flag_rhs ) ]
                                           )
                                           //A-Z, AA-ZZ, AAA-XFD
                                           // , column = ( as_lower_d[( range_p( 'a', 'x' ) >> range_p( 'a', 'f' )  >> range_p( 'a', 'd' ) ) | ( range_p( 'a', 'z' ) >> range_p( 'a', 'z' ) ) | range_p( 'a', 'z' )] )
                                           //A_Z, AA-IV
                                           , column = ( as_lower_d[( range_p( 'a', 'h' ) >> range_p( 'a', 'z' ) ) | ( ch_p( 'i' ) >> range_p( 'a', 'v' ) ) | range_p( 'a', 'z' )] )
                                   );


                named_formula =
                    !(
                        (
                            // [workbook_1]sheet1 or sheet1
                            (
                                !(
                                    ch_p( '[' )
                                    >> workbook_name[ named_formula.workbook = construct_<std::string>( arg1, arg2 ) ]
                                    >> ch_p( ']' )
                                )
                                >> eps_p( ( worksheet_name ) >> ch_p( '!' ) ) >> ( worksheet_name )[ named_formula.worksheet = construct_<std::string>( arg1, arg2 ) ]
                            )
                            |
                            // '[workbook 1]sheet 1' or 'sheet 1'
                            (
                                ch_p( '\'' )
                                >> !(
                                    ch_p( '[' )
                                    >> ( + ( ~ch_p( ']' ) ) )[ named_formula.workbook = construct_<std::string>( arg1, arg2 ) ]
                                    >> ch_p( ']' )
                                )
                                >> ( + ( ~ch_p( '\'' ) ) )[ named_formula.worksheet = construct_<std::string>( arg1, arg2 ) ]
                                >> ch_p( '\'' )
                            )
                        )
                        >> ch_p( '!' )
                    )
                    >>
                    generic_name
                    [ function<tree::add_named_formula>( tree::add_named_formula( self.m_p ) )( named_formula.workbook, named_formula.worksheet, construct_<std::string>( arg1, arg2 ) ) ];

                empty = epsilon_p[ tree::add_child<empty_node>( self.m_p )];

                extension_function  =   ( + ( ~ch_p( '(' ) & ~ch_p( '#' ) & ~ch_p( '{' ) & ~ch_p( '}' ) & ~ch_p( ')' ) & ~ch_p( ':' ) & ~ch_p( '!' ) & ~ch_p( '@' ) & ~ch_p( '<' ) & ~ch_p( '>' ) & ~ch_p( '[' ) & ~ch_p( ']' ) & ~ch_p( '*' ) & ~ch_p( '/' ) & ~ch_p( '^' ) & ~ch_p( '%' ) & ~ch_p( '=' ) & ~ch_p( '&' ) & ~ch_p( '+' ) & ~ch_p( ' ' ) & ~ch_p( '-' ) & ~ch_p( ';' ) & ~ch_p( ',' ) & ~ch_p( '\'' ) & ~ch_p( '"' ) & ~ch_p( '$' ) ) )[ extension_function.name = construct_<std::string>( arg1, arg2 ) ]
                                        >> ch_p( '(' )[ tree::start_parent( self.m_p ) ]
                                        >> ( ch_p( ')' ) | ( epsilon_p[ tree::add_child<function_call_up_node>( self.m_p )] >> ( ( expression | expressions | empty ) >> *( locale_dependent_parameter_separator_p( self.m_p ) >> ( expression | expressions | empty ) ) ) >> epsilon_p[ tree::add_child<function_call_down_node>( self.m_p )] >> ch_p( ')' ) ) ) [ function<tree::add_function>( tree::add_function( self.m_p ) )( extension_function.name ) ];

                expressions     =   ( ch_p( '(' ) >> expression >> * ( locale_dependent_parameter_separator_p( self.m_p ) >> expression ) >> ch_p( ')' ) );

                expression     =   (
                                       comparison = term >> *(
                                                        ( ch_p( '>' ) >> term )[ tree::add_parent<greater_node>( self.m_p ) ]
                                                        | ( ch_p( '<' ) >> term )[ tree::add_parent<less_node>( self.m_p ) ]
                                                        | ( ch_p( '=' ) >> term )[ tree::add_parent<equal_node>( self.m_p ) ]
                                                        | ( str_p( ">=" ) >> term )[ tree::add_parent<greater_equal_node>( self.m_p ) ]
                                                        | ( str_p( "<=" ) >> term )[ tree::add_parent<less_equal_node>( self.m_p ) ]
                                                        | ( str_p( "<>" ) >> term )[ tree::add_parent<not_equal_node>( self.m_p ) ]
                                                    )
                                                    , term = factor >> *( ( '+' >> factor )[ tree::add_parent<addition_node>( self.m_p ) ] | ( '-' >> factor )[ tree::add_parent<subtraction_node>( self.m_p ) ] )
                                                             , factor = exponent >> *( ( '/' >> exponent )[ tree::add_parent<division_node>( self.m_p ) ] | ( '*' >> factor )[ tree::add_parent<multiplication_node>( self.m_p ) ] )
                                                                     , exponent = concatination >> *( ( ch_p( '^' ) >> concatination )[ tree::add_parent<exponent_node>( self.m_p ) ] )
                                                                             , concatination = percentage >> *( ( ch_p( '&' ) >> percentage )[ tree::add_parent<concatenation_node>( self.m_p ) ] )
                                                                                     , percentage = negation >> *( ch_p( '%' )[ tree::add_parent<percentage_node, 1>( self.m_p ) ] )
                                                                                             , negation = ( primitive | array ) | ch_p( '(' )[ tree::start_parent( self.m_p ) ] >> expression >> ch_p( ')' )[ tree::finalize_parent<brace_node>( self.m_p ) ] | ( '-' >> negation )[ tree::add_parent<negation_node, 1>( self.m_p ) ] | ( '+' >> negation )
                                                                                                     , variable = ch_p( '@' ) >>  as_lower_d[ ( range_p( 'a', 'z' ) | ch_p( '_' ) ) >> *( range_p( 'a', 'z' ) | range_p( '0', '9' ) | ch_p( '_' ) | ch_p( '.' ) ) ][ tree::add_variable( self.m_p ) ]
                                                                                                             , array = ch_p( '{' )[ tree::start_parent( self.m_p ) ] >> ( ( eps_p( no_actions_d[ array_row ] ) >> array_row ) | primitive ) >> *( locale_dependent_row_separator_p( self.m_p ) >> ( ( eps_p( no_actions_d[ array_row ] ) >> array_row ) | primitive ) ) >> ch_p( '}' )[ tree::finalize_parent<array_node>( self.m_p )]
                                                                                                                     , array_row = eps_p[ tree::start_parent( self.m_p ) ] >> ( primitive >> * ( locale_dependent_column_separator_p( self.m_p ) >> primitive ) )[ tree::finalize_parent<array_row_node>( self.m_p ) ]
                                                                                                                             , primitive = ( ~eps_p( language_dependent_numeric_parser_p( self.m_p ) >> ch_p( ':' ) ) >> language_dependent_numeric_parser_p( self.m_p )[ tree::add_child<digit_node, double>( self.m_p ) ] )
                                                                                                                                     | cell_range( 0, 0, 0, 0 )
                                                                                                                                     | cell( 0, 0 )
                                                                                                                                     | cell_ref_error
                                                                                                                                     | extension_function
                                                                                                                                     | variable
                                                                                                                                     | locale_dependent_boolean_p<true>( self.m_p )[ tree::add_child<boolean_true_node>( self.m_p )]
                                                                                                                                     | locale_dependent_boolean_p<false>( self.m_p )[ tree::add_child<boolean_false_node>( self.m_p )]
                                                                                                                                     | ch_p( '#' ) >> locale_dependent_error_p( self.m_p )[ tree::add_child<error_node>( self.m_p ) ]
                                                                                                                                     | lexeme_d[( ch_p( '"' ) >> *( ~ch_p( '"' ) | str_p( "\"\"" ) ) >> ch_p( '"' ) )][ tree::add_child<string_node, std::string>( self.m_p ) ]
                                                                                                                                     | named_formula
                                   );

                formula     =     (
                                      formula_actual = ch_p( '=' ) >> ( reference_list | expression )
                                                       , reference_list = eps_p( no_actions_d[ ( cell_range( 0, 0, 0, 0 ) | cell_ref_error | cell( 0, 0 ) | named_formula ) >> +( locale_dependent_parameter_separator_p( self.m_p ) >> ( cell_range( 0, 0, 0, 0 ) | cell( 0, 0 ) | named_formula ) ) ] )[ tree::start_parent( self.m_p ) ]
                                                               >> ( ( cell_range( 0, 0, 0, 0 ) | cell( 0, 0 ) | cell_ref_error | named_formula ) >> +( locale_dependent_parameter_separator_p( self.m_p ) >> ( cell_range( 0, 0, 0, 0 ) | cell( 0, 0 ) | cell_ref_error | named_formula ) ) )[ tree::finalize_parent<reference_list_node>( self.m_p ) ]
                                  );

                //ASTYLE_IGNORE


#if defined( BOOST_SPIRIT_DEBUG )
                BOOST_SPIRIT_DEBUG_RULE( entry );
                BOOST_SPIRIT_DEBUG_RULE( expression );
                BOOST_SPIRIT_DEBUG_RULE( expressions );
                BOOST_SPIRIT_DEBUG_RULE( term );
                BOOST_SPIRIT_DEBUG_RULE( factor );
                BOOST_SPIRIT_DEBUG_RULE( reference );
                BOOST_SPIRIT_DEBUG_RULE( unescaped_string );
                BOOST_SPIRIT_DEBUG_RULE( column );
                BOOST_SPIRIT_DEBUG_RULE( primitive );
                BOOST_SPIRIT_DEBUG_RULE( cell );
                BOOST_SPIRIT_DEBUG_RULE( cell_range );
                BOOST_SPIRIT_DEBUG_RULE( cell_ref_error );
                BOOST_SPIRIT_DEBUG_RULE( empty );
                BOOST_SPIRIT_DEBUG_RULE( formula );
                BOOST_SPIRIT_DEBUG_RULE( formula_actual );
                BOOST_SPIRIT_DEBUG_RULE( comparison );
                BOOST_SPIRIT_DEBUG_RULE( percentage );
                BOOST_SPIRIT_DEBUG_RULE( concatination );
                BOOST_SPIRIT_DEBUG_RULE( exponent );
                BOOST_SPIRIT_DEBUG_RULE( negation );
                BOOST_SPIRIT_DEBUG_RULE( extension_function );
                BOOST_SPIRIT_DEBUG_RULE( named_formula_name );
                BOOST_SPIRIT_DEBUG_RULE( named_formula );
                BOOST_SPIRIT_DEBUG_RULE( variable );
                BOOST_SPIRIT_DEBUG_RULE( array );
                BOOST_SPIRIT_DEBUG_RULE( array_row );
                BOOST_SPIRIT_DEBUG_RULE( formula_actual );
                BOOST_SPIRIT_DEBUG_RULE( reference_list );
                BOOST_SPIRIT_DEBUG_RULE( generic_name );
                BOOST_SPIRIT_DEBUG_RULE( workbook_name );
                BOOST_SPIRIT_DEBUG_RULE( worksheet_name );
#endif // BOOST_SPIRIT_DEBUG
            }

            bs::subrule<__LINE__> entry;
            bs::subrule<__LINE__> term;
            bs::subrule<__LINE__> factor;
            bs::subrule<__LINE__> reference;
            bs::subrule<__LINE__> unescaped_string;
            bs::subrule<__LINE__> column;
            bs::subrule<__LINE__> primitive;
            bs::subrule<__LINE__> comparison;
            bs::subrule<__LINE__> percentage;
            bs::subrule<__LINE__> concatination;
            bs::subrule<__LINE__> exponent;
            bs::subrule<__LINE__> negation;
            bs::subrule<__LINE__> variable;
            bs::subrule<__LINE__> named_formula_name;
            bs::subrule<__LINE__> array;
            bs::subrule<__LINE__> array_row;
            bs::subrule<__LINE__> formula_actual;
            bs::subrule<__LINE__> reference_list;

            typedef bs::scanner_list< ScannerT, typename bs::no_actions_scanner<ScannerT>::type > scanner_list_type;

            bs::rule<scanner_list_type, cell_parser_context::context_t> cell;
            bs::rule<scanner_list_type, cell_range_parser_context::context_t> cell_range;
            bs::rule<scanner_list_type, cell_ref_error_parser_context::context_t> cell_ref_error;
            bs::rule<ScannerT> empty;
            bs::rule<ScannerT, formula_parser_context::context_t> extension_function;
            bs::rule<scanner_list_type> expression;
            bs::rule<ScannerT> formula;
            bs::rule<ScannerT> expressions;
            bs::rule<ScannerT> generic_name;
            bs::rule<ScannerT> workbook_name;
            bs::rule<ScannerT> worksheet_name;
            bs::rule<scanner_list_type, named_formula_parser_context::context_t> named_formula;

            const bs::rule<ScannerT>& start() const {
                return formula;
            }
        };

        formula_grammar& operator =( const formula_grammar& );

        formula_parser::parser& m_p;
    };

public:
    /*!
     * \brief
     * perform the parsing step.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    explicit parser( const parsing_context& c, changeable_formula_parsing_result& r )
        : m_builder( *r.root() )
        , m_context( c )
        , m_result( r ) {
        if ( ! context().formula().empty() && ( context().formula()[0] == ' ' || context().formula()[context().formula().size()-1] == ' ' ) ) {
            const std::string trimmed_formula( boost::algorithm::trim_copy( context().formula() ) );
            bs::parse_info<> info = bs::parse( trimmed_formula.c_str(), formula_grammar( *this ), bs::space_p );
            if ( info.full ) {
                result().flag_success();
            }
        } else {
            bs::parse_info<> info = bs::parse( context().formula().c_str(), formula_grammar( *this ), bs::space_p );
            if ( info.full ) {
                result().flag_success();
            }
        }
    }

private:
    /*!
     * \brief
     * return the parsing context.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const parsing_context& context() {
        return m_context;
    }

    /*!
     * \brief
     * return the parsing context.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline const parsing_context& context() const {
        return m_context;
    }

    /*!
     * \brief
     * return the parsing result context.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline changeable_formula_parsing_result& result() {
        return m_result;
    }

private:
    parser& operator =( const parser& );

    tree::tree_builder m_builder;
    const parsing_context& m_context;
    changeable_formula_parsing_result& m_result;
};

formula_parser::parsing_result_auto_type formula_parser::operator()( const parsing_context& context )
{
    parsing_result_auto_type return_value( new changeable_formula_parsing_result() );
    parser instance( context, static_cast<changeable_formula_parsing_result&>( *return_value ) );
    return return_value;
}

#if defined( WIN32 )
# pragma warning ( pop )
#endif // WIN32


