/**
 *  \file
 *  implementation of generic cell
 *
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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#undef ERROR
#undef ERROR_NOT_FOUND

#include <PaloSpreadsheetFuncs/GenericCell.h>

#include <wss/variant.hpp>
#include <wss/session.hpp>

#include <stdexcept> // for std::runtime_error
#include <boost/ptr_container/ptr_vector.hpp>
#include "palo_context.hpp"

using namespace Palo::SpreadsheetFuncs;
using namespace Palo::Types;

namespace Palo
{
    namespace Types
    {
        class DimensionElementInfoSimple;
        class DimensionElementInfoSimple;
        class ConsolidationElementInfo;
        typedef std::vector<DimensionElementInfo> DimensionElementInfoArray;
        typedef std::vector<DimensionElementInfoSimple> DimensionElementInfoSimpleArray;
        typedef std::vector<ConsolidationElementInfo> ConsolidationElementInfoArray;
        class SubsetResult;
    }
}

/*!
 * \brief
 * will be thrown in the palo_cell_adapter::adapter_cell_iterator
 * when trying to access elements beyond "end".
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class adapter_iterator_not_dereferenceable_exception
    : public std::runtime_error
{
public:
    adapter_iterator_not_dereferenceable_exception();
};

/*! \brief palo_cell_adapter class.
 *
 * Provides an interface to access and store values.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class palo_cell_adapter : public GenericCell
{
public:
    typedef boost::shared_ptr<jedox::palo::Server> ServerSPtr;

    palo_cell_adapter( session& s );

    palo_cell_adapter( session& s, variant& value, const bool is_retval = false, const size_t rows = 0, const size_t cols = 0 );

    palo_cell_adapter( const palo_cell_adapter& other );

    inline void set_subset_inside_nf() {
        m_subset_inside_nf = true;
    }

    /*! \brief Get the cells type.
     */
    Type getType();

    /*! \brief Argument not passed?
     *
     *  Check if the cell represents a function argument which
     *  has been omitted in the function call.
     */
    bool isMissing();

    /*! \brief Argument empty?
     *
     *  Check if the argument is empty, e.g. contains an empty string.
     */
    bool empty( bool allelements = true );

    /*! \brief Set the argument to empty.
     */
    GenericCell& setEmpty();

    /*! \brief Retrieve an array.
     *
     *  Arrays are one-dimensional.
     */
    Iterator getArray();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests. This function is required by GenericArgumentArray::fixConnection()
     */
    ServerSPtr getConnection( ConnectionPool& cp, std::string& database );

    /*! \brief Retrieve an argument.
    *
    *  What the name suggests. This function is required by GenericArgumentArray::fixConnection()
    */
    ServerSPtr getConnection( ConnectionPool& cp );

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    ElementList getElementList();

    /*
        virtual GenericCell& set( const std::string& s ) = 0;
        virtual std::string getString() = 0;
    */

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    std::string getString();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    long int getSLong();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    unsigned long int getULong();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    unsigned int getUInt();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    int getSInt();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    bool getBool();

    /*! \brief Retrieve an argument.
     *
     *  What the name suggests.
     */
    double getDouble();

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( ServerSPtr s );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( int i );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( unsigned int i );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( long int i );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( unsigned long int i );

    GenericCell& set( long double d );

#ifdef WIN64
    /*! \brief Set a value.
     *
     *  What the name suggests (this is required for Windows x64).
     */
    GenericCell& set( size_t n );
