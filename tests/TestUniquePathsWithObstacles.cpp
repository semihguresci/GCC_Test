#include "GTestCommon.hpp"
#include "UniquePathsWithObstacles.hpp"

TEST(UniquePathsWithObstacles, Empty) {
  std::vector<std::vector<int>> grid = {};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, SingleCell) {
  std::vector<std::vector<int>> grid = {{0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 1);
}

TEST(UniquePathsWithObstacles, SingleObstacle) {
  std::vector<std::vector<int>> grid = {{1}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, TwoXTwoGrid) {
  std::vector<std::vector<int>> grid = {{0, 0}, {0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 2);
}

TEST(UniquePathsWithObstacles, TwoXTwoGridWithObstacle) {
  std::vector<std::vector<int>> grid = {{0, 1}, {0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 1);
}

TEST(UniquePathsWithObstacles, TwoXTwoGridWithStartObstacle) {
  std::vector<std::vector<int>> grid = {{1, 0}, {0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, TwoXTwoGridWithEndObstacle) {
  std::vector<std::vector<int>> grid = {{0, 0}, {0, 1}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, ThreeXThreeGrid) {
  std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 6);
}

TEST(UniquePathsWithObstacles, ThreeXThreeGridWithStartObstacle) {
  std::vector<std::vector<int>> grid = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, ThreeXThreeGridWithMiddleObstacle) {
  std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 2);
}

TEST(UniquePathsWithObstacles, ThreeXThreeGridWithEndObstacle) {
  std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 0);
}

TEST(UniquePathsWithObstacles, TenXTenGridWithEndObstacle) {
  std::vector<std::vector<int>> grid(10, std::vector<int>(10, 0));
  auto result = UniquePathsWithObstacles(grid);
  EXPECT_EQ(result, 48620);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}