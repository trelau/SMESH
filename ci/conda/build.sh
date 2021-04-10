mkdir build
cd build

declare -a CMAKE_PLATFORM_FLAGS
if [[ ${HOST} =~ .*linux.* ]]; then
    CMAKE_PLATFORM_FLAGS+=(-DCMAKE_TOOLCHAIN_FILE="${RECIPE_DIR}/cross-linux.cmake")
fi

declare ENABLE_NETGEN=true
if [[ ${HOST} =~ .*apple.* ]]; then
  ENABLE_NETGEN=true  # set to false if you don't want to build and test Netgen
fi

cmake -G "Ninja" \
      -D CMAKE_BUILD_TYPE:STRING="Release" \
      ${CMAKE_PLATFORM_FLAGS[@]} \
      -D CMAKE_INSTALL_PREFIX:FILEPATH=$PREFIX \
      -D CMAKE_PREFIX_PATH:FILEPATH=$PREFIX \
      -D Boost_NO_BOOST_CMAKE:BOOL=ON \
      -D ENABLE_NETGEN:BOOL=$ENABLE_NETGEN \
      ..

ninja install
