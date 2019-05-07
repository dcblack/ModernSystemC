/**
 * @file main.cpp
 */
#include "top.hpp"
#include "report.hpp"
#include "fpsqrt.hpp"
#include <string>
#include <map>
#include <vector>

namespace {
  char const * const MSGID{ "/Doulos/Example/Magnitude/main" };
}
std::map<std::string,std::string> cmdline;
std::ostringstream mout;
int sc_main( int argc, char* argv[] )
{
  using namespace sc_core;

  /**...........................................................................
   * Scan command-line for options
   */
  bool debugging { false };
  std::string others;
  for( int i=1; i<sc_argc(); ++i ) {
    std::string arg(sc_argv()[i]);
    if( arg == "--" ) {
      // ignore
    } else if( arg[0] == '-' and arg.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == 1 ) {
      size_t pos = arg.find_first_of( "=" );
      if( pos == std::string::npos ) {
        cmdline[ arg ] = "1";
      } else {
        cmdline[ arg.substr( 0, pos ) ] = arg.substr( pos+1 );
      }
    } else {
      if( others.length() > 0 ) others += '\1';
      others += arg;
    }
  }//endfor
  if( others.length() > 0 ) cmdline[ "~" ] = others;
  if( cmdline.size() > 0 ) {
    MESSAGE( "Command-line options:" );
    for( auto const& o: cmdline ) {
      MESSAGE( "\n  " << o.first << " = " << o.second );
    }
    MEND( ALWAYS );
  }

  /**...........................................................................
   * Test fpsqrt
   */
  {
    std::vector<FixedPt_t> sqrs = { 0, 1, 2, 4, 9.5, 6.4, 64.5, 100, 100.5, 95, 10000, 11200 };
    for( auto v : sqrs ) {
      INFO( ALWAYS, "FP::fpsqrt( " << v.to_double() << " ) = " << FP::fpsqrt( v ).to_double() );
    }
  }
  if( cmdline.count("-x") > 0 ) {
    exit( 0 );
  }

  /**...........................................................................
   * Setup reporting
   */
  if( cmdline.count("-d") > 0 ) {
    sc_report_handler::set_verbosity_level( SC_DEBUG );
  }
  sc_report_handler::set_actions( SC_ERROR, SC_DISPLAY | SC_LOG );

  /**...........................................................................
   * Instantiate
   */
  Top_module top{ "top" };

  /**...........................................................................
   * Simulate
   */
  sc_start();

  if ( not sc_end_of_simulation_invoked() )
  {
    SC_REPORT_ERROR( MSGID, "Simulation stopped without explicit sc_stop()");
    sc_stop();
  }

  /**...........................................................................
   * Report results
   */
  if ( ( sc_report_handler::get_count( SC_ERROR )
         + sc_report_handler::get_count( SC_FATAL )
       ) == 0 
     )
  {
     SC_REPORT_INFO_VERB( MSGID, "PASSED", SC_NONE );
     return 0;
  } else {
     SC_REPORT_INFO_VERB( MSGID, "FAILED", SC_NONE );
     return 1;
  }
}
