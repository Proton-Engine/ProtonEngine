add_subdirectory(assets)
add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(renderer)

add_library(ProtonEngine INTERFACE)

target_link_libraries(ProtonEngine
        INTERFACE
        ProtonEngine::Assets
        ProtonEngine::Components
        ProtonEngine::Core
        ProtonEngine::Renderer
        ProtonEngine::Ui
)

if (WIN32)
    target_link_libraries(ProtonEngine PRIVATE opengl32)
endif ()

if (APPLE)
    target_link_libraries(ProtonEngine PRIVATE "-framework OpenGL")
endif ()