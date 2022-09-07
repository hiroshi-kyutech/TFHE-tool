/**
 * @file mux.hpp
 * @brief 条件演算子(multiplexer)の関数.
 */
#ifndef MUX
#define MUX

#include "../../../type/core/bool_core.hpp"

/**
 * @brief 条件式conditionに応じて、真式true_valueか偽式false_valueを返す関数.
 * @param[in] TFHEBoolCore condition(条件式)[TFHEBoolでも可]
 * @param[in] 任意の型Type true_value(真式)
 * @param[in] 任意の型Type false_value(偽式)
 * @return 任意の型Type
 */
template <typename Type>
Type mux(TFHEBoolCore condition, Type true_value, Type false_value) {
  Type true_result;
  std::thread tv([&true_result, &true_value, &condition]() {
    true_result = true_value * condition;
  });
  tv.join();
  Type false_result = false_value * !condition;

  return true_result + false_result;
};

#endif
