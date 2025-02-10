#ifndef SEARCHROTATEDARRAY_HPP
#define SEARCHROTATEDARRAY_HPP

#include <cmath>
#include <concepts>
#include <limits>
#include <optional>
#include <type_traits>
#include <vector>

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
auto IsEqual(T a, T b) {
  constexpr bool isIntegral = std::integral<T>;
  T epsilon = isIntegral ? static_cast<T>(1)
                         : std::numeric_limits<T>::epsilon() *
                               std::max(std::abs(a), std::abs(b));
  return std::abs(a - b) < epsilon;
}

template <typename Container>
  requires Numeric<typename Container::value_type>
auto SearchRotatedArray(const Container& nums,
                        typename Container::value_type target)
    -> std::optional<std::ptrdiff_t> {
  if (nums.empty()) return std::nullopt;

  std::ptrdiff_t left = 0;
  std::ptrdiff_t right = nums.size() - 1;

  while (left <= right) {
    std::ptrdiff_t mid = left + (right - left) / 2;

    if (IsEqual(nums[left], target)) return left;
    if (IsEqual(nums[mid], target)) return mid;
    if (IsEqual(nums[right], target)) return right;

    if (IsEqual(nums[left], nums[mid])) {
      ++left;
      continue;
    }

    if (IsEqual(nums[mid], nums[right])) {
      --right;
      continue;
    }

    if (nums[left] <= nums[mid]) {
      if (nums[left] <= target && target < nums[mid]) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    } else {
      if (nums[mid] < target && target <= nums[right]) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }
  return std::nullopt;
}
#endif  // !SEARCHROTATEDARRAY_HPP
