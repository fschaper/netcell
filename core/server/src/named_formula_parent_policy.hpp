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
*
*  \author
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/
#pragma once

#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"
#include "wss/exception.hpp"
#include "wss/non_instantiable.hpp"
#include "named_formula_utility.hpp"
#include <boost/shared_ptr.hpp>

#ifdef 0
namespace policy
{
    namespace named_formula
    {

        template<class parent_T>
        class parent_policy
        {
        protected:
            typedef boost::shared_ptr<parent_T> shared_parent_type;
        public:
            parent_policy( parent_T& p )
                : m_parent( p ) {}

            const parent_T& parent() const {
                return m_parent;
            }

            parent_T& parent() {
                return m_parent;
            }


        protected:
            parent_T& m_parent;
        };

        template<>
        class parent_policy<weak_worksheet_type>
        {
        protected:
            typedef boost::shared_ptr<worksheet> shared_parent_type;
            /* typedef boost::weak_ptr<worksheet> weak_parent_type;*/
        public:
            parent_policy( const weak_worksheet_type& parent )
                : m_parent( parent ) {}

            weak_worksheet_type worksheet() const {
                return m_parent;
            }

            weak_workbook_type workbook() const {
                shared_parent_type ws = m_parent.lock();
                if ( !ws ) {
                    throw invalid_worksheet_exception();
                }
                return ws->parent();
            }

            named_formula_utils::scope::Type scope() const {
                return named_formula_utils::scope::worksheet_scope;
            }

        protected:

            weak_worksheet_type m_parent;
        };

        template<>
        class parent_policy<weak_workbook_type>
        {
        protected:
            typedef boost::shared_ptr<workbook> shared_parent_type;

        public:
            parent_policy( const weak_workbook_type& parent )
                : m_parent( parent ) {}

            weak_workbook_type workbook() const {
                return m_parent;
            }

            weak_worksheet_type worksheet() const {
                return weak_worksheet_type();
            }

            named_formula_utils::scope::Type scope() const {
                return named_formula_utils::scope::workbook_scope;
            }

        protected:
            weak_workbook_type m_parent;
        };
    }
}
#endif // 0