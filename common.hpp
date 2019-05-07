/**
 * @file common.hpp
 */

#ifndef COMMON_HPP
#define COMMON_HPP
#include <systemc>
#include <cstdint>
#include "coord.hpp"
#define FIFO_DEPTH 1
#define INT_WIDTH 16
using RawData_t = Coordinate;
using FixedPt_t = sc_dt::sc_fixed<32,INT_WIDTH>; // +/- 32767.9999
#endif/*COMMON_HPP*/
