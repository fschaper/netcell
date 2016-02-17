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
#include <wss/calculation_cache.hpp>
#include <wss/calculation_setting.hpp>
#include <wss/stack.hpp>
#include <wss/session.hpp>
#include <wss/return_type_format.hpp>

class interpreter_context;

/*!
 * \brief
 * keeps information that need be available during an consecutive
 * calculation run.
 *
 * during one calculation run volatile information for one may
 * only be generated once. information about that is stored in the
 * calculation_cache. perform_stackwalk deals with recursive
 * calculations withing cyclic references.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class calculation_context
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
    calculation_context( ::session& s, const calculation_settings& settings )
        : m_session( s )
        , m_perform_stackwalk( true )
        , m_calculation_settings( settings )
        , m_return_type( return_type_format::unspecified )
        , m_interpreter_context( NULL ) {
    }

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    calculation_context( ::session& s )
        : m_session( s )
        , m_perform_stackwalk( true )
        , m_calculation_settings( s.calculation_settings() )
        , m_return_type( return_type_format::unspecified )
        , m_interpreter_context( NULL ) {
    }

    /*!
     * \brief
     * returns the calculation settings that should be applied
     * for the current calculation round.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const calculation_settings& settings() const {
        return m_calculation_settings;
    }

    /*!
     * \brief
     * holds the volatile information that will have to
     * be re-used once generated for one calculation run.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    calculation_cache& cache() {
        return m_session.cache();
    }

    /*!
     * \brief
     * session of the user.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::session& session() const {
        return m_session;
    }

    /*!
     * \brief
     * returns true in case a formula has to resolve
     * its precedents.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool perform_stackwalk() const {
        return m_perform_stackwalk;
    }

    /*!
     * \brief
     * set to false if formulas shall not calculate their
     * precedents before calculating themselves.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void perform_stackwalk( bool do_stackwalk ) {
        m_perform_stackwalk = do_stackwalk;
    }

    /*!
     * \brief
     * set the return type of functions
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    void return_type( return_type_format::type return_type ) {
        m_return_type = return_type;
    }

    /*!
     * \brief
     * get the return type of functions
     *
     * \author
     * Vali Nitu <vali@yalos-solutions.com>
     */
    return_type_format::type return_type() {
        return m_return_type;
    }

    /*!
    * \brief
    * store pointer to const interpreter_context
    * this allows us to access interpreter data when available
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void interpreter_context( const ::interpreter_context* ic ) {
        m_interpreter_context = ic;
    }

    /*!
    * \brief
    * retrieve interpreter_context pointer
    * might be NULL in case no interpreter was created
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    const ::interpreter_context* interpreter_context() const {
        return m_interpreter_context;
    }

    /*!
    * \brief
    * check if we're allowed to run a calculation
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    bool is_calculation_enabled()const {
        return m_calculation_settings.auto_calculation();
    }

private:
    ::session& m_session;
    bool m_perform_stackwalk;
    const calculation_settings& m_calculation_settings;
    return_type_format::type m_return_type;
    const ::interpreter_context* m_interpreter_context;
};

