#include "GTestCommon.hpp"
#include "GreedyAlgorithm.hpp"

TEST(SearchRotatedArray, Empty) {
  std::vector<TimeInterval> nums = {};
  EXPECT_EQ(MinMeetingRoom(nums), 0);
}

TEST(SearchRotatedArray, One) {
  std::vector<TimeInterval> nums = {{0, 30}};
  EXPECT_EQ(MinMeetingRoom(nums), 1);
}

TEST(SearchRotatedArray, Two) {
  std::vector<TimeInterval> nums = {{7, 10}, {2, 4}};
  EXPECT_EQ(MinMeetingRoom(nums), 1);
}

TEST(SearchRotatedArray, Three) {
  std::vector<TimeInterval> nums = {{0, 30}, {5, 10}, {15, 20}};
  EXPECT_EQ(MinMeetingRoom(nums), 2);
}

TEST(SearchRotatedArray, Four) {
  std::vector<TimeInterval> nums = {{0, 30}, {5, 10}, {15, 20}, {1, 5}};
  EXPECT_EQ(MinMeetingRoom(nums), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}