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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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
# include <vector>
#endif

/*!
 * \brief
 * allows for read/write access to std::vector<char> types.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class vector_io_device
{
    typedef std::vector<char> buffer_type;
public:
    enum seek_type { seek_current, seek_beginning, seek_end };

    typedef buffer_type::size_type size_type;

    /*!
     * \brief
     * constructor
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    vector_io_device();

    /*!
     * \brief
     * constructor
     *
     * assign the passed vector as input/output device.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    vector_io_device( buffer_type* buffer );

    /*!
     * \brief
     * open the passed buffer as the new input/output device.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void open( buffer_type* buffer );

    /*!
     * \brief
     * close the passed buffer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void close();

    /*!
     * \brief
     * returns true when a buffer is assigned and ready for
     * read/write operations.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_open() const;

    /*!
     * \brief
     * returns true when the read cursor reaches the end of
     * the buffer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool eof() const;

    /*!
     * \brief
     * write data to the buffer.
     *
     * moved the write cursor to CURRENT_POSITION + SIZE
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type write( const char* ptr, size_type size );

    /*!
     * \brief
     * read from the buffer.
     *
     * moved the read cursor to CURRENT_POSITION + SIZE
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type read( char* buffer, size_type size );

    /*!
     * \brief
     * current position of the write cursor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_t tellp() const;

    /*!
     * \brief
     * set the write cursor position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void seekp( int position, seek_type seek );

    /*!
     * \brief
     * current position of the read cursor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_t tellg() const;

    /*!
     * \brief
     * set the read cursor position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void seekg( int position, seek_type seek );

    /*!
     * \brief
     * get the absolute size of the buffer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    size_type size() const;

    /*!
     * \brief
     * truncate the buffer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void clear();

private:
    buffer_type* m_buffer;
    size_t m_read_cursor;
    size_t m_write_cursor;
    bool m_fail;
};

