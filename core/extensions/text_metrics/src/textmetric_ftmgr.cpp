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

// textmetric_ftmgr.cpp - Freetype2 manager implamentation

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "textmetric_constants.hpp"
#include "textmetric_ftmgr.hpp"
#include "textmetric_routines.hpp"
#include "textmetric_tables.hpp"
#include "textmetric_types.hpp"
#include "textmetric_converter.hpp"

namespace textmetric_internal
{

    static const char* STDE_TEXTDECORATION = "text-decoration";
    static const char* INHERIT = "inherit";
    static const char* NORMAL = "normal";

    // Init static data
    FTMgr* FTMgr::m_Instance_ = NULL;
    simapmap_t FTMgr::m_StylesTable_;
    simapmap_t FTMgr::m_WeightsTable_;
    simapmap_t FTMgr::m_TextDecorsTable_;

    // FTMgr subclasses

    // FTMgrShutdownGuard
    void FTMgr::FTMgrShutdownGuard::destructor()
    {
        if ( m_Instance_ ) {
            delete m_Instance_;
            m_Instance_ = NULL;
        }
    }
    FTMgr::FTMgrShutdownGuard::~FTMgrShutdownGuard() throw ()
    {
        try {
            destructor();
        } catch ( ... ) { }
    }

    // FTFacesCache
    FTMgr::FTFacesCache::FTFacesCache()
    {
    }

    FTMgr::FTFacesCache::~FTFacesCache() throw ()
    {
        // Free all faces
        try {
            destructor();
        } catch ( ... ) { }
    }

    void FTMgr::FTFacesCache::destructor()
    {
        // Destroy the character to glyph index objects
        faceidglyidxmapper_c xiter = m_FaceIDToGlyphIndex.begin();
        faceidglyidxmapper_c xiter_e = m_FaceIDToGlyphIndex.end();

        for ( ; xiter != xiter_e; ++xiter ) {
            chartoglyph_t* data = ( *xiter ).second;
            delete data;
        }

        m_FaceIDToGlyphIndex.clear();

        // Destroy the faceid objects
        faceidlist_c iter = m_FaceIDs.begin();
        faceidlist_c iter_e = m_FaceIDs.end();

        for ( ; iter != iter_e; ++iter ) {
            delete ( *iter );
        }

        m_FaceIDs.clear();
    }

    void FTMgr::FTFacesCache::cacheFontFile( const std::string& filename )
    {
        // Do nothing if we already have it
        if ( m_FontFiles.count( filename ) == 0 ) {
            // Cache that file!

            // Build the slot 0 face ID first
            faceid_t* fid = new faceid_t;
            fid->filename = filename;
            fid->index = 0;

            // Try to "lookup" it in the cache. Of course, this will
            // fail and force the cache to load it.
            FT_Face id0;
            FT_Error error = FTC_Manager_LookupFace( m_Instance_->m_FTCManager, fid, &id0 );

            // Load failed. This might be a damaged file or not a font
            // file at all - remember, we scan each file in the directory,
            // perhaps also font files that can't be used with Freetype2
            // or other random garbage.
            // So DON'T consider this to be an error that should be thrown
            // up to client code!
            if ( error ) {
                delete fid;
                return;
            }

            // Could load the file. Add to list so we won't load this file again
            m_FontFiles.insert( filename );

            // Register the font't parameters in our own mapper
            cacheFaceDetails( id0, fid );

            // Some font formats allow several faces to be in a single
            // file. Get all of them.
            // We have index 0 already
            for ( int i = 1; i < id0->num_faces; i++ ) {
                faceid_t* nfid = new faceid_t;
                nfid->filename = filename;
                nfid->index = i;

                FT_Face idxface;

                error =
                    FTC_Manager_LookupFace( m_Instance_->m_FTCManager, nfid, &idxface );

                if ( error ) {
                    delete nfid;
                    continue;
                }

                // Add face details
                cacheFaceDetails( idxface, nfid );
            }
        }
    }

