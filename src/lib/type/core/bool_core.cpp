/**
 * @file bool_core.cpp
 * @brief TFHEの真理値型のcoreクラスの実装.
 **/
#include "bool_core.hpp"
TFHEBoolCore::TFHEBoolCore(TFHEBit value) : bit(value) {}

TFHEBoolCore::TFHEBoolCore(const TFHEBoolCore& elm) : bit(elm.bit) {}

TFHEBoolCore::TFHEBoolCore() : bit(TFHEBit()) {}

TFHEBoolCore::TFHEBoolCore(bool value) : TFHEBoolCore() {
  if (secret_key() != nullptr) {
    bootsSymEncrypt(bit.bit, value, secret_key());
  } else {
    if (cloud_key() != nullptr) {
      bootsCONSTANT(bit.bit, value, cloud_key());
    } else {
      // ERROR
    }
  }
}

bool TFHEBoolCore::decrypt() {
  int value;
  value = bootsSymDecrypt(bit.bit, secret_key());
  return value;
}

TFHEBoolCore TFHEBoolCore::_not(TFHEBoolCore value) {
  TFHEBoolCore result;
  bootsNOT(result.bit.bit, value.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore TFHEBoolCore::_and(TFHEBoolCore value1, TFHEBoolCore value2) {
  TFHEBoolCore result;
  bootsAND(result.bit.bit, value1.bit.bit, value2.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore TFHEBoolCore::_or(TFHEBoolCore value1, TFHEBoolCore value2) {
  TFHEBoolCore result;
  bootsOR(result.bit.bit, value1.bit.bit, value2.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore TFHEBoolCore::_xor(TFHEBoolCore value1, TFHEBoolCore value2) {
  TFHEBoolCore result;
  bootsXOR(result.bit.bit, value1.bit.bit, value2.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore TFHEBoolCore::et(TFHEBoolCore value1, TFHEBoolCore value2) {
  TFHEBoolCore result;
  bootsXNOR(result.bit.bit, value1.bit.bit, value2.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore TFHEBoolCore::net(TFHEBoolCore value1, TFHEBoolCore value2) {
  TFHEBoolCore result;
  bootsXOR(result.bit.bit, value1.bit.bit, value2.bit.bit, cloud_key());
  return result;
}

TFHEBoolCore& TFHEBoolCore::operator=(const TFHEBoolCore& elm) {
  bit = elm.bit;
  return *this;
}

TFHEBoolCore TFHEBoolCore::operator!() { return _not(*this); }

TFHEBoolCore TFHEBoolCore::operator&(const TFHEBoolCore& other) {
  return _and(*this, other);
}

TFHEBoolCore TFHEBoolCore::operator|(const TFHEBoolCore& other) {
  return _or(*this, other);
}

TFHEBoolCore TFHEBoolCore::operator^(const TFHEBoolCore& other) {
  return _xor(*this, other);
}

TFHEBoolCore TFHEBoolCore::operator*(const TFHEBoolCore& other) {
  return _and(*this, other);
}
TFHEBoolCore TFHEBoolCore::operator+(const TFHEBoolCore& other) {
  return _or(*this, other);
}

TFHEBoolCore TFHEBoolCore::operator==(const TFHEBoolCore& other) {
  return et(*this, other);
}
TFHEBoolCore TFHEBoolCore::operator!=(const TFHEBoolCore& other) {
  return net(*this, other);
}

void TFHEBoolCore::load_raw(FILE* fp) {
  import_gate_bootstrapping_ciphertext_fromFile(fp, bit.bit, parameters());
}

void TFHEBoolCore::save_raw(FILE* fp) {
  export_gate_bootstrapping_ciphertext_toFile(fp, bit.bit, parameters());
}

TFHEBoolCore::TFHEBoolCore(const char* path, int id) : TFHEBoolCore() {
  long pos[3];

  find_file_pointer(path, id, pos);
  if (pos[0] == -1) {
    // 見つからない
  }
  if (pos[1] != static_cast<int>(TFHEType::TFHEBool)) {
    // Error 該当するIDは要求する型ではない
  }
  FILE* fp;
  if ((fp = fopen(path, "rb")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }
  fseek(fp, pos[0] + 12L, SEEK_SET);

  load_raw(fp);

  fclose(fp);
}

void TFHEBoolCore::save(const char* path, int id) {
  // 同じIDのものがあれば上書きする
  long pos[3];

  find_file_pointer(path, id, pos);

  if (pos[0] != -1) {
    remove_from_file(path, pos);
  }

  int size = sizeof(int) * 3 + 2536;
  int outbf[3] = {id, static_cast<int>(TFHEType::TFHEBool), size};

  FILE* fp;
  if ((fp = fopen(path, "ab+")) == NULL) {
    printf("ファイルオープンエラー\n");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0L, SEEK_END);

  fwrite(outbf, sizeof(int), 3, fp);

  save_raw(fp);

  fclose(fp);
}