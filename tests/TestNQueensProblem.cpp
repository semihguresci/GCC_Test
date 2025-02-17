#include "GTestCommon.hpp"
#include "NQueensProblem.hpp"


TEST(ValidateBTSInOrder, Negative) {
  NQueensSolver solver(-100);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(ValidateBTSInOrder, Empty) {
  NQueensSolver solver(0);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(ValidateBTSInOrder, One) {
  NQueensSolver solver(1);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(ValidateBTSInOrder, Two) {
  NQueensSolver solver(1);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(ValidateBTSInOrder, Four) {
  NQueensSolver solver(4);
  EXPECT_EQ(solver.Solve(), 2);
}

TEST(ValidateBTSInOrder, Eight) {
  NQueensSolver solver(8);
  EXPECT_EQ(solver.Solve(), 92);
}

TEST(ValidateBTSInOrder, Ten) {
  NQueensSolver solver(10);
  EXPECT_EQ(solver.Solve(), 724);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}