#ifndef MAX_XOR_HPP
#define MAX_XOR_HPP

#include <algorithm>
#include <cstddef>
#include <limits>
#include <span>
#include <type_traits>
#include <vector>
/*
Given an array of integers, find the maximum XOR of any two elements.
*/

template <typename T>
  requires std::is_unsigned_v<T>
class MaxXOR {
 public:
  struct Node {
    int next[2]{-1, -1};
    T value{};  
  };

  struct MaxXorResult {
    T a{};
    T b{};
    T xor_value{};
  };

  static MaxXorResult MaxXORPair(std::span<const T> nums) {
    MaxXorResult out{};
    if (nums.size() < 2) return out;

    constexpr int W = std::numeric_limits<T>::digits;

    std::vector<Node> trie;
    trie.emplace_back();  

    auto insert = [&](T x) {
      int node = 0;
      for (int b = W - 1; b >= 0; --b) {
        int bit = static_cast<int>((x >> b) & T{1});
        if (trie[node].next[bit] == -1) {
          trie[node].next[bit] = static_cast<int>(trie.size());
          trie.emplace_back();
        }
        node = trie[node].next[bit];
      }
      trie[node].value = x;
    };

    auto bestMatch = [&](T x) -> T {
      int node = 0;
      for (int b = W - 1; b >= 0; --b) {
        int bit = static_cast<int>((x >> b) & T{1});
        int want = bit ^ 1;
        if (trie[node].next[want] != -1)
          node = trie[node].next[want];
        else
          node = trie[node].next[bit];
      }
      return trie[node].value;
    };

    insert(nums[0]);

    T best_xor = 0;
    T best_a = 0, best_b = 0;

    for (size_t i = 1; i < nums.size(); ++i) {
      T x = nums[i];
      T y = bestMatch(x);
      T v = x ^ y;

      if (v > best_xor) {
        best_xor = v;
        best_a = x;
        best_b = y;
      }
      insert(x);
    }

    out.a = best_a;
    out.b = best_b;
    out.xor_value = best_xor;
    return out;
  }
};

#endif  // MAX_XOR_HPP
