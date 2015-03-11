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

#include "precompiled_header.hpp"

// /common functions

interpreter_variant function_rand( function_parameter& parameters );
interpreter_variant function_isblank( function_parameter& parameters );
interpreter_variant function_iserror( function_parameter& parameters );
interpreter_variant function_if( function_parameter& parameters );
interpreter_variant function_not( function_parameter& parameters );
interpreter_variant function_isduplicate( function_parameter& parameters );
interpreter_variant function_isunique( function_parameter& parameters );
interpreter_variant function_average( function_parameter& parameters );
interpreter_variant function_averagea( function_parameter& parameters );
interpreter_variant function_averagee( function_parameter& parameters );
interpreter_variant function_max( function_parameter& parameters );
interpreter_variant function_min( function_parameter& parameters );
interpreter_variant function_percentrank( function_parameter& parameters );
interpreter_variant function_rank( function_parameter& parameters );
interpreter_variant function_iseven( function_parameter& parameters );
interpreter_variant function_isodd( function_parameter& parameters );
interpreter_variant function_syd( function_parameter& parameters );
interpreter_variant function_isnumber( function_parameter& parameters );
interpreter_variant function_istext( function_parameter& parameters );
interpreter_variant function_isref( function_parameter& parameters );

interpreter_variant function_var( function_parameter& parameters );
interpreter_variant function_varp( function_parameter& parameters );
interpreter_variant function_vara( function_parameter& parameters );
interpreter_variant function_varpa( function_parameter& parameters );
interpreter_variant function_stdev( function_parameter& parameters );
interpreter_variant function_stdevp( function_parameter& parameters );
interpreter_variant function_stdeva( function_parameter& parameters );
interpreter_variant function_stdevpa( function_parameter& parameters );
interpreter_variant function_covar( function_parameter& parameters );
interpreter_variant function_correl( function_parameter& parameters );
interpreter_variant function_rsq( function_parameter& parameters );
interpreter_variant function_pearson( function_parameter& parameters );
interpreter_variant function_slope( function_parameter& parameters );
interpreter_variant function_intercept( function_parameter& parameters );
interpreter_variant function_steyx( function_parameter& parameters );
interpreter_variant function_sumx2py2( function_parameter& parameters );
interpreter_variant function_sumx2my2( function_parameter& parameters );
interpreter_variant function_sumxmy2( function_parameter& parameters );
interpreter_variant function_countif( function_parameter& parameters );
interpreter_variant function_sumif( function_parameter& parameters );
interpreter_variant function_percentile( function_parameter& parameters );
interpreter_variant function_quartile( function_parameter& parameters );
interpreter_variant function_median( function_parameter& parameters );

interpreter_variant function_left( function_parameter& parameters );
interpreter_variant function_right( function_parameter& parameters );
interpreter_variant function_search( function_parameter& parameters );
interpreter_variant function_len( function_parameter& parameters );
interpreter_variant function_between( function_parameter& parameters );
interpreter_variant function_nbetween( function_parameter& parameters );
interpreter_variant function_concatenate( function_parameter& parameters );
interpreter_variant function_proper( function_parameter& parameters );
interpreter_variant function_toupper( function_parameter& parameters );
interpreter_variant function_tolower( function_parameter& parameters );
interpreter_variant function_exact( function_parameter& parameters );
interpreter_variant function_t( function_parameter& parameters );
interpreter_variant function_trim( function_parameter& parameters );
interpreter_variant function_substitute( function_parameter& parameters );
interpreter_variant function_code( function_parameter& parameters );
interpreter_variant function_char( function_parameter& parameters );
interpreter_variant function_concatenate_range( function_parameter& parameters );

