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
//YLS: RELOCATED HERE

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "textmetric_glyphcache.hpp"

#include "textmetric_routines.hpp"
#include "textmetric_enums.hpp"
#include "textmetric_constants.hpp"
#include "textmetric_ftmgr.hpp"

namespace textmetric_internal
{

    void FTGlyphCache::destructor()
    {
        // Remove all items from cache
        gldescmapper_c iter = m_Cache.begin();
        gldescmapper_c iter_e = m_Cache.end();

        for ( ; iter != iter_e; ++iter ) {
            glyphset_t* data = ( *iter ).second;
            delete data;
        }

        m_Cache.clear();
    }

    // Just check whether a glyph set is available already,
    // and render it if not
    void FTGlyphCache::SpawnGlyphSet( const styledesc_t& stde,
                                      unsigned int xdpi, unsigned int ydpi )
    {
        glyphset_t* ngset = NULL;

        // Lock the glyph cache in any case
        mutexlock_t cachelock( m_CacheLock );

        gldescmapper_c testset = m_Cache.find( stde );
        bool have_this_style = testset != m_Cache.end();
        if ( have_this_style ) {
            if ( NULL != testset->second->at( xdpi, ydpi ) ) {
                // Do nothing if the set exists already
                return;
            }

            ngset = const_cast<glyphset_t*>( testset->second );
        } else {
            // Allocate the new glyph set and initialize it
            ngset = new glyphset_t;
        }

        // This was not a quick find, so some calculations are
        // to be done. Lock the engine now.
        mutexlock_t enginelock( FTMgr::m_Instance_->m_EngineLock );

        // No map parameter checking here. The map is cooked.

        // Build the set

        // First, make weight and style available.
        // Assume a bold one if weight >= 700
        // Note: "bold" is a WEIGHT and _not_ a style! See CSS2 spec.
        FT_Long searchstyle = 0;

        int style = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTSTYLE] );
        int weight = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTWEIGHT] );
        int size = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTSIZE] );

        if ( style == FONTSTYLE_ITALIC ) {
            searchstyle |= FT_STYLE_FLAG_ITALIC;
        }

        if ( weight >= FONTWEIGHT_700 ) {
            searchstyle |= FT_STYLE_FLAG_BOLD;
        }

        // Get the list of all possible font families. We choose
        // the first one that is available.
        strvec_t fams;
        std::string splitworkaround = ConstMapFetch( stde )[STDE_FONTFAMILY];
        boost::algorithm::split( fams, splitworkaround, boost::algorithm::is_from_range( ',', ',' ) );

        strvec_c iter = fams.begin();
        strvec_c iter_e = fams.end();

        // Final face ID
        const faceid_t* theface = NULL;

        for ( ; iter != iter_e; ++iter ) {
            // Ignore "no match" exceptions - we have others to come
            try {
                theface = FTMgr::m_Instance_->m_FacesCache.GetBestMatchingFaceID(
                              ( *iter ), searchstyle );

                // theface is valid -> we're done
                if ( theface ) {
                    break;
                }
            } catch ( text_metric_exception ) {
                // Ok, then try the next one
                continue;
            } // Throw up all other exception types
        }

        // Now, if there's not a single match, except
        if ( !theface )
            throw text_metric_fontfamilynotfound_exception(
                "None of the given font-families is available" );

        // We do not support mixing glyphs from various fonts
        // while rendering the final string. If the first found
        // font does not contain a particular glyph, this slot
        // stays unfilled. It is OK here and will result in an
        // exception if the bounding box for an invalid slot is
        // to be calculated later.

        // Get the global sizer for some parameters first
        FTC_ScalerRec sr;
        memset( &sr, 0, sizeof( FTC_ScalerRec ) );

        // The const_cast<> is OK -> FT will not touch the handle
        sr.face_id = const_cast<faceid_t*>( theface );
        sr.width = size * 64; // 1/64th points
        sr.height = sr.width;
        sr.pixel = 0; // Interpret as points
        sr.x_res = xdpi;
        sr.y_res = ydpi;

        FT_Size thesize;
        if ( FTC_Manager_LookupSize( FTMgr::m_Instance_->m_FTCManager, &sr, &thesize ) ) {
            throw text_metric_internalerror_exception( "Cannot load sizer" );
        }

        // Get the char-to-glyph mapping table for the face
        chartoglyph_t* cgm =
            const_cast< chartoglyph_t* >( FTMgr::m_Instance_->m_FacesCache.GetCharToGlyphMap( theface ) );
        std::map< unsigned int, unsigned int >* glyphidx
        = const_cast< std::map< unsigned int, unsigned int >* >( cgm->at( xdpi, ydpi ) );

        glyphset_t::scaled_data* data = ngset->register_scale( xdpi, ydpi );

        // Set global parameters
        FT_Face ft = FTMgr::m_Instance_->m_FacesCache.GetCachedFace( theface );
        data->linereserve   = ( FT_MulFix( ft->ascender - ft->descender, thesize->metrics.y_scale ) >> 6 );
        //  data->linestep      = (thesize->metrics.height >> 6);
        //YLS:  Move to line spacing, As there is no UI support in it, default to excel: Double spacing.
        //      This is exactly one line of empty text between two consecutive lines
        data->linestep      = data->linereserve;

        data->x_ppem = ft->size->metrics.x_ppem;

        //        FT_Size ft_size;
        //        FT_New_Size( ft, &ft_size );

        //        FT_Set_Pixel_Sizes(

        //        FT_Done_Size( ft_size );


        //        ft->units_per_EM

        // Underlining position and thickness must be scaled!
        data->underline_position =
            ( FT_MulFix( ft->underline_position, thesize->metrics.y_scale ) >> 6 );
        data->underline_thickness =
            ( FT_MulFix( ft->underline_thickness, thesize->metrics.y_scale ) >> 6 );

        //Copy all glyphs (in scaled version)
        for ( chartoglyph_t::glyphidx_c i = glyphidx->begin(); i != glyphidx->end(); i++ ) {
            FT_Glyph glyph;
            FTC_Node node;
            gscharinfo_t crt;

            if ( FTC_ImageCache_LookupScaler( FTMgr::m_Instance_->m_FTCImageCache, &sr,
                                              FT_LOAD_RENDER, i->second, &glyph, &node ) ) {
                crt.isvalid = false;

                if ( node ) {
                    FTC_Node_Unref( node, FTMgr::m_Instance_->m_FTCManager );
                }

                continue;
            }

            // Calculate the bounding box for the glyph and save the data
            FT_BBox bbox;
            FT_Glyph_Get_CBox( glyph, FT_GLYPH_BBOX_PIXELS, &bbox );

            // Copy result
            crt.isvalid = true;
            crt.glyph_bbox = bbox;
            crt.advance = ( glyph->advance.x >> 16 );

            data->data[i->first] = crt;

            // Allow the cache to remove the scaler
            FTC_Node_Unref( node, FTMgr::m_Instance_->m_FTCManager );
        }

        if ( !have_this_style ) {
            // Finally, add glyph set to cache
            m_Cache[stde] = ngset;
        }
    }

    void FTGlyphCache::AddGlyphs( const styledesc_t& stde,
                                  unsigned int xdpi, unsigned int ydpi, const std::vector< unsigned int >& new_chars )
    {
        gldescmapper_c ngset;
        // Lock the glyph cache in any case
        mutexlock_t cachelock( m_CacheLock );

        // the set should already be in the cache. we only add new glyphs
        ngset = m_Cache.find( stde );
        if ( ngset == m_Cache.end() ) {
            return;//this should be called with the face already in the cache
        }

        // This was not a quick find, so some calculations are
        // to be done. Lock the engine now.
        mutexlock_t enginelock( FTMgr::m_Instance_->m_EngineLock );

        // No map parameter checking here. The map is cooked.

        // Build the set

        // First, make weight and style available.
        // Assume a bold one if weight >= 700
        // Note: "bold" is a WEIGHT and _not_ a style! See CSS2 spec.
        FT_Long searchstyle = 0;

        int style = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTSTYLE] );
        int weight = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTWEIGHT] );
        int size = boost::lexical_cast<int>( ConstMapFetch( stde )[STDE_FONTSIZE] );

        if ( style == FONTSTYLE_ITALIC ) {
            searchstyle |= FT_STYLE_FLAG_ITALIC;
        }

        if ( weight >= FONTWEIGHT_700 ) {
            searchstyle |= FT_STYLE_FLAG_BOLD;
        }

        // Get the list of all possible font families. We choose
        // the first one that is available.
        strvec_t fams;
        std::string splitworkaround = ConstMapFetch( stde )[STDE_FONTFAMILY];
        boost::algorithm::split( fams, splitworkaround, boost::algorithm::is_from_range( ',', ',' ) );

        strvec_c iter = fams.begin();
        strvec_c iter_e = fams.end();

        // Final face ID
        const faceid_t* theface = NULL;

        for ( ; iter != iter_e; ++iter ) {
            // Ignore "no match" exceptions - we have others to come
            try {
                theface = FTMgr::m_Instance_->m_FacesCache.GetBestMatchingFaceID(
                              ( *iter ), searchstyle );

                // theface is valid -> we're done
                if ( theface ) {
                    break;
                }
            } catch ( text_metric_exception ) {
                // Ok, then try the next one
                continue;
            } // Throw up all other exception types
        }

        // Now, if there's not a single match, except
        if ( !theface )
            throw text_metric_fontfamilynotfound_exception(
                "None of the given font-families is available" );

        // We do not support mixing glyphs from various fonts
        // while rendering the final string. If the first found
        // font does not contain a particular glyph, this slot
        // stays unfilled. It is OK here and will result in an
        // exception if the bounding box for an invalid slot is
        // to be calculated later.

        // Allocate the new glyph set and initialize it


        // Get the global sizer for some parameters first
        FTC_ScalerRec sr;
        memset( &sr, 0, sizeof( FTC_ScalerRec ) );

        // The const_cast<> is OK -> FT will not touch the handle
        sr.face_id = const_cast<faceid_t*>( theface );
        sr.width = size * 64; // 1/64th points
        sr.height = sr.width;
        sr.pixel = 0; // Interpret as points
        sr.x_res = xdpi;
        sr.y_res = ydpi;

        FT_Size thesize;
        if ( FTC_Manager_LookupSize( FTMgr::m_Instance_->m_FTCManager, &sr, &thesize ) ) {
            throw text_metric_internalerror_exception( "Cannot load sizer" );
        }

        // Get the char-to-glyph mapping table for the face.
        // No need to lock. After all the entire engine is locked.
        chartoglyph_t* cgm =
            const_cast< chartoglyph_t* >( FTMgr::m_Instance_->m_FacesCache.GetCharToGlyphMap( theface ) );
        std::map< unsigned int, unsigned int >* glyphidx
        = const_cast< std::map< unsigned int, unsigned int >* >( cgm->at( xdpi, ydpi ) );

        FT_Face idxface;

        if ( FTC_Manager_LookupFace( FTMgr::m_Instance_->m_FTCManager, sr.face_id, &idxface ) ) {
            return;
        }

        glyphset_t::scaled_data* data = ngset->second->at( xdpi, ydpi );

        for ( std::vector< unsigned int >::const_iterator i = new_chars.begin(); i != new_chars.end(); i++ ) {
            FT_Glyph glyph;
            FTC_Node node;
            gscharinfo_t crt;
            FT_UInt idx = FT_Get_Char_Index( idxface, *i );

            //this is mantained just for possible future scalability.
            //in fact, this structure only helped in creating the ASCII part of the glyph.
            //who knows? sometime, someone might expect this structure to be in synch with
            //the glyph set
            ( *glyphidx )[*i] = idx;

            if ( FTC_ImageCache_LookupScaler( FTMgr::m_Instance_->m_FTCImageCache, &sr,
                                              FT_LOAD_RENDER, idx, &glyph, &node ) ) {
                crt.isvalid = false;

                if ( node ) {
                    FTC_Node_Unref( node, FTMgr::m_Instance_->m_FTCManager );
                }

                continue;
            }

            // Calculate the bounding box for the glyph and save the data
            FT_BBox bbox;
            FT_Glyph_Get_CBox( glyph, FT_GLYPH_BBOX_PIXELS, &bbox );

            // Copy result
            crt.isvalid = true;
            crt.glyph_bbox = bbox;
            crt.advance = ( glyph->advance.x >> 16 );

            //Add to the map
            data->data[*i] = crt;

            // Allow the cache to remove the scaler
            FTC_Node_Unref( node, FTMgr::m_Instance_->m_FTCManager );
        }

    }


    const glyphset_t* FTGlyphCache::GetGlyphSet( const styledesc_t& stde )
    {
        // Get a copy of the in-cache glyph set

        // Lock the cache
        mutexlock_t cachelock( m_CacheLock );

        gldescmapper_c iter = m_Cache.find( stde );

        // Should not happen as SpawnGlyphSet() is in code path before
        if ( iter == m_Cache.end() ) {
            throw text_metric_internalerror_exception( "glyphset_t not in cache" );
        }

        return ( *iter ).second;
    }

}; // namespace textmetric_internal
