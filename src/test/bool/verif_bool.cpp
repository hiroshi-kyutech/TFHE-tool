/**
 * @file  verif_bool.cpp
 * @brief TFHEの真理値型の復号と読み込みのテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_secret_key("secret.key");

  TFHEBool bool3("cloud_bool.data", 3);

  printf("verify:%d\n", bool3.decrypt());

  return 0;
}