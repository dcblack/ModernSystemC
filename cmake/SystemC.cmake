#!cmake .

# Any important Modern C++ defaults
# add_compile_definitions( )
# SystemC specific needs
set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})
find_package(SystemCLanguage CONFIG REQUIRED)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD} CACHE STRING
     "C++ standard to build all targets. Supported values are 98, 11, and 14.")
set (CMAKE_CXX_STANDARD_REQUIRED ${SystemC_CXX_STANDARD_REQUIRED} CACHE BOOL
     "The with CMAKE_CXX_STANDARD selected C++ standard is a requirement.")
link_libraries(SystemC::systemc)

# Things that affect all targets
set(shared_env LD_LIBRARY_PATH=${CMAKE_PREFIX_PATH}/lib DYLD_LIBRARY_PATH=${CMAKE_PREFIX_PATH}/lib)

#find_package( Boost 1.65 REQUIRED )
#find_package( yaml-cpp CONFIG REQUIRED )

add_custom_target(run
   time env ${shared_env} ./${TARGET_EXECUTABLE} ${ARGS} 2>&1 | tee ${TARGET_EXECUTABLE}.log
   COMMENT "Running program ${TARGET_EXECUTABLE}"
   USES_TERMINAL
   )
