/**
 * @file  type.hpp
 * @brief クラスに固有の番号を振り分けする列挙型.
 **/
#ifndef TFHETYPE
#define TFHETYPE

/**
 * @brief クラスに固有の番号を振り分けする列挙型.
 **/
enum class TFHEType {
  TFHEArray = 0,
  TFHEBool,
  TFHEInteger,
  TFHEInt8,
  TFHEInt16,
  TFHEInt32
};

#endif