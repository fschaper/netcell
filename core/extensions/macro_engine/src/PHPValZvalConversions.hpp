/*!
 *  \brief
 *  PHP/WSS bridge: conversions vetwwen internal Value end exterbal zval
 *
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 *  Vali Nitu <vali.nitu@yalos-solutions.com>
 */

#ifndef _PHPBVALZVALCONVERSION
#   define _PHPBVALZVALCONVERSION

class val_zval
{
public:
    ~val_zval() {
        if ( NULL != m_zval ) {
            zval_dtor( m_zval );
        }
        if ( NULL != m_Value ) {
            delete m_Value;
        }
    }

    val_zval( zval* arg ) {
        m_zval          = NULL;
        m_zval_arg      = arg;
        m_Value         = zval2val( arg );
    }

    val_zval( Value* arg ) {
        m_Value         = NULL;
        m_Value_arg     = arg;
        m_zval          = val2zval( arg );
    }

    zval*   get_zval() {
        if ( NULL != m_zval ) {
            return m_zval;
        } else {
            return m_zval_arg;
        }
    }
    Value*  get_Value() {
        if ( NULL != m_Value ) {
            return m_Value;
        } else {
            return m_Value_arg;
        }
    }

    static void fill_array( zval* argZval, std::vector< std::string>& result ) {

        HashTable*  php_array = Z_ARRVAL_P( argZval );

        for (    zend_hash_internal_pointer_reset( php_array );
                 SUCCESS == zend_hash_has_more_elements( php_array );
                 zend_hash_move_forward( php_array ) ) {

            int             type;
            char*            key;
            unsigned int    keylen;
            unsigned long   idx;
            zval**            ppzval;//warning
            void*           zval_temp;

            type = zend_hash_get_current_key_ex( php_array, &key, &keylen, &idx, 0, NULL );

            if ( zend_hash_get_current_data( php_array, &zval_temp ) == FAILURE ) {
                /* Should never actually fail
                * since the key is known to exist. */
                continue;
            }
            ppzval = ( zval** )zval_temp;
            if ( IS_STRING != Z_TYPE_PP( ppzval ) ) {
                throw std::string( "Invalid argument type." );
            }


            result.push_back( Z_STRVAL_PP( ppzval ) );
        }
    }

    static void fill_array_string( zval* argZval, std::vector< std::string>& result ) {

        HashTable*  php_array = Z_ARRVAL_P( argZval );

        for (    zend_hash_internal_pointer_reset( php_array );
                 SUCCESS == zend_hash_has_more_elements( php_array );
                 zend_hash_move_forward( php_array ) ) {

            int             type;
            char*            key;
            unsigned int    keylen;
            unsigned long   idx;
            zval**            ppzval;//warning
            void*           zval_temp = NULL;

            type = zend_hash_get_current_key_ex( php_array, &key, &keylen, &idx, 0, NULL );

            if ( zend_hash_get_current_data( php_array, &zval_temp ) == FAILURE ) {
                /* Should never actually fail
                * since the key is known to exist. */
                continue;
            }
            ppzval = ( zval** )zval_temp;
            if ( IS_STRING != Z_TYPE_PP( ppzval ) ) {
                throw std::string( "Invalid argument type." );
            }


            result.push_back( Z_STRVAL_PP( ppzval ) );
        }
    }

    static void fill_array_pair( zval* argZval, WorksheetElement::key_value_vector_type& result ) {

        HashTable*  php_array = Z_ARRVAL_P( argZval );

        for (    zend_hash_internal_pointer_reset( php_array );
                 SUCCESS == zend_hash_has_more_elements( php_array );
                 zend_hash_move_forward( php_array ) ) {

            int             type;
            char*            key;
            unsigned int    keylen;
            unsigned long   idx;
            zval**            ppzval;//warning
            void*           zval_temp = NULL;

            type = zend_hash_get_current_key_ex( php_array, &key, &keylen, &idx, 0, NULL );

            if ( zend_hash_get_current_data( php_array, &zval_temp ) == FAILURE ) {
                /* Should never actually fail
                * since the key is known to exist. */
                continue;
            }
            ppzval = ( zval** )zval_temp;
            if ( IS_ARRAY != Z_TYPE_PP( ppzval ) ) {
                throw std::string( "Invalid argument type." );
            }

            HashTable*                          crt_php_array = Z_ARRVAL_PP( ppzval );
            WorksheetElement::key_value_type    crt_val;
            unsigned char                       pass_count = 0;

            for (    zend_hash_internal_pointer_reset( crt_php_array );
                     SUCCESS == zend_hash_has_more_elements( crt_php_array );
                     zend_hash_move_forward( crt_php_array ) ) {

                int             crt_type;
                char*            crt_key;
                unsigned int    crt_keylen;
                unsigned long   crt_idx;
                zval**            crt_ppzval;//warning
                void*           crt_zval_temp = NULL;

                crt_type = zend_hash_get_current_key_ex( crt_php_array, &crt_key, &crt_keylen, &crt_idx, 0, NULL );

                if ( zend_hash_get_current_data( crt_php_array, &crt_zval_temp ) == FAILURE ) {
                    /* Should never actually fail
                    * since the key is known to exist. */
                    continue;
                }
                crt_ppzval = ( zval** )crt_zval_temp;
                if ( IS_ARRAY != Z_TYPE_PP( ppzval ) ) {
                    throw std::string( "Invalid argument type." );
                }

                switch ( pass_count ) {
                    case 0:
                        if ( IS_STRING != Z_TYPE_PP( ppzval ) ) {
                            throw std::string( "Invalid argument type." );
                        } else {
                            crt_val.first = Z_STRVAL_PP( ppzval );
                        }
                        break;
                    case 1: {
                        crt_val.second = *val_zval( *ppzval ).get_Value();//TODO: make sure there is a copy construcotr here
                    }
                    break;
                    default:
                        throw std::string( "Invalid argument type." );
                }

                pass_count++;
            }

            result.push_back( crt_val );
        }
    }
private:

    Value* zval2val( zval* argZval ) {

        Value* ret_value = NULL;

        switch ( Z_TYPE_P( argZval ) ) {
            case IS_NULL: {
                ret_value = new Value();
            }
            break;
            case IS_BOOL:
                if ( Z_BVAL_P( argZval ) ) {
                    ret_value = new Value( true );
                } else {
                    ret_value = new Value( false );
                }
                break;
            case IS_LONG:
                ret_value = new Value( ( double )Z_LVAL_P( argZval ) );
                break;
            case IS_DOUBLE:
                ret_value = new Value( Z_DVAL_P( argZval ) );
                break;
            case IS_STRING:
                ret_value = new Value( Z_STRVAL_P( argZval ) );
                break;
            case IS_ARRAY: {
                HashTable*                                      php_array = Z_ARRVAL_P( argZval );
                WorksheetElement::value_type::value_array_type  wss_array;

                for (    zend_hash_internal_pointer_reset( php_array );
                         SUCCESS == zend_hash_has_more_elements( php_array );
                         zend_hash_move_forward( php_array ) ) {

                    int             type;
                    char*            key;
                    unsigned int    keylen;
                    unsigned long   idx;
                    zval**            ppzval;//warning
                    void*           zval_temp = NULL;

                    type = zend_hash_get_current_key_ex( php_array, &key, &keylen, &idx, 0, NULL );

                    if ( zend_hash_get_current_data( php_array, &zval_temp ) == FAILURE ) {
                        /* Should never actually fail
                        * since the key is known to exist. */
                        continue;
                    }
                    ppzval = ( zval** )zval_temp;

                    Value* crt = zval2val( *ppzval );
                    if ( NULL == ret_value ) {
                        ret_value = new Value( crt->type );
                    }

                    ret_value->array->push_back( *crt );
                    delete ret_value;

                }

            }
            break;
            case IS_OBJECT:
                throw std::string( "Cannot store complex objects" );
            case IS_RESOURCE:
                throw std::string( "Cannot store resources" );
            default:
                throw std::string( "Internal error" );
        }
        return ret_value;
    }
    zval* val2zval( Value* argValue ) {

        zval* ret_zval;
        ALLOC_INIT_ZVAL( ret_zval );

        switch ( argValue->type ) {

            case WorksheetElement::value_type::type_boolean:
                ZVAL_BOOL( ret_zval, argValue->get_numeric() );
                break;
            case WorksheetElement::value_type::type_numeric:
                ZVAL_DOUBLE( ret_zval, argValue->get_numeric() );
                break;
            case WorksheetElement::value_type::type_string:
                ZVAL_STRING( ret_zval, const_cast<char*>( argValue->get_string().c_str() ), 1 )
                break;
            case WorksheetElement::value_type::type_array: {
                array_init( ret_zval );
                for (
                    Value::value_array_type::iterator i = argValue->array->begin();
                    i != argValue->array->end();
                    i++ ) {

                    add_next_index_zval( ret_zval, val2zval( &( *i ) ) );
                    //TODO: call destroy here? Who has the ownership?
                }
            }
            break;
            default:
                ZVAL_NULL( ret_zval );
                break;
        }

        return ret_zval;
    }
private:
    //computed values. allocated here
    zval*   m_zval;
    Value*  m_Value;

    //arguments. allocated elsewere
    zval*   m_zval_arg;
    Value*  m_Value_arg;
};

#endif //_PHPBVALZVALCONVERSION