    void FTMgr::FTFacesCache::cacheFaceDetails( FT_Face& face, faceid_t* faceid )
    {
        // Add faceid to object list
        m_FaceIDs.push_back( faceid );

        // Build access cache
        fontdetails_t det;
        det.family = face->family_name;
        det.styleflags = face->style_flags;
        det.faceid = faceid;

        // Add to cache
        m_DM_FontFamily.insert( std::make_pair( det.family, det ) );

        // Cache the glyph indices for all 128 posible ASCII set
        chartoglyph_t* ctg = new chartoglyph_t;

        std::map< unsigned int, unsigned int >* glyphs
        = const_cast<std::map< unsigned int, unsigned int >*>( ctg->at( 0, 0 ) );

        for ( int i = 0; i < 128; i++ ) {
            ( *glyphs )[i] = FT_Get_Char_Index( face, i );
        }

        // Add to mapper
        m_FaceIDToGlyphIndex[faceid] = ctg;
    }

    FT_Face FTMgr::FTFacesCache::GetCachedFace( const faceid_t* faceid )
    {
        // Copying is cheap, it's a pointer...
        FT_Face rv;

        // Every face that is in the m_DM_xxx-cache *must* be
        // available from the cache manager. If not, we've got
        // a serious problem (should never happen)
        // The const_cast<> is OK -> FT doesn't touch the handle
        if ( FTC_Manager_LookupFace( m_Instance_->m_FTCManager,
                                     const_cast<faceid_t*>( faceid ), &rv ) ) {
            throw text_metric_internalerror_exception(
                "Cannot cache previously registerd face" );
        }

        return rv;
    }

    void FTMgr::FTFacesCache::LoadFromPath( const boost::filesystem::path& np )
    {
        // Scan the given directory for font files.

        // Engine must be fully locked for this
        mutexlock_t enginelock( m_Instance_->m_EngineLock );

        // By default, the iterator points to the end
        boost::filesystem::directory_iterator diter_e;

        std::vector< std::string >::iterator filter_end = m_font_filter.end();
        std::vector< std::string >::iterator filter_begin = m_font_filter.begin();

        for ( boost::filesystem::directory_iterator diter( np ); diter != diter_e; ++diter ) {
            if ( !boost::filesystem::is_directory( diter->status() ) ) {
                std::string crt = diter->path().leaf();
                std::string::size_type dot_pos = crt.find( "." );
                if ( dot_pos != std::string::npos ) {
                    crt = crt.substr( 0, dot_pos );
                }

                //std::transform(crt.begin(), crt.end(), crt.begin(), boost::to_lower);
                boost::to_lower( crt );

                bool found = false;
                for ( std::vector< std::string >::const_iterator i = filter_begin; i != filter_end; i++ ) {
                    if ( crt == *i ) {
                        found = true;
                        break;
                    }

                    if ( 0 == crt.find( *i ) ) {
                        found = true;
                        break;
                    }
                }
                if ( !found ) {
                    continue;
                }
                // Don't necessarily accept TTF only. Freetype will of course
                // not create a font objects if the directory contains random
                // garbage :)
                cacheFontFile( diter->path().string() );
            }
        }
    }

    FT_Face FTMgr::FTFacesCache::GetBestMatchingFace( const std::string& family,
                                                      FT_Long styleflags )
    {
        return GetCachedFace( GetBestMatchingFaceID( family, styleflags ) );
    }

