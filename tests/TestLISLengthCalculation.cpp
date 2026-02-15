#include <vector>
#include <limits>

#include "LISLengthCalculation.hpp"
#include "GTestCommon.hpp"


static bool IsStrictlyIncreasing(const std::vector<int>& v) {
  for (std::size_t i = 1; i < v.size(); ++i) {
    if (!(v[i - 1] < v[i])) return false;
  }
  return true;
}

static bool IsSubsequence(const std::vector<int>& a,
                          const std::vector<int>& sub) {
  std::size_t j = 0;
  for (std::size_t i = 0; i < a.size() && j < sub.size(); ++i) {
    if (a[i] == sub[j]) ++j;
  }
  return j == sub.size();
}


static bool IsNonDecreasing(const std::vector<int>& v) {
  for (std::size_t i = 1; i < v.size(); ++i) {
    if (v[i - 1] > v[i]) return false;
  }
  return true;
}

TEST(LIS, GivenExample) {
  std::vector<int> a = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 6u);
}

TEST(LIS, Empty) {
  std::vector<int> a;
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 0u);
}

TEST(LIS, Single) {
  std::vector<int> a = {42};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 1u);
}

TEST(LIS, StrictlyIncreasing) {
  std::vector<int> a = {1, 2, 3, 4, 5};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 5u);
}

TEST(LIS, StrictlyDecreasing) {
  std::vector<int> a = {5, 4, 3, 2, 1};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 1u);
}

TEST(LIS, WithDuplicatesStrictlyIncreasingMeansNoEquals) {
  std::vector<int> a = {2, 2, 2, 2};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 1u);
}

TEST(LIS, MixedNegatives) {
  std::vector<int> a = {-1, -2, -3, 0, 1};
  // One LIS: -3, 0, 1
  EXPECT_EQ(LongestIncreasingSubsequence::Length<int>(a), 3u);
}

TEST(LIS, LargeValues) {
  using ll = long long;
  std::vector<ll> a = {std::numeric_limits<ll>::min(), 0, 1, 2,
                       std::numeric_limits<ll>::max()};
  EXPECT_EQ(LongestIncreasingSubsequence::Length<ll>(a), 5u);
}


TEST(LNDS, AllowsEquals) {
  std::vector<int> a = {2, 2, 2, 2};
  auto seq = LongestNonDecreasingSubsequence::Sequence<int>(a);

  EXPECT_EQ(seq.size(), 4u);
  EXPECT_TRUE(IsNonDecreasing(seq));
  EXPECT_TRUE(IsSubsequence(a, seq));
}

TEST(LNDS, MixedWithDuplicates) {
  std::vector<int> a = {3, 1, 2, 2, 2, 1, 4};
  // One LNDS: 1,2,2,2,4 (length 5)
  auto seq = LongestNonDecreasingSubsequence::Sequence<int>(a);

  EXPECT_EQ(seq.size(), 5u);
  EXPECT_TRUE(IsNonDecreasing(seq));
  EXPECT_TRUE(IsSubsequence(a, seq));
}

TEST(LNDS, Empty) {
  std::vector<int> a;
  auto seq = LongestNonDecreasingSubsequence::Sequence<int>(a);
  EXPECT_TRUE(seq.empty());
}



TEST(LISSeq, GivenExample) {
  std::vector<int> a = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

  auto lis = LongestIncreasingSubsequence::Sequence<int>(a);

  EXPECT_EQ(lis.size(), 6u);
  EXPECT_TRUE(IsStrictlyIncreasing(lis));
  EXPECT_TRUE(IsSubsequence(a, lis));

  // One valid LIS is {0,2,6,9,11,15}, but there are others.
}

TEST(LISSeq, Empty) {
  std::vector<int> a;
  auto lis = LongestIncreasingSubsequence::Sequence<int>(a);
  EXPECT_TRUE(lis.empty());
}

TEST(LISSeq, AllEqual) {
  std::vector<int> a = {2, 2, 2, 2};
  auto lis = LongestIncreasingSubsequence::Sequence<int>(a);
  EXPECT_EQ(lis.size(), 1u);
  EXPECT_TRUE(IsStrictlyIncreasing(lis));
  EXPECT_TRUE(IsSubsequence(a, lis));
}

TEST(LISSeq, Decreasing) {
  std::vector<int> a = {5, 4, 3, 2, 1};
  auto lis = LongestIncreasingSubsequence::Sequence<int>(a);
  EXPECT_EQ(lis.size(), 1u);
  EXPECT_TRUE(IsStrictlyIncreasing(lis));
  EXPECT_TRUE(IsSubsequence(a, lis));
}

TEST(LISSeq, Mixed) {
  std::vector<int> a = {3, 1, 2, 1, 8, 5, 6};
  auto lis = LongestIncreasingSubsequence::Sequence<int>(a);

  EXPECT_EQ(lis.size(), 4u);  // e.g. 1,2,5,6
  EXPECT_TRUE(IsStrictlyIncreasing(lis));
  EXPECT_TRUE(IsSubsequence(a, lis));
}