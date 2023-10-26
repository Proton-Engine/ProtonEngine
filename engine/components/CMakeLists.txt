project(ProtonEngineComponents)

add_library(ProtonEngineComponents STATIC
        include/protonengine/components/mesh_renderer.h
        include/protonengine/components/tag.h
        include/protonengine/components/transform.h

        src/temp.cpp)

target_include_directories(ProtonEngineComponents PUBLIC include)

target_link_libraries(ProtonEngineComponents
        PUBLIC
        glm::glm

        PRIVATE
        fmt)

add_library(ProtonEngine::Components ALIAS ProtonEngineComponents)