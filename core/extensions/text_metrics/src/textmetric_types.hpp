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

// textmetric_types.hpp - Internal types

#ifndef __TEXTMETRIC_TYPES_H__
#define __TEXTMETRIC_TYPES_H__

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/thread.hpp>

#include <ft2build.h>
#include FT_TYPES_H

#include "textmetric_glyphs.hpp"
#include "textmetric_impl.hpp"

namespace textmetric_internal
{

    // Structures

    // Mapper structure, mapping a string to an integer
    struct simap_t {
        const char* str;
        int i;
    };

    // Face ID
    struct faceid_t {
        std::string filename;
        unsigned int index;
    };

    // Font details
    struct fontdetails_t {
        // This does NOT contain a size or a weight. Both of those
        // are generated when the font's charmap is scaled for a
        // particular styleset glyphmap.

        // Font family (here again for convenience)
        std::string family;

        // Font style flags (1 = Italic, 2 = Bold)
        unsigned long styleflags;

        // Font
        faceid_t* faceid;
    };

    // Typedefs

    // Vector of strings
    typedef std::vector<std::string> strvec_t;
    typedef strvec_t::const_iterator strvec_c;
    typedef strvec_t::iterator strvec_i;

    // std::map representation of an simap (static tables from header)
    typedef std::map<std::string, int> simapmap_t;
    typedef simapmap_t::const_iterator simapmap_c;
    typedef simapmap_t::iterator simapmap_i;

    // Set of known font files. Caches full path and file
    // name of individual files.
    typedef std::set<std::string> fontfileset_t;

    // Normalized style description, generated from a cleaned-up
    // style_map_type. No need for case-insenitivity here.
    typedef std::map<std::string, std::string> styledesc_t;

    // List of faceid descriptions
    typedef std::list<faceid_t*> faceidlist_t;
    typedef faceidlist_t::const_iterator faceidlist_c;
    typedef faceidlist_t::iterator faceidlist_i;

    // Face mapping type. Maps a single property (font-family)
    // to a font details description.
    typedef std::multimap<std::string, fontdetails_t, case_insensitive_cmp> detailsmapper_t;
    typedef detailsmapper_t::const_iterator detailsmapper_c;
    typedef detailsmapper_t::iterator detailsmapper_i;
    typedef std::pair<detailsmapper_c, detailsmapper_c> detailsmapper_pc;

    // Map face IDs to their character->glyph index translation tables
    typedef std::map<const faceid_t*, chartoglyph_t*> faceidglyidxmapper_t;
    typedef faceidglyidxmapper_t::const_iterator faceidglyidxmapper_c;
    typedef faceidglyidxmapper_t::iterator faceidglyidxmapper_i;

    // Glyph cache mapping type.
    // Maps a cleaned-up style description
    // to a glyph map.
    typedef std::map<styledesc_t, glyphset_t*> gldescmapper_t;
    typedef gldescmapper_t::const_iterator gldescmapper_c;
    typedef gldescmapper_t::iterator gldescmapper_i;

    // Lock guard for a standard mutex
    typedef boost::lock_guard<boost::mutex> mutexlock_t;

}; // namespace textmetric_internal

#endif // __TEXTMETRIC_TYPES_H__
