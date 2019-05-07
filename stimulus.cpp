/**
 * @file stimulus.cpp
 */
#include "stimulus.hpp"
#include "objection.hpp"
#include "report.hpp"
#include <random>
using namespace sc_core;
namespace {
  char const * const MSGID{ "/Doulos/Example/Magnitude/Stimulus_module" };
}

//..............................................................................
Stimulus_module::Stimulus_module( sc_module_name instance ) //< Constructor
{
  SC_HAS_PROCESS( Stimulus_module );
  SC_THREAD( stimulus_thread );
}

//..............................................................................
Stimulus_module::~Stimulus_module( void ) = default;

//..............................................................................
void Stimulus_module::stimulus_thread( void )
{
  Objection generating_data( name() );
  unsigned int seed = 1;
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution (-128.0,128.0);
  std::vector<double> directed = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
  size_t samples = directed.size()*directed.size()*directed.size();
  REPORT( INFO, "Sending " << samples << " directed samples" );
  for( auto const& x : directed ) {
    for( auto const& y : directed ) {
      for( auto const& z : directed ) {
        Coordinate xyz{ x, y, z };
        rawout_port->write( xyz );
        INFO( DEBUG, "Sent " << xyz );
      }
    }
  }
  samples = 1000;
  REPORT( INFO, "Sending " << samples << " random samples" );
  for( size_t n=0; n<samples; ++n ) {
    Coordinate xyz = { distribution(generator), distribution(generator), distribution(generator) };
    rawout_port->write( xyz );
    INFO( DEBUG, "Sent " << xyz );
  }
  REPORT( INFO, "Stimulus complete" );
}

