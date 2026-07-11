add_subdirectory(assets)
add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(renderer)

add_library(ProtonEngine SHARED)

generate_export_header(ProtonEngine BASE_NAME PROTONENGINE EXPORT_FILE_NAME protonengine/export.h)

target_sources(
        ProtonEngine
        PRIVATE
        $<TARGET_OBJECTS:ProtonEngineAssets>
        $<TARGET_OBJECTS:ProtonEngineCommon>
        $<TARGET_OBJECTS:ProtonEngineCore>
        $<TARGET_OBJECTS:ProtonEngineRenderer>
        $<TARGET_OBJECTS:ProtonEngineUi>
        PUBLIC
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineExport,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/export.h
)

target_include_directories(ProtonEngine
        PUBLIC
        $<TARGET_PROPERTY:ProtonEngineExport,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:ProtonEngineAssets,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:ProtonEngineCommon,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:ProtonEngineCore,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:ProtonEngineRenderer,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:ProtonEngineUi,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(ProtonEngine
        PRIVATE
        ProtonEngine::Assets
        ProtonEngine::Common
        ProtonEngine::Core
        ProtonEngine::Renderer
        ProtonEngine::Ui
)

install(
        TARGETS ProtonEngine
        FILE_SET generated_headers
)

add_library(ProtonEngineExport INTERFACE)
add_library(ProtonEngine::Export ALIAS ProtonEngineExport)

target_include_directories(ProtonEngineExport
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(ProtonEngineExport INTERFACE ProtonEngine_EXPORTS)