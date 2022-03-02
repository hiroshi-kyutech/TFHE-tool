/**
 * @file  cloud_sign.cpp
 * @brief TFHEの整数型の符号の取得のテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");

  TFHEInteger<8> integer1("cloud_integer.data", 1);

  printf("integer1.sign()\n");
  start_timer();
  TFHEInteger<8> integer3 = integer1.sign();
  printf("calc time:%f[s]\n", lap());

  integer3.save("cloud_integer.data", 3);

  return 0;
}