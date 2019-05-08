/**
 * @file checker.cpp
 */
#include "checker.hpp"
#include "objection.hpp"
#include <cmath>
#include <string>
#include "fpsqrt.hpp"
#include "report.hpp"
using namespace sc_core;
namespace {
  char const * const MSGID{ "/Doulos/Example/Modern/Checker_module" };
}

//..............................................................................
Checker_module::Checker_module( sc_module_name instance ) //< Constructor
{
  SC_HAS_PROCESS( Checker_module );
  SC_METHOD( received_method );
    sensitive << result_port;
    dont_initialize();
  SC_THREAD( checker_thread );
}

//..............................................................................
void Checker_module::received_method( void ) {
  result_fifo.put( result_port->read() );
}

//..............................................................................
void Checker_module::checker_thread( void ) {
  const FixedPt_t allowable( 1.0/64.0 );
  FixedPt_t expect_value, actual_value, difference;
  REPORT( INFO, "Preparing checker" );
  for(;;) {
    // Is anything expected?
    RawData_t v = rawin_port->read();
    FixedPt_t expect_value = FP::fpsqrt( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );
    {
      Objection verifying{ name() };
      // Wait for corresponding result
      actual_value = result_fifo.get();
      // Compare result to expected 
      difference = expect_value - actual_value;
      if( difference < 0 ) difference = -difference;
      if( difference > allowable ) {
        REPORT( ERROR, "Expect:" << expect_value.to_string()
              << " Actual:" << actual_value.to_string()
              << " at " << sc_time_stamp() << " FAILURE"
        );
        ++mismatches;
      }
      ++verified_count;
    }
  }
}

//..............................................................................
void Checker_module::end_of_simulation( void ) {
  INFO( ALWAYS, "Verified " << std::to_string( verified_count ) << " transactions\n"
             << "- Found " << std::to_string( mismatches ) << " mismatches\n"
             << "- Objected " << Objection::total() << " times" );
}
