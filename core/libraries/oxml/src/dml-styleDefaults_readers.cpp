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


#include "dml-styleDefaults_readers.hpp"
#include "dml-styleDefaults_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_DefaultShapeDefinition_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_spPr_literal))
			{
				driver()->push(localname, _spPr_reader.get_reader(&t()->spPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_bodyPr_literal))
			{
				driver()->push(localname, _bodyPr_reader.get_reader(&t()->bodyPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_lstStyle_literal))
			{
				driver()->push(localname, _lstStyle_reader.get_reader(&t()->lstStyle));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_style_literal))
			{
				driver()->push(localname, _style_reader.get_reader(&t()->style.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ObjectStyleDefaults_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_spDef_literal))
			{
				driver()->push(localname, _spDef_reader.get_reader(&t()->spDef.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_lnDef_literal))
			{
				driver()->push(localname, _lnDef_reader.get_reader(&t()->lnDef.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_txDef_literal))
			{
				driver()->push(localname, _txDef_reader.get_reader(&t()->txDef.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_styleDefaults_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
	}
}
