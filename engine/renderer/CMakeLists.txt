set(PROTON_ENGINE_RENDERER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/opengl/opengl_renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/opengl/opengl_renderer.h

        ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
        PARENT_SCOPE)