#include "GTestCommon.hpp"
#include "ValueRangeMap.hpp"


TEST(ValueRangeMap, BasicAddQuery) {
  ValueRangeMap rm;
  rm.Add(1, 3, "A");

  EXPECT_EQ(rm.Query(1), "A");
  EXPECT_EQ(rm.Query(2), "A");
  EXPECT_EQ(rm.Query(3), "A");

  EXPECT_EQ(rm.Query(0), "");
  EXPECT_EQ(rm.Query(4), "");

  auto ranges = rm.GetRanges();
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(std::get<0>(ranges[0]), 1);
  EXPECT_EQ(std::get<1>(ranges[0]), 3);
  EXPECT_EQ(std::get<2>(ranges[0]), "A");
}

TEST(ValueRangeMap, OverlappingAdd) {
  ValueRangeMap rm;
  rm.Add(1, 3, "A");
  rm.Add(2, 5, "B");  

  auto ranges = rm.GetRanges();
  ASSERT_EQ(ranges.size(), 2u);

  EXPECT_EQ(std::get<0>(ranges[0]), 1);
  EXPECT_EQ(std::get<1>(ranges[0]), 1);
  EXPECT_EQ(std::get<2>(ranges[0]), "A");

  EXPECT_EQ(std::get<0>(ranges[1]), 2);
  EXPECT_EQ(std::get<1>(ranges[1]), 5);
  EXPECT_EQ(std::get<2>(ranges[1]), "B");

  EXPECT_EQ(rm.Query(1), "A");
  EXPECT_EQ(rm.Query(2), "B");
  EXPECT_EQ(rm.Query(4), "B");
  EXPECT_EQ(rm.Query(5), "B");
  EXPECT_EQ(rm.Query(6), "");
}

TEST(ValueRangeMap, AdjacentMerging) {
  ValueRangeMap rm;
  rm.Add(1, 3, "A");
  rm.Add(4, 5, "A");  

  auto ranges = rm.GetRanges();
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(std::get<0>(ranges[0]), 1);
  EXPECT_EQ(std::get<1>(ranges[0]), 5);
  EXPECT_EQ(std::get<2>(ranges[0]), "A");

  EXPECT_EQ(rm.Query(1), "A");
  EXPECT_EQ(rm.Query(5), "A");
  EXPECT_EQ(rm.Query(6), "");
}

TEST(ValueRangeMap, QueryRangeTest) {
  ValueRangeMap rm;
  rm.Add(1, 5, "A");
  rm.Add(10, 12, "B");

  auto [covers1, val1] = rm.QueryRange(1, 5);
  EXPECT_TRUE(covers1);
  EXPECT_EQ(val1, "A");

  auto [covers2, val2] = rm.QueryRange(2, 4);
  EXPECT_TRUE(covers2);
  EXPECT_EQ(val2, "A");

  auto [covers3, val3] = rm.QueryRange(6, 10);
  EXPECT_FALSE(covers3);
  EXPECT_EQ(val3, "");

  auto [covers4, val4] = rm.QueryRange(10, 12);
  EXPECT_TRUE(covers4);
  EXPECT_EQ(val4, "B");
}

TEST(ValueRangeMap, UpdateTest) {
  ValueRangeMap rm;
  rm.Add(1, 3, "A");
  rm.Add(4, 6, "A");

  rm.Update(3, 5, "B");  

  auto ranges = rm.GetRanges();
  ASSERT_EQ(ranges.size(), 3u);

  EXPECT_EQ(std::get<0>(ranges[0]), 1);
  EXPECT_EQ(std::get<1>(ranges[0]), 2);
  EXPECT_EQ(std::get<2>(ranges[0]), "A");

  EXPECT_EQ(std::get<0>(ranges[1]), 3);
  EXPECT_EQ(std::get<1>(ranges[1]), 5);
  EXPECT_EQ(std::get<2>(ranges[1]), "B");

  EXPECT_EQ(std::get<0>(ranges[2]), 6);
  EXPECT_EQ(std::get<1>(ranges[2]), 6);
  EXPECT_EQ(std::get<2>(ranges[2]), "A");
}

