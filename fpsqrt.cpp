/**
 * @file fpsqrt.cpp
 *
 * Computing the square root of a fixed point integer into a 
 * fixed point integer. 
 * 
 * The algorithms can be easily extended to other number formats.
 * The algorithm uses the property that computing x² is trivial compared to the
 * sqrt. It will thus search the biggest x so that x² <= v, assuming we compute
 * sqrt(v).  
 *   
 * The algorithm tests each bit of x starting with the most significant toward
 * the less significant. It tests if the bit must be set or not. 
 * 
 * The algorithm uses the relation (x + a)² = x² + 2ax + a² to add the bit
 * efficiently. Instead of computing x² it keeps track of (x + a)² - x².
 * 
 * When computing sqrt(v), r = v - x², q = 2ax, b = a² and t = 2ax + a2. 
 * Note that the input integers are signed and that the sign bit is used in 
 * the computation. To accept unsigned integer as input, unfolding the initial
 * loop is required to handle this particular case. See the usenet discussion
 * for the proposed solution. 
 * 
 *
 * Algorithm and code Author Christophe Meessen 1993. 
 * Initially published in usenet comp.lang.c, Thu, 28 Jan 1993 08:35:23 GMT, 
 * Modified to use SystemC types by David Black 2019.
 * Subject: Fixed point sqrt ; by Meessen Christophe
 * 
 * https://groups.google.com/forum/?hl=fr%05aacf5997b615c37&fromgroups#!topic/comp.lang.c/IpwKbw0MAxw/discussion
 * Note: there was a bug in the published sqrtL2L routine. It is corrected in
 *       this implementation.
 * 
 */
#include "fpsqrt.hpp"

/**
 * FixedPt_t fpsqrt( FixedPt_t v );
 *
 * Compute FixedPt_t to FixedPt_t square root
 * RETURNS the fixed point square root of v (FixedPt_t)
 * REQUIRES v is positive
 */
FixedPt_t FP::fpsqrt ( FixedPt_t x )
{
    FixedPt_t t, q, b, r;
    r = x;
    b = 0x4000;
    q = 0;
    while( b > 0 )
    {
        t = q + b;
        if( r >= t )
        {
            r -= t;
            q = t + b; // equivalent to q += 2*b
        }
        r <<= 1;
        b >>= 1;
    }
    q /= (1<<8);
    return q;
}
