file(GLOB_RECURSE metal_core_src
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
file(GLOB_RECURSE metal_core_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${metal_core_src} ${metal_core_inc})

add_library(metal_core ${metal_core_src} ${metal_core_inc})
target_include_directories(metal_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp-extensions
)
target_link_libraries(metal_core
    "-framework Metal"
    "-framework MetalKit"
    "-framework AppKit"
    "-framework Foundation"
    "-framework QuartzCore"
)