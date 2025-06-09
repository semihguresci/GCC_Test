#include "GTestCommon.hpp"
#include "MaximumSubarray.hpp"

using namespace MaximumSubarray;

TEST(MaxSubArrayTest, HandlesEmptyInputKadane) {
  std::vector<int> nums;
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), std::numeric_limits<int>::min());
}

TEST(MaxSubArrayTest, SingleElementKadane) {
  std::vector<int> nums = {5};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 5);
}

TEST(MaxSubArrayTest, AllPositiveNumbersKadane) {
  std::vector<int> nums = {1, 2, 3, 4};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 10);
}

TEST(MaxSubArrayTest, AllNegativeNumbersKadane) {
  std::vector<int> nums = {-1, -2, -3, -4};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), -1);
}

TEST(MaxSubArrayTest, MixedPositiveNegativeKadane) {
  std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 6);
}

TEST(MaxSubArrayTest, WithZeroKadane) {
  std::vector<int> nums = {-1, 0, -2};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 0);
}

TEST(MaxSubArrayTest, LargeArrayKadane) {
  std::vector<int> nums(1000, 1);
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 1000);
}

TEST(MaxSubArrayTest, SingleNegativeElementKadane) {
  std::vector<int> nums = {-10};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), -10);
}

TEST(MaxSubArrayTest, MaxAtBeginningKadane) {
  std::vector<int> nums = {10, -2, -3, 5};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 10);
}

TEST(MaxSubArrayTest, MaxAtEndKadane) {
  std::vector<int> nums = {1, -2, -3, 10};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 10);
}

TEST(MaxSubArrayTest, AllZerosKadane) {
  std::vector<int> nums = {0, 0, 0, 0};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), 0);
}

TEST(MaxSubArrayTest, LargeNegativeNumbersKadane) {
  std::vector<int> nums = {-1000000, -2000000, -3000000};
  EXPECT_EQ(MaxSubArraySumKadane<int>(nums), -1000000);
}

TEST(MaxSubArrayTest, LargePositiveNumbersKadane) {
  std::vector<int> nums = {1000000, 2000000, 3000000};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 6000000);
}

TEST(MaxSubArrayTest, HandlesEmptyInputModern) {
  std::vector<int> nums;
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), std::numeric_limits<int>::min());
}

TEST(MaxSubArrayTest, SingleElementModern) {
  std::vector<int> nums = {5};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 5);
}

TEST(MaxSubArrayTest, AllPositiveNumbersModern) {
  std::vector<int> nums = {1, 2, 3, 4};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 10);
}

TEST(MaxSubArrayTest, AllNegativeNumbersModern) {
  std::vector<int> nums = {-1, -2, -3, -4};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), -1);
}

TEST(MaxSubArrayTest, MixedPositiveNegativeModern) {
  std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 6);
}

TEST(MaxSubArrayTest, WithZeroModern) {
  std::vector<int> nums = {-1, 0, -2};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 0);
}

TEST(MaxSubArrayTest, LargeArrayModern) {
  std::vector<int> nums(1000, 1);
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 1000);
}

TEST(MaxSubArrayTest, SingleNegativeElementModern) {
  std::vector<int> nums = {-10};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), -10);
}

TEST(MaxSubArrayTest, MaxAtBeginningModern) {
  std::vector<int> nums = {10, -2, -3, 5};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 10);
}

TEST(MaxSubArrayTest, MaxAtEndModern) {
  std::vector<int> nums = {1, -2, -3, 10};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 10);
}

TEST(MaxSubArrayTest, AllZerosModern) {
  std::vector<int> nums = {0, 0, 0, 0};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 0);
}

TEST(MaxSubArrayTest, LargeNegativeNumbersModern) {
  std::vector<int> nums = {-1000000, -2000000, -3000000};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), -1000000);
}

TEST(MaxSubArrayTest, LargePositiveNumbersModern) {
  std::vector<int> nums = {1000000, 2000000, 3000000};
  EXPECT_EQ(MaxSubArraySumModern<int>(nums), 6000000);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}