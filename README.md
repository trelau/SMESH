# SMESH
A stand-alone library of the mesh framework from the Salome Platform
(www.salome-platform.org).

The project is in early development and started by copying the sources from the
latest Salome Platform release which at the time of this writing was 8.3.0.
Modifications were applied to enable:

1. Functionality independent of the other Salome Platform libraries
2. Newer [Netgen](https://github.com/LaughlinResearch/netgen4smesh) integration
3. Support for OpenCASCADE 7.2.0

Some areas that could use contributor support:

* Improve robustness of CMake build process and add support for targeting other
  platforms and architectures
* Leverage CI platforms like AppVeyor and Travis-CI
* Support for building and deploying Conda packages
* Tests, examples, and benchmarks
