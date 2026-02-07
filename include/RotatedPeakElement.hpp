/*
Given a array that's sorted but rotated at some unknown pivot, in which all
elements are distinct, find a "peak" element in O(log N) time. An element is
considered a peak if it is greater than both its left and right neighbors. It is
guaranteed that the first and last elements are lower than all others.
*/

#ifndef ROTATED_PEAK_ELEMENT_HPP
#define ROTATED_PEAK_ELEMENT_HPP
#include <span>
#include <stdexcept>

class RotatedPeakElement {
 public:
  static int FindPeakElement(std::span<const int> nums) {
    int n = (int)nums.size();
    if (n < 3) throw std::invalid_argument("Need at least 3 elements.");

    int l = 0, r = n - 1;

    while (l < r) {
      int mid = l + (r - l) / 2;

      if (nums[mid] > nums[r]) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    int minIdx = l;
    int peakIdx = (minIdx - 1 + n) % n;
    return peakIdx;
  }
};

#endif  // ! ROTATED_PEAK_ELEMENT_HPP
