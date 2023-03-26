project(ProtonEngineRenderer)

add_library(ProtonEngineRenderer STATIC
        src/renderer.cpp
        src/shader_progam.cpp)

target_include_directories(ProtonEngineRenderer PUBLIC include)

target_link_libraries(ProtonEngineRenderer PRIVATE
        fmt
        glad)

if(WIN32)
    target_link_libraries(ProtonEngineRenderer PRIVATE
            opengl32)
endif()

if (APPLE)
    target_link_libraries(ProtonEngineRenderer PRIVATE "-framework OpenGL")
endif()

target_link_libraries(ProtonEngineRenderer PRIVATE fmt)

add_library(ProtonEngine::Renderer ALIAS ProtonEngineRenderer)

configure_file(shaders/fragment.shader shaders/fragment.shader COPYONLY)
configure_file(shaders/vertex.shader shaders/vertex.shader COPYONLY)
