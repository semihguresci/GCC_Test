#ifndef MAX_PRODUCT_H
#define MAX_PRODUCT_H

#include <algorithm>
#include <limits>
#include <optional>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <vector>

/// Computes the maximum product of any two numbers in the given array.
/// @param values A span of integral or floating-point values.
/// @return The maximum product of any two numbers in the array.
/// @throws std::invalid_argument if the array contains fewer than two elements.
template <typename ValueType>
  requires std::integral<ValueType> || std::floating_point<ValueType>
auto MaxProduct(const std::span<ValueType>) -> std::optional<ValueType>;

template auto MaxProduct<int>(const std::span<int>) -> std::optional<int>;
template auto MaxProduct<double>(const std::span<double>)
    -> std::optional<double>;

template <typename ValueType>
  requires std::integral<ValueType> || std::floating_point<ValueType>
inline auto MaxProduct(const std::span<ValueType> values)
    -> std::optional<ValueType> {
  if (values.size() < 2) {
    return std::nullopt;
  }

  ValueType min1 = std::min(values[0], values[1]);
  ValueType min2 = std::max(values[0], values[1]);
  ValueType max1 = min2;
  ValueType max2 = min1;

  for (size_t i = 2; i < values.size(); ++i) {
    const auto val = values[i];
    if (val > max1) {
      max2 = max1;
      max1 = val;
    } else if (val > max2) {
      max2 = val;
    }

    if (val < min1) {
      min2 = min1;
      min1 = val;
    } else if (val < min2) {
      min2 = val;
    }
  }

  return std::max(max1 * max2, min1 * min2);
}

#endif  // MAX_PRODUCT_H
