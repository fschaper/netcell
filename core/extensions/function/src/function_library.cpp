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
 *  \author\
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "function_library.hpp"


/*
interpreter_variant function_sum( function_parameter& parameters )
{
    interpreter_variant return_value( 0.0 );
    foreach( const interpreter_variant& current_argument, parameters ) {
        switch ( current_argument.i_type() ) {
            case interpreter_variant::type_range: {
                foreach( const shared_dependency_type& d, range_reference_cast( current_argument.reference() )->iterators() ) {
                    return_value += d->value( parameters.context() );
                }
            }
            break;

            default:
                return_value += current_argument;
                break;
        }
    }
    return return_value;
}*/


/*!
 * \brief
 * Returns an evenly distributed random number greater than or equal to 0 and less than 1.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node&
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the random number
 *
 * \details
 * A new random number is returned every time the worksheet is calculated.
 * To generate a random real number between a and b, use: RAND()*(b-a)+a
 *
 * \see
 * function_randbetween
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_rand
interpreter_variant function_rand( function_parameter& )
{
    static bool initialized = false;
    if ( ! initialized ) {
        std::srand ( std::time( NULL ) );
        initialized = true;
    }
    return interpreter_variant( variant( static_cast<double>( std::rand() ) / ( RAND_MAX * 1.00000000000001 ) ) );
    // Returns an evenly distributed random number greater than or equal to 0 and less than 1.
    // A new random number is returned every time the worksheet is calculated.
}
#endif

#ifdef namspace_internal
namespace internal
{
    class SumStrategy //-------------------------------------------------------------------------------------------
    {
    public:
        typedef double return_type;

        SumStrategy()
            : m_summe( 0.0 ) {}

        operator return_type() const {
            return m_summe;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    m_summe += boost::lexical_cast<double>( v );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_summe += v;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_summe += v == true ? 1.0 : 0.0;
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            // Empty is ignored for all states.
        }

    private:
        double m_summe;
    };

    class SumsqStrategy //-------------------------------------------------------------------------------------------
    {
    public:
        typedef double return_type;

        SumsqStrategy()
            : m_sumsq( 0.0 ) {}

        operator return_type() const {
            return m_sumsq;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    m_sumsq += newDouble * newDouble;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_sumsq += v * v;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_sumsq += v == true ? 1.0 : 0.0;
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            // Empty is ignored for all states.
        }

    private:
        double m_sumsq;
    };

    class CountStrategy //------------------------------------------------------------------------------------------
    {
    public:
        typedef double return_type;

        CountStrategy()
            : m_count( 0.0 ) {}

        operator return_type() const {
            return m_count;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    boost::lexical_cast<double>( v );
                    ++m_count;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers is ignored.
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double counts for all states.
            ++m_count;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                ++m_count;
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // Error values are ignored for all states.
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && s.is_range ) {
                ++m_count;
            }
            // otherwise empty is ignored.
        }

    private:
        double m_count;
    };

    class CountaStrategy //------------------------------------------------------------------------------------------
    {
    public:
        typedef double return_type;

        CountaStrategy()
            : m_counta( 0.0 ) {}

        operator return_type() const {
            return m_counta;
        }

        void handle( const State& s, const std::string& ) {
            // Text counts for all states.
            ++m_counta;
        }

        void handle( const State& s, double v ) {
            // Double counts for all states.
            ++m_counta;
        }

        void handle( const State& s, bool v ) {
            // Bool counts for all states.
            ++m_counta;
        }

        void handle( const State& s, variant::error_type error ) {
            // Error values are counted for all states.
            ++m_counta;
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                ++m_counta;
            }
            // otherwise empty is ignored.
        }

    private:
        double m_counta;
    };

    /*class AverageStrategy now defined in UtilityMath.hpp*/

    class AverageaStrategy //------------------------------------------------------------------------------------------
    {
    public:
        struct averagea_result {
            averagea_result()
                : summe( 0.0 )
                , count( 0 ) {}

            double summe;
            long int count;
        };

        typedef averagea_result return_type;

        AverageaStrategy() {}

        operator return_type() const {
            return m_averagea_result;
        }


        void handle( const State& s, const std::string& v ) {
            if ( s.is_array || s.is_range ) {
                m_averagea_result.count++;
            } else {
                try {
                    // text representations of numbers are counted.
                    m_averagea_result.summe += boost::lexical_cast<double>( v );
                    m_averagea_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
        }

        void handle( const State& s, double v ) {
            // Double counts for all states.
            m_averagea_result.summe += v;
            m_averagea_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( s.is_range || !s.is_array ) {
                m_averagea_result.summe += v == true ? 1.0 : 0.0;
                m_averagea_result.count++;
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_averagea_result.count++;
            }
            // otherwise empty is ignored.
        }

    private:
        averagea_result m_averagea_result;
    };

    class HarmeanStrategy //------------------------------------------------------------------------------------------
    {
    public:
        struct harmean_result {
            harmean_result()
                : summe( 0.0 )
                , count( 0 ) {}

            double summe;
            long int count;
        };

        typedef harmean_result return_type;

        HarmeanStrategy() {}

        operator return_type() const {
            return m_harmean_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( newDouble <= 0.0 ) {
                        throw variant( variant::error_num );
                    }
                    m_harmean_result.summe += 1.0 / newDouble;
                    m_harmean_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double counts for all states.
            if ( v <= 0.0 ) {
                throw variant( variant::error_num );
            }
            m_harmean_result.summe += 1.0 / v;
            m_harmean_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                if ( v ) {
                    m_harmean_result.summe += 1.0;
                    m_harmean_result.count++;
                } else {
                    throw variant( variant::error_num );
                }
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                throw variant( variant::error_num );
            }
            // otherwise empty is ignored.
        }

    private:
        harmean_result m_harmean_result;
    };

    class MaxStrategy //--------------------------------------------------------------------------------------------
    {
    public:
        struct max_result {
            max_result()
                : max( -std::numeric_limits<double>::max() )
                , has_value( false ) {}

            double max;
            bool has_value;
        };

        typedef max_result return_type;

        MaxStrategy() {}

        operator return_type() const {
            return m_max_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( ( ! m_max_result.has_value ) || newDouble > m_max_result.max ) {
                        m_max_result.has_value = true;
                        m_max_result.max = newDouble;
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            if ( ( ! m_max_result.has_value ) || v > m_max_result.max ) {
                m_max_result.has_value = true;
                m_max_result.max = v;
            }
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // single parameter is evaluated as 1 for true and 0 for false.
                if ( ( ! m_max_result.has_value ) || v > m_max_result.max ) {
                    m_max_result.has_value = true;
                    m_max_result.max = v == true ? 1.0 : 0.0;
                }
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as 0.
                if ( ( ! m_max_result.has_value ) || 0.0 > m_max_result.max ) {
                    m_max_result.has_value = true;
                    m_max_result.max = 0.0;
                }
            }
            // otherwise empty is ignored.
        }

    private:
        max_result m_max_result;
    };

    class MaxaStrategy //-------------------------------------------------------------------------------------------
    {
    public:
        struct maxa_result {
            maxa_result()
                : maxa( -std::numeric_limits<double>::max() )
                , has_value( false ) {}

            double maxa;
            bool has_value;
        };

        typedef maxa_result return_type;

        MaxaStrategy() {}

        operator return_type() const {
            return m_maxa_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( s.is_range ) {
                // In ranges text is evaluated as 0.
                if ( ( ! m_maxa_result.has_value ) || 0.0 > m_maxa_result.maxa ) {
                    m_maxa_result.has_value = true;
                    m_maxa_result.maxa = 0.0;
                }
            } else if ( !s.is_array ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( ( ! m_maxa_result.has_value ) || newDouble > m_maxa_result.maxa ) {
                        m_maxa_result.has_value = true;
                        m_maxa_result.maxa = newDouble;
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise (single array) text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            if ( ( ! m_maxa_result.has_value ) || v > m_maxa_result.maxa ) {
                m_maxa_result.has_value = true;
                m_maxa_result.maxa = v;
            }
        }

        void handle( const State& s, bool v ) {
            if ( s.is_range || !s.is_array ) {
                // 1 for true and 0 for false.
                if ( ( ! m_maxa_result.has_value ) || v > m_maxa_result.maxa ) {
                    m_maxa_result.has_value = true;
                    m_maxa_result.maxa = v == true ? 1.0 : 0.0;
                }
            }
            // otherwise (single array) a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as 0.
                if ( ( ! m_maxa_result.has_value ) || 0.0 > m_maxa_result.maxa ) {
                    m_maxa_result.has_value = true;
                    m_maxa_result.maxa = 0.0;
                }
            }
            // otherwise empty is ignored.
        }

    private:
        maxa_result m_maxa_result;
    };

    class MinStrategy //------------------------------------------------------------------------------------------
    {
    public:
        struct min_result {
            min_result()
                : min( std::numeric_limits<double>::max() )
                , has_value( false ) {}

            double min;
            bool has_value;
        };

        typedef min_result return_type;

        MinStrategy() {}

        operator return_type() const {
            return m_min_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( ( ! m_min_result.has_value ) || newDouble < m_min_result.min ) {
                        m_min_result.has_value = true;
                        m_min_result.min = newDouble;
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            if ( ( ! m_min_result.has_value ) || v < m_min_result.min ) {
                m_min_result.has_value = true;
                m_min_result.min = v;
            }
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // single parameter is evaluated as 1 for true and 0 for false.
                if ( ( ! m_min_result.has_value ) || v < m_min_result.min ) {
                    m_min_result.has_value = true;
                    m_min_result.min = v == true ? 1.0 : 0.0;
                }
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as 0.
                if ( ( ! m_min_result.has_value ) || 0.0 < m_min_result.min ) {
                    m_min_result.has_value = true;
                    m_min_result.min = 0.0;
                }
            }
            // otherwise empty is ignored.
        }

    private:
        min_result m_min_result;
    };

    class MinaStrategy //------------------------------------------------------------------------------------------
    {
    public:
        struct mina_result {
            mina_result()
                : mina( std::numeric_limits<double>::max() )
                , has_value( false ) {}

            double mina;
            bool has_value;
        };

        typedef mina_result return_type;

        MinaStrategy() {}

        operator return_type() const {
            return m_mina_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( ( ! m_mina_result.has_value ) || newDouble < m_mina_result.mina ) {
                        m_mina_result.has_value = true;
                        m_mina_result.mina = newDouble;
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            if ( ( ! m_mina_result.has_value ) || v < m_mina_result.mina ) {
                m_mina_result.has_value = true;
                m_mina_result.mina = v;
            }
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // single parameter is evaluated as 1 for true and 0 for false.
                if ( ( ! m_mina_result.has_value ) || v < m_mina_result.mina ) {
                    m_mina_result.has_value = true;
                    m_mina_result.mina = v == true ? 1.0 : 0.0;
                }
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as 0.
                if ( ( ! m_mina_result.has_value ) || 0.0 < m_mina_result.mina ) {
                    m_mina_result.has_value = true;
                    m_mina_result.mina = 0.0;
                }
            }
            // otherwise empty is ignored.
        }

    private:
        mina_result m_mina_result;
    };

    class AndStrategy //--------------------------------------------------------------------------------------------
    {
    public:
        struct and_result {
            and_result()
                : result( true )
                , has_value( false ) {}

            bool result;
            bool has_value;
        };

        typedef and_result return_type;

        AndStrategy() {}

        operator return_type() const {
            return m_and_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_and_result.has_value = true;
                if ( boost::algorithm::iequals( v, "FALSE" ) ) {
                    m_and_result.result = false;
                    return;
                }
                if ( !boost::algorithm::iequals( v, "TRUE" ) ) {
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_and_result.has_value = true;
            m_and_result.result = m_and_result.result && ( v == 0.0 ? false : true );
        }

        void handle( const State& s, bool v ) {
            // A bool is evaluated for all states.
            m_and_result.has_value = true;
            m_and_result.result = m_and_result.result && v;
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as false.
                m_and_result.has_value = true;
                m_and_result.result = false;
            }
            // otherwise empty is ignored.
        }

    private:
        and_result m_and_result;
    };
    class OrStrategy //--------------------------------------------------------------------------------------------
    {
    public:
        struct or_result {
            or_result()
                : result( false )
                , has_value( false ) {}

            bool result;
            bool has_value;
        };

        typedef or_result return_type;

        OrStrategy() {}

        operator return_type() const {
            return m_or_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_or_result.has_value = true;
                if ( boost::algorithm::iequals( v, "TRUE" ) ) {
                    m_or_result.result = true;
                    return;
                }
                if ( !boost::algorithm::iequals( v, "FALSE" ) ) {
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_or_result.has_value = true;
            m_or_result.result = m_or_result.result || ( v == 0.0 ? false : true );
        }

        void handle( const State& s, bool v ) {
            // A bool is evaluated for all states.
            m_or_result.has_value = true;
            m_or_result.result = m_or_result.result || v;
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                // empty single parameter is evaluated as false.
                m_or_result.has_value = true;
                m_or_result.result = m_or_result.result || false;
            }
            // otherwise empty is ignored.
        }

    private:
        or_result m_or_result;
    };

    /*class VarStrategy - now defined in UtilityMath.hpp*/

    class VaraStrategy // also for VARPA, STDEVA, STDEVPA-----------------------------------------------------------
    {
    public:
        struct vara_result {
            vara_result()
                : summe( 0.0 )
                , sumsq( 0.0 )
                , count( 0 ) {}

            double summe;
            double sumsq;
            long int count;
        };

        typedef vara_result return_type;

        VaraStrategy() {}

        operator return_type() const {
            return m_vara_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( s.is_range ) {
                m_vara_result.count++;
            } else if ( !s.is_array ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    m_vara_result.summe += newDouble;
                    m_vara_result.sumsq += newDouble * newDouble;
                    m_vara_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_vara_result.summe += v;
            m_vara_result.sumsq += v * v;
            m_vara_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) || s.is_range ) {
                m_vara_result.summe += v == true ? 1.0 : 0.0;
                m_vara_result.sumsq += v == true ? 1.0 : 0.0;
                m_vara_result.count++;
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_vara_result.count++;
            }
            // otherwise empty is ignored.
        }

    private:
        vara_result m_vara_result;
    };

    class ProductStrategy //-------------------------------------------------------------------------------------------
    {
    public:
        typedef double return_type;

        ProductStrategy()
            : m_product( 1.0 ) {}

        operator return_type() const {
            return m_product;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    m_product *= boost::lexical_cast<double>( v );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_product *= v;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                if ( !v ) {
                    m_product = 0.0;
                }
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            // Empty is ignored for all states.
        }

    private:
        double m_product;
    };

    class GeomeanStrategy //---------------------------------------------------------------------------------------
    {
    public:
        struct geomean_result {
            geomean_result()
                : product( 1.0 )
                , count( 0 ) {}

            double product;
            long int count;
        };

        typedef geomean_result return_type;

        GeomeanStrategy() {}

        operator return_type() const {
            return m_geomean_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    if ( newDouble <= 0.0 ) {
                        throw variant( variant::error_num );
                    }
                    m_geomean_result.product *= newDouble;
                    m_geomean_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            if ( v <= 0.0 ) {
                throw variant( variant::error_num );
            }
            m_geomean_result.product *= v;
            m_geomean_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                if ( v ) {
                    m_geomean_result.count++;
                } else {
                    throw variant( variant::error_num );
                }
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                throw variant( variant::error_num );
            }
            // otherwise empty is ignored.
        }

    private:
        geomean_result m_geomean_result;
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    typedef Reduce<SumStrategy> Sumf;
    typedef Reduce<SumsqStrategy> Sumsq;
    typedef Reduce<CountStrategy> Count;
    typedef Reduce<CountaStrategy> Counta;
    //typedef Reduce<AverageStrategy> Average;
    typedef Reduce<AverageaStrategy> Averagea;
    typedef Reduce<HarmeanStrategy> Harmean;
    typedef Reduce<MaxStrategy> Max;
    typedef Reduce<MaxaStrategy> Maxa;
    typedef Reduce<MinStrategy> Min;
    typedef Reduce<MinaStrategy> Mina;
    typedef Reduce<AndStrategy> And;
    typedef Reduce<OrStrategy> Or;
    //typedef Reduce<VarStrategy> Var;
    typedef Reduce<VaraStrategy> Vara;
    typedef Reduce<ProductStrategy> Product;
    typedef Reduce<GeomeanStrategy> Geomean;

    struct Sum {
        Sum()
            : summe( 0.0 ) {}

        inline void operator()( const variant& value ) {
            // If an argument is an array or reference, only numbers in that array or reference are counted.
            // Empty cells, logical values, text, or error values in the array or reference are ignored.
            if ( value.type() == variant::type_double ) {
                summe += value.numeric();
            }
        }
        double summe;
    };

    struct SumA {
        SumA()
            : summe( 0.0 ) {}

        inline void operator()( const variant& value ) {
            // Empty text and text evaluate as 0, FALSE as 0 and TRUE as 1.
            if ( value.type() != variant::type_empty ) {
                summe += value.numeric();
            }
        }
        double summe;
    };

    struct SumSq {
        SumSq()
            : summe( 0.0 ) {}

        inline void operator()( const variant& value ) {
            // If an argument is an array or reference, only numbers in that array or reference are counted.
            // Empty cells, logical values, text, or error values in the array or reference are ignored.
            if ( value.type() == variant::type_double ) {
                summe += value.numeric() * value.numeric();
            }
        }
        double summe;
    };

    struct SumSqA {
        SumSqA()
            : summe( 0.0 ) {}

        inline void operator()( const variant& value ) {
            // Empty text and text evaluate as 0, FALSE as 0 and TRUE as 1.
            if ( value.type() != variant::type_empty ) {
                summe += value.numeric() * value.numeric();
            }
        }
        double summe;
    };

    struct Counter {
        Counter()
            : counter( 0 ) {}

        inline void operator()( const variant& value ) {
            // If an argument is an array or reference, only numbers in that array or reference are counted.
            // Empty cells, logical values, text, or error values in the array or reference are ignored.
            if ( value.type() == variant::type_double ) {
                counter++;
            }
        }
        unsigned long int counter;
    };

    struct CounterA {
        CounterA()
            : counter( 0 ) {}

        inline void operator()( const variant& value ) {
            // Empty cells within the array or reference are ignored.
            if ( value.type() != variant::type_empty ) {
                counter++;
            }
        }
        unsigned long int counter;
    };
}
#endif
/*!
 * \brief
 * Adds all the numbers and returns the sum.
 *
 * SUM( [ RANGE | CELL | NUMERIC | STRING | BOOLEAN | EXPRESSION | *[ ; RANGE | CELL | NUMERIC | STRING | BOOLEAN | EXPRESSION ] ] ] )
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the parameters
 *
 * \details
 * Numbers, logical values, and text representations of numbers that you type directly into the list of arguments are counted.
 * Error values will abort the calculation and form the result if not part of an array (range or array).
 * Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_sum
interpreter_variant function_sum( function_parameter& parameters )
{
    internal::Sumf sum( parameters );
    try {
        for ( std::vector<interpreter_variant>::size_type i = 0; i < parameters.count(); i++ ) {
            sum( parameters[i] );
        }
    } catch ( const interpreter_variant& e ) {
        return e;
    }
    return interpreter_variant( variant( sum ) );
}
#endif

// alternate implementation that makes use of sparse arrays but doesn't handle
// all the edge cases as described in the "details" section of the sum function above!
/*
interpreter_variant function_sum( function_parameter& parameters n ) {

    typedef variant::sparse_array_type::mapping_type::value_type mapping_value_type;

    interpreter_variant return_value( variant::type_double );

    foreach( const interpreter_variant& v, parameters ) {
        if( v.is_array() ) {
            const variant::sparse_array_type& sparse_array( v.array() );
            namespace ba = boost::accumulators;
            return_value += sparse_array.default_value().numeric() * ( sparse_array.size() - sparse_array.direct().size() );
            return_value += ba::extract::sum( std::for_each(
                boost::make_transform_iterator( sparse_array.direct().begin(),
                boost::bind( &mapping_value_type::second, _1 ) ),
                boost::make_transform_iterator( sparse_array.direct().end(),
                boost::bind( &mapping_value_type::second, _1 ) ),
                ba::accumulator_set<variant, ba::features<ba::tag::sum> >() ) );
        } else {
            return_value += v;
        }
    }

    return return_value;
}
*/


/*!
 * \brief
 * Returns the sum of the squares of the arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the squares of the arguments
 *
 * \details
 * Numbers, logical values, and text representations of numbers that you type directly into the list of arguments are counted.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::SumSq
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumsq
interpreter_variant function_sumsq( function_parameter& parameters )
{
    internal::Sumsq sumsq( parameters );
    try {
        for ( std::vector<interpreter_variant>::size_type i = 0; i < parameters.count(); i++ ) {
            sumsq( parameters[i] );
        }
    } catch ( const interpreter_variant& e ) {
        return e;
    }
    return interpreter_variant( variant( sumsq ) );
}
#endif

/*!
 * \brief
 * Joins several text strings into one text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the joined text string
 *
 * \see
 * function_rept
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_concatenate
interpreter_variant function_concatenate( function_parameter& parameters )
{
    interpreter_variant result( variant( "" ) );
    for ( int i = 0; i < parameters.count(); i++ ) {
        interpreter_variant current = parameters[i];
        switch ( current.type() ) {
            case variant::type_empty:
                //assert( false );
                continue;
                break;

            case variant::type_double:
                result.as_string( parameters.context().locale() ).append( boost::lexical_cast<std::string>( current.numeric() ) );
                break;

            case variant::type_bool:
                result.as_string( parameters.context().locale() ).append( current.numeric() > 0 ? "TRUE" : "FALSE" );
                break;

            case variant::type_error:
                return current;
                //assert( false );

            case variant::type_string:
                result.as_string( parameters.context().locale() ).append( current.string() );
                break;

            case variant::type_array:
                //assert( false );
            {
                const variant::sparse_array_type& arr = current.array();
                switch ( static_cast<const variant&>( arr[0] ).type() ) {
                    case variant::type_double:
                        result.as_string( parameters.context().locale() ).append( boost::lexical_cast<std::string>( static_cast<const variant&>( arr[0] ).numeric() ) );
                        break;
                    case variant::type_bool:
                        result.as_string( parameters.context().locale() ).append( static_cast<const variant&>( arr[0] ).numeric() > 0 ? "TRUE" : "FALSE" );
                        break;
                    case variant::type_error:
                        return interpreter_variant( arr[0] );
                    case variant::type_string:
                        result.as_string( parameters.context().locale() ).append( static_cast<const variant&>( arr[0] ).string() );
                        break;
                    default:
                        continue;
                        break;
                }
            }
            break;

            default:
                continue;
                break;
        }
    }
    return result;
    // Joins several text strings into one text string.
    // The text items can be text strings, numbers, or single-cell references.
}
#endif

/*!
 * \brief
 * Multiplies corresponding components in the given arrays, and returns the sum of those products.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the products of the parameters
 *
 * \details
 *
 * \see
 * internal::Sum | function_mmult | function_product | function_sum
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumproduct
interpreter_variant function_sumproduct( function_parameter& parameters )
{
    if ( parameters.count() == 0 ) {
        return interpreter_variant( 0.0 );
    }
    // An array, in which all matrices are stored
    typedef std::vector<double> MatrixItem;
    std::vector<MatrixItem> MatrixList;
    interpreter_variant result( variant::type_double );

    // Sort parameters

    // All parameters must be matrices, return the #VALUE! error value if not.
    // Furthermore all matrices must have the same size, otherwise #VALUE! is returned.
    // If a value in the matrix is no number, it is treated as 0.
    unsigned int iSize = 0;
    boost::int_fast32_t columnWidth = 0;
    for ( int i = static_cast<int>( parameters.count() ) - 1; i >= 0; i-- ) {
        variant::sparse_array_type arr;
        if ( parameters[i].i_type() == interpreter_variant::type_range ) { // TODO: sparse
            range_reference& rref = range_reference_cast( parameters[i].reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned int imax = sra.size();
            unsigned int xmax = rref.actualize().position().row_count();
            arr = variant::sparse_array_type( imax );
            for ( unsigned int i1 = 0; i1 < imax; i1++ ) {
                arr[i1] = sra[i1];
            }

            if ( ( iSize != arr.size() && iSize != 0 ) || ( columnWidth != xmax && columnWidth != 0 ) ) {
                return interpreter_variant( variant::error_value );
            }
            iSize = arr.size();
            columnWidth = xmax;
        } else if ( parameters[i].type() == variant::type_array ) {
            arr = parameters[i].array();

            if ( ( iSize != arr.size() && iSize != 0 ) || ( columnWidth != parameters[i].column_width() && columnWidth != 0 ) ) {
                return interpreter_variant( variant::error_value );
            }
            iSize = arr.size();
            columnWidth = parameters[i].column_width();
        } else {
            return interpreter_variant( variant::error_value );
        }

        // As a trial write all values out
        MatrixItem myMatrix;
        for ( unsigned int x = 0; x < iSize; x++ ) {
            // error values cause errors.
            if ( static_cast<const variant&>( arr[x] ).type() == variant::type_error ) {
                return interpreter_variant( arr[x] );
            }

            if ( static_cast<const variant&>( arr[x] ).type() == variant::type_double ) {
                myMatrix.push_back( static_cast<const variant&>( arr[x] ).numeric() );
            } else {
                myMatrix.push_back( 0.0 );
            }
            //std::cout << ((*value.array)[x]) << "\n";
        }
        MatrixList.push_back( myMatrix );
    }

    // After we have all values, we can calculate
    // Go through the matrix list
    for ( int i = 0; i < static_cast<int>( MatrixList.size() ) - 1; i++ ) {
        // Treat each matrix in the list individually
        for ( unsigned int x = 0; x < MatrixList[i].size(); x++ ) {
            // Get the first value of the matrix and multiply it with the first value of the following matrix
            MatrixList[( i+1 )][x] = MatrixList[i][x] * MatrixList[( i+1 )][x];
        }
    }

    // After this calculation sum over the last matrix
    MatrixItem myItem = MatrixList[MatrixList.size()-1];
    for ( unsigned int i = 0; i < myItem.size(); i++ )  {
        result += myItem[i];
    }
    return result;
    // Multiplies corresponding components in the given arrays, and returns the sum of those products.
}
#endif

/*!
 * \brief
 * Returns a vertical range of cells as a horizontal range, or vice versa.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the transposed range
 *
 * \details
 * TRANSPOSE must be entered as an array formula in a range that has the same number
 * of rows and columns, respectively, as an array has columns and rows.
 *
 * \see
 * function_mdeterm | function_minverse | function_mmult
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_transpose
interpreter_variant function_transpose( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_ref );
    }
    interpreter_variant current = parameters[0];
    if ( current.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref = range_reference_cast( current.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int xmax = rref.actualize().position().column_count();
        unsigned int ymax = rref.actualize().position().row_count();
        variant::sparse_array_type resultArray( xmax * ymax );
        for ( unsigned int rowi = 0; rowi < xmax; rowi++ ) { // Fill the resultArray row by row.
            for ( unsigned coli = 0; coli < ymax; coli++ ) {
                resultArray.push_back( sra( rowi, coli ) );// resultArray by rows - original array by columns.
            }
        }
        variant result( resultArray, ymax );
        return interpreter_variant( result );
    } else if ( current.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = current.array();
        unsigned long int arraySize = arr.size();
        unsigned int columnWidth = current.column_width(); // the number of columns ( the length of a row )
        unsigned int rowWidth = arraySize / columnWidth; // the number of rows ( the length of a column )
        variant::sparse_array_type resultArray( arraySize );
        for ( unsigned int rowi = 0; rowi < columnWidth; rowi++ ) { // Fill the resultArray row by row.
            for ( unsigned int coli = 0; coli < rowWidth; coli++ ) {
                resultArray.push_back( arr[coli*columnWidth + rowi] ); // resultArray by rows - original array by columns.
            }
        }
        variant result( resultArray, rowWidth );
        return interpreter_variant( result );
    }
    return current;
}
#endif

/*!
 * \brief
 * Returns the matrix product of two arrays.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the matrix product of the two arrays
 *
 * \details
 * MMULT must be entered as an array formula in a range that has the same number
 * of rows as the first array and the same number of columns as the second array.
 * Select the range starting with the formula cell, press F2, and then press CTRL SHIFT ENTER together.
 *
 * \see
 * function_mdeterm | function_minverse | function_transpose
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mmult
interpreter_variant function_mmult( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant array1 = parameters[0];
    interpreter_variant array2 = parameters[1];
    variant::sparse_array_type arr1, arr2;
    if ( array1.i_type() == interpreter_variant::type_range || array1.type() == variant::type_array ) {
        unsigned int colWidth1;
        if ( array1.i_type() == interpreter_variant::type_range ) { // TODO: sparse
            range_reference& rref1 = range_reference_cast( array1.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            unsigned int imax1 = sra1.size();
            unsigned int xmax1 = rref1.actualize().position().column_count();
            arr1 = variant::sparse_array_type( imax1 );
            for ( unsigned int i = 0; i < imax1; i++ ) {
                arr1[i] = sra1[i];
            }
            colWidth1 = xmax1;
        } else {
            arr1 = array1.array();
            colWidth1 = array1.column_width();
        }
        unsigned int arraySize1 = arr1.size();
        unsigned int rows1 = arraySize1 / colWidth1;
        for ( unsigned int i1 = 0; i1 < arraySize1; i1++ ) {
            variant val1 = arr1[i1];
            // Error values cause errors.
            if ( val1.type() == variant::type_error ) {
                return interpreter_variant( val1 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( val1.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
        }
        if ( array2.i_type() == interpreter_variant::type_range || array2.type() == variant::type_array ) {
            unsigned int colWidth2;
            if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
                range_reference& rref2 = range_reference_cast( array2.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                unsigned int xmax2 = rref2.actualize().position().column_count();
                arr2 = variant::sparse_array_type( imax2 );
                for ( unsigned int i = 0; i < imax2; i++ ) {
                    arr2[i] = sra2[i];
                }
                colWidth2 = xmax2;
            } else {
                arr2 = array2.array();
                colWidth2 = array2.column_width();
            }
            unsigned int arraySize2 = arr2.size();
            unsigned int rows2 = arraySize2 / colWidth2;
            for ( unsigned int i2 = 0; i2 < arraySize2; i2++ ) {
                variant val2 = arr2[i2];
                // Error values cause errors.
                if ( val2.type() == variant::type_error ) {
                    return interpreter_variant( val2 );
                }
                // If any cell contains no number, MMULT returns the #VALUE! error value.
                if ( val2.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
            }
            // If the number of columns in array1 is different from the number of rows in array2, MMULT returns the #VALUE! error value.
            if ( colWidth1 != rows2 ) {
                return interpreter_variant( variant::error_value );
            }
            variant::sparse_array_type resultArray( rows1 * colWidth2 );
            for ( unsigned int i = 0; i < rows1; i++ ) {
                for ( unsigned int j = 0; j < colWidth2; j++ ) {
                    double sum = 0.0;
                    for ( unsigned int k = 0; k < colWidth1; k++ ) {
                        sum += static_cast<const variant&>( arr1[i*colWidth1+k] ).numeric() * static_cast<const variant&>( arr2[k*colWidth2+j] ).numeric();
                    }
                    resultArray.push_back( sum ); // Fill resultArray row by row.
                }
            }
            variant result( resultArray, colWidth2 );
            return interpreter_variant( result );
            // Returns the matrix product of the two arrays.
        } else {
            // Error values cause errors.
            if ( array2.type() == variant::type_error ) {
                return array2;
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( array2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }

            if ( arraySize1 != 1 ) {
                return interpreter_variant( variant::error_value );
            }
            variant content1 = arr1[0];
            // Error values cause errors.
            if ( content1.type() == variant::type_error ) {
                return interpreter_variant( content1 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( content1.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( content1.numeric() * array2.numeric() );
        }
    } else {
        // Error values cause errors.
        if ( array1.type() == variant::type_error ) {
            return array1;
        }
        // If any cell contains no number, MMULT returns the #VALUE! error value.
        if ( array1.type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }

        if ( array2.i_type() == interpreter_variant::type_range || array2.type() == variant::type_array ) {
            if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
                range_reference& rref2 = range_reference_cast( array2.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arr2 = variant::sparse_array_type( imax2 );
                for ( unsigned i = 0; i < imax2; i++ ) {
                    arr2[i] = sra2[i];
                }
            } else {
                arr2 = array2.array();
            }
            unsigned long int arraySize2 = arr2.size();
            if ( arraySize2 != 1 ) {
                return interpreter_variant( variant::error_value );
            }
            variant content2 = arr2[0];
            // Error values cause errors.
            if ( content2.type() == variant::type_error ) {
                return interpreter_variant( content2 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( content2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( array1.numeric() * content2.numeric() );
        } else {
            // Error values cause errors.
            if ( array2.type() == variant::type_error ) {
                return array1;
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( array2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( array1.numeric() * array2.numeric() );
        }
    }

    // making gcc happy for now; a design cleanup is required!
    return interpreter_variant( variant::error_value );
}
#endif

#ifdef lu_det
/** General matrix determinant.
 * It uses lu_factorize in uBLAS.
 * Helps to calculate function_mdeterm.
 */
template<class M>
double lu_det( M const& m )
{
    if ( m.size1() != m.size2() ) {
        throw "matrix is not quadratic";
    }

    // Create a working copy of the input.
    boost::numeric::ublas::matrix<double> mLu( m );
    boost::numeric::ublas::permutation_matrix<std::size_t> pivots( m.size1() );

    lu_factorize( mLu, pivots );

    double det = 1.0;

    for ( std::size_t i = 0; i < pivots.size(); ++i ) {
        if ( pivots( i ) != i ) {
            det *= -1.0;
        }
        det *= mLu( i, i );
    }
    return det;
}
#endif