interpreter_variant function_ftest( function_parameter& parameters );
interpreter_variant function_betainv( function_parameter& parameters );
interpreter_variant function_betadist( function_parameter& parameters );
interpreter_variant function_finv( function_parameter& parameters );
interpreter_variant function_fdist( function_parameter& parameters );
interpreter_variant function_chitest( function_parameter& parameters );
interpreter_variant function_chiinv( function_parameter& parameters );
interpreter_variant function_chidist( function_parameter& parameters );
interpreter_variant function_gammainv( function_parameter& parameters );
interpreter_variant function_gammadist( function_parameter& parameters );
interpreter_variant function_gammaln( function_parameter& parameters );
interpreter_variant function_ttest( function_parameter& parameters );
interpreter_variant function_tinv( function_parameter& parameters );
interpreter_variant function_tdist( function_parameter& parameters );
interpreter_variant function_expondist( function_parameter& parameters );
interpreter_variant function_poisson( function_parameter& parameters );
interpreter_variant function_hypgeomdist( function_parameter& parameters );
interpreter_variant function_negbinomdist( function_parameter& parameters );
interpreter_variant function_critbinom( function_parameter& parameters );
interpreter_variant function_binomdist( function_parameter& parameters );
interpreter_variant function_iserr( function_parameter& parameters );
interpreter_variant function_error_type( function_parameter& parameters );
interpreter_variant function_isna( function_parameter& parameters );
interpreter_variant function_islogical( function_parameter& parameters );
interpreter_variant function_isnontext( function_parameter& parameters );
interpreter_variant function_weibull( function_parameter& parameters );
interpreter_variant function_fisherinv( function_parameter& parameters );
interpreter_variant function_fisher( function_parameter& parameters );
interpreter_variant function_rate( function_parameter& parameters );
interpreter_variant function_npv( function_parameter& parameters );
interpreter_variant function_nper( function_parameter& parameters );
interpreter_variant function_mirr( function_parameter& parameters );
interpreter_variant function_ispmt( function_parameter& parameters );
interpreter_variant function_irr( function_parameter& parameters );
interpreter_variant function_pv( function_parameter& parameters );
interpreter_variant function_pmt( function_parameter& parameters );
interpreter_variant function_combin( function_parameter& parameters );
interpreter_variant function_volatile_count( function_parameter& parameters );
interpreter_variant function_used_range( function_parameter& parameters );
interpreter_variant function_standardize( function_parameter& parameters );
interpreter_variant function_round( function_parameter& parameters );
interpreter_variant function_maxa( function_parameter& parameters );
interpreter_variant function_mina( function_parameter& parameters );
interpreter_variant function_geomean( function_parameter& parameters );
interpreter_variant function_harmean( function_parameter& parameters );
interpreter_variant function_devsq( function_parameter& parameters );
interpreter_variant function_skew( function_parameter& parameters );
interpreter_variant function_kurt( function_parameter& parameters );
interpreter_variant function_avedev( function_parameter& parameters );
interpreter_variant function_mode( function_parameter& parameters );
interpreter_variant function_sln( function_parameter& parameters );
interpreter_variant function_forecast( function_parameter& parameters );
interpreter_variant function_prob( function_parameter& parameters );
interpreter_variant function_normsdist( function_parameter& parameters );
interpreter_variant function_normdist( function_parameter& parameters );
interpreter_variant function_lognormdist( function_parameter& parameters );
interpreter_variant function_normsinv( function_parameter& parameters );
interpreter_variant function_norminv( function_parameter& parameters );
interpreter_variant function_confidence( function_parameter& parameters );
interpreter_variant function_loginv( function_parameter& parameters );
interpreter_variant function_countblank( function_parameter& parameters );
interpreter_variant function_ddb( function_parameter& parameters );
interpreter_variant function_db( function_parameter& parameters );
interpreter_variant function_fv( function_parameter& parameters );
interpreter_variant function_frequency( function_parameter& parameters );

