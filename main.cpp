/**
 * @file main.cpp
 */
#include "top.hpp"
#include "report.hpp"
#include "fpsqrt.hpp"
#include "wallclock.hpp"
#include <string>
#include <map>
#include <vector>
#include <memory>

using namespace sc_core;

namespace {
  char const * const MSGID{ "/Doulos Inc/Example/Modern/main" };
  double elaboration_cpuTime=-1.0, starting_cpuTime=-1.0, finished_cpuTime=-1.0;
  int summary( void );
}

/**
 * Globals
 */
std::map<std::string,std::string> cmdline; ///< parsed from command-line

/**
 * @brief Entry point for SystemC
 */
int sc_main( [[maybe_unused]]int argc, [[maybe_unused]]char* argv[] )
{

  /**...........................................................................
   * Scan command-line for options
   */
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
    for( auto const& [option, value] : cmdline ) {
      MESSAGE( "\n  " << option << " = " << value );
    }
    MEND( ALWAYS );
  }

  /**...........................................................................
   * @brief Test fpsqrt
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
  // Simplify error handling by avoiding the SC_THROW
  sc_report_handler::set_actions( SC_ERROR, SC_DISPLAY | SC_LOG );

  /**...........................................................................
   * Instantiate
   */
  elaboration_cpuTime = get_cpu_time(); //< Capture start of elaboration
  std::unique_ptr<Top_module> top;
  try {
    // Construct top-level
    top.reset(new Top_module("top"));
  } catch (sc_core::sc_exception& e) {
    REPORT(INFO,"\n" << e.what() << "\n\n*** Please fix elaboration errors and retry. ***");
    return summary();
  } catch (...) {
    REPORT(INFO,"\n Error: *** Caught unknown exception during elaboration. ***");
    return summary();
  }//endtry

  /**...........................................................................
   * Simulate
   */
  sc_core::sc_time finished_simTime;
  try {
    REPORT(INFO,"Starting kernel");
    starting_cpuTime = get_cpu_time(); //< Capture start of simulation
    sc_core::sc_start();
    finished_simTime = sc_core::sc_time_stamp();
    finished_cpuTime = get_cpu_time();
  } catch (sc_core::sc_exception& e) {
    REPORT(WARNING,"\n\nCaught exception during active simulation.\n" << e.what());
  } catch (...) {
    REPORT(WARNING,"Error: Caught unknown exception during active simulation.");
  }//endtry
  REPORT(INFO,"Exited kernel at " << finished_simTime);

  // Clean up
  if ( not sc_end_of_simulation_invoked() )
  {
    SC_REPORT_ERROR( MSGID, "Simulation stopped without explicit sc_stop()");
    sc_stop(); //< invoke end_of_simulation() overrides
  }

  return summary();

}

#include <iomanip>

namespace {

  using namespace std;

  // Summarize results
  int summary( void )
  {
    std::string kind = "Simulation";
    if ( starting_cpuTime < 0.0 ) {
      kind = "Elaboration";
      starting_cpuTime = finished_cpuTime = get_cpu_time();
    } 
    if ( finished_cpuTime < 0.0 ) {
      finished_cpuTime = get_cpu_time();
    }
    auto errors = sc_report_handler::get_count(SC_ERROR)
                + sc_report_handler::get_count(SC_FATAL);
    REPORT(INFO, "\n" << std::string(80,'#') << "\nSummary for " << sc_argv()[0] << ":\n  "
      << "CPU elaboration time " << std::setprecision(4) << (starting_cpuTime - elaboration_cpuTime) << " sec\n  "
      << "CPU simulation  time " << setprecision(4) << (finished_cpuTime - starting_cpuTime) << " sec\n  "
      << setw(2) << sc_report_handler::get_count(SC_INFO)    << " informational messages" << "\n  "
      << setw(2) << sc_report_handler::get_count(SC_WARNING) << " warnings" << "\n  "
      << setw(2) << sc_report_handler::get_count(SC_ERROR)   << " errors"   << "\n  "
      << setw(2) << sc_report_handler::get_count(SC_FATAL)   << " fatals"   << "\n\n"
      << kind << " " << (errors?"FAILED":"PASSED")
    );
    return (errors?1:0);
  }

}