/*!
 * \brief
 * Returns the matrix determinant of an array.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the matrix determinant of the argument
 *
 * \details
 *
 * \see
 * function_inverse | function_mmult | function_transpose
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mdeterm
interpreter_variant function_mdeterm( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant current = parameters[0];
    if ( current.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref = range_reference_cast( current.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int xmax = rref.actualize().position().column_count();
        unsigned int ymax = rref.actualize().position().row_count();
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( xmax != ymax ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( xmax, ymax );
        for ( unsigned int i = 0; i < xmax; i++ ) {
            for ( unsigned int j = 0; j < xmax; j++ ) {
                variant val = sra[xmax * i + j];
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric();
            }
        }
        try {
            return interpreter_variant( lu_det( m ) );
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value );
        }
    } else if ( current.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = current.array();
        boost::int_fast32_t arraySize = arr.size();
        boost::int_fast32_t columnWidth = current.column_width();
        boost::int_fast32_t rowWidth = arraySize / columnWidth;
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( columnWidth != rowWidth || arraySize % columnWidth != 0 ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( columnWidth, columnWidth );
        for ( boost::int_fast32_t i = 0; i < columnWidth; i++ ) {
            for ( boost::int_fast32_t j = 0; j < columnWidth; j++ ) {
                variant val = arr[columnWidth * i + j];
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric();
            }
        }
        try {
            return interpreter_variant( lu_det( m ) );
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value );
        }
    }
    // Error values cause errors.
    if ( current.type() == variant::type_error ) {
        return current;
    }
    // If any cell contains no number, MDETERM returns the #VALUE! error value.
    if ( current.type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return current;
}
#endif

#ifdef InvertMatrix
/** Matrix inversion routine.
 * Uses lu_factorize with pivotisation and lu_substitute in uBLAS to invert a matrix.
 * Helps to calcutate function_minverse.
 */
template<class T>
bool InvertMatrix( const boost::numeric::ublas::matrix<T>& input, boost::numeric::ublas::matrix<T>& inverse )
{
    if ( input.size1() != input.size2() ) {
        throw "matrix is not quadratic";
    }

    if ( inverse.size1() != input.size1() || inverse.size2() != input.size2() ) {
        throw "inverse matrix has invalid size";
    }

    // Create a working copy of the input.
    boost::numeric::ublas::matrix<T> A( input );

    // Create a permutation matrix for the LU-factorization.
    boost::numeric::ublas::permutation_matrix<std::size_t> pm( A.size1() );

    // Perform LU-factorization.
    int res = lu_factorize( A, pm );
    if ( res != 0 ) {
        return false;
    }

    // Create identity matrix of "inverse".
    inverse.assign( boost::numeric::ublas::identity_matrix<T>( A.size1() ) );

    // Backsubstitute to get the inverse.
    boost::numeric::ublas::lu_substitute( A, pm, inverse );

    return true;
}
#endif

/*!
 * \brief
 * Returns the inverse matrix of the argument.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse matrix of the argument
 *
 * \details
 * The argument matrix must be quadratic.
 * MINVERSE must be entered as an array formula in a range that has the same number
 * of rows and columns as the argument matrix.
 * Select the range starting with the formula cell, press F2, and then press CTRL SHIFT ENTER together.
 *
 * \see
 * function_index | function_mmult | function_transpose
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_minverse
interpreter_variant function_minverse( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant current = parameters[0];
    if ( current.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( current.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int xmax = rref.actualize().position().column_count();
        unsigned int ymax = rref.actualize().position().row_count();
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( xmax != ymax ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( xmax, xmax );
        boost::numeric::ublas::matrix<double> inv( xmax, xmax );
        for ( unsigned int i = 0; i < xmax; i++ ) {
            for ( unsigned int j = 0; j < xmax; j++ ) {
                variant val = sra[xmax * i + j]; // row i, column j.
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric(); // row i, column j.
            }
        }

        try {
            if ( !InvertMatrix( m, inv ) ) {
                return interpreter_variant( variant::error_num ); // m is singular.
            }
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value ); // number of rows and columns don't match.
        }
        variant::sparse_array_type resultArray( xmax * ymax );
        for ( unsigned i = 0; i < xmax; i++ ) {
            for ( unsigned j = 0; j < xmax; j++ ) {
                resultArray.push_back( variant( inv( i, j ) ) ); // Fill resultArray row by row.
            }
        }
        variant result( resultArray, xmax );
        return interpreter_variant( result );
        // Returns the inverse matrix of the argument.
    } else if ( current.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = current.array();
        boost::int_fast32_t arraySize = arr.size();
        boost::int_fast32_t columnWidth = current.column_width();
        boost::int_fast32_t rowWidth = arraySize / columnWidth;
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( columnWidth != rowWidth || arraySize % columnWidth != 0 ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( columnWidth, columnWidth );
        boost::numeric::ublas::matrix<double> inv( columnWidth, columnWidth );
        for ( boost::int_fast32_t i = 0; i < columnWidth; i++ ) {
            for ( boost::int_fast32_t j = 0; j < columnWidth; j++ ) {
                variant val = arr[columnWidth * i + j]; // row i, column j.
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric(); // row i, column j.
            }
        }

        try {
            if ( !InvertMatrix( m, inv ) ) {
                return interpreter_variant( variant::error_num ); // m is singular.
            }
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value ); // number of rows and columns don't match.
        }
        variant::sparse_array_type resultArray( arraySize );
        for ( boost::int_fast32_t i = 0; i < columnWidth; i++ ) {
            for ( boost::int_fast32_t j = 0; j < columnWidth; j++ ) {
                resultArray.push_back( variant( inv( i, j ) ) ); // Fill resultArray row by row.
            }
        }
        variant result( resultArray, columnWidth );
        return interpreter_variant( result );
        // Returns the inverse matrix of the argument.
    }
    // Error values cause errors.
    if ( current.type() == variant::type_error ) {
        return current;
    }
    // If any cell contains no number, MDETERM returns the #VALUE! error value.
    if ( current.type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    if ( current.numeric() == 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( 1.0 / current.numeric() ) );
}
#endif

/*!
 * \brief
 * Returns the largest value in a list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the largest value of the arguments
 *
 * \details
 * Arguments that are numbers, logical values, or text representations of numbers are counted.
 * Empty parameters are evaluated as 0, empty cells are ignored.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, numbers and logical values in that array or reference are used.
 * Empty cells are ignored. Text is evaluated as 0.
 * If the arguments contain no values, MAXA returns 0.
 *
 * \see
 * function_max | function_dmax
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_maxa
interpreter_variant function_maxa( function_parameter& parameters )
{
    internal::Maxa iMaxa( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            iMaxa( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    // If the arguments contain no numbers, MAXA returns 0.
    internal::MaxaStrategy::maxa_result result = iMaxa;
    if ( result.has_value ) {
        return interpreter_variant( variant( result.maxa ) );
    } else {
        return interpreter_variant( variant( 0.0 ) );
    }
}
#endif


/*!
 * \brief
 * Returns the smallest value in the list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * result of the calculation
 *
 * \details
 * Arguments that are numbers, logical values, or text representations of numbers are counted.
 * Empty parameters are evaluated as 0, empty cells are ignored.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, numbers and logical values in that array or reference are used.
 * Empty cells are ignored. Text is evaluated as 0.
 * If the arguments contain no values, MINA returns 0.
 *
 * \see
 * function_min | function_dmin
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mina
interpreter_variant function_mina( function_parameter& parameters )
{
    internal::Mina iMina( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            iMina( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    // If the arguments contain no numbers, MINA returns 0.
    internal::MinaStrategy::mina_result result = iMina;
    if ( result.has_value ) {
        return interpreter_variant( variant( result.mina ) );
    } else {
        return interpreter_variant( variant( 0.0 ) );
    }
}
#endif

/*!
 * \brief
 * Multiplies all the numbers given as arguments and returns the product.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the product of the arguments
 *
 * \details
 * Arguments that are numbers, logical values, or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an argument is an array or reference, only numbers in the array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::Product
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_product
interpreter_variant function_product( function_parameter& parameters )
{
    internal::Product product( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            product( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    return interpreter_variant( variant( product ) );
    // Multiplies all the numbers given as arguments and returns the product.
}
#endif

/*!
 * \brief
 * Returns the geometric mean of positive data, that is the n-th root of their product.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the geometric mean of the parameters
 *
 * \details
 * The arguments must be numbers, text representations of numbers, or arrays or references that contain numbers.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * internal::Product | internal::Counter | function_average | function_harmean | function_median | function_mode | function_trimmean
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_geomean
interpreter_variant function_geomean( function_parameter& parameters )
{
    internal::Geomean geomean( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            geomean( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::GeomeanStrategy::geomean_result res = geomean;
    // If there is no counted value, GEOMEAN returns the #NUM! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( pow( res.product, 1.0 / static_cast<double>( res.count ) ) ) );
    // Returns the geometric mean of positive data, that is the n-th root of their product.
}
#endif

/*!
 * \brief
 * Returns the harmonic mean of data.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the harmonic mean of the parameters
 *
 * \details
 * The harmonic mean is the reciprocal of the arithmetic mean of reciprocals.
 * Arguments must be numbers, or text that contains numbers, or arrays or references that contain numbers.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * function_average | function_geomean | function_median | function_mode | function_trimmean
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef funtion_harmean
interpreter_variant function_harmean( function_parameter& parameters )
{
    internal::Harmean harmean( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            harmean( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::HarmeanStrategy::harmean_result res = harmean;
    // If there is no counted value, HARMEAN returns the #N/A error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_n_a );
    }
    return interpreter_variant( variant( static_cast<double>( res.count ) / res.summe ) );
    // Returns the harmonic mean of a data set.
    // The harmonic mean is the reciprocal of the arithmetic mean of reciprocals.
}

#endif

/*!
 * \brief
 * Returns the sum of squares of deviations of data points from their sample mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of squared deviations
 *
 * \details
 * Arguments must be numbers, text that contain numbers, or arrays or references that contain numbers.
 * Empty cells are ignored. Empty parameters are evaluated as 0.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_avedev | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_devsq
interpreter_variant function_devsq( function_parameter& parameters )
{
    internal::Var var( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            var( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VarStrategy::var_result res = var;
    // If there is no counted value, DEVSQ returns the #NUM! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_num );
    }
    double result = res.sumsq - res.summe * res.summe / static_cast<double>( res.count );
    return interpreter_variant( variant( result ) );
    // Returns the sum of squares of deviations of data points from their sample mean.
}
#endif

/*!
 * \brief
 * Estimates variance based on a sample.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sample variance of the parameters
 *
 * \details
 * The variance is calculated using the unbiased "n-1" method.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_vara | function_varp | function_varpa | function_dvar | function_dvarp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_var
interpreter_variant function_var( function_parameter& parameters )
{
    internal::Var var( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            var( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VarStrategy::var_result res = var;
    // If there is one or no counted value, VAR returns the #DIV/0! error value.
    if ( res.count == 0 || res.count == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq - res.summe * res.summe / static_cast<double>( res.count );
    result = result / static_cast<double>( res.count - 1 ); // unbiased n-1 method for a sample of the population.
    return interpreter_variant( variant( result ) );
    // Estimates variance based on a sample.
    // The variance is a measure of how widely values are dispersed from the average value (the mean).
}
#endif


/*!
 * \brief
 * Estimates standard deviation based on a sample, including text and logical values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sample standard deviation of the parameters
 *
 * \details
 * The standard deviation is calculated using the unbiased "n-1" method.
 * Arguments that are numbers or logical values are counted. Text evaluates as 0.
 * Arguments that are error values cause errors.
 *
 * \see
 * internal::SumA | internal::SumSqA | internal::CounterA | function_stdev | function_stdevp | function_stdevpa | function_dstdev | function_dstdevp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_stdeva
interpreter_variant function_stdeva( function_parameter& parameters )
{
    internal::Vara vara( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            vara( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VaraStrategy::vara_result res = vara;
    // If there is one or no counted value, STDEVA returns the #DIV/0! error value.
    if ( res.count == 0 || res.count == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq - res.summe * res.summe / static_cast<double>( res.count );
    result = sqrt( result / static_cast<double>( res.count - 1 ) ); // unbiased n-1 method for a sample of the population.
    return interpreter_variant( variant( result ) );
    // Estimates standard deviation based on a sample.
    // The standard deviation is a measure of how widely values are dispersed from the average value (the mean).
    // Text and logical values such as TRUE and FALSE are included in the calculation.
}
#endif

/*!
 * \brief
 * Estimates variance based on a sample, including text and logical values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sample variance of the parameters
 *
 * \details
 * The variance is calculated using the unbiased "n-1" method.
 * Arguments that are numbers or logical values are counted. Text evaluates as 0.
 * Arguments that are error values cause errors.
 *
 * \see
 * internal::SumA | internal::SumSqA | internal::CounterA | function_var | function_varp | function_varpa | function_dvar | function_dvarp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_vara
interpreter_variant function_vara( function_parameter& parameters )
{
    internal::Vara vara( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            vara( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VaraStrategy::vara_result res = vara;
    // If there is one or no counted value, VARA returns the #DIV/0! error value.
    if ( res.count == 0 || res.count == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq - res.summe * res.summe / static_cast<double>( res.count );
    result = result / static_cast<double>( res.count - 1 ); // unbiased n-1 method for a sample of the population.
    return interpreter_variant( variant( result ) );
    // Estimates variance based on a sample.
    // The variance is a measure of how widely values are dispersed from the average value (the mean).
    // Text and logical values such as TRUE and FALSE are included in the calculation.
}
#endif


/*!
 * \brief
 * Calculates standard deviation based on the entire population given as arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the population standard deviation
 *
 * \details
 * The standard deviation is calculated using the biased "n" method.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_stdev | function_stdeva | function_stdevpa | function_dstdev
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_stdevp
interpreter_variant function_stdevp( function_parameter& parameters )
{
    internal::Var varp( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            varp( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VarStrategy::var_result res = varp;
    // If there is no counted value, STDEVP returns the #DIV/0! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq / static_cast<double>( res.count ) - pow( res.summe / static_cast<double>( res.count ), 2.0 );
    result = sqrt( result ); // biased n-method for the entire population.
    return interpreter_variant( variant( result ) );
    // Calculates standard deviation based on the entire population given as arguments.
    // The standard deviation is a measure of how widely values are dispersed from the average value (the mean).
}
#endif

/*!
 * \brief
 * Calculates variance based on the entire population given as arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the population variance
 *
 * \details
 * The variance is calculated using the biased "n" method.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are counted.
 * Empty cells, logical values, or text in the array or reference are ignored.
 *
 * \see
 * internal::Sum | internal::SumSq | internal::Counter | function_var | function_vara | function_varpa | function_dvar | function_dvarp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_varp
interpreter_variant function_varp( function_parameter& parameters )
{
    internal::Var varp( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            varp( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VarStrategy::var_result res = varp;
    // If there is no counted value, VARP returns the #DIV/0! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq / static_cast<double>( res.count ) - pow( res.summe / static_cast<double>( res.count ), 2.0 ); // biased n-method for the entire population.
    return interpreter_variant( variant( result ) );
    // Calculates variance based on the entire population given as arguments.
    // The variance is a measure of how widely values are dispersed from the average value (the mean).
}
#endif

/*!
 * \brief
 * Calculates standard deviation based on the entire population given as arguments, including text and logical values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the population standard deviation of the parameters
 *
 * \details
 * The standard deviation is calculated using the biased "n" method.
 * Arguments that are numbers or logical values are counted. Text evaluates as 0.
 * Arguments that are error values cause errors.
 *
 * \see
 * internal::SumA | internal::SumSqA | internal::CounterA | function_stdev | function_stdeva | function_stdevp | function_dstdev | function_dstdevp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_stdevpa
interpreter_variant function_stdevpa( function_parameter& parameters )
{
    internal::Vara varpa( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            varpa( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VaraStrategy::vara_result res = varpa;
    // If there is no counted value, STDEVPA returns the #DIV/0! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq / static_cast<double>( res.count ) - pow( res.summe / static_cast<double>( res.count ), 2.0 );
    result = sqrt( result ); // biased n-method for the entire population.
    return interpreter_variant( variant( result ) );
    // Calculates standard deviation based on the entire population given as arguments, including text and logical values.
    // The standard deviation is a measure of how widely values are dispersed from the average value (the mean).
    // Text and logical values such as TRUE and FALSE are included in the calculation.
}
#endif

/*!
 * \brief
 * Calculates variance based on the entire population given as arguments, including text and logical values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the population variance of the parameters
 *
 * \details
 * The variance is calculated using the biased "n" method.
 * Arguments that are numbers or logical values are counted. Text evaluates as 0.
 * Arguments that are error values cause errors.
 *
 * \see
 * internal::SumA | internal::SumSqA | internal::CounterA | function_var | function_vara | function_varp | function_dvar | function_dvarp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_varpa
interpreter_variant function_varpa( function_parameter& parameters )
{
    internal::Vara varpa( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            varpa( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::VaraStrategy::vara_result res = varpa;
    // If there is no counted value, VARPA returns the #DIV/0! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = res.sumsq / static_cast<double>( res.count ) - pow( res.summe / static_cast<double>( res.count ), 2.0 ); // biased n-method for the entire population.
    return interpreter_variant( variant( result ) );
    // Calculates variance based on the entire population given as arguments, including text and logical values.
    // The variance is a measure of how widely values are dispersed from the average value (the mean).
    // Text and logical values such as TRUE and FALSE are included in the calculation.
}
#endif

/*!
 * \brief
 * Returns the skewness of a distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the skewness
 *
 * \details
 * Skewness characterizes the degree of asymmetry of a distribution around its mean.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored;
 * only numbers are counted.
 *
 * \see
 * function_kurt | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_skew
interpreter_variant function_skew( function_parameter& parameters )
{
    double summe = 0.0;
    double sumsq = 0.0;
    double result = 0.0;
    std::vector<double> vx;
    unsigned long int i;
    for ( int p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned int arraySize = sra.size();
            for ( i = 0; i < arraySize; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }
                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    vx.push_back( currenti.numeric() );
                    summe += currenti.numeric();
                    sumsq += currenti.numeric() * currenti.numeric();
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                unsigned long int arraySize = arr.size();
                for ( i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        vx.push_back( currenti.numeric() );
                        summe += currenti.numeric();
                        sumsq += currenti.numeric() * currenti.numeric();
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try { // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    vx.push_back( currentd );
                    summe += currentd;
                    sumsq += currentd * currentd;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                vx.push_back( current.numeric() );
                summe += current.numeric();
                sumsq += current.numeric() * current.numeric();
            }
        }
    }
    unsigned long int count = vx.size();
    if ( count < 3 ) {
        // If there are fewer than 3 counted values, SKEW returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }
    double stdev = sqrt( ( sumsq - summe * summe / count ) / ( count - 1.0 ) );
    if ( stdev <= 0.0 ) {
        // If the sample standard deviation is zero, SKEW returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }

    for ( i = 0; i < count; i++ ) {
        result += pow( vx[i] - summe / count, 3.0 );
    }

    result = result * pow( stdev, -3.0 ) * count / ( count - 1.0 ) / ( count - 2.0 );
    return interpreter_variant( variant( result ) );
    // Returns the skewness of a distribution.
    // Skewness characterizes the degree of asymmetry of a distribution around its mean.
    // Positive skewness indicates a distribution with an asymmetric tail extending toward more positive values.
    // Negative skewness indicates a distribution with an asymmetric tail extending toward more negative values.
}
#endif

/*!
 * \brief
 * Returns the kurtosis of data.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the kurtosis
 *
 * \details
 * Kurtosis characterizes the relative peakedness or flatness of a distribution compared with the normal distribution.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored;
 * only numbers are counted.
 *
 * \see
 * function_skew | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_kurt
interpreter_variant function_kurt( function_parameter& parameters )
{
    double summe = 0.0;
    double sumsq = 0.0;
    double result = 0.0;
    std::vector<double> vx;
    unsigned long int i;
    for ( int p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned long int arraySize = sra.size();
            for ( i = 0; i < arraySize; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }
                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    vx.push_back( currenti.numeric() );
                    summe += currenti.numeric();
                    sumsq += currenti.numeric() * currenti.numeric();
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                unsigned long int arraySize = arr.size();
                for ( i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        vx.push_back( currenti.numeric() );
                        summe += currenti.numeric();
                        sumsq += currenti.numeric() * currenti.numeric();
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try { // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    vx.push_back( currentd );
                    summe += currentd;
                    sumsq += currentd * currentd;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                vx.push_back( current.numeric() );
                summe += current.numeric();
                sumsq += current.numeric() * current.numeric();
            }
        }
    }
    unsigned long int count = vx.size();
    if ( count < 4 ) {
        // If there are fewer than 4 counted values, KURT returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }
    double stdev = sqrt( ( sumsq - summe * summe / count ) / ( count - 1.0 ) );
    if ( stdev <= 0.0 ) {
        // If the sample standard deviation is zero, KURT returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }

    for ( i = 0; i < count; i++ ) {
        result += pow( vx[i] - summe / count, 4.0 );
    }

    result = result * pow( stdev, -4.0 ) * count * ( count + 1.0 ) / ( count - 1.0 ) / ( count - 2.0 ) / ( count - 3.0 );
    return interpreter_variant( variant( result ) );
    // Returns the kurtosis of a data set.
    // Kurtosis characterizes the relative peakedness or flatness of a distribution compared with the normal distribution.
    // Positive kurtosis indicates a relatively peaked distribution.
    // Negative kurtosis indicates a relatively flat distribution.
}
#endif

/*!
 * \brief
 * Returns the average of the absolute deviations of data points from their mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the average of the absolute deviations
 *
 * \details
 * The arguments must be numbers, logical values, or text that contains numbers, or arrays or references that contain numbers.
 * Empty cells are ignored. Empty parameters are evaluated as 0.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * function_average | function_devsq | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_avedev
interpreter_variant function_avedev( function_parameter& parameters )
{
    double summe = 0.0;
    double result = 0.0;
    std::vector<double> vx;
    unsigned long int i;
    for ( int p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned long int arraySize = sra.size();
            for ( i = 0; i < arraySize; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }
                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    vx.push_back( currenti.numeric() );
                    summe += currenti.numeric();
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                unsigned long int arraySize = arr.size();
                variant currenti;
                for ( i = 0; i < arraySize; i++ ) {
                    currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        vx.push_back( currenti.numeric() );
                        summe += currenti.numeric();
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try { // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    vx.push_back( currentd );
                    summe += currentd;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                vx.push_back( current.numeric() );
                summe += current.numeric();
            }
        }
    }
    unsigned long int count = vx.size();
    if ( count == 0 ) {
        // If there is no counted value, AVEDEV returns the #NUM! error value.
        return interpreter_variant( variant::error_num );
    }

    for ( i = 0; i < count; i++ ) {
        result += fabs( vx[i] - summe / count );
    }

    result = result / count;
    return interpreter_variant( variant( result ) );
    // Returns the average of the absolute deviations of data points from their mean.
    // AVEDEV is a measure of the variability in a data set.
}
#endif

/*!
 * \brief
 * Returns the first most frequently occurring, or repetitive, value in an array or range of data.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the first most frequently occurring, or repetitive, value
 *
 * \details
 * Arguments should be numbers. Error values cause errors.
 * Logical values or text or empty cells or empty parameters cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * function_average | function_geomean | function_harmean | function_median | function_trimmean
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mode
interpreter_variant function_mode( function_parameter& parameters )
{
    std::vector<double> numbers;
    for ( int p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned long int arraySize = sra.size();
            for ( unsigned long int i = 0; i < arraySize; i++ ) {
                variant currenti = sra[i];
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }
                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    numbers.push_back( currenti.numeric() );
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                unsigned long int arraySize = arr.size();
                for ( unsigned long int i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        numbers.push_back( currenti.numeric() );
                    }
                }
            } else if ( current.type() == variant::type_double ) {
                numbers.push_back( current.numeric() );
            } else {
                return interpreter_variant( variant::error_value );
            }
        }
    }
    std::vector<double> vx;
    std::vector<unsigned long int> vf; // absolute frequencies.
    for ( unsigned long int i = 0; i < numbers.size(); i++ ) {
        bool newNumber = true;
        for ( unsigned long int j = 0; j < vx.size(); j++ ) {
            if ( numbers[i] == vx[j] ) {
                newNumber = false;
                vf[j]++;
                break;
            }
        }

        if ( newNumber ) {
            vx.push_back( numbers[i] );
            vf.push_back( 1 );
        }
    }
    unsigned long int maxf = 0; // the maximum frequency.
    for ( unsigned long int i = 0; i < vf.size(); i++ ) {
        if ( vf[i] > maxf ) {
            maxf = vf[i];
        }
    }
    // If the data set contains no duplicate data points, MODE returns the #N/A error value.
    if ( maxf == 0 || maxf == 1 ) {
        return interpreter_variant( variant::error_n_a );
    }

    for ( unsigned long int i = 0; i < vf.size(); i++ ) {
        if ( vf[i] == maxf ) {
            // MODE returns the first most frequently value.
            return interpreter_variant( variant( vx[i] ) );
        }
    }
    return interpreter_variant( variant::error_n_a );
    // Returns the first most frequently occurring, or repetitive, value in an array or range of data.
    // MODE is a location measure.
}
#endif

/*!
 * \brief
 * Returns covariance, the average of the products of deviations for each data point pair.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the covariance
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_correl | function_fisher | function_fisherinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_covar
interpreter_variant function_covar( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant array1 = parameters[1]; // a cell range of values.
    if ( array1.i_type() != interpreter_variant::type_range && array1.type() != variant::type_array ) {
        return interpreter_variant( variant::error_n_a );
    }
    variant::sparse_array_type arrx, arry;
    unsigned long int arraySize;
    if ( array1.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = array1.array();
    }
    arraySize = arrx.size();
    interpreter_variant array2 = parameters[0]; // another cell range of values.
    if ( array2.i_type() != interpreter_variant::type_range && array2.type() != variant::type_array ) {
        return interpreter_variant( variant::error_n_a );
    }

    if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref2 = range_reference_cast( array2.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = array2.array();
    }
    // If array1 and array2 have a different number of data points, COVAR returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of array1.
    double sumy = 0.0; // the sum of the data of array2.
    double sumxy = 0.0; // the sum of the products of corresponding data of array1 and array2.
    unsigned long int counter = 0; // the number of the proper pairs of data of array1 and array2.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumy += yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is no counted value-pair, COVAR returns the #DIV/0! error value.
    if ( counter == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double result = sumxy - sumx * sumy / counter;
    result = result / counter;
    return interpreter_variant( variant( result ) );
    // Returns covariance, the average of the products of deviations for each data point pair.
    // Use the covariance to determine the relationship between two data sets.
}
#endif

/*!
 * \brief
 * Returns the correlation coefficient of the array1 and array2 cell ranges.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the correlation coefficient
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_covar | function_fisher | function_fisherinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_correl
interpreter_variant function_correl( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant array1 = parameters[1]; // a cell range of values or an array.
    if ( array1.i_type() != interpreter_variant::type_range && array1.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( array1.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = array1.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant array2 = parameters[0]; // another cell range of values or an array.
    if ( array2.i_type() != interpreter_variant::type_range && array2.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    if ( array2.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( array2.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = array2.array();
    }
    // If array1 and array2 have a different number of data points, CORREL returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of array1.
    double sumx2 = 0.0; // the sum of the squares of the data of array1.
    double sumy = 0.0; // the sum of the data of array2.
    double sumy2 = 0.0; // the sum of the squares of the data of array2.
    double sumxy = 0.0; // the sum of the products of corresponding data of array1 and array2.
    unsigned long int counter = 0; // the number of the proper pairs of data of array1 and array2.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumy2 += yi.numeric() * yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, CORREL returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    double sy = sumy2 - sumy * sumy / counter;
    // If any standard deviation equals zero, CORREL returns the #DIV/0! error value.
    if ( sx <= 0.0 || sy <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = sumxy - sumx * sumy / counter;
    result = result / sqrt( sx * sy );
    return interpreter_variant( variant( result ) );
    // Returns the correlation coefficient of the array1 and array2 cell ranges.
    // Use the correlation coefficient to determine the relationship between two properties.
}
#endif

/*!
 * \brief
 * Returns the square of the Pearson product moment correlation coefficient through data points of the array1 and array2 cell ranges.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the square of the Pearson product moment correlation coefficient
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_correl | function_covar | function_intercept | function_linest | function_logest | function_slope | function_steyx | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_rsq
interpreter_variant function_rsq( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant array1 = parameters[1]; // a cell range of values or an array.
    if ( array1.i_type() != interpreter_variant::type_range && array1.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( array1.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = array1.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant array2 = parameters[0]; // another cell range of values or an array.
    if ( array2.i_type() != interpreter_variant::type_range && array2.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    if ( array2.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( array2.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = array2.array();
    }
    // If array1 and array2 have a different number of data points, RSQ returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of array1.
    double sumx2 = 0.0; // the sum of the squares of the data of array1.
    double sumy = 0.0; // the sum of the data of array2.
    double sumy2 = 0.0; // the sum of the squares of the data of array2.
    double sumxy = 0.0; // the sum of the products of corresponding data of array1 and array2.
    unsigned long int counter = 0; // the number of the proper pairs of data of array1 and array2.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumy2 += yi.numeric() * yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, RSQ returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    double sy = sumy2 - sumy * sumy / counter;
    // If any variance equals zero, RSQ returns the #DIV/0! error value.
    if ( sx <= 0.0 || sy <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = sumxy - sumx * sumy / counter;
    result = result * result / sx / sy;
    return interpreter_variant( variant( result ) );
    // Returns the square of the Pearson product moment correlation coefficient
    // through data points of the array1 and array2 cell ranges.
}
#endif

/*!
 * \brief
 * Returns the slope of the linear regression line through data points in known_ys and known_xs.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the slope of the linear regression line
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_intercept | function_linest | function_logest | function_rsq | function_steyx | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_slope
interpreter_variant function_slope( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant known_xs = parameters[1]; // a cell range of values or an array.
    if ( known_xs.i_type() != interpreter_variant::type_range && known_xs.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( known_xs.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( known_xs.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = known_xs.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant known_ys = parameters[0]; // another cell range of values or an array.
    if ( known_ys.i_type() != interpreter_variant::type_range && known_ys.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    if ( known_ys.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( known_ys.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = known_ys.array();
    }
    // If known_xs and known_ys have a different number of data points, SLOPE returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of known_xs.
    double sumx2 = 0.0; // the sum of the squares of the data of known_xs.
    double sumy = 0.0; // the sum of the data of known_ys.
    double sumxy = 0.0; // the sum of the products of corresponding data of known_xs and known_ys.
    unsigned long int counter = 0; // the number of the proper pairs of data of known_xs and known_ys.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, SLOPE returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    // If the standard deviation equals zero, SLOPE returns the #DIV/0! error value.
    if ( sx <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = ( sumxy - sumx * sumy / counter ) / sx;
    return interpreter_variant( variant( result ) );
    // Returns the slope of the linear regression line through data points in known_ys and known_xs.
    // The slope is the vertical distance divided by the horizontal distance between any two points
    // on the line, which is the rate of change along the regression line.
}
#endif


/*!
 * \brief
 * Calculates the point at which a line will intersect the y-axis by using existing x-values and y-values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the intercept of the linear regression line
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_forecast | function_growth | function_linest | function_logest | function_rsq | function slope | function_steyx | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_intercept
interpreter_variant function_intercept( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant known_xs = parameters[1]; // a cell range of values or an array.
    if ( known_xs.i_type() != interpreter_variant::type_range && known_xs.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( known_xs.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( known_xs.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = known_xs.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant known_ys = parameters[0]; // another cell range of values or an array.
    if ( known_ys.i_type() != interpreter_variant::type_range && known_ys.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    if ( known_ys.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( known_ys.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = known_ys.array();
    }
    // If known_xs and known_ys have a different number of data points, INTERCEPT returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of known_xs.
    double sumx2 = 0.0; // the sum of the squares of the data of known_xs.
    double sumy = 0.0; // the sum of the data of known_ys.
    double sumxy = 0.0; // the sum of the products of corresponding data of known_xs and known_ys.
    unsigned long int counter = 0; // the number of the proper pairs of data of known_xs and known_ys.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, INTERCEPT returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    // If the standard deviation equals zero, INTERCEPT returns the #DIV/0! error value.
    if ( sx <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double slope = ( sumxy - sumx * sumy / counter ) / sx; // the slope of the linear regression line.
    double result = sumy / counter - slope * sumx / counter;
    return interpreter_variant( variant( result ) );
    // Calculates the point at which a line will intersect the y-axis by using existing x-values and y-values.
    // The intercept point is based on the best-fit regression line plotted through the known x-values and known y-values.
    // Use the INTERCEPT function, when you want to determine the value of the dependent variable when the independent variable is 0.
}
#endif

/*!
 * \brief
 * Returns the standard error of the predicted y-value for each x in the regression.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the standard error of the predicted y-value
 *
 * \details
 * The arguments must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_forecast | function_intercept | function_linest | function_logest | function_rsq | function_slope
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_steyx
interpreter_variant function_steyx( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant known_xs = parameters[1]; // a cell range of values or an array.
    if ( known_xs.i_type() != interpreter_variant::type_range && known_xs.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( known_xs.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( known_xs.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = known_xs.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant known_ys = parameters[0]; // another cell range of values or an array.
    if ( known_ys.i_type() != interpreter_variant::type_range && known_ys.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    if ( known_ys.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( known_ys.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = known_ys.array();
    }
    // If known_xs and known_ys have a different number of data points, STEYX returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    double sumx = 0.0; // the sum of the data of known_xs.
    double sumx2 = 0.0; // the sum of the squares of the data of known_xs.
    double sumy = 0.0; // the sum of the data of known_ys.
    double sumy2 = 0.0; // the sum of the squares of the data of known_ys.
    double sumxy = 0.0; // the sum of the products of corresponding data of known_xs and known_ys.
    unsigned long int counter = 0; // the number of the proper pairs of data of known_xs and known_ys.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumy2 += yi.numeric() * yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there are fewer than 3 counted value-pair, STEYX returns the #DIV/0! error value.
    if ( counter < 3 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    // If the standard deviation equals zero, STEYX returns the #DIV/0! error value.
    if ( sx <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double result = sumy2 - sumy * sumy / counter;
    result -= pow( sumxy - sumx * sumy / counter, 2.0 ) / sx;
    return interpreter_variant( variant( sqrt( result / ( counter - 2.0 ) ) ) );
    // Returns the standard error of the predicted y-value for each x in the regression.
    // The standard error is a measure of the amount of error in the prediction of y for an individual x.
}
#endif


/*!
 * \brief
 * Calculates, or predicts, a future value by using linear regression through existing values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the predicted value is a y-value for a given x-value
 *
 * \details
 * The known values must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_growth | function_linest | function_logest | function_slope | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_forecast
interpreter_variant function_forecast( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant known_xs = parameters[2]; // a cell range of values or an array.
    if ( known_xs.i_type() != interpreter_variant::type_range && known_xs.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( known_xs.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( known_xs.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = known_xs.array();
    }
    unsigned long int arraySize = arrx.size();
    interpreter_variant known_ys = parameters[1]; // another cell range of values or an array.
    if ( known_ys.i_type() != interpreter_variant::type_range && known_ys.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    if ( known_ys.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( known_ys.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = known_ys.array();
    }
    // If known_xs and known_ys have a different number of data points, INTERCEPT returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant given_xValue = parameters[0];
    double given_x = 0.0;
    // error values cause errors.
    if ( given_xValue.type() == variant::type_error ) {
        return given_xValue;
    }

    if ( given_xValue.type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            given_x = boost::lexical_cast<double>( static_cast<const std::string&>( given_xValue.string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        given_x = given_xValue.numeric();
    }
    double sumx = 0.0; // the sum of the data of known_xs.
    double sumx2 = 0.0; // the sum of the squares of the data of known_xs.
    double sumy = 0.0; // the sum of the data of known_ys.
    double sumxy = 0.0; // the sum of the products of corresponding data of known_xs and known_ys.
    unsigned long int counter = 0; // the number of the proper pairs of data of known_xs and known_ys.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, INTERCEPT returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    // If the standard deviation equals zero, INTERCEPT returns the #DIV/0! error value.
    if ( sx <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double slope = ( sumxy - sumx * sumy / counter ) / sx; // the slope of the linear regression line.
    double intercept = sumy / counter - slope * sumx / counter;
    double result = intercept + slope * given_x;
    return interpreter_variant( variant( result ) );
    // Calculates, or predicts, a future value by using linear regression through existing values.
    // The predicted value is a y-value for a given x-value.
    // The known values are existing x-values and y-values, and the new value is predicted by using linear regression.
}
#endif

/*!
 * \brief
 * Calculates the statistics for the linear regression by using the "least squares" method.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * an array containing the statistics of the linear regression
 *
 * \details
 * Must be entered as an array formula (CTRL SHIFT ENTER).
 * With the third parameter you can force the intercept to equal zero.
 *
 * \see
 * function_forecast | function_growth | function_logest | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*interpreter_variant function_linest( calculation_context& cx, unsigned int param )
{
internal::ParameterList parameters( cx, param );

bool bConst = true; // If TRUE or omitted, the intercept is calculated normally.
// If FALSE, the intercept is forced to equal zero.
if ( parameters.size() > 2 && parameters[2].type() != variant::type_empty ) {
bConst = static_cast<bool>( parameters[2].numeric() );
}
bool stats = false; // If FALSE or omitted, only the coefficients and the intercept are returned.
// If TRUE, all regression statistics are returned.
if ( parameters.size() > 3 ) {
stats = static_cast<bool>( parameters[3].numeric() );
}

std::vector<double> ys;
int n; // the number of data points
boost::int_fast32_t yColumnWidth;
boost::int_fast32_t yRowWidth;
bool inColumns = true; // Data are in columns.
double b = 0.0; // the intercept
variant seb = variant::error_n_a; // the standard error for the intercept
double r2 = 1.0; // the coefficient of determination
double sey = 0.0; // the standard error for the y estimate
variant F = variant::error_num; // the F-value
long long df = 0; // the degrees of freedom
double ssreg = 0.0; // the regression sum of squares
double ssresid = 0.0; // the residual sum of squares

// Read in known_y's out of parameters[0].
if ( parameters[0].i_type() == interpreter_variant::type_range ) {
const variant& value = static_cast<range*>( parameters[0].reference() )->get_value( cx );
n = ( *value.array ).size();
yColumnWidth = value.column_width();
yRowWidth = n / yColumnWidth;
if ( yColumnWidth > 1 && yRowWidth > 1 ) {
return interpreter_variant( variant::error_ref );
}
if ( yColumnWidth > 1 ) {
inColumns = false; // Data are in rows.
}
variant vali;
for ( boost::int_fast32_t i = 0; i < n; i++ ) {
vali = ( *value.array )[i];
if ( vali.type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}
ys.push_back( vali.numeric() );
}
} else {
if ( parameters[0].type() == variant::type_error ) {
return parameters[0];
}

if ( parameters[0].type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}
n = 1;
yColumnWidth = 1;
yRowWidth = 1;
ys.push_back( parameters[0].numeric() );
}

std::vector<std::vector<double> > xs;
boost::int_fast32_t xArraySize;
boost::int_fast32_t xColumnWidth;
boost::int_fast32_t xRowWidth;

// Read in known_x's out of parameters[1].
if ( parameters.size() < 2 || parameters[1].type() == variant::type_empty ) {
for ( boost::int_fast32_t i = 0; i < n; i++ ) {
std::vector<double> v;
v.push_back( static_cast<double>( i ) );
xs.push_back( v );
}
} else if ( parameters[1].i_type() == interpreter_variant::type_range ) {
const variant& value = static_cast<range*>( parameters[1].reference() )->get_value( cx );
xArraySize = ( *value.array ).size();
xColumnWidth = value.column_width();
xRowWidth = xArraySize / xColumnWidth;
if ( inColumns ) {
if ( yRowWidth != xRowWidth && n > 1 ) {
return interpreter_variant( variant::error_ref );
}
} else {
if ( yColumnWidth != xColumnWidth && n > 1 ) {
return interpreter_variant( variant::error_ref );
}
}

if ( n == 1 && xColumnWidth > 1 && xRowWidth > 1 ) {
return interpreter_variant( variant::error_ref );
}

variant val;
if ( n == 1 ) {
for ( boost::int_fast32_t i = 0; i < xArraySize; i++ ) {
val = ( *value.array )[i];
if ( val.type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}
std::vector<double> v;
v.push_back( val.numeric() );
xs.push_back( v );
}
} else {
if ( inColumns ) {
for ( boost::int_fast32_t i = 0; i < xColumnWidth; i++ ) {
std::vector<double> v;
for ( boost::int_fast32_t j = 0; j < xRowWidth; j++ ) {
val = ( *value.array )[i*xColumnWidth+j];
if ( val.type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}
v.push_back( val.numeric() );
}
xs.push_back( v );
}
} else {
for ( boost::int_fast32_t i = 0; i < xRowWidth; i++ ) {
std::vector<double> v;
for ( boost::int_fast32_t j = 0; j < xColumnWidth; j++ ) {
val = ( *value.array )[i*xRowWidth+j];
if ( val.type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}
v.push_back( val.numeric() );
}
xs.push_back( v );
}
}
}
} else {
if ( parameters[1].type() == variant::type_error ) {
return parameters[1];
}

if ( parameters[1].type() != variant::type_double ) {
return interpreter_variant( variant::error_value );
}

if ( n > 1 ) {
return interpreter_variant( variant::error_ref );
}
std::vector<double> v;
v.push_back( parameters[1].numeric() );
xs.push_back( v );
}

// Calculate the coefficients.



return interpreter_variant( 0.0 );
}*/


