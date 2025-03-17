#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <algorithm>
#include <span>
#include <vector> 

namespace binary_search {

auto LengthofLongestIncreasingSubsequence(std::span<int> nums) -> int {
  if (nums.empty()) {
    return 0;
  }

  std::vector<int> tails;
  for (int num : nums) {
    auto it = std::lower_bound(tails.begin(), tails.end(), num);
    if (it == tails.end()) {
      tails.push_back(num);
    } else {
      *it = num;
    }
  }
  return static_cast<int>(tails.size());
}

}  // namespace binary_search

#endif  // !BINARY_SEARCH_HPP
