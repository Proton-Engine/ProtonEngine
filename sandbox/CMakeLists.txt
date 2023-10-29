add_executable(Sandbox
        src/main.cpp)

target_link_libraries(Sandbox PRIVATE
        ProtonEngine
        fmt)

add_dependencies(Sandbox ProtonEngine)

file(GLOB ASSETS
        "assets/*"
)
file(COPY ${ASSETS} DESTINATION "${BINARY_DIRECTORY}/assets")