project(ProtonEngineCore)

add_library(ProtonEngineCore SHARED
        src/application.cpp
        src/asset_manager.cpp
        src/cube.cpp
        src/entity.cpp
        src/scene.cpp
        src/delta_time.cpp
        src/triangle.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PRIVATE include)

target_link_libraries(ProtonEngineCore
        PUBLIC
        EnTT::EnTT
        glm::glm
        ProtonEngine::SDK

        PRIVATE
        ProtonEngine::Renderer
        ProtonEngine::Components
        ProtonEngine::Assets

        fmt
        glfw
        stb_image)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)

set_target_properties(ProtonEngineCore PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR})

#target_compile_definitions(ProtonEngineCore PRIVATE PROTON_BUILDING_ENGINE)