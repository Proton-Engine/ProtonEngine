file(GLOB_RECURSE ASSETS CONFIGURE_DEPENDS LIST_DIRECTORIES false "*")

foreach (asset ${ASSETS})
    get_filename_component(assetName ${asset} NAME)
    get_filename_component(pathWithoutName "${asset}" PATH)
    get_filename_component(assetTypeDirectory "${pathWithoutName}" NAME)

    if (NOT ${assetName} STREQUAL "CMakeLists.txt")
        configure_file(${asset} ${BINARY_DIRECTORY}/assets/${assetTypeDirectory}/${assetName} COPYONLY)
    endif ()
endforeach ()