file(GLOB_RECURSE metal_shader_src ${CMAKE_CURRENT_SOURCE_DIR}/*.metal)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${metal_shader_src})

foreach(shader_src ${metal_shader_src})
    message("compiling ${shader_src}")

    get_filename_component(shader_name ${shader_src} NAME_WE)
    set(shader_air ${CMAKE_BINARY_DIR}/shaders/air/${shader_name}.air)
    
    add_custom_command(
        OUTPUT ${shader_air}
        COMMAND xcrun -sdk macosx metal -o ${shader_air} -c ${shader_src}
        DEPENDS ${metal_shader}
    )

    set(shader_lib ${shader_lib_path}/${shader_name}.metallib)
    add_custom_command(
        OUTPUT ${shader_lib}
        COMMAND xcrun -sdk macosx metallib -o ${shader_lib} ${shader_air}
        DEPENDS ${shader_air}
    )

    list(APPEND metal_shader_lib ${shader_lib})
endforeach()

add_custom_target(shaders ALL
    DEPENDS ${metal_shader_lib}
    SOURCES ${metal_shader_src}
    COMMENT "Building Metal shader library"
)