/*
You are given an array of nonnegative integers. Let's say you start at the
beginning of the array and are trying to advance to the end. You can advance at
most, the number of steps that you're currently on. Determine whether you can
get to the end of the array.

For example, given the array [1, 3, 1, 2, 0, 1], we can go from indices 0 -> 1
-> 3 -> 5, so return true.

Given the array [1, 2, 1, 0, 0], we can't reach the end, so return false.
*/

#ifndef JUMP_GAME_HPP
#define JUMP_GAME_HPP

#include <algorithm>
#include <cstddef>
#include <span>

class JumpGame {
 public:
  static bool canJump(std::span<const int> nums) {
    const std::size_t n = nums.size();
    if (n == 0) return false;
    if (n == 1) return true;
    std::size_t maxReach = 0;
    for (size_t i = 0; i < n; ++i) {
      if (i > maxReach) {
        return false;  // Can't reach this index
      }
      maxReach = std::max(
          maxReach, static_cast<std::size_t>(static_cast<int>(i) + nums[i]));
    }
    return true;  // Can reach the end
  }
};

#endif  // JUMP_GAME_HPP