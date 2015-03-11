/**
 *  \file
 *  Copyright (C) 2008 - 2009 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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

#include <wss/i_weak_dependency.hpp>
#include <wss/sheet_point.hpp>

/*!
 * \brief
 * defines a reference to an cell that will be
 * resolved on request.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
/*
class lazy_cell_reference
            : public i_lazy_reference
{
public:
    virtual reference_type type() const;

    virtual ~lazy_cell_reference();

    virtual shared_dependency_type lock() const;

    virtual void register_dependent( shared_dependency_type sd );

    virtual bool operator <( const i_lazy_reference& other ) const;

    const sheet_point& position() const;

    static shared_dependency_reference_type create( weak_worksheet_type wws, const sheet_point& sp );

private:
    lazy_cell_reference( weak_worksheet_type wws, const sheet_point& sp );

private:
    weak_dependency_type m_cell;
    weak_worksheet_type m_worksheet;
    sheet_point m_position;
};
*/

