#include "JumpGame.hpp"
#include "GTestCommon.hpp"


TEST(JumpGameTest, HandlesEmptyInput) {
  std::vector<int> nums;
  EXPECT_FALSE(JumpGame::canJump(nums));
}

TEST(JumpGameTest, SingleElement) {
  std::vector<int> nums = {0};
  EXPECT_TRUE(JumpGame::canJump(nums));
}

TEST(JumpGameTest, CanJumpToEnd) {
  std::vector<int> nums = {1, 3, 1, 2, 0, 1};
  EXPECT_TRUE(JumpGame::canJump(nums));
}

TEST(JumpGameTest, CannotJumpToEnd) {
  std::vector<int> nums = {1, 2, 1, 0, 0};
  EXPECT_FALSE(JumpGame::canJump(nums));
}