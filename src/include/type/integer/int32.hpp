/**
 * @file int32.hpp
 * @brief TFHEの32bitsの整数型のクラス.
 **/
#ifndef INT32
#define INT32
#include "integer.hpp"

/**
 * @brief TFHEの32bitsの整数型のクラス.
 **/
class TFHEInt32 : public TFHEInteger<32> {
 public:
  friend class TFHEArray<TFHEInt32>;
  TFHEInt32();
  TFHEInt32(int number);
  TFHEInt32(const TFHEInt32& elm);
  TFHEInt32(const TFHEInteger<32>& elm);
  TFHEInt32(const TFHEIntegerCore& elm);
};

#endif