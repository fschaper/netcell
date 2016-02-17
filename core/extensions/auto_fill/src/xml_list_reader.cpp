/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*  Vali Nitu <vali@yalos-solutions.com>
*/

#include "precompiled_header.hpp"
#include "sequence_text_fill_handler.hpp"
#include "xml_list_reader.hpp"


namespace autofill_internal
{

    void xml_list_reader::register_handler( const std::vector<std::string>& list , locale& list_locale )
    {
        autofill_handler::handler_type text_handler( new sequence_text_fill_handler() );
        static_cast<sequence_text_fill_handler*>( text_handler.get() )->set_list( list , list_locale );
        m_ah.register_handler( text_handler );
    }

    void xml_list_reader::read_list( const boost::filesystem::path& folder_path, std::string& locale )
    {
        //TODO
        std::string locale_string = folder_path.leaf();
        ::locale list_locale = locale::create( locale );


        for ( boost::filesystem::directory_iterator it( folder_path ); it != boost::filesystem::directory_iterator(); ++it ) {
            std::vector<std::string> myList;
            try {
                jedox::wss::autofill_internal::autocompletion_list doc;
                ::xio::xml::binding::parser parser;
                std::ifstream   src( it->path().native_directory_string().c_str() );
                parser.parse_doc( src, doc );
                if ( !doc.autofill_list.present() ) {
                    std::cout << " invalid autofill file: " << it->path() << std::endl;
                    continue;
                }
                jedox::wss::autofill_internal::CT_autofill_list new_list = doc.autofill_list.get();

                std::vector< std::string >& el_sequence = new_list.element;

                BOOST_FOREACH( std::string & el, el_sequence ) {
                    myList.push_back( static_cast<std::string>( el ) );
                }
            } catch ( ... ) {
                std::cout << "XMLListReader::read_list fails" << std::endl;
            }

            register_handler( myList, list_locale );//TODO transport locale
        }

    }


}

