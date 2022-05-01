# --------------------------------------------------------------------------- #
# zlib
# --------------------------------------------------------------------------- #
find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})


# --------------------------------------------------------------------------- #
# Netgen
# --------------------------------------------------------------------------- #
add_definitions(-DOCCGEOMETRY -D_OCC64)

if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

# CORE
SET(CORE_SOURCES
    ${NETGEN_ROOT_DIR}/libsrc/core/archive.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/bitarray.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/exception.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/localheap.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/logging.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/flags.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/paje_trace.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/profiler.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/table.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/taskmanager.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/utils.cpp
    ${NETGEN_ROOT_DIR}/libsrc/core/version.cpp
)

# CGS
SET(CGS_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/csg/algprim.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/brick.cpp
    ${NETGEN_ROOT_DIR}/libsrc/csg/bspline2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/csgeom.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/csgparser.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/curve2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/edgeflw.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/explicitcurve2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/extrusion.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/gencyl.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/genmesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/identify.cpp  
    ${NETGEN_ROOT_DIR}/libsrc/csg/manifold.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/meshsurf.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/polyhedra.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/revolution.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/singularref.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/solid.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/specpoin.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/spline3d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/splinesurface.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/surface.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/csg/triapprox.cpp
    ${NETGEN_ROOT_DIR}/libsrc/csg/zrefine.cpp)

# GENERAL
SET(GENERAL_SOURCES 
   ${NETGEN_ROOT_DIR}/libsrc/general/ngarray.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/ngbitarray.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/dynamicmem.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/hashtabl.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/mystring.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/optmem.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/parthreads.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/seti.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/sort.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/spbita2d.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/table.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/mpi_interface.cpp 
   ${NETGEN_ROOT_DIR}/libsrc/general/gzstream.cpp)

# FILE(GLOB GENERAL_INCLUDES "${NETGEN_ROOT_DIR}/libsrc/general/*.h*")

# GEOM2D
SET (GEOM2D_SOURCES 
     ${NETGEN_ROOT_DIR}/libsrc/geom2d/csg2d.cpp
     ${NETGEN_ROOT_DIR}/libsrc/geom2d/genmesh2d.cpp
     ${NETGEN_ROOT_DIR}/libsrc/geom2d/geometry2d.cpp)

# GPRIM
SET(GPRIM_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/adtree.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/geom2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/geom3d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/geomfuncs.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/geomtest3d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/transform3d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/spline.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/gprim/splinegeometry.cpp)

# FILE(GLOB GPRIM_INCLUDES "${NETGEN_ROOT_DIR}/libsrc/gprim/*.h*")

# INCLUDE
SET(INCLUDE_INCLUDES 
    ${NETGEN_ROOT_DIR}/libsrc/include/nginterface.h
    ${NETGEN_ROOT_DIR}/libsrc/include/nginterface_v2.hpp
    ${NETGEN_ROOT_DIR}/libsrc/include/mydefs.hpp
    ${NETGEN_ROOT_DIR}/libsrc/include/netgen_version.hpp)

# INTERFACE
SET(INTERFACE_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/interface/nginterface.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/nginterface_v2.cpp
    ${NETGEN_ROOT_DIR}/libsrc/interface/read_fnf_mesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/readtetmesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/readuser.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/rw_cgns.cpp
    ${NETGEN_ROOT_DIR}/libsrc/interface/writeabaqus.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writediffpack.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writedolfin.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writeelmer.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writefeap.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writefluent.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writegmsh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writejcm.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writepermas.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writetecplot.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writetet.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writetochnog.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writeuser.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/wuchemnitz.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writegmsh2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/interface/writeOpenFOAM15x.cpp)

# LINALG
SET (LINALG_SOURCES 
     ${NETGEN_ROOT_DIR}/libsrc/linalg/densemat.cpp 
     ${NETGEN_ROOT_DIR}/libsrc/linalg/polynomial.cpp 
     ${NETGEN_ROOT_DIR}/libsrc/linalg/bfgs.cpp 
     ${NETGEN_ROOT_DIR}/libsrc/linalg/linopt.cpp 
     ${NETGEN_ROOT_DIR}/libsrc/linalg/linsearch.cpp)

# FILE(GLOB LINALG_INCLUDES "${NETGEN_ROOT_DIR}/libsrc/linalg/*.h*")

# MESHING
SET(MESHING_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/adfront2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/adfront3.cpp
    ${NETGEN_ROOT_DIR}/libsrc/meshing/bisect.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/boundarylayer.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/clusters.cpp      
    ${NETGEN_ROOT_DIR}/libsrc/meshing/curvedelems.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/delaunay.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/delaunay2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/geomsearch.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/global.cpp     
    ${NETGEN_ROOT_DIR}/libsrc/meshing/hprefinement.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/improve2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/improve2gen.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/improve3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/localh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshclass.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshfunc.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshfunc2d.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshing2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshing3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshtool.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/meshtype.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/msghandler.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/netrule2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/netrule3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/parser2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/parser3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/prism2rls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/pyramid2rls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/pyramidrls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/quadrls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/refine.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/ruler2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/ruler3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/secondorder.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/smoothing2.5.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/smoothing2.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/smoothing3.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/specials.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/tetrarls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/topology.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/triarls.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/validate.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/bcfunctions.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/parallelmesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/paralleltop.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/paralleltop.hpp 
    ${NETGEN_ROOT_DIR}/libsrc/meshing/basegeom.cpp
    ${NETGEN_ROOT_DIR}/libsrc/meshing/hexarls.cpp
    ${NETGEN_ROOT_DIR}/libsrc/meshing/surfacegeom.cpp)

