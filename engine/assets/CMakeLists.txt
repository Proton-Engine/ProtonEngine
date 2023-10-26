project(ProtonEngineAssets)

add_library(ProtonEngineAssets STATIC
        src/image.cpp)

target_include_directories(ProtonEngineAssets PUBLIC include)

target_link_libraries(ProtonEngineAssets
        PRIVATE
        ProtonEngine::SDK
        fmt)

add_library(ProtonEngine::Assets ALIAS ProtonEngineAssets)