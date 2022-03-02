/**
 * @file float32.hpp
 * @brief TFHEの単精度(32bits)の浮動小数点型のwrapperクラス.
 **/
#ifndef FLOAT32
#define FLOAT32
#include "../array/array.hpp"
#include "float.hpp"

/**
 * @brief TFHEの単精度(32bits)の浮動小数点型のwrapperクラス.
 **/
class TFHEFloat32 : public TFHEFloat<8, 23> {
 public:
  friend class TFHEArray<TFHEFloat32>;
  TFHEFloat32();
  TFHEFloat32(float number);
};

#endif