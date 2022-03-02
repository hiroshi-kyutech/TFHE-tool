/**
 * @file  test_float_add.cpp
 * @brief TFHEの浮動小数点型の加算のテスト.
 **/
#include <cassert>

#include "tfhe_libex.hpp"

int main() {
  TFHEKeySet::create_new_keyset(110);
  // TFHEFloat<5, 10> float1(3.14);
  // TFHEFloat<5, 10> float1(1.23);
  // TFHEFloat<5, 10> float1(0.0001);
  // TFHEFloat<5, 10> float1(8888);
  TFHEFloat<5, 10> float1(24.1528);

  float f1 = float1.decrypt();
  printf("float1.decrypt %f\n", f1);
  // TFHEFloat<5, 10> float2(3.14);
  // TFHEFloat<5, 10> float2(987.6);
  // TFHEFloat<5, 10> float2(8888);
  // TFHEFloat<5, 10> float2(0.0001);
  TFHEFloat<5, 10> float2(698.777);

  float f2 = float2.decrypt();

  TFHEFloat<5, 10> float3 = float1 + float2;

  TFHEFloat<5, 10> float4(f1 + f2);
  return 0;
}