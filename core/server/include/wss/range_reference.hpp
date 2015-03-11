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

#include <wss/dependency_node_reference.hpp>
#include <wss/i_dependency_reference.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/enable_shared_from_this.hpp>
# include <boost/noncopyable.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

class cell_manager;

/*!
 * \brief
 * worksheet range reference (like for A:A).
 *
 * the node holds the informations about existing cells in
 * a region and the observers of that region.
 * the destructor of range_reference will unregister the
 * observer from the dependency_manager and if there are no
 * more observers for a region the dependency manager will erase
 * the node.
 *
 * in case a region on the sheet gets erased (or better overwritten
 * due to move) the dependency manager will remove all nodes that
 * are covered by the erasure. the range_reference will then
 * be invalid and calls to operator ->() will fail
 * (leading to #REF! in formulas).
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE range_reference
    : public i_dependency_reference
    , public boost::enable_shared_from_this<range_reference>
    , boost::noncopyable
{
    template< class T, class A1, class A2, class A3 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const&, A3 const& );
public:
    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~range_reference();

    /*!
     * \brief
     * factory method.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_reference_type create( const shared_dependency_type& dependent, const sheet_range& r, const shared_dependency_node_reference_type& sld );

    /*!
     * \brief
     * return the reference type (will always be range_reference)
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual reference_type type() const;

    /*!
     * \brief
     * return the associated worksheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_worksheet_type worksheet() const;

    /*!
     * \brief
     * provides access to the contained reference.
     *
     * the reference might no longer be valid in case it was
     * destroyed during a move or erase operation.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class WSS_MODULE actual
        : boost::noncopyable
    {
    public:
        /*!
         * \brief
         * constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        actual( const shared_dependency_node_reference_type& sdn );

        /*!
         * \brief
         * copy constructor.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        actual( const actual& other );

        /*!
         * \brief
         * returns true in case the reference still exits.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        bool is_valid() const;

        /*!
         * \brief
         * returns the associated worksheet.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        weak_worksheet_type worksheet() const;

        /*!
         * \brief
         * sets the associated worksheet.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        void worksheet( const weak_worksheet_type& ws );

        /*!
         * \brief
         * returns the position on the sheet.
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        sheet_range position() const;

        /*!
         * \brief
         * provides direct access to the reference
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        locked_dependency_set_type* operator ->();

        /*!
         * \brief
         * provides direct access to the reference
         *
         * \author
         * Florian Schaper <florian.schaper@jedox.com>
         */
        locked_dependency_set_type& operator *();

    private:
        shared_dependency_node_reference_type m_precedents;
    };

    /*!
     * \brief
     * create a actualize object to access the reference.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    actual actualize() const;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_reference( const shared_dependency_type& dependent, const sheet_range& r, const shared_dependency_node_reference_type& sld );

    /*!
     * \brief
     * range references can not be copied.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_reference( const range_reference& );

    /*!
     * \brief
     * range references can not be copied.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_reference& operator =( const range_reference& );

private:
    weak_dependency_node_reference_type m_precedents;
    weak_dependency_type m_dependent;

#if defined(_DEBUG)
    // the original position where the reference was created. before
    // any move operation was performed!
    sheet_range m_debug_position;
#endif // _DEBUG
};

inline range_reference& range_reference_cast( const shared_reference_type& srr )
{
    assert( "reference is not of range type!" && srr->type() == i_dependency_reference::range_reference );
    return *boost::shared_static_cast<range_reference>( srr ).get();
}
