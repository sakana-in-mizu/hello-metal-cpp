#pragma once

#include <Metal/Metal.hpp>

namespace MeshFactory {

struct Mesh {
    MTL::Buffer *vertex_buffer {};
    MTL::Buffer *index_buffer {};
};

MTL::Buffer *buildTriangle(MTL::Device *device);

Mesh buildQuad(MTL::Device *device);

}; // namespace MeshFactory