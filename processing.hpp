/**
 * @file processing.hpp
 * @brief Synthesizable module that computes the magnitude of a 3-dimensional
 *        vector.
 */
#ifndef PROCESSING_HPP
#define PROCESSING_HPP
#include "common.hpp"
#include <systemc>
SC_MODULE( Processing_module )
{
  SC_CTOR( Processing_module );
  ~Processing_module( void );
  sc_core::sc_fifo_in <RawData_t>    input_port  { "input_port"  };
  sc_core::sc_out<FixedPt_t>         output_port { "output_port" };
  sc_core::sc_in<bool>               clk_port    { "clk_port"    };
private:
  void processing_thread( void );
};
#endif/*PROCESSING_HPP*/
