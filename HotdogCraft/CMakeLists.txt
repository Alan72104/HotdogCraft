cmake_minimum_required(VERSION 3.8)

include(cmake/CPM.cmake)

find_package(OpenGL REQUIRED)
CPMAddPackage("gh:glfw/glfw#3.4")
CPMAddPackage("gh:g-truc/glm#1.0.1")
CPMAddPackage(
    NAME stb
    GITHUB_REPOSITORY nothings/stb
    GIT_TAG master
    DOWNLOAD_ONLY YES
)
CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    VERSION 1.91.0-docking
    DOWNLOAD_ONLY YES
)

project(HotdogCraftCommon CXX)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/**.h"
)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/**.cpp"
)
set(DEP_SOURCES
    "${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_demo.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(HotdogCraftCommon STATIC)
target_compile_features(HotdogCraftCommon PUBLIC cxx_std_23)
target_include_directories(HotdogCraftCommon PUBLIC include)

target_sources(HotdogCraftCommon
    PUBLIC
        ${SOURCES}
        ${DEP_SOURCES}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(HotdogCraftCommon PUBLIC stdc++exp)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else()
    message(FATAL_ERROR "C++23 stacktrace library is only supported on G++ or MSVC'")
endif()

target_link_libraries(HotdogCraftCommon PUBLIC
    OpenGL::GL
    glfw
    glm::glm
)
target_include_directories(HotdogCraftCommon PUBLIC deps/glad/include)
if (stb_ADDED)
    target_include_directories(HotdogCraftCommon PUBLIC ${stb_SOURCE_DIR})
endif()
if (imgui_ADDED)
    target_include_directories(HotdogCraftCommon PUBLIC ${imgui_SOURCE_DIR})
    target_include_directories(HotdogCraftCommon PUBLIC ${imgui_SOURCE_DIR}/backends)
endif()
