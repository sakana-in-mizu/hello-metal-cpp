#include <metal_stdlib>
using namespace metal;

struct VertexInput {
    float3 position [[attribute(0)]];
    float3 color [[attribute(1)]];
};

struct VertexOutput {
    float4 position [[position]];
    half3 color;
};

VertexOutput vertex vertexMain(VertexInput input [[stage_in]]) {
    VertexOutput output;
    output.position = float4(input.position, 1.0);
    output.color = half3(input.color);
    return output;
}

half4 fragment fragmentMain(VertexOutput frag [[stage_in]]) {
    return half4(frag.color, 1.0);
}
