#pragma once

///
// @brief get elapsed actual wall clock time - reasonable for simulator
// performance measurements. Works for Linux, OS X and Windows.
// @return wall clock time since epoch in seconds
double get_wall_time(void);

///
// @brief get elapsed CPU time since program start - reasonable for simulator
// performance measurements. Does not include sub-processes (i.e. system() calls).
// Works for Linux, OS X and Windows.
// @return returns CPU clock time since start of program in seconds
double get_cpu_time(void);
//EOF
