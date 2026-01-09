function(build_and_export_library TARGET_NAME)
    cmake_parse_arguments(
        LIB
        ""
        "OUTPUT_DIR;BUILD_DESTINATION_PATH;VERSION;EXPORT_FLAG"
        "SOURCES;HEADERS;LINK_LIBS;PUBLIC_INCLUDES;PRIVATE_INCLUDES"
        ${ARGN}
    )

    # Determine configuration name
    if(CMAKE_CONFIGURATION_TYPES)
        set(CONFIG_NAME "$<CONFIG>")
    else()
        set(CONFIG_NAME "${CMAKE_BUILD_TYPE}")
    endif()

    # Base output directory with config folder
    set(BASE_OUT "${LIB_BUILD_DESTINATION_PATH}/${LIB_OUTPUT_DIR}/${CONFIG_NAME}")

    # Create necessary sub-folders
    file(MAKE_DIRECTORY "${BASE_OUT}/bin")
    file(MAKE_DIRECTORY "${BASE_OUT}/include/${TARGET_NAME}")
    file(MAKE_DIRECTORY "${BASE_OUT}/cmake")

    # Create shared library
    add_library(${TARGET_NAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})

    # Include directories
    target_include_directories(${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${LIB_PUBLIC_INCLUDES}>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            $<BUILD_INTERFACE:${LIB_PRIVATE_INCLUDES}>
            $<INSTALL_INTERFACE:internal/>
    )

    # Compile definitions
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE ${LIB_EXPORT_FLAG})

    # UTF-8 compile options
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # Link libraries (if any)
    if(LIB_LINK_LIBS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_LINK_LIBS})
    endif()

    # Output directories
    
    # Output directories (DLL → bin/, LIB → lib/)

    # Copy headers
    if(LIB_HEADERS)
        foreach(header IN LISTS LIB_HEADERS)
            configure_file(${header} "${BASE_OUT}/include/${TARGET_NAME}/" COPYONLY)
        endforeach()
    endif()

    # -------------------------------
    # Config + Version + Export (relocatable)
    # -------------------------------
    include(CMakePackageConfigHelpers)

    if(NOT LIB_VERSION)
        set(LIB_VERSION "1.0.0")
    endif()

    set(CONFIG_FILE  "${BASE_OUT}/cmake/${TARGET_NAME}Config.cmake")
    set(VERSION_FILE "${BASE_OUT}/cmake/${TARGET_NAME}ConfigVersion.cmake")

    write_basic_package_version_file(
        "${VERSION_FILE}"
        VERSION ${LIB_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
        "${CONFIG_FILE}"
        INSTALL_DESTINATION cmake      # Relocatable install path
    )

    # Install target and export (relocatable)
    install(TARGETS ${TARGET_NAME}
        EXPORT ${TARGET_NAME}Targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include/${TARGET_NAME}
    )

    install(EXPORT ${TARGET_NAME}Targets
        NAMESPACE ${TARGET_NAME}::
        DESTINATION cmake
    )

    # Ensures all files are properly moved to the users preferred destination 
    get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
    foreach(tgt IN LISTS all_targets)
        # Skip the library itself
        if(tgt STREQUAL ${TARGET_NAME})
            continue()
        endif()

        # Check if this target links against the library
        get_target_property(linked_libs ${tgt} LINK_LIBRARIES)
        if(linked_libs MATCHES ${TARGET_NAME})
            add_custom_command(TARGET ${tgt} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${BASE_OUT}/bin/${TARGET_NAME}.dll"
                    $<TARGET_FILE_DIR:${tgt}>
                COMMENT "Auto-copying ${TARGET_NAME}.dll to ${tgt} output directory"
            )
        endif()
    endforeach()

    # -------------------------------
    # Visual Studio-friendly automatic install
    # -------------------------------
    add_custom_target(install_${TARGET_NAME} ALL
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix ${BASE_OUT}
        DEPENDS ${TARGET_NAME}
        COMMENT "Installing ${TARGET_NAME} (headers, binaries, cmake files) to ${BASE_OUT}"
    )

    message(STATUS "Library ${TARGET_NAME} built in ${BASE_OUT}/bin")
    message(STATUS "Headers copied to ${BASE_OUT}/include/${TARGET_NAME}")
    message(STATUS "Config: ${CONFIG_FILE}")
    message(STATUS "Version: ${VERSION_FILE}")
endfunction()
