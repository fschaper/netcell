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

// textmetric_glyphs.hpp - glyph related classes
// YLS: Relocated here and updated to maps

#ifndef __TEXTMETRIC_GLYPHS_H__
#define __TEXTMETRIC_GLYPHS_H__

#include <boost/thread.hpp>

namespace textmetric_internal
{

    // Description for a single character
    struct gscharinfo_t {
        // Is the slot valid (=font contains desired character)
        bool isvalid;

        // Glyph bounding box
        FT_BBox glyph_bbox;

        // Advance distance to next glyph
        int advance;
    };

    // Character to glyph index - map character codes
    // glyph index in face
    struct chartoglyph_t {
        const std::map< unsigned int, unsigned int >* at( unsigned int xdpi, unsigned int ydpi ) {
            for ( std::vector< scaled_idx >::const_iterator i = data.begin(); i != data.end(); i++ ) {
                if ( ( xdpi == i->xdpi ) && ( ydpi == i->ydpi ) ) {
                    return &( i->glyphidx );
                }
            }
            register_scale( xdpi, ydpi );
            return &data[ data.size()-1 ].glyphidx;
        }

        const std::map< unsigned int, unsigned int >* register_scale( unsigned int xdpi, unsigned int ydpi ) {
            scaled_idx scale = data[0];
            scale.xdpi = xdpi;
            scale.ydpi = ydpi;
            data.push_back( scale );
            return at( xdpi, ydpi );
        }

        typedef std::map< unsigned int, unsigned int >::iterator glyphidx_i;
        typedef std::map< unsigned int, unsigned int >::const_iterator glyphidx_c;

        chartoglyph_t() {
            scaled_idx scale;
            scale.xdpi = 0;
            scale.ydpi = 0;
            data.push_back( scale );
        }
    private:
        struct scaled_idx {
            unsigned int                                xdpi;
            unsigned int                                ydpi;
            std::map< unsigned int, unsigned int >      glyphidx;
        };
        //position zero contains the reference idx-s. siigned to xdpi=ydpi=0
        std::vector< scaled_idx >                       data;
    };

    // A glyph set.
    // Cooked -> char/index mapped
    // Character descriptions for all current characters. starts with the ASCII set
    struct glyphset_t {
        struct scaled_data {
            friend struct glyphset_t;
            mutable boost::mutex                        lock;
            std::map< unsigned int, gscharinfo_t >      data;

            // Baseline-to-baseline step in pixels (for multiline input)
            int linestep;

            // Total text reserve in pixels computed as ascent - descent (scaled)
            int linereserve;

            // Underlining position and thickness
            int underline_position;
            int underline_thickness;

            unsigned int x_ppem;

            explicit scaled_data() {
                linestep            = 0;
                underline_position  = 0;
                underline_thickness = 0;
                linereserve         = 0;
                x_ppem              = 0;
            }

            scaled_data( const scaled_data& other ) {
                boost::mutex::scoped_lock scoped_lock( other.lock );
                xdpi = other.xdpi;
                ydpi = other.ydpi;
                data = other.data;

                linestep            = other.linestep;
                linereserve         = other.linereserve;
                underline_position  = other.underline_position;
                underline_thickness = other.underline_thickness;
                x_ppem              = other.x_ppem;
            }

            const scaled_data& operator=( const scaled_data& other ) {
                if ( this == &other ) {
                    return *this;
                }

                boost::mutex::scoped_lock lock1( &lock < &other.lock ? lock : other.lock );
                boost::mutex::scoped_lock lock2( &lock > &other.lock ? lock : other.lock );

                xdpi = other.xdpi;
                ydpi = other.ydpi;
                data = other.data;

                linestep            = other.linestep;
                linereserve         = other.linereserve;
                underline_position  = other.underline_position;
                underline_thickness = other.underline_thickness;
                x_ppem              = other.x_ppem;

                return *this;
            }
        private:
            unsigned int                                xdpi;
            unsigned int                                ydpi;
        };

        typedef std::map< unsigned int, gscharinfo_t >::iterator data_i;
        typedef std::map< unsigned int, gscharinfo_t >::const_iterator data_c;
        scaled_data* at( unsigned int xdpi, unsigned int ydpi ) {
            boost::mutex::scoped_lock lock( this->lock );
            for ( std::vector< scaled_data >::iterator i = data.begin(); i != data.end(); i++ ) {
                if ( ( xdpi == i->xdpi ) && ( ydpi == i->ydpi ) ) {
                    return &( *i );
                }
            }
            return NULL;
        }

        scaled_data* register_scale( unsigned int xdpi, unsigned int ydpi ) {
            {
                boost::mutex::scoped_lock lock( this->lock );
                scaled_data scale;
                scale.xdpi = xdpi;
                scale.ydpi = ydpi;
                data.push_back( scale );
            }
            return at( xdpi, ydpi );
        }
    private:
        boost::mutex                                    lock;
        std::vector< scaled_data >                      data;
    };

}; // namespace textmetric_internal

#endif //__TEXTMETRIC_GLYPHS_H__
