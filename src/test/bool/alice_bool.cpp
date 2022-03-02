/**
 * @file  alice_bool.cpp
 * @brief TFHEの真理値型の暗号化と保存のテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  uint32_t seed[] = {314, 1592, 657};
  TFHEConfig::setSeed(seed, 3);

  TFHEKeySet::create_new_keyset(110);

  TFHEKeySet::save_secret_key("secret.key");
  TFHEKeySet::save_cloud_key("cloud.key");

  TFHEBool bool1(true);
  TFHEBool bool2(false);

  bool1.save("cloud_bool.data", 1);
  bool2.save("cloud_bool.data", 2);

  printf(
      "ciphertext saved.\n"
      "bool1(true),bool2(false)\n");

  return 0;
}