TEST(ValueRangeMap, EqualityOperator) {
  ValueRangeMap rm1;
  rm1.Add(1, 3, "A");
  rm1.Add(4, 6, "A");  
  rm1.Update(3, 5, "B");

  ValueRangeMap rm2;
  rm2.Add(1, 2, "A");
  rm2.Add(3, 5, "B");
  rm2.Add(6, 6, "A");

  EXPECT_EQ(rm1, rm2);

  rm2.Update(6, 6, "X");
  EXPECT_NE(rm1, rm2);
}

TEST(ValueRangeMap, InvalidRange) {
  ValueRangeMap rm;

  EXPECT_THROW(rm.Add(5, 4, "Bad"), std::invalid_argument);
  EXPECT_THROW(rm.Update(10, 9, "Bad"), std::invalid_argument);
}

TEST(ValueRangeMap, RemoveEmptyMap) {
  ValueRangeMap rm;
  rm.Remove(5, 10);
  auto intervals = rm.GetRanges();
  EXPECT_TRUE(intervals.empty());
}

TEST(ValueRangeMap, RemovePartialCoverage) {
  ValueRangeMap rm;
  rm.Add(1, 5, "A");

  rm.Remove(3, 4);
  auto intervals = rm.GetRanges();
  ASSERT_EQ(intervals.size(), 2u);

  EXPECT_EQ(std::get<0>(intervals[0]), 1);
  EXPECT_EQ(std::get<1>(intervals[0]), 2);
  EXPECT_EQ(std::get<2>(intervals[0]), "A");

  EXPECT_EQ(std::get<0>(intervals[1]), 5);
  EXPECT_EQ(std::get<1>(intervals[1]), 5);
  EXPECT_EQ(std::get<2>(intervals[1]), "A");
}

TEST(ValueRangeMap, RemoveFrontOverlap) {
  ValueRangeMap rm;
  rm.Add(1, 5, "A");
  rm.Remove(1, 2);

  auto intervals = rm.GetRanges();
  ASSERT_EQ(intervals.size(), 1u);

  EXPECT_EQ(std::get<0>(intervals[0]), 3);
  EXPECT_EQ(std::get<1>(intervals[0]), 5);
  EXPECT_EQ(std::get<2>(intervals[0]), "A");
}

TEST(ValueRangeMap, RemoveEndOverlap) {
  ValueRangeMap rm;
  rm.Add(1, 5, "A");
  rm.Remove(4, 5);

  auto intervals = rm.GetRanges();
  ASSERT_EQ(intervals.size(), 1u);

  EXPECT_EQ(std::get<0>(intervals[0]), 1);
  EXPECT_EQ(std::get<1>(intervals[0]), 3);
  EXPECT_EQ(std::get<2>(intervals[0]), "A");
}

TEST(ValueRangeMap, RemoveEntireInterval) {
  ValueRangeMap rm;
  rm.Add(1, 5, "A");
  rm.Remove(1, 5);

  auto intervals = rm.GetRanges();
  EXPECT_TRUE(intervals.empty());
}

TEST(ValueRangeMap, RemoveMultipleIntervals) {
  ValueRangeMap rm;
  rm.Add(1, 3, "A");
  rm.Add(4, 6, "B");

  rm.Remove(2, 5);

  auto intervals = rm.GetRanges();
  ASSERT_EQ(intervals.size(), 2u);

  EXPECT_EQ(std::get<0>(intervals[0]), 1);
  EXPECT_EQ(std::get<1>(intervals[0]), 1);
  EXPECT_EQ(std::get<2>(intervals[0]), "A");

  EXPECT_EQ(std::get<0>(intervals[1]), 6);
  EXPECT_EQ(std::get<1>(intervals[1]), 6);
  EXPECT_EQ(std::get<2>(intervals[1]), "B");
}

TEST(ValueRangeMap, RemoveCoversAll) {
  ValueRangeMap rm;
  rm.Add(1, 2, "A");
  rm.Add(3, 5, "B");
  rm.Add(6, 8, "C");

  rm.Remove(1, 10);

  auto intervals = rm.GetRanges();
  EXPECT_TRUE(intervals.empty());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}