#include "CAMetalLayer.hpp"

namespace CA {
MetalLayer *MetalLayer::alloc() {
  return NS::Object::alloc<MetalLayer>(_CA_PRIVATE_CLS(CAMetalLayer));
}

MetalLayer *MetalLayer::init() { return NS::Object::init<MetalLayer>(); }
void MetalLayer::setDevice(const MTL::Device *device) {
  Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setDevice_), device);
}
void MetalLayer::setOpaque(bool yes) {
  Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setOpaque_), yes);
}
CA::MetalDrawable *MetalLayer::nextDrawable() {
  return Object::sendMessage<CA::MetalDrawable *>(
      this, _CA_PRIVATE_SEL(nextDrawable_));
}
} // namespace CA