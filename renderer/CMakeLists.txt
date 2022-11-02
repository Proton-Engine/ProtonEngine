project(ProtonEngineRenderer)

add_library(ProtonEngineRenderer STATIC
        src/renderer.cpp)

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

add_library(ProtonEngine::Renderer ALIAS ProtonEngineRenderer)
