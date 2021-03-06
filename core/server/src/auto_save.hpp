/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#pragma once

#include "wss/singleton.hpp"

class auto_save : public singleton< auto_save >
{
    friend class singleton< auto_save >;
public:
    bool start();
    bool stop();
    void set_interval( int sec );

private:
    auto_save();
    void wait_on_save();

    enum save_handler_state {
        SAVE_HANDLER_RUNNING
        , SAVE_HANDLER_SHUTTING_DOWN
        , SAVE_HANDLER_HALTED
    }                           m_state;
    int                         m_interval;
    boost::mutex                m_lock;
    boost::condition_variable   m_wait_for_shutdown;

    boost::thread*              m_worker;
};


