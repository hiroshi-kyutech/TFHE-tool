/**
 * @file int32.cpp
 * @brief TFHEの32bitsの整数型のクラスの実装.
 **/
#include "int32.hpp"

TFHEInt32::TFHEInt32() : TFHEInteger<32>() {}
TFHEInt32::TFHEInt32(int32_t number) : TFHEInteger<32>(number) {}
TFHEInt32::TFHEInt32(const TFHEInt32& elm) : TFHEInteger<32>(elm) {}
TFHEInt32::TFHEInt32(const TFHEInteger<32>& elm) : TFHEInteger<32>(elm) {}
TFHEInt32::TFHEInt32(const TFHEIntegerCore& elm) : TFHEInteger<32>(elm) {}
