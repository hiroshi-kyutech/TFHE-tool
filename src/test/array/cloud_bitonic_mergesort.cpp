/**
 * @file  cloud_bitonic_mergesort.cpp
 * @brief TFHEのbitonic_mergesortのテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

void bitonic_compare(TFHEBool up, TFHEArray<TFHEInt8>& x, int l, int r) {
  int length = r - l;

  int dist = length / 2;
  auto prcs = [&up, &x](int a, int b) {
    TFHEBool result = (x.at(a) > x.at(b)) == up;
    TFHEInt8 tmp = x.at(a);
    x.at(a) = mux(result, x.at(b), x.at(a));
    x.at(b) = mux(result, tmp, x.at(b));
  };
  std ::vector<std::thread> threads;
  for (int i = l; i < dist + l; i++) {
    threads.emplace_back(std::thread(prcs, i, i + dist));
  }
  for (auto& elm : threads) {
    elm.join();
  }
}

void bitonic_merge(TFHEBool up, TFHEArray<TFHEInt8>& x, int l, int r) {
  int length = r - l;
  if (length != 1) {
    bitonic_compare(up, x, l, r);
    bitonic_merge(up, x, l, l + length / 2);
    bitonic_merge(up, x, l + length / 2, r);
  }
}

void bitonic_sort(TFHEBool up, TFHEArray<TFHEInt8>& x, int l, int r) {
  int length = r - l;

  if (length > 1) {
    bitonic_sort(true, x, l, l + length / 2);
    bitonic_sort(false, x, l + length / 2, r);
    bitonic_merge(up, x, l, r);
  }
}

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");
  TFHEArray<TFHEInt8> array1("cloud_array.data", 1);

  start_timer();
  bitonic_sort(TFHEBool(true), std::ref(array1), 0, array1.shape[0]);
  printf("calc time:%f[s]\n", lap());

  array1.save("cloud_array.data", 2);

  return 0;
}