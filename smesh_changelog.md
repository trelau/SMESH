

## Overview



### subfolders extracted from salome 

+ Trace: Kernel `SalomeLocalTrace`
+ Utils: `SMESHUtils`
+ Basics: come from Kernel module of Salome
+ Misc: 
+ the other subfolders: mesh  module of Salome
+ swig interfacing and GUI related code are dropped

### C++ standard version must support C++14

C++11 is reequired by OCCT 7.3 

while  netgen 6.2dev requires C++14,   `std::enable_if_t` is not available on g++ 5.x

```cmake
# netget 6.2 also need g++6, using `export CXX=g++6` to select compiler
# Compiler flags, c++11 is essential for OCCT 7.3
    if (${NETGEN_VERSION} VERSION_GREATER_EQUAL 6.2)
        set_target_properties(NETGENPlugin PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
        )
    endif()

# is that possible to detect OpenCASCADE_VERSION by cmake?
```



/usr/include/netgen/core/type_traits.hpp:14:20: warning: variable templates only available with -std=c++14 or -std=gnu++14
     constexpr bool all_of_tmpl = std::is_same<_BoolArray<vals...>, _BoolArray<(vals || true)...>>::value; // NOLINT



### Migration to C++17

Salome code is C++17 ready, except from some plugin suppressed. , 

esp, the breaking  exception declearation change in C++17

*looo* has started working on `c++17: dynamic exception specification -> noexcept(false)`
https://github.com/LaughlinResearch/SMESH/pull/13



### netgen must be patched

netgen license?  GNU Lesser General Public License v2.1

salome 9.3 stills use the netgen 5.5 version

why there is no gmsh plugin? built-in?

### Python binding for salomesmesh

PyOCCT has the binding for salomesmesh, using generated pybind11 wrapping.
<https://github.com/LaughlinResearch/>





## Changelog for this fork

### missing dependencies
libmetis.so is needed
libtbb-dev is needed, added to *conda*, but it is not mentioned in readme.

### CGNS mesh format added

`libcgns-dev` on debian-like systems,  `libcgns-devel`

`FindCGNS.cmake` is downloaded from paraview project

windows system is not clear, perhaps just disable it.


### smesh cmake failed on windows for `pthread`

```
CMake Error at src/3rdParty/salomesmesh/CMakeLists.txt:150 (message):
  pthread include directory is required.
```

`set(CMAKE_USE_WIN32_THREADS_INIT 1)`

pthread detect can be removed for windows?
in CMake,  `UNIX` cover Linux, MacOS?

*src file, has C preprocessor*, but it is also used by several headers

qingfeng@qingfeng-ubuntu:/opt/SMESH/inc$ grep -rnw ./ -e "pthread"
./BaseTraceCollector.hxx:33:#include <pthread.h>
./BasicsGenericDestructor.hxx:40:#include <pthread.h>
./LocalTraceBufferPool.hxx:36:#include <pthread.h>

### smesh tweak on windows

already done for windows

`MinGW` should work, has it has pthread built in 

https://github.com/LaughlinResearch/SMESH/commit/685632514a06172c16cbf12ee05cf7776998ecd1
```
// Keep compatibility with paraview 5.0.1 on Linux
#ifndef WIN32
//#ifndef WIN32
  #ifndef VTK_HAS_MTIME_TYPE
  #define VTK_HAS_MTIME_TYPE
  typedef unsigned long int vtkMTimeType;
  #endif
#endif
//#endif
```

### FreeCAD specific

https://github.com/qingfengxia/FreeCAD/blob/smesh/cMake/FindSMESH.cmake

[src/3rdParty/CMakeLists.txt]
FREECAD_USE_EXTERNAL_SMESH

 	`SMESH_Version.h.cmake`

    used only in FEM module

### segment fault during netgen meshing in FreeCAD

FreeCAD has segment fault with this version of netgen, perhaps it is not patched

https://forum.freecadweb.org/viewtopic.php?f=4&t=40637&p=346703#p346703