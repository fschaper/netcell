/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
*
*  This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU General Public License (Version 2) as published
*  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
*
*  This program is distributed in the hope that it will be useful, but WITHOUT
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
*  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
*  more details.
*
*  You should have received a copy of the GNU General Public License along with
*  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
*  Place, Suite 330, Boston, MA 02111-1307 USA
*
*  You may obtain a copy of the License at
*
*  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
*    http://www.jedox.com/license_palo_bi_suite.txt
*  </a>
*
*  If you are developing and distributing open source applications under the
*  GPL License, then you are free to use Worksheetserver under the GPL License.
*  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
*  and do not license and distribute their source code under the GPL, Jedox provides
*  a flexible OEM Commercial License.
*
*  \author
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#ifndef _COMMANDFUNCTORS
#   define _COMMANDFUNCTORS


class SetColRowDims_BaseFunctor
{
public:
    virtual void operator() ( session&, const sheet_layout_trait::line_type&, const unsigned int ) const = 0;
    virtual ~SetColRowDims_BaseFunctor () { }
};

template <class C>
class SetColRowDims_Functor : public SetColRowDims_BaseFunctor
{
public:
    void operator() ( session& cx, const sheet_layout_trait::line_type& line, const unsigned int dim ) const {
        C c( cx, line, dim );
        c.execute();
    }
};


class GetMaxColRowDims_BaseFunctor
{
public:
    typedef get_sparse_max_cell_width_command::result_type return_value_type;
    virtual return_value_type operator() ( session&, const sheet_layout_trait::line_type& ) const = 0;
    virtual ~GetMaxColRowDims_BaseFunctor () { }
};

template <class C>
class GetMaxColRowDims_Functor : public GetMaxColRowDims_BaseFunctor
{
public:
    return_value_type operator() ( session& cx, const sheet_layout_trait::line_type& line ) const {
        C c( cx, line );
        return execute_command < C >()( c );
    }
};


#endif // _COMMANDFUNCTORS
