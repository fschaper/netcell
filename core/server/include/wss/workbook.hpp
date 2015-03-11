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

#include <wss/identifiable_object.hpp>
#include <wss/loadable_object.hpp>
#include <wss/object_container.hpp>
#include <wss/variable_map.hpp>
#include <wss/worksheet.hpp>


#if defined( WIN32 )
# pragma warning ( disable : 4251 4275 ) // disable "needs to have dll-interface" warning
#endif // WIN32

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <string>
# include <boost/noncopyable.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/integer.hpp>
#endif

class worksheet_element_storage;
class i_named_formula_manager;

namespace spreadsheetml
{
    class CT_extended_data;
}

/*!
 * \brief
 * Workbook representation.
 *
 * \see
 * server | application | worksheet
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE workbook
    : public identifiable_object
    , public object_container<workbook, worksheet>
    , public boost::enable_shared_from_this<workbook>
    , public loadable_object
{
    friend class application;
    friend class worksheet_element;
    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );
public:
    /*!
     * \brief
     * event handler that will be called for all workbooks upon destruction
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static boost::signal<void( const workbook& )> on_global_workbook_delete;

    /*!
     * \brief
     * event handler that will be called for all workbooks on save
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static boost::signal<void( const workbook& )> on_global_workbook_save;

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~workbook();

    /*!
     * \brief
     * return the application object holding the workbook
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_application_type parent() const;

    /*!
     * \brief
     * sets the workbook as selected in the passed state object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void select( selection_state& s );

    /*!
     * \brief
     * get the variable manager
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    variable_map& variable();

    /*!
     * \brief
     * list all the variables
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    variable_name_list_type variable_list();

    /*!
     * \brief
     * retreive a weak pointer of the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    weak_workbook_type weak_pointer() const;

    /*!
     * \brief
     * get the named_formula_manager
     *
     * \see
     * i_named_formula_manager
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    i_named_formula_manager& named_formulas() const;

    const boost::uint_fast32_t get_next_cf_id() const;

    // region Persistence

    /*!
     * \brief
     * deserialize from xml persistence.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void deserialize( session& s, const spreadsheetml::CT_extended_data& data );

    /*!
     * \brief
     * serialize to xml persistence.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void serialize( session& s, spreadsheetml::CT_extended_data& data ) const;

    // endregion Persistence

    worksheet_element_storage& elements() const;

    /*!
     * \brief
     * flag the workbook as having changes.
     *
     * \remarks
     * we could (any maybe very well should) use the objects diff
     * facilities here and use the token counter to determine changes
     * to the workbook.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void flag_changed();

    void flag_changed( bool val );

    void flag_changed_autosave( bool val );

    /*!
     * \brief
     * returns true in case the worksheet has unsaved changes.
     *
     * \remarks
     * workbook::flag_changed for the remarks section
     *
     * \see
     * workbook::flag_changed
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool has_changes() const;

    bool has_changes_autosave() const;

    bool is_temp() const;

    void is_temp( bool val );

    void version_major( short major );
    void version_minor( short minor );
    short version_major();
    short version_minor();

private:
    template<class, class, class>
    friend struct policy::has_parent;
    static shared_workbook_type create( const shared_application_type& app, const utf8_ci_string& name );

    template<class, class, template<class, class, class> class, class >
    friend class object_container;

    /*!
     * \brief
     * unload the workbook from memory.
     *
     * will in turn call unload on all worksheets.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();
private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    workbook( const shared_application_type& app, const utf8_ci_string& name );
private:
    struct workbook_impl;
    boost::scoped_ptr<workbook_impl> m_impl;

private:
    shared_application_type m_application;
    weak_workbook_type m_weak_workbook;
    variable_map m_variable;
    bool m_workbook_has_changes;
    bool m_workbook_has_changes_autosave;
    bool m_is_temp;
    short m_version_minor;
    short m_version_major;

};


