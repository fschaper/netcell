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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

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
                if ( ( ! m_max_result.has_value ) || ( double )v > m_max_result.max ) {
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
                if ( ( ! m_maxa_result.has_value ) || ( double )v > m_maxa_result.maxa ) {
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
                if ( ( ! m_min_result.has_value ) || ( double )v < m_min_result.min ) {
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
                if ( ( ! m_mina_result.has_value ) || ( double )v < m_mina_result.mina ) {
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
};

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
    size_t res = lu_factorize( A, pm );
    if ( res != 0 ) {
        return false;
    }

    // Create identity matrix of "inverse".
    inverse.assign( boost::numeric::ublas::identity_matrix<T>( A.size1() ) );

    // Backsubstitute to get the inverse.
    boost::numeric::ublas::lu_substitute( A, pm, inverse );

    return true;
};


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
};

