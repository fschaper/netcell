/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#pragma once

#include <iomanip>
#include <sstream>

#include "ControlTokens.hpp"
#include "i18n.hpp"

namespace cell_format
{
    /*! Formatting condition for conditional formats.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    struct Condition {
        Condition() : op( Condition::none ), operand( 0.0 ) {}
        ~Condition() {}

        bool matches( double val ) const {
            switch ( op ) {
                case EQ:
                    return val == operand;
                case NEQ:
                    return val != operand;
                case GTE:
                    return val >= operand;
                case LTE:
                    return val <= operand;
                case GT:
                    return val > operand;
                case LT:
                    return val < operand;
                default:
                    return true;
            }
        }

        inline std::string to_string( const ControlTokens& ct ) const;

        inline bool operator==( const Condition& other ) const {
            return op == other.op && operand == other.operand;
        }

        enum Operators {
            EQ, NEQ, GTE, LTE, GT, LT, none
        } op;

        double operand;
    };

    inline std::string Condition::to_string( const ControlTokens& ct ) const
    {
        std::ostringstream ostr;

        ostr << '[';

        switch ( op ) {
            case Condition::EQ:
                ostr << "=";
                break;
            case Condition::NEQ:
                ostr << "<>";
                break;
            case Condition::GTE:
                ostr << ">=";
                break;
            case Condition::LTE:
                ostr << "<=";
                break;
            case Condition::GT:
                ostr << ">";
                break;
            case Condition::LT:
                ostr << "<";
                break;
            case Condition::none:
                ostr << "none]";
                return ostr.str();
            default:
                ostr << "invalid]";
                return ostr.str();
        }

        ostr << std::setprecision( 9 ) << operand << ']';

        std::string res = ostr.str();

        std::string::size_type i;
        if ( ( i = res.find( '.' ) ) != std::string::npos ) {
            res[i] = ct.format_codes.decimal;
        }

        return res;
    }
}
