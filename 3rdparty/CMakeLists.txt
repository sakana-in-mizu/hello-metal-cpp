set(third_party_folder "3rdparty")

if(NOT TARGET metal_core)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/metal-core)
    set_target_properties(metal_core PROPERTIES FOLDER ${third_party_folder})
endif()