    const faceid_t* FTMgr::FTFacesCache::GetBestMatchingFaceID( const std::string& family,
            FT_Long styleflags )
    {
        // Lookup this family name
        detailsmapper_pc mpairs = m_DM_FontFamily.equal_range( family );

        if ( mpairs.first == m_DM_FontFamily.end() ) {
            throw text_metric_fontfamilynotfound_exception( "Family not found" );
        }

        // Process all
        detailsmapper_c iter = mpairs.first;
        detailsmapper_c iter_e = mpairs.second;

        // We scan the whole list. If we find a perfect match (exact styleflag),
        // we use this one. Nevertheless, we also scan for a near match, that is,
        // a font that meets one of the possible style flags. We assume here that
        // bold has a higher match priority than italic. This means that if caller
        // request a BOLD | ITALIC font and we find a BOLD one and an ITALIC one,
        // we return the BOLD match.
        // This is nailed down for two flags. It there were more style flags,
        // a score table (sum of two lower flags counts more than one higher
        // flag) might be better, unless you still follow the assumption that any
        // higher priority flag counts more than any *sum* of lower priority flags.
        // In this case, simply adjust the value for "numbits".
        static const int numbits = 2;
        faceid_t* matchtable[numbits];

        memset( matchtable, 0, sizeof( matchtable ) );

        for ( ; iter != iter_e; ++iter ) {
            // Convenience
            const fontdetails_t& fd = ( *iter ).second;

            // Full match?
            if ( fd.styleflags == ( unsigned long )styleflags ) {
                return ( fd.faceid );
            }

            // Partial match?
            for ( int i = 0; i < numbits; i++ ) {
                if ( styleflags & fd.styleflags & ( 1 << numbits ) ) {
                    matchtable[numbits] = fd.faceid;    // Don't do this if using a scoretable!
                }
            }
        }

        // No perfect match. Check the matchtable and return the highest one
        // as a high match outperforms any number of low matches here
        for ( int i = ( numbits - 1 ); i >= 0; i-- ) {
            if ( matchtable[i] ) {
                return ( matchtable[i] );
            }
        }

        // Still no match? Ok, then ... the spec does not say we must except
        // if we don't find any style, so simply return the first font.
        iter = mpairs.first;
        return ( ( *iter ).second.faceid );
    }

    const chartoglyph_t* FTMgr::FTFacesCache::GetCharToGlyphMap( const faceid_t* fid ) const
    {
        return ConstMapFetch( m_FaceIDToGlyphIndex )[fid];
    }

    // FTMgr

    FTMgr::FTMgr()
    {
        // Build fast tables from static tables
        SimapToSimapmap( FontStylesMap, m_StylesTable_ );
        SimapToSimapmap( FontWeightsMap, m_WeightsTable_ );
        SimapToSimapmap( TextDecorationsMap, m_TextDecorsTable_ );

        // Initilize the Freetype2 library
        if ( FT_Init_FreeType( &m_FTLib ) ) {
            throw text_metric_internalerror_exception( "Cannot init Freetype2 library" );
        }

        // Init FT's cache
        if ( FTC_Manager_New( m_FTLib, 0, 0, 0, ftcFaceRequester, NULL, &m_FTCManager ) ) {
            // Shutdown library!
            FT_Done_FreeType( m_FTLib );
            throw text_metric_internalerror_exception( "Cannot init FTC cache manager" );
        }

        // Init FT's image cache
        if ( FTC_ImageCache_New( m_FTCManager, &m_FTCImageCache ) ) {
            // Shuddown cache and library!
            FTC_Manager_Done( m_FTCManager );
            FT_Done_FreeType( m_FTLib );
            throw text_metric_internalerror_exception( "Cannot init FTC image cache" );
        }
    }

    FTMgr::~FTMgr() throw ()
    {
        // Need to wrap this in a function call
        try {
            destructor();
        } catch ( ... ) { }
    }

    FT_Error FTMgr::ftcFaceRequester( FTC_FaceID faceid, FT_Library library,
                                      FT_Pointer request_data, FT_Face* aface )
    {
        // Locate the given file and load the FT_Face from it.
        // faceid is a pointer to a faceid_t struct.
        faceid_t* dptr = static_cast<faceid_t*>( faceid );

        // Should never happen, but...
        if ( !dptr ) {
            return -1;
        }

        return FT_New_Face( library, dptr->filename.c_str(), dptr->index, aface );
    }

    void FTMgr::destructor()
    {
        // Destroy FT objects
        FTC_Manager_Done( m_FTCManager );
        FT_Done_FreeType( m_FTLib );

        // Note: Image cache doesn't seem to have a shutdown routine
    }

    void FTMgr::Yell()
    {
        // Make sure it will shutdown sometime
        static FTMgrShutdownGuard guard;

        // And yes, create it :)
        if ( !m_Instance_ ) {
            m_Instance_ = new FTMgr();
        }
    }

