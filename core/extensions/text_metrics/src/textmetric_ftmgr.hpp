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

// TextMetric library

// textmetric_ftmgr.hpp - Header for the Freetype2 manager


#ifndef BOOST_FILESYSTEM_VERSION
#define BOOST_FILESYSTEM_VERSION 2
#endif

#ifndef __TEXTMETRIC_FTMGR_H__
#define __TEXTMETRIC_FTMGR_H__

#include <list>
#include <set>
#include <algorithm>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H

#include "textmetric_impl.hpp"
#include "textmetric_types.hpp"
#include "textmetric_glyphcache.hpp"

namespace textmetric_internal
{

    //forward
    class FTGlyphCache;

    // Engine (automatic singleton) class FTMgr
    class FTMgr
    {
        friend class FTGlyphCache;
        // This is a singleton that manages itself, so I don't want
        // anyone else to create an instance of it ... thus private
        // Anyway, we can't live with a static-only version as we
        // need a "hook" for shutdown when the program ends as the
        // specification does not allow a InitLib() and ShutdownLib()
        // routine.
    private:
        FTMgr();
        virtual ~FTMgr() throw ();

        // Shutdown guard
        class FTMgrShutdownGuard
        {
        private:
            void destructor();

        public:
            virtual ~FTMgrShutdownGuard() throw ();
        };
        // Font faces cache subclass (functional unit).
        // Tries to load the best-matching font
        // for a given description. Also holds all font objects
        // in given paths.
        class FTFacesCache
        {
        private:
            // font filter
            std::vector< std::string >  m_font_filter;
            // Known files (each may contain several faces)
            fontfileset_t m_FontFiles;

            // List of used face IDs
            faceidlist_t m_FaceIDs;

            // Property detail mapping
            detailsmapper_t m_DM_FontFamily;

            // Mapping of face IDs to glyph indices for the face
            faceidglyidxmapper_t m_FaceIDToGlyphIndex;

            // Destruction code
            void destructor();

            // Cache the font file (if not already there)
            void cacheFontFile( const std::string& filename );

            // Cache a font face's details
            void cacheFaceDetails( FT_Face& face, faceid_t* faceid );

        public:
            FTFacesCache();
            virtual ~FTFacesCache() throw ();

            //sets the font filter
            void SetFontFilter( const std::vector< std::string >& fontlist ) {
                for ( std::vector< std::string >::const_iterator i = fontlist.begin(), e = fontlist.end(); i != e; i++ ) {
                    std::string crt = *i;
                    boost::to_lower( crt );
                    //              std::transform(crt.begin(), crt.end(), crt.begin(), boost::to_lower);
                    m_font_filter.push_back( crt );
                }
            }

            // Load all files from the given path (if not already loaded)
            void LoadFromPath( const boost::filesystem::path& np );

            // Get the best-matching FT_Face
            FT_Face GetBestMatchingFace( const std::string& family, FT_Long styleflags );

            // Get the best-matching faceid.
            // Note that this returns the handle itself (trusted siblings).
            // Do not return this handle to client code!
            const faceid_t* GetBestMatchingFaceID( const std::string& family, FT_Long styleflags );

            // Get a face from cache
            FT_Face GetCachedFace( const faceid_t* faceid );

            // Get the character-to-glyph mapping table for a face id.
            // Note that this returns the handle itself (FTGlyphCache is
            // a trusted sibling). Do not return the handle to client code!
            const chartoglyph_t* GetCharToGlyphMap( const faceid_t* fid ) const;
        };

        // Static instance
        static FTMgr* m_Instance_;

        // Fixed tables. Copied from what you see in
        // textmetric_tables.h
        static simapmap_t m_StylesTable_;
        static simapmap_t m_WeightsTable_;
        static simapmap_t m_TextDecorsTable_;

        // Mutice
        boost::mutex m_EngineLock; // Lock whole engine

        // Callback function for ID->FT_Face conversion
        static FT_Error ftcFaceRequester( FTC_FaceID faceid, FT_Library library,
                                          FT_Pointer request_data, FT_Face* aface );

        // Freetype library handle
        FT_Library m_FTLib;

        // Freetype cache manager
        FTC_Manager m_FTCManager;

        // Freetype image cache
        FTC_ImageCache m_FTCImageCache;

        // Faces cache
        FTFacesCache m_FacesCache;

        // Glyph cache
        FTGlyphCache m_GlyphCache;

        // Destructor code
        void destructor();

    public:
        // Yelling the FTMgr -> Make sure the singleton is initialized.
        static void Yell();

        // Build a style descriptor from a raw style map
        static void BuildDescriptor( const style_map_type& smt, styledesc_t& stde,
                                     bool& dounderline );

        // Create the "world" required to calculate a bounding box
        // for a given stylemap/descriptor. This means rendering the
        // glyph map of its best-matching font for the desired weight
        // and size (if not done already).
        // Returns the internal glyphset_t* as a void* handle.
        // xdpi and ypdi are the DPI-resolution of the renderer
        static void* CreateWorld( const styledesc_t& stde,
                                  unsigned int xdpi, unsigned int ydpi );

        static void AddGlyphs( const styledesc_t& stde,
                               unsigned int xdpi, unsigned int ydpi, const std::vector< unsigned int >& new_chars );

        // Set the font list
        static void RegisterFontList( const std::vector< std::string >& fontlist );

        // Add a new font path
        static void RegisterFontPath( const boost::filesystem::path& np );

        // Calculate the bounding box for a string
        static void GetBoundingBox( void* glhandle, const std::string& arg,
                                    bool dounderline, unsigned int xdpi, unsigned int ydpi, bounding_box& bb, unsigned int& x_ppem );
    };

}; // namespace textmetric_internal

#endif // __TEXTMETRIC_FTMGR_H__

