#include <metal_stdlib>
#include "ShaderTypes.h"
using namespace metal;

// Vertex関数が出力するデータの型定義
typedef struct {
    // 座標
    float4 position [[position]];
    // 色
    float4 color;
} RasterizerData;

vertex RasterizerData vertexShader(
   uint vertexID [[vertex_id]],
   device const float2 *vertices
        [[buffer(kShaderVertexInputIndexVertices)]],
   device const CameraData& cameraData
        [[buffer(kShaderVertexInputIndexCamera)]])
{
    RasterizerData result = {};
    float4x4 mvp = cameraData.projectionMatrix * cameraData.modelMatrix;
    result.color = float4(1, 1, 1, 1);
	result.position = mvp *  float4(vertices[vertexID], 0, 1);
    return result;
}

fragment float4 fragmentShader(RasterizerData in [[stage_in]])
{
    return in.color;
}