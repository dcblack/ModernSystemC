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
struct Dut_module;
struct Checker_module;
struct Top_module : sc_core::sc_module
{
  Top_module( sc_core::sc_module_name instance );
  ~Top_module( void );
  /**
   * Components
   */
  std::unique_ptr<Stimulus_module>   stim;
  std::unique_ptr<Duplicator_module> dupl;
  std::unique_ptr<Dut_module>        dut;
  std::unique_ptr<Checker_module>    check;
  sc_core::sc_fifo<RawData_t>        raw_fifo      { "raw_fifo", FIFO_DEPTH };
};
#endif/*TOP_HPP*/
