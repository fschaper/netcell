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
*  Dragan Simic <dragan.simic@develabs.com>
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*  Momcilo Kleut <momcilo.kleut@develabs.com>
*/

#ifndef _JSONSERIALIZER
# define _JSONSERIALIZER

// stl
#include <vector>
#include <string>

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4244; disable:4267)
# endif

// boost
//#include <boost/cstdint.hpp>
//#include <boost/tuple/tuple.hpp>
//#include <boost/algorithm/string/join.hpp>
//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_io.hpp>

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

// ui_backend
#include "memory_manager.hpp"

// jlib
//#include <wss/non_instantiable.hpp>

// wss
//#include <wss/variant.hpp>
//#include <wss/sheet_point.hpp>
//#include <wss/sheet_point.hpp>
//#include <wss/Range.hpp>
//#include <wss/Rect.hpp>

//#include <wss/get_conditional_format.hpp>
//#include <wss/variant.hpp>
//#include <wss/sheet_point.hpp>
//#include <wss/sheet_range.hpp>
//#include <wss/dependency_info.hpp>
// tinyjson
#include <tinyjson/tinyjson.hpp>
//#include <wss/border_types.hpp>

#undef ANGLED_ARRAY
#undef CURLY_OBJECT

#undef DEFAULT_ENC
#undef PAIR_SECOND_RAW
#undef PAIR_AS_ASSOCIATIVE
#undef POINT_TRANSFORM_COORD
#undef RAW_IF_CURL_OR_ANGL

#ifdef ERROR
#undef ERROR
#endif

#ifdef JSON_ENCODING_FUNCARG
# undef JSON_ENCODING_FUNCARG
#endif

// compact the code a bit...
#define JSON_ENCODING_FUNCARG const unsigned long encoding = JsonEncoding::DEFAULT_ENC



/**
 * JSON serializer for the compound commands results
 */
class JSONSerializer
{
protected:
    typedef std::string json_serialized_type;

    class JsonBraces: non_instantiable
    {
    public:
        enum Type {
            NO_BRACES,
            ANGLED_ARRAY,
            CURLY_OBJECT
        };
    };

public:
    class JsonEncoding: non_instantiable
    {
    public:
        enum Type {
            DEFAULT_ENC           = 0lu,
            PAIR_SECOND_RAW       = 1lu,
            PAIR_AS_ASSOCIATIVE   = 2lu, // => JSON object;  default: as list => JSON array
            POINT_TRANSFORM_COORD = 4lu,
            RAW_IF_CURL_OR_ANGL   = 8lu
        };
    };

protected:
    template<typename T>
    class RecursiveSerializerImpl
    {
    public:
        inline json_serialized_type operator()( const T& value, JSON_ENCODING_FUNCARG ) const {
            json_serialized_type return_value;

            for ( typename T::const_iterator it = value.begin(), end = value.end(); it != end; ) {
                return_value.append( JSONSerializer()( *it, encoding ) );
                if ( ++it != end ) {
                    return_value.append( "," );
                }
            }

            return return_value;
        }
    };

    template<typename T, int>
    class RecursiveSerializer;

    template<typename T>
    class RecursiveSerializer<T, JsonBraces::ANGLED_ARRAY>
    {
    public:
        inline json_serialized_type operator()( const T& value, JSON_ENCODING_FUNCARG ) const {
            return json_serialized_type( "[" ).append( RecursiveSerializerImpl<T>()( value, encoding ) )
                   .append( "]" );
        }
    };

    template<typename T>
    class RecursiveSerializer<T, JsonBraces::CURLY_OBJECT>
    {
    public:
        inline json_serialized_type operator()( const T& value, JSON_ENCODING_FUNCARG ) const {
            return json_serialized_type( "{" ).append( RecursiveSerializerImpl<T>()( value, encoding ) )
                   .append( "}" );
        }
    };


protected:
    template<typename T>
    class PrintingSerializer
    {
    public:
        inline json_serialized_type operator()( const T& value, JSON_ENCODING_FUNCARG ) const {
            std::stringstream value_printed;
            value_printed.precision( 20 );

            value_printed << value;

            return value_printed.str();
        }
    };

protected:
    template<typename T, typename U, int>
    class PairSerializer;

