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
  char const * const MSGID{ "/Doulos/Example/Magnitude/Checker_module" };
}

//..............................................................................
Checker_module::Checker_module( sc_module_name instance ) //< Constructor
{
  SC_HAS_PROCESS( Checker_module );
  SC_METHOD( anticipate_method );
  SC_METHOD( received_method );
    sensitive << result_port;
    dont_initialize();
  SC_THREAD( checker_thread );
}

//..............................................................................
Checker_module::~Checker_module( void ) = default;

//..............................................................................
void Checker_module::anticipate_method( void )
{
  RawData_t v;
  while( rawin_port->nb_read( v ) ) {
    FixedPt_t magnitude = FP::fpsqrt( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );
    INFO( DEBUG, "From " << v << " expected data " << magnitude.to_string() << " arrived" );
    expect_fifo.nb_put( magnitude );
  }
  next_trigger( rawin_port->data_written_event() );
}

//..............................................................................
void Checker_module::received_method( void )
{
  auto d = result_port->read();
  INFO( DEBUG, "Incoming data " << d << " arrived" );
  result_fifo.put( d );
}

//..............................................................................
void Checker_module::checker_thread( void )
{
  const FixedPt_t allowable( 1.0/64.0 );
  FixedPt_t expect_value, actual_value, difference;
  REPORT( INFO, "Preparing checker" );
  for(;;) {
    // Is anything expected?
    INFO( DEBUG, "Waiting for expected" );
    expect_value = expect_fifo.get();
    INFO( DEBUG, "Obtained expected" );
    {
      Objection verifying{ name() };
      // Wait for result
      INFO( DEBUG, "Waiting for actual" );
      actual_value = result_fifo.get();
      // Compare result
      MESSAGE( "Expect:" << expect_value.to_string()
            << " Actual:" << actual_value.to_string()
            << " at " << sc_time_stamp()
      );
      difference = expect_value - actual_value;
      if( difference < 0 ) difference = -difference;
      if( difference > allowable ) {
        MESSAGE( " FAILURE" );
        MEND( ALWAYS );
        ++mismatches;
      } else {
        MESSAGE( " SUCCESS" );
        MEND( DEBUG );
      }
      ++verified_count;
    }
  }
}

//..............................................................................
void Checker_module::end_of_simulation( void )
{
  INFO( ALWAYS, "Verified " << std::to_string( verified_count ) << " transactions" );
  INFO( ALWAYS, "Had " << std::to_string( mismatches ) << " mismatches" );
  INFO( ALWAYS, "Objected " << Objection::total() << " times" );
}

