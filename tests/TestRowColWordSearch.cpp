#include "GTestCommon.hpp"
#include "RowColWordSearch.hpp"


TEST(RowColWordSearch, Example_FOAM_InFirstColumn) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_TRUE(RowColWordSearch::Exists(board, "FOAM"));
}

TEST(RowColWordSearch, Example_MASS_InLastRow) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_TRUE(RowColWordSearch::Exists(board, "MASS"));
}

TEST(RowColWordSearch, Finds_RowSubstring_NotStartingAtZero) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_TRUE(RowColWordSearch::Exists(board, "ACI"));
}

TEST(RowColWordSearch, Finds_ColumnSubstring_NotStartingAtZero) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_TRUE(RowColWordSearch::Exists(board, "BN"));
}

TEST(RowColWordSearch, Rejects_Diagonal) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(board, "FBO"));
}

TEST(RowColWordSearch, Rejects_TurningPath) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(board, "FOB"));
}

TEST(RowColWordSearch, Rejects_ReverseDirection) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(board, "SSAM"));

  EXPECT_FALSE(RowColWordSearch::Exists(board, "MAOF"));
}

TEST(RowColWordSearch, Rejects_NotPresent) {
  const std::vector<std::vector<char>> board = {
      {'F', 'A', 'C', 'I'},
      {'O', 'B', 'Q', 'P'},
      {'A', 'N', 'O', 'B'},
      {'M', 'A', 'S', 'S'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(
      board, "FACE"));  
  EXPECT_FALSE(RowColWordSearch::Exists(board, "NOPE"));
}

TEST(RowColWordSearch, WordLongerThanAnyRowOrCol) {
  const std::vector<std::vector<char>> board = {
      {'A', 'B'},
      {'C', 'D'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(board, "ABCDE"));
}

TEST(RowColWordSearch, EmptyWord_ReturnsTrue) {
  const std::vector<std::vector<char>> board = {
      {'A', 'B'},
      {'C', 'D'},
  };

  EXPECT_TRUE(RowColWordSearch::Exists(board, ""));
}

TEST(RowColWordSearch, EmptyBoard_ReturnsFalseUnlessEmptyWord) {
  const std::vector<std::vector<char>> empty_board;
  EXPECT_FALSE(RowColWordSearch::Exists(empty_board, "A"));
  EXPECT_TRUE(RowColWordSearch::Exists(empty_board,
                                       ""));  
}

TEST(RowColWordSearch, NonRectangularBoard_ReturnsFalse) {
  const std::vector<std::vector<char>> jagged = {
      {'A', 'B', 'C'},
      {'D', 'E'},
      {'F', 'G', 'H'},
  };

  EXPECT_FALSE(RowColWordSearch::Exists(jagged, "AB"));
}
