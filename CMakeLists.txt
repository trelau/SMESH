# SMESH cmake build file
project(SMESH C CXX)
cmake_minimum_required(VERSION 2.8)

# Options
option(ENABLE_NETGEN "Enable NETGEN" OFF)
option(ENABLE_BLSURF "Enable BLSURF" OFF)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation directory.")

if(ENABLE_BLSURF)
    set(MESHGEMS_INCLUDE "" CACHE PATH "MeshGems include directory.")
    set(MESHGEMS_LIB "" CACHE FILE "MeshGems library.")
    set(MESHGEMS_CADSURF_LIB "" CACHE FILE "MeshGems MG-CADSurf library.")
endif(ENABLE_BLSURF)

set(SMESH_VERSION_MAJOR 8)
set(SMESH_VERSION_MINOR 3)
set(SMESH_VERSION_PATCH 0)
set(SMESH_VERSION_TWEAK)

# Build shared libraries
set(BUILD_SHARED_LIBS ON)

# Includes
include_directories(inc)

# OpenCASCADE
find_package(OpenCASCADE REQUIRED)
include_directories(${OpenCASCADE_INCLUDE_DIR})
link_directories(${OpenCASCADE_LIBRARY_DIR})

# VTK
find_package(VTK REQUIRED)
include_directories(${VTK_INCLUDE_DIRS})

# Boost 
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# pthread
set(pthread_INCLUDE_DIRS "C:/Miniconda/envs/occt/Library/include" CACHE PATH "Path to pthread.h")
include_directories(${pthread_INCLUDE_DIRS})
set(pthread_LIB_DIRS "C:/Miniconda/envs/occt/Library/lib" CACHE PATH "Path to pthread library.")
link_directories(${pthread_LIB_DIRS})

# NETGEN
if(ENABLE_NETGEN)
    find_package(Netgen REQUIRED)
    link_directories(${NETGEN_LIBRARY_DIR})
    include_directories(${NETGEN_INCLUDE_DIR})
    include_directories(${NETGEN_INCLUDE_DIR}/occ)
    include_directories(${NETGEN_INCLUDE_DIR}/meshing)
    include_directories(${NETGEN_INCLUDE_DIR}/general)
    include_directories(${NETGEN_INCLUDE_DIR}/linalg)
    include_directories(${NETGEN_INCLUDE_DIR}/csg)
    include_directories(${NETGEN_INCLUDE_DIR}/geom2d)
    include_directories(${NETGEN_INCLUDE_DIR}/gprim)
    include_directories(${NETGEN_INCLUDE_DIR}/include)
    include_directories(${NETGEN_INCLUDE_DIR}/stlgeom)
    
    # Set NETGEN_VERSION
    file(STRINGS ${NETGEN_INCLUDE_DIR}/mydefs.hpp NETGEN_VERSION
        REGEX "#define PACKAGE_VERSION.*"
    )
    string(REGEX MATCHALL "[0-9]+" NETGEN_VERSION ${NETGEN_VERSION})
    list(LENGTH NETGEN_VERSION NETGEN_VERSION_COUNT)
    list(GET NETGEN_VERSION 0 NETGEN_VERSION_MAJOR)
    if(NETGEN_VERSION_COUNT GREATER 1)
        list(GET NETGEN_VERSION 1 NETGEN_VERSION_MINOR)
    else()
        set(NETGEN_VERSION_MINOR 0)
    endif()

    MATH(EXPR NETGEN_VERSION "(${NETGEN_VERSION_MAJOR} << 16) + (${NETGEN_VERSION_MINOR} << 8)")
    MESSAGE(STATUS "Using NETGEN version ${NETGEN_VERSION_MAJOR}.${NETGEN_VERSION_MINOR}, calculated: ${NETGEN_VERSION}")
    
endif(ENABLE_NETGEN)

# Default to release build
if(NOT DEFINED CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Built type will be ${CMAKE_BUILD_TYPE}")

# Check 32/64 bit platform
if(${CMAKE_SIZEOF_VOID_P} MATCHES "8")
    add_definitions(-D_OCC64)
    message(STATUS "Build 64bit")
    set(BIT 64)
else()
    message(STATUS "Build 32bit")
    set(BIT 32)
endif()

# Build settings according to the platform
if(UNIX)
    # Same settings are used for both MacOSX and Unix/Linux
    add_definitions(-DHAVE_CONFIG_H -DHAVE_LIMITS_H -DCSFDB -DLIN -DOCC_CONVERT_SIGNALS)
else(UNIX)
  if(WIN32)
    if(MSVC)
        add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB -DUSE_CLOCK -DMSDOS -DNO_ONEXIT -DNO_My_ctype -DNO_ISATTY -DNO_FPINIT /wd4290 /wd4251 /wd4018 /wd4800 /wd4996 /wd4244 /wd4805 /wd4806 /wd4275 /wd4005 /wd4099 /wd4101 /wd4146 /wd4267 /wd4390 /wd4503 /wd4436)
    else(MSVC)
        add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB)
    endif(MSVC)
  else(WIN32)
    message("Unknown platform")
  endif(WIN32)
