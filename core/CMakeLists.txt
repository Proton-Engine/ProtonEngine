project(ProtonEngineCore)

add_library(ProtonEngineCore SHARED src/proton_application.cpp)

target_include_directories(ProtonEngineCore PUBLIC include)

add_library(ProtonEngine::Core ALIAS ProtonEngineCore)
add_library(ProtonEngine ALIAS ProtonEngineCore)