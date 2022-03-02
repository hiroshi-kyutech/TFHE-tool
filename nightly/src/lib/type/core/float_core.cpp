/**
 * @file float_core.cpp
 * @brief TFHEの浮動小数点型のクラスの実装.
 **/
#include "float_core.hpp"

TFHEFloatCore::TFHEExponent::TFHEExponent() {}

TFHEFloatCore::TFHEExponent::TFHEExponent(int nbelems)
    : bits(TFHEBits(nbelems)), integer(TFHEIntegerCore(nbelems + 1)) {}

TFHEFloatCore::TFHEExponent::TFHEExponent(int nbelems, float value)
    : TFHEExponent(nbelems) {
  union {
    float f;
    int i;
  } num;
  num.f = value;
  if (secret_key() != nullptr) {
    for (int i = 0; i < nbelems - 1; i++) {
      bootsSymEncrypt(&bits[i], (num.i >> i + 23) & 1, secret_key());
    }
    bootsSymEncrypt(&bits[nbelems - 1], (num.i >> 30) & 1, secret_key());
    upadte_integer();
  } else {
    if (cloud_key() != nullptr) {
      for (int i = 0; i < nbelems - 1; i++) {
        bootsCONSTANT(&bits[i], (num.i >> i + 23) & 1, cloud_key());
      }
      bootsCONSTANT(&bits[nbelems - 1], (num.i >> 30) & 1, cloud_key());
      upadte_integer();
    } else {
      // Error
    }
  }
}

TFHEFloatCore::TFHEExponent::TFHEExponent(TFHEIntegerCore value)
    : TFHEExponent(value.bits.nbelems - 1) {
  integer = value;
  upadte_bits();
}

TFHEFloatCore::TFHEExponent::TFHEExponent(const TFHEExponent& elm)
    : bits(elm.bits), integer(elm.integer) {}

void TFHEFloatCore::TFHEExponent::upadte_bits() {
  TFHEIntegerCore copy_integer = integer;
  copy_integer = copy_integer + TFHEIntegerCore(2, -1);
  for (int i = 0; i < bits.nbelems; i++) {
    bootsCOPY(&bits[i], &copy_integer.bits[i], cloud_key());
  }
  bootsNOT(&bits[bits.nbelems - 1], &bits[bits.nbelems - 1], cloud_key());
}

void TFHEFloatCore::TFHEExponent::upadte_integer() {
  int size = bits.nbelems + 1;
  TFHEIntegerCore result(size);
  for (int i = 0; i < size - 2; i++) {
    bootsCOPY(&result.bits[i], &bits[i], cloud_key());
  }
  bootsCOPY(&result.bits[size - 2], &bits[size - 2], cloud_key());
  bootsNOT(&result.bits[size - 2], &result.bits[size - 2], cloud_key());
  bootsCOPY(&result.bits[size - 1], &bits[size - 2], cloud_key());
  result = result + TFHEIntegerCore(2, 1);
  integer = result;
}

