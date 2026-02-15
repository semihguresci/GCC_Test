#include "GTestCommon.hpp"
#include "LongestDistinctSubarray.hpp"

TEST(LongestDistinctSubarrayLen, Empty) {
  std::vector<int> a;
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 0u);
}

TEST(LongestDistinctSubarrayLen, SingleElement) {
  std::vector<int> a{42};
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 1u);
}

TEST(LongestDistinctSubarrayLen, AllUnique) {
  std::vector<int> a{1, 2, 3, 4, 5};
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 5u);
}

TEST(LongestDistinctSubarrayLen, AllSame) {
  std::vector<int> a{7, 7, 7, 7};
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 1u);
}

TEST(LongestDistinctSubarrayLen, AdjacentDuplicate) {
  std::vector<int> a{1, 2, 2, 3};
  // best is [1,2] or [2,3]
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 2u);
}

TEST(LongestDistinctSubarrayLen, NonAdjacentDuplicateForcesLeftJump) {
  std::vector<int> a{1, 2, 3, 1, 4};
  // when seeing 1 again, left jumps; best is [2,3,1,4] length 4
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 4u);
}

TEST(LongestDistinctSubarrayLen, RepeatedPattern) {
  std::vector<int> a{1, 2, 3, 1, 2, 3};
  // best is 3: [1,2,3]
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 3u);
}

TEST(LongestDistinctSubarrayLen, ExampleFromPrompt) {
  std::vector<int> a{5, 1, 3, 5, 2, 3, 4, 1};
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 5u);
}

TEST(LongestDistinctSubarrayLen, WorksWithStrings) {
  std::vector<std::string> a{"a", "b", "c", "a", "d", "e"};
  // best is ["b","c","a","d","e"] length 5
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 5u);
}

TEST(LongestDistinctSubarrayLen, LargeDuplicateAtEnd) {
  std::vector<int> a{0, 1, 2, 3, 4, 0};
  // best is 5: [0,1,2,3,4]
  EXPECT_EQ(LongestDistinctSubarray::Get(a), 5u);
}