#include <numeric>
#include <random>
#include <vector>

#include "GTestCommon.hpp"
#include "TwoSum.hpp"

TEST(TwoSum, BasicTestCase) {
  std::vector<std::uint32_t> nums = {2, 7, 11, 15};
  std::uint32_t target = 9;
  std::vector<std::int32_t> expected = {0, 1};
  EXPECT_EQ(TwoSum(nums, target), expected);
}

TEST(TwoSum, NotAtTheBeggining) {
  std::vector<std::uint32_t> nums = {3, 2, 4};
  std::uint32_t target = 6;
  std::vector<std::int32_t> expected = {1, 2};
  EXPECT_EQ(TwoSum(nums, target), expected);
}

TEST(TwoSumTest, LargeNumbers) {
  std::vector<std::uint32_t> nums = {4000000000, 294967296, 1};
  std::uint32_t target = 4000000001;
  std::vector<std::int32_t> expected = {0, 2};
  EXPECT_EQ(TwoSum(nums, target), expected);
}
TEST(TwoSumTest, NoSolution) {
  std::vector<std::uint32_t> nums = {1, 2, 3};
  std::uint32_t target = 7;
  EXPECT_TRUE(TwoSum(nums, target).empty());
}

TEST(TwoSumTest, EmptyInput) {
  std::vector<std::uint32_t> nums;
  std::uint32_t target = 0;
  EXPECT_TRUE(TwoSum(nums, target).empty());
}

TEST(TwoSumTest, SingleElement) {
  std::vector<std::uint32_t> nums = {1};
  std::uint32_t target = 1;
  EXPECT_TRUE(TwoSum(nums, target).empty());
}

TEST(TwoSumTest, ZeroValues) {
  std::vector<std::uint32_t> nums = {0, 0, 0};
  std::uint32_t target = 0;
  std::vector<std::int32_t> expected = {0, 1};
  EXPECT_EQ(TwoSum(nums, target), expected);
}

TEST(TwoSumTest, DuplicateValues) {
  std::vector<std::uint32_t> nums = {3, 3, 2, 4};
  std::uint32_t target = 6;
  std::vector<std::int32_t> expected = {0, 1};
  EXPECT_EQ(TwoSum(nums, target), expected);

}

TEST(TwoSumTest, MultiplePossibleSolutions) {
  std::vector<std::uint32_t> nums = {3, 2, 3, 4, 5};
  std::uint32_t target = 6;
  auto result = TwoSum(nums, target);
  ASSERT_EQ(result.size(), 2);
  EXPECT_EQ(std::accumulate(result.begin(), result.end(), 0u,
                            [&nums](std::uint32_t sum, std::int32_t index) {
                              return sum + nums[index];
                            }),
            target);
}

TEST(TwoSumTest, LargeData) {
  std::vector<std::uint32_t> nums;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::uint32_t> dist(1, 1000000);
  std::uint32_t target;

  nums.resize(1000000);
  for (auto& num : nums) {
    num = dist(gen);
  }

  nums[500000] = 123456;
  nums[750000] = 876544;
  target = 1000000;

  auto result = TwoSum(nums, target);
  ASSERT_EQ(result.size(), 2);
  EXPECT_EQ(std::accumulate(result.begin(), result.end(), 0u,
                            [&nums](std::uint32_t sum, std::int32_t index) {
                              return sum + nums[index];
                            }),
            target);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}