/*!
 * \brief
 * Returns values along a linear trend.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the y-values along that line for the array of new_x's that you specify
 *
 * \details
 * Fits a straight line (using the method of least squares) to the arrays known_y's and known_x's.
 * With the fourth parameter you can force the intercept to equal zero.
 *
 * \see
 * function_forecast | function_growth | function_linest | function_logest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_trend( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    bool bConst = true; // If TRUE or omitted, the intercept is calculated normally.
    // If FALSE, the intercept is forced to equal zero.
    if ( parameters.count() > 3 ) {
        bConst = parameters[3].numeric() != 0.0;
    }

    return interpreter_variant( 0.0 );
}


/*!
 * \brief
 * Returns the sum of the sum of squares of corresponding values in two arrays.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the sum of squares
 *
 * \details
 * If an array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 *
 * \see
 * function_sumx2my2 | function_sumxmy2
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumx2py2
interpreter_variant function_sumx2py2( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant array_x = parameters[0];
    interpreter_variant array_y = parameters[1];
    variant::sparse_array_type arrx, arry;
    double result = 0.0;
    if ( array_x.i_type() == interpreter_variant::type_range || array_x.type() == variant::type_array ) {
        if ( array_x.i_type() == interpreter_variant::type_range ) {
            range_reference& rref1 = range_reference_cast( array_x.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            unsigned int imax1 = sra1.size();
            arrx = variant::sparse_array_type( imax1 );
            for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
                arrx[i1] = sra1[i1];
            }
        } else {
            arrx = array_x.array();
        }
        unsigned long int array_xSize = arrx.size();
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            // If array_x and array_y have a different number of values, SUMX2PY2 returns the #N/A error value.
            if ( array_xSize != array_ySize ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                variant y0 = arry[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( x0.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( x0.numeric() * x0.numeric() + y0.numeric() * y0.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                unsigned long int counter = 0;
                for ( unsigned long int i = 0; i < array_xSize; i++ ) {
                    variant xi = arrx[i];
                    variant yi = arry[i];
                    // error values cause errors.
                    if ( xi.type() == variant::type_error ) {
                        return interpreter_variant( xi );
                    }

                    if ( yi.type() == variant::type_error ) {
                        return interpreter_variant( yi );
                    }
                    // If an array or reference argument contains text, logical values, or empty cells,
                    // those value-pairs are ignored.
                    if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
                        result += xi.numeric() * xi.numeric() + yi.numeric() * yi.numeric();
                        counter++;
                    }
                }
                if ( counter == 0 ) {
                    return interpreter_variant( variant::error_div_null );
                } else {
                    return interpreter_variant( variant( result ) );
                }
            }
        } else { // x is RANGE, array_y not.
            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( array_y.type() == variant::type_error ) {
                    return array_y;
                }

                if ( x0.type() == variant::type_double && array_y.type() == variant::type_double ) {
                    return interpreter_variant( variant( x0.numeric() * x0.numeric() + array_y.numeric() * array_y.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        }
    } else { // array_x is no RANGE.
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            if ( array_ySize == 1 ) {
                variant y0 = arry[0];
                // error values cause errors.
                if ( array_x.type() == variant::type_error ) {
                    return array_x;
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( array_x.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( array_x.numeric() * array_x.numeric() + y0.numeric() * y0.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        } else { // array_x and array_y are no RANGE.
            // error values cause errors.
            if ( array_x.type() == variant::type_error ) {
                return array_x;
            }

            if ( array_y.type() == variant::type_error ) {
                return array_y;
            }

            if ( array_x.type() == variant::type_double && array_y.type() == variant::type_double ) {
                return interpreter_variant( variant( array_x.numeric() * array_x.numeric() + array_y.numeric() * array_y.numeric() ) );
            } else {
                return interpreter_variant( variant::error_value );
            }
        }
    }
    // Returns the sum of the sum of squares of corresponding values in two arrays.

    // making gcc happy for now; a design cleanup is required!
    return interpreter_variant( variant::error_value );
}
#endif

/*!
 * \brief
 * Returns the sum of the difference of squares of corresponding values in two arrays.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the difference of squares
 *
 * \details
 * If an array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 *
 * \see
 * function_sumx2py2 | function_sumxmy2
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumx2my2
interpreter_variant function_sumx2my2( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant array_x = parameters[0];
    interpreter_variant array_y = parameters[1];
    variant::sparse_array_type arrx, arry;
    double result = 0.0;
    if ( array_x.i_type() == interpreter_variant::type_range || array_x.type() == variant::type_array ) {
        if ( array_x.i_type() == interpreter_variant::type_range ) {
            range_reference& rref1 = range_reference_cast( array_x.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            unsigned int imax1 = sra1.size();
            arrx = variant::sparse_array_type( imax1 );
            for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
                arrx[i1] = sra1[i1];
            }
        } else {
            arrx = array_x.array();
        }
        unsigned long int array_xSize = arrx.size();
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            // If array_x and array_y have a different number of values, SUMX2MY2 returns the #N/A error value.
            if ( array_xSize != array_ySize ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                variant y0 = arry[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( x0.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( x0.numeric() * x0.numeric() - y0.numeric() * y0.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                unsigned long int counter = 0;
                for ( unsigned long int i = 0; i < array_xSize; i++ ) {
                    variant xi = arrx[i];
                    variant yi = arry[i];
                    // error values cause errors.
                    if ( xi.type() == variant::type_error ) {
                        return interpreter_variant( xi );
                    }

                    if ( yi.type() == variant::type_error ) {
                        return interpreter_variant( yi );
                    }
                    // If an array or reference argument contains text, logical values, or empty cells,
                    // those value-pairs are ignored.
                    if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
                        result += xi.numeric() * xi.numeric() - yi.numeric() * yi.numeric();
                        counter++;
                    }
                }

                if ( counter == 0 ) {
                    return interpreter_variant( variant::error_div_null );
                } else {
                    return interpreter_variant( variant( result ) );
                }
            }
        } else { // x is RANGE, array_y not.
            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( array_y.type() == variant::type_error ) {
                    return array_y;
                }

                if ( x0.type() == variant::type_double && array_y.type() == variant::type_double ) {
                    return interpreter_variant( variant( x0.numeric() * x0.numeric() - array_y.numeric() * array_y.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        }
    } else { // array_x is no RANGE.
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            if ( array_ySize == 1 ) {
                variant y0 = arry[0];
                // error values cause errors.
                if ( array_x.type() == variant::type_error ) {
                    return array_x;
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( array_x.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( array_x.numeric() * array_x.numeric() - y0.numeric() * y0.numeric() ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        } else { // array_x and array_y are no RANGE.
            // error values cause errors.
            if ( array_x.type() == variant::type_error ) {
                return array_x;
            }

            if ( array_y.type() == variant::type_error ) {
                return array_y;
            }

            if ( array_x.type() == variant::type_double && array_y.type() == variant::type_double ) {
                return interpreter_variant( variant( array_x.numeric() * array_x.numeric() - array_y.numeric() * array_y.numeric() ) );
            } else {
                return interpreter_variant( variant::error_value );
            }
        }
    }
    // Returns the sum of the difference of squares of corresponding values in two arrays.

    // making gcc happy for now; a design cleanup is required!
    return interpreter_variant( variant::error_value );
}
#endif


/*!
 * \brief
 * Returns the sum of squares of the differences of corresponding values in two arrays.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of squares of the differences
 *
 * \details
 * If an array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 *
 * \see
 * function_sumx2py2 | function_sumx2my2
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumxmy2
interpreter_variant function_sumxmy2( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant array_x = parameters[0];
    interpreter_variant array_y = parameters[1];
    variant::sparse_array_type arrx, arry;
    double result = 0.0;
    if ( array_x.i_type() == interpreter_variant::type_range || array_x.type() == variant::type_array ) {
        if ( array_x.i_type() == interpreter_variant::type_range ) {
            range_reference& rref1 = range_reference_cast( array_x.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            unsigned int imax1 = sra1.size();
            arrx = variant::sparse_array_type( imax1 );
            for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
                arrx[i1] = sra1[i1];
            }
        } else {
            arrx = array_x.array();
        }
        unsigned long int array_xSize = arrx.size();
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            // If array_x and array_y have a different number of values, SUMXMY2 returns the #N/A error value.
            if ( array_xSize != array_ySize ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                variant y0 = arry[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( x0.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( pow( x0.numeric() - y0.numeric(), 2.0 ) ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                for ( unsigned long int i = 0; i < array_xSize; i++ ) {
                    variant xi = arrx[i];
                    variant yi = arry[i];
                    // error values cause errors.
                    if ( xi.type() == variant::type_error ) {
                        return interpreter_variant( xi );
                    }

                    if ( yi.type() == variant::type_error ) {
                        return interpreter_variant( yi );
                    }
                    // If an array or reference argument contains text, logical values, or empty cells,
                    // those value-pairs are ignored.
                    if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
                        result += pow( xi.numeric() - yi.numeric(), 2.0 );
                    }
                }
                return interpreter_variant( variant( result ) );
            }
        } else { // x is RANGE, array_y not.
            if ( array_xSize == 1 ) {
                variant x0 = arrx[0];
                // error values cause errors.
                if ( x0.type() == variant::type_error ) {
                    return interpreter_variant( x0 );
                }

                if ( array_y.type() == variant::type_error ) {
                    return array_y;
                }

                if ( x0.type() == variant::type_double && array_y.type() == variant::type_double ) {
                    return interpreter_variant( variant( pow( x0.numeric() - array_y.numeric(), 2.0 ) ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        }
    } else { // array_x is no RANGE.
        if ( array_y.i_type() == interpreter_variant::type_range || array_y.type() == variant::type_array ) {
            if ( array_y.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( array_y.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                arry = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    arry[i2] = sra2[i2];
                }
            } else {
                arry = array_y.array();
            }
            unsigned long int array_ySize = arry.size();
            if ( array_ySize == 1 ) {
                variant y0 = arry[0];
                // error values cause errors.
                if ( array_x.type() == variant::type_error ) {
                    return array_x;
                }

                if ( y0.type() == variant::type_error ) {
                    return interpreter_variant( y0 );
                }

                if ( array_x.type() == variant::type_double && y0.type() == variant::type_double ) {
                    return interpreter_variant( variant( pow( array_x.numeric() - y0.numeric(), 2.0 ) ) );
                } else {
                    return interpreter_variant( variant::error_value );
                }
            } else {
                return interpreter_variant( variant::error_n_a );
            }
        } else { // array_x and array_y are no RANGE.
            // error values cause errors.
            if ( array_x.type() == variant::type_error ) {
                return array_x;
            }

            if ( array_y.type() == variant::type_error ) {
                return array_y;
            }

            if ( array_x.type() == variant::type_double && array_y.type() == variant::type_double ) {
                return interpreter_variant( variant( pow( array_x.numeric() - array_y.numeric(), 2.0 ) ) );
            } else {
                return interpreter_variant( variant::error_value );
            }
        }
    }
    // Returns the sum of squares of the differences of corresponding values in two arrays.

    // making gcc happy for now; a design cleanup is required!
    return interpreter_variant( variant::error_value );
}

#endif

/*!
 * \brief
 * Returns the probability that values in a range are between two limits.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * result of the calculation
 *
 * \details
 * If upper_limit is not supplied, PROB returns the probability that values in x_range are equal to lower_limit.
 *
 * \see
 * function_binomdist | function_critbinom
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_prob
interpreter_variant function_prob( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant x_range = parameters[0]; // the range of numeric values of x with which there are associated probabilities.
    interpreter_variant prob_range = parameters[1]; // a set of probabilities associated with values in x_range.
    double lower_limit = parameters[2].numeric(); // the lower bound on the value for which you want a probability.
    double upper_limit = lower_limit; // the optional upper bound on the value for which you want a probability.
    if ( parameters.count() > 3 ) {
        upper_limit = parameters[3].numeric();
    }

    if ( lower_limit > upper_limit ) {
        return interpreter_variant( variant( 0.0 ) );
    }
    double sum = 0.0; // the sum of the probabilities.
    double result = 0.0;
    if ( x_range.i_type() == interpreter_variant::type_range || x_range.type() == variant::type_array ) {
        variant::sparse_array_type x_arr;
        if ( x_range.i_type() == interpreter_variant::type_range ) {
            range_reference& rref1 = range_reference_cast( x_range.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            unsigned int imax1 = sra1.size();
            x_arr = variant::sparse_array_type( imax1 );
            for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
                x_arr[i1] = sra1[i1];
            }
        } else {
            x_arr = x_range.array();
        }
        unsigned long int arraySize = x_arr.size();
        if ( prob_range.i_type() == interpreter_variant::type_range || prob_range.type() == variant::type_array ) {
            variant::sparse_array_type prob_arr;
            if ( prob_range.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( prob_range.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                unsigned int imax2 = sra2.size();
                prob_arr = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    prob_arr[i2] = sra2[i2];
                }
            } else {
                prob_arr = prob_range.array();
            }
            // If x_range and prob_range contain a different number of data points, PROB returns the #N/A error value.
            if ( arraySize != prob_arr.size() ) {
                return interpreter_variant( variant::error_n_a );
            }
            variant xi, probi;
            for ( unsigned long int i = 0; i < arraySize; i++ ) {
                xi = x_arr[i];
                if ( xi.type() == variant::type_error ) {
                    return interpreter_variant( xi );
                }
                probi = prob_arr[i];
                if ( probi.type() == variant::type_error ) {
                    return interpreter_variant( probi );
                }

                if ( xi.type() != variant::type_double || probi.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_num );
                }
                double dprobi = probi.numeric();
                // If any value in prob_range <= 0 or if any value in prob_range > 1, PROB returns the #NUM! error value.
                if ( dprobi <= 0.0 || dprobi > 1.0 ) {
                    return interpreter_variant( variant::error_num );
                }
                sum += dprobi;
                // If the sum of the values in prob_range > 1, PROB returns the #NUM! error value.
                if ( sum > 1.0 ) {
                    return interpreter_variant( variant::error_num );
                }

                if ( !( lower_limit > xi.numeric() || xi.numeric() > upper_limit ) ) {
                    result += dprobi;
                }
            }
        } else {
            return interpreter_variant( variant::error_num );
        }
    } else {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( result ) );
    // Returns the probability that values in a range are between two limits.
    // If upper_limit is not supplied, PROB returns the probability that values in x_range are equal to lower_limit.
}
#endif

/*!
 * \brief
 * Returns the serial number of the current date and time.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the current date and time
 *
 * \details
 * Numbers to the right of the decimal point in the serial number represent the time;
 * numbers to the left represent the date. For example, the serial number 0.5 represents the time 12:00 noon.
 * By default, January 1, 1900 is serial number 1, and January 1, 2008 is serial number 39448
 * because it is 39448 days after January 1, 1900.
 * The NOW function changes only when the worksheet is calculated or when a macro
 * that contains the function is run.
 *
 * \see
 * function_today
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_now
interpreter_variant function_now( function_parameter& /*parameters*/ )
{
    std::time_t time = std::time( NULL );
    // number of days (include leap day 29feb 1900) until 01.01.1970 = 25569
    // plus number of days since 01.01.1970 (seconds since then divided by
    // seconds(60)*minutes(60)*hours(24) = 86400
    // see http://en.wikipedia.org/wiki/Epoch_%28reference_date%29
    // for comments about excel date calculation in the trivia section
    return interpreter_variant( variant( 25569.0 + time / 86400.0 ) );
    // Numbers to the right of the decimal point represent the time.
    // Numbers to the left represent the date.
    // The NOW function changes only when the worksheet is calculated,
    // or when a macro that contains the function is run. It is not updated continuously.
}
#endif

/*!
 * \brief
 * Returns the serial number of the current date.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the current date
 *
 * \details
 * By default, January 1, 1900 is serial number 1, and January 1, 2008 is serial number 39448
 * because it is 39448 days after January 1, 1900.
 *
 * \see
 * function_now
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_today
interpreter_variant function_today( function_parameter& /*parameters*/ )
{
    std::time_t time = std::time( NULL );
    // number of days (include leap day 29feb 1900) until 01.01.1970 = 25569
    // plus number of days since 01.01.1970 (seconds since then divided by
    // seconds(60)*minutes(60)*hours(24) = 86400
    // see http://en.wikipedia.org/wiki/Epoch_%28reference_date%29
    // for comments about excel date calculation in the trivia section
    return interpreter_variant( variant( 25569.0 + time / 86400 ) );
}
#endif


/*!
 * \brief
 * Returns the relative position of an item in an array that matches a specified value in a specified order.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the position
 *
 * \details
 * MATCH returns the position of the matched value within lookup_array.
 * MATCH does not distinguish between uppercase and lowercase letters when matching text values.
 * If MATCH is unsuccessful in finding a match, it returns the #N/A error value.
 *
 * \see
 * function_hlookup | function_index | function_lookup | function_vlookup
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*interpreter_variant function_match( calculation_context& cx, unsigned int param )
{
internal::ParameterList parameters( cx, param );

interpreter_variant lookup_value = parameters[0];

int match_type = 1;
if ( parameters.size() > 2 ) {
match_type = static_cast<int>( parameters[2].numeric() );
}

if ( parameters[1].i_type() == interpreter_variant::type_range ) {
const variant& value = static_cast<range*>( parameters[1].reference() )->get_value( cx.get_session_context() );
const variant::sparse_array_type& arr = *value.array;
boost::int_fast32_t arraySize = arr.size();
boost::int_fast32_t columnWidth = value.column_width();
boost::int_fast32_t rows = arraySize / columnWidth;
if ( columnWidth > 1 && rows > 1 ) {
return interpreter_variant( variant::error_n_a );
}

} else if ( parameters[1].type() == variant::type_array ) {
const variant::sparse_array_type& arr = parameters[1].array();
boost::int_fast32_t columnWidth = parameters[1].column_width();
boost::int_fast32_t arraySize = arr.size();
boost::int_fast32_t rows = arraySize / columnWidth;
if ( columnWidth > 1 && rows > 1 ) {
return interpreter_variant( variant::error_n_a );
}

} else {
return interpreter_variant( variant::error_n_a );
}
}*/


/*!
 * \brief
 * Returns the reference specified by a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the reference specified by the text string
 *
 * \details
 * References are immediately evaluated to display their contents.
 *
 * \see
 * function_offset | Parser | ParseContext | ParseResult | Interpreter
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*
interpreter_variant function_indirect( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( variant::error_ref );
    }
    std::string ref_text = parameters[0].string();
    bool a1 = true; // Interpret ref_text as an A1-style reference. If false R1C1-style reference.
    if ( parameters.count() > 1 ) {
        a1 = parameters[1].numeric() != 0.0;
    }
    Parser parser;
    ParseContext px( *cx.get_current_cell(), *cx.get_current_cell()->get_worksheet(), cx.get_session_context() );
    Parser::ParseResult result = parser( px, std::string( "=" ).append( ref_text ) );
    // if the parse failed we return the #REF! error value.
    if ( result.successful == false ) {
        return interpreter_variant( variant::error_ref );
        // If the parse succeeded we return the result.
    } else {
        Interpreter ip;
        return ip( cx, *result.tree );
    }
    // Returns the reference specified by a text string.
}*/


/*!
 * \brief
 * Returns true if the argument is even.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value, if the argument is even
 *
 * \details
 * If the argument is nonnumeric, ISEVEN returns the #VALUE! error value.
 *
 * \see
 * function_isodd | function_even | function_odd
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_iseven
interpreter_variant function_iseven( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant value = parameters[0];
    // If the argument is nonnumeric, ISEVEN returns the #VALUE! error value.
    if ( value.type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    if ( ( static_cast<long long>( value.numeric() ) % 2 ) == 0 ) {
        return interpreter_variant( true );
    } else {
        return interpreter_variant( false );
    }
    // Returns true if the argument is even.
}
#endif

/*!
 * \brief
 * Returns true if the argument is odd.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value, if the argument is odd
 *
 * \details
 * If the argument is nonnumeric, ISODD returns the #VALUE! error value.
 *
 * \see
 * function_iseven | function_even | function_odd
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_isodd
interpreter_variant function_isodd( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant value = parameters[0];
    // If the argument is nonnumeric, ISODD returns the #VALUE! error value.
    if ( value.type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    if ( ( static_cast<long long>( value.numeric() ) % 2 ) == 0 ) {
        return interpreter_variant( false );
    } else {
        return interpreter_variant( true );
    }
    // Returns true if the argument is odd.
}
#endif


/*!
 * \brief
 * Returns the logical value TRUE.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value TRUE
 *
 * \details
 * You can enter the value TRUE directly into cells and formulas without using this function.
 *
 * \see
 * function_false | function_not | function_and
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_true
interpreter_variant function_true( function_parameter& /*parameters*/ )
{
    // Returns the logical value TRUE.
    return interpreter_variant( variant( true ) );
}
#endif


/*!
 * \brief
 * Returns the logical value FALSE.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value FALSE
 *
 * \details
 * You can enter the value FALSE directly into cells and formulas without using this function.
 *
 * \see
 * function_true | function_not | function_and
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_false
interpreter_variant function_false( function_parameter& /*parameters*/ )
{
    // Returns the logical value FALSE.
    return interpreter_variant( variant( false ) );
}
#endif

