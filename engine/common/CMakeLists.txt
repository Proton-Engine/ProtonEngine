file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB_RECURSE COMMON_HEADERS CONFIGURE_DEPENDS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include include/*.h)

source_group(src FILES ${COMMON_SOURCES})
source_group(include FILES ${COMMON_HEADERS})

add_library(ProtonEngineCommon STATIC)
add_library(ProtonEngine::Common ALIAS ProtonEngineCommon)

target_sources(
        ProtonEngineCommon
        PRIVATE ${COMMON_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES ${COMMON_HEADERS}
)

target_include_directories(ProtonEngineCommon
        PUBLIC include
)