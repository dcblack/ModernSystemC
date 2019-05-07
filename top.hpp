/**
 * @file top.hpp
 */
#ifndef TOP_HPP
#define TOP_HPP
#include "common.hpp"
#include <systemc>
#include <memory>
struct Stimulus_module;
struct Duplicator_module;
struct Processing_module;
struct Checker_module;
struct Top_module : sc_core::sc_module
{
  Top_module( sc_core::sc_module_name instance );
  ~Top_module( void );
  std::unique_ptr<Stimulus_module>   stim;
  std::unique_ptr<Duplicator_module> dupl;
  std::unique_ptr<Processing_module> process;
  std::unique_ptr<Checker_module>    check;
  std::unique_ptr<sc_core::sc_clock> clock;
  sc_core::sc_fifo<RawData_t>        raw_fifo      { "raw_fifo", FIFO_DEPTH };
  sc_core::sc_buffer<FixedPt_t>      result_buffer { "result_buffer" };
};
#endif/*TOP_HPP*/
