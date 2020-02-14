/**
 * @file top.hpp
 */
#ifndef TOP_HPP
#define TOP_HPP
#include "common.hpp"
#include <systemc>
#include <memory>
/**
 * Forward declarations
 */
// YOUR DECLARATIONS HERE

struct Top_module : sc_core::sc_module
{
  /**
   * Constructors
   */
  Top_module( sc_core::sc_module_name instance );
  ~Top_module( void );
  /**
   * Components
   */
  // YOUR INSTANCES HERE

};
#endif/*TOP_HPP*/
