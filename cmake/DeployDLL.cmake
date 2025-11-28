function(copy_library_post_build LIB_TARGET DEST_DIR)
    if(NOT TARGET ${LIB_TARGET})
        message(FATAL_ERROR "Target ${LIB_TARGET} does not exist!")
    endif()

    if(NOT DEST_DIR)
        message(FATAL_ERROR "Destination directory must be provided for copy_library_post_build()")
    endif()

    # Ensure the destination exists
    file(MAKE_DIRECTORY ${DEST_DIR})

    # Copy runtime library (DLL/.so/.dylib)
    add_custom_command(TARGET ${LIB_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${LIB_TARGET}>"
            "${DEST_DIR}"
        COMMENT "Copying runtime library ${LIB_TARGET} to ${DEST_DIR}"
    )

    # Copy import library (LIB/.a)
    add_custom_command(TARGET ${LIB_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_LINKER_FILE:${LIB_TARGET}>"
            "${DEST_DIR}"
        COMMENT "Copying import library ${LIB_TARGET} to ${DEST_DIR}"
    )

endfunction()
