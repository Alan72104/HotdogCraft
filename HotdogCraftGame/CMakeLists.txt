cmake_minimum_required(VERSION 3.8)

project(HotdogCraftGame CXX)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/**.h"
)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/**.cpp"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(HotdogCraftGame ${SOURCES} ${HEADERS})
target_include_directories(HotdogCraftGame PUBLIC include)

target_compile_features(HotdogCraftGame PUBLIC cxx_std_23)

target_link_libraries(HotdogCraftGame PRIVATE HotdogCraftCommon)

# configure_file(${ASSET_DIR} assets COPYONLY)

set(ASSET_DIR ${PROJECT_SOURCE_DIR}/../assets)
file(COPY ${ASSET_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
