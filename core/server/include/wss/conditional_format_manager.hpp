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

#include <wss/define.hpp>
#include <wss/session.hpp>
#include <wss/free_formula.hpp>
#include <wss/sheet_point.hpp>
#include <wss/style_set.hpp>
#include <wss/friend.hpp>
#include <wss/worksheet.hpp>
#include <wss/flyweight_types.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <map>
#   include <stdexcept>
#   include <string>
#   include <memory>

#   include <boost/noncopyable.hpp>
#   include <boost/cstdint.hpp>
#   include <boost/scoped_ptr.hpp>
#   include <boost/ptr_container/ptr_map.hpp>
#   include <boost/thread/shared_mutex.hpp>
#   include <boost/enable_shared_from_this.hpp>
#   include <boost/optional.hpp>
#   include <boost/flyweight.hpp>
#endif

class set_conditional_format;
struct get_conditional_format;
typedef std::list<get_conditional_format> get_conditionalformat_list_type;

namespace cf
{
    typedef boost::optional<style_set_type> optional_style_set_type;
    typedef boost::optional<conditional_format_border_type> optional_border_type;

    typedef internal_flyweights::conditional_format_format_type format_type;
    typedef boost::optional<format_type> optional_format_type;
    class conditional_format_storage;
    class conditional_format_locked_storage;
}

class range;
class layout_coord;
class move_conditional_format_rank_command;

class WSS_MODULE conditional_format_manager : boost::noncopyable
{
    FRIEND_CLASS cf::conditional_format_locked_storage;
    FRIEND_CLASS move_conditional_format_rank_command;
    FRIEND_CLASS range;
    FRIEND_CLASS layout_coord;
    FRIEND_CLASS get_server_query_command;

    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    typedef cf::conditional_format_storage storage_type;
public:

    enum conditional_format_query_type {
        query_conditional_format_style = 1,
        query_conditional_format_format = 2,
        query_conditional_format_lock = 4,
        query_conditional_format_all = query_conditional_format_style | query_conditional_format_format | query_conditional_format_lock
    };


    /*!
    * \brief
    * constructs an new conditional_format_manager
    */
    conditional_format_manager( worksheet& ws );

    ~conditional_format_manager();


public:

    /*!
    * \brief
    * get the parent worksheet
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    worksheet& parent();

    /*!
    * \brief
    * add a conditional format rule
    *
    * \param s
    * session
    *
    * \param cf_format
    * the conditional format rule
    *
    * \param format
    * /TODO
    *
    * \param position
    * the position used when parsing formulas inside the rule
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void add( session& s, const set_conditional_format& cf_format, bool relative = true );

    /*!
    * \brief
    * update a conditional format rule
    *
    * \param s
    * session
    *
    * \param id
    * id of the conditional format rule to be updated
    *
    * \param cf_format
    * the conditional format rule
    *
    * \param format
    * /TODO
    *
    * \param position
    * the position used when parsing formulas inside the rule
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void update( session& s, const conditional_format_lookup_id_type id, const set_conditional_format& cf_format );

    /*!
    * \brief
    * removes a conditional format
    *
    *
    * \param s
    * session
    *
    * \param ranges
    * erase on these ranges only
    *
    * \param ids
    * erase these ids only
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void erase( session& s, const sheet_range::rectangles_type& ranges, const id_list_type& ids );

    /*!
      * \brief
      * erase all conditional formats in a given range
      *
      *
      * \param s
      * session
      *
      * \param range
      * erase on these range only
      *
      * \author
      * Frieder Hofmann <frieder.hofmann@jedox.com>
      */
    void erase( session& s, const sheet_range& range );

    /*!
     * \brief
     * get conditional formats
     *
     * \param s
     * session
     *
     * \param ranges
     * ranges to query on
     *
     * \return get_conditionalformat_list_type
     * all the conditional formats that are set on the ranges
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    get_conditionalformat_list_type get( session& s, const sheet_range::rectangles_type& ranges ) const;

    /*!
    * \brief
    * same as the one above but will return all conditional formats on this sheet!
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void get( get_conditionalformat_list_type& return_val, session& s, const bool solve_formulas = false ) const;

    optional_sheet_range_type used_range() const;

private:

    /*!
     * \brief
     * move
     *
     * \param s
     * session
     *
     * \param source
     * source range
     *
     * \param target
     * target range
     *
     *
     * \param target_ws
     * the target worksheet
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void move( session& s, const sheet_range& source, const sheet_point& target, const shared_worksheet_type& target_ws );

    /*!
    * \brief
    * copy
    *
    * \param s
    * session
    *
    * \param source
    * source range
    *
    * \param target
    * target range
    *
    *
    * \param target_ws
    * the target worksheet
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void copy( session& s, const sheet_range& source, const sheet_range& target, const shared_worksheet_type& target_ws, const bool use_copy_move = false );

    /*!
    * \brief
    * copy
    *
    * \param s
    * session
    *
    * \param id
    * id of the conditional format
    *
    * \param selected_region
    * the currently selected region
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void move_up( session& s, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region );

    /*!
    * \brief
    * copy
    *
    * \param s
    * session
    *
    * \param id
    * id of the conditional format
    *
    * \param selected_region
    * the currently selected region
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    void move_down( session& s, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region );

    /*!
     * \brief
     * match and get all the styles/formats set in this area
     *
     * \param s
     * session
     *
     * \param query_type
     * either all the information or just one of style/format
     *
     * \return format_style_border_vec_type
     * vector with one item for each sheet_point in the range
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    cf::cf_vec_type match( session& s, const sheet_range& range, const conditional_format_query_type query_type = query_conditional_format_all ) const;

    /*!
    * \brief
    * get_the storage
    *
    * \see conditional_format_locked_storage
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    cf::conditional_format_storage& get_store( lock_type& );

    /*!
    * \brief
    * get the parent worksheet
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    worksheet& parent( lock_type& );


private:
    /*!
     * \brief
     * mutex
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    mutable mutex_type m_mutex;

    /*!
     * \brief
     * storage of all conditional formats in this worksheet
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    mutable boost::scoped_ptr<cf::conditional_format_storage> m_storage;

    /*!
     * \brief
     * the parent worksheet that contains this manager
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    worksheet& m_parent_ws;
};
