#pragma once

#include <filesystem>

class ConfigManager {
public:
    static std::filesystem::path shaderLibPath();
};