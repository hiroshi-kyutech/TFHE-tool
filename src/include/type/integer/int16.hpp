/**
 * @file int16.hpp
 * @brief TFHEの16bitsの整数型のクラス.
 **/
#ifndef INT16
#define INT16
#include "integer.hpp"

/**
 * @brief TFHEの16bitsの整数型のクラス.
 **/
class TFHEInt16 : public TFHEInteger<16> {
 public:
  friend class TFHEArray<TFHEInt16>;
  TFHEInt16();
  TFHEInt16(int number);
  TFHEInt16(const TFHEInt16& elm);
  TFHEInt16(const TFHEInteger<16>& elm);
  TFHEInt16(const TFHEIntegerCore& elm);
};
#endif