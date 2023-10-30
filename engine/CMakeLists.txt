add_compile_definitions(PROTON_BUILDING_ENGINE)

set(PROTON_ENGINE_SOURCES)

add_subdirectory(assets)
add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(renderer)

add_library(ProtonEngine SHARED ${PROTON_ENGINE_SOURCES})

target_include_directories(ProtonEngine PUBLIC include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ProtonEngine
        PUBLIC
        EnTT::EnTT
        glm::glm

        PRIVATE
        fmt
        glad
        stb_image
        glfw)

if(WIN32)
    target_link_libraries(ProtonEngine PRIVATE
            opengl32)
endif()

if (APPLE)
    target_link_libraries(ProtonEngine PRIVATE "-framework OpenGL")
endif()