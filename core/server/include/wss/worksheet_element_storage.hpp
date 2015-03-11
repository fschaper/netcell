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
#include <wss/worksheet_element_exception.hpp>
#include <wss/i_named_formula_manager.hpp>
#include <wss/worksheet_element.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <string>
#   include <map>
#   include <vector>
#   include <boost/uuid/uuid.hpp>
# include <boost/noncopyable.hpp>
#   include <boost/thread/mutex.hpp>
#endif

class session;
class worksheet;
class workbook;

class WSS_MODULE worksheet_element_storage
    : boost::noncopyable
{
    FRIEND_CLASS worksheet_element;
    FRIEND_CLASS worksheet;
    FRIEND_CLASS workbook;

    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    typedef map_to_use<ws_elem_id_type, shared_worksheet_element_type>::type  container_type;

    typedef std::list<shared_worksheet_element_type>  list_type;

    typedef container_type::iterator iterator;
    typedef container_type::const_iterator const_iterator;

public:
    typedef worksheet_element::key_vec_type key_vec_type;
    typedef worksheet_element::key_value_vector_type key_value_vector_type;
    typedef worksheet_element::key_value_vector_vector_type key_value_vector_vector_type;
    typedef std::vector< std::string > id_vec_type;
    typedef std::list<shared_worksheet_element_type> insertion_order_list_type;
    typedef std::vector<std::string> element_name_vector_type;

    typedef container_type worksheet_element_vec_type;

    typedef std::set<ws_elem_id_type> changed_elements_list_type;
    typedef std::map<ws_elem_id_type, worksheet_element::change_list_type> changed_keys_list_type;
    typedef std::map<ws_elem_id_type, worksheet_element::key_value_vector_type> changed_key_values_list_type;

    ~worksheet_element_storage();

    /*!
    * \brief
    * delete worksheet element with specified
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void delete_worksheet_element( session& s, const std::string& uuid );
    void delete_worksheet_element( session& s, const ws_elem_id_type& uuid );

    /*!
    * \brief
    * delete worksheet elements with ids specified by list
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void delete_worksheet_elements( session& s, const element_name_vector_type& list );

    /*!
    * \brief
    * get worksheet element with id uuid
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    shared_worksheet_element_type get_worksheet_element( session& /* s */, const std::string& uuid ) const;

    /*!
    * \brief
    * get worksheet elements filtered
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    key_value_vector_vector_type get_worksheet_elements_filtered( session& s, const id_vec_type& elem_ids = id_vec_type(), const key_vec_type& keys = key_vec_type(), const key_value_vector_type& vals = key_value_vector_type() ) const;

    /*!
    * \brief
    * set worksheet elements filtered
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void set_worksheet_elements_filtered( session& s,  const id_vec_type& elem_id_vec,  const key_value_vector_vector_type& vals  );

    /*!
     * \brief
     * list of worksheet elements
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    list_type list_all_elements() const;

private:

    /*!
    * \brief
    * copy all worksheet elements to target_sheet
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void copy_to_sheet( session& s, const shared_worksheet_type& target_sheet ) const;

    /*!
    * \brief
    * constructor
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    worksheet_element_storage();

    /*!
    * \brief
    * add a worksheet element
    *
    * \note this is private now, use worksheet_element_storage::create to get a worksheet_element
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void add_worksheet_element( shared_worksheet_element_type e );

    /*!
    * \brief
    * next functions are internally used only
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    inline void delete_worksheet_element( lock_type& lock, session& /* s */, const ws_elem_id_type& uuid );
    inline iterator find( lock_type& lock, const std::string& uuid );

    inline const_iterator find( lock_type& lock, const std::string& uuid ) const;

    inline iterator find( lock_type& , const ws_elem_id_type& uuid );

    inline const_iterator find( lock_type& , const ws_elem_id_type& uuid ) const;

    void set_values_filter( lock_type& lock, session& s, const id_vec_type& elem_id_vec, const key_value_vector_vector_type& vals );

private:
    mutable mutex_type m_mutex;
    mutable mutex_type m_token_mutex;
    container_type m_container;
    //carefull with this list as it might keep the element alive!
    insertion_order_list_type m_insert_order;
    token_id_type m_counter;
};

