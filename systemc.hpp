#pragma once
/** @brief Wrapper around SystemC
 *
 * Allows compiling with `--pedantic -Wall -Wextra` without suppressing things that SystemC currently violates.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma GCC   diagnostic push
#pragma GCC   diagnostic ignored "-Wunused-parameter"
#include <systemc>
#include <sc_time_literals.hpp>
#pragma clang diagnostic pop
#pragma GCC   diagnostic pop
//vim:syntax=systemc
