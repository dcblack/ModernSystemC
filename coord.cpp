/**
 * @file coord.cpp
 */
#include "coord.hpp"
using namespace sc_core;
using namespace sc_dt;

//..............................................................................
Coordinate operator*( Coordinate::T lhs, Coordinate rhs ) {
  for( auto& v : rhs.m_data ) v *= lhs;
  return std::move(rhs);
}

//..............................................................................
std::ostream& operator<<( std::ostream& os, const Coordinate& rhs )
{
  os << "{" << rhs.x() << "," << rhs.y() << "," << rhs.z() << "}";
  return os;
}

