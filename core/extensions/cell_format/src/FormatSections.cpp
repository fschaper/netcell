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

#include "FormatSections.hpp"

namespace cell_format
{

    DecimalFormatSection::DecimalFormatSection()
        : factor( 1.0 )
        , have_thousand_sep( false )
        , suppress_sign( false )
    {}

    DecimalFormatSection::~DecimalFormatSection()
    {}

    DecimalFormatSection::Type DecimalFormatSection::get_type() const
    {
        return Decimal;
    }

    void DecimalFormatSection::accept( FormatSectionVisitor& v )
    {
        v.visit( *this );
    }

    void DecimalFormatSection::accept( FormatSectionConstVisitor& v ) const
    {
        v.visit( *this );
    }

    bool DecimalFormatSection::operator==( const FormatSection& other ) const
    {
        try {
            const DecimalFormatSection& o = dynamic_cast<const DecimalFormatSection&>( other );

            return digits == o.digits
                   && factor == o.factor
                   && have_thousand_sep == o.have_thousand_sep
                   && suppress_sign == o.suppress_sign
                   && FormatSection::equals( other );
        } catch ( std::bad_cast ) {
            return false;
        }
    }


    FractionFormatSection::FractionFormatSection()
        : integer_idx( -1 )
        , numerator_idx( -1 )
        , denominator_idx( -1 )
        , suppress_sign( false )
        , factor( 1.0 )
    {}

    FractionFormatSection::~FractionFormatSection()
    {}

    FractionFormatSection::Type FractionFormatSection::get_type() const
    {
        return Fraction;
    }

    void FractionFormatSection::accept( FormatSectionVisitor& v )
    {
        v.visit( *this );
    }

    void FractionFormatSection::accept( FormatSectionConstVisitor& v ) const
    {
        v.visit( *this );
    }

    bool FractionFormatSection::operator==( const FormatSection& other ) const
    {
        try {
            const FractionFormatSection& o = dynamic_cast<const FractionFormatSection&>( other );

            return factor == o.factor
                   && suppress_sign == o.suppress_sign
                   && FormatSection::equals( other );
        } catch ( std::bad_cast ) {
            return false;
        }
    }


    TextFormatSection::TextFormatSection()
    {}

    TextFormatSection::~TextFormatSection()
    {}

    TextFormatSection::Type TextFormatSection::get_type() const
    {
        return Text;
    }

    void TextFormatSection::accept( FormatSectionVisitor& v )
    {
        v.visit( *this );
    }

    void TextFormatSection::accept( FormatSectionConstVisitor& v ) const
    {
        v.visit( *this );
    }

    bool TextFormatSection::operator==( const FormatSection& other ) const
    {
        try {
            /*const TextFormatSection& o =*/ dynamic_cast<const TextFormatSection&>( other );

            return FormatSection::equals( other );
        } catch ( std::bad_cast ) {
            return false;
        }
    }


    DateTimeFormatSection::DateTimeFormatSection()
        : have_ampm( false )
        , have_second_fraction( false )
    {}

    DateTimeFormatSection::~DateTimeFormatSection()
    {}

    DateTimeFormatSection::Type DateTimeFormatSection::get_type() const
    {
        return DateTime;
    }

    void DateTimeFormatSection::accept( FormatSectionVisitor& v )
    {
        v.visit( *this );
    }

    void DateTimeFormatSection::accept( FormatSectionConstVisitor& v ) const
    {
        v.visit( *this );
    }

    bool DateTimeFormatSection::operator==( const FormatSection& other ) const
    {
        try {
            const DateTimeFormatSection& o = dynamic_cast<const DateTimeFormatSection&>( other );

            return have_ampm == o.have_ampm
                   && have_second_fraction == o.have_second_fraction
                   && FormatSection::equals( other );
        } catch ( std::bad_cast ) {
            return false;
        }
    }

    EmptyFormatSection::EmptyFormatSection()
    {}

    EmptyFormatSection::~EmptyFormatSection()
    {}

    EmptyFormatSection::Type EmptyFormatSection::get_type() const
    {
        return Empty;
    }

    void EmptyFormatSection::accept( FormatSectionVisitor& v )
    {
        v.visit( *this );
    }

    void EmptyFormatSection::accept( FormatSectionConstVisitor& v ) const
    {
        v.visit( *this );
    }

    bool EmptyFormatSection::operator==( const FormatSection& other ) const
    {
        try {
            /*const EmptyFormatSection& o =*/ dynamic_cast<const EmptyFormatSection&>( other );

            return true;
        } catch ( std::bad_cast ) {
            return false;
        }
    }
}
