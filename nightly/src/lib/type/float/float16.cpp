/**
 * @file float16.cpp
 * @brief TFHEの半精度(16bits)の浮動小数点型のwrapperクラスの実装.
 **/
#include "float16.hpp"

TFHEFloat16::TFHEFloat16() : TFHEFloat<5, 10>() {}
TFHEFloat16::TFHEFloat16(float number) : TFHEFloat<5, 10>(number) {}
