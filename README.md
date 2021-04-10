# SMESH
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/installer/conda.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/platforms.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/downloads.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/latest_release_date.svg)](https://anaconda.org/conda-forge/smesh)

A stand-alone library of the mesh framework from the [Salome Platform](www.salome-platform.org).
This repository primary copies upstream sources and builds a library that be linked to other
programs.

If you are looking to use this functionality in a Python application, check out
[pySMESH](https://github.com/trelau/pySMESH). 

## Build from sources
This repository makes use of submodules so to build from sources you must clone this repository
and the submodules with:

    git clone --recurse-submodules https://github.com/trelau/SMESH.git

After cloning the repository and submodules, the source files from the external submodules need to
be prepared using the provided Python script:

    python prepare.py

In order to run the script above, you'll need to have
[python-patch](https://github.com/techtonik/python-patch/) installed. This can be installed using

    conda install -c conda-forge python-patch

or

    pip intall "patch==1.*"

With the sources prepared, a CMake build process can be initiated by:

    mkdir build
    cd build
    cmake ..

Note that for Windows systems `PTHREAD_INCLUDE_DIR`  and `PTHREAD_LIB_DIRS` will likely need
defined manually since they cannot typically be automatically found by CMake.
