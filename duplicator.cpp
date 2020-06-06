/**
 * @file duplicator.cpp
 */
#include "duplicator.hpp"
#include "report.hpp"
using namespace sc_core;
namespace {
  char const * const MSGID{ "/Doulos/Example/Modern/Duplicator_module" };
}

//..............................................................................
Duplicator_module::Duplicator_module( sc_module_name instance ) //< Constructor
: sc_module( instance )
{
  // Connectivity
  out1_xport.bind( out1_fifo );
  out2_xport.bind( out2_fifo );
  // Process
  auto m = this;
  sc_spawn( [m]{
      for(;;) {
        RawData_t v = m->input_port->read();
        INFO( DEBUG, "Duplicating " << v );
        m->out1_fifo.write( v );
        m->out2_fifo.write( v );
      }
    }, "duplicator_thread" );
}
