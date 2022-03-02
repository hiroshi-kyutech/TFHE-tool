/**
 * @file  verif_array.cpp
 * @brief TFHEの多次元配列の復号と読み込みのテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_secret_key("secret.key");

  TFHEArray<TFHEInt8> array2("cloud_array.data", 2);

  printf("result: ");
  for (int i = 0; i < array2.shape[0]; i++) {
    printf("%d ", array2.at(i).decrypt());
  }
  printf("\n");

  return 0;
}