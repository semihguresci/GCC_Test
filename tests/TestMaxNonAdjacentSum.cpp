#include "MaxNonAdjacentSum.hpp"
#include "GTestCommon.hpp"

TEST(MaxNonAdjacentSum, EmptyVector) {
  std::vector<int> nums = {};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, 0);
}

TEST(MaxNonAdjacentSum, TwoElements) {
  std::vector<int> nums = {3, 2};
  MaxNonAdjacentSum solver;
  EXPECT_EQ(solver.MaxSum(nums), 3);
}

TEST(MaxNonAdjacentSum, OneVector) {
  std::vector<int> nums = {100};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, 100);
}

TEST(MaxNonAdjacentSum, MixedNumbers) {
  std::vector<int> nums = {3, 2, 7, 10};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, 13);  // 3 + 10
}

TEST(MaxNonAdjacentSum, NegativeNumbers) {
  std::vector<int> nums = {-1, -2, -3, -4};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, -1);  // Choose the least negative number
}

TEST(MaxNonAdjacentSum, AllNegative) {
  std::vector<int> nums = {-10, -5, -2, -1};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, -1);  // Choose the least negative number
}

TEST(MaxNonAdjacentSum, LargeNumbers) {
  std::vector<int> nums = {1000, 2000, 3000, 4000, 5000};
  MaxNonAdjacentSum solver;
  auto result = solver.MaxSum(nums);
  EXPECT_EQ(result, 9000);  // 1000 + 3000 + 5000
}
