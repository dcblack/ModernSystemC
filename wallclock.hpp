#pragma once

#include <cstdint>

// get_wall_time() returns wall wall clock time since epoch in seconds - reasonable for simulator
// performance measurements. Works for Linux, OS X and Windows.
double get_wall_time(void);

// get_cpu_time() returns wall CPU clock time since start of program in seconds - reasonable for simulator
// performance measurements. Does not include sub-processes (i.e. system() calls).
// Works for Linux, OS X and Windows.
double get_cpu_time(void);
//EOF
