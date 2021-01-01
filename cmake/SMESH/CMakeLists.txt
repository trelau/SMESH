# --------------------------------------------------------------------------- #
# SMESH
# --------------------------------------------------------------------------- #
set(SMESH_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Driver
file(GLOB Driver_SRC ${SMESH_SRC_DIR}/Driver/*.cxx)
add_library(Driver ${Driver_SRC})
target_link_libraries(Driver SMESHUtils TKernel TKTopAlgo)
target_include_directories(Driver PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/Driver>
  $<INSTALL_INTERFACE:include/smesh/Driver>
)
if(WIN32)
    set_target_properties(Driver PROPERTIES COMPILE_FLAGS "-DMESHDRIVER_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} Driver)
file(GLOB Driver_INCLUDES ${SMESH_SRC_DIR}/Driver/*.h*)
install(FILES ${Driver_INCLUDES} DESTINATION "include/smesh/Driver")

# DriverDAT
file(GLOB DriverDAT_SRC ${SMESH_SRC_DIR}/DriverDAT/*.cxx)
add_library(DriverDAT ${DriverDAT_SRC})
target_link_libraries(DriverDAT Driver SMDS)
target_include_directories(DriverDAT PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/DriverDAT>
  $<INSTALL_INTERFACE:include/smesh/DriverDAT>
)
if(WIN32)
    set_target_properties(DriverDAT PROPERTIES COMPILE_FLAGS "-DMESHDRIVERDAT_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} DriverDAT)
file(GLOB DriverDAT_INCLUDES ${SMESH_SRC_DIR}/DriverDAT/*.h*)
install(FILES ${DriverDAT_INCLUDES} DESTINATION "include/smesh/DriverDAT")

# DriverGMF
file(GLOB DriverGMF_SRC ${SMESH_SRC_DIR}/DriverGMF/*.cxx ${SMESH_SRC_DIR}/DriverGMF/libmesh5.c)
add_library(DriverGMF ${DriverGMF_SRC})
target_link_libraries(DriverGMF SMESHUtils SMESHDS Driver)
target_include_directories(DriverGMF PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/DriverGMF>
  $<INSTALL_INTERFACE:include/smesh/DriverGMF>
)
if(WIN32)
    set_target_properties(DriverGMF PROPERTIES COMPILE_FLAGS "-DMESHDriverGMF_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} DriverGMF)
file(GLOB DriverGMF_INCLUDES ${SMESH_SRC_DIR}/DriverGMF/*.h*)
install(FILES ${DriverGMF_INCLUDES} DESTINATION "include/smesh/DriverGMF")

# DriverSTL
file(GLOB DriverSTL_SRC ${SMESH_SRC_DIR}/DriverSTL/*.cxx)
add_library(DriverSTL ${DriverSTL_SRC})
target_link_libraries(DriverSTL Driver SMDS SMESHUtils TKernel TKSTL TKTopAlgo TKMesh)
target_include_directories(DriverSTL PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/DriverSTL>
  $<INSTALL_INTERFACE:include/smesh/DriverSTL>
)
if(WIN32)
    set_target_properties(DriverSTL PROPERTIES COMPILE_FLAGS "-DMESHDRIVERSTL_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} DriverSTL)
file(GLOB DriverSTL_INCLUDES ${SMESH_SRC_DIR}/DriverSTL/*.h*)
install(FILES ${DriverSTL_INCLUDES} DESTINATION "include/smesh/DriverSTL")

# DriverUNV
file(GLOB DriverUNV_SRC ${SMESH_SRC_DIR}/DriverUNV/*.cxx)
add_library(DriverUNV ${DriverUNV_SRC})
target_link_libraries(DriverUNV SMDS SMESHDS Driver)
target_include_directories(DriverUNV PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/DriverUNV>
  $<INSTALL_INTERFACE:include/smesh/DriverUNV>
)
if(WIN32)
    set_target_properties(DriverUNV PROPERTIES COMPILE_FLAGS "-DMESHDRIVERUNV_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} DriverUNV)
file(GLOB DriverUNV_INCLUDES ${SMESH_SRC_DIR}/DriverUNV/*.h*)
install(FILES ${DriverUNV_INCLUDES} DESTINATION "include/smesh/DriverUNV")

# MEFISTO2
file(GLOB MEFISTO2_SRC ${SMESH_SRC_DIR}/MEFISTO2/aptrte.cxx ${SMESH_SRC_DIR}/MEFISTO2/trte.c)
add_library(MEFISTO2 ${MEFISTO2_SRC})
target_link_libraries(MEFISTO2 Kernel)
target_include_directories(MEFISTO2 PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/MEFISTO2>
  $<INSTALL_INTERFACE:include/smesh/MEFISTO2>
)
if (WIN32)
    set_target_properties(MEFISTO2 PROPERTIES COMPILE_FLAGS "-DMEFISTO2D_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} MEFISTO2)
file(GLOB MEFISTO2_INCLUDES ${SMESH_SRC_DIR}/MEFISTO2/*.h*)
install(FILES ${MEFISTO2_INCLUDES} DESTINATION "include/smesh/MEFISTO2")

# Controls
file(GLOB Controls_SRC ${SMESH_SRC_DIR}/Controls/*.cxx)
add_library(Controls ${Controls_SRC})
target_link_libraries(Controls Kernel Geom SMDS SMESHDS SMESHUtils TKernel TKBRep TKG3d TKTopAlgo TKGeomBase TKGeomAlgo VTK::FiltersVerdict)
target_include_directories(Controls PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/Controls>
  $<INSTALL_INTERFACE:include/smesh/Controls>
)
if(WIN32)
    set_target_properties(Controls PROPERTIES COMPILE_FLAGS "-DSMESHCONTROLS_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} Controls)
file(GLOB Controls_INCLUDES ${SMESH_SRC_DIR}/Controls/*.h*)
install(FILES ${Controls_INCLUDES} DESTINATION "include/smesh/Controls")

# SMDS
file(GLOB SMDS_SRC ${SMESH_SRC_DIR}/SMDS/*.cxx)
add_library(SMDS ${SMDS_SRC})
target_link_libraries(SMDS Kernel VTK::CommonCore VTK::CommonDataModel)
target_include_directories(SMDS PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/SMDS>
  $<INSTALL_INTERFACE:include/smesh/SMDS>
)
if(WIN32)
    set_target_properties(SMDS PROPERTIES COMPILE_FLAGS "-DSMDS_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} SMDS)
file(GLOB SMDS_INCLUDES ${SMESH_SRC_DIR}/SMDS/*.h*)
install(FILES ${SMDS_INCLUDES} DESTINATION "include/smesh/SMDS")

# SMESH
file(GLOB SMESH_SRC ${SMESH_SRC_DIR}/SMESH/*.cxx)
add_library(SMESH ${SMESH_SRC})
target_link_libraries(SMESH Kernel Geom Controls SMESHDS Driver DriverDAT DriverSTL DriverUNV DriverGMF TKShHealing TKPrim TKG2d TKCDF TKMeshVS ${Boost_LIBRARIES})
target_include_directories(SMESH PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/SMESH>
  $<INSTALL_INTERFACE:include/smesh/SMESH>
)
if(WIN32)
    set_target_properties(SMESH PROPERTIES COMPILE_FLAGS "-DSMESHimpl_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} SMESH)
file(GLOB SMESH_INCLUDES ${SMESH_SRC_DIR}/SMESH/*.h*)
install(FILES ${SMESH_INCLUDES} DESTINATION "include/smesh/SMESH")

# SMESHDS
file(GLOB SMESHDS_SRC ${SMESH_SRC_DIR}/SMESHDS/*.cxx)
add_library(SMESHDS ${SMESHDS_SRC})
target_link_libraries(SMESHDS SMDS Kernel TKBRep)
target_include_directories(SMESHDS PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/SMESHDS>
  $<INSTALL_INTERFACE:include/smesh/SMESHDS>
)
if(WIN32)
    set_target_properties(SMESHDS PROPERTIES COMPILE_FLAGS "-DSMESHDS_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} SMESHDS)
file(GLOB SMESHDS_INCLUDES ${SMESH_SRC_DIR}/SMESHDS/*.h*)
install(FILES ${SMESHDS_INCLUDES} DESTINATION "include/smesh/SMESHDS")

# StdMeshers
file(GLOB StdMeshers_SRC ${SMESH_SRC_DIR}/StdMeshers/*.cxx)
add_library(StdMeshers ${StdMeshers_SRC})
target_link_libraries(StdMeshers SMESH MEFISTO2 TKOffset ${Boost_LIBRARIES})
target_include_directories(StdMeshers PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/StdMeshers>
  $<INSTALL_INTERFACE:include/smesh/StdMeshers>
)
if(WIN32)
    set_target_properties(StdMeshers PROPERTIES COMPILE_FLAGS "-DSTDMESHERS_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} StdMeshers)
file(GLOB StdMeshers_INCLUDES ${SMESH_SRC_DIR}/StdMeshers/*.h*)
install(FILES ${StdMeshers_INCLUDES} DESTINATION "include/smesh/StdMeshers")

# SMESHUtils
file(GLOB SMESHUtils_SRC ${SMESH_SRC_DIR}/SMESHUtils/*.cxx)
add_library(SMESHUtils ${SMESHUtils_SRC})
target_link_libraries(SMESHUtils SMDS TKShHealing TKPrim TKernel TKBRep TKG2d TKG3d TKGeomBase TKGeomAlgo TKTopAlgo TKMesh ${Boost_LIBRARIES})
target_include_directories(SMESHUtils PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/SMESHUtils>
  $<INSTALL_INTERFACE:include/smesh/SMESHUtils>
)
if(WIN32)
    set_target_properties(SMESHUtils PROPERTIES COMPILE_FLAGS "-DSMESHUtils_EXPORTS")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} SMESHUtils)
file(GLOB SMESHUtils_INCLUDES ${SMESH_SRC_DIR}/SMESHUtils/*.h*)
install(FILES ${SMESHUtils_INCLUDES} DESTINATION "include/smesh/SMESHUtils")

# NETGENPlugin
set(NETGENPlugin_SRC_DIR ${SMESH_SRC_DIR}/NETGENPlugin/src/NETGENPlugin)

# Get sources and remove unsupported ones
file(GLOB NETGENPlugin_SRC ${NETGENPlugin_SRC_DIR}/*.cxx)
file(GLOB NETGENPlugin_Remesher_2D_SRC ${NETGENPlugin_SRC_DIR}/*Remesher_2D.cxx)
list(REMOVE_ITEM NETGENPlugin_SRC ${NETGENPlugin_Remesher_2D_SRC})
file(GLOB NETGENPlugin_SRC_i ${NETGENPlugin_SRC_DIR}/*_i.cxx)
list(REMOVE_ITEM NETGENPlugin_SRC ${NETGENPlugin_SRC_i})
add_library(NETGENPlugin ${NETGENPlugin_SRC})
target_link_libraries(NETGENPlugin StdMeshers nglib4smesh)
target_include_directories(NETGENPlugin PUBLIC
  $<BUILD_INTERFACE:${NETGENPlugin_SRC_DIR}>
  $<INSTALL_INTERFACE:include/smesh/NETGENPlugin>
)
if(WIN32)
    set_target_properties(NETGENPlugin PROPERTIES COMPILE_FLAGS "-DNETGENPLUGIN_EXPORTS -DNO_PARALLEL_THREADS -DOCCGEOMETRY -DNETGEN_V5")
else()
    set_target_properties(NETGENPlugin PROPERTIES COMPILE_FLAGS "${NETGEN_CXX_FLAGS} -DNO_PARALLEL_THREADS -DOCCGEOMETRY -DNETGEN_V5")
endif()
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} NETGENPlugin)
file(GLOB NETGENPlugin_INCLUDES ${NETGENPlugin_SRC_DIR}/*.h*)
install(FILES ${NETGENPlugin_INCLUDES} DESTINATION "include/smesh/NETGENPlugin")

# MeshVSLink
file(GLOB MeshVSLink_SRC ${SMESH_SRC_DIR}/MeshVSLink/*.cxx)
add_library(MeshVSLink ${MeshVSLink_SRC})
target_link_libraries(MeshVSLink SMDS SMESHDS SMESH TKMeshVS)
target_include_directories(MeshVSLink PUBLIC
  $<BUILD_INTERFACE:${SMESH_SRC_DIR}/MeshVSLink>
  $<INSTALL_INTERFACE:include/smesh/MeshVSLink>
)
if(WIN32)
    set_target_properties(MeshVSLink PROPERTIES COMPILE_FLAGS "-DSMESHimpl_EXPORTS")
endif(WIN32)
set(SMESH_LIBRARIES ${SMESH_LIBRARIES} MeshVSLink)
file(GLOB MeshVSLink_INCLUDES ${SMESH_SRC_DIR}/MeshVSLink/*.hxx
  ${SMESH_SRC_DIR}/MeshVSLink/*.ixx
  ${SMESH_SRC_DIR}/MeshVSLink/*.jxx
)
install(FILES ${MeshVSLink_INCLUDES} DESTINATION "include/smesh/MeshVSLink")
