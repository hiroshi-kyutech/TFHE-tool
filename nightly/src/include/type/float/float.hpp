/**
 * @file float.hpp
 * @brief TFHEの浮動小数点型のwrapperクラス.
 **/
#ifndef FLOAT
#define FLOAT

#include "../core/float_core.hpp"

/**
 * @brief TFHEの浮動小数点型のwrapperクラス.
 **/
template <int Exponent, int Fraction>
class TFHEFloat : public TFHEFloatCore {
 public:
  TFHEFloat(const TFHEFloat &elm) : TFHEFloatCore(elm) {}
  TFHEFloat(TFHEFloatCore elm) : TFHEFloatCore(elm) {}
  TFHEFloat() : TFHEFloatCore(Exponent, Fraction) {}
  TFHEFloat(float number) : TFHEFloatCore(Exponent, Fraction, number) {}
};
#endif