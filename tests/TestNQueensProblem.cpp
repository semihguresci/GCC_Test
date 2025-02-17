#include "GTestCommon.hpp"
#include "NQueensProblem.hpp"

TEST(NQueensProblem, Empty) {
  NQueensSolver solver(0);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(NQueensProblem, One) {
  NQueensSolver solver(1);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(NQueensProblem, Two) {
  NQueensSolver solver(1);
  EXPECT_EQ(solver.Solve(), 1);
}

TEST(NQueensProblem, Four) {
  NQueensSolver solver(4);
  EXPECT_EQ(solver.Solve(), 2);
}

TEST(NQueensProblem, Eight) {
  NQueensSolver solver(8);
  EXPECT_EQ(solver.Solve(), 92);
}

TEST(NQueensProblem, Ten) {
  NQueensSolver solver(10);
  EXPECT_EQ(solver.Solve(), 724);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}