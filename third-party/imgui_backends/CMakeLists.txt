get_target_property(IMGUI_INCLUDE_DIR imgui::imgui INTERFACE_INCLUDE_DIRECTORIES)
set(IMGUI_BACKEND_DIR ${IMGUI_INCLUDE_DIR}/../res/bindings)

add_library(imgui_backends STATIC
        ${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp
)

target_link_libraries(imgui_backends
        PUBLIC
        imgui::imgui
        glfw
        OpenGL::GL
)

target_include_directories(imgui_backends
        PUBLIC
        ${IMGUI_BACKEND_DIR}
)