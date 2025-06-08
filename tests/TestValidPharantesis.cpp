#include <string_view>

#include "GTestCommon.hpp"
#include "ValidPharantesis.hpp"

// Test valid cases
TEST(IsValidPharantesis, ValidCases) {
  EXPECT_TRUE(IsValidPharantesis(""));
  EXPECT_TRUE(IsValidPharantesis("()"));
  EXPECT_TRUE(IsValidPharantesis("()[]{}"));
  EXPECT_TRUE(IsValidPharantesis("({[]})"));
  EXPECT_TRUE(IsValidPharantesis("(([]){})"));
}

// Test invalid cases
TEST(IsValidPharantesis, InvalidCases) {
  EXPECT_FALSE(IsValidPharantesis("("));
  EXPECT_FALSE(IsValidPharantesis(")"));
  EXPECT_FALSE(IsValidPharantesis("(]"));
  EXPECT_FALSE(IsValidPharantesis("([)]"));
  EXPECT_FALSE(IsValidPharantesis("())"));
  EXPECT_FALSE(IsValidPharantesis("(()"));
  EXPECT_FALSE(IsValidPharantesis("{"));
  EXPECT_FALSE(IsValidPharantesis("}"));
}

// Test edge cases
TEST(IsValidPharantesis, EdgeCases) {
  EXPECT_TRUE(IsValidPharantesis(""));        
  EXPECT_FALSE(IsValidPharantesis(" "));      
  EXPECT_FALSE(IsValidPharantesis("( )"));    
  EXPECT_FALSE(IsValidPharantesis("([]){"));
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}