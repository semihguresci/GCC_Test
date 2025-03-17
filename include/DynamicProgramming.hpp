#ifndef DYNAMICPROGRAMMING_HPP
#define DYNAMICPROGRAMMING_HPP

#include <algorithm>
#include <limits>
#include <span>
#include <stdexcept>
#include <tuple>

namespace dp {
auto ClimbStairs(int n) -> int {
  if (n < 0) {
    throw std::invalid_argument(
        "Factorial is not defined for negative numbers.");
  }

  if (n == 0 || n == 1) return 1;

  int prev2 = 1;
  int prev1 = 1;

  int curr = 0;
  for (int i = 2; i <= n; ++i) {
    curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }
  return curr;
}

auto MaxSubarray(std::span<int> nums) -> std::tuple<int, size_t, size_t> {
  if (nums.empty()) {
    return std::make_tuple(0, 0, 0);
  }
  int max_global = nums[0];
  int max_current = nums[0];

  size_t start = 0;
  size_t end = 0;
  size_t temp_start = 0;

  for (size_t i = 1; i < nums.size(); ++i) {
    if (nums[i] > max_current + nums[i]) {
      max_current = nums[i];
      temp_start = i;
    } else {
      max_current += nums[i];
    }

    if (max_current > max_global) {
      max_global = max_current;
      start = temp_start;
      end = i;
    }
  }

  return std::make_tuple(max_global, start, end);
}

auto CoinChange(std::span<int> coins, int amont) -> int {
  std::vector<int> dp(amont + 1, std::numeric_limits<int>::max());
  dp[0] = 0;

  for (int i = 1; i <= amont; ++i) {
    for (int j = 0; j < coins.size(); ++j) {
      if (coins[j] <= i &&
          dp[i - coins[j]] != std::numeric_limits<int>::max()) {
        dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
      }
    }
  }
  return dp[amont] == std::numeric_limits<int>::max() ? -1 : dp[amont];
}

auto LengthofLongestIncreasingSubsequence(std::span<int> nums) {
  if (nums.empty()) {
    return 0;
  }
  std::vector<int> dp(nums.size(), 1);
  int max_length = 1;
  for (size_t i = 1; i < nums.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        dp[i] = std::max(dp[i], dp[j] + 1);
        max_length = std::max(max_length, dp[i]);
      }
    }
  }
  return max_length;
}

auto Knapsack01Problem(int W, std::span<int> weights, std::span<int> values)
    -> int {
  int n = weights.size();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

  for (size_t i = 1; i <= n; ++i) {
    for (int w = 1; w <= W; ++w) {
      if (weights[i - 1] <= w) {
        dp[i][w] = std::max(dp[i - 1][w],
                            values[i - 1] + dp[i - 1][w - weights[i - 1]]);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }
  return dp[n][W];
}

}  // namespace dp

#endif  // !DYNAMICPROGRAMMING_HPP
