add_executable(Sandbox
        src/scripts/camera_controller.cpp
        src/scripts/rotator.cpp

        src/main.cpp)

target_link_libraries(Sandbox PRIVATE
        ProtonEngine
        fmt)

add_dependencies(Sandbox ProtonEngine)

copy_assets(assets)
