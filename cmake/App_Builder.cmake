# cmake/build_application.cmake

function(App_builder TARGET_NAME)
    cmake_parse_arguments(
        APP
        ""                                      # no single-letter args
        "OUTPUT_DIR;BUILD_DESTINATION_PATH;WIN32;DEBUG_CONSOLE_INCLUSION_STATE;EXPORT_FLAG"          # single-value keywords
        "SOURCES;HEADERS;LINK_LIBS;PUBLIC_INCLUDES;PRIVATE_INCLUDES"
        ${ARGN}
    )

    # Determine multi-config vs single-config
    if(CMAKE_CONFIGURATION_TYPES)
        set(CONFIG_NAME "$<CONFIG>")
    else()
        set(CONFIG_NAME "${CMAKE_BUILD_TYPE}")
    endif()

    # Where the .exe will live
    set(OUT_DIR "${APP_BUILD_DESTINATION_PATH}/${APP_OUTPUT_DIR}/${CONFIG_NAME}")

    # Add executable (optionally WIN32 GUI)
    if(APP_WIN32)
        add_executable(${TARGET_NAME} WIN32 ${APP_SOURCES})
    else()
        add_executable(${TARGET_NAME} ${APP_SOURCES})
    endif()

    # IDE visibility: inject headers so VS/Xcode show them
    if(APP_HEADERS)
        target_sources(${TARGET_NAME} PRIVATE ${APP_HEADERS})
        source_group("Header Files" FILES ${APP_HEADERS})
    endif()

    # Public & private include paths (BUILD_INTERFACE only)
    if(APP_PUBLIC_INCLUDES)
        target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${APP_PUBLIC_INCLUDES}>)
    endif()
    if(APP_PRIVATE_INCLUDES)
        target_include_directories(${TARGET_NAME} PRIVATE $<BUILD_INTERFACE:${APP_PRIVATE_INCLUDES}>)
    endif()

    # Unicode export flag + UTF-8 compiler options
    if(APP_EXPORT_FLAG)
        target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE ${APP_EXPORT_FLAG})
    else()
        target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
    endif()

    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
        $<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
    )

    # Link libraries (imported targets or full paths)
    if(APP_LINK_LIBS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${APP_LINK_LIBS})
    endif()

    # Automatically include interface directories from imported targets
    foreach(lib IN LISTS APP_LINK_LIBS)
        if(TARGET ${lib})
            get_target_property(INC_DIRS ${lib} INTERFACE_INCLUDE_DIRECTORIES)
            if(INC_DIRS)
                target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIRS})
            endif()
        endif()
    endforeach()

    # Debug CLI inclusion in either Debug or Released builds using int main() | optional use case for WinMain() also supported if 
    # WIN32 is set to TRUE

    if(APP_WIN32 AND APP_DEBUG_CONSOLE_INCLUSION_STATE)
        message(WARNING "DEBUG_CONSOLE_INCLUSION_STATE is ignored when WIN32 is defined as TRUE. Enabling WinMain() entry point for WINDOWS 
        applications only.")
        elseif(NOT APP_WIN32 AND APP_DEBUG_CONSOLE_INCLUSION_STATE)
            if(MSVC)
                if(APP_DEBUG_CONSOLE_INCLUSION_STATE STREQUAL "ENABLED")
                elseif(APP_DEBUG_CONSOLE_INCLUSION_STATE STREQUAL "RELEASE_ONLY")
                    target_link_options(${TARGET_NAME} PRIVATE
                        $<$<CONFIG:Release>:/SUBSYSTEM:CONSOLE>
                        $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
                        $<$<CONFIG:Debug>:/SUBSYSTEM:WINDOWS>
                        $<$<CONFIG:Debug>:/ENTRY:mainCRTStartup>
                    )
                elseif(APP_DEBUG_CONSOLE_INCLUSION_STATE STREQUAL "DISABLED")
                    target_link_options(${TARGET_NAME} PRIVATE
                        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
                        $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
                        $<$<CONFIG:Debug>:/SUBSYSTEM:WINDOWS>
                        $<$<CONFIG:Debug>:/ENTRY:mainCRTStartup>
                    )
                else()
                    message(WARNING "Unknown value for DEBUG_CONSOLE_INCLUSION_STATE: ${APP_DEBUG_CONSOLE_INCLUSION_STATE}")
            endif()
        endif()
    endif()

    # Set output directories
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
        OUTPUT_NAME ${TARGET_NAME}
    )
endfunction()
