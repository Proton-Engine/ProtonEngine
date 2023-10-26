project(ProtonEngineComponents)

add_library(ProtonEngineComponents STATIC
        src/temp.cpp)

target_include_directories(ProtonEngineComponents PUBLIC include)

target_link_libraries(ProtonEngineComponents
        PUBLIC
        glm::glm

        PRIVATE
        ProtonEngine::SDK
        fmt)

add_library(ProtonEngine::Components ALIAS ProtonEngineComponents)