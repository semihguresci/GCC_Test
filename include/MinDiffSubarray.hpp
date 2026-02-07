/*
Given an array of positive integers, divide the array into two subsets such that
the difference between the sum of the subsets is as small as possible. For
example, given [5, 10, 15, 20, 25], return the sets {10, 25} and {5, 15, 20},
which has a difference of 5, which is the smallest possible difference.
*/

#ifndef MIN_DIFF_SUBARRAY_HPP
#define MIN_DIFF_SUBARRAY_HPP

#include <algorithm>
#include <numeric>
#include <span>
#include <vector>

class MinDiffSubarray {
 public:
  struct PartitionResult {
    std::vector<int> subset1;
    std::vector<int> subset2;
    int diff;
    int sum1;
    int sum2;
  };

  PartitionResult FindMinDiffSubarray(std::span<const int> nums) {
    auto n = static_cast<int>(nums.size());
    auto s = std::accumulate(nums.begin(), nums.end(), 0);
    auto half = s / 2;

    // dp[i] will be true if there is a subset of nums that sums to i
    std::vector<bool> dp(half + 1, false);
    dp[0] = true;

    std::vector<int> prev(half + 1, -1);  // To reconstruct the subset
    std::vector<int> prevIdx(half + 1,
                             -1);  // To track the index of the number used

    for (int i = 0; i < n; ++i) {
      int v = nums[i];
      for (int sum = half; sum >= v; --sum) {
        if (dp[sum - v] && !dp[sum]) {
          dp[sum] = true;
          prev[sum] = sum - v;
          prevIdx[sum] = i;
        }
      }
    }

    // Find the best possible sum for subset1
    int best = half;
    while (best >= 0 && !dp[best]) {
      --best;
    }

    std::vector<bool> used(n, false);
    int curr = best;
    while (curr > 0) {
      int idx = prevIdx[curr];
      used[idx] = true;
      curr = prev[curr];
    }

    PartitionResult res;
    res.sum1 = best;
    res.sum2 = s - best;
    res.diff = std::abs(res.sum1 - res.sum2);

    for (int i = 0; i < n; ++i) {
      if (used[i]) {
        res.subset1.push_back(nums[i]);
      } else {
        res.subset2.push_back(nums[i]);
      }
    }
    return res;
  }
};

#endif  // ! MIN_DIFF_SUBARRAY_HPP