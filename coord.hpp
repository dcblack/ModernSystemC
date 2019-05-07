/**
 * @file   coord.hpp
 * @brief  3-dimensional coordinate using floating point
 */
#include <systemc>
#include <string>
#include <ostream>
#include <valarray>
struct Coordinate
{
  using T = double;
  Coordinate( const T& x, const T& y, const T& z ): m_data( {x, y, z} ) {}
  Coordinate( void ) = default;
  ~Coordinate( void ) = default;
  Coordinate( const Coordinate& rhs ) : m_data( rhs.m_data ) {}
  Coordinate( Coordinate&& rhs ) : m_data( std::move( rhs.m_data ) ) {}
  Coordinate& operator=( const Coordinate& rhs ) {
    if( this != &rhs ) {
      m_data = rhs.m_data;
    }
    return *this;
  }
  Coordinate& operator=( Coordinate&& rhs ) {
    m_data = std::move( rhs.m_data );
    return *this;
  }
  bool operator==( const Coordinate& rhs ) const {
    return *this == rhs;
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
  const Coordinate& operator-( const Coordinate& rhs ) {
    return Coordinate(*this) -= rhs;
  }
  Coordinate operator*( T rhs ) {
    Coordinate result( *this );
    for( auto& v : result.m_data ) v *= rhs;
    return std::move(result);
  }
  friend Coordinate operator*( T lhs, Coordinate rhs );
  friend std::ostream& operator<<( std::ostream& os, const Coordinate& rhs );
private:
  std::valarray<T> m_data;
};

