#pragma once
#include "Metal.hpp"

namespace CA::Private::Class {
_CA_PRIVATE_DEF_CLS(CAMetalLayer);
} // namespace CA::Private::Class

namespace CA::Private::Selector {
_CA_PRIVATE_DEF_SEL(setDevice_, "setDevice:");
_CA_PRIVATE_DEF_SEL(setOpaque_, "setOpaque:");
_CA_PRIVATE_DEF_SEL(nextDrawable_, "nextDrawable");
} // namespace CA::Private::Selector

namespace CA {
class MetalLayer : public NS::Referencing<MetalLayer> {
public:
  static MetalLayer *alloc();
  MetalLayer *init();
  void setDevice(const MTL::Device *device);
  void setOpaque(bool yes);
  CA::MetalDrawable *nextDrawable();
};
} // namespace CA