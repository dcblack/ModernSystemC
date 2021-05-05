// The following was obtained from http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows

#include "wallclock.hpp"
#include <time.h>
#include <sys/utsname.h>
#ifdef _MSC_VER
#  include <Windows.h>
#else
#  include <sys/time.h>
#  include <ctime>
#endif
#if __cplusplus >= 201103
#  include <chrono>
namespace {
  using hres_clock = std::chrono::high_resolution_clock;
  using ns_t = std::chrono::duration<double,std::nano>;
  struct Wall_time {
    Wall_time() : m_timestart ( hres_clock::now() ) { }
    std::chrono::nanoseconds elapsed() const { return hres_clock::now() - m_timestart; }
    double seconds() const { return elapsed()/ns_t(1.0)*1.0e-9; }
  private:
    const hres_clock::time_point m_timestart;
  };
  Wall_time t0;
}
double get_wall_time(){ return t0.seconds(); }
#endif

//  Windows
#ifdef _WIN32
#include <Windows.h>
//------------------------------------------------------------------------------
#if __cplusplus < 201103
double get_wall_time(){
  LARGE_INTEGER time,freq;
  if (!QueryPerformanceFrequency(&freq)){
    //  Handle error
    return 0;
  }
  if (!QueryPerformanceCounter(&time)){
    //  Handle error
    return 0;
  }
  return (double)time.QuadPart / freq.QuadPart;
}
#endif
//------------------------------------------------------------------------------
double get_cpu_time(){
  FILETIME a,b,c,d;
  if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
    //  Returns total user time.
    //  Can be tweaked to include kernel times as well.
    return
      (double)(d.dwLowDateTime |
      ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
  }else{
    //  Handle error
    return 0;
  }
}

//  Posix/Linux
#else
#include <sys/time.h>
//------------------------------------------------------------------------------
#if __cplusplus < 201103
double get_wall_time(){
  struct timeval time;
  if (gettimeofday(&time,NULL)){
    //  Handle error
    return 0;
  }
  return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
#endif
//------------------------------------------------------------------------------
double get_cpu_time(){
  return (double)clock() / CLOCKS_PER_SEC;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Self-test
#ifdef WALLCLOCK_SELFTEST
#include <iostream>
#include <cmath>
using namespace std;

int main(){

  cout << "Testing get_wall_time() and get_cpu_time()" << endl;
  //  Start Timers
  double wall0 = get_wall_time();
  double cpu0  = get_cpu_time();

  //  Perform some computation.
  volatile double sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (long long i = 1; i < 1000000000; i++){
      sum += log((double)i);
  }

  //  Stop timers
  double wall1 = get_wall_time();
  double cpu1  = get_cpu_time();

  cout << "Wall Time = " << wall1 - wall0 << endl;
  cout << "CPU Time  = " << cpu1  - cpu0  << endl;

  //  Prevent Code Elimination
  cout << endl;
  cout << "Sum = " << sum << endl;

}
#endif/*defined WALLCLOCK_SELFTEST*/

///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 by Doulos. All rights reserved.
//END wallclock.cpp
