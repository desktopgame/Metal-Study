#pragma once
// このマクロ定義が必要。詳細は以下
// https://stackoverflow.com/questions/54930382/is-the-glm-math-library-compatible-with-apples-metal-shading-language
#define GLM_FORCE_DEPTH_ZERO_TO_ONE 1

#include "CAMetalLayer.hpp"
#include "CocoaWindow.hpp"
#include "Metal.hpp"
#include "NSView.hpp"
#include "NSWindow.hpp"
#include "ShaderTypes.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct GLFWwindow;
class Renderer {
public:
  explicit Renderer();
  ~Renderer();
  void setup(GLFWwindow *window);
  void render();

private:
  void initShader(MTL::RenderPipelineDescriptor *desc, const std::string &file,
                  const std::string &vert, const std::string &frag);
  void initBuffer();
  static NS::String *makeString(const std::string &chars);
  static simd::float4x4 glm2simd(const glm::mat4 &mat);
  MTL::Device *m_device;
  MTL::Library *m_library;
  MTL::CommandQueue *m_commandQueue;
  MTL::RenderPipelineState *m_renderPipelineState;
  MTL::Buffer *m_vertexBuffer;
  MTL::Buffer *m_indexBuffer;
  MTL::Buffer *m_cameraBuffer;
  CA::MetalLayer *m_layer;
};