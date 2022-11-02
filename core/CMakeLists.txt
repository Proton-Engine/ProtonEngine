project(ProtonEngineCore)

add_library(ProtonEngineCore STATIC
        src/application.cpp
        src/window.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

target_link_libraries(ProtonEngineCore PRIVATE
        fmt
        glfw
        glad)

if(WIN32)
    target_link_libraries(ProtonEngineCore PRIVATE
            opengl32)
endif()

if (APPLE)
    target_link_libraries(ProtonEngineCore PRIVATE "-framework OpenGL")
endif()

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)
add_library(ProtonEngine ALIAS ProtonEngineCore)