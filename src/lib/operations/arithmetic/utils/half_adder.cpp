/**
 * @file half_adder.cpp
 * @brief half_adder(半加算器)の関数の実装.
 **/
#include "half_adder.hpp"

void half_adder(LweSample* sum, LweSample* carry_out, LweSample* a,
                LweSample* b, const TFheGateBootstrappingCloudKeySet* bk) {
  bootsXOR(sum, a, b, bk);
  bootsAND(carry_out, a, b, bk);
}

void half_adder_4sub(LweSample* sum, LweSample* carry_out, LweSample* a,
                     LweSample* b, const TFheGateBootstrappingCloudKeySet* bk) {
  bootsXNOR(sum, a, b, bk);
  bootsOR(carry_out, a, b, bk);
}