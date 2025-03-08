#include "Fibonacci.hpp"
#include "GTestCommon.hpp"

TEST(Fibonacci, FibonacciTests) {
  std::uint64_t base1 = 0, result1 = 0;
  std::uint64_t base2 = 1, result2 = 1;
  std::uint64_t base3 = 2, result3 = 1;
  std::uint64_t base4 = 3, result4 = 2;
  std::uint64_t base5 = 4, result5 = 3;
  std::uint64_t base6 = 5, result6 = 5;
  std::uint64_t base7 = 10, result7 = 55;
  std::uint64_t base8 = 20, result8 = 6765;
  std::uint64_t base9 = 30, result9 = 832040;
  std::uint64_t base10 = 50, result10 = 12586269025;

  EXPECT_EQ(FibonacciIterative(base1), result1);
  EXPECT_EQ(FibonacciIterative(base2), result2);
  EXPECT_EQ(FibonacciIterative(base3), result3);
  EXPECT_EQ(FibonacciIterative(base4), result4);
  EXPECT_EQ(FibonacciIterative(base5), result5);
  EXPECT_EQ(FibonacciIterative(base6), result6);
  EXPECT_EQ(FibonacciIterative(base7), result7);
  EXPECT_EQ(FibonacciIterative(base8), result8);
  EXPECT_EQ(FibonacciIterative(base9), result9);
  EXPECT_EQ(FibonacciIterative(base10), result10);

  EXPECT_EQ(FibonacciDP<std::uint64_t>(base1), result1);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base2), result2);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base3), result3);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base4), result4);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base5), result5);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base6), result6);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base7), result7);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base8), result8);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base9), result9);
  EXPECT_EQ(FibonacciDP<std::uint64_t>(base10), result10);

  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base1), result1);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base2), result2);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base3), result3);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base4), result4);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base5), result5);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base6), result6);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base7), result7);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base8), result8);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base9), result9);
  EXPECT_EQ(FibonacciMatrix<std::uint64_t>().Fibonacci(base10), result10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}