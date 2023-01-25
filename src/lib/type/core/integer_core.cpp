/**
 * @file integer_core.cpp
 * @brief TFHEの整数型のcoreクラスの実装.
 **/
#include "integer_core.hpp"

TFHEIntegerCore::TFHEIntegerCore()
    : bits(),
      overflow_error_flag(TFHEBoolCore(false)),
      division_byZero_error_flag(TFHEBoolCore(false)) {}

TFHEIntegerCore::TFHEIntegerCore(const TFHEIntegerCore &elm, int nbelems)
    : overflow_error_flag(elm.overflow_error_flag),
      division_byZero_error_flag(elm.division_byZero_error_flag) {
  if (nbelems == elm.bits.nbelems) {
    bits = elm.bits;
  } else {
    bits = TFHEBits(nbelems);
    if (nbelems > elm.bits.nbelems) {
      for (int i = 0; i < elm.bits.nbelems; i++) {
        bootsCOPY(&bits[i], &elm.bits.bits[i], cloud_key());
      }
      for (int i = elm.bits.nbelems; i < nbelems; i++) {
        bootsCOPY(&bits[i], &elm.bits.bits[elm.bits.nbelems - 1], cloud_key());
      }
    } else {
      for (int i = 0; i < nbelems; i++) {
        bootsCOPY(&bits[i], &elm.bits.bits[i], cloud_key());
      }
    }
  }
}

TFHEIntegerCore::TFHEIntegerCore(int nbelems)
    : bits(TFHEBits(nbelems)),
      overflow_error_flag(TFHEBoolCore(false)),
      division_byZero_error_flag(TFHEBoolCore(false)) {
  if (nbelems < 2) {
    // Error
  }
}

TFHEIntegerCore::TFHEIntegerCore(int nbelems, int number)
    : TFHEIntegerCore(nbelems) {
  if (secret_key() != nullptr) {
    for (int i = 0; i < nbelems; i++) {
      bootsSymEncrypt(&(bits[i]), (number >> i) & 1, secret_key());
    }
  } else {
    if (cloud_key() != nullptr) {
      for (int i = 0; i < nbelems; i++) {
        bootsCONSTANT(&(bits[i]), (number >> i) & 1, cloud_key());
      }
    } else {
      // Error
    }
  }
}
int TFHEIntegerCore::decrypt() {
  check_decrypt_error();

  int int_answer = 0;
  int ai;
  ai = bootsSymDecrypt(&bits.bits[bits.nbelems - 1], secret_key());

  if (ai == 1) {
    int_answer = ~int_answer;

    for (int i = bits.nbelems - 2; i > -1; i--) {
      ai = bootsSymDecrypt(&bits.bits[i], secret_key());
      if (ai == 0) {
        int_answer &= ~(1 << i);
      }
    }
  } else {
    int_answer |= (ai << bits.nbelems - 1);
    for (int i = bits.nbelems - 2; i > -1; i--) {
      ai = bootsSymDecrypt(&bits.bits[i], secret_key());

      int_answer |= (ai << i);
    }
  }
  return int_answer;
}

TFHEIntegerCore TFHEIntegerCore::sign() {
  TFHEIntegerCore result(bits.nbelems);
  bootsCONSTANT(&result.bits[0], 1, cloud_key());
  for (int i = 1; i < bits.nbelems; i++) {
    bootsCOPY(&result.bits[i], &bits[bits.nbelems - 1], cloud_key());
  }
  return result;
}

TFHEIntegerCore TFHEIntegerCore::abs() {
  return mux(TFHEBoolCore(TFHEBit(&bits[bits.nbelems - 1])), -*this, *this);
}

void TFHEIntegerCore::check_division_byZero(TFHEIntegerCore value) {
  TFHEIntegerCore zero(2, 0);
  TFHEBoolCore error = (value == zero);

  division_byZero_error_flag = division_byZero_error_flag | error;
}

