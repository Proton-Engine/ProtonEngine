# ProtonEngine

Simple cross-platform game engine written in modern C++

## How to build

The project is set up to be build using a combination of Conan and CMake, of which Conan is the entrypoint.
Both the toolchain and profiles are provided in external repositories.

1. First install conan 2 and CMake 3.31+
2. Install the required conan profiles: `conan config install https://github.com/timherreijgers/conan-profiles.git`.
   The available profiles are: `clang-20-linux-x86_64`, `clang-20-linux-armv8`, `clang-20-macos-armv8`,
   `clang-20-win-x86_64` and `clang-20-win-armv8`.
3. Add the conan artifactory for the llvm-toolchain package:
   `conan remote add tims-conan https://conan.timherreijgers.nl/artifactory/api/conan/tims-conan`.
   Alternatively you can build the conan package manually by checking
   out [this repo](https://www.github.com/timherreijgers/conan-llvm-toolchain) and running
   `conan create -pr:a=clang-20-<platform>-<arch> toolchain/llvm/conanfile.py --build-require` for the folder that
   contains the checked out repository.
4. Install conan using:
   `conan install -pr:a=clang-20-<platform>-<arch> -s compiler.cppstd=23 -s build_type=<buildtype> -c tools.cmake.cmaketoolchain:generator="<generator>" . --build=missing`.
   The buildtype can be any of the CMake build types.
5. Configure the project using `cmake --preset=conan-<buildtype>`.
6. Build the project using `cmake --build --preset=conan-<buildtype>`.
7. Run the tests using `ctest --preset=conan-<buildtype>`.
