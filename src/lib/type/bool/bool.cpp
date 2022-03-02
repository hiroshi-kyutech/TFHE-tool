/**
 * @file bool.cpp
 * @brief TFHEの真理値型のクラスの実装.
 **/
#include "bool.hpp"

TFHEBool::TFHEBool(const TFHEBool& elm) : TFHEBoolCore(elm) {}

TFHEBool::TFHEBool() : TFHEBoolCore() {}

TFHEBool::TFHEBool(bool value) : TFHEBoolCore(value) {}

TFHEBool::TFHEBool(const TFHEBoolCore& elm) : TFHEBoolCore(elm) {}

TFHEBool::TFHEBool(const char* path, int id) : TFHEBoolCore(path, id) {}

TFHEIntegerCore TFHEBool::mul(TFHEBool value1, TFHEIntegerCore value2) {
  TFHEIntegerCore result(value2.bits.nbelems);
  for (int i = 0; i < result.bits.nbelems; i++) {
    bootsAND(&result.bits[i], &value2.bits[i], value1.bit.bit, cloud_key());
  }
  return result;
}

TFHEIntegerCore TFHEBool::operator*(const TFHEIntegerCore& other) {
  TFHEIntegerCore result = mul(*this, other);
  return result;
}

TFHEBoolCore TFHEBool::operator+(const TFHEBoolCore& other) {
  TFHEBoolCore result = _or(other, (*this));
  return result;
}

TFHEBoolCore TFHEBool::operator*(const TFHEBoolCore& other) {
  TFHEBoolCore result = _and(other, (*this));
  return result;
}

void TFHEBool::save_option_forArray(FILE* fp) {
  int outbf[1];
  outbf[0] = static_cast<int>(TFHEType::TFHEBool);
  fwrite(outbf, sizeof(int), 1, fp);
}
int TFHEBool::array_size(int shape_size, int array_size) {
  return sizeof(int) * (5 + shape_size) + 2536 * array_size;
}
int TFHEBool::array_option_num() { return 1; }

void TFHEBool::save_raw(FILE* fp) { TFHEBoolCore::save_raw(fp); }
void TFHEBool::load_raw(FILE* fp) { TFHEBoolCore::load_raw(fp); }