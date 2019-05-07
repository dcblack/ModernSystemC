/**
 * @file objection.cpp
 */
#include "objection.hpp"

//..............................................................................
size_t Objection::total( bool incr )
{
  static size_t total = 0u;
  total += ( incr == true ) ? 1 : 0;
  return total;
}

//..............................................................................
size_t Objection::count( void )
{
  return collection().size();
}

//..............................................................................
std::set<std::string>& Objection::collection( void )
{
  static std::set<std::string> objections;
  return objections;
}

