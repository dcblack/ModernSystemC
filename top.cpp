/**
 * @file  top.cpp
 * @brief Top-level interconnect implementation
 *
 *                           Duplicator   Processing                     Checker
 * Stimulus                  _module      _module          sc_buffer     _module
 * _module      sc_fifo      .------.     .-----------.     .------.     .-------.
 * .------.     .------.     |     1|o--[]|> process >|[]--o|result|o--[]|>      |
 * | stim |[]--o| raw  |o--[]| dupl |     '-----^-----'     'buffer'     | check |
 * '------'     '-fifo-'     |     2|o--.       |                        |       |
 *                           '------'   |  clk -'                        |       |
 *                                      |                       raw_in   |       |
 *                                      '------------------------------[]|>      |
 *                                                                       '-------'
 */
#include "top.hpp"
#include "stimulus.hpp"
#include "duplicator.hpp"
#include "processing.hpp"
#include "checker.hpp"
using namespace sc_core;

//..............................................................................
Top_module::Top_module( sc_module_name instance ) //< Constructor
{
  /**
   * Instantiate
   */
  stim    = std::make_unique<Stimulus_module>   ( "stim"    );
  dupl    = std::make_unique<Duplicator_module> ( "dupl"    );
  process = std::make_unique<Processing_module> ( "process" );
  check   = std::make_unique<Checker_module>    ( "check"   );
  clock   = std::make_unique<sc_clock>          ( "clock"   );
  /**
   * Connect
   */
  stim->rawout_port   .bind( raw_fifo         );
  dupl->input_port    .bind( raw_fifo         );
  process->input_port .bind( dupl->out1_xport );
  process->output_port.bind( result_buffer    );
  process->clk_port   .bind( *clock           );
  check->result_port  .bind( result_buffer    );
  check->rawin_port   .bind( dupl->out2_xport );
}

//..............................................................................
Top_module::~Top_module( void ) = default;
