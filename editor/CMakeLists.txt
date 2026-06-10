file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS src/*.h src/*.cpp)

add_executable(ProtonEditor)

target_sources(
        ProtonEditor
        PRIVATE ${EDITOR_SOURCES}
)

target_link_libraries(ProtonEditor PRIVATE
        ProtonEngine)

#add_dependencies(ProtonEditor ProtonEngine)