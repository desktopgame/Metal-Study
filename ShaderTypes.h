#ifndef SHADER_TYPES_H
#define SHADER_TYPES_H

#include <simd/simd.h>

enum {
  kShaderVertexInputIndexVertices = 0,
  kShaderVertexInputIndexCamera = 1,
};

typedef struct {
  simd::float4x4 modelMatrix;
  simd::float4x4 viewMatrix;
  simd::float4x4 projectionMatrix;
} CameraData;

#endif /* SHADER_TYPES_H */