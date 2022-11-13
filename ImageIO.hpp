#pragma once
#include <memory>
#include <string>

struct FIBITMAP;
class ImageHandle {
public:
  explicit ImageHandle(FIBITMAP *content);
  ~ImageHandle();

  const uint8_t *getData() const;
  int getWidth() const;
  int getHeight() const;
  int getBPP() const;
  int getColorType() const;

private:
  FIBITMAP *m_content;
};

class ImageIO {
public:
  static const int COLOR_TYPE_A;
  static void init();
  static std::shared_ptr<ImageHandle> load(const std::string &file);
  static void destroy();

private:
  ImageIO() = delete;
  ~ImageIO() = delete;
};