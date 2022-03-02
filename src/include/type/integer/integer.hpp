/**
 * @file integer.hpp
 * @brief TFHEの整数型のクラス.
 **/
#ifndef INTEGER
#define INTEGER

#include "../array/array.hpp"
#include "../core/integer_core.hpp"
#include "../keyset/keyset.hpp"
#include "../type.hpp"

/**
 * @brief TFHEの整数型のクラス.
 **/
template <int Nbelems>
class TFHEInteger : public TFHEIntegerCore {
 public:
  friend class TFHEArray<TFHEInteger<Nbelems>>;
  TFHEInteger(const TFHEInteger& elm) : TFHEIntegerCore(elm, Nbelems) {}
  TFHEInteger(const TFHEIntegerCore& elm) : TFHEIntegerCore(elm, Nbelems) {}

  /**
   * @brief 空のTFHEの整数型を生成するコンストラクタ.
   **/
  TFHEInteger() : TFHEIntegerCore(Nbelems) {}

  /**
   * @brief TFHEの整数型を生成するコンストラクタ.
   * @param[in] int number(暗号化対象)
   **/
  TFHEInteger(int number) : TFHEIntegerCore(Nbelems, number) {}

  /**
   * @brief TFHEの整数型をファイルから読み込むコンストラクタ.
   * @param[in] const char* path(保存先のパス)
   * @param[in] int id(識別用のID)
   **/
  TFHEInteger(const char* path, int id) : TFHEIntegerCore(Nbelems, path, id) {}

 protected:
  static void save_option_forArray(FILE* fp) {
    int outbf[2];
    outbf[0] = static_cast<int>(TFHEType::TFHEInteger);
    outbf[1] = Nbelems;
    fwrite(outbf, sizeof(int), 2, fp);
  }

  static int array_size(int shape_size, int array_size) {
    return sizeof(int) * (6 + shape_size) + 2536 * array_size * Nbelems;
  }

  static int array_option_num() { return 2; }

  void save_raw(FILE* fp) override { TFHEIntegerCore::save_raw(fp); }
  void load_raw(FILE* fp) override { TFHEIntegerCore::load_raw(fp); }
};

#endif