/**
 * @file  cloud_mux_bool.cpp
 * @brief TFHEの真理値型の条件演算子のテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");

  TFHEBool bool1("cloud_bool.data", 1);
  TFHEBool bool2("cloud_bool.data", 2);

  TFHEBool bool_c = bool1 == bool2;
  printf("bool1 == bool2 ? bool1 : bool2\n");
  start_timer();
  TFHEBool bool3 = mux(bool_c, bool1, bool2);
  printf("calc time:%f[s]\n", lap());

  bool3.save("cloud_bool.data", 3);

  return 0;
}