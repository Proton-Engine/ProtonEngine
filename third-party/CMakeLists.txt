add_subdirectory(entt)
add_subdirectory(fmt)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(stb_image)

file(GLOB IMGUI_SOURCE_FILES imgui/*.cpp imgui/*.h imgui/backends/imgui_impl_opengl3* imgui/backends/imgui_impl_glfw.* imgui/misc/cpp/imgui_stdlib.*)

add_library(ImGui STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_BACKENDS_SOURCE_FILES})
target_include_directories(ImGui PUBLIC imgui)
target_link_libraries(ImGui PRIVATE glfw)
