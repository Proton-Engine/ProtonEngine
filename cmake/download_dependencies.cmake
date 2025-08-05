SET(CPM_SOURCE_CACHE ${CMAKE_CURRENT_SOURCE_DIR}/third-party/cpm)

CPMAddPackage("gh:skypjack/entt#v3.15.0")
#CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:glfw/glfw#3.4")
CPMAddPackage("gh:g-truc/glm#1.0.1")
CPMAddPackage(NAME "IMGUI" DOWNLOAD_ONLY YES GIT_REPOSITORY "https://github.com/ocornut/imgui" VERSION 1.92.1)

file(GLOB IMGUI_SOURCE_FILES
        ${IMGUI_SOURCE_DIR}/*.cpp
        ${IMGUI_SOURCE_DIR}/*.h
        ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3*
        ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.*
        ${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.*)

add_library(ImGui STATIC ${IMGUI_SOURCE_FILES})
target_include_directories(ImGui PUBLIC ${IMGUI_SOURCE_DIR})
target_link_libraries(ImGui PRIVATE glfw)