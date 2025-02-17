#ifndef NQUEENPROBLEM_HPP
#define NQUEENPROBLEM_HPP

#include <vector>

class NQueensSolver {
 public:
  NQueensSolver(std::uint32_t n) : n_{n} {}

  auto Solve() -> std::uint64_t {
    std::vector<bool> cols(n_, false);
    std::vector<bool> diag1(2 * n_ - 1, false);
    std::vector<bool> diag2(2 * n_ - 1, false);

    Backtrack(0, cols, diag1, diag2);
    return solution_count;
  }

 private:
  std::uint32_t n_{0};
  std::uint64_t solution_count{0};

  void Backtrack(std::uint32_t row, std::vector<bool>& cols,
                 std::vector<bool>& diag1, std::vector<bool> diag2) {
    if (row == n_) {
      ++solution_count;
      return;
    }
    for (std::uint32_t col = 0; col < n_; ++col) {
      if (!cols[col] && !diag1[row + col] && !diag2[row - col + n_ - 1]) {
        cols[col] = true;
        diag1[row + col] = true;
        diag2[row - col + n_ - 1] = true;

        Backtrack(row + 1, cols, diag1, diag2);

        cols[col] = false;
        diag1[row + col] = false;
        diag2[row - col + n_ - 1] = false;
      }
    }
  }
};

#endif  // NQUEENPROBLEM_HPP