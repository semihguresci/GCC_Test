#ifndef MAXNONADJACENTSUM_HPP
#define MAXNONADJACENTSUM_HPP

/*
 * Given a list of integers, write a function that returns the largest sum of
 * non-adjacent numbers. Numbers can be 0 or negative.
 */

#include <algorithm>
#include <cstdint>
#include <vector>
#include <limits>


class MaxNonAdjacentSum {
 public:
  long long MaxSum(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];

    constexpr long long NEG_INF = std::numeric_limits<long long>::min();

    long long prev1 = NEG_INF;
    long long prev2 = NEG_INF;

    for (auto xi : nums) {
      long long x = static_cast<long long>(xi);
      
      long long extend = (prev2 == NEG_INF) ? NEG_INF : (prev2 + x);
      long long take = std::max(x, extend);
      long long cur = std::max(prev1, take);

      prev2 = prev1;
      prev1 = cur;
    }

    return prev1;
  }
};

#endif  // MAXNONADJACENTSUM_HPP