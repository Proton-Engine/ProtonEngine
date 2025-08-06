file(GLOB_RECURSE COMPONENT_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE COMPONENT_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${COMPONENT_SOURCES})
source_group(include FILES ${COMPONENT_HEADERS})

add_library(ProtonEngineComponents STATIC)
add_library(ProtonEngine::Components ALIAS ProtonEngineComponents)
generate_export_header(ProtonEngineComponents BASE_NAME PROTONENGINE_COMPONENTS EXPORT_FILE_NAME protonengine/components/export.h)

target_sources(
        ProtonEngineComponents
        PRIVATE ${COMPONENT_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${COMPONENT_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineComponents,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/components/export.h
)

target_include_directories(ProtonEngineComponents
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ProtonEngineComponents PUBLIC ProtonEngine::Core)

install(
        TARGETS ProtonEngineComponents
        FILE_SET HEADERS
        FILE_SET generated_headers
)