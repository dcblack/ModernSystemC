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
    objections.insert( m_name );
    std::string note{ "Raising objection " };
    note += m_name;
    SC_REPORT_INFO_VERB( MSGID, note.c_str(), sc_core::SC_DEBUG );
    ++created;
  }
  ~Objection() ///< Remove an objection
  {
    auto elt = objections.find( m_name );
    sc_assert( elt != objections.end() );
    objections.erase( elt );
    if( objections.empty() and sc_core::sc_is_running() ) 
    {
      sc_core::sc_spawn( [&]()
      {
        sc_core::wait( sc_core::SC_ZERO_TIME );
        if( objections.empty() ) {
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
  static size_t total() { return created; } ///< Return total times used
  static size_t count() { return objections.size(); } ///< Return the outstanding objections
private:
  std::string m_name;
  // Static stuff
  static constexpr const char* const  MSGID { "/Doulos/Objection" };
  inline static size_t                created{ 0u };
  inline static std::set<std::string> objections{};
};
#endif/*OBJECTION_HPP*/