/*!
 * \brief
 * Returns true if any argument is true; returns false if all arguments are false.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value if any argument is true
 *
 * \details
 * The arguments must evaluate to logical values, or the arguments must be arrays or references that contain logical values.
 * If an array or reference argument contains text or empty cells, those values are ignored.
 *
 * \see
 * function_and | function_not
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_or
interpreter_variant function_or( function_parameter& parameters )
{
    internal::Or iOr( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            iOr( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::OrStrategy::or_result res = iOr;
    if ( res.has_value ) {
        return interpreter_variant( variant( res.result ) );
    } else {
        // If there are no logical values, OR returns the #VALUE! error value.
        return interpreter_variant( variant::error_value );
    }
}

#endif

/*!
 * \brief
 * Returns true if all arguments are true; returns false if one or more argument is false.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value if all arguments are true
 *
 * \details
 * The arguments must evaluate to logical values, or the arguments must be arrays or references that contain logical values.
 * If an array or reference argument contains text or empty cells, those values are ignored.
 *
 * \see
 * function_or | function_not
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_and
interpreter_variant function_and( function_parameter& parameters )
{
    internal::And iAnd( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            iAnd( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::AndStrategy::and_result res = iAnd;
    if ( res.has_value ) {
        return interpreter_variant( variant( res.result ) );
    } else {
        // If there are no logical values, AND returns the #VALUE! error value.
        return interpreter_variant( variant::error_value );
    }
}
#endif


/*!
 * \brief
 * Repeats text a given number of times.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * a string which contains a text a given number of times
 *
 * \details
 * If number_times is 0, REPT returns "". If number_times is not an integer, it is truncated.
 * The result of the REPT function cannot be longer than 32767 characters, or REPT returns the #VALUE! error value.
 *
 * \see
 * function_concatenate
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_rept
interpreter_variant function_rept( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    unsigned int number_times = static_cast<unsigned int>( parameters[1].numeric() ); // a positive number specifying the number of times to repeat text.
    // If number_times is not an integer, it is truncated.
    interpreter_variant text = parameters[0]; // the text you want to repeat.
    if ( ( text.string() ).length() * number_times > 32767 ) {
        return interpreter_variant( variant::error_value );
    }
    interpreter_variant result( "" ); // If number_times is zero, REPT returns ""(empty text).
    for ( unsigned int i = 0; i < number_times; i++ ) {
        ( result.as_string( parameters.context().locale() ) ).append( text.string() );
    }


    return result;
    // Repeats text a given number of times.
}
#endif


/*!
 * \brief
 * Replaces part of a text, based on the number of characters you specify, with a different text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * text containing the replacement
 *
 * \details
 * This function is for use with characters. Use function_replaceb for bytes.
 *
 * \see
 * function_replaceb | function_mid | function_search | function_substitute | function_trim
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_replace
interpreter_variant function_replace( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    using namespace std;
    interpreter_variant temp     = parameters[3];
    string new_text = temp.string(); // the text that will replace characters in old_text.
    int count       = static_cast<int>( parameters[2].numeric() ); // the number of characters in old_text that you want REPLACE to replace with new_text.
    int begin       = static_cast<int>( parameters[1].numeric() ); // the position of the character in old_text that you want to replace with new_text.
    temp            = parameters[0];
    string old_text = temp.string(); // the text in which you want to replace some characters.

    string first_part = old_text.substr( 0, begin - 1 );
    string end_part = old_text.substr( ( begin + count ) - 1 );

    return interpreter_variant( first_part + new_text + end_part );
    // Replaces part of a text, based on the number of characters you specify, with a different text string.
}
#endif


/*!
 * \brief
 * LEFTB returns the first character or characters in a text string,
 * based on the number of bytes (count) you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the first character or characters in a text string, based on the number of bytes (count) you specify
 *
 * \details
 * This function is for use with bytes. Use function_left for characters.
 *
 * \see
 * function_left
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_leftb
interpreter_variant function_leftb( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    const interpreter_variant& text = parameters[0];
    double count = 1; // If count is omitted, it is assumed to be 1.
    if ( parameters.count() > 1 ) {
        count = parameters[1].numeric();
    }

    return interpreter_variant( ( text.string() ).substr( 0, static_cast<size_t>( count ) ) );
    // LEFTB returns the first character or characters in a text string,
    // based on the number of bytes (count) you specify.
    // This function is for use with double-byte characters.
}
#endif

/*!
 * \brief
 * Returns the standard normal cumulative distribution function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the standard normal cumulative distribution function
 *
 * \details
 * If probability = NORMSDIST(x), then NORMSINV(probability) = x.
 *
 * \see
 * function_normsinv | function_normdist | function_norminv | function_standardize | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_normsdist
interpreter_variant function_normsdist( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If z is nonnumeric, NORMSDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double z = parameters[0].numeric();
    boost::math::normal s; // standard normal distribution.
    return interpreter_variant( cdf( s, z ) );
    // Returns the standard normal cumulative distribution function.
}
#endif

/*!
 * \brief
 * If cumulative is TRUE, NORMDIST returns the cumulative distribution function;
 * if FALSE, it returns the normal density function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the normal distribution
 *
 * \details
 * If probability = NORMDIST(x,...), then NORMINV(probability,...) = x.
 *
 * \see
 * function_norminv | function_normsdist | function_normsinv | function_standardize | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_normdist
interpreter_variant function_normdist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If mean or standard_dev is nonnumeric, NORMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // the value for which you want the distribution.
    double x = parameters[0].numeric();
    // the arithmetic mean of the distribution.
    double mean = parameters[1].numeric();
    // the standard deviation of the distribution.
    double standard_dev = parameters[2].numeric();
    // Flag.
    bool cumulative = parameters[3].numeric() != 0.0;

    // If standard_dev <= 0, NORMDIST returns the #NUM! error value.
    if ( standard_dev <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    boost::math::normal s( mean, standard_dev );
    if ( cumulative ) {
        result = cdf( s, x );
    } else { // normal density function:
        result = pdf( s, x );
    }
    return interpreter_variant( result );
    // If cumulative is TRUE, NORMDIST returns the cumulative distribution function.
    // If FALSE, it returns the normal density function.
}
#endif

/*!
 * \brief
 * Returns the cumulative lognormal distribution of x, where ln(x) is normally distributed with parameters mean and standard_dev.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the cumulative lognormal distribution
 *
 * \details
 * If probability = LOGNORMDIST(x,...), then LOGINV(probability,...) = x.
 *
 * \see
 * function_loginv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_lognormdist
interpreter_variant function_lognormdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, LOGNORMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // the value at which to evaluate the function.
    double x = parameters[0].numeric();
    // the mean of ln(x).
    double mean = parameters[1].numeric();
    // the standard deviation of ln(x).
    double standard_dev = parameters[2].numeric();

    // If x <= 0 or if standard_dev <= 0, LOGNORMDIST returns the #NUM! error value.
    if ( x <= 0.0 || standard_dev <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double z = ( log( x ) - mean ) / standard_dev;
    boost::math::normal s; // standard normal distribution.
    return interpreter_variant( cdf( s, z ) );
    // Returns the cumulative lognormal distribution of x, where ln(x) is normally distributed with parameters mean and standard_dev.
}
#endif

/*!
 * \brief
 * Returns the one-tailed probability-value of a z-test.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the one-tailed probability-value of a z-test
 *
 * \details
 * For a given hypothesized population mean, mu0, ZTEST returns the probability
 * that the sample mean would be greater than the average of observations in the data set(array) -
 * that is, the observed sample mean.
 *
 * \see
 * function_confidence | function_normdist | function_norminv | function_normsdist | function_normsinv | function_standardize
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ztest
interpreter_variant function_ztest( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 3 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    interpreter_variant array = parameters[0];

    if ( array.i_type() != interpreter_variant::type_range && array.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    double mu0 = 0.0;
    if ( parameters.count() > 1 && parameters[1].type() != variant::type_empty ) {
        mu0 = parameters[1].numeric();
    }
    double sigma = -1.0;
    if ( parameters.count() > 2 ) {
        // If sigma <= 0, ZTEST returns the #NUM! error value.
        if ( parameters[2].numeric() <= 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        sigma = parameters[2].numeric();
    }

    double summe = 0.0;
    double sumsq = 0.0;
    unsigned long int counter = 0;
    variant::sparse_array_type arr;
    if ( array.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( array.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        arr = variant::sparse_array_type( imax );
        for ( unsigned int i = 0; i < imax; i++ ) {
            arr[i] = sra[i];
        }
    } else {
        arr = array.array();
    }
    unsigned long int arraySize = arr.size();
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant val = arr[i];
        if ( val.type() == variant::type_error ) {
            return interpreter_variant( val );
        }
    }
    // If an argument is an array or reference, only numbers in that array or reference are counted.
    // Empty cells, logical values, or text in the array or reference are ignored.
    counter += std::for_each( arr.begin(), arr.end(), internal::Counter() ).counter;
    summe += std::for_each( arr.begin(), arr.end(), internal::Sum() ).summe;
    if ( sigma == -1.0 ) {
        sumsq += std::for_each( arr.begin(), arr.end(), internal::SumSq() ).summe;
    }

    if ( counter == 0 ) {
        return interpreter_variant( variant::error_n_a );
    }
    double std_dev;
    if ( sigma == -1.0 ) {
        if ( counter == 1 ) {
            return interpreter_variant( variant::error_div_null );
        }
        std_dev = sumsq - summe * summe / counter;
        std_dev = sqrt( std_dev / ( counter - 1 ) );
    } else {
        std_dev = sigma;
    }
    double z = ( summe / counter - mu0 ) * sqrt( static_cast<double>( counter ) ) /  std_dev;
    boost::math::normal s; // standard normal distribution.
    return interpreter_variant( variant( 1.0 - cdf( s, z ) ) );
    // Returns the one-tailed probability-value of a z-test.
    // For a given hypothesized population mean, mu0, ZTEST returns the probability
    // that the sample mean would be greater than the average of observations in the data set(array) -
    // that is, the observed sample mean.
}
#endif


/*!
 * \brief
 * Returns the inverse of the standard normal cumulative distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the standard normal cumulative distribution
 *
 * \details
 * If probability = NORMSDIST(x), then NORMSINV(probability) = x.
 *
 * \see
 * function_normsdist | function_normdist | function_norminv | function_standardize | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_normsinv
interpreter_variant function_normsinv( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If probability is nonnumeric, NORMSINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability corresponding to the normal distribution.
    // If probability < 0 or if probability > 1, NORMSINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::normal s; // standard normal distribution.
    double result = quantile( s, probability );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the standard normal cumulative distribution (with a mean of 0 and a standard deviation of 1).
}
#endif


/*!
 * \brief
 * Returns the inverse of the normal cumulative distribution for the specified mean and standard deviation.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the normal cumulative distribution
 *
 * \details
 * If probability = NORMDIST(x,...), then NORMINV(probability,...) = x.
 *
 * \see
 * function_normdist | function_normsdist | function_normsinv | function_standardize | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_norminv
interpreter_variant function_norminv( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, NORMINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability corresponding to the normal distribution.
    double mean = parameters[1].numeric(); // the arithmetic mean of the distribution.
    double standard_dev = parameters[2].numeric(); // the standard deviation of the distribution.
    // If probability < 0 or if probability > 1 or if standard_dev <= 0, NORMINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 || standard_dev <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    boost::math::normal s( mean, standard_dev );
    double result = quantile( s, probability );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the normal cumulative distribution for the specified mean and standard deviation.
}
#endif

/*!
 * \brief
 * Returns a value that you can use to construct a confidence interval for a population mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the half length of the confidence interval
 *
 * \details
 * The confidence interval is population mean+-CONFIDENCE.
 *
 * \see
 * function_normsdist | function_normsinv | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_confidence
interpreter_variant function_confidence( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, CONFIDENCE returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double alpha = parameters[0].numeric(); // the significance level used to compute the confidence level. The confidence level equals 1-alpha.
    double standard_dev = parameters[1].numeric(); // the population standard deviation for the data range (is assumed to be known).
    long long size = static_cast<long long>( parameters[2].numeric() ); // the sample size.
    // If alpha <= 0 or alpha >= 1 or standard_dev <= 0 or size < 1, CONFIDENCE returns the #NUM! error value.
    if ( alpha <= 0.0 || alpha >= 1.0 || standard_dev <= 0.0 || size < 1 ) {
        return interpreter_variant( variant::error_num );
    }

    boost::math::normal s; // standard normal distribution.
    double quant = quantile( s, 1.0 - alpha / 2.0 );
    double result = quant * standard_dev / sqrt( static_cast<double>( size ) );
    return interpreter_variant( variant( result ) );
    // Returns a value that you can use to construct a confidence interval for a population mean.
    // The confidence interval is a range of values.
    // Your sample mean m is at the center of this range and the range is m+-CONFIDENCE.
    // Assume that we use m, standard_dev, and size to construct a two-tailed test at significance level alpha
    // of the hypothesis that the population mean is mu. Then we will not reject that hypothesis,
    // if mu is in the confidence interval, and will reject that hypothesis, if mu is not in the confidence interval.
}
#endif

/*!
 * \brief
 * Returns the inverse of the lognormal cumulative distribution function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the lognormal cumulative distribution function
 *
 * \details
 * If probability = LOGNORMDIST(x,...), then LOGINV(probability,...) = x.
 *
 * \see
 * function_lognormdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_loginv
interpreter_variant function_loginv( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, LOGINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability associated with the lognormal distribution.
    double mean = parameters[1].numeric(); // the mean of ln(x).
    double standard_dev = parameters[2].numeric(); // the standard deviation of ln(x).
    // If probability < 0 or probability > 1 or standard_dev <= 0, LOGINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 || standard_dev <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    boost::math::normal s; // standard normal distribution.
    double result = exp( mean + standard_dev * quantile( s, probability ) );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the lognormal cumulative distribution function of x,
    // where ln(x) is normally distributed with parameters mean and standard_dev.
}
#endif

/*!
 * \brief
 * Counts empty cells in a specified range of cells.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of empty cells in the specified range of cells
 *
 * \details
 * If the argument is no range, COUNTBLANK returns the #VALUE! error value.
 *
 * \see
 * function_countif
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_countblank
interpreter_variant function_countblank( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If the argument is no range, COUNTBLANK returns the #VALUE! error value.
    // The argument is the range from which you want to count the blank cells.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }
    size_t sum = 0;
    range_reference& rref = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra( rref, parameters.context() );
    unsigned int xmax = rref.actualize().position().row_count();
    unsigned int ymax = rref.actualize().position().column_count();
    for ( unsigned int y = 0; y < ymax; y++ ) {
        for ( unsigned int x = 0; x < xmax; x++ ) {
            if ( sra( x, y ).is_empty() ) {
                // Counts empty cells, cells with formulas that return ""(empty text) are also counted.
                ++sum;
            }
        }
    }
    return interpreter_variant( variant( static_cast<double>( sum ) ) );
    // Counts empty cells in a specified range of cells.
}
#endif

/*!
 * \brief
 * Returns e raised to the power of number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the power e^number
 *
 * \details
 * EXP is the inverse of LN, the natural logarithm.
 * The constant e equals 2.71828182845904, the base of the natural logarithm.
 *
 * \see
 * function_imexp | function_ln | function_log | function_power
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_exp
interpreter_variant function_exp( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, EXP returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( exp( parameters[0].numeric() ) ) );
    // Returns e raised to the power of number.
    // The constant e equals 2.71828182845904, the base of the natural logarithm.
}
#endif

/*!
 * \brief
 * Returns a positive square root.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the positive square root
 *
 * \details
 * If number is negative, SQRT returns the #NUM! error value.
 *
 * \see
 * function_sqrtpi | function_abs
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sqrt
interpreter_variant function_sqrt( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, SQRT returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // number is the number for which you want the square root.
    // If number is negative, SQRT returns the #NUM! error value.
    if ( number < 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( sqrt( number ) ) );
    // Returns a positive square root.
}
#endif

/*!
 * \brief
 * Returns the logarithm of a number to the base you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logarithm
 *
 * \details
 * If base is omitted, it is assumed to be 10.
 *
 * \see
 * function_ln | function_log10 | function_exp | function_power | function_imln | function_imlog10
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_log
interpreter_variant function_log( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If number is nonnumeric, LOG returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the argument of the logarithm.
    // If number is not positive, LOG returns the #NUM! error value.
    if ( number <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    double iBase = 10.0; // the base of the logarithm. If base is omitted, it is assumed to be 10.
    if ( parameters.count() > 1 ) {
        if ( parameters[1].type() == variant::type_double && parameters[1].numeric() > 0.0 ) {
            iBase = parameters[1].numeric();
        }
    }
    return interpreter_variant( variant( log( number ) / log( iBase ) ) );
    // Returns the logarithm of a number to the base you specify.
}
#endif

/*!
 * \brief
 * Returns the natural logarithm of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the natural logarithm
 *
 * \details
 * LN is the inverse of the EXP function.
 * Natural logarithms are based on the constant e (2.71828182845904).
 *
 * \see
 * function_log | function_log10 | function_exp | function_imln | function_imlog10
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ln
interpreter_variant function_ln( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, LN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the argument of the logarithm.
    // If the argument is not positive, LN returns the #NUM! error value.
    if ( number <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( log( number ) ) );
    // Returns the natural logarithm of a number.
    // Natural logarithms are based on the constant e (2.71828182845904).
}
#endif

/*!
 * \brief
 * Returns the base-10 logarithm of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the base-10 logarithm
 *
 * \details
 * function_log with only one parameter provides the same.
 *
 * \see
 * function_log | function_ln | function_exp | function_imlog10 | function_imln | function_imlog2
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_log10
interpreter_variant function_log10( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, LOG10 returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the argument of the logarithm.
    // If the argument is not positive, LOG10 returns the #NUM! error value.
    if ( number <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( log10( number ) ) );
    // Returns the base-10 logarithm of a number.
}
#endif

/*!
 * \brief
 * Returns the sign of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sign of the number
 *
 * \details
 * Returns 1 if the number is positive, zero(0) if the number is 0, and -1 if the number is negative.
 *
 * \see
 * function_abs
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sign
interpreter_variant function_sign( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, SIGN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric();
    if ( number > 0.0 ) {
        return interpreter_variant( variant( 1.0 ) );
    }

    if ( number < 0.0 ) {
        return interpreter_variant( variant( -1.0 ) );
    }
    return interpreter_variant( variant( 0.0 ) );
    // Returns the sign of a number. Returns 1 if the number is positive,
    // zero(0) if the number is 0, and -1 if the number is negative.
}
#endif

/*!
 * \brief
 * Returns the cosine of the given angle in radians.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the cosine
 *
 * \details
 * If the angle is in degrees, multiply it by PI()/180 or use the function RADIANS to convert it to radians.
 *
 * \see
 * function_acos | function_sin | function_tan | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_cos
interpreter_variant function_cos( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, COS returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( cos( parameters[0].numeric() ) ) );
    // Returns the cosine of the given angle in radians.
}
#endif

/*!
 * \brief
 * Returns the sine of the given angle in radians.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sine
 *
 * \details
 * If the angle is in degrees, multiply it by PI()/180 or use the function RADIANS to convert it to radians.
 *
 * \see
 * function_asin | function_cos | function_tan | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sin
interpreter_variant function_sin( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, SIN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( sin( parameters[0].numeric() ) ) );
    // Returns the sine of the given angle in radians.
}
#endif

/*!
 * \brief
 * Returns the absolute value of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the absolute value
 *
 * \details
 * The absolute value of a number is the number without its sign.
 *
 * \see
 * function_sign | function_imabs
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_abs
interpreter_variant function_abs( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ABS returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( fabs( parameters[0].numeric() ) ) );
    // Returns the absolute value of a number.
    // The absolute value of a number is the number without its sign.
}
#endif

/*!
 * \brief
 * Returns the tangent of the given angle in radians.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the tangent
 *
 * \details
 * If the angle is in degrees, multiply it by PI()/180 or use the function RADIANS to convert it to radians.
 *
 * \see
 * function_atan | function_atan2 | function_sin | function_cos | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_tan
interpreter_variant function_tan( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, TAN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( tan( parameters[0].numeric() ) ) );
    // Returns the tangent of the given angle in radians.
}
#endif

/*!
 * \brief
 * Returns the arccosine, or inverse cosine, of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arccosine
 *
 * \details
 * The arccosine is the angle whose cosine is number. The returned angle is given in radians in the range 0 to pi.
 *
 * \see
 * function_cos | function_asin | function_atan | function_atan2 | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_acos
interpreter_variant function_acos( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ACOS returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // number is the cosine of the angle you want.
    // And must be from -1 to 1, else ACOS returns the #NUM! error value.
    if ( number < -1.0 || number > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( acos( number ) ) );
    // Returns the arccosine, or inverse cosine, of a number.
    // The arccosine is the angle whose cosine is number.
    // The returned angle is given in radians in the range 0 to pi.
}
#endif

/*!
 * \brief
 * Returns the arcsine, or inverse sine, of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arcsine
 *
 * \details
 * The arcsine is the angle whose sine is number. The returned angle is given in radians in the range -pi/2 to pi/2.
 *
 * \see
 * function_sin | function_acos | function_atan | function_atan2 | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_asin
interpreter_variant function_asin( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ASIN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // number is the sine of the angle you want.
    // And must be from -1 to 1, else ASIN returns the #NUM! error value.
    if ( number < -1.0 || number > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( asin( number ) ) );
    // Returns the arcsine, or inverse sine, of a number.
    // The arcsine is the angle whose sine is number.
    // The returned angle is given in radians in the range -pi/2 to pi/2.
}
#endif

/*!
 * \brief
 * Returns the arctangent, or inverse tangent, of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arctangent
 *
 * \details
 * The arctangent is the angle whose tangent is number. The returned angle is given in radians in the range -pi/2 to pi/2.
 *
 * \see
 * function_atan2 | function_tan | function_asin | function_acos | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_atan
interpreter_variant function_atan( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ATAN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( atan( parameters[0].numeric() ) ) );
    // Returns the arctangent, or inverse tangent, of a number.
    // The arctangent is the angle whose tangent is number.
    // The returned angle is given in radians in the range -pi/2 to pi/2.
}
#endif

/*!
 * \brief
 * Returns the arctangent, or inverse tangent, of the specified x- and y-coordinates.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arctangent
 *
 * \details
 * The arctangent is the angle from the x-axis to a line containing the origin (0,0) and a point with coordinates (x_num, y_num).
 * The angle is given in radians between -pi and pi, excluding -pi.
 *
 * \see
 * function_atan | function_tan | function_asin | function_acos | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_atan2
interpreter_variant function_atan2( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If there are less than 2 arguments, ATAN2 returns the #VALUE! error value.
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If any argument is nonnumeric, ATAN2 returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x_num = parameters[0].numeric(); // the x-coordinate of the point.
    double y_num = parameters[1].numeric(); // the y-coordinate of the point.
    // If both x_num and y_num are 0, ATAN2 returns the #DIV/0! error value.
    if ( x_num == 0.0 && y_num == 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    return interpreter_variant( variant( atan2( x_num, y_num ) ) );
    // Returns the arctangent, or inverse tangent, of the specified x- and y-coordinates.
    // The arctangent is the angle from the x-axis to a line containing the origin (0,0)
    // and a point with coordinates (x_num, y_num).
    // The angle is given in radians between -pi and pi, excluding -pi.
}
#endif

/*!
 * \brief
 * Returns the remainder after number is divided by divisor.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the remainder of the division
 *
 * \details
 * The result has the same sign as divisor.
 * function_mod( number, divisor ) = number - divisor * function_floor( number / divisor )
 *
 * \see
 * function_floor | function_int | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mod
interpreter_variant function_mod( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If there are less than 2 arguments, MOD returns the #VALUE! error value.
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If any argument is nonnumeric, MOD returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the number for which you want to find the remainder.
    double divisor = parameters[1].numeric(); // the divisor by which you want to divide number.
    // If divisor is 0, MOD returns the #DIV/0! error value.
    if ( divisor == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    //return interpreter_variant( divisor * function_int_ex( interpreter_variant( number / divisor ) ).numeric() );
    return interpreter_variant( variant( number - divisor * floor( number / divisor ) ) );
    // Returns the remainder after number is divided by divisor.
    // The result has the same sign as divisor.
}
#endif

/*!
 * \brief
 * Returns the number 3.14159265358979, the mathematical constant pi.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * 3.14159265358979, the mathematical constant pi
 *
 * \details
 * Ludolph's constant
 *
 * \see
 * function_radians | function_degrees | function_sin | function_cos | function_tan
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_pi
interpreter_variant function_pi( function_parameter& /*parameters*/ )
{
    return interpreter_variant( variant( M_PI ) );
    // Returns the number 3.14159265358979, the mathematical constant pi.
}
#endif

/*!
 * \brief
 * Returns the result of a number raised to a power.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the power
 *
 * \details
 * The "^" operator can be used instead of POWER to indicate to what power the base number is to be raised.
 * base^exponent
 *
 * \see
 * function_log | function_exp
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_power
interpreter_variant function_power( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If there are less than 2 arguments, POWER returns the #VALUE! error value.
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If any argument is nonnumeric, POWER returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the base.
    double exponent = parameters[1].numeric(); // the exponent to which the base number is raised.
    // If the base is zero and the exponent negative, POWER returns the #DIV/0! error value.
    if ( number == 0.0 && exponent < 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    // If the base is negative and the exponent no integer, POWER returns the #NUM! error value.
    if ( number < 0.0 && exponent != floor( exponent ) ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( pow( number, exponent ) ) );
    // Returns the result of a number raised to a power.
}
#endif

/*!
 * \brief
 * Rounds a number down to the nearest integer.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the nearest lower integer
 *
 * \details
 *
 * \see
 * function_ceiling | function_floor | function_mround | function_round | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_int
interpreter_variant function_int( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, INT returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( floor( parameters[0].numeric() ) ) );
    // Rounds a number down to the nearest integer.
}
#endif


/*!
 * \brief
 * Returns true, if the argument refers to a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to a number
 *
 * \details
 * The value argument is not converted. For example, in the formula ISNUMBER("19"),
 * "19" is not converted from a text value, and the ISNUMBER function returns FALSE.
 *
 * \see
 * function_isnontext | function_istext | function_islogical
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_isnumber
interpreter_variant function_isnumber( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant( false ) );
    }
    return interpreter_variant( variant( true ) );
    // Returns true, if the argument refers to a number.
}
#endif


/*!
 * \brief
 * Returns true, if the argument refers to a text.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to a text
 *
 * \details
 * The value argument is not converted. For example, in the formula ISNUMBER("19"),
 * "19" is not converted from a text value, and the ISTEXT function returns TRUE.
 *
 * \see
 * function_isnontext | function_isnumber | function_islogical
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_istext
interpreter_variant function_istext( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( variant( false ) );
    }
    return interpreter_variant( variant( true ) );
    // Returns true, if the argument refers to a text.
}
#endif

/*!
 * \brief
 * Capitalizes the first letter in a text string and any other letters in text
 * that follow any character other than a letter.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the converted text
 *
 * \details
 * Converts all other letters to lowercase letters.
 *
 * \see
 * function_toupper | function_tolower
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_proper
interpreter_variant function_proper( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is no text, it is returned unchanged.
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( parameters[0] );
    }

    std::string text = parameters[0].string();
    bool inWord = false;
    for ( unsigned int i = 0; i < text.length(); i++ ) {
        if ( isalpha( text[i] ) ) {
            if ( inWord ) {
                text[i] = tolower( text[i] );
            } else {
                text[i] = toupper( text[i] );
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }

    return interpreter_variant( variant( text ) );
    // Capitalizes the first letter in a text string and
    // any other letters in text that follow any character other than a letter.
    // Converts all other letters to lowercase letters.
}
#endif

/*!
 * \brief
 * Converts text to uppercase.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the converted text
 *
 * \details
 * Does not change characters in text that are not letters.
 *
 * \see
 * function_tolower | function_proper
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef funtion_toupper
interpreter_variant function_toupper( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( parameters[0] );
    }
    std::string word = parameters[0].string();
    for ( size_t i = 0;  i < word.size(); i++ ) {
        word[i] = std::toupper( word[i], std::locale() );
    }
    return interpreter_variant( variant( word ) );
    // Converts text to uppercase.
    // Does not change characters in text that are not letters.
}
#endif

/*!
 * \brief
 * Converts all uppercase letters in a text string to lowercase.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the converted text
 *
 * \details
 * Does not change characters in text that are not letters.
 *
 * \see
 * function_toupper | function_proper
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_tolower
interpreter_variant function_tolower( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( parameters[0] );
    }
    std::string word = parameters[0].string();
    for ( size_t i = 0;  i < word.size(); i++ ) {
        word[i] = std::tolower( word[i], std::locale() );
    }
    return interpreter_variant( variant( word ) );
    // Converts all uppercase letters in a text string to lowercase.
    // Does not change characters in text that are not letters.
}
#endif


/*!
 * \brief
 * Returns number rounded up to the nearest even integer.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * number rounded up to the nearest even integer
 *
 * \details
 * Regardless of the sign of number, a value is rounded up when adjusted away from zero.
 * If number is an even integer, no rounding occurs.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_even
interpreter_variant function_even( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If number is nonnumeric, EVEN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the value to round.

    double result = 0.0;
    if ( number < 0.0 ) {
        result = floor( number );
        if ( fmod( result, 2.0 ) < -0.1 ) {
            result--;
        }
    } else {
        result = ceil( number );
        if ( fmod( result, 2.0 ) > 0.1 ) {
            result++;
        }
    }
    return interpreter_variant( variant( result ) );
    // Returns number rounded up to the nearest even integer.
}
#endif

/*!
 * \brief
 * Returns number rounded up to the nearest odd integer.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * number rounded up to the nearest odd integer
 *
 * \details
 * Regardless of the sign of number, a value is rounded up when adjusted away from zero.
 * If number is an odd integer, no rounding occurs.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_odd
interpreter_variant function_odd( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If number is nonnumeric, ODD returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the value to round.

    double result = 0.0;
    if ( number < 0.0 ) {
        result = floor( number );
        if ( fmod( result, 2.0 ) > -0.9 ) {
            result--;
        }
    } else {
        result = ceil( number );
        if ( fmod( result, 2.0 ) < 0.9 ) {
            result++;
        }
    }
    return interpreter_variant( variant( result ) );
    // Returns number rounded up to the nearest odd integer.
}
#endif

/*!
 * \brief
 * Rounds a number up, away from zero.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * If num_digits is greater than 0, then number is rounded up to the specified number of decimal places.
 * If num_digits is 0, then number is rounded up to the nearest integer.
 * If num_digits is less than 0, then number is rounded up to the left of the decimal point.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_round | function_rounddown | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_roundup
interpreter_variant function_roundup( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, ROUNDUP returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the real number that you want rounded up.
    int num_digits = static_cast<int>( parameters[1].numeric() ); // the number of digits to which you want to round number.
    // If num_digits is greater than 0, then number is rounded up to the specified number of decimal places.
    // If num_digits is 0, then number is rounded up to the nearest integer.
    // If num_digits is less than 0, then number is rounded up to the left of the decimal point.
    double factor = pow( 10.0, num_digits );
    double result = 0.0;
    if ( number < 0.0 ) {
        result = floor( number * factor ) / factor;
    } else {
        result = ceil( number * factor ) / factor;
    }
    return interpreter_variant( variant( result ) );
    // Rounds a number up, away from zero.
}
#endif


/*!
 * \brief
 * Rounds a number down, toward zero.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * If num_digits is greater than 0, then number is rounded down to the specified number of decimal places.
 * If num_digits is 0, then number is rounded down to the nearest integer.
 * If num_digits is less than 0, then number is rounded down to the left of the decimal point.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_round | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_rounddouwn
interpreter_variant function_rounddown( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, ROUNDDOWN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the real number that you want rounded down.
    int num_digits = static_cast<int>( parameters[1].numeric() ); // the number of digits to which you want to round number.
    // If num_digits is greater than 0, then number is rounded down to the specified number of decimal places.
    // If num_digits is 0, then number is rounded down to the nearest integer.
    // If num_digits is less than 0, then number is rounded down to the left of the decimal point.
    double factor = pow( 10.0, num_digits );
    double result = 0.0;
    if ( number < 0.0 ) {
        result = ceil( number * factor ) / factor;
    } else {
        result = floor( number * factor ) / factor;
    }
    return interpreter_variant( variant( result ) );
    // Rounds a number down, toward zero.
}
#endif

/*!
 * \brief
 * Truncates a number to an integer by removing the fractional part of the number at the specified precision.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the truncated number
 *
 * \details
 * TRUNC and INT are similar in that both return integers. TRUNC removes the fractional part of the number.
 * INT rounds numbers down to the nearest integer based on the value of the fractional part of the number.
 * INT and TRUNC are different only when using negative numbers:
 * TRUNC(-4.3) returns -4, but INT(-4.3) returns -5 because -5 is the lower number.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_round | function_roundup
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_trunc
interpreter_variant function_trunc( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If number is nonnumeric, TRUNC returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    int num_digits = 0; // specifying the precision of the truncation. The default value is 0.
    if ( parameters.count() > 1 ) {
        if ( parameters[1].type() == variant::type_double ) {
            num_digits = static_cast<int>( parameters[1].numeric() );
        }
    }

    double faktor = pow( 10.0, num_digits );
    return interpreter_variant( variant( static_cast<long long>( parameters[0].numeric() * faktor ) / faktor ) );
    // Truncates a number to an integer by removing the fractional part of the number at the specified precision.
}
#endif


/*!
 * \brief
 * Counts the number of cells that contain numbers and also numbers within the list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of cells that contain numbers and also numbers within the list of arguments
 *
 * \details
 * Arguments that are numbers, dates, or text representations of numbers are counted.
 * Arguments that are error values or text that cannot be translated into numbers are ignored.
 * Use COUNT to get the number of entries in a number field that's in a range or array of numbers.
 *
 * \see
 * internal::Counter | function_counta | function_dcount | function_dcounta
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_count
interpreter_variant function_count( function_parameter& parameters )
{
    internal::Count count( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            count( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    return interpreter_variant( variant( count ) );
    // Counts the number of cells that contain numbers and also numbers within the list of arguments.
    // Arguments that are numbers, dates, or text representations of numbers are counted.
    // Arguments that are error values or text that cannot be translated into numbers are ignored.
    // Use COUNT to get the number of entries in a number field that's in a range or array of numbers.
}
#endif

/*!
 * \brief
 * Counts the number of cells that are not empty and the values within the list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of cells that are not empty and the values within the list of arguments
 *
 * \details
 * A value is any type of information, including empty text("") but not including empty cells.
 * If an argument is an array or reference, empty cells within the array or reference are ignored.
 * Use COUNTA to count the number of cells that contain data in a range or array.
 *
 * \see
 * internal::CounterA | function_count | function_dcount | function_dcounta
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_counta
interpreter_variant function_counta( function_parameter& parameters )
{
    internal::Counta counta( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            counta( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    return interpreter_variant( variant( counta ) );
    // Counts the number of cells that are not empty and the values within the list of arguments.
    // A value is any type of information, including empty text("") but not including empty cells.
    // If an argument is an array or reference, empty cells within the array or reference are ignored.
    // Use COUNTA to count the number of cells that contain data in a range or array.
}
#endif

/*!
 * \brief
 * TRIMMEAN calculates the mean taken by excluding a percentage of data points from the top and bottom tails of a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the trimmed mean
 *
 * \details
 * TRIMMEAN rounds the number of excluded data points down to the nearest multiple of 2.
 * If percent = 0.1, 10 percent of 30 data points equals 3 points.
 * For symmetry, TRIMMEAN excludes a single value from the top and bottom of the data set.
 *
 * \see
 * function_average | function_geomean | function_harmean | function_median | function_mode
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_trimmean
interpreter_variant function_trimmean( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // Error values cause errors.
    if ( parameters[1].type() == variant::type_error ) {
        return parameters[1];
    }
    double percent = 0.0; // the fractional number of data points to exclude from calculation.
    if ( parameters[1].type() == variant::type_string ) {
        try { // text representation of numbers or logical values are counted.
            percent = boost::lexical_cast<double>( parameters[1].string() );
        } catch ( boost::bad_lexical_cast& ) { // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        percent = parameters[1].numeric();
    }
    // If percent < 0 or percent >= 1, TRIMMEAN returns the #NUM! error value.
    if ( percent < 0.0 || percent >= 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    std::vector<double> vx;
    if ( parameters[0].i_type() == interpreter_variant::type_range || parameters[0].type() == variant::type_array ) {
        variant::sparse_array_type arr;
        if ( parameters[0].i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( parameters[0].reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned int imax = sra.size();
            arr = variant::sparse_array_type( imax );
            for ( unsigned int i = 0; i < imax; i++ ) {
                arr[i] = sra[i];
            }
        } else {
            arr = parameters[0].array();
        }
        unsigned long arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant xi = arr[i];
            // error values cause errors.
            if ( xi.type() == variant::type_error ) {
                return interpreter_variant( xi );
            }
            // If the array or reference contains empty cells, logical values, or text, those values are ignored.
            if ( xi.type() == variant::type_double ) {
                vx.push_back( xi.numeric() );
            }

        }
        // If the array or reference contains no counted value, TRIMMEAN returns the #NUM! error value.
        if ( vx.size() == 0 ) {
            return interpreter_variant( variant::error_num );
        }
        std::sort( vx.begin(), vx.end() );
        unsigned long int exclude = static_cast<unsigned long int>( 0.5 * percent * vx.size() );
        for ( unsigned long int i = 0; i < exclude; i++ ) {
            vx.pop_back();
            vx.erase( vx.begin() );
        }
        unsigned long int vcount = vx.size();
        double summe = 0;
        for ( unsigned long int i = 0; i < vcount; i++ ) {
            summe += vx[i];
        }
        result = summe / vcount;
    } else {
        // error values cause errors.
        if ( parameters[0].type() == variant::type_error ) {
            return parameters[0];
        }

        if ( parameters[0].type() == variant::type_string ) {
            try { // text representation of numbers or logical values are counted.
                result = boost::lexical_cast<double>( parameters[0].string() );
            } catch ( boost::bad_lexical_cast& ) { // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else {
            result = parameters[0].numeric();
        }
    }
    return interpreter_variant( variant( result ) );
    // Returns the mean of the interior of a data set.
    // TRIMMEAN calculates the mean taken by excluding a percentage of data points
    // from the top and bottom tails of a data set.
}
#endif
/*!
 * \brief
 * Returns the average (arithmetic mean) of the values in the list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the average (arithmetic mean)
 *
 * \details
 * In addition to numbers, text and logical values such as TRUE and FALSE are included in the calculation.
 *
 * \see
 * internal::SumA | internal::CounterA | function_average
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_averagea
interpreter_variant function_averagea( function_parameter& parameters )
{
    internal::Averagea averagea( parameters );
    try {
        for ( int i = 0; i < parameters.count(); i++ ) {
            averagea( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::AverageaStrategy::averagea_result res = averagea;
    // If there is no counted value, AVERAGEA returns the #DIV/0! error value.
    if ( res.count == 0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    return interpreter_variant( variant( res.summe / static_cast<double>( res.count ) ) );
    // Returns the average (arithmetic mean) of the values in the list of arguments.
    // In addition to numbers, text and logical values such as TRUE and FALSE are included in the calculation.
}
#endif

/*!
 * \brief
 * Compares two text strings and returns true, if they are exactly the same, false otherwise.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the two text strings are exactly the same
 *
 * \details
 * EXACT is case-sensitive but ignores formatting differences.
 *
 * \see
 * function_delta | function_len | function_search
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_exact
interpreter_variant function_exact( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If any argument is not a string, EXACT returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    if ( parameters[0].string() == parameters[1].string() ) {
        return interpreter_variant( variant( true ) );
    }
    return interpreter_variant( variant( false ) );
    // Compares two text strings and returns true, if they are exactly the same, false otherwise.
    // EXACT is case-sensitive but ignores formatting differences.
}
#endif

/*!
 * \brief
 * Returns the k-th largest value in a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the k-th largest value
 *
 * \details
 * You can use this function to select a value based on its relative standing.
 * For example, you can use LARGE to return the highest, runner-up, or third-place score.
 *
 * \see
 * function_percentile | function_percentrank | function_quartile | function_small
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_large
interpreter_variant function_large( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[1].type() != variant::type_double || ( parameters[0].i_type() != interpreter_variant::type_range && parameters[0].type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_value );
    }

    std::vector<double> numbers;
    variant::sparse_array_type arr;
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        arr = variant::sparse_array_type( imax );
        for ( unsigned int i = 0; i < imax; i++ ) {
            arr[i] = sra[i];
        }
    } else {
        arr = parameters[0].array();
    }
    size_t iSize = arr.size();
    for ( size_t i = 0; i < iSize; i++ ) {
        if ( static_cast<const variant&>( arr[i] ).type() == variant::type_double ) {
            numbers.push_back( static_cast<const variant&>( arr[i] ).numeric() );
        }
    }

    std::vector<double>::size_type index = static_cast<std::vector<double>::size_type>( parameters[1].numeric() - 1 ); // k=index+1 is the position (from the largest) in the array or cell range of data to return.
    // If the array is empty or index+1 <= 0 or if index+1 is greater than the number of data points, LARGE returns the #NUM! error value.
    if ( index >= numbers.size() || index < 0 ) {
        return interpreter_variant( variant::error_num );
    } else {
        std::sort( numbers.begin(), numbers.end(), std::greater<double>() ); // sort downwards.
        return interpreter_variant( variant( numbers[ index ] ) );
    }
    // Returns the k-th largest value in a data set.
}
#endif


/*!
 * \brief
 * Returns the k-th smallest value in a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the k-th smallest value
 *
 * \details
 * Use this function to return values with a particular relative standing in a data set.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentile | function_percentrank | function_quartile
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_small
interpreter_variant function_small( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[1].type() != variant::type_double || ( parameters[0].i_type() != interpreter_variant::type_range && parameters[0].type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_value );
    }

    std::vector<double> numbers;
    variant::sparse_array_type arr;
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        arr = variant::sparse_array_type( imax );
        for ( unsigned int i = 0; i < imax; i++ ) {
            arr[i] = sra[i];
        }
    } else {
        arr = parameters[0].array();
    }
    size_t iSize = arr.size();
    for ( size_t i = 0; i < iSize; i++ ) {
        if ( static_cast<const variant&>( arr[i] ).type() == variant::type_double ) {
            numbers.push_back( static_cast<const variant&>( arr[i] ).numeric() );
        }
    }

    std::vector<double>::size_type index = static_cast<std::vector<double>::size_type>( parameters[1].numeric() - 1 ); // k=index+1 is the position (from the smallest) in the array or range of data to return.
    // If the array is empty or index+1 <= 0 or if index+1 exceeds the number of data points, SMALL returns the #NUM! error value.
    if ( index >= numbers.size() || index < 0 ) {
        return interpreter_variant( variant::error_num );
    } else {
        std::sort( numbers.begin(), numbers.end(), std::less<double>() ); // sort upwards.
        return interpreter_variant( variant( numbers[ index ] ) );
    }
    // Returns the k-th smallest value in a data set.
}
#endif




/*!
 * \brief
 * Returns the text referred to by value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the text value or ""
 *
 * \details
 * If value is or refers to text, T returns value.
 * If value does not refer to text, T returns "" (empty text).
 *
 * \see
 * function_cell | function_n | function_value
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_t
interpreter_variant function_t( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[0].type() == variant::type_string ) {
        return parameters[0];
    } else {
        return interpreter_variant( variant( "" ) );
    }
    // Returns the text referred to by value.
    // If value is or refers to text, T returns value.
    // If value does not refer to text, T returns "" (empty text).
}
#endif

/*!
 * \brief
 * Rounds number down, toward zero, to the nearest multiple of significance.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * Regardless of the sign of number, a value is rounded down when adjusted away from zero.
 * If number is an exact multiple of significance, no rounding occurs.
 *
 * \see
 * function_ceiling | function_int | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_floor
interpreter_variant function_floor( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, FLOOR returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    } else if ( parameters[0].numeric() * parameters[1].numeric() < 0.0 ) {
        // If number and significance have different signs, FLOOR returns the #NUM! error value.
        return interpreter_variant( variant::error_num );
    } else if ( parameters[0].numeric() == 0.0 || parameters[1].numeric() == 0.0 ) {
        return interpreter_variant( variant( 0.0 ) );
    } else {
        long long quotient = static_cast<long long>( parameters[0].numeric() / parameters[1].numeric() );
        return interpreter_variant( variant( quotient * parameters[1].numeric() ) );
    }
    // Rounds number down, toward zero, to the nearest multiple of significance.
}
#endif

/*!
 * \brief
 * Returns number rounded to the nearest multiple of significance.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 *
 * \see
 * function_ceiling | function_floor | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mround
interpreter_variant function_mround( function_parameter& parameters )
{
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_n_a );
    }
    if ( parameters.count() > 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If either argument is nonnumeric, MROUND returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the value you want to round.
    double significance = parameters[1].numeric(); // the multiple to which you want to round.
    if ( number == 0.0 ) {
        return interpreter_variant( 0.0 );
    }
    // If the arguments have different signs, MROUND returns the #NUM! error value.
    if ( number* significance < 0.0 || significance == 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    long long quotient = static_cast<long long>( number / significance );

    double rest = number - quotient * significance;

    if ( fabs( 2.0 * rest ) >= ( fabs( significance ) * ( 1.0 - 1e-15 ) ) ) {
        quotient++;
    }

    return interpreter_variant( variant( quotient * significance ) );
    // Returns number rounded to the nearest multiple of significance.
}
#endif

/*!
 * \brief
 * Returns number rounded up, away from zero, to the nearest multiple of significance.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * Regardless of the sign of number, a value is rounded up when adjusted away from zero.
 * If number is an exact multiple of significance, no rounding occurs.
 *
 * \see
 * function_floor | function_int | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ceiling
interpreter_variant function_ceiling( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, CEILING returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the value you want to round.
    double significance = parameters[1].numeric(); // the multiple to which you want to round.
    if ( number == 0.0 ) {
        return interpreter_variant( variant( 0.0 ) );
    }
    // If number and significance have different signs, CEILING returns the #NUM! error value.
    if ( number* significance < 0.0 || significance == 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    long long quotient = static_cast<long long>( number / significance );
    double rest = number - quotient * significance;

    if ( rest != 0.0 ) {
        ++quotient;
    }

    return interpreter_variant( variant( quotient * significance ) );
    // Returns number rounded up, away from zero, to the nearest multiple of significance.
}
#endif


/*!
 * \brief
 * Removes all spaces from text except for single spaces between words.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the trimmed text
 *
 * \details
 * Use TRIM on text that you have received from another application that may have irregular spacing.
 *
 * \see
 * function_clean | function_mid | function_replace | function_substitute
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_trim
interpreter_variant function_trim( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is no text, TRIM returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string text = parameters[0].string(); // the text from which you want spaces removed.

    typedef std::vector<std::string> SplitVector;
    SplitVector Elements;
    boost::algorithm::split( Elements, text, boost::algorithm::is_from_range( ' ', ' ' ) );

    std::string returnValue = "";
    for ( size_t i = 0; i < Elements.size(); i++ ) {
        if ( Elements[i] != " " && Elements[i] != "" ) {
            returnValue.append( Elements[i] );
            returnValue.append( " " );
        }
    }

    size_t newSize = returnValue.size();
    if ( newSize > 0 ) {
        returnValue = returnValue.substr( 0, newSize - 1 );
    }

    return interpreter_variant( variant( returnValue ) );
    // Removes all spaces from text except for single spaces between words.
}
#endif

/*!
 * \brief
 * Substitutes new_text for old_text in a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the substituted text
 *
 * \details
 * Use SUBSTITUTE when you want to replace specific text in a text string.
 *
 * \see
 * function_replace | function_trim
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_substitute
interpreter_variant function_substitute( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If any of the first 3 arguments is no text, SUBSTITUTE returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_string || parameters[2].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string text = parameters[0].string(); // the text or the reference to a cell containing text, for which you want to substitute characters.
    std::string old_text = parameters[1].string(); // the text you want to replace.
    std::string new_text = parameters[2].string(); // the text you want to replace old_text with.

    int begin = -1;
    if ( parameters.count() > 3 ) {
        begin = ( static_cast<int>( parameters[3].numeric() ) - 1 );
    } // specifies which occurrence of old_text you want to replace with new_text.
    // If you specify it, only that instance of old_text is replaced.
    // Otherwise, every occurrence of old_text in text is changed to new_text.
    if ( begin != -1 ) {
        boost::algorithm::replace_nth( text, old_text, begin, new_text );
    } else {
        boost::algorithm::replace_all( text, old_text, new_text );
    }
    return interpreter_variant( variant( text ) );
    // Substitutes new_text for old_text in a text string.
    // Use SUBSTITUTE when you want to replace specific text in a text string.
}
#endif

/*!
 * \brief
 * FIND finds one string (find) within another text string (text),
 * and returns the number of the starting position of find, from the first character of text.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the starting position of the found text
 *
 * \details
 * FIND is case sensitive and doesn't allow wildcard characters.
 *
 * \see
 * function_findb | function_mid | function_search | function_searchb
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_find
interpreter_variant function_find( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If any of the first two arguments is no text, FIND returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string find = parameters[0].string(); // the text you want to find.
    std::string text = parameters[1].string(); // the text containing the text you want to find.
    int begin = -1;
    if ( parameters.count() > 2 ) {
        // If the third parameter is not greater than zero, FIND returns the #VALUE! error value.
        if ( parameters[2].numeric() < 1.0 ) {
            return interpreter_variant( variant::error_value );
        }
        // If the third parameter is greater than the length of text, FIND returns the #VALUE! error value.
        if ( parameters[2].numeric() >= text.length() + 1 ) {
            return interpreter_variant( variant::error_value );
        }
        begin = ( static_cast<int>( parameters[2].numeric() ) - 1 );
    } // specifies the character at which to start the search.
    // The first character in text is character number 1.
    // If you omit the third parameter, it is assumed to be 1.

    // If text is ""(empty text), FIND matches the first character in the search string.
    // That is, the character numbered by the third parameter or 1.
    if ( text == "" ) {
        return interpreter_variant( variant( static_cast<double>( std::max( 1, begin + 1 ) ) ) );
    }
    unsigned int pos = 0;
    if ( begin != -1 ) {
        pos = text.find( find, begin ) + 1;
    } else {
        pos = text.find( find, 0 ) + 1;
    }
    // If find does not appear in text, FIND returns the #VALUE! error value.
    if ( pos == 0 ) {
        return interpreter_variant( variant::error_value );
    }

    return interpreter_variant( variant( static_cast<double>( pos ) ) );
    // FIND finds one string (find) within another text string (text),
    // and returns the number of the starting position of find, from the first character of text.
    // FIND is case sensitive and doesn't allow wildcard characters.
}
#endif


/*!
 * \brief
 * MID returns a specific number of characters from a text string, starting at the position you specify,
 * based on the number of characters you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the specific number of characters from a text string
 *
 * \details
 * MIDB is for use with double-byte characters.
 *
 * \see
 * function_midb | function_code | function_find | function_left | function_right | function_search
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_mid
interpreter_variant function_mid( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first argument is no text or either other argument is nonnumeric, MID returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    std::string text = parameters[0].string(); // the text string containing the characters you want to extract.
    int start_num = static_cast<int>( parameters[1].numeric() ); // the position of the first character you want to extract in text.
    // The first character in text has start_num 1, and so on.
    int num_chars = static_cast<int>( parameters[2].numeric() ); // specifies the number of characters you want MID to return from text.
    // If start_num is less than 1 or num_chars is negative, MID returns the #VALUE! error value.
    if ( start_num < 1 || num_chars < 0 ) {
        return interpreter_variant( variant::error_value );
    }
    // If start_num is greater than the length of text, MID returns ""(empty text).
    if ( static_cast<unsigned>( start_num ) > text.length() ) {
        return interpreter_variant( variant( "" ) );
    }
    // If start_num is less than the length of text, but start_num plus num_chars exceeds the length of text,
    // MID returns the characters up to the end of text.
    text = text.substr( ( start_num - 1 ), num_chars );

    return interpreter_variant( variant( text ) );
    // MID returns a specific number of characters from a text string, starting at the position you specify,
    // based on the number of characters you specify.
}
#endif

/*!
 * \brief
 * Returns the error value #N/A.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the error value #N/A
 *
 * \details
 * #N/A is the error value that means "no value is available."
 *
 * \see
 * function_isna
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_na
interpreter_variant function_na( function_parameter& /*parameters*/ )
{
    return interpreter_variant( variant::error_n_a );
    // Returns the error value #N/A. #N/A is the error value that means "no value is available."
}
#endif

