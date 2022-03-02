/**
 * @file  keyset.cpp
 * @brief TFHEの秘密鍵,クラウド鍵,パラメータをまとめて管理するクラスの実装.
 **/
#include "keyset.hpp"

_TFHEKeySet TFHEKeySet::keyset = _TFHEKeySet();

_TFHEKeySet::~_TFHEKeySet() { delete_keyset(); }

void _TFHEKeySet::delete_keyset() {
  if (_parameters != nullptr) {
    delete_gate_bootstrapping_parameters(_parameters);
    _parameters = nullptr;
  }
  if (_cloud_key != nullptr) {
    delete_gate_bootstrapping_cloud_keyset(_cloud_key);
    _cloud_key = nullptr;
  }
  if (_secret_key != nullptr) {
    delete_gate_bootstrapping_secret_keyset(_secret_key);
    _secret_key = nullptr;
  }
}

const TFheGateBootstrappingParameterSet* _TFHEKeySet::parameters() {
  if (_parameters != nullptr) {
    return _parameters;
  } else {
    if (_cloud_key != nullptr) {
      return _cloud_key->params;
    } else {
      if (_secret_key != nullptr) {
        return _secret_key->params;
      }
    }
  }
  return nullptr;
}

const TFheGateBootstrappingCloudKeySet* _TFHEKeySet::cloud_key() {
  if (_cloud_key != nullptr) {
    return _cloud_key;
  } else {
    if (_secret_key != nullptr) {
      return &(_secret_key->cloud);
    }
  }
  return nullptr;
}

const TFheGateBootstrappingSecretKeySet* _TFHEKeySet::secret_key() {
  if (_secret_key != nullptr) {
    return _secret_key;
  }
  return nullptr;
}

void _TFHEKeySet::create_new_keyset(int minimum_lambda) {
  delete_keyset();
  _parameters = new_default_gate_bootstrapping_parameters(minimum_lambda);
  _secret_key = new_random_gate_bootstrapping_secret_keyset(_parameters);
}

void _TFHEKeySet::load_parameters(const char* path) {
  delete_keyset();
  FILE* fp = fopen(path, "rb");
  _parameters = new_tfheGateBootstrappingParameterSet_fromFile(fp);
  fclose(fp);
}

void _TFHEKeySet::load_cloud_key(const char* path) {
  FILE* fp = fopen(path, "rb");
  _cloud_key = new_tfheGateBootstrappingCloudKeySet_fromFile(fp);
  fclose(fp);
}

void _TFHEKeySet::load_secret_key(const char* path) {
  FILE* fp = fopen(path, "rb");
  _secret_key = new_tfheGateBootstrappingSecretKeySet_fromFile(fp);
  fclose(fp);
}

void TFHEKeySet::save_parameters(const char* path) {
  FILE* fp = fopen(path, "wb");
  export_tfheGateBootstrappingParameterSet_toFile(fp, keyset.parameters());
  fclose(fp);
}

void TFHEKeySet::save_cloud_key(const char* path) {
  FILE* fp = fopen(path, "wb");
  export_tfheGateBootstrappingCloudKeySet_toFile(fp, keyset.cloud_key());
  fclose(fp);
}

void TFHEKeySet::save_secret_key(const char* path) {
  FILE* fp = fopen(path, "wb");
  export_tfheGateBootstrappingSecretKeySet_toFile(fp, keyset.secret_key());
  fclose(fp);
}
