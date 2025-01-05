cmake_minimum_required(VERSION 3.20)
project(cyrillic-text-web-win-sdl3-c LANGUAGES C)
add_executable(app)

# Specify where the application source files are stored
target_sources(app
PRIVATE
    src/main.c
)

# Check for WebAssembly
if (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    target_link_options("app" PRIVATE "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/arial.ttf@/assets/fonts/arial.ttf")
    set_property(TARGET "app" APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/arial.ttf")
endif()

# Check for Windows
if (WIN32)
    # Copy the assets folder to the dist folder
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:app>/assets)

    # This code copies DLL's to the dist directory
    #[===[
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
    )
    ]===]

    target_link_options(app PRIVATE -static)
endif()

find_package(SDL3)
find_package(SDL3_ttf)
target_link_libraries(app PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)
