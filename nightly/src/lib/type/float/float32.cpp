/**
 * @file float32.cpp
 * @brief TFHEの単精度(32bits)の浮動小数点型のwrapperクラスの実装.
 **/
#include "float32.hpp"

TFHEFloat32::TFHEFloat32() : TFHEFloat<8, 23>() {}
TFHEFloat32::TFHEFloat32(float number) : TFHEFloat<8, 23>(number) {}