void TFHEIntegerCore::check_overflow_add(TFHEIntegerCore value1,
                                         TFHEIntegerCore value2) {
  TFHEBoolCore value1_msb(TFHEBit(&value1.bits[value1.bits.nbelems - 1]));
  TFHEBoolCore value2_msb(TFHEBit(&value2.bits[value2.bits.nbelems - 1]));
  TFHEBoolCore result_msb(TFHEBit(&this->bits[bits.nbelems - 1]));
  TFHEBoolCore error = ((value1_msb & value2_msb & !result_msb) |
                        (!value1_msb & !value2_msb & result_msb));
  overflow_error_flag = overflow_error_flag | error;
}

void TFHEIntegerCore::check_overflow_sub(TFHEIntegerCore value1,
                                         TFHEIntegerCore value2) {
  TFHEBoolCore value1_msb(TFHEBit(&value1.bits[value1.bits.nbelems - 1]));
  TFHEBoolCore value2_msb(TFHEBit(&value2.bits[value2.bits.nbelems - 1]));
  TFHEBoolCore result_msb(TFHEBit(&this->bits[bits.nbelems - 1]));
  TFHEBoolCore error = ((!value1_msb & value2_msb & result_msb) |
                        (value1_msb & !value2_msb & !result_msb));
  overflow_error_flag = overflow_error_flag | error;
}

void TFHEIntegerCore::check_overflow_mul() {
  TFHEBoolCore error(TFHEBit(&this->bits[bits.nbelems - 1]));

  overflow_error_flag = overflow_error_flag | error;
}

void TFHEIntegerCore::check_error(TFHEIntegerCore value) {
  overflow_error_flag = overflow_error_flag | value.overflow_error_flag;

  division_byZero_error_flag =
      division_byZero_error_flag | value.division_byZero_error_flag;
}

void TFHEIntegerCore::check_decrypt_error() {
  if (overflow_error_flag.decrypt()) {
    fprintf(stderr, "Error: division by zero\n");
    exit(1);
  }
  if (division_byZero_error_flag.decrypt()) {
    fprintf(stderr, "Error: division by zero\n");
    exit(1);
  }
}

TFHEIntegerCore TFHEIntegerCore::add(TFHEIntegerCore value1,
                                     TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEIntegerCore result(max_nbelems);
  TFHEBits carry_out(2);
  half_adder(&result.bits[0], &carry_out[0], &value1.bits[0], &value2.bits[0],
             cloud_key());
  int v1, v2;
  for (int i = 1; i < max_nbelems; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    full_adder(&result.bits[i], &carry_out[i % 2 == 0 ? 0 : 1],
               &value1.bits[v1], &value2.bits[v2],
               &carry_out[i % 2 == 0 ? 1 : 0], cloud_key());
  }

  return result;
}

TFHEIntegerCore TFHEIntegerCore::minus(TFHEIntegerCore value) {
  TFHEIntegerCore result = TFHEIntegerCore(value.bits.nbelems);
  for (int i = 0; i < value.bits.nbelems; i++) {
    bootsNOT(&result.bits[i], &value.bits[i], cloud_key());
  }

  TFHEIntegerCore one = TFHEIntegerCore(2, 1);
  return result + one;
}

TFHEIntegerCore TFHEIntegerCore::sub(TFHEIntegerCore value1,
                                     TFHEIntegerCore value2) {
  TFHEIntegerCore value2_rev = TFHEIntegerCore(value2.bits.nbelems);
  for (int i = 0; i < value2.bits.nbelems; i++) {
    bootsNOT(&value2_rev.bits[i], &value2.bits[i], cloud_key());
  }

  int max_nbelems = value1.bits.nbelems > value2_rev.bits.nbelems
                        ? value1.bits.nbelems
                        : value2_rev.bits.nbelems;
  TFHEIntegerCore result(max_nbelems);
  TFHEBits carry_out(2);
  half_adder_4sub(&result.bits[0], &carry_out[0], &value1.bits[0],
                  &value2_rev.bits[0], cloud_key());
  int v1, v2;
  for (int i = 1; i < max_nbelems; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2_rev.bits.nbelems ? i : value2_rev.bits.nbelems - 1;
    full_adder(&result.bits[i], &carry_out[i % 2 == 0 ? 0 : 1],
               &value1.bits[v1], &value2_rev.bits[v2],
               &carry_out[i % 2 == 0 ? 1 : 0], cloud_key());
  }

  return result;
}

