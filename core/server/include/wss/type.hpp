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

#include <wss/define.hpp>
#include <wss/ci_string.hpp>
#include <wss/sheet_point.hpp>
#include <wss/sheet_range.hpp>
#include <wss/indexed_mapping.hpp>
#include <wss/locked_object.hpp>
#include <wss/sparse_vector.hpp>
#include <wss/core2_compatibility.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/shared_ptr.hpp>
# include <boost/weak_ptr.hpp>
# include <boost/optional.hpp>
# include <boost/thread/recursive_mutex.hpp>
# include <boost/flyweight.hpp>
# include <boost/flyweight/refcounted.hpp>
# include <vector>
# include <string>
# include <list>
# include <set>
# include <map>
#endif // HAS_PRECOMPILED_HEADER == 0

#ifndef _DEBUG
#include <boost/unordered/unordered_map.hpp>
#include <boost/unordered/unordered_set.hpp>
#endif // _DEBUG

namespace boost
{
    namespace uuids
    {
        struct uuid;
    }
}

template<typename T>
std::size_t hash_value( boost::shared_ptr<T> const& v )
{
    return boost::hash_value( v.get() );
}

inline std::size_t hash_value( utf8_ci_string const& v )
{
    return boost::hash_range( v.begin(), v.end() );
}


/*!
 * \brief only use this one if you don't need sorting!
 */
template<class T>
struct set_to_use : non_instantiable {
#ifdef _DEBUG
    typedef std::set<T> type;
#else
    typedef boost::unordered_set<T> type;
#endif // _DEBUG
};

/*!
 * \brief only use this one if you don't need sorting!
 */
template<class T>
struct multiset_to_use : non_instantiable {
#ifdef _DEBUG
    typedef std::multiset<T> type;
#else
    typedef boost::unordered_multiset<T> type;
#endif // _DEBUG
};


/*!
 * \brief only use this one if you don't need sorting!
 */
template<class keyT, class valueT>
struct map_to_use : non_instantiable {
#ifdef _DEBUG
    typedef std::map<keyT, valueT> type;
#else
    typedef boost::unordered_map<keyT, valueT> type;
#endif // _DEBUG
};

typedef boost::uuids::uuid uuid_type;

typedef uuid_type ws_elem_id_type;

/*!
 * \brief
 * dependency abstraction types.
 *
 * for more detailed information you should have a look at
 * i_dependency but to give a quick introduction to the next few types:
 *
 * f.ex. a formula cell can be dependent on other cells
 * or to just give an example for example named ranges
 * (or how we call it "named formulas").
 * the relationship between the cell and f.ex. the named formula (or another
 * cell) is expressed via the i_dependency interface.
 *
 * So in order to calculate A1 in "A1=B1+C2" we need to calculate B1 and C2.
 * Any change to B1 and C2 would in turn also require a recalculation of A1.
 * The i_dependency interface gives us the means to tell A1 that it needs to
 * update.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_dependency;
typedef boost::shared_ptr<i_dependency> shared_dependency_type;
typedef boost::weak_ptr<i_dependency> weak_dependency_type;
typedef std::vector<shared_dependency_type> shared_dependency_array_type;


/*!
 * \brief
 * shared cell type defined to remove duplicates and for convenience, usually shared_dependency_type should be used!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class cell;
typedef boost::shared_ptr<cell> shared_cell_type;

/*!
 * \brief
 * a dependency_reference is a reference to a dependency that might in
 * itself not as of yet exist.
 *
 * to give an example:
 * Cell A1 with the formula "=B1+C1+SUM(D1:D1000)" references
 * the Cell B1, C1 and all cells from D1 to D1000. If dependencies
 * would be connected directly all these 1001 dependencies would
 * need to be intatiated.
 * Instead of intatiating the dependency we maintain a "region of interest"
 * in the dependency_manager class where we connect the dependency_reference to.
 * If now a cell (or named formula) would be intatiated in a position that
 * is covered by one of these regions we would add the cell/named formula
 * to a set that is queries by the dependency_reference uppon call.
 * So let's say we write a value into cell D999. If D999 was not intatiated
 * before it will be created by the cell_manager. The cell_manager will
 * in turn inform the dependency_manager that a cell got created and it's position.
 * The dependency manager will then go through his list of entries and
 * add the cell dependency to all entries that are listed as being "interested" in
 * that area.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_dependency_reference;
typedef boost::shared_ptr<i_dependency_reference> shared_reference_type;

/*!
 * \brief
 * a application is foremost a container for a set of workbooks.
 *
 * on this level a user can define settings that are valid for all
 * workbooks and worksheets (such as calculation settings like number
 * of recursive operations that are allowed for a formula or the default
 * style for a worksheet cell).
 *
 * \see
 * workbook | worksheet | range
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class application;
typedef boost::shared_ptr<application> shared_application_type;
typedef boost::weak_ptr<application> weak_application_type;

/*!
 * \brief
 * a workbook is a container for worksheets and hosts workbook wide
 * named formulas and variables.
 *
 * \see
 * application | worksheet | range
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class workbook;
typedef boost::shared_ptr<workbook> shared_workbook_type;
typedef boost::weak_ptr<workbook> weak_workbook_type;

/*!
 * \brief
 * a worksheet is a cell container and also provides operations that work on
 * row and column level and provides access to cells via the range object.
 *
 * \see
 * application | workbook | range
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class worksheet;
typedef boost::shared_ptr<worksheet> shared_worksheet_type;
typedef boost::weak_ptr<worksheet> weak_worksheet_type;

/*!
 * \brief
 * provide thread based container for abstract locking of regions on a worksheet.
 *
 * some operations like cell movement or copy operate on regions rather than individual
 * cells. The range lock provides an abstract lock to all cells that will be affected
 * by such an operation so no two operations can interfere with the same range at any
 * one time.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock_keeper;
typedef boost::shared_ptr<range_lock_keeper> shared_range_lock_keeper_type;

/*!
 * \brief
 * the session object contains all user specific information that is valid
 * only for the duration of one connection.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class session;
typedef boost::shared_ptr<session> shared_session_type;
typedef boost::weak_ptr<session> weak_session_type;

class worksheet_element;
typedef boost::shared_ptr<worksheet_element> shared_worksheet_element_type;

class variant;
typedef sparse_vector<variant> css_style_vec_type;
/*!
 * \brief
 * mapping from a (string) key to some value
 *
 * TODO: (fschaper) maybe we should make the switch to
 * std::map<std::string, variant> at some point to provide
 * support for numeric values without the need of string
 * conversion.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef map_to_use<std::string, std::string>::type key_value_map_type;

typedef std::map<utf8_ci_string, std::string> ci_key_value_map_type;

typedef std::list<sheet_range> rectangle_list_type;

/*!
 * \brief
 * list of variables.
 *
 * variables are placeholders that can be set on a workbook/worksheet level
 * and take part in formula calculation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef std::vector<std::string> variable_name_list_type;

/*!
 * \brief
 * signifies a range on the sheet or "no" range.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef boost::optional<sheet_range> optional_sheet_range_type;

/*!
 * \brief
 * set of group named a user belongs to.
 * (currently mostly transparent to the core
 * and only needed in functions like =CURRENTGROUP())
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef std::set<std::string> group_set_type;

/*!
 * \brief
 * set of dependencies.
 *
 * since this set uses "shared_pointers" ensure that
 * we don't keep some references dangling around.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */

