#pragma once

#include <zxing/LuminanceSource.h>
#include "ofPixels.h"

namespace zxing {

// modeled off the Image Magick demo
class ofPixelsBitmapSource : public LuminanceSource {
private:
  ofPixels& image_;
  int width;
  int height;
	const unsigned char* pixel_cache;

public:
  ofPixelsBitmapSource(ofPixels& image);

  ~ofPixelsBitmapSource();

  int getWidth() const;
  int getHeight() const;
  unsigned char* getRow(int y, unsigned char* row);
  unsigned char* getMatrix();
  bool isRotateSupported() const;
  Ref<LuminanceSource> rotateCounterClockwise();
};

}