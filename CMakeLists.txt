#!cmake .
# vim:syntax=cmake
#
# This works with SystemV versions 2.3.2 and later, which have support for
# cmake and specify SystemC_CXX_STANDARD.
# 
# REQUIREMENTS:
#   Define SYSTEMC_HOME to point to install directory of SystemC (not source)
#   that has been built with CMake.
#
# See /apps/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      modern
  VERSION     0.2 # n.n[.n[.n]]
  DESCRIPTION "Compute magnitude of x/y/z coordinates from sensors using modern SystemC and C++."
  LANGUAGES   CXX C
  )

set( default_build_type "Debug" )
include( /apps/cmake/SystemC.cmake )
add_compile_definitions( SC_INCLUDE_FX SC_INCLUDE_DYNAMIC_PROCESSES )
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-g -Wall -Wextra -pedantic -Werror)
endif()

add_executable( modern )
target_include_directories( modern PRIVATE . )
target_sources( modern PRIVATE
  report.cpp
  wallclock.cpp
  checker.cpp
  duplicator.cpp
  fpsqrt.cpp
  dut.cpp
  processing.cpp
  stimulus.cpp
  top.cpp
  main.cpp
)

# add a target to generate API documentation with Doxygen
find_package( Doxygen REQUIRED dot )
if( DOXYGEN_FOUND )
  set( DOXYGEN_OUTPUT_DIRECTORY ../doc )
  set( DOXYGEN_IMAGE_PATH .. )
  set( DOXYGEN_EXTRACT_ALL yes )
  set( DOXYGEN_EXTRACT_PRIVATE yes )
  set( DOXYGEN_EXTRACT_STATIC yes )
  set( DOXYGEN_TOC_INCLUDE_HEADINGS 1 )
  set( DOXYGEN_EXCLUDE_PATTERNS */build*/* )
  doxygen_add_docs( docs )
endif( DOXYGEN_FOUND )
