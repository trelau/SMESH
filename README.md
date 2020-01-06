# SMESH
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/installer/conda.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/platforms.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/downloads.svg)](https://anaconda.org/conda-forge/smesh)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/smesh/badges/latest_release_date.svg)](https://anaconda.org/conda-forge/smesh)

A stand-alone library of the mesh framework from the [Salome Platform](www.salome-platform.org).

For now, the sources are manually copied from the specified Salome Platform
release which at the time of this writing is 8.3.0. Modifications were applied
to enable:

1. Functionality independent of the other Salome Platform libraries
2. Netgen 6.2 integration
3. Support for OpenCASCADE 7.X.X

Some areas that could use contributor support:

* Improve robustness of CMake build process and add support for targeting other
  platforms and architectures
* Leverage CI via Azure Pipelines
* Tests and benchmarks
