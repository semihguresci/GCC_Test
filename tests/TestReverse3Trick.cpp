#include "GTestCommon.hpp"
#include "Reverse3Trick.hpp"

using namespace Reverse3Trick;

TEST(Reverse3Trick, Reverse3TrickTest) {
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> expected = {5, 6, 7, 1, 2, 3, 4};
  Reverse3Trick::RotateRight(vec, 3);

  EXPECT_EQ(vec, expected);
}