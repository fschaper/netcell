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

#ifndef DML_GRAPHICALOBJECTANIMATION_READERS_HPP
#define DML_GRAPHICALOBJECTANIMATION_READERS_HPP

#include "dml-graphicalObjectAnimation.hpp"
#include "dml-baseTypes_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_AnimationDgmElement_reader;
		class CT_AnimationChartElement_reader;
		class CT_AnimationElementChoice_reader;
		class ST_AnimationDgmBuildType_reader;
		class CT_AnimationDgmBuildProperties_reader;
		class ST_AnimationChartBuildType_reader;
		class CT_AnimationChartBuildProperties_reader;
		class CT_AnimationGraphicalObjectBuildProperties_reader;

		class CT_AnimationDgmElement_reader : public type_reader
		{
		protected:
			CT_AnimationDgmElement* t() { return static_cast<CT_AnimationDgmElement*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AnimationChartElement_reader : public type_reader
		{
		protected:
			CT_AnimationChartElement* t() { return static_cast<CT_AnimationChartElement*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AnimationElementChoice_reader : public type_reader
		{
			auto_type_reader< CT_AnimationDgmElement_reader > _dgm_reader;
			auto_type_reader< CT_AnimationChartElement_reader > _chart_reader;
		protected:
			CT_AnimationElementChoice* t() { return static_cast<CT_AnimationElementChoice*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_AnimationDgmBuildType_reader : public type_reader
		{
		protected:
			ST_AnimationDgmBuildType* t() { return static_cast<ST_AnimationDgmBuildType*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_AnimationDgmBuildProperties_reader : public type_reader
		{
		protected:
			CT_AnimationDgmBuildProperties* t() { return static_cast<CT_AnimationDgmBuildProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_AnimationChartBuildType_reader : public type_reader
		{
		protected:
			ST_AnimationChartBuildType* t() { return static_cast<ST_AnimationChartBuildType*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_AnimationChartBuildProperties_reader : public type_reader
		{
		protected:
			CT_AnimationChartBuildProperties* t() { return static_cast<CT_AnimationChartBuildProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AnimationGraphicalObjectBuildProperties_reader : public type_reader
		{
			auto_type_reader< CT_AnimationDgmBuildProperties_reader > _bldDgm_reader;
			auto_type_reader< CT_AnimationChartBuildProperties_reader > _bldChart_reader;
		protected:
			CT_AnimationGraphicalObjectBuildProperties* t() { return static_cast<CT_AnimationGraphicalObjectBuildProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

