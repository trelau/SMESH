set(Kernel_SRCS
    # Basics
    ${Kernel_SRC_DIR}/Basics/Basics_Utils.cxx
    ${Kernel_SRC_DIR}/Basics/Basics_DirUtils.cxx
    ${Kernel_SRC_DIR}/Basics/BasicsGenericDestructor.cxx
    # Local Trace
    ${Kernel_SRC_DIR}/SALOMELocalTrace/BaseTraceCollector.cxx
    ${Kernel_SRC_DIR}/SALOMELocalTrace/FileTraceCollector.cxx
    ${Kernel_SRC_DIR}/SALOMELocalTrace/LocalTraceBufferPool.cxx
    ${Kernel_SRC_DIR}/SALOMELocalTrace/LocalTraceCollector.cxx
    # Utils
    ${Kernel_SRC_DIR}/Utils/duplicate.cxx
    ${Kernel_SRC_DIR}/Utils/OpUtil.cxx
    ${Kernel_SRC_DIR}/Utils/Utils_SALOME_Exception.cxx
    ${Kernel_SRC_DIR}/Utils/Utils_ExceptHandlers.cxx)

add_library(Kernel ${Kernel_SRCS})
if(UNIX)
    target_link_libraries(Kernel Threads::Threads)
else()
    target_link_libraries(Kernel pthreads)
endif()

target_include_directories(Kernel PUBLIC
    $<BUILD_INTERFACE:${Kernel_SRC_DIR}/Basics>
    $<BUILD_INTERFACE:${Kernel_SRC_DIR}/SALOMELocalTrace>
    $<BUILD_INTERFACE:${Kernel_SRC_DIR}/Utils>
    $<INSTALL_INTERFACE:include/smesh/Kernel>
)

if(WIN32)
    set_target_properties(Kernel PROPERTIES COMPILE_FLAGS
        "-DBASICS_EXPORTS \
        -DSALOMELOCALTRACE_EXPORTS \
        -DUTILS_EXPORTS \
        -DSMESH_ONLY")
else()
    set_target_properties(Kernel PROPERTIES COMPILE_FLAGS "-DSMESH_ONLY")
endif()

configure_file(${Kernel_SRC_DIR}/Basics/smIdType.hxx.in ${Kernel_SRC_DIR}/Basics/smIdType.hxx)

file(GLOB Kernel_INCLUDES
     ${Kernel_SRC_DIR}/Basics/*.h*
     ${Kernel_SRC_DIR}/SALOMELocalTrace/*.h*
     ${Kernel_SRC_DIR}/Utils/*.h*)

install(FILES ${Kernel_INCLUDES} DESTINATION "include/smesh/Kernel")

set(Kernel_LIBRARIES Kernel)
