/**
 * @file   objection.hpp
 * @brief  Stop SystemC simulation when the last objection is removed.
 */
#ifndef OBJECTION_HPP
#define OBJECTION_HPP
#include <systemc>
#include <string>
#include <set>
struct Objection
{
  Objection( const std::string& name ) ///< Create an objection
  : m_name( name )
  {
    sc_assert( name.size() > 0 );
    collection().insert( m_name );
    std::string note{ "Raising objection " };
    note += m_name;
    SC_REPORT_INFO_VERB( MSGID, note.c_str(), sc_core::SC_DEBUG );
    (void) total( true );
  }
  ~Objection( void ) ///< Remove an objection
  {
    auto elt = collection().find( m_name );
    sc_assert( elt != collection().end() );
    collection().erase( elt );
    if( collection().empty() and sc_core::sc_is_running() ) 
    {
      sc_core::sc_spawn( [&]()
      {
        sc_core::wait( sc_core::SC_ZERO_TIME );
        if( Objection::collection().empty() ) {
          std::string note{ "Shutting down " };
          note += m_name;
          SC_REPORT_INFO_VERB( MSGID, note.c_str(), sc_core::SC_NONE );
          sc_core::sc_stop();
        }
      });
    } else {
      std::string note{ "Removing objection " };
      note += m_name;
      SC_REPORT_INFO_VERB( MSGID, note.c_str(), sc_core::SC_DEBUG );
    }
  }
  static size_t total( bool incr = false ); ///< Return total times used
  static size_t count( void ); ///< Return the number of objections
private:
  std::string m_name;
  static std::set<std::string>& collection( void );
  static constexpr const char* const MSGID { "/Doulos/Objection" };
};
#endif/*OBJECTION_HPP*/

