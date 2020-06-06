/**
 * @file  top.cpp
 * @brief Top-level interconnect implementation
 */
#include "top.hpp"
#include "stimulus.hpp"
#include "duplicator.hpp"
#include "dut.hpp"
#include "checker.hpp"
#include "sc_cxx11.hpp"
using namespace sc_core;

//..............................................................................
Top_module::Top_module( sc_module_name instance ) //< Constructor
: sc_module( instance )
{
  /**
   * Instantiate
   */
  stim    = std::make_unique<Stimulus_module>   ( "stim"    );
  dupl    = std::make_unique<Duplicator_module> ( "dupl"    );
  dut     = std::make_unique<Dut_module>        ( "dut"     );
  check   = std::make_unique<Checker_module>    ( "check"   );
  /**
   * Connect
   */
  stim->rawout_port   .bind( raw_fifo         );
  dupl->input_port    .bind( raw_fifo         );
  dut->input_port     .bind( dupl->out1_xport );
  check->result_port  .bind( dut->out_xport   );
  check->rawin_port   .bind( dupl->out2_xport );
}

//..............................................................................
Top_module::~Top_module( void ) = default;
