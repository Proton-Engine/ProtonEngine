file(GLOB_RECURSE ASSET_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE ASSET_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${ASSET_SOURCES})
source_group(include FILES ${ASSET_HEADERS})

add_library(ProtonEngineAssets STATIC)
add_library(ProtonEngine::Assets ALIAS ProtonEngineAssets)
generate_export_header(ProtonEngineAssets BASE_NAME PROTONENGINE_ASSETS EXPORT_FILE_NAME protonengine/assets/export.h)

target_sources(
        ProtonEngineAssets
        PRIVATE ${ASSET_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${ASSET_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineAssets,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/assets/export.h
)

target_include_directories(ProtonEngineAssets
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        TARGETS ProtonEngineAssets
        FILE_SET HEADERS
        FILE_SET generated_headers
)