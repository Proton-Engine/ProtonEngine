file(GLOB_RECURSE UI_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE UI_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${UI_SOURCES})
source_group(include FILES ${UI_HEADERS})

add_library(ProtonEngineUi SHARED)
add_library(ProtonEngine::Ui ALIAS ProtonEngineUi)
generate_export_header(ProtonEngineUi BASE_NAME PROTONENGINE_UI EXPORT_FILE_NAME protonengine/ui/export.h)

target_sources(
        ProtonEngineUi
        PRIVATE ${UI_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${UI_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineUi,BINARY_DIR>
        FILES ${CMAKE_CURRENT_BINARY_DIR}/protonengine/ui/export.h
)

target_include_directories(ProtonEngineUi
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ProtonEngineUi
        PRIVATE
        ImGui
        glfw
)

install(
        TARGETS ProtonEngineUi
        FILE_SET HEADERS
        FILE_SET generated_headers
)