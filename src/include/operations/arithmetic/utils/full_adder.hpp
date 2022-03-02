/**
 * @file full_adder.hpp
 * @brief full_adder(全加算器)の関数.
 **/
#ifndef FULL_ADDER
#define FULL_ADDER
#include "../../../common/tfhe_lib.hpp"
#include "./half_adder.hpp"

void full_adder(LweSample* sum, LweSample* carry_out, LweSample* a,
                LweSample* b, LweSample* x,
                const TFheGateBootstrappingCloudKeySet* bk);
#endif