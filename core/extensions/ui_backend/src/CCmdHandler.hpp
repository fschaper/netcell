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

#ifndef _CCMDHANDLER
# define _CCMDHANDLER



// ui_backend
#include "SnapshotManager.hpp"
#include "CommandFunctors.hpp"

// local error codes
#define ERR_RUNTIME_ERROR 100
#define ERR_PARSING_FAILED 101
#define ERR_NOT_IMPLEMENTED 102
#define ERR_INVALID_SESSION 103

/**
 * \brief
 * Compound command handler.
 */

class CCmdHandler : public BackendHandler
{
private:
    static const std::string HEADER_SESS;
    static const std::string HEADER_BOOK;
    static const std::string DEFAULT_SESS_NAME;
    static const std::string DEFAULT_L10N;

    typedef json::grammar<char>::variant json_variant_t;
    typedef json::grammar<char>::array json_array_t;
    typedef json::grammar<char>::object json_obj_t;
    typedef bool ( CCmdHandler::*cmd_handler_ptr_t ) ( const json_array_t& );
    typedef std::map<std::string, cmd_handler_ptr_t> cmd_handlers_map_t;
    typedef std::string diff_result;

    class Init
    {
    public:
        cmd_handlers_map_t cmd_handlers_map;

        Init ();
    };

    static const Init init;

    JSONSerializer m_json_serializer;
    const HttpRequest* m_request;
    HttpResponse* m_response;

    std::stringstream m_result;

    bool m_logged_out;
    std::string m_session_id;
    std::string m_session_name;
    std::string m_l10n_curr;
    std::string m_l10n_orig;

    locked_session m_session_context;

    enum Flags {
        FLAG_STOP_ON_ERROR = 1lu,
        FLAG_USE_DEFAULT_L10N  = 2lu
    };

    void respond ( int status_code, const std::string& response );
    void fail ( int status_code, const char* msg );
    void succeed ( const std::string& response );
    void succeed ();

    bool fail_cmd ( const char* cmd, const std::exception& );
    bool fail_cmd ( const char* cmd, int err_code, const std::string& err_msg );
    bool fail_cmd ( const char* cmd, int err_code, const char* err_msg );

    variant json2Value ( const json_variant_t& );
    bool transform_coords ( unsigned long&, unsigned long& );
    bool transform_coords ( unsigned long&, unsigned long&, unsigned long&, unsigned long& );
    bool bind_rect ( int, const json_array_t&, sheet_range& );

    bool cmd_login ( const json_array_t& ); // logi
    bool cmd_logout ( const json_array_t& ); // logo
    bool cmd_is_logged_in ( const json_array_t& ); // ilog

    bool cmd_get_user_locale ( const json_array_t& ); // gusl
    bool cmd_set_user_locale ( const json_array_t& ); // susl
    bool cmd_l10n_default ( const json_array_t& ); // l10nd
    bool cmd_l10n_revert ( const json_array_t& ); // l10nr

    bool cmd_get_server_info ( const json_array_t& ); // gsi

    bool cmd_set_border( const json_array_t& ); // sbrd
    bool cmd_get_border ( const json_array_t& ); // gbrd

    void get_changed_wsels ( std::stringstream& );
    bool cmd_get_changed_wsels ( const json_array_t& ); // gcwe

    bool cmd_snapshot_create ( const json_array_t& ); // snpc
    bool cmd_snapshot_get ( const json_array_t& ); // snpg
    bool cmd_snapshot_diff ( const json_array_t& ); // snpd

    bool cmd_wssobjects_list ( const json_array_t& ); // olst
    bool cmd_wssobjects_select ( const json_array_t& ); // osel
    bool cmd_wssobjects_rename ( const json_array_t& ); // oren
    bool cmd_wssobjects_add ( const json_array_t& ); // oadd
    bool cmd_wssobjects_delete ( const json_array_t& ); // odel

    bool cmd_get_used_range ( const json_array_t& ); // gurn
    bool cmd_get_rng_as_vals ( const json_array_t& ); // grav
    bool cmd_get_rng_as_rgns ( const json_array_t& ); // grar

    bool cmd_get_def_style ( const json_array_t& ); // gdst
    bool cmd_set_def_style ( const json_array_t& ); // sdst

    bool cmd_get_def_colrow_dims ( const json_array_t& ); // gdcr
    bool cmd_set_def_colrow_dims ( const json_array_t& ); // sdcr
    bool cmd_get_colrow_dims ( const json_array_t& ); // gcr
    bool cmd_set_colrow_dims ( const json_array_t& ); // scr
    bool cmd_autofit ( const json_array_t& ); // afit
    bool cmd_adapt ( const json_array_t& ); // adcr
    bool cmd_get_max_cell_dims ( const json_array_t& ); // gmc

    bool cmd_set_auto_calc ( const json_array_t& ); // sac

    bool cmd_get_formatted_sample ( const json_array_t& ); // gfs

    bool cmd_load_workbook ( const json_array_t& ); // load
    bool cmd_save_workbook ( const json_array_t& ); // save
    bool cmd_import_workbook ( const json_array_t& ); // limp
    bool cmd_export_workbook ( const json_array_t& ); // lexp
    bool cmd_book_not_saved ( const json_array_t& cmd ); // bsp


    bool cmd_get_undo_state ( const json_array_t& ); // gust
    bool cmd_start_undo_transaction ( const json_array_t& ); // undots
    bool cmd_end_undo_transaction ( const json_array_t& ); // undote
    bool cmd_undo ( const json_array_t& ); // undo
    bool cmd_redo ( const json_array_t& ); // redo

