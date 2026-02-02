#ifndef REVERSE3TRICK_H
#define REVERSE3TRICK_H

/*
Given an array and a number k that's smaller than the length of the array,
rotate the array to the right k elements in-place.
*/

#include <algorithm>
#include <vector>

namespace Reverse3Trick {
void RotateRight(std::vector<int>& a, int k) {
  int n = a.size();
  if (k <= 0 || k > n) return;

  std::reverse(a.begin(), a.end());
  std::reverse(a.begin(), a.begin() + k);
  std::reverse(a.begin() + k, a.end());
}
}  // namespace Reverse3Trick
#endif  // REVERSE3TRICK_H