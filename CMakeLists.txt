cmake_minimum_required(VERSION 3.23)

project(ProtonEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

#add_compile_options(-fPIC -Wall -Wextra -Wpedantic)
add_compile_options(-fPIC)

set(BINARY_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_INSTALL_PREFIX "install")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})

include(cmake/copy_assets.cmake)
include(cmake/CPM.cmake)
include(cmake/download_dependencies.cmake)
include(GenerateExportHeader)

# Third-party libraries
add_subdirectory(third-party)
find_package(OpenGL REQUIRED)

# Engine includes
add_subdirectory(engine)
add_subdirectory(graphviz)

copy_assets("engine_assets")

add_subdirectory(sandbox)
