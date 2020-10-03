/**
 * @file   coord.hpp
 * @brief  3-dimensional coordinate using floating point
 */
#include <systemc>
#include <string>
#include <ostream>
#include <valarray>
#include <algorithm>
struct Coordinate
{
  using T = double;
  Coordinate( const T& x, const T& y, const T& z ): m_data( {x, y, z} ) {}
  Coordinate( void ) = default;
  // Rule of 0
  // Need comparison for sc_signal<T>
  bool operator==( const Coordinate& rhs ) const {
    return std::equal( std::begin(m_data), std::end(m_data), std::begin(rhs.m_data) );
  }
  // Convenience
  T& x( void ) { return m_data[0]; }
  T& y( void ) { return m_data[1]; }
  T& z( void ) { return m_data[2]; }
  const T& x( void ) const { return m_data[0]; }
  const T& y( void ) const { return m_data[1]; }
  const T& z( void ) const { return m_data[2]; }
  // Arithmetic
  Coordinate& operator+=( const Coordinate& rhs ) {
    m_data += rhs.m_data;
    return *this;
  }
  const Coordinate& operator+( const Coordinate& rhs ) {
    return Coordinate(*this) += rhs;
  }
  Coordinate& operator-=( const Coordinate& rhs ) {
    m_data -= rhs.m_data;
    return *this;
  }
  Coordinate operator-( const Coordinate& rhs ) {
    auto result = Coordinate(*this);
    result -= rhs;
    return result;
  }
  // Scale
  Coordinate operator*( T rhs ) {
    Coordinate result( *this );
    for( auto& v : result.m_data ) v *= rhs;
    return result;
  }
  // Scale
  friend Coordinate operator*( T lhs, Coordinate rhs )
  {
    for( auto& v : rhs.m_data ) v *= lhs;
    return rhs;
  }
  friend std::ostream& operator<<( std::ostream& os, const Coordinate& rhs )
  {
    os << "{" << rhs.x() << "," << rhs.y() << "," << rhs.z() << "}";
    return os;
  }
private:
  std::valarray<T> m_data;
};