/*!
 * \brief
 * Returns the median of the given numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the median
 *
 * \details
 * The median is the number in the middle of a set of numbers; that is,
 * half the numbers have values that are greater than the median, and half have values that are less.
 *
 * \see
 * function_average | function_averagea | function_daverage | function_mode
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_median
interpreter_variant function_median( function_parameter& parameters )
{
    if ( parameters.count() == 0 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    std::vector<double> numbers;

    // Write all numbers into a vector.
    for ( int p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned int imax = sra.size();
            for ( unsigned int i = 0; i < imax; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }

                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    numbers.push_back( currenti.numeric() );
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                unsigned long int arraySize = arr.size();
                for ( unsigned long int i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        numbers.push_back( currenti.numeric() );
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try {
                    // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    numbers.push_back( currentd );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                numbers.push_back( current.numeric() );
            }
        }
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );

    // Find the middle.
    double result;
    int index = numbers.size() / 2;
    if ( numbers.size() % 2 == 1 ) {
        result = numbers[index];
    } else {
        result = ( numbers[index-1] + numbers[index] ) * 0.5;
    }
    return interpreter_variant( variant( result ) );
    // Returns the median of the given numbers.
    // The median is the number in the middle of a set of numbers; that is,
    // half the numbers have values that are greater than the median, and half have values that are less.
}
#endif

/*!
 * \brief
 * Returns the quartile of a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the quartile
 *
 * \details
 * MIN, MEDIAN, and MAX return the same value as QUARTILE when quart is equal to 0, 2, and 4, respectively.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentile | function_percentrank | function_small
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_quartile
interpreter_variant function_quartile( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant arrayx = parameters[0]; // the array or cell range of numeric values for which you want the quartile value.
    int quart = static_cast<int>( parameters[1].numeric() ); // indicates which value to return.
    // If quart < 0 or if quart > 4, QUARTILE returns the #NUM! error value.
    if ( quart < 0 || quart > 4 ) {
        return interpreter_variant( variant::error_num );
    }
    std::vector<double> numbers;
    if ( arrayx.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( arrayx.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            variant iValue = sra[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else if ( arrayx.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = arrayx.array();
        unsigned long int arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant iValue = arr[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else {
        if ( arrayx.type() == variant::type_error ) {
            return arrayx;
        }

        if ( arrayx.type() == variant::type_string ) {
            try {
                double d = boost::lexical_cast<double>( static_cast<const std::string&>( arrayx.string() ) );
                numbers.push_back( d );
            } catch ( boost::bad_lexical_cast& ) {
                return interpreter_variant( variant::error_value );
            }
        } else {
            numbers.push_back( arrayx.numeric() );
        }
    }
    unsigned long int count = numbers.size();
    // If array is empty, QUARTILE returns the #NUM! error value.
    if ( count == 0 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( count == 1 ) {
        return interpreter_variant( variant( numbers[0] ) );
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );
    unsigned long int index;
    switch ( quart ) {
        case 1: // First quartile.
            index = count / 4;
            switch ( count % 4 ) {
                case 0:
                    return interpreter_variant( variant( ( numbers[index-1] + 3.0 * numbers[index] ) * 0.25 ) );
                case 1:
                    return interpreter_variant( variant( numbers[index] ) );
                case 2:
                    return interpreter_variant( variant( ( 3.0 * numbers[index] + numbers[index+1] ) * 0.25 ) );
                case 3:
                    return interpreter_variant( variant( ( numbers[index] + numbers[index+1] ) * 0.5 ) );
            }
        case 2: // Median value.
            index = count / 2;
            if ( count % 2 == 1 ) {
                return interpreter_variant( variant( numbers[index] ) );
            } else {
                return interpreter_variant( variant( ( numbers[index - 1] + numbers[index] ) * 0.5 ) );
            }
        case 3: // Third quartile.
            index = ( count * 3 ) / 4;
            switch ( count % 4 ) {
                case 0:
                    return interpreter_variant( variant( ( 3.0 * numbers[index-1] + numbers[index] ) * 0.25 ) );
                case 1:
                    return interpreter_variant( variant( numbers[index] ) );
                case 2:
                    return interpreter_variant( variant( ( numbers[index-1] + 3.0 * numbers[index] ) * 0.25 ) );
                case 3:
                    return interpreter_variant( variant( ( numbers[index-1] + numbers[index] ) * 0.5 ) );
            }
        case 4: // Maximum value.
            return interpreter_variant( variant( numbers[ count - 1 ] ) );
    }

    // moved here just to make g++ happy
    // case 0: Minimum value.
    return interpreter_variant( variant( numbers[0] ) );

    // Returns the quartile of a data set.
}
#endif

/*!
 * \brief
 * Returns the k-th percentile of values in a range.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the k-th percentile
 *
 * \details
 * If k is not a multiple of 1/(n-1), PERCENTILE interpolates to determine the value at the k-th percentile.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentrank | function_quartile | function_small
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_percentile
interpreter_variant function_percentile( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant arrayx = parameters[0]; // array or range of data that defines relative standing.
    // If k is nonnumeric, PERCENTILE returns the #VALUE! error value.
    if ( parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double k = parameters[1].numeric(); // the percentile value in the range 0..1, inclusive.
    // If k < 0 or if k > 1, PERCENTILE returns the #NUM! error value.
    if ( k < 0.0 || k > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    std::vector<double> numbers;
    if ( arrayx.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( arrayx.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            variant iValue = sra[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else if ( arrayx.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = arrayx.array();
        unsigned long int arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant iValue = arr[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else {
        if ( arrayx.type() == variant::type_error ) {
            return arrayx;
        }

        if ( arrayx.type() == variant::type_string ) {
            try {
                double d = boost::lexical_cast<double>( static_cast<const std::string&>( arrayx.string() ) );
                numbers.push_back( d );
            } catch ( boost::bad_lexical_cast& ) {
                return interpreter_variant( variant::error_value );
            }
        } else {
            numbers.push_back( arrayx.numeric() );
        }
    }
    unsigned long int n = numbers.size();
    // If array is empty or contains more than 8191 data points, PERCENTILE returns the #NUM! error value.
    if ( n == 0 || n > 8191 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( n == 1 ) {
        return interpreter_variant( variant( numbers[0] ) );
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );
    unsigned long int index = static_cast<unsigned long int>( k * ( n - 1.0 ) );
    if ( k * ( n - 1.0 ) == static_cast<double>( index ) ) {
        return interpreter_variant( variant( numbers[index] ) );
    }
    // If k is not a multiple of 1/(n-1), PERCENTILE interpolates to determine the value at the k-th percentile.
    double result = numbers[index] + ( numbers[index+1] - numbers[index] ) * ( k * ( n - 1.0 ) - index );
    return interpreter_variant( variant( result ) );
    // Returns the k-th percentile of values in a range.
}
#endif

/*!
 * \brief
 * Returns the character specified by a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the character specified by the number
 *
 * \details
 * The argument is a number between 1 and 255 specifying which character you want.
 * The character is from the character set used by your computer.
 *
 * \see
 * function_code
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_char
interpreter_variant function_char( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, CHAR returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    int number = static_cast<int>( parameters[0].numeric() ); //a number between 1 and 255 specifying which character you want.
    // The character is from the character set used by your computer.
    // If number < 1 or number > 255, CHAR returns the #VALUE! error value.
    if ( number < 1 || number > 255 ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( boost::lexical_cast<std::string>( static_cast<char>( number ) ) ) );
    // Returns the character specified by a number.
}
#endif

/*!
 * \brief
 * Returns a numeric code for the first character in a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the numeric code for the first character in the text string
 *
 * \details
 * The returned code corresponds to the character set used by your computer.
 *
 * \see
 * function_char
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_code
interpreter_variant function_code( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is no text, CODE returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }
    std::string text = parameters[0].string(); // the text for which you want the code of the first character.
    return interpreter_variant( variant( static_cast<double>( ( int )text[0] ) ) );
    // Returns a numeric code for the first character in a text string.
    // The returned code corresponds to the character set used by your computer.
}
#endif

/*!
 * \brief
 * Adds the cells specified by a given criteria.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the cells specified by the criteria
 *
 * \details
 * Use criteria in the form of a number, expression, or text that defines which cells will be added.
 * For example, criteria can be expressed as 32, "32", ">32", "apples".
 *
 * \see
 * function_countif | function_if | function_sum
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sumif
interpreter_variant function_sumif( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first parameter is no range, SUMIF returns the #VALUE! error value.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }

    // If "sum_range" is empty, then "sum_range" corresponds "criteria"
    interpreter_variant addthis = interpreter_variant( variant( "" ) );
    if ( parameters.count() < 3 ) {
        addthis = parameters[1];
    } else {
        addthis = parameters[2];
    }

    // If a number is given, convert into String
    if ( parameters[1].type() == variant::type_double ) {
        std::stringstream ssStream;
        ssStream << parameters[1].numeric();
        interpreter_variant newVal = interpreter_variant( variant( ssStream.str() ) );
        parameters[1] = newVal;
    }

    // Comparison method, always assuming String
    int compareMethod = 0;
    double lookfor = 0;
    if ( parameters[1].type() == variant::type_string ) {
        // Smaller
        if ( ( parameters[1].string() ).substr( 0, 1 ) == "<" ) {
            compareMethod = 1;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        }
        // Greater
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == ">" ) {
            compareMethod = 2;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        }
        // Equal
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "=" ) {
            compareMethod = 3;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        } else {
            std::stringstream ssStream( ( parameters[1].string() ) );
            ssStream >> lookfor;
        }
    } else {
        return interpreter_variant( variant::error_value );
    }

    double result = 0;
    range_reference& rref1 = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra1( rref1, parameters.context() );
    unsigned int imax1 = rref1.actualize().position().count();
    range_reference& rref2 = range_reference_cast( addthis.reference() );
    sparse_range_array sra2( rref2, parameters.context() );
    for ( unsigned int i = 0; i < imax1; i++ ) {
        if ( sra1[i].type() == variant::type_double ) {
            if ( compareMethod == 1 && sra1[i].numeric() < lookfor ) {
                result = result + sra2[i].numeric();
            } else if ( compareMethod == 2 && sra1[i].numeric() > lookfor ) {
                result = result + sra2[i].numeric();
            } else if ( ( compareMethod == 3 || compareMethod == 0 ) && sra1[i].numeric() == lookfor ) {
                result = result + sra2[i].numeric();
            }
        }
    }
    return interpreter_variant( variant( result ) );
    // Adds the cells specified by a given criteria.
}
#endif

/*!
 * \brief
 * Counts the number of cells within a range that meet the given criteria.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the cells within the range that meet the given criteria
 *
 * \details
 * Use criteria in the form of a number, expression, or text that defines which cells will be counted.
 * For example, criteria can be expressed as 32, "32", ">32", "apples".
 *
 * \see
 * function_sumif | function_if | function_countblank
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_countif
interpreter_variant function_countif( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first parameter is no range, COUNTIF returns the #VALUE! error value.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }

    // If an array is given, only take the first value.
    if ( parameters[1].type() == variant::type_array ) {
        const variant::sparse_array_type& arr = parameters[1].array();
        interpreter_variant newVal = interpreter_variant( arr[0] );
        parameters[1] = newVal;
    }

    // If a number is given, convert into String.
    if ( parameters[1].type() == variant::type_double ) {
        std::stringstream ssStream;
        ssStream << parameters[1].numeric();
        interpreter_variant newVal = interpreter_variant( ssStream.str() );
        parameters[1] = newVal;
    }

    // If a boolean is given, convert into String.
    if ( parameters[1].type() == variant::type_bool ) {
        if ( parameters[1].numeric() == 0 ) {
            parameters[1] = interpreter_variant( variant( "false" ) );
        } else {
            parameters[1] = interpreter_variant( variant( "true" ) );
        }
    }

    // If empty is given, take empty String.
    if ( parameters[1].type() == variant::type_empty ) {
        parameters[1] = interpreter_variant( variant( "" ) );
    }

    // Comparison method, always assuming String.
    int compareMethod = 0;
    std::string compareWith = "";
    if ( parameters[1].type() == variant::type_string ) {
        // Unequal
        if ( ( parameters[1].string() ).substr( 0, 2 ) == "<>" ) {
            compareMethod = 1;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Smaller equal
        else if ( ( parameters[1].string() ).substr( 0, 2 ) == "<=" ) {
            compareMethod = 2;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Greater equal
        else if ( ( parameters[1].string() ).substr( 0, 2 ) == ">=" ) {
            compareMethod = 3;
            compareWith = ( parameters[1].string() ).substr( 2 );
        }
        // Smaller
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "<" ) {
            compareMethod = 4;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Greater
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == ">" ) {
            compareMethod = 5;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Equal
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "=" ) {
            compareMethod = 0;
            compareWith = ( parameters[1].string() ).substr( 1 );
        }
        // Without operator
        else {
            compareWith = parameters[1].string();
        }
    } else {
        return interpreter_variant( variant::error_value );
    }

    double result = 0;
    range_reference& rref = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra( rref, parameters.context() );

    for ( size_t i = 0; i < sra.size(); i++ ) {
        switch ( sra[i].type() ) {
            case variant::type_double:
                try {
                    double compareDouble = boost::lexical_cast<double>( compareWith );
                    switch ( compareMethod ) {
                        case 0:
                            if ( sra[i].numeric() == compareDouble ) {
                                result++;
                            }
                            break;
                        case 1:
                            if ( sra[i].numeric() != compareDouble ) {
                                result++;
                            }
                            break;
                        case 2:
                            if ( sra[i].numeric() <= compareDouble ) {
                                result++;
                            }
                            break;
                        case 3:
                            if ( sra[i].numeric() >= compareDouble ) {
                                result++;
                            }
                            break;
                        case 4:
                            if ( sra[i].numeric() < compareDouble ) {
                                result++;
                            }
                            break;
                        case 5:
                            if ( sra[i].numeric() > compareDouble ) {
                                result++;
                            }
                            break;
                        default:
                            if ( sra[i].numeric() == compareDouble ) {
                                result++;
                            }
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    continue;
                }
                break;
            case variant::type_bool:
                try {
                    std::string lowerString = compareWith;
                    boost::algorithm::to_lower( lowerString );
                    bool compareBool = boost::lexical_cast<bool>( lowerString );
                    switch ( compareMethod ) {
                        case 0:
                            if ( sra[i].numeric() == compareBool ) {
                                result++;
                            }
                            break;
                        case 1:
                            if ( sra[i].numeric() != compareBool ) {
                                result++;
                            }
                            break;
                        case 2:
                            if ( sra[i].numeric() <= compareBool ) {
                                result++;
                            }
                            break;
                        case 3:
                            if ( sra[i].numeric() >= compareBool ) {
                                result++;
                            }
                            break;
                        case 4:
                            if ( sra[i].numeric() < compareBool ) {
                                result++;
                            }
                            break;
                        case 5:
                            if ( sra[i].numeric() > compareBool ) {
                                result++;
                            }
                            break;
                        default:
                            if ( sra[i].numeric() == compareBool ) {
                                result++;
                            }
                    }
                } catch ( boost::bad_lexical_cast& ) {
                    continue;
                }
                break;
            case variant::type_string:
                switch ( compareMethod ) {
                    case 0:
                        if ( boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 1:
                        if ( !boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 2:
                        if ( !boost::algorithm::ilexicographical_compare( compareWith, sra[i].string() ) ) {
                            result++;
                        }
                        break;
                    case 3:
                        if ( !boost::algorithm::ilexicographical_compare( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 4:
                        if ( boost::algorithm::ilexicographical_compare( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                        break;
                    case 5:
                        if ( boost::algorithm::ilexicographical_compare( compareWith, sra[i].string() ) ) {
                            result++;
                        }
                        break;
                    default:
                        if ( boost::algorithm::iequals( sra[i].string(), compareWith ) ) {
                            result++;
                        }
                }
                break;
            default:
                continue;
        }
    }
    return interpreter_variant( variant( result ) );
    // Counts the number of cells within a range that meet the given criteria.
}
#endif

/*!
 * \brief
 * Returns true, if the argument refers to a reference (CELL or RANGE).
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value, if the argument refers to a reference
 *
 * \details
 *
 * \see
 * function_istext | function_isnontext | function_isnumber | function_islogical
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_isref
interpreter_variant function_isref( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[0].i_type() == interpreter_variant::type_value ) {
        return interpreter_variant( variant( false ) );
    } else {
        return interpreter_variant( variant( true ) );
    }
    // Returns true, if the argument refers to a reference (CELL or RANGE).
}
#endif

/*!
 * \brief
 * Returns the number of rows in a reference or array.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of rows
 *
 * \details
 *
 * \see
 * function_columns | function_row
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_rows
interpreter_variant function_rows( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If the argument is no range or array, ROWS returns the #VALUE! error value.
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        return interpreter_variant( variant( static_cast<double>( rref.actualize().position().row_count() ) ) );
    } else if ( parameters[0].type() == variant::type_array ) {
        const variant::sparse_array_type& arr = parameters[0].array();
        boost::int_fast32_t arraySize = arr.size();
        boost::int_fast32_t column_width = parameters[0].column_width();
        boost::int_fast32_t rows = arraySize / column_width;
        return interpreter_variant( static_cast<double>( rows ) );
    } else {
        return interpreter_variant( variant::error_value );
    }
    // Returns the number of rows in a reference or array.
}
#endif

/*!
 * \brief
 * Returns the number of columns in an array or reference.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of columns
 *
 * \details
 *
 * \see
 * function_rows | function_column
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_columns
interpreter_variant function_columns( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If the argument is no range or array, COLUMNS returns the #VALUE! error value.
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        return interpreter_variant( variant( static_cast<double>( rref.actualize().position().column_count() ) ) );
    } else if ( parameters[0].type() == variant::type_array ) {
        return interpreter_variant( static_cast<double>( parameters[0].column_width() ) );
    } else {
        return interpreter_variant( variant::error_value );
    }
    // Returns the number of columns in an array or reference.
}
#endif

/*!
 * \brief
 * Returns the column number of the given reference.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the column number
 *
 * \details
 * If reference is a range of cells, and if COLUMN is entered as a horizontal array,
 * COLUMN returns the column numbers of reference as a horizontal array.
 * reference cannot refer to multiple areas.
 *
 * \see
 * function_row | function_columns
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_column
interpreter_variant function_column( function_parameter& parameters )
{
    if ( parameters.count() > 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If reference is omitted, it is assumed to be the reference of the cell in which the COLUMN function appears.
    if ( parameters.count() == 0 ) {
        if ( parameters.context().has_array_return_type() ) {
            sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
            //unsigned int rowCount = arrayCoverage.get_row_count();
            unsigned int columnCount = arrayCoverage.column_count();
            /*unsigned int arraySize = arrayCoverage.count();
            variant result( variant::type_array, arraySize, columnCount );
            variant::sparse_array_type& resultArray = result.array();
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
            variant colNumV = variant( static_cast<double>( cx.get_current_cell()->get_position().column() + 1 + coli ) );
            resultArray.push_back( colNumV );
            }
            }*/
            variant::sparse_array_type resultArray( columnCount );
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
                variant colNumV = variant( static_cast<double>( parameters.context().caller()->position().column() + 1 + coli ) );
                resultArray.push_back( colNumV );
            }
            variant result( resultArray, columnCount );
            return interpreter_variant( result );
        } else {
            return interpreter_variant( variant( static_cast<double>( parameters.context().caller()->position().column() + 1 ) ) );
        }
    }

    //range& coveredRange = *static_cast<range*>( parameters[0].reference() );
    sheet_range coveredRange( sheet_point( 0, 0 ) );
    switch ( parameters[0].i_type() ) {
        case interpreter_variant::type_range: {
            range_reference& rrefr = range_reference_cast( parameters[0].reference() );
            coveredRange = rrefr.actualize().position();
        }
        break;
        default:
            //assert( "invalid parameter" );
            return interpreter_variant( variant::error_ref );
    }

    if ( coveredRange.column_count() == 1 ) {
        variant colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 ) );
        /*if ( cx.is_array_formula() ) {
        BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( colNumV );
        }
        }
        return interpreter_variant( result );
        } else {
        return interpreter_variant( colNumV );
        }*/
        return interpreter_variant( colNumV );
    }

    if ( parameters.context().has_array_return_type() ) {
        /*BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        variant colNumV;
        if ( coli < coveredRange.get_column_count() ) {
        colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 + coli ) );
        } else {
        colNumV = variant::error_n_a;
        }
        resultArray.push_back( colNumV );
        }
        }*/
        unsigned int rowLength = coveredRange.column_count();
        variant::sparse_array_type resultArray( rowLength );
        for ( unsigned int coli = 0; coli < rowLength; coli++ ) {
            variant colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 + coli ) );
            resultArray.push_back( colNumV );
        }
        variant result( resultArray, rowLength );
        return interpreter_variant( result );
    } else {
        return interpreter_variant( variant( static_cast<double>( coveredRange.upper_left().column() + 1 ) ) );
    }
    // TODO: Choose the right column, when we can handle array formulas.
    // Returns the column number of the given reference.
}
#endif

/*!
 * \brief
 * Returns the row number of a reference.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the row number
 *
 * \details
 * If reference is a range of cells, and if ROW is entered as a vertical array,
 * ROW returns the row numbers of reference as a vertical array.
 * reference cannot refer to multiple areas.
 *
 * \see
 * function_column | function_rows
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_row
interpreter_variant function_row( function_parameter& parameters )
{
    if ( parameters.count() > 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If reference is omitted, it is assumed to be the reference of the cell in which the ROW function appears.
    if ( parameters.count() == 0 ) {
        if ( parameters.context().has_array_return_type() ) {
            sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
            unsigned int rowCount = arrayCoverage.row_count();
            /*unsigned int columnCount = arrayCoverage.get_column_count();
            unsigned int arraySize = arrayCoverage.count();
            variant result( variant::type_array, arraySize, columnCount );
            variant::sparse_array_type& resultArray = result.array();
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            variant rowNumV = variant( static_cast<double>( cx.get_current_cell()->get_position().row() + 1 + rowi ) );
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
            resultArray.push_back( rowNumV );
            }
            }*/
            variant::sparse_array_type resultArray( rowCount );
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
                variant rowNumV = variant( static_cast<double>( parameters.context().caller()->position().row() + 1 + rowi ) );
                resultArray.push_back( rowNumV );
            }
            variant result( resultArray, 1 );
            return interpreter_variant( result );
        } else {
            return interpreter_variant( static_cast<double>( parameters.context().caller()->position().row() + 1 ) );
        }
    }

    sheet_range coveredRange( sheet_point( 0, 0 ) );
    switch ( parameters[ 0 ].i_type() ) {
        case interpreter_variant::type_range: {
            range_reference& rref = range_reference_cast( parameters[0].reference() );
            coveredRange = rref.actualize().position();
        }
        break;

        default:
            //assert( "invalid parameter" );
            return interpreter_variant( variant::error_ref );
    }

    if ( coveredRange.row_count() == 1 ) {
        variant rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 ) );
        /*if ( cx.is_array_formula() ) {
        BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( rowNumV );
        }
        }
        return interpreter_variant( result );
        } else {
        return interpreter_variant( rowNumV );
        }*/
        return interpreter_variant( rowNumV );
    }

    if ( parameters.context().has_array_return_type() ) {
        /*BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        variant rowNumV;
        if ( rowi < coveredRange.get_row_count() ) {
        rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 + rowi ) );
        } else {
        rowNumV = variant::error_n_a;
        }
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( rowNumV );
        }
        }*/
        unsigned int columnLength = coveredRange.row_count();
        variant::sparse_array_type resultArray( columnLength );
        for ( unsigned int rowi = 0; rowi < columnLength; rowi++ ) {
            variant rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 + rowi ) );
            resultArray.push_back( rowNumV );
        }
        variant result( resultArray, 1 );
        return interpreter_variant( result );
    } else {
        return interpreter_variant( variant( static_cast<double>( coveredRange.upper_left().row() + 1 ) ) );
    }
    // TODO: Choose the right row, when we can handle array formulas.
    // Returns the row number of a reference.
}
#endif

