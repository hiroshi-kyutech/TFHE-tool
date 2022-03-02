/**
 * @file int16.cpp
 * @brief TFHEの16bitsの整数型のクラスの実装.
 **/
#include "int16.hpp"

TFHEInt16::TFHEInt16() : TFHEInteger<16>() {}
TFHEInt16::TFHEInt16(int32_t number) : TFHEInteger<16>(number) {}
TFHEInt16::TFHEInt16(const TFHEInt16& elm) : TFHEInteger<16>(elm) {}
TFHEInt16::TFHEInt16(const TFHEInteger<16>& elm) : TFHEInteger<16>(elm) {}
TFHEInt16::TFHEInt16(const TFHEIntegerCore& elm) : TFHEInteger<16>(elm) {}
