add_executable(Sandbox
        src/scripts/camera_controller.cpp
        src/scripts/rotator.cpp

        src/main.cpp)

target_link_libraries(Sandbox PRIVATE
        ProtonEngine)

add_dependencies(Sandbox ProtonEngine)

add_subdirectory(assets)

set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")