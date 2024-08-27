#pragma once

#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    Renderer(MTL::Device *device);
    ~Renderer();

    void draw(MTK::View *view);

private:
    MTL::Device       *m_device {};
    MTL::CommandQueue *m_command_queue {};

    MTL::Buffer *m_vertex_buffer {};
    MTL::Buffer *m_index_buffer {};

    MTL::RenderPipelineState *m_pipeline {};

    void buildMesh();
    void buildPipeline();
};
