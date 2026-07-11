function(configure_rpath target)

    if (APPLE)
        set(_rpath "@loader_path/../lib")
    elseif (UNIX)
        set(_rpath "$ORIGIN/../lib")
    endif ()

    if (UNIX)
        set_target_properties(${target} PROPERTIES
                INSTALL_RPATH "${_rpath}"
        )
    endif ()

endfunction()