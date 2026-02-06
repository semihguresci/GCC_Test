#include "GTestCommon.hpp"
#include "MajorityElement.h"

TEST(MajorityElementTest, HandlesEmptyInput) {
  std::vector<int> nums;
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 0);
}
TEST(MajorityElementTest, SingleElement) {
  std::vector<int> nums = {5};
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 5);
}
TEST(MajorityElementTest, AllSameElements) {
  std::vector<int> nums = {2, 2, 2, 2};
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 2);
}
TEST(MajorityElementTest, MajorityAtBeginning) {
  std::vector<int> nums = {3, 3, 4, 2, 4, 4, 2, 4, 4};
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 4);
}
TEST(MajorityElementTest, MajorityAtEnd) {
  std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 2);
}
TEST(MajorityElementTest, MixedElements) {
  std::vector<int> nums = {1, 2, 3, 2, 2};
  EXPECT_EQ(MajorityElement::FindMajorityElement<int>(nums), 2);
}