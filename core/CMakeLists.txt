project(ProtonEngineCore)

add_library(ProtonEngineCore STATIC
        src/application.cpp
        src/cube.cpp
        src/entity.cpp
        src/scene.cpp
        src/triangle.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

target_link_libraries(ProtonEngineCore
        PUBLIC
        EnTT::EnTT
        ProtonEngine::Renderer

        PRIVATE
        fmt
        glfw)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)
add_library(ProtonEngine ALIAS ProtonEngineCore)