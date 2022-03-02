/**
 * @file  bit.hpp
 * @brief 単数のLweSample*をwrapするクラス.
 **/
#ifndef BIT
#define BIT
#include "../keyset/keyset.hpp"

/**
 * @brief 単数のLweSample*をwrapするクラス.
 **/
class TFHEBit : private TFHEKeySet {
 public:
  LweSample* bit = nullptr;

  TFHEBit(LweSample* elm);

  TFHEBit(const TFHEBit& elm);

  TFHEBit();

  ~TFHEBit();

  TFHEBit& operator=(const TFHEBit& elm);
};
#endif