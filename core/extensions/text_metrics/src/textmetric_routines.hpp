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

// textmetric_routines.hpp - Routines prototypes

#ifndef __TEXTMETRIC_ROUTINES_H__
#define __TEXTMETRIC_ROUTINES_H__

#include "textmetric_types.hpp"

namespace textmetric_internal
{

    // Build a (fast) std::map from a static simap
    void SimapToSimapmap( const simap_t* table, simapmap_t& outmap );

    // Lookup something in a simapmap. Returns 0 if the element
    // does not exist (therefore, use "0" as an invalidity marker)
    int SimapmapLookup( const simapmap_t& themap, const std::string& key );

    // Allow "T = map[key]" on a constant map
    // will be: ConstMapFetch(mymap)["key"]
    template<typename K, typename O, typename C, typename A>
    class ConstMapHelper
    {
    protected:
        const std::map<K, O, C, A>* m_Ptr;

    public:
        ConstMapHelper( const std::map<K, O, C, A>& themap ) {
            m_Ptr = &themap;
        }

        virtual ~ConstMapHelper() {
        }

        virtual O operator[]( const K& k ) {
            typename std::map<K, O, C, A>::const_iterator iter =
                m_Ptr->find( k );

            if ( iter == m_Ptr->end() ) {
                return O();
            }

            return ( *iter ).second;
        }
    };

    template<typename K, typename O, typename C, typename A>
    ConstMapHelper<K, O, C, A> ConstMapFetch( const std::map<K, O, C, A>& parm )
    {
        return ConstMapHelper<K, O, C, A>( parm );
    }

}; // namespace textmetric_internal

#endif // __TEXTMETRIC_ROUTINES_H__