    bool cmd_copy_range ( const json_array_t& ); // cprn
    bool cmd_copyfill_range ( const json_array_t& ); // cfrn
    bool cmd_copymove_range ( const json_array_t& ); // cmrn
    bool cmd_cut_range ( const json_array_t& ); // ctrn
    bool cmd_paste_range ( const json_array_t& ); // ptrn

    bool cmd_clear_attributes ( const json_array_t& ); // clat
    bool cmd_hb_dependents ( const json_array_t& ); // hbd
    bool cmd_set_array_formula ( const json_array_t& ); // saf
    bool cmd_unset_array_formula ( const json_array_t& ); // uaf

    bool cmd_names_get ( const json_array_t& ); // nget
    bool cmd_names_list ( const json_array_t& ); // nlst
    bool cmd_names_add ( const json_array_t& ); // nadd
    bool cmd_names_update ( const json_array_t& ); // nupd
    bool cmd_names_delete ( const json_array_t& ); // ndel
    bool cmd_names_exists ( const json_array_t& ); // nexs

    bool cmd_set_variable ( const json_array_t& ); // svar
    bool cmd_get_variable ( const json_array_t& ); // gvar
    bool cmd_get_variable_list ( const json_array_t& ); // gvls
    bool cmd_clear_variables ( const json_array_t& ); // cvar

    bool cmd_get_book_var_list ( const json_array_t& ); // gbvl
    bool cmd_get_wsheet_elements ( const json_array_t& ); // wget
    bool cmd_add_wsheet_elements ( const json_array_t& ); // wadd
    bool cmd_update_wsheet_elements ( const json_array_t& ); // wupd
    bool cmd_delete_wsheet_elements ( const json_array_t& ); // wdel

    void set_cell ( const json_obj_t&, const sheet_range&, const bool, const bool, const bool );
    bool cmd_set_cell_region ( const json_array_t& ); // cdrg
    bool cmd_set_cell_range ( const json_array_t& ); // cdrn

    bool cmd_clear ( const json_array_t& ); // clr
    bool cmd_copypaste ( const json_array_t& ); // co
    bool cmd_copymovepaste ( const json_array_t& ); // cm
    bool cmd_cutpaste ( const json_array_t& ); // cu

    bool cmd_insert_cells ( const json_array_t& ); // icel
    bool cmd_delete_cells ( const json_array_t& ); // dcel

    bool cmd_insert_column ( const json_array_t& ); // ic
    bool cmd_insert_row ( const json_array_t& ); // ir
    bool cmd_delete_column ( const json_array_t& ); // dc
    bool cmd_delete_row ( const json_array_t& ); // dr

    bool cmd_merge ( const json_array_t& ); // mrg
    bool cmd_unmerge ( const json_array_t& ); // umrg

    bool cmd_cndfmt_set ( const json_array_t& ); // cfset
    bool cmd_cndfmt_get ( const json_array_t& ); // cfget
    bool cmd_cndfmt_move ( const json_array_t& ); // cfmov
    bool cmd_cndfmt_delete ( const json_array_t& ); // cfdel

    bool cmd_mark ( const json_array_t& ); // mark

    bool cmd_lock ( const json_array_t& ); // lock

    bool cmd_wss_active_objects_select ( const json_array_t& ); // ocurr

    bool cmd_trigger_exten_event ( const json_array_t& ); // tee
    bool cmd_execute_macro ( const json_array_t& ); // em

    bool cmd_workbook_list_ex ( const json_array_t& ); // bels

    bool cmd_move_worksheet ( const json_array_t& ); // smv
    bool cmd_copy_worksheet ( const json_array_t& ); // scp

    bool cmd_add_clone_worksheet ( const json_array_t& ); // sclo
    bool cmd_remove_clone_worksheet ( const json_array_t& ); // srcl

    bool cmd_get_unlckd_ranges ( const json_array_t& ); // gur

    bool cmd_begin_calc_context ( const json_array_t& ); // bcc
    bool cmd_end_calc_context ( const json_array_t& ); // ecc

    bool cmd_book_change_metadata ( const json_array_t& ); // bcmd

    bool cmd_ping ( const json_array_t& cmd );// ping

    bool cmd_get_workbook_version ( const json_array_t& ); // gwv


    template <class T_1> bool test_types ( json_array_t::size_type, char, int, const json_array_t& );
    template <class T_1, class T_2 > bool test_types ( json_array_t::size_type, char, int, const json_array_t& );
    template <class T_1, class T_2,  class T_3 > bool test_types ( json_array_t::size_type, char, int, const json_array_t& );
    template <class T_1, class T_2,  class T_3, class T_4> bool test_types ( json_array_t::size_type, char, int,  const json_array_t& );
    template <class T_1, class T_2,  class T_3, class T_4, class T_5 > bool test_types ( json_array_t::size_type, char, int, const json_array_t& );
    template <class T_1, class T_2,  class T_3, class T_4, class T_5, class T_6 > bool test_types ( json_array_t::size_type, char, int, const json_array_t& );
    template <class T_1, class T_2,  class T_3, class T_4, class T_5, class T_6, class T_7, class T_8 > bool test_types ( json_array_t::size_type, char, int, const json_array_t& );

public:
    CCmdHandler ( const char* handle );

    void operator() ( const HttpRequest&, HttpResponse& );
};


#endif // _CCMDHANDLER
