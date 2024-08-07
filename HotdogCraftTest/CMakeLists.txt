cmake_minimum_required (VERSION 3.8)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
)

FetchContent_MakeAvailable(Catch2)

project(HotdogCraftTests CXX)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/**.h"
)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/**.cpp"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(HotdogCraftTests ${SOURCES} ${HEADERS})
target_include_directories(HotdogCraftTests PUBLIC include)

target_compile_features(HotdogCraftTests PUBLIC cxx_std_23)

target_link_libraries(HotdogCraftTests PRIVATE HotdogCraftCommon)

set(ASSET_DIR ${PROJECT_SOURCE_DIR}/../assets)
file(COPY ${ASSET_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
