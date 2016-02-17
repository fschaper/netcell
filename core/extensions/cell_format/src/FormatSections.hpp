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

#include "FormatSection.hpp"

namespace cell_format
{
    /*! A decimal format section.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    struct DecimalFormatSection : public FormatSection {
        DecimalFormatSection();
        ~DecimalFormatSection();

        Type get_type() const;

        void accept( FormatSectionVisitor& v );
        void accept( FormatSectionConstVisitor& v ) const;

        virtual bool operator==( const FormatSection& other ) const;

        struct DigitCounts {
            DigitCounts() : integer( 0 ), fraction( 0 ), exp_integer( 0 ), exp_fraction( 0 ) {}

            unsigned int integer, fraction, exp_integer, exp_fraction;

            bool operator==( const DigitCounts& other ) const {
                return integer == other.integer
                       && fraction == other.fraction
                       && exp_integer == other.exp_integer
                       && exp_fraction == other.exp_fraction;
            }
        } digits;

        double factor;
        bool have_thousand_sep;
        bool suppress_sign;
    };

    /*! A fraction format section.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    struct FractionFormatSection : public FormatSection {
        FractionFormatSection();
        ~FractionFormatSection();

        Type get_type() const;

        void accept( FormatSectionVisitor& v );
        void accept( FormatSectionConstVisitor& v ) const;

        virtual bool operator==( const FormatSection& other ) const;

        int integer_idx; // -1 if none
        int numerator_idx;
        int denominator_idx;
        bool suppress_sign;
        double factor;
    };

    /*! A text format section.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    struct TextFormatSection : public FormatSection {
        TextFormatSection();
        ~TextFormatSection();

        Type get_type() const;

        void accept( FormatSectionVisitor& v );
        void accept( FormatSectionConstVisitor& v ) const;

        virtual bool operator==( const FormatSection& other ) const;
    };

    /*! A date/time format section.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    struct DateTimeFormatSection : public FormatSection {
        DateTimeFormatSection();
        ~DateTimeFormatSection();

        Type get_type() const;

        void accept( FormatSectionVisitor& v );
        void accept( FormatSectionConstVisitor& v ) const;

        virtual bool operator==( const FormatSection& other ) const;

        bool have_ampm;
        bool have_second_fraction;
    };

    /*! An empty format section (meaning will be determined by position inside format list).
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    struct EmptyFormatSection : public FormatSection {
        EmptyFormatSection();
        ~EmptyFormatSection();

        Type get_type() const;

        void accept( FormatSectionVisitor& v );
        void accept( FormatSectionConstVisitor& v ) const;

        virtual bool operator==( const FormatSection& other ) const;
    };

    /*! Visitor.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    class FormatSectionVisitor
    {
    public:
        virtual ~FormatSectionVisitor()
        {}

        virtual void visit( DecimalFormatSection& s ) = 0;
        virtual void visit( FractionFormatSection& s ) = 0;
        virtual void visit( DateTimeFormatSection& s ) = 0;
        virtual void visit( TextFormatSection& s ) = 0;
        virtual void visit( EmptyFormatSection& s ) = 0;
    };

    /*! Visitor.
     *
     *  \author Marek Pikulski <marek.pikulski@jedox.com>
     */
    class FormatSectionConstVisitor
    {
    public:
        virtual ~FormatSectionConstVisitor()
        {}

        virtual void visit( const DecimalFormatSection& s ) = 0;
        virtual void visit( const FractionFormatSection& s ) = 0;
        virtual void visit( const DateTimeFormatSection& s ) = 0;
        virtual void visit( const TextFormatSection& s ) = 0;
        virtual void visit( const EmptyFormatSection& s ) = 0;
    };
}
