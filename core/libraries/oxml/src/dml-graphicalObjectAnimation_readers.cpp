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

#include "dml-graphicalObjectAnimation_readers.hpp"
#include "dml-graphicalObjectAnimation_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_AnimationDgmElement_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bldStep_literal))
			{
				driver()->context()->parse(value, t()->bldStep);
				return;
			}
		}
		void CT_AnimationChartElement_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_seriesIdx_literal))
			{
				driver()->context()->parse(value, t()->seriesIdx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_categoryIdx_literal))
			{
				driver()->context()->parse(value, t()->categoryIdx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bldStep_literal))
			{
				driver()->context()->parse(value, t()->bldStep);
				return;
			}
		}
		void CT_AnimationElementChoice_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_dgm_literal))
			{
				driver()->push(localname, _dgm_reader.get_reader(&t()->dgm.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_chart_literal))
			{
				driver()->push(localname, _chart_reader.get_reader(&t()->chart.getset()));
				return;
			}
		}
		void ST_AnimationDgmBuildType_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_AnimationDgmBuildProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bld_literal))
			{
				driver()->context()->parse(value, t()->bld);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_rev_literal))
			{
				driver()->context()->parse(value, t()->rev);
				return;
			}
		}
		void ST_AnimationChartBuildType_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_AnimationChartBuildProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bld_literal))
			{
				driver()->context()->parse(value, t()->bld);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_animBg_literal))
			{
				driver()->context()->parse(value, t()->animBg);
				return;
			}
		}
		void CT_AnimationGraphicalObjectBuildProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bldDgm_literal))
			{
				driver()->push(localname, _bldDgm_reader.get_reader(&t()->bldDgm.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_graphicalObjectAnimation_bldChart_literal))
			{
				driver()->push(localname, _bldChart_reader.get_reader(&t()->bldChart.getset()));
				return;
			}
		}
	}
}
