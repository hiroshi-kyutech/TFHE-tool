/**
 * @file  test_error_check.cpp
 * @brief TFHEの整数型の0除算とオーバーフローのエラーチェックのテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::create_new_keyset(110);
  TFHEInteger<4> integer1(7);
  TFHEInteger<4> integer2(7);
  TFHEInteger<4> integer3 = integer2 * integer1;
  // integer3.decrypt(); //Error
  integer2 = TFHEInteger<4>(0);
  integer3 = integer1 / integer2;
  // integer3.decrypt(); //Error
  return 0;
}