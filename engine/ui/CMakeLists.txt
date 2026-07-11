set(MODULE_NAME Ui)
set(FULL_MODULE_NAME ProtonEngine${MODULE_NAME})
set(ALIAS_MODULE_NAME ProtonEngine::${MODULE_NAME})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)
file(GLOB_RECURSE INSTALL_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdk sdk/*.h)

source_group(src FILES ${SOURCES})
source_group(include FILES ${HEADERS})
source_group(sdk FILES ${INSTALL_HEADERS})

add_library(${FULL_MODULE_NAME} OBJECT)
add_library(${ALIAS_MODULE_NAME} ALIAS ${FULL_MODULE_NAME})

target_sources(
        ${FULL_MODULE_NAME}
        PRIVATE
        ${SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${HEADERS}
        PUBLIC
        FILE_SET installed_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/sdk
        FILES ${INSTALL_HEADERS}
)

target_include_directories(${FULL_MODULE_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sdk>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE src
)

target_link_libraries(${FULL_MODULE_NAME}
        PUBLIC
        ProtonEngine::Export
        PRIVATE
        imgui::imgui
        imgui_backends
        glfw
)

install(
        TARGETS ${FULL_MODULE_NAME}
        FILE_SET installed_headers
)