/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef FUNCTION_TABLE_HPP
#define FUNCTION_TABLE_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace jedox
{
    namespace wss
    {
        using namespace ::xio;
        using namespace ::xio::xml::schema;

        class general_type;
        class group_type;
        class groups_type;
        class parameter_type;
        class sequence_type;
        class parameters_type;
        class syntax_type;
        class description_type;
        class function_type;
        class translation_table_type;
        class function_table;

        class general_type
        {
        public:
            String parameter_separator;
            String column_separator;
            String row_separator;
            Boolean use_dot;
            String boolean_true;
            String boolean_false;
        };

        class group_type
        {
        public:
            String translation;
            String id;
            String name;
        };

        class groups_type
        {
        public:
            std::vector< group_type > group;
        };

        class parameter_type : public simple_type<String>
        {
        public:
            parameter_type() {}
            parameter_type( const String& v ) : simple_type<String>( v ) {}
            String name;
            optional< String > type;
        };

        class sequence_type
        {
        public:
            parameter_type parameter;
            UnsignedByte from;
            UnsignedByte to;
        };

        class parameters_type
        {
        public:
            std::vector< parameter_type > parameter;
            poptional< sequence_type > sequence;
        };

        class syntax_type
        {
        public:
            String parameters;
        };

        class description_type
        {
        public:
            poptional< parameters_type > parameters;
            syntax_type syntax;
            String _short_;
            String _long_;
        };

        class function_type
        {
        public:
            String translation;
            description_type description;
            String comment;
            String name;
            String category;
        };

        class translation_table_type
        {
        public:
            general_type general;
            groups_type groups;
            std::vector< function_type > function;
            String lang;
        };

        class function_table
        {
        public:
            poptional< translation_table_type > translation_table;
        };

    }
}
#endif

