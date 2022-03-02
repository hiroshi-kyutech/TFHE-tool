/**
 * @file bool_core.hpp
 * @brief TFHEのBool型のcoreクラス.
 **/
#ifndef BOOL_CORE
#define BOOL_CORE
#include "../../operations/io/io.hpp"
#include "../raw/bit.hpp"
#include "../type.hpp"

/**
 * @brief TFHEのBool型のcoreクラス.
 **/
class TFHEBoolCore : virtual protected TFHEKeySet, virtual protected TFHEIO {
 public:
  TFHEBit bit;
  TFHEBoolCore(const TFHEBoolCore& elm);
  TFHEBoolCore();
  TFHEBoolCore(bool value);
  TFHEBoolCore(TFHEBit value);
  TFHEBoolCore(const char* path, int id);

  void save(const char* path, int id);

  /**
   * @brief TFHEのBool型を復号するメソッド.
   * @return bool 復号結果
   **/
  bool decrypt();

  /**
   * @brief TFHEのBool型の代入を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 代入結果
   **/
  TFHEBoolCore& operator=(const TFHEBoolCore& elm);

  /**
   * @brief TFHEのBool型の否定を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @return TFHEBoolCore(TFHEBool)論理演算結果
   **/
  TFHEBoolCore operator!();

  /**
   * @brief TFHEのBool型の論理積を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator&(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の論理和を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator|(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の排他的論理和を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator^(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の論理積を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator*(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の論理和を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator+(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の等号の判定を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator==(const TFHEBoolCore& other);

  /**
   * @brief TFHEのBool型の等号の否定の判定を行うオペレータ.
   * @param[in] TFHEBoolCore(TFHEBool) this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator!=(const TFHEBoolCore& other);

 protected:
  virtual void load_raw(FILE* fp);
  virtual void save_raw(FILE* fp);

  TFHEBoolCore _not(TFHEBoolCore value);
  TFHEBoolCore _and(TFHEBoolCore value1, TFHEBoolCore value2);
  TFHEBoolCore _or(TFHEBoolCore value1, TFHEBoolCore value2);
  TFHEBoolCore _xor(TFHEBoolCore value1, TFHEBoolCore value2);
  TFHEBoolCore et(TFHEBoolCore value1, TFHEBoolCore value2);
  TFHEBoolCore net(TFHEBoolCore value1, TFHEBoolCore value2);
};

#endif