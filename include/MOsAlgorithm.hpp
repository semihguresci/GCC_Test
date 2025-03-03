#ifndef MOsALGORITHM_H
#define MOsALGORITHM_H

#include <algorithm>
#include <cmath>
#include <span>
#include <unordered_map>
#include <vector>

struct MosQuery {
  int l, r;
};

class MosAlgorithm {
 private:
  std::size_t block_size;

 public:
  auto Process(std::span<int> arr, std::span<MosQuery> queries)
      -> std::vector<int> {
    size_t n = arr.size();

    if (n == 0) {
      return std::vector<int>(queries.size(), 0);
    }

    block_size = static_cast<std::size_t>(std::sqrt(n));

    for (const auto& query : queries) {
      if (query.l < 0 || query.r >= n || query.l > query.r) {
        throw std::out_of_range("Query range is out of bounds or invalid.");
      }
    }

    auto compare = [&](const MosQuery& a, const MosQuery& b) {
      if (a.l / block_size != b.l / block_size) {
        return a.l / block_size < b.l / block_size;
      }
      return a.r < b.r;
    };

    std::ranges::sort(queries, compare);

    std::size_t c_l = 0;
    std::size_t c_r = 0;
    std::size_t distinct_count = 0;
    std::unordered_map<int, int> freq;

    auto add = [&](int x) {
      if (++freq[x] == 1) {
        distinct_count++;
      }
    };

    auto remove = [&](int x) {
      if (--freq[x] == 0) {
        distinct_count--;
      }
    };

    add(arr[c_r]);
    std::vector<int> result(queries.size());
    for (std::size_t i = 0; i < queries.size(); ++i) {
      const auto& query = queries[i];
      while (c_l < query.l) {
        remove(arr[c_l++]);
      }
      while (c_l > query.l) {
        add(arr[--c_l]);
      }
      while (c_r < query.r) {
        add(arr[++c_r]);
      }
      while (c_r > query.r) {
        remove(arr[c_r--]);
      }
      result[i] = distinct_count;
    }
    return result;
  }
};

#endif  // !MOsALGORITHM_H
