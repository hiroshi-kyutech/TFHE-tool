/**
 * @file  verif_integer.cpp
 * @brief TFHEの整数型の演算結果(整数型)の復号と読み込みのテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_secret_key("secret.key");

  TFHEInteger<8> integer("cloud_integer.data", 3);

  printf("verify:%d\n", integer.decrypt());

  return 0;
}