TFHEIntegerCore TFHEIntegerCore::shift(TFHEIntegerCore value, int shift) {
  TFHEIntegerCore result(value.bits.nbelems);
  for (int i = 0; i < shift; i++) {
    bootsCONSTANT(&result.bits[i], 0, cloud_key());
  }
  for (int i = shift; i < value.bits.nbelems; i++) {
    bootsCOPY(&result.bits[i], &value.bits[i - shift], cloud_key());
  }
  if (TFHEConfig::safe_mode) {
    result.check_overflow_mul();
  }
  return result;
}

TFHEIntegerCore TFHEIntegerCore::mul(TFHEIntegerCore value1,
                                     TFHEBoolCore value2) {
  TFHEIntegerCore result(value1.bits.nbelems);
  for (int i = 0; i < result.bits.nbelems; i++) {
    bootsAND(&result.bits[i], &value1.bits[i], value2.bit.bit, cloud_key());
  }
  return result;
}

TFHEIntegerCore TFHEIntegerCore::mul(TFHEIntegerCore value1,
                                     TFHEIntegerCore value2) {
  TFHEIntegerCore max_nb_value =
      value1.bits.nbelems > value2.bits.nbelems ? value1 : value2;
  TFHEIntegerCore min_nb_value =
      value1.bits.nbelems > value2.bits.nbelems ? value2 : value1;

  TFHEIntegerCore tmps[min_nb_value.bits.nbelems];
  auto prcs1 = [&tmps, &max_nb_value, &min_nb_value](int index) {
    tmps[index] = shift(max_nb_value, index);

    for (int i = index; i < max_nb_value.bits.nbelems; i++) {
      bootsAND(&tmps[index].bits[i], &tmps[index].bits[i],
               &min_nb_value.bits[index], cloud_key());
    }
  };
  {
    std::vector<std::thread> threads;
    for (int j = 0; j < min_nb_value.bits.nbelems; j++) {
      threads.emplace_back(std::thread(prcs1, j));
    }
    for (int j = 0; j < min_nb_value.bits.nbelems; j++) {
      threads[j].join();
    }
  }
  auto prcs2 = [&tmps, &min_nb_value](int cur, int pos) {
    int augend = pos << cur + 1;
    int addend = (pos << cur + 1) | (1 << cur);
    if (min_nb_value.bits.nbelems <= addend) return;

    // tmps[augend] = tmps[augend] + tmps[addend];
    TFHEBits carry_out(2);
    TFHEBit sum;
    half_adder(sum.bit, &carry_out[addend % 2], &tmps[augend].bits[addend],
               &tmps[addend].bits[addend], cloud_key());
    bootsCOPY(&tmps[augend].bits[addend], sum.bit, cloud_key());
    for (int i = addend + 1; i < tmps[augend].bits.nbelems; i++) {
        full_adder(sum.bit, &carry_out[i % 2 == 0 ? 0 : 1],
                   &tmps[augend].bits[i], &tmps[addend].bits[i],
                   &carry_out[i % 2 == 0 ? 1 : 0], cloud_key());
        bootsCOPY(&tmps[augend].bits[i], sum.bit, cloud_key());
    }
  };

  int last = min_nb_value.bits.nbelems + (min_nb_value.bits.nbelems & 1) >> 1;
  for (int i = 0; 1 << i <= min_nb_value.bits.nbelems; i++) {
    std::vector<std::thread> threads;
    for (int j = 0; j < last; j++) {
      threads.emplace_back(std::thread(prcs2, i, j));
    }
    for (int j = 0; j < last; j++) {
      threads[j].join();
    }
    last = (last + (last & 1)) >> 1;
  }

  return tmps[0];
}

