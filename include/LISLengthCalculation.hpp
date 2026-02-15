/*
Given an array of numbers, find the length of the longest increasing subsequence
in the array. The subsequence does not necessarily have to be contiguous. For
example, given the array [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15],
the longest increasing subsequence has length 6: it is 0, 2, 6, 9, 11, 15.
*/

#ifndef LONGEST_INCREASING_SUBSEQUENCE_LENGTH_CALCULATION_HPP
#define LONGEST_INCREASING_SUBSEQUENCE_LENGTH_CALCULATION_HPP

#include <algorithm>
#include <span>
#include <vector>

class LongestIncreasingSubsequence {
 public:
  template <typename T>
  static std::size_t Length(std::span<const T> nums) {
    std::vector<T> tails;
    tails.reserve(nums.size());

    for (const T& x : nums) {
      auto it = std::lower_bound(tails.begin(), tails.end(), x);
      if (it == tails.end()) {
        tails.push_back(x);
      } else {
        *it = x;
      }
    }
    return tails.size();
  }

  template <typename T>
  static std::vector<T> Sequence(std::span<const T> nums) {
    const std::size_t n = nums.size();
    if (n == 0) return {};

    std::vector<T> tails_vals;
    std::vector<std::size_t> tails_indices;
    std::vector<std::size_t> prev_indices(n, n);

    tails_vals.reserve(n);
    tails_indices.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
      const T& x = nums[i];

      auto it = std::lower_bound(tails_vals.begin(), tails_vals.end(), x);
      std::size_t pos = static_cast<std::size_t>(it - tails_vals.begin());

      if (pos > 0) {
        prev_indices[i] = tails_indices[pos - 1];
      }

      if (it == tails_vals.end()) {
        tails_vals.push_back(x);
        tails_indices.push_back(i);
      } else {
        *it = x;
        tails_indices[pos] = i;
      }
    }

    std::vector<T> result;
    result.reserve(tails_indices.size());

    std::size_t idx = tails_indices.back();
    while (idx != n) {
      result.push_back(nums[idx]);
      idx = prev_indices[idx];
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};

class LongestNonDecreasingSubsequence {
 public:
  template <typename T>
  static std::vector<T> Sequence(std::span<const T> nums) {
    const std::size_t n = nums.size();
    if (0 == n) return {};

    std::vector<T> tails;
    std::vector<std::size_t> tails_indices;
    std::vector<std::size_t> prev_indices(n, n);

    tails.reserve(n);
    tails_indices.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
      const T& x = nums[i];

      auto it = std::upper_bound(tails.begin(), tails.end(), x);
      const std::size_t idx = std::distance(tails.begin(), it);

      if (idx > 0) {
        prev_indices[i] = tails_indices[idx - 1];
      }

      if (it == tails.end()) {
        tails.push_back(x);
        tails_indices.push_back(i);
      } else {
        *it = x;
        tails_indices[idx] = i;
      }
    }

    std::vector<T> result;
    result.reserve(tails_indices.size());
    std::size_t idx = tails_indices.back();
    while (idx != n) {
      result.push_back(nums[idx]);
      idx = prev_indices[idx];
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};
#endif  // !LONGEST_INCREASING_SUBSEQUENCE_LENGTH_CALCULATION_HPP