cmake_minimum_required(VERSION 3.3)
project(test_SMESH CXX)


# --------------------------------------------------------------------------- #
# SETTINGS
# --------------------------------------------------------------------------- #
# Force C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# --------------------------------------------------------------------------- #
# Catch
# --------------------------------------------------------------------------- #
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)


# --------------------------------------------------------------------------- #
# BOOST
# --------------------------------------------------------------------------- #
message(STATUS "Searching for Boost...")
find_package(Boost REQUIRED COMPONENTS filesystem thread serialization)

if (MSVC)
  # find the shared boost libs
  add_definitions(-DBOOST_ALL_DYN_LINK)
  # set postfix for debug libs
  if(NOT CMAKE_DEBUG_POSTFIX)
      set(CMAKE_DEBUG_POSTFIX d)
  endif()
endif()


# --------------------------------------------------------------------------- #
# PTHREAD
# --------------------------------------------------------------------------- #
if(UNIX)
    find_package(Threads REQUIRED)
else(UNIX)
  set(PTHREAD_INCLUDE_DIRS "" CACHE PATH "pthread include directory.")
  if(NOT EXISTS ${PTHREAD_INCLUDE_DIRS})
      message(FATAL_ERROR "pthread include directory is required.")
  endif()
  include_directories(${PTHREAD_INCLUDE_DIRS})

  set(PTHREAD_LIB_DIRS "" CACHE PATH "pthread library directory.")
  if(NOT EXISTS ${PTHREAD_LIB_DIRS})
      message(FATAL_ERROR "pthread library directory is required.")
  endif()
  link_directories(${PTHREAD_LIB_DIRS})
endif(UNIX)


# --------------------------------------------------------------------------- #
# OpenCASCADE
# --------------------------------------------------------------------------- #
find_package(OpenCASCADE REQUIRED)
include_directories(${OpenCASCADE_INCLUDE_DIR})


# --------------------------------------------------------------------------- #
# VTK
# --------------------------------------------------------------------------- #
message(STATUS "Searching for VTK...")
find_package(VTK REQUIRED COMPONENTS CommonCore CommonDataModel FiltersVerdict)


# --------------------------------------------------------------------------- #
# SMESH
# --------------------------------------------------------------------------- #
find_package(SMESH REQUIRED)


# --------------------------------------------------------------------------- #
# Test SMESH
# --------------------------------------------------------------------------- #
add_executable(test_SMESH src/SMESH.t.cpp)
target_link_libraries(test_SMESH Catch2::Catch2 ${SMESH_LIBRARIES})
catch_discover_tests(test_SMESH)

install(TARGETS test_SMESH
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/tests
)
