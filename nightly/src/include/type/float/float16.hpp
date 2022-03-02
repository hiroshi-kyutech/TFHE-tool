/**
 * @file float16.hpp
 * @brief TFHEの半精度(16bits)の浮動小数点型のwrapperクラス.
 **/
#ifndef FLOAT16
#define FLOAT16
#include "../array/array.hpp"
#include "float.hpp"

/**
 * @brief TFHEの半精度(16bits)の浮動小数点型のwrapperクラス.
 **/
class TFHEFloat16 : public TFHEFloat<5, 10> {
 public:
  friend class TFHEArray<TFHEFloat16>;
  TFHEFloat16();
  TFHEFloat16(float number);
};

#endif