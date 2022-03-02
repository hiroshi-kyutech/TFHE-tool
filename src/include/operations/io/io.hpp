/**
 * @file io.hpp
 * @brief ファイル入出力の共通処理のクラス.
 **/
#ifndef INPUTOUTPUT
#define INPUTOUTPUT
#include "../../type/keyset/keyset.hpp"

/**
 * @brief ファイル入出力の共通処理のクラス.
 */
class TFHEIO : virtual protected TFHEKeySet {
 protected:
  static void find_file_pointer(const char *path, int id, long result[3]);
  static void remove_from_file(const char *path, long pos[3]);
};

#endif