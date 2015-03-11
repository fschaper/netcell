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
 *  \author
 *  Dragan Simic <dragan.simic@develabs.com>
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#ifndef _PHPBRIDGE_RANGE_HELPERS
#   define _PHPBRIDGE_RANGE_HELPERS

#define GET_UUIDS_AND_A1_RANGE() \
    zval *worksheet_object  = zend_read_property(wss_range_class, this_ptr, WSS_PHP_STRING_NO_NULL("m_parent"), 0 TSRMLS_CC); \
    \
    zval *worksheets_object = zend_read_property(wss_worksheet_class, worksheet_object, WSS_PHP_STRING_NO_NULL("m_parent"), 0 TSRMLS_CC); \
    zval *workbook_object   = zend_read_property(wss_worksheets_class, worksheets_object, WSS_PHP_STRING_NO_NULL("m_parent"), 0 TSRMLS_CC); \
    \
    zval *worksheet_uuid    = zend_read_property(wss_worksheet_class, worksheet_object, WSS_PHP_STRING_NO_NULL("m_worksheet_uuid"), 0 TSRMLS_CC); \
    zval *workbook_uuid     = zend_read_property(wss_workbook_class, workbook_object, WSS_PHP_STRING_NO_NULL("m_workbook_uuid"), 0 TSRMLS_CC); \
    zval *range_a1_notation = zend_read_property(wss_range_class, this_ptr, WSS_PHP_STRING_NO_NULL("m_range_a1"), 0 TSRMLS_CC);

// set of macros for making the code shorter
#define FUNC_SET_RETURN_PREPARE_CHECK(x) \
    zval *x = NULL; \
    \
    if (ZEND_NUM_ARGS() > 0) { \
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &x) == FAILURE) { \
            WRONG_PARAM_COUNT; \
        } \
    } \
    \
    GET_UUIDS_AND_A1_RANGE() \
    boost::shared_ptr<Application> application = WSS_PHP_G(cx)->get_active_application().lock();

#define GET_WORKBOOK_WORKSHEET() \
    /* get the workbook and worksheet */ \
    Application::value_type workbook = application->get_by_uuid(*WSS_PHP_G(cx), Z_STRVAL_P(workbook_uuid)); \
    Workbook::value_type worksheet   = workbook->get_by_uuid(*WSS_PHP_G(cx), Z_STRVAL_P(worksheet_uuid)); \
    \
    /* convert a1 notation to array of BoundedRect objects */ \
    A1Conversion::multi_rect_vector_type ranges = A1Conversion::from_a1(Z_STRVAL_P(range_a1_notation));

#define RETURN_FIRST_RANGE_PROPS(x) \
    { \
        /* excel does only return the values of the first range and ignores the rest, so do we */ \
        if (ranges.size() > 0) { \
            const BoundedRect& source_range = ranges[0]; \
            Value wss_range_result = worksheet->get_range(source_range).x(*WSS_PHP_G(cx)); \
            \
            /* convert props format to excel format, and then to zval form */ \
            array_return_converter()(wss_range_result, source_range); \
            zend_value_converter()(return_value, wss_range_result); \
            \
        } else { \
            RETURN_NULL() \
        } \
    }

#define SET_RANGES_PROP(x, y) \
    { \
        /* iterate over all BoundedRects and set to the specified value */ \
        Value tmp = zend_value_converter()(y TSRMLS_CC); \
        A1Conversion::multi_rect_vector_type::const_iterator it(ranges.begin()); \
        A1Conversion::multi_rect_vector_type::const_iterator end(ranges.end()); \
        \
        for (; it != end; ++it) { \
            worksheet->get_range(*it).x(*WSS_PHP_G(cx), tmp); \
        } \
    }

#endif // _PHPBRIDGE_RANGE_HELPERS
