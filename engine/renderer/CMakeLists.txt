file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE RENDERER_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${RENDERER_SOURCES})
source_group(include FILES ${RENDERER_HEADERS})

add_library(ProtonEngineRenderer STATIC)
add_library(ProtonEngine::Renderer ALIAS ProtonEngineRenderer)
generate_export_header(ProtonEngineRenderer BASE_NAME PROTONENGINE_RENDERER EXPORT_FILE_NAME protonengine/renderer/export.h)

target_sources(
        ProtonEngineRenderer
        PRIVATE ${RENDERER_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${RENDERER_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineRenderer,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/renderer/export.h
)

target_include_directories(ProtonEngineRenderer
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ProtonEngineRenderer
        PUBLIC
        ProtonEngine::Core
        PRIVATE
        glad
        glm::glm
        ProtonEngine::Common
)

if (WIN32)
    target_link_libraries(ProtonEngineRenderer PRIVATE opengl32)
endif ()

if (APPLE)
    target_link_libraries(ProtonEngineRenderer PRIVATE "-framework OpenGL")
endif ()

install(
        TARGETS ProtonEngineRenderer
        FILE_SET HEADERS
        FILE_SET generated_headers
)