/**
 * @file bool.hpp
 * @brief TFHEの真理値型のクラス.
 **/
#ifndef BOOL
#define BOOL
#include "../array/array.hpp"
#include "../core/integer_core.hpp"

/**
 * @brief TFHEの真理値型のクラス.
 **/
class TFHEBool : public TFHEBoolCore {
 public:
  friend class TFHEArray<TFHEBool>;
  TFHEBool(const TFHEBool& elm);
  TFHEBool(const TFHEBoolCore& elm);

  /**
   * @brief 空のTFHEのBool型を生成するコンストラクタ.
   **/
  TFHEBool();

  /**
   * @brief TFHEのBool型を生成するコンストラクタ.
   * @param[in] int number(暗号化対象)
   **/
  TFHEBool(bool value);

  /**
   * @brief TFHEのBool型をファイルから読み込むコンストラクタ.
   * @param[in] const char* path(保存先のパス)
   * @param[in] int id(識別用のID)
   **/
  TFHEBool(const char* path, int id);

  TFHEIntegerCore operator*(const TFHEIntegerCore& other);

  /**
   * @brief TFHEBool型の論理和を行うオペレータ.
   * @param[in] TFHEBool this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator+(const TFHEBoolCore& other);

  /**
   * @brief TFHEBool型の論理積を行うオペレータ.
   * @param[in] TFHEBool this(呼び出し元のポインタ)
   * @param[in] TFHEBoolCore(TFHEBool) other(対象の参照)
   * @return TFHEBoolCore(TFHEBool) 論理演算結果
   **/
  TFHEBoolCore operator*(const TFHEBoolCore& other);

 protected:
  static void save_option_forArray(FILE* fp);
  static int array_size(int shape_size, int array_size);
  static int array_option_num();
  void load_raw(FILE* fp) override;
  void save_raw(FILE* fp) override;
  TFHEIntegerCore mul(TFHEBool value1, TFHEIntegerCore value2);
};

#endif