/*!
 * \brief
 * Uses index_num to return a value from the list of value arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the index_num-th value from the list of value arguments
 *
 * \details
 * Use CHOOSE to select one of up to 29 values based on the index number.
 *
 * \see
 * function_index
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#ifdef function_choose
interpreter_variant function_choose( function_parameter& parameters )
{
    // If there are less than 2 parameters, or if index_num is nonnumeric, CHOOSE returns the #VALUE! error value.
    if ( parameters.count() < 2 || parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    unsigned int index_num = static_cast<unsigned int>( parameters[0].numeric() ); // specifies which value argument is selected.
    // index_num must be a number between 1 and at most 29, or a formula or reference to a cell containing a number between 1 and at most 29.
    // If index_num is less than 1 or greater than the number of the last value in the list, CHOOSE returns the #VALUE! error value.
    if ( index_num < 1 || index_num > parameters.count() - 1 ) {
        return interpreter_variant( variant::error_value );
    }
    return parameters[index_num];
    // Uses index_num to return a value from the list of value arguments.
    // Use CHOOSE to select one of up to 29 values based on the index number.
}
#endif

/*!
 * \brief
 * Counts how often values occur within a range of values, and returns a vertical array of numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the vertical array of numbers
 *
 * \details
 * must be entered as an array formula (CTRL SHIFT ENTER)
 *
 * \see
 * function_count | function_dcount
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_frequency
interpreter_variant function_frequency( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    std::vector<double> frontiers;
    // Evaluate second parameter and fill bins-array of frontiers.
    if ( parameters[1].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[1].reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            if ( sra[i].type() == variant::type_double ) {
                frontiers.push_back( sra[i].numeric() );
            }
        }
    } else if ( parameters[1].type() == variant::type_array ) {
        const variant::sparse_array_type& arrBins = parameters[1].array();
        size_t arraySize = arrBins.size();
        for ( size_t i = 0; i < arraySize; i++ ) {
            if ( arrBins[i].type() == variant::type_double ) {
                frontiers.push_back( arrBins[i].numeric() );
            }
        }
    } else {
        if ( parameters[1].type() == variant::type_error ) {
            return parameters[1];
        }

        if ( parameters[1].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        frontiers.push_back( parameters[1].numeric() );
    }
    std::vector<double> sorted( frontiers );
    std::sort( sorted.begin(), sorted.end() ); // upwards
    std::vector<bool> got;
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        got.push_back( false );
    }
    std::vector<double> lowerFrontiers;
    // Set correlated lowerFrontiers.
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        for ( size_t j = 0; j < sorted.size(); j++ ) {
            if ( sorted[j] == frontiers[i] && !got[j] ) {
                got[j] = true;
                if ( j == 0 ) {
                    lowerFrontiers.push_back( -std::numeric_limits<double>::max() );
                } else {
                    lowerFrontiers.push_back( sorted[j-1] );
                }
            }
        }
    }
    frontiers.push_back( std::numeric_limits<double>::max() );
    lowerFrontiers.push_back( sorted[sorted.size() - 1] );
    std::vector<int> counter;
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        counter.push_back( 0 );
    }
    // Count data from first parameter.
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref0 = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra0( rref0, parameters.context() );
        unsigned int imax0 = sra0.size();
        for ( unsigned int i = 0; i < imax0; i++ ) {
            variant vali = sra0[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }

            if ( vali.type() == variant::type_double ) {
                for ( size_t i = 0; i < frontiers.size(); i++ ) {
                    if ( lowerFrontiers[i] < vali.numeric() && vali.numeric() <= frontiers[i] ) {
                        counter[i]++;
                        break;
                    }
                }
            }
        }
    } else if ( parameters[0].type() == variant::type_array ) {
        const variant::sparse_array_type& arrData = parameters[0].array();
        size_t arraySize = arrData.size();
        for ( size_t i = 0; i < arraySize; i++ ) {
            variant vali = arrData[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }

            if ( vali.type() == variant::type_double ) {
                for ( size_t i = 0; i < frontiers.size(); i++ ) {
                    if ( lowerFrontiers[i] < vali.numeric() && vali.numeric() <= frontiers[i] ) {
                        counter[i]++;
                        break;
                    }
                }
            }
        }
    } else {
        if ( parameters[0].type() == variant::type_error ) {
            return parameters[0];
        }

        if ( parameters[0].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        for ( size_t i = 0; i < frontiers.size(); i++ ) {
            if ( lowerFrontiers[i] < parameters[0].numeric() && parameters[0].numeric() <= frontiers[i] ) {
                counter[i]++;
                break;
            }
        }
    }
    // Fill return-array.
    if ( parameters.context().has_array_return_type() ) {
        sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
        unsigned int rowCount = arrayCoverage.row_count();
        unsigned int columnCount = arrayCoverage.column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant::sparse_array_type resultArray( arraySize );
        variant res;
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            if ( rowi < counter.size() ) {
                res = variant( static_cast<double>( counter[rowi] ) );
            } else {
                res = variant::error_n_a;
            }
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
                resultArray.push_back( res );
            }
        }
        variant result( resultArray, columnCount );
        return interpreter_variant( result );
    }

    return interpreter_variant( variant( static_cast<double>( counter[0] ) ) );
}
#endif

/*!
 * \brief
 * Converts radians into degrees.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the corresponding number of degrees
 *
 * \details
 * 360 degrees make a whole circle.
 *
 * \see
 * function_radians
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_degrees
interpreter_variant function_degrees( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, DEGREES returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double rads = parameters[0].numeric(); // the angle in radians that you want to convert.
    double degs = rads * 180.0 / M_PI;
    return interpreter_variant( variant( degs ) );
    // Converts radians into degrees.
}
#endif

/*!
 * \brief
 * Converts degrees to radians.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the corresponding number of radians
 *
 * \details
 * 2*PI make a whole circle.
 *
 * \see
 * function_degrees
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_radians
interpreter_variant function_radians( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, RADIANS returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double degs = parameters[0].numeric(); // the angle in degrees that you want to convert.
    double rads = degs * M_PI / 180.0;
    return interpreter_variant( variant( rads ) );
    // Converts degrees to radians.
}
#endif

/*!
 * \brief
 * Returns the factorial of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the factorial
 *
 * \details
 * The factorial of a number is equal to 1*2*3*...*number.
 *
 * \see
 * function_factdouble | function_product
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_fact
interpreter_variant function_fact( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the nonnegative number you want the factorial of.
    // If number < 0 or number >= 171, FACT returns the #NUM! error value.
    // double ends at 1.7976931348623158e+308
    if ( number < 0.0 || number >= 171 ) {
        return interpreter_variant( variant::error_num );
    }

    double product = 1.0;
    // If number is not an integer, it is truncated.
    for ( int i = 2; i <= number; i++ ) {
        product *= i;
    }
    return interpreter_variant( variant( product ) );
    // Returns the factorial of a number. The factorial of a number is equal to 1*2*3*...*number.
}
#endif

/*!
 * \brief
 * Returns the number of permutations for a given number of objects, that can be selected from number objects.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of permutations
 *
 * \details
 * A permutation is any set or subset of objects, where internal order is significant.
 *
 * \see
 * function_fact | function_combin
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_permut
interpreter_variant function_permut( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If number or number_chosen is nonnumeric, PERMUT returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // Both arguments are truncated to integers.
    // describes the number of objects.
    long long number = static_cast<long long>( parameters[0].numeric() );
    // describes the number of objects in each permutation.
    long long number_chosen = static_cast<long long>( parameters[1].numeric() );

    // If number <= 0 or if number_chosen < 0, PERMUT returns the #NUM! error value.
    // If number < number_chosen, PERMUT returns the #NUM! error value.
    if ( number <= 0 || number_chosen < 0 || number < number_chosen ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 1.0;
    for ( long long i = 0; i < number_chosen; i++ ) {
        result *= static_cast<double>( number - i );
    }
    return interpreter_variant( variant( result ) );
    // Returns the number of permutations for a given number of objects, that can be selected from number objects.
    // A permutation is any set or subset of objects, where internal order is significant.
}
#endif

#ifdef function_combin
// combin helps to calculate function_combin and function_hypgeomdist.
long long combin( long long number, long long number_chosen )
{
    if ( number < 0 || number_chosen < 0 || number < number_chosen ) {
        return 1L;
    }

    double result = 1.0;
    long long minNcDiff = number_chosen < number - number_chosen ? number_chosen : number - number_chosen;
    // Factorize only to the minimum.
    for ( long long i = 0; i < minNcDiff; i++ ) {
        result *= static_cast<double>( number - i ) / static_cast<double>( i + 1 );
    }

    return static_cast<long long>( result + 0.5 );
    // Returns the number of combinations (groups with number_chosen items) for a given number of items (number).
}


/*!
 * \brief
 * Returns the number of combinations for a given number of items.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of combinations
 *
 * \details
 * Use COMBIN to determine the total possible number of groups for a given number of items.
 *
 * \see
 * function_fact | function_permut
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_combin( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If either argument is nonnumeric, COMBIN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // Numeric arguments are truncated to integers.
    // the number of items.
    long long number = static_cast<long long>( parameters[0].numeric() );
    // the number of items in each combination.
    long long number_chosen = static_cast<long long>( parameters[1].numeric() );

    // If number < 0, number_chosen < 0, or number < number_chosen, COMBIN returns the #NUM! error value.
    if ( number < 0 || number_chosen < 0 || number < number_chosen ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( static_cast<double>( combin( number, number_chosen ) ) ) );
    // Returns the number of combinations (groups with number_chosen items) for a given number of items (number).
}
#endif

/*!
 * \brief
 * Returns the type of value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the type of value
 *
 * \details
 * Use TYPE when the behavior of another function depends on the type of value in a particular cell.
 *
 * \see
 * function_isblank | function_iserror | function_islogical | function_isnumber | function_isref | function_istext
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_type
interpreter_variant function_type( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is a number, TYPE returns 1.
    if ( parameters[0].type() == variant::type_double ) {
        return interpreter_variant( variant( 1.0 ) );
    }
    // If the argument is text, TYPE returns 2.
    if ( parameters[0].type() == variant::type_string ) {
        return interpreter_variant( variant( 2.0 ) );
    }
    // If the argument is a logical value, TYPE returns 4.
    if ( parameters[0].type() == variant::type_bool ) {
        return interpreter_variant( variant( 4.0 ) );
    }
    // If the argument is an array, TYPE returns 64.
    if ( parameters[0].type() == variant::type_array ) {
        return interpreter_variant( variant( 64.0 ) );
    }
    // If the argument is an error value, TYPE returns 16.
    return interpreter_variant( variant( 16.0 ) );
    // Returns the type of value.
}
#endif

/*!
 * \brief
 * Returns the hyperbolic cosine of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the hyperbolic cosine
 *
 * \details
 * COSH(z)=0.5*(EXP(z)+EXP(-z))
 *
 * \see
 * function_acosh | function_sinh | function_tanh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_cosh
interpreter_variant function_cosh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, COSH returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( cosh( parameters[0].numeric() ) ) );
    // Returns the hyperbolic cosine of a number.
}
#endif

/*!
 * \brief
 * Returns the hyperbolic sine of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the hyperbolic sine
 *
 * \details
 * SINH(z)=0.5*(EXP(z)-EXP(-z))
 *
 * \see
 * function_asinh | function_cosh | function_tanh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sinh
interpreter_variant function_sinh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, SINH returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( sinh( parameters[0].numeric() ) ) );
    // Returns the hyperbolic sine of a number.
}
#endif

/*!
 * \brief
 * Returns the hyperbolic tangent of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the hyperbolic tangent
 *
 * \details
 * TANH(z)=SINH(z)/COSH(z)
 *
 * \see
 * function_atanh | function_sinh | function_cosh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_tanh
interpreter_variant function_tanh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, TANH returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return interpreter_variant( variant( tanh( parameters[0].numeric() ) ) );
    // Returns the hyperbolic tangent of a number.
}
#endif

/*!
 * \brief
 * Creates a cell address as text, given specified row and column numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the cell address as text
 *
 * \details
 *
 * \see
 * function_column | function_row | function_offset
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_address
interpreter_variant function_address( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // get parameters
    std::string myString = "";
    int row_num = static_cast<int>( parameters[0].numeric() ); // the row number to use in the cell reference.
    int column_num = static_cast<int>( parameters[1].numeric() ); // the column number to use in the cell reference.
    int abs_num = 1;
    if ( parameters.count() >= 3 && parameters[2].type() != variant::type_empty ) {
        abs_num = static_cast<int>( parameters[2].numeric() ); // specifies the type of reference to return.
    }
    bool a1 = true;
    if ( parameters.count() >= 4 && parameters[3].type() != variant::type_empty ) {
        a1 = parameters[3].numeric() != 0.0; // logical value that specifies the A1 or R1C1 reference style.
        // If a1 is true or omitted, ADDRESS returns an A1-style reference; if false, ADDRESS returns an R1C1-style reference.
    }
    std::string sheet_text = ""; // text specifying the name of the worksheet to be used as the external reference.
    // If sheet_text is omitted, no sheet name is used.
    if ( parameters.count() == 5 ) {
        sheet_text = parameters[4].string();
    }

    // build together
    if ( sheet_text != "" ) {
        myString.append( sheet_text + "!" );
    }

    if ( a1 ) {
        if ( abs_num == 1 || abs_num == 3 ) {
            myString.append( "$" );
        }
        myString.append( a1conversion::to_a1::column( column_num - 1, reference::relative ) );
        if ( abs_num == 1 || abs_num == 2 ) {
            myString.append( "$" );
        }
        myString.append( boost::lexical_cast<std::string>( row_num ) );
    } else {
        myString.append( "R" );
        if ( abs_num == 4 || abs_num == 3 ) {
            myString.append( "[" );
        }
        myString.append( boost::lexical_cast<std::string>( column_num ) );
        if ( abs_num == 4 || abs_num == 3 ) {
            myString.append( "]" );
        }
        myString.append( "C" );
        if ( abs_num == 4 || abs_num == 2 ) {
            myString.append( "[" );
        }
        myString.append( boost::lexical_cast<std::string>( row_num ) );
        if ( abs_num == 4 || abs_num == 2 ) {
            myString.append( "]" );
        }
    }

    return interpreter_variant( variant( myString ) );
    // Creates a cell address as text, given specified row and column numbers.
}
#endif

/*!
 * \brief
 * Returns the future value of an investment based on periodic, constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the future value
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest, use 12%/12 for rate and 4*12 for nper.
 * If you make annual payments on the same loan, use 12% for rate and 4 for nper.
 * For all the arguments, cash you pay out, such as deposits to savings, is represented by negative numbers;
 * cash you receive, such as dividend checks, is represented by positive numbers.
 *
 * \see
 * function_fvschedule | function_ipmt | function_nper | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_fv
interpreter_variant function_fv( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double nper = parameters[1].numeric(); // the total number of payment periods in an annuity.
    double pmt  = parameters[2].numeric(); // the payment made each period.
    // It cannot change over the life of the annuity.
    // Typically, pmt contains principal and interest but no other fees or taxes.
    double pv   = 0; // the present value, or the lump-sum amount that a series of future payments is worth right now.
    // If pv is omitted, it is assumed to be zero, and you must include the pmt argument.
    if ( parameters.count() >= 4 && parameters[3].type() != variant::type_empty ) {
        pv = parameters[3].numeric();
    }
    bool typ = false; // 0 or 1, indicates when payments are due. If typ is omitted, it is assumed to be 0.
    if ( parameters.count() >= 5 ) {
        typ = parameters[4].numeric() != 0.0;
    }

    if ( rate == 0 ) {
        return interpreter_variant( variant( -1 * ( pv + ( nper * pmt ) ) ) );
    } else {
        double tmp = rate + 1;
        return interpreter_variant( variant( ( ( 1 - pow( tmp, nper ) ) * ( typ ? tmp : 1 ) * pmt ) / rate  - pv * pow( tmp, nper ) ) );
    }
    // Returns the future value of an investment based on periodic, constant payments and a constant interest rate.
}
#endif

/*!
 * \brief
 * Returns the inverse hyperbolic cosine of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse hyperbolic cosine
 *
 * \details
 * number must be >= 1.
 * ACOSH(COSH(number))=number
 *
 * \see
 * function_cosh | function_asinh | function_atanh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_acosh
interpreter_variant function_acosh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ACOSH returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x  = parameters[0].numeric();
    // If x < 1, ACOSH returns the #NUM! error value.
    if ( x < 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    //if ( !( x >= 1.0 ) ) return interpreter_variant( sqrt( -1.0 ) );
    return interpreter_variant( variant( log( x + sqrt( x * x - 1.0 ) ) ) );
    // Returns the inverse hyperbolic cosine of a number.
}
#endif

/*!
 * \brief
 * Returns the inverse hyperbolic sine of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse hyperbolic sine
 *
 * \details
 * ASINH(SINH(number))=number
 *
 * \see
 * function_sinh | function_acosh | function_atanh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_asinh
interpreter_variant function_asinh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ASINH returns the #VALUE! error value.
    double x  = parameters[0].numeric();
    return interpreter_variant( variant( log( x + sqrt( x * x + 1.0 ) ) ) );
    // Returns the inverse hyperbolic sine of a number.
}
#endif

/*!
 * \brief
 * Returns the inverse hyperbolic tangent of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse hyperbolic tangent
 *
 * \details
 * number must be between -1 and 1 (excluding -1 and 1).
 * ATANH(TANH(number))=number
 *
 * \see
 * function_tanh | function_acosh | function_asinh
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_atanh
interpreter_variant function_atanh( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ATANH returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x  = parameters[0].numeric();
    // If x <= -1.0 or x >= 1.0, ATANH returns the #NUM! error value.
    if ( x <= -1.0 || x >= 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    //if ( !( x > -1.0 && x < 1.0 ) ) return interpreter_variant( sqrt( -1.0 ) );
    return interpreter_variant( variant( log( ( 1.0 + x ) / ( 1.0 - x ) ) / 2.0 ) );
    // Returns the inverse hyperbolic tangent of a number.
}
#endif

/*!
 * \brief
 * Returns the depreciation of an asset for a specified period using the fixed-declining balance method.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the depreciation
 *
 * \details
 * The fixed-declining balance method computes depreciation at a fixed rate.
 * DB uses the following formulas to calculate depreciation for a period:
 * (cost - total depreciation from prior periods) * rate
 * rate = 1 - ((salvage/cost)^(1/life)), rounded to three decimal places
 * Depreciation for the first and last periods is a special case.
 * For the first period, DB uses this formula:
 * cost * rate * month/12
 * For the last period, DB uses this formula:
 * ((cost - total depreciation from prior periods)*rate*(12-month))/12
 *
 * \see
 * function_ddb | function_sln | function_syd | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_db
interpreter_variant function_db( function_parameter& parameters )
{
    if ( parameters.count() < 4 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    double cost     = parameters[0].numeric(); // the initial cost of the asset.
    double salvage  = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life     = parameters[2].numeric(); // the number of periods over which the asset is being depreciated (sometimes called the useful life of the asset).
    int period   = static_cast<int>( parameters[3].numeric() ); // the period for which you want to calculate the depreciation. period must use the same units as life.
    int month = 12; // the number of months in the first year. If month is omitted, it is assumed to be 12.
    if ( parameters.count() > 4 ) {
        month = static_cast<int>( parameters[4].numeric() );
    }

    if ( cost < 0.0 || salvage < 0.0 || life <= 0.0 || period < 1 || month < 1 ) {
        return interpreter_variant( variant::error_num );
    }
    double rate = 1000.0 * ( 1.0 - pow( salvage / cost, 1.0 / life ) );
    rate = floor( rate + 0.5 )  / 1000.0; // rounded to three decimal places
    // For the first period, DB uses:
    double result = cost * rate * month / 12.0;

    if ( period == 1 ) {
        return interpreter_variant( variant( result ) );
    }

    for ( int i = 1; i < life; ++i ) {
        if ( i == period - 1 ) {
            return interpreter_variant( variant( ( cost - result ) * rate ) ); // depreciation for a period
        } else {
            result += ( cost - result ) * rate;
        }
    }
    // For the last period, DB uses:
    return interpreter_variant( variant( ( cost - result ) * rate * ( 12.0 - month ) / 12.0 ) );
    // Returns the depreciation of an asset for a specified period using the fixed-declining balance method.
}
#endif

/*!
 * \brief
 * Returns the depreciation of an asset for a specified period
 * using the double-declining balance method or some other method you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the depreciation
 *
 * \details
 * All five arguments must be positive numbers.
 * The double-declining balance method computes depreciation at an accelerated rate.
 * Depreciation is highest in the first period and decreases in successive periods.
 * DDB uses the following formula to calculate depreciation for a period:
 * ((cost-salvage) - total depreciation from prior periods)*(factor/life)
 * Change factor if you do not want to use the double-declining balance method.
 * Use the VDB function if you want to switch to the straight-line depreciation method
 * when depreciation is greater than the declining balance calculation.
 *
 * \see
 * function_sln | function_syd | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ddb
interpreter_variant function_ddb( function_parameter& parameters )
{
    if ( parameters.count() < 4 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    double cost     = parameters[0].numeric(); // the initial cost of the asset.
    double salvage  = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life     = parameters[2].numeric(); // the number of periods over which the asset is being depreciated (sometimes called the useful life of the asset).
    double period   = parameters[3].numeric(); // the period for which you want to calculate the depreciation. period must use the same units as life.
    double factor   = 2; // the rate at which the balance declines. If factor is omitted, it is assumed to be 2 (the double-declining balance method).
    if ( parameters.count() > 4 ) {
        factor = parameters[4].numeric();
    }

    if ( cost < 0.0 || salvage < 0.0 || life <= 0.0 || period < 0.0 || factor < 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    double result = 0.0;
    for ( size_t i = 0; i < life - 1; ++i ) {
        double tmpRes = ( cost - result ) * ( factor / life );
        if ( i == period - 1 ) {
            return interpreter_variant( variant( tmpRes ) );
        } else {
            result += tmpRes;
        }
    }
    return interpreter_variant( variant( cost - result - salvage ) );
    // Returns the depreciation of an asset for a specified period
    // using the double-declining balance method or some other method you specify.
}
#endif

/*!
 * \brief
 * Returns the straight-line depreciation of an asset for one period.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the straight-line depreciation
 *
 * \details
 *
 * \see
 * function_ddb | function_syd | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_sln
interpreter_variant function_sln( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double cost = parameters[0].numeric(); // the initial cost of the asset.
    double salvage = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life = parameters[2].numeric(); // the number of periods over which the asset is depreciated (sometimes called the useful life of the asset).

    if ( life == 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    return interpreter_variant( variant( ( cost - salvage ) / life ) );
    // Returns the straight-line depreciation of an asset for one period.
}
#endif

/*!
 * \brief
 * Returns the sum-of-years' digits depreciation of an asset for a specified period.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum-of-years' digits depreciation
 *
 * \details
 * SYD=(cost-salvage)*(life-per+1)*2/(life*(life+1))
 *
 * \see
 * function_ddb | function_sln | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_syd
interpreter_variant function_syd( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    double cost = parameters[0].numeric(); // the initial cost of the asset.
    double salvage = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life = parameters[2].numeric(); // the number of periods over which the asset is depreciated (sometimes called the useful life of the asset).
    double period = parameters[3].numeric(); // the period. period must use the same units as life.

    if ( life <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double numerator = ( cost - salvage ) * ( life - period + 1.0 ) * 2.0;
    double denominator = life * ( life + 1.0 );

    return interpreter_variant( variant( numerator / denominator ) );
    // Returns the sum-of-years' digits depreciation of an asset for a specified period.
}
#endif

/*!
 * \brief
 * Rounds a number to a specified number of digits.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * If num_digits is greater than 0, then number is rounded to the specified number of decimal places.
 * If num_digits is 0, then number is rounded up to the nearest integer.
 * If num_digits is less than 0, then number is rounded to the left of the decimal point.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_round
interpreter_variant function_round( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, ROUND returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the number you want to round.
    int num_digits = static_cast<int>( parameters[1].numeric() ); // the number of digits to which you want to round number.
    // If num_digits is greater than 0, then number is rounded to the specified number of decimal places.
    // If num_digits is 0, then number is rounded to the nearest integer.
    // If num_digits is less than 0, then number is rounded to the left of the decimal point.
    double factor = pow( 10.0, num_digits );
    double result = floor( number * factor + 0.5 ) / factor;
    return interpreter_variant( variant( result ) );
    // Rounds a number to a specified number of digits.
}
#endif

/*!
 * \brief
 * Returns a normalized value from a distribution characterized by mean and standard_dev.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the normalized value
 *
 * \details
 * The equation of the normalized value is:
 * Z=(x-mean)/standard_dev
 *
 * \see
 * function_normdist | function_norminv | function_normsdist | function_normsinv | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_standardize
interpreter_variant function_standardize( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // the value you want to normalize.
    double x = parameters[0].numeric();
    // the arithmetic mean of the distribution.
    double mean = parameters[1].numeric();
    // the standard deviation of the distribution.
    double standard_dev = parameters[2].numeric();

    // If standard_dev <= 0, STANDARDIZE returns the #NUM! error value.
    if ( !( standard_dev > 0.0 ) ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( ( x - mean ) / standard_dev ) );
    // Returns a normalized value from a distribution characterized by mean and standard_dev.
}
#endif

/*!
 * \brief
 * Calculates the payment for a loan based on constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the payment for a loan
 *
 * \details
 * The payment returned by PMT includes principal and interest but no taxes,
 * reserve payments, or fees sometimes associated with loans.
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at an annual interest rate of 12 percent,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12 percent for rate and 4 for nper.
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_pmt
interpreter_variant function_pmt( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate for the loan.
    double nper = parameters[1].numeric(); // the total number of payments for the loan.
    double pv   = parameters[2].numeric(); // the present value, or the total amount that a series of future payments is worth now; also known as the principal.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    // If fv is omitted, it is assumed to be 0, that is, the future value of a loan is 0.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0; // the number 0 or 1. type indicates when payments are due.
    if ( parameters.count() == 5 ) {
        type = parameters[4].numeric();
    }

    if ( rate == 0.0 ) {
        return interpreter_variant( variant( -( pv + fv ) / nper ) );
    }

    double pvfact  = pow( 1.0 + rate, nper );
    double pmtfact = ( pvfact - 1.0 ) / rate;
    double result = ( -pv * pvfact - fv ) / ( ( 1.0 + rate * type ) * pmtfact );
    return interpreter_variant( variant( result ) );
    // Calculates the payment for a loan based on constant payments and a constant interest rate.
}
#endif

/*!
 * \brief
 * Returns the present value of an investment.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the present value
 *
 * \details
 * The present value is the total amount that a series of future payments is worth now.
 * For example, when you borrow money, the loan amount is the present value to the lender.
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 * An annuity is a series of constant cash payments made over a continuous period.
 * For example, a car loan or a mortgage is a annuity.
 * In annuity functions, cash you pay out, such as a deposit to savings, is represented by a negative number;
 * cash you receive, such as a dividend check, is represented by a positive number.
 * For example, a $1000 deposit to the bank would be represented by the argument -1000
 * if you are the depositor and by the argument 1000 if you are the bank.
 * pv*(1+rate)^nper + pmt*(1+rate*type)*((1+rate)^nper -1)/rate + fv = 0
 * If rate is 0, then: (pmt*nper) + pv + fv = 0
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pmt | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_pv
interpreter_variant function_pv( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double nper = parameters[1].numeric(); // the total number of payment periods in an annuity.
    double pmt  = parameters[2].numeric(); // the payment made each period , pmt cannot change over the life of the annuity.
    // Typically, pmt includes principal and interest but no other fees or taxes.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    // If fv is omitted, it is assumed to be 0 (the future value of a loan, for example, is 0).
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 ) {
        type = parameters[4].numeric();
    }
    double result = 0.0;
    if ( rate == 0.0 ) {
        result = -fv - pmt * nper;
    } else {
        double numerator = -fv - pmt * ( 1.0 + rate * type ) * ( pow( 1.0 + rate, nper ) - 1.0 ) / rate;
        double denominator = pow( 1.0 + rate , nper );
        result = numerator / denominator;
    }
    return interpreter_variant( variant( result ) );
    // Returns the present value of an investment.
    // The present value is the total amount that a series of future payments is worth now.
}
#endif

/*!
 * \brief
 * Returns the interest payment for a given period for an investment based on periodic, constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the interest payment
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 * For all the arguments, cash you pay out, such as deposits to savings, is represented by negative numbers;
 * cash you receive, such as dividend checks, is represented by positive numbers.
 *
 * \see
 * function_accrint | function_accrintm | function_cumipmt | function_intrate | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*interpreter_variant function_ipmt( calculation_context& cx, unsigned int param )
{
if ( param < 4 || param > 6 ) {
// formula-error! We give #N/A until we can give a message-window.
return interpreter_variant( variant::error_n_a );
}
internal::ParameterList parameters( cx, param );


}*/