    void FTMgr::BuildDescriptor( const style_map_type& smt, styledesc_t& stde,
                                 bool& dounderline )
    {
        // "Cook" the style map so we have something that
        // is equal across several differntly formed style_map_type
        // fills which map to the same glyphset. This will also
        // detect bad input in the style_map_type.
        std::string tmp;

        // Cook style.
        // Format: "normal | italic | oblique | inherit"
        // We map "oblique" to "italic" as Freetype2 can't handle this.
        // "inherit" in unsupported and will retult in exception.

        // First lowercase/trim all...
        tmp = boost::algorithm::to_lower_copy( ConstMapFetch( smt )[STDE_FONTSTYLE] );
        boost::algorithm::trim( tmp );

        // No font style given -> Assume "normal"
        if ( tmp.empty() ) {
            tmp = NORMAL;
        }

        // Lookup in table. SimapmapLookup() will automatically
        // return "0" if it does not exist ... and 0 is the
        // _INVALID marker in all tables :)
        int tmpi = SimapmapLookup( m_StylesTable_, tmp );

        if ( tmpi == FONTSTYLE_INVALID ) {
            throw text_metric_malformedstyle_exception( "font-style: Invalid font style" );
        }

        // Add to the style descriptor
        stde[STDE_FONTSTYLE] = boost::lexical_cast<std::string>( tmpi );

        // Cook weight
        tmp = boost::algorithm::to_lower_copy( ConstMapFetch( smt )[STDE_FONTWEIGHT] );
        boost::algorithm::trim( tmp );

        // No weight given -> Assume "normal"
        if ( tmp.empty() ) {
            tmp = NORMAL;
        }

        tmpi = SimapmapLookup( m_WeightsTable_, tmp );

        if ( tmpi == FONTWEIGHT_INVALID ) {
            throw text_metric_malformedstyle_exception( "font-weight: Invalid font weight" );
        }

        stde[STDE_FONTWEIGHT] = boost::lexical_cast<std::string>( tmpi );

        // Cook size
        // Format: <positive integer>pt
        // We don't accept any other format as there's no context info

        // Make it a pure lowercased thing
        tmp = boost::algorithm::to_lower_copy( ConstMapFetch( smt )[STDE_FONTSIZE] );
        boost::algorithm::trim( tmp );

        // When stripping away "pt", it must be convertable to an
        // integer > 0.
        // Will accept it without the pt also :)
        tmp = boost::algorithm::replace_all_copy( tmp, "pt", "" );

        int fsize = 0;

        try {
            fsize = boost::lexical_cast<int>( tmp );
        } catch ( ... ) {
            fsize = 0;
        }

        if ( fsize <= 0 ) {
            throw text_metric_malformedstyle_exception( "font-size: Must be <uint>pt > 0" );
        }

        stde[STDE_FONTSIZE] = boost::lexical_cast<std::string>( fsize );

        // Get families
        // Format:
        // "[[<family-name>|<generic-family>],]*[<family-name>|<generic-family>]|inherit"
        // "inherit" is unsupported. It it appears alone, this will result in
        // an exception being thrown. Otherwise, it's ignored.
        tmp = ConstMapFetch( smt )[STDE_FONTFAMILY];

        // Do not lowercase anything for now, assume well-written names.
        // Tokenize (split at "," and remove all whitespace as well as ")
        strvec_t tokens;
        boost::algorithm::split( tokens, tmp, boost::algorithm::is_from_range( ',', ',' ) );
        const size_t mxs = tokens.size();

        for ( size_t i = 0; i < mxs; i++ ) {
            tokens[i] = boost::algorithm::replace_all_copy( tokens[i], "\"", "" );
            boost::algorithm::trim( tokens[i] );
        }

        // We can't take care about the "generic families" here as
        // we have no context and thus don't know about generic
        // families.

        // If it's only one and this is "inherit" -> except
        if ( mxs == 1 ) {
            if ( boost::algorithm::to_lower_copy( tokens[0] ) == INHERIT ) {
                throw text_metric_malformedstyle_exception(
                    "font-family: Cannot accept inherit as pure family description" );
            }
        } else if ( mxs == 0 ) {
            throw text_metric_malformedstyle_exception( "font-family: Need at lease one" );
        }

        // Pack the font family list back into the styledesc.
        // Priority stays alive.
        tmp.clear();
        for ( size_t i = 0; i < mxs; i++ ) {
            if ( i ) {
                tmp += ",";
            }

            tmp += tokens[i];
        }

        stde[STDE_FONTFAMILY] = tmp;

        // Cook text decoration
        // Ignore anything except "underline"
        tmp = ConstMapFetch( smt )[STDE_TEXTDECORATION];

        dounderline =
            ( SimapmapLookup( m_TextDecorsTable_, tmp ) == TEXTDECOR_UNDERLINE );
    }

