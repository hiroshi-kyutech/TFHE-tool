/**
 * @file full_adder.cpp
 * @brief full_adder(全加算器)の関数の実装.
 **/
#include "full_adder.hpp"

void full_adder(LweSample* sum, LweSample* carry_out, LweSample* a,
                LweSample* b, LweSample* x,
                const TFheGateBootstrappingCloudKeySet* bk) {
  LweSample* tmp = new_gate_bootstrapping_ciphertext_array(3, bk->params);
  half_adder(&tmp[0], &tmp[1], a, b, bk);
  half_adder(sum, &tmp[2], &tmp[0], x, bk);
  bootsOR(carry_out, &tmp[1], &tmp[2], bk);
  delete_gate_bootstrapping_ciphertext_array(3, tmp);
}