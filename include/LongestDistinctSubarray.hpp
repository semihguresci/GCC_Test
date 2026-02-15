/*
Given an array of elements, return the length of the longest subarray where all
its elements are distinct.

For example, given the array [5, 1, 3, 5, 2, 3, 4, 1], return 5 as the longest
subarray of distinct elements is [5, 2, 3, 4, 1].
*/

#ifndef LONGEST_DISTINCT_SUBARRAY_HPP
#define LONGEST_DISTINCT_SUBARRAY_HPP

#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <vector>

class LongestDistinctSubarray {
 public:
  template <class T>
  static std::size_t Get(const std::vector<T>& a) {
    std::unordered_map<T, std::size_t> last;  
    std::size_t left = 0;
    std::size_t best = 0;

    for (std::size_t right = 0; right < a.size(); ++right) {
      auto it = last.find(a[right]);
      if (it != last.end() && it->second >= left) {
        left = it->second + 1;  
      }
      last[a[right]] = right;
      best = std::max(best, right - left + 1);
    }
    return best;
  }
};



#endif  // !LONGEST_DISTINCT_SUBARRAY_HPP