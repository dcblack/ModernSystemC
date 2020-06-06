/**
 * @file common.hpp
 */

#ifndef COMMON_HPP
#define COMMON_HPP
#include <systemc>
#include <cstdint>
#include "coord.hpp"
#define FIFO_DEPTH 1
#define BINARY_PT 16
using RawData_t = Coordinate;
using FixedPt_t = sc_dt::sc_fixed<32,BINARY_PT>; // +/- 32767.9999
#endif/*COMMON_HPP*/
