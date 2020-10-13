#ifndef SC_TIME_LITERALS_HPP
#define SC_TIME_LITERALS_HPP

// Description
// -----------
//
// This header makes time specification more natural and convenient:
//
//    15.3_ns, 0.1_us, 0_sec, 1_min
//
// Usage
// -----
//
// In line with the Modern C++ standard's std::literals namespace, this feature must be
// explicitly enabled by specifying the nested namespace:
//
//    using namespace sc_core::literals;
//
// Rationale
// ---------
//
// This addition to SystemC makes the "language of SystemC" feel more natural and succinct
// than the clunky specification of `sc_time( double, units )`. It also continues to remain
// optional, while allowing those wanting a more modern coding style to do so.
//
// Consider the follow contrasts between old and new:
//
//    wait( 10.1, SC_NS ); /* vs */ wait( 10.1_ns );
//
//    With the old, it is necessary to use awkward SHOUTING about the time units.
//
// Q: Why didn't we just use the <chrono> definitions?
// A: Because they have a very different underlying system of time and the notion of time used in
//    SystemC currently has a number of internal representation issues that would make it awkward
//    to add without a much more substantial set of changes. This addition is relatively trivial,
//    provides a significant improvement for little effort. If a future effort revamped SystemC to
//    define a systemc_clock compatible with <chrono>, this minor addition would seemlessly continue
//    to work.

#if __cplusplus >= 201103L

// Allow --pedantic --Wall to compile without warning about internal issues in <systemc>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma GCC   diagnostic push
#pragma GCC   diagnostic ignored "-Wunused-parameter"
#include <systemc>
#pragma clang diagnostic pop
#pragma GCC   diagnostic pop

namespace sc_core {
  namespace literals {

    inline sc_core::sc_time operator "" _day (long double val)        { return sc_core::sc_time( val        , sc_core::SC_SEC )*3600*24; }
    inline sc_core::sc_time operator "" _day (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_SEC )*3600*24; }
    inline sc_core::sc_time operator "" _hr  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_SEC )*3600;    }
    inline sc_core::sc_time operator "" _hr  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_SEC )*3600;    }
    inline sc_core::sc_time operator "" _min (long double val)        { return sc_core::sc_time( val        , sc_core::SC_SEC )*60;      }
    inline sc_core::sc_time operator "" _min (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_SEC )*60;      }
    inline sc_core::sc_time operator "" _sec (long double val)        { return sc_core::sc_time( val        , sc_core::SC_SEC );         }
    inline sc_core::sc_time operator "" _sec (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_SEC );         }
    inline sc_core::sc_time operator "" _ms  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_MS  );         }
    inline sc_core::sc_time operator "" _ms  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_MS  );         }
    inline sc_core::sc_time operator "" _us  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_US  );         }
    inline sc_core::sc_time operator "" _us  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_US  );         }
    inline sc_core::sc_time operator "" _ns  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_NS  );         }
    inline sc_core::sc_time operator "" _ns  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_NS  );         }
    inline sc_core::sc_time operator "" _ps  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_PS  );         }
    inline sc_core::sc_time operator "" _ps  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_PS  );         }
    inline sc_core::sc_time operator "" _fs  (long double val)        { return sc_core::sc_time( val        , sc_core::SC_FS  );         }
    inline sc_core::sc_time operator "" _fs  (unsigned long long val) { return sc_core::sc_time( double(val), sc_core::SC_FS  );         }

}}

#endif

#endif/*SC_TIME_LITERALS_HPP*/
