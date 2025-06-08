#include <numeric>
#include <random>
#include <vector>

#include "GTestCommon.hpp"
#include "ReverseString.hpp"

TEST(ReverseString, EmptyString) {
  std::string input = "";
  std::string expected = "";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, SingleCharacter) {
  std::string input = "a";
  std::string expected = "a";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, EvenLengthString) {
  std::string input = "hello";
  std::string expected = "olleh";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, OddLengthString) {
  std::string input = "Hannah";
  std::string expected = "hannaH";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, PalindromeString) {
  std::string input = "madam";
  std::string expected = "madam";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, SpecialCharacters) {
  std::string input = "@#$%&";
  std::string expected = "&%$#@";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}



TEST(ReverseString, WhitespaceString) {
  std::string input = "   ";
  std::string expected = "   ";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

TEST(ReverseString, NumbersOnly) {
  std::string input = "1234567890";
  std::string expected = "0987654321";
  ReverseString(input);
  EXPECT_EQ(input, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}