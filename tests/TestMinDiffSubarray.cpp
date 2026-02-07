#include "GTestCommon.hpp"
#include "MinDiffSubarray.hpp"

TEST(MinDiffSubarray, BasicTest) {
  auto arr = std::vector<int>{5, 10, 15, 20, 25};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 5);
  EXPECT_EQ(result.sum1 + result.sum2, 75);
}
TEST(MinDiffSubarray, SingleElement) {
  auto arr = std::vector<int>{10};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 10);
  EXPECT_EQ(result.sum1 + result.sum2, 10);
}
TEST(MinDiffSubarray, TwoElements) {
  auto arr = std::vector<int>{10, 20};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 10);
  EXPECT_EQ(result.sum1 + result.sum2, 30);
}
TEST(MinDiffSubarray, EmptyArray) {
  auto arr = std::vector<int>{};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 0);
  EXPECT_EQ(result.sum1 + result.sum2, 0);
}
TEST(MinDiffSubarray, LargeNumbers) {
  auto arr = std::vector<int>{10000, 20000, 30000, 40000, 50000};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 10000);
  EXPECT_EQ(result.sum1 + result.sum2, 150000);
}
TEST(MinDiffSubarray, AllSameElements) {
  auto arr = std::vector<int>{10, 10, 10, 10};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 0);
  EXPECT_EQ(result.sum1 + result.sum2, 40);
}
TEST(MinDiffSubarray, OddNumberOfElements) {
  auto arr = std::vector<int>{1, 2, 3, 4, 5};
  MinDiffSubarray mds;
  auto result = mds.FindMinDiffSubarray(arr);
  EXPECT_EQ(result.diff, 1);
  EXPECT_EQ(result.sum1 + result.sum2, 15);
}
TEST(MinDiffSubarray, LargeArray) {
  MinDiffSubarray mds;
  std::vector<int> largeArray(1000);
  for (int i = 0; i < 1000; ++i) {
	largeArray[i] = i + 1;
  }
  auto result = mds.FindMinDiffSubarray(largeArray);
  EXPECT_EQ(result.diff, 0);
  EXPECT_EQ(result.sum1 + result.sum2, 500500);
}
TEST(MinDiffSubarray, MemorySafety) {
  MinDiffSubarray mds;
  std::vector<int> arr = {1, 2, 3, 4, 5};
  auto result = mds.FindMinDiffSubarray(arr);
  SUCCEED();  
			
}