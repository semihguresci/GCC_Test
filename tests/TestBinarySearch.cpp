#include "BinarySearch.hpp"
#include "GTestCommon.hpp"

TEST(BinarySearch, BinarySearchTests) {
  {
    std::vector<int> nums = {};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 0);
  }
  {
    std::vector<int> nums = {5};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 5);
  }
  {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {0, 1, 0, 3, 2, 3};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    EXPECT_EQ(binary_search::LengthofLongestIncreasingSubsequence(nums), 6);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}