#pragma once
#include "Metal.hpp"

namespace NS::Private::Class {
_NS_PRIVATE_DEF_CLS(NSView);
} // namespace NS::Private::Class

namespace NS::Private::Selector {
_NS_PRIVATE_DEF_SEL(setLayer_, "setLayer:");
_NS_PRIVATE_DEF_SEL(setWantsLayer_, "setWantsLayer:");
} // namespace NS::Private::Selector

namespace CA {
class MetalLayer;
}
namespace NS {
class View : public Referencing<View> {
public:
  void setLayer(const CA::MetalLayer *layer);
  void setWantsLayer(bool yes);
};
} // namespace NS