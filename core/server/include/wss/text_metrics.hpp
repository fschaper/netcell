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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <wss/i_text_metrics.hpp>
#include <wss/singleton.hpp>

/*!
 * \brief
 * text metrics.
 *
 * \author
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
class WSS_MODULE text_metrics
    : public singleton< text_metrics >
{
    FRIEND_CLASS singleton< text_metrics >;
public:
    typedef boost::shared_ptr< i_text_metrics > shared_engine_type;

    void register_engine( const shared_engine_type& text_metrics_engine );

    shared_engine_type&    engine();
private:
    text_metrics();
    ~text_metrics();
private:
    shared_engine_type        m_engine;
};

