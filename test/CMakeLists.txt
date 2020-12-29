cmake_minimum_required(VERSION 3.3)
project(test_SMESH CXX)


# --------------------------------------------------------------------------- #
# Catch
# --------------------------------------------------------------------------- #
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)


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
# Test NETGENPlugin
# --------------------------------------------------------------------------- #
add_executable(test_Netgen src/Netgen.t.cpp)
target_link_libraries(test_Netgen Catch2::Catch2 ${SMESH_LIBRARIES})
catch_discover_tests(test_Netgen)

install(TARGETS test_Netgen
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/tests
)
