#include "Renderer.hpp"
#include <glm/ext.hpp>
#include <iostream>
#include <string>

Renderer::Renderer()
    : m_device(nullptr), m_library(nullptr), m_commandQueue(nullptr),
      m_renderPipelineState(nullptr), m_vertexBuffer(nullptr),
      m_indexBuffer(nullptr), m_cameraBuffer(nullptr){};
Renderer::~Renderer() {
  m_vertexBuffer->release();
  m_indexBuffer->release();
  m_library->release();
  m_renderPipelineState->release();
  m_commandQueue->release();
  m_device->release();
  m_layer->release();
}
void Renderer::setup(GLFWwindow *window) {
  m_device = MTL::CreateSystemDefaultDevice();
  m_commandQueue = m_device->newCommandQueue();
  // シェーダー初期化
  MTL::RenderPipelineDescriptor *desc =
      MTL::RenderPipelineDescriptor::alloc()->init();
  initShader(desc, "Sprite.metallib", "vertexShader", "fragmentShader");
  // パイプライン初期化
  NS::Error *pipError = nullptr;
  m_renderPipelineState = m_device->newRenderPipelineState(desc, &pipError);
  if (pipError) {
    std::abort();
  }
  desc->release();
  // レイヤー初期化
  m_layer = CA::MetalLayer::alloc()->init();
  m_layer->setDevice(m_device);
  m_layer->setOpaque(true);
  NS::Window *nsWindow =
      NS::Window::bridgingCast(GLFW::Private::getCocoaWindow(window));
  NS::View *contentView = nsWindow->contentView();
  contentView->setLayer(m_layer);
  contentView->setWantsLayer(true);
  // 頂点情報を作成
  initBuffer();
}
void Renderer::render() {
  CA::MetalDrawable *surface = m_layer->nextDrawable();
  MTL::CommandBuffer *buffer = m_commandQueue->commandBuffer();
  MTL::RenderPassDescriptor *pass = MTL::RenderPassDescriptor::alloc();
  pass->init();
  MTL::RenderPassColorAttachmentDescriptor *desc =
      pass->colorAttachments()->object(0);
  desc->setClearColor(MTL::ClearColor(1.0, 0.0, 0.0, 1.0));
  desc->setLoadAction(MTL::LoadAction::LoadActionClear);
  desc->setStoreAction(MTL::StoreAction::StoreActionStore);
  desc->setTexture(surface->texture());
  MTL::RenderCommandEncoder *encoder = buffer->renderCommandEncoder(pass);
  encoder->setRenderPipelineState(m_renderPipelineState);
  encoder->setVertexBuffer(m_vertexBuffer, 0, kShaderVertexInputIndexVertices);
  encoder->setVertexBuffer(m_cameraBuffer, 0, kShaderVertexInputIndexCamera);
  encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 6,
                                 MTL::IndexType::IndexTypeUInt16, m_indexBuffer,
                                 0);
  encoder->endEncoding();
  buffer->presentDrawable(surface);
  buffer->commit();
  pass->release();
}
// private
void Renderer::initShader(MTL::RenderPipelineDescriptor *desc,
                          const std::string &file, const std::string &vert,
                          const std::string &frag) {
  // シェーダーのコンパイル
  NS::Error *libError = nullptr;
  m_library = m_device->newLibrary(makeString(file), &libError);
  if (libError) {
    std::abort();
  }
  MTL::Function *vFunc = m_library->newFunction(makeString(vert));
  MTL::Function *fFunc = m_library->newFunction(makeString(frag));
  desc->setVertexFunction(vFunc);
  desc->setFragmentFunction(fFunc);
  desc->colorAttachments()->object(0)->setPixelFormat(
      MTL::PixelFormatBGRA8Unorm);
  desc->setDepthAttachmentPixelFormat(MTL::PixelFormat::PixelFormatInvalid);
}

void Renderer::initBuffer() {
  const float left = 0;
  const float right = 1;
  const float top = 0;
  const float bottom = 1;
  const float verts[] = {left, top, right, top, right, bottom, left, bottom};
  const uint16_t index[] = {0, 1, 2, 2, 3, 0};
  const MTL::ResourceOptions bufOption = MTL::ResourceStorageModeManaged;
  m_vertexBuffer = m_device->newBuffer(sizeof(float) * 8, bufOption);
  m_indexBuffer = m_device->newBuffer(sizeof(uint16_t) * 6, bufOption);
  m_cameraBuffer = m_device->newBuffer(sizeof(CameraData), bufOption);
  ::memcpy(m_vertexBuffer->contents(), verts, sizeof(float) * 8);
  ::memcpy(m_indexBuffer->contents(), index, sizeof(uint16_t) * 6);
  m_vertexBuffer->didModifyRange(NS::Range::Make(0, m_vertexBuffer->length()));
  m_indexBuffer->didModifyRange(NS::Range::Make(0, m_indexBuffer->length()));
  // カメラを作成
  CameraData *camera =
      reinterpret_cast<CameraData *>(m_cameraBuffer->contents());
  camera->modelMatrix = glm2simd(
      glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3((1280 - 100) / 2,
                                                           (720 - 100) / 2, 0)),
                 glm::vec3(100, 100, 1)));
  camera->viewMatrix = glm2simd(glm::mat4(1.0f));
  camera->projectionMatrix =
      glm2simd(glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f /* lrbt*/, 0.0f, 1.0f));
  m_cameraBuffer->didModifyRange(NS::Range(0, m_cameraBuffer->length()));
}

NS::String *Renderer::makeString(const std::string &chars) {
  return NS::String::alloc()->init(chars.c_str(),
                                   NS::StringEncoding::UTF8StringEncoding);
}
simd::float4x4 Renderer::glm2simd(const glm::mat4 &mat) {
  const glm::vec4 &v0 = glm::row(mat, 0);
  const glm::vec4 &v1 = glm::row(mat, 1);
  const glm::vec4 &v2 = glm::row(mat, 2);
  const glm::vec4 &v3 = glm::row(mat, 3);
  return simd_matrix_from_rows((simd::float4){v0.x, v0.y, v0.z, v0.w},
                               (simd::float4){v1.x, v1.y, v1.z, v1.w},
                               (simd::float4){v2.x, v2.y, v2.z, v2.w},
                               (simd::float4){v3.x, v3.y, v3.z, v3.w});
}