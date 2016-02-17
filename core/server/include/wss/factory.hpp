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

#include <wss/i_createable.hpp>
#include <wss/creation_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/shared_ptr.hpp>
#   include <memory>
#   include <string>
#   include <stdexcept>
#   include <map>
#endif

#ifdef WIN32
#   pragma warning( disable : 4290 )
#endif // WIN32

/*!
 * \brief
 * template class for an generic factory based on creator objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
typename base_T
, typename indentifier_T = std::string
, typename result_T = std::auto_ptr<base_T>
>
class factory
{
public:
    typedef result_T result_type;
    typedef base_T base_type;
    typedef indentifier_T identifier_type;
    typedef i_createable<result_type> creator_base_type;
    typedef boost::shared_ptr<creator_base_type > shared_creator_type;

    /*!
     * \brief
     * create the object by passed identifier.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    result_type create( const identifier_type& type ) const throw( creation_exception );

    /*!
     * \brief
     * register a creator for a given identifier.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void register_creator( const identifier_type& type, const shared_creator_type& creator );

private:
    typedef std::map<identifier_type, shared_creator_type > creator_map_type;
    creator_map_type m_creator_map;
};

template
<
typename base_T
, typename indentifier_T
, typename result_T >
typename factory<base_T, indentifier_T, result_T>::result_type factory<base_T, indentifier_T, result_T>::create( const identifier_type& type ) const throw( creation_exception )
{
    typename creator_map_type::const_iterator it( m_creator_map.find( type ) );
    if ( it == m_creator_map.end() ) {
        throw creation_exception();
    }
    return ( *it ).second->create();
}

template
<
typename base_T
, typename indentifier_T
, typename result_T
>
void factory<base_T, indentifier_T, result_T>::register_creator( const identifier_type& type, const shared_creator_type& creator )
{
    typename creator_map_type::const_iterator it( m_creator_map.find( type ) );
    assert( it == m_creator_map.end() );
    m_creator_map[ type ] = creator;
}

