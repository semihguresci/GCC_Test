#include "GTestCommon.hpp"
#include "Power.hpp"

TEST(Power, PowerTests) {
  int base1 = 2, exponent1 = 0, result1 = 1;
  int base2 = 2, exponent2 = 10, result2 = 1024;
  int base3 = 3, exponent3 = 3, result3 = 27;
  int base4 = 5, exponent4 = 5, result4 = 3125;
  int base5 = 0, exponent5 = 10, result5 = 0;
  int base6 = 10, exponent6 = 1, result6 = 10;
  int base7 = 2, exponent7 = 16, result7 = 65536;
  int base8 = -2, exponent8 = 3, result8 = -8;
  int base9 = -2, exponent9 = 4, result9 = 16;

  EXPECT_EQ(PowerIterative(base1, exponent1), result1);
  EXPECT_EQ(PowerIterative(base2, exponent2), result2);
  EXPECT_EQ(PowerIterative(base3, exponent3), result3);
  EXPECT_EQ(PowerIterative(base4, exponent4), result4);
  EXPECT_EQ(PowerIterative(base5, exponent5), result5);
  EXPECT_EQ(PowerIterative(base6, exponent6), result6);
  EXPECT_EQ(PowerIterative(base7, exponent7), result7);
  EXPECT_EQ(PowerIterative(base8, exponent8), result8);
  EXPECT_EQ(PowerIterative(base9, exponent9), result9);

  EXPECT_EQ(PowerRecursive(base1, exponent1), result1);
  EXPECT_EQ(PowerRecursive(base2, exponent2), result2);
  EXPECT_EQ(PowerRecursive(base3, exponent3), result3);
  EXPECT_EQ(PowerRecursive(base4, exponent4), result4);
  EXPECT_EQ(PowerRecursive(base5, exponent5), result5);
  EXPECT_EQ(PowerRecursive(base6, exponent6), result6);
  EXPECT_EQ(PowerRecursive(base7, exponent7), result7);
  EXPECT_EQ(PowerRecursive(base8, exponent8), result8);
  EXPECT_EQ(PowerRecursive(base9, exponent9), result9);

  EXPECT_EQ(PowerBitwise(base1, exponent1), result1);
  EXPECT_EQ(PowerBitwise(base2, exponent2), result2);
  EXPECT_EQ(PowerBitwise(base3, exponent3), result3);
  EXPECT_EQ(PowerBitwise(base4, exponent4), result4);
  EXPECT_EQ(PowerBitwise(base5, exponent5), result5);
  EXPECT_EQ(PowerBitwise(base6, exponent6), result6);
  EXPECT_EQ(PowerBitwise(base7, exponent7), result7);
  EXPECT_EQ(PowerBitwise(base8, exponent8), result8);
  EXPECT_EQ(PowerBitwise(base9, exponent9), result9);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}