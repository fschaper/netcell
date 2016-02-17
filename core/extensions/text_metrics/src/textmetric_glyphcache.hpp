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

#ifndef __TEXTMETRIC_GLYPHCACHE_H__
#define __TEXTMETRIC_GLYPHCACHE_H__

#include <boost/thread.hpp>

#include "textmetric_types.hpp"

namespace textmetric_internal
{
    // Glyph cache subclass (functional unit)
    class FTGlyphCache
    {
    private:
        // Glyphset cache
        gldescmapper_t m_Cache;

        // Destruction code
        void destructor();

        // Mutice
        boost::mutex m_CacheLock; // Lock m_Cache access

    public:
        FTGlyphCache() {
        }

        virtual ~FTGlyphCache() throw () {
            try {
                destructor();
            } catch ( ... ) {
            }
        }

        // Just check whether a glyph set is available already,
        // and render it if not
        void SpawnGlyphSet( const styledesc_t& stde,
                            unsigned int xdpi, unsigned int ydpi );

        void AddGlyphs( const styledesc_t& stde,
                        unsigned int xdpi, unsigned int ydpi, const std::vector< unsigned int >& new_chars );

        // Get the glyphset for a stylemap
        const glyphset_t* GetGlyphSet( const styledesc_t& stde );
    };
}; // namespace textmetric_internal

#endif //__TEXTMETRIC_GLYPHCACHE_H__
