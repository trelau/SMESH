add_executable(unv_test unv_test.cpp)
target_link_libraries(unv_test DriverUNV SMDS SMESH ${Boost_LIBRARIES})

install(TARGETS unv_test DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/smesh/tests)