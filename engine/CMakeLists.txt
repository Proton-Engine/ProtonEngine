add_compile_definitions(PROTON_BUILDING_ENGINE)

add_subdirectory(assets)
add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(user_interface)
add_subdirectory(include)
add_subdirectory(renderer)

add_library(ProtonEngine SHARED
        ${PROTON_ENGINE_ASSETS_SOURCES}
        ${PROTON_ENGINE_COMPONENTS_SOURCES}
        ${PROTON_ENGINE_CORE_SOURCES}
        ${PROTON_ENGINE_USER_INTERFACE_SOURCES}
        ${PROTON_ENGINE_RENDERER_SOURCES}

        ${PROTON_ENGINE_ASSETS_HEADERS}
        ${PROTON_ENGINE_COMPONENTS_HEADERS}
        ${PROTON_ENGINE_CORE_HEADERS}
        ${PROTON_ENGINE_USER_INTERFACE_HEADERS}
        ${PROTON_ENGINE_MATH_HEADERS}
        ${PROTON_ENGINE_RENDERER_HEADERS})

source_group(assets FILES ${PROTON_ENGINE_ASSETS_SOURCES})
source_group(components FILES ${PROTON_ENGINE_COMPONENTS_SOURCES})
source_group(core FILES ${PROTON_ENGINE_CORE_SOURCES})
source_group(imgui FILES ${PROTON_ENGINE_USER_INTERFACE_SOURCES})
source_group(renderer FILES ${PROTON_ENGINE_RENDERER_SOURCES})

source_group(include/assets FILES ${PROTON_ENGINE_ASSETS_HEADERS})
source_group(include/components FILES ${PROTON_ENGINE_COMPONENTS_HEADERS})
source_group(include/core FILES ${PROTON_ENGINE_CORE_HEADERS})
source_group(include/imgui FILES ${PROTON_ENGINE_USER_INTERFACE_HEADERS})
source_group(include/math FILES ${PROTON_ENGINE_MATH_HEADERS})
source_group(include/renderer FILES ${PROTON_ENGINE_RENDERER_HEADERS})

target_include_directories(ProtonEngine PUBLIC include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ProtonEngine
        PUBLIC
        EnTT::EnTT
        glm::glm

        PRIVATE
        glad
        stb_image
        glfw
        ImGui)

if(WIN32)
    target_link_libraries(ProtonEngine PRIVATE
            opengl32)
endif()

if (APPLE)
    target_link_libraries(ProtonEngine PRIVATE "-framework OpenGL")
endif()