endif(UNIX)

# Basics
file(GLOB Basics_SRC src/Basics/*.cxx)
add_library(SMESHBasics ${Basics_SRC})
target_link_libraries(SMESHBasics pthreads)
if(WIN32)
    set_target_properties(SMESHBasics PROPERTIES COMPILE_FLAGS "-DBASICS_EXPORTS")
endif(WIN32)

# Controls
file(GLOB Controls_SRC src/Controls/*.cxx)
add_library(SMESHControls ${Controls_SRC})
target_link_libraries(SMESHControls SMDS SMESHDS SMESHUtils TKernel TKBRep TKG3d TKTopAlgo TKGeomBase TKGeomAlgo ${VTK_LIBRARIES})
if(WIN32)
    set_target_properties(SMESHControls PROPERTIES COMPILE_FLAGS "-DSMESHCONTROLS_EXPORTS")
endif(WIN32)

# Driver
file(GLOB Driver_SRC src/Driver/*.cxx)
add_library(Driver ${Driver_SRC})
target_link_libraries(Driver SMESHMisc SMESHDS SMESHUtils TKernel TKTopAlgo)
if(WIN32)
    set_target_properties(Driver PROPERTIES COMPILE_FLAGS "-DMESHDRIVER_EXPORTS")
endif(WIN32)

# DriverDAT
file(GLOB DriverDAT_SRC src/DriverDAT/*.cxx)
add_library(DriverDAT ${DriverDAT_SRC})
target_link_libraries(DriverDAT SMESHMisc SMESHTrace SMESHBasics Driver SMDS)
if(WIN32)
    set_target_properties(DriverDAT PROPERTIES COMPILE_FLAGS "-DMESHDRIVERDAT_EXPORTS")
endif(WIN32)

# DriverGMF
file(GLOB DriverGMF_SRC src/DriverGMF/*.cxx src/DriverGMF/libmesh5.c)
add_library(DriverGMF ${DriverGMF_SRC})
target_link_libraries(DriverGMF SMESHBasics SMESHUtils Driver)
if(WIN32)
    set_target_properties(DriverGMF PROPERTIES COMPILE_FLAGS "-DMESHDriverGMF_EXPORTS")
endif(WIN32)

# DriverSTL
file(GLOB DriverSTL_SRC src/DriverSTL/*.cxx)
add_library(DriverSTL ${DriverSTL_SRC})
target_link_libraries(DriverSTL Driver SMDS SMESHUtils TKernel TKSTL TKTopAlgo TKMesh)
if(WIN32)
    set_target_properties(DriverSTL PROPERTIES COMPILE_FLAGS "-DMESHDRIVERSTL_EXPORTS")
endif(WIN32)

# DriverUNV
file(GLOB DriverUNV_SRC src/DriverUNV/*.cxx)
add_library(DriverUNV ${DriverUNV_SRC})
target_link_libraries(DriverUNV SMDS Driver SMESHMisc SMESHTrace SMESHBasics)
if(WIN32)
    set_target_properties(DriverUNV PROPERTIES COMPILE_FLAGS "-DMESHDRIVERUNV_EXPORTS")
endif(WIN32)

# MEFISTO2
file(GLOB MEFISTO2_SRC src/MEFISTO2/aptrte.cxx src/MEFISTO2/trte.c)
add_library(MEFISTO2 ${MEFISTO2_SRC})
set_target_properties(MEFISTO2 PROPERTIES COMPILE_FLAGS "-DMEFISTO2D_EXPORTS")

# Misc
file(GLOB Misc_SRC src/Misc/*.cxx)
add_library(SMESHMisc ${Misc_SRC})
target_link_libraries(SMESHMisc SMESHTrace TKBRep TKShHealing TKMesh TKGeomAlgo TKTopAlgo TKG2d TKG3d TKV3d TKGeomBase TKBO)
if(WIN32)
    set_target_properties(SMESHMisc PROPERTIES COMPILE_FLAGS "-DUTILS_EXPORTS")
endif(WIN32)

# NETGENPlugin
if(ENABLE_NETGEN)
    file(GLOB NETGENPlugin_SRC src/NETGENPlugin/*.cxx)
    add_library(NETGENPlugin ${NETGENPlugin_SRC})
    target_link_libraries(NETGENPlugin StdMeshers nglib)
    if(WIN32)
        set_target_properties(NETGENPlugin PROPERTIES COMPILE_FLAGS "-DNETGENPLUGIN_EXPORTS -DNO_PARALLEL_THREADS -DOCCGEOMETRY -DNETGEN_VERSION=${NETGEN_VERSION}")
    else()
        set_target_properties(NETGENPlugin PROPERTIES COMPILE_FLAGS "${NETGEN_CXX_FLAGS}")
    endif(WIN32)    
endif(ENABLE_NETGEN)

# SMDS
file(GLOB SMDS_SRC src/SMDS/*.cxx)
add_library(SMDS ${SMDS_SRC})
target_link_libraries(SMDS SMESHMisc SMESHTrace ${VTK_LIBRARIES})
if(WIN32)
    set_target_properties(SMDS PROPERTIES COMPILE_FLAGS "-DSMDS_EXPORTS")
endif(WIN32)

# SMESH
file(GLOB SMESH_SRC src/SMESH/*.cxx)
add_library(SMESH ${SMESH_SRC})
target_link_libraries(SMESH SMESHControls SMESHMisc SMESHDS DriverDAT DriverSTL DriverUNV DriverGMF TKShHealing TKPrim TKG2d TKCDF TKMeshVS)
if(WIN32)
    set_target_properties(SMESH PROPERTIES COMPILE_FLAGS "-DSMESHimpl_EXPORTS")
endif(WIN32)

# SMESHDS
file(GLOB SMESHDS_SRC src/SMESHDS/*.cxx)
add_library(SMESHDS ${SMESHDS_SRC})
target_link_libraries(SMESHDS SMDS SMESHTrace TKBRep)
if(WIN32)
    set_target_properties(SMESHDS PROPERTIES COMPILE_FLAGS "-DSMESHDS_EXPORTS")
endif(WIN32)

# StdMeshers
file(GLOB StdMeshers_SRC src/StdMeshers/*.cxx)
add_library(StdMeshers ${StdMeshers_SRC})
target_link_libraries(StdMeshers SMESH MEFISTO2 TKOffset)
if(WIN32)
    set_target_properties(StdMeshers PROPERTIES COMPILE_FLAGS "-DSTDMESHERS_EXPORTS")
else(WIN32)
    set_target_properties(StdMeshers PROPERTIES COMPILE_FLAGS "${StdMeshers_CFLAGS}")
endif(WIN32)

# Trace
file(GLOB Trace_SRC src/Trace/*.cxx)
add_library(SMESHTrace ${Trace_SRC})
target_link_libraries(SMESHTrace pthreads SMESHBasics)
if(WIN32)
    set_target_properties(SMESHTrace PROPERTIES COMPILE_FLAGS "-DSALOMELOCALTRACE_EXPORTS")
endif(WIN32)

# Utils
file(GLOB Utils_SRC src/Utils/*.cxx)
add_library(SMESHUtils ${Utils_SRC})
target_link_libraries(SMESHUtils SMDS TKShHealing TKPrim TKernel TKBRep TKG2d TKG3d TKGeomBase TKGeomAlgo TKTopAlgo TKMesh)
if(WIN32)
    set_target_properties(SMESHUtils PROPERTIES COMPILE_FLAGS "-DSMESHUtils_EXPORTS")
endif(WIN32)

# BLSURFPlugin
if(ENABLE_BLSURF)
    # Python requried
    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})

    # Include MeshGems
    include_directories(${MESHGEMS_INCLUDE})
    file(GLOB BLSURFPlugin_SRC src/BLSURFPlugin/*.cxx)
    add_library(BLSURFPlugin ${BLSURFPlugin_SRC})
    target_link_libraries(BLSURFPlugin ${PYTHON_LIBRARY} TKBRep TKG2d TKG3d TKGeomBase TKGeomAlgo TKShHealing SMDS SMESHDS SMESH StdMeshers ${MESHGEMS_CADSURF_LIB} ${MESHGEMS_LIB})
    if(WIN32)
        set_target_properties(BLSURFPlugin PROPERTIES COMPILE_FLAGS "-DBLSURFPLUGIN_EXPORTS")
    endif(WIN32)
    # TODO Add to SMESH_LIBRARIES
endif(ENABLE_BLSURF)

# Install
set(SMESH_LIBRARIES Driver DriverDAT DriverGMF DriverSTL DriverUNV MEFISTO2 SMDS SMESH SMESHBasics SMESHControls SMESHDS SMESHMisc SMESHTrace SMESHUtils StdMeshers)
if(ENABLE_NETGEN)
    set(SMESH_LIBRARIES ${SMESH_LIBRARIES} NETGENPlugin)
endif(ENABLE_NETGEN)
if(ENABLE_BLSURF)
    set(SMESH_LIBRARIES ${SMESH_LIBRARIES} BLSURFPlugin)
endif(ENABLE_BLSURF)

install(TARGETS ${SMESH_LIBRARIES}
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "bin")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/inc/
    DESTINATION "include/smesh")

# Configuration file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SMESHConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/SMESHConfig.cmake @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SMESHConfig.cmake DESTINATION cmake)