typedef set_to_use<shared_dependency_type>::type dependency_set_type;

/*!
 * \brief
 * set of weak dependencies.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef std::set<weak_dependency_type> weak_dependency_set_type;

/*!
 * \brief
 * set of shared_dependencies but wrapped into a locked
 * object which ensures access to it is serialized.
 *
 * this object type is used when we have to access
 * the "live" dependencies to an object and want to prevent
 * others access to the dependencies while we are performing
 * an operation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef locked_object
<
dependency_set_type
> locked_dependency_set_type;

/*!
 * \brief
 * set of weak_dependencies but wrapped into a locked
 * object which ensures access to it is serialized.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef locked_object
<
weak_dependency_set_type
> locked_weak_dependency_set_type;

/*!
 * \brief
 * set of shared_dependencies but wrapped into a locked
 * object which ensures access to it is serialized.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef boost::shared_ptr<locked_dependency_set_type> shared_locked_dependency_type;

/*!
 * \brief
 * set of weak_dependencies but wrapped into a locked
 * object which ensures access to it is serialized.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef boost::shared_ptr<locked_weak_dependency_set_type> shared_locked_weak_dependency_type;

/*!
 * \brief
 * type for tracking changes
 */
typedef boost::uint_least64_t token_id_type;

typedef boost::uint_fast32_t lookup_id_type;
typedef std::list<lookup_id_type> id_list_type;

/*!
 * \brief
 * id type for conditional formatting
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef boost::uint_fast32_t conditional_format_lookup_id_type;

namespace cf
{
    struct format_style_unlock_type;
    typedef boost::shared_ptr<format_style_unlock_type> shared_format_style_unlock_type;
    typedef map_to_use<size_t, cf::shared_format_style_unlock_type>::type cf_vec_type;
}


struct border_types;
//template<class T>
class border;
//typedef borderT<border_types> border;
typedef border conditional_format_border_type;

typedef sparse_vector<border> border_vec_type;

/*!
 * \brief
 * vector type for unlocked cells queries
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef sparse_vector<bool> unlocked_cells_vec_type;

/*!
 * \brief
 * kernel for named formula usage
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class named_formula_kernel;
typedef boost::shared_ptr<named_formula_kernel> shared_named_formula_kernel_type;

/*!
 * \brief
 * kernel for cell usage
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class formula_kernel;
typedef boost::shared_ptr<formula_kernel> shared_formula_kernel_type;

/*!
 * \brief
 * vector used when returning the list of workbooks
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
typedef boost::tuple< std::string, std::string, std::string, std::string > id_name_path_mapping_type;
typedef std::vector< id_name_path_mapping_type > id_name_path_mapping_vec_type;

typedef boost::uint_fast32_t insertion_counter_type;

/*!
 * \brief
 * the volatile cache will either return a cached result or an
 * uninitialized variant (optional).
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class variant;
typedef boost::optional<variant> optional_variant_type;

/*!
 * \brief
 * shared undo able command object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_undoable_command;
typedef boost::shared_ptr<i_undoable_command> shared_undoable_command_type;

/*!
 * \brief
 * locked list of import progress messages.
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
typedef std::vector<std::string> progress_list_type;
typedef locked_object<progress_list_type> locked_import_progress_list;

