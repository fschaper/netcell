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

#include "precompiled_header.hpp"
#include "wss/storage_rotation.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/regex.hpp>
#   include <boost/lexical_cast.hpp>
#endif

filename_rotation_iterator::filename_rotation_iterator( const boost::filesystem::path& filename, unsigned int max_rotation_id /*= 10*/ )
    : m_base_name( filename.native_file_string() )
    , m_max_rotation_id( max_rotation_id )
    , m_rotation_id( 0 )
{
    if ( m_max_rotation_id == 0 ) {
        throw std::exception();
    }

    static const boost::regex extract_rotation_id( "(.*?)\\.~(\\d+)$", boost::match_perl );
    boost::smatch results;
    bool success = boost::regex_match( m_base_name, results, extract_rotation_id );
    if ( success ) {
        m_rotation_id = boost::lexical_cast<int>( results[ 2 ].str() );
        m_base_name = results[ 1 ].str();
    }
}

filename_rotation_iterator& filename_rotation_iterator::operator ++()
{
    ++m_rotation_id;
    return *this;
}

filename_rotation_iterator& filename_rotation_iterator::operator --()
{
    if ( m_rotation_id ) {
        --m_rotation_id;
    }
    return *this;
}

boost::filesystem::path filename_rotation_iterator::get() const
{
    return boost::filesystem::path( m_base_name + ".~" + boost::lexical_cast<std::string>( m_rotation_id % m_max_rotation_id ) );
}

unsigned int filename_rotation_iterator::iteration_count()
{
    return m_rotation_id / m_max_rotation_id;
}

bool filename_rotation_iterator::is_first() const
{
    return m_rotation_id == 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

file_rotation::file_rotation( unsigned int max_rotation_id /*= 10 */ )
    : m_max_rotation_id( max_rotation_id )
{}

void file_rotation::rotate( const boost::filesystem::path& filename )
{
    filename_rotation_iterator fnr( filename, m_max_rotation_id );

    const std::string& temp = filename.string() + ".~0";
    if ( !boost::filesystem::exists( boost::filesystem::path( temp ) ) ) {
        //        boost::filesystem::copy_file( filename, temp );
        return;
    }

    // find the last file in the list of backup files
    while ( boost::filesystem::exists( fnr.get() ) && ! fnr.iteration_count() ) {
        ++fnr;
    }

    // delete the oldest file if we reached the max.
    // number of backups
    if ( fnr.iteration_count() ) {
        --fnr;
        boost::filesystem::remove( fnr.get() );
    }

    // rename all backup copy's
    while ( ! fnr.is_first() ) {
        boost::filesystem::path to( fnr.get() );
        boost::filesystem::path from( ( --fnr ).get() );
        boost::filesystem::rename( from, to );
    }
}

void file_rotation::remove( const boost::filesystem::path& filename )
{
    // remove the file at the specified location
    filename_rotation_iterator fnr( filename, m_max_rotation_id );
    boost::filesystem::remove( fnr.get() );

    // rename all previous files to fill the gap (if any)
    boost::filesystem::path previous( fnr.get() );
    while ( boost::filesystem::exists( ( ++fnr ).get() ) ) {
        boost::filesystem::rename( fnr.get(), previous );
        previous = fnr.get();
    }
}

