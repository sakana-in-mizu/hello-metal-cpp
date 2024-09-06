#pragma once

#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    static constexpr uint s_max_frame_in_flight{3};

    Renderer(MTL::Device *device);
    ~Renderer();

    void draw(MTK::View *view);

private:
    MTL::Device       *m_device {};
    MTL::CommandQueue *m_command_queue {};

    MTL::Buffer *m_vertex_buffer {};
    MTL::Buffer *m_index_buffer {};

    MTL::RenderPipelineState *m_pipeline {};

    dispatch_semaphore_t m_semaphore{};

    uint m_frame{0};

    void buildMesh();
    void buildPipeline();
};
