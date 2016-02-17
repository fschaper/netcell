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

template<class serializer_T, class unserializer_T>
key_value_set<serializer_T, unserializer_T>::key_value_set()
{}

template<class serializer_T, class unserializer_T>
key_value_set<serializer_T, unserializer_T>::key_value_set( const ci_key_value_map_type& m )
    : m_map( m )
{}

template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::add( const std::string& key, const std::string& value )
{
    const std::string trimmed_key( boost::trim_copy( key ) );
    m_map.insert( std::make_pair( convert_utf8_ci( trimmed_key ), value ) );
}

template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::add( const key_type& key, const value_type& value )
{
    m_map.insert( std::make_pair( key , value ) );
}


template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::erase( const key_type& key )
{
    m_map.erase( key );
}

template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::combine( const key_value_set& other )
{
    foreach( const pair_type & p, other ) {
        add( convert_utf8_ci( p.first ), p.second );
    }
}

template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::clear()
{
    m_map.clear();
}

template<class serializer_T, class unserializer_T>
bool key_value_set<serializer_T, unserializer_T>::empty() const
{
    return m_map.empty();
}

template<class serializer_T, class unserializer_T>
typename key_value_set<serializer_T, unserializer_T>::const_iterator key_value_set<serializer_T, unserializer_T>::begin() const
{
    return m_map.begin();
}

template<class serializer_T, class unserializer_T>
typename key_value_set<serializer_T, unserializer_T>::const_iterator key_value_set<serializer_T, unserializer_T>::end() const
{
    return m_map.end();
}

template<class serializer_T, class unserializer_T>
void key_value_set<serializer_T, unserializer_T>::swap( key_value_set& other )
{
    m_map.swap( other.m_map );
}

template<class serializer_T, class unserializer_T>
bool key_value_set<serializer_T, unserializer_T>::operator ==( const key_value_set& other ) const
{
    return m_map == other.m_map;
}

template<class serializer_T, class unserializer_T>
bool key_value_set<serializer_T, unserializer_T>::operator !=( const key_value_set& other ) const
{
    return !( m_map == other.m_map );
}

template<class serializer_T, class unserializer_T>
std::string key_value_set<serializer_T, unserializer_T>::serialize( const bool skip_empties/* = true*/ ) const
{
    return serializer_type::serialize( m_map, skip_empties );
}

template<class serializer_T, class unserializer_T>
key_value_set<serializer_T, unserializer_T> key_value_set<serializer_T, unserializer_T>::unserialize( const std::string& s )
{
    return key_value_set<serializer_T, unserializer_T>( unserializer_type::unserialize( s ) );
}

template<class serializer_T, class unserializer_T>
key_value_set<serializer_T, unserializer_T>& key_value_set<serializer_T, unserializer_T>::operator +=( const key_value_set& other )
{
    if ( &other == this ) {
        return *this;
    }

    foreach( const pair_type & p, other ) {
        if ( p.second.empty() ) {
            ci_key_value_map_type::iterator to_delete = m_map.find( p.first );
            if ( m_map.end() != to_delete ) {
                m_map.erase( to_delete );
            }
        } else {
            m_map[p.first] = p.second;
        }
    }

    return *this;
}
