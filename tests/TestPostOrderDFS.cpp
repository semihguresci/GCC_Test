#include "PostOrderDFS.hpp"
#include "GTestCommon.hpp"

using namespace PostOrderDFS;

TEST(PostOrderDFS, PostOrderDFSTest) {
  // Construct the expression tree for ((3 + 2) * (4 - 1))
  auto root = std::make_unique<Node>(
	  "*",
	  std::make_unique<Node>(
		  "+",
		  std::make_unique<Node>("3"),
		  std::make_unique<Node>("2")),
	  std::make_unique<Node>(
		  "-",
		  std::make_unique<Node>("4"),
		  std::make_unique<Node>("1")));
  long long result = Evaluate(root);
  EXPECT_EQ(result, 15);  // (3 + 2) * (4 - 1) = 5 * 3 = 15
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}