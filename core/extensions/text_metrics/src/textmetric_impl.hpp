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

// textmetric.hpp - This is the public inferface header.
// It's the only header required to use textmetric from
// client code.

#ifndef __TEXTMETRIC_IMPL_H__
#define __TEXTMETRIC_IMPL_H__

// C++ includes
#include <map>
#include <stdexcept>
#include <string>

// Additional includes
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

// This should be usable both as a static and a dynamic library,
// in both Windows and UNIX. Things will just work on UNIX as
// libtool handles this perfectly. Note that on Windows, you
// must define DLL_EXPORT when building the DLL version (cygwin
// and MinGW do this automatically), and so does the library
// project file for DLL output in VisualStudio.

// BUILD_TEXTMETRIC must be defined during library build

// Define TEXTMETRIC_DLLIMPORT in your project file to link
// against the DLL version
#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__))
#ifdef BUILD_TEXTMETRIC
#ifdef DLL_EXPORT
#define __DLLDECL_TEXTMETRIC__ __declspec(dllexport)
#endif
// Else building a static library
#else
#ifdef TEXTMETRIC_DLLIMPORT
#define __DLLDECL_TEXTMETRIC__ __declspec(dllimport)
#endif
#endif
#endif

// Make sure it is also defined in the UNIX case
#ifndef __DLLDECL_TEXTMETRIC__
#define __DLLDECL_TEXTMETRIC__
#endif

namespace textmetric_internal
{

    // Structure defining the bounding box of a string
    // As the spec doesn't say anything about fixed
    // endianness, alignment or integer widths, I assume
    // the defaults.
    struct __DLLDECL_TEXTMETRIC__ bounding_box {
        unsigned int height;    // bounding box height (pixels)
        unsigned int width;     // bounding box width (pixels)
    };

    // A case-insensitive string comparator functor
    struct __DLLDECL_TEXTMETRIC__ case_insensitive_cmp
            : public std::binary_function<std::string, std::string, bool> {
        bool operator()( const std::string& s1, const std::string& s2 ) const {
            return boost::algorithm::ilexicographical_compare( s1, s2 );
        }
    };

    // Parameter list wrapper type. Maps case-insensitive CSS property
    // parameter to parameter content in string representation.
    typedef std::map<std::string, std::string, case_insensitive_cmp> style_map_type;
    typedef style_map_type::const_iterator style_map_type_c;
    typedef style_map_type::iterator style_map_type_i;

    // Exceptions

    // text_metric exception base class, for catch-all scenarios
    class __DLLDECL_TEXTMETRIC__ text_metric_exception : public std::runtime_error
    {
    public:
        explicit text_metric_exception( const std::string& arg );
    };

    // text_metric internal error exception
    class __DLLDECL_TEXTMETRIC__ text_metric_internalerror_exception : public text_metric_exception
    {
    public:
        explicit text_metric_internalerror_exception( const std::string& arg );
    };

    // bounding_box not calculatable for argument
    class __DLLDECL_TEXTMETRIC__ text_metric_boxnotcalcable_exception : public text_metric_exception
    {
    public:
        explicit text_metric_boxnotcalcable_exception( const std::string& arg );
    };

    // font-family not found in font list
    class __DLLDECL_TEXTMETRIC__ text_metric_fontfamilynotfound_exception : public text_metric_exception
    {
    public:
        explicit text_metric_fontfamilynotfound_exception( const std::string& arg );
    };

    // Malformed style_map_type table
    class __DLLDECL_TEXTMETRIC__ text_metric_malformedstyle_exception : public text_metric_exception
    {
    public:
        explicit text_metric_malformedstyle_exception( const std::string& arg );
    };

    // text_metric class
    class __DLLDECL_TEXTMETRIC__ text_metric
    {
    protected:
        //style descriptor
        std::map<std::string, std::string>  m_Stde;

        //dpi
        int                                 m_xdpi;
        int                                 m_ydpi;
        unsigned int                        m_em;

        // Glyph set handle (opaque)
        void* m_GlyphSetHandle;

        // Underlined text desired?
        bool b_Underlined;

        // Internal mutex
        mutable boost::mutex m_Mutex;

        // Copier routine
        void doCC( const text_metric& cc );

        // checks if there is a need to register more glyphs
        void validate_string( const std::string& arg ) const;
    public:
        // Should be explicit? Spec doesn't say so, so ...
        text_metric( const style_map_type& smt, int xdpi, int ydpi );
        text_metric( const text_metric& cc );
        virtual ~text_metric() throw ();

        // Get the bounding box for a given string.
        // The spec doesn't explicitely say it must be virtual,
        // but I guess it should be.
        virtual bounding_box get_bounding_box( const std::string& arg ) const;

        // Set the font list
        static void set_font_list( const std::vector< std::string >& fontlist );

        // Set the font search path
        static void set_font_path( const boost::filesystem::path& fspath );

        // Assignment
        text_metric& operator=( const text_metric& cc );
    };

}; // namespace textmetric_internal

#endif // __TEXTMETRIC_H__
