/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef DML_SHAPELINEPROPERTIES_READERS_HPP
#define DML_SHAPELINEPROPERTIES_READERS_HPP

#include "dml-shapeLineProperties.hpp"
#include "dml-shapeEffects_readers.hpp"
#include "dml-baseTypes_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_PresetLineDashProperties_reader;
		class CT_DashStop_reader;
		class CT_DashStopList_reader;
		class CT_LineJoinRound_reader;
		class CT_LineJoinBevel_reader;
		class CT_LineJoinMiterProperties_reader;
		class CT_LineEndProperties_reader;
		class ST_LineWidth_reader;
		class CT_LineProperties_reader;

		class CT_PresetLineDashProperties_reader : public type_reader
		{
		protected:
			CT_PresetLineDashProperties* t() { return static_cast<CT_PresetLineDashProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DashStop_reader : public type_reader
		{
		protected:
			CT_DashStop* t() { return static_cast<CT_DashStop*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DashStopList_reader : public type_reader
		{
			auto_type_reader< CT_DashStop_reader > _ds_reader;
		protected:
			CT_DashStopList* t() { return static_cast<CT_DashStopList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_LineJoinRound_reader : public type_reader
		{
		protected:
			CT_LineJoinRound* t() { return static_cast<CT_LineJoinRound*>(target()); }
		};

		class CT_LineJoinBevel_reader : public type_reader
		{
		protected:
			CT_LineJoinBevel* t() { return static_cast<CT_LineJoinBevel*>(target()); }
		};

		class CT_LineJoinMiterProperties_reader : public type_reader
		{
		protected:
			CT_LineJoinMiterProperties* t() { return static_cast<CT_LineJoinMiterProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_LineEndProperties_reader : public type_reader
		{
		protected:
			CT_LineEndProperties* t() { return static_cast<CT_LineEndProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_LineWidth_reader : public ST_Coordinate32_reader
		{
		protected:
			ST_LineWidth* t() { return static_cast<ST_LineWidth*>(target()); }
		};

		class CT_LineProperties_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_PresetLineDashProperties_reader > _prstDash_reader;
			auto_type_reader< CT_DashStopList_reader > _custDash_reader;
			auto_type_reader< CT_LineJoinRound_reader > _round_reader;
			auto_type_reader< CT_LineJoinBevel_reader > _bevel_reader;
			auto_type_reader< CT_LineJoinMiterProperties_reader > _miter_reader;
			auto_type_reader< CT_LineEndProperties_reader > _headEnd_reader;
			auto_type_reader< CT_LineEndProperties_reader > _tailEnd_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_LineProperties* t() { return static_cast<CT_LineProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

