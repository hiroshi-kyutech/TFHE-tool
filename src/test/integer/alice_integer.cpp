/**
 * @file  alice_integer.cpp
 * @brief TFHEの整数型の暗号化と保存のテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  uint32_t seed[] = {314, 1592, 657};
  TFHEConfig::setSeed(seed, 3);

  TFHEKeySet::create_new_keyset(110);

  TFHEKeySet::save_secret_key("secret.key");
  TFHEKeySet::save_cloud_key("cloud.key");

  // TFHEInteger<8> integer1(-3);
  // TFHEInteger<8> integer2(7);
  TFHEInteger<16> integer1(-3);
  TFHEInteger<16> integer2(7);

  integer1.save("cloud_integer.data", 1);
  integer2.save("cloud_integer.data", 2);

  printf(
      "ciphertext saved.\n"
      "integer1(-3),integer2(7)\n");

  return 0;
}