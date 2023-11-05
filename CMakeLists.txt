cmake_minimum_required(VERSION 3.16)

project(ProtonEngine)

set(CMAKE_CXX_STANDARD 23)

set(BINARY_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})

include(cmake/copy_assets.cmake)

# Third-party libraries
add_subdirectory(third-party)
find_package(OpenGL REQUIRED)

# Engine includes
add_subdirectory(engine)

copy_assets("engine_assets")

add_subdirectory(sandbox)
