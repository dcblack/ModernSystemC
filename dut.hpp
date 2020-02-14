/**
 * @file dut.hpp
 */
#ifndef DUT_HPP
#define DUT_HPP
#include "common.hpp"
#include <systemc>
#include <memory>
struct Processing_module;
struct Dut_module : sc_core::sc_module
{
  /**
   * Ports
   */
  sc_core::sc_port<sc_core::sc_fifo_in_if<RawData_t>>     input_port { "input_port" };
  sc_core::sc_export<sc_core::sc_signal_in_if<FixedPt_t>> out_xport  { "out_xport"  };
  /**
   * Constructors
   */
  Dut_module( sc_core::sc_module_name instance );
  ~Dut_module( void );
  /**
   * Ports
   */
  std::unique_ptr<Processing_module> process;
  std::unique_ptr<sc_core::sc_clock> clock;
  sc_core::sc_buffer<FixedPt_t>      result_buffer { "result_buffer" };
};
#endif/*DUT_HPP*/
