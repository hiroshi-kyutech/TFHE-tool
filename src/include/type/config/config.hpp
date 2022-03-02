/**
 * @file  config.hpp
 * @brief 設定するクラス.
 **/
#ifndef CONFIG
#define CONFIG
#include "../../common/common.hpp"

/**
 * @brief 設定するクラス.
 **/
class TFHEConfig {
 public:
  /**
   * @brief TFHEBool型の論理積を行うオペレータ.
   * falseに設定することでエラー検出機能をoffにする代わりに計算時間を短くする.
   **/
  static bool safe_mode;
  TFHEConfig();
  ~TFHEConfig();
  /**
   * @brief TFHEの鍵生成前にシード値を設定するためのメソッド.
   * @param[in] uint32_t* values(配列)
   * @param[in] int size(配列の要素の数)
   **/
  static void setSeed(uint32_t* values, int size);
};
#endif