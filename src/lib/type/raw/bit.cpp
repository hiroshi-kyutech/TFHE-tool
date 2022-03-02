/**
 * @file  bit.cpp
 * @brief 単数のLweSample*をwrapするクラスの実装.
 **/
#include "bit.hpp"

TFHEBit::TFHEBit(LweSample* elm) : TFHEBit() {
  bootsCOPY(bit, elm, TFHEBit::cloud_key());
}

TFHEBit::TFHEBit(const TFHEBit& elm) : TFHEBit() {
  bootsCOPY(bit, elm.bit, TFHEBit::cloud_key());
}

TFHEBit::TFHEBit() {
  bit = new_gate_bootstrapping_ciphertext(TFHEBit::parameters());
}

TFHEBit::~TFHEBit() {
  if (bit != nullptr) {
    delete_gate_bootstrapping_ciphertext(bit);
  }
}

TFHEBit& TFHEBit::operator=(const TFHEBit& elm) {
  if (this != &elm) {
    bootsCOPY(bit, elm.bit, TFHEBit::cloud_key());
  }
  return *this;
}