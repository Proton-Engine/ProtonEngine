file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${CORE_SOURCES})
source_group(include FILES ${CORE_HEADERS})

add_library(ProtonEngineCore OBJECT)
add_library(ProtonEngine::Core ALIAS ProtonEngineCore)

target_link_libraries(ProtonEngineCore PUBLIC ProtonEngine::Export)

target_sources(
        ProtonEngineCore
        PRIVATE ${CORE_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${CORE_HEADERS}
        FILE_SET generated_headers
        TYPE HEADERS
        BASE_DIRS $<TARGET_PROPERTY:ProtonEngineCore,BINARY_DIR>
)

target_include_directories(ProtonEngineCore
        PUBLIC include
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ProtonEngineCore
        PUBLIC
        ProtonEngine::Export
        ProtonEngine::Common
        ProtonEngine::Assets
        ProtonEngine::Renderer
        ProtonEngine::Ui
        EnTT::EnTT
        PRIVATE
        glfw
)

install(
        TARGETS ProtonEngineCore
        FILE_SET HEADERS
        FILE_SET generated_headers
)