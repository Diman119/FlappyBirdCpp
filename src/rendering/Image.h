#pragma once

#include "Surface.h"
#include <vector>
#include <cstring>

// taken from GIMP exports
#define IMAGE_RUN_LENGTH_DECODE(image_buf, rle_data, size, bpp) do \
{ unsigned int __bpp; unsigned char *__ip; const unsigned char *__il, *__rd; \
  __bpp = (bpp); __ip = (image_buf); __il = __ip + (size) * __bpp; \
  __rd = (rle_data); if (__bpp > 3) { /* RGBA */ \
    while (__ip < __il) { unsigned int __l = *(__rd++); \
      if (__l & 128) { __l = __l - 128; \
        do { memcpy (__ip, __rd, 4); __ip += 4; } while (--__l); __rd += 4; \
      } else { __l *= 4; memcpy (__ip, __rd, __l); \
               __ip += __l; __rd += __l; } } \
  } else if (__bpp == 3) { /* RGB */ \
    while (__ip < __il) { unsigned int __l = *(__rd++); \
      if (__l & 128) { __l = __l - 128; \
        do { memcpy (__ip, __rd, 3); __ip += 3; } while (--__l); __rd += 3; \
      } else { __l *= 3; memcpy (__ip, __rd, __l); \
               __ip += __l; __rd += __l; } } \
  } else { /* RGB16 */ \
    while (__ip < __il) { unsigned int __l = *(__rd++); \
      if (__l & 128) { __l = __l - 128; \
        do { memcpy (__ip, __rd, 2); __ip += 2; } while (--__l); __rd += 2; \
      } else { __l *= 2; memcpy (__ip, __rd, __l); \
               __ip += __l; __rd += __l; } } \
  } } while (0)

class Image : public Surface {
public:
    Image(int width, int height) : Surface(width, height), pixel_data_(width * height) {}

    template<typename T>
    explicit Image(T* gimp_image_struct) : Image(static_cast<int>(gimp_image_struct->width),
                                                 static_cast<int>(gimp_image_struct->height)) {
        IMAGE_RUN_LENGTH_DECODE(reinterpret_cast<unsigned char*>(pixel_data_.data()), gimp_image_struct->rle_pixel_data,
                                pixel_data_.size(), 4);
    }

    [[nodiscard]] Image Scaled(float factor) const;

protected:
    [[nodiscard]] uint32_t* PixelData() override {
        return pixel_data_.data();
    }

    [[nodiscard]] const uint32_t* PixelData() const override {
        return pixel_data_.data();
    }

private:
    std::vector<uint32_t> pixel_data_;
};
