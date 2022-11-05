#include "NSWindow.hpp"
#include "NSView.hpp"

namespace NS {
Window *Window::bridgingCast(const void *ptr) {
  return Object::bridgingCast<Window *>(ptr);
}
View *Window::getContentView() const {
  return Object::sendMessage<View *>(this, _NS_PRIVATE_SEL(contentView_));
}
} // namespace NS