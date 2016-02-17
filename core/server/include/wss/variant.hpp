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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/sparse_vector.hpp>
#include <wss/locale.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#ifdef _WIN32
#   pragma warning( push )
#   pragma warning( disable : 4267 )
#endif
#  include <boost/lexical_cast.hpp>
#  include <boost/shared_ptr.hpp>
#ifdef _WIN32
#   pragma warning( pop )
#endif
#   include <cassert>
#   include <string>
#   include <vector>
#   include <memory> // for std::auto_ptr
#   include <iostream>
#endif // HAS_PRECOMPILED_HEADER == 0

#ifdef _WIN32
# pragma warning ( disable : 4251 ) // ignore warnings about variant members having no dll-interface.
#endif

namespace spreadsheetml
{
    class CT_vt_value;
}

/*!
 * \brief
 * variant type.
 *
 * visual studio debugger visualizer.
 * copy into the [Visualizer] section of your autoexp.dat
 * file in your "...\Microsoft Visual Studio 8\Common7\Packages\Debugger"
 * for Visual Studio 2010: "...\Microsoft Visual Studio 10.0\Common7\Packages\Debugger"
 * directory.
 *
 * ---- &< -------- &< -------- &< -------- &< -------- &< ----
 *   variant{
 *   preview
 *   (
 *    #(
 *     #switch( (unsigned)$e.m_value_type )
 *     #case 0 ( #("EMPTY") )
 *     #case 1 ( #("STRING=", $e.m_string._Myptr) )
 *     #case 2 ( #("DOUBLE=", $e.m_double) )
 *     #case 3 ( #("BOOL=", (bool)$e.m_double) )
 *     #case 4
 *     (
 *      #(
 *       "ARRAY(WIDTH:", (unsigned)$c.m_double, ")=",
 *       #array
 *       (
 *        expr : ($c.m_array._Myptr->_Myfirst)[$i],
 *        size : $c.m_array._Myptr->_Mylast-$c.m_array._Myptr->_Myfirst
 *       )
 *      )
 *     )
 *     #case 5
 *     (
 *      #switch( (unsigned)$e.m_double )
 *      #case 1 ( #("ERROR=#NULL!") )
 *      #case 2 ( #("ERROR=#DIV/0!") )
 *      #case 3 ( #("ERROR=#VALUE!") )
 *      #case 4 ( #("ERROR=#REF!") )
 *      #case 5 ( #("ERROR=#NAME!") )
 *      #case 6 ( #("ERROR=#NUM!") )
 *      #case 7 ( #("ERROR=#N/A!") )
 *      #default ( #("ERROR=UNKNOWN") )
 *     )
 *     #default ( #("UNKNOWN") )
 *    )
 *   )
 *  }
 * ---- &< -------- &< -------- &< -------- &< -------- &< ----
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE variant
{
public:
    typedef sparse_vector<variant> sparse_array_type;
    typedef sparse_array_type variant_array_type;

    enum variant_type {
        type_empty
        , type_string
        , type_double
        , type_bool
        , type_array
        , type_error
    };

    enum error_type {
        dummy = 0
        , error_null
        , error_div_null
        , error_value
        , error_ref
        , error_name
        , error_num
        , error_n_a
    };

    /*!
     * \brief
     * constructor which initializes the variant with type_empty state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant();

    /*!
     * \brief
     * constructor which initializes the variant with type_numeric and the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( double d );

    /*!
     * \brief
     * constructor which initializes the variant with type_bool and the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( bool b );

    /*!
     * \brief
     * constructor which initializes the variant with type_string and the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( const char* s );

    /*!
     * \brief
     * constructor which initializes the variant with type_string and the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( const std::string& s );

    /*!
     * \brief
     * constructor which initializes the variant with type_string and
     * a shared_ptr to string data, thus getting ref semantics.
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    variant( boost::shared_ptr<std::string> s );

    /*!
     * \brief
     * constructor which initializes the variant with type_error and the passed error code.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( error_type error );

    /*!
     * \brief
     * constructor which created a variant of the passed variant type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( variant_type v_type );

    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( const variant& other );

    /*!
     * \brief
     * constructor which initializes the variant with type_array and
     * sets the column width of the variant.
     *
     * with the help of "column_width" we can treat the one dimensional
     * array as a two dimensional array with x,y coordinate.
     * you can retrieve the row dimension by calling:
     * row_count = my_varaint.array().size() / my_variant.column_width();
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant( sparse_array_type& array, unsigned int column_width = 1 );

    /*!
    * \brief
    * constructor which initializes the variant with type_array and
    * sets the column width of the variant.
    * uses ref semantics from the hared_ptr to array
    *
    * with the help of "column_width" we can treat the one dimensional
    * array as a two dimensional array with x,y coordinate.
    * you can retrieve the row dimension by calling:
    * row_count = my_varaint.array().size() / my_variant.column_width();
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    variant( boost::shared_ptr<sparse_array_type> array, unsigned int column_width = 1 );

    /*!
     * \brief
     * constructor taking const array as parameter.
     * see non-const ctor for details on how to be used
     *
     * \author
     * Radu Racariu <radu@yalos-solutions.com>
     */
    variant( const sparse_array_type& array, unsigned int column_width = 1 );

    /*!
     * \brief
     * swaps the guts of other with this
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void swap( variant& other );

    /*!
     * \brief
     * assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator =( const variant& rhs );

    /*!
     * \brief
     * returns the type of the variant.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant_type type() const;

    /*!
     * \brief
     * will return true in case the variant is of type_empty or
     * contains an empty string, empty array or is of type_numeric with a value of 0.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_of_empty_value() const;

    /*!
     * \brief
     * will return true in case the variant is of type_empty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_empty() const;

    /*!
     * \brief
     * will return true in case the variant is of type_boolean.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_boolean() const;

    /*!
     * \brief
     * will return true in case the variant is of type_double.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_double() const;

    /*!
     * \brief
     * will return true in case the variant is of type_error.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_error() const;

    /*!
     * \brief
     * will return true in case the variant is of type_array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_array() const;

    /*!
     * \brief
     * will return true in case the variant is of type_string.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_string() const;

    /*!
     * \brief
     * will return true in case the variant is of type_numeric.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_numeric() const;

    /*!
     * \brief
     * in case the variant is of string type will return the contained string.
     *
     * will throw variant_conversion_exception in case the variant is not of string type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& string() const;

    /*!
     * \brief
     * in case the variant is of numeric type will return the contained value.
     *
     * will throw variant_conversion_exception in case the variant is not of numeric, boolean or empty type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    double numeric() const;

    /*!
     * \brief
     * in case the variant is of boolean type will return the contained value.
     *
     * will throw variant_conversion_exception in case the variant is not of numeric, boolean or empty type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool boolean() const;

    /*!
     * \brief
     * in case the variant is of error type will return the contained error code.
     *
     * will throw variant_conversion_exception in case the variant is not of error type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    error_type error_code() const;

    /*!
     * \brief
     * in case the variant is of error type will associate a error message with the variant.
     *
     * will throw variant_conversion_exception in case the variant is not of error type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void error_message( const std::string& msg );

    /*!
     * \brief
     * get the error message if type is error and a message has been set.
     * All other cases will return an empty string
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    std::string error_message() const;

    /*!
     * \brief
     * in case the variant is of array type will return the mutable contained array.
     *
     * will throw variant_conversion_exception in case the variant is not of array type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_array_type& array();

    /*!
     * \brief
     * in case the variant is of array type will return the immutable contained array.
     *
     * will throw variant_conversion_exception in case the variant is not of array type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const sparse_array_type& array() const;

    /*!
     * \brief
     * will convert all types except arrays to string form.
     *
     * boolean values and error types will be converted with the help of the users locale.
     *
     * will throw variant_conversion_exception in case the variant is of array type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string as_string( const ::locale& l ) const;

    /*!
     * \brief
     * will convert all types except arrays and errors to double form.
     *
     * will throw variant_conversion_exception in case the variant is of array or error type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    double as_double() const;

    /*!
     * \brief
     * will convert all types except error variants to boolean form.
     *
     * for arrays if the array contains at least one element that evaluates to false will result in false.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool as_boolean( const ::locale& l ) const;

    /*!
     * \brief
     * for arrays will return the "width" of the array.
     *
     * with the help of "column_width" we can treat the one dimensional
     * array as a two dimensional array with x,y coordinate.
     * you can retrieve the row dimension by calling:
     * row_count = my_varaint.array().size() / my_variant.column_width();
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    unsigned int column_width() const;

    /*!
     * \brief
     * for array set the column width
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void column_width( unsigned int column_width );

#ifdef _DEBUG
    void dump() const;
#endif // _DEBUG

    /*!
     * \brief
     * comparison for equality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const variant& other ) const;

    /*!
     * \brief
     * comparison for equality. promotes empties
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    bool equals( const variant& other ) const;

    /*!
     * \brief
     * comparison for inequality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator !=( const variant& other ) const;

    /*!
     * \brief
     * comparison for inequality. promotes empties
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    bool nequals( const variant& other ) const;

    /*!
     * \brief
     * comparison for larger then.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator >( const variant& other ) const;

    /*!
     * \brief
     * comparison for smaller then.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <( const variant& other ) const;

    /*!
     * \brief
     * comparison for larger then or equal.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator >=( const variant& other ) const;

    /*!
     * \brief
     * comparison for smaller then or equal.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <=( const variant& other ) const;

    /*!
     * \brief
     * addition operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator +( const variant& other ) const;

    /*!
     * \brief
     * subtraction operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator -( const variant& other ) const;

    /*!
     * \brief
     * multiplication operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator *( const variant& other ) const;

    /*!
     * \brief
     * division operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator /( const variant& other ) const;

    /*!
     * \brief
     * modulo operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant operator %( const variant& other ) const;

    /*!
     * \brief
     * comparison operator.
     *
     * since this is a common comparison throughout the code
     * implemented to prevent implicit instantiation of an
     * variant of double type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( double rhs ) const;

    /*!
     * \brief
     * addition & assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator +=( const variant& other );

    /*!
     * \brief
     * addition & assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator -=( const variant& other );

    /*!
     * \brief
     * multiplication & assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator *=( const variant& other );

    /*!
     * \brief
     * division & assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator /=( const variant& other );

    /*!
     * \brief
     * modulo & assignment operator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant& operator %=( const variant& other );

    /*!
     * \brief
     * will perform comparison for equality that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant eq( const variant& rhs ) const;

    /*!
     * \brief
     * will do comparison for inequality that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant neq( const variant& rhs ) const;

    /*!
     * \brief
     * will perform comparison for "less or equal" that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant le( const variant& rhs ) const;

    /*!
     * \brief
     * will do comparison for "greater than or equal" that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant gte( const variant& rhs ) const;

    /*!
     * \brief
     * will perform comparison for "less than" that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant lt( const variant& rhs ) const;

    /*!
     * \brief
     * will perform comparison for "greater than" that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant gt( const variant& rhs ) const;

    /*!
     * \brief
     * will perform "addition" that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant add( const variant& rhs ) const;

    /*!
     * \brief
     * will perform "subtraction" that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant sub( const variant& rhs ) const;

    /*!
     * \brief
     * will perform "multiplication" that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant mul( const variant& rhs ) const;

    /*!
     * \brief
     * will perform "division" that works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant div( const variant& rhs ) const;

    /*!
     * \brief
     * will perform a "percentage" operation that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant percent( const variant& rhs ) const;

    /*!
     * \brief
     * will perform a "exponent" operation that also works on arrays.
     *
     * the result will be an array of MAX(this, rhs) size.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant exp( const variant& rhs ) const;

    //region Persistence

    /*!
     * \brief
     * deserialize from xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void deserialize( const spreadsheetml::CT_vt_value& data );

    /*!
     * \brief
     * serialize to xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void serialize( spreadsheetml::CT_vt_value& data ) const;
    // endregion Persistence

private:
    /*!
     * \brief
     * helper for array operations.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template< typename conversion_T, conversion_T callback>
    variant on_array( const variant& rhs, const variant& default_value = variant() ) const;

    /*!
     * \brief
     * special case for "power of" array operations.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    variant pow( const variant& rhs ) const;

    /*!
     * \brief
     * helper that converts to numeric value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void to_numeric();

    /*!
     * \brief
     * herlper class used to compare variants of different type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class arrayize;

private:
    variant_type m_value_type;
    double m_double;
    boost::shared_ptr<std::string> m_string;
    boost::shared_ptr<sparse_array_type> m_array;
};

/*!
 * \brief
 * swap operation for variant type.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline void swap( variant& a, variant& b )
{
    a.swap( b );
}

/*!
 * \brief
 * output stream operator.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
WSS_MODULE std::ostream& operator <<( std::ostream& os, const variant& v );
