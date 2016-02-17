/*
 * Copyright (C) 2008 by Florian Stoehr <ich@florian-stoehr.de>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,  with  or
 * without  modification,  are permitted provided that the fol-
 * lowing conditions are met:
 *
 *  (1)   Redistributions of source code must retain the  above
 *        copyright  notice,  this  list  of conditions and the
 *        following disclaimer.
 *
 *  (2)   Redistributions in binary  form  must  reproduce  the
 *        above  copyright  notice, this list of conditions and
 *        the following disclaimer in the documentation  and/or
 *        other materials provided with the distribution.
 *
 *  (3)   All  advertising materials mentioning features or use
 *        of this software must display the following  acknowl-
 *        edgement: This product includes software developed by
 *        Florian Stoehr
 *
 *  (4)   The name of Florian Stoehr may not be used to endorse
 *        or  promote products derived from this software with-
 *        out specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY FLORIAN STOEHR  ''AS  IS''  AND
 * ANY  EXPRESS  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIM-
 * ITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FIT-
 * NESS  FOR  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT
 * SHALL FLORIAN STOEHR BE LIABLE  FOR  ANY  DIRECT,  INDIRECT,
 * INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO,  PROCUREMENT  OF  SUBSTITUTE
 * GOODS  OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSI-
 * NESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  LIA-
 * BILITY,  WHETHER  IN  CONTRACT,  STRICT  LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY  WAY  OUT
 * OF  THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSI-
 * BILITY OF SUCH DAMAGE.
 */

// TextMetric library implementation

// No config.h required.

#ifndef BOOST_FILESYSTEM_VERSION
#define BOOST_FILESYSTEM_VERSION 2
#endif

#include "textmetric_impl.hpp"

#include "textmetric_types.hpp"
#include "textmetric_ftmgr.hpp"
#include "textmetric_converter.hpp"
#include "textmetric_constants.hpp"
#include "textmetric_routines.hpp"

#include <boost/lexical_cast.hpp>

namespace textmetric_internal
{
    text_metric::text_metric( const style_map_type& smt, int xdpi, int ydpi )
    {
        m_xdpi = xdpi;
        m_ydpi = ydpi;

        // Make sure the Freetype2 manager is ready
        FTMgr::Yell();

        // Cook the style map type
        FTMgr::BuildDescriptor( smt, m_Stde, b_Underlined );

        // Generate all that is required in order to
        // calculate some bounding boxes for that descriptor
        // The glyph set is finally rendered then.
        // The returned void* really is a glyphset_t* but expressed
        // as an opaque type to that we can't fool around with it
        // on this level.
        m_GlyphSetHandle = FTMgr::CreateWorld( m_Stde, m_xdpi, m_ydpi );

        //text ident
        std::string tmp = ConstMapFetch( smt )[STDE_TEXTIDENT];

        if ( !tmp.empty() ) {
            //this was already validated to a number. it si silly as it is today.
            //TODO: better style cooking
            m_em = boost::lexical_cast< unsigned int >( tmp );
        } else {
            m_em = 0;
        }
    }

    text_metric::text_metric( const text_metric& cc )
    {
        doCC( cc );
    }

    text_metric::~text_metric() throw ()
    {
        // Nothing to do
    }

    void text_metric::doCC( const text_metric& cc )
    {
        // Copy in a locked manner. May safely except.

        // Don't just simply lock both mutice, as this will lead
        // to a race condition for the (rare) case when two
        // threads each call inst1 = inst2 / inst2 = inst1
        // concurrently.

        // Use a buffer variable and always lock only one of the
        // mutice.

        void* workhandle;
        bool workunderline;

        // Copy data from other object
        {
            mutexlock_t lg2( cc.m_Mutex );
            workhandle = cc.m_GlyphSetHandle;
            workunderline = cc.b_Underlined;
            m_xdpi = cc.m_xdpi;
            m_ydpi = cc.m_ydpi;
            m_Stde = cc.m_Stde;
        }

        // Update internal version
        {
            mutexlock_t lg1( m_Mutex );
            m_GlyphSetHandle = workhandle;
            b_Underlined = workunderline;
        }
    }

    bounding_box text_metric::get_bounding_box( const std::string& arg ) const
    {
        // Acquire a short lock on the mutex, and just copy the
        // pointer withing the lock slice. Then, the member variable
        // pointer may safely be overwritten and we can run the
        // bounding box calculation unlocked (and multithreaded).
        void* workhandle;
        bool workunderline;

        // Use new scope so lock is freed immediately
        {
            mutexlock_t lg( m_Mutex );
            workhandle = m_GlyphSetHandle;
            workunderline = b_Underlined;
        }

        //validate against possible characters misses in the cache
        validate_string( arg );

        // Now using the private copy
        bounding_box rv;
        unsigned int x_ppem;
        FTMgr::GetBoundingBox( workhandle, arg, workunderline, m_xdpi, m_ydpi, rv, x_ppem );
        if ( 0 != m_em ) {
            rv.width += ( m_em * x_ppem );
        }
        return rv;
    }

    void text_metric::validate_string( const std::string& arg ) const
    {
        std::vector< unsigned int > special_chars;
        Converter conv( arg );

        for ( Converter::conversion_iterator i = conv.begin(); i != conv.end(); ++i ) {
            if ( *i > 0x7F ) {
                special_chars.push_back( *i );
            }
        }

        if ( !special_chars.empty() ) {
            glyphset_t* gly = static_cast<textmetric_internal::glyphset_t*>( m_GlyphSetHandle );
            std::vector< unsigned int >::iterator i = special_chars.begin();

            glyphset_t::scaled_data* data = gly->at( m_xdpi, m_ydpi );
            {
                boost::mutex::scoped_lock   lock( data->lock );
                while ( i != special_chars.end() ) {
                    if ( data->data.end() != data->data.find( *i ) ) {
                        i = special_chars.erase( i );
                    } else {
                        i++;
                    }
                }
            }


            FTMgr::AddGlyphs( m_Stde, m_xdpi, m_ydpi, special_chars );
        }
    }


    void text_metric::set_font_list( const std::vector< std::string >& fontlist )
    {
        FTMgr::Yell();
        FTMgr::RegisterFontList( fontlist );
    }

    void text_metric::set_font_path( const boost::filesystem::path& fspath )
    {
        FTMgr::Yell();
        FTMgr::RegisterFontPath( fspath );
    }

    text_metric& text_metric::operator=( const text_metric& cc )
    {
        doCC( cc );

        return *this;
    }

};//namespace textmetric_internal
