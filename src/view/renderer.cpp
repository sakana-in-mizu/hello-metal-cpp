#include "renderer.h"

#include <assert.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <Foundation/Foundation.hpp>

#include "config/config_manager.h"
#include "mesh_factory.h"
#include "utils/buffer_utils.h"

#include <simd/simd.h>

Renderer::Renderer(MTL::Device *device) : m_device(device->retain()) {
    m_command_queue = device->newCommandQueue();
    buildMesh();
    buildPipeline();

    m_semaphore = dispatch_semaphore_create(s_max_frame_in_flight);
}

Renderer::~Renderer() {
    m_pipeline->release();

    m_vertex_buffer->release();
    m_index_buffer->release();
    m_device->release();
    m_command_queue->release();
}

void Renderer::draw(MTK::View *view) {
    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();

    m_frame = (m_frame + 1) % s_max_frame_in_flight;

    MTL::CommandBuffer *command_buffer = m_command_queue->commandBuffer();
    dispatch_semaphore_wait(m_semaphore, DISPATCH_TIME_FOREVER);
    command_buffer->addCompletedHandler([this](MTL::CommandBuffer *command_buffer) {
        dispatch_semaphore_signal(m_semaphore);
    });

    MTL::RenderPassDescriptor *render_pass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder *encoder     = command_buffer->renderCommandEncoder(render_pass);

    encoder->setVertexBuffer(m_vertex_buffer, 0, 0);
    encoder->setRenderPipelineState(m_pipeline);

    encoder->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, 6, MTL::IndexTypeUInt16, m_index_buffer, 0, 1);

    encoder->endEncoding();
    command_buffer->presentDrawable(view->currentDrawable());
    command_buffer->commit();

    pool->release();
}

void Renderer::buildMesh() {
    auto staging = MeshFactory::buildQuad(m_device);

    m_vertex_buffer = m_device->newBuffer(staging.vertex_buffer->length(), MTL::ResourceStorageModePrivate);
    m_index_buffer  = m_device->newBuffer(staging.index_buffer->length(), MTL::ResourceStorageModePrivate);

    BufferUtils::copyBuffer(staging.vertex_buffer, m_vertex_buffer, m_command_queue);
    BufferUtils::copyBuffer(staging.index_buffer, m_index_buffer, m_command_queue);

    staging.vertex_buffer->release();
    staging.index_buffer->release();
}

void Renderer::buildPipeline() {
    NS::Error *error = nullptr;

    auto        concatenated_path = ConfigManager::shaderLibPath() / "mesh_with_color.metallib";
    NS::String *shader_lib_path   = NS::String::string(concatenated_path.c_str(), NS::UTF8StringEncoding);

    MTL::Library *library = m_device->newLibrary(shader_lib_path, &error);
    if (!library) {
        std::cerr << error->localizedDescription()->utf8String() << std::endl;
    }

    NS::String    *vertex_name = NS::String::string("vertexMain", NS::UTF8StringEncoding);
    MTL::Function *vertex_main = library->newFunction(vertex_name);

    NS::String    *fragment_name = NS::String::string("fragmentMain", NS::UTF8StringEncoding);
    MTL::Function *fragment_main = library->newFunction(fragment_name);

    MTL::RenderPipelineDescriptor *pipeline_descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipeline_descriptor->setVertexFunction(vertex_main);
    pipeline_descriptor->setFragmentFunction(fragment_main);
    pipeline_descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm_sRGB);

    MTL::VertexDescriptor *vertex_descriptor = MTL::VertexDescriptor::alloc()->init();

    auto attributes = vertex_descriptor->attributes();

    auto position_attrib = attributes->object(0);
    position_attrib->setFormat(MTL::VertexFormatFloat3);
    position_attrib->setBufferIndex(0);
    position_attrib->setOffset(0);

    auto color_attrib = attributes->object(1);
    color_attrib->setFormat(MTL::VertexFormatFloat3);
    color_attrib->setBufferIndex(0);
    color_attrib->setOffset(sizeof(simd::float3));

    auto layout_descriptor = vertex_descriptor->layouts()->object(0);
    layout_descriptor->setStride(2 * sizeof(simd::float3));

    pipeline_descriptor->setVertexDescriptor(vertex_descriptor);

    m_pipeline = m_device->newRenderPipelineState(pipeline_descriptor, &error);
    if (!m_pipeline) {
        std::cerr << error->localizedDescription()->utf8String() << std::endl;
    }

    vertex_descriptor->release();
    pipeline_descriptor->release();
    fragment_main->release();
    vertex_main->release();
    library->release();
}
