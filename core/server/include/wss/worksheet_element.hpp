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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/type.hpp>
#include <wss/define.hpp>
#include <wss/variant.hpp>
#include <wss/free_formula.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <string>
#   include <utility>
#   include <vector>
#   include <map>
#endif // HAS_PRECOMPILED_HEADER == 0

class worksheet_element_storage;
namespace spreadsheetml
{
    class CT_worksheet_element;
}

class WSS_MODULE worksheet_element
    : boost::noncopyable
{
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
    template< class T, class A1 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const& );

    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );

    friend class worksheet_element_storage;
public:
    typedef std::string key_type;
    typedef std::vector< key_type> key_vec_type;
    typedef variant value_type;
    typedef std::pair< key_type, value_type > key_value_type;
    typedef std::vector< key_value_type > key_value_vector_type;
    typedef std::vector< key_value_vector_type > key_value_vector_vector_type;

    typedef std::set<key_type> change_list_type;

public:
    ~worksheet_element();

    /*!
    * \brief
    * create a worksheet element with scope worksheet
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    static shared_worksheet_element_type create( const shared_worksheet_type& ws );
    static shared_worksheet_element_type create( const shared_worksheet_type& ws, const uuid_type& id );

    /*!
    * \brief
    * create a worksheet element with scope workbook
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    static shared_worksheet_element_type create( const shared_workbook_type& wb );
    static shared_worksheet_element_type create( const shared_workbook_type& wb, const uuid_type& id );

    inline const ws_elem_id_type uuid() const {
        return m_id;
    }
    /*!
    * \brief
    * get a property
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    key_value_type property( session& s, const key_type& k  ) ;

    /*!
    * \brief
    * set a property
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void property( session& s, const key_value_type& k );

    /*!
    * \brief
    * get properties
    *
    * \param s
    * session
    *
    * \param keys
    * vector containing the keys to return - if empty, return all
    *
    * \param vals
    * filter, so that there will only be a vector returned if all key value pairs specified in vals match with this
    * worksheet element
    *
    * \return if everything matches, a key value vector with all the keys specified in variable keys, if not, an empty vector!
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    key_value_vector_type properties( session& s, const key_vec_type& keys, const key_value_vector_type& vals );

    /*!
    * \brief
    * set properties
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void properties( session& s, const key_value_vector_type& vals );

    /*!
    * \brief
    * set type
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void type( const std::string& t );

    /*!
    * \brief
    * get type
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    const std::string& type() const;

    /*!
    * \brief
    * get the scope ( will return either "ws" or "wb")
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    const std::string& scope() const;

    /*!
    * \brief
    * check if a formula has been set
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    bool has_nf() const;

    /*!
    * \brief
    * check if a location formula has been set
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    bool has_location_nf() const;

    /*!
    * \brief
    * get value of the formula attached
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    variant get_nf_value( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    /*!
    * \brief
    * check if the formula attached has been flagged dirty
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    const bool is_dirty( session& s, const sheet_point& position = sheet_point( 0, 0 ) ) const;

    /*!
    * \brief
    * check if the formula attached has been flagged moved
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    const bool has_moved( session& s ) const;

    // region Persistence

    /*!
     * \brief
     * deserialize from xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void deserialize( session& s, const spreadsheetml::CT_worksheet_element& data );

    /*!
     * \brief
     * serialize to xml persistence.
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void serialize( session& s, spreadsheetml::CT_worksheet_element& data ) const ;

    // endregion Persistence
private:

    //special setter for copying
    struct copied_ws_element {};
    void properties( session& s, const key_value_vector_type& vals, const copied_ws_element& );


    /*!
    * \brief
    * constructors are all private, use worksheet_element::create to get one
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    worksheet_element( const shared_worksheet_type& ws );
    //TODO the next one will vanish in the future
    worksheet_element( const shared_worksheet_type& ws, const uuid_type& id );

    worksheet_element( const shared_workbook_type& wb );
    //TODO the next one will vanish in the future
    worksheet_element( const shared_workbook_type& wb, const uuid_type& id );

    worksheet_element( const worksheet_element& );
    struct worksheet_element_impl;
    boost::scoped_ptr<worksheet_element_impl> m_impl;

    /*!
    * \brief
    * keep a reference to the store
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    mutable mutex_type m_mutex;
    worksheet_element_storage& m_store;
    const ws_elem_id_type m_id;
};