    template<typename T, typename U>
    class PairSerializer<T, U, JsonBraces::NO_BRACES>
    {
    public:
        inline json_serialized_type operator()( const T first, const U second, JSON_ENCODING_FUNCARG ) const {
            return JSONSerializer()( first, encoding )
                   .append( ( encoding & JsonEncoding::PAIR_AS_ASSOCIATIVE ) ? ":" : "," )
                   .append( ( encoding & JsonEncoding::PAIR_SECOND_RAW ) ? PrintingSerializer<U>()( second )
                            : JSONSerializer()( second, encoding ) );
        }
    };

    template<typename T, typename U>
    class PairSerializer<T, U, JsonBraces::ANGLED_ARRAY>
    {
    public:
        inline json_serialized_type operator()( const T first, const U second, JSON_ENCODING_FUNCARG ) const {
            return json_serialized_type( "[" ).append( PairSerializer<T, U, JsonBraces::NO_BRACES>()( first, second, encoding ) )
                   .append( "]" );
        }
    };

    template<typename T, typename U>
    class PairSerializer<T, U, JsonBraces::CURLY_OBJECT>
    {
    public:
        inline json_serialized_type operator()( const T first, const U second, JSON_ENCODING_FUNCARG ) const {
            return json_serialized_type( "{" ).append( PairSerializer<T, U, JsonBraces::NO_BRACES>()( first, second, encoding ) )
                   .append( "}" );
        }
    };

public:
    inline json_serialized_type operator()( const bool value, JSON_ENCODING_FUNCARG ) const {
        return value ? json_serialized_type( "true" ) : json_serialized_type( "false" );
    }

    inline json_serialized_type operator()( const int value, JSON_ENCODING_FUNCARG ) const {
        return PrintingSerializer<int>()( value );
    }

    inline json_serialized_type operator()( const unsigned value, JSON_ENCODING_FUNCARG ) const {
        return PrintingSerializer<unsigned>()( value );
    }

    inline json_serialized_type operator()( const long value, JSON_ENCODING_FUNCARG ) const {
        return PrintingSerializer<long>()( value );
    }

    inline json_serialized_type operator()( const unsigned long value, JSON_ENCODING_FUNCARG ) const {
        return PrintingSerializer<unsigned long>()( value );
    }

    inline json_serialized_type operator()( const double value, JSON_ENCODING_FUNCARG ) const {
        return PrintingSerializer<double>()( value );
    }

    inline json_serialized_type operator()( const uuid_type& value, JSON_ENCODING_FUNCARG ) const {
        return json_serialized_type( "\"" ).append( boost::lexical_cast<std::string>( value ) ).append( "\"" );
    }

    inline json_serialized_type operator()( const std::string& value, JSON_ENCODING_FUNCARG ) const {
        char c = value[0];

        if ( encoding& JsonEncoding::RAW_IF_CURL_OR_ANGL && ( c == '{' || c == '[' ) ) {
            return json_serialized_type( "" ).append( value );
        }

        std::stringstream value_out;

        for ( json_serialized_type::const_iterator it = value.begin(), end = value.end(); it != end; ++it )
            switch ( *it ) {
                case '\b':
                    value_out << "\\b";
                    break;
                case '\f':
                    value_out << "\\f";
                    break;
                case '\n':
                    value_out << "\\n";
                    break;
                case '\r':
                    value_out << "\\r";
                    break;
                case '\t':
                    value_out << "\\t";
                    break;

                case '"':
                case '\\':
                case '/':
                    value_out << '\\';

                default:
                    value_out << *it;
                    break;
            }

        return json_serialized_type( "\"" ).append( value_out.str() ).append( "\"" );
    }

