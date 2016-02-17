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
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/algorithm/string.hpp>
#   include <boost/foreach.hpp>
#   include <sstream>
#   include <vector>
#   include <string>
#   include <map>
#endif

/*!
 * \brief
 * key/value information set.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class serializer_T, class unserializer_T>
class key_value_set
{
public:
    typedef typename ci_key_value_map_type::value_type pair_type;
    typedef typename ci_key_value_map_type::const_iterator const_iterator;
    typedef serializer_T serializer_type;
    typedef unserializer_T unserializer_type;
    typedef typename pair_type::first_type key_type;
    typedef typename pair_type::second_type value_type;

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    key_value_set();

    /*!
     * \brief
     * copy constructor used by the serializers.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    key_value_set( const ci_key_value_map_type& m );

    /*!
     * \brief
     * add a new key/value definition to the set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add( const std::string& key, const std::string& value );

    /*!
     * \brief
     * add a new key/value definition to the set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add( const key_type& key, const value_type& value );

    /*!
     * \brief
     * erases the entry with the passed key.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( const key_type& key );

    /*!
     * \brief
     * combines one key/value set with the other.
     *
     * \remarks
     * other will overwrite "this" in case of duplicate entries.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void combine( const key_value_set& other );

    /*!
     * \brief
     * clears all key/value pairs from the set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void clear();

    /*!
     * \brief
     * returns true if the key_value_set is empty.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool empty() const;

    /*!
     * \brief
     * begin iterator over the key/value-set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator begin() const;

    /*!
     * \brief
     * end iterator over the key/value-set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const_iterator end() const;

    /*!
     * \brief
     * takes an encoded string and returns an key/value-set.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static key_value_set unserialize( const std::string& s );

    /*!
     * \brief
     * encodes the key/value-set to an encoded string.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string serialize( const bool skip_empties = true ) const;

    /*!
     * \brief
     * swap the contained information with the passed object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void swap( key_value_set& other );

    /*!
    * \brief
    * compare with other for equality.
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    bool operator ==( const key_value_set& other ) const;

    /*!
    * \brief
    * compare with other for inequality.
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    bool operator !=( const key_value_set& other ) const;

    /*!
    * \brief
    * adds the keys of the right operand. will replace existing keys
    *
    * \author
    * Radu Ialovoi <ialovoi@yalos-solutions.com>
    */
    key_value_set& operator +=( const key_value_set& other );


    /*!
    * \brief
    * size
    *
    * \author
    * Radu Ialovoi <ialovoi@yalos-solutions.com>
    */
    const size_t size() const {
        return m_map.size();
    }

private:
    ci_key_value_map_type m_map;
};

#include <wss/key_value_set.ipp>
