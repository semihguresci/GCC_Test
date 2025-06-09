#ifndef MAXIMUM_SUBARRAY_HPP
#define MAXIMUM_SUBARRAY_HPP

#include <algorithm>
#include <limits>
#include <span>
#include <utility>
#include <vector>

namespace MaximumSubarray {

// Function to find the maximum subarray sum using Kadane's algorithm
template <typename T>
auto MaxSubArraySumKadane(const std::span<T>& nums) -> T {
  T max_so_far = std::numeric_limits<T>::min();

  if (nums.empty()) return max_so_far;

  T max_ending_here = 0;
  for (const auto& num : nums) {
    max_ending_here += num;
    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }
    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
  }
  return max_so_far;
}

template <typename T>
auto MaxSubArraySumModern(const std::span<T>& nums) -> T {
  T max_sum = std::numeric_limits<T>::min();
  return std::ranges::fold_left(nums, std::pair{max_sum, T(0)},
                                [](auto&& acc, auto num) {
                                  auto& [max_sum, current_sum] = acc;
                                  current_sum =
                                      std::max(num, current_sum + num);
                                  max_sum = std::max(max_sum, current_sum);
                                  return acc;
                                })
      .first;
}

}  // namespace MaximumSubarray
#endif  // !MAXIMUM_SUBARRAY_HPP
