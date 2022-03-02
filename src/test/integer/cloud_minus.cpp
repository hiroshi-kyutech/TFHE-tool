/**
 * @file  cloud_minus.cpp
 * @brief TFHEの整数型の符号反転のテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");

  TFHEInteger<8> integer1("cloud_integer.data", 1);

  printf("-integer1\n");
  start_timer();
  TFHEInteger<8> integer3 = -integer1;
  printf("calc time:%f[s]\n", lap());

  integer3.save("cloud_integer.data", 3);

  return 0;
}