void TFHEFloatCore::TFHEExponent::set_integer(TFHEIntegerCore value) {
  integer = value;
  upadte_bits();
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::add(
    TFHEFloatCore::TFHEExponent value1, TFHEFloatCore::TFHEExponent value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEExponent result(max_nbelems);
  TFHEIntegerCore result_integer = value1.integer + value2.integer;
  result.set_integer(result_integer);

  return result;
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::minus(
    TFHEFloatCore::TFHEExponent value) {
  TFHEExponent result(value.integer.bits.nbelems - 1);
  TFHEIntegerCore result_integer = -value.integer;
  result.set_integer(result_integer);
  return result;
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::sub(
    TFHEFloatCore::TFHEExponent value1, TFHEFloatCore::TFHEExponent value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEExponent result(max_nbelems - 1);
  TFHEIntegerCore result_integer = value1.integer - value2.integer;
  result.set_integer(result_integer);
  return result;
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::mul(
    TFHEFloatCore::TFHEExponent value1, TFHEBoolCore value2) {
  TFHEExponent result(value1.integer.bits.nbelems - 1);
  TFHEIntegerCore result_integer = value1.integer * value2;
  result.set_integer(result_integer);
  return result;
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::et(
    TFHEFloatCore::TFHEExponent value1, TFHEFloatCore::TFHEExponent value2) {
  return value1.integer == value2.integer;
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::lt(
    TFHEFloatCore::TFHEExponent value1, TFHEFloatCore::TFHEExponent value2) {
  return value1.integer < value2.integer;
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::gt(
    TFHEFloatCore::TFHEExponent value1, TFHEFloatCore::TFHEExponent value2) {
  return value1.integer > value2.integer;
}

TFHEFloatCore::TFHEExponent& TFHEFloatCore::TFHEExponent::operator=(
    const TFHEFloatCore::TFHEExponent& elm) {
  if (this != &elm) {
    bits = elm.bits;
    integer = elm.integer;
  }

  return *this;
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::operator+(
    const TFHEFloatCore::TFHEExponent& other) {
  return add(*this, other);
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::operator-() {
  return minus(*this);
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::operator-(
    const TFHEFloatCore::TFHEExponent& other) {
  return sub(*this, other);
}

TFHEFloatCore::TFHEExponent TFHEFloatCore::TFHEExponent::operator*(
    const TFHEBoolCore& other) {
  return mul(*this, other);
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator==(
    const TFHEFloatCore::TFHEExponent& other) {
  return et(*this, other);
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator==(const int& other) {
  if (other == 0) {
    return et(*this, TFHEFloatCore::TFHEExponent(TFHEIntegerCore(2, other)));
  }

  int value = other < 0 ? -other : other;
  return et(*this, TFHEFloatCore::TFHEExponent(
                       TFHEIntegerCore(ceil(log2(value)) + 2, other)));
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator<(
    const TFHEFloatCore::TFHEExponent& other) {
  return lt(*this, other);
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator<(const int& other) {
  if (other == 0) {
    return lt(*this, TFHEFloatCore::TFHEExponent(TFHEIntegerCore(2, other)));
  }

  int value = other < 0 ? -other : other;
  return lt(*this, TFHEFloatCore::TFHEExponent(
                       TFHEIntegerCore(ceil(log2(value)) + 2, other)));
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator>(
    const TFHEFloatCore::TFHEExponent& other) {
  return gt(*this, other);
}

TFHEBoolCore TFHEFloatCore::TFHEExponent::operator>(const int& other) {
  if (other == 0) {
    return gt(*this, TFHEFloatCore::TFHEExponent(TFHEIntegerCore(2, other)));
  }

  int value = other < 0 ? -other : other;
  return gt(*this, TFHEFloatCore::TFHEExponent(
                       TFHEIntegerCore(ceil(log2(value)) + 2, other)));
}

TFHEFloatCore::TFHEFraction::TFHEFraction(int nbelems)
    : bits(TFHEBits(nbelems)),
      integer(TFHEIntegerCore(nbelems + 2)),
      aexp(TFHEIntegerCore(ceil(log2(nbelems)) + 2, 0)) {}

TFHEFloatCore::TFHEFraction::TFHEFraction(int nbelems, float value)
    : TFHEFraction(nbelems) {
  union {
    float f;
    int i;
  } num;
  num.f = value;
  TFHEIntegerCore integer_tmp(nbelems + 2);
  if (secret_key() != nullptr) {
    for (int i = 0; i < nbelems; i++) {
      bootsSymEncrypt(&bits[nbelems - 1 - i], (num.i >> 22 - i) & 1,
                      secret_key());
      bootsCONSTANT(&integer_tmp.bits[nbelems - 1 - i], (num.i >> 22 - i) & 1,
                    cloud_key());
    }
    bootsCONSTANT(&integer_tmp.bits[nbelems], 1, cloud_key());

    bootsCONSTANT(&integer_tmp.bits[nbelems + 1], (num.i >> 31) & 1,
                  cloud_key());

    integer = integer_tmp;

  } else {
    if (cloud_key() != nullptr) {
      for (int i = 0; i < nbelems; i++) {
        bootsCONSTANT(&bits[nbelems - 1 - i], (num.i >> 22 - i) & 1,
                      cloud_key());
        bootsCONSTANT(&integer_tmp.bits[nbelems - 1 - i], (num.i >> 22 - i) & 1,
                      cloud_key());
      }

      bootsCONSTANT(&integer_tmp.bits[nbelems], 1, cloud_key());
      bootsCONSTANT(&integer_tmp.bits[nbelems + 1], (num.i >> 31) & 1,
                    cloud_key());
      integer = integer_tmp;

    } else {
      // Error
    }
  }
}

TFHEFloatCore::TFHEFraction::TFHEFraction() {}
TFHEFloatCore::TFHEFraction::TFHEFraction(const TFHEFraction& elm)
    : bits(elm.bits), integer(elm.integer), aexp(elm.aexp) {}

void TFHEFloatCore::TFHEFraction::upadte_bits() {
  for (int i = 0; i < bits.nbelems; i++) {
    bootsCOPY(&bits[bits.nbelems - i - 1],
              &integer.bits[integer.bits.nbelems - 3 - i], cloud_key());
  }
}

TFHEFloatCore::TFHEFraction TFHEFloatCore::TFHEFraction::shift_and_add(
    TFHEFloatCore::TFHEFraction other, int i) {
  int max_nbelems =
      bits.nbelems > other.bits.nbelems ? bits.nbelems : other.bits.nbelems;
  TFHEFraction result(max_nbelems);

  TFHEIntegerCore value1(integer.bits.nbelems + 1);
  for (int j = 0; j < value1.bits.nbelems - 1; j++) {
    bootsCOPY(&value1.bits[j], &integer.bits[j], cloud_key());
  }
  bootsCOPY(&value1.bits[value1.bits.nbelems - 1],
            &integer.bits[integer.bits.nbelems - 1], cloud_key());

  TFHEIntegerCore value2(other.integer.bits.nbelems + 1);
  for (int j = 0; j < value2.bits.nbelems - 1; j++) {
    bootsCOPY(&value2.bits[j], &other.integer.bits[j], cloud_key());
  }
  bootsCOPY(&value2.bits[value2.bits.nbelems - 1],
            &other.integer.bits[other.integer.bits.nbelems - 1], cloud_key());
  if (i < 0) {
    int k = -i;

    for (int j = 0; j < value1.bits.nbelems - k; j++) {
      bootsCOPY(&value1.bits[j], &value1.bits[j + k], cloud_key());
    }

    for (int j = 0; j < k; j++) {
      bootsCOPY(&value1.bits[value1.bits.nbelems - k + j],
                &value1.bits[value1.bits.nbelems - k - 1], cloud_key());
    }
  }
  if (i > 0) {
    for (int j = 0; j < value2.bits.nbelems - i; j++) {
      bootsCOPY(&value2.bits[j], &value2.bits[j + i], cloud_key());
    }

    for (int j = 0; j < i; j++) {
      bootsCOPY(&value2.bits[value2.bits.nbelems - i + j],
                &value2.bits[value2.bits.nbelems - i - 1], cloud_key());
    }
  }

  TFHEIntegerCore result_integer = value1 + value2;

  TFHEIntegerCore exp(ceil(log2(result.integer.bits.nbelems - 2)) + 1, 1);
  TFHEIntegerCore tmp(result_integer.bits.nbelems);
  bootsCOPY(&tmp.bits[tmp.bits.nbelems - 1],
            &result_integer.bits[result_integer.bits.nbelems - 1], cloud_key());
  TFHEBoolCore flag(false);

  for (int j = result_integer.bits.nbelems - 2; j >= 0; j--) {
    TFHEBoolCore result_bool(
        TFHEBit(&result_integer.bits[result_integer.bits.nbelems - 2]));
    flag = mux(result_bool, TFHEBoolCore(true), flag);
    exp = mux(flag, exp, exp + TFHEIntegerCore(2, -1));

    for (int k = result_integer.bits.nbelems - 2; k > 0; k--) {
      bootsCOPY(&tmp.bits[k], &result_integer.bits[k - 1], cloud_key());
    }

    bootsCONSTANT(&tmp.bits[0], 0, cloud_key());
    result_integer = mux(flag, result_integer, tmp);
  }

  for (int j = 0; j < result.integer.bits.nbelems; j++) {
    bootsCOPY(&result.integer.bits[result.integer.bits.nbelems - 1 - j],
              &result_integer.bits[result_integer.bits.nbelems - 1 - j],
              cloud_key());
  }

  result.upadte_bits();
  result.aexp = exp;
  return result;
}

TFHEFloatCore::TFHEFraction TFHEFloatCore::TFHEFraction::add(
    TFHEFloatCore::TFHEFraction value1, TFHEFloatCore::TFHEFraction value2) {
  int max_nbelems = value1.bits.nbelems > value2.bits.nbelems
                        ? value1.bits.nbelems
                        : value2.bits.nbelems;
  TFHEFraction result(max_nbelems);
  result.integer = value1.integer + value2.integer;

  result.aexp = value1.aexp + value2.aexp;
  result.upadte_bits();
  return result;
}

TFHEFloatCore::TFHEFraction TFHEFloatCore::TFHEFraction::mul(
    TFHEFloatCore::TFHEFraction value1, TFHEBoolCore value2) {
  TFHEFraction result(value1.bits.nbelems);
  result.integer = value1.integer * value2;

  result.aexp = value1.aexp * value2;
  result.upadte_bits();
  return result;
}

TFHEFloatCore::TFHEFraction& TFHEFloatCore::TFHEFraction::operator=(
    const TFHEFloatCore::TFHEFraction& elm) {
  if (this != &elm) {
    bits = elm.bits;
    integer = elm.integer;
    aexp = elm.aexp;
  }

  return *this;
}
TFHEFloatCore::TFHEFraction TFHEFloatCore::TFHEFraction::operator+(
    const TFHEFloatCore::TFHEFraction& other) {
  return add(*this, other);
}

TFHEFloatCore::TFHEFraction TFHEFloatCore::TFHEFraction::operator*(
    const TFHEBoolCore& other) {
  return mul(*this, other);
}

TFHEFloatCore::TFHEFloatCore() {}

TFHEFloatCore::TFHEFloatCore(const TFHEFloatCore& elm)
    : exponent(elm.exponent), fraction(elm.fraction) {}

TFHEFloatCore::TFHEFloatCore(int exponent_nbelems, int fraction_nbelems)
    : exponent(TFHEExponent(exponent_nbelems)),
      fraction(TFHEFraction(fraction_nbelems)) {
  if (1 + exponent_nbelems + fraction_nbelems < 3) {
    // Error
  }
}

TFHEFloatCore::TFHEFloatCore(int exponent_nbelems, int fraction_nbelems,
                             float number)
    : TFHEFloatCore(exponent_nbelems, fraction_nbelems) {
  fraction = TFHEFraction(fraction_nbelems, number);
  exponent = TFHEExponent(exponent_nbelems, number);
}

float TFHEFloatCore::decrypt() {
  union {
    float f;
    int i;
  } num;
  num.f = 0.0f;
  int ai;

  for (int i = 0; i < fraction.bits.nbelems; i++) {
    ai = bootsSymDecrypt(&fraction.bits[fraction.bits.nbelems - 1 - i],
                         secret_key());
    num.i |= (ai << 22 - i);
  }
  for (int i = 0; i < exponent.bits.nbelems - 1; i++) {
    ai = bootsSymDecrypt(&exponent.bits[i], secret_key());
    num.i |= (ai << 23 + i);
  }
  ai = bootsSymDecrypt(&exponent.bits[exponent.bits.nbelems - 1], secret_key());
  num.i |= (ai << 30);
  ai = ai ? 0 : 1;
  for (int i = 0; i < 8 - exponent.bits.nbelems; i++) {
    num.i |= (ai << 22 + exponent.bits.nbelems + i);
  }
  ai = bootsSymDecrypt(
      &fraction.integer.bits[fraction.integer.bits.nbelems - 1], secret_key());

  num.i |= (ai << 31);
  return num.f;
}

TFHEFloatCore TFHEFloatCore::add(TFHEFloatCore value1, TFHEFloatCore value2) {
  int max_exponent_nbelems =
      value1.exponent.bits.nbelems > value2.exponent.bits.nbelems
          ? value1.exponent.bits.nbelems
          : value2.exponent.bits.nbelems;
  int max_fraction_nbelems =
      value1.fraction.bits.nbelems > value2.fraction.bits.nbelems
          ? value1.fraction.bits.nbelems
          : value2.fraction.bits.nbelems;
  TFHEFloatCore result(max_exponent_nbelems, max_fraction_nbelems);
  TFHEFloatCore::TFHEExponent result_exponent =
      mux(value1.exponent > value2.exponent, value1.exponent, value2.exponent);
  TFHEIntegerCore value1_exp_integer(value1.exponent.integer.bits.nbelems + 1);
  for (int i = 0; i < value1_exp_integer.bits.nbelems - 1; i++) {
    bootsCOPY(&value1_exp_integer.bits[i], &value1.exponent.integer.bits[i],
              cloud_key());
  }
  bootsCOPY(&value1_exp_integer.bits[value1_exp_integer.bits.nbelems - 1],
            &value1_exp_integer.bits[value1_exp_integer.bits.nbelems - 2],
            cloud_key());
  TFHEIntegerCore value2_exp_integer(value2.exponent.integer.bits.nbelems + 1);
  for (int i = 0; i < value2_exp_integer.bits.nbelems - 1; i++) {
    bootsCOPY(&value2_exp_integer.bits[i], &value2.exponent.integer.bits[i],
              cloud_key());
  }
  bootsCOPY(&value2_exp_integer.bits[value2_exp_integer.bits.nbelems - 1],
            &value2_exp_integer.bits[value2_exp_integer.bits.nbelems - 2],
            cloud_key());

  TFHEIntegerCore diff_exp = value1_exp_integer - value2_exp_integer;
  TFHEFloatCore::TFHEFraction result_fraction(max_fraction_nbelems, 0);
  TFHEFloatCore::TFHEFraction result_fraction_tmp(max_fraction_nbelems);
  TFHEBoolCore result_bool(false);
  printf("Cushion Start\n");
  result_fraction = result_fraction * result_bool;  // cushion
  printf("Cushion End\n");
  printf("result_fraction:%d\n", result_fraction.integer.decrypt());
  printf("result_fraction bit: ");
  for (int i = result_fraction.integer.bits.nbelems - 1; i >= 0; i--) {
    printf("%d",
           bootsSymDecrypt(&result_fraction.integer.bits[i], secret_key()));
  }
  printf("\n");
  result_bool = diff_exp > value2.exponent.bits.nbelems;
  result_fraction = mux(result_bool, value2.fraction, result_fraction);

  result_exponent.set_integer(
      mux(result_bool, value2.exponent.integer, result_exponent.integer));

  result_bool = diff_exp < -value1.exponent.bits.nbelems;
  result_fraction = mux(result_bool, value1.fraction, result_fraction);
  result_exponent.set_integer(
      mux(result_bool, value1.exponent.integer, result_exponent.integer));

  for (int i = -value1.fraction.bits.nbelems;
       i < value2.fraction.bits.nbelems + 1; i++) {
    result_fraction_tmp = value1.fraction.shift_and_add(value2.fraction, i);

    result_bool = diff_exp == i;

    result_fraction = mux(result_bool, result_fraction_tmp, result_fraction);
    result_exponent.set_integer(
        mux(result_bool, result_exponent.integer + result_fraction.aexp,
            result_exponent.integer));
  }

  result.fraction = result_fraction;
  result.exponent = result_exponent;

  return result;
}

TFHEFloatCore& TFHEFloatCore::operator=(const TFHEFloatCore& elm) {
  exponent = elm.exponent;
  fraction = elm.fraction;
  return *this;
}

TFHEFloatCore TFHEFloatCore::operator+(const TFHEFloatCore& other) {
  return add(*this, other);
}