/*!
 * \brief
 * Returns the internal rate of return for a series of cash flows represented by the numbers in values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the internal rate of return
 *
 * \details
 * The cash flows must occur at regular intervals, such as monthly or annually.
 * The internal rate of return is the interest rate received for an investment consisting of
 * payments (negative values) and income (positive values) that occur at regular periods.
 * We use an iterative technique for calculating IRR.
 * If IRR can't find a result that works after 20 tries, the #NUM! error value is returned.
 * If IRR gives the #NUM! error value, or if the result is not close to what you expected,
 * try again with a different value for guess.
 *
 * \see
 * function_mirr | function_npv | function_rate | function_xirr | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_irr
interpreter_variant function_irr( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant values = parameters[0]; // an array or reference to cells that contain numbers
    // for which you want to calculate the internal rate of return.
    double guess = 0.1; // a number that you guess is close to the result of IRR.
    if ( parameters.count() > 1 ) {
        guess = parameters[1].numeric();
    }

    std::vector<double> coefficient;
    if ( values.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( values.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            variant vi = sra[i];
            if ( vi.type() == variant::type_error ) {
                return interpreter_variant( variant::error_value );
            }

            if ( vi.type() == variant::type_double ) {
                coefficient.push_back( vi.numeric() );
            }
        }
    } else if ( values.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = values.array();
        unsigned long int arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant vi = arr[i];
            if ( vi.type() == variant::type_error ) {
                return interpreter_variant( variant::error_value );
            }

            if ( vi.type() == variant::type_double ) {
                coefficient.push_back( vi.numeric() );
            }
        }
    } else {
        return interpreter_variant( variant::error_num );
    }
    unsigned long int count = coefficient.size();

    double result = guess;
    double old, function, derivation;
    for ( int n = 0; n < 20; n++ ) {
        old = result;
        function = 0.0;
        derivation = 0.0;
        for ( unsigned long int j = 0; j < count; j++ ) {
            function += coefficient[j] / pow( 1.0 + old, static_cast<double>( j ) );
            derivation -= j * coefficient[j] / pow( 1.0 + old, j + 1.0 );
        }

        if ( derivation == 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        result = old - function / derivation; // Newton's method.
        if ( fabs( result - old ) <= 0.0000001 ) {
            return interpreter_variant( variant( result ) );
        }
    }
    // If IRR can't find a result that works after 20 tries, the #NUM! error value is returned.
    // If IRR gives the #NUM! error value, or if the result is not close to what you expected,
    // try again with a different value for guess.
    return interpreter_variant( variant::error_num );
    // Returns the internal rate of return for a series of cash flows represented by the numbers in values.
    // The cash flows must occur at regular intervals, such as monthly or annually.
    // The internal rate of return is the interest rate received for an investment consisting of
    // payments (negative values) and income (positive values) that occur at regular periods.
}
#endif

/*!
 * \brief
 * Calculates the interest paid during a specific period of an investment.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the interest paid during a specific period
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at an annual interest rate of 12 percent,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 * For all the arguments, the cash you pay out, such as deposits to savings or other withdrawals, is represented by negative numbers;
 * the cash you receive, such as dividend checks and other deposits, is represented by positive numbers.
 *
 * \see
 * function_rate | function_nper | function_pv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ispmt
interpreter_variant function_ispmt( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate for the investment.
    double per = parameters[1].numeric(); // the period for which you want to find the interest, and must be between 1 and nper.
    double nper = parameters[2].numeric(); // the total number of payment periods for the investment.
    double pv = parameters[3].numeric(); // the present value of the investment. For a loan, pv is the loan amount.

    double result = -pv * rate;
    return interpreter_variant( variant( result - result * per / nper ) );
    // Calculates the interest paid during a specific period of an investment.
    // This function is provided for compatibility with Lotus 1-2-3.
}
#endif

/*!
 * \brief
 * Returns the modified internal rate of return for a series of periodic cash flows.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the modified internal rate of return
 *
 * \details
 * MIRR considers both the cost of the investment and the interest received on reinvestment of cash.
 * MIRR uses the order of values to interpret the order of cash flows.
 * Be sure to enter your payment and income values in the sequence you want and with the correct signs
 * (positive values for cash received, negative values for cash paid).
 * MIRR=((-NPV(rrate,values[positive])*(1+rrate)^n)/(NPV(frate,values[negative])*(1+frate)))^(1/(n-1)) -1
 *
 * \see
 * function_rate | function_xirr | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_mirr
interpreter_variant function_mirr( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant values = parameters[0]; // array or reference to cells that contain numbers.
    // These numbers represent a series of payments (negative values) and income (positive values) occurring at regular periods.
    double finance_rate = parameters[1].numeric(); // the interest rate you pay on the money used in the cash flows.
    double reinvest_rate = parameters[2].numeric(); // the interest rate you receive on the cash flows as you reinvest them.

    // values must contain at least one positive and one negative value to calculate the modified internal rate of return.
    // Otherwise, MIRR returns the #DIV/0! error value.
    double npv_pos = 0.0, npv_neg = 0.0;
    int counter = 0; // the number of proper values.

    if ( values.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( values.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int n = sra.size();
        for ( unsigned int i = 0; i < n; i++ ) {
            variant v = sra[i];
            // If values contains text, logical values, or empty cells, those values are ignored.
            if ( v.type() == variant::type_double ) {
                counter++;
                if ( v.numeric() >= 0.0 ) {
                    npv_pos += v.numeric() / pow( 1.0 + reinvest_rate, counter );
                } else {
                    npv_neg += v.numeric() / pow( 1.0 + finance_rate, counter );
                }
            }
        }
    } else if ( values.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = values.array();
        int n = arr.size();
        for ( int i = 0; i < n; i++ ) {
            variant v = arr[i];
            // If values contains text, logical values, or empty cells, those values are ignored.
            if ( v.type() == variant::type_double ) {
                counter++;
                if ( v.numeric() >= 0.0 ) {
                    npv_pos += v.numeric() / pow( 1.0 + reinvest_rate, counter );
                } else {
                    npv_neg += v.numeric() / pow( 1.0 + finance_rate, counter );
                }
            }
        }
    } else {
        return interpreter_variant( variant::error_div_null );
    }

    if ( npv_neg == 0.0 || npv_pos == 0.0 || reinvest_rate <= -1.0 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double result = pow( ( -npv_pos * pow( 1.0 + reinvest_rate, counter ) ) / ( npv_neg * ( 1.0 + finance_rate ) ), ( 1.0 / ( counter - 1.0 ) ) ) - 1.0;

    return interpreter_variant( variant( result ) );
    // Returns the modified internal rate of return for a series of periodic cash flows.
    // MIRR considers both the cost of the investment and the interest received on reinvestment of cash.
}
#endif

/*!
 * \brief
 * Returns the number of periods for an investment based on periodic, constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of periods
 *
 * \details
 * pv*(1+rate)^nper + pmt*(1+rate*type)*((1+rate)^nper -1)/rate + fv = 0
 * If rate is 0, then: (pmt*nper) + pv + fv = 0
 *
 * \see
 * function_fv | function_ipmt | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_nper
interpreter_variant function_nper( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double pmt = parameters[1].numeric(); // the payment made each period; it cannot change over the life of the annuity.
    // Typically, pmt contains principal and interest but no other fees or taxes.
    double pv = parameters[2].numeric(); // the present value, or the lump-sum amount that a series of future payments is worth right now.
    double fv = 0.0; // the future value, or cash balance you want to attain after the last payment is made.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 ) {
        type = parameters[4].numeric();
    }
    double result;
    if ( rate == 0.0 ) {
        return interpreter_variant( variant( -( pv + fv ) / pmt ) );
    }

    if ( type == 0.0 ) {
        result = log( ( pmt - fv * rate ) / ( pmt + pv * rate ) ) / log( 1.0 + rate );
    } else {
        result = log( ( -fv * rate + pmt * ( 1.0 + rate ) ) / ( pv * rate + pmt * ( 1.0 + rate ) ) ) / log( 1.0 + rate );
    }
    return interpreter_variant( variant( result ) );
    // Returns the number of periods for an investment based on periodic, constant payments and a constant interest rate.
}
#endif

/*!
 * \brief
 * Calculates the net present value of an investment by using a discount rate and a series
 * of future payments (negative values) and income (positive values).
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the net present value
 *
 * \details
 * The NPV investment begins one period before the date of the value 1 cash flow
 * and ends with the last cash flow in the list. The NPV calculation is based on future cash flows.
 * If your first cash flow occurs at the beginning of the first period,
 * the first value must be added to the NPV result, not included in the values arguments.
 * If n is the number of cash flows in the list of values, the formula for NPV is:
 * NPV = Sum{j=1..n}values{j}/(1+rate)^j
 * NPV is similar to the PV function (present value). The primary difference between PV and NPV is
 * that PV allows cash flows to begin either at the end or at the beginning of the period.
 * Unlike the variable NPV cash flow values, PV cash flows must be constant throughout the investment.
 * NPV is also related to the IRR function (internal rate of return).
 * IRR is the rate for which NPV equals zero:
 * NPV(IRR(...),...) = 0
 *
 * \see
 * function_fv | function_irr | function_pv | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_npv
interpreter_variant function_npv( function_parameter& parameters )
{
    if ( parameters.count() < 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the rate of discount over the length of one period.
    unsigned long int counter = 0; // the number of proper values.
    double result = 0.0;
    for ( size_t i = 1; i < parameters.count(); i++ ) {
        if ( parameters[i].i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( parameters[i].reference() );
            sparse_range_array sra( rref, parameters.context() );
            unsigned int imax = sra.size();
            for ( unsigned long int j = 0; j < imax; j++ ) {
                variant currentj = sra[j];
                // error values in the array or reference cause errors.
                if ( currentj.type() == variant::type_error ) {
                    return interpreter_variant( currentj );
                }
                // only numbers in that array or reference are counted.
                if ( currentj.type() == variant::type_double ) {
                    counter++;
                    result += currentj.numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
                }
                // Empty cells, logical values, or text are ignored.
            }
        } else {
            // Arguments that are error values cause errors.
            if ( parameters[i].type() == variant::type_error ) {
                return parameters[i];
            }

            if ( parameters[i].type() == variant::type_array ) {
                const variant::sparse_array_type& arr = parameters[i].array();
                unsigned long int arraySize = arr.size();
                for ( unsigned long int j = 0; j < arraySize; j++ ) {
                    variant currentj = arr[j];
                    // error values in the array or reference cause errors.
                    if ( currentj.type() == variant::type_error ) {
                        return interpreter_variant( currentj );
                    }
                    // only numbers in that array or reference are counted.
                    if ( currentj.type() == variant::type_double ) {
                        counter++;
                        result += currentj.numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
                    }
                    // logical values, or text are ignored.
                }
            }

            if ( parameters[i].type() == variant::type_string ) {
                counter++;
                try { // text representations of numbers are counted.
                    result += boost::lexical_cast<double>( static_cast<const std::string&>( parameters[i].string() ) ) / pow( 1.0 + rate, static_cast<double>( counter ) );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            }
            // numbers and logical values are counted.
            if ( parameters[i].type() == variant::type_double || parameters[i].type() == variant::type_bool ) {
                counter++;
                result += parameters[i].numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
            }
            // empty cells are ignored.
        }
    }

    return interpreter_variant( variant( result ) );
    // Calculates the net present value of an investment by using a discount rate and a series
    // of future payments (negative values) and income (positive values).
}
#endif

/*!
 * \brief
 * Returns the payment on the principal for a given period for an investment based on periodic,
 * constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the payment on the principal
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*interpreter_variant function_ppmt( calculation_context& cx, unsigned int param )
{
if ( param < 4 || param > 6 ) {
// formula-error! We give #N/A until we can give a message-window.
return interpreter_variant( variant::error_n_a );
}
internal::ParameterList parameters( cx, param );


}*/


/*!
 * \brief
 * Returns the interest rate per period of an annuity.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the interest rate per period
 *
 * \details
 * RATE is calculated by iteration and can have zero or more solutions.
 * If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
 * If RATE does not converge, try different values for guess. RATE usually converges, if guess is between 0 and 1.
 * Make sure that you are consistent about the units you use for specifying guess or nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest, use 12%/12 for guess and 4*12 for nper.
 * If you make annual payments on the same loan, use 12% for guess and 4 for nper.
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pmt | function_pv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_rate
interpreter_variant function_rate( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 6 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double nper = parameters[0].numeric(); // the total number of payment periods in an annuity.
    double pmt = parameters[1].numeric(); // the payment made each period, cannot change over the life of the annuity.
    // Typically, pmt includes principal and interest but no other fees or taxes.
    // If pmt is omitted, you must include the fv argument.
    double pv = parameters[2].numeric(); // the present value - the total amount that a series of future payments is worth now.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 && parameters[4].type() != variant::type_empty ) {
        type = parameters[4].numeric();
    }
    double guess = 0.1; // your guess for what the rate will be.
    if ( parameters.count() > 5 ) {
        guess = parameters[5].numeric();
    }

    double result = guess;
    double old, function, derivation;
    for ( int i = 0; i < 20; i++ ) {
        old = result;
        if ( type == 0.0 ) {
            function = fv + pv * pow( 1.0 + old, nper );
            function += pmt * ( pow( 1.0 + old, nper ) - 1.0 ) / old;
            derivation = pv * nper * pow( 1.0 + old, nper - 1.0 );
            derivation += pmt * ( ( old * ( nper - 1.0 ) - 1.0 ) * pow( 1.0 + old, nper - 1.0 ) + 1.0 ) / old / old;
        } else {
            function = fv + pv * pow( 1.0 + old, nper );
            function += pmt * ( 1.0 + old ) * ( pow( 1.0 + old, nper ) - 1.0 ) / old;
            derivation = pv * nper * pow( 1.0 + old, nper - 1.0 );
            derivation += pmt * ( ( nper - 1.0 ) * pow( 1.0 + old, nper ) + 1.0 ) / old / old;
        }

        if ( derivation == 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        result = old - function / derivation; // Newton's method.
        if ( fabs( result - old ) <= 0.0000001 ) {
            return interpreter_variant( variant( result ) );
        }
    }

    // If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
    return interpreter_variant( variant::error_num );
    // Returns the interest rate per period of an annuity.
    // RATE is calculated by iteration and can have zero or more solutions.
    // If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
    // If RATE does not converge, try different values for guess. RATE usually converges, if guess is between 0 and 1.
}
#endif

/*!
 * \brief
 * Returns the depreciation of an asset for any period you specify, including partial periods,
 * using the double-declining balance method or some other method you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the depreciation
 *
 * \details
 * VDB stands for variable declining balance.
 *
 * \see
 * function_ddb | function_sln | function_syd
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
/*interpreter_variant function_vdb( calculation_context& cx, unsigned int param )
{
if ( param < 5 || param > 7 ) {
// formula-error! We give #N/A until we can give a message-window.
return interpreter_variant( variant::error_n_a );
}
internal::ParameterList parameters( cx, param );

}*/


/*!
 * \brief
 * Returns the Fisher transformation at x.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the Fisher transformation
 *
 * \details
 * This transformation produces a function that is normally distributed rather than skewed.
 * Use this function to perform hypothesis testing on the correlation coefficient.
 * The equation for the Fisher transformation is:
 * z=0.5*log((1+x)/(1-x))
 *
 * \see
 * function_fisherinv | function_correl | function_covar
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_fisher
interpreter_variant function_fisher( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x is nonnumeric, FISHER returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // a numeric value for which you want the transformation.

    // If x <= -1 or if x >= 1, FISHER returns the #NUM! error value.
    if ( x <= -1.0 || x >= 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( 0.5 * log( ( 1.0 + x ) / ( 1.0 - x ) ) ) );
    // Returns the Fisher transformation at x.
}
#endif

/*!
 * \brief
 * Returns the inverse of the Fisher transformation.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the Fisher transformation
 *
 * \details
 * Use this transformation when analyzing correlations between ranges or arrays of data.
 * The equation for the inverse of the Fisher transformation is:
 * x=(exp(2*y)-1)/(exp(2*y)+1)
 * If y = FISHER(x), then FISHERINV(y) = x.
 *
 * \see
 * function_fisher | function_correl | function_covar
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_fisherinv
interpreter_variant function_fisherinv( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a mesage-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If y is nonnumeric, FISHERINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double y = parameters[0].numeric(); // the value for which you  want to perform the inverse of the transformation.

    return interpreter_variant( variant( ( exp( 2.0 * y ) - 1.0 ) / ( exp( 2.0 * y ) + 1.0 ) ) );
    // Returns the inverse of the Fisher transformation.
}
#endif

/*!
 * \brief
 * Returns the Weibull distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the Weibull distribution
 *
 * \details
 * Use this distribution in reliability analysis, such as calculating a device's mean time to failure.
 * The equation for the Weibull probability density function is:
 * f(x;alpha,beta) = x^(alpha-1) * exp((x/beta)^alpha) * alpha/beta^alpha
 * The equation for the Weibull cumulative distribution function is:
 * F(x;alpha,beta) = 1 - exp(-(x/beta)^alpha)
 * When alpha=1, Weibull returns the exponential distribution with lambda=1/beta.
 *
 * \see
 * function_expondist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_weibull
interpreter_variant function_weibull( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x, alpha, or beta is nonnumeric, WEIBULL returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // the value at which to evaluate the function.
    double x = parameters[0].numeric();
    // parameter to the distribution.
    double alpha = parameters[1].numeric();
    // parameter to the distribution.
    double beta = parameters[2].numeric();
    // Flag.
    bool cumulative = parameters[3].numeric() != 0.0;

    // If x < 0, WEIBULL returns the #NUM! error value.
    // If alpha <= 0 or if beta <= 0, WEIBULL returns the #NUM! error value.
    if ( x < 0.0 || alpha <= 0.0 || beta <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    double result;
    if ( cumulative ) {
        result = 1.0 - exp( - pow( x / beta, alpha ) );
    } else {
        result = pow( x, alpha - 1 ) * exp( -pow( x / beta, alpha ) ) * alpha / pow( beta, alpha );
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, WEIBULL returns the Weibull cumulative distribution function.
    // If FALSE, it returns the Weibull probability density function.
}
#endif

/*!
 * \brief
 * Returns true, if the argument refers to any item that is not text.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to any item that is not text
 *
 * \details
 * Returns also true, if the argument refers to a blank cell.
 *
 * \see
 * function_istext
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef funtion_isnontext
interpreter_variant function_isnontext( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    if ( parameters[0].type() == variant::type_string || parameters[0].is_empty() ) {
        return interpreter_variant( variant( true ) );
    } else {
        return interpreter_variant( variant( false ) );
    }
    // Returns true, if the argument refers to any item that is not text.
    // Returns also true, if the argument refers to a blank cell.
}
#endif

/*!
 * \brief
 * Returns true, if the argument refers to a logical value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to a logical value
 *
 * \details
 *
 * \see
 * function_isnumber
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_islogical
interpreter_variant function_islogical( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    return interpreter_variant( parameters[0].type() == variant::type_bool );
    // Returns true, if the argument refers to a logical value.
}
#endif

/*!
 * \brief
 * Returns true, if the argument refers to the #N/A (value not available) error value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to the #N/A (value not available) error value
 *
 * \details
 *
 * \see
 * function_iserror | function_iserr
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_isna
interpreter_variant function_isna( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    if ( parameters[0].type() == variant::type_error && parameters[0].numeric() == variant::error_n_a ) {
        return interpreter_variant( variant( true ) );
    } else {
        return interpreter_variant( variant( false ) );
    }
    // Returns true, if the argument refers to the #N/A (value not available) error value.
}
#endif

/*!
 * \brief
 * Returns a number corresponding to one of the error values or returns the #N/A error, if no error exists.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number corresponding to one of the error values or the #N/A error, if no error exists
 *
 * \details
 * You can use ERROR.TYPE in an IF function to test for an error value
 * and return a text string, such as a message, instead of the error value.
 *
 * \see
 * function_iserror | function_iserr
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_error_type
interpreter_variant function_error_type( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // The argument is the error value whose identifying number you want to find.
    if ( parameters[0].type() == variant::type_error ) {
        return interpreter_variant( parameters[0].numeric() );
    }

    return interpreter_variant( variant::error_n_a );
    // Returns a number corresponding to one of the error values
    // or returns the #N/A error, if no error exists.
}
#endif

/*!
 * \brief
 * Returns true, if the argument refers to any error value except #N/A
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to any error value except #N/A
 *
 * \details
 *
 * \see
 * function_iserror | function_isna
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_iserr
interpreter_variant function_iserr( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    if ( ( parameters[0].type() == variant::type_error ) && ( parameters[0].numeric() != variant::error_n_a ) ) {
        return interpreter_variant( variant( true ) );
    } else {
        return interpreter_variant( variant( false ) );
    }
    // Returns true, if the argument refers to any error value except #N/A
}

#endif



#ifdef function_binomdist
// binomdist_density helps to calculate function_binomdist and function_critbinom.
double binomdist_density( long long number_s, long long trials, double probability_s )
{
    double result = pow( probability_s, static_cast<double>( number_s ) ) * pow( 1.0 - probability_s, static_cast<double>( trials - number_s ) );
    result *= static_cast<double>( combin( trials, number_s ) );

    return result;
}


/*!
 * \brief
 * Returns the individual term binomial distribution probability.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * result of the calculation
 *
 * \details
 * Use BINOMDIST in problems with a fixed number of tests or trials,
 * when the outcomes of any trial are only success or failure, when trials are independent,
 * and when the probability of success is constant throughout the experiment.
 *
 * \see
 * function_combin | function_critbinom | function_hypgeomdist | function_negbinomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_binomdist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If number_s, trials, or probability_s is nonnumeric, BINOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ||
            parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // number_s and trials are truncated to integers.
    // the number of successes in trials.
    long long number_s = static_cast<long long>( parameters[0].numeric() );
    // the number of independent trials.
    long long trials = static_cast<long long>( parameters[1].numeric() );

    // If number_s < 0 or number_s > trials, BINOMDIST returns the #NUM! error value.
    if ( number_s < 0 || number_s > trials ) {
        return interpreter_variant( variant::error_num );
    }

    // the probability of success on each trial.
    double probability_s = parameters[2].numeric();
    // If probability_s < 0 or probability_s > 1, BINOMDIST returns the #NUM! error value.
    if ( probability_s < 0.0 || probability_s > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    // Flag.
    bool cumulative = parameters[3].numeric() != 0.0;
    double result = 0.0;
    if ( !cumulative ) {
        result = binomdist_density( number_s, trials, probability_s );
    } else {
        if ( number_s <= trials / 2 ) {
            for ( long long i = 0; i <= number_s; i++ ) {
                result += binomdist_density( i, trials, probability_s );
            }
        } else {
            result = 1.0;
            for ( long long i = trials; i > number_s; i-- ) {
                result -= binomdist_density( i, trials, probability_s );
            }
        }
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, then BINOMDIST returns the cumulative distribution function,
    // which is the probability, that there are at most number_s successes. If FLASE,
    // it returns the probability mass function, which is the probability, that there are number_s successes.
}
#endif

#ifdef function_critbinom
// binomdist_cumulative helps to calculate function_critbinom.
double binomdist_cumulative( long long number_s, long long trials, double probability_s )
{
    double result = 0.0;

    if ( number_s <= trials / 2 ) {
        for ( long long i = 0; i <= number_s; i++ ) {
            result += binomdist_density( i, trials, probability_s );
        }
    } else {
        result = 1.0;
        for ( long long i = trials; i > number_s; i-- ) {
            result -= binomdist_density( i, trials, probability_s );
        }
    }

    return result;
}


/*!
 * \brief
 * Returns the smallest value for which the cumulative binomial distribution
 * is greater than or equal to a criterion value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the smallest value for which the cumulative binomial distribution
 * is greater than or equal to the criterion value
 *
 * \details
 * Use this function for quality assurance applications
 *
 * \see
 * function_binomdist | function_combin | function_hypgeomdist | function_negbinomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_critbinom( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, CRITBINOM returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // If trials is not an integer, it is truncated.
    // the number of Bernoulli trials.
    long long trials = static_cast<long long>( parameters[0].numeric() );
    // the probability of a success on each trial.
    double probability_s = parameters[1].numeric();
    // the criterion value.
    double alpha = parameters[2].numeric();

    // If trials < 0, CRITBINOM returns the #NUM! error value.
    // If probability_s is < 0 or probability_s > 1, CRITBINOM returns the #NUM! error value.
    // If alpha < 0 or alpha > 1, CRITBINOM returns the #NUM! error value.
    if ( trials < 0 || probability_s < 0.0 || probability_s > 1.0 || alpha < 0.0 || alpha > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    long long number_s;
    for ( number_s = 0; number_s <= trials; number_s++ ) {
        if ( binomdist_cumulative( number_s, trials, probability_s ) >= alpha ) {
            break;
        }
    }

    return interpreter_variant( variant( static_cast<double>( number_s ) ) );
    // the smallest number_s, for which the cumulative binomial distribution is greater than or equal to alpha.
}
#endif

/*!
 * \brief
 * Returns the negative binomial distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the negative binomial distribution
 *
 * \details
 * NEGBINOMDIST returns the probability, that there will be number_f failures
 * before the number_s-th success, when the constant probability of a success is probability_s.
 *
 * \see
 * function_binomdist | function_combin | function_hypgeomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_negbinomdist
interpreter_variant function_negbinomdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, NEGBINOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // number_f and number_s are truncated to integers.
    // the number of failures.
    long long number_f = static_cast<long long>( parameters[0].numeric() );
    // the threshold number of successes.
    long long number_s = static_cast<long long>( parameters[1].numeric() );
    // the probability of a success.
    double probability_s = parameters[2].numeric();

    // If probability_s < 0 or if probability_s > 1, NEGBINOMDIST returns the #NUM! error value.
    // If number_f < 0 or number_s < 1, NEGBINOMDIST returns the #NUM! error value.
    if ( probability_s < 0.0 || probability_s > 1.0 || number_f < 0 || number_s < 1 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = pow( probability_s, static_cast<double>( number_s ) ) * pow( 1.0 - probability_s, static_cast<double>( number_f ) );
    result *= static_cast<double>( combin( number_f + number_s - 1, number_f ) );

    return interpreter_variant( variant( result ) );
    // NEGBINOMDIST (negative binomial distribution) returns the probability, that there will be number_f failures
    // before the number_s-th success, when the constant probability of a success is probability_s.
}
#endif

/*!
 * \brief
 * Returns the hypergeometric distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the hypergeometric distribution
 *
 * \details
 * HYPGEOMDIST returns the probability of a given number of sample successes (sample_s),
 * given the sample size (number_sample), population successes (population_s), and population size (number_population).
 *
 * \see
 * function_binomdist | function_combin | function_negbinomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_hypgeomdist
interpreter_variant function_hypgeomdist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, HYPGEOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ||
            parameters[2].type() != variant::type_double || parameters[3].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // All arguments are truncated to integers.
    // the number of successes in the sample.
    long long sample_s = static_cast<long long>( parameters[0].numeric() );
    // the size of the sample.
    long long number_sample = static_cast<long long>( parameters[1].numeric() );
    // the number of successes in the population.
    long long population_s = static_cast<long long>( parameters[2].numeric() );
    // the population size.
    long long number_population = static_cast<long long>( parameters[3].numeric() );

    // If sample_s < 0 or sample_s is greater than the lesser of number_sample or population_s, HYPGEOMDIST returns the #NUM! error value.
    long long lesser = number_sample < population_s ? number_sample : population_s;
    if ( sample_s < 0 || sample_s > lesser ) {
        return interpreter_variant( variant::error_num );
    }
    // If sample_s is less than the larger of 0 or (number_sample - number_population + population_s), HYPGEOMDIST returns the #NUM! error value.
    long long limit = number_sample - number_population + population_s;
    long long larger = 0 > limit ? 0 : limit;
    if ( sample_s < larger ) {
        return interpreter_variant( variant::error_num );
    }
    // If number_sample < 0 or number_sample > number_population, HYPGEOMDIST returns the #NUM! error value.
    if ( number_sample < 0 || number_sample > number_population ) {
        return interpreter_variant( variant::error_num );
    }
    // If population_s < 0 or population_s > number_population, HYPGEOMDIST returns the #NUM! error value.
    // If number_population < 0, HYPGEOMDIST returns the #NUM! error value.
    if ( population_s < 0 || population_s > number_population || number_population < 0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = static_cast<double>( combin( population_s, sample_s ) );
    result *= static_cast<double>( combin( number_population - population_s, number_sample - sample_s ) );
    result /= static_cast<double>( combin( number_population, number_sample ) );

    return interpreter_variant( variant( result ) );
    // HYPGEOMDIST (hypergeometric distribution) returns the probability of a given number of sample successes (sample_s),
    // given the sample size (number_sample), population successes (population_s), and population size (number_population).
}
#endif

#ifdef function_poisson
// poisson_density helps to calculate function_poisson.
double poisson_density( long long x, double mean )
{
    double result = exp( - mean ) * pow( mean, static_cast<double>( x ) );
    for ( long long i = 2; i <= x; i++ ) {
        result /= static_cast<double>( i );
    }
    return result;
}


/*!
 * \brief
 * Returns the Poisson distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the Poisson distribution
 *
 * \details
 * For cumulative=FALSE: POISSON = exp(-mean)*mean^x /x!
 * For cumulative=TRUE: POISSON = Sum{k=0..x} exp(-mean)*mean^k /k!
 *
 * \see
 * function_expondist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_poisson( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x or mean is nonnumeric, POISSON returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // If x is not an integer, it is truncated.
    // the number of events.
    long long x = static_cast<long long>( parameters[0].numeric() );
    // the expected numeric value.
    double mean = parameters[1].numeric();
    // Flag.
    bool cumulative = parameters[2].numeric() != 0.0;

    // If x < 0, POISSON returns the #NUM! error value.
    // If mean <= 0, POISSON returns the #NUM! error value.
    if ( x < 0 || mean <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    if ( !cumulative ) {
        result = poisson_density( x, mean );
    } else {
        for ( long long k = 0; k <= x; k++ ) {
            result += poisson_density( k, mean );
        }
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, POISSON returns the cumulative Poisson probability,
    // that the number of random events occurring will be between zero and x inclusive.
    // If FALSE, it returns the Poisson probability mass function, that the number of events occurring will be exactly x.
}
#endif


/*!
 * \brief
 * Returns the exponential distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the exponential distribution
 *
 * \details
 * The equation for the probability density function is:
 * f(x;lambda) = lambda*exp(-lambda*x)
 * The equation for the cumulative distribution function is:
 * F(x;lambda) = 1 - exp(-lambda*x)
 *
 * \see
 * function_gammadist | function_poisson
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_expondist
interpreter_variant function_expondist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x or lambda is nonnumeric, EXPONDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // the value of the function.
    double x = parameters[0].numeric();
    // the parameter value.
    double lambda = parameters[1].numeric();
    // Flag.
    bool cumulative = parameters[2].numeric() != 0.0;

    // If x < 0, EXPONDIST returns the #NUM! error value.
    // If lambda <= 0, EXPONDIST returns the #NUM! error value.
    if ( x < 0.0 || lambda <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result;
    if ( cumulative ) {
        result = 1.0 - exp( - lambda * x );
    } else {
        result = lambda * exp( - lambda * x );
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, EXPONDIST returns the cumulative exponential distribution function.
    // If FALSE, it returns the probability density function.
}
#endif

/*!
 * \brief
 * Returns the probability for the Student t-distribution
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the probability for the Student t-distribution
 *
 * \details
 * If probability = TDIST(x,...), then TINV(probability,...) = x.
 *
 * \see
 * function_tinv | function_ttest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_tdist
interpreter_variant function_tdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, TDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x = parameters[0].numeric(); // the numeric value at which to evaluate the distribution.
    double degrees_freedom = parameters[1].numeric(); // the number of degrees of freedom.
    int tails = static_cast<int>( parameters[2].numeric() ); // the number of distribution tails to return.
    // 1 for one-tailed distribution, 2 for two-tailed distribution.
    // If x < 0 or degrees_freedom < 1 or tails is any value other than 1 or 2, TDIST returns the #NUM! error value.
    if ( x < 0.0 || degrees_freedom < 1.0 || ( tails != 1 && tails != 2 ) ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::students_t dist( degrees_freedom );
    double result;
    if ( tails == 1 ) {
        result = cdf( complement( dist, x ) );
    } else {
        result = 2.0 * cdf( complement( dist, x ) );
    }
    return interpreter_variant( variant( result ) );
    // Returns the Percentage Points (probability) for the Student t-distribution, where a numeric value (x) is a calculated value of t,
    // for which the Percentage Points are to be computed.
    // The t-distribution is used in the hypothesis testing of small sample data sets.
}
#endif

/*!
 * \brief
 * Returns the t-value of the Student's t-distribution as a function of the probability and the degrees of freedom.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the t-value of the Stundent's t-distribution
 *
 * \details
 * If probability = TDIST(x,...), then TINV(probability,...) = x.
 *
 * \see
 * function_tdist | function_ttest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_tinv
interpreter_variant function_tinv( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If either argument is nonnumeric, TINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // the probability associated with the two-tailed Student's t-distribution.
    double degrees_freedom = parameters[1].numeric(); // the number of degrees of freedom with which to characterize the distribution.
    // If probability < 0 or if probability > 1 or if degrees-Freedom < 1, TINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 || degrees_freedom < 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::students_t dist( degrees_freedom );
    double result = quantile( complement( dist, probability / 2.0 ) );
    return interpreter_variant( variant( result ) );
    // Returns the t-value of the Student's t-distribution as a function of the probability and the degrees of freedom.
}
#endif

/*!
 * \brief
 * Returns the probability associated with a Student's t-Test to determine
 * whether two samples are likely to have come from the same two underlying populations
 * that have the same mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the probability associated with a Stundent's t-Test
 *
 * \details
 * If type = 1, this test is performed paired.
 * If type = 2, this test is performed unpaired and it is assumed, that the sample variances are equal (homoscedastic).
 * If type = 3, this test is performed unpaired and it is assumed, that the sample variances can differ (heteroscedastic).
 *
 * \see
 * function_tdist | function_tinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ttest
interpreter_variant function_ttest( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( ( parameters[0].i_type() != interpreter_variant::type_range && parameters[0].type() != variant::type_array )
            || ( parameters[1].i_type() != interpreter_variant::type_range && parameters[1].type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arr0, arr1;
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref0 = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra0( rref0, parameters.context() );
        unsigned int imax0 = sra0.size();
        arr0 = variant::sparse_array_type( imax0 );
        for ( unsigned int i = 0; i < imax0; i++ ) {
            arr0[imax0] = sra0[i];
        }
    } else {
        arr0 = parameters[0].array();
    }

    if ( parameters[1].i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( parameters[1].reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arr1 = variant::sparse_array_type( imax1 );
        for ( unsigned int i = 0; i < imax1; i++ ) {
            arr1[i] = sra1[i];
        }
    } else {
        arr1 = parameters[1].array();
    }
    unsigned long int arraySize0 = arr0.size();
    unsigned long int arraySize1 = arr1.size();
    // If tails or type is nonnumeric, TTEST returns the #VALUE! error value.
    if ( parameters[2].type() != variant::type_double || parameters[3].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    // The tails and type arguments are truncated to integers.
    int tails = static_cast<int>( parameters[2].numeric() );
    int type = static_cast<int>( parameters[3].numeric() );
    // If tails is any value other than 1 or 2 or if type is any value other than 1 or 2 or 3, TTEST returns the #NUM! error value.
    if ( tails < 1 || tails > 2 || type < 1 || type > 3 ) {
        return interpreter_variant( variant::error_num );
    }
    // If the two arrays have a different number of data points, and type = 1 (paired), TTEST returns the #N/A error value.
    if ( type == 1 && arraySize0 != arraySize1 ) {
        return interpreter_variant( variant::error_n_a );
    }

    if ( type == 1 ) { // paired
        double summe = 0.0;
        double sumsq = 0.0;
        unsigned long int counter = 0;
        for ( unsigned long int i = 0; i < arraySize0; i++ ) {
            variant val0i = arr0[i];
            if ( val0i.type() == variant::type_error ) {
                return interpreter_variant( val0i );
            }
            variant val1i = arr1[i];
            if ( val1i.type() == variant::type_error ) {
                return interpreter_variant( val1i );
            }
            if ( val0i.type() != variant::type_double || val1i.type() != variant::type_double ) {
                continue;
            }
            counter++;
            double diff = val0i.numeric() - val1i.numeric();
            summe += diff;
            sumsq += diff * diff;
        }
        if ( counter < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double var = ( sumsq - summe * summe / counter ) / ( counter - 1 );
        if ( var <= 0.0 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double t = summe / sqrt( counter * var );
        boost::math::students_t dist( counter - 1 );
        if ( tails == 2 ) { // two-tailed
            return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
        } else { // one-tailed
            return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
        }
    } else { // unpaired
        double sumx = 0.0;
        double sumy = 0.0;
        double sumx2 = 0.0;
        double sumy2 = 0.0;
        unsigned long int countx = 0;
        unsigned long int county = 0;
        for ( unsigned long int i = 0; i < arraySize0; i++ ) {
            variant vali = arr0[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }
            if ( vali.type() != variant::type_double ) {
                continue;
            }
            countx++;
            sumx += vali.numeric();
            sumx2 += vali.numeric() * vali.numeric();
        }
        if ( countx < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        for ( unsigned long int i = 0; i < arraySize1; i++ ) {
            variant vali = arr1[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }
            if ( vali.type() != variant::type_double ) {
                continue;
            }
            county++;
            sumy += vali.numeric();
            sumy2 += vali.numeric() * vali.numeric();
        }
        if ( county < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double var = ( sumx2 - sumx * sumx / countx + sumy2 - sumy * sumy / county ) / ( countx + county - 2 );
        if ( var <= 0.0 ) {
            return interpreter_variant( variant::error_div_null );
        }
        if ( type == 2 ) { // homoscedastic (It is assumed that the variances of x and y are equal.)
            double t = sqrt( countx * county / ( ( countx + county ) * var ) ) * ( sumx / countx - sumy / county );
            boost::math::students_t dist( countx + county - 2 );
            if ( tails == 2 ) { // two-tailed
                return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
            } else { // one-tailed
                return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
            }
        } else { // heteroscedastic (It is assumed that the variances of x and y can differ.)
            double varxN = ( sumx2 - sumx * sumx / countx ) / ( countx * ( countx - 1 ) );
            double varyN = ( sumy2 - sumy * sumy / county ) / ( county * ( county - 1 ) );
            double t = ( sumx / countx - sumy / county ) / sqrt( varxN + varyN );
            double degrees_freedom = ( varxN + varyN ) * ( varxN + varyN ) / ( varxN * varxN / ( countx - 1 ) + ( varyN * varyN / ( county - 1 ) ) );
            boost::math::students_t dist( degrees_freedom );
            if ( tails == 2 ) { // two-tailed
                return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
            } else { // one-tailed
                return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
            }
        }
    }
    //return interpreter_variant( variant::error_div_null ); // We should not get here!
}
#endif

/*!
 * \brief
 * Returns the natural logarithm of the gamma function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the natural logarithm of the gamma function
 *
 * \details
 * GAMMALN(x) = LN(GAMMA(x))
 *
 * \see
 * function_ln | function_fact
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_gammaln
interpreter_variant function_gammaln( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x is nonnumeric, GAMMALN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric();

    // If x <= 0, GAMMALN returns the #NUM! error value.
    if ( !( x > 0.0 ) ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( boost::math::lgamma( x ) ) );
    // Returns the natural logarithm of the gamma function.
}
#endif


/*!
 * \brief
 * Returns the gamma distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the gamma distribution
 *
 * \details
 * If probability = GAMMADIST(x,...), then GAMMAINV(probability,...) = x.
 *
 * \see
 * function_gammainv | function_expondist | function_chidist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_gammadist
interpreter_variant function_gammadist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x, alpha, or beta is nonnumeric, GAMMADIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // the value at which you want to evaluate the distribution.
    double alpha = parameters[1].numeric(); // the shape parameter to the distribution.
    double beta = parameters[2].numeric(); // the scale parameter to the distribution.
    bool cumulative = parameters[3].numeric() != 0.0; // Flag.

    // If x < 0, GAMMADIST returns the #NUM! error value.
    // If alpha <= 0 or if beta <= 0, GAMMADIST returns the #NUM! error value.
    if ( x < 0.0 || alpha <= 0.0 || beta <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    boost::math::gamma_distribution<> dist( alpha, beta );
    if ( cumulative ) {
        result = cdf( dist, x );
    } else {
        result = pdf( dist, x );
    }
    return interpreter_variant( variant( result ) );
    // Returns the gamma distribution.
}
#endif


/*!
 * \brief
 * Returns the inverse of the gamma cumulative distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the gamma cumulative distribution
 *
 * \details
 * If probability = GAMMADIST(x,...), then GAMMAINV(probability,...) = x.
 *
 * \see
 * function_gammadist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_gammainv
interpreter_variant function_gammainv( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, GAMMAINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // the probability associated with the gamma distribution.
    double alpha = parameters[1].numeric(); // the shape parameter to the distribution.
    double beta = parameters[2].numeric(); // the scale parameter to the distribution.
    // If probability < 0 or probability > 1 or if alpha a <= 0 or if beta <= 0, GAMMAINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 || alpha <= 0.0 || beta <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::gamma_distribution<> dist( alpha, beta );
    double result = quantile( dist, probability );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the gamma cumulative distribution.
}
#endif


/*!
 * \brief
 * Returns the one-tailed probability of the chi-squared distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the one-tailed chi-squared distribution
 *
 * \details
 * If probability = CHIDIST(x,...), then CHIINV(probability,...) = x.
 *
 * \see
 * function_chiinv | function_chitest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_chidist
interpreter_variant function_chidist( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If either argument is nonnumeric, CHIDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // the value at which to evaluate the distribution.
    double x = parameters[0].numeric();
    // If degrees_freedom is not an integer, it is truncated.
    // the number of degrees of freedom.
    double degrees_freedom = parameters[1].numeric();

    // If x is negative, CHIDIST returns the #NUM! error value.
    // If degrees_freedom < 1 or degrees_freedom >= 10^10, CHIDIST returns the #NUM! error value.
    if ( ( x < 0 ) || ( degrees_freedom < 1.0 ) || ( degrees_freedom >= 1.0e+10 ) ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::chi_squared dist( degrees_freedom );
    double result = cdf( complement( dist, x ) );
    return interpreter_variant( variant( result ) );
    // Returns the one-tailed probability of the chi-squared distribution.
}
#endif

/*!
 * \brief
 * Returns the inverse of the one-tailed probability of the chi-squared distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the one-tailed chi-squared distribution
 *
 * \details
 * If probability = CHIDIST(x,...), then CHIINV(probability,...) = x.
 *
 * \see
 * function_chidist | function_chitest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef funtion_chiinv
interpreter_variant function_chiinv( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If either argument is nonnumeric, CHIINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability associated with the chi-squared distribution.
    double degrees_freedom = parameters[1].numeric(); // the number of degrees of freedom.
    // If probability < 0 or probability > 1 or degrees_freedom < 1 or degrees_freedom >= 10^10, CHIINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 || degrees_freedom < 1.0 || degrees_freedom > 1.0e+10 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::chi_squared dist( degrees_freedom );
    double result = quantile( complement( dist, probability ) );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the one-tailed probability of the chi-squared distribution.
}
#endif

/*!
 * CHITEST returns the value from the chi-squared distribution for the statistic as test for independence.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the value from the chi-squared distribution for the statistic as test for independence
 *
 * \details
 *
 * \see
 * function_chidist | function_chiinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_chitest
interpreter_variant function_chitest( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant actual_range = parameters[0];
    interpreter_variant expected_range = parameters[1];
    if ( ( actual_range.i_type() != interpreter_variant::type_range && actual_range.type() != variant::type_array )
            || ( expected_range.i_type() != interpreter_variant::type_range && expected_range.type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_n_a );
    }
    variant::sparse_array_type actual_arr, expected_arr;
    if ( actual_range.i_type() == interpreter_variant::type_range ) {
        range_reference& rrefa = range_reference_cast( actual_range.reference() );
        sparse_range_array sraa( rrefa, parameters.context() );
        unsigned int imaxa = sraa.size();
        actual_arr = variant::sparse_array_type( imaxa );
        for ( unsigned int i = 0; i < imaxa; i++ ) {
            actual_arr[i] = sraa[i];
        }
    } else {
        actual_arr = actual_range.array();
    }
    boost::int_fast32_t expectedColumnWidth;
    if ( expected_range.i_type() == interpreter_variant::type_range ) {
        range_reference& rrefe = range_reference_cast( expected_range.reference() );
        sparse_range_array srae( rrefe, parameters.context() );
        unsigned int imaxe = srae.size();
        expected_arr = variant::sparse_array_type( imaxe );
        for ( unsigned int i = 0; i < imaxe; i++ ) {
            expected_arr[i] = srae[i];
        }
        expectedColumnWidth = rrefe.actualize().position().column_count();
    } else {
        expected_arr = expected_range.array();
        expectedColumnWidth = expected_range.column_width();
    }
    boost::int_fast32_t actualArraySize = actual_arr.size();
    boost::int_fast32_t expectedArraySize = expected_arr.size();
    if ( actualArraySize != expectedArraySize || actualArraySize == 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    double x = 0.0;
    bool found = false;
    variant actVali, expVali;
    double diff;
    for ( boost::int_fast32_t i = 0; i < expectedArraySize; i++ ) {
        actVali = actual_arr[i];
        if ( actVali.type() == variant::type_error ) {
            return interpreter_variant( actVali );
        }
        expVali = expected_arr[i];
        if ( expVali.type() == variant::type_error ) {
            return interpreter_variant( expVali );
        }
        if ( actVali.type() != variant::type_double || expVali.type() != variant::type_double ) {
            continue;
        }
        diff = actVali.numeric() - expVali.numeric();
        x += diff * diff / expVali.numeric();
        found = true;
    }
    if ( !found ) {
        return interpreter_variant( variant::error_div_null );
    }
    // boost::int_fast32_t actualColumnWidth = actual_value.column_width();
    // boost::int_fast32_t actualRows = actualArraySize / actualColumnWidth;
    boost::int_fast32_t expectedRows = expectedArraySize / expectedColumnWidth;
    double degrees_freedom;
    if ( expectedRows == 1 ) {
        degrees_freedom = expectedColumnWidth - 1.0;
    } else if ( expectedColumnWidth == 1 ) {
        degrees_freedom = expectedRows - 1.0;
    } else {
        degrees_freedom = ( expectedRows - 1.0 ) * ( expectedColumnWidth - 1.0 );
    }
    boost::math::chi_squared dist( degrees_freedom );
    double result = cdf( complement( dist, x ) );
    return interpreter_variant( variant( result ) );
    // Returns the test for independence.
    // CHITEST returns the value from the chi-squared distribution for the statistic
    // and the appropriate degrees of freedom.
}
#endif

/*!
 * \brief
 * Returns the F probability distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the F probability distribution
 *
 * \details
 * If probability = FDIST(x,...), then FINV(probability,...) = x.
 *
 * \see
 * function_finv | function_ftest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_fdist
interpreter_variant function_fdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, FDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x = parameters[0].numeric(); // the value at which to evaluate the function.
    double degrees_freedom1 = parameters[1].numeric(); // the numerator degrees of freedom.
    double degrees_freedom2 = parameters[2].numeric(); // the denominator degrees of freedom.
    // If x is negative or if degrees_freedom1 < 1 or degrees_freedom1 >= 10^10 or if degrees_freedom2 < 1 or degrees_freedom2 >= 10^10, FDIST returns the #NUM! error value.
    if ( x < 0.0 || degrees_freedom1 < 1.0 || degrees_freedom1 >= 1.0e+10 || degrees_freedom2 < 1.0 || degrees_freedom2 >= 1.0e+10 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::fisher_f dist( degrees_freedom1, degrees_freedom2 );
    double result = cdf( complement( dist, x ) );
    return interpreter_variant( variant( result ) );
    // Returns the F probability distribution.
}
#endif

/*!
 * \brief
 * Returns the inverse of the F probability distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the F probability distribution
 *
 * \details
 * If probability = FDIST(x,...), then FINV(probability,...) = x.
 *
 * \see
 * function_fdist | function_ftest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_finv
interpreter_variant function_finv( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, FINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability associated with the F cumulative distribution.
    double degrees_freedom1 = parameters[1].numeric(); // the numerator degrees of freedom.
    double degrees_freedom2 = parameters[2].numeric(); // the denominator degrees of freedom.
    // If probability < 0 or probability > 1, FINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    // If degrees_freedom1 < 1 or degrees_freedom1 >= 10^10 or if degrees_freedom2 < 1 or degrees_freedom2 >= 10^10, FINV returns the #NUM! error value.
    if ( degrees_freedom1 < 1.0 || degrees_freedom1 >= 1.0e+10 || degrees_freedom2 < 1.0 || degrees_freedom2 >= 1.0e+10 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::fisher_f dist( degrees_freedom1, degrees_freedom2 );
    double result = quantile( complement( dist, probability ) );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the F probability distribution.
}
#endif

/*!
 * \brief
 * Returns the one-tailed probability that the variances in array1 and array2 are not significantly different.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the one-tailed probability that the variances in array1 and array2 are not significantly different
 *
 * \details
 *
 * \see
 * function_fdist | function_finv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_ftest
interpreter_variant function_ftest( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant array1 = parameters[0];
    interpreter_variant array2 = parameters[1];
    if ( ( array1.i_type() != interpreter_variant::type_range && array1.type() != variant::type_array )
            || ( array2.i_type() != interpreter_variant::type_range && array2.type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arr1, arr2;
    if ( array1.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        unsigned int imax1 = sra1.size();
        arr1 = variant::sparse_array_type( imax1 );
        for ( unsigned int i = 0; i < imax1; i++ ) {
            arr1[i] = sra1[i];
        }
    } else {
        arr1 = array1.array();
    }
    boost::int_fast32_t arraySize1 = arr1.size();
    if ( array2.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( array2.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        unsigned int imax2 = sra2.size();
        arr2 = variant::sparse_array_type( imax2 );
        for ( unsigned int i = 0; i < imax2; i++ ) {
            arr2[i] = sra2[i];
        }
    } else {
        arr2 = array2.array();
    }
    boost::int_fast32_t arraySize2 = arr2.size();

    for ( boost::int_fast32_t i = 0; i < arraySize1; i++ ) {
        // error values cause errors.
        if ( static_cast<const variant&>( arr1[i] ).type() == variant::type_error ) {
            return interpreter_variant( arr1[i] );
        }
    }
    double sum1 = 0.0;
    double sumsq1 = 0.0;
    unsigned long int counter1 = 0;
    // If an argument is an array or reference, only numbers in that array or reference are counted.
    // Empty cells, logical values, or text in the array or reference are ignored.
    sum1 += std::for_each( arr1.begin(), arr1.end(), internal::Sum() ).summe;
    sumsq1 += std::for_each( arr1.begin(), arr1.end(), internal::SumSq() ).summe;
    counter1 += std::for_each( arr1.begin(), arr1.end(), internal::Counter() ).counter;

    for ( boost::int_fast32_t i = 0; i < arraySize2; i++ ) {
        // error values cause errors.
        if ( static_cast<const variant&>( arr2[i] ).type() == variant::type_error ) {
            return interpreter_variant( arr2[i] );
        }
    }
    double sum2 = 0.0;
    double sumsq2 = 0.0;
    unsigned long int counter2 = 0;
    // If an argument is an array or reference, only numbers in that array or reference are counted.
    // Empty cells, logical values, or text in the array or reference are ignored.
    sum2 += std::for_each( arr2.begin(), arr2.end(), internal::Sum() ).summe;
    sumsq2 += std::for_each( arr2.begin(), arr2.end(), internal::SumSq() ).summe;
    counter2 += std::for_each( arr2.begin(), arr2.end(), internal::Counter() ).counter;

    // If the number of data points in array1 or array2 is less than 2, FTEST returns the #DIV/0! error value.
    if ( counter1 < 2 || counter2 < 2 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double var1 = sumsq1 - sum1 * sum1 / counter1;
    var1 = var1 / ( counter1 - 1 );

    double var2 = sumsq2 - sum2 * sum2 / counter2;
    var2 = var2 / ( counter2 - 1 );

    // If the variance of array1 or array2 is zero, FTEST returns the #DIV/0! error value.
    if ( var1 == 0.0 || var2 == 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double F;
    double result = 0.0;
    if ( var1 < var2 ) {
        F = var2 / var1;
        boost::math::fisher_f dist( counter2 - 1, counter1 - 1 );
        result = cdf( complement( dist, F ) );
    } else {
        F = var1 / var2;
        boost::math::fisher_f dist( counter1 - 1, counter2 - 1 );
        result = cdf( complement( dist, F ) );
    }
    return interpreter_variant( variant( 2.0 * result ) );
}
#endif

/*!
 * \brief
 * Returns the beta cumulative distribution function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the beta cumulative distribution function
 *
 * \details
 * If probability = BETADIST(x,...), then BETAINV(probability,...) = x.
 *
 * \see
 * function_betainv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_betadist
interpreter_variant function_betadist( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, BETADIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // the value at which to evaluate the function.
    double alpha = parameters[1].numeric(); // shape parameter of the distribution.
    double beta = parameters[2].numeric(); // shape parameter of the distribution.
    double A = 0.0; // optional lower bound to the interval of x.
    double B = 1.0; // optional upper bound to the interval of x.

    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        if ( parameters[3].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        A = parameters[3].numeric();
    }

    if ( parameters.count() > 4 ) {
        if ( parameters[4].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        B = parameters[4].numeric();
    }
    // If alpha <= 0 or beta <= 0 or if x < A, x > B or A = B, BETADIST returns the #NUM! error value.
    if ( alpha <= 0.0 || beta <= 0.0 || x < A || x > B || A == B ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::beta_distribution<> dist( alpha, beta );
    double y = ( x - A ) / ( B - A );
    double result = cdf( dist, y );
    return interpreter_variant( variant( result ) );
    // Returns the beta cumulative distribution function.
}
#endif

/*!
 * \brief
 * Returns the inverse of the cumulative distribution function for a specified beta distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the cumulative beta distribution function
 *
 * \details
 * If probability = BETADIST(x,...), then BETAINV(probability,...) = x.
 *
 * \see
 * function_betadist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
#ifdef function_betainv
interpreter_variant function_betainv( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, BETAINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability associated with the beta distribution.
    double alpha = parameters[1].numeric(); // shape parameter of the distribution.
    double beta = parameters[2].numeric(); // shape parameter of the distribution.
    double A = 0.0; // optional lower bound to the interval of x.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        if ( parameters[3].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        A = parameters[3].numeric();
    }
    double B = 1.0; // optional upper bound to the interval of x.
    if ( parameters.count() > 4 ) {
        if ( parameters[4].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        B = parameters[4].numeric();
    }
    // If alpha <= 0 or beta <= 0 or if probability <= 0 or probability > 1 or A >= B, BETAINV returns the #NUM! error value.
    if ( alpha <= 0.0 || beta <= 0.0 || probability <= 0.0 || probability > 1.0 || A >= B ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::beta_distribution<> dist( alpha, beta );
    double x = quantile( dist, probability );
    double result = x * ( B - A ) + A;
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the cumulative distribution function for a specified beta distribution.
}
#endif

/*!
 * \brief
 * Returns a reference to a range that is a specified number of rows and columns from a cell or range of cells.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the reference to the range
 *
 * \details
 *
 *
 * \see
 * function_address | function_choose | function_hlookup | function_index | function_indirect | function_lookup | function_match | function_vlookup
 *
 * \author
 *
 */
