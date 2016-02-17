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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/iterator/iterator_facade.hpp>
#   include <boost/optional.hpp>
#   include <boost/assign.hpp>
#   include <boost/bind.hpp>
#   include <algorithm>
#   include <stdexcept>
#   include <vector>
#   include <map>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * sparse vector implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class element_T>
class sparse_vector
{
public:
    typedef sparse_vector<element_T> self_type;
    typedef element_T value_type;
    typedef const value_type& const_reference_type;
    typedef value_type& reference_type;
    typedef std::size_t size_type;
    typedef std::map<size_type, value_type> mapping_type;
    typedef std::vector<element_T> native_vector_type;

    /*!
     * \brief
     * proxy class to provide on demand assignment
     * of values to the sparse_vector.
     *
     * we can not provide a direct reference to mutable elements
     * in the sparse vector because depending on the value we want
     * to set, we either need to add the new value to the underlaying
     * map (in case it's non-default) or, in case the new value is of
     * default value, erase it from it's old position (in case it was
     * of non-default value before).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class sparse_element
    {
    public:
        /*!
         * \brief
         * constructor.
         *
         * constructs a proxy-element that simulates a reference to a
         * vector-element at an defined index.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        sparse_element( sparse_vector<element_T>& v, size_type index )
            : m_vector( v )
            , m_index( index ) {}

        /*!
         * \brief
         * copy constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        sparse_element( const sparse_element& other )
            : m_vector( other.m_vector )
            , m_index( other.m_index ) {}

        /*!
         * \brief
         * returns a const reference to the sparse vectors value type.
         *
         * will return either a const reference to the vectors default
         * value or to the underlaying map in case the requested position
         * is of non-default value.
         *
         * \see
         * const_reference_type sparse_vector<element_T>::operator[]( size_type index ) const
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        operator const_reference_type() const {
            return const_cast<const sparse_vector<element_T>& >( m_vector )[ m_index ];
        }

        /*!
         * \brief
         * assign the passed value to the sparse_vector at the position the
         * proxy object was initialized with.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void operator =( const_reference_type v ) {
            m_vector.set( m_index, v );
        }

        /*!
         * \brief
         * comparison of the the value type with the element at vector position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool operator ==( const element_T& other ) const {
            return other == const_cast<const sparse_vector<element_T>& >( m_vector )[ m_index ];
        }

        /*!
         * \brief
         * comparison of the the value type with the element at vector position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool operator !=( const element_T& other ) const {
            return !( ( *this ) == other );
        }

        /*!
         * \brief
         * comparison of the the value type with the element at vector position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool operator <( const element_T& other ) const {
            return const_cast<const sparse_vector<element_T>& >( m_vector )[ m_index ] < other;
        }

        /*!
         * \brief
         * comparison of the the value type with the element at vector position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool operator >( const element_T& other ) const {
            return const_cast<const sparse_vector<element_T>& >( m_vector )[ m_index ] > other;
        }

        /*!
         * \brief
         * swap an element with another.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void swap( sparse_element& other ) {
            // (fschaper) in case we are dealing with the same vector that means
            // we have the same default value making it safe to directly access
            // and modify the underlaying map.
            if ( &m_vector == &other.m_vector ) {
                typename mapping_type::iterator this_it( m_vector.m_mapping.find( m_index ) );
                typename mapping_type::iterator other_it( other.m_vector.m_mapping.find( other.m_index ) );
                if ( this_it != m_vector.m_mapping.end() && other_it != other.m_vector.m_mapping.end() ) {
                    // the keys stay the same, only the value changes.
                    std::swap( this_it->second, other_it->second );
                    return;
                }
            }
            // (fschaper) we are handling (potentially) different default/non-default values
            // perform a regular insert.
            value_type tmp( *this );
            *this = other;
            other = tmp;
        }

    private:
        sparse_element& operator =( const sparse_element& other ) {
            m_index = other.m_index;
            return *this;
        }

    private:
        sparse_vector<element_T>& m_vector;
        size_type m_index;
    };

    /*!
     * \brief
     * sparse iterator.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class trait_T>
    class sparse_iterator
        : public boost::iterator_facade<sparse_iterator<trait_T>, typename trait_T::value_type, boost::forward_traversal_tag, typename trait_T::dereference_type >
    {
    public:
        /*!
         * \brief
         * constructor.
         *
         * empty, uninitialized iterator that can signify "end".
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        sparse_iterator()
            : m_vector()
            , m_index( 0 ) {}

        /*!
         * \brief
         * constructor.
         *
         * iterator that points to index for the passed vector.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        sparse_iterator( boost::optional<typename trait_T::container_type&> v, size_type index_offset = 0 )
            : m_vector( v )
            , m_index( index_offset ) {}

        /*!
         * \brief
         * copy constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template <class other_trait_T>
        sparse_iterator( const sparse_iterator<other_trait_T>& other )
            : m_vector( other.m_vector )
            , m_index( other.m_index ) {}

    private:
        friend class boost::iterator_core_access;
        template <class> friend class sparse_iterator;

        /*!
         * \brief
         * increment the iterator.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void increment() {
            ++m_index;
        }

        /*!
         * \brief
         * compare iterators for equality.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template<class other_trait_T>
        bool equal( const sparse_iterator<other_trait_T>& other ) const {
            // two iterator positions are equal in case:
            if ( other.m_vector && m_vector ) {
                // both iterators point to the same object and have the same index
                // position.
                return &( *other.m_vector ) == &( *m_vector ) && other.m_index == m_index;
            } else {
                // both iterators have no vector assigned and have the same index.
                // f.ex. to compare two default constructed iterators.
                return !other.m_vector && !m_vector && other.m_index == m_index;
            }
        }

        /*!
         * \brief
         * dereferences an element at the current index position.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        typename trait_T::dereference_type dereference() const {
            return ( *m_vector )[ m_index ];
        }

        boost::optional<typename trait_T::container_type&> m_vector;
        size_type m_index;
    };

    typedef sparse_element proxy_type;

    /*!
     * \brief
     * trait used for const iterators.
     *
     * const iterators may directly return references to the
     * elements of the sparse vector since they are immutable.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct const_iterator_trait {
        typedef const self_type container_type;
        typedef const element_T& dereference_type;
        typedef const element_T value_type;
    };

    /*!
     * \brief
     * trait used for mutable iterators.
     *
     * since the value pointed to by the iterator can be changed
     * we return a proxy object that takes care of the book-keeping
     * involved. in case we want to change a entry from default-value to
     * non default - an insertion into the underlaying map need be performed.
     * in case we change from non-default to default value we need to erase
     * the old value from its former map position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct iterator_trait {
        typedef self_type container_type;
        typedef proxy_type dereference_type;
        typedef proxy_type value_type;
    };

    typedef sparse_iterator<const_iterator_trait> const_iterator;
    typedef sparse_iterator<iterator_trait> iterator;

public:
    /*!
     * \brief
     * default constructor.
     *
     * constructs an empty sparse_vector with a optionally passed default value.
     * in case no default value was passed the default value will be default-initialized.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_vector(
        const_reference_type default_value = value_type() )
        : m_tail_index( 0 )
        , m_default( default_value ) {}

    /*!
     * \brief
     * constructs a sparse_vector of size 'n' with optionally passed default_value.
     * in case no default value was passed the default value will be default-initialized.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_vector( size_type n, const_reference_type default_value = value_type() )
        : m_tail_index( n )
        , m_default( default_value ) {}

    /*!
     * \brief
     * constructs a sparse vector and initializes it with the values taken from a native STL
     * vector and an optionally passed default value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    sparse_vector( const native_vector_type& v, const_reference_type default_value = value_type() )
        : m_tail_index( 0 )
        , m_default( default_value ) {
        for ( typename native_vector_type::const_iterator it = v.begin(); it != v.end(); ++it ) {
            push_back( *it );
        }
    }

    /*!
    * \brief
    * constructs a sparse vector and initializes it with the values taken from m
    * and an optionally passed default value.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    sparse_vector( const mapping_type& m, size_type n, const_reference_type default_value = value_type() )
        :  m_mapping( m )
        , m_tail_index( n )
        , m_default( default_value ) {
    }

    /*!
     * \brief
     * provided only to conform to the STL vector interface.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void reserve( size_type /*new_size*/ ) {
        // intentionally does nothing!
    }

    /*!
     * \brief
     * add an element to the end of the sparse_vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void push_back( const_reference_type v ) {
        // (fschaper) in case the element to be added is of 'default' value
        // we only increase the size of the vector. otherwise we
        // have to add the value to the underlaying map at index
        // position.
        if ( v != m_default ) {
            m_mapping[ m_tail_index ] = v;
        }
        ++m_tail_index;
    }

    /*!
     * \brief
     * erase all elements from the vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void clear() {
        // (fschaper) since the sparse vector is all about memory
        // we forcefully clean the underlaying map as well.
        mapping_type().swap( m_mapping );
        m_tail_index = 0;
    }

    /*!
     * \brief
     * returns true in case the sparse_vector is empty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool empty() const {
        return size() == 0 && m_mapping.empty();
    }

    /*!
     * \brief
     * returns the number of elements contained.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type size() const {
        return m_tail_index;
    }

    /*!
     * \brief
     * returns the number of elements that are of default value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type default_count() const {
        return m_tail_index - m_mapping.size();
    }

    /*!
     * \brief
     * swaps the guts with another const sparse vector of the same type.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void swap( const self_type& other ) {
        swap( const_cast<self_type&>( other ) );
    }

    /*!
    * \brief
    * swaps the guts with another sparse vector of the same type.
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    void swap( self_type& other ) {
        other.m_mapping.swap( m_mapping );
        std::swap( other.m_tail_index, m_tail_index );
        std::swap( other.m_default, m_default );
    }

    /*!
     * \brief
     * sets an element at position to the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void set( size_type index, const_reference_type v ) {
        if ( v != m_default ) {
            // (fschaper) in case the passed element is of non-default value
            // we simply add it to the map at the requested position.
            m_mapping[ index ] = v;
        } else {
            // (fschaper) the element is of default value. erase any existing
            // value in the non-default map.
            m_mapping.erase( index );
        }
        // (fschaper) in case the requested index was larger than our
        // current tail we have to adapt the size.
        if ( index >= m_tail_index ) {
            m_tail_index = index + 1;
        } else if ( size() == 0 ) {
            m_tail_index = 1;
        }
    }

    /*!
     * \brief
     * resized the sparse vector to 'size' with the passed value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void resize( size_type size, boost::optional<value_type> resize_value = boost::optional<value_type>() ) {
        if ( size < m_tail_index ) {
            // (fschaper) we have to reduce the size of the vector. erase all elements from the non-default-map
            // that are outside our new bounds.
            m_mapping.erase( m_mapping.lower_bound( size ), m_mapping.end() );
        } else if ( resize_value && ( *resize_value ) != m_default ) {
            // (fschaper) we have to increase the size of the vector and the element we have to fill
            // up the newly formed space is of non-default value. insert piece by piece.
            for ( typename mapping_type::size_type i = m_tail_index; i < size; ++i ) {
                m_mapping.insert( typename mapping_type::value_type( i, *resize_value ) );
            }
        }
        // (fschaper) set the new size of the vector.
        m_tail_index = size;
    }

    /*!
     * \brief
     * return a const reference to a sparse vector element.
     *
     * this is the fastest method to address elements in the vector since we
     * return direct references here and no proxy object is needed since the
     * element is immutable.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_reference_type operator[]( size_type index ) const {
        if ( index >= m_tail_index ) {
            throw std::out_of_range( "sparse vector index out of range!" );
        }

        typename mapping_type::const_iterator it( m_mapping.find( index ) );
        if ( it != m_mapping.end() ) {
            // (fschaper) the index position is of non-default value, return a direct
            // reference the to underlaying map, which is ok, since the reference is
            // const.
            return it->second;
        }
        // (fschaper) the position is of default value. we return our stub.
        // a real stl vector has a unique memory address for every element contained but
        // we return the same address for every default value. This will fail if your
        // implementation requires unique memory addresses.
        return m_default;
    }

    /*!
     * \brief
     * returns a proxy object to the vector at index position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    proxy_type operator[]( size_type index ) {
        if ( index >= m_tail_index ) {
            throw std::out_of_range( "sparse vector index out of range!" );
        }
        // (fschaper) see the explanation of what the proxy_type does at it's
        // class definition above.
        return proxy_type( *this, index );
    }

    /*!
     * \brief
     * provides direct read-only access to the underlaying non-default map.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const mapping_type& direct() const {
        return m_mapping;
    }

    /*!
     * \brief
     * will create an actual element in memory for every default value.
     *
     * this actually defeats pretty much the purpose of the sparse vector.
     * it might still be useful in rare occasions.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void fill_to_size() {
        for ( typename mapping_type::size_type i = 0; i < m_tail_index; ++i ) {
            // (fschaper) the insert will do actually nothing in case a value exists at the position
            // we are accessing that way existing values that may exist will not be overwritten.
            m_mapping.insert( typename mapping_type::value_type( i, default_value() ) );
        }
    }

    /*!
     * \brief
     * shift num_idxs to the right starting at index
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void shift( size_type index, const int num_idxs ) {
        typename mapping_type::iterator idx_it( m_mapping.lower_bound( index ) );
        typename mapping_type::const_iterator end_it( m_mapping.end() );
        if ( idx_it == end_it ) {
            return;
        }

        mapping_type tmp_map( m_mapping.begin(), idx_it );

        while ( idx_it != end_it && idx_it->first + num_idxs < index ) {
            ++idx_it;
        }

        for ( ; idx_it != end_it; ++idx_it ) {
            if ( static_cast< int >( idx_it->first ) + static_cast<int>( num_idxs ) >= static_cast<int>( index ) ) {
                tmp_map[ idx_it->first + num_idxs ] = idx_it->second;
            }
        }
        m_mapping.swap( tmp_map );
    }

    /*!
     * \brief
     * the default value of the sparse_vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const value_type& default_value() const {
        return m_default;
    }

    /*!
     * \brief
     * const iterator to the the beginning of the sparse vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator begin() const {
        return const_iterator( *this );
    }

    /*!
     * \brief
     * const iterator to the end of the sparse vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator end() const {
        return const_iterator( *this, size() );
    }

    /*!
     * \brief
     * iterator to the beginning of the sparse vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    iterator begin() {
        return iterator( *this );
    }

    /*!
     * \brief
     * iterator to the end of the sparse vector.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    iterator end() {
        return iterator( *this, size() );
    }

    /*!
     * \brief
     * compares two vectors for equality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const self_type& other ) const {
        if ( other.m_tail_index != m_tail_index ) {
            return false;
        }

        const bool is_other_sparse = other.direct().size() != other.m_tail_index;
        const bool is_this_sparse = direct().size() != m_tail_index;

        if ( ( !is_other_sparse && !is_this_sparse ) || ( other.m_default == m_default ) ) {
            return other.direct() == direct();
        } else {
            // TODO: we need only to compare the two maps and
            // compare the default value for any missing element.
            return std::equal( begin(), end(), other.begin() );
        }
    }

    /*!
     * \brief
     * compares two vectors for inequality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator !=( const self_type& other ) const {
        return !( ( *this ) == other );
    }

private:
    mapping_type m_mapping;
    typename mapping_type::size_type m_tail_index;
    value_type m_default;
};

namespace std
{
    /*!
     * \brief
     * std::swap specialization that makes use of sparse_element's
     * swap member function.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<class param_T>
    void swap( typename sparse_vector<param_T>::sparse_element& e1, typename sparse_vector<param_T>::sparse_element& e2 )
    {
        e1.swap( e2 );
    }
}

namespace boost
{
    namespace assign
    {
        /*!
         * \brief
         * sparse_vector support for boost::assign
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        template< class element_T, class value_T >
        inline list_inserter< assign_detail::call_push_back< sparse_vector<element_T> >, value_T >
        operator+=( sparse_vector<element_T>& c, value_T v )
        {
            return make_list_inserter( assign_detail::call_push_back< sparse_vector<element_T> >( c ) )( v );
        }
    }
}



