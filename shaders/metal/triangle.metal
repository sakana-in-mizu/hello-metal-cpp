#include <metal_stdlib>
using namespace metal;

struct VertexPayload {
    float4 position [[position]];
    half3 color;
};

constant float4 positions[] = {
    float4(-0.75, -0.75, 0.0, 1.0), //bottom left: red
    float4( 0.75, -0.75, 0.0, 1.0), //bottom right: green
    float4(  0.0,  0.75, 0.0, 1.0), //center top: blue
};

constant half3 colors[] = {
    half3(1.0, 0.0, 0.0), //bottom left: red
    half3(0.0, 1.0, 0.0), //bottom right: green
    half3(0.0, 0.0, 1.0), //center top: blue
};

VertexPayload vertex vertexMain(uint vert_id [[vertex_id]]) {
    VertexPayload payload;
    payload.position = positions[vert_id];
    payload.color = colors[vert_id];
    return payload;
}

half4 fragment fragmentMain(VertexPayload frag [[stage_in]]) {
    return half4(frag.color, 1.0);
}