/*interpreter_variant function_offset( calculation_context& cx, unsigned int param ) {
internal::ParameterList parameters( cx, param );

interpreter_variant ref = parameters[0]; // the reference from which you want to base the offset.
Point current_position;
int height = 1; // the height, in number of rows, that you want the returned reference to be. height must be a positive number.
int width = 1; // the width, in number of columns, that you want the returned reference to be. width must be a positive number.
if( ref.i_type() == interpreter_variant::type_cell ) {
current_position = reinterpret_cast<const Cell*>( ref.reference() )->getPoint();
} else {
current_position = reinterpret_cast<const range*>( ref.reference() )->upper_left();
// If height or width is omitted, it is assumed to be the same height or width as reference.
height = reinterpret_cast<const range*>( ref.reference() )->get_rowHeight();
width = reinterpret_cast<const range*>( ref.reference() )->get_columnWidth();
}

// ist zelle
Point offset_position = current_position.offset( Point( static_cast<int>( parameters[1].numeric() ), static_cast<int>(parameters[2].numeric()) ) );
Cell * cell_ptr = cx.get_current_cell().get_worksheet().getCell( offset_position );
return interpreter_variant( cell_ptr == NULL ? variant(variant::type_empty) : cell_ptr->get_value( cx ), cell_ptr );

return interpreter_variant( range( offset_position, offset_position.offset( height, width ), cx.get_current_cell().get_worksheet() ) );

if(parameters.size() >= 4 && parameters[3].type() != variant::type_empty ) {
height = static_cast<int>( parameters[3].numeric() );
}else{
if(ref.i_type() == interpreter_variant::type_range) {
range& myRange = *static_cast<range*>( ref.reference() );
height = myRange.get_row_count();
}else{
height = 1;
}
}

if(parameters.size() == 5) {
width = static_cast<int>( parameters[4].numeric() );
}else{
if(ref.i_type() == interpreter_variant::type_range) {
range& myRange = *static_cast<range*>( ref.reference() );
width = myRange.get_column_count();
}else{
width = 1;
}
}
// Returns a reference to a range that is a specified number of rows and columns from a cell or range of cells.
// The reference that is returned can be a single cell or a range of cells.
}*/


void register_functions( function_registry& r )
{
    r.register_function( ::function_entry( &function_sum, "sum", "", false, false, false, false, return_type_format::numeric ) );
    r.register_function( ::function_entry( &function_rand, "rand", "", true ) );

    r.register_function( ::function_entry( &function_if, "if", "", false, true ) );
    r.register_function( ::function_entry( &function_now, "now", "", true, false, false, false, return_type_format::date_time ) );
    r.register_function( ::function_entry( &function_today, "today", "", true ) );
    r.register_function( ::function_entry( &function_vlookup, "vlookup", "" ) );
    r.register_function( ::function_entry( &function_indirect, "indirect", "", true ) );
    r.register_function( ::function_entry( &function_transpose, "transpose", "" ) );
    r.register_function( ::function_entry( &function_mmult, "mmult", "" ) );
    r.register_function( ::function_entry( &function_mdeterm, "mdeterm", "" ) );
    r.register_function( ::function_entry( &function_minverse, "minverse", "" ) );
    r.register_function( ::function_entry( &function_max, "max", "" ) );
    r.register_function( ::function_entry( &function_maxa, "maxa", "" ) );
    r.register_function( ::function_entry( &function_min, "min", "" ) );
    r.register_function( ::function_entry( &function_mina, "mina", "" ) );
    r.register_function( ::function_entry( &function_product, "product", "" ) );
    r.register_function( ::function_entry( &function_sumproduct, "sumproduct", "" ) );
    r.register_function( ::function_entry( &function_geomean, "geomean", "" ) );
    r.register_function( ::function_entry( &function_harmean, "harmean", "" ) );
    r.register_function( ::function_entry( &function_devsq, "devsq", "" ) );
    r.register_function( ::function_entry( &function_stdev, "stdev",  "", false, false, false, false, return_type_format::numeric  ) );
    r.register_function( ::function_entry( &function_var, "var", "", false, false, false, false, return_type_format::numeric  ) );
    r.register_function( ::function_entry( &function_stdeva, "stdeva", "", false, false, false, false, return_type_format::numeric ) );
    r.register_function( ::function_entry( &function_vara, "vara", "" ) );
    r.register_function( ::function_entry( &function_stdevp, "stdevp", "" ) );
    r.register_function( ::function_entry( &function_varp, "varp", "" ) );
    r.register_function( ::function_entry( &function_stdevpa, "stdevpa", "" ) );
    r.register_function( ::function_entry( &function_varpa, "varpa", "" ) );
    r.register_function( ::function_entry( &function_skew, "skew", "" ) );
    r.register_function( ::function_entry( &function_kurt, "kurt", "" ) );
    r.register_function( ::function_entry( &function_avedev, "avedev", "" ) );
    r.register_function( ::function_entry( &function_mode, "mode", "" ) );
    r.register_function( ::function_entry( &function_covar, "covar", "" ) );
    r.register_function( ::function_entry( &function_correl, "correl", "" ) );
    r.register_function( ::function_entry( &function_rsq, "rsq", "" ) );
    r.register_function( ::function_entry( &function_pearson, "pearson", "" ) );
    r.register_function( ::function_entry( &function_slope, "slope", "" ) );
    r.register_function( ::function_entry( &function_intercept, "intercept", "" ) );
    r.register_function( ::function_entry( &function_steyx, "steyx", "" ) );
    r.register_function( ::function_entry( &function_forecast, "forecast", "" ) );
    r.register_function( ::function_entry( &function_sumx2py2, "sumx2py2", "" ) );
    r.register_function( ::function_entry( &function_sumx2my2, "sumx2my2", "" ) );
    r.register_function( ::function_entry( &function_sumxmy2, "sumxmy2", "" ) );
    r.register_function( ::function_entry( &function_prob, "prob", "" ) );
    r.register_function( ::function_entry( &function_concatenate, "concatenate", "" ) );
    r.register_function( ::function_entry( &function_or, "or", "" ) );
    r.register_function( ::function_entry( &function_and, "and", "" ) );
    r.register_function( ::function_entry( &function_true, "true", "" ) );
    r.register_function( ::function_entry( &function_false, "false", "" ) );
    r.register_function( ::function_entry( &function_rept, "rept", "" ) );
    r.register_function( ::function_entry( &function_replace, "replace", "" ) );
    r.register_function( ::function_entry( &function_left, "left", "" ) );
    r.register_function( ::function_entry( &function_right, "right", "" ) );
    r.register_function( ::function_entry( &function_countblank, "countblank", "" ) );
    r.register_function( ::function_entry( &function_sqrt, "sqrt", "" ) );
    r.register_function( ::function_entry( &function_sign, "sign", "" ) );
    r.register_function( ::function_entry( &function_exp, "exp", "" ) );
    r.register_function( ::function_entry( &function_log, "log", "" ) );
    r.register_function( ::function_entry( &function_ln, "ln", "" ) );
    r.register_function( ::function_entry( &function_log10, "log10", "" ) );
    r.register_function( ::function_entry( &function_cos, "cos", "" ) );
    r.register_function( ::function_entry( &function_sin, "sin", "" ) );
    r.register_function( ::function_entry( &function_tan, "tan", "" ) );
    r.register_function( ::function_entry( &function_acos, "acos", "" ) );
    r.register_function( ::function_entry( &function_asin, "asin", "" ) );
    r.register_function( ::function_entry( &function_atan, "atan", "" ) );
    r.register_function( ::function_entry( &function_atan2, "atan2", "" ) );
    r.register_function( ::function_entry( &function_pi, "pi", "" ) );
    r.register_function( ::function_entry( &function_normsdist, "normsdist", "" ) );
    r.register_function( ::function_entry( &function_normdist, "normdist", "" ) );
    r.register_function( ::function_entry( &function_lognormdist, "lognormdist", "" ) );
    r.register_function( ::function_entry( &function_ztest, "ztest", "" ) );
    r.register_function( ::function_entry( &function_normsinv, "normsinv", "" ) );
    r.register_function( ::function_entry( &function_norminv, "norminv", "" ) );
    r.register_function( ::function_entry( &function_confidence, "confidence", "" ) );
    r.register_function( ::function_entry( &function_loginv, "loginv", "" ) );
    r.register_function( ::function_entry( &function_mod, "mod", "" ) );
    r.register_function( ::function_entry( &function_int, "int", "" ) );
    r.register_function( ::function_entry( &function_power, "power", "" ) );
    r.register_function( ::function_entry( &function_isnumber, "isnumber", "" ) );
    r.register_function( ::function_entry( &function_proper, "proper", "" ) );
    r.register_function( ::function_entry( &function_toupper, "upper", "" ) );
    r.register_function( ::function_entry( &function_tolower, "lower", "" ) );
    r.register_function( ::function_entry( &function_even, "even", "" ) );
    r.register_function( ::function_entry( &function_odd, "odd", "" ) );
    r.register_function( ::function_entry( &function_roundup, "roundup", "" ) );
    r.register_function( ::function_entry( &function_rounddown, "rounddown", "" ) );
    r.register_function( ::function_entry( &function_trunc, "trunc", "" ) );
    r.register_function( ::function_entry( &function_count, "count", "" ) );
    r.register_function( ::function_entry( &function_counta, "counta", "" ) );
    r.register_function( ::function_entry( &function_sumsq, "sumsq", "", false, false, false, false, return_type_format::numeric ) );
    r.register_function( ::function_entry( &function_trimmean, "trimmean", "" ) );
    r.register_function( ::function_entry( &function_average, "average", "" ) );
    r.register_function( ::function_entry( &function_averagea, "averagea", "" ) );
    r.register_function( ::function_entry( &function_averagee, "averagee", "" ) );
    r.register_function( ::function_entry( &function_istext, "istext", "" ) );
    r.register_function( ::function_entry( &function_abs, "abs", "" ) );
    r.register_function( ::function_entry( &function_len, "len", "" ) );
    r.register_function( ::function_entry( &function_exact, "exact", "" ) );
    r.register_function( ::function_entry( &function_large, "large", "" ) );
    r.register_function( ::function_entry( &function_small, "small", "" ) );
    r.register_function( ::function_entry( &function_t, "t", "" ) );//
    r.register_function( ::function_entry( &function_iseven, "iseven", "" ) );
    r.register_function( ::function_entry( &function_isodd, "isodd", "" ) );
    r.register_function( ::function_entry( &function_index, "index", "" ) );
    r.register_function( ::function_entry( &function_floor, "floor", "" ) );
    r.register_function( ::function_entry( &function_mround, "mround", "" ) );
    r.register_function( ::function_entry( &function_ceiling, "ceiling", "" ) );
    r.register_function( ::function_entry( &function_trim, "trim", "" ) );
    r.register_function( ::function_entry( &function_substitute, "substitute", "" ) );
    r.register_function( ::function_entry( &function_find, "find", "" ) );
    r.register_function( ::function_entry( &function_search, "search", "" ) );
    r.register_function( ::function_entry( &function_mid, "mid", "" ) );
    r.register_function( ::function_entry( &function_not, "not", "" ) );
    r.register_function( ::function_entry( &function_na, "na", "" ) );
    r.register_function( ::function_entry( &function_median, "median", "" ) );
    r.register_function( ::function_entry( &function_quartile, "quartile", "" ) );
    r.register_function( ::function_entry( &function_percentile, "percentile", "" ) );
    r.register_function( ::function_entry( &function_char, "char", "" ) );
    r.register_function( ::function_entry( &function_code, "code", "" ) );
    r.register_function( ::function_entry( &function_sumif, "sumif", "" ) );
    r.register_function( ::function_entry( &function_countif, "countif", "" ) );
    r.register_function( ::function_entry( &function_isref, "isref", "" ) );
    r.register_function( ::function_entry( &function_rows, "rows", "" ) );
    r.register_function( ::function_entry( &function_columns, "columns", "" ) );
    r.register_function( ::function_entry( &function_column, "column", "" ) );
    r.register_function( ::function_entry( &function_row, "row", "" ) );
    r.register_function( ::function_entry( &function_choose, "choose", "" ) );
    r.register_function( ::function_entry( &function_rank, "rank", "" ) );
    r.register_function( ::function_entry( &function_percentrank, "percentrank", "" ) );
    r.register_function( ::function_entry( &function_frequency, "frequency", "" ) );
    r.register_function( ::function_entry( &function_degrees, "degrees", "" ) );
    r.register_function( ::function_entry( &function_radians, "radians", "" ) );
    r.register_function( ::function_entry( &function_fact, "fact", "" ) );
    r.register_function( ::function_entry( &function_permut, "permut", "" ) );
    r.register_function( ::function_entry( &function_combin, "combin", "" ) );
    r.register_function( ::function_entry( &function_type, "type", "" ) );
    r.register_function( ::function_entry( &function_lookup, "lookup", "" ) );
    r.register_function( ::function_entry( &function_hlookup, "hlookup", "" ) );
    r.register_function( ::function_entry( &function_cosh, "cosh", "" ) );
    r.register_function( ::function_entry( &function_sinh, "sinh", "" ) );
    r.register_function( ::function_entry( &function_tanh, "tanh", "" ) );
    r.register_function( ::function_entry( &function_address, "address", "" ) );
    r.register_function( ::function_entry( &function_fv, "fv", "" ) );
    r.register_function( ::function_entry( &function_acosh, "acosh", "" ) );
    r.register_function( ::function_entry( &function_asinh, "asinh", "" ) );
    r.register_function( ::function_entry( &function_atanh, "atanh", "" ) );
    r.register_function( ::function_entry( &function_db, "db", "" ) );
    r.register_function( ::function_entry( &function_ddb, "ddb", "" ) );
    r.register_function( ::function_entry( &function_sln, "sln", "" ) );
    r.register_function( ::function_entry( &function_syd, "syd", "" ) );
    r.register_function( ::function_entry( &function_round, "round", "" ) );
    r.register_function( ::function_entry( &function_standardize, "standardize", "" ) );
    r.register_function( ::function_entry( &function_pmt, "pmt", "" ) );
    r.register_function( ::function_entry( &function_pv, "pv", "" ) );
    //r.register_function( ::function_entry( &function_ipmt, "ipmt", "" ) );
    r.register_function( ::function_entry( &function_irr, "irr", "" ) );
    r.register_function( ::function_entry( &function_ispmt, "ispmt", "" ) );
    r.register_function( ::function_entry( &function_mirr, "mirr", "" ) );
    r.register_function( ::function_entry( &function_nper, "nper", "" ) );
    r.register_function( ::function_entry( &function_npv, "npv", "" ) );
    //r.register_function( ::function_entry( &function_ppmt, "ppmt", "" ) );
    r.register_function( ::function_entry( &function_rate, "rate", "" ) );
    //r.register_function( ::function_entry( &function_vdb, "vdb", "" ) );
    r.register_function( ::function_entry( &function_fisher, "fisher", "" ) );
    r.register_function( ::function_entry( &function_fisherinv, "fisherinv", "" ) );
    r.register_function( ::function_entry( &function_weibull, "weibull", "" ) );
    r.register_function( ::function_entry( &function_isnontext, "isnontext", "" ) );
    r.register_function( ::function_entry( &function_isblank, "isblank", "" ) );
    r.register_function( ::function_entry( &function_islogical, "islogical", "" ) );
    r.register_function( ::function_entry( &function_isna, "isna", "" ) );
    r.register_function( ::function_entry( &function_error_type, "error.type", "" ) );
    r.register_function( ::function_entry( &function_iserr, "iserr", "" ) );
    r.register_function( ::function_entry( &function_iserror, "iserror", "" ) );
    r.register_function( ::function_entry( &function_binomdist, "binomdist", "" ) );
    r.register_function( ::function_entry( &function_critbinom, "critbinom", "" ) );
    r.register_function( ::function_entry( &function_hypgeomdist, "hypgeomdist", "" ) );
    r.register_function( ::function_entry( &function_negbinomdist, "negbinomdist", "" ) );
    r.register_function( ::function_entry( &function_poisson, "poisson", "" ) );
    r.register_function( ::function_entry( &function_expondist, "expondist", "" ) );
    r.register_function( ::function_entry( &function_tdist, "tdist", "" ) );
    r.register_function( ::function_entry( &function_tinv, "tinv", "" ) );
    r.register_function( ::function_entry( &function_ttest, "ttest", "" ) );
    r.register_function( ::function_entry( &function_gammaln, "gammaln", "" ) );
    r.register_function( ::function_entry( &function_gammadist, "gammadist", "" ) );
    r.register_function( ::function_entry( &function_gammainv, "gammainv", "" ) );
    r.register_function( ::function_entry( &function_chidist, "chidist", "" ) );
    r.register_function( ::function_entry( &function_chiinv, "chiinv", "" ) );
    r.register_function( ::function_entry( &function_chitest, "chitest", "" ) );
    r.register_function( ::function_entry( &function_fdist, "fdist", "" ) );
    r.register_function( ::function_entry( &function_finv, "finv", "" ) );
    r.register_function( ::function_entry( &function_ftest, "ftest", "" ) );
    r.register_function( ::function_entry( &function_betadist, "betadist", "" ) );
    r.register_function( ::function_entry( &function_betainv, "betainv", "" ) );
    r.register_function( ::function_entry( &function_isunique, "isunique", "" ) );
    r.register_function( ::function_entry( &function_isduplicate, "isduplicate", "" ) );
    r.register_function( ::function_entry( &function_between, "between", "" ) );
    r.register_function( ::function_entry( &function_nbetween, "nbetween", "" ) );
    r.register_function( ::function_entry( &function_volatile_count, "volatile_count", "" ) );
    r.register_function( ::function_entry( &function_used_range, "used_range", "", true ) );
    r.register_function( ::function_entry( &function_text, "text", "" ) );
    r.register_function( ::function_entry( &function_match, "match", "" ) );
    r.register_function( ::function_entry( &function_offset, "offset", "", true ) );
    r.register_function( ::function_entry( &function_hiderow, "hiderow", "", false, false, true, false ) );
    r.register_function( ::function_entry( &function_hidecolumn, "hidecolumn", "", false, false, true, false ) );
    r.register_function( ::function_entry( &function_randbetween, "randbetween", "", true ) );
    r.register_function( ::function_entry( &function_currentuser, "currentuser", "" ) );
    r.register_function( ::function_entry( &function_usergroups, "usergroups", "" ) );
    r.register_function( ::function_entry( &function_userlocale, "userlocale", "" ) );
    r.register_function( ::function_entry( &function_month, "month", "" ) );
    r.register_function( ::function_entry( &function_day, "day", "" ) );
    r.register_function( ::function_entry( &function_year, "year", "" ) );
    r.register_function( ::function_entry( &function_weeknum, "weeknum", "" ) );
    r.register_function( ::function_entry( &function_date, "date", "" ) );
    r.register_function( ::function_entry( &function_time, "time", "" ) );
    r.register_function( ::function_entry( &function_concatenate_range, "concatenate.range", "" ) );
    r.register_function( ::function_entry( &function_value, "value", "" ) );
    r.register_function( ::function_entry( &function_unformatted, "unformatted", "" ) );

}
