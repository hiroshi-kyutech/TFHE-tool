/**
 * @file half_adder.hpp
 * @brief half_adder(半加算器)の関数.
 **/
#ifndef HALF_ADDER
#define HALF_ADDER
#include "../../../common/tfhe_lib.hpp"

void half_adder(LweSample* sum, LweSample* carry_out, LweSample* a,
                LweSample* b, const TFheGateBootstrappingCloudKeySet* bk);

void half_adder_4sub(LweSample* sum, LweSample* carry_out, LweSample* a,
                     LweSample* b, const TFheGateBootstrappingCloudKeySet* bk);

#endif