#define BOOST_FILESYSTEM_VERSION 2
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <wss/extension_module_load_exception.hpp>
#include <wss/extension_function_call_failed_exception.hpp>
#include <wss/module_registry.hpp>
#include <wss/translation_table.hpp>
#include <wss/locale.hpp>
#include <wss/server.hpp>
#include <wss/variant.hpp>
#include <wss/tied_stream.hpp>
#include <wss/flyweight_types.hpp>
#include <iostream>
#include <fstream>
#if defined(_WSS_UNIT_TESTS) && (_NDEBUG)
#include <configuration.hpp>
#endif

using namespace boost::unit_test;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    // we intentionally leak some memory here.
    std::ofstream* logfile = new std::ofstream( "report.xml" );
    tied_ostream* tied_stream = new tied_ostream( *logfile, std::cout );
    if ( ( *logfile ).good() ) {
        ::boost::unit_test::unit_test_log.set_stream( ( *tied_stream ) );
    }
    internal_flyweights::init();
    shared_translation_map_type t_map = translation_map::create( locale::create( "en-*" ), ";", ",", ";", true, "true", "false" );
    t_map->add( translation_map::function_translation_entry( "rand", "rand" ) );
    t_map->add( translation_map::function_translation_entry( "if", "if" ) );
    t_map->add( translation_map::function_translation_entry( "average", "average" ) );
    t_map->add( translation_map::function_translation_entry( "averagee", "averagee" ) );
    t_map->add( translation_map::function_translation_entry( "stdev", "stdev" ) );
    t_map->add( translation_map::function_translation_entry( "rank", "rank" ) );
    t_map->add( translation_map::function_translation_entry( "percentrank", "percentrank" ) );
    t_map->add( translation_map::function_translation_entry( "not", "not" ) );
    t_map->add( translation_map::function_translation_entry( "iserror", "iserror" ) );
    t_map->add( translation_map::function_translation_entry( "isblank", "isblank" ) );
    t_map->add( translation_map::function_translation_entry( "isunique", "isunique" ) );
    t_map->add( translation_map::function_translation_entry( "isduplicate", "isduplicate" ) );
    t_map->add( translation_map::function_translation_entry( "max", "max" ) );
    t_map->add( translation_map::function_translation_entry( "min", "min" ) );
    t_map->add( translation_map::function_translation_entry( "search", "search" ) );
    t_map->add( translation_map::function_translation_entry( "left", "left" ) );
    t_map->add( translation_map::function_translation_entry( "len", "len" ) );
    t_map->add( translation_map::function_translation_entry( "between", "between" ) );
    t_map->add( translation_map::function_translation_entry( "nbetween", "nbetween" ) );
    t_map->add( translation_map::function_translation_entry( "search", "search" ) );

    translation_map::error_mapping::type error_map;
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_div_null, "#div/0!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_n_a, "#na!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_name, "#name!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_null, "#null!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_value, "#value!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_ref, "#ref!" ) );
    error_map.insert( translation_map::error_mapping::entity_type( variant::error_num, "#num!" ) );
    t_map->error_translation( error_map );

    translation_table::instance().add( t_map );

    framework::master_test_suite().p_name.value = "core3";

#if defined(_WSS_UNIT_TESTS) && (_NDEBUG)
    const std::string DEBUG_POSTFIX( "" );
    static server& server_instance = server::instance();
    configuration::instance().configure( argc, argv );

#else
    const std::string DEBUG_POSTFIX( "_d" );

    //load extensions
    try {
#if defined(WIN32)
        module_registry::instance().register_extension( "extension/function" + DEBUG_POSTFIX + ".dll" );
#else
    module_registry::instance().register_extension( "function" + DEBUG_POSTFIX + ".so" );
#endif
    } catch ( const extension_module_load_exception& ) {
        std::cout << "Failed to load function_library!" << std::endl;
    } catch ( const extension_function_call_failed_exception& ) {
        std::cout << "Failed to initialize the function_library!" << std::endl;
    }

    try {
#if defined(WIN32)

        module_registry::instance().register_extension( "extension/cell_format" + DEBUG_POSTFIX + ".dll", "locale/cell_format_data.xml" );
#else
    module_registry::instance().register_extension( "cell_format" + DEBUG_POSTFIX + ".so" );
#endif
    } catch ( const extension_module_load_exception& ) {
        std::cout << "Failed to load cell format extension!" << std::endl;
    }

    try {
#if defined(WIN32)
        module_registry::instance().register_extension( "extension/persistence" + DEBUG_POSTFIX + ".dll" );
#else
    module_registry::instance().register_extension( "persistence" + DEBUG_POSTFIX + ".so" );
#endif
    } catch ( const extension_module_load_exception& ) {
        std::cout << "Failed to load persistence extension!" << std::endl;
    }
#if 0
    try {
#if defined(WIN32)
        module_registry::instance().register_extension( "auto_fill" + DEBUG_POSTFIX + ".dll", "locale" );
#else
    module_registry::instance().register_extension( "auto_fill" + DEBUG_POSTFIX + ".so", "locale" );
#endif
    } catch ( const extension_module_load_exception& ) {
        std::cout << "Failed to load autofill extension!" << std::endl;
    }
#endif
#endif
    return 0;
}