TFHEIntegerCore TFHEIntegerCore::div(TFHEIntegerCore value1,
                                     TFHEIntegerCore value2) {
  TFHEIntegerCore value1_abs = value1.abs();
  TFHEIntegerCore value2_abs = value2.abs();

  TFHEIntegerCore result(value1_abs.bits.nbelems);
  TFHEIntegerCore tmp(value1_abs.bits.nbelems, 0);
  TFHEIntegerCore tmp1(value1_abs.bits.nbelems);
  TFHEIntegerCore tmp2(value1_abs.bits.nbelems);
  TFHEBoolCore rslt_bit;
  bootsCOPY(&tmp.bits[0], &value1_abs.bits.bits[value1_abs.bits.nbelems - 1],
            cloud_key());
  rslt_bit = value2_abs <= tmp;

  bootsCOPY(&result.bits[value1_abs.bits.nbelems - 1], rslt_bit.bit.bit,
            cloud_key());
  for (int i = 1; i < value1_abs.bits.nbelems; i++) {
    tmp1 = tmp - value2_abs;

    tmp1 = shift(tmp1, 1);
    tmp2 = shift(tmp, 1);

    tmp = mux(rslt_bit, tmp1, tmp2);

    bootsCOPY(&tmp.bits[0],
              &value1_abs.bits.bits[value1_abs.bits.nbelems - 1 - i],
              cloud_key());

    rslt_bit = value2_abs <= tmp;
    bootsCOPY(&result.bits[value1_abs.bits.nbelems - 1 - i], rslt_bit.bit.bit,
              cloud_key());
  }

  return mux(TFHEBoolCore(TFHEBit(&value1.bits[value1.bits.nbelems - 1])) ^
                 TFHEBoolCore(TFHEBit(&value2.bits[value2.bits.nbelems - 1])),
             -result, result);
}

TFHEIntegerCore TFHEIntegerCore::mod(TFHEIntegerCore value1,
                                     TFHEIntegerCore value2) {
  TFHEIntegerCore value1_abs = value1.abs();
  TFHEIntegerCore value2_abs = value2.abs();

  TFHEIntegerCore result(value1_abs.bits.nbelems);
  TFHEIntegerCore tmp(value1_abs.bits.nbelems, 0);
  TFHEIntegerCore tmp1(value1_abs.bits.nbelems);
  TFHEIntegerCore tmp2(value1_abs.bits.nbelems);
  TFHEBoolCore rslt_bit;
  bootsCOPY(&tmp.bits[0], &value1_abs.bits.bits[value1_abs.bits.nbelems - 1],
            cloud_key());
  for (int i = 1; i < value1_abs.bits.nbelems; i++) {
    rslt_bit = value2_abs <= tmp;
    tmp1 = tmp - value2_abs;
    tmp1 = shift(tmp1, 1);
    tmp2 = shift(tmp, 1);
    tmp = mux(rslt_bit, tmp1, tmp2);
    bootsCOPY(&tmp.bits[0],
              &value1_abs.bits.bits[value1_abs.bits.nbelems - 1 - i],
              cloud_key());
  }
  rslt_bit = value2_abs <= tmp;
  tmp1 = tmp - value2_abs;
  tmp = mux(rslt_bit, tmp1, tmp);
  result = tmp;
  return mux(TFHEBoolCore(TFHEBit(&value1.bits[value1.bits.nbelems - 1])),
             -result, result);
}

TFHEBoolCore TFHEIntegerCore::lt(TFHEIntegerCore value1,
                                 TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 0, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems - 1; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsMUX(result.bit.bit, tmp, result.bit.bit, &value2.bits[v2],
             cloud_key());
  }

  v1 = value1.bits.nbelems - 1;
  v2 = value2.bits.nbelems - 1;
  bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
  bootsMUX(result.bit.bit, tmp, result.bit.bit, &value1.bits[v1], cloud_key());

  return result;
}

