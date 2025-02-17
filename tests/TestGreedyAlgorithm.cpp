#include "GTestCommon.hpp"
#include "GreedyAlgorithm.hpp"

TEST(GreedyAlgorithm, Empty) {
  std::vector<TimeInterval> nums = {};
  EXPECT_EQ(MinMeetingRoom(nums), 0);
}

TEST(GreedyAlgorithm, One) {
  std::vector<TimeInterval> nums = {{0, 30}};
  EXPECT_EQ(MinMeetingRoom(nums), 1);
}

TEST(GreedyAlgorithm, Two) {
  std::vector<TimeInterval> nums = {{7, 10}, {2, 4}};
  EXPECT_EQ(MinMeetingRoom(nums), 1);
}

TEST(GreedyAlgorithm, Three) {
  std::vector<TimeInterval> nums = {{0, 30}, {5, 10}, {15, 20}};
  EXPECT_EQ(MinMeetingRoom(nums), 2);
}

TEST(GreedyAlgorithm, Four) {
  std::vector<TimeInterval> nums = {{0, 30}, {5, 10}, {15, 20}, {1, 5}};
  EXPECT_EQ(MinMeetingRoom(nums), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}