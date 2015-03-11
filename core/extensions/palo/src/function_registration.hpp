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
 */

// This file has been auto-generated. Don't change it by hand!

REGISTER_PALO_FUNCTION( palo_register_server, "PALO.REGISTER", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eprev, "PALO.EPREV", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_enext, "PALO.ENEXT", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_echildname, "PALO.ECHILD", 5, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_efirst, "PALO.EFIRST", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_echildcount, "PALO.ECHILDCOUNT", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_ecount, "PALO.ECOUNT", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eindex, "PALO.EINDEX", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eischild, "PALO.EISCHILD", 5, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_ename, "PALO.ENAME", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eparentcount, "PALO.EPARENTCOUNT", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eparentname, "PALO.EPARENT", 5, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_etype, "PALO.ETYPE", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_esibling, "PALO.ESIBLING", 5, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_setdata, "PALO.SETDATA", 0, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_setdataif, "PALO.SETDATAIF", 0, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_setdataaif, "PALO.SETDATAAIF", 6, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_datav, "PALO.DATAV", 0, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_data, "PALO.DATA", 0, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_datac, "PALO.DATAC", 0, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_datat, "PALO.DATAT", 0, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_dataat, "PALO.DATAAT", 3, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_dataa, "PALO.DATAA", 3, false, false, return_type_format::numeric )
REGISTER_PALO_FUNCTION( palo_setdataa, "PALO.SETDATAA", 5, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eweight, "PALO.EWEIGHT", 5, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_elevel, "PALO.ELEVEL", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eindent, "PALO.EINDENT", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_etoplevel, "PALO.ETOPLEVEL", 2, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_ping, "PALO.PING", 1, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_root_list_databases, "PALO.ROOT_LIST_DATABASES", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_database_list_cubes, "PALO.DATABASE_LIST_CUBES", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_database_list_dimensions, "PALO.DATABASE_LIST_DIMENSIONS", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_cube_list_dimensions, "PALO.CUBE_LIST_DIMENSIONS", 2, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_dimension_list_cubes, "PALO.DIMENSION_LIST_CUBES", 2, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_dimension_list_elements, "PALO.DIMENSION_LIST_ELEMENTS", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_consolidation_elements, "PALO.ELEMENT_LIST_CONSOLIDATION_ELEMENTS", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_children, "PALO.ELEMENT_LIST_CHILDREN", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_parents, "PALO.ELEMENT_LIST_PARENTS", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_siblings, "PALO.ELEMENT_LIST_SIBLINGS", 3, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_edelete, "PALO.EDELETE", 4, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eadd, "PALO.EADD", 8, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_eupdate, "PALO.EUPDATE", 6, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_erename, "PALO.ERENAME", 5, true, true, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_subset, "PALO.SUBSET", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_subsetsize, "PALO.SUBSETSIZE", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_picklist, "PALO.PICKLIST", 2, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_tfilter, "PALO.TFILTER", 2, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_sort, "PALO.SORT", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_afilter, "PALO.AFILTER", 1, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_hfilter, "PALO.HFILTER", 9, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_dfilter, "PALO.DFILTER", 7, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_subcube, "PALO.SUBCUBE", 0, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_remove_connection, "PALO.REMOVE_CONNECTION", 1, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_descendants, "PALO.ELEMENT_LIST_DESCENDANTS", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_element_list_ancestors, "PALO.ELEMENT_LIST_ANCESTORS", 4, false, false, return_type_format::unspecified )
REGISTER_PALO_FUNCTION( palo_ealias, "PALO.EALIAS", 6, false, false, return_type_format::unspecified )