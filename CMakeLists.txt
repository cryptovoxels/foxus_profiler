cmake_minimum_required(VERSION 3.1)
project(foxus_profiler
  VERSION 1.0.0
  DESCRIPTION "Foxus Profiler"
)

set(SOURCES
  src/perfetto.cc
  src/profiler_main.cc
)

set(BUILD_SHARED true)

if(BUILD_SHARED)
  add_library(foxus_profiler SHARED ${SOURCES})
else()
  add_library(foxus_profiler STATIC ${SOURCES})
endif()

if(ANDROID)
  find_library(log-lib log)
  target_link_libraries(foxus_profiler ${log-lib})
endif()

set_target_properties(foxus_profiler PROPERTIES PUBLIC_HEADER
  "include/cprofiler.h;include/perfetto.h;include/profiler.h")

set_property(TARGET foxus_profiler PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET foxus_profiler PROPERTY CXX_STANDARD 14)

target_include_directories(foxus_profiler
  PUBLIC include
)

target_compile_definitions(foxus_profiler PRIVATE ENABLE_PERFETTO)

install(
  TARGETS foxus_profiler
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
