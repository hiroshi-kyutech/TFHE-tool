/**
 * @file float_core.hpp
 * @brief TFHEの浮動小数点型のクラス.
 **/
#ifndef FLOAT_CORE
#define FLOAT_CORE
#include "../../operations/arithmetic/ternary/mux.hpp"
#include "../../operations/arithmetic/utils/full_adder.hpp"
#include "../../operations/arithmetic/utils/half_adder.hpp"
#include "../raw/bit.hpp"
#include "../raw/bits.hpp"
#include "bool_core.hpp"
#include "integer_core.hpp"

/**
 * @brief TFHEの浮動小数点型のクラス.
 **/
class TFHEFloatCore : virtual protected TFHEKeySet {
 private:
  class TFHEExponent : virtual protected TFHEKeySet {
   public:
    TFHEBits bits;
    TFHEIntegerCore integer;
    TFHEExponent();
    TFHEExponent(int nbelems);
    TFHEExponent(int nbelems, float value);
    TFHEExponent(TFHEIntegerCore value);
    TFHEExponent(const TFHEExponent& elm);
    void upadte_bits();
    void upadte_integer();
    void set_integer(TFHEIntegerCore value);
    static TFHEExponent add(TFHEExponent value1, TFHEExponent value2);
    static TFHEExponent minus(TFHEExponent value);
    static TFHEExponent sub(TFHEExponent value1, TFHEExponent value2);
    static TFHEExponent mul(TFHEExponent value1, TFHEBoolCore value2);
    static TFHEBoolCore et(TFHEExponent value1, TFHEExponent value2);
    static TFHEBoolCore lt(TFHEExponent value1, TFHEExponent value2);
    static TFHEBoolCore gt(TFHEExponent value1, TFHEExponent value2);

    TFHEExponent& operator=(const TFHEExponent& elm);
    TFHEExponent operator+(const TFHEExponent& elm);
    TFHEExponent operator-();
    TFHEExponent operator-(const TFHEExponent& elm);
    TFHEExponent operator*(const TFHEBoolCore& elm);
    TFHEBoolCore operator==(const TFHEExponent& elm);
    TFHEBoolCore operator==(const int& elm);
    TFHEBoolCore operator<(const TFHEExponent& elm);
    TFHEBoolCore operator<(const int& elm);
    TFHEBoolCore operator>(const TFHEExponent& elm);
    TFHEBoolCore operator>(const int& elm);
  };

  class TFHEFraction : virtual protected TFHEKeySet {
   public:
    TFHEBits bits;
    TFHEIntegerCore integer;
    TFHEIntegerCore aexp;
    TFHEFraction();
    TFHEFraction(int nbelems);
    TFHEFraction(int nbelems, float value);
    TFHEFraction(const TFHEFraction& elm);
    void upadte_bits();
    TFHEFraction shift_and_add(TFHEFraction orher, int i);
    TFHEFraction add(TFHEFraction value1, TFHEFraction value2);
    TFHEFraction mul(TFHEFraction value1, TFHEBoolCore value2);
    TFHEFraction& operator=(const TFHEFraction& elm);
    TFHEFraction operator+(const TFHEFraction& other);
    TFHEFraction operator*(const TFHEBoolCore& other);
  };

 public:
  TFHEExponent exponent;
  TFHEFloatCore();
  TFHEFraction fraction;
  TFHEFloatCore(const TFHEFloatCore& elm);
  TFHEFloatCore(int exponent_nbelems, int fraction_nbelems);
  TFHEFloatCore(int exponent_nbelems, int fraction_nbelems, float number);
  float decrypt();
  TFHEFloatCore add(TFHEFloatCore value1, TFHEFloatCore value2);

  TFHEFloatCore& operator=(const TFHEFloatCore& num);
  TFHEFloatCore operator+(const TFHEFloatCore& other);
};

#endif