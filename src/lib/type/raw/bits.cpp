/**
 * @file  bits.cpp
 * @brief 複数のLweSample*をwrapするクラスの実装.
 **/
#include "bits.hpp"

TFHEBits::TFHEBits() {}

TFHEBits::TFHEBits(const TFHEBits& elm) : TFHEBits(elm.nbelems) {
  for (int i = 0; i < nbelems; i++) {
    bootsCOPY(&bits[i], &elm.bits[i], cloud_key());
  }
}

TFHEBits::TFHEBits(int32_t nbelems) : nbelems(nbelems) {
  bits = new_gate_bootstrapping_ciphertext_array(nbelems, parameters());
}

TFHEBits::~TFHEBits() {
  if (bits != nullptr) {
    delete_gate_bootstrapping_ciphertext_array(nbelems, bits);
  }
}

LweSample& TFHEBits::operator[](int n) {
  if (0 > n && n >= nbelems) {
    // ERROR:Index is out of range
  }
  return bits[n];
}

TFHEBits& TFHEBits::operator=(const TFHEBits& elm) {
  if (this != &elm) {
    if (nbelems == elm.nbelems) {
      if (bits == nullptr) {
        bits = new_gate_bootstrapping_ciphertext_array(nbelems, parameters());
      }
      for (int i = 0; i < nbelems; i++) {
        bootsCOPY(&bits[i], &elm.bits[i], cloud_key());
      }
    } else {
      if (bits != nullptr) {
        delete_gate_bootstrapping_ciphertext_array(nbelems, bits);
      }
      nbelems = elm.nbelems;
      bits = new_gate_bootstrapping_ciphertext_array(nbelems, parameters());
      for (int i = 0; i < nbelems; i++) {
        bootsCOPY(&bits[i], &elm.bits[i], cloud_key());
      }
    }
  }
  return *this;
}
