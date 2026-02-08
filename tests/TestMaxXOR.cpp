#include "GTestCommon.hpp"
#include "MaxXOR.hpp"

static uint32_t BruteMaxXorTwosComplement(const std::vector<int>& nums) {
  uint32_t best = 0;
  for (size_t i = 0; i < nums.size(); ++i) {
    for (size_t j = i + 1; j < nums.size(); ++j) {
      uint32_t a = static_cast<uint32_t>(nums[i]);
      uint32_t b = static_cast<uint32_t>(nums[j]);
      best = std::max(best, a ^ b);
    }
  }
  return best;
}

static unsigned long BruteMaxXorTwosComplement(
    const std::vector<unsigned long>& nums) {
  unsigned long best = 0UL;
  for (size_t i = 0; i < nums.size(); ++i)
    for (size_t j = i + 1; j < nums.size(); ++j)
      best = std::max(best, nums[i] ^ nums[j]);
  return best;
}



TEST(MaxXOR, MaxXORTests) {
  std::vector<unsigned long> nums = {3UL, 10UL, 5UL, 25UL, 2UL, 8UL};

  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, 28UL);  

  EXPECT_TRUE((r.a == 5UL && r.b == 25UL) || (r.a == 25UL && r.b == 5UL));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR, ExampleFromPrompt) {
  std::vector<unsigned long> nums = {3UL, 10UL, 5UL, 25UL, 2UL, 8UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, 28UL);  // 5 ^ 25
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
  EXPECT_TRUE((r.a == 5UL && r.b == 25UL) || (r.a == 25UL && r.b == 5UL));
}

TEST(MaxXOR, EmptyVectorReturnsZeros) {
  std::vector<unsigned long> nums = {};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.a, 0UL);
  EXPECT_EQ(r.b, 0UL);
  EXPECT_EQ(r.xor_value, 0UL);
}

TEST(MaxXOR, SingleElementReturnsZeros) {
  std::vector<unsigned long> nums = {42UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.a, 0UL);
  EXPECT_EQ(r.b, 0UL);
  EXPECT_EQ(r.xor_value, 0UL);
}

TEST(MaxXOR, TwoElementsOnlyPair) {
  std::vector<unsigned long> nums = {1UL, 2UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, (1UL ^ 2UL));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
  EXPECT_TRUE((r.a == 1UL && r.b == 2UL) || (r.a == 2UL && r.b == 1UL));
}

TEST(MaxXOR, AllZeros) {
  std::vector<unsigned long> nums = {0UL, 0UL, 0UL, 0UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, 0UL);
  EXPECT_EQ((r.a ^ r.b), 0UL);
}

TEST(MaxXOR, AllSameValue) {
  std::vector<unsigned long> nums = {7UL, 7UL, 7UL, 7UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, 0UL);
  EXPECT_EQ((r.a ^ r.b), 0UL);
}

TEST(MaxXOR, DuplicatesStillFindsBest) {
  std::vector<unsigned long> nums = {5UL, 25UL, 5UL, 25UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, (5UL ^ 25UL));  // 28
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
  EXPECT_TRUE((r.a == 5UL && r.b == 25UL) || (r.a == 25UL && r.b == 5UL));
}

TEST(MaxXOR, PowersOfTwo_MaxIsTwoLargestDistinct) {
  std::vector<unsigned long> nums = {1UL, 2UL, 4UL, 8UL, 16UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, (16UL ^ 8UL));  // 24
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR, IncludesMaxBitPatternsForUnsignedLong) {
  const unsigned long all_ones = std::numeric_limits<unsigned long>::max();
  std::vector<unsigned long> nums = {0UL, all_ones, 123UL, 456UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, all_ones);
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
  EXPECT_TRUE((r.a == 0UL && r.b == all_ones) ||
              (r.a == all_ones && r.b == 0UL));
}

TEST(MaxXOR, WideBitWidthNotAssuming32Bits) {
  const unsigned long hi = (std::numeric_limits<unsigned long>::digits > 32)
                               ? (1UL << 40)
                               : (1UL << 20);
  std::vector<unsigned long> nums = {hi, 0UL, 1UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, BruteMaxXorTwosComplement(nums));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR, MultipleCandidatesButCorrectValue) {
  std::vector<unsigned long> nums = {12UL, 4UL, 6UL, 2UL};
  auto r = MaxXOR<unsigned long>::MaxXORPair(nums);

  EXPECT_EQ(r.xor_value, 14UL);
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR_IntTwosComplement, MixedPosNeg_MatchesBruteForce) {
  std::vector<int> nums = {3, 10, 5, 25, -1, -8, 2, 8};

  std::vector<uint32_t> u;
  u.reserve(nums.size());
  for (int x : nums) u.push_back(static_cast<uint32_t>(x));

  auto r = MaxXOR<uint32_t>::MaxXORPair(u);

  EXPECT_EQ(r.xor_value, BruteMaxXorTwosComplement(nums));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR_IntTwosComplement, IncludesZeroAndMinusOne_MaxAllOnes) {
  std::vector<int> nums = {0, -1, 7, 42};

  std::vector<uint32_t> u;
  for (int x : nums) u.push_back(static_cast<uint32_t>(x));

  auto r = MaxXOR<uint32_t>::MaxXORPair(u);

  EXPECT_EQ(r.xor_value, std::numeric_limits<uint32_t>::max());
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
  EXPECT_TRUE((r.a == 0u && r.b == std::numeric_limits<uint32_t>::max()) ||
              (r.b == 0u && r.a == std::numeric_limits<uint32_t>::max()));
}

TEST(MaxXOR_IntTwosComplement, OnlyNegatives_MatchesBruteForce) {
  std::vector<int> nums = {-1, -2, -3, -4, -5};

  std::vector<uint32_t> u;
  for (int x : nums) u.push_back(static_cast<uint32_t>(x));

  auto r = MaxXOR<uint32_t>::MaxXORPair(u);

  EXPECT_EQ(r.xor_value, BruteMaxXorTwosComplement(nums));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR_IntTwosComplement, Extremes_MatchesBruteForce) {
  std::vector<int> nums = {std::numeric_limits<int>::min(),
                           std::numeric_limits<int>::max(), 0, -1, 1};

  std::vector<uint32_t> u;
  for (int x : nums) u.push_back(static_cast<uint32_t>(x));

  auto r = MaxXOR<uint32_t>::MaxXORPair(u);

  EXPECT_EQ(r.xor_value, BruteMaxXorTwosComplement(nums));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}

TEST(MaxXOR_IntTwosComplement, TwoElements_PosNeg) {
  std::vector<int> nums = {1, -1};

  std::vector<uint32_t> u;
  for (int x : nums) u.push_back(static_cast<uint32_t>(x));

  auto r = MaxXOR<uint32_t>::MaxXORPair(u);

  EXPECT_EQ(r.xor_value, static_cast<uint32_t>(1) ^ static_cast<uint32_t>(-1));
  EXPECT_EQ((r.a ^ r.b), r.xor_value);
}