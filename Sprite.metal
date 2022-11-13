#include <metal_stdlib>
#include "ShaderTypes.h"
using namespace metal;

// Vertex関数が出力するデータの型定義
typedef struct {
    float4 position [[position]];
    float2 texcoord;
} RasterizerData;

vertex RasterizerData vertexShader(
   uint vertexID [[vertex_id]],
   device const VertexData *vertices
        [[buffer(kShaderVertexInputIndexVertices)]],
   device const CameraData& cameraData
        [[buffer(kShaderVertexInputIndexCamera)]])
{
    const device VertexData& vd = vertices[vertexID];
    RasterizerData result = {};
    float4x4 mvp = cameraData.projectionMatrix * cameraData.modelMatrix;
	result.position = mvp *  float4(vd.position, 0, 1);
    result.texcoord = vd.texcoord;
    return result;
}

fragment half4 fragmentShader(
    RasterizerData in [[stage_in]],
    texture2d<half, access::sample> tex [[texture(kShaderTexture)]])
{
    constexpr sampler s(address::repeat, filter::linear);
    return tex.sample(s, in.texcoord).rgba;
}