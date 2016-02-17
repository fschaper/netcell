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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#ifndef _SNAPSHOTMANAGER
#   define _SNAPSHOTMANAGER

// ui_backend
#include "JSONSerializer.hpp"


class SnapshotManager
    : public threadsafe_singleton<SnapshotManager>
{
    typedef boost::mutex mutex_t;
    typedef mutex_t::scoped_lock lock_t;
    mutable mutex_t m_mutex;
    mutable mutex_t m_wait_mutex;

    FRIEND_CLASS threadsafe_singleton<SnapshotManager>;

public:
    class Snapshot
    {
    public:
        Snapshot ( const sheet_range&, const unsigned long, const variant&, const unsigned short, const sheet_layout_trait::sparse_value_range_type&, const sheet_layout_trait::sparse_value_range_type&,
                   const sheet_point&, const std::string& );

        sheet_range coords;
        unsigned long property_set;
        variant values;

        unsigned short dimension_set;
        sheet_layout_trait::sparse_value_range_type col_widths, row_heights;

        sheet_point used_range;

        std::string uid;
    };

    typedef std::auto_ptr<Snapshot> snapshot_auto_type;

    class DimensionTypes
    {
    public:
        enum Type {
            NONE = 0u
            , COLS = 1u
            , ROWS = 2u
            , BOTH = 3u
        };
    };

    snapshot_auto_type make_snapshot ( session&, const sheet_range&, const unsigned long, const unsigned short ) const;
    const std::string save_snapshot ( const std::string&, snapshot_auto_type, const unsigned short, const std::string& );
    snapshot_auto_type get_snapshot ( const std::string&, const std::string& );

    void remove_snapshots ( const std::string& );

    const std::string diff_snapshots ( session&, const std::string&, const std::string& );
    const std::string diff_snapshots ( session&, const std::string&, const std::string&, const std::string& );

    void diff_values ( session&, std::stringstream&, const sheet_range&, const unsigned long, const variant&, const variant& ) const;
    void diff_dimensions ( std::stringstream&, const DimensionTypes::Type, const sheet_layout_trait::sparse_value_range_type&, const sheet_layout_trait::sparse_value_range_type& ) const;

    void gc_startup ();
    bool gc_shutdown ();

    bool gc_is_running () const;
    bool gc_is_shutting_down () const;
    bool gc_is_halted () const;

    void gc_set_interval ( const unsigned );

private:
    void gc_run ();

    SnapshotManager ();

    class State
    {
    public:
        enum Type {
            RUNNING
            , SHUTTING_DOWN
            , HALTED
        };
    };

    typedef std::pair<std::string, unsigned short> snapshot_uid_ttl_pair_t;
    typedef std::list<snapshot_uid_ttl_pair_t> snapshots_list_t;
    typedef std::map<std::string, Snapshot*> snapshots_map_t;
    typedef std::pair<snapshots_list_t, snapshots_map_t> snapshots_session_storage_t;
    typedef std::map<std::string, snapshots_session_storage_t> snapshots_storage_t;


    boost::condition_variable m_wait_condvar;

    State::Type m_gc_state;

    unsigned m_gc_interval;

    JSONSerializer m_json_serializer;
    snapshots_storage_t m_snapshots_storage;
};


#endif // _SNAPSHOTMANAGER
