/**
 * @file  bits.hpp
 * @brief 複数のLweSample*をwrapするクラス.
 **/
#ifndef BITS
#define BITS
#include "../keyset/keyset.hpp"

/**
 * @brief 複数のLweSample*をwrapするクラス.
 **/
class TFHEBits : private TFHEKeySet {
 public:
  int nbelems;
  LweSample* bits = nullptr;

  TFHEBits();
  TFHEBits(const TFHEBits& elm);

  TFHEBits(int nbelems);

  ~TFHEBits();

  LweSample& operator[](int n);
  TFHEBits& operator=(const TFHEBits& elm);
};
#endif