interpreter_variant function_trimmean( function_parameter& parameters );
interpreter_variant function_large( function_parameter& parameters );
interpreter_variant function_small( function_parameter& parameters );
interpreter_variant function_sum( function_parameter& parameters );
interpreter_variant function_sumsq( function_parameter& parameters );
interpreter_variant function_sumproduct( function_parameter& parameters );
interpreter_variant function_product( function_parameter& parameters );
interpreter_variant function_sign( function_parameter& parameters );
interpreter_variant function_log10( function_parameter& parameters );
interpreter_variant function_ln( function_parameter& parameters );
interpreter_variant function_log( function_parameter& parameters );
interpreter_variant function_sqrt( function_parameter& parameters );
interpreter_variant function_exp( function_parameter& parameters );
interpreter_variant function_transpose( function_parameter& parameters );
interpreter_variant function_atanh( function_parameter& parameters );
interpreter_variant function_asinh( function_parameter& parameters );
interpreter_variant function_acosh( function_parameter& parameters );
interpreter_variant function_cos( function_parameter& parameters );
interpreter_variant function_sin( function_parameter& parameters );
interpreter_variant function_pi( function_parameter& parameters );
interpreter_variant function_abs( function_parameter& parameters );
interpreter_variant function_tan( function_parameter& parameters );
interpreter_variant function_atan( function_parameter& parameters );
interpreter_variant function_acos( function_parameter& parameters );
interpreter_variant function_asin( function_parameter& parameters );
interpreter_variant function_atan2( function_parameter& parameters );
interpreter_variant function_sinh( function_parameter& parameters );
interpreter_variant function_tanh( function_parameter& parameters );
interpreter_variant function_cosh( function_parameter& parameters );
interpreter_variant function_mod( function_parameter& parameters );
interpreter_variant function_power( function_parameter& parameters );
interpreter_variant function_int( function_parameter& parameters );
interpreter_variant function_fact( function_parameter& parameters );
interpreter_variant function_radians( function_parameter& parameters );
interpreter_variant function_permut( function_parameter& parameters );
interpreter_variant function_radians( function_parameter& parameters );
interpreter_variant function_degrees( function_parameter& parameters );
interpreter_variant function_floor( function_parameter& parameters );
interpreter_variant function_ceiling( function_parameter& parameters );
interpreter_variant function_mround( function_parameter& parameters );
interpreter_variant function_even( function_parameter& parameters );
interpreter_variant function_odd( function_parameter& parameters );
interpreter_variant function_now( function_parameter& parameters );
interpreter_variant function_today( function_parameter& parameters );
interpreter_variant function_address( function_parameter& parameters );
interpreter_variant function_type( function_parameter& parameters );
interpreter_variant function_roundup( function_parameter& parameters );
interpreter_variant function_rounddown( function_parameter& parameters );
interpreter_variant function_trunc( function_parameter& parameters );
interpreter_variant function_count( function_parameter& parameters );
interpreter_variant function_counta( function_parameter& parameters );
interpreter_variant function_column( function_parameter& parameters );
interpreter_variant function_row( function_parameter& parameters );
interpreter_variant function_choose( function_parameter& parameters );

interpreter_variant function_true( function_parameter& parameters );
interpreter_variant function_false( function_parameter& parameters );


interpreter_variant function_lookup( function_parameter& parameters );
interpreter_variant function_hlookup( function_parameter& parameters );
interpreter_variant function_vlookup( function_parameter& parameters );
interpreter_variant function_columns( function_parameter& parameters );
interpreter_variant function_rows( function_parameter& parameters );

interpreter_variant function_index( function_parameter& parameters );
interpreter_variant function_find( function_parameter& parameters );
interpreter_variant function_mid( function_parameter& parameters );
interpreter_variant function_na( function_parameter& parameters );
interpreter_variant function_frequency( function_parameter& parameters );
interpreter_variant function_leftb( function_parameter& parameters );
interpreter_variant function_replace( function_parameter& parameters );
interpreter_variant function_rept( function_parameter& parameters );
interpreter_variant function_and( function_parameter& parameters );
interpreter_variant function_or( function_parameter& parameters );
interpreter_variant function_ztest( function_parameter& parameters );
interpreter_variant function_minverse( function_parameter& parameters );
interpreter_variant function_mdeterm( function_parameter& parameters );
interpreter_variant function_mmult( function_parameter& parameters );
interpreter_variant function_text( function_parameter& parameters );
interpreter_variant function_match( function_parameter& parameters );
interpreter_variant function_offset( function_parameter& parameters );
interpreter_variant function_indirect( function_parameter& parameters );

interpreter_variant function_hiderow( function_parameter& parameters );
interpreter_variant function_randbetween( function_parameter& parameters );
interpreter_variant function_hidecolumn( function_parameter& parameters );

interpreter_variant function_currentuser( function_parameter& parameters );
interpreter_variant function_usergroups( function_parameter& parameters );
interpreter_variant function_userlocale( function_parameter& parameters );

interpreter_variant function_month( function_parameter& parameters );
interpreter_variant function_year( function_parameter& parameters );
interpreter_variant function_day( function_parameter& parameters );
interpreter_variant function_weeknum( function_parameter& parameters );
interpreter_variant function_date( function_parameter& parameters );
interpreter_variant function_time( function_parameter& parameters );

interpreter_variant function_value( function_parameter& parameters );

interpreter_variant function_unformatted( function_parameter& parameters );

void register_functions( function_registry& r );
