/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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
#include "wss/ast_formula.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/invalid_formula_exception.hpp"
#include "wss/formula_parsing_context.hpp"
#include "wss/syntax.hpp"

ast_formula::ast_formula( ::session& s, const weak_worksheet_type& ws, const std::string& formula )
{
    static formula_parser fp;
    try {
        parsing_context pc( s, ws, formula );
        m_ast = fp( pc );
        if ( NULL == m_ast.get() || ! m_ast->is_success() ) {
            throw invalid_formula_exception( std::string( "parsing of the formula '" ).append( formula ).append( "' failed!" ) );
        }
    } catch ( const object_not_found_exception& e ) {
        throw invalid_formula_exception( e );
    } catch ( const std::logic_error& e ) {
        throw invalid_formula_exception( std::string( "parsing of the formula '" ).append( formula ).append( "' failed: " ).append( e.what() ) );
    }
}

bool ast_formula::test_formula( ::session& s, const weak_worksheet_type& ws, const std::string& formula )
{
    //first two are either "=+" or "=-"
    for ( size_t i = 2; i < formula.size(); i++ ) {
        char crt = formula[i];
        if ( crt  < '0' || crt > '9' ) {
            if ( crt != '-' && crt != '+' && crt != '*' && crt != '/' && crt != '.' && crt != ',' ) {
                return false;
            }
        }
    }

    static formula_parser fp;
    try {
        parsing_context pc( s, ws, formula );
        formula_parser::parsing_result_auto_type ast = fp( pc );
        if ( NULL == ast.get() || ! ast->is_success() ) {
            return false;
        }
    } catch ( const object_not_found_exception& e ) {
        return false;
    }

    return true;
}

formula_parser::parsing_result_auto_type& ast_formula::disown()
{
    return m_ast;
}
bool ast_formula::is_view_independent() const
{
    return m_ast->view_independent();
}

bool ast_formula::executes_on_set() const
{
    return m_ast->executes_on_set();
}

