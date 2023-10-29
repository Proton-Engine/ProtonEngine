project(ProtonEngineSDK)

add_library(ProtonEngineSDK INTERFACE)

target_include_directories(ProtonEngineSDK INTERFACE include)

add_library(ProtonEngine::SDK ALIAS ProtonEngineSDK)
