/**
 * @file  cloud_equal_to.cpp
 * @brief TFHEの整数型の等号のテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");

  TFHEInteger<8> integer1("cloud_integer.data", 1);

  TFHEInteger<8> integer2("cloud_integer.data", 2);

  printf("integer1 == integer2\n");
  start_timer();
  TFHEBool bool3 = integer1 == integer2;
  printf("calc time:%f[s]\n", lap());

  bool3.save("cloud_bool.data", 3);

  return 0;
}