#include "config_manager.h"

#include "shader_path_config.h"

std::filesystem::path ConfigManager::shaderLibPath() {
    std::filesystem::path result {SHADER_LIB_PATH};
    return result;
}