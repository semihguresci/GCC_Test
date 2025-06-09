#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <algorithm>
#include <span>
#include <vector> 

namespace BinarySearch {

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

template <typename T>
auto Search(std::span<T> nums, T target) -> int {
  int left = 0;
  int right = static_cast<int>(nums.size()) - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;  
}

}  // namespace BinarySearch

#endif  // !BINARY_SEARCH_HPP
