// The following was obtained from http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows

#include "wallclock.hpp"
#include <time.h>
#include <sys/utsname.h>
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

//  Windows
#ifdef _WIN32
#include <Windows.h>
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
double get_wall_time(){
  struct timeval time;
  if (gettimeofday(&time,NULL)){
    //  Handle error
    return 0;
  }
  return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double get_cpu_time(){
  return (double)clock() / CLOCKS_PER_SEC;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Self-test
#ifdef TEST_WALLCLOCK
#include <iostream>
#include <cmath>
using namespace std;

int main(){

  cout << "Testing get_wall_time() and get_cpu_time()" << endl;
  //  Start Timers
  double wall0 = get_wall_time();
  double cpu0  = get_cpu_time();

  //  Perform some computation.
  double sum = 0;
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
#endif
//EOF
