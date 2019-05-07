/**
 * @file stimulus.hpp
 * @brief Generates stimulus to test the design
 */
#ifndef STIMULUS_HPP
#define STIMULUS_HPP
#include "common.hpp"
#include <systemc>
SC_MODULE( Stimulus_module )
{
  SC_CTOR( Stimulus_module );
  ~Stimulus_module( void );
  sc_core::sc_fifo_out<RawData_t>  rawout_port { "rawout_port" };
private:
  void stimulus_thread( void );
};
#endif/*STIMULUS_HPP*/
