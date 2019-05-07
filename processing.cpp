/**
 * @file processing.cpp
 */
#include "processing.hpp"
#include "fpsqrt.hpp"
#ifndef __SYNTHESIS__
#include "report.hpp"
#endif
using namespace sc_core;
namespace {
  char const * const MSGID{ "/Doulos/Example/Magnitude/Processing_module" };
}

//..............................................................................
Processing_module::Processing_module( sc_module_name instance ) //< Constructor
{
  SC_HAS_PROCESS( Processing_module );
  SC_CTHREAD( processing_thread, clk_port.pos() );
}

//..............................................................................
Processing_module::~Processing_module( void ) = default;

//..............................................................................
void Processing_module::processing_thread( void )
{
  RawData_t v;
  FixedPt_t x, y, z, sum2, magnitude;
  wait(1);
  for(;;) {
    wait(1);
    if( input_port->nb_read( v ) ) {
      x = v.x();
      y = v.y();
      z = v.z();
      x *= x;
      y *= y;
      z *= z;
      sum2 = x + y +z;
      magnitude = FP::fpsqrt( sum2 );
      #ifndef __SYNTHESIS__
      INFO( DEBUG, "Processed " << v << " => " << magnitude.to_string() );
      #endif
      output_port->write( magnitude );
    }
  }
}
