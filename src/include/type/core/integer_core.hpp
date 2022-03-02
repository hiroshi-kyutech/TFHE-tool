/**
 * @file integer_core.hpp
 * @brief TFHEの整数型のcoreクラス.
 **/
#ifndef INTEGER_CORE
#define INTEGER_CORE
#include "../../operations/arithmetic/ternary/mux.hpp"
#include "../../operations/arithmetic/utils/full_adder.hpp"
#include "../../operations/arithmetic/utils/half_adder.hpp"
#include "../../operations/io/io.hpp"
#include "../config/config.hpp"
#include "../raw/bits.hpp"
#include "bool_core.hpp"

/**
 * @brief TFHEの整数型のcoreクラス.
 **/
class TFHEIntegerCore : virtual protected TFHEKeySet, virtual protected TFHEIO {
 public:
  TFHEBits bits;

  TFHEIntegerCore();
  TFHEIntegerCore(const TFHEIntegerCore& elm, int nbelems);

  TFHEIntegerCore(int nbelems);

  TFHEIntegerCore(int nbelems, int number);

  TFHEIntegerCore(int nbelems, const char* path, int id);

  /**
   * @brief TFHEの整数型を復号するメソッド.
   * @return int 復号結果
   **/
  int decrypt();

  /**
   * @brief TFHEの整数型をファイルに保存するメソッド.
   * @param[in] const char* path(保存先のパス)
   * @param[in] int id(識別用のID)
   **/
  void save(const char* path, int id);

  /**
   * @brief TFHEの整数型で符号を取得するメソッド.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @return TFHEIntegerCore(TFHEInteger) 符号(1 or -1)
   **/
  TFHEIntegerCore sign();

  /**
   * @brief TFHEの整数型で絶対値を取得するメソッド.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @return TFHEIntegerCore(TFHEInteger) 絶対値
   **/
  TFHEIntegerCore abs();

  /**
   * @brief TFHEの整数型の代入を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 代入結果
   **/
  TFHEIntegerCore& operator=(const TFHEIntegerCore& num);

  /**
   * @brief TFHEの整数型で加算を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 加算結果
   **/
  TFHEIntegerCore operator+(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型の反数を返すオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @return TFHEIntegerCore(TFHEInteger) 反数
   **/
  TFHEIntegerCore operator-();

  /**
   * @brief TFHEの整数型で減算を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 減算結果
   **/
  TFHEIntegerCore operator-(const TFHEIntegerCore& other);

  /**
   * @brief
   *TFHEの整数型で真理値がtrueならば現在値をfalseならば0を返すオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 現在値か0
   **/
  TFHEIntegerCore operator*(const TFHEBoolCore& other);

  /**
   * @brief TFHEの整数型で乗算を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 乗算結果
   **/
  TFHEIntegerCore operator*(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で除算を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 除算結果
   **/
  TFHEIntegerCore operator/(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で剰余演算を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEIntegerCore(TFHEInteger) 剰余演算結果
   **/
  TFHEIntegerCore operator%(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で不等号(less than)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator<(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で等号付き不等号(less than or equal
   *to)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator<=(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で不等号(greater than)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator>(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で等号付き不等号(greater than or
   * equal to)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator>=(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で等号(eqaul to)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator==(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型で等号否定(not equal to)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] TFHEIntegerCore(TFHEInteger) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator!=(const TFHEIntegerCore& other);

  /**
   * @brief TFHEの整数型とint型で不等号(less than)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] int other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator<(const int& other);

  /**
   * @brief TFHEの整数型で不等号(greater than)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] int other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator>(const int& other);

  /**
   * @brief TFHEの整数型とint型で等号(eqaul to)の判定を行うオペレータ.
   * @param[in] TFHEIntegerCore(TFHEInteger) this(呼び出し元のポインタ)
   * @param[in] int other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 判定結果
   **/
  TFHEBoolCore operator==(const int& other);

 protected:
  TFHEBoolCore overflow_error_flag;
  TFHEBoolCore division_byZero_error_flag;
  virtual void save_raw(FILE* fp);
  virtual void load_raw(FILE* fp);
  void check_division_byZero(TFHEIntegerCore value);
  void check_overflow_add(TFHEIntegerCore value1, TFHEIntegerCore value2);
  void check_overflow_sub(TFHEIntegerCore value1, TFHEIntegerCore value2);
  void check_overflow_mul();
  void check_error(TFHEIntegerCore value);
  void check_decrypt_error();
  TFHEIntegerCore add(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEIntegerCore minus(TFHEIntegerCore value);
  TFHEIntegerCore sub(TFHEIntegerCore value1, TFHEIntegerCore value2);
  static TFHEIntegerCore shift(TFHEIntegerCore value, int shift);
  TFHEIntegerCore mul(TFHEIntegerCore value1, TFHEBoolCore value2);
  TFHEIntegerCore mul(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEIntegerCore div(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEIntegerCore mod(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore lt(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore ltoet(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore gt(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore gtoet(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore et(TFHEIntegerCore value1, TFHEIntegerCore value2);
  TFHEBoolCore net(TFHEIntegerCore value1, TFHEIntegerCore value2);
};

#endif