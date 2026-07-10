add_subdirectory(assets)
add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(renderer)

add_library(ProtonEngine SHARED
        $<TARGET_OBJECTS:ProtonEngineAssets>
        $<TARGET_OBJECTS:ProtonEngineCommon>
        $<TARGET_OBJECTS:ProtonEngineCore>
        $<TARGET_OBJECTS:ProtonEngineRenderer>
        $<TARGET_OBJECTS:ProtonEngineUi>
)

target_include_directories(ProtonEngine
        PUBLIC
        $<INSTALL_INTERFACE:$<TARGET_PROPERTY:ProtonEngineAssets,INTERFACE_INCLUDE_DIRECTORIES>>
        $<INSTALL_INTERFACE:$<TARGET_PROPERTY:ProtonEngineCore,INTERFACE_INCLUDE_DIRECTORIES>>
        $<INSTALL_INTERFACE:$<TARGET_PROPERTY:ProtonEngineRenderer,INTERFACE_INCLUDE_DIRECTORIES>>
        $<INSTALL_INTERFACE:$<TARGET_PROPERTY:ProtonEngineUi,INTERFACE_INCLUDE_DIRECTORIES>>
)

target_link_libraries(ProtonEngine
        PRIVATE
        ProtonEngine::Assets
        ProtonEngine::Core
        ProtonEngine::Renderer
        ProtonEngine::Ui
)

install(
        TARGETS ProtonEngine
)