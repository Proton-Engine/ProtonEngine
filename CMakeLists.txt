cmake_minimum_required(VERSION 3.31)

project(ProtonEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

#add_compile_options(-fPIC -Wall -Wextra -Wpedantic)
add_compile_options(-fPIC)

set(BINARY_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_INSTALL_PREFIX "install")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})

include(GenerateExportHeader)
include(cmake/configure_rpath.cmake)

# Third-party libraries
find_package(glad REQUIRED)
find_package(EnTT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenGL REQUIRED)
find_package(stb REQUIRED)

add_subdirectory(third-party)

# Engine includes
add_subdirectory(engine)
add_subdirectory(engine_assets)
add_subdirectory(graphviz)

add_subdirectory(sandbox)