    void* FTMgr::CreateWorld( const styledesc_t& stde, unsigned int xdpi, unsigned int ydpi )
    {
        // Make sure the glyph set exists.
        m_Instance_->m_GlyphCache.SpawnGlyphSet( stde, xdpi, ydpi );

        // Return the (internal) handle, casted to void*
        return static_cast<void*>( const_cast<glyphset_t*>( m_Instance_->m_GlyphCache.GetGlyphSet( stde ) ) );
    }

    void FTMgr::AddGlyphs( const styledesc_t& stde, unsigned int xdpi, unsigned int ydpi, const std::vector< unsigned int >& new_chars )
    {
        // Make sure the glyph set exists.
        m_Instance_->m_GlyphCache.AddGlyphs( stde, xdpi, ydpi, new_chars );
    }

    void FTMgr::RegisterFontList( const std::vector< std::string >& fontlist )
    {
        m_Instance_->m_FacesCache.SetFontFilter( fontlist );
    }

    void FTMgr::RegisterFontPath( const boost::filesystem::path& np )
    {
        // Must be Yell()ed already!
        m_Instance_->m_FacesCache.LoadFromPath( np );
    }

    void FTMgr::GetBoundingBox( void* glhandle, const std::string& arg,
                                bool dounderline, unsigned int xdpi, unsigned int ydpi, bounding_box& bb, unsigned int& x_ppem  )
    {
        // Init bounding box
        bb.height = 0;
        bb.width = 0;

        // The handle really is a glyphset_t*
        glyphset_t* gly = static_cast<glyphset_t*>( glhandle );
        glyphset_t::scaled_data* data = gly->at( xdpi, ydpi );
        x_ppem = data->x_ppem;

        // Convert windows newlines to UNIX newlines
        std::string unixarg = boost::algorithm::replace_all_copy( arg, "\r\n", "\n" );

        // Split the argument into lines
        strvec_t lines;
        boost::algorithm::split( lines, unixarg, boost::algorithm::is_from_range( '\n', '\n' ) );

        strvec_c iter = lines.begin();
        strvec_c iter_e = lines.end();

        bb.width = 0;
        for ( size_t curline = 0; iter != iter_e; ++iter, ++curline ) {
            // Readability
            const std::string& line = ( *iter );

            // Init horizontal position
            int curx = 0;

            // Iterate over string characters
            Converter convertor( line );
            {
                boost::mutex::scoped_lock   lock( data->lock );
                for ( Converter::conversion_iterator i = convertor.begin(); i != convertor.end(); ++i ) {
                    glyphset_t::data_c crt_i = data->data.find( *i );
                    if ( data->data.end() == crt_i ) {
                        throw text_metric_boxnotcalcable_exception( "Character not available" );
                    }

                    gscharinfo_t crt = crt_i->second;
                    if ( !crt.isvalid ) {
                        throw text_metric_boxnotcalcable_exception( "Character not available" );
                    }

                    // Advance position
                    curx += crt.advance;
                }
            }

            if ( ( int )bb.width < curx ) {
                bb.width = curx;
            }
        }

        bb.height = ( unsigned int )( data->linestep * ( lines.size() - 1 ) ) + data->linereserve - 1; //-1 here to adjust for a single pixel loss. possibly from the UI.
    }

}; // namespace textmetric_internal
