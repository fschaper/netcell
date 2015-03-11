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

// textmetric_exceptions.cpp - Exceptions implementation

#include "textmetric_impl.hpp"

namespace textmetric_internal
{

    text_metric_exception::text_metric_exception( const std::string& arg )
        : std::runtime_error( arg )
    {
    }

    text_metric_internalerror_exception::text_metric_internalerror_exception( const std::string& arg )
        : text_metric_exception( arg )
    {
    }

    text_metric_boxnotcalcable_exception::text_metric_boxnotcalcable_exception( const std::string& arg )
        : text_metric_exception( arg )
    {
    }

    text_metric_fontfamilynotfound_exception::text_metric_fontfamilynotfound_exception(
        const std::string& arg )
        : text_metric_exception( arg )
    {
    }

    text_metric_malformedstyle_exception::text_metric_malformedstyle_exception(
        const std::string& arg )
        : text_metric_exception( arg )
    {
    }

}; // namespace textmetric_internal