TFHEBoolCore TFHEIntegerCore::ltoet(TFHEIntegerCore value1,
                                    TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 1, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems - 1; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsMUX(result.bit.bit, tmp, result.bit.bit, &value2.bits[v2],
             cloud_key());
  }

  v1 = value1.bits.nbelems - 1;
  v2 = value2.bits.nbelems - 1;
  bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
  bootsMUX(result.bit.bit, tmp, result.bit.bit, &value1.bits[v1], cloud_key());

  return result;
}

TFHEBoolCore TFHEIntegerCore::gt(TFHEIntegerCore value1,
                                 TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 0, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems - 1; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsMUX(result.bit.bit, tmp, result.bit.bit, &value1.bits[v1],
             cloud_key());
  }

  v1 = value1.bits.nbelems - 1;
  v2 = value2.bits.nbelems - 1;
  bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
  bootsMUX(result.bit.bit, tmp, result.bit.bit, &value2.bits[v2], cloud_key());

  return result;
}

TFHEBoolCore TFHEIntegerCore::gtoet(TFHEIntegerCore value1,
                                    TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 1, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems - 1; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsMUX(result.bit.bit, tmp, result.bit.bit, &value1.bits[v1],
             cloud_key());
  }

  v1 = value1.bits.nbelems - 1;
  v2 = value2.bits.nbelems - 1;
  bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
  bootsMUX(result.bit.bit, tmp, result.bit.bit, &value2.bits[v2], cloud_key());

  return result;
}

TFHEBoolCore TFHEIntegerCore::et(TFHEIntegerCore value1,
                                 TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 1, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXNOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsAND(result.bit.bit, result.bit.bit, tmp, cloud_key());
  }

  return result;
}

TFHEBoolCore TFHEIntegerCore::net(TFHEIntegerCore value1,
                                  TFHEIntegerCore value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEBoolCore result = TFHEBoolCore();
  LweSample *tmp = new_gate_bootstrapping_ciphertext(parameters());
  bootsCONSTANT(result.bit.bit, 0, cloud_key());
  int v1, v2;
  for (int i = 0; i < max_nbelems; i++) {
    v1 = i < value1.bits.nbelems ? i : value1.bits.nbelems - 1;
    v2 = i < value2.bits.nbelems ? i : value2.bits.nbelems - 1;
    bootsXOR(tmp, &value1.bits[v1], &value2.bits[v2], cloud_key());
    bootsOR(result.bit.bit, result.bit.bit, tmp, cloud_key());
  }

  return result;
}

TFHEIntegerCore &TFHEIntegerCore::operator=(const TFHEIntegerCore &elm) {
  bits = elm.bits;
  return *this;
}

TFHEIntegerCore TFHEIntegerCore::operator+(const TFHEIntegerCore &other) {
  TFHEIntegerCore result = add(*this, other);

  if (TFHEConfig::safe_mode) {
    result.check_overflow_add(*this, other);
    result.check_error(*this);
    result.check_error(other);
  }

  return result;
}

TFHEIntegerCore TFHEIntegerCore::operator-() {
  TFHEIntegerCore result = minus(*this);
  if (TFHEConfig::safe_mode) {
    result.check_error(*this);
  }
  return result;
}