#endif

    ConsolidationElementArray getConsolidationElementArray();

    GenericCell& supressPadding();
    /*! \brief Set a value.
         *
         *  What the name suggests.
         */
    GenericCell& set( double d );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( const std::string& s );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( const char* s );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( bool b );

    /*! \brief Set a value.
     *
     *  What the name suggests.
     */
    GenericCell& set( const DimensionElementInfo& ei );

    /*! \brief Set an error value.
     *
     *  What the name suggests.
     */
    GenericCell& setError( const Palo::Types::ErrorInfo& error_info, bool SetErrorDesc = true );

    /*! \brief Set an empty value.
     *
     *  What the name suggests.
     */
    GenericCell& setNull();

    /*! \brief Set an array.
     *
     *  What the name suggests.
     */
    ArrayBuilder setArray( size_t length, bool value );
    GenericCell& set( const DimensionElementInfoSimple& ei );
    GenericCell& set( const ConsolidationElementInfo& ei );
    GenericCell& set( const DimensionElementInfoSimpleArray& ei );
    GenericCell& set( const ConsolidationElementInfoArray& ceia );
    GenericCell& set( const SubsetResults& srs );
    ArrayBuilder setMatrix();
    ArrayBuilder setMatrix( size_t rows, size_t cols );
    ArrayBuilder setMatrix( size_t rows, size_t cols, bool pad );

    /*! \brief Retrieve a matrix.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    virtual GenericCell::Iterator getMatrix( unsigned int& rows, unsigned int& cols );

    /*!
     * \brief
     * create a new palo_cell_adapter based on the current type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::auto_ptr<GenericCell> create() const;

    /*!
     * \brief
     * clone the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual std::auto_ptr<GenericCell> clone() const;

private:
    class AdapterArrayBuilder : public GenericArrayBuilderImpl
    {
    public:
        AdapterArrayBuilder( session& s, variant& value, size_t rows, size_t cols, size_t real_rows, size_t real_cols, bool pad_to_caller, size_t cols_to_set );
        ~AdapterArrayBuilder();
        /*! \brief "Instantiate" a GenericCell.
         *
         *  This function creates an instance of a class derived from GenericCell and
         *  returns a reference to it.
         */
        std::auto_ptr<GenericCell> createGenericCell();

        /*! \brief Append a GenericCell to the array.
         *
         *  Append the referenced class derived from GenericCell to the array.
         */
        virtual void append( GenericCell& v );

        /*! \brief Append a GenericCell to the array.
         *
         *  Append the referenced object of a class derived from GenericCell to the array.
         *  This function allows you to provide a key for the array entry.
         */
        virtual void append( const std::string key, GenericCell& v );

        virtual void transpose();

    private:
        variant& m_value;
        session& m_session;
        bool pad;
        size_t rows, cols, real_rows, real_cols, cols_to_set;
        bool is_retval;
    };
    /*! helper function for set() */
    static void setDimensionElementInfoSimple( GenericArrayBuilder& a, const DimensionElementInfoSimple& dis, unsigned int num_entries );

    /*! helper function for set() */
    static void setSubsetResult( GenericArrayBuilder& a, const SubsetResult& sr, unsigned int num_entries );

    /*! helper function for set() */
    static void setConsolidationElementInfo( GenericArrayBuilder& a, const ConsolidationElementInfo& cei, unsigned int num_entries );

    /*! helper function for set() */
    template<unsigned int max_entries, typename MultiColumn, typename Functor>
    GenericCell& set( const std::vector<MultiColumn>& mc, Functor setter );

    /*! helper function for set() */
    palo_cell_adapter::ArrayBuilder internal_setMatrix( size_t rows, size_t cols, bool pad );

    class adapter_cell_iterator : public GenericCellIteratorImpl
    {
    public:
        adapter_cell_iterator( session& s, variant& value );

        /*! \brief Dereference operator.
         *
         *  Retrieve a pointer to the GenericCell the iterator is currently pointing to.
         */
        GenericCell* operator ->();

        /*! \brief Increment operator (prefix)
         *
         *  Move one step forward (you have to assure that there are elements left!).
         */
        GenericCellIteratorImpl& operator ++();

        /*! \brief Release pointer.
         *
         *  Return a pointer to a GenericCell that remains valid after the iterator
         *  modification. You should call delete on the return value when you don't need it
         *  anymore.
         */
        GenericCell* release();

        /*! \brief End reached?
         */
        bool end() const;

        /*! \brief Minimal number of elements remaining.
         *
         *  Tell how many element are left at least.
         */
        size_t minRemaining() const;

    private:
        typedef boost::ptr_vector<palo_cell_adapter> PaloCellAdapterTable;
        PaloCellAdapterTable m_palo_cell_adapter_table;
        PaloCellAdapterTable::iterator m_current;
        session& m_session;
    };

private:
    std::auto_ptr<variant> m_value_ptr;
    variant& m_value;
    ServerSPtr m_server;
    session& m_session;
    static palo_context m_context;
    bool m_is_retval;
    /*!
     * \brief
     * coverage of the originator - given as rows and cols
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    size_t m_rows;
    size_t m_cols;
    bool m_dont_pad;
    bool m_subset_inside_nf;
};
