/*
 Given a 2D matrix of characters and a target word, write a function that
 returns whether the word can be found in the matrix by going left-to-right, or
 up-to-down. For example, given the following matrix: [['F', 'A', 'C', 'I'],
 ['O', 'B', 'Q', 'P'], ['A', 'N', 'O', 'B'], ['M', 'A', 'S', 'S']] and the
 target word 'FOAM', you should return true, since it's the leftmost column.
 Similarly, given the target word 'MASS', you should return true, since it's the
 last row.
*/

#ifndef ROW_COL_WORD_SEARCH_HPP
#define ROW_COL_WORD_SEARCH_HPP
#include <string>
#include <vector>
class RowColWordSearch {
 public:
  static bool Exists(const std::vector<std::vector<char>>& grid,
                     const std::string& word) {
    if (word.empty()) return true;
    const int R = static_cast<int>(grid.size());
    if (R == 0) return false;
    const int C = static_cast<int>(grid[0].size());
    if (C == 0) return false;

    // Optional: validate rectangular grid
    for (const auto& row : grid) {
      if (static_cast<int>(row.size()) != C) return false;
    }

    const int L = static_cast<int>(word.size());

    // Check each row (left-to-right)
    for (int r = 0; r < R; ++r) {
      for (int start = 0; start + L <= C; ++start) {
        int k = 0;
        while (k < L && grid[r][start + k] == word[k]) ++k;
        if (k == L) return true;
      }
    }

    // Check each column (top-to-down)
    for (int c = 0; c < C; ++c) {
      for (int start = 0; start + L <= R; ++start) {
        int k = 0;
        while (k < L && grid[start + k][c] == word[k]) ++k;
        if (k == L) return true;
      }
    }
    return false;
  }
};

#endif  // !ROW_COL_WORD_SEARCH_HPP