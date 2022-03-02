/**
 * @file  keyset.hpp
 * @brief TFHEの秘密鍵,クラウド鍵,パラメータをまとめて管理するクラス.
 **/
#ifndef KEY_SET
#define KEY_SET
#include "../../common/common.hpp"

/**
 * @brief TFHEの秘密鍵,クラウド鍵,パラメータをまとめて管理するクラス.
 **/
class _TFHEKeySet {
 private:
  TFheGateBootstrappingParameterSet* _parameters = nullptr;
  TFheGateBootstrappingCloudKeySet* _cloud_key = nullptr;
  TFheGateBootstrappingSecretKeySet* _secret_key = nullptr;

 public:
  const TFheGateBootstrappingParameterSet* parameters();
  const TFheGateBootstrappingCloudKeySet* cloud_key();
  const TFheGateBootstrappingSecretKeySet* secret_key();

  //  public:
  _TFHEKeySet() {}
  ~_TFHEKeySet();
  void create_new_keyset(int minimum_lambda);

  void load_parameters(const char* path);

  void load_cloud_key(const char* path);

  void load_secret_key(const char* path);

  void delete_keyset();
};

/**
 * @brief TFHEの秘密鍵,クラウド鍵,パラメータをまとめて管理するwrapperクラス.
 * @details
 * パラメータは秘密鍵,クラウド鍵に依存,
 * クラウド鍵は秘密鍵に依存している.
 **/
class TFHEKeySet {
 private:
  static _TFHEKeySet keyset;

 protected:
  /**
   * @brief TFheGateBootstrappingParameterSet*を返すメソッド.
   * @return TFheGateBootstrappingParameterSet*
   **/
  static const TFheGateBootstrappingParameterSet* parameters() {
    return keyset.parameters();
  }

  /**
   * @brief TFheGateBootstrappingCloudKeySet*を返すメソッド.
   * @return TFheGateBootstrappingCloudKeySet*
   **/
  static const TFheGateBootstrappingCloudKeySet* cloud_key() {
    return keyset.cloud_key();
  }

  /**
   * @brief TFheGateBootstrappingSecretKeySet*を返すメソッド.
   * @return TFheGateBootstrappingSecretKeySet*
   **/
  static const TFheGateBootstrappingSecretKeySet* secret_key() {
    return keyset.secret_key();
  }

 public:
  TFHEKeySet() {}
  ~TFHEKeySet() {}

  /**
   * @brief TFHEの秘密鍵,クラウド鍵,パラメータを作成するメソッド.
   **/
  static void create_new_keyset(int minimum_lambda) {
    keyset.create_new_keyset(minimum_lambda);
  }

  static void set_seed(uint32_t* values, int size) {
    tfhe_random_generator_setSeed(values, size);
  }

  /**
   * @brief TFHEのパラメータを読み込むメソッド.
   **/
  static void load_parameters(const char* path) {
    keyset.load_parameters(path);
  }

  /**
   * @brief TFHEのクラウド鍵を読み込むメソッド.
   **/
  static void load_cloud_key(const char* path) { keyset.load_cloud_key(path); }

  /**
   * @brief TFHEの秘密鍵を読み込むメソッド.
   **/
  static void load_secret_key(const char* path) {
    keyset.load_secret_key(path);
  }

  /**
   * @brief TFHEのパラメータをファイルに保存するメソッド.
   **/
  static void save_parameters(const char* path);

  /**
   * @brief TFHEのクラウド鍵をファイルに保存するメソッド.
   **/
  static void save_cloud_key(const char* path);

  /**
   * @brief TFHEの秘密鍵をファイルに保存するメソッド.
   **/
  static void save_secret_key(const char* path);
};
#endif