file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE COMMON_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${COMMON_SOURCES})
source_group(include FILES ${COMMON_HEADERS})

add_library(ProtonEngineCommon SHARED)
add_library(ProtonEngine::Common ALIAS ProtonEngineCommon)
generate_export_header(ProtonEngineCommon BASE_NAME PROTONENGINE_COMMON EXPORT_FILE_NAME protonengine/common/export.h)

target_sources(
        ProtonEngineCommon
        PRIVATE ${COMMON_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${COMMON_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineCommon,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/common/export.h
)

target_include_directories(ProtonEngineCommon
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ProtonEngineCommon
        PUBLIC
        # TODO: Add local wrappers around the glm objects we use. This can temporary be something like: using ProtonEngine::Math::Vec2 = glm::vec2
        # This will allow us to hide glm in the future
        glm::glm
)

install(
        TARGETS ProtonEngineCommon
        FILE_SET HEADERS
        FILE_SET generated_headers
)