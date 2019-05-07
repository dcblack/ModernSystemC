/**
 * @file duplicator.hpp
 * @brief Takes a single input and copies it out to two downstream
 * connections.
 */
#ifndef DUPLICATOR_HPP
#define DUPLICATOR_HPP
#include "common.hpp"
#include <systemc>
struct Duplicator_module : sc_core::sc_module
{
  Duplicator_module( sc_core::sc_module_name instance );
  ~Duplicator_module( void );
  sc_core::sc_fifo_in <RawData_t>                       input_port { "input_port" };
  sc_core::sc_export<sc_core::sc_fifo_in_if<RawData_t>> out1_xport { "out1_xport" };
  sc_core::sc_export<sc_core::sc_fifo_in_if<RawData_t>> out2_xport { "out2_xport" };
private:
  sc_core::sc_fifo<RawData_t> fifo1 { "fifo1", FIFO_DEPTH };
  sc_core::sc_fifo<RawData_t> fifo2 { "fifo2", FIFO_DEPTH };
  void duplicator_thread( void );
};
#endif/*DUPLICATOR_HPP*/
