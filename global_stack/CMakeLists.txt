cmake_minimum_required(VERSION 3.21)

project(
  integrate
  DESCRIPTION "Using global stask algorithm to integrate in parallel"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE is not specified, using Release by default")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

set(SRC_DIR src)
set(INC_DIR inc)

file(GLOB SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

option(VERBOSE "Additional prints of debug information" OFF)
if (VERBOSE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE VERBOSE=1)
endif()

option(TIME "Additional prints of elapsed time" OFF)
if (TIME)
  target_compile_definitions(${PROJECT_NAME} PRIVATE TIME=1)
endif()

if(NOT DEFINED NTHREADS)
  message(STATUS "NTHREADS is not set, defaulting to std::thread::hardware_concurrency()")
endif(NOT DEFINED NTHREADS)

if (DEFINED NTHREADS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NTHREADS=${NTHREADS})
endif(DEFINED NTHREADS)
