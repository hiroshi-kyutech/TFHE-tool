/**
 * @file  alice_array.cpp
 * @brief TFHEの多次元配列の暗号化と保存のテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  uint32_t seed[] = {314, 1592, 657};
  TFHEConfig::setSeed(seed, 3);

  TFHEKeySet::create_new_keyset(110);

  TFHEKeySet::save_secret_key("secret.key");
  TFHEKeySet::save_cloud_key("cloud.key");

  std::vector<int> vec1{2, 4, 3, 5, 6, 1, 7, 8};

  TFHEArray<TFHEInt8> array1(vec1);

  array1.save("cloud_array.data", 1);

  printf(
      "ciphertext saved.\n"
      "array1{2, 4, 3, 5, 6, 1, 7, 8}\n");

  return 0;
}