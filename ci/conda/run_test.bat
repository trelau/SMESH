cd test
mkdir build
cd build

cmake -G "Ninja" ^
    -D CMAKE_BUILD_TYPE=Release ^
    -D CMAKE_PREFIX_PATH:FILEPATH="%LIBRARY_PREFIX%" ^
    -D CMAKE_SYSTEM_PREFIX_PATH:FILEPATH="%LIBRARY_PREFIX%" ^
    -D PTHREAD_INCLUDE_DIRS:FILEPATH="%LIBRARY_PREFIX%/include" ^
    -D PTHREAD_LIB_DIRS:FILEPATH="%LIBRARY_PREFIX%/lib"
    ..

if errorlevel 1 exit 1
ninja install
if errorlevel 1 exit 1

cd ..
cd tests
test_Catch.exe
test_StdMeshers.exe
test_NETGENPlugin.exe
test_MEFISTO2.exe
