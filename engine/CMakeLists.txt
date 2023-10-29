add_compile_definitions(PROTON_BUILDING_ENGINE)

add_subdirectory(assets)
add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(sdk)

add_library(ProtonEngine ALIAS ProtonEngineCore)