#include "mesh_factory.h"

#include <string.h>

#include <simd/simd.h>

namespace MeshFactory {

struct VertexWithColor {
    simd::float3 position {};
    simd::float3 color {};
};

MTL::Buffer *buildTriangle(MTL::Device *device) {
    // clang-format off
    VertexWithColor vertices[] = {
        {{-0.75, -0.75, 0.0}, {1.0, 0.0, 0.0}},
        {{ 0.75, -0.75, 0.0}, {0.0, 1.0, 0.0}},
        {{  0.0,  0.75, 0.0}, {0.0, 0.0, 1.0}}
    };
    // clang-format on

    MTL::Buffer *staging_buffer = device->newBuffer(sizeof(vertices), MTL::ResourceStorageModeShared);
    memcpy(staging_buffer->contents(), vertices, sizeof(vertices));
    return staging_buffer;
}

Mesh buildQuad(MTL::Device *device) {
    // clang-format off
    VertexWithColor vertices[] = {
        {{-0.75, -0.75, 0.0}, {1.0, 0.0, 0.0}},
        {{ 0.75, -0.75, 0.0}, {0.0, 1.0, 0.0}},
        {{ 0.75,  0.75, 0.0}, {0.0, 0.0, 1.0}},
        {{-0.75,  0.75, 0.0}, {1.0, 1.0, 1.0}}
    };

    ushort indices[] = {0, 1, 2, 2, 3, 0};
    // clang-format on

    Mesh mesh;
    mesh.vertex_buffer = device->newBuffer(sizeof(vertices), MTL::ResourceStorageModeShared);
    mesh.index_buffer  = device->newBuffer(sizeof(indices), MTL::ResourceStorageModeShared);

    memcpy(mesh.vertex_buffer->contents(), vertices, sizeof(vertices));
    memcpy(mesh.index_buffer->contents(), indices, sizeof(indices));

    return mesh;
}

} // namespace MeshFactory
