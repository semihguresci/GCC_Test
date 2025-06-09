#ifndef LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS_HPP
#define LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS_HPP

/*
Longest Substring Without Repeating Characters
Problem:
Given a string s, find the length of the longest substring without repeating
characters.
*/
#include <string>
#include <unordered_map>

namespace LongestSubstringWithoutRepeatingCharacters {
int LengthOfLongestSubstring(const std::string& s) {
  std::unordered_map<char, int> last_seen;
  int left = 0;
  int max_len = 0;

  for (int right = 0; right < s.size(); ++right) {
    char c = s[right];
    if (last_seen.count(c) && last_seen[c] >= left) {
      left = last_seen[c] + 1; 
    }
    last_seen[c] = right;
    max_len = std::max(max_len, right - left + 1);
  }
  return max_len;
  }
}

#endif  // !LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS_HPP