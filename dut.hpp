/**
 * @file dut.hpp
 */
#ifndef DUT_HPP
#define DUT_HPP
#include "common.hpp"
#include <systemc>
#include <memory>
/**
 * Forward declarations
 */
// YOUR DECLARTIONS HERE

struct Dut_module : sc_core::sc_module
{
  /**
   * Ports
   */
  // YOUR PORTS HERE

  /**
   * Constructors
   */
  Dut_module( sc_core::sc_module_name instance );
  ~Dut_module( void );

  /**
   * Components
   */
  // YOUR INSTANCES HERE

};
#endif/*DUT_HPP*/