# FILE(GLOB MESHING_INCLUDES "${NETGEN_ROOT_DIR}/libsrc/meshing/meshing.hpp")
SET(MESHING_INCLUDES ${NETGEN_ROOT_DIR}/libsrc/meshing/meshing.hpp)

# OCC
SET(OCC_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Inter2d.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Inter3d.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Loop.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Loop2d.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Loop3d.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/Partition_Spliter.cxx 
    ${NETGEN_ROOT_DIR}/libsrc/occ/occconstruction.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/occ/occgenmesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/occ/occgeom.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/occ/occmeshsurf.cpp)

SET(OCC_INCLUDES ${NETGEN_ROOT_DIR}/libsrc/occ/occgeom.hpp
                 ${NETGEN_ROOT_DIR}/libsrc/occ/occmeshsurf.hpp)

# STLGEOM
SET(STLGEOM_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/meshstlsurface.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stlgeom.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stlgeomchart.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stlgeommesh.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stlline.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stltool.cpp 
    ${NETGEN_ROOT_DIR}/libsrc/stlgeom/stltopology.cpp)

# VISUALIZATION
SET(VISUALIZATION_SOURCES 
    ${NETGEN_ROOT_DIR}/libsrc/visualization/visual_dummy.cpp)

# NGLIB
SET(NGLIB_SOURCES ${NETGEN_ROOT_DIR}/nglib/nglib.cpp)
ADD_LIBRARY(nglib4smesh SHARED
            ${CORE_SOURCES}
            ${CGS_SOURCES}
            ${GENERAL_SOURCES}
            ${GEOM2D_SOURCES}
            ${GPRIM_SOURCES}
            ${INTERFACE_SOURCES}
            ${LINALG_SOURCES}
            ${MESHING_SOURCES}
            ${OCC_SOURCES}
            ${STLGEOM_SOURCES}
            ${VISUALIZATION_SOURCES}
            ${NGLIB_SOURCES})

# Link
SET(OCCLIBS TKernel TKGeomBase TKMath TKG2d TKG3d TKXSBase TKOffset TKFillet TKShHealing)
SET(OCCLIBS ${OCCLIBS} TKMesh TKMeshVS TKTopAlgo TKGeomAlgo TKBool TKPrim TKBO TKIGES TKBRep)
SET(OCCLIBS ${OCCLIBS} TKSTEPBase TKSTEP TKSTL TKSTEPAttr TKSTEP209 TKXDESTEP TKXDEIGES TKXCAF TKLCAF)

TARGET_LINK_LIBRARIES(nglib4smesh PUBLIC ${OCCLIBS} ${ZLIB_LIBRARIES} ${PLATFORM_LIBADD})
target_include_directories(nglib4smesh PUBLIC
  $<BUILD_INTERFACE:${NETGEN_ROOT_DIR}/libsrc>
  $<BUILD_INTERFACE:${NETGEN_ROOT_DIR}/libsrc/general>
  $<BUILD_INTERFACE:${NETGEN_ROOT_DIR}/libsrc/include>
  $<BUILD_INTERFACE:${NETGEN_ROOT_DIR}/nglib>
  $<INSTALL_INTERFACE:include/smesh/Netgen>
)

if(WIN32)
  set_target_properties(nglib4smesh PROPERTIES COMPILE_FLAGS "-DNGLIB_EXPORTS -DNGCORE_EXPORTS -DNGINTERFACE_EXPORTS")
  target_compile_options(nglib4smesh PUBLIC /bigobj /MP /W1 /wd4068)
  target_compile_definitions(nglib4smesh PUBLIC _WIN32_WINNT=0x0501 WNT WNT_WINDOW NOMINMAX MSVC_EXPRESS _CRT_SECURE_NO_WARNINGS HAVE_STRUCT_TIMESPEC)
  target_link_options(nglib4smesh PUBLIC /ignore:4273 /ignore:4217 /ignore:4049)
else(WIN32)
  target_compile_options(nglib4smesh PRIVATE -fvisibility=hidden)
endif(WIN32)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  target_compile_options(nglib4smesh PUBLIC -fsized-deallocation -faligned-allocation)
endif()

# Install
# install(FILES ${GENERAL_INCLUDES} DESTINATION "include/smesh/Netgen")
# install(FILES ${GPRIM_INCLUDES} DESTINATION "include/smesh/Netgen")
# install(FILES ${INCLUDE_INCLUDES} DESTINATION "include/smesh/Netgen")
# install(FILES ${LINALG_INCLUDES} DESTINATION "include/smesh/Netgen")
install(FILES ${MESHING_INCLUDES} DESTINATION "include/smesh/Netgen")
install(FILES ${OCC_INCLUDES} DESTINATION "include/smesh/Netgen")
install(FILES ${NETGEN_ROOT_DIR}/nglib/nglib.h DESTINATION "include/smesh/Netgen")

set(Netgen_LIBRARIES nglib4smesh)
