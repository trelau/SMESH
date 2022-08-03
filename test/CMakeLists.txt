cmake_minimum_required(VERSION 3.3)
project(test_SMESH CXX)


# --------------------------------------------------------------------------- #
# OPTIONS
# --------------------------------------------------------------------------- #
option(ENABLE_NETGEN "Enable Netgen" ON)


# --------------------------------------------------------------------------- #
# SETTINGS
# --------------------------------------------------------------------------- #
# Force C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ref https://conda-forge.org/docs/maintainer/knowledge_base.html#newer-c-features-with-old-sdk
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-D_LIBCPP_DISABLE_AVAILABILITY)
endif()

if(CMAKE_SIZEOF_VOID_P STREQUAL 8)
    add_definitions(-D_OCC64)
    add_definitions(-DSALOME_USE_64BIT_IDS)
endif(CMAKE_SIZEOF_VOID_P STREQUAL 8)


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
find_package(Boost REQUIRED COMPONENTS filesystem thread serialization regex)

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

set(test_Execs)
# --------------------------------------------------------------------------- #
# Test CATCH
# --------------------------------------------------------------------------- #
add_executable(test_Catch src/Catch.t.cpp)
target_link_libraries(test_Catch Catch2::Catch2)
catch_discover_tests(test_Catch)

set(test_Execs ${test_Execs} test_Catch)


# --------------------------------------------------------------------------- #
# Test StdMeshers
# --------------------------------------------------------------------------- #
add_executable(test_StdMeshers src/StdMeshers.t.cpp)
target_link_libraries(test_StdMeshers Catch2::Catch2 ${SMESH_LIBRARIES})
catch_discover_tests(test_StdMeshers)

set(test_Execs ${test_Execs} test_StdMeshers)


# --------------------------------------------------------------------------- #
# Test MEFISTO2
# --------------------------------------------------------------------------- #
add_executable(test_MEFISTO2 src/MEFISTO2.t.cpp)
target_link_libraries(test_MEFISTO2 Catch2::Catch2 ${SMESH_LIBRARIES})
catch_discover_tests(test_MEFISTO2)

set(test_Execs ${test_Execs} test_MEFISTO2)


# --------------------------------------------------------------------------- #
# Test NETGENPlugin
# --------------------------------------------------------------------------- #
if(ENABLE_NETGEN)
    add_executable(test_NETGENPlugin src/NETGENPlugin.t.cpp)
    target_link_libraries(test_NETGENPlugin Catch2::Catch2 ${SMESH_LIBRARIES})
    catch_discover_tests(test_NETGENPlugin)

    set(test_Execs ${test_Execs} test_NETGENPlugin)
else()
    message(STATUS "Skipping NETGENPlugin tests.")
endif(ENABLE_NETGEN)


# --------------------------------------------------------------------------- #
# INSTALL
# --------------------------------------------------------------------------- #
install(TARGETS ${test_Execs}
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/tests
)
