cmake_minimum_required(VERSION 3.16)

project(ProtonEngine)

set(CMAKE_CXX_STANDARD 23)

# Third-party libraries
add_subdirectory(third-party)
find_package(OpenGL REQUIRED)

# Engine includes
add_subdirectory(core)
add_subdirectory(renderer)

# Example project
add_subdirectory(sandbox)