    inline json_serialized_type operator()( const std::vector<bool>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<bool>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<long>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<long>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<unsigned>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<unsigned>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<unsigned long>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<unsigned long>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<double>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<double>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::string>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::string>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<border_style_flyweight_type>& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<border_style_flyweight_type>, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::pair<sheet_point, variant>& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<sheet_point, variant, JsonBraces::ANGLED_ARRAY>()
               ( value.first, value.second, encoding & ~JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

    inline json_serialized_type operator()( const std::map<uuid_type, uuid_type>::value_type& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<std::map<uuid_type, uuid_type>::value_type::first_type, std::map<uuid_type, uuid_type>::value_type::second_type, JsonBraces::NO_BRACES>()
               ( value.first, value.second, encoding | JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

    inline json_serialized_type operator()( const std::list<std::pair<sheet_point, variant> >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::list<std::pair<sheet_point, variant> >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::list<std::pair<sheet_point, variant> > >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::list<std::pair<sheet_point, variant> > >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const variant::variant_array_type& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<variant::variant_array_type, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::map<uuid_type, uuid_type> & value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::map<uuid_type, uuid_type>, JsonBraces::CURLY_OBJECT>()( value, encoding );
    }

    inline json_serialized_type operator()( std::vector<get_conditionalformat_list_type> &cf_value, JSON_ENCODING_FUNCARG ) const {
        std::vector<get_conditionalformat_list_type>::iterator it_vec_vec = cf_value.begin();
        std::vector<get_conditionalformat_list_type>::iterator end_it_vec_vec = cf_value.end();
        std::vector<std::string> result;
        while ( it_vec_vec != end_it_vec_vec ) {
            for ( get_conditionalformat_list_type::const_iterator p = ( *it_vec_vec ).begin(); p != ( *it_vec_vec ).end(); p++ ) {
                std::stringstream format_out;
                format_out << "{";
                format_out               << "\"id\":"         << boost::lexical_cast<std::string>( ( *p ).id ) << ",";
                format_out               << "\"rule\":"       << ( *this )( ( *p ).rule );
                if ( !( *p ).format.empty() ) {
                    format_out  << ","   << "\"format\":"     << ( *this )( ( *p ).format )     ;
                }
                if ( !( *p ).style.empty() ) {
                    format_out  << ","   << "\"style\":"      << ( *this )( ( *p ).style )      ;
                }
                format_out  << ","       << "\"applies_to\":" << ( *this )( ( *p ).applies_to )  << ",";
                format_out               << "\"operands\":"   << ( *this )( ( *p ).operands );
                if ( ( *p ).lock_cells ) {
                    format_out   << ","  << "\"lock\":"       << ( *this )( *( *p ).lock_cells );
                }
                if ( ! p->borders.empty() ) {

                    get_conditional_format::border_map_type::const_iterator it_border = p->borders.begin();
                    get_conditional_format::border_map_type::const_iterator it_border_end = p->borders.end();
                    format_out << "," << "\"border\":" ;
                    format_out << "{" ;
                    while ( it_border != it_border_end ) {
                        switch ( ( *it_border ).first ) {
                            case border_types::top:
                                format_out << "\"top\":"  << ( *this )( ( *it_border ).second );
                                break;
                            case border_types::bottom:
                                format_out << "\"bottom\":"  << ( *this )( ( *it_border ).second );
                                break;
                            case border_types::left:
                                format_out << "\"left\":"  << ( *this )( ( *it_border ).second );
                                break;
                            case border_types::right:
                                format_out << "\"right\":"  << ( *this )( ( *it_border ).second );
                                break;
                            default:
                                assert( !"unknown border type returned by conditional format" );

                        }
                        ++it_border;
                        if ( it_border != it_border_end ) {
                            format_out << ",";
                        }
                    }

                    format_out << "}" ;
                }
                format_out << "}";
                result.push_back( format_out.str() );
            }
            ++it_vec_vec;
        }


        return "[" + boost::algorithm::join( result, "," ) + "]";
    }
public:
    inline json_serialized_type operator() ( const std::set<sheet_range> &br, JSON_ENCODING_FUNCARG ) const {
        std::set<sheet_range>::const_iterator it_begin = br.begin();
        std::set<sheet_range>::const_iterator it_end = br.end();
        std::stringstream format_out;
        format_out << "[";
        while ( it_begin != it_end ) {
            boost::int_fast32_t coord_offset = ( ( encoding & JsonEncoding::POINT_TRANSFORM_COORD ) ? 1 : 0 );
            format_out << "[";
            format_out << ( *it_begin ).upper_left().column() + coord_offset << ",";
            format_out << ( *it_begin ).upper_left().row() + coord_offset << ",";
            format_out << ( *it_begin ).lower_right().column() + coord_offset << ",";
            format_out << ( *it_begin ).lower_right().row() + coord_offset  ;
            format_out << "]";
            ++it_begin;

            if ( it_begin != it_end ) {
                format_out << ",";
            }
        }
        format_out << "]";

        return format_out.str();
    }
public:
    inline json_serialized_type operator() ( const std::list<sheet_range> &br, JSON_ENCODING_FUNCARG ) const {
        std::list<sheet_range>::const_iterator it_begin = br.begin();
        std::list<sheet_range>::const_iterator it_end = br.end();
        std::stringstream format_out;
        format_out << "[";
        while ( it_begin != it_end ) {
            boost::int_fast32_t coord_offset = ( ( encoding & JsonEncoding::POINT_TRANSFORM_COORD ) ? 1 : 0 );
            format_out << "[";
            format_out << ( *it_begin ).upper_left().column() + coord_offset << ",";
            format_out << ( *it_begin ).upper_left().row() + coord_offset << ",";
            format_out << ( *it_begin ).lower_right().column() + coord_offset << ",";
            format_out << ( *it_begin ).lower_right().row() + coord_offset  ;
            format_out << "]";
            ++it_begin;

            if ( it_begin != it_end ) {
                format_out << ",";
            }
        }
        format_out << "]";

        return format_out.str();
    }
public:
    inline json_serialized_type operator()( const std::vector< boost::tuple< std::string, std::string, std::string, std::string > > &id_name_mapping_ex_vec_type ) const {
        std::vector< boost::tuple< std::string, std::string, std::string, std::string > >::const_iterator it_vec_tuple = id_name_mapping_ex_vec_type.begin();
        std::vector< boost::tuple< std::string, std::string, std::string, std::string > >::const_iterator end_it_vec_tuple = id_name_mapping_ex_vec_type.end();
        typedef  boost::tuple< std::string, std::string, std::string, std::string >  item_tuple;
        std::vector<std::string> result;
        while ( it_vec_tuple != end_it_vec_tuple ) {
            std::stringstream format_out;
            item_tuple it = boost::any_cast<item_tuple>( *it_vec_tuple );
            format_out << "{";
            format_out << "\"id\":"   << ( *this )( boost::lexical_cast<std::string>( boost::get<0>( it ) ) ) << ",";
            format_out << "\"name\":" << ( *this )( boost::lexical_cast<std::string>( boost::get<1>( it ) ) ) << ",";
            format_out << "\"path\":" << ( *this )( boost::lexical_cast<std::string>( boost::get<2>( it ) ) ) << ",";
            format_out << "\"meta\":" << ( *this )( boost::lexical_cast<std::string>( boost::get<3>( it ) ) );
            format_out << "}";
            result.push_back( format_out.str() );
            ++it_vec_tuple;
        }
        return "[" + boost::algorithm::join( result, "," ) + "]";
    }

    inline json_serialized_type operator()( const variant& value, JSON_ENCODING_FUNCARG ) const {
        json_serialized_type return_value;

        switch ( value.type() ) {
            case variant::type_empty:
                return_value = "\"\"";
                break;

            case variant::type_double:
                return_value = ( *this )( value.numeric(), encoding );
                break;

            case variant::type_bool:
                // TODO this should be locale specific too
                return_value = ( value.boolean() ? "true" : "false" );
                break;


            case variant::type_error: {
                std::string error_value;
                switch ( value.error_code() ) {
                    case variant::error_div_null:
                        error_value = "#DIV/0!";
                        break;
                    case variant::error_n_a:
                        error_value = "#N/A!";
                        break;
                    case variant::error_name:
                        error_value = "#NAME!";
                        break;
                    case variant::error_null:
                        error_value = "#NULL!";
                        break;
                    case variant::error_num:
                        error_value = "#NUM!";
                        break;
                    case variant::error_ref:
                        error_value = "#REF!";
                        break;
                    case variant::error_value:
                        error_value = "#VALUE!";
                        break;
                    default:
                        error_value = "#UNKNOWN!";
                }
                return_value = JSONSerializer()( error_value );
                break;
            }

            case variant::type_string:
                return_value = ( *this )( value.string(), encoding ) ;
                break;

            case variant::type_array:
                return_value = ( *this )( value.array(), encoding );
                break;
        }

        return return_value ;
    }

public:
    inline json_serialized_type operator()( const sheet_range& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<json_serialized_type, json_serialized_type, JsonBraces::ANGLED_ARRAY>()
               (
                   ( *this )( value.upper_left(), encoding ),
                   ( *this )( value.lower_right(), encoding ),
                   encoding & ~JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

    inline json_serialized_type operator()( const sheet_point& value, JSON_ENCODING_FUNCARG ) const {
        boost::int_fast32_t coord_offset = ( ( encoding & JsonEncoding::POINT_TRANSFORM_COORD ) ? 1 : 0 );
        return PairSerializer<boost::int_fast32_t, boost::int_fast32_t, JsonBraces::ANGLED_ARRAY>()
               (
                   value.column() + coord_offset,
                   value.row() + coord_offset,
                   encoding & ~JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }



public:
    inline json_serialized_type operator()( const boost::tuple<unsigned long, unsigned long>& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<unsigned long, unsigned long, JsonBraces::ANGLED_ARRAY>()
               ( value.get<0>(), value.get<1>(), encoding & ~JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

public:
    inline json_serialized_type operator()( const std::pair<std::string, std::string>& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<std::string, std::string, JsonBraces::NO_BRACES>()
               ( value.first, value.second, encoding | JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

    inline json_serialized_type operator()( const std::vector<std::pair<std::string, std::string> >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::pair<std::string, std::string> >, JsonBraces::CURLY_OBJECT>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::vector<std::pair<std::string, std::string> > >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::vector<std::pair<std::string, std::string> > >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::vector<std::vector<std::pair<std::string, std::string> > > >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::vector<std::vector<std::pair<std::string, std::string> > > >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

public:
    inline json_serialized_type operator()( const std::pair<std::string, variant>& value, JSON_ENCODING_FUNCARG ) const {
        return PairSerializer<std::string, variant, JsonBraces::NO_BRACES>()
               ( value.first, value.second, encoding | JsonEncoding::PAIR_AS_ASSOCIATIVE );
    }

    inline json_serialized_type operator()( const std::vector<std::pair<std::string, variant> >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::pair<std::string, variant> >, JsonBraces::CURLY_OBJECT>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::vector<std::pair<std::string, variant> > >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::vector<std::pair<std::string, variant> > >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::vector<std::vector<std::pair<std::string, variant> > > >& value, JSON_ENCODING_FUNCARG ) const {
        return RecursiveSerializer<std::vector<std::vector<std::vector<std::pair<std::string, variant> > > >, JsonBraces::ANGLED_ARRAY>()( value, encoding );
    }

    inline json_serialized_type operator()( const std::vector<std::vector<std::map<std::string, variant > > >& value, JSON_ENCODING_FUNCARG ) const {

        json_serialized_type ret( "" );
        std::vector<std::vector<std::map<std::string, variant > > >::const_iterator it_begin = value.begin();
        std::vector<std::vector<std::map<std::string, variant > > >::const_iterator it_end = value.end();
        while ( it_begin != it_end ) {
            ret.append( "[" );
            std::vector<std::map<std::string, variant > >::const_iterator it_it_begin = ( *it_begin ).begin();
            std::vector<std::map<std::string, variant > >::const_iterator it_it_end = ( *it_begin ).end();
            while ( it_it_begin != it_it_end ) {
                ret.append( "[" );
                std::map<std::string, variant >::const_iterator it_map_begin = ( *it_it_begin ).begin();
                std::map<std::string, variant >::const_iterator it_map_end = ( *it_it_begin ).end();
                while ( it_map_begin != it_map_end ) {
                    std::pair<std::string, variant> par = ( *it_map_begin );
                    ret.append( PairSerializer<std::string, variant, JsonBraces::NO_BRACES>()
                                ( par.first, par.second, encoding | JsonEncoding::PAIR_AS_ASSOCIATIVE ) );
                    ++it_map_begin;
                }

                ret.append( "]" );
                ++it_it_begin;
            }


            ret.append( "]" );
            ++it_begin;
        }

        return ret;

    }

    inline json_serialized_type operator()( const std::vector< std::vector <dependency_info> >& value, JSON_ENCODING_FUNCARG ) const {

        json_serialized_type ret( "" );
        std::vector<std::vector<dependency_info> >::const_iterator it_begin = value.begin();
        std::vector<std::vector<dependency_info > >::const_iterator it_end = value.end();

        while ( it_begin != it_end ) {
            ret.append( "[" );
            std::vector<dependency_info>::const_iterator it_it_begin = ( *it_begin ).begin();
            std::vector<dependency_info>::const_iterator it_it_end = ( *it_begin ).end();
            while ( it_it_begin != it_it_end ) {
                ret.append( "[" );
                std::string worksheet_id = boost::lexical_cast<std::string>( it_it_begin->worksheet_id );
                std::string workbook_id  =  boost::lexical_cast<std::string>( it_it_begin->workbook_id );
                std::string application_id =    boost::lexical_cast<std::string>( it_it_begin->application_id );
                sheet_range coverage     =     it_it_begin->coverage;
                ret.append( worksheet_id + "," );
                ret.append( workbook_id + "," );
                ret.append( application_id + "," );
                ret.append( this->operator ()( coverage, encoding ) );
                ret.append( "]" );
                ++it_it_begin;
            }

            ret.append( "]" );
            ++it_begin;
        }
        return ret;
    }
};



#endif // _JSONSERIALIZER
