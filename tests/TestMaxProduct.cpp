#include "GTestCommon.hpp"
#include "MaxProduct.hpp"

TEST(MaxProduct, EmptyVector) {
  std::vector<int> nums = {};
  auto result = MaxProduct<int>(nums);

  EXPECT_FALSE(result.has_value());
}

TEST(MaxProduct, OneVector) {
  std::vector<int> nums = {100};
  auto result = MaxProduct<int>(nums);

  EXPECT_FALSE(result.has_value());
}

TEST(MaxProduct, IntegerMaxProduct) {
  std::vector<int> nums = {-10, -30, 0, 5, 6, 100};
  auto result = MaxProduct<int>(nums);

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 600);
}

TEST(MaxProduct, DoubleMaxProduct) {
  std::vector<double> dnums = {-10.0, -30.0, 0.0, 5.0, 6.0, 100.0};
  auto result = MaxProduct<double>(dnums);

  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(*result, 600.0);
}

TEST(MaxProduct, AllNegative) {
  std::vector<int> nums = {-10, -5, -2, -1};
  auto result = MaxProduct<int>(nums);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 50);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}