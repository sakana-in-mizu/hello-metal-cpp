cmake_minimum_required(VERSION 3.21)

project(hello_metal_cpp)

set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(FATAL_ERROR "This project can only be built on macOS.")
endif()

set(shader_lib_path ${CMAKE_BINARY_DIR}/shaders/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/shaders)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty)

file(GLOB_RECURSE hello_metal_cpp_src
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE hello_metal_cpp_inc
    ${CMAKE_SOURCE_DIR}/src/*.h
)

source_group(TREE ${CMAKE_SOURCE_DIR}/src FILES ${hello_metal_cpp_src} ${hello_metal_cpp_inc})

add_executable(${PROJECT_NAME} ${hello_metal_cpp_src} ${hello_metal_cpp_inc})
target_link_libraries(${PROJECT_NAME} metal_core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

configure_file(${CMAKE_SOURCE_DIR}/shaders/shader_path_config.h.in ${CMAKE_BINARY_DIR}/shader_path_config.h @ONLY)
add_dependencies(${PROJECT_NAME} shaders)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})