TFHEIntegerCore TFHEIntegerCore::operator-(const TFHEIntegerCore &other) {
  TFHEIntegerCore result = sub(*this, other);
  if (TFHEConfig::safe_mode) {
    result.check_overflow_sub(*this, other);
    result.check_error(*this);
    result.check_error(other);
  }
  return result;
}
TFHEIntegerCore TFHEIntegerCore::operator*(const TFHEBoolCore &other) {
  TFHEIntegerCore result = mul(*this, other);
  return result;
}
TFHEIntegerCore TFHEIntegerCore::operator*(const TFHEIntegerCore &other) {
  TFHEIntegerCore result = mul(*this, other);
  if (TFHEConfig::safe_mode) {
    result.check_error(*this);
    result.check_error(other);
  }
  return result;
}
TFHEIntegerCore TFHEIntegerCore::operator/(const TFHEIntegerCore &other) {
  TFHEIntegerCore result = div(*this, other);
  if (TFHEConfig::safe_mode) {
    result.check_division_byZero(other);
    result.check_error(*this);
    result.check_error(other);
  }
  return result;
}
TFHEIntegerCore TFHEIntegerCore::operator%(const TFHEIntegerCore &other) {
  TFHEIntegerCore result = mod(*this, other);
  if (TFHEConfig::safe_mode) {
    result.check_division_byZero(other);
    result.check_error(*this);
    result.check_error(other);
  }
  return result;
}
TFHEBoolCore TFHEIntegerCore::operator<(const TFHEIntegerCore &other) {
  return lt(*this, other);
}
TFHEBoolCore TFHEIntegerCore::operator<=(const TFHEIntegerCore &other) {
  return ltoet(*this, other);
}
TFHEBoolCore TFHEIntegerCore::operator>(const TFHEIntegerCore &other) {
  return gt(*this, other);
}
TFHEBoolCore TFHEIntegerCore::operator>=(const TFHEIntegerCore &other) {
  return gtoet(*this, other);
}
TFHEBoolCore TFHEIntegerCore::operator==(const TFHEIntegerCore &other) {
  return et(*this, other);
}
TFHEBoolCore TFHEIntegerCore::operator!=(const TFHEIntegerCore &other) {
  return net(*this, other);
}

TFHEBoolCore TFHEIntegerCore::operator<(const int &other) {
  int num = other > 0 ? other : -other;
  if (num == 0 || num == 1) {
    return lt(*this, TFHEIntegerCore(2, other));
  }
  return lt(*this, TFHEIntegerCore(ceil(log2(num)) + 1, other));
}

TFHEBoolCore TFHEIntegerCore::operator>(const int &other) {
  int num = other > 0 ? other : -other;
  if (num == 0 || num == 1) {
    return gt(*this, TFHEIntegerCore(2, other));
  }
  return gt(*this, TFHEIntegerCore(ceil(log2(num)) + 1, other));
}

TFHEBoolCore TFHEIntegerCore::operator==(const int &other) {
  int num = other > 0 ? other : -other;
  if (num == 0 || num == 1) {
    return et(*this, TFHEIntegerCore(2, other));
  }
  return et(*this, TFHEIntegerCore(ceil(log2(num)) + 1, other));
}

void TFHEIntegerCore::load_raw(FILE *fp) {
  for (int i = 0; i < bits.nbelems; i++) {
    import_gate_bootstrapping_ciphertext_fromFile(fp, &bits[i], parameters());
  }
}

void TFHEIntegerCore::save(const char *path, int id) {
  // 同じIDのものがあれば上書きする
  long pos[3];

  find_file_pointer(path, id, pos);

  if (pos[0] != -1) {
    remove_from_file(path, pos);
  }

  // TFHEInteger is 1
  // size sizeof(int)*4+2536*Nbelems
  int size = sizeof(int) * 4 + 2536 * bits.nbelems;
  int outbf[4] = {id, static_cast<int>(TFHEType::TFHEInteger), size,
                  bits.nbelems};

  FILE *fp;
  if ((fp = fopen(path, "ab+")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0L, SEEK_END);

  fwrite(outbf, sizeof(int), 4, fp);

  save_raw(fp);

  fclose(fp);
}

TFHEIntegerCore::TFHEIntegerCore(int nbelems, const char *path, int id)
    : TFHEIntegerCore(nbelems) {
  long pos[3];

  find_file_pointer(path, id, pos);
  if (pos[0] == -1) {
    // 見つからない
  }

  if (pos[1] != static_cast<int>(TFHEType::TFHEInteger)) {
    // Error 該当するIDは要求する型ではない
  }
  FILE *fp;
  if ((fp = fopen(path, "rb")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }
  fseek(fp, pos[0] + 16L, SEEK_SET);

  load_raw(fp);

  fclose(fp);
}

void TFHEIntegerCore::save_raw(FILE *fp) {
  for (int j = 0; j < bits.nbelems; j++) {
    export_gate_bootstrapping_ciphertext_toFile(fp, &bits[j], parameters());
  }
}