function(copy_assets assetDirectory)
    file(GLOB_RECURSE ASSETS
            "${assetDirectory}/*"
    )

    foreach (asset ${ASSETS})
        get_filename_component(assetName ${asset} NAME)
        get_filename_component(pathWithoutName "${asset}" PATH)
        get_filename_component(assetTypeDirectory "${pathWithoutName}" NAME)

        configure_file(${asset} ${BINARY_DIRECTORY}/assets/${assetTypeDirectory}/${assetName} COPYONLY)
    endforeach ()

endfunction()