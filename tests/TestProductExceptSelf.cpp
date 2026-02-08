#include "GTestCommon.hpp"
#include "ProductExceptSelf.hpp"

TEST(ProductExceptSelf, Sample) {
  ProductExceptSelf solver;
  std::vector<long long> input{1, 2, 3, 4, 5};
  std::vector<long long> expected{120, 60, 40, 30, 24};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, Sample2) {
  ProductExceptSelf solver;
  std::vector<long long> input{3, 2, 1};
  std::vector<long long> expected{2, 3, 6};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithZero) {
  ProductExceptSelf solver;
  std::vector<long long> input{1, 2, 0, 4};
  std::vector<long long> expected{0, 0, 8, 0};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithMultipleZeros) {
  ProductExceptSelf solver;
  std::vector<long long> input{1, 0, 3, 0};
  std::vector<long long> expected{0, 0, 0, 0};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithNegative) {
  ProductExceptSelf solver;
  std::vector<long long> input{-1, 2, -3, 4};
  std::vector<long long> expected{-24, 12, -8, 6};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithNegativeAndZero) {
  ProductExceptSelf solver;
  std::vector<long long> input{-1, 2, 0, 4};
  std::vector<long long> expected{0, 0, -8, 0};
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithOneElement) {
  ProductExceptSelf solver;
  std::vector<long long> input{42};
  std::vector<long long> expected{1};  
  EXPECT_EQ(solver.Solve(input), expected);
}

TEST(ProductExceptSelf, WithEmpty) {
  ProductExceptSelf solver;
  std::vector<long long> input{};
  std::vector<long long> expected{};
  EXPECT_EQ(solver.Solve(input), expected);
}