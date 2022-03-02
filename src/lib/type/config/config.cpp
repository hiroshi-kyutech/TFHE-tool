/**
 * @file  config.cpp
 * @brief 設定するクラスの実装.
 **/
#include "config.hpp"

bool TFHEConfig::safe_mode = true;

void TFHEConfig::setSeed(uint32_t* values, int size) {
  tfhe_random_generator_setSeed(values, size);
}