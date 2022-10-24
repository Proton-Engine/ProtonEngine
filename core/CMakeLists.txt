project(ProtonEngineCore)

add_library(ProtonEngineCore SHARED
        src/application.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

target_link_libraries(ProtonEngineCore PRIVATE
        fmt
        glfw)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)
add_library(ProtonEngine ALIAS ProtonEngineCore)