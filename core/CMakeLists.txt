project(ProtonEngineCore)

add_library(ProtonEngineCore STATIC
        src/application.cpp
        src/cube.cpp
        src/triangle.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

target_link_libraries(ProtonEngineCore PRIVATE
        fmt
        glfw

        ProtonEngine::Renderer)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)
add_library(ProtonEngine ALIAS ProtonEngineCore)