#include "GTestCommon.hpp"
#include "Puzzle.hpp"

TEST(Puzzle, FactorialTest) {
  EXPECT_EQ(puzzle::Factorial(0), 1);
  EXPECT_EQ(puzzle::Factorial(1), 1);
  EXPECT_EQ(puzzle::Factorial(2), 2);
  EXPECT_EQ(puzzle::Factorial(3), 6);
  EXPECT_EQ(puzzle::Factorial(5), 120);
  EXPECT_EQ(puzzle::Factorial(6), 720);
  EXPECT_EQ(puzzle::Factorial(7), 5040);
  EXPECT_EQ(puzzle::Factorial(10), 3628800);
  EXPECT_THROW(puzzle::Factorial(-1), std::invalid_argument);
  EXPECT_THROW(puzzle::Factorial(-5), std::invalid_argument);
}

TEST(Puzzle, CombinationsTest) {
  EXPECT_THROW(puzzle::Combinations(-1, 2), std::invalid_argument);
  EXPECT_THROW(puzzle::Combinations(5, -1), std::invalid_argument);
  EXPECT_THROW(puzzle::Combinations(3, 5), std::invalid_argument);

  {
    std::vector<std::vector<int>> result = puzzle::Combinations(5, 0);
    std::vector<std::vector<int>> expected = {{}};
    EXPECT_EQ(result, expected);
  }
  {
    std::vector<std::vector<int>> result = puzzle::Combinations(0, 0);
    std::vector<std::vector<int>> expected = {{}};
    EXPECT_EQ(result, expected);
  }
  {
    std::vector<std::vector<int>> result = puzzle::Combinations(3, 1);
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}};
    EXPECT_EQ(result, expected);
  }
  {
    std::vector<std::vector<int>> result = puzzle::Combinations(3, 3);
    std::vector<std::vector<int>> expected = {{1, 2, 3}};
    EXPECT_EQ(result, expected);
  }
  {
    std::vector<std::vector<int>> result = puzzle::Combinations(4, 2);
    std::vector<std::vector<int>> expected = {{1, 2}, {1, 3}, {1, 4},
                                              {2, 3}, {2, 4}, {3, 4}};
    EXPECT_EQ(result, expected);
  }
  {
    std::vector<std::vector<int>> result = puzzle::Combinations(5, 3);
    std::vector<std::vector<int>> expected = {
        {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 3, 4}, {1, 3, 5},
        {1, 4, 5}, {2, 3, 4}, {2, 3, 5}, {2, 4, 5}, {3, 4, 5}};
    EXPECT_EQ(result, expected);
  }
}

TEST(Puzzle, PermutationsTest) {
  {
    std::string key = "";
    std::vector<std::string> result =
        puzzle::PermutationsRecursive(key, 0, key.size() - 1);
    std::vector<std::string> expected = {};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "";
    std::vector<std::string> result =
        puzzle::PermuationsIterative(key, 0, key.size() - 1);
    std::vector<std::string> expected = {};
    EXPECT_EQ(result, expected);
  }

  {
    std::string key = "a";
    std::vector<std::string> result =
        puzzle::PermutationsRecursive(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"a"};
    EXPECT_EQ(result, expected);
  }

  {
    std::string key = "a";
    std::vector<std::string> result =
        puzzle::PermuationsIterative(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"a"};
    EXPECT_EQ(result, expected);
  }

  {
    std::string key = "ab";
    std::vector<std::string> result =
        puzzle::PermutationsRecursive(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"ab", "ba"};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "ab";
    std::vector<std::string> result =
        puzzle::PermuationsIterative(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"ab", "ba"};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "abc";
    std::vector<std::string> result =
        puzzle::PermutationsRecursive(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"abc", "acb", "bac",
                                         "bca", "cba", "cab"};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "abc";
    std::vector<std::string> result =
        puzzle::PermuationsIterative(key, 0, key.size() - 1);
    std::vector<std::string> expected = {"abc", "bac", "cab",
                                         "acb", "bca", "cba"};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "abcd";
    std::vector<std::string> result = puzzle::PermutationsRecursive(key, 1, 2);
    std::vector<std::string> expected = {"abcd", "acbd"};
    EXPECT_EQ(result, expected);
  }
  {
    std::string key = "abcd";
    std::vector<std::string> result = puzzle::PermuationsIterative(key, 1, 2);
    std::vector<std::string> expected = {"abcd", "acbd"};
    EXPECT_EQ(result, expected);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}