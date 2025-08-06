add_subdirectory(assets)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(renderer)

add_library(ProtonEngine INTERFACE)

target_link_libraries(ProtonEngine
        INTERFACE
        ProtonEngine::Assets
        ProtonEngine::Core
        ProtonEngine::Renderer
        ProtonEngine::Ui
)