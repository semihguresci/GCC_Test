#include "GTestCommon.hpp"
#include "RangeMap.hpp"

TEST(RangeMap, AddRangeTest) {
  RangeMap rm;
  rm.AddRange(10, 20);
  std::vector<std::pair<int, int>> range;
  range = {{10, 20}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(15, 25);
  range = {{10, 25}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(30, 40);
  range = {{10, 25}, {30, 40}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(5, 12);
  range = {{5, 25}, {30, 40}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(38, 45);
  range = {{5, 25}, {30, 45}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(25, 32);
  range = {{5, 45}};
  EXPECT_EQ(rm.GetRanges(), range);

  rm.AddRange(46, 50);
  range = {{5, 50}};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, RemoveRangeTest1) {
  RangeMap rm;
  rm.AddRange(10, 20);
  rm.RemoveRange(12, 18);
  std::vector<std::pair<int, int>> range = {{10, 12}, {18, 20}};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, RemoveRangeTest2) {
  RangeMap rm;
  std::vector<std::pair<int, int>> range;
  rm.AddRange(5, 25);
  rm.RemoveRange(10, 20);
  range = {{5, 10}, {20, 25}};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, RemoveRangeTest3) {
  RangeMap rm;
  std::vector<std::pair<int, int>> range;
  rm.AddRange(10, 20);
  rm.AddRange(25, 35);
  rm.RemoveRange(12, 30);
  range = {{10, 12}, {30, 35}};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, RemoveRangeTest4) {
  RangeMap rm;
  std::vector<std::pair<int, int>> range;
  rm.AddRange(10, 20);
  rm.RemoveRange(5, 25);
  range = {};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, RemoveRangeTest5) {
  RangeMap rm;
  std::vector<std::pair<int, int>> range;
  rm.AddRange(1, 5);
  rm.AddRange(6, 10);
  rm.AddRange(11, 15);
  rm.RemoveRange(3, 8);
  range = {{1, 3}, {8, 15}};
  EXPECT_EQ(rm.GetRanges(), range);
}

TEST(RangeMap, QueryRanges) {
  RangeMap rm;
  rm.AddRange(10, 20);

  EXPECT_TRUE(rm.QueryRange(12, 18));
  EXPECT_FALSE(rm.QueryRange(10, 20));

  EXPECT_FALSE(rm.QueryRange(5, 15));
  EXPECT_FALSE(rm.QueryRange(9, 20));
  EXPECT_FALSE(rm.QueryRange(9, 19));
  EXPECT_FALSE(rm.QueryRange(10, 21));

  rm.AddRange(25, 35);
  EXPECT_TRUE(rm.QueryRange(12, 18));
  EXPECT_TRUE(rm.QueryRange(27, 30));
  EXPECT_FALSE(rm.QueryRange(18, 27));
}

TEST(RangeMap, TestEquity) {
  RangeMap rm0;
  rm0.AddRange(25, 35);
  rm0.AddRange(10, 20);

  RangeMap rm1;
  rm1.AddRange(25, 35);
  rm1.AddRange(10, 20);

  EXPECT_EQ(rm0.GetRanges(), rm1.GetRanges());

  RangeMap rm2;
  rm2.AddRange(10, 20);
  rm2.AddRange(25, 35);

  EXPECT_EQ(rm1.GetRanges(), rm2.GetRanges());

  RangeMap rm3;
  std::vector<std::pair<int, int>> range;
  EXPECT_EQ(rm3.GetRanges(), range);

  EXPECT_NE(rm3.GetRanges(), rm2.GetRanges());
}

TEST(RangeMap, InvalidRange) {
  RangeMap rm;

  EXPECT_THROW(rm.AddRange(20, 10), std::invalid_argument);
  EXPECT_THROW(rm.RemoveRange(20, 10), std::invalid_argument);
  EXPECT_THROW(rm.QueryRange(20, 10), std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}