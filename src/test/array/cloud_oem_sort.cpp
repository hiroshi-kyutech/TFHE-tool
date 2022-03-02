/**
 * @file  cloud_oem_sort.cpp
 * @brief TFHEのoem_sortのテスト.
 **/
#include <cassert>

#include "../utils.hpp"
#include "tfhe_libex.hpp"

void oddeven_merge(TFHEArray<TFHEInt8> &x, int lo, int hi, int r) {
  auto compare_and_swap = [&x](int a, int b) {
    TFHEBool result = x.at(a) > x.at(b);
    TFHEInt8 tmp = x.at(a);
    x.at(a) = mux(result, x.at(b), x.at(a));
    x.at(b) = mux(result, tmp, x.at(b));
  };
  int step = r * 2;
  if (step < hi - lo) {
    oddeven_merge(x, lo, hi, step);
    oddeven_merge(x, lo + r, hi, step);
    std ::vector<std::thread> threads;
    for (int i = lo + r; i < hi - r; i += step) {
      threads.emplace_back(std::thread(compare_and_swap, i, i + r));
    }
    for (auto &elm : threads) {
      elm.join();
    }
  } else {
    compare_and_swap(lo, lo + r);
  }
}

void oddeven_merge_sort_range(TFHEArray<TFHEInt8> &x, int lo, int hi) {
  if ((hi - lo) >= 1) {
    int mid = lo + (hi - lo) / 2;
    oddeven_merge_sort_range(x, lo, mid);
    oddeven_merge_sort_range(x, mid + 1, hi);
    oddeven_merge(x, lo, hi, 1);
  }
}

void oddeven_merge_sort(TFHEArray<TFHEInt8> &x) {
  oddeven_merge_sort_range(x, 0, x.shape[0] - 1);
}

int main() {
  TFHEKeySet::load_cloud_key("cloud.key");
  TFHEArray<TFHEInt8> array1("cloud_array.data", 1);

  start_timer();
  oddeven_merge_sort(std::ref(array1));
  printf("calc time:%f[s]\n", lap());

  array1.save("cloud_array.data", 2);

  return 0;
}