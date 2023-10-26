project(ProtonEngineCore)

add_library(ProtonEngineCore STATIC
        src/assets/image.cpp

        src/application.cpp
        src/asset_manager.cpp
        src/cube.cpp
        src/entity.cpp
        src/scene.cpp
        src/triangle.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

target_link_libraries(ProtonEngineCore
        PUBLIC
        EnTT::EnTT
        glm::glm
        ProtonEngine::Renderer

        PRIVATE
        fmt
        glfw
        stb_image)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)