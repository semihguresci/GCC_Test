#include "BinarySearch.hpp"
#include "GTestCommon.hpp"

using namespace BinarySearch;

TEST(BinarySearch, BinarySearchTests) {
  {
    std::vector<int> nums = {};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 0);
  }
  {
    std::vector<int> nums = {5};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 5);
  }
  {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {0, 1, 0, 3, 2, 3};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 4);
  }
  {
    std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 1);
  }
  {
    std::vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    EXPECT_EQ(BinarySearch::LengthofLongestIncreasingSubsequence(nums), 6);
  }
}

TEST(BinarySearchTest, EmptyArray) {
  std::vector<int> nums;
  EXPECT_EQ(Search(std::span<int>(nums), 5), -1);
}

TEST(BinarySearchTest, SingleElementFound) {
  std::vector<int> nums{5};
  EXPECT_EQ(Search(std::span<int>(nums), 5), 0);
}

TEST(BinarySearchTest, SingleElementNotFound) {
  std::vector<int> nums{3};
  EXPECT_EQ(Search(std::span<int>(nums), 5), -1);
}

TEST(BinarySearchTest, OddLengthFound) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 5), 2);
}

TEST(BinarySearchTest, EvenLengthFound) {
  std::vector<int> nums{1, 3, 5, 7, 9, 11};
  EXPECT_EQ(Search(std::span<int>(nums), 7), 3);
}

TEST(BinarySearchTest, FirstElementFound) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 1), 0);
}

TEST(BinarySearchTest, LastElementFound) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 9), 4);
}

TEST(BinarySearchTest, NotFoundInMiddle) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 4), -1);
}

TEST(BinarySearchTest, NotFoundAboveRange) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 10), -1);
}

TEST(BinarySearchTest, NotFoundBelowRange) {
  std::vector<int> nums{1, 3, 5, 7, 9};
  EXPECT_EQ(Search(std::span<int>(nums), 0), -1);
}

TEST(BinarySearchTest, WithDuplicates) {
  std::vector<int> nums{1, 3, 5, 5, 5, 7, 9};
  int result = Search(std::span<int>(nums), 5);
  EXPECT_TRUE(result == 2 || result == 3 || result == 4);
}

TEST(BinarySearchTest, StringType) {
  std::vector<std::string> words{"apple", "banana", "cherry", "date"};
  EXPECT_EQ(Search(std::span<std::string>(words), std::string("cherry")), 2);
}

TEST(BinarySearchTest, FloatType) {
  std::vector<float> nums{1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  EXPECT_EQ(Search(std::span<float>(nums), 4.4f), 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}