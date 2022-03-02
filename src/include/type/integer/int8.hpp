/**
 * @file int8.hpp
 * @brief TFHEの8bitsの整数型のクラス.
 **/
#ifndef INT8
#define INT8
#include "integer.hpp"

/**
 * @brief TFHEの8bitsの整数型のクラス.
 **/
class TFHEInt8 : public TFHEInteger<8> {
 public:
  friend class TFHEArray<TFHEInt8>;
  TFHEInt8();
  TFHEInt8(int number);
  TFHEInt8(const TFHEInt8& elm);
  TFHEInt8(const TFHEInteger<8>& elm);
  TFHEInt8(const TFHEIntegerCore& elm);
};

#endif