add_executable(Sandbox
        src/main.cpp)

target_link_libraries(Sandbox PRIVATE
        ProtonEngine::Core
        fmt)

file(GLOB ASSETS
        "assets/*"
)
file(COPY ${ASSETS} DESTINATION assets)