#include "NSView.hpp"

namespace NS {
void View::setLayer(const CA::MetalLayer *layer) {
  Object::sendMessage<void>(this, _NS_PRIVATE_SEL(setLayer_), layer);
}
void View::setWantsLayer(bool yes) {
  Object::sendMessage<void>(this, _NS_PRIVATE_SEL(setWantsLayer_), yes);
}
} // namespace NS