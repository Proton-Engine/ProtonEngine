set(PROTON_ENGINE_SOURCES ${PROTON_ENGINE_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
        PARENT_SCOPE)

configure_file(shaders/shader.fragment ${BINARY_DIRECTORY}/assets/shaders/shader.fragment COPYONLY)
configure_file(shaders/shader.vertex ${BINARY_DIRECTORY}/assets/shaders/shader.vertex COPYONLY)
