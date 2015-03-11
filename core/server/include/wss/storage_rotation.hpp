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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/filesystem.hpp>
#   include <string>
#endif

/*!
 * \brief
 * filename rotation iterator
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class filename_rotation_iterator
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    filename_rotation_iterator( const boost::filesystem::path& filename, unsigned int max_rotation_id = 10 );

    /*!
     * \brief
     * iterate forward
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    filename_rotation_iterator& operator ++();

    /*!
     * \brief
     * iterate back
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    filename_rotation_iterator& operator --();

    /*!
     * \brief
     * gets the modified filename with ".~x" applied.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    boost::filesystem::path get() const;

    /*!
     * \brief
     * returns the current iteration id
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    unsigned int iteration_count();

    /*!
     * \brief
     * returns true when the iterator points to the '0' file
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_first() const;

private:
    std::string m_base_name;
    unsigned int m_max_rotation_id;
    unsigned int m_rotation_id;
};

/*!
 * \brief
 * rotate filenames on disk
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class file_rotation
{
public:
    file_rotation( unsigned int max_rotation_id = 10 );

    /*!
     * \brief
     * rotate all ".~*" files
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void rotate( const boost::filesystem::path& filename );

    /*!
     * \brief
     * remove all ".~*" files.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void remove( const boost::filesystem::path& filename );

private:
    unsigned int m_max_rotation_id;
};
