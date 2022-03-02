/**
 * @file int8.cpp
 * @brief TFHEの8bitsの整数型のクラスの実装.
 **/
#include "int8.hpp"

TFHEInt8::TFHEInt8() : TFHEInteger<8>() {}
TFHEInt8::TFHEInt8(int32_t number) : TFHEInteger<8>(number) {}
TFHEInt8::TFHEInt8(const TFHEInt8& elm) : TFHEInteger<8>(elm) {}
TFHEInt8::TFHEInt8(const TFHEInteger<8>& elm) : TFHEInteger<8>(elm) {}
TFHEInt8::TFHEInt8(const TFHEIntegerCore& elm) : TFHEInteger<8>(elm) {}
