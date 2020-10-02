/**
 * @file report.hpp
 * @brief Improve reporting with macros, more overloads on `operator<<`,
 *        and other enhancements to `sc_report_handler`.
 *
 * See `ABOUT_REPORT.md` for more information.
 */
#ifndef REPORT_HPP
#define REPORT_HPP
#include <systemc>
#include <tlm>
#include <string>
#include <sstream>
#include <iomanip>
extern std::ostringstream mout;
#define HEX std::hex << std::showbase
#define DEC std::dec << std::noshowbase << std::setfill(' ')

#ifdef __SYNTHESIS__
  #define REPORT(type,stream)
  #define ASSERT(expr,stream)
  #define SC_ALWAYS SC_NONE
  #define SC_NEVER  (1<<14)
  #define SC_HYPER  1024
  #define DEVID (std::string("(")+name()+")").c_str()
  #define NOINFO(level,stream)
  #define INFO(level,stream)
  #define MESSAGE(stream)
  #define MEND(level)
  #define RULER(c)
  #define TODO(stream)
  #define NOT_YET_IMPLEMENTED()
  #define DELETE_THIS_LINE(lno,message)
#else

// For type: WARNING, ERROR, FATAL
#define REPORT(type,stream)                      \
do {                                             \
  mout << DEC << stream << std::ends;            \
  std::string str = mout.str(); mout.str("");    \
  SC_REPORT_##type( MSGID, str.c_str() );        \
} while (0)
//
// Use the following to (A) add more information in the event of failure, and
// and (B) control sc_assert behavior (i.e. not unconditional abort on failure).
#ifndef NDEBUG
#define ASSERT(expr,stream) do {\
  if(!(expr)) REPORT(FATAL, "Assertion failed: " << # expr << ".  " << stream );\
} while (0)
#else
#define ASSERT(expr,stream)
#endif
//
#define SC_ALWAYS SC_NONE
#define SC_NEVER  16*KB
#define SC_HYPER  1024
#define DEVID ((std::string("(")+name()+")").c_str())
#define NOINFO(level,stream)
// For level: NONE, LOW, MEDIUM, HIGH, DEBUG
#define INFO(level,stream)                                                          \
do {                                                                                \
  if( sc_core::sc_report_handler::get_verbosity_level() >= (sc_core::SC_##level) ) {\
    mout << DEC << stream << std::ends; auto now = sc_time_stamp();                 \
    if( now > SC_ZERO_TIME or sc_get_status() >= SC_START_OF_SIMULATION ) {         \
      mout << std::dec << stream << " at " << sc_time_stamp();                      \
    }                                                                               \
    if( (sc_core::SC_##level) > sc_core::SC_DEBUG ) {                               \
      std::string id{"DEBUG("};                                                     \
      id+=__FILE__ ; id+=":"; id+=std::to_string(__LINE__)+")";                     \
      size_t p0=id.find("/"),p1=id.find_last_of("/");                               \
      if(p1!=std::string::npos) id.erase(p0,p1-p0+1);                               \
      std::string str = mout.str(); mout.str("");                                   \
      SC_REPORT_INFO_VERB( id.c_str(), str.c_str(), (sc_core::SC_##level) );        \
    } else {                                                                        \
      std::string str = mout.str(); mout.str("");                                   \
      SC_REPORT_INFO_VERB( MSGID, str.c_str(), (sc_core::SC_##level) );             \
    }                                                                               \
  }                                                                                 \
} while (0)
//
#define MESSAGE(stream) do { mout << stream; } while(0)
#define MEND(level) do {                                                            \
  if( sc_core::sc_report_handler::get_verbosity_level() >= (sc_core::SC_##level) ) {\
    mout << std::ends;                                                              \
    std::string str = mout.str(); mout.str("");                                     \
    SC_REPORT_INFO_VERB( MSGID, str.c_str(), (sc_core::SC_##level));                \
  }                                                                                 \
  mout.str( "" );                                                                   \
} while (0)
#define RULER(c) MESSAGE( std::string( 80, c ) << "\n" )
//
#define TODO(stream) REPORT( WARNING, "TODO: " << stream )
#define NOT_YET_IMPLEMENTED() REPORT( WARNING, __func__ << " is not yet implemented." )
//
struct DELETE_THIS
{
  DELETE_THIS( char const * const filename, int lineno, char const * const message )
  {
    ::sc_core::sc_report_handler::report(  \
            ::sc_core::SC_WARNING, "Code incomplete", message, filename, lineno );
  }
};
#define DELETE_THIS_LINE(lno,message) const DELETE_THIS lno{ __FILE__, __LINE__, #message }

#endif/*__SYNTHESIS__*/

#endif/*REPORT_HPP*/
