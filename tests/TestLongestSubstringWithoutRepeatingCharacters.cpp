#include "GTestCommon.hpp"
#include "LongestSubstringWithoutRepeatingCharacters.hpp"

using namespace LongestSubstringWithoutRepeatingCharacters;

TEST(LongestSubstringTest, EmptyString) {
  EXPECT_EQ(LengthOfLongestSubstring(""), 0);
}

TEST(LongestSubstringTest, AllUniqueCharacters) {
  EXPECT_EQ(LengthOfLongestSubstring("abcde"), 5);
}

TEST(LongestSubstringTest, AllSameCharacters) {
  EXPECT_EQ(LengthOfLongestSubstring("aaaaa"), 1);
}

TEST(LongestSubstringTest, RepeatedCharacters) {
  EXPECT_EQ(LengthOfLongestSubstring("abcabcbb"), 3);
}

TEST(LongestSubstringTest, SubstringInMiddle) {
  EXPECT_EQ(LengthOfLongestSubstring("pwwkew"), 3);
}

TEST(LongestSubstringTest, SingleCharacter) {
  EXPECT_EQ(LengthOfLongestSubstring("a"), 1);
}

TEST(LongestSubstringTest, TwoCharactersSame) {
  EXPECT_EQ(LengthOfLongestSubstring("aa"), 1);
}

TEST(LongestSubstringTest, TwoCharactersDifferent) {
  EXPECT_EQ(LengthOfLongestSubstring("ab"), 2);
}

TEST(LongestSubstringTest, LongStringWithRepeats) {
  EXPECT_EQ(LengthOfLongestSubstring(
                "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"),
            26);
}

TEST(LongestSubstringTest, MixedCaseCharacters) {
  EXPECT_EQ(LengthOfLongestSubstring("aAbBcCdD"), 8);
}

TEST(LongestSubstringTest, WithSpaces) {
  EXPECT_EQ(LengthOfLongestSubstring("a b c d e"), 3);
  EXPECT_EQ(LengthOfLongestSubstring("   "), 1);

  EXPECT_EQ(LengthOfLongestSubstring("a\tb\nc"), 5);

  EXPECT_EQ(LengthOfLongestSubstring("  abc  "), 4);

  EXPECT_EQ(LengthOfLongestSubstring("a bc  de"), 4);

  EXPECT_EQ(LengthOfLongestSubstring("a b a b"), 3);

  EXPECT_EQ(LengthOfLongestSubstring("x\tx\ty"), 3);
}

TEST(LongestSubstringTest, SpecialCharacters) {
  EXPECT_EQ(LengthOfLongestSubstring("!@#$%^&*()"), 10);
}

TEST(LongestSubstringTest, RepeatedPattern) {
  EXPECT_EQ(LengthOfLongestSubstring("ababababab"), 2);
}

TEST(LongestSubstringTest, LongNonRepeatingSubstringAtEnd) {
  EXPECT_EQ(LengthOfLongestSubstring("abcdeffghijklm"), 8);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}