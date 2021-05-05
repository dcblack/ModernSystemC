#pragma once

#include "systemc.hpp"
#include <string>

/* Usage: #include this file in your design. Then call Commandline::has_opt("-YOUR_SWITCH").
 * The return value will be zero if not found; otherwise, it will represent which
 * command-line argument matched. For example:
     // Following is C++17 code..
     bool debug=false;
     if ( int i = Commandline::has_opt("--debug"); i != 0 ) {
        DEBUG( "Enabling debug" );
        debug=true;
     }
 */

struct Commandline
{
  // Return index if a command-line argument beginning with opt exists; otherwise, zero
  // Optional index may be used to continue scanning from previous scan (0 =>
  // start from first)
  inline static size_t has_opt( const std::string& opt, int i=0 )
  {
    for( ++i; i < sc_core::sc_argc(); ++i ) {
      std::string arg{ sc_core::sc_argv()[ i ] };
      if( arg.find( opt ) == 0 ) return i;
    }
    return 0;
  }

private:
  [[maybe_unused]]inline constexpr static char const * const
  MSGID{ "/Doulos/Example/Commandline" };
};