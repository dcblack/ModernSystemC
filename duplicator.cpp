/**
 * @file duplicator.cpp
 */
#include "duplicator.hpp"
#include "report.hpp"
using namespace sc_core;
namespace {
  char const * const MSGID{ "/Doulos/Example/Magnitude/Duplicator_module" };
}

//..............................................................................
Duplicator_module::Duplicator_module( sc_module_name instance ) //< Constructor
{
  SC_HAS_PROCESS( Duplicator_module );
  SC_THREAD( duplicator_thread );
  // Connectivity
  out1_xport.bind( out1_fifo );
  out2_xport.bind( out2_fifo );
}

//..............................................................................
Duplicator_module::~Duplicator_module( void ) = default;

//..............................................................................
void Duplicator_module::duplicator_thread( void )
{
  RawData_t v;
  for(;;) {
    v = input_port->read();
    INFO( DEBUG, "Duplicating " << v );
    out1_fifo.write( v );
    out2_fifo.write( v );
  }
}
