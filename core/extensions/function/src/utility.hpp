
#pragma once

#include <wss/define.hpp>
#include <wss/range.hpp>

#include <wss/calculation_context.hpp>
#include <wss/sparse_range.hpp>

#ifdef xxx
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
// binomdist_density helps to calculate function_binomdist and function_critbinom.
double binomdist_density( long long number_s, long long trials, double probability_s )
{
    double result = pow( probability_s, static_cast<double>( number_s ) ) * pow( 1.0 - probability_s, static_cast<double>( trials - number_s ) );
    result *= static_cast<double>( combin( trials, number_s ) );

    return result;
}

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

#endif
namespace internal
{

    struct State {
        State()
            : is_array( false )
            , is_range( false ) {}

        State( bool is_array, bool is_range )
            : is_array( is_array )
            , is_range( is_range ) {}

        bool is_array;
        bool is_range;
    };

    class AverageStrategy //------------------------------------------------------------------------------------------
    {
    public:
        struct average_result {
            average_result()
                : summe( 0.0 )
                , count( 0 ) {}

            double summe;
            long int count;
        };

        typedef average_result return_type;

        AverageStrategy() {}

        operator return_type() const {
            return m_average_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    m_average_result.summe += boost::lexical_cast<double>( v );
                    m_average_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double counts for all states.
            m_average_result.summe += v;
            m_average_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_average_result.summe += v == true ? 1.0 : 0.0;
                m_average_result.count++;
            }
            // otherwise a bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_average_result.count++;
            }
            // otherwise empty is ignored.
        }

    private:
        average_result m_average_result;
    };

    class VarStrategy // also for VARP, STDEV, STDEVP, DEVSQ--------------------------------------------------------
    {
    public:
        struct var_result {
            var_result()
                : summe( 0.0 )
                , sumsq( 0.0 )
                , count( 0 ) {}

            double summe;
            double sumsq;
            long int count;
        };

        typedef var_result return_type;

        VarStrategy() {}

        operator return_type() const {
            return m_var_result;
        }

        void handle( const State& s, const std::string& v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                try {
                    // text representations of numbers are counted.
                    double newDouble = boost::lexical_cast<double>( v );
                    m_var_result.summe += newDouble;
                    m_var_result.sumsq += newDouble * newDouble;
                    m_var_result.count++;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    throw variant( variant::error_value );
                }
            }
            // otherwise text is ignored.
        }

        void handle( const State& s, double v ) {
            // A double is evaluated for all states.
            m_var_result.summe += v;
            m_var_result.sumsq += v * v;
            m_var_result.count++;
        }

        void handle( const State& s, bool v ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_var_result.summe += v == true ? 1.0 : 0.0;
                m_var_result.sumsq += v == true ? 1.0 : 0.0;
                m_var_result.count++;
            }
            // otherwise bool is ignored.
        }

        void handle( const State& s, variant::error_type error ) {
            // An error value causes an error for all states.
            throw variant( error );
        }

        void handle( const State& s ) {
            if ( ( !s.is_array ) && !s.is_range ) {
                m_var_result.count++;
            }
            // otherwise empty is ignored.
        }

    private:
        var_result m_var_result;
    };

    template< class strategy_T >
    class Reduce
    {
    public:
        typedef strategy_T strategy_type;

        Reduce( function_parameter& parameters )
            : m_parameters( parameters ) {}

        inline void operator()( const variant& value ) {
            ( *this )( value, State() );
        }

        inline void operator()( const interpreter_variant& value, const State& s = State() ) {
            switch ( value.i_type() ) {
                case interpreter_variant::type_named_formula:
                    //nothing to do in that case
                    break;
                case interpreter_variant::type_range: { // TODO: sparse
                    range_reference& rref = range_reference_cast( value.reference() );
                    sparse_range_array sra( rref, m_parameters.context() );
                    unsigned int xmax = rref.actualize().position().column_count();
                    unsigned int ymax = rref.actualize().position().row_count();
                    variant::sparse_array_type arr = variant::sparse_array_type( xmax * ymax );
                    for ( unsigned int y = 0; y < ymax; y++ ) {
                        for ( unsigned int x = 0; x < xmax; x++ ) {
                            arr[y* xmax+x] = sra( x, y );
                        }
                    }
                    variant result( arr, xmax );
                    ( *this )( interpreter_variant( result ), State( ( result.type() == variant::type_array ), true ) );
                    //const variant array_value = static_cast<Range*>( value.reference() )->get_value( m_interpreter_context );
                    //( *this )( array_value, State( ( array_value.type() == variant::type_array ), true ) );
                }
                break;

                case interpreter_variant::type_value:
                    switch ( value.type() ) {
                        case variant::type_bool:
                            m_strategy.handle( s, value.numeric() != 0.0 );
                            break;

                        case variant::type_double:
                            m_strategy.handle( s, value.numeric() );
                            break;

                        case variant::type_string:
                            m_strategy.handle( s, value.string() );
                            break;

                        case variant::type_array: {
                            const variant::sparse_array_type& array = value.array();
                            variant::sparse_array_type::const_iterator it = array.begin();
                            variant::sparse_array_type::const_iterator end = array.end();
                            for ( ; it != end; ++it ) {
                                ( *this )( interpreter_variant( *it ), State( true, s.is_range ) );
                            }
                            break;
                        }

#undef ERROR

                        case variant::type_error:
                            m_strategy.handle( s, static_cast<variant::error_type>( static_cast<int>( value.numeric() ) ) );
                            break;

                        case variant::type_empty:
                            m_strategy.handle( s );
                            break;
                    }
                    break;
                default:
                    throw std::logic_error( "invalid case" );
            }
        }

        operator typename strategy_type::return_type() const {
            return m_strategy;
        }

    private:
        strategy_type m_strategy;
        function_parameter& m_parameters;
    };


    typedef Reduce<AverageStrategy> Average;
    typedef Reduce<VarStrategy> Var;
}
