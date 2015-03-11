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

#include "parsed_cell_format.hpp"
#include "i18n.hpp"
#include "CellFormatParser.hpp"
#include "CellFormatParseTreeConverter.hpp"
#include "CellFormatPostParser.hpp"
#include "CellFormatPrinter.hpp"

namespace cell_format
{
    parsed_cell_format::parsed_cell_format( bool conditionless )
        : m_sections( new FormatSections ), m_conditionless( conditionless )
    {}

    parsed_cell_format::parsed_cell_format( const parsed_cell_format& other )
    {
        //TODO: remove
        m_conditionless = other.m_conditionless;
        m_sections      = other.m_sections;
    }

    parsed_cell_format::~parsed_cell_format()
    {
    }

    bool parsed_cell_format::operator==( const parsed_cell_format& other ) const
    {
        if ( m_sections->size() != other.get_sections().size() ) {
            return false;
        }

        for ( FormatSections::const_iterator i = m_sections->begin(), e = m_sections->end(), j = other.get_sections().begin(); i != e; ++i, ++j ) {
            if ( *i != *j ) {
                return false;
            }
        }

        return true;
    }

    bool parsed_cell_format::operator!=( const parsed_cell_format& other ) const
    {
        return !operator==( other );
    }

    bool parsed_cell_format::is_conditionless() const
    {
        return m_conditionless;
    }

    const parsed_cell_format::FormatSections& parsed_cell_format::get_sections() const
    {
        return *m_sections;
    }

    parsed_cell_format* parsed_cell_format::Allocator::get_new( const std::string& format )
    {
        parsed_cell_format* new_format = new parsed_cell_format;

        const ControlTokens         english     = i18n::instance().get_english();
        CellFormatParser            parser( english );
        CellFormatParseTree         pt;

        format >> parser >> pt;
        pt >> CellFormatParseTreeConverter( english ) >> *new_format;
        *new_format >> CellFormatPostParser( english );

        {
            lock_type lock( mutex );
            m_data.push_back( new_format );
        }
        return new_format;
    }

    const std::string parsed_cell_format::Allocator::translate( const locale& from, const locale& to, const std::string& format )
    {
        parsed_cell_format          local_format;
        const ControlTokens&        local_tokens     = i18n::instance()[ from ];
        CellFormatParser            parser( local_tokens );
        CellFormatParseTree         pt;
        CellFormatPrinter           printer( i18n::instance()[ to ] );

        format >> parser >> pt;
        pt >> CellFormatParseTreeConverter( local_tokens ) >> local_format;
        local_format >> CellFormatPostParser( local_tokens );

        return printer.process( local_format );
    }

    parsed_cell_format::Allocator::Allocator()
    {
    }

    parsed_cell_format::Allocator::~Allocator()
    {
        lock_type lock( mutex );

        for ( std::vector< parsed_cell_format* >::iterator i = m_data.begin(); i != m_data.end(); i++ ) {
            delete *i;
        }
    }
}
