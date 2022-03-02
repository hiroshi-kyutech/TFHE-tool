/**
 * @file  time.cpp
 * @brief テスト用の時間計測関数の実装.
 **/
#include <time.h>

#include "utils.hpp"

struct timespec start_time, end_time;

void start_timer() { clock_gettime(CLOCK_REALTIME, &start_time); }

double lap() {
  unsigned int sec;
  int nsec;
  double d_sec;
  clock_gettime(CLOCK_REALTIME, &end_time);
  sec = end_time.tv_sec - start_time.tv_sec;
  nsec = end_time.tv_nsec - start_time.tv_nsec;

  return (double)sec + (double)nsec / (1000 * 1000 * 1000);
}