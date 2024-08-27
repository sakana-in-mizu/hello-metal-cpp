#pragma once

#include <Metal/Metal.hpp>

namespace BufferUtils {

void copyBuffer(MTL::Buffer *src, MTL::Buffer *dst, MTL::CommandQueue *command_queue);

};