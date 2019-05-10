/**
 * @file fpsqrt.hpp
 *
 * Computing the square root of a fixed point integer.
 * 
 * The algorithms can be easily extended to other formats.
 * 
 * Algorithm and code Author: Christophe Meessen 1993. 
 * Initially published in: usenet comp.lang.c, Thu, 28 Jan 1993 08:35:23 GMT, 
 * Modified to use SystemC types by David Black 2019.
 * Subject: Fixed point sqrt ; by Meessen Christophe
 */
#ifndef FSQRT_HPP
#define FSQRT_HPP
#include "common.hpp"
#include <systemc>
struct FP
{

/**
 * FixedPt_t fpsqrt( FixedPt_t v );
 *
 * Compute FixedPt_t to FixedPt_t square root
 * RETURNS the FixedPt_t point square root of v (FixedPt_t)
 * REQUIRES v is positive
 */

static FixedPt_t fpsqrt ( FixedPt_t X );

};
#endif/*FSQRT_HPP*/
