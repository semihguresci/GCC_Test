#include "GTestCommon.hpp"
#include "RotatedPeakElement.hpp"

TEST(RotatedPeakElement, FindPeakElement) {
  std::vector<int> nums1 = {3, 4, 5, 1, 2};
  EXPECT_EQ(RotatedPeakElement::FindPeakElement(nums1), 2);
  std::vector<int> nums2 = {5, 1, 2, 3, 4};
  EXPECT_EQ(RotatedPeakElement::FindPeakElement(nums2), 0);
  std::vector<int> nums3 = {2, 3, 4, 5, 1};
  EXPECT_EQ(RotatedPeakElement::FindPeakElement(nums3), 3);
  std::vector<int> nums4 = {4, 5, 1, 2, 3};
  EXPECT_EQ(RotatedPeakElement::FindPeakElement(nums4), 1);
}