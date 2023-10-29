project(ProtonEngineRenderer)

add_library(ProtonEngineRenderer STATIC
        src/renderer.cpp
        src/shader_progam.cpp
        src/mesh.cpp
        src/texture.cpp)

target_include_directories(ProtonEngineRenderer PUBLIC include)

target_link_libraries(ProtonEngineRenderer PRIVATE
        fmt
        glad
        glm

        ProtonEngine::Components
        ProtonEngine::Assets
        ProtonEngine::SDK
)

if(WIN32)
    target_link_libraries(ProtonEngineRenderer PRIVATE
            opengl32)
endif()

if (APPLE)
    target_link_libraries(ProtonEngineRenderer PRIVATE "-framework OpenGL")
endif()

target_link_libraries(ProtonEngineRenderer PRIVATE fmt)

add_library(ProtonEngine::Renderer ALIAS ProtonEngineRenderer)

configure_file(shaders/shader.fragment ${BINARY_DIRECTORY}/assets/shaders/shader.fragment COPYONLY)
configure_file(shaders/shader.vertex ${BINARY_DIRECTORY}/assets/shaders/shader.vertex COPYONLY)
