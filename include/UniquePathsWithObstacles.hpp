#ifndef UNIQUEPATHSWITHOBSTACLES_HPP
#define UNIQUEPATHSWITHOBSTACLES_HPP

#include <vector>

auto UniquePathsWithObstacles(const std::vector<std::vector<int>>& grid)
    -> int {
  std::size_t m = grid.size();

  if (m == 0) return 0;

  std::size_t n = grid[0].size();
  std::vector<int> dp(n, 0);

  dp[0] = (grid[0][0] == 0) ? 1 : 0;

  for (std::size_t i = 0; i < m; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      if (grid[i][j] == 1) {
        dp[j] = 0;
      } else if (j > 0) {
        dp[j] += dp[j - 1];
      }
    }
  }
  return dp[n - 1];
}

#endif  // UNIQUEPATHSWITHOBSTACLES_HPP
