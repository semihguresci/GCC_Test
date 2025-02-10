#include "GTestCommon.hpp"
#include "SearchRotatedArray.hpp"

TEST(SearchRotatedArray, EmptyInteger) {
  std::vector<int> nums = {};

  EXPECT_FALSE(SearchRotatedArray(nums, 2).has_value());
}

TEST(SearchRotatedArray, SingleInteger) {
  std::vector<int> nums = {1};

  EXPECT_EQ(SearchRotatedArray(nums, 1).value(), 0);

  EXPECT_FALSE(SearchRotatedArray(nums, 2).has_value());
}

TEST(SearchRotatedArray, SortedIntegerVector) {
  std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(SearchRotatedArray(nums, 1).value(), 0);
  EXPECT_EQ(SearchRotatedArray(nums, 3).value(), 2);
  EXPECT_EQ(SearchRotatedArray(nums, 7).value(), 6);

  EXPECT_FALSE(SearchRotatedArray(nums, 8).has_value());
}

TEST(SearchRotatedArray, SameIntegerVector) {
  std::vector<int> nums = {2, 2, 2, 2, 2, 2, 2};

  EXPECT_EQ(SearchRotatedArray(nums, 2).value(), 0);

  EXPECT_FALSE(SearchRotatedArray(nums, 8).has_value());
}

TEST(SearchRotatedArray, RotatedIntegerVector) {
  std::vector<int> nums = {4, 5, 6, 7, 1, 2, 3};

  EXPECT_EQ(SearchRotatedArray(nums, 2).value(), 5);
  EXPECT_EQ(SearchRotatedArray(nums, 7).value(), 3);
  EXPECT_EQ(SearchRotatedArray(nums, 4).value(), 0);

  EXPECT_FALSE(SearchRotatedArray(nums, 8).has_value());
}

TEST(SearchRotatedArray, RotatedFloatingVector) {
  std::vector<double> nums = {4.5, 5.5, 6.5, 7.5, 1.5, 2.5, 3.5};

  EXPECT_EQ(SearchRotatedArray(nums, 2.5).value(), 5);
  EXPECT_EQ(SearchRotatedArray(nums, 7.5).value(), 3);
  EXPECT_EQ(SearchRotatedArray(nums, 4.5).value(), 0);

  EXPECT_FALSE(SearchRotatedArray(nums, 8.5).has_value());
}

TEST(SearchRotatedArray, RotatedDublicateValues) {
  std::vector<int> nums = {2, 5, 6, 0, 0, 1, 2};

  EXPECT_EQ(SearchRotatedArray(nums, 0).value(), 3);
  EXPECT_EQ(SearchRotatedArray(nums, 2).value(), 0);

  EXPECT_FALSE(SearchRotatedArray(nums, 3).has_value());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}