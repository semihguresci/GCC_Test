#include <vector>

#include "DynamicProgramming.hpp"
#include "GTestCommon.hpp"

TEST(ClimbStairs, Test) {
  EXPECT_EQ(dp::ClimbStairs(0), 1);
  EXPECT_EQ(dp::ClimbStairs(1), 1);
  EXPECT_EQ(dp::ClimbStairs(2), 2);
  EXPECT_EQ(dp::ClimbStairs(3), 3);
  EXPECT_EQ(dp::ClimbStairs(4), 5);
  EXPECT_EQ(dp::ClimbStairs(5), 8);
  EXPECT_EQ(dp::ClimbStairs(6), 13);
  EXPECT_THROW(dp::ClimbStairs(-1), std::invalid_argument);
  EXPECT_THROW(dp::ClimbStairs(-5), std::invalid_argument);
}

TEST(MaxSubarray, Test) {
  {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto [max_sum, start_idx, end_idx] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 6);
    EXPECT_EQ(start_idx, 3);
    EXPECT_EQ(end_idx, 6);
  }
  {
    std::vector<int> nums = {1};
    auto [max_sum, start_idx, end_idx] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 1);
    EXPECT_EQ(start_idx, 0);
    EXPECT_EQ(end_idx, 0);
  }
  {
    std::vector<int> nums = {-2, -3, -1, -5};
    auto [max_sum, start_idx, end_idx] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, -1);
    EXPECT_EQ(start_idx, 2);
    EXPECT_EQ(end_idx, 2);
  }
  {
    std::vector<int> nums = {5};
    auto [max_sum, start_idx, end_idx] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 5);
    EXPECT_EQ(start_idx, 0);
    EXPECT_EQ(end_idx, 0);
  }
  {
    std::vector<int> nums = {};
    auto [max_sum, start_idx, end_idx] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 0);
    EXPECT_EQ(start_idx, 0);
    EXPECT_EQ(end_idx, 0);
  }

  {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto [max_sum, start, end] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 15);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 4);
  }

  {
    std::vector<int> nums = {1, -2, 3, -4, 5};
    auto [max_sum, start, end] = dp::MaxSubarray(nums);
    EXPECT_EQ(max_sum, 5);
    EXPECT_EQ(start, 4);
    EXPECT_EQ(end, 4);
  }
}

TEST(CoinChange, Test) {
  {
    std::vector<int> coins = {2};
    int amount = 3;
    EXPECT_EQ(dp::CoinChange(coins, amount), -1);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    EXPECT_EQ(dp::CoinChange(coins, amount), 3);
  }
  {
    std::vector<int> coins = {1};
    int amount = 0;
    EXPECT_EQ(dp::CoinChange(coins, amount), 0);
  }
  {
    std::vector<int> coins = {1};
    int amount = 1;
    EXPECT_EQ(dp::CoinChange(coins, amount), 1);
  }
  {
    std::vector<int> coins = {1};
    int amount = 2;
    EXPECT_EQ(dp::CoinChange(coins, amount), 2);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 100;
    EXPECT_EQ(dp::CoinChange(coins, amount), 20);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 1000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 200);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 10000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 2000);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 100000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 20000);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 1000000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 200000);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 10000000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 2000000);
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 100000000;
    EXPECT_EQ(dp::CoinChange(coins, amount), 20000000);
  }
}

TEST(LengthofLongestIncreasingSubsequence, Test) {
  {
    std::vector<int> nums = {};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 0);
  }
  {
    std::vector<int> nums = {5};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 5);
  }
  {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {0, 1, 0, 3, 2, 3};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    EXPECT_EQ(dp::LengthofLongestIncreasingSubsequence(nums), 6);
  }
}

TEST(Knapsack, Test) {
  {
    std::vector<int> values = {60, 100, 120};
    std::vector<int> weights = {10, 20, 30};
    int capacity = 50;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 220);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 4;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 3);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 5;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 4);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 6;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 5);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 7;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 5);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 8;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 5);
  }
  {
    std::vector<int> values = {1, 2, 3};
    std::vector<int> weights = {4, 5, 1};
    int capacity = 9;
    EXPECT_EQ(dp::Knapsack01Problem(capacity, weights, values), 5);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}