#include "ImageIO.hpp"
#include <FreeImage.h>

// ImageHandle
ImageHandle::ImageHandle(FIBITMAP *content) : m_content(content) {}
ImageHandle::~ImageHandle() { FreeImage_Unload(m_content); }
const uint8_t *ImageHandle::getData() const {
  return FreeImage_GetBits(m_content);
}
int ImageHandle::getWidth() const { return FreeImage_GetWidth(m_content); }
int ImageHandle::getHeight() const { return FreeImage_GetHeight(m_content); }
int ImageHandle::getBPP() const { return FreeImage_GetBPP(m_content); }
int ImageHandle::getColorType() const {
  return FreeImage_GetColorType(m_content);
}

// ImageIO
const int ImageIO::COLOR_TYPE_A = FIC_RGBALPHA;
void ImageIO::init() { FreeImage_Initialise(); }

std::shared_ptr<ImageHandle> ImageIO::load(const std::string &file) {
  return std::make_shared<ImageHandle>(FreeImage_Load(FIF_PNG, file.c_str()));
}

void ImageIO::destroy() { FreeImage_DeInitialise(); }