#include "buffer_utils.h"

namespace BufferUtils {

void copyBuffer(MTL::Buffer *src, MTL::Buffer *dst, MTL::CommandQueue *command_queue) {
    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer *command_buffer = command_queue->commandBuffer();

    MTL::BlitCommandEncoder *encoder = command_buffer->blitCommandEncoder();
    encoder->copyFromBuffer(src, 0, dst, 0, src->length());
    encoder->endEncoding();

    command_buffer->commit();
    command_buffer->waitUntilCompleted();

    pool->release();
}

} // namespace BufferUtils