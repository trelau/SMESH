cmake_minimum_required(VERSION 3.3)
project(SMESH VERSION 9.7.0.1 LANGUAGES C CXX)

# --------------------------------------------------------------------------- #
# OPTIONS
# --------------------------------------------------------------------------- #
option(ENABLE_NETGEN "Enable Netgen" ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation directory")
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")


# --------------------------------------------------------------------------- #
# SETTINGS
# --------------------------------------------------------------------------- #
set(SMESH_VERSION_MAJOR 9)
set(SMESH_VERSION_MINOR 7)
set(SMESH_VERSION_PATCH 0)
set(SMESH_VERSION_TWEAK 1)

# Build shared libraries
set(BUILD_SHARED_LIBS TRUE)

# Force C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warning and errors
if(MSVC)
    add_compile_options(/W1)
    add_compile_options(/wd4715 /wd4091 /wd4503 /wd4805 /wd4267 /wd4477 /wd4138 /wd4273 /wd4311 /wd4806)
else()
    add_compile_options(-Wno-deprecated)
endif()

# Definitions
if(UNIX)
  # Same settings are used for both MacOSX and Unix/Linux
  add_definitions(-DHAVE_LIMITS_H -DCSFDB -DLIN -DOCC_CONVERT_SIGNALS)
else(UNIX)
  if(WIN32)
      if(MSVC)
          add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB -DUSE_CLOCK -DMSDOS -DNO_ONEXIT -DNO_My_ctype -DNO_ISATTY -DNO_FPINIT)
      else(MSVC)
          add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB)
      endif(MSVC)
  else(WIN32)
      message(FATAL_ERROR "Unknown platform")
  endif(WIN32)
endif(UNIX)

if(CMAKE_SIZEOF_VOID_P STREQUAL 8)
    add_definitions(-D_OCC64)
    # add_definitions(-DSALOME_USE_64BIT_IDS)
endif(CMAKE_SIZEOF_VOID_P STREQUAL 8)


# --------------------------------------------------------------------------- #
# OpenCASCADE
# --------------------------------------------------------------------------- #
message(STATUS "Searching for OpenCASCADE...")
find_package(OpenCASCADE REQUIRED)

include_directories(${OpenCASCADE_INCLUDE_DIR})
link_directories(${OpenCASCADE_LIBRARY_DIR})


# --------------------------------------------------------------------------- #
# VTK
# --------------------------------------------------------------------------- #
message(STATUS "Searching for VTK...")
find_package(VTK REQUIRED COMPONENTS CommonCore CommonDataModel FiltersVerdict)


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
# SMESH
# --------------------------------------------------------------------------- #

# Kernel
set(Kernel_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Kernel/src)

# Geom
set(Geom_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Geom/src)

# Netgen
if(ENABLE_NETGEN)
    set(NETGEN_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Netgen)
endif(ENABLE_NETGEN)

# Add subdirectories
add_subdirectory(src)

# Retrieve variables
if(ENABLE_NETGEN)
    get_directory_property(Netgen_LIBRARIES
      DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/Netgen
      DEFINITION Netgen_LIBRARIES
    )
else()
    set(Netgen_LIBRARIES)
    message(STATUS "Netgen is not enabled and will not be available in the resulting library.")
endif(ENABLE_NETGEN)

get_directory_property(Kernel_LIBRARIES
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/Kernel
  DEFINITION Kernel_LIBRARIES
)

get_directory_property(Geom_LIBRARIES
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/Geom
  DEFINITION Geom_LIBRARIES
)

get_directory_property(SMESH_LIBRARIES
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/SMESH
  DEFINITION SMESH_LIBRARIES
)


# --------------------------------------------------------------------------- #
# Install
# --------------------------------------------------------------------------- #
install(TARGETS ${Netgen_LIBRARIES} ${Kernel_LIBRARIES} ${Geom_LIBRARIES} ${SMESH_LIBRARIES} EXPORT SMESH-targets
  ARCHIVE DESTINATION "lib"
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(EXPORT SMESH-targets DESTINATION cmake)


# --------------------------------------------------------------------------- #
# Configuration files
# --------------------------------------------------------------------------- #
include(CMakePackageConfigHelpers)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SMESHConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/SMESHConfig.cmake @ONLY)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/SMESHConfigVersion.cmake
  VERSION ${SMESH_VERSION_MAJOR}.${SMESH_VERSION_MINOR}.${SMESH_VERSION_PATCH}
  COMPATIBILITY SameMinorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SMESHConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/SMESHConfigVersion.cmake
  